// PPActor.h : header file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#ifndef __PPACTOR_H__
#define __PPACTOR_H__

/////////////////////////////////////////////////////////////////////////////
// CPPActor dialog

class CPhasedSprite;

class CPPActor : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPActor)

// Construction
public:
	CPPActor();
	~CPPActor();

	int		m_nCharID;
	int		m_nSex;		// 0: Male, 1: Female

// Dialog Data
	//{{AFX_DATA(CPPActor)
	enum { IDD = IDD_PP_ACTOR };
	CComboBox	m_cbSex;
	CListBox	m_lbActors;
	CScrollBar	m_sbActor;
	UINT	m_nAge;
	CString	m_strName;
	CString	m_strProfile;
	CString	m_strHomePage;
	CString	m_strChatID;
	CString	m_strUnitelID;
	CString	m_strVersion;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPActor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void		UpdateActorImage();

	int				m_nCellID;
	CPhasedSprite*	m_pPSActor;
	CRect			m_rcActor;

	// Generated message map functions
	//{{AFX_MSG(CPPActor)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeEditAge();
	afx_msg void OnChangeEditName();
	afx_msg void OnChangeEditProfile();
	afx_msg void OnSelchangeLbActors();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeComboSex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __PPACTOR_H__
