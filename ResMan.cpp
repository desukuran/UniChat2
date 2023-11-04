//	ResMan: Resource Manager
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================
//
/* ==========================================================
; "resrc000.rit"	for resrc000.bmc
;=========================================
; Resource Info Specification
; RIT: Resource Information Table
; Specification written by Soomin Kim
; Feb 1998, Samsung SDS
;=========================================
; filename=[(col,row)][,(cz.x,cz.y)][,nickname];
;   filename = resource type flag(1) + name(4) + serial(3);
;   resource type flag = t(TILE), s(STATIC), i(ANI), a(AVATAR), w(WAVE), m(MIDI)
;   (col,row) = # of cells in (column, row); for STATIC this attribute is omitted
;   (cz.x,cz.y) = center of z-order in (x, y) pixel position from the left-top
;   nickname = nickname for actor

// Think of tile as a PhasedSprite
#TIL=	// TILE
{
	tcity001=(1,4);
...
}
#STT=	// STATIC Sprites
{
	ccity002=(23,28);		// Earth Position
...
}
#ANI=	// ANIMATED Sprites
{
	wroom001=(1,17),(34,8);		// 34,22
	iadvt000=(1,3),(123,321);	// not exist
...
}
#AVT=	// AVATAR
{
	aman_001=(11,4),(27,45),°ÅºÏ;
...
}
#WAV=
{
	wwhip;	// wwhip.wav
	...
}
#MID=
{
	mtest;	// mtest.mid
	...
}

// Comments
// Resources are sequentially numbered according to the order in RIT.
// BMP file merger will read this info and then load each bitmap file
// with the same name as it's id (+.bm).

; ACTOR SECTION
; (*i): - change orientation, * 50%, / 25%, | 12%, ~ 0%, ^ don't USE_COLORKEY
; #ACTORBASE=nMSPT	// Basic formula for all the actors
; #ACTOR=id			// Overridden formula for special cases
; {
;	// nMSPT is Milliseconds per Tick
;	// Behaviors
;	0=nRepeatCount,(cell index(, delay ticks(, displacement_x, displacement_y(, sound id))))...;
;	// nRepeatCount = 0 for infinite loop, - value for pendulum movement
;	// delay ticks;  5 = fast; 10 = moderate; 15 = slow
; }
; #COACTOR=...

#ACTORBASE=
{
	STANDF		=1,(0);
	STANDB		=1,(8);
...
}

#ACTOR=aman_000;
{
	SPECIAL		=1,...
...
}
==========================================================*/

#include "stdafx.h"

#include "ResMan.h"
#include "Parser.h"

#include "UC2Ani/DIB.h"
#include "UC2Ani/PhSprite.h"
#include "Behavior.h"
#include "Actor.h"
#include "UC2Ani/Sound.h"
#include "UC2Ani/MCIObj.h"

extern CParser gParser;

double GetMapEditorVersion()
{
	// V0.90 Feb 1998
	// V0.99 Mar 7, 1998	integer Resource ID
	// V1.00 Mar 11, 1998	MIT merged into SIT, Hyperlink
	// V1.01 Mar 17, 1998	DEFAULT_IO=0x1000 => 0x0000
	return 1.01;
}

LPCTSTR RESFILE_FILTER = "Resource Information Tables(*.RIT)|*.RIT|"
						"All files (*.*)|*.*||";
LPCTSTR RES_BMPEXT = ".bmp";	// ".bm"
LPCTSTR ACTOR_SHADOW_NAME = "cs00|cshad001";
LPCTSTR PUBLIC_STAGE_NAME_FORMAT	= "[p2/%s]";
LPCTSTR MUD_STAGE_NAME_FORMAT		= "[u2/%s]00";

static const PALETTEENTRY apeMASTER[256] =
{
#include "U2Pal.Inc"	// 256 Color Table
};

const char* DATA_PATH = 
#ifdef	_DEBUG
#ifdef MAPEDITOR
	"\\data\\";
#else
#ifdef	_MALL
	"\\Mall\\";
#else
	"\\MapEd\\data\\";
#endif
#endif
#else
	"\\";
#endif

///////////////////////////////////////////////////////////////////

