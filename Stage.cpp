// Stage.cpp: implementation of the CStage class.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

/* ==================================================================
; Stage stage000.sit
#VERSION=0.90;
#DEPENDENCY=
{
	resrc000.rit;
}

#STAGE=[u2]°ÅºÏ ´E­¹EÁ¦¸Emaster.pal,map000.mit;
{
//	resurce name=cell id, LeftTop(x,y), Image Operation, Elevation, Sprite Type, nMSPT;
	ccity014=0,(333,-10),4096,8,http://www.microsoft.com;
	aman_007=26,(325,67),4096,0,272,150;
; ...
}	// 0 sprites.
================================================================== */

#include "stdafx.h"
#include "Stage.h"

#include "TileMap.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/PhSprite.h"
#include "UC2Ani/Bubble.h"
#include "UC2Ani/OSBView.h"
#include "UC2Ani/MCIObj.h"
#include "Actor.h"
#include "ResMan.h"
#include "Parser.h"
#include "Behavior.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CResMan	gResMan;			// global Resource Manager
extern CParser	gParser;

double GetMapEditorVersion();

const char* STAGEFILE_FILTER = "Stage Information Tables(*.SIT)|*.SIT|"
								"All files (*.*)|*.*||";
const char* STAGEFILE_EXT = ".sit";		// should be lower case
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStage::CStage()
{
	TRACE0("CStage::CStage()\n");
	m_pOSBView		= NULL;
	m_pTiles		= NULL;
	m_pThisActor	= NULL;
	m_wRM			= RM_NORMAL;
	m_aBGM			= NULL;
	m_nBGMs	= m_iBGM = 0;
	m_pBGM			= NULL;
	m_strStageFile.Empty();
	m_strPalFile.Empty();
	m_bExitOpen		= FALSE;
	m_bMusicPlayOK	= FALSE;
}

CStage::~CStage()
{
	TRACE0("CStage::~CStage()\n");
	DeleteStage();
}

//////////////////////////////////////////////////////////////////////////
// Be sure to call this function before calling any other member functions
// pass COSBView-inherited View
BOOL CStage::Initialize(COSBView* pView)
{
	m_pOSBView = pView;
    m_SpriteList.m_NotifyObj.SetView(pView);
//    m_AniList.m_NotifyObj.SetView(pView);	// Each sprite need not notify
    m_BubbleList.m_NotifyObj.SetView(pView);
	return TRUE;
}

void CStage::DeleteStage()
{
	TRACE0("CStage::DeleteStage()\n");
	m_pThisActor = NULL;

    m_SpriteList.RemoveAll();	// This should go before deleting Tiles
    m_BubbleList.RemoveAll();
	m_AniList.RemoveAll(FALSE);	// do not delete

	if (m_pTiles)
		delete m_pTiles;
	m_pTiles = NULL;

	if (m_aBGM)
		delete [] m_aBGM;
	m_aBGM = NULL;
	if (m_pBGM)
		delete m_pBGM;
	m_pBGM = NULL;

	m_strTitle.Empty();
	m_strMusicSeq.Empty();
	m_bExitOpen = FALSE;
}

BOOL CStage::InitMap()
{
	if (m_pTiles)
		delete m_pTiles;
	m_pTiles = new CTileMap;
	m_pTiles->SetPalette((CPalette*)m_pOSBView->GetOSBPalette());
	m_pTiles->SetSpriteList(&m_SpriteList);
	m_pTiles->SetAniList(&m_AniList);
	ASSERT(m_pOSBView);

	return TRUE;
}

BOOL CStage::CreateStage(CSize& szT, CSize& szScr)
{
	TRACE("CStage::CreateStage()\n");
	// CreateStage() function will call gResMan.Load() every time
	// to update (maybe) changed items in RIT file.
	if (!gResMan.Load())
		return FALSE;

	CreateOSB(szScr);
	ASSERT(m_pOSBView);

	InitMap();	// New m_pTiles
	m_pTiles->SetTileSize(szT);
	m_pTiles->Create(szScr);
#ifdef MAPEDITOR
	m_pTiles->LoadGrid();
#endif
	return TRUE;
}

// Create OSB from the Map file (tiles)
BOOL CStage::CreateOSB(const CSize sScreen)
{
	// Delete any existing sprites
	m_SpriteList.RemoveAll();	// Since the palette will be changed

	// Create OSB
	CDIB* pDIB = new CDIB;
	// Load master palette - This will be an OSB palette
//	CString strPal(m_strPalFile);
//	gResMan.IncludePath(strPal);
	pDIB->Create(sScreen.cx, sScreen.cy);	//, strPal);
	gResMan.LoadMasterPalette(pDIB);
	m_pOSBView->CreateOSB(pDIB);	// virtual function
	delete pDIB;
	return TRUE;
}

