// PPChannel.cpp : implementation file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#include "stdafx.h"
#include "resource.h"
#include "PPChannel.h"
#include "PSJoinChannel.h"
#include "UC2CS.h"
#include "MemberListDlg.h"
#include "InputPassword.h"
#include "UC2.h"	// RegGetLastStageID()
#include "ResMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

IMPLEMENT_DYNCREATE(CPPChannel, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CPPChannel property page

CPPChannel::CPPChannel() : CPropertyPage(CPPChannel::IDD)
{
	TRACE0("CPPChannel::CPPChannel()\n");
	//{{AFX_DATA_INIT(CPPChannel)
	m_strCount = _T("");
	m_strMessage = _T("");
	m_strStageID = _T("");
	//}}AFX_DATA_INIT
	m_font.CreateFont(-13, 0, 0, 0, FW_BOLD,
			FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
			"±¼¸²Ã¼");
#else
			"Times New Roman");
#endif
	m_ilChannel.Create(IDB_IL_CHANNEL, 16, 1, CLR_NONE);
	m_nIndex = -1;
	m_nUsers = 0;
	m_bMUD = FALSE;
}

CPPChannel::~CPPChannel()
{
	TRACE0("CPPChannel::~CPPChannel()\n");
}

void CPPChannel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPChannel)
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_lcChannel);
	DDX_Text(pDX, IDC_STATIC_CHANNEL_COUNT, m_strCount);
	DDX_Text(pDX, IDC_STATIC_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_ST_STAGEID, m_strStageID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPChannel, CPropertyPage)
	//{{AFX_MSG_MAP(CPPChannel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHANNEL, OnClickListChannel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CHANNEL, OnDblclkListChannel)
	ON_BN_CLICKED(IDC_BTN_RENEW, OnBtnRenew)
	ON_BN_CLICKED(IDC_BTN_MEMBER, OnBtnMember)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_CHANNEL, OnDeleteitemListChannel)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MUD, OnBtnMud)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CMD_QUERY_CHANNELS,		OnQueryChannels)
	ON_MESSAGE(CMD_QUERY_CHANNELS_END,	OnQueryChannelsEnd)
	ON_MESSAGE(CMD_QUERY_NOMATCHES,		OnQueryNoMatches)
	ON_MESSAGE(CMD_QUERY_ERROR,			OnQueryError)
END_MESSAGE_MAP()

BOOL CPPChannel::OnEraseBkgnd(CDC* pDC) 
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	return pPSJC->OnPageEraseBkgnd(pDC);
}

/*
HBRUSH CPPChannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)*pPSJC->GetNullBrush();
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
*/
//	TRACE("CPSJoinChannel::OnSize(%d,%d,%d)\n", nType, cx, cy);

void CPPChannel::OnClickListChannel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	m_lcChannel.ScreenToClient(&point);
	
	if ((m_nIndex = m_lcChannel.HitTest(point)) != -1)
	{
/*		// for UniChat 1.1
		CS_PROPDATA	cspd;
		PICS_PROPERTY picsProp = (PICS_PROPERTY)m_lcChannel.GetItemData(m_nIndex);
		picsProp->HrGetProperty(&cspd, CSINDEX_PROP_CHANNEL_MODE);
		DWORD dwMode = *((DWORD*)cspd.pbData);
		BOOL bPrivate = (dwMode & CS_CHANNEL_PROTECTED);

		picsProp->HrGetProperty(&cspd, CSINDEX_PROP_TOPIC);
		CString strStage((CHAR*)cspd.pbData);
*/
		m_strStageID = m_lcChannel.GetItemText(m_nIndex, 0);	// SubItem=0
		m_strMessage = m_strStageID;
		UpdateData(FALSE);	// Write
//		m_btnBkg.EnableWindow();
	}
	*pResult = 0;
}