WORD CResMan::CSpriteInfo::GetType()
{
	int iDS = m_strName.Find('|');
	if (iDS >= 0)	// found
		iDS++;
	else
		iDS = 0;
	switch (tolower(m_strName[iDS]))
	{
	case 't':	return SPRITE_TILE;
	case 'w':	return SPRITE_WALL;
	case 'c':	return SPRITE_STATIC;
	case 'i':	return SPRITE_PHASED;
	case 'a':	return SPRITE_ACTOR;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////

CResMan::CResMan()
{
	TRACE0("CResMan::CResMan()\n");
	m_nSprites		= 0;
	m_aSI			= NULL;
	m_nWaves		= 0;
	m_aWave			= NULL;
	m_nActorDescs	= 0;
	m_aActorDesc	= NULL;
	m_nStageNames	= 0;
	m_aStageName	= NULL;
	m_nServerIPs	= 0;
	m_aServerIP		= NULL;
	m_nResFiles		= 1;
	m_strResFile.Empty();
	m_bMute			= FALSE;
	m_nBubbleTextLimit	= GetDefaultBubbleTextLimit();
	m_nBubbleTime		= GetDefaultBubbleTime();

	CString strRes;
	int len=512;
	char* psz = strRes.GetBuffer(len);
	::GetCurrentDirectory(len, psz);
	strRes.ReleaseBuffer();
	strRes += DATA_PATH;
	SetResPath(strRes);
	TRACE("CResMan::CResMan - SetResPath(%s)\n", strRes);
}

CResMan::~CResMan()
{
	TRACE0("CResMan::~CResMan()\n");
	DeleteResources();
}

void CResMan::DeleteResources()
{
	if (m_aSI)
		delete [] m_aSI;
	m_aSI		= NULL;
	m_nSprites	= 0;

	if (m_aWave)
	{
		for (int i=0; i < m_nWaves; i++)
		{
			CWaveData& wd = m_aWave[i];
			if (wd.m_pWave)
				delete wd.m_pWave;
		}
		delete [] m_aWave;
	}
	m_aWave = NULL;
	m_nWaves = 0;
	if (m_aMIDI)
		delete [] m_aMIDI;
	m_nMIDIs = 0;

	if (m_aActorDesc)
		delete [] m_aActorDesc;
	m_aActorDesc	= NULL;
	m_nActorDescs	= 0;

	if (m_aStageName)
		delete [] m_aStageName;
	m_nStageNames	= 0; 

	if (m_aServerIP)
		delete [] m_aServerIP;
	m_nServerIPs	= 0; 

	RemoveAllDIBs();
}

void CResMan::CountItems(CTextFileBuffer& tfb)
{
	m_nSprites	= 0;
	m_nWaves	= 0;
	m_nMIDIs	= 0;
	m_nStageNames = 0;
	m_nServerIPs = 0;
	int nAD=0;
	while (tfb.ReadString()) 
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())	// At first, check if it's a comment line
			continue;
		CString strBuf;
		if (!gParser.SetLeftToken('#') ||
			!gParser.GetValueRightToken(strBuf, '='))
			continue;		// get next line
		if ((lstrcmpi(strBuf, "TIL") == 0) ||	// matching!
			(lstrcmpi(strBuf, "STT") == 0) ||
			(lstrcmpi(strBuf, "ANI") == 0) ||
			(lstrcmpi(strBuf, "AVT") == 0))
		{
			m_nSprites += CountContents(tfb);
		}
		else if (lstrcmpi(strBuf, "WAV") == 0)
		{
			m_nWaves += CountContents(tfb, ';');
		}
		else if (lstrcmpi(strBuf, "MID") == 0)
		{
			m_nMIDIs += CountContents(tfb, ';');
		}
		else if (lstrcmpi(strBuf, "STAGE") == 0)
		{
			m_nStageNames += CountContents(tfb, ';');
		}
		else if (lstrcmpi(strBuf, "SERVERIP") == 0)
		{
			m_nServerIPs += CountContents(tfb, ';');
		}
		else if (lstrcmpi(strBuf, "ACTOR") == 0)	// matching!
		{
			m_aActorDesc[nAD++].SetNumBehaviors(CountContents(tfb));
		}
	}
	tfb.SeekToBegin();
}

