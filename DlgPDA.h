#if !defined(AFX_DLGPDA_H__A78B1261_47F3_11D2_BCFD_0080C7EADFBB__INCLUDED_)
#define AFX_DLGPDA_H__A78B1261_47F3_11D2_BCFD_0080C7EADFBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPDA.h : header file
//
#include "UC2Ani/PSButton.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPDA dialog
class CDIB;
class CPhasedSprite;

class CDlgPDA : public CDialog
{
// Construction
public:
	CDlgPDA(LPCTSTR strUpper, LPCTSTR strLower, const int nPages, CWnd* pParent=NULL);   // standard constructor
	~CDlgPDA();

	void SetMode(const BOOL bAutoDestroy, const BOOL bAutoPages)
	{
		m_bAutoDestroy = bAutoDestroy;
		m_bAutoPages = bAutoPages;
	}
	void SetPage(const int nPage)		{	m_nCurPage = nPage;	}
	void SetDuration(const UINT uiInt, const DWORD dwD)
		{	m_uiInterval = uiInt;	m_dwDurationTick = dwD;	}

// Dialog Data
	//{{AFX_DATA(CDlgPDA)
	enum { IDD = IDD_DLG_PDA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPDA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	PlayCameraSound();

	CDIB*			m_pDIBBack;		// Background frame image
	CPhasedSprite*	m_apDIBAni[2];	// Ani Upper, Lower
	CPalette*		m_pPal;			// main palette
	BOOL			m_bPaletteCreated;

	CPSButton		m_btnClose;
	CPSButton		m_btnBuy;
	CPSButton		m_btnMore;
	CPSButton		m_btnAuto;
	CPSButton		m_btnLeft;
	CPSButton		m_btnRight;
	CRect			m_arcAni[2];

	int				m_nCurPage;
	UINT			m_uiTimer;
	DWORD			m_dwLastTick;
	DWORD			m_dwStartTick;
	DWORD			m_dwDurationTick;
	UINT			m_uiInterval;

	BOOL			m_bAutoDestroy;
	BOOL			m_bAutoPages;

	CString			m_astrAniFile[2];
//	CPoint			m_aptLT[2];
	int				m_nPages;

	// Generated message map functions
	//{{AFX_MSG(CDlgPDA)
	virtual BOOL OnInitDialog();
	afx_msg void OnPdaBtnAuto();
	afx_msg void OnPdaBtnBuy();
	afx_msg void OnPdaBtnLeft();
	afx_msg void OnPdaBtnMore();
	afx_msg void OnPdaBtnRight();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDA_H__A78B1261_47F3_11D2_BCFD_0080C7EADFBB__INCLUDED_)
