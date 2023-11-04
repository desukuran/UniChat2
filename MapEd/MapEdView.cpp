// MapEdView.cpp : implementation of the CMapEdView class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"

#include "MapEdDoc.h"
#include "MapEdView.h"
#include "MapListView.h"
#include "MainFrm.h"
#include "../ResMan.h"
#include "../TileMap.h"
#include "../Stage.h"
#include "GetIntDlg.h"
#include "GetTextDlg.h"

#include "../UC2Ani/DIB.h"
#include "../UC2Ani/DIBPal.h"
#include "../UC2Ani/PhSprite.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan	gResMan;
/////////////////////////////////////////////////////////////////////////////
// CMapEdView

IMPLEMENT_DYNCREATE(CMapEdView, COSBView)

BEGIN_MESSAGE_MAP(CMapEdView, COSBView)
	//{{AFX_MSG_MAP(CMapEdView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SPRITE_DELETE, OnSpriteDelete)
	ON_COMMAND(ID_SPRITE_ELEVATION, OnSpriteElevation)
	ON_COMMAND(ID_SPRITE_FLIP, OnSpriteFlip)
	ON_COMMAND(ID_SPRITE_OPACITY100, OnSpriteOpacity100)
	ON_COMMAND(ID_SPRITE_OPACITY12, OnSpriteOpacity12)
	ON_COMMAND(ID_SPRITE_OPACITY25, OnSpriteOpacity25)
	ON_COMMAND(ID_SPRITE_OPACITY50, OnSpriteOpacity50)
	ON_COMMAND(ID_SPRITE_VERTICAL, OnSpriteVertical)
	ON_COMMAND(ID_SPRITE_FLIPVERT, OnSpriteFlipvert)
	ON_COMMAND(ID_SPRITE_TYPE, OnSpriteType)
	ON_COMMAND(ID_MENU_ANI_REPEAT, OnMenuAniRepeat)
	ON_COMMAND(ID_MENU_ANI_FADE, OnMenuAniFade)
	ON_COMMAND(ID_MENU_NOANI, OnMenuNoani)
	ON_COMMAND(ID_SPRITE_OPACITY75, OnSpriteOpacity75)
	ON_COMMAND(ID_ACTOR_ELEVATION, OnActorElevation)
	ON_COMMAND(ID_MENU_ANI_RANDOM, OnMenuAniRandom)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_MENU_DA_FR, OnMenuDaFr)
	ON_COMMAND(ID_MENU_DA_BL, OnMenuDaBl)
	ON_COMMAND(ID_MENU_DA_BR, OnMenuDaBr)
	ON_COMMAND(ID_MENU_DA_FL, OnMenuDaFl)
	ON_COMMAND(ID_MENU_DA_OPEN, OnMenuDaOpen)
	ON_COMMAND(ID_MENU_DA_CLOSED, OnMenuDaClosed)
	ON_COMMAND(ID_MENU_EXIT_POINT, OnMenuExitPoint)
	ON_COMMAND(ID_MENU_ENTRY_POINT, OnMenuEntryPoint)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEdView construction/destruction

CMapEdView::CMapEdView()
{
	TRACE0("CMapEdView::CMapEdView()\n");
	m_bMouseCaptured = FALSE;
	m_pCS	= NULL;		// LBUTTONDOWN
	m_pMS	= NULL;		// RBUTTONDOWN
	m_wCurResType	= 0;

	TRACE("* sizeof(CDIB)			= %d bytes\n", sizeof(CDIB));
	TRACE("* sizeof(CSprite)		= %d bytes\n", sizeof(CSprite));
	TRACE("* sizeof(CPhasedSprite)	= %d bytes\n", sizeof(CPhasedSprite));
}

CMapEdView::~CMapEdView()
{
	TRACE0("CMapEdView::~CMapEdView()\n");
}

BOOL CMapEdView::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE0("CMapEdView::PreCreateWindow()\n");
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEdView drawing

