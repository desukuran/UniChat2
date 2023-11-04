#if !defined(AFX_MEMBERLISTDLG_H__BCD11B02_C239_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_MEMBERLISTDLG_H__BCD11B02_C239_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemberListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemberListDlg dialog

class CUC2Doc;

class CMemberListDlg : public CDialog
{
// Construction
public:
	CMemberListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMemberListDlg)
	enum { IDD = IDD_DLG_MEMBER };
	CListCtrl	m_lcMember;
	CString	m_strCount;
	CString	m_strMessage;
	//}}AFX_DATA

	enum
	{
		IL_HOST,
		IL_SPEAKER,
		IL_SPECTATOR,
		IL_COUNT
	} MEMBER_IL_INDEX;

	void	SetPPChannel(CUC2Doc* pDoc, const DWORD nID, LPCTSTR szChannelName=NULL)
			{	m_pDoc = pDoc;		m_dwChannelID = nID;
				if (szChannelName)
					m_strChannel = szChannelName; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemberListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		AddItem(const int i, int iImage, PICS_PROPERTY picsProp, TCHAR* psz);
	BOOL	AddMember(PICS_PROPERTY picsProp);
	BOOL	ShowList();
	void	EndOfList();

	CUC2Doc*		m_pDoc;
	DWORD			m_dwChannelID;
	CString			m_strChannel;
	CFont			m_font;
	CImageList		m_ilMember;
//	int				m_iRealName;
	int				m_nIndex;

	// Generated message map functions
	//{{AFX_MSG(CMemberListDlg)
	afx_msg void OnBtnInvite();
	afx_msg void OnBtnRenew();
	afx_msg void OnClickListMember(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteitemListMember(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMember(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnQueryMembers(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryMembersEnd(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryNoMatches(WPARAM, LPARAM);
	afx_msg LRESULT OnQueryGetRealname(WPARAM, LPARAM);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMBERLISTDLG_H__BCD11B02_C239_11D1_80E2_080009B9F339__INCLUDED_)
