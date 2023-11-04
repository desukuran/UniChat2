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
#SND=	// SOUND
{
	wwhip;	// wwhip.wav
	mtest;	// mtest.mid
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

extern CParser gParser;

const char* RESFILE_FILTER = "Resource Information Tables(*.RIT)|*.RIT|"
							"All files (*.*)|*.*||";
const char* RES_BMPEXT = ".bmp";	// ".bm"

static const PALETTEENTRY apeMASTER[256] =
{
#include "UC2Master.pal"	// 256 Color Table
};

///////////////////////////////////////////////////////////////////

WORD CResMan::CSpriteInfo::GetType()
{
	switch (tolower(m_strName[0]))
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
	m_nSprites		= 0;
	m_aSI			= NULL;
	m_nActorDescs	= 0;
	m_aActorDesc	= NULL;
	m_nResFiles		= 1;
	m_strResFile.Empty();
}

CResMan::~CResMan()
{
	DeleteResources();
}

void CResMan::DeleteResources()
{
	if (m_aSI)
		delete [] m_aSI;
	m_aSI		= NULL;
	m_nSprites	= 0;
	if (m_aActorDesc)
		delete [] m_aActorDesc;
	m_aActorDesc	= NULL;
	m_nActorDescs	= 0;
	RemoveAllDIBs();
}

void CResMan::CountItems(CStdioFile& f, char* szBuf)
{
	m_nSprites	= 0;
	int nAD=0;
	while (f.ReadString(szBuf, gParser.GetMaxBuffer()))
	{
		gParser.CopyBuffer(szBuf);
		if (gParser.IsCommentLine())	// At first, check if it's a comment line
			continue;
		if (!gParser.SetLeftToken('#') ||
			!gParser.GetValueRightToken(szBuf, '='))
			continue;		// get next line
		if ((lstrcmpi(szBuf, "TIL") == 0) ||	// matching!
			(lstrcmpi(szBuf, "STT") == 0) ||
			(lstrcmpi(szBuf, "ANI") == 0) ||
			(lstrcmpi(szBuf, "AVT") == 0))
		{
			m_nSprites += CountContents(f, szBuf);
		}
		else if (lstrcmpi(szBuf, "ACTOR") == 0)	// matching!
		{
			m_aActorDesc[nAD++].SetNumBehaviors(CountContents(f, szBuf));
		}
	}
	f.SeekToBegin();
}

// Count the number of lines that matches a specified string between '#' and '='
int CResMan::CountHeaders(CStdioFile& f, char* szBuf, const char* szToken)
{
	int i=0;
	while (f.ReadString(szBuf, gParser.GetMaxBuffer()))
	{
		gParser.CopyBuffer(szBuf);
		if (gParser.IsCommentLine())	// At first, check if it's a comment line
			continue;
		if (!gParser.SetLeftToken('#') ||	// get next line
			!gParser.GetValueRightToken(szBuf, '='))
			continue;
		if (lstrcmpi(szBuf, szToken) == 0)	// matching!
			i++;
	}
	f.SeekToBegin();
	return i;
}

// Count the number of lines that include '=' between { and }
int CResMan::CountContents(CStdioFile& f, char* szBuf)
{
	int i=0;
	while (f.ReadString(szBuf, gParser.GetMaxBuffer()))
	{
		gParser.CopyBuffer(szBuf);
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
		if (gParser.SetLeftToken('='))
			i++;		// Anyway, we should increase the counter
	}
	return i;
}

BOOL CResMan::Initialize(CStdioFile& f, char* szBuf)
{
	DeleteResources();

	m_nActorDescs = CountHeaders(f, szBuf, "ACTOR");
	//////////// Initialize Actor Behaviors
	if (m_nActorDescs <= 0)
	{
		AfxMessageBox("Resource file: No behaviors found!");
//		return FALSE;
	}
	m_aActorDesc = new CActorDesc[m_nActorDescs];
	TRACE("# of Actor Descriptions = %d\n", m_nActorDescs);

	CountItems(f, szBuf);

	//////////// Initialize Sprite Informations
	if (m_nSprites <= 0)
	{
		AfxMessageBox("Resource file: No sprites found!");
		return FALSE;
	}
	m_aSI = new CSpriteInfo[m_nSprites];
	TRACE("# of Sprites = %d\n", m_nSprites);

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

	char*	szBuf = new char[gParser.GetMaxBuffer()];	// ReadString(CString&) has a bug!

	TRY
	{
		CFile f;
		if (!f.Open(m_strResFile, CFile::modeRead | CFile::shareDenyWrite))
		{
			TRACE1("File Open Failure: %s\n", m_strResFile);
			delete [] szBuf;
			return FALSE;
		}
		UINT hLZFile = ::LZInit(f.m_hFile);
		LONG lFileSize = ::LZSeek(f.m_hFile, 0L, 2);	// points to the end of file
		TRACE("FileSize=%ld bytes\n",  lFileSize);
		::LZSeek(hLZFile, 0, 0);  // seek to beginning of file
		char* pTextSrc = new char[lFileSize+1];
		int iBytes = ::LZRead(hLZFile, pTextSrc, lFileSize);
		if (iBytes != (int)lFileSize)
		{
			TRACE("File read failure! %s: %d bytes read\n", m_strResFile, iBytes);
			delete [] szBuf;
			return FALSE;
		}
		::LZClose(hLZFile);

//		CStdioFile f(m_strResFile, CFile::modeRead | CFile::shareDenyNone | CFile::typeText);
		ExcludePath(m_strResFile);

		if (!Initialize(f, szBuf))
		{
			f.Close();
			delete [] szBuf;
			return FALSE;
		}

		int i=0;
		int ad=0;
		CString strTemp;

		while (f.ReadString(szBuf, gParser.GetMaxBuffer()))
		{
			gParser.CopyBuffer(szBuf);
			if (gParser.IsCommentLine())
				continue;
			if (!gParser.SetLeftToken('#'))
				continue;
			if (!gParser.GetValueRightToken(szBuf, '='))
				continue;

			/////////////////////////////////////////////////////////// ENVIRONMENT SECTION
			if (lstrcmpi(szBuf, "TIL") == 0)	// matching!
			{
				while (f.ReadString(szBuf, gParser.GetMaxBuffer())) 
				{
					gParser.CopyBuffer(szBuf);
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
					gParser.GetValueRightToken(m_aSI[i].m_sColRow, ',');
					m_aSI[i].m_sEarth = CSize(64/2,0);
					i++;
				}
			}
			else if (lstrcmpi(szBuf, "STT") == 0)
			{
				while (f.ReadString(szBuf, gParser.GetMaxBuffer())) 
				{
					gParser.CopyBuffer(szBuf);
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
					gParser.GetValueRightToken(m_aSI[i].m_sEarth, ';');
					i++;
				}
			}
			else if (lstrcmpi(szBuf, "ANI") == 0)
			{
				while (f.ReadString(szBuf, gParser.GetMaxBuffer())) 
				{
					gParser.CopyBuffer(szBuf);
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
					gParser.GetValueRightToken(m_aSI[i].m_sEarth, ';');
					i++;
				}
			}
			else if (lstrcmpi(szBuf, "AVT") == 0)
			{
				while (f.ReadString(szBuf, gParser.GetMaxBuffer())) 
				{
					gParser.CopyBuffer(szBuf);
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
					gParser.GetValueRightToken(m_aSI[i].m_sEarth, ',');
					i++;
				}
			}
			else if (lstrcmpi(szBuf, "ACTOR") == 0)
			{
				m_aActorDesc[ad++].Load(f, szBuf);
				if (ad >= m_nActorDescs)
					break;
			}
			else
			{
//				TRACE1("Unknown Data type in Cast file(%s)!\n", szBuf);
			}
		}
		f.Close();
		delete [] szBuf;
#ifdef _DEBUG
		for (i=0; i < m_nSprites; i++)
			TRACE("%d)\t%s=(%d,%d),(%d,%d)\n", i, m_aSI[i].m_strName, m_aSI[i].m_sColRow.cx, m_aSI[i].m_sColRow.cy,
					m_aSI[i].m_sEarth.cx, m_aSI[i].m_sEarth.cy);
		for (i=0; i < ad; i++)
			TRACE("%d)\t%d behaviors\n", i, m_aActorDesc[i].GetNumBehaviors());
#endif
		return TRUE;
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		delete [] szBuf;
		return FALSE;
	}
	END_CATCH
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

WORD CResMan::GetSpriteTypeByName(const CString& strName) const
{
	CString strRes(strName);
	MakeResName(strRes);
	int i = GetSpriteID(strRes);
	return (i >= 0) ? GetSpriteType(i) : 0;
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
	MapToMasterPalette(pDIB);
	m_olDIB.AddTail(pDIB);
	return pDIB;
}

CDIB* CResMan::LoadDIB(const WORD wResid)
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
	m_olDIB.AddTail(pDIB);
	return pDIB;
}

// Load the specified resource into CPhasedSprite
// and sets initial conditions such as # of cells.
// The caller is responsible for deleting this sprite.
CPhasedSprite* CResMan::LoadPhasedSprite(LPCSTR szResName, const BOOL bDIBReuse)
{
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
		MapToMasterPalette(pPS->GetDIB());
#ifdef MAPEDITOR
		if (GetSpriteType(GetSpriteID(szResName)) == SPRITE_ACTOR)
		{	// Show Outline
			static int nColorSet = 1;
			RotateActorColorSet(pPS->GetDIB(), nColorSet);
			nColorSet++;
			if (nColorSet > 4)
				nColorSet = 1;
		}
#endif
	}
	int i = GetSpriteID(szResName);
	ASSERT(i >= 0);
	pPS->SetType(GetSpriteType(i));
	pPS->SetNumCells(GetSpriteColRow(i));
	pPS->SetEarth(GetSpriteEarth(i));
	return pPS;
}