void CMapEdView::OnDraw(CDC* pDC)
{
	CMapEdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	COSBView::OnDraw(pDC);

	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;
	if (pDoc->IsViewGraph())
		pTM->DrawElevationGraph(pDC);
	if (pDoc->IsViewEAGraph())
		pTM->DrawActorElevationGraph(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEdView printing

BOOL CMapEdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapEdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapEdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapEdView diagnostics

#ifdef _DEBUG
void CMapEdView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEdDoc* CMapEdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEdDoc)));
	return (CMapEdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEdView message handlers

// Create a new buffer and palette to match a new background DIB
BOOL CMapEdView::CreateOSB(CDIB* pDIB)
{
	m_pCS	= NULL;
	m_pMS	= NULL;

	// Create a new buffer and palette
	if (!COSBView::CreateOSB(pDIB))
		return FALSE;

	// Map the colors of the background DIB to
	// the identity palette we just created for the background
	pDIB->MapColorsToPalette((CPalette*)GetOSBPalette());

	// Resize the main frame window to fit the background image
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);	// Try shrinking first
	ResizeParentToFit(TRUE);	// Let's be daring

	Render();	// Render the entire scene to the off-screen buffer
//	DrawOSB();	// Paint the off-screen buffer to the window
	Invalidate(FALSE);

	return TRUE;
}

// Render the scene to the off-screen buffer pClipRect defaults to NULL
void CMapEdView::Render(CRect* pClipRect)
{
	CStage* pStage = GetDocument()->GetStage();
	if (pStage)
		pStage->Render(pClipRect);
}

void CMapEdView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bMouseCaptured)
		return;

	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);

	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;

	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;

	// See if it hit a sprite
	CPhasedSprite* pSprite;
	if (pDoc->IsTileEditMode())
	{
		pSprite = (CPhasedSprite*)pStage->TileHitTest(lpt);
	}
	else
	{
		WORD wRM = pStage->GetRenderMode();
		if ((wRM & RM_ELEV) != RM_ELEV)	// No Elevation mode
		{
			if (!pDoc->IsStandEditMode())	// OnLButtonDblClk
			{
				AfxMessageBox("You can edit only tiles in No Elevation Mode!");
			}
			return;
		}

		pSprite = (CPhasedSprite*)pStage->SpriteHitTest(lpt);
		if (pSprite && (pSprite->GetSrcType() == SPRITE_TILE))
		{
			pSprite = NULL;
		}
	}

	if (pSprite)
	{
		m_bMouseCaptured = TRUE;
		if (m_pCS != pSprite)
		{
			m_pCS = pSprite;
			TRACE("Sprite %8.8XH Selected(%04x)\n", m_pCS, m_pCS->GetType());
		}
		SetCapture();
		m_wCurResType = m_pCS->GetSrcType();

		CSize sEP(m_pCS->GetEarthPoint());
		m_sOffset = lpt - sEP;
//		ShowInfo(lpt);
	}
	else if (pDoc->IsCreateMode())	// Insert New Sprite
	{
		CMapListView* pMLV = pDoc->GetMapListView();
		ASSERT(pMLV);

		m_wCurResType = pMLV->GetSelectedResType();
		if (m_wCurResType == 0)
			return;
		if (pDoc->IsTileEditMode() &&
			((m_wCurResType & SPRITE_SRC_MASK) != SPRITE_TILE))
		{	// Change Edit Mode
//			pDoc->SetEditMode(SPRITE_EDIT_MODE);
			return;
		}

		CString strName;
		if (pMLV->GetSelectedResName(strName) < 0)
			return;

		// Resource Allocation via Resource Manager
		CPhasedSprite* pPS = gResMan.LoadPhasedSprite(strName,
										(m_wCurResType != SPRITE_ACTOR));
		if (!pPS)
		{
			strName += " not found!";
			AfxMessageBox(strName);
			return;
		}
		if ((m_wCurResType == SPRITE_PHASED) ||
			(m_wCurResType == SPRITE_ACTOR))
		{
			pPS->SetType(m_wCurResType, SPRITE_ANI_REPEAT);
			pPS->SetMSPT(150L);
		}
		pPS->SetCell(pMLV->m_nCellID);

		if (pDoc->IsTileEditMode())
		{
			pPS->MoveToCenter(lpt);
			pStage->InsertTile(pPS);	// AddDirtyRegion
			WORD wRM = pStage->GetRenderMode();
			if ((wRM & RM_ELEV) != RM_ELEV)	// No Elevation mode
			{
				int nElev = pPS->GetElevation();
				if (nElev)
				{
					CRect rc;
					pPS->GetRect(rc);
					rc.top		+= nElev;
					rc.bottom	+= nElev;
					AddDirtyRegion(&rc);
				}
			}
		}
		else
		{
			CPoint ptTID(pTM->GetNearestTileIndex(lpt));
			CPoint ptC = pTM->GetCenter(ptTID);
			int	nElev = pTM->GetElevation(ptTID);
			if ((m_wCurResType & SPRITE_SRC_MASK) != SPRITE_WALL)
			{
				if ((m_wCurResType & SPRITE_ACTOR) == SPRITE_ACTOR)
					pPS->SetElevation(pTM->GetEA(ptTID));
				else
					pPS->SetElevation(nElev);	// Normal Sprites
			}
			pPS->MoveToEarth(pDoc->IsTileCoordMode() ? ptC : lpt);

			if (pPS->GetSrcType() == SPRITE_TILE)	// In sprite edit mode
				pPS->SetSrcType(SPRITE_STATIC);	// We put tile as a normal sprite
			pPS->SetZByEarth();
			pStage->InsertSprite(pPS);	// AddDirtyRegion

// we need to put more walls for elevated tile...
			if (nElev && ((m_wCurResType & SPRITE_SRC_MASK) == SPRITE_WALL))
			{
				int n = nElev / ELEVATION_UNIT;
				for (int e=1; e < n; e++)
				{
					CPhasedSprite* pWall = gResMan.LoadPhasedSprite(strName);
					if (!pWall)
					{
						strName += " not found!";
						AfxMessageBox(strName);
						return;
					}
					pWall->SetCell(pMLV->m_nCellID);
					pWall->SetElevation(e * ELEVATION_UNIT);
					pWall->MoveToEarth(ptC);
					pWall->SetZByEarth();
					pStage->InsertSprite(pWall);	// AddDirtyRegion
				}
			}
		}
		RenderAndDrawDirtyList();
//		ShowInfo(lpt);
	}
