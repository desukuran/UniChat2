//==========================================================
//	(C) Programmed by Kim, Soomin, Feb, 1996
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_UC2PANEL_H__CB0995A1_AF81_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_UC2PANEL_H__CB0995A1_AF81_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UC2Panel.h : header file
//
#include "UC2Ani/PhSprite.h"
#include "UC2Ani/PSButton.h"
#include "UC2Ani/DIB.h"
#include "EditSend.h"

/////////////////////////////////////////////////////////////////////////////
// CUC2Panel window

class CUC2Panel : public CDialogBar	// CControlBar - CWnd
{
// Construction
public:
	CUC2Panel();

// Attributes
public:

// Operations
public:
	BOOL		Create(CWnd* pParentWnd, UINT nStyle);
	BOOL		InitControls();
	CEditSend*	GetEditSend()	{ return m_bInitialized ? &m_eSend : NULL; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUC2Panel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUC2Panel();

protected:
	CPalette*	GetPalette();

	CDIB*			m_pDIB;
	CPSButton		m_aButton[6];	// CButton derived
	CEditSend		m_eSend;		// CEdit derived
	BOOL			m_bInitialized;
	// Generated message map functions
protected:
	//{{AFX_MSG(CUC2Panel)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
//	int		OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
//	void	OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UC2PANEL_H__CB0995A1_AF81_11D1_80E2_080009B9F339__INCLUDED_)