void CPPChannel::OnDblclkListChannel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnClickListChannel(pNMHDR, pResult);

	if (m_nIndex == -1)
		return;

	CPSJoinChannel* pSheet = (CPSJoinChannel*)GetParent();
	ASSERT(pSheet);
	CUC2Socket* pCS = pSheet->GetSocket();
	if (pCS && !pCS->IsQueryOK())
	{
		AfxMessageBox(IDS_QUERY_LINE_BUSY);
		return;
	}
	// Get the MIC channel index of the current selected item
	CS_PROPDATA	cspd;
	PICS_PROPERTY picsProp = (PICS_PROPERTY)m_lcChannel.GetItemData(m_nIndex);
	if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_ID)))
		return;
	ASSERT(cspd.dwcb == sizeof(DWORD));
	DWORD dwChannelID = *((DWORD*)cspd.pbData);

	CMemberListDlg dlgML;
	dlgML.SetPPChannel(pSheet->GetDocument(), dwChannelID);
	dlgML.DoModal();
	
	*pResult = 0;
}

void CPPChannel::OnBtnRenew() 
{
	VERIFY(ShowList());
}

void CPPChannel::OnBtnMember() 
{
	CPSJoinChannel* pSheet = (CPSJoinChannel*)GetParent();
	ASSERT(pSheet);
	CMemberListDlg dlgML;
	dlgML.SetPPChannel(pSheet->GetDocument(), 0);
	dlgML.DoModal();
}

void CPPChannel::OnDeleteitemListChannel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->lParam)
	{
		PICS_PROPERTY picsProp = (PICS_PROPERTY)pNMListView->lParam;
		picsProp->Release();
	}
	*pResult = 0;
}

BOOL CPPChannel::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT(GetDlgItem(IDC_STATIC_MESSAGE));
	GetDlgItem(IDC_STATIC_MESSAGE)->SetFont(&m_font, FALSE);

	// Prepare List Control for Channels list
	m_lcChannel.SetImageList(&m_ilChannel, LVSIL_SMALL);
	
	char*	szColumn[]	= {"Stage", "Topic", "Members"};
	int		nWidth[]	= {130, 205, 35};

	LV_COLUMN	lvC;	// list view column structure
	lvC.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;	// valid members
	lvC.fmt		= LVCFMT_LEFT;	// left-align column

	// Add the columns.
	for (int i=0; i < sizeof(nWidth)/sizeof(nWidth[0]); i++)
	{
		lvC.cx			= nWidth[i];	// width of column in pixels
		lvC.iSubItem	= i;
		lvC.pszText		= szColumn[i];
		if (m_lcChannel.InsertColumn(i, &lvC) == -1)
			return NULL;
	}
//	if (m_bMUD)
//		GetDlgItem(IDC_LIST_CHANNEL)->EnableWindow(FALSE);	//ShowWindow(SW_HIDE);
	SetMUDButtonTitle();
	VERIFY(ShowList());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPChannel::OnDestroy() 
{
	CPropertyPage::OnDestroy();
}

// returns the index of the added item
int CPPChannel::AddItem(const int i, int iImage, PICS_PROPERTY picsProp, TCHAR* psz)
{
	if (picsProp)
		picsProp->AddRef();

	LV_ITEM		lvI;	// list view item structure
	::ZeroMemory(&lvI, sizeof(lvI));
	lvI.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state		= 0;
	lvI.stateMask	= 0;

	lvI.iItem		= i;
	lvI.iSubItem	= 0;
	// The parent window is responsible for storing the text.
	// The list view control will send an LVN_GETDISPINFO 
	// when it needs the text to display.
	lvI.pszText		= psz;
	lvI.cchTextMax	= MIC_MAX_CHANNEL_NAME_LENGTH_MIC;	// 63
	lvI.iImage		= iImage;
	lvI.lParam		= (LPARAM)picsProp;

	int iItem = m_lcChannel.InsertItem(&lvI);
	if ((iItem == -1) && picsProp)
		picsProp->Release();
	return iItem;
}