//	COSBView::OnLButtonDown(nFlags, point);
}

void CMapEdView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bMouseCaptured)
	{
		::ReleaseCapture();
		m_bMouseCaptured = FALSE;
		m_pCS	= NULL;
		m_pMS	= NULL;
	}
//	COSBView::OnLButtonUp(nFlags, point);
}

void CMapEdView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);
	
	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;

	CPoint ptTID(pTM->GetNearestTileIndex(lpt));
	ShowInfo(lpt, ptTID);

	if (!m_bMouseCaptured)
		return;
	ASSERT(m_pCS);

	if (pDoc->IsTileEditMode())
	{
		pStage->MoveTileSpriteTo(m_pCS, lpt);	// Render
	}
	else	// Sprite edit mode
	{
		if (pDoc->IsTileCoordMode())
		{
			CPoint ptC(pTM->GetCenter(ptTID));
			if ((m_wCurResType & SPRITE_ACTOR) == SPRITE_ACTOR)
			{
				m_pCS->SetElevation(pTM->GetEA(ptTID));	// for Actors
				switch (pTM->GetDA(ptTID))
				{
				case DA_OPEN:	m_pCS->SetOpacity(OPACITY_100);	break;
				case DA_CLOSED:	m_pCS->SetOpacity(OPACITY_25);	break;
				default:		m_pCS->SetOpacity(OPACITY_100);	break;
				}
			}
			else if ((m_wCurResType & SPRITE_WALL) != SPRITE_WALL)
			{
				m_pCS->SetElevation(pTM->GetElevation(ptTID));	// for Sprites
			}
			m_pCS->MoveToEarth(ptC);
		}
		else	// Free coord. mode
		{
			CPoint ptNew(lpt - m_sOffset);
			m_pCS->MoveToEarth(ptNew);
		}
		m_pCS->SetZByEarth();
	// For sprites inserted into CSpriteList, SetZ() adds dirty region for itself.
	}
	RenderAndDrawDirtyList();
//		GetDocument()->SetModifiedFlag(TRUE);
//	COSBView::OnMouseMove(nFlags, point);
}

