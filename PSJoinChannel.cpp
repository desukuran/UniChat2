// PSJoinChannel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PSJoinChannel.h"
#include "ResMan.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/DIBPal.h"
#include "MainFrm.h"
#include "MemberInfo.h"
#include "UC2Doc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

LPCTSTR HTTP = _T("http://");

/////////////////////////////////////////////////////////////////////////////
// CPSJoinChannel

IMPLEMENT_DYNAMIC(CPSJoinChannel, CPropertySheet)

CPSJoinChannel::CPSJoinChannel(CUC2Doc* pDoc, const int nPageSelect, LPCTSTR pszCaption, UINT iSelectPage)
	 : CPropertySheet(pszCaption, NULL, iSelectPage)	/* IDS_PROPSHT_CAPTION */
{
	TRACE0("CPSJoinChannel::CPSJoinChannel()\n");

	m_pDoc = pDoc;
	m_nPageSelect = nPageSelect;

	m_brNull.CreateStockObject(NULL_BRUSH);
	m_font.CreateFont(-12, 0, 0, 0, FW_BOLD,	// NORMAL,
			FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
			"±¼¸²Ã¼");
#else
			"Times New Roman");
#endif

	m_pPal = NULL;	// Set it NULL before loading DIB successfully
	m_pDIBBack = NULL;

	CString strPath(*gResMan.GetResPath());
/*
	CString strFile(strPath + "U2Login|LoginBk.bmp");
	m_pDIBBack = new CDIB;
	if (!m_pDIBBack->Load(strFile))
	{
		delete m_pDIBBack;
		m_pDIBBack = NULL;
		return;
	}
	m_pDIBBack->ShiftRGBPercent(0, 256, 100);
*/
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();

//	if (pMF->Is256Palette())
//	{	// Use mainframe's palette to avoid color flickering
		m_pPal = pMF->GetPalette();
//		m_pDIBBack->MapColorsToPalette(m_pPal);
		m_bPaletteCreated = FALSE;
/*	}
	else	// Use original palette in the file for TRUE color system
	{		// Create the palette from the DIB.
		CDIBPal* pDIBPal;
		pDIBPal = new CDIBPal;
		ASSERT(pDIBPal);
		if (!pDIBPal->Create(m_pDIBBack))
		{
			AfxMessageBox("Failed to create palette from DIB file");
			delete pDIBPal;
		}
		m_pPal = pDIBPal;	// type casting to parent class
		m_bPaletteCreated = TRUE;
	}
*/
//	m_pDIBBack->GetRect(m_rcPSheet);
//	m_rcPSheet.InflateRect(14, 49);
/*
	// Create the palette from the DIB.
	m_pPal = new CDIBPal;
	ASSERT(m_pPal);
	if (!m_pPal->Create(m_pDIBBack))
	{
		AfxMessageBox("Failed to create palette from DIB file");
		delete m_pPal;
		m_pPal = NULL;
	}
*/
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	TRACE0("\tAddPage(&m_ActorListPage);\n");

	if (nPageSelect & PS_ACTOR_PAGE)
		AddPage(&m_ActorListPage);
#ifdef _MALL
	if (nPageSelect & PS_JOIN_PAGE)
		AddPage(&m_ShoppingCartPage);
	if (nPageSelect & PS_CREATE_PAGE)
		AddPage(&m_PaymentInfoPage);
#else
	if (nPageSelect & PS_JOIN_PAGE)
		AddPage(&m_JoinChannelPage);
	if (nPageSelect & PS_CREATE_PAGE)
		AddPage(&m_CreateChannelPage);
#endif
}

CPSJoinChannel::~CPSJoinChannel()
{
	TRACE0("CPSJoinChannel::~CPSJoinChannel()\n");
	if (m_pDIBBack)
		delete m_pDIBBack;
	if (m_pPal && m_bPaletteCreated)
		delete m_pPal;
}

BEGIN_MESSAGE_MAP(CPSJoinChannel, CPropertySheet)
	//{{AFX_MSG_MAP(CPSJoinChannel)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPSJoinChannel message handlers
