// PSFrame.h : header file
//
// This file contains the mini-frame that controls modeless 
// property sheet CPSMemberInfo.

#ifndef __PSFRAME_H__
#define __PSFRAME_H__

#include "PSMemberInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPSFrame frame

class CPSFrame : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CPSFrame)
//Construction
public:
	CPSFrame();

// Attributes
public:
	CPSMemberInfo* m_pModelessPropSheet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSFrame)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSFrame();

	// Generated message map functions
	//{{AFX_MSG(CPSFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif	// __PSFRAME_H__