void CMapEdView::ShowInfo(const CPoint& point, const CPoint& ptTID)
{
	// Show current state in the status bar
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	ASSERT(pFrame);
	int nS=0;
	int nA=0;
	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (pStage)
	{
		nS = pStage->GetNumSprites();
		nA = pStage->GetNumAniSprites();
	}

	char buf[256];
	wsprintf(buf, "(%d,%d) T[%d,%d] Sprites:%d Ani:%d",
			point.x, point.y, ptTID.x, ptTID.y, nS, nA);
	pFrame->SetStatusBarText(buf);
}

void CMapEdView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);

	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;

	if (pDoc->IsStandEditMode())
	{
		m_ptHit = lpt;
		OnMenuDirectionAttribute(DA_CLOSED);
		return;
	}

	// See if it hit a sprite
	CPhasedSprite* pSprite;
	if (pDoc->IsTileEditMode())
	{
		pSprite = (CPhasedSprite*)pStage->TileHitTest(lpt);
		if (pSprite)
		{
			CPoint ptTID(pTM->GetNearestTileIndex(lpt));
			pTM->IncEA(ptTID, ELEVATION_UNIT);
		}
	}
	else
	{
		pSprite = (CPhasedSprite*)pStage->SpriteHitTest(lpt);
		if (pSprite && (pSprite->GetSrcType() == SPRITE_TILE))
		{
			pSprite = NULL;
		}
	}

	if (pSprite)
	{
		pSprite->IncElevation(ELEVATION_UNIT);
		pSprite->MoveBy(0, -ELEVATION_UNIT);
		pSprite->SetZByEarth();
		if (pDoc->IsViewGraph())
			Invalidate(FALSE);	// To update DrawElevationGraph()
		RenderAndDrawDirtyList();
	}
	COSBView::OnLButtonDblClk(nFlags, point);
}