// To be shared in child property pages
BOOL CPSJoinChannel::OnPageEraseBkgnd(CDC* pDC)
{
	// Make sure we have what we need to do a paint.
	if (!GetDIBBack())
	{
//		TRACE("CPSJoinChannel: No DIB!\n");
		return FALSE;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	CPalette* pPal = GetPalette();
	if (pPal)
	{
		pPalOld = pDC->SelectPalette(pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	if (m_pDIBBack)
	{
		m_pDIBBack->Draw(pDC, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
							12, 12);
	}
	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
	
	return TRUE;
}

BOOL CPSJoinChannel::OnQueryNewPalette() 
{
	TRACE("CPSJoinChannel::OnQueryNewPalette\n");
//	if (m_pDoumi && m_pDoumi->GetDIBPal())
	if (m_pPal)
	{
		CDC* pdc = GetDC();
		CPalette* pPalOld = pdc->SelectPalette((CPalette*)m_pPal, FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (pPalOld)
			pdc->SelectPalette(pPalOld, FALSE);
		ReleaseDC(pdc);
		if (u)
		{	// Some colors changed so we need to do a repaint.
			Invalidate();	// Repaint the lot.
			return TRUE;	// Say we did something.
		}
	}
	return FALSE;	// Say we did nothing.
}

void CPSJoinChannel::OnPaletteChanged(CWnd* pFocusWnd) 
{
	TRACE("CPSJoinChannel::OnPaletteChanged\n");
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

/*
void CPSJoinChannel::OnSize(UINT nType, int cx, int cy) 
{
	TRACE("CPSJoinChannel::OnSize(%d,%d,%d)\n", nType, cx, cy);
	CPropertySheet::OnSize(nType, cx, cy);

	if (m_pDIBBack)
	{
		SetWindowPos(NULL, 0, 0, m_rcPSheet.Width(), m_rcPSheet.Height(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}
*/

BOOL CPSJoinChannel::OnInitDialog() 
{
	TRACE("CPSJoinChannel::OnInitDialog() => 0x%x\n", this);
/*
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	CRect rc;
	CWnd* pW = (CWnd*)GetDlgItem(IDOK);
	if (pW)
	{
		pW->GetClientRect(&rc);
		pW->SetWindowPos(NULL, rcPSheet.left, rcCtrl.top,
						rcCtrl.Width(), rcCtrl.Height(),
						SWP_NOZORDER | SWP_NOACTIVATE);
#ifdef _ENGLISH
		pW->SetWindowText("OK!");
#endif
	}
	pW = (CWnd*)GetDlgItem(IDCANCEL);
	if (pW)
		pW->SetWindowText("Cancel");
	pW = (CWnd*)GetDlgItem(IDHELP);
	if (pW)
		pW->SetWindowText("Help");
	pW = (CWnd*)GetDlgItem(0x3021);	// Apply
	if (pW)
		pW->SetWindowText("Apply");
*/
#ifdef _MALL
	((CWnd*)GetDlgItem(IDOK))->SetWindowText("OK");
	((CWnd*)GetDlgItem(IDCANCEL))->SetWindowText("Cancel");
#endif
	CWnd* pW = (CWnd*)GetDlgItem(IDHELP);
	if (pW)
		pW->ShowWindow(SW_HIDE);
	pW = (CWnd*)GetDlgItem(0x3021);	// Apply
	if (pW)
		pW->ShowWindow(SW_HIDE);
//		pW->EnableWindow(FALSE);
	return CPropertySheet::OnInitDialog();
}

void CPSJoinChannel::InitControl(const int nCtrlID, const CRect& rcCtrl)
{
	CWnd* pW = GetDlgItem(nCtrlID);
	ASSERT(pW);
	pW->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top,
					rcCtrl.Width(), rcCtrl.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);
	pW->SetFont(&m_font, FALSE);	// do not Redraw
}

BOOL CPSJoinChannel::GetChannelInfo(EC_CHANNELINFO& ecInfo)
{
	::ZeroMemory(&ecInfo, sizeof(EC_CHANNELINFO));

	CString* pS;
	int len;
	// N.B. You should not pass the pointer to objects in this stack!
	if (IsCreateChannel())
	{
		pS = m_CreateChannelPage.GetStageName();
		len = pS->GetLength();
		if (!len)
			return FALSE;
		ecInfo.szName	= pS->GetBuffer(len+1);
		ecInfo.dwType	=	m_CreateChannelPage.IsPublic()
						?	CS_CHANNEL_PUBLIC		/*  | CS_CHANNEL_ALLOWANON */
						:	CS_CHANNEL_PROTECTED;	/*  | CS_CHANNEL_ALLOWANON */
	}
	else // Join the Channel
	{
		// m_strStageID will be the selected channel
		pS = &m_JoinChannelPage.m_strStageID;
		m_CreateChannelPage.m_strTopic = *pS;
		len = pS->GetLength();
		if (!len)	// No room is selected: Consider as a MUD mode
		{
			m_JoinChannelPage.GetLastStageID();
			gResMan.GetStageTitle(m_CreateChannelPage.m_strTopic);	// = UC2MUD_TOPIC;
		}
		ecInfo.szName	= pS->GetBuffer(len+1);

		if (m_JoinChannelPage.IsMUD())
		{
			gResMan.GetStageTitle(m_CreateChannelPage.m_strTopic);	// = UC2MUD_TOPIC;
		}

		if (m_JoinChannelPage.m_strPassword.IsEmpty())
		{
			ecInfo.dwType	= CS_CHANNEL_PUBLIC;	/* | CS_CHANNEL_ALLOWANON */
			m_CreateChannelPage.m_strPassword.Empty();
		}
		else
		{
			ecInfo.dwType	= CS_CHANNEL_PROTECTED;	/* | CS_CHANNEL_ALLOWANON */
			m_CreateChannelPage.m_strPassword = m_JoinChannelPage.m_strPassword;
		}
	}
	pS = &m_CreateChannelPage.m_strTopic;
	len = pS->GetLength();
	ecInfo.szTopic		= pS->GetBuffer(len+1);

	if (m_CreateChannelPage.m_strPassword.IsEmpty())
	{
		ecInfo.szPass	= _T("");
	}
	else
	{
		pS = &m_CreateChannelPage.m_strPassword;
		len = pS->GetLength();
		ecInfo.szPass	= pS->GetBuffer(len+1);
	}

	ecInfo.cUsersMax	= MAX_MEMBERS_IN_CHANNEL;	// limit # of members in a channel
	ecInfo.dwFlags		= CS_CHANNEL_FLAG_MICONLY;

//	CPropertySheet::OnClose();
	return TRUE;
}

void CPSJoinChannel::SetMemberInfo(CMemberInfo& mi)
{
	m_ActorListPage.m_nCharID		= mi.GetCharID();
	m_ActorListPage.m_nAge			= mi.GetAge();
	m_ActorListPage.m_nSex			= mi.GetSex();
	m_ActorListPage.m_strProfile	= *mi.GetProfile();
	m_ActorListPage.m_strName		= *mi.GetRealName();
	m_ActorListPage.m_strChatID		= *mi.GetNick();
	m_ActorListPage.m_strHomePage	= *mi.GetHyperlink();
	if (m_ActorListPage.m_strHomePage.IsEmpty())
		m_ActorListPage.m_strHomePage = HTTP;
	int nVer = mi.GetVersion();
	m_ActorListPage.m_strVersion.Format("V%d.%02d ", nVer / 100, nVer % 100);
}

void CPSJoinChannel::GetMemberInfo(CMemberInfo& mi) const
{
	mi.SetCharID(	m_ActorListPage.m_nCharID);
	mi.SetAge(		m_ActorListPage.m_nAge);
	mi.SetSex(		m_ActorListPage.m_nSex);
	mi.SetBubbleKind(m_ActorListPage.m_nSex);	// Later I'll change this...
	mi.SetProfile(	m_ActorListPage.m_strProfile);
	mi.SetRealName(	m_ActorListPage.m_strName);
	mi.SetNick(		m_ActorListPage.m_strChatID);
	if (!m_ActorListPage.m_strHomePage.IsEmpty() &&
		(lstrcmpi(m_ActorListPage.m_strHomePage, HTTP) != 0))
		mi.SetHyperlink(m_ActorListPage.m_strHomePage);
}

BOOL CPSJoinChannel::ActivateCreateChannelPage()
{
	if (!(m_nPageSelect & PS_CREATE_PAGE))
		AddPage(&m_CreateChannelPage);
	return SetActivePage(&m_CreateChannelPage);
}

BOOL CPSJoinChannel::ActivateJoinChannelPage()
{
	if (!(m_nPageSelect & PS_JOIN_PAGE))
		AddPage(&m_JoinChannelPage);
	return SetActivePage(&m_JoinChannelPage);
}
