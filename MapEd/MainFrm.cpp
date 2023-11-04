// MainFrm.cpp : implementation of the CMainFrame class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"

#include "MainFrm.h"

#include "MapEdView.h"
#include "MapListView.h"
#include "MapEdDoc.h"

#include "CloseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	TRACE0("CMainFrame::CMainFrame()\n");
}

CMainFrame::~CMainFrame()
{
	TRACE0("CMainFrame::~CMainFrame()\n");
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// CG: This line was added by the Palette Support component
	m_pPalette = NULL;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetFlatLookStyle();	// CFlatToolBar

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
/*
    // Create a window without min/max buttons or sizable border 
    cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;

    // Size the window and center it 
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN) - 200; 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN) - 200; 
    cs.y = ((cs.cy + 200) - cs.cy) / 2; 
    cs.x = ((cs.cx + 200) - cs.cx) / 2;
*/
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnQueryNewPalette()
{
	CMapEdDoc* pDoc = (CMapEdDoc*)GetActiveDocument();
	CMapEdView* pMEV = pDoc->GetMapEdView();
	CMapListView* pMLV = pDoc->GetMapListView();
	if (pMEV)
		pMEV->SendMessage(WM_QUERYNEWPALETTE, (WPARAM)0, (LPARAM)0);
	if (pMLV)
		pMLV->SendMessage(WM_QUERYNEWPALETTE, (WPARAM)0, (LPARAM)0);
	// CG: This function was added by the Palette Support component

	if (m_pPalette == NULL)
		return FALSE;
	
	// BLOCK
	{
		CClientDC dc(this);
		CPalette* pOldPalette = dc.SelectPalette(m_pPalette,
			GetCurrentMessage()->message == WM_PALETTECHANGED);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;
	}
	
	Invalidate();
	
	return TRUE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	// CG: This function was added by the Palette Support component
	if (pFocusWnd == this || IsChild(pFocusWnd))
		return;
	
	// Pass this message on to the active view (OSBVeiw-derived)
	CMapEdDoc* pDoc = (CMapEdDoc*)GetActiveDocument();
	CMapEdView* pMEV = pDoc->GetMapEdView();
	CMapListView* pMLV = pDoc->GetMapListView();
	if (pMEV)
		pMEV->SendMessage(WM_PALETTECHANGED,
							(WPARAM)(pFocusWnd->GetSafeHwnd()),
							(LPARAM)0);
	if (pMLV)
		// OnPaletteChanged is not public
		pMLV->SendMessage(WM_PALETTECHANGED,
							(WPARAM)(pFocusWnd->GetSafeHwnd()),
							(LPARAM)0);
	OnQueryNewPalette();
}

CPalette* CMainFrame::SetPalette(CPalette* pPalette)
{
	// CG: This function was added by the Palette Support component

	// Call this function when the palette changes.  It will
	// realize the palette in the foreground to cause the screen
	// to repaint correctly.  All calls to CDC::SelectPalette in
	// painting code should select palettes in the background.

	CPalette* pOldPalette = m_pPalette;
	m_pPalette = pPalette;
	OnQueryNewPalette();
	return pOldPalette;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create static splitters\n");
		return FALSE;    // failed to create
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CMapEdView), CSize(590, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CMapListView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,1));

	return TRUE;
}

void CMainFrame::OnClose() 
{
	CCloseDlg	dlg;
	if (dlg.DoModal() == IDCANCEL)
		return;
	CFrameWnd::OnClose();
}