void CMapEdView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);

	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;

	if (pDoc->IsStandEditMode())
	{
		CTileMap* pTM = pStage->GetTileMap();
		if (!pTM)
			return;

		CPoint ptTID(pTM->GetNearestTileIndex(lpt));

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_GRID));
		CMenu* pPopup = menu.GetSubMenu(0);
		m_ptHit = lpt;

		WORD wDA = pTM->GetDA(ptTID);
		if ((wDA & DA_FR) == DA_FR)
			pPopup->CheckMenuItem(ID_MENU_DA_FR, MF_CHECKED);
		if ((wDA & DA_FL) == DA_FL)
			pPopup->CheckMenuItem(ID_MENU_DA_FL, MF_CHECKED);
		if ((wDA & DA_BR) == DA_BR)
			pPopup->CheckMenuItem(ID_MENU_DA_BR, MF_CHECKED);
		if ((wDA & DA_BL) == DA_BL)
			pPopup->CheckMenuItem(ID_MENU_DA_BL, MF_CHECKED);
		if (wDA == DA_OPEN)
			pPopup->CheckMenuItem(ID_MENU_DA_OPEN, MF_CHECKED);
		else if (wDA == DA_CLOSED)
			pPopup->CheckMenuItem(ID_MENU_DA_CLOSED, MF_CHECKED);

		ClientToScreen(&point);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		return;
	}

	// See if it hit a sprite
	CPhasedSprite* pSprite;
	if (pDoc->IsTileEditMode())
	{
		pSprite = (CPhasedSprite*)pStage->TileHitTest(lpt);
	}
	else
	{
		pSprite = (CPhasedSprite*)pStage->SpriteHitTest(lpt);
		if (pSprite && (pSprite->GetSrcType() == SPRITE_TILE))
		{
			pSprite = NULL;
		}
	}
	if (!pSprite)
		return;

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_TILE));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
	m_pMS = pSprite;
	m_ptHit = lpt;

	CString strName(*pSprite->GetName());
	gResMan.MakeResName(strName);
	CString strZ;
	strZ.Format("[%d]", pSprite->GetZ());
	strName += strZ;
	CString strType;
	switch (pSprite->GetSrcType())
	{
	case SPRITE_TILE:		strType = "Tile";	break;
	case SPRITE_WALL:		strType = "Wall";	break;
	case SPRITE_STATIC:		strType = "Sprite";	break;
	case SPRITE_PHASED:		strType = "Phased";	break;
	case SPRITE_ACTOR:		strType = "Actor";	break;
	}
	switch (pSprite->GetAniType())
	{
	case SPRITE_ANI_REPEAT:	strType += "(Repeat)";	break;
	case SPRITE_ANI_FADE:	strType += "(Fade)";	break;
	case SPRITE_ANI_ACTOR:	strType += "(Actor)";	break;
	}
	strName += strType;
	pPopup->InsertMenu(0, MF_BYPOSITION | MF_STRING, ID_SPRITE_TYPE, strName);
	CString strText;
	strText.Format("Elev=%d", pSprite->GetElevation());
	pPopup->ModifyMenu(ID_SPRITE_ELEVATION, MF_BYCOMMAND | MF_STRING,
						ID_SPRITE_ELEVATION, strText);
	if (pSprite->GetSrcType() == SPRITE_TILE)
	{
		CTileMap* pTM = pStage->GetTileMap();
		if (pTM)
		{
			CPoint ptTID(pTM->GetNearestTileIndex(lpt));
			strText.Format("A.Elev=%d", pTM->GetEA(ptTID));
			pPopup->InsertMenu(ID_SPRITE_ELEVATION, MF_BYCOMMAND | MF_STRING,
								ID_ACTOR_ELEVATION, strText);
			if (pSprite->HasHyperlink())
			{
				if (pSprite->GetLinkType() == CPhasedSprite::HLINK_U2_ENTRY)
				{
					pPopup->ModifyMenu(ID_MENU_ENTRY_POINT, MF_BYCOMMAND | MF_STRING,
										ID_MENU_ENTRY_POINT, *pSprite->GetHyperlink());
					pPopup->CheckMenuItem(ID_MENU_ENTRY_POINT, MF_CHECKED);
				}
				else
				{
					pPopup->ModifyMenu(ID_MENU_EXIT_POINT, MF_BYCOMMAND | MF_STRING,
										ID_MENU_EXIT_POINT, *pSprite->GetHyperlink());
					pPopup->CheckMenuItem(ID_MENU_EXIT_POINT, MF_CHECKED);
				}
			}
		}
	}
	else
	{
		pPopup->RemoveMenu(ID_MENU_ENTRY_POINT, MF_BYCOMMAND | MF_STRING);
		pPopup->RemoveMenu(ID_MENU_EXIT_POINT, MF_BYCOMMAND | MF_STRING);
	}

	if (pSprite->IsImageFlip())
		pPopup->CheckMenuItem(ID_SPRITE_FLIP, MF_CHECKED);
	if (pSprite->IsImageVertical())
		pPopup->CheckMenuItem(ID_SPRITE_VERTICAL, MF_CHECKED);
	if (pSprite->IsImageFlip() && pSprite->IsImageVertical())
		pPopup->CheckMenuItem(ID_SPRITE_FLIPVERT, MF_CHECKED);

	switch (pSprite->GetAniType())
	{
	case SPRITE_ANI_REPEAT:
		pPopup->CheckMenuItem(ID_MENU_ANI_REPEAT, MF_CHECKED);	break;
	case SPRITE_ANI_FADE:
		pPopup->CheckMenuItem(ID_MENU_ANI_FADE, MF_CHECKED);	break;
	case SPRITE_ANI_RANDOM:
		pPopup->CheckMenuItem(ID_MENU_ANI_RANDOM, MF_CHECKED);	break;
	}

	WORD wImOp = pSprite->GetImOp();
	switch (wImOp & OPACITY_MASK)
	{
	case OPACITY_100:
		pPopup->CheckMenuItem(ID_SPRITE_OPACITY100, MF_CHECKED);	break;
	case OPACITY_75:
		pPopup->CheckMenuItem(ID_SPRITE_OPACITY75, MF_CHECKED);		break;
	case OPACITY_50:
		pPopup->CheckMenuItem(ID_SPRITE_OPACITY50, MF_CHECKED);		break;
	case OPACITY_25:
		pPopup->CheckMenuItem(ID_SPRITE_OPACITY25, MF_CHECKED);		break;
	case OPACITY_12:
		pPopup->CheckMenuItem(ID_SPRITE_OPACITY12, MF_CHECKED);		break;
	}

	ClientToScreen(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

//	COSBView::OnRButtonDown(nFlags, point);
}

void CMapEdView::OnSpriteDelete() 
{
	if (!m_pMS)
		return;
	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	if (pDoc->IsTileEditMode())
		pStage->DeleteTile(m_pMS);
	else
		pStage->DeleteSprite(m_pMS);
	m_pCS = NULL;
	m_pMS = NULL;
	RenderAndDrawDirtyList();
}