// Count the number of lines that matches a specified string between '#' and '='
int CResMan::CountHeaders(CTextFileBuffer& tfb, const char* szToken)
{
	int i=0;
	while (tfb.ReadString()) 
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())	// At first, check if it's a comment line
			continue;
		CString strBuf;
		if (!gParser.SetLeftToken('#') ||	// get next line
			!gParser.GetValueRightToken(strBuf, '='))
			continue;
		if (lstrcmpi(strBuf, szToken) == 0)	// matching!
			i++;
	}
	tfb.SeekToBegin();
	return i;
}

// Count the number of lines that include token('=') between { and }
int CResMan::CountContents(CTextFileBuffer& tfb, const char token)
{
	int i=0;
	while (tfb.ReadString()) 
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())		// At first, check if it's a comment line
			continue;
		if (gParser.SetLeftToken('{'))	// Begin
		{
			if (gParser.SetLeftToken('}'))	// {}
				break;
			continue;	// get next line
		}
		if (gParser.SetLeftToken('}'))	// End of contents
			break;	// out of while loop
		if (gParser.SetLeftToken(token))
			i++;		// Anyway, we should increase the counter
	}
	return i;
}

BOOL CResMan::Initialize(CTextFileBuffer& tfb)
{
	DeleteResources();

	m_nActorDescs = CountHeaders(tfb, "ACTOR");
	//////////// Initialize Actor Behaviors
	if (m_nActorDescs <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_BEHAVIORS);
//		return FALSE;
	}
	else
	{
		m_aActorDesc = new CActorDesc[m_nActorDescs];
	}
	TRACE("# of Actor Descriptions = %d\n", m_nActorDescs);

	CountItems(tfb);

	//////////// Initialize Sprite Informations
	if (m_nSprites <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_SPRITES);
		return FALSE;
	}
	else
	{
		m_aSI = new CSpriteInfo[m_nSprites];
	}
	TRACE("# of Sprites = %d\n", m_nSprites);

	if (m_nWaves <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_WAVES);
//		return FALSE;
	}
	else
	{
		m_aWave = new CWaveData[m_nWaves];
	}
	TRACE("# of Waves = %d\n", m_nWaves);

	if (m_nMIDIs <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_MIDIS);
//		return FALSE;
	}
	else
	{
		m_aMIDI = new CString[m_nMIDIs];
	}
	TRACE("# of MIDIs = %d\n", m_nMIDIs);

	if (m_nStageNames <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_STAGES);
//		return FALSE;
	}
	else
	{
		m_aStageName = new CString[m_nStageNames];
	}
	TRACE("# of Stage Names = %d\n", m_nStageNames);

	if (m_nServerIPs <= 0)
	{
		AfxMessageBox(IDS_RIT_NO_SERVERIPS);
//		return FALSE;
	}
	else
	{
		m_aServerIP = new CString[m_nServerIPs];
	}
	TRACE("# of Server IPs = %d\n", m_nServerIPs);

	return TRUE;
}

BOOL CResMan::SetResPath(LPCSTR path)
{
	m_strResPath = path;
	int len = lstrlen(path);
	if (path[len-1] != '\\')
		m_strResPath += "\\";
	return TRUE;
}

