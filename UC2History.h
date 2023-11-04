//==========================================================
//	(C) Programmed by Kim, Soomin, Mar 18, 1996
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_UC2HISTORY_H__4B176645_BE79_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_UC2HISTORY_H__4B176645_BE79_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UC2History.h : header file
//

//#include "EditHistory.h"

/////////////////////////////////////////////////////////////////////////////
// CUC2History window

class CUC2History : public CDialogBar	// CControlBar - CWnd
{
// Construction
public:
	CUC2History();

// Attributes
public:
//	CEditHistory*	GetEditHistory()
	CEdit*	GetEditHistory()
//				{ return m_bInitialized ? &m_eHistory : NULL; }
		{ return m_bInitialized ? (CEdit*)GetDlgItem(IDC_EDIT_HISTORY) : NULL; }
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUC2History)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUC2History();

	BOOL		Create(CWnd* pParentWnd, UINT nStyle);
	BOOL		InitControls();

	// Generated message map functions
protected:
//	CEditHistory	m_eHistory;
//	CEdit			m_eHistory;
	BOOL			m_bInitialized;

	//{{AFX_MSG(CUC2History)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UC2HISTORY_H__4B176645_BE79_11D1_80E2_080009B9F339__INCLUDED_)