////////////////////////////////////////////////
// Elevation
void CMapEdView::OnSpriteElevation() 
{
	if (!m_pMS)
		return;
	CMapEdDoc* pDoc = GetDocument();

	int nElevOld = m_pMS->GetElevation();

	CGetIntDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_ELEVATION);
	dlg.m_nNew = nElevOld;	// / ELEVATION_UNIT;
	if (dlg.DoModal() != IDOK)
		return;

	m_pMS->SetElevation(dlg.m_nNew);	// * ELEVATION_UNIT);
	m_pMS->MoveBy(0, nElevOld - dlg.m_nNew);	// * ELEVATION_UNIT);
	m_pMS->SetZByEarth();

	if (m_pMS->GetSrcType() == SPRITE_TILE)
	{
		CStage* pStage = pDoc->GetStage();
		if (pStage)
		{
			CTileMap* pTM = pStage->GetTileMap();
			if (pTM)
			{	// call GetNearestTileIndex() after MoveBy
				CPoint ptTID(pTM->GetNearestTileIndex(m_pMS));
				pTM->SetEA(ptTID, m_pMS->GetElevation());
			}
		}
	}
	RenderAndDrawDirtyList();
	if (pDoc->IsViewGraph())
		Invalidate(FALSE);	// To update DrawElevationGraph()
}

void CMapEdView::OnActorElevation() 
{
	if (!m_pMS)
		return;
	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;

	// m_pMS is tile
	CPoint ptTID(pTM->GetNearestTileIndex(m_pMS));

	CGetIntDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_ACTOR_ELEVATION);
	dlg.m_nNew = pTM->GetEA(ptTID);
	if (dlg.DoModal() != IDOK)
		return;

	pTM->SetEA(ptTID, dlg.m_nNew);
	if (pDoc->IsViewEAGraph())
		Invalidate(FALSE);	// To update DrawElevationGraph()
}

void CMapEdView::ChangeSpriteImOp(const int nMenu)
{
	if (!m_pMS)
		return;

	WORD wImOp = m_pMS->GetImOp();
	switch (nMenu)
	{
	case ID_SPRITE_FLIP:
			wImOp ^= IMAGE_FLIP;		break;
	case ID_SPRITE_VERTICAL:
			wImOp ^= IMAGE_VERTICAL;	break;
	case ID_SPRITE_FLIPVERT:
		if (m_pMS->IsImageFlip() && m_pMS->IsImageVertical())
			wImOp &= ~ORIENT_MASK;
		else
			wImOp |= (IMAGE_FLIP | IMAGE_VERTICAL);	break;
	case ID_SPRITE_OPACITY100:
			wImOp = (wImOp & ~OPACITY_MASK) | OPACITY_100;		break;
	case ID_SPRITE_OPACITY75:
			wImOp = (wImOp & ~OPACITY_MASK) | OPACITY_75;		break;
	case ID_SPRITE_OPACITY50:
			wImOp = (wImOp & ~OPACITY_MASK) | OPACITY_50;		break;
	case ID_SPRITE_OPACITY25:
			wImOp = (wImOp & ~OPACITY_MASK) | OPACITY_25;		break;
	case ID_SPRITE_OPACITY12:
			wImOp = (wImOp & ~OPACITY_MASK) | OPACITY_12;		break;
	}
	m_pMS->SetImOp(wImOp);

	AddDirtyRegion(m_pMS);
	RenderAndDrawDirtyList();
}

void CMapEdView::OnSpriteFlip()			{	ChangeSpriteImOp(ID_SPRITE_FLIP);	}
void CMapEdView::OnSpriteVertical()		{	ChangeSpriteImOp(ID_SPRITE_VERTICAL);	}
void CMapEdView::OnSpriteFlipvert()		{	ChangeSpriteImOp(ID_SPRITE_FLIPVERT);	}

void CMapEdView::OnSpriteOpacity100()	{	ChangeSpriteImOp(ID_SPRITE_OPACITY100);	}
void CMapEdView::OnSpriteOpacity75()	{	ChangeSpriteImOp(ID_SPRITE_OPACITY75);	}
void CMapEdView::OnSpriteOpacity50()	{	ChangeSpriteImOp(ID_SPRITE_OPACITY50);	}
void CMapEdView::OnSpriteOpacity25()	{	ChangeSpriteImOp(ID_SPRITE_OPACITY25);	}
void CMapEdView::OnSpriteOpacity12()	{	ChangeSpriteImOp(ID_SPRITE_OPACITY12);	}

