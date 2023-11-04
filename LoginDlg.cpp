// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "LoginDlg.h"
#include "ResMan.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/DIBPal.h"
#include "UC2CS.h"
#include "InputPassword.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

extern int	GetClientVersion();	// UC2Doc.cpp

const int MSPT_TIMER = 400;
#define ArrayCount(a)	(sizeof(a)/sizeof(a[0]))

#ifdef _MALL
LPCTSTR BMP_LOGIN_BACK		= "MLoginBk.bmp";
//LPCTSTR BMP_LOGIN_ANI		= "MLgnAni.bmp";
LPCTSTR BMP_LOGIN_BTN_OK	= "MBtnOK.bmp";
LPCTSTR BMP_LOGIN_BTN_NO	= "MBtnNo.bmp";
//LPCTSTR BMP_LOGIN_BTN_LAN	= "MBtnLAN.bmp";
//LPCTSTR BMP_LOGIN_BTN_MODEM	= "MBtnMdm.bmp";
//const CPoint	PTLT_ANI(85, 98);
//const CPoint	PTLT_LM[2] = {CPoint(276, 219), CPoint(276, 171)};	// LAN or Modem
//const CRect		RECT_NICKNAME(139, 209, 246, 229);
//const CRect		RECT_PASSWORD(139, 232, 246, 251);
const CRect		RECT_NICKNAME(111, 186, 218, 206);
const CRect		RECT_PASSWORD(111, 212, 218, 232);
const CRect		RECT_MESSAGE(50, 239, 243, 259);
const CRect		RECT_SECONDS(306, 145, 374, 165);
const CRect		RECT_HOST(62, 14, 315, 29+100);
//const int BEHAVIOR0[] = {0,0,1,0,0,0,0,1,0,0};
//const int BEHAVIOR1[] = {0,2,3,4,6,3,4,6,3,4,6};
//const int BEHAVIOR2[] = {0,4,7,4,7,4,7};
#else
LPCTSTR BMP_LOGIN_BACK		= "U2Login|LoginBk.bmp";
LPCTSTR BMP_LOGIN_OVAL		= "U2Login|LoginOva.bmp";
LPCTSTR BMP_LOGIN_ANI		= "U2Login|LoginAni.bmp";
LPCTSTR BMP_LOGIN_BTN_OK	= "U2Login|BtnOK.bmp";
LPCTSTR BMP_LOGIN_BTN_NO	= "U2Login|BtnNo.bmp";
LPCTSTR BMP_LOGIN_BTN_LAN	= "U2Login|BtnLAN.bmp";
LPCTSTR BMP_LOGIN_BTN_MODEM	= "U2Login|BtnMODEM.bmp";
const CPoint	PTLT_OVAL(91, 12);
const CPoint	PTLT_ANI(161, 40);
const CPoint	PTLT_LM[2] = {CPoint(120, 207), CPoint(207, 207)};	// LAN or Modem
const CRect		RECT_NICKNAME(158, 159, 264, 180);
const CRect		RECT_PASSWORD(158, 189, 264, 207);
const CRect		RECT_MESSAGE(90, 258, 340, 285);
const CRect		RECT_SECONDS(180, 286, 230, 305);
const CRect		RECT_HOST(105, 7, 325, 22+100);
const int BEHAVIOR0[] = {0,0,1,0,0,0,0,1,0,1,0};
const int BEHAVIOR1[] = {0,2,3,3,3,3,3,2,3};
const int BEHAVIOR2[] = {4,5,6, 7,8,9,10,11, 7,8,9,10,11, 7,8,9,10,11};
const int* ANI_BEH[] = {BEHAVIOR0, BEHAVIOR1, BEHAVIOR2};
const int ANI_BEH_COUNT[] =
{
	ArrayCount(BEHAVIOR0),
	ArrayCount(BEHAVIOR1),
	ArrayCount(BEHAVIOR2)
};
#endif


