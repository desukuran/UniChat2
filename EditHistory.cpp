//
//	CEditHistory
//
//	(C) Programmed by Kim, Soomin, Dec 9, 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "UC2.h"
#include "EditHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditHistory

CEditHistory::CEditHistory()
{
}

CEditHistory::~CEditHistory()
{
}


BEGIN_MESSAGE_MAP(CEditHistory, CEdit)	//CRichEditCtrl)
	//{{AFX_MSG_MAP(CEditHistory)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditHistory message handlers

HWND CEditHistory::GetNotepad()
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
		CString strCmd = _T("WRITE ") + strFile;
		BOOL bRes = ::CreateProcess("C:\\WINDOWS\\NOTEPAD.EXE", strCmd.GetBuffer(128), NULL, NULL,
						FALSE, NULL, NULL, NULL, &si, &pi);
		if (!bRes)
			return NULL;
		::CloseHandle(pi.hThread);
		::WaitForInputIdle(pi.hProcess, 10000);
		::CloseHandle(pi.hProcess);
		int nRep=0;
		while (!hwndFind && (nRep++ < 100))
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
void CEditHistory::SendTextToNotepad()
{
	CString strText;
	GetWindowText(strText);
	int len = strText.GetLength();
	TRACE1("CEditHistory::SendTextToNotepad - length:%d\n", len);
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

/*
void CEditHistory::Experiment2()
{
	char	szBuf[2048];
	HWND	hwndFind	= GetNotepad();
	HWND	hwndChild	= ::GetWindow(hwndFind, GW_CHILD);
	HWND	hwnd		= hwndChild;
	UINT	msg			= WM_GETTEXT;
	WPARAM	wParam		= sizeof(szBuf);
	LPARAM	lParam		= (LPARAM)szBuf;
	LRESULT	res			= ::SendMessage(hwnd, msg, wParam, lParam);
	TRACE("::SendMessage(0x%lx, msg, wParam, lParam); returned %lx\n",
						hwnd, msg, wParam, lParam, res);
	CString str = (char*)lParam;
	CRect rc;
	GetClientRect(&rc);
	CClientDC dc(this);
	dc.DrawText(str, &rc, DT_LEFT | DT_TABSTOP);
}
*/
