// UC2.cpp : Defines the class behaviors for the application.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "UC2.h"

#include "MainFrm.h"
#include "UC2Doc.h"
#include "UC2View.h"
#include "Splash.h"
#include "Stage.h"
#include "CloseDlg.h"
#include "ResMan.h"	// GetBubbleTextLimit, ...
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#define IDS_ENTER_STAGE_MUSIC           133
#define IDS_ENTER_STAGE_LINK            134
#define IDD_PALETTE                     135
#define IDS_ENTER_TILE_ELEVS            135
static char THIS_FILE[] = __FILE__;
#endif

// LPCTSTR SAIT_TTS		= _T("Software\\Samsung\\TTS\\SAIT_TTS");
LPCTSTR ENT_ROOTDIR		= _T("RootDir");
// Member Info Entries
LPCTSTR ENT_NICK		= _T("Nick");
LPCTSTR ENT_REALNAME	= _T("RealName");
LPCTSTR ENT_PROFILE		= _T("Profile");
LPCTSTR ENT_HYPERLINK	= _T("Hyperlink");
LPCTSTR ENT_SEX			= _T("Sex");
LPCTSTR ENT_AGE			= _T("Age");
LPCTSTR ENT_CHARID		= _T("CharID");
LPCTSTR ENT_BUBBLEKIND	= _T("BubbleKind");
LPCTSTR	ENT_CONNTYPE	= _T("ConnType");
LPCTSTR	ENT_TIMEOUT		= _T("TimeOut");
LPCTSTR	ENT_STAGESEC	= _T("StageSec");
LPCTSTR	ENT_LASTSTAGEID	= _T("LastStageID");
LPCTSTR	ENT_BUBBLELEN	= _T("BubbleLen");
LPCTSTR	ENT_BUBBLETIME	= _T("BubbleTime");
// 
LPCTSTR	ENT_SERVER		= _T("ServerIP");	// Only for user-defined connection type

#ifdef _MALL
const int DEFAULT_STAGE_SEC = 0;
#else
const int DEFAULT_STAGE_SEC = 10;
#endif
extern CResMan gResMan;

/////////////////////////////////////////////////////////////////////////////
// CUC2App

BEGIN_MESSAGE_MAP(CUC2App, CWinApp)
	//{{AFX_MSG_MAP(CUC2App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_DEVELOPERS, OnHelpDevelopers)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUC2App construction

CUC2App::CUC2App()
: m_strVersion(_T("Version 1.0"))
{
	TRACE("CUC2App::CUC2App()\n");
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pStage = NULL;
	m_bPause = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUC2App object

CUC2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CUC2App initialization

BOOL CUC2App::InitInstance()
{
	TRACE0("CUC2App::InitInstance()\n");
	// CG: The following block was inserted by 'Status Bar' component.
	{
		//Set up date and time defaults so they're the same as system defaults
		setlocale(LC_ALL, "");
	}
	// CG: The following block was added by the Splash Screen component.
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}

	DWORD dwVer = ::GetVersion();
	if ((dwVer & 0x800000FF) != 0x080000003)
	{
		// Not on Win32s so try to get the CreateDIBSection procedure address.
		HMODULE hMod = ::GetModuleHandle("gdi32");
		if (!hMod || (hMod && !::GetProcAddress(hMod, "CreateDIBSection")))
		{
			AfxMessageBox(IDS_ERROR_NOT_WIN95);
			return FALSE;
		}
	}
	else
	{
		AfxMessageBox(IDS_ERROR_NOT_WIN95);
		return FALSE;
	}

	// First chance exception in UC2.exe (WCA_32.dll) after installing UniWin98
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	// Call AfxSocketTerm() in CUC2App::ExitInstance()

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Samsung"));
	if (!CreateUniChatKey())
	{
		AfxMessageBox(IDS_ERROR_WRITE_REGISTRY);
		return FALSE;
	}
	GetUniChatRoot(m_strUniChatRoot);
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CUC2Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CUC2View));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
/*
	if (m_lpCmdLine[0] == '-')
	{
		CString strOption(m_lpCmdLine);
		if (strOption.Find(MYPASSWORD) >= 0)	// should be >= 1
		{
			m_bLock = FALSE;
		}
	}
*/
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	TRACE0("CUC2App::InitInstance() - Done.\n");
	return TRUE;
}

