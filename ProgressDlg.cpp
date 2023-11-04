// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "ProgressDlg.h"
#include "Prog.h"
#include "ResMan.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/DIBPal.h"
#include "MainFrm.h"
#include "LoginDlg.h"	// USERDEF_HOST
#include "Parser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CParser gParser;
extern CResMan gResMan;

const CRect	RECT_EDIT(14, 14, 407, 227);
const CRect	RECT_PROGRESS(82, 233, 342, 250);
const CRect	RECT_PROGRESS_BAR(77, 253, 342, 262);
const CRect	RECT_DISPLAY(82, 270, 338, 287);
LPCTSTR URLSERVER		= _T("ftp://");
LPCTSTR U2SERVERPATH	= _T("/UniChat/");
LPCTSTR U2MOD_TXT		= _T("u2mod.txt");		// Message of the Day
#ifdef _KOREAN
LPCTSTR TOKEN_MOD		= _T("MOD");
#else
LPCTSTR TOKEN_MOD		= _T("MODE");
#endif
LPCTSTR TOKEN_FILELIST	= _T("FILELIST");

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
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMF);
	m_NullBrush.CreateStockObject(NULL_BRUSH);
	m_ftMessage.CreateFont(-12, 0, 0, 0, FW_NORMAL,	// FW_BOLD,
				FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
				"¹ÙÅÁÃ¼");
#else
				"Arial");
#endif

	m_pPal = NULL;	// Set it NULL before loading DIB

	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + "U2Login|LoginBk.bmp");
	m_pDIBBack = new CDIB;
	if (!m_pDIBBack->Load(strFile))
	{
		delete m_pDIBBack;
		m_pDIBBack = NULL;
		return;
	}

	if (pMF->Is256Palette())
	{	// Use mainframe's palette to avoid color flickering
		m_pPal = pMF->GetPalette();
		m_pDIBBack->MapColorsToPalette(m_pPal);
		m_bPaletteCreated = FALSE;
	}
	else	// Use original palette in the file for TRUE color system
	{		// Create the palette from the DIB.
		CDIBPal* pDIBPal;
		pDIBPal = new CDIBPal;
		ASSERT(pDIBPal);
		if (!pDIBPal->Create(m_pDIBBack))
		{
			AfxMessageBox("Failed to create palette from DIB file");
			delete pDIBPal;
		}
		m_pPal = pDIBPal;	// type casting to parent class
		m_bPaletteCreated = TRUE;
	}

	strFile = strPath + "U2Login|BtnOK.bmp";
	m_btnOK.Load(strFile);
	m_btnOK.SetPalette(m_pPal);

	strFile = strPath + "U2Login|BtnNo.bmp";
	m_btnCancel.Load(strFile);
	m_btnCancel.SetPalette(m_pPal);

	m_pDownload = NULL;
	m_aDI	= NULL;
	m_nDIs	= 0;

	m_bFirst	= TRUE;
	m_bMOD		= FALSE;
	m_nCurDI	= 0;
	m_strDownloadingFile = strPath + "down.tmp";
	m_bRITModified = FALSE;
}

CProgressDlg::~CProgressDlg()
{
	if (m_pDIBBack)
		delete m_pDIBBack;
	if (m_pPal && m_bPaletteCreated)
		delete m_pPal;

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
	DDX_Control(pDX, IDC_EDIT_MSG, m_ecMsg);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_pbProgress);
	DDX_Text(pDX, IDC_DISPLAY, m_strDisplay);
	DDX_Text(pDX, IDC_PROGRESS, m_strProgress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_NCHITTEST()
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
	TRACE0("CProgressDlg::OnInitDialog()\n");
	if (!m_pDIBBack)
		return FALSE;
	CDialog::OnInitDialog();

	m_btnOK.SubclassDlgItem(IDOK, this);
	m_btnCancel.SubclassDlgItem(IDCANCEL, this);

	CPoint ptLT(349, 238);
	m_btnOK.MoveResize(ptLT);
	ptLT.x = 17;
	m_btnCancel.MoveResize(ptLT);
	
	InitControl(IDC_EDIT_MSG,		RECT_EDIT);
	InitControl(IDC_PROGRESS,		RECT_PROGRESS);
	InitControl(IDC_PROGRESSBAR,	RECT_PROGRESS_BAR);
	InitControl(IDC_DISPLAY,		RECT_DISPLAY);

	CUC2App* pApp = (CUC2App*)AfxGetApp();
	ASSERT(pApp);
	int nConnType = pApp->RegGetConnType();
	if (nConnType == USERDEF_HOST)
	{
		pApp->RegGetServer(m_strHost);
	}
	else
	{
		CString* pS = gResMan.GetServerIP(nConnType);
		m_strHost = pS ? *pS : _T("88.1.26.2");
	}

//	HRESULT hr = CoInitialize(NULL);
//	if (FAILED(hr))
//		return FALSE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProgressDlg::DownloadFilesList()
{
	CString strU2MOD(URLSERVER + m_strHost + U2SERVERPATH + U2MOD_TXT);
	if (m_pDownload)
		delete m_pDownload;
	m_pDownload = new CDownload(strU2MOD);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

//	char rgchBuf[INTERNET_MAX_PATH_LENGTH];
//	WideCharToMultiByte(CP_ACP, 0, m_pDownload->m_url, -1, rgchBuf, MAX_PATH, 0, 0);
//	SetWindowText(rgchBuf);

	m_strDisplay.LoadString(IDS_PROGRESS_INIT_BIND);
	UpdateDisplay();
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + U2MOD_TXT);
	m_bMOD = TRUE;	// Set MOD mode
	m_pDownload->DoDownload(GetSafeHwnd(), strFile);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}