/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_EN_SETFOCUS(IDC_EDIT_NICKNAME, OnSetfocusEditNickname)
	ON_EN_SETFOCUS(IDC_EDIT_PASSWORD, OnSetfocusEditPassword)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CTLCOLOR()
	ON_EN_UPDATE(IDC_EDIT_NICKNAME, OnUpdateEditNickname)
	ON_EN_UPDATE(IDC_EDIT_PASSWORD, OnUpdateEditPassword)
	ON_EN_KILLFOCUS(IDC_EDIT_NICKNAME, OnKillfocusEditNickname)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD, OnKillfocusEditPassword)
	ON_CBN_EDITUPDATE(IDC_CB_HOST, OnEditupdateCbHost)
	ON_CBN_KILLFOCUS(IDC_CB_HOST, OnKillfocusCbHost)
	ON_WM_PAINT()
//	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CMD_CONNECT_CONNECTING,	OnConnectConnecting)
	ON_MESSAGE(CMD_CONNECT_LOGIN,		OnConnectLogin)
	ON_MESSAGE(CMD_CONNECT_BACKUPID,	OnConnectBackupID)
	ON_MESSAGE(CMD_CONNECT_FAILURE,		OnConnectFailure)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

CLoginDlg::CLoginDlg(CUC2Socket* pSocket, CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strHost = _T("");
	m_strPassword = _T("");
	m_strSec = _T("");
	//}}AFX_DATA_INIT
	m_bConnecting	= FALSE;
	m_uiTimer		= 0;
	m_pConnThread	= NULL;
	m_hConnThread	= NULL;
	m_pSocket		= pSocket;

	ASSERT(m_pSocket);
	m_strMessage.LoadString(IDS_LOGIN_BEGIN);
	m_bFirstFocus	= TRUE;
#ifndef	_MALL
	m_bPause		= TRUE;
#endif
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + BMP_LOGIN_BACK);
	m_pDIBBack = new CDIB;
	if (!m_pDIBBack->Load(strFile))
	{
		delete m_pDIBBack;
		m_pDIBBack = NULL;
		return;
	}

	// Create the palette from the DIB.
	m_pPal = new CDIBPal;
	ASSERT(m_pPal);
	if (!m_pPal->Create(m_pDIBBack))
	{
		AfxMessageBox("Failed to create palette from DIB file");
		delete m_pPal;
		m_pPal = NULL;
	}

#ifndef _MALL
	strFile = strPath + BMP_LOGIN_OVAL;
	m_pDIBOval = new CDIB;
	if (!m_pDIBOval->Load(strFile))
	{
		delete m_pDIBOval;
		m_pDIBOval = NULL;
		return;
	}

	strFile = strPath + BMP_LOGIN_ANI;
	m_pDIBAni = new CPhasedSprite;
	if (!m_pDIBAni->Load(strFile))
	{
		delete m_pDIBAni;
		m_pDIBAni = NULL;
//		return;	// skip
	}
	else
	{
//#ifdef _MALL
//		m_pDIBAni->SetNumCells(1, 8);	// Row, Col
		m_pDIBAni->SetNumCells(3, 4);	// Row, Col
		m_pDIBAni->SetCell(0);
		m_pDIBAni->GetRect(m_rcAni);
		m_rcAni.OffsetRect(PTLT_ANI);
	}
#endif

	strFile = strPath + BMP_LOGIN_BTN_OK;
	m_btnOK.Load(strFile);
	m_btnOK.SetPalette(m_pPal);

	strFile = strPath + BMP_LOGIN_BTN_NO;
	m_btnCancel.Load(strFile);
	m_btnCancel.SetPalette(m_pPal);

#ifndef	_MALL
	for (int i=0; i < 2; i++)
	{
		strFile = (i==0)	? strPath + BMP_LOGIN_BTN_LAN
							: strPath + BMP_LOGIN_BTN_MODEM;
		m_apDIBLM[i] = new CPhasedSprite;
		if (!m_apDIBLM[i]->Load(strFile))
		{
			delete m_apDIBLM[i];
			m_apDIBLM[i] = NULL;
		}
		else
		{
			m_apDIBLM[i]->SetNumCells(3, 1);	// Row, Col
			m_apDIBLM[i]->SetCell(0);
			m_apDIBLM[i]->GetRect(m_rcLM[i]);
			m_rcLM[i].OffsetRect(PTLT_LM[i]);
		}
	}
	m_nCurCell		= 0;
	m_nBehavior		= ANI_TAP;
