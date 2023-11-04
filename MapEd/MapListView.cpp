// MapListView.cpp : implementation file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"
#include "MapListView.h"
#include "MapEdView.h"
#include "MapEdDoc.h"
#include "../ResMan.h"
#include "../UC2Ani/PhSprite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan	gResMan;

/////////////////////////////////////////////////////////////////////////////
// CMapListView

IMPLEMENT_DYNCREATE(CMapListView, CFormView)

CMapListView::CMapListView()
	: CFormView(CMapListView::IDD)
{
	TRACE0("CMapListView::CMapListView()\n");
	//{{AFX_DATA_INIT(CMapListView)
	m_strCellInfo = _T("");
	m_nCellID = 0;
	//}}AFX_DATA_INIT
	m_ilObject.Create(IDB_IL_OBJECT, 16, 1, CLR_NONE);
	m_nIndex	= -1;
	m_nCellID	= 0;
	m_pPS		= NULL;
	m_bFirst	= TRUE;
}

CMapListView::~CMapListView()
{
	TRACE0("CMapListView::~CMapListView()\n");
	if (m_pPS)
		delete m_pPS;
}

void CMapListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapListView)
	DDX_Control(pDX, IDC_LIST_OBJ, m_lcObject);
	DDX_Text(pDX, IDC_ST_CELL_INFO, m_strCellInfo);
	DDX_Scroll(pDX, IDC_SB_CELL_ID, m_nCellID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapListView, CFormView)
	//{{AFX_MSG_MAP(CMapListView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_OBJ, OnClickListObj)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_OBJ, OnDblclkListObj)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapListView diagnostics

#ifdef _DEBUG
void CMapListView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMapListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMapEdDoc* CMapListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEdDoc)));
	return (CMapEdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapListView message handlers

// CDocument::UpdateAllViews() will call this function
// Multiple calls possible
void CMapListView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	if (m_bFirst)
	{
		Initialize();
		m_bFirst = FALSE;
	}
	UpdateList();
}

void CMapListView::Initialize()
{
	// Prepare List Control for Channels list
	m_lcObject.SetImageList(&m_ilObject, LVSIL_SMALL);

	char*	szColumn[]	= {"SPRITE", "CxR"};
	int		nWidth[]	= {120, 50};

	LV_COLUMN	lvC;	// list view column structure
	lvC.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;	// valid members
	lvC.fmt		= LVCFMT_LEFT;	// left-align column
	// Add the columns.
	for (int i=0; i < sizeof(nWidth)/sizeof(nWidth[0]); i++)
	{
		lvC.cx			= nWidth[i];	// width of column in pixels
		lvC.iSubItem	= i;
		lvC.pszText		= szColumn[i];
		if (m_lcObject.InsertColumn(i, &lvC) == -1)
			return;
	}

	CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_CELL_ID);
	CRect rc;
	pSB->GetWindowRect(&rc);
	m_rcDraw = CRect(5, 208+25, 5+rc.Width(), 480+25);
	pSB->ShowWindow(FALSE);
}

void CMapListView::UpdateList()
{
	// Initialize
	m_lcObject.DeleteAllItems();
	m_nIndex	= -1;
	m_nCellID	= 0;
	if (m_pPS)
	{
		delete m_pPS;
		m_pPS = NULL;
	}
	InvalidateRect(&m_rcDraw);

	int	nSprites = gResMan.GetNumSprites();
	for (int i=0; i < nSprites; i++)
	{
		LV_ITEM		lvI;	// list view item structure
		::ZeroMemory(&lvI, sizeof(lvI));
		lvI.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
		lvI.state		= 0;
		lvI.stateMask	= 0;

		lvI.iItem		= i;
		lvI.iSubItem	= 0;
		CString* pStr = gResMan.GetSpriteName(i);
		lvI.pszText		= pStr->GetBuffer(17);
		lvI.cchTextMax	= 17;
		switch (gResMan.GetSpriteType(i))
		{
		case SPRITE_TILE:	lvI.iImage = 0;	break;
		case SPRITE_WALL:	lvI.iImage = 1;	break;
		case SPRITE_STATIC:	lvI.iImage = 2;	break;
		case SPRITE_PHASED: lvI.iImage = 3;	break;
		case SPRITE_ACTOR:	lvI.iImage = 4;	break;
		}
		CSize szCell(gResMan.GetSpriteColRow(i));
		lvI.lParam		= (LPARAM)(szCell.cx * szCell.cy);	// # of cells
		m_lcObject.InsertItem(&lvI);

		CString strCell;
		strCell.Format("%dx%d", szCell.cx, szCell.cy);
		m_lcObject.SetItemText(i, 1, strCell);
	}
}