// Modify this so that it can handle multiple RIT files (resrc00?.rit)
BOOL CResMan::Load(LPCSTR path)
{
	TRACE0("CResMan::Load()\n");
	if ((path == NULL) || (lstrlen(path) == 0))
	{
		::SetCurrentDirectory(m_strResPath);
		// Show an Open File dialog to get the name.
		CFileDialog dlg(TRUE,	// Open
						NULL,	// No default extension
						m_strResFile,	// Initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
						RESFILE_FILTER);
        if (dlg.DoModal() == IDOK)
			m_strResFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{
		// Copy the supplied file path.
		m_strResFile = path;
		IncludePath(m_strResFile);
	}

	CTextFileBuffer tfb(gParser.GetMaxBuffer());
	if (!tfb.Load(m_strResFile))
	{
		return FALSE;
	}

	ExcludePath(m_strResFile);

	if (!Initialize(tfb))
	{
		return FALSE;
	}

	int i=0;
	int ad=0;
	CString strTemp;
	BOOL bOldVersion = FALSE;

	while (tfb.ReadString())
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())
			continue;
		if (!gParser.SetLeftToken('#'))
			continue;
		CString strBuf;
		if (!gParser.GetValueRightToken(strBuf, '='))
			continue;

		//////////////////////////////////////
		if (lstrcmpi(strBuf, "VERSION") == 0)
		{
			gParser.SetLeftToken('=');
			double	fVersion;
			gParser.GetValueRightToken(fVersion, ';');
			if (fVersion <= 0.90)
			{
				CString strMsg;
				strMsg.Format("Old Version %.2f", fVersion);
				AfxMessageBox(strMsg);
				bOldVersion = TRUE;
			}
		}
		else if (lstrcmpi(strBuf, "TIL") == 0)	// matching!
		{
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, '='))
					continue;
				m_aSI[i].m_strName = strTemp;
				gParser.GetValueRightToken(m_aSI[i].m_sColRow, ',', ';');
				m_aSI[i].m_sEarth = CSize(64/2,0);
				gParser.GetValueRightToken(m_aSI[i].m_strHyperlink, ',', ';');
				i++;
			}
		}
		else if (lstrcmpi(strBuf, "STT") == 0)
		{
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, '='))
					continue;
				strTemp.MakeLower();
				m_aSI[i].m_strName = strTemp;
				m_aSI[i].m_sColRow = CSize(1, 1);
				gParser.GetValueRightToken(m_aSI[i].m_sEarth, ',', ';');
				gParser.GetValueRightToken(m_aSI[i].m_strHyperlink, ',', ';');
				i++;
			}
		}
		else if (lstrcmpi(strBuf, "ANI") == 0)
		{
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, '='))
					continue;
				strTemp.MakeLower();
				m_aSI[i].m_strName = strTemp;
				gParser.GetValueRightToken(m_aSI[i].m_sColRow, ',');
				gParser.GetValueRightToken(m_aSI[i].m_sEarth, ',', ';');
				gParser.GetValueRightToken(m_aSI[i].m_strHyperlink, ',', ';');
				i++;
			}
		}
		else if (lstrcmpi(strBuf, "AVT") == 0)
		{
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, '='))
					continue;
				strTemp.MakeLower();
				m_aSI[i].m_strName = strTemp;
				gParser.GetValueRightToken(m_aSI[i].m_sColRow, ',');
				gParser.GetValueRightToken(m_aSI[i].m_sEarth, ',', ';');
				gParser.GetValueRightToken(m_aSI[i].m_strHyperlink, ',', ';');
				i++;
			}
		}
		else if (lstrcmpi(strBuf, "WAV") == 0)
		{
			int w=0;
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, ';'))
					continue;
				if (w >= m_nWaves)
					break;
				strTemp.MakeLower();
				m_aWave[w++].m_strName = strTemp;
			}
		}
		else if (lstrcmpi(strBuf, "MID") == 0)
		{
			int m=0;
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, ';'))
					continue;
				if (m >= m_nMIDIs)
					break;
				strTemp.MakeLower();
				m_aMIDI[m++] = strTemp;
			}
		}
		else if (lstrcmpi(strBuf, "STAGE") == 0)
		{
			int s=0;
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, ';'))
					continue;
				if (s >= m_nStageNames)
					break;
				strTemp.MakeLower();
				m_aStageName[s++] = strTemp;
			}
		}
		else if (lstrcmpi(strBuf, "SERVERIP") == 0)
		{
			int p=0;
			while (tfb.ReadString()) 
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
				if (!gParser.GetValueRightToken(strTemp, ';'))
					continue;
				if (p >= m_nServerIPs)
					break;
				m_aServerIP[p++] = strTemp;
			}
		}
		else if (lstrcmpi(strBuf, "ACTOR") == 0)
		{
			if (ad >= m_nActorDescs)
				break;
			m_aActorDesc[ad++].Load(tfb);
		}
		else
		{
			TRACE("Unknown Data type in RIT file(%s)!\n", m_strResFile);
		}
	}
