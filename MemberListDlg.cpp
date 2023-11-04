// MemberListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "MemberListDlg.h"
#include "UC2Doc.h"
#include "UC2CS.h"
#include "PPChannel.h"
#include "Actor.h"
#include "Parser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemberListDlg dialog

CMemberListDlg::CMemberListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemberListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemberListDlg)
	m_strCount = _T("");
	m_strMessage = _T("");
	//}}AFX_DATA_INIT
	m_pDoc = NULL;
//	m_dwChannelID	= 0L;
	m_font.CreateFont(-12, 0, 0, 0, FW_BOLD,
			FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
			"굴림체");
#else
			"Times New Roman");
#endif
	m_ilMember.Create(IDB_IL_MEMBER, 16, 1, CLR_NONE);
	m_nIndex = -1;
	m_strChannel.Empty();
}

void CMemberListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemberListDlg)
	DDX_Control(pDX, IDC_LIST_MEMBER, m_lcMember);
	DDX_Text(pDX, IDC_STATIC_MEMBER_COUNT, m_strCount);
	DDX_Text(pDX, IDC_STATIC_MESSAGE, m_strMessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMemberListDlg, CDialog)
	//{{AFX_MSG_MAP(CMemberListDlg)
	ON_BN_CLICKED(IDC_BTN_INVITE, OnBtnInvite)
	ON_BN_CLICKED(IDC_BTN_RENEW, OnBtnRenew)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEMBER, OnClickListMember)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_MEMBER, OnDeleteitemListMember)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEMBER, OnDblclkListMember)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CMD_QUERY_MEMBERS,		OnQueryMembers)
	ON_MESSAGE(CMD_QUERY_MEMBERS_END,	OnQueryMembersEnd)
	ON_MESSAGE(CMD_QUERY_NOMATCHES,		OnQueryNoMatches)
	ON_MESSAGE(CMD_QUERY_GET_REALNAME,	OnQueryGetRealname)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemberListDlg message handlers

void CMemberListDlg::OnBtnInvite() 
{
	if (m_nIndex == -1)
	{
		AfxMessageBox(IDS_INVITE_SELECT_MEMBER);
		return;
	}
	CString strNick = m_lcMember.GetItemText(m_nIndex, 0);	// SubItem=0
	CUC2Channel* pChan = m_pDoc->GetChannel();
	if (!pChan)
	{
		AfxMessageBox(IDS_INVITE_OPEN_CHANNEL);
		return;
	}

	CString strMsg;
	CActor* pA = m_pDoc->GetThisActor();
	ASSERT(pA);
	if (*pA->GetNick() == strNick)
	{
		if (strMsg.LoadString(IDS_INVITE_ERROR_MYSELF))
			AfxMessageBox(strMsg);
		return;
	}

	int len = strNick.GetLength();
	CS_INVITEINFO csiInfo;
	csiInfo.dwUserID = 0;
	csiInfo.pvNickTo = strNick.GetBuffer(len);
	if (pChan->FSendInvite(&csiInfo))
	{
		AfxFormatString1(strMsg, IDS_INVITE_OK, strNick);
		AfxMessageBox(strMsg);
	}
	else
	{
		AfxMessageBox(IDS_INVITE_FAIL);
	}
}

void CMemberListDlg::OnBtnRenew() 
{
	VERIFY(ShowList());
}

void CMemberListDlg::OnClickListMember(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	m_lcMember.ScreenToClient(&point);
	
	m_nIndex = m_lcMember.HitTest(point);
	if (m_nIndex != -1)
	{
		m_strMessage = m_lcMember.GetItemText(m_nIndex, 0);	// SubItem=0
		UpdateData(FALSE);
	}
	*pResult = 0;
}

