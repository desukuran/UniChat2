// Behavior.cpp: implementation of the CBehavior class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Behavior.h"

#include "Parser.h"
#include "ResMan.h"

#include "UC2Ani/DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CParser	gParser;
extern CResMan	gResMan;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
CBehavior::CBehavior()
{
	m_nID	= 0;
	m_nCells = 0;
	m_aCell = NULL;
	m_sDisp = CSize(0, 0);
}

CBehavior::~CBehavior()
{
	if (m_aCell)
		delete [] m_aCell;
}

// Loop in a line
BOOL CBehavior::Load(const int nID)
{
	// 0=1,(0,10,-1)(1,10,5,0,-1)(2,10,10,0,-1);	Walk
	// 1=1,(0)(1)(2); Changing direction
	// 2=1,(0)(1,10,0,0,-1)(2)(3)(4)(5)(6); Say
	m_nID = nID;
	m_nCells = gParser.CountOccurrencesUpto(')', ';');
	if (m_nCells <= 0)
	{
		return FALSE;
	}
	m_aCell = new Cell[m_nCells];
	gParser.GetValueRightToken(m_nRepeat, ',');
	for (int i=0; i < m_nCells; i++)
	{
		// initialize with default values
		m_aCell[i].wIO		= DEFAULT_IO;
		m_aCell[i].nTicks	= 10;
		m_aCell[i].ptDisp	= CPoint(0, 0);
		m_aCell[i].nSI		= -1;
		char* p = gParser.SetLeftToken('(');
		if (!p)
		{
			CString msg;
			msg.Format("Syntax Error in Behavior (ID=%d)\"", nID);
			AfxMessageBox(msg);
			return FALSE;
		}
		while (!IsNum(*p))
		{
			switch (*p)
			{
			case '#': m_aCell[i].wIO |= OPACITY_75;		break;
			case '*': m_aCell[i].wIO |= OPACITY_50;		break;
			case '/': m_aCell[i].wIO |= OPACITY_25;		break;
			case '|': m_aCell[i].wIO |= OPACITY_12;		break;
			case '~': m_aCell[i].wIO |= OPACITY_0;		break;
			case '-': m_aCell[i].wIO |= IMAGE_FLIP;		break; 
			case '^': m_aCell[i].wIO |= NO_COLORKEY;	break; 
			}
			gParser.SetCurrent(++p);
		}
		p = gParser.GetValueRightToken(m_aCell[i].nID, ')', ',');	// priority is for ')'
		if (!p)
		{
			TRACE0("Error reading in CBehavior::Load()\n");
			return FALSE;
		}
		if (*p == '(' || *p == ';')		// next brace begins or end of...
			continue;
		
		p = gParser.GetValueRightToken(m_aCell[i].nTicks, ')', ',');
		if (!p)
		{
			m_aCell[i].nTicks	= 5;	// Although not found, the parameter can be changed
			continue;
		}
		if (*p == '(' || *p == ';')
			continue;
		
		p = gParser.GetValueRightToken(m_aCell[i].ptDisp.x, ')', ',');
		if (!p)
		{
			m_aCell[i].ptDisp.x	= 0;
			continue;
		}
		else
			m_sDisp.cx += m_aCell[i].ptDisp.x;
		if (*p == '(' || *p == ';')
			continue;
		
		p = gParser.GetValueRightToken(m_aCell[i].ptDisp.y, ')', ',');
		if (!p)
		{
			m_aCell[i].ptDisp.y	= 0;
			continue;
		}
		else
			m_sDisp.cy += m_aCell[i].ptDisp.y;
		if (*p == '(' || *p == ';')
			continue;

		CString strSndName;
		p = gParser.GetValueRightToken(strSndName, ')');
		if (!p)
		{
			m_aCell[i].nSI		= -1;
			continue;
		}
		else
		{
			m_aCell[i].nSI	= gResMan.GetWaveID(strSndName);
		}
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LPCSTR	BEHAVIOR_NAME[] =
{
	"STANDF",	// States
	"STANDB",
	"STANDINGF",
	"STANDINGB",
	"MORPHF",
	"MORPHB",
	"MORPHINGF",
	"MORPHINGB",
	"DOZEF",
	"DOZEB",
	"RES_STATE1",
	"RES_STATE2",
	"WALKF",	// Movements
	"WALKB",
	"UPF",
	"UPB",
	"DOWNF",
	"DOWNB",
	"MORPHWALKF",
	"MORPHWALKB",
	"RES_MOVE1",
	"RES_MOVE2",
	"CHAT",		// Gestures
	"ENTER",
	"EXIT",
	"SMILE",
	"MAD",
	"HELLO",
	"CRY",
	"SCRATCH",
	"PICK",
	"SPECIAL",
	"WIGGLEB",
	"PUNCHF",
	"PUNCHB",
	"BEATENF",
	"BEATENB",
//	"TURN180",
//	"TURN360",
	"RES_ACTION1",
	"RES_ACTION2"
};

CActorDesc::CActorDesc()
{
	m_aBeh	= NULL;
	m_nBehs	= 0;
}

CActorDesc::~CActorDesc()
{
	if (m_aBeh)
		delete [] m_aBeh;
}

// If the requested Behavior ID is not found in this Actor Description,
// return NULL. CResMan::GetActorBehavior will deal with that case.
CBehavior* CActorDesc::GetBehavior(const int nID)
{
	for (int i=0; i < m_nBehs; i++)
	{
		if (m_aBeh[i].GetID() == nID)
			return &m_aBeh[i];
	}
	return NULL;
}

BOOL CActorDesc::Load(CTextFileBuffer& tfb)
{
	// #ACTOR=aman_000,°ÅºÏ³²0,50;
	gParser.GetValueRightToken(m_strResName, ',');
	gParser.GetValueRightToken(m_strNick, ',');
	gParser.GetValueRightToken(m_nMSPT, ',', ';');

	if (m_nBehs <= 0)
		return TRUE;

	m_aBeh = new CBehavior[m_nBehs];	// CActorDesc::SetNumBehaviors
	// Read overloaded behaviors
	for (int nBeh=0; (nBeh < m_nBehs) && tfb.ReadString(); )
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())
			continue;
		if (gParser.SetLeftToken('{'))
		{
			if (gParser.SetLeftToken('}'))
				break;
			continue;
		}
		if (gParser.SetLeftToken('}'))
			break;
		CString strBuf;
		if (gParser.GetValueRightToken(strBuf, '='))
		{
			int nID = GetIDFromString(strBuf);
			if (nID >= 0)
			{
				m_aBeh[nBeh++].Load(nID);
			}
			else
			{
				strBuf += ": Behavior not indexed!";
				AfxMessageBox(strBuf);
			}
		}
	}
	return TRUE;
}

int CActorDesc::GetIDFromString(const CString& strName) const
{
	for (int i=0; i < AB_RES_ACTION2; i++)
	{
		if (lstrcmpi(BEHAVIOR_NAME[i], strName) == 0)
			return i;
	}
	return -1;
}