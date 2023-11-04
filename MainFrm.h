// MainFrm.h : interface of the CMainFrame class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_MAINFRM_H__A131386D_A610_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_MAINFRM_H__A131386D_A610_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2Panel.h"
#include "UC2History.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CPalette*		GetPalette()		{ return m_pPalette; }
	CUC2Panel*		GetPanel()			{ return &m_wndControlPanel; }
	CUC2History*	GetHistoryPanel()	{ return &m_wndHistoryPanel; }
	CTime			m_tmStart;

// Operations
public:
	CPalette*	SetPalette(CPalette* pPalette);
	void		SetFreeze(const BOOL bFreeze=TRUE);
	void		AdjustFrame(const int nW, const int nH);
	BOOL		InitControlPanel(CPalette* pPal);
	void		ShowHistoryPanel(const BOOL bShow=TRUE);
	BOOL		ShellBrowseURL(LPCTSTR szURL);
	BOOL		Is256Palette() const;
	void		SetAskBeforeClose(const BOOL bABC)	{ m_bAskBeforeClose = bABC; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nDatePaneNo;
	int m_nTimePaneNo;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar	m_wndStatusBar;
//	CToolBar	m_wndToolBar;
	CUC2Panel	m_wndControlPanel;
	CUC2History	m_wndHistoryPanel;

// Generated message map functions
protected:
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	CEdit*		GetEditFocus();
	HWND		GetNotepad();
	void		SendTextToNotepad();

	CPalette*	m_pPalette;
	BOOL		m_bFreeze;
	CRect		m_rcView;
	CRect		m_rcMax;
	BOOL		m_bAskBeforeClose;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditNotepad();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnHelpHomepage();
	//}}AFX_MSG
	// ChatSock
	afx_msg LRESULT OnCsAddChannel(WPARAM, LPARAM);
	afx_msg LRESULT OnCsPrivateMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnCsQueryData(WPARAM, LPARAM);
	afx_msg LRESULT OnCsInvite(WPARAM, LPARAM);
	afx_msg LRESULT OnCsGotMemList(WPARAM, LPARAM);
	afx_msg LRESULT OnCsAddMember(WPARAM, LPARAM);
	afx_msg LRESULT OnCsDelMember(WPARAM, LPARAM);
	afx_msg LRESULT OnCsDelChannel(WPARAM, LPARAM);
	afx_msg LRESULT OnCsModeMember(WPARAM, LPARAM);
	afx_msg LRESULT OnCsModeChannel(WPARAM, LPARAM);
	afx_msg LRESULT OnCsTextA(WPARAM, LPARAM);
	afx_msg LRESULT OnCsData(WPARAM, LPARAM);
	afx_msg LRESULT OnCsWhisperText(WPARAM, LPARAM);
	afx_msg LRESULT OnCsWhisperData(WPARAM, LPARAM);
	afx_msg LRESULT OnCsNewTopic(WPARAM, LPARAM);
	afx_msg LRESULT OnCsNewNick(WPARAM, LPARAM);
	afx_msg LRESULT OnChannelFullRetry(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A131386D_A610_11D1_80E2_080009B9F339__INCLUDED_)
