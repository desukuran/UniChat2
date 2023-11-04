// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Test.h"

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
	ON_COMMAND_EX(CG_ID_VIEW_TEST, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_TEST, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_HISTORYPANEL, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_HISTORYPANEL, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_CONTROLPANEL, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_CONTROLPANEL, OnUpdateControlBarMenu)
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
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "Control Panel":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_CONTROLPANEL
	//   5. Assign the item a Caption: Control Panel

	// TODO: Change the value of CG_ID_VIEW_CONTROLPANEL to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndControlPanel
		if (!m_wndControlPanel.Create(this, CG_IDD_CONTROLPANEL,
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_CONTROLPANEL))
		{
			TRACE0("Failed to create dialog bar m_wndControlPanel\n");
			return -1;		// fail to create
		}
	}

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "HistoryPanel":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_HISTORYPANEL
	//   5. Assign the item a Caption: HistoryPanel

	// TODO: Change the value of CG_ID_VIEW_HISTORYPANEL to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndHistoryPanel
		if (!m_wndHistoryPanel.Create(this, CG_IDD_HISTORYPANEL,
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_HISTORYPANEL))
		{
			TRACE0("Failed to create dialog bar m_wndHistoryPanel\n");
			return -1;		// fail to create
		}

		m_wndHistoryPanel.EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndHistoryPanel);

	}

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "Test":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_TEST
	//   5. Assign the item a Caption: Test

	// TODO: Change the value of CG_ID_VIEW_TEST to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndTest
		if (!m_wndTest.Create(this, CG_IDD_TEST,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_TEST))
		{
			TRACE0("Failed to create dialog bar m_wndTest\n");
			return -1;		// fail to create
		}

		m_wndTest.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndTest);


		ShowControlBar(&m_wndTest, FALSE, FALSE);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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
