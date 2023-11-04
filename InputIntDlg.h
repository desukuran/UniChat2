#if !defined(AFX_INPUTINTDLG_H__E57FAA23_27A2_11D2_80E2_080009B9F339__INCLUDED_)
#define AFX_INPUTINTDLG_H__E57FAA23_27A2_11D2_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InputIntDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputIntDlg dialog

class CInputIntDlg : public CDialog
{
// Construction
public:
	CInputIntDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputIntDlg)
	enum { IDD = IDD_INPUT_INT };
	int		m_nVal;
	//}}AFX_DATA

	void	SetDefaultVal(const int nDV)	{ m_nDefaultVal = nDV; }
	void	SetTitle(const CString& str)	{ m_strTitle = str; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputIntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nDefaultVal;
	CString	m_strTitle;

	// Generated message map functions
	//{{AFX_MSG(CInputIntDlg)
	afx_msg void OnBtnDefault();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTINTDLG_H__E57FAA23_27A2_11D2_80E2_080009B9F339__INCLUDED_)
