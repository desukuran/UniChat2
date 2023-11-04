// PPChannel.h : header file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#ifndef __PPCHANNEL_H__
#define __PPCHANNEL_H__

/////////////////////////////////////////////////////////////////////////////
// CPPChannel dialog

class CPPChannel : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPChannel)

// Construction
public:
	CPPChannel();
	~CPPChannel();

	enum CHANNEL_IL_INDEX
	{
		IL_CHANNEL=0,
		IL_CHANNELPRIV,
		IL_CHANNELMUD,
		IL_COUNT
	};

	int		AddItem(const int i, int iImage, PICS_PROPERTY picsProp, TCHAR* psz);
	BOOL	AddChannel(PICS_PROPERTY picsProp);
	BOOL	ShowList();
	void	EndOfList();
	BOOL	IsMUD() const	{ return m_bMUD; }
	void	GetLastStageID();

	CString m_strPassword;

// Dialog Data
	//{{AFX_DATA(CPPChannel)
	enum { IDD = IDD_PP_CHANNEL };
	CListCtrl	m_lcChannel;
	CString	m_strCount;
	CString	m_strMessage;
	CString	m_strStageID;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPChannel)
	protected:
	virtual BOOL OnApply();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	SetMUDButtonTitle();

	int			m_nIndex;	// Current selection index for ListControl
	int			m_nUsers;	// Total users
	int			m_i;		// item index
	CFont		m_font;
	CImageList	m_ilChannel;
	BOOL		m_bMUD;		// MUD mode

	// Generated message map functions
	//{{AFX_MSG(CPPChannel)
	afx_msg void OnClickListChannel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListChannel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRenew();
	afx_msg void OnBtnMember();
	afx_msg void OnDeleteitemListChannel(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnMud();
	//}}AFX_MSG
	afx_msg LRESULT OnQueryChannels(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryChannelsEnd(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryNoMatches(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryError(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

};
#endif // __PPCHANNEL_H__