// Load SIT (Stage Information Table) file
// This method can be called multiple times in the App.'s Document class.
BOOL CStage::Load(const char* szStage)
{
	TRACE("CStage::Load(%s)\n", szStage);
	if (!m_strStageFile.IsEmpty())
	{	// Save Previous Stage ID
		m_strPrevID = m_strStageFile;
		gResMan.MakeResName(m_strPrevID);
	}

	if ((szStage == NULL) || (lstrlen(szStage) == 0))
	{
		::SetCurrentDirectory(*gResMan.GetResPath());
		// Show an Open File dialog to get the name.
		CFileDialog dlg(TRUE,	// Open
						NULL,	// No default extension
						m_strStageFile,	// Initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
						STAGEFILE_FILTER);
        if (dlg.DoModal() == IDOK)
			m_strStageFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{
		// Copy the supplied file path.
		m_strStageFile = szStage;
		gResMan.ExpandResName(m_strStageFile, STAGEFILE_EXT);
	}

#ifdef MAPEDITOR
	// CreateStage() function will call gResMan.Load() every time
	// to update (maybe) changed items in RIT file.
	gResMan.Load();	// "resrc000.rit");
#endif

	CTextFileBuffer tfb(gParser.GetMaxBuffer());
	if (!tfb.Load(m_strStageFile))
	{
		return FALSE;
	}
	gResMan.ExcludePath(m_strStageFile);

//	int ny=0;	// Current Row of the tiles
	double	fVersion;

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

		//////////////////////////////////////////////////////
		if (lstrcmpi(strBuf, "VERSION") == 0)
		{
			gParser.SetLeftToken('=');
			gParser.GetValueRightToken(fVersion, ',');
			if (fVersion <= 0.90)
			{
				CString strMsg;
				strMsg.Format("SIT: Old Version %.2f", fVersion);
				AfxMessageBox(strMsg);
			}
		}
//////////////////////// STAGE
		else if (lstrcmpi(strBuf, "STAGE") == 0)
		{
			DeleteStage();	// Delete current
			InitMap();

			gParser.SetLeftToken('=');
			gParser.GetValueRightToken(m_strTitle, ',', ';');

			if (fVersion <= 0.99)	// Separate MIT file
			{
				TRACE0("This SIT an obsolete version with separate MIT file!\n");
				gParser.GetValueRightToken(m_strPalFile, ',', ';');
				CString strMap;
				gParser.GetValueRightToken(strMap, ',', ';');
				if (!m_pTiles->Load(strMap))
				{
					delete m_pTiles;
					m_pTiles = NULL;
					strMap += " not found!";
					AfxMessageBox(strMap);
					return FALSE;
				}
			}
			else	// Version 1.0 or above
			{
				gParser.GetValueRightToken(m_strMusicSeq, ',', ';');
				ParseBGMs();	// will deal with empty string case
			}

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

				CString strResName;
/*
				if (fVersion <= 0.90)	// Resource ID as a filename
				{
					gParser.GetValueRightToken(strResName, '=');
					gResMan.PrefixUDS00(strResName);
				}
				else	// New Version
				{
*/
					int nResID;
					gParser.GetValueRightToken(nResID, '=');
					CString* pStr = gResMan.GetSpriteName(nResID);
					if (!pStr)
					{
						strResName.Format("Invalid ResID=%d in Stage file!", nResID);
						AfxMessageBox(strResName);
						continue;
					}
					strResName = *pStr;
//				}
				int		nCellID;
				CPoint	ptLT;
				WORD	wImOp = DEFAULT_IO;
				int		nElev = 0;
				WORD	wType = SPRITE_STATIC;
				int		nMSPT = 0;
//				CString strHyperlink;

				gParser.GetValueRightToken(nCellID, ',');
				gParser.GetValueRightToken(ptLT, ',', ';');
				if (!gParser.GetValueRightToken(wImOp, ',', ';'))
					wImOp = DEFAULT_IO;
				else
				{
					if (!gParser.GetValueRightToken(nElev, ',', ';'))
						nElev = 0;
					else
					{
						if (!gParser.GetValueRightToken(wType, ',', ';'))
							wType = SPRITE_STATIC;
						else
						{
							if (!gParser.GetValueRightToken(nMSPT, ',', ';'))
								nMSPT = 0;
//							else
//							{
//								if (!gParser.GetValueRightToken(strHyperlink, ',', ';'))
//									strHyperlink.Empty();
//							}
						}
					}
				}
				// Resource Allocation via Resource Manager
				BOOL bReuse = ((wType & SPRITE_ACTOR) != SPRITE_ACTOR);
				CPhasedSprite* pPS = gResMan.LoadPhasedSprite(strResName, bReuse);
				if (!pPS)
				{
					strResName += " not found!";
					AfxMessageBox(strResName);
					continue;
				}
				pPS->SetCell(nCellID);
				if (nElev)
				{
					pPS->SetElevation(nElev);
					ptLT.y -= nElev;
				}
				pPS->SetLT(ptLT);
				pPS->SetType(wType);	// This should come before Z-ordering for SPRITE_TILE!
#ifndef	MAPEDITOR
				if (pPS->GetSrcType() == SPRITE_ACTOR)
					pPS->SetSrcType(SPRITE_PHASED);
#endif
				if (fVersion < 1.01)
				{
					wImOp &= ~NO_COLORKEY;
					if (nMSPT && !pPS->GetAniType())
						nMSPT = 0;
				}
				pPS->SetImOp(wImOp);
				pPS->SetZByEarth();
				if (nMSPT > 0)
					pPS->SetMSPT(nMSPT);
//				if (!strHyperlink.IsEmpty())
//					pPS->SetHyperlink(strHyperlink);
			
				InsertSprite(pPS);	// Insert into Sprite List
			}
		}
//////////////////////// TILE: After verion 1.0, MIT is integrated into SIT
		else if (lstrcmpi(strBuf, "TILESIZE") == 0)
		{
			ASSERT(fVersion >= 1.00);
			gParser.SetLeftToken('=');
			CSize sT;
			gParser.GetValueRightToken(sT, ';');
			m_pTiles->SetTileSize(sT);
		}
		else if (lstrcmpi(strBuf, "SCREENSIZE") == 0)	// matching!
		{
			ASSERT(fVersion >= 1.00);
			gParser.SetLeftToken('=');
			CSize sScr;
			gParser.GetValueRightToken(sScr, ';');
			m_pTiles->Create(sScr);	// Create Tiles
		}
		else if (lstrcmpi(strBuf, "ROW") == 0)
		{
			ASSERT(fVersion >= 1.00);
			gParser.SetLeftToken('(');
			int ny;
			gParser.GetValueRightToken(ny, ')');
			if (!m_pTiles->LoadRow(tfb, ny, fVersion))
				continue;
		}
		else
		{
			TRACE1("Unknown Data type in Stage file(%s)!\n", strBuf);
		}
	}