/*
void CMapEdView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// switch for input key
	switch (nChar)
	{
	case VK_UP:		pDoc->SendCommand(CMD_MOVE_NORTH);	break;
	case VK_LEFT:	pDoc->SendCommand(CMD_MOVE_WEST);	break;
	case VK_DOWN:	pDoc->SendCommand(CMD_MOVE_SOUTH);	break;
	case VK_RIGHT:	pDoc->SendCommand(CMD_MOVE_EAST);	break;
//	case VK_F5:		SetMode(0);	break;
//	case VK_F6:		SetMode(1);	break;
//	case VK_F7:		SetMode(1);	break;
//	case VK_F8:		SetMode(2);	break;
//	case VK_F9:		SetMode(3);	break;
//	case VK_F10:	SetMode(4);	break;
	}
	// Show current state in the status bar
//	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
//	ASSERT(pFrame);
//	pFrame->m_wndStatusBar.SetWindowText(buf);
	
	COSBView::OnKeyDown(nChar, nRepCnt, nFlags);
}
*/

void CMapEdView::OnSpriteType() 
{
	CMapEdDoc* pDoc = GetDocument();
	CMapListView* pMLV = pDoc->GetMapListView();
	ASSERT(pMLV);

	if (!m_pMS)
		return;
	CString strName(*m_pMS->GetName());
	gResMan.MakeResName(strName);
	int i = gResMan.GetSpriteID(strName);
	if (i >= 0)
		pMLV->SetSelectedItem(i);
}

void CMapEdView::AnimateSprite(CPhasedSprite* pPS, const WORD wAniType)
{
	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;

	CGetIntDlg	dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_MSPT);
	dlg.m_nNew = pPS->GetMSPT() ? pPS->GetMSPT() : 100;

	if (dlg.DoModal() != IDOK)
		return;
	pPS->SetMSPT(dlg.m_nNew);	// includes SetAlarmTick();
	pPS->SetAniType(wAniType);
	pStage->InsertAniSprite(pPS);
}

void CMapEdView::OnMenuAniRepeat() 
{
	if (!m_pMS)
		return;
	AnimateSprite(m_pMS, SPRITE_ANI_REPEAT);
}

void CMapEdView::OnMenuAniFade() 
{
	if (!m_pMS)
		return;
	AnimateSprite(m_pMS, SPRITE_ANI_FADE);
}

void CMapEdView::OnMenuAniRandom() 
{
	if (!m_pMS)
		return;
	AnimateSprite(m_pMS, SPRITE_ANI_RANDOM);
}

void CMapEdView::OnMenuNoani() 
{
	if (!m_pMS)
		return;

	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;
//	CString strName(*m_pMS->GetName());
//	m_pMS->SetType(gResMan.GetSpriteTypeByName(strName));	// Restore
	m_pMS->SetAniType(0);
	pStage->RemoveAniSprite(m_pMS);	// Multiple calls possible
}

void CMapEdView::AdjustFrameWindow()
{
	CMainFrame* pMF = (CMainFrame*)GetParentFrame();
	ASSERT(pMF);
//	pMF->SetFreeze(FALSE);
	pMF->SetPalette((CPalette*)GetOSBPalette());

	return;
/*
	CDIB* pDIB = GetOSB();
	if (pDIB)
	{
		CClientDC dc(this);
		int nWidth = min(dc.GetDeviceCaps(HORZRES) - 40, pDIB->GetWidth());
		int nHeight = min(dc.GetDeviceCaps(VERTRES) - 40, pDIB->GetHeight());
		if (((pDIB->GetWidth() + 40) >= dc.GetDeviceCaps(HORZRES)) ||
			((pDIB->GetHeight() + 40) >= dc.GetDeviceCaps(VERTRES)))
			pMF->SetWindowPos(&wndTopMost, 0, 0, nWidth, nHeight, SWP_NOZORDER);
		else
			pMF->SetWindowPos(&wndTopMost, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
	}
	// Resize the main frame window to fit the background image
	pMF->RecalcLayout();
	ResizeParentToFit(FALSE);	// Try shrinking first
	ResizeParentToFit(TRUE);	// Let's be daring
//	pMF->SetFreeze();
*/
}