/*
#ifdef _DEBUG
	for (i=0; i < m_nSprites; i++)
		TRACE("%d)\t%s=(%d,%d),(%d,%d)\n", i, m_aSI[i].m_strName, m_aSI[i].m_sColRow.cx, m_aSI[i].m_sColRow.cy,
				m_aSI[i].m_sEarth.cx, m_aSI[i].m_sEarth.cy);
	for (i=0; i < ad; i++)
		TRACE("%d)\t%d behaviors\n", i, m_aActorDesc[i].GetNumBehaviors());
#endif
*/

	for (int s=0; s < GetNumStageNames(); s++)
	{
		CString strStageID(m_aStageName[s]);
		CString strTitle(strStageID);
		if (GetStageTitle(strTitle))	// access each sit file
		{
			MakeStageName(strStageID, TRUE);
			m_aStageName[s] = strStageID + ' ' + strTitle;
		}
		else
		{
			TRACE("SIT(%s) file not found!\n", strTemp);
		}
	}

	LoadWave();

	return TRUE;
}

int CResMan::GetSpriteID(const CString& strName) const
{
	for (int i=0; i < m_nSprites; i++)
	{
		if (lstrcmpi(m_aSI[i].m_strName, strName) == 0)
			return i;
	}
	return -1;	// Not Found!
}

int CResMan::GetWaveID(const CString& strName) const
{
	for (int i=0; i < m_nWaves; i++)
	{
		if (lstrcmpi(m_aWave[i].m_strName, strName) == 0)
			return i;
	}
	return -1;	// Not Found!
}

int CResMan::GetMIDIID(const CString& strName) const
{
	for (int i=0; i < m_nMIDIs; i++)
	{
		if (lstrcmpi(m_aMIDI[i], strName) == 0)
			return i;
	}
	return -1;	// Not Found!
}

BOOL CResMan::LoadWave()
{
	CString strFile;
	for (int i=0; i < m_nWaves; i++)
	{
		CWaveData& wd = m_aWave[i];
		ASSERT(!wd.m_strName.IsEmpty());
		if (wd.m_strName[0] == 's')	// wave
		{
			wd.m_pWave = new CSound;
			strFile = m_strResPath + wd.m_strName + ".wav";
//			TRACE("Loading Wave %s\n", strFile);
			if (!wd.m_pWave->Load(strFile))
			{
				delete wd.m_pWave;
				wd.m_pWave = NULL;
			}
		}
		else
		{
			wd.m_pWave = NULL;
		}
	}
	return TRUE;
}

// Play wave sound (memory-loaded)
BOOL CResMan::PlayWave(const int nID) const
{
	if (m_bMute)
		return FALSE;
	CWaveData& wd = m_aWave[nID];
	CString& s = wd.m_strName;

	if (s[0] == 's')	// wave
	{
		if (!wd.m_pWave)
			return FALSE;
		wd.m_pWave->Play();
		return TRUE;
	}
	else
	{
		TRACE("Not wave sound\n");
		return FALSE;
	}
	return FALSE;
}

WORD CResMan::GetSpriteTypeByName(const CString& strName) const
{
	CString strRes(strName);
	MakeResName(strRes);
	int i = GetSpriteID(strRes);
	return (i >= 0) ? GetSpriteType(i) : SPRITE_STATIC;
}

///////////////////////////////////////////////////////////////////
// DIB Management
CDIB* CResMan::LoadDIB(LPCSTR szResName)
{
	CString strFile(szResName);
	ExpandResName(strFile, RES_BMPEXT);
	strFile.MakeLower();
	CDIB* pDIB;
	POSITION pos = m_olDIB.GetHeadPosition();
	while (pos)
	{
		pDIB = (CDIB*)m_olDIB.GetNext(pos); // Increment position.
		if (pDIB)
		{
			ASSERT(pDIB->IsKindOf(RUNTIME_CLASS(CDIB)));
			CString* pstr = pDIB->GetName();
			if (*pstr == strFile)	// compare with only filename (excluding path)
				return pDIB;
		}
	}
	// File not found in current resource bank.
	// So create a new one and add it to the bank.
	pDIB = new CDIB;
	if (!pDIB->Load(strFile))
	{
		TRACE("%s: Resource Load Failure!\n", strFile);
		delete pDIB;
		return NULL;
	}
	LoadMasterPalette(pDIB);
	m_olDIB.AddTail(pDIB);
	return pDIB;
}