#ifdef MAPEDITOR
	if (fVersion >= 1.00)
		m_pTiles->LoadGrid();
#endif
	// Insert Animated Tiles to m_AniList

	return TRUE;
}

// syntax: 0>1>2>3>...n>;
void CStage::ParseBGMs()
{
	m_bMusicPlayOK = FALSE;	// Prevent access to musice seq array
	if (!m_pBGM)
		m_pBGM = new CMCIObject;	// Create once
	if (m_aBGM)
		delete [] m_aBGM;
	gParser.CopyBuffer(m_strMusicSeq);
	m_nBGMs = gParser.CountOccurrencesUpto('>', ';');
	if (m_nBGMs <= 0)
	{
		TRACE("No BGMs found in this stage\n");
		m_nBGMs = 3;	// set default;
		m_aBGM = new int[m_nBGMs];
		for (int i=0; i < m_nBGMs; i++)
			m_aBGM[i] = i;
	}
	else
	{
		m_aBGM = new int[m_nBGMs];
		int nID;
		int i=0;
		while (gParser.GetValueRightToken(nID, '>', ';'))
		{
			ASSERT(i < m_nBGMs);
			m_aBGM[i++] = nID;
		}
	}
	m_iBGM = 0;
	m_bMusicPlayOK = TRUE;
}

