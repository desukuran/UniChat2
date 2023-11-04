// MainFrm.cpp : implementation of the CMainFrame class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "UC2.h"

#include "MainFrm.h"
#include "Splash.h"
#include "CloseDlg.h"
#include "UC2Doc.h"
//#include "ResMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CResMan gResMan;

// Menu/View/Status Bar:	ID_VIEW_STATUS_BAR
// Menu/View/Control Panel:	CG_ID_VIEW_CONTROLPANEL
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
	ON_COMMAND_EX(CG_ID_VIEW_HISTORYPANEL, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_HISTORYPANEL, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_CONTROLPANEL, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_CONTROLPANEL, OnUpdateControlBarMenu)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_NOTEPAD, OnEditNotepad)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_HELP_HOMEPAGE, OnHelpHomepage)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	// User-Defined Messages
	ON_MESSAGE(CSMSG_CMD_ADDCHANNEL,	OnCsAddChannel)
	ON_MESSAGE(CSMSG_CMD_PRIVATEMSG,	OnCsPrivateMsg)
	ON_MESSAGE(CSMSG_CMD_QUERYDATA,		OnCsQueryData)
	ON_MESSAGE(CSMSG_CMD_INVITE,		OnCsInvite)
	ON_MESSAGE(CSMSG_CMD_GOTMEMLIST,	OnCsGotMemList)
	ON_MESSAGE(CSMSG_CMD_ADDMEMBER,		OnCsAddMember)
	ON_MESSAGE(CSMSG_CMD_DELMEMBER,		OnCsDelMember)
	ON_MESSAGE(CSMSG_CMD_DELCHANNEL,	OnCsDelChannel)
	ON_MESSAGE(CSMSG_CMD_MODEMEMBER,	OnCsModeMember)
	ON_MESSAGE(CSMSG_CMD_MODECHANNEL,	OnCsModeChannel)
	ON_MESSAGE(CSMSG_CMD_TEXT_A,		OnCsTextA)
	ON_MESSAGE(CSMSG_CMD_DATA,			OnCsData)
	ON_MESSAGE(CSMSG_CMD_WHISPERTEXT_A,	OnCsWhisperText)
	ON_MESSAGE(CSMSG_CMD_WHISPERDATA,	OnCsWhisperData)
	ON_MESSAGE(CSMSG_CMD_NEWTOPIC,		OnCsNewTopic)
	ON_MESSAGE(CSMSG_CMD_NEWNICK,		OnCsNewNick)
	ON_MESSAGE(CMD_CHANNELFULL_RETRY,	OnChannelFullRetry)
#ifdef _UNITEL
	ON_MESSAGE(WM_COMMREAD,	OnCommRead)
	ON_MESSAGE(UM_EXIT,		OnUmExit)
//	ON_MESSAGE(UM_DOWNLOAD,	OnUmDownLoad)
#endif	// _UNITEL
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
	m_tmStart	= CTime::GetCurrentTime();
	m_pPalette	= NULL;
	m_bFreeze	= FALSE;
	m_bAskBeforeClose	= TRUE;
}

CMainFrame::~CMainFrame()
{
	TRACE("CMainFrame::~CMainFrame()\n");
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TRACE("CMainFrame::OnCreate()\n");
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
/*
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
*/
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "ControlPanel":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_CONTROLPANEL
	//   5. Assign the item a Caption: ControlPanel

	// TODO: Change the value of CG_ID_VIEW_CONTROLPANEL to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndControlPanel
		if (!m_wndControlPanel.Create(this,
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE))
		{
			TRACE0("Failed to create dialog bar m_wndControlPanel\n");
			return -1;		// fail to create
		}
#ifdef DOCKING
		m_wndControlPanel.EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndControlPanel);
