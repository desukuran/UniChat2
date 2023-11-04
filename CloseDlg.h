#if !defined(AFX_CLOSEDLG_H__11F28E44_B405_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_CLOSEDLG_H__11F28E44_B405_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CloseDlg.h : header file
//
#include "UC2Ani/PSButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg dialog
class CDIB;

class CCloseDlg : public CDialog
{
// Construction
public:
	CCloseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCloseDlg();

// Dialog Data
	//{{AFX_DATA(CCloseDlg)
	enum { IDD = IDD_CLOSE };
	CString	m_strMessage;
	CString	m_strTimeReport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	InitControl(const int nCtrlID, const CRect& rcCtrl);

	CDIB*			m_pDIBBack;		// Background frame image
	CPalette*		m_pPal;			// main palette
	BOOL			m_bPaletteCreated;
#ifndef _MALL
	CPSButton		m_btnOK;
	CPSButton		m_btnCancel;
#endif
	CBrush			m_NullBrush;
	CFont			m_ftMessage;
	int				m_nMsgCur;		// Current Message index

	// Generated message map functions
	//{{AFX_MSG(CCloseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEDLG_H__11F28E44_B405_11D1_80E2_080009B9F339__INCLUDED_)
