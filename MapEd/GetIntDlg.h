#if !defined(AFX_GETINTDLG_H__4F156CC2_AA1E_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_GETINTDLG_H__4F156CC2_AA1E_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetIntDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetIntDlg dialog

class CGetIntDlg : public CDialog
{
// Construction
public:
	CString m_strCaption;
	CGetIntDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetIntDlg)
	enum { IDD = IDD_GETINT };
	int		m_nNew;
	CString	m_strCur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetIntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetIntDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETINTDLG_H__4F156CC2_AA1E_11D1_80E2_080009B9F339__INCLUDED_)