void CProgressDlg::OnOK() 
{
	CDialog::OnOK();
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
	m_strDisplay.LoadString(IDS_PROGRESS_PREPARE);
	UpdateDisplay();
	return 0;
}

LRESULT CProgressDlg::OnBindFailed(WPARAM, LPARAM)
{
	m_strDisplay.LoadString(IDS_PROGRESS_DOWNLOAD_FAIL);
	UpdateDisplay();
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
		UpdateProgress();
	}
	return 0;
}

LRESULT CProgressDlg::OnBindProgressBar(WPARAM wParam, LPARAM lParam)
{
	ULONG cProgress		= (ULONG)wParam;
	ULONG maxProgress	= (ULONG)lParam;
	m_pbProgress.SetRange(0, 100);
//	m_pbProgress.SetPos(maxProgress ? cProgress * 100 / maxProgress : 0);
	if (m_nDIs)
		m_pbProgress.SetPos((m_nCurDI + 1) * 100 / m_nDIs);
	return 0;
}

LRESULT CProgressDlg::OnBindDownloadDone(WPARAM, LPARAM)
{
	m_strDisplay.LoadString(IDS_PROGRESS_DOWNLOADED);
	UpdateDisplay();

	CString strPath(*gResMan.GetResPath());
	CString strFile;

	if (!m_bMOD)	// Normal data files
	{
		if (m_aDI[m_nCurDI].m_bNew)
		{
			strFile = strPath + m_aDI[m_nCurDI].m_strFile;
			CFileStatus	fs;
			if (CFile::GetStatus(m_strDownloadingFile, fs))
			{
				if (fs.m_size == m_aDI[m_nCurDI].m_lSize)
				{
					::CopyFile(m_strDownloadingFile, strFile, FALSE);

					if (CFile::GetStatus(strFile, fs))
					{
						fs.m_mtime = m_aDI[m_nCurDI].m_mtime;
						CFile::SetStatus(strFile, fs);
						if (strFile.Find(".rit") > 0)	// RIT file
							m_bRITModified = TRUE;
					}
					else
					{
						strFile += " not found!";
						AfxMessageBox(strFile);
					}
				}
			}
		}
		m_nCurDI++;
		DownloadNewFile();
		return 0;
	}

	// Message of the Day
	strFile = strPath + U2MOD_TXT;
	m_bMOD = FALSE;
	CTextFileBuffer tfb(gParser.GetMaxBuffer());
	if (!tfb.Load(strFile))
	{
		strFile += ": Load Error!";
		AfxMessageBox(strFile);
		return -1;
	}

	m_nCurDI = 0;
	m_nDIs = 0;
	while (tfb.ReadString()) 
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())	// At first, check if it's a comment line
			continue;
		CString strBuf;
		if (!gParser.SetLeftToken('#') ||
			!gParser.GetValueRightToken(strBuf, '='))
			continue;		// get next line
		if (lstrcmpi(strBuf, "FILELIST") == 0)	// matching!
		{
			while (tfb.ReadString()) 
			{
				gParser.CopyBuffer(tfb.GetString());
				if (gParser.IsCommentLine())		// At first, check if it's a comment line
					continue;
				if (gParser.SetLeftToken('{'))	// Begin
				{
					if (gParser.SetLeftToken('}'))	// {}
						break;
					continue;	// get next line
				}
				if (gParser.SetLeftToken('}'))	// End of contents
					break;	// out of while loop
				if (gParser.SetLeftToken('='))
					m_nDIs++;		// Anyway, we should increase the counter
			}
		}
	}
	tfb.SeekToBegin();

	if (m_nDIs)
		m_aDI = new CDownInfo[m_nDIs];

	int di=0;
	CString strTemp;

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

		//////////////////////////////////////
		if (lstrcmpi(strBuf, TOKEN_FILELIST) == 0)
		{
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
				if (!gParser.GetValueRightToken(strTemp, '='))
					continue;
				strTemp.MakeLower();
				m_aDI[di].m_strFile = strTemp;
				gParser.GetValueRightToken(m_aDI[di].m_nType, ',', ';');
				gParser.GetValueRightToken(m_aDI[di].m_lSize, ',', ';');
				int yy, mm, dd, hh, mn;
				gParser.GetValueRightToken(yy, ',');
				gParser.GetValueRightToken(mm, ',');
				gParser.GetValueRightToken(dd, ',');
				gParser.GetValueRightToken(hh, ',');
				gParser.GetValueRightToken(mn, ',');
				if (di >= m_nDIs)
					break;
				CTime t(yy, mm, dd, hh, mn, 0);
				m_aDI[di++].m_mtime = t;
			}
		}
		else if (lstrcmpi(strBuf, TOKEN_MOD) == 0)	// matching!
		{
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

				strTemp = tfb.GetString();
				strTemp += _T("\r\n");
				int len = m_ecMsg.GetWindowTextLength();
				m_ecMsg.SetSel(len, len);		// starting position, ending position
				m_ecMsg.ReplaceSel(strTemp);
			}
		}
	}
	DownloadNewFile();