#endif
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
		if (!m_wndHistoryPanel.Create(this,
			CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE))
		{
			TRACE0("Failed to create dialog bar m_wndHistoryPanel\n");
			return -1;		// fail to create
		}

		m_wndHistoryPanel.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndHistoryPanel);
		CString strTitle;
		if (strTitle.LoadString(IDS_HISTORY_PANEL))
			m_wndHistoryPanel.SetWindowText(strTitle);

		ShowControlBar(&m_wndHistoryPanel, FALSE, FALSE);
	}

	// CG: The following line was added by the Splash Screen component.
	TRACE("CSplashWnd::ShowSplashScreen()\n");
	CSplashWnd::ShowSplashScreen(this);
	TRACE("CMainFrame::OnCreate() - done\n");

	// CG: The following block was inserted by 'Status Bar' component.
	{
		// Find out the size of the static variable 'indicators' defined
		// by AppWizard and copy it
		int nOrigSize = sizeof(indicators) / sizeof(UINT);

		UINT* pIndicators = new UINT[nOrigSize + 2];
		memcpy(pIndicators, indicators, sizeof(indicators));

		// Call the Status Bar Component's status bar creation function
		if (!InitStatusBar(pIndicators, nOrigSize, 60))
		{
			TRACE0("Failed to initialize Status Bar\n");
			return -1;
		}
		delete[] pIndicators;
	}

	return 0;
}

void CMainFrame::ShowHistoryPanel(const BOOL bShow)
{
	ShowControlBar(&m_wndHistoryPanel, bShow, FALSE);
}

