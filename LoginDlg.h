#if !defined(AFX_LOGINDLG_H__5D07DF04_B344_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_LOGINDLG_H__5D07DF04_B344_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LoginDlg.h : header file
//
#include "UC2Ani/PSButton.h"
#include "UC2CS.h"	// EC_CONNINFO
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
class CDIB;
class CDIBPal;
class CPhasedSprite;
class CUC2Socket;

enum CONNECTION_TYPE
{
	GLOBAL_HOST=0, LOCAL_HOST=1, USERDEF_HOST
};

class CLoginDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CLoginDlg(CUC2Socket* pSocket, CWnd* pParent=NULL);   // standard constructor
	virtual ~CLoginDlg();

#ifndef	_MALL
	enum ANI_BEHAVIOR
	{
		ANI_TAP=0, ANI_LOOK, ANI_ROUND
	};
#endif
// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_LOGIN };
	CString	m_strHost;
	CString	m_strNickName;
	CString	m_strPassword;
	CString	m_strMessage;
	CString	m_strSec;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void		PositionControl(const int nCtrlID, const CRect& rcCtrl) const;
	void		UpdateControlBackground(const CRect& rcBack, const bool bDeflate=TRUE);
	void		ShowMessage(const int nIDS);
	void		SetConnType(const int n);

	CToolTipCtrl	m_tooltip;
	CDIB*			m_pDIBBack;		// Background frame image
#ifndef _MALL
	CDIB*			m_pDIBOval;		// Oval image
	CPhasedSprite*	m_pDIBAni;		// Ani Character
	CPhasedSprite*	m_apDIBLM[2];	// LAN or MODEM button image
	CRect			m_rcAni;
	CRect			m_rcLM[2];		// LAN or MODEM
#endif
	CDIBPal*		m_pPal;			// main palette
	CPSButton		m_btnOK;
	CPSButton		m_btnCancel;
	CBrush			m_NullBrush;
	BOOL			m_bFirstFocus;

#ifndef _MALL
// Animation
	void		StopAnimation()
				{ m_bPause = TRUE; m_nCurCell = 0; }
	void		StartAnimation(const int nBeh)
				{ m_bPause = FALSE; m_nBehavior = nBeh; m_nCurCell = 0; }

	int				m_nCurCell;		// for m_pDIBAni
	int				m_nBehavior;	// for m_pDIBAni
	BOOL			m_bPause;		// Pause Animation
#endif
	UINT			m_uiTimer;
	int				m_nElapsedSec;
	DWORD			m_dwLastTick;
	CFont			m_fontMessage;

	CUC2Socket*		m_pSocket;
	EC_CONNINFO		m_ecInfo;
	BOOL			m_bConnecting;
	CWinThread*		m_pConnThread;
	HANDLE			m_hConnThread;
	int				m_nConnType;
	int				m_nTimeOut;

	void	StartCount();
	void	StopCount();
	static UINT ConnectFunction(LPVOID pParam);
	void	WaitForConnectThread();

	// ON_MESSAGE
	LRESULT OnConnectConnecting(WPARAM, LPARAM);
	LRESULT OnConnectLogin(WPARAM, LPARAM);
	LRESULT OnConnectBackupID(WPARAM, LPARAM);
	LRESULT OnConnectFailure(WPARAM, LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetfocusEditNickname();
	afx_msg void OnSetfocusEditPassword();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnUpdateEditNickname();
	afx_msg void OnUpdateEditPassword();
	afx_msg void OnKillfocusEditNickname();
	afx_msg void OnKillfocusEditPassword();
	afx_msg void OnEditupdateCbHost();
	afx_msg void OnKillfocusCbHost();
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__5D07DF04_B344_11D1_80E2_080009B9F339__INCLUDED_)