CDIB* CResMan::LoadDIB(const WORD wResid, const BOOL bMasterPalette)
{
	CString strName;
	strName.Format("RES:%d", wResid);
	CDIB* pDIB;
	POSITION pos = m_olDIB.GetHeadPosition();
	while (pos)
	{
		pDIB = (CDIB*)m_olDIB.GetNext(pos); // Increment position.
		if (pDIB)
		{
			ASSERT(pDIB->IsKindOf(RUNTIME_CLASS(CDIB)));
			CString* pstr = pDIB->GetName();
			if (*pstr == strName)
				return pDIB;
		}
	}
	// File not found in current resource bank.
	// So create a new one and add it to the bank.
	pDIB = new CDIB;
	if (!pDIB->Load(wResid))
	{
		TRACE("%d: Resource Load Failure!\n", wResid);
		delete pDIB;
		return NULL;
	}
	if (bMasterPalette)
		LoadMasterPalette(pDIB);
	m_olDIB.AddTail(pDIB);
	return pDIB;
}

// Load the specified resource into CPhasedSprite
// and sets initial conditions such as # of cells.
// The caller is responsible for deleting this sprite.
CPhasedSprite* CResMan::LoadPhasedSprite(LPCSTR szResName, const BOOL bDIBReuse)
{
	int nResID = GetSpriteID(szResName);
	if (nResID < 0)	// Not found in RIT
	{
		CString strMsg;
		strMsg.Format("%s not found in RIT", szResName);
		AfxMessageBox(strMsg);
		return NULL;
	}
	CPhasedSprite* pPS;
	if (bDIBReuse)	// Reuse Mechanism
	{
		CDIB* pDIB = LoadDIB(szResName);
		if (!pDIB)
			return NULL;
		pPS = new CPhasedSprite;
		pPS->SetDIB(pDIB);	// link DIB resource to this sprite
	}
	else	// Do not Reuse
	{
		CString strFile(szResName);
		ExpandResName(strFile, RES_BMPEXT);
		pPS = new CPhasedSprite;
		if (!pPS->Load(strFile))
		{
			delete pPS;
			TRACE("%s: Resource Load Failure!\n", strFile);
			return NULL;
		}
		ASSERT(pPS->GetDIB());
		LoadMasterPalette(pPS->GetDIB());
#ifdef MAPEDITOR
		if (GetSpriteTypeByName(szResName) == SPRITE_ACTOR)
		{
			static int nColorSet = 1;
			RotateActorColorSet(pPS->GetDIB(), nColorSet);
			nColorSet++;
			if (nColorSet > 4)
				nColorSet = 1;
		}
#endif
	}
	pPS->SetType(GetSpriteType(nResID));
	pPS->SetNumCells(GetSpriteColRow(nResID));
	pPS->SetEarth(GetSpriteEarth(nResID));
	CString* pStr = GetSpriteHyperlink(nResID);
	if (!pStr->IsEmpty())
		pPS->SetHyperlink(*pStr);
	return pPS;
}

CActor* CResMan::LoadActor(const int nCharID, const int nColorSet, const BOOL bME)
{
	CActorDesc* pAD = GetActorDesc(nCharID);
	if (!pAD)
	{
		CString strMsg;
		strMsg.Format("Actor Description: %d not found!", nCharID);
		AfxMessageBox(strMsg);
		return NULL;
	}

	CString strFile(*pAD->GetResName());
	ExpandResName(strFile, RES_BMPEXT);
	CActor* pA = new CActor;
	if (!pA->Load(strFile))
	{
		delete pA;
		TRACE("%s: Resource Load Failure!\n", strFile);
		return NULL;
	}
	ASSERT(pA->GetDIB());
	LoadMasterPalette(pA->GetDIB());

	if (bME)
		ShowOutline(pA->GetDIB());
	if (nColorSet)
		RotateActorColorSet(pA->GetDIB(), nColorSet);

	// Load Shadow
	CDIB* pDIB = LoadDIB(ACTOR_SHADOW_NAME);	//	LoadMasterPalette();

	if (pDIB)
	{
		CSprite* pS = new CSprite;
		pS->SetDIB(pDIB);	// link DIB resource to this sprite
		pS->SetType(SPRITE_STATIC);
		int nResID = GetSpriteID(ACTOR_SHADOW_NAME);
		pS->SetEarth(GetSpriteEarth(nResID));
		pA->SetShadow(pS);
	}

	int nResID = GetSpriteID(*pAD->GetResName());
	ASSERT(nResID>= 0);
	pA->SetType(GetSpriteType(nResID), SPRITE_ANI_ACTOR);
	pA->SetNumCells(GetSpriteColRow(nResID));
	pA->SetEarth(GetSpriteEarth(nResID));
	pA->SetCharID(nCharID);
	CString* pStr = GetSpriteHyperlink(nResID);
	if (!pStr->IsEmpty())
		pA->SetHyperlink(*pStr);

	return pA;
}