#endif
	m_uiTimer		= 0;
	m_nElapsedSec	= 0;
	m_dwLastTick	= 0L;

	m_NullBrush.CreateStockObject(NULL_BRUSH);
	m_fontMessage.CreateFont(-12, 0, 0, 0, FW_BOLD,// FW_NORMAL
				FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
				"굴림체");
#else
				"Times New Roman");
#endif
}

CLoginDlg::~CLoginDlg()
{
	if (m_pDIBBack)
		delete m_pDIBBack;
	if (m_pPal)
		delete m_pPal;
#ifndef _MALL
	if (m_pDIBOval)
		delete m_pDIBOval;
	if (m_pDIBAni)
		delete m_pDIBAni;
	for (int i=0; i < 2; i++)
	{
		if (m_apDIBLM[i])
			delete m_apDIBLM[i];
	}
#endif
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_CBString(pDX, IDC_CB_HOST, m_strHost);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, m_strNickName);
	DDV_MaxChars(pDX, m_strNickName, 20);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 12);
	DDX_Text(pDX, IDC_ST_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_ST_SECONDS, m_strSec);
	//}}AFX_DATA_MAP
}

void CLoginDlg::PositionControl(const int nCtrlID, const CRect& rcCtrl) const
{
	CWnd* pW = GetDlgItem(nCtrlID);
	ASSERT(pW);
	pW->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top,
					rcCtrl.Width(), rcCtrl.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CLoginDlg::OnInitDialog() 
{
	if (!m_pDIBBack)
		return FALSE;
	CDialog::OnInitDialog();
	
	m_btnOK.SubclassDlgItem(IDOK, this);
	m_btnCancel.SubclassDlgItem(IDCANCEL, this);

#ifdef _MALL
//	CPoint ptLT(360, 262);
	CPoint ptLT(338, 178);
	m_btnOK.MoveResize(ptLT);
//	ptLT.x = 10;
//	ptLT.y = 265;
	ptLT.x = 266;
	ptLT.y = 231;
	m_btnCancel.MoveResize(ptLT);
#else
	CPoint ptLT(349, 238);
	m_btnOK.MoveResize(ptLT);
	ptLT.x = 17;
	m_btnCancel.MoveResize(ptLT);
#endif
	PositionControl(IDC_EDIT_NICKNAME,	RECT_NICKNAME);
	PositionControl(IDC_EDIT_PASSWORD,	RECT_PASSWORD);
#ifndef _MALL
	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
#endif
	PositionControl(IDC_ST_MESSAGE,		RECT_MESSAGE);
	PositionControl(IDC_ST_SECONDS,		RECT_SECONDS);
	PositionControl(IDC_CB_HOST,		RECT_HOST);

	CWnd* pW = GetDlgItem(IDC_ST_MESSAGE);
	pW->SetFont(&m_fontMessage, FALSE);

	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_CB_HOST);
	pCB->SetItemHeight(-1, 15);
	pCB->ShowWindow(SW_HIDE);
	for (int i=0; i < gResMan.GetNumServerIPs(); i++)
	{
		pCB->InsertString(-1, *gResMan.GetServerIP(i));
	}
	CUC2App* pApp = (CUC2App*)AfxGetApp();
	ASSERT(pApp);
	m_nTimeOut = pApp->RegGetTimeOut();
	if (m_nTimeOut < 10)
		m_nTimeOut = 10;	// must be at least 10 sec.

	SetConnType(pApp->RegGetConnType());
	m_uiTimer = SetTimer(4002, MSPT_TIMER, NULL);
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_NICKNAME),	IDC_EDIT_NICKNAME);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_PASSWORD),	IDC_EDIT_PASSWORD);
//		m_tooltip.AddTool(this,	IDS_CONNECT_LAN,	&m_rcLM[0],	100);
//		m_tooltip.AddTool(this,	IDS_CONNECT_MODEM,	&m_rcLM[1],	101);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}
/*
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CClientDC dc(this);
	// Center this dialog in the screen
	CPoint lt(	(dc.GetDeviceCaps(HORZRES) - rcWnd.Width()) / 2,
				(dc.GetDeviceCaps(VERTRES) - rcWnd.Height()) / 2);
	SetWindowPos(NULL, lt.x, lt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
*/
	CSplashWnd::HideSplashScreen();
