// ProgressDlg.h : header file
//

#if !defined(AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog
class CDownload;

class CDownInfo
{
public:	// CFileStatus
	CString		m_strFile;
	CTime		m_mtime;	// The date and time the file was created.
	LONG		m_size;		// The logical size of the file in bytes
	BOOL		m_bExtract;
};

class CProgressDlg : public CDialog
{
// Construction
public:
	CProgressDlg(CWnd* pParent = NULL);	// standard constructor
	~CProgressDlg();

// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CProgressCtrl	m_pbProgress;
	CString	m_strDisplay;
	CString	m_strProgress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;
	CDownload*	m_pDownload;
	CDownInfo*	m_aDI;
	int			m_nDIs;

	// ON_MESSAGE
	LRESULT OnBindStart(WPARAM, LPARAM);
	LRESULT OnBindFailed(WPARAM, LPARAM);
	LRESULT OnBindFileOpened(WPARAM, LPARAM);
	LRESULT OnBindFileClosed(WPARAM, LPARAM);
	LRESULT OnBindProgressMsg(WPARAM, LPARAM);
	LRESULT OnBindProgressBar(WPARAM, LPARAM);
	LRESULT OnBindDownloadDone(WPARAM, LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_)