// App command to run the dialog
void CUC2App::OnAppAbout()
{
	CCloseDlg dlg;
	dlg.m_strMessage.LoadString(IDS_ABOUT_TEXT);
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CUC2App commands

BOOL CUC2App::OnIdle(LONG lCount)
{
	// CG: The following code inserted by 'Idle Time Processing' component.

	// Note: Do not perform lengthy tasks during OnIdle because your
	// application cannot process user input until OnIdle returns.

	// call the base class
	CWinApp::OnIdle(lCount);

	if (m_bPause)
		return FALSE;

/*	if (lCount == 0)
	{
		// TODO: add code to perform important idle time processing
	}
	else if (lCount == 100)
	{
		// TODO: add code to perform less important tasks during idle
	}
	else if (lCount == 1000)
	{
	}
*/
	// This is the Heart of the Program!
	if (m_pStage)
	{
		m_pStage->TickAll();
		return TRUE;
	}
	// return FALSE when there is no more idle processing to do
	return FALSE;
}

BOOL CUC2App::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}
/*
// returns FALSE if not found
BOOL CUC2App::GetMagicVoicePath(CString& str)
{
//	str = GetProfileString(m_strVersion,	ENT_TTSDB,		"C:\\TTS\\");
//	return TRUE;
//
	BOOL fRet = FALSE;
	HKEY	hkey;
	LONG lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, SAIT_TTS, 0, KEY_READ, &hkey);
	if (lRet != ERROR_SUCCESS)
		return FALSE;
	DWORD	dwType;
	DWORD	cbBuf=1024;	// This was the bug!
	LPTSTR p = str.GetBuffer(cbBuf);
	lRet = ::RegQueryValueEx(hkey, _T("DB Directory"), 0, &dwType, (BYTE*)p, &cbBuf);
	str = p;
	str.ReleaseBuffer();	// Surplus memory released, p is now invalid
	if (lRet == ERROR_SUCCESS)
	{
		fRet = (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
		ASSERT(fRet);
		int len = str.GetLength();
		if (len > 0)
		{
			if (str[len-1] != '\\')
				str += '\\';
		}
	}
	::RegCloseKey(hkey);
	return fRet;
}
*/
BOOL CUC2App::GetUniChatKey(PHKEY phkey, REGSAM samDesired)
{
	LONG lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Samsung\\UniChat"),
								0, samDesired, phkey);
	return (lRet == ERROR_SUCCESS);
}

// Check if we already have a key for UniChat or Create the key
// Create HKEY_CURRENT_USER/Software/Samsung/UniChat Key
// Set Values under this key
//	RootDir = "C:\UNICHAT\"
BOOL CUC2App::CreateUniChatKey()
{
	CString strRoot;
	int	len = 256;
	LPTSTR pszRoot = strRoot.GetBuffer(len);
#ifdef _ROOTCURDIR		// Root is current directory
	::GetCurrentDirectory(len, pszRoot);
	strRoot.ReleaseBuffer();
	strRoot += '\\';
#else					// Root is module directory
	::GetModuleFileName(NULL, pszRoot, len);
	strRoot.ReleaseBuffer();
	int i = strRoot.ReverseFind('\\');
	if (i > 0)
	{
		pszRoot = strRoot.GetBuffer(len);
		pszRoot[i] = NULL;
		strRoot.ReleaseBuffer();
		strRoot += '\\';
	}
	else
	{
		AfxMessageBox(strRoot);
		return FALSE;
	}
#endif
	// Section, Entry, Value
	return WriteProfileString(m_strVersion, ENT_ROOTDIR, strRoot);
}

BOOL CUC2App::GetUniChatRoot(CString& str)
{
	str = GetProfileString(m_strVersion, ENT_ROOTDIR);
	return TRUE;
}

// Update registry values
BOOL CUC2App::RegSetMemberInfo(CMemberInfo& mi)
{
	if (!WriteProfileString(m_strVersion,	ENT_NICK,		*mi.GetNick()))
		return FALSE;
	if (!WriteProfileString(m_strVersion,	ENT_REALNAME,	*mi.GetRealName()))
		return FALSE;
	if (!WriteProfileString(m_strVersion,	ENT_PROFILE,	*mi.GetProfile()))
		return FALSE;
	if (!WriteProfileString(m_strVersion,	ENT_HYPERLINK,	*mi.GetHyperlink()))
		return FALSE;
	if (!WriteProfileInt(m_strVersion,		ENT_SEX,		mi.GetSex()))
		return FALSE;
	if (!WriteProfileInt(m_strVersion,		ENT_AGE,		mi.GetAge()))
		return FALSE;
	if (!WriteProfileInt(m_strVersion,		ENT_CHARID,		mi.GetCharID()))
		return FALSE;
	if (!WriteProfileInt(m_strVersion,		ENT_BUBBLEKIND,	mi.GetBubbleKind()))
		return FALSE;
	return TRUE;
}

BOOL CUC2App::RegGetMemberInfo(CMemberInfo& mi)
{
	mi.SetNick(			GetProfileString(m_strVersion,	ENT_NICK));
	mi.SetRealName(		GetProfileString(m_strVersion,	ENT_REALNAME));
	mi.SetProfile(		GetProfileString(m_strVersion,	ENT_PROFILE));
	mi.SetHyperlink(	GetProfileString(m_strVersion,	ENT_HYPERLINK));
	mi.SetSex(			GetProfileInt(m_strVersion,		ENT_SEX,		0));
	mi.SetAge(			GetProfileInt(m_strVersion,		ENT_AGE,		20));
	mi.SetCharID(		GetProfileInt(m_strVersion,		ENT_CHARID,		0));
	mi.SetBubbleKind(	GetProfileInt(m_strVersion,		ENT_BUBBLEKIND,	0));
	return TRUE;
}