CActor* CResMan::LoadActor(const int nID)
{
	CActorDesc* pAD = GetActorDesc(nID);
	if (pAD)
	{
		CString strMsg;
		strMsg.Format("Actor Description: %d not found!", nID);
		AfxMessageBox(strMsg);
		return NULL;
	}

	CPhasedSprite* pPS = LoadPhasedSprite(*pAD->GetResName(), FALSE);
	if (!pPS)
		return NULL;
	CActor* pA = new CActor;
	CPhasedSprite* pPSDest = (CPhasedSprite*)pA;
	*pPSDest = *pPS;
	delete pPS;
	pA->SetID(nID);
	return pA;
}

CBehavior* CResMan::GetActorBehavior(const int ad, const int bi)
{
	CActorDesc* pAD = GetActorDesc(ad);
	ASSERT(pAD);
	CBehavior* pBeh = pAD->GetBehavior(bi);
	if (!pBeh)	// If not found in this ActorDesc, use that of the standard instead
	{
		pAD = GetActorDesc(0);	// Standard ActorDesc
		ASSERT(pAD);
		return pAD->GetBehavior(bi);
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
void CResMan::MakeResName(CString& strName) const
{
	int i = strName.ReverseFind('\\');
	if (i >= 0)
	{
		char* p = strName.GetBuffer(256);
		int j = strName.ReverseFind('.');
		if (j > 0)
			p[j] = NULL;		// Exclude file extension
		p += (i+1);
		CString strTemp((char*)p);
		strName.ReleaseBuffer();
		strName = strTemp;
	}
}

void CResMan::ExcludePath(CString& strName) const
{
	int i = strName.ReverseFind('\\');
	if (i >= 0)
	{
		char* p = strName.GetBuffer(256);
		p += (i+1);
		CString strTemp((char*)p);
		strName.ReleaseBuffer();
		strName = strTemp;
	}
}

void CResMan::IncludePath(CString& strName) const
{
	if (strName.Find('\\') >= 0)
		return;
	CString strFN(m_strResPath);
	strFN += strName;
	strName = strFN;
}

// tile0000:tcity000 ===> C:\UC2\Data\tile0000:tcity000.bmp
void CResMan::ExpandResName(CString& strName, LPCSTR szExt) const
{
	CString strFN(m_strResPath);

	if ((strName.Find('\\') >= 0) || (strName.Find('.') >= 0))
		MakeResName(strName);
	strFN += strName;
	if (szExt)
		strFN +=szExt;
	strName = strFN;
}

/////////////////////////////// Palette Control
// Be sure to call these methods before calling MapColorsToPalette
UINT CResMan::MapToMasterPalette(CDIB* pDIB) const
{
	return pDIB->SetPaletteEntries(0, 256, (const LPPALETTEENTRY)apeMASTER);
}

void CResMan::ShowOutline(CDIB* pDIB) const
{
	// Write Outline Color to Outline (Off) Index
	pDIB->SetPaletteEntries(237, 1, (const LPPALETTEENTRY)&(apeMASTER[240]));
}

// nColorSet = 1,2,3,4,
void CResMan::RotateActorColorSet(CDIB* pDIB, const int nColorSet) const
{
	int a = nColorSet;
	int b = nColorSet;
	if (nColorSet > 4)
	{
		a = nColorSet / 4;
		b = nColorSet % 4;
	}
	pDIB->RotatePaletteIndex(200, 4*4, a*4);
	pDIB->RotatePaletteIndex(220, 4*4, b*4);
}