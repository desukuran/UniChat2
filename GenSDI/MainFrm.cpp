// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GenSDI.h"

#include "MainFrm.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
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
	TRACE("CMainFrame::CMainFrame()\n");
}

CMainFrame::~CMainFrame()
{
	TRACE("CMainFrame::~CMainFrame()\n");
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// CG: This line was added by the Palette Support component
	m_pPalette = NULL;

	TRACE("CMainFrame::OnCreate(LPCREATESTRUCT)\n");
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TRACE("\tm_wndToolBar.Create(%ld);\n", this);
	TRACE("\tm_wndToolBar.LoadToolBar(%d);\n", IDR_MAINFRAME);
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	TRACE("\tm_wndStatusBar.Create(%lx);\n", this);
	TRACE("\tm_wndStatusBar.SetIndicators(...);\n");
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	TRACE("\tm_wndToolBar.SetBarStyle(...);\n");
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	TRACE("\tm_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);\n");
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	TRACE("\tEnableDocking(CBRS_ALIGN_ANY);\n");
	EnableDocking(CBRS_ALIGN_ANY);
	TRACE("\tDockControlBar(&m_wndToolBar);\n");
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE("CMainFrame::PreCreateWindow(CREATESTRUCT& cs)\n");
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	TRACE("\tCFrameWnd::PreCreateWindow(cs);\n");
	BOOL bRes = CFrameWnd::PreCreateWindow(cs);
	return bRes;
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
