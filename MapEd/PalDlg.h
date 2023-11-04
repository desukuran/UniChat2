#if !defined(AFX_PALDLG_H__E036BF42_A18D_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_PALDLG_H__E036BF42_A18D_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PalDlg.h : header file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

class CDIBPal;
/////////////////////////////////////////////////////////////////////////////
// CPalDlg dialog

class CPalDlg : public CDialog
{
// Construction
public:
	CPalDlg(CWnd* pParent = NULL);   // standard constructor

	void	SetPalette(CDIBPal* pPal)	{ m_pPal = pPal; }

// Dialog Data
	//{{AFX_DATA(CPalDlg)
	enum { IDD = IDD_PALETTE };
	BOOL	m_bShowIndex;
	CString	m_stRGB;
	int		m_sbBlue;
	int		m_sbGreen;
	int		m_sbRed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	ShowRGB(CPoint point);

	CDIBPal*	m_pPal;
	CRect		m_rcPal;
	BOOL		m_bCaptured;

	// Generated message map functions
	//{{AFX_MSG(CPalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheckShowIndex();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALDLG_H__E036BF42_A18D_11D1_80E2_080009B9F339__INCLUDED_)
