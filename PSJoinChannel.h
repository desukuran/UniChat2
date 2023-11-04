// PSJoinChannel.h : header file
//
// This class defines custom modal property sheet 
// CPSJoinChannel.
 
#ifndef __PSJOINCHANNEL_H__
#define __PSJOINCHANNEL_H__

#ifdef _MALL
#include "PPShoppingCart.h"
#include "PPPaymentInfo.h"
#endif
#include "PPCreateChannel.h"
#include "PPChannel.h"
#include "PPActor.h"
#include "UC2CS.h"	// EC_CHANNELINFO
#include "UC2Doc.h"	// GetSocket()

/////////////////////////////////////////////////////////////////////////////
// CPSJoinChannel

class CDIB;
class CMemberInfo;
class CUC2Socket;

enum PAGE_SELECT
{
	PS_ACTOR_PAGE	= 0x0001,
	PS_JOIN_PAGE	= 0x0002,
	PS_CREATE_PAGE	= 0x0004,
	PS_ALL_PAGES	= PS_ACTOR_PAGE | PS_JOIN_PAGE | PS_CREATE_PAGE
};

class CPSJoinChannel : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSJoinChannel)

// Construction
public:
	CPSJoinChannel(CUC2Doc* pDoc, const int nPageSelect, LPCTSTR pszCaption, UINT iSelectPage=0);

// Attributes
public:
	CDIB*		GetDIBBack()	{ return m_pDIBBack; }
	CPalette*	GetPalette()	{ return m_pPal; }
	CFont*		GetFont()		{ return &m_font; }
	CBrush*		GetNullBrush()	{ return &m_brNull; }

	BOOL		IsListOnly() const	{ return (m_nPageSelect == PS_JOIN_PAGE); }
	BOOL		IsCreateChannel() const
				{ return ((m_nPageSelect & PS_CREATE_PAGE) &&
							!m_CreateChannelPage.m_strTopic.IsEmpty()); }

	CUC2Doc*		GetDocument()	{ return m_pDoc; }
	CUC2Socket*		GetSocket()		{ return m_pDoc->GetSocket(); }

	CPPActor			m_ActorListPage;
#ifdef _MALL
	CPPShoppingCart		m_ShoppingCartPage;
	CPPPaymentInfo		m_PaymentInfoPage;
#endif
	CPPChannel			m_JoinChannelPage;
	CPPCreateChannel	m_CreateChannelPage;
	EC_CHANNELINFO		m_ecInfo;

// Operations
public:
	BOOL		OnPageEraseBkgnd(CDC* pDC);
	void		InitControl(const int nCtrlID, const CRect& rcCtrl);
	BOOL		ActivateCreateChannelPage();
	BOOL		ActivateJoinChannelPage();
	BOOL		GetChannelInfo(EC_CHANNELINFO& ecInfo);
	void		SetMemberInfo(CMemberInfo& mi);
	void		GetMemberInfo(CMemberInfo& mi) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSJoinChannel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSJoinChannel();

// Generated message map functions
protected:
	CDIB*			m_pDIBBack;		// Background frame image
	CPalette*		m_pPal;			// main palette
	BOOL			m_bPaletteCreated;
//	CRect			m_rcPSheet;
	CBrush			m_brNull;
	CFont			m_font;
	int				m_nPageSelect;	// enum PAGE_SELECT
	CUC2Doc*		m_pDoc;			// To get pointers to Socket
	//{{AFX_MSG(CPSJoinChannel)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PSJOINCHANNEL_H__