void CMainFrame::AdjustFrame(const int nW, const int nH)
{
	SetFreeze(FALSE);
	CClientDC dc(this);
	int nWidth = min(dc.GetDeviceCaps(HORZRES) - 40, nW);
	int nHeight = min(dc.GetDeviceCaps(VERTRES) - 40, nH);
	if (((nW + 40) >= dc.GetDeviceCaps(HORZRES)) ||
		((nH + 40) >= dc.GetDeviceCaps(VERTRES)))
		SetWindowPos(&wndTopMost, 0, 0, nWidth, nHeight, SWP_NOZORDER);
	else
		SetWindowPos(&wndTopMost, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
	RecalcLayout();
	CScrollView* pView = (CScrollView*)GetActiveView();
	pView->ResizeParentToFit(FALSE);	// Try shrinking first
	pView->ResizeParentToFit(TRUE);	// Let's be daring
	SetFreeze();
}

// You can call this method in CXXView::OnInitialUpdate
BOOL CMainFrame::InitControlPanel(CPalette* pPal)
{
	TRACE0("CMainFrame::InitControlPanel()\n");
	SetPalette(pPal);
	if (!m_wndControlPanel.InitControls())
		return FALSE;
	if (!m_wndHistoryPanel.InitControls())
		return FALSE;
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE0("CMainFrame::PreCreateWindow()\n");
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 640;
	cs.cy = 480;

#ifdef DEMO
	if (cs.hMenu)
	{
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}
#endif
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
	CView* pview = GetActiveView();
	if (pview)
		pview->SendMessage(WM_QUERYNEWPALETTE, (WPARAM)0, (LPARAM)0);

	if (m_wndControlPanel.GetSafeHwnd())
		m_wndControlPanel.SendMessage(WM_QUERYNEWPALETTE, (WPARAM)0, (LPARAM)0);

	return CFrameWnd::OnQueryNewPalette();
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	// CG: This function was added by the Palette Support component
	if (pFocusWnd == this || IsChild(pFocusWnd))
		return;

//	OnQueryNewPalette();

	// Pass this message on to the active view (OSBVeiw-derived)
	CView* pview = GetActiveView();
	if (pview)	// OnPaletteChanged is not public, so I'll send a message
		pview->SendMessage(WM_PALETTECHANGED,
							(WPARAM)(pFocusWnd->GetSafeHwnd()),
							(LPARAM)0);
	if (m_wndControlPanel.GetSafeHwnd())
		m_wndControlPanel.SendMessage(WM_PALETTECHANGED, (WPARAM)(pFocusWnd->GetSafeHwnd()), (LPARAM)0);
	CFrameWnd::OnPaletteChanged(pFocusWnd);
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

void CMainFrame::OnClose() 
{
	TRACE0("CMainFrame::OnClose()\n");
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	ASSERT(pDoc);
	if (pDoc->IsDemo())
	{
		pDoc->EndDemo();
		return;
	}
	if (m_bAskBeforeClose)
	{
		CCloseDlg dlg;
		dlg.m_strMessage.LoadString(IDS_CLOSE_TEXT);
		if (dlg.DoModal() != IDOK)
			return;
	}
	CFrameWnd::OnClose();
}

void CMainFrame::OnDestroy() 
{
	TRACE0("CMainFrame::OnDestroy()\n");
	CFrameWnd::OnDestroy();
}

void CMainFrame::SetFreeze(const BOOL bFreeze)
{
	m_bFreeze = bFreeze;
	if (m_bFreeze)
		GetWindowRect(&m_rcMax);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	TRACE0("OnGetMinMaxInfo ");
	if (m_bFreeze)
	{
		CRect rc;
		GetWindowRect(&rc);
		TRACE("(%d,%d)(%d,%d)\n", rc.left, rc.top, m_rcMax.Width(), m_rcMax.Height());
		lpMMI->ptMaxSize.x = m_rcMax.Width();
		lpMMI->ptMaxSize.y = m_rcMax.Height();
		lpMMI->ptMaxPosition.x = rc.left;
		lpMMI->ptMaxPosition.y = rc.top;
		lpMMI->ptMinTrackSize.x = 0;
		lpMMI->ptMinTrackSize.y = 0;
		lpMMI->ptMaxTrackSize.x = m_rcMax.Width();
		lpMMI->ptMaxTrackSize.y = m_rcMax.Height();
	}
	TRACE0("\n");
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

// If the mainframe is maximized, disable the Freeze menu option because
// there is no point in making the window non-resizable because a maximized
// window cannot be resized anyway.
void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
#ifdef _DEBUG
	TCHAR* szType = "";
	switch(nType)
	{
	case SIZE_MAXIMIZED:	szType = "SIZE_MAXIMIZED";	break;
	case SIZE_MINIMIZED:	szType = "SIZE_MINIMIZED";	break;
	case SIZE_RESTORED:		szType = "SIZE_RESTORED";	break;
	case SIZE_MAXHIDE:		szType = "SIZE_MAXHIDE";	break;
	case SIZE_MAXSHOW:		szType = "SIZE_MAXSHOW";	break;
	}
	TRACE("CMainFrame::OnSize(%s,%d,%d)\n", szType, cx, cy);
#endif

//	CMenu* pMenu = GetMenu();
//	if (nType == SIZE_MAXIMIZED)
//		pMenu->EnableMenuItem(ID_VIEW_FREEZE, MF_DISABLED | MF_GRAYED);
//	else
//		pMenu->EnableMenuItem(ID_VIEW_FREEZE, MF_ENABLED);
//	DrawMenuBar();
}

////////////////////////////////////////////////////////////////////
// Edit

HWND CMainFrame::GetNotepad()
{
	HWND	hwndFind	= ::FindWindow("Notepad", NULL);	// "Tortoise's Experiment"
	CTime time = CTime::GetCurrentTime();
	CString strFile(time.Format(_T("UC%y%m%d.txt")));
	if (!hwndFind)
	{
		STARTUPINFO			si;
		PROCESS_INFORMATION	pi;
		::ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
//		int len = strFile.GetLength();
//		char* szFile = strFile.GetBuffer(len);
//		HINSTANCE hRes = ::ShellExecute(GetSafeHwnd(), "open", szFile, NULL, NULL, SW_SHOWNORMAL);
//		TRACE("::ShellExecute(%xh) returned %ld\n", hRes);
//		if (hRes <= (HINSTANCE)32)
//		{
//			CString strError;
//			strError.LoadString(IDS_ERROR_BROWSER);
//			strError += szFile;
//			AfxMessageBox(strError);
//			return NULL;
//		}

		CString strCmd = _T("WRITE ") + strFile;
		BOOL bRes = ::CreateProcess("C:\\WINDOWS\\NOTEPAD.EXE", strCmd.GetBuffer(128), NULL, NULL,
						FALSE, NULL, NULL, NULL, &si, &pi);
		if (!bRes)
			return NULL;
		::CloseHandle(pi.hThread);
		::WaitForInputIdle(pi.hProcess, 10000);
		::CloseHandle(pi.hProcess);
		int nRep=0;
		while (!hwndFind && (nRep++ < 20))
		{
			::Sleep(1000);
			TRACE("z");
			hwndFind	= ::FindWindow("Notepad", NULL);	// "Tortoise's Experiment"
		}
	}
//	::SendMessage(hwndFind, WM_SETTEXT, 0, (LPARAM)(LPCSTR)strFile);
	return hwndFind;
}

// 1. Find a running Notepad (or initiate a new Notepad) application.
// 2. Set the contents in the notepad (Edit control) with some texts.
void CMainFrame::SendTextToNotepad()
{
	CEdit* pE = m_wndHistoryPanel.GetEditHistory();
	if (!pE)
		return;
	CString strText;
	pE->GetWindowText(strText);
	int len = strText.GetLength();
	TRACE1("SendTextToNotepad - length:%d\n", len);
	if (len == 0)
		return;
	LPCSTR szText = strText;
	HWND	hwndFind	= GetNotepad();
	HWND	hwndChild	= ::GetWindow(hwndFind, GW_CHILD);
	HWND	hwnd		= hwndChild;
	UINT	msg			= WM_SETTEXT;
	WPARAM	wParam		= 0;
	LPARAM	lParam		= (LPARAM)szText;
	LRESULT	res			= ::SendMessage(hwnd, msg, wParam, lParam);
	TRACE("::SendMessage(0x%lx, msg, wParam, lParam); returned %lx\n",
						hwnd, msg, wParam, lParam, res);
}

void CMainFrame::OnEditCopy() 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
		pEdit->Copy();
}

void CMainFrame::OnEditCut() 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
		pEdit->Cut();
}

