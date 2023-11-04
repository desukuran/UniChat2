#if !defined(AFX_CLOSEDLG_H__D5010EC7_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_CLOSEDLG_H__D5010EC7_A1F9_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CloseDlg.h : header file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg dialog

class CCloseDlg : public CDialog
{
// Construction
public:
	CCloseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCloseDlg)
	enum { IDD = IDD_CLOSE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCloseDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEDLG_H__D5010EC7_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
