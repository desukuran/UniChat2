#if !defined(AFX_TARGETDLG_H__C3C37D1B_AD07_11D1_9169_0000F0610C92__INCLUDED_)
#define AFX_TARGETDLG_H__C3C37D1B_AD07_11D1_9169_0000F0610C92__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TargetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTargetDlg dialog

class CTargetDlg : public CDialog
{
// Construction
public:
	CTargetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTargetDlg)
	enum { IDD = IDD_TARGETNAME };
	CEdit	m_ctlTarget;
	CString	m_strTargetFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTargetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTargetDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARGETDLG_H__C3C37D1B_AD07_11D1_9169_0000F0610C92__INCLUDED_)
