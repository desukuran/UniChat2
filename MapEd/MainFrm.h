// MainFrm.h : interface of the CMainFrame class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_MAINFRM_H__7ECC1E0A_9C09_11D1_80E2_288A06C10000__INCLUDED_)
#define AFX_MAINFRM_H__7ECC1E0A_9C09_11D1_80E2_288A06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../FlatToolBar.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	void	SetStatusBarText(const char* msg)	{ m_wndStatusBar.SetWindowText(msg); }
	CPalette* SetPalette(CPalette* pPalette);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar		m_wndStatusBar;
	CFlatToolBar	m_wndToolBar;

// Generated message map functions
protected:
	CSplitterWnd m_wndSplitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	CPalette* m_pPalette;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7ECC1E0A_9C09_11D1_80E2_288A06C10000__INCLUDED_)