BOOL CMemberListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pDoc);

	ASSERT(GetDlgItem(IDC_STATIC_MESSAGE));
	GetDlgItem(IDC_STATIC_MESSAGE)->SetFont(&m_font, FALSE);

	// Prepare List Control for Channels list
	m_lcMember.SetImageList(&m_ilMember, LVSIL_SMALL);

	char*	szColumn[]	= {"Chat ID", "Information"};
	int		nWidth[]	= {120, 210};

	LV_COLUMN	lvC;	// list view column structure
	lvC.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;	// valid members
	lvC.fmt		= LVCFMT_LEFT;	// left-align column

	// Add the columns.
	for (int i=0; i < sizeof(nWidth)/sizeof(int); i++)
	{
		lvC.cx			= nWidth[i];	// width of column in pixels
		lvC.iSubItem	= i;
		lvC.pszText		= szColumn[i];
		if (m_lcMember.InsertColumn(i, &lvC) == -1)
			return NULL;
	}
	VERIFY(ShowList());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMemberListDlg::OnDeleteitemListMember(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->lParam)
	{
		PICS_PROPERTY picsProp = (PICS_PROPERTY)pNMListView->lParam;
		picsProp->Release();
	}
	*pResult = 0;
}

void CMemberListDlg::OnDblclkListMember(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	m_lcMember.ScreenToClient(&point);
	
	m_nIndex = m_lcMember.HitTest(point);
	if (m_nIndex != -1)
	{
		m_strMessage = m_lcMember.GetItemText(m_nIndex, 0);	// SubItem=0
		UpdateData(FALSE);
	}

	CUC2Socket* pCS = m_pDoc->GetSocket();
	if (!pCS)
		return;
	if (pCS->IsQueryOK())
	{
		// I'm alive.
		pCS->SetQueryClient(GetSafeHwnd());
		BeginWaitCursor();
//		m_strMessage = _T("사용자 실제 이름 조회...");
//		UpdateData(FALSE);
		CString strNick = m_lcMember.GetItemText(m_nIndex, 0);
		int len = strNick.GetLength();
		TCHAR* pszNick = strNick.GetBuffer(len);
		if (!pCS->FQueryRealName(pszNick))
		{
//			EndDialog(-1);
		}
	}
	*pResult = 0;
}

void CMemberListDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

// returns the index of the added item
int CMemberListDlg::AddItem(const int i, int iImage, PICS_PROPERTY picsProp, TCHAR* psz)
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
	lvI.cchTextMax	= MIC_MAX_USER_NAME_LENGTH;	// 63
	lvI.iImage		= iImage;
	lvI.lParam		= (LPARAM)picsProp;

	int iItem = m_lcMember.InsertItem(&lvI);
	if ((iItem == -1) && picsProp)	// Insert failure
		picsProp->Release();
	return iItem;
}

BOOL CMemberListDlg::AddMember(PICS_PROPERTY picsProp)
{
	ASSERT(picsProp);
	int i;
	if (FAILED(picsProp->HrGetPrivateData((PVOID*)&i)))
	{
		TRACE0("CMemberListDlg::AddMember - HrGetPrivateData failed.\n");
		return FALSE;
	}
	// Add the channel name..
	CS_PROPDATA	cspd;
	if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_MEMBER_NAME)))
		return FALSE;
	CHAR* szName = (CHAR*)cspd.pbData;

	if (FAILED(picsProp->HrGetProperty(&cspd, CSINDEX_PROP_MEMBER_MODE)))
		return FALSE;
	DWORD dwMode = *((DWORD*)cspd.pbData);

	int iImg;
	if (dwMode & CS_MEMBER_HOST)
		iImg = IL_HOST;
	else if (dwMode & CS_MEMBER_SPEAKER)
		iImg = IL_SPEAKER;
	else
		iImg = IL_SPECTATOR;
	int iItem = AddItem(i, iImg, picsProp, szName);
//	m_lcMember.SetItemText(i, 1, szRealName);
	return (iItem != -1);
}