#ifndef _MALL
	StartAnimation(ANI_TAP);
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CLoginDlg::OnQueryNewPalette() 
{
	if (m_pPal)
	{
		CDC* pdc = GetDC();
		CPalette* pPalOld = pdc->SelectPalette(m_pPal, FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (pPalOld)
			pdc->SelectPalette(pPalOld, FALSE);
		ReleaseDC(pdc);
//		if (u)
//		{	// Some colors changed so we need to do a repaint.
			Invalidate(); // Repaint the lot.
			return TRUE; // Say we did something.
//		}
	}
	return FALSE; // Say we did nothing.
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

void CLoginDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pDIBBack)
		SetWindowPos(NULL, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC) 
{
	CDialog::OnEraseBkgnd(pDC);	// This should be called here!

	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)	//|| !m_pDIBOval)
	{
		TRACE("CLoginDlg: No DIB!\n");
		return FALSE;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = pDC->SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	m_pDIBBack->Draw(pDC, 0, 0);
#ifndef _MALL
	m_pDIBOval->Draw(pDC, PTLT_OVAL.x, PTLT_OVAL.y);
#endif
/*
	if (m_pDIBAni)
		m_pDIBAni->Draw(pDC, PTLT_ANI);
	if (m_apDIBLM[0])
		m_apDIBLM[0]->Draw(pDC, PTLT_LM[0]);
	if (m_apDIBLM[1])
		m_apDIBLM[1]->Draw(pDC, PTLT_LM[1]);
*/
	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);

	return TRUE;
}

void CLoginDlg::OnPaint()	// will work for InvalidateRect()
{
	CPaintDC dc(this); // device context for painting
	
	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)	// || !m_pDIBOval)
	{
		TRACE("CLoginDlg: No DIB!\n");
		return;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = dc.SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
//	m_pDIBBack->Draw(&dc, 0, 0);
//	m_pDIBOval->Draw(&dc, PTLT_OVAL.x, PTLT_OVAL.y);
#ifndef	_MALL
	if (m_pDIBAni)
		m_pDIBAni->Draw(&dc, PTLT_ANI);
	if (m_apDIBLM[0])
		m_apDIBLM[0]->Draw(&dc, PTLT_LM[0]);
	if (m_apDIBLM[1])
		m_apDIBLM[1]->Draw(&dc, PTLT_LM[1]);
#endif
	// Select old palette if we altered it.
	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
}

void CLoginDlg::OnTimer(UINT nIDEvent) 
{
	if (m_bConnecting)
	{
		int nSec = (::GetTickCount() - m_dwLastTick)/1000;
		if (nSec != m_nElapsedSec)
		{
			m_nElapsedSec = nSec;
			CWnd* pW = GetDlgItem(IDC_ST_SECONDS);
//			pW->ShowWindow(SW_HIDE);
			m_strSec.Format("%3d", m_nElapsedSec);
			UpdateData(FALSE);	// Write
			InvalidateRect(RECT_SECONDS, TRUE);
//			pW->ShowWindow(SW_SHOW);
			if (m_nElapsedSec > m_nTimeOut)
			{
				ShowMessage(IDS_ERROR_TIMEOUT);
				m_pSocket->FDisconnect();
				StopCount();
				WaitForConnectThread();	// Wait until the thread ends
				m_btnOK.EnableWindow(TRUE);
				GetDlgItem(IDCANCEL);
				CWnd* pWnd = GetDlgItem(IDCANCEL);
				pWnd->SetFocus();
			}
		}
	}

	/////////// Animation
#ifndef	_MALL
	if (!m_pDIBAni || (m_nBehavior < 0) || m_bPause)
		return;

	if (++m_nCurCell > ANI_BEH_COUNT[m_nBehavior])
	{
		if (m_bConnecting)
			StartAnimation(ANI_ROUND);
		else
		{
			StartAnimation(ANI_TAP);
//			StopAnimation();
		}
	}
#endif
	
	CClientDC dc(this);
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = dc.SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}