CBehavior* CResMan::GetActorBehavior(const WORD nCharID, const int bi)
{
	CActorDesc* pAD = GetActorDesc(nCharID);
	if (!pAD)
	{
		AfxMessageBox("Actor not found!");
		return NULL;
	}
	CBehavior* pBeh = pAD->GetBehavior(bi);
	if (!pBeh)	// If not found in this ActorDesc, use that of the standard instead
	{
		pAD = GetActorDesc(0);	// Standard ActorDesc
		ASSERT(pAD);
		return pAD->GetBehavior(bi);	// return that of the standard
	}
	return pBeh;
}

void CResMan::DeleteDIB(CDIB* pDIB)
{
	POSITION pos = m_olDIB.Find(pDIB);
	if (pos) // Hunt for pDIB
	{
		m_olDIB.RemoveAt(pos);
		delete pDIB;
	}
}

// Be sure not to do use DIBs allocated here elsewhere!!!
void CResMan::RemoveAllDIBs()
{
	// Walk down the list deleting objects as we go.
	// We need to do this here because the base class simply deletes the pointers.
	POSITION pos = m_olDIB.GetHeadPosition();
	CDIB* pDIB;
	while (pos)
	{
		pDIB = (CDIB*)m_olDIB.GetNext(pos); // Increment position.
		if (pDIB)
		{
			ASSERT(pDIB->IsKindOf(RUNTIME_CLASS(CDIB)));
			delete pDIB;
		}
	}
	// Now call the base class to remove the pointers.
	m_olDIB.RemoveAll();
}

//////////////////////////////////// Naming Handling Methods
// Extract filename only
// C:\UC2\Data\t00|tcity000.bmp ===> t00|tcity000
void CResMan::MakeResName(CString& strName) const
{
	int i = strName.ReverseFind('\\');
	int j = strName.ReverseFind('.');
	if ((i < 0) && (j < 0))
		return;

	char* p = strName.GetBuffer(256);
	if (j > 0)
		p[j] = NULL;		// Exclude file extension
	if (i >= 0)
		p += (i+1);
	CString strTemp((char*)p);
	strName.ReleaseBuffer();
	strName = strTemp;
	strName.MakeLower();
}

void CResMan::ExcludePath(CString& strName) const
{
	int i = strName.ReverseFind('\\');
	if (i < 0)
		return;

	char* p = strName.GetBuffer(256);
	p += (i+1);
	CString strTemp((char*)p);
	strName.ReleaseBuffer();
	strName = strTemp;
}

void CResMan::IncludePath(CString& strName) const
{
	if (strName.Find('\\') >= 0)
		return;
	CString strFN(m_strResPath);
	strFN += strName;
	strName = strFN;
}

// "t00|tcity000" => "C:\UC2\Data\t00|tcity000.bmp"
void CResMan::ExpandResName(CString& strName, LPCSTR szExt) const
{
	MakeResName(strName);
	CString strFN(m_strResPath);
	strFN += strName;
	if (szExt)
		strFN +=szExt;
	strName = strFN;
}
// "[p2/0010csin]Castle of the Wind" => "0010csin"
BOOL CResMan::ExtractStageID(CString& strName) const
{
	if (strName.GetLength() <= 5)
		return FALSE;

	if ((strName[0] == '[') && (strName[2] == '2') && (strName[3] == '/'))
	{
		int i = strName.Find(']');
		if (i < 4)
			return FALSE;
		CString strRes(strName.Mid(4, i-3-1));
		strName = strRes;
		return TRUE;
	}
	return FALSE;
}

// "0010csin" => "[p2/0010csin]"
// Public or MUD
void CResMan::MakeStageName(CString& strName, const BOOL bPublic) const
{
	CString strID(strName);
	strID.Format(bPublic ? PUBLIC_STAGE_NAME_FORMAT : MUD_STAGE_NAME_FORMAT,
				strName);
	strName = strID;
}