BOOL CMemberListDlg::ShowList()
{
	CUC2Socket* pCS = m_pDoc->GetSocket();
	if (!pCS)
		return FALSE;
	m_lcMember.DeleteAllItems();

	if (pCS->IsQueryOK())
	{
		// I'm alive.
		pCS->SetQueryClient(GetSafeHwnd());
		BeginWaitCursor();

		if (m_dwChannelID || !m_strChannel.IsEmpty())
		{
			m_strMessage.LoadString(IDS_TRANSFER_MEMBER_CHANNEL);
			UpdateData(FALSE);
			if (m_dwChannelID)
			{
				if (!pCS->FQueryMembersInChannel(m_dwChannelID))
					EndDialog(-1);
			}
			else
			{
				int nLen = m_strChannel.GetLength();
				if (!pCS->FQueryMembersInChannelName(m_strChannel.GetBuffer(nLen)))
					EndDialog(-1);
				m_strChannel.ReleaseBuffer();
			}
		}
		else
		{
			m_strMessage.LoadString(IDS_TRANSFER_MEMBER_ALL_CHANNEL);
			UpdateData(FALSE);
			if (!pCS->FQueryListAllUsers())
				EndDialog(-1);
		}
	}
	else
	{
		AfxMessageBox(IDS_QUERY_LINE_BUSY);
		EndDialog(-1);
	}
	// Then UC2Socket will call AddChannel for each item

	return TRUE;
}

void CMemberListDlg::EndOfList()
{
	m_strMessage.LoadString(IDS_DATA_TRANSMISSION_DONE);	// "자료 전송 완료"
	UpdateData(FALSE);
	EndWaitCursor();
//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

//////////////////////////////////////////////////////////////////
// to handle messages from ChatSock

LRESULT CMemberListDlg::OnQueryMembers(WPARAM wParam, LPARAM lParam)
{
	AddMember((PICS_PROPERTY)lParam);

	m_strCount.Format("%d", m_lcMember.GetItemCount());
	SetDlgItemText(IDC_STATIC_MEMBER_COUNT, m_strCount);
	UpdateData(FALSE);
	return 0;
}

LRESULT CMemberListDlg::OnQueryMembersEnd(WPARAM wParam, LPARAM lParam)
{
	EndOfList();
/*
	CUC2Socket* pCS = m_pDoc->GetSocket();
	if (!pCS)
		return FALSE;
	if (pCS->IsQueryOK())
	{
		// I'm alive.
		pCS->SetQueryClient(GetSafeHwnd());
		BeginWaitCursor();
//		m_strMessage = _T("사용자 실제 이름 조회...");
//		UpdateData(FALSE);
		int nItems = m_lcMember.GetItemCount();
		CString strNick;
		int len;
		m_iRealName = 0;
		for (int i=0; i < nItems; i++)
		{
			strNick = m_lcMember.GetItemText(i, 0);
			len = strNick.GetLength();
			TCHAR* pszNick = strNick.GetBuffer(len);
			if (!pCS->FQueryRealName(pszNick))
			{
//				EndDialog(-1);
			}
		}
	}
*/
	return 0;
}

LRESULT CMemberListDlg::OnQueryGetRealname(WPARAM wParam, LPARAM lParam)
{
	TCHAR* szSource = (TCHAR*)lParam;
	if (!szSource)
		return -1;

//	extern CParser gParser;
	CString strInfo(szSource);
//	CString strVersion;
//	CString strIP;
//	gParser.CopyBuffer(szSource);
//	gParser.SetLeftToken('`');
//	gParser.GetValueRightToken(strVersion, '@');
//	gParser.GetValueRightToken(strIP, '`');
//	strInfo.Format("%s @%s", strVersion, strIP);
	m_lcMember.SetItemText(m_nIndex, 1, strInfo);
//	CString strNick = m_lcMember.GetItemText(m_nIndex, 0);
//	m_strMessage = strNick + "=" + strInfo;
//	UpdateData(FALSE);
	return 0;
}

LRESULT CMemberListDlg::OnQueryNoMatches(WPARAM wParam, LPARAM lParam)
{
	m_strMessage.LoadString(IDS_QUERY_NO_MATCH);
	SetDlgItemText(IDC_STATIC_MESSAGE, m_strMessage);
	return 0;
}