void CMainFrame::OnEditNotepad() 
{
//	CEditHistory* pEH = m_wndHistoryPanel.GetEditHistory();
//	if (pEH)
//		pEH->SendTextToNotepad();
	SendTextToNotepad();
}

void CMainFrame::OnEditPaste() 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
		pEdit->Paste();
}

void CMainFrame::OnEditUndo() 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
		pEdit->Undo();
}

void CMainFrame::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
	{
		int n1, n2;
		pEdit->GetSel(n1, n2);
		pCmdUI->Enable(n1 != n2);	// IsTextSelected
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	CEdit* pEdit = GetEditFocus();
	if (pEdit)
	{
		int n1, n2;
		pEdit->GetSel(n1, n2);
		pCmdUI->Enable(n1 != n2);	// IsTextSelected
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_TEXT));
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CEdit* pEdit = GetEditFocus();
	pCmdUI->Enable(pEdit ? pEdit->CanUndo() : FALSE);
}

// Get current (focused) edit control
CEdit* CMainFrame::GetEditFocus()
{
	CWnd* pFocus = GetFocus();
	CEdit* pEditSend	= m_wndControlPanel.GetEditSend();
	CEdit* pEditHistory	= m_wndHistoryPanel.GetEditHistory();
	if (pEditSend == pFocus)
		return pEditSend;
	if (pEditHistory == pFocus)
		return pEditHistory;
	return NULL;
}

BOOL CMainFrame::ShellBrowseURL(LPCTSTR szURL)
{
	TRACE("Browsing %s\n", szURL); 
	HINSTANCE hRes = ::ShellExecute(GetSafeHwnd(), "open", szURL, NULL, NULL, SW_SHOWNORMAL);
	TRACE("::ShellExecute(%xh) returned %ld\n", hRes);
	if (hRes <= (HINSTANCE)32)
	{
		CString strError;
		strError.LoadString(IDS_ERROR_BROWSER);
		strError += szURL;
		AfxMessageBox(strError);
		return FALSE;
	}
	return TRUE;
}

/*
BOOL CMainFrame::LaunchBrowser(LPCTSTR szURL)
{
	HKEY	hKey;
	CString	strBuf;
	LONG	cbSize = 255;
	if (::RegOpenKey(HKEY_LOCAL_MACHINE,
		"Software\\Classes\\http\\shell\\open", &hKey))
	{
		TRACE("ERROR Open Registry\n");
		return FALSE;
	}
// "C:\PROGRA~1\PLUS!\MICROS~1\iexplore.exe" -nohome
	::RegQueryValue(hKey, "Command", strBuf.GetBuffer(cbSize), &cbSize);   
	::RegCloseKey(hKey);
	strBuf.ReleaseBuffer();
	
	CString strExec;
	CString strURL(szURL);
	int nTot = strBuf.GetLength();
	int sep	= strBuf.ReverseFind(' ');
	int nRead = nTot - sep;
	strExec = strBuf.Left(nTot-nRead) + " " + strURL;
	TRACE("::WinExec(%s)\n", strExec);
	::WinExec(strExec, SW_SHOWNORMAL);

	return TRUE;
}
*/