BOOL CPPChannel::AddChannel(PICS_PROPERTY picsProp)
{
	ASSERT(picsProp);
	// Add the channel name..
	int i;
	if (FAILED(picsProp->HrGetPrivateData((PVOID*)&i)))
	{
		TRACE0("CPPChannel::AddChannel - HrGetPrivateData failed.\n");
		return FALSE;
	}
	
	CS_PROPDATA	cspd;
	if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_CHANNEL_NAME)))
		return FALSE;
	TCHAR* szChannel = (TCHAR*)cspd.pbData;

	// Filter display according to the channel type
	if (gResMan.GetStageType(szChannel) == (m_bMUD ? ST_MUD : ST_PUBLIC))
	{
		if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_CHANNEL_MODE)))
			return FALSE;
		DWORD dwMode = *((DWORD*)cspd.pbData);

		if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_TOPIC)))
			return FALSE;
		CString strTopic((CHAR*)cspd.pbData);

		if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_CHANNEL_CUSER)))
			return FALSE;
		CHAR szCount[20];
		int nCount = *((DWORD*)cspd.pbData);
		wsprintf(szCount, "%d", nCount);
		m_nUsers += nCount;

		int iImg;
		if (dwMode & CS_CHANNEL_PROTECTED)
			iImg = IL_CHANNELPRIV;
		else
			iImg = m_bMUD ? IL_CHANNELMUD : IL_CHANNEL;
		int iItem = AddItem(i, iImg, picsProp, szChannel);
//		if (dwMode & CS_CHANNEL_PROTECTED)
//			strTopic += " *PRIVATE*";
		m_lcChannel.SetItemText(m_i, 1, strTopic);
		m_lcChannel.SetItemText(m_i, 2, szCount);
		m_i++;
		return (iItem != -1);
	}
	return FALSE;
}

BOOL CPPChannel::ShowList()
{
	CPSJoinChannel* pSheet = (CPSJoinChannel*)GetParent();
	ASSERT(pSheet);
	CUC2Socket* pCS = pSheet->GetSocket();
	if (!pCS)
		return FALSE;

	m_strMessage.LoadString(IDS_RECEIVING_CHANNELS_LIST);
	UpdateData(FALSE);
//	m_pSheet->Chat(m_strMessage);
//	m_pSheet->GetDoumi()->SetMode(CDoumi::DOUMI_WINK);

	if (pCS->IsQueryOK())
	{
		m_lcChannel.DeleteAllItems();
		m_i = m_nUsers = 0;
		// Say that now I'm the client of the socket query service (to let CUC2Socket know)
		pCS->SetQueryClient(GetSafeHwnd());
		BeginWaitCursor();

		if (!pCS->FQueryListChannels())
			EndDialog(-1);
	}
	else
	{
		AfxMessageBox(IDS_QUERY_LINE_BUSY);
		EndDialog(-1);
	}
	// Then PXSocket will call AddChannel for each item

	return TRUE;
}