#ifndef	_MALL
	int nCell = ANI_BEH[m_nBehavior][m_nCurCell];
	if (nCell != m_pDIBAni->GetCellID())
	{
		m_pDIBAni->SetCell(nCell);
		m_pDIBAni->Draw(&dc, PTLT_ANI);
	}
#endif
	// Select old palette if we altered it.
	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
	
//	CDialog::OnTimer(nIDEvent);
}

void CLoginDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_uiTimer)
	{
		KillTimer(m_uiTimer);
//		m_uiTimer = 0;
	}
}

BOOL CLoginDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
//	::SetCursor(AfxGetApp()->LoadCursor(IDC_HARROW));
//	return TRUE;
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
#ifndef _MALL
	m_nBehavior++;
	if (m_nBehavior > 2)
		m_nBehavior = 0;
	m_nCurCell = 0;
	if (!m_bConnecting && m_apDIBLM[0] && m_apDIBLM[1])
	{
		if (m_rcLM[0].PtInRect(point))	// LAN
		{
			SetConnType(GLOBAL_HOST);
			ShowMessage(IDS_CONNECTION_TYPE_GLOBAL);
		}
		else if (m_rcLM[1].PtInRect(point))	// MODEM
		{
			SetConnType(LOCAL_HOST);
			ShowMessage(IDS_CONNECTION_TYPE_LOCAL);
		}
	}
#endif
	CDialog::OnLButtonDown(nFlags, point);
}

void CLoginDlg::SetConnType(const int n)
{
	m_nConnType = n;
	if (m_nConnType == USERDEF_HOST)
	{
		CUC2App* pApp = (CUC2App*)AfxGetApp();
		ASSERT(pApp);
		pApp->RegGetServer(m_strHost);
		CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_CB_HOST);
		pCB->ShowWindow(SW_SHOW);
		if (!m_strHost.IsEmpty())
		{
			pCB->InsertString(0, m_strHost);
			pCB->SetCurSel(0);
		}
	}
#ifndef _MALL
	if (m_apDIBLM[0] && m_apDIBLM[1])
	{
		m_apDIBLM[0]->SetCell((n == GLOBAL_HOST) ? 2 : 0);
		m_apDIBLM[1]->SetCell((n == LOCAL_HOST) ? 2 : 0);
		InvalidateRect(m_rcLM[0], FALSE);
		InvalidateRect(m_rcLM[1], FALSE);
	}
#endif
}

void CLoginDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (nFlags & MK_CONTROL)
	{
#ifndef	_MALL
		// Authority Check
		if (m_rcAni.PtInRect(point))
		{
			CInputPassword PasswordDlg;
			PasswordDlg.DoModal();
			if (PasswordDlg.m_strPassword == UC2PASSWORD)
			{
				CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_CB_HOST);
				pCB->ShowWindow(SW_SHOW);
				SetConnType(USERDEF_HOST);
			}
		}
#endif
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CLoginDlg::OnOK() 
{
	m_btnOK.EnableWindow(FALSE);	// Disable OK button to prohibit reentrancy
	UpdateControlBackground(RECT_MESSAGE);
	UpdateData(TRUE);	// Retrieve
	if (m_strNickName.IsEmpty())
	{
//		MsgProgress2("채팅 이름을 입력하세퓖E");
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NICKNAME);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);	// select all
		pEdit->ReplaceSel("chat-name!");
		pEdit->SetSel(0, -1);
		m_btnOK.EnableWindow(TRUE);
		return;
	}
	ShowMessage(IDS_LOGIN_CONNECTING);
#ifndef _MALL
	StartAnimation(ANI_ROUND);