void CMapEdView::OnMenuEntryPoint() 
{
	SetEntryExitPoint(TRUE);
}

void CMapEdView::OnMenuExitPoint()
{
	SetEntryExitPoint(FALSE);
}

void CMapEdView::SetEntryExitPoint(const BOOL bEntry)
{
	if (!m_pMS)
		return;
	extern const char* STAGEFILE_FILTER;

	CString strFilename(*m_pMS->GetHyperlink());
	::SetCurrentDirectory(*gResMan.GetResPath());
	// Show a File Save dialog to get the name.
	CFileDialog dlg(TRUE,	// Open
					NULL,	// No default extension
					strFilename,	// initial file name
					OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
					STAGEFILE_FILTER);
	if (dlg.DoModal() == IDOK)
	{
		strFilename = dlg.GetPathName();
		if (!strFilename.IsEmpty())
		{
			gResMan.MakeResName(strFilename);
			CString strHL;
			strHL.Format("%c:%s", bEntry ? 'e' : 'x', strFilename);
			m_pMS->SetHyperlink(strHL);
		}
	}
	else
	{
		if (!strFilename.IsEmpty())
			m_pMS->GetHyperlink()->Empty();	// Erase
	}
	if (GetDocument()->IsViewGraph())
		Invalidate(FALSE);	// To update DrawElevationGraph()
/*
	CGetTextDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_STAGE_LINK);
	CString* pStr = m_pMS->GetHyperlink();
	if (!pStr->IsEmpty())
		dlg.m_strText = *pStr;
	if (dlg.DoModal() == IDOK)
	{
		if (!dlg.m_strText.IsEmpty())
			m_pMS->SetHyperlink(dlg.m_strText);
	}
*/
}

BOOL CMapEdView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CMapEdDoc* pDoc = GetDocument();
	if (pDoc->IsTileEditMode())
	{
		::SetCursor(AfxGetApp()->LoadCursor(m_bMouseCaptured ? IDC_GREP_DOWN : IDC_GREP_UP));
		return TRUE;
	}
	else
		return COSBView::OnSetCursor(pWnd, nHitTest, message);
}

// On Direction Attribute: Forward Right
void CMapEdView::OnMenuDaFr()		{ OnMenuDirectionAttribute(DA_FR); }
void CMapEdView::OnMenuDaBl()		{ OnMenuDirectionAttribute(DA_BL); }
void CMapEdView::OnMenuDaBr()		{ OnMenuDirectionAttribute(DA_BR); }
void CMapEdView::OnMenuDaFl()		{ OnMenuDirectionAttribute(DA_FL); }
void CMapEdView::OnMenuDaOpen()		{ OnMenuDirectionAttribute(DA_OPEN); }
void CMapEdView::OnMenuDaClosed()	{ OnMenuDirectionAttribute(DA_CLOSED); }

void CMapEdView::OnMenuDirectionAttribute(const WORD wDA)
{
	CMapEdDoc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;

	CPoint ptTID(pTM->GetNearestTileIndex(m_ptHit));
	CPoint ptCtr(pTM->GetNearestTileCenter(m_ptHit));

	WORD wDirAttr;
	if ((wDA == DA_OPEN) || (wDA == DA_CLOSED))	// Assign
	{
		wDirAttr = wDA;
	}
	else
	{
		wDirAttr = pTM->GetDA(ptTID);
		wDirAttr ^= wDA;	// toggle only the specified bit
	}

	pTM->SetDA(ptTID, wDirAttr);

	CRect rcDirty;
	rcDirty.SetRect(ptCtr.x-64, ptCtr.y-32, ptCtr.x+64, ptCtr.y+32);
	AddDirtyRegion(&rcDirty);
	RenderAndDrawDirtyList();
}

void CMapEdView::RecalculateDA() 
{
	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;
	pTM->RecalculateDA();
}

void CMapEdView::SynchronizeEA()
{
	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;
	CTileMap* pTM = pStage->GetTileMap();
	if (!pTM)
		return;
	pTM->SynchronizeAllEA();
}
