#if !defined(AFX_INPUTPASSWORD_H__A1BFE564_C321_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_INPUTPASSWORD_H__A1BFE564_C321_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InputPassword.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputPassword dialog

class CInputPassword : public CDialog
{
// Construction
public:
	CInputPassword(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputPassword)
	enum { IDD = IDD_INPUT_PASSWORD };
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputPassword)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTPASSWORD_H__A1BFE564_C321_11D1_80E2_080009B9F339__INCLUDED_)
