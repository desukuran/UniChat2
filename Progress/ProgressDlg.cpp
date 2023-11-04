// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Progress.h"
#include "ProgressDlg.h"
#include "Prog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	m_strDisplay = _T("");
	m_strProgress = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDownload = NULL;
	m_aDI	= NULL;
	m_nDIs	= 0;
}

CProgressDlg::~CProgressDlg()
{
	if (m_pDownload)
		delete m_pDownload;
	if (m_aDI)
		delete [] m_aDI;

//	CoUninitialize();
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESSBAR, m_pbProgress);
	DDX_Text(pDX, IDC_DISPLAY, m_strDisplay);
	DDX_Text(pDX, IDC_PROGRESS, m_strProgress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CMD_BIND_START,			OnBindStart)
	ON_MESSAGE(CMD_BIND_FAILED,			OnBindFailed)
	ON_MESSAGE(CMD_BIND_FILE_OPENED,	OnBindFileOpened)
	ON_MESSAGE(CMD_BIND_FILE_CLOSED,	OnBindFileClosed)
	ON_MESSAGE(CMD_BIND_PROGRESS_MSG,	OnBindProgressMsg)	// SendMessage(CMD_BIND_PROGRESS_MSG, 0, (LPARAM)msg);
	ON_MESSAGE(CMD_BIND_PROGRESS_BAR,	OnBindProgressBar)	// SendMessage(CMD_BIND_PROGRESS_BAR, (WPARAM)ulProgress, (LPARAM)ulProgressMax);
	ON_MESSAGE(CMD_BIND_DOWNLOAD_DONE,	OnBindDownloadDone)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
//	HRESULT hr = CoInitialize(NULL);
//	if (FAILED(hr))
//		return FALSE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
		CDialog::OnSysCommand(nID, lParam);
//	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgressDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProgressDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CProgressDlg::OnOK() 
{
	CString strURL("ftp://88.1.26.2/UniChat/u2files.txt");	// 203.241.132.83
	static WCHAR	szDefaultURL[MAX_PATH];			//	L"http://www.msn.com";
	MultiByteToWideChar(CP_ACP, 0, strURL, -1, szDefaultURL, MAX_PATH);
	if (m_pDownload)
	{
		delete m_pDownload;
	}
	m_pDownload = new CDownload(szDefaultURL);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	char rgchBuf[INTERNET_MAX_PATH_LENGTH];
	WideCharToMultiByte(CP_ACP, 0, m_pDownload->m_url, -1, rgchBuf, MAX_PATH, 0, 0);
	SetWindowText(rgchBuf);

	m_strDisplay = "Status: Initiating Bind...";
	UpdateData(FALSE);
	m_pDownload->DoDownload(GetSafeHwnd(), "test.txt");
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

//	CDialog::OnOK();
}

void CProgressDlg::OnCancel()
{
	if (m_pDownload)
		m_pDownload->CancelDownload();
//	EndDialog(hwndDlg,0);
	CDialog::OnCancel();
}

LRESULT CProgressDlg::OnBindStart(WPARAM, LPARAM)
{
	m_strDisplay = "Status: Preparing download...";	//Starting to bind...";
	UpdateData(FALSE);	// Write
	return 0;
}

LRESULT CProgressDlg::OnBindFailed(WPARAM, LPARAM)
{
	m_strDisplay = "Status: File download Failed.";
	UpdateData(FALSE);	// Write
	return 0;
}

LRESULT CProgressDlg::OnBindFileOpened(WPARAM, LPARAM)
{
	return 0;
}

LRESULT CProgressDlg::OnBindFileClosed(WPARAM, LPARAM)
{
	return 0;
}

LRESULT CProgressDlg::OnBindProgressMsg(WPARAM wParam, LPARAM lParam)
{
	char* szMsg = (char*)lParam;
	if (szMsg && lstrlen(szMsg))
	{
		m_strProgress = szMsg;
		UpdateData(FALSE);	// Write
	}
	return 0;
}

LRESULT CProgressDlg::OnBindProgressBar(WPARAM wParam, LPARAM lParam)
{
	ULONG cProgress		= (ULONG)wParam;
	ULONG maxProgress	= (ULONG)lParam;
	m_pbProgress.SetRange(0, 100);
	m_pbProgress.SetPos(maxProgress ? cProgress * 100 / maxProgress : 0);
	return 0;
}

LRESULT CProgressDlg::OnBindDownloadDone(WPARAM, LPARAM)
{
	m_strDisplay = "Status: File downloaded.";
	UpdateData(FALSE);	// Write
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	return 0;
}