// Update Items and Images
void CMapListView::UpdateItemImage(const int nIndex)
{
	int nCells = (int)m_lcObject.GetItemData(nIndex);
	CString strName = m_lcObject.GetItemText(nIndex, 0);	// SubItem=0
	m_strCellInfo.Format("%s (%d/%d)", strName, 0, nCells);
	UpdateData(FALSE);
	CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_CELL_ID);
	pSB->SetScrollRange(0, nCells-1);
	pSB->SetScrollPos(0);
	pSB->ShowWindow(nCells > 1);	// // Hide for STATIC SPRITE

	// We'll not reuse DIB here:
	// Since this image is not need to be resident in memory.
	CPhasedSprite* pPS = gResMan.LoadPhasedSprite(strName, FALSE);
	if (!pPS)
	{
		delete pPS;
		strName += " not found!";
		AfxMessageBox(strName);
		return;
	}

	if (m_pPS)
		delete m_pPS;	// Delete previously allocated resource
	m_pPS = pPS;
	m_nCellID = 0;
	m_pPS->SetCell(m_nCellID);
	if (m_pPS->GetSrcType() == SPRITE_TILE)
		GetDocument()->SetEditMode(TILE_EDIT_MODE);
	else
		GetDocument()->SetEditMode(SPRITE_EDIT_MODE);

	InvalidateRect(&m_rcDraw);
}

void CMapListView::OnClickListObj(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	m_lcObject.ScreenToClient(&point);

	int nHitIndex = m_lcObject.HitTest(point);
	if (nHitIndex == -1)
		return;
	if (m_nIndex != nHitIndex)
	{
		m_nIndex = nHitIndex;
		UpdateItemImage(m_nIndex);
	}
	*pResult = 0;
}

void CMapListView::OnDblclkListObj(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	m_lcObject.ScreenToClient(&point);
	
	int nHitIndex = m_lcObject.HitTest(point);
	if (nHitIndex == -1)
		return;
	if (m_nIndex != nHitIndex)
	{
		m_nIndex = nHitIndex;
		UpdateItemImage(m_nIndex);
	}
	*pResult = 0;
}

void CMapListView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_CELL_ID);
	if (pScrollBar == pSB)
	{
		if (m_nIndex < 0)
			return;
		int nCells = (int)m_lcObject.GetItemData(m_nIndex);
		CString strName = m_lcObject.GetItemText(m_nIndex, 0);	// SubItem=0
		int nMin, nMax;
		pSB->GetScrollRange(&nMin, &nMax);
		switch (nSBCode)
		{
		case SB_THUMBPOSITION:
			m_nCellID = nPos;
			pSB->SetScrollPos(nPos);
			break;
		case SB_LINELEFT:
			m_nCellID = pSB->GetScrollPos() - 1;
			if (m_nCellID < nMin)
				m_nCellID = nMax;	// Wrap
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_LINERIGHT:
			m_nCellID = pSB->GetScrollPos() + 1;
			if (m_nCellID > nMax)
				m_nCellID = nMin;	// Wrap
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_PAGELEFT:
			m_nCellID = pSB->GetScrollPos() - (nMax - nMin) / 5;
			if (m_nCellID < nMin)
				m_nCellID = nMin;
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_PAGERIGHT:
			m_nCellID = pSB->GetScrollPos() + (nMax - nMin) / 5;
			if (m_nCellID > nMax)
				m_nCellID = nMax;
			pSB->SetScrollPos(m_nCellID);
			break;
		}
		if (m_pPS)
		{
			InvalidateRect(&m_rcDraw, FALSE);
/*
// Synchronize the sprite in CMapEdView with this selection
			CMapEdView* pMEV = GetDocument()->GetMapEdView();
			CPhasedSprite* pSV = pMEV->GetCapturedSprite();
			if (m_pPS->IsSameDIB(pSV))
			{
				pSV->SetCell(m_nCellID);
				pMEV->RenderAndDrawDirtyList();
			}
*/
		}
		m_strCellInfo.Format("%s (%d/%d)", strName, m_nCellID, nCells);
		UpdateData(FALSE);
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMapListView::OnDraw(CDC* pDC) 
{
//	CFormView::OnDraw(pDC);
//	OnPrepareDC(pDC);	// CScroll changes the viewport origin and mapping mode.
	CRect rcDraw(m_rcDraw);
//	pDC->DPtoLP(&rcDraw);		// THIS WAS THE KEY!

	if (!m_pPS || (m_nIndex < 0))
		return;

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	CMapEdDoc* pDoc = GetDocument();
	CMapEdView* pMEV = pDoc->GetMapEdView();
	CPalette* pPal = (CPalette*)pMEV->GetOSBPalette();
	if (pPal)
	{
		pPalOld = pDC->SelectPalette(pPal, FALSE);	// bForceBackground = FALSE
		pDC->RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}

	CPoint ptLT(rcDraw.TopLeft());
	if (gResMan.GetSpriteType(m_nIndex) == SPRITE_TILE)
	{
		int nCells = m_pPS->GetNumCells();
		int w = m_pPS->GetWidth() + 2;
		int h = m_pPS->GetHeight() + 2;
		for (int i=0; i < nCells; i++)
		{
			ptLT.y = rcDraw.top + h * (i/3);
			ptLT.x = rcDraw.left + w * (i%3);
			m_pPS->SetCell(i);
			m_pPS->Draw(pDC, ptLT);
			if (i == m_nCellID)
			{
				CPen pen(PS_SOLID, 1, PALETTERGB(255,0,0));
				pDC->SelectObject(&pen);
				pDC->MoveTo(ptLT);
				pDC->LineTo(ptLT.x+w-3, ptLT.y);
				pDC->LineTo(ptLT.x+w-3, ptLT.y+h-3);
				pDC->LineTo(ptLT.x, ptLT.y+h-3);
				pDC->LineTo(ptLT);
			}
		}
	}
	else
	{
		m_pPS->SetCell(m_nCellID);
		m_pPS->Draw(pDC, ptLT);
		// Draw Earth point
		CSize sE(m_pPS->GetEarth());
		CPen pen(PS_SOLID, 1, PALETTERGB(255,0,255));	// Magenta
		pDC->SelectObject(&pen);
		pDC->MoveTo(ptLT.x, ptLT.y + sE.cy);
		pDC->LineTo(ptLT.x + m_pPS->GetWidth(), ptLT.y + sE.cy);
		pDC->MoveTo(ptLT.x + sE.cx, ptLT.y);
		pDC->LineTo(ptLT.x + sE.cx, ptLT.y + m_pPS->GetHeight());
	}
	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
}

int CMapListView::GetSelectedResName(CString& strName) const
{
	if (m_nIndex >= 0)
		strName = m_lcObject.GetItemText(m_nIndex, 0);	// SubItem=0
	return m_nIndex;
}

WORD CMapListView::GetSelectedResType() const
{
	return ((m_nIndex >= 0) ? gResMan.GetSpriteType(m_nIndex) : 0);
}

void CMapListView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_pPS || (m_nIndex < 0) || !m_rcDraw.PtInRect(point))
		return;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_GREP_DOWN));
	if (GetSelectedResType() == SPRITE_TILE)
	{
		int x = m_rcDraw.left;
		int y = m_rcDraw.top;
		int w = m_pPS->GetWidth() + 2;
		int h = m_pPS->GetHeight() + 2;
		int i = ((point.y - m_rcDraw.top)/h) * 3 +
				((point.x - m_rcDraw.left)/w);
		if (i < m_pPS->GetNumCells())
		{
			m_nCellID = i;
			m_pPS->SetCell(m_nCellID);
			CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_CELL_ID);
			OnHScroll(SB_THUMBPOSITION, m_nCellID, pSB);
		}
	}

	CFormView::OnLButtonDown(nFlags, point);
}