void CPPChannel::EndOfList()
{
	if (m_bMUD)
	{
		AfxFormatString1(m_strMessage, IDS_MUD_MODE, m_strStageID);
	}
	else
	{
		m_strMessage.LoadString(m_lcChannel.GetItemCount()
						? IDS_CLICK_CHANNEL_TITLE
						: IDS_NO_CHANNEL_OPENED);
	}
	UpdateData(FALSE);
	EndWaitCursor();
//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

//////////////////////////////////////////////////////////////////
// to handle messages from ChatSock

LRESULT CPPChannel::OnQueryChannels(WPARAM wParam, LPARAM lParam)
{
//	TRACE("<=0x%lx RECV\n", lParam);
	if (!AddChannel((PICS_PROPERTY)lParam))
		return -1;
	m_strCount.Format("%d:%d", m_lcChannel.GetItemCount(), m_nUsers);
	SetDlgItemText(IDC_STATIC_CHANNEL_COUNT, m_strCount);	// for speed
	return 0;
}

LRESULT CPPChannel::OnQueryChannelsEnd(WPARAM wParam, LPARAM lParam)
{
	EndOfList();
	return 0;
}

LRESULT CPPChannel::OnQueryNoMatches(WPARAM wParam, LPARAM lParam)
{
	m_strCount = "0:0";
//	m_strMessage = (char*)lParam;
	m_strMessage.LoadString(IDS_NO_CHANNEL_OPENED);
	UpdateData(FALSE);	// Write
//	m_pSheet->ChatVoice(m_strMessage);
	return 0;
}

LRESULT CPPChannel::OnQueryError(WPARAM wParam, LPARAM lParam)
{
	m_strCount = "0:0";
	m_strMessage = (char*)lParam;
	m_strMessage.LoadString(IDC_STATIC_MESSAGE);
	UpdateData(FALSE);	// Write
//	m_pSheet->ChatVoice(m_strMessage);
	return 0;
}

/*
void CPPChannel::OnBtnCreateChannel()
{
	m_pSheet->AddCreateChannelPage();
	GetDlgItem(IDC_BTN_CREATE_CHANNEL)->EnableWindow(FALSE);
}
*/

BOOL CPPChannel::OnApply() 
{
	CPSJoinChannel* pSheet = (CPSJoinChannel*)GetParent();
	ASSERT(pSheet);
	if (m_bMUD)
	{
	}
	else if (!pSheet->IsListOnly() && (m_nIndex == -1) && !pSheet->IsCreateChannel())
	{
		if (m_lcChannel.GetItemCount() == 0)
		{
			if (m_strMessage.LoadString(IDS_NO_CHANNEL_OPENED))
				UpdateData(FALSE);
			pSheet->ActivateCreateChannelPage();
			AfxMessageBox(IDS_FILL_CHANNEL_TITLE);
		}
		else
		{
			if (m_strMessage.LoadString(IDS_SELECT_CHANNEL))
				UpdateData(FALSE);
			pSheet->ActivateJoinChannelPage();
		}
		return FALSE;
	}
	else
	{
		LV_ITEM it;
		::ZeroMemory(&it, sizeof(it));	// Missing this was the bug!
		it.iItem = m_nIndex;
		it.mask = LVIF_IMAGE;
		if (m_lcChannel.GetItem(&it) && (it.iImage == IL_CHANNELPRIV))
		{
			CInputPassword IPDlg;
			if (IPDlg.DoModal() == IDOK) //&& !IPDlg.m_strPassword.IsEmpty())
			{
				m_strPassword = IPDlg.m_strPassword;
			}
			else
			{
				return FALSE;
			}
		}
	}
	return CPropertyPage::OnApply();
}

void CPPChannel::OnBtnMud() 
{
	m_bMUD = !m_bMUD;
//	GetDlgItem(IDC_LIST_CHANNEL)->EnableWindow(!m_bMUD);
	if (m_bMUD)
	{
		m_nIndex = -1;
		m_strPassword.Empty();
		GetLastStageID();
	}
	else
	{
		m_strStageID.Empty();
	}
	SetMUDButtonTitle();
	OnBtnRenew();
}

void CPPChannel::GetLastStageID()
{
	((CUC2App*)AfxGetApp())->RegGetLastStageID(m_strStageID);
	if (m_strStageID.IsEmpty())
	{
		m_strStageID = *gResMan.GetStageName(0);
		gResMan.ExtractStageID(m_strStageID);
	}
	gResMan.MakeStageName(m_strStageID, FALSE);	// MUD name
}

void CPPChannel::SetMUDButtonTitle()
{
	CString strBtn;
	strBtn.LoadString(m_bMUD ? IDS_BTN_MUD : IDS_BTN_USER);
	GetDlgItem(IDC_BTN_MUD)->SetWindowText(strBtn);
}