/////////////////////////////// Palette Control
// Be sure to call these methods before calling MapColorsToPalette
UINT CResMan::LoadMasterPalette(CDIB* pDIB) const
{
	return pDIB->SetPaletteEntries(0, 256, (const LPPALETTEENTRY)apeMASTER);
}

void CResMan::ShowOutline(CDIB* pDIB) const
{
	// Write Outline Color to Outline (Off) Index
//	pDIB->SetPaletteEntries(237, 1, (const LPPALETTEENTRY)&(apeMASTER[240]));
	pDIB->CopyPaletteEntry(237, 240);
}

// nColorSet = 0,1,2,3
void CResMan::RotateActorColorSet(CDIB* pDIB, const int nColorSet) const
{
	static int COLORS = 16;
	static int COLORSET[] =
	{
	0,1, 0,2, 0,3,	// nColorSet=4,5,6,
	1,0, 1,2, 1,3,	// 7,8,9,
	2,0, 2,1, 2,3,	// 10,11,12,
	3,0, 3,1, 3,2	// 13,14,15
	};
	int nCS = (nColorSet < COLORS) ? nColorSet : nColorSet % COLORS;
	int nC = (nCS < 4) ? nCS : COLORSET[(nCS-4)*2];
	int nH = (nCS < 4) ? nCS : COLORSET[(nCS-4)*2+1];
	pDIB->RotatePaletteIndex(200, COLORS, nC*4);	// Clothes
	pDIB->RotatePaletteIndex(220, COLORS, nH*4);	// Hair
}

/*
t00.uds
========
t*.bmp

ca00.uds
========
ca*.bmp ~ cc*.bmp

cd00.uds
========
cd*.bmp ~ cf*.bmp

cg00.uds
========
cg*.bmp ~ cp*.bmp

cs00.uds
========
cs*.bmp ~ ct*.bmp

cw00.uds
========
cw*.bmp ~
i*.bmp
w*.bmp
*/
// Add prefix for UDS resource name
void CResMan::PrefixUDS00(CString& strName) const
{
	int iDS = strName.Find('|');
	if (iDS >= 0)	// Found, no need to ...
		return;
	CString strDS;
	switch (tolower(strName[0]))
	{
	case 't':	strDS = "t";	break;
	case 'c':
		{
		char ch = tolower(strName[1]);
		if (ch <= 'c')		strDS = "ca";
		else if (ch <= 'f')	strDS = "cd";
		else if (ch <= 'p')	strDS = "cg";
		else if (ch <= 't')	strDS = "cs";
		else				strDS = "cw";
		break;
		}
	case 'i':
	case 'w':	strDS = "cw";	break;
	case 'a':	strDS = "a";		break;
	}
	strDS += "00|";
	strName =  strDS + strName;
}

int CResMan::GetStageType(LPCTSTR szName) const
{
	if (!szName)
		return ST_INVALID;
	if ((lstrlen(szName) < 5) || (szName[0] != '['))
		return ST_OLD;
	if ((szName[2] == '2') && (szName[3] == '/'))
	{
		if (szName[1] == 'u')
			return ST_MUD;
		if (szName[1] == 'p')
			return ST_PUBLIC;
	}
	return ST_OLD;
}

// strTitle(IN: stage filename, OUT: stage title)
BOOL CResMan::GetStageTitle(CString& strTitle) const
{
	CString strFile(strTitle);
	ExtractStageID(strFile);
	if (strFile.IsEmpty())
		return FALSE;
	ExpandResName(strFile, ".sit");
	CTextFileBuffer tfb(gParser.GetMaxBuffer());
	if (!tfb.Load(strFile))
	{
		return FALSE;
	}

	while (tfb.ReadString())
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())
			continue;
		if (!gParser.SetLeftToken('#'))
			continue;
		CString strBuf;
		if (!gParser.GetValueRightToken(strBuf, '='))
			continue;

		if (lstrcmpi(strBuf, "STAGE") == 0)
		{
			gParser.SetLeftToken('=');
			gParser.GetValueRightToken(strTitle, ',', ';');
			// remove [u2/0000abcd]
			int i = strTitle.Find(']');
			if (i > 0)
			{
				int n = strTitle.GetLength() - (i+1);
				CString strTemp(strTitle);
				strTitle = strTemp.Right(n);
			}
			return TRUE;
		}
	}
	return FALSE;
}