void CMapListView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_pPS && (m_nIndex >= 0) && m_rcDraw.PtInRect(point))
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_GREP_UP));
	}
	CFormView::OnMouseMove(nFlags, point);
}

// Document Window calls this
void CMapListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (m_lcObject.GetSafeHwnd())	// Invalidates any calls before OnInitialUpdate()
		UpdateList();
}

void CMapListView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
/*
	// switch for input key
	switch (nChar)
	{
	case VK_UP:		pDoc->SendCommand(CMD_MOVE_NORTH);	break;
	case VK_LEFT:	pDoc->SendCommand(CMD_MOVE_WEST);	break;
	case VK_DOWN:	pDoc->SendCommand(CMD_MOVE_SOUTH);	break;
	case VK_RIGHT:	pDoc->SendCommand(CMD_MOVE_EAST);	break;
	}
*/
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMapListView::SetSelectedItem(const int nIndex)
{
	if (m_nIndex == nIndex)
		return;
	m_lcObject.SetItemState(m_nIndex, 0, LVIF_STATE);
	m_lcObject.SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_nIndex = nIndex;
	UpdateItemImage(m_nIndex);
}

void CMapListView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CFormView::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CMapListView::OnQueryNewPalette() 
{
	TRACE("CMapListView::OnQueryNewPalette()\n");
	CMapEdDoc* pDoc = GetDocument();
	CMapEdView* pMEV = pDoc->GetMapEdView();
	if (pMEV->GetOSBPalette())
	{
		CDC* pdc = GetDC();
		CPalette* poldpal = pdc->SelectPalette((CPalette*)pMEV->GetOSBPalette(),
												FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (poldpal)
			pdc->SelectPalette(poldpal, FALSE);
		ReleaseDC(pdc);
		if (u)
		{	// Some colors changed so we need to do a repaint.
			Invalidate(); // Repaint the lot.
			return TRUE; // Say we did something.
		}
	}
	return CFormView::OnQueryNewPalette();
}
