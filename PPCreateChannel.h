// PPCreateChannel.h : header file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#ifndef __PPCREATECHANNEL_H__
#define __PPCREATECHANNEL_H__

/////////////////////////////////////////////////////////////////////////////
// CPPCreateChannel dialog

class CPPCreateChannel : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPCreateChannel)

// Construction
public:
	CPPCreateChannel();
	~CPPCreateChannel();

	BOOL		IsPublic() const		{ return m_bPublic; }
	CString*	GetStageName()			{ return &m_strStageName; }

// Dialog Data
	//{{AFX_DATA(CPPCreateChannel)
	enum { IDD = IDD_PP_CREATE_CHANNEL };
	CListBox	m_lbBackground;
	CString	m_strPassword;
	CString	m_strTopic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPCreateChannel)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL		m_bPublic;
	CString		m_strStageName;	// resource name [p2/0000abcd]

	// Generated message map functions
	//{{AFX_MSG(CPPCreateChannel)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRadioPrivate();
	afx_msg void OnRadioPublic();
	afx_msg void OnSelchangeLbBackground();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // __PPCREATECHANNEL_H__