// Paly BGMs sequentially
// Application's View window will drive this method
BOOL CStage::PlayBGM()
{
	if (!m_bMusicPlayOK)
		return FALSE;
	if (!m_pBGM)
	{
		TRACE("Error: BGM not created!\n");
		return FALSE;
	}
	m_pBGM->Close();

	CString strFile(*gResMan.GetResPath());
	if (m_iBGM >= m_nBGMs)
		m_iBGM = 0;
	CString* pS = gResMan.GetMIDIName(m_aBGM[m_iBGM]); 
	if (!pS)
	{
		TRACE("Resource(MIDI:%d) not found!\n", m_aBGM[m_iBGM]);
		return FALSE;
	}
	m_iBGM++;
	strFile += *pS;
	strFile += ".mid";
	
	if (!m_pBGM->Load(strFile))
		return FALSE;
	return m_pBGM->Play();
}

void CStage::StopBGM()
{
	if (m_pBGM)
		m_pBGM->Close();
}
	
// Save SIT (Stage Information Table) file
BOOL CStage::Save(const char* szStage)
{
	// Save Map File first
	if ((szStage == NULL) || (lstrlen(szStage) == 0))
	{
		::SetCurrentDirectory(*gResMan.GetResPath());
		// Show a File Save dialog to get the name.
		CFileDialog dlg(FALSE,   // Save
						NULL,    // No default extension
						m_strStageFile,    // No initial file name
						OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
						STAGEFILE_FILTER);
		if (dlg.DoModal() == IDOK)
			m_strStageFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{
		// Copy the supplied file path.
		m_strStageFile = szStage;
		gResMan.ExpandResName(m_strStageFile, STAGEFILE_EXT);
	}

	TRY
	{
		::CopyFile(m_strStageFile, "SIT.BAK", FALSE);
		CStdioFile f(m_strStageFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		gResMan.ExcludePath(m_strStageFile);
		
		CString str;
		str.Format("; Stage %s\n", m_strStageFile);
		f.WriteString(str);

		str.Format("#VERSION=%.2f;\n", GetMapEditorVersion());
		f.WriteString(str);

//		str.Format("#DEPENDENCY=\n{\n%s;\n}\n\n", *gResMan.GetFileName());
//		f.WriteString(str);

		if (m_strTitle.IsEmpty())
			m_strTitle = "[u2]";
		str.Format("#STAGE=%s,%s;\n", m_strTitle, m_strMusicSeq);
		f.WriteString(str);
		f.WriteString("{\n");

		POSITION pos = m_SpriteList.GetTailPosition();
		CPhasedSprite* pPS;

		while (pos)
		{
			pPS = (CPhasedSprite*)m_SpriteList.GetPrev(pos);
			if (pPS->GetSrcType() == SPRITE_TILE)
				continue;	// skip for tile
			m_SpriteList.RemoveRedundantSprite(pPS);
		}

		pos = m_SpriteList.GetTailPosition();
		int n=0;
		while (pos)
		{
			pPS = (CPhasedSprite*)m_SpriteList.GetPrev(pos);
			if (pPS->GetSrcType() == SPRITE_TILE)
				continue;	// skip for tile

			CString strResName(*pPS->GetDIB()->GetName());
			gResMan.MakeResName(strResName);
//			str.Format("%s=%d,(%d,%d),%d,%d,%d,%d;\n", strResName,	// #VERSION=0.90
			int nResID = gResMan.GetSpriteID(strResName);
			if (nResID < 0)
			{
				strResName += " not found";
				AfxMessageBox(strResName);
			}
			if ((pPS->GetImOp() == DEFAULT_IO) &&
				(pPS->GetElevation() == 0) &&
				(pPS->GetType() == SPRITE_STATIC))
//				(!pPS->HasHyperlink()))
			{	// Typical case
				str.Format("%d=%d,(%d,%d)", nResID,
						pPS->GetCellID(), pPS->GetX(),
						pPS->GetY() + pPS->GetElevation());
			}
			else
			{
				str.Format("%d=%d,(%d,%d),%d,%d,%d,%d", nResID,
							pPS->GetCellID(), pPS->GetX(),
							pPS->GetY() + pPS->GetElevation(),
							pPS->GetImOp(), pPS->GetElevation(),
							pPS->GetType(), pPS->GetMSPT());
//				if (pPS->HasHyperlink())
//				{
//					str += ',';
//					str += *pPS->GetHyperlink();
//				}
			}
			str += ";\n";
			f.WriteString(str);
			n++;
		}
		str.Format("}\t// %d sprites.\n", n);
		f.WriteString(str);

		str.Format("%s: %d sprites written.", m_strStageFile, n);
		if (m_pTiles)
		{
			if (!m_pTiles->GetFileName()->IsEmpty())
				str += "\n\nMIT file has been integrated into SIT file.";
			m_pTiles->Save(f);
		}

		f.Close();
		AfxMessageBox(str);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Sprite Manipulations

// Render the scene to the off-screen buffer pClipRect defaults to NULL
void CStage::Render(CRect* pClipRect)
{
	CRect rcDraw;
	ASSERT(m_pOSBView);
	CDIB* pOSB = m_pOSBView->GetOSB();
	ASSERT(pOSB);
	pOSB->GetRect(rcDraw);
	if (pClipRect)
		rcDraw.IntersectRect(pClipRect, &rcDraw);
//	if (m_pTiles)
//		m_pTiles->Render(pOSB, &rcDraw);	// Tiles are rendered with sprites

	pOSB->ClearRect(rcDraw);	// No background image

	// Render the sprite list from the bottom of the list to the top
	POSITION pos = m_SpriteList.GetTailPosition();
	CSprite* pSprite;
	while (pos)
	{
		pSprite = m_SpriteList.GetPrev(pos);
		// while sprites off and for normal sprites, skip!
#ifdef MAPEDITOR
		if ((m_wRM & RM_NORMAL) == RM_NORMAL)
		{
#endif	// MAPEDITOR
			pSprite->Render(pOSB, &rcDraw);
#ifdef MAPEDITOR
		}
		else
		{
			if ((m_wRM & RM_SPRITE) != RM_SPRITE)	// Exclude Sprite
			{
				if (pSprite->GetSrcType() != SPRITE_TILE)
					continue;
			}
			else if ((m_wRM & RM_TILE) != RM_TILE)	// Exclude Tile
			{
				if (pSprite->GetSrcType() == SPRITE_TILE)
					continue;
			}

			if ((m_wRM & RM_ELEV) != RM_ELEV)	// No Elevation
			{
				int nE = pSprite->GetElevation();
				if (nE)
					pSprite->Unelevate();	// Temporarily do not elevate
				pSprite->Render(pOSB, &rcDraw);
				if (nE)
					pSprite->Elevate();
			}
		}
#endif	// MAPEDITOR
	}
	// Render the bubble list
	pos = m_BubbleList.GetTailPosition();
	CBubble* pBubble;
	while (pos)
	{
		pBubble = m_BubbleList.GetPrev(pos);
		// render only if this sprite hits the region
		pBubble->Render(m_pOSBView->GetHBitmap(),
					(CPalette*)m_pOSBView->GetOSBPalette(), &rcDraw);
	}

#ifdef MAPEDITOR
	if (m_pTiles && ((m_wRM & RM_GRID) == RM_GRID))
		m_pTiles->RenderGrid(pOSB, &rcDraw);
#endif

#ifdef _DEBUG_RENDER
	static DWORD dwRender;
	dwRender++;
	if (dwRender%100 == 0)
		TRACE("CStage::Render %ld times...\n", dwRender);
#endif	// _DEBUG
}
/*
void CStage::RenderZOrder(CSprite* pSprite)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);	// create a memory dc that is compatible with current screen
	CBitmap* pbmOld	= dcMem.SelectObject(CBitmap::FromHandle(m_pOSBView->GetHBitmap()));

	CPen pen(PS_SOLID, 1, PALETTERGB(255,0,0));
	CPen* penOld = (CPen*)dcMem.SelectObject(&pen);

	CPoint ptCtr(pSprite->GetCenter());
	CSize sScr(GetScreenSize());
	ptCtr.y = sScr.cy - pSprite->GetZ();

	const int d = 3;	// Draw a cross
	CRect rcZO(ptCtr.x-d, ptCtr.y-d, ptCtr.x+d,	ptCtr.y+d);
	dcMem.MoveTo(rcZO.TopLeft());
	dcMem.LineTo(rcZO.BottomRight());
	dcMem.MoveTo(rcZO.right, rcZO.top);
	dcMem.LineTo(rcZO.left,	rcZO.bottom);

	m_pOSBView->AddDirtyRegion(&rcZO);

	dcMem.SelectObject(penOld);
	dcMem.SelectObject(pbmOld);
}
*/

// Multiple calls possible
void CStage::InsertSprite(CPhasedSprite* pPS)
{
	// At first remove if exist...
	m_AniList.Remove(pPS);
	m_SpriteList.Remove(pPS);
	m_SpriteList.Insert(pPS);
	if (pPS->GetAniType())
		m_AniList.Insert(pPS);	// add to the check list in CStage::TickAll

	// map the colors in the sprite DIB to the
	// palette in the off-screen buffered view
	if (m_pOSBView->GetOSBPalette())
		pPS->MapColorsToPalette((CPalette*)m_pOSBView->GetOSBPalette());
	
	m_pOSBView->AddDirtyRegion(pPS);
}

void CStage::DeleteSprite(CPhasedSprite* pPS)
{
	m_AniList.Remove(pPS);
	CPhasedSprite* pS = (CPhasedSprite*)m_SpriteList.Remove(pPS);
	if (pS)
	{
		m_pOSBView->AddDirtyRegion(pS);
		delete pS;
	}
}

// Multiple calls possible
void CStage::InsertBubble(CBubble* pBB)
{
	// At first remove if exist...
	m_BubbleList.Remove(pBB);
	m_BubbleList.Insert(pBB);
	m_pOSBView->AddDirtyRegion(pBB);
}

CBubble* CStage::RemoveBubble(CBubble* pBB)
{
	if (m_BubbleList.Remove(pBB))
	{
		m_pOSBView->AddDirtyRegion(pBB);
		return pBB;
	}
	return NULL;
}

// Insert Sprite into the animation sprites list
void CStage::InsertAniSprite(CPhasedSprite* pPS)
{
	// At first remove if exist...
	m_AniList.Remove(pPS);
	if (pPS->GetAniType())
		m_AniList.Insert(pPS);	// add to the check list in CStage::TickAll
}

// Create CActor and insert into the sprite list
CActor* CStage::CreateActor(const int nCharID, const CPoint& point,
							const BOOL bTileID, const WORD wState, const BOOL bThis)
{
	int nGCS=0;	// Greatest ColorSet in this list
	for (POSITION pos = m_AniList.GetHeadPosition(); pos; )
	{
		CPhasedSprite* pPS = (CPhasedSprite*)m_AniList.GetNext(pos);
		if (pPS->GetSrcType() == SPRITE_ACTOR)
		{
			CActor* pA = (CActor*)pPS;
			if (pA->GetCharID() == nCharID)
			{
				nGCS = max(nGCS, pA->GetColorSet()) + 1;
			}
		}
	}
	CActorDesc* pAD = gResMan.GetActorDesc(nCharID);
	if (!pAD)
	{
		CString strMsg;
		strMsg.Format("%d Actor is not defined in RIT.", nCharID);
		AfxMessageBox(strMsg);
		return NULL;
	}
	CActor* pActor = gResMan.LoadActor(nCharID, nGCS, bThis);
	if (!pActor)
		return NULL;
	CPoint ptTID;
	if (bThis)	// point is ignored
	{
		m_pThisActor = pActor;
		ptTID = m_pTiles->GetEntryID(m_strPrevID);	// Find Entry tile
	}
	else
	{
		ptTID = bTileID ? point : m_pTiles->GetNearestTileIndex(point);
	}
	if (!m_pTiles->IsValidTileID(ptTID))
	{
		TRACE("CreateActor - Invalid Tile ID [%d,%d]\n", ptTID.x, ptTID.y);
		ptTID = CPoint(5,12);
	}
	CPoint ptC(m_pTiles->GetCenter(ptTID));
	int nEA = m_pTiles->GetEA(ptTID);	// Elevation for actor
	if (nEA > ELEVATION_LIMIT)
	{
		TRACE("Actor was created in Elevation Limit Area!\n");
//		pActor->SetOpacity(OPACITY50);
		nEA = m_pTiles->GetElevation(ptTID);
	}
	pActor->SetTileMap(m_pTiles);
	pActor->SetElevation(nEA);
	pActor->MoveToEarth(ptC);
	pActor->SetZByEarth();
	pActor->SetMSPT(pAD->GetMSPT());

	pActor->SetOpacity(OPACITY_0);	// At first, hide this actor
	InsertSprite(pActor);	// This is the first chance to draw sprite
	InsertBubble(pActor->GetBubble());

	// OPACITY_0 will be automatically cleared by the behavior descriptions.
	pActor->SetState(wState);	// First behavior

	TRACE("Actor(%lx)\n", pActor);
	return pActor;
}

CActor*	CStage::CreateActor(CMemberInfo& mi, const BOOL bThis)
{
	CActor* pA = CreateActor(mi.GetCharID(), mi.GetTileID(), TRUE,
							mi.GetState(), bThis);
	ASSERT(pA);
	mi.SetTileID(pA->m_mi.GetTileID());	// CreateActor may have changed tile ID
	pA->InitState(mi);
	return pA;
}

void CStage::DeleteActor(CActor* pActor)
{
	if (pActor == m_pThisActor)
		m_pThisActor = NULL;
	delete RemoveBubble(pActor->GetBubble());
	DeleteSprite((CPhasedSprite*)pActor);
}

/*
int CStage::SetZByYBottom(CPhasedSprite* pPS)
{
//	CSize szScr(GetScreenSize());
	CPoint pt(pPS->GetEarthPoint());
	if (!m_pTiles)
		return (-pt.y);
	CPoint ptID(m_pTiles->GetNearestTileIndex(pt));
	return pPS->SetZByGroup(ptID.y);
}
*/
/////////////////////////////////////////////////////////////////////////////////////
// PUMP, HEART!
// CPXClientApp::OnIdle calls this function during idle states between message processing.
// TickAll activates all the actors and coactors in the stage.
int CStage::TickAll()
{
	DWORD dwCurTick = ::GetTickCount();
	int iCalled=0;
	POSITION pos = m_AniList.GetTailPosition();
	while (pos)
	{
		CPhasedSprite* pPS = (CPhasedSprite*)m_AniList.GetPrev(pos);	// Increment position.
		ASSERT(pPS);
		if (dwCurTick >= pPS->GetAlarmTick())
		{
			if (pPS->HeartBeat(dwCurTick))
				m_pOSBView->RenderAndDrawDirtyList();
			iCalled++;
		}
	}
	pos = m_BubbleList.GetTailPosition();
	while (pos)
	{
		CBubble* pBB = m_BubbleList.GetPrev(pos);
		ASSERT(pBB);
		if (dwCurTick >= pBB->GetAlarmTick())
		{
			if (pBB->IsShown())	// Check if there is a bubble
				pBB->Show(FALSE);	// Erase bubble
			iCalled++;
		}
	}
//	if (iCalled)
//		m_pOSBView->RenderAndDrawDirtyList();
	return iCalled;	// counter which indicates how are we busy...
}

// returns StageID on Exit tile
CString* CStage::ActorMove(CActor* pActor, const BOOL bForward)
{
	ASSERT(pActor);
	WORD wDA = pActor->GetDA();
	if (!bForward)	// Backward
	{	// Reverse direction
		if (wDA <= DA_FL)	wDA <<= 2;
		else				wDA >>= 2;
	}
//	CPoint ptTID(m_pTiles->GetNearestTileIndex(pActor->GetEarthPoint()));
	CPoint ptTID(pActor->m_mi.GetTileID());
	if (m_pTiles->GetActorNextTileID(ptTID, wDA))	// ptTID will be reset
	{
		CPoint ptC(m_pTiles->GetCenter(ptTID));
		int nEA = m_pTiles->GetEA(ptTID);
		pActor->MoveTo(ptC, nEA, bForward);

		CPhasedSprite* pTilePS = m_pTiles->GetPS(ptTID);
		if (m_bExitOpen &&
			pTilePS && (pTilePS->GetLinkType() == CPhasedSprite::HLINK_U2_EXIT))
		{
			char szName[256];
			lstrcpy(szName, *pTilePS->GetHyperlink());
			ASSERT((szName[0] == 'x') && (szName[1] == ':'));
			m_strExitID = &szName[2];
			TRACE("Actor landed on Exit tile (%s)!\n", m_strExitID);
			return &m_strExitID;
		}
	}
	else
	{
		pActor->Act(CMD_SCRATCH);
		TRACE("Can't go further...\n");
	}
	return NULL;
}

void CStage::SetExitOpen(const BOOL bOpen)
{
	m_bExitOpen = bOpen;
#ifndef _MALL
	// Insert key sprites on the exit tiles
	CDIB* pDIBKey = gResMan.LoadDIB(DIB_ROOMKEY, TRUE);
	if (!pDIBKey)
	{
		TRACE0("Error: Could not create room key DIB!\n");
		return;
	}

	POSITION pos = m_SpriteList.GetTailPosition();
	CPhasedSprite* pPS;
	int n=0;
	while (pos)
	{
		pPS = (CPhasedSprite*)m_SpriteList.GetPrev(pos);
		if ((pPS->GetSrcType() == SPRITE_TILE) &&
			(pPS->GetLinkType() == CPhasedSprite::HLINK_U2_EXIT))
		{
			CPoint ptC(pPS->GetCenter());
			CPhasedSprite* pPSKey = new CPhasedSprite;
			pPSKey->SetDIB(pDIBKey);
			pPSKey->SetType(SPRITE_STATIC | SPRITE_ANI_FADE);
			switch (n++)
			{
			case 1:
				pPSKey->SetImOp(IMAGE_FLIP);
				pPSKey->SetMSPT(900);
				break;
			case 2:
				pPSKey->SetImOp(IMAGE_VERTICAL);
				pPSKey->SetMSPT(700);
				break;
			case 3:
				pPSKey->SetImOp(IMAGE_FLIP | IMAGE_VERTICAL);
				pPSKey->SetMSPT(500);
				break;
			default:
				pPSKey->SetMSPT(1000);
				break;
			}
			pPSKey->SetNumCells(1, 1);
			pPSKey->SetEarth(CPoint(10, 10));
			pPSKey->MoveToEarth(ptC);
			pPSKey->SetZByEarth();
		// Set Elevation
			InsertSprite(pPSKey);
		}
	}
#endif
}

// ChatSock-related
CActor* CStage::GetActor(PICS_MEMBER pMem)
{
	for (POSITION pos = m_AniList.GetHeadPosition(); pos; )
	{
		CPhasedSprite* pPS = (CPhasedSprite*)m_AniList.GetNext(pos);	// Increment position.
		if (pPS->GetSrcType() == SPRITE_ACTOR)	// pPS->IsKindOf(RUNTIME_CLASS(CActor))
		{
			CActor* pA = (CActor*)pPS;
			if (pA->m_mi.RefMember() == pMem)
				return pA;
		}
	}
	return NULL;
}

CActor*	CStage::GetActor(CString& strNick)
{
	for (POSITION pos = m_AniList.GetHeadPosition(); pos; )
	{
		CPhasedSprite* pPS = (CPhasedSprite*)m_AniList.GetNext(pos);	// Increment position.
		if (pPS->GetSrcType() == SPRITE_ACTOR)	// pPS->IsKindOf(RUNTIME_CLASS(CActor))
		{
			CActor* pA = (CActor*)pPS;
			if (*pA->GetNick() == strNick)
				return pA;
		}
	}
	return NULL;
}

CActor* CStage::GetFrontActor()
{
	if (!m_pThisActor)
		return NULL;

	WORD wDA = m_pThisActor->GetDA();
	CPoint ptTID(m_pThisActor->m_mi.GetTileID());
	if (!m_pTiles->GetActorNextTileID(ptTID, wDA))	// ptTID will be reset
		return NULL;

	for (POSITION pos = m_AniList.GetHeadPosition(); pos; )
	{
		CPhasedSprite* pPS = (CPhasedSprite*)m_AniList.GetNext(pos);	// Increment position.
		if (pPS->GetSrcType() == SPRITE_ACTOR)	// pPS->IsKindOf(RUNTIME_CLASS(CActor))
		{
			if (((CActor*)pPS)->m_mi.GetTileID() == ptTID)
			{
				return (CActor*)pPS;
			}
		}
	}
	return NULL;
}

#ifdef MAPEDITOR
///////////////////////////////////////////////////////////////////////
// Tile Manipulations
// Sprites in the map are not managed by CSpriteList class
// CSpriteList::Insert() method calls CSprite::SetNotificationObject().
// So the sprites handled by CSpriteList are automatically
// updates their dirty regions that are rendered in
// COSBView::RenderAndDrawDirtyList().
// But for the sprites in the map, we should handle dirty regions.

void CStage::InsertTile(CPhasedSprite* pPS)
{
	if (!m_pTiles)
		return;
	m_pTiles->Insert(pPS);
	if (m_pOSBView->GetOSBPalette())
		pPS->MapColorsToPalette((CPalette*)m_pOSBView->GetOSBPalette());
	
	m_pOSBView->AddDirtyRegion(pPS);
}

void CStage::DeleteTile(CPhasedSprite* pPS)
{
	if (!m_pTiles)
		return;
	m_pOSBView->AddDirtyRegion(pPS);
	
	m_pTiles->Delete(pPS);
}

BOOL CStage::MoveTileSpriteTo(CPhasedSprite* pPS, CPoint& ptTo)
{
	if (!m_pTiles)
		return FALSE;

	m_pOSBView->AddDirtyRegion(pPS);	// Save Current Region

	if (!m_pTiles->MoveSpriteTo(pPS, ptTo))
		return FALSE;

	m_pOSBView->AddDirtyRegion(pPS);
	return TRUE;
}
#endif
