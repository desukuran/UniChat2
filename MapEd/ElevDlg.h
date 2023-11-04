#if !defined(AFX_ELEVDLG_H__857FFE42_A782_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_ELEVDLG_H__857FFE42_A782_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ElevDlg.h : header file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

/////////////////////////////////////////////////////////////////////////////
// CElevDlg dialog

class CElevDlg : public CDialog
{
// Construction
public:
	CElevDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElevDlg)
	enum { IDD = IDD_ELEVATION };
	int		m_nElevNew;
	CString	m_strElevCur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElevDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CElevDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEVDLG_H__857FFE42_A782_11D1_80E2_080009B9F339__INCLUDED_)
