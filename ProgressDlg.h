// ProgressDlg.h : header file
//

#if !defined(AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2Ani/PSButton.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog
class CDownload;

class CDownInfo
{
public:	// CFileStatus
	CString		m_strFile;
	int			m_nType;	// 0: No Extract, 1: Extract
	LONG		m_lSize;	// The logical size of the file in bytes
	CTime		m_mtime;	// The date and time the file was created.
	BOOL		m_bNew;		// Newly downloaded file
};

class CDIB;

class CProgressDlg : public CDialog
{
// Construction
public:
	CProgressDlg(CWnd* pParent = NULL);	// standard constructor
	~CProgressDlg();

	BOOL	RITModified() const		{ return m_bRITModified; }
// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CEdit	m_ecMsg;
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
	void		InitControl(const int nCtrlID, const CRect& rcCtrl);
	void		UpdateControlBackground(const CRect& rcBack);
	void		UpdateDisplay();
	void		UpdateProgress();
	void		DownloadFilesList();
	void		DownloadNewFile();

	CDIB*			m_pDIBBack;		// Background frame image
	CPalette*		m_pPal;			// main palette
	BOOL			m_bPaletteCreated;
	CPSButton		m_btnOK;
	CPSButton		m_btnCancel;
	CBrush			m_NullBrush;
	CFont			m_ftMessage;

	CDownload*	m_pDownload;
	CDownInfo*	m_aDI;
	int			m_nDIs;
	int			m_nCurDI;
	CString		m_strHost;
	CString		m_strDownloadingFile;
	BOOL		m_bFirst;
	BOOL		m_bMOD;		// Message of the Day
	BOOL		m_bRITModified;	// need to reload stage

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
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__C8A475E9_CD64_11D1_80E2_080009B9F339__INCLUDED_)