#endif	
	// New Connect
	::ZeroMemory(&m_ecInfo, sizeof(EC_CONNINFO));
	int len;

	CUC2App* pApp = (CUC2App*)AfxGetApp();
	ASSERT(pApp);
	pApp->RegSetConnType(m_nConnType);	// Save current connection type
	if (m_nConnType == USERDEF_HOST)
	{
		len = m_strHost.GetLength();
		m_ecInfo.szServer	= m_strHost.GetBuffer(len);
		pApp->RegSetServer(m_strHost);	// Save server address
	}
	else
	{
		CString* pS = gResMan.GetServerIP(m_nConnType);
		if (pS)
		{
			len = pS->GetLength();
			m_ecInfo.szServer = pS->GetBuffer(len);
		}
		else
		{
			m_ecInfo.szServer = _T("88.1.26.2");
		}
	}
	len = m_strNickName.GetLength();
	m_ecInfo.szNick			= m_strNickName.GetBuffer(len);
	// This should be in memory for ConnectionFunction thread
	static CString strNickBak = m_strNickName + _T("0");
	m_ecInfo.szNickBak		= strNickBak.GetBuffer(len+1);
	static CString strUserName;
	strUserName.Format("%c%d%02d`", UC2_SIGN_CHAR, GetClientVersion() / 100, GetClientVersion() % 100);
//	strUserName += *((CMainFrame*)AfxGetMainWnd())->GetUserID();	// Can't use Korean
	len = strUserName.GetLength();
	m_ecInfo.szUserName		= strUserName.GetBuffer(len+1);
	m_ecInfo.szPass			= NULL;
	m_ecInfo.fAuthenticate	= FALSE;		// use anonymous connection
	ASSERT(m_nTimeOut >= 10);
	m_ecInfo.dwTimeOut		= (DWORD)m_nTimeOut * 1000;	// milliseconds

	HRESULT hr = ::HrVerifyNickA(m_ecInfo.szNick);
	if (FAILED(hr))
	{
		ShowMessage(IDS_INVALID_CHATID);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NICKNAME);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);	// select all
		m_btnOK.EnableWindow(TRUE);
		return;
	}

	StartCount();
//	m_btnCancel.EnableWindow(FALSE);
	WaitForConnectThread();
	m_pConnThread = AfxBeginThread(ConnectFunction, (LPVOID)this);
	ASSERT(m_pConnThread);
	m_hConnThread = m_pConnThread->m_hThread;	// Save the handle for ::WaitSingleObject
	TRACE("CLoginDlg created a thread for ConnectionFunction [%lx]\n",
			m_pConnThread->m_nThreadID);

//	CDialog::OnOK();	// ConnectionFunction will call EndDialog
}

void CLoginDlg::OnCancel() 
{
	ShowMessage(IDS_CANCELED_CONNECTION);

	m_pSocket->FDisconnect();
	StopCount();
	WaitForConnectThread();	// Wait until the thread ends
	
	CDialog::OnCancel();
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
#ifdef _MALL
	if (nCtlColor != CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(PALETTERGB(0, 0, 255));	// yellow 255,255,128;
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)m_NullBrush;
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
#else
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)m_NullBrush;
#endif
}

void CLoginDlg::UpdateControlBackground(const CRect& rcBack, const bool bDeflate)
{
	if (!m_pDIBBack)
		return;
	CRect rc(rcBack);
	if (bDeflate)
		rc.DeflateRect(1, 2);
	InvalidateRect(&rc, TRUE);
}

void CLoginDlg::ShowMessage(const int nIDS)
{
	UpdateData(TRUE);	// Retrieve contents in edit control
	if (nIDS && !m_strMessage.LoadString(nIDS))
		return;
	CWnd* pWnd = GetDlgItem(IDC_ST_MESSAGE);
	pWnd->ShowWindow(SW_HIDE);
	UpdateControlBackground(RECT_MESSAGE, FALSE);	// Don't deflate rectangle
	UpdateData(FALSE);	// Write
	pWnd->ShowWindow(SW_SHOW);
}

void CLoginDlg::OnSetfocusEditNickname()
{
	if (m_bFirstFocus)
	{
		m_bFirstFocus = FALSE;
		return;
	}
	ShowMessage(IDC_EDIT_NICKNAME);
#ifndef _MALL
	StartAnimation(ANI_LOOK);
#endif
}

void CLoginDlg::OnSetfocusEditPassword()
{
	ShowMessage(IDC_EDIT_PASSWORD);
#ifndef	_MALL
	StartAnimation(ANI_LOOK);
#endif
}

void CLoginDlg::OnUpdateEditNickname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
#ifndef	_MALL
	StartAnimation(ANI_LOOK);
#endif
	UpdateControlBackground(RECT_NICKNAME);
}

