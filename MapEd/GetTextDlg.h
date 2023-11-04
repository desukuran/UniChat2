#if !defined(AFX_GETTEXTDLG_H__C58C7FE4_B59C_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_GETTEXTDLG_H__C58C7FE4_B59C_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetTextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetTextDlg dialog

class CGetTextDlg : public CDialog
{
// Construction
public:
	CString m_strCaption;
	CGetTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetTextDlg)
	enum { IDD = IDD_GETSTRING };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetTextDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETTEXTDLG_H__C58C7FE4_B59C_11D1_80E2_080009B9F339__INCLUDED_)