BOOL CUC2App::RegGetNick(CString& strNick)
{
	strNick = GetProfileString(m_strVersion,	ENT_NICK);
	return TRUE;
}

BOOL CUC2App::RegSetNick(const CString& strNick)
{
	return WriteProfileString(m_strVersion,	ENT_NICK,		strNick);
}

BOOL CUC2App::RegGetServer(CString& strServer)
{
	strServer = GetProfileString(m_strVersion,	ENT_SERVER);
	return TRUE;
}

BOOL CUC2App::RegSetServer(const CString& strServer)
{
	return WriteProfileString(m_strVersion,	ENT_SERVER,		strServer);
}

// Connection Type: LAN(0), MODEM(1)
int CUC2App::RegGetConnType()
{
	return GetProfileInt(m_strVersion,	ENT_CONNTYPE,		1);
}

BOOL CUC2App::RegSetConnType(const int nConnType)
{
	return WriteProfileInt(m_strVersion,	ENT_CONNTYPE,	nConnType);
}

// Connection Type: Dial_Up Networking, Dedicated Line
int CUC2App::RegGetTimeOut()
{
	return GetProfileInt(m_strVersion,	ENT_TIMEOUT,		60);
}

int CUC2App::RegGetStageSec()	// delay in a stage
{
	return GetProfileInt(m_strVersion,	ENT_STAGESEC,		DEFAULT_STAGE_SEC);
}

BOOL CUC2App::RegGetUserID(CString& strID)
{
	BOOL fRet = FALSE;
#ifdef _ATT
	HKEY	hkey;
	LONG lRet = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("RemoteAccess\\Profile\\AT&T"),
								0, KEY_READ, &hkey);
	if (lRet != ERROR_SUCCESS)
		return FALSE;
	DWORD	dwType;
	DWORD	cbBuf=1024;
	LPTSTR p = strID.GetBuffer(cbBuf);
	lRet = ::RegQueryValueEx(hkey, _T("User"), 0, &dwType, (BYTE*)p, &cbBuf);
	strID = p;
	strID.ReleaseBuffer();	// Surplus memory released, p is now invalid
	if (lRet == ERROR_SUCCESS)
	{
		fRet = (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
		ASSERT(fRet);
		int i = strID.Find('@');
		if (i > 0)
		{
			p = strID.GetBuffer(cbBuf);
			p[i] = NULL;
			strID.ReleaseBuffer();
		}
	}
	::RegCloseKey(hkey);
#endif	// _ATT
	return fRet;
}

BOOL CUC2App::RegGetLastStageID(CString& strSID)
{
	strSID = GetProfileString(m_strVersion,	ENT_LASTSTAGEID,	NULL);
	return TRUE;
}

BOOL CUC2App::RegSetLastStageID(const CString& strSID)
{
	return WriteProfileString(m_strVersion,	ENT_LASTSTAGEID,	strSID);
}

int CUC2App::RegGetBubbleTextLength()
{
	return GetProfileInt(m_strVersion,	ENT_BUBBLELEN,	gResMan.GetBubbleTextLimit());
}

BOOL CUC2App::RegSetBubbleTextLength(const int nLen)
{
	return WriteProfileInt(m_strVersion,	ENT_BUBBLELEN,	nLen);
}

int CUC2App::RegGetBubbleTime()
{
	return GetProfileInt(m_strVersion,	ENT_BUBBLETIME,	gResMan.GetBubbleTime());
}

BOOL CUC2App::RegSetBubbleTime(const int nMS)
{
	return WriteProfileInt(m_strVersion,	ENT_BUBBLETIME,	nMS);
}

int CUC2App::ExitInstance() 
{
	TRACE("CUC2App::ExitInstance()\n");
	AfxSocketTerm();
/*
	CString strModule("ChatSock.dll");	//ChatSock.dll");
	HMODULE hMod = ::GetModuleHandle(strModule);
	TRACE("GetModuleHandle(%s) returned %lx\n", strModule, hMod);
	if (hMod && ::FreeLibrary(hMod))
		TRACE("::FreeLibrary returned TRUE.\n");
*/
	return CWinApp::ExitInstance();
}

void CUC2App::WinHelp(DWORD dwData, UINT nCmd) 
{
//	CCloseDlg dlg;
//	dlg.m_strMessage.LoadString(IDS_HELP_SIMPLE);
//	dlg.DoModal();
//	CWinApp::WinHelp(dwData, nCmd);	// Block
}

void CUC2App::OnHelpDevelopers() 
{
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + "Developers.htm");
	pMF->ShellBrowseURL(strFile);	//"http://www.samsung.co.kr/");
}