void CLoginDlg::OnKillfocusEditNickname() 
{
	OnUpdateEditNickname();
}

void CLoginDlg::OnUpdateEditPassword()
{
	UpdateControlBackground(RECT_PASSWORD);
}

void CLoginDlg::OnKillfocusEditPassword() 
{
	OnUpdateEditPassword();
}

void CLoginDlg::OnEditupdateCbHost()
{
	CRect rc(RECT_HOST);
	rc.bottom = rc.top + 22;
	UpdateControlBackground(rc);
}

void CLoginDlg::OnKillfocusCbHost() 
{
	OnEditupdateCbHost();
}

// another thread for connection
// m_pFactory->HrMakeSocket() blocks
UINT CLoginDlg::ConnectFunction(LPVOID pParam)
{
	CLoginDlg* pDlg = (CLoginDlg*)pParam;
	HWND hDlg = pDlg->GetSafeHwnd();
	if (!pDlg->m_pSocket->FConnect(&pDlg->m_ecInfo, hDlg))
	{
		::PostMessage(hDlg, WM_COMMAND, MAKEWPARAM(CMD_CONNECT_FAILURE, 0), 0);
		return FALSE;
	}
	pDlg->EndDialog(IDOK);
	return TRUE;
}

void CLoginDlg::WaitForConnectThread()	// to end
{
	if (!m_hConnThread)
		return;

	TRACE("CLoginDlg - ::WaitForSingleObject(0x%lx, 3000L);\n", m_hConnThread);
	DWORD dwRc = ::WaitForSingleObject(m_hConnThread, 3000L);
	switch (dwRc)
	{
	case WAIT_OBJECT_0:
		TRACE0("Thread: WAIT_OBJECT_0\n");
		break;
	case WAIT_ABANDONED:
		TRACE0("Thread: WAIT_ABANDONED\n");
		break;
	case WAIT_TIMEOUT:
		TRACE0("Thread Hung! Deleting...\n");
		AfxMessageBox("Connecting thread hung!");
//		delete m_pConnThread;
		break;
	case WAIT_FAILED:
		PrintWin32Error("Thread: WAIT_FAILED ");
		break;
	default:
		TRACE0("Thread Hung!\n");
		break;
	}
	m_pConnThread = NULL;	// auto-deleted
	m_hConnThread = NULL;
}

void CLoginDlg::StartCount()
{
	m_dwLastTick	= ::GetTickCount();
	m_nElapsedSec	= -1;
	m_bConnecting	= TRUE;
}

void CLoginDlg::StopCount()
{
	m_bConnecting	= FALSE;
}

//////////////////////////////////////////////////////////////////////////////////
// ChatSock message handler

LRESULT CLoginDlg::OnConnectConnecting(WPARAM wParam, LPARAM lParam)
{
	ShowMessage(IDS_CONNECTING_SERVER);
	return 0;
}

LRESULT CLoginDlg::OnConnectLogin(WPARAM wParam, LPARAM lParam)
{
	ShowMessage(IDS_LOGGING_ON_SERVER);
	return 0;
}

LRESULT CLoginDlg::OnConnectBackupID(WPARAM wParam, LPARAM lParam)
{
	ShowMessage(IDS_TRYING_BACKUP_ID);
	m_ecInfo.szNick	= m_ecInfo.szNickBak;
	return 0;
}
LRESULT CLoginDlg::OnConnectFailure(WPARAM wParam, LPARAM lParam)
{
	ShowMessage(IDS_CONNECTION_FAILED);
	// AfxGetApp()->WinHelp(HID_MYTOPIC);
 	StopCount();
	m_btnOK.EnableWindow(TRUE);
//	m_bmbCancel.EnableWindow(TRUE);
	return 0;
}

UINT CLoginDlg::OnNcHitTest(CPoint point) 
{
    UINT nHitTest = CDialog::OnNcHitTest(point);
#ifndef _MALL
	CPoint pt(point);
	ScreenToClient(&pt);
//	const CRect rcInput(129, 172, 366, 261);
	const CRect rcInput(113, 159, 307, 246);
	if (!rcInput.PtInRect(pt) && !m_rcAni.PtInRect(pt) &&
		(nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
#endif
    return nHitTest;
}