void CMainFrame::OnHelpHomepage() 
{
	CString strURL;
	if (strURL.LoadString(IDS_UNICHAT_HOMEURL))
		ShellBrowseURL(strURL);
}

BOOL CMainFrame::Is256Palette() const
{
	BOOL bResult=TRUE;
	// Get a screen DC to work with.
	HWND hwndActive = ::GetActiveWindow();
	HDC hdcScreen = ::GetDC(hwndActive);
	ASSERT(hdcScreen);

	// Make sure we are on a palettized device.
	if (!(::GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE))
	{
		bResult = FALSE;
	}
	else
	{
		// Get the number of system colors and the number of palette
		// entries. Note that on a palletized device the number of
		// colors is the number of guaranteed colors, i.e., the number
		// of reserved system colors.
		int iSysColors = ::GetDeviceCaps(hdcScreen, NUMCOLORS);
		int iPalEntries = ::GetDeviceCaps(hdcScreen, SIZEPALETTE);

		// If there are more than 256 colors we are wasting our time.
		if (iSysColors < 0 || iSysColors > 256)
		{
			bResult = FALSE;
		}
	}
	::ReleaseDC(hwndActive, hdcScreen);
	return bResult;
}

/////////////////////////////////////////////////////////////////////////
// ChatSock Message Handler
LRESULT CMainFrame::OnCsAddChannel(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsAddChannel(wParam, lParam);
}

LRESULT CMainFrame::OnCsPrivateMsg(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsPrivateMsg(wParam, lParam);
}

LRESULT CMainFrame::OnCsQueryData(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsQueryData(wParam, lParam);
}

LRESULT CMainFrame::OnCsInvite(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsInvite(wParam, lParam);
}

LRESULT CMainFrame::OnCsGotMemList(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsGotMemList(wParam, lParam);
}

LRESULT CMainFrame::OnCsAddMember(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsAddMember(wParam, lParam);
}

LRESULT CMainFrame::OnCsDelMember(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsDelMember(wParam, lParam);
}

LRESULT CMainFrame::OnCsDelChannel(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsDelChannel(wParam, lParam);
}

LRESULT CMainFrame::OnCsModeMember(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsModeMember(wParam, lParam);
}

LRESULT CMainFrame::OnCsModeChannel(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsModeChannel(wParam, lParam);
}

LRESULT CMainFrame::OnCsTextA(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsTextA(wParam, lParam);
}

LRESULT CMainFrame::OnCsData(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsData(wParam, lParam);
}

LRESULT CMainFrame::OnCsWhisperText(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsWhisperText(wParam, lParam);
}

LRESULT CMainFrame::OnCsWhisperData(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsWhisperData(wParam, lParam);
}

LRESULT CMainFrame::OnCsNewTopic(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsNewTopic(wParam, lParam);
}

LRESULT CMainFrame::OnCsNewNick(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnCsNewNick(wParam, lParam);
}

LRESULT CMainFrame::OnChannelFullRetry(WPARAM wParam, LPARAM lParam)
{
	CUC2Doc* pDoc = (CUC2Doc*)GetActiveDocument();
	return pDoc->OnChannelFullRetry(wParam, lParam);
}

void CMainFrame::OnUpdateDate(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strDate = time.Format(_T("%x"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strDate);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current date
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nDatePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nDatePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strDate);
	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%X"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strTime);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current time
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nTimePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nTimePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strTime);
	pCmdUI->Enable(TRUE);
}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Create an index for the DATE pane
	m_nDatePaneNo = nSize++;
	pIndicators[m_nDatePaneNo] = ID_INDICATOR_DATE;
	// Create an index for the TIME pane
	m_nTimePaneNo = nSize++;
	nSeconds = 1;
	pIndicators[m_nTimePaneNo] = ID_INDICATOR_TIME;

	// TODO: Select an appropriate time interval for updating
	// the status bar when idling.
	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);
}