#ifdef _DEBUG
	for (int i=0; i < m_nDIs; i++)
	{
		CTime& t = m_aDI[i].m_mtime;
		TRACE("%s=%d,%ld,%d,%d,%d,%d,%d\n",
			m_aDI[i].m_strFile, m_aDI[i].m_nType, m_aDI[i].m_lSize,
			t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	}
#endif
	return 0;
}

void CProgressDlg::DownloadNewFile()
{
	if (m_nCurDI >= m_nDIs)
	{
		m_strDisplay.LoadString(IDS_PROGRESS_ALL_FILES_DONE);
		UpdateDisplay();
		m_pbProgress.SetPos(100);
		CWnd* pW = GetDlgItem(IDOK);
		pW->EnableWindow(TRUE);
		pW->SetFocus();
		return;
	}
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + m_aDI[m_nCurDI].m_strFile);
	CTime& tHost = m_aDI[m_nCurDI].m_mtime;
	CFileStatus	fsLocal;
	BOOL bFound = CFile::GetStatus(strFile, fsLocal);
	// Compare with local files
	if (!bFound || (fsLocal.m_mtime < tHost))
	{
		CString strDFile(URLSERVER + m_strHost + U2SERVERPATH + m_aDI[m_nCurDI].m_strFile);
		if (m_pDownload)
			delete m_pDownload;
		m_pDownload = new CDownload(strDFile);	// Server

		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_strDisplay.LoadString(IDS_PROGRESS_INIT_BIND);
		UpdateDisplay();
		m_pDownload->DoDownload(GetSafeHwnd(), m_strDownloadingFile);	//strFile);	// Local
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		m_aDI[m_nCurDI].m_bNew = TRUE;
	}
	else
	{
		m_aDI[m_nCurDI].m_bNew = FALSE;
		PostMessage(CMD_BIND_DOWNLOAD_DONE, 0, 0);	// to proceed to the next file
	}
}

void CProgressDlg::InitControl(const int nCtrlID, const CRect& rcCtrl)
{
	CWnd* pW = GetDlgItem(nCtrlID);
	ASSERT(pW);
	pW->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top,
					rcCtrl.Width(), rcCtrl.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);
	pW->SetFont(&m_ftMessage, FALSE);	// do not Redraw
}

void CProgressDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CProgressDlg::OnQueryNewPalette() 
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

void CProgressDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pDIBBack)
	{
		SetWindowPos(NULL, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

BOOL CProgressDlg::OnEraseBkgnd(CDC* pDC) 
{
	CDialog::OnEraseBkgnd(pDC);

	if (m_bFirst)
	{
		m_bFirst = FALSE;
		DownloadFilesList();
	}

	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)
	{
		TRACE("CProgressDlg: No DIB!\n");
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
	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
	
	return TRUE;
}

HBRUSH CProgressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)m_NullBrush;
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}

void CProgressDlg::UpdateControlBackground(const CRect& rcBack)
{
	if (!m_pDIBBack)
		return;
	CRect rc(rcBack);
	InvalidateRect(&rc, TRUE);
}

void CProgressDlg::UpdateDisplay()
{
	CWnd* pWnd = GetDlgItem(IDC_DISPLAY);
	pWnd->ShowWindow(SW_HIDE);
	UpdateControlBackground(RECT_DISPLAY);
	UpdateData(FALSE);	// Write
	pWnd->ShowWindow(SW_SHOW);
}

void CProgressDlg::UpdateProgress()
{
	CWnd* pWnd = GetDlgItem(IDC_PROGRESS);
	pWnd->ShowWindow(SW_HIDE);
	UpdateControlBackground(RECT_PROGRESS);
	UpdateData(FALSE);	// Write
	pWnd->ShowWindow(SW_SHOW);
}

UINT CProgressDlg::OnNcHitTest(CPoint point) 
{
    UINT nHitTest = CDialog::OnNcHitTest(point);
	CPoint pt(point);
	ScreenToClient(&pt);
	if (!RECT_EDIT.PtInRect(pt) &&
		(nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;
}
