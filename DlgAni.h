#if !defined(AFX_DLGANI_H__D89C3A46_988E_11D2_89CC_0080C7EADFBB__INCLUDED_)
#define AFX_DLGANI_H__D89C3A46_988E_11D2_89CC_0080C7EADFBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAni.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAni dialog
class CDIB;
class CPhasedSprite;

class CDlgAni : public CDialog
{
// Construction
public:
	CDlgAni(LPCTSTR strBack, LPCTSTR strAni, const int nPages=1, CWnd* pParent=NULL);   // standard constructor
	~CDlgAni();

	void	SetAutoDestroy(const BOOL bAutoDestroy)	{ m_bAutoDestroy = bAutoDestroy; }
	void	SetTimeAttr(const UINT uiElapse, const DWORD dwDT)
	{
		m_uiElapse			= uiElapse;
		m_dwDurationTick	= dwDT;
	}
	void	SetLT(const int nx, const int ny)
	{
		m_ptLTAni = CPoint(nx, ny);
	}
	void	SetRelPosition(const int nX, const int nY)
	{
		m_ptLeftTop = CPoint(nX, nY);
	}

// Dialog Data
	//{{AFX_DATA(CDlgAni)
	enum { IDD = IDD_DLG_ANI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAni)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	ShowNextPage();

	CDIB*			m_pDIBBack;		// Background frame image
	CPhasedSprite*	m_pPSAni;		// Animated Background
	CPalette*		m_pPal;			// main palette
	BOOL			m_bPaletteCreated;

	int				m_nCurPage;
	int				m_nNumPages;

	UINT			m_uiTimer;
	UINT			m_uiElapse;		// ticking period
	DWORD			m_dwLastTick;
	DWORD			m_dwStartTick;
	DWORD			m_dwDurationTick;
	BOOL			m_bAutoDestroy;
	CPoint			m_ptLTAni;
	CPoint			m_ptLeftTop;

	// Generated message map functions
	//{{AFX_MSG(CDlgAni)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGANI_H__D89C3A46_988E_11D2_89CC_0080C7EADFBB__INCLUDED_)
