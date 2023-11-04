// UC2Doc.cpp : implementation of the CUC2Doc class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "UC2.h"

#include "UC2Doc.h"
#include "UC2View.h"
#include "MainFrm.h"
#include "Parser.h"
#include "ResMan.h"
#include "Stage.h"
#include "TileMap.h"
#include "LoginDlg.h"
#include "Actor.h"
#include "EditSend.h"
#include "UC2Panel.h"
#include "UC2History.h"
#include "PSJoinChannel.h"
#include "MemberListDlg.h"
#include "ProgressDlg.h"
#include "CloseDlg.h"
#ifdef _MALL
#include "DlgPDA.h"
#include "DlgAni.h"
#endif
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CParser	gParser(1024*4);	// to be used as an extern variable in other files
CResMan	gResMan;

int		GetClientVersion()
{
	return CLIENT_VERSION;
}

const int MAX_SEND_CHAR=256;
const CSize DEFAULT_TILE_SIZE(64, 32);
const CSize DEFAULT_VIEW_SIZE(630, 368);	// (640, 384);

#ifdef _MALL
LPCTSTR	UNICHAT_TITLE(_T("WoW - QuarterView "));	// M@ll
#else
LPCTSTR	UNICHAT_TITLE(_T("UniChat 2 "));
#endif
//LPCTSTR	USSC_NAME(_T("[u2/ussc]"));
//char*	USSC_PASSWORD = _T("qweqwe");

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc

IMPLEMENT_DYNCREATE(CUC2Doc, CDocument)

BEGIN_MESSAGE_MAP(CUC2Doc, CDocument)
	//{{AFX_MSG_MAP(CUC2Doc)
	ON_COMMAND(ID_VIEW_PAUSE, OnViewPause)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE, OnUpdateViewPause)
	ON_COMMAND(ID_VIEW_DEMO, OnViewDemo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEMO, OnUpdateViewDemo)
	ON_COMMAND(ID_CONNECT_SYNC, OnConnectSync)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_BTN_CREATE, OnBtnCreate)
	ON_UPDATE_COMMAND_UI(IDC_BTN_CREATE, OnUpdateBtnCreate)
	ON_COMMAND(IDC_BTN_ROOM, OnBtnRoom)
	ON_UPDATE_COMMAND_UI(IDC_BTN_ROOM, OnUpdateBtnRoom)
	ON_COMMAND(IDC_BTN_MEMBER, OnBtnMember)
	ON_UPDATE_COMMAND_UI(IDC_BTN_MEMBER, OnUpdateBtnMember)
	ON_COMMAND(IDC_BTN_SOUND, OnBtnSound)
	ON_UPDATE_COMMAND_UI(IDC_BTN_SOUND, OnUpdateBtnSound)
	ON_COMMAND(IDC_BTN_HISTORY, OnBtnHistory)
	ON_UPDATE_COMMAND_UI(IDC_BTN_HISTORY, OnUpdateBtnHistory)
	ON_COMMAND(IDC_BTN_QUIT, OnBtnQuit)
	ON_UPDATE_COMMAND_UI(IDC_BTN_QUIT, OnUpdateBtnQuit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc construction/destruction

CUC2Doc::CUC2Doc()
{
	TRACE0("CUC2Doc::CUC2Doc()\n");
	m_pStage	= NULL;
	m_bSound	= TRUE;
	m_bHPanel	= FALSE;
	m_wUC2Mode	= UC2MODE_OFFLINE;
	m_pSocket	= NULL;
	m_pChannel	= NULL;
	m_wSavedState = AS_STAND | DA_BR;
}

CUC2Doc::~CUC2Doc()
{
	TRACE0("CUC2Doc::~CUC2Doc()\n");
	if (m_pStage)
	{
		EndAnimation();
		delete m_pStage;
	}
	if (m_pSocket)
	{
		TRACE0("~CUC2Doc - Destroying m_pSocket\n");
		delete m_pSocket;
	}
}

CUC2View* CUC2Doc::GetUC2View()
{
	POSITION pos = GetFirstViewPosition();
	ASSERT(pos);
	CUC2View* pView = (CUC2View*)GetNextView(pos);
	ASSERT(pView);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CUC2View)));
	return pView;
}

void CUC2Doc::DeleteContents() 
{
	TRACE0("CUC2Doc::DeleteContents()\n");
	Disconnect();

//	if (m_pScript)
//	{
//		TRACE0("~CUC2Doc - Destroying m_pScript\n");
//		if (m_pScript->IsPlaying())
//			m_pScript->Stop();
//		delete m_pScript;
//		m_pScript = NULL;
//	}
#ifndef _MALL
	if (IsDemo())
	{
		AfxMessageBox(IDS_TURNING_OFF_DEMO);
		SetUC2Mode(UC2MODE_OFFLINE);
		Wait(1000);
	}
#endif

	if (m_pStage)
	{
		TRACE0("~CUC2Doc - Destroying m_pStage\n");
		delete m_pStage;
		m_pStage = NULL;
	}

	SetModifiedFlag(FALSE);
	CDocument::DeleteContents();
}

BOOL CUC2Doc::OnNewDocument()
{
	TRACE0("CUC2Doc::OnNewDocument()\n");
	EndAnimation();
	if (!CDocument::OnNewDocument())
		return FALSE;

	CreateNewStage();

	return TRUE;
}

BOOL CUC2Doc::CreateNewStage()
{
    CUC2View* pView = GetUC2View();
    ASSERT(pView);

	if (m_pStage)
	{
		m_pStage->DeleteStage();
		m_pStage->ClearFilename();
	}
	else
	{
		m_pStage = new CStage;
		m_pStage->Initialize(pView);
	}

	CTileMap* pTM = m_pStage->GetTileMap();
	CSize szT	= pTM ? pTM->GetTileSize() : DEFAULT_TILE_SIZE;
	CSize szScr	= pTM ? pTM->GetScreenSize() : DEFAULT_VIEW_SIZE;

	if (!m_pStage->CreateStage(szT, szScr))
		return FALSE;
/*
	CString strSID;
	CUC2App* pApp = (CUC2App*)AfxGetApp();
	pApp->RegGetLastStageID(strSID);
	// Just display the last stage (not connected yet)
	// *gResMan.GetStageName(0) is the fist UniChat MUD stage
	LoadStage(strSID.IsEmpty() ? *gResMan.GetStageName(0) : strSID);
*/
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc serialization

void CUC2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc diagnostics

#ifdef _DEBUG
void CUC2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUC2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc commands

void CUC2Doc::LoadStage(LPCTSTR szStageID)
{
	TRACE("CUC2Doc::LoadStage(%s)\n", szStageID);
	EndAnimation();
	BeginWaitCursor();

	CActor* pActor = m_pStage->GetThisActor();
	if (pActor)
		m_wSavedState = pActor->GetState();	// Save direction at previous stage

	// Get the file for szStageID from the host

	if (m_pStage->Load(szStageID))
	{
	// <Testing...
//		m_pStage->CreateActor(0, CPoint(5, 12), TRUE, wState, TRUE);//(nChar%4 == 0));
//		pActor = m_pStage->GetThisActor();
//		GetUC2View()->SetActor(pActor);
	// Testing>
		GetUC2View()->NewStageLoaded();	// Notify
	}
	EndWaitCursor();
	BeginAnimation();
	UpdateAllViews(NULL);
	SetTitle(*m_pStage->GetTitle());
}

void CUC2Doc::SetTitle(LPCTSTR lpszTitle) 
{
	CString strTitle(UNICHAT_TITLE);
	if (lpszTitle)
		strTitle += lpszTitle;
	CDocument::SetTitle(strTitle);
}

void CUC2Doc::OnViewPause() 
{
	PauseAnimation(!GetPause());
}

void CUC2Doc::OnUpdateViewPause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetPause());
}

void CUC2Doc::EndDemo()
{
	m_bSound = FALSE;
	gResMan.SetMute(!m_bSound);
	if (!m_bSound && m_pStage)
		m_pStage->StopBGM();

	CCloseDlg dlg;
	dlg.m_strMessage.LoadString(IDS_TURNING_OFF_DEMO);
	if (dlg.DoModal() != IDOK)
		return;
	SetUC2Mode(UC2MODE_OFFLINE);
}

void CUC2Doc::PlayWaveFile(LPCTSTR szFile)
{
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + szFile);
	::sndPlaySound(strFile, SND_ASYNC);
}

//////////////////////////// Create Channel
void CUC2Doc::OnBtnCreate()
{
	TRACE("CUC2Doc::OnBtnCreate()\n");

#ifdef _MALL
	if (IsInChannel())
	{
		CMemberListDlg dlgML;
		dlgML.SetPPChannel(this, 0, m_strStageName);
		dlgML.DoModal();
	}
	else
	{
		JoinChannel();
	}
#else
	if (IsDemo())
	{
		EndDemo();
		return;
	}
	JoinChannel();
#endif
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();
}

void CUC2Doc::OnUpdateBtnCreate(CCmdUI* pCmdUI)
{
#ifndef _MALL	// Shopping Cart
	pCmdUI->Enable((BOOL)m_pStage);
#endif
}

//////////////////////////// Rooms List
void CUC2Doc::OnBtnRoom()
{
#ifdef _MALL	// Shopping Cart
	CString strTitle;
	strTitle.LoadString(IDS_JOIN_CHANNEL_TITLE);
	CPSJoinChannel	psjc(this, PS_JOIN_PAGE, strTitle);	// List Only
	psjc.DoModal();
#else
	ListChannels();
#endif
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();
// Testing
//	LoadStage("preview");
}

void CUC2Doc::OnUpdateBtnRoom(CCmdUI* pCmdUI)
{
#ifndef _MALL	// Payment Info
	pCmdUI->Enable((BOOL)m_pStage);
#endif
}

//////////////////////////// Members List
void CUC2Doc::OnBtnMember()
{
#ifdef _MALL	// Payment Info
	CString strTitle;
	strTitle.LoadString(IDS_JOIN_CHANNEL_TITLE);
	CPSJoinChannel	psjc(this, PS_CREATE_PAGE, strTitle);	// List Only
	psjc.DoModal();
#else
	CMemberListDlg dlgML;
	dlgML.SetPPChannel(this, 0, m_strStageName);
	dlgML.DoModal();
#endif
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();
}

void CUC2Doc::OnUpdateBtnMember(CCmdUI* pCmdUI)
{
#ifndef _MALL	// Payment Info
	pCmdUI->Enable((BOOL)m_pStage);
#endif
}

//////////////////////////// Sound On/Off
void CUC2Doc::OnBtnSound()
{
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();
	m_bSound = !m_bSound;
	gResMan.SetMute(!m_bSound);
	if (!m_bSound && m_pStage)
		m_pStage->StopBGM();
}

void CUC2Doc::OnUpdateBtnSound(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((BOOL)m_bSound);
}

//////////////////////////// History Panel Show/Hide
void CUC2Doc::OnBtnHistory()
{
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();
	m_bHPanel = !m_bHPanel;
	((CMainFrame*)AfxGetMainWnd())->ShowHistoryPanel(m_bHPanel);
}

void CUC2Doc::OnUpdateBtnHistory(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bHPanel);
}

//////////////////////////// Quit
void CUC2Doc::OnBtnQuit()
{
	CEditSend* pES = GetEditSend();
	if (pES)
		pES->SetFocus();

	if (IsInChannel())
	{
		LeaveChannel();	// delete m_pChannel
		CCloseDlg dlg;
		dlg.m_strMessage.LoadString(IDS_CHANNEL_OUT);
		if (dlg.DoModal() == IDOK)
		{
			CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
			pMF->PostMessage(WM_CLOSE);
		}
	}
	else
	{
		CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
		pMF->PostMessage(WM_CLOSE);
	}
}

void CUC2Doc::OnUpdateBtnQuit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)m_pStage);
}

////////////////////////////////////////////////////////////////////////////

CEditSend* CUC2Doc::GetEditSend() const
{
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMF);
	CUC2Panel* pPanel = pMF->GetPanel();
	return (pPanel ? pPanel->GetEditSend() : NULL);
}

//CEditHistory* CUC2Doc::GetEditHistory() const
CEdit* CUC2Doc::GetEditHistory() const
{
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMF);
	CUC2History* pHPanel = pMF->GetHistoryPanel();
	return (pHPanel ? pHPanel->GetEditHistory() : NULL);
}

// Display message in CChatView
void CUC2Doc::DisplayText(LPCTSTR lpszText)
{
//	CEditHistory* pEdit = GetEditHistory();
	CEdit* pEdit = GetEditHistory();
	if (!pEdit)
		return;
	int count = pEdit->GetLineCount();
/* // First Line Deletion Scheme: Flickering Problem
	if (count > MAX_CHAT_LINES)
	{
		len = pEdit->LineLength(0);
		pEdit->SetSel(0, len+2);		// remove the first line
		pEdit->ReplaceSel(_T(""));
		TRACE("CChatView::Message() removed %d chars\n", len+2);
	}
*/
	if (count > 1000)	// MAX_CHAT_LINES
	{
		// Save the whole text
		pEdit->SetSel(0, -1);		// remove the whole lines
		pEdit->ReplaceSel(_T(""));
	}
	CString strAdd(lpszText);
	strAdd += _T("\r\n");
	int len = pEdit->GetWindowTextLength();
	pEdit->SetSel(len, len);		// starting position, ending position
// "tortoise:...........................\n" halts the system
	pEdit->ReplaceSel(strAdd);
}

void CUC2Doc::ClearHistory()
{
//	CEditHistory* pEdit = GetEditHistory();
	CEdit* pEdit = GetEditHistory();
	if (pEdit)
	{
		pEdit->SetSel(0, -1);		// select all
		pEdit->ReplaceSel(_T(""));
	}
}

// Demo
long CUC2Doc::Wait(const DWORD dwInterval)
{
	MSG		msg;
	long	lCount=0L;
	DWORD	dwLastTick = ::GetTickCount();
	CUC2App* pApp = (CUC2App*)AfxGetApp();
	while ((m_wUC2Mode & UC2MODE_DEMO) &&
			((::GetTickCount() - dwLastTick) < dwInterval))
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!::GetMessage(&msg, NULL, 0, 0))
			{
				m_wUC2Mode = UC2MODE_OFFLINE;
				::PostQuitMessage(0);
				return -1;
			}
			::TranslateMessage(&msg); 
			::DispatchMessage(&msg);
		}
		pApp->OnIdle(lCount++);
	}
	return lCount;
}

void CUC2Doc::OnUpdateViewDemo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(IsDemo());
}

CActor* CUC2Doc::GetThisActor() const
{
	ASSERT(m_pStage);
	return m_pStage->GetThisActor();
}

//////////////////////////////////////////////////////////////////////////
// ChatSock API
BOOL CUC2Doc::IsConnected()
{
	return (m_pSocket && m_pSocket->FConnected());
}

BOOL CUC2Doc::IsInChannel()
{
	return (m_pChannel && m_pChannel->FInChannel());
}

// Send text into opened channel
// 1. To send text chat data
// called in CEditSend::OnChar
BOOL CUC2Doc::SendText(LPCTSTR szText, const BOOL bWhisper)
{
	if (!m_pStage)
		return FALSE;
	CActor* pTA = m_pStage->GetThisActor();
	if (!pTA)
	{
		TRACE("CStage: This Actor not found!\n");
		return FALSE;
	}

	// Truncate exceeding characters
	char szTemp[MAX_SEND_CHAR+1];
	LPCSTR pSend = szText;		// pointer to the text to send
	int len = lstrlen(szText);
	if (len > MAX_SEND_CHAR)
	{
		::CopyMemory(szTemp, szText, len);
		szTemp[len] = 0;
		pSend = szTemp;
	}

	CString strOut(m_strNick.IsEmpty() ? pSend : m_strNick + _T(":") + pSend);
	pTA->m_mi.SetBubbleKind(pTA->m_mi.GetSex());	// Yello
	pTA->Chat(strOut);			// Later, consider DBCS...
//	if (pTA->IsVoice())
//		GetView()->ChatVoice(szText);
	DisplayText(strOut);
	return (m_pChannel ? m_pChannel->FSendAnsiText((char*)pSend) : FALSE);
}

// Send whisper message to
BOOL CUC2Doc::WhisperTo(CActor* pA, LPCTSTR szText)
{
	if (!IsInChannel())
		return FALSE;
	ASSERT(pA);
	PICS_MEMBER pM = pA->GetMember();
	if (!pM)
		return FALSE;
	CString strText(szText);
	int len = strText.GetLength();
	BOOL bRes = m_pChannel->FWhisperTo(pM, strText.GetBuffer(len));
	pM->Release();

	// Show whisper bubble only in this (sender's) client
	if (!m_pStage)
		return FALSE;
	CActor* pTA = m_pStage->GetThisActor();
	if (pTA)
	{
		pTA->m_mi.SetBubbleKind(2);	// Green
		pTA->Chat(strText);
	}
	return bRes;
}

// Send State or Action Command
void CUC2Doc::SendCommand(const int nCmd)
{
	if (!m_pStage)
		return;

	CUC2View* pView = GetUC2View();

	if (nCmd == CMD_PUNCH)
	{
		if (!pView->PunchAvailable())
			return;
		pView->SaveLastHitTick();
	}

	CActor* pMe = m_pStage->GetThisActor();
	if (!pMe)
	{
		TRACE0("CUC2Doc::SendCommand - GetThisActor() failed\n");
		return;
	}
	// If we use this scheme, ActionQueue in CActor is no more used.
	if (pMe->IsMoving())	// don't accept continuous move commands
	{
		TRACE0("->");
		return;
	}

//	CTileMap* pTM = m_pStage->GetTileMap();
//	CPoint ptTID(pTM->GetNearestTileIndex(pMe->GetEarthPoint()));
	CPoint ptTID(pMe->m_mi.GetTileID());
	CString	strCmd;
	// Get state before action!
	strCmd.Format("%c`%d`(%d,%d)`%d`", UC2_SIGN_CHAR,
					nCmd, ptTID.x, ptTID.y, pMe->GetState());
	if (nCmd == CMD_PUNCH)
	{
		CActor* pFA = m_pStage->GetFrontActor();
		if (pFA)
		{
			// Show action in this machine immediately...
			pMe->Act(nCmd);
			pFA->Act(CMD_BEATEN);
			strCmd += *pFA->GetNick();
			strCmd += '`';
			SendData(strCmd);
			return;
		}
	}
	pMe->Act(nCmd);
	SendData(strCmd);
}

void CUC2Doc::SendMoveCommand(const int nCmd)
{
	if (!m_pStage)
		return;
	CActor* pMe = m_pStage->GetThisActor();
	if (!pMe)
	{
		TRACE0("CUC2Doc::SendCommand - GetThisActor() failed\n");
		return;
	}
	// If we use this scheme, ActionQueue in CActor is no more used.
	if (pMe->IsMoving())	// don't accept continuous move commands
	{
		TRACE0("->");
		return;
	}
//	CTileMap* pTM = m_pStage->GetTileMap();
//	CPoint ptTID(pTM->GetNearestTileIndex(pMe->GetEarthPoint()));
	CPoint ptTID(pMe->m_mi.GetTileID());
	CString	str;
	str.Format("%c`%d`(%d,%d)`%d`", UC2_SIGN_CHAR,
				nCmd, ptTID.x, ptTID.y, pMe->GetState());
	CString* pStrExit = m_pStage->ActorMove(pMe, nCmd == CMD_MOVEF);	// Forward or Backward
	SendData(str);
	if (pStrExit)
	{
		JoinChannel(*pStrExit);
	}
}

// Send data into an opened channel
// To let all the members in the channel know
// 1. To broadcast my entry in the channel I just joined
// 2. To send command data (behaviors selected)
BOOL CUC2Doc::SendData(LPCTSTR szText)
{
	if (!IsInChannel())
		return FALSE;
	DWORD len = lstrlen(szText) + 1;
	return m_pChannel->FSendData((LPBYTE)szText, len);
}

/////////////////////////////////////////////////////////////////////////
// ChatSock Message Handler: coming from CMainFrame
//
// Since Document cannot receive WM_COMMAND message
// Frame window will call this function for us...
// typedef	IChatSocketFactory*	PICS_FACTORY;
// typedef	IChatSocket*		PICS;
// typedef	ICSChannel*			PICS_CHANNEL;
// typedef	ICSMember*			PICS_MEMBER;
// typedef	ICSQuery*			PICS_QUERY;
// typedef	ICSProperty*		PICS_PROPERTY;
// typedef	ICSPrivateMsg*		PICS_PRIVMSG;
// typedef	ICSInvitation*		PICS_INVITATION;
//
// Typical sequence of commands from ChatSock
// 1. CSMSG_TYPE_ADDCHANNEL
// 2. CSMSG_TYPE_ADDMEMBER ...
// 3. CSMSG_TYPE_PRIVATEMSG
// 4. CSMSG_TYPE_GOTMEMLIST
// 5. CSMSG_TYPE_TEXT_A ...
// 6. CSMSG_TYPE_DELMEMBER ...
// 7. CSMSG_TYPE_DELCHANNEL

CActor*	CUC2Doc::GetActor(PICS_MEMBER pMem) const
{
	ASSERT(m_pStage);
	return m_pStage->GetActor(pMem);
}

// Load Stage on ADDCHANNEL
LRESULT CUC2Doc::OnCsAddChannel(WPARAM wParam, LPARAM lParam)
{
	PICS_CHANNEL picsChannel = (PICS_CHANNEL)lParam;	// ICSChannel*
	TRACE("CUC2Doc::OnCsAddChannel - SetChannel(%lx)\n", picsChannel);
	SetChannel(picsChannel);	// Don't Release pC here.
	picsChannel->Release();

	char* pszChName = m_pChannel->SzName();
	if (!pszChName)
		return -1;

	ClearHistory();

	CString strMsg;
//	CString strStageID(pszChName);	// "[u2/0000abcd]00" or "[p2/0000abcd]00"
//	if (gResMan.ExtractStageID(strStageID))	// "0000abcd"
	if (gResMan.GetStageType(pszChName) >= ST_MUD)
	{
//		LoadStage(strStageID);
		AfxFormatString1(strMsg, IDS_JOINED_CHANNEL, pszChName);
	//	GetView()->ChatVoice(strMsg);
		DisplayText(strMsg);
	}
	else
	{
		AfxFormatString1(strMsg, IDS_INVALID_CHANNEL_NAME, pszChName);
		AfxMessageBox(strMsg);
	}
	return 0;
}

// When I enter a channel, I receive member info via Private message
LRESULT CUC2Doc::OnCsPrivateMsg(WPARAM wParam, LPARAM lParam)
{
	PICS_PRIVMSG picsPrivMsg = (PICS_PRIVMSG)lParam;	// ICSPrivateMsg*
	ASSERT(picsPrivMsg);
	CS_PRIVMSG pm;
	if (FAILED(picsPrivMsg->HrGetMsg(&pm)))
	{
		TRACE("picsPrivMsg->HrGetMsg() failed!\n");
		picsPrivMsg->Release();
		return FALSE;
	}
	CString strData;
	if (pm.fText)
	{
		if (pm.fAnsi)
		{
			TRACE0("CSMSG_CMD_PRIVATEMSG - not ANSI\n");
			picsPrivMsg->Release();
			AfxFormatString1(strData, IDS_PRIVATE_MESSAGE, (CHAR*)pm.pbData);
			DisplayText(strData);
			return FALSE;
		}
	}
	else	// binary
	{
		TRACE("Private MSG: binary\n");
		gParser.CopyBuffer((CHAR*)pm.pbData);
		char c;
		gParser.GetValueRightToken(c, UC2TOKEN);
		if (c == UC2_SIGN_CHAR)
		{
			char* szNickFrom;
			BOOL bAnsi;
			picsPrivMsg->HrGetMsgSender((BYTE**)&szNickFrom, &bAnsi);
			PICS_MEMBER pM=NULL;
			if (szNickFrom && m_pChannel)
			{
				PICS_CHANNEL picsChannel = m_pChannel->PChannel();
				ASSERT(picsChannel);
				picsChannel->HrGetMemberFromNameA(szNickFrom, &pM);
				picsChannel->Release();

				int nCmd;
				strData = gParser.GetValueRightToken(nCmd, UC2TOKEN);
				if (nCmd == CMD_MEMBER_INFO)	// Add Actor
				{
					CActor* pA = GetActor(pM);	// Find corresponding Actor object
					TRACE("\tOnCsPrivateMsg - CMD_MEMBER_INFO: %lx\n", pM);
					if (!pA)	// Not Found: New User
					{
						CMemberInfo	mi;
						mi.SetMember(pM);
						if (mi.SetMemberInfo(strData) && m_pStage)
						{	// Create the actor who was already in the channel
							pA = m_pStage->CreateActor(mi, m_pChannel->FIsMemberMe(pM));
						}
					}
				}
			}
			if (pM)
				pM->Release();
		}
	}
	picsPrivMsg->Release();
	return 0;
}

LRESULT CUC2Doc::OnCsQueryData(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CUC2Doc::OnCsInvite(WPARAM wParam, LPARAM lParam)
{
	PICS_INVITATION picsInvite = (PICS_INVITATION)lParam;
	ASSERT(picsInvite);
	BYTE*	pbName;
	BYTE*	pbSender;
	BOOL	bAnsi;
	CHAR*	szChannel;
	CHAR*	szFrom;

	if (FAILED(picsInvite->HrGetChannelName(&pbName, &bAnsi)))
	{
		picsInvite->Release();
		return FALSE;
	}

	if (bAnsi)
	{
		szChannel = (CHAR*)pbName;
	}

	if (FAILED(picsInvite->HrGetSender(&pbSender, &bAnsi)))
	{
		picsInvite->Release();
		return FALSE;
	}

	if (bAnsi)
	{
		szFrom = (CHAR*)pbSender;
	}

	CString strMsg;
	AfxFormatString2(strMsg, IDS_INVITATION, szFrom, szChannel);
//	if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
//	{	// Show Join Channels Dialog
//		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COMMAND, (WPARAM)IDC_BTN_CREATE, (LPARAM)0);
//	}
	DisplayText(strMsg);
	picsInvite->Release();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Channel thread

LRESULT CUC2Doc::OnCsGotMemList(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// We only respond to the ADDMEMBER message after GOTMEMLIST
// 1. On ADDMEMBER myself
//			SendData => Inform myself to this channel I just joined
// 2. On ADDMEMBER new member in the course of chat
//			SendPrivData => Inform myself only to this new member
LRESULT CUC2Doc::OnCsAddMember(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_pChannel);
	PICS_MEMBER pM = (PICS_MEMBER)lParam;
	ASSERT(pM);
	CString strData;
	CString str;
	CHAR* szName = m_pChannel->SzMemName(pM);

	//AddMember(picsMember);
	AfxFormatString1(str, IDS_MEMBER_ENTRY, szName);
	DisplayText(str);
	// Member info
	if (m_pChannel->FGotMemList())	// After
	{
		if (m_pChannel->FIsMemberMe(pM))	// Myself: Broadcast my info
		{
			// Set ChatID again in case this member has logged in with a backup id
			m_strNick = szName;
			// Load my actor
			CMemberInfo	mi;
			mi.LoadMyInfo();

			PICS_CHANNEL pC = m_pChannel->PChannel();
			ASSERT(pC);
			PICS_MEMBER pM;
			pC->HrGetMe(&pM);
			pC->Release();
			ASSERT(pM);
			mi.SetMember(pM);	// AddRef()
			pM->Release();
			mi.SetVersion(GetClientVersion());	// myself
			mi.SetState(m_wSavedState);

			ASSERT(m_pStage);
			CActor* pA = m_pStage->CreateActor(mi, TRUE);	// myself
//			CActor* pA = GetActor(pM);
			if (pA)
			{
				strData.Format("%c`%d`", UC2_SIGN_CHAR, CMD_MEMBER_INFO);
				pA->m_mi.GetMemberInfo(str);
				strData += str;
				TRACE("OnCsAddMember:[SendData:Broadcast myself]%s\n", strData);
				SendData(strData);	// Broadcast in the channel
			}
			else
			{
				TRACE0("CUC2Doc::OnCsAddMember - Creation Failure!\n");
			}
		}
		else	// Inform myself to the new member
		{
			CActor* pA = GetThisActor();
			if (pA)
			{
				strData.Format("%c`%d`", UC2_SIGN_CHAR, CMD_MEMBER_INFO);
				CMemberInfo mi;
				pA->GetMemberInfo(mi);	// Get member info from this actor
				mi.GetMemberInfo(str);	// express member info in string
				strData += str;
				DWORD dwcb = strData.GetLength() + 1;
				TRACE("OnCsAddMember:[PrivData:Inform myself]%s\n", strData);
				m_pSocket->FSendPrivData(szName, (BYTE*)strData.GetBuffer(dwcb-1), dwcb);
			}
			else
			{
				TRACE0("CUC2Doc::OnCsAddMember - Oops!, I'm not created yet?\n");
			}
		}
	}
	pM->Release();
	return 0;
}

LRESULT CUC2Doc::OnCsDelMember(WPARAM wParam, LPARAM lParam)
{
	PCS_MSGMEMBER pMsg = (PCS_MSGMEMBER)lParam;
	PICS_MEMBER pM = pMsg->picsMember;
	ASSERT(pM);
	pM->AddRef();

	if (m_pChannel)
	{
		CHAR* szName = m_pChannel->SzMemName(pM);
		//DelMember(picsMember);
		CString str;
		AfxFormatString1(str, IDS_MEMBER_EXIT, szName);
		DisplayText(str);

		// Delete the member
		CActor* pA = GetActor(pM);

		if (pMsg->picsMemSrc)
		{
			PICS_MEMBER pMemKick = pMsg->picsMemSrc;
			// Someone was kicked..
			// If the member being kicked was US.. notify the user
//			if (m_pChannel->FIsMemberMe(pM))	// This doesn't work since the member is already kicked out.
			CString strKickReason;
			CHAR* szKicker = m_pChannel->SzMemName(pMemKick);
			// Also save the reason, if any.. and only if its ANSI
			if (pMsg->pvReason && pMsg->fAnsi)
			{
				if (szKicker && pMsg->pvReason)
				{
					CString strFmt;
					strFmt.LoadString(IDS_KICKOFF_REASON);
					wsprintf(strKickReason.GetBuffer(1024),
							strFmt, szKicker, szName, (CHAR*)pMsg->pvReason);
					strKickReason.ReleaseBuffer();
					DisplayText(strKickReason);
					if (pA == GetThisActor())
					{
						AfxMessageBox(strKickReason);
					}
				}
			}
		}

		if (pA)
		{
			m_pStage->DeleteActor(pA);
//			CRect rc;
//			m_pStage->GetRect(rc);
//			GetView()->AddDirtyRegion(&rc);
//			GetView()->RenderAndDrawDirtyList();	// Erase
		}
	}
	pM->Release();
	return 0;
}

LRESULT CUC2Doc::OnCsDelChannel(WPARAM wParam, LPARAM lParam)
{
	SetTitle(NULL);
	PICS_CHANNEL pC = (PICS_CHANNEL)lParam;
	ASSERT(pC);
	TRACE("OnCsDelChannel\n");
	pC->Release();
	return 0;
}

LRESULT CUC2Doc::OnCsModeMember(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CUC2Doc::OnCsModeChannel(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// On TEXT_A - Just a text conversation
// 1. Find the actor object corresponding to the MIC member
// 2. Show the text through this actor
LRESULT CUC2Doc::OnCsTextA(WPARAM wParam, LPARAM lParam)
{
	PCS_MSG pMsg = (PCS_MSG)lParam;
	// Obtain the sender's name
	PICS_MEMBER pM = pMsg->picsFrom;
	ASSERT(m_pChannel);
	// if member is NULL, the message is from the channel
	CHAR* szName = (pM) ? m_pChannel->SzMemName(pM) : m_pChannel->SzName();
	ASSERT(szName);
	// Is this user a Host?
	CString strText;
	if (pM && (pM->HrIsMemberHost() == NOERROR))
		strText = _T("*");
	CString strVoice((LPCSTR)pMsg->pbData);
//	if (StripComicHeader((LPCSTR)pMsg->pbData, strVoice) > 0)
//	{
	strText += szName;
	strText += _T(":");
	strText += strVoice;
	DisplayText(strText);

	if (!pM)
		return 0;

	if (pM->HrIsMemberIgnored() == NOERROR)
		return 0;
	CActor* pA = GetActor(pM);
	if (pA)
	{
		if (strText.GetLength() > MAX_SEND_CHAR)
		{
//			strText.GetBufferSetLength(MAX_SEND_CHAR);
			strText.ReleaseBuffer(MAX_SEND_CHAR);
		}
		pA->Chat(strText);		// Later, consider DBCS...
//		if (pA->IsVoice())
//			GetView()->ChatVoice(strVoice, pA->GetGender());
	}
//	}
	return 0;
}

// 1. Actors' command data
LRESULT CUC2Doc::OnCsData(WPARAM wParam, LPARAM lParam)
{
	PCS_MSG pMsg = (PCS_MSG)lParam;
	// Obtain the sender's name
	PICS_MEMBER pM = pMsg->picsFrom;

	if (pM->HrIsMemberIgnored() == NOERROR)
		return 0;
	TRACE0("Data: binary\n");
	int len = (int)pMsg->dwcbData;
	char* szBuf = new char[len+2];	// +1 for safety
	::CopyMemory(szBuf, (LPBYTE)pMsg->pbData, len);
	szBuf[len] = NULL;
	gParser.CopyBuffer(szBuf);
	char c;
	gParser.GetValueRightToken(c, UC2TOKEN);
	if (c == UC2_SIGN_CHAR)
	{
		CActor* pA = GetActor(pM);	// Sender: Find corresponding Actor object
		int nCmd;
		CString strData(gParser.GetValueRightToken(nCmd, UC2TOKEN));
		if (nCmd == CMD_MEMBER_INFO)
		{
			TRACE("CUC2Doc::OnCsData - CMD_MEMBER_INFO: %lx\n", pM);
			if (!pA)	// Not Found: New Member
			{
				CMemberInfo	mi;
				mi.SetMember(pM);
				if (mi.SetMemberInfo(strData) && m_pStage)
				{	// Create the actor who joined this channel
					CActor* pA = m_pStage->CreateActor(mi, m_pChannel->FIsMemberMe(pM));
				}
			}
		}
		else if (nCmd > CMD_MOVE)	// Move or Action
		{							// CMD_ACTION means just repositioning
			TRACE("CUC2Doc::OnCsData - CMD(%d): %lx => ", nCmd, pM);
			if (pA)
			{
				WORD	wState;
				CPoint	ptTID;
				if (gParser.GetValueRightToken(ptTID, UC2TOKEN))
				{
					gParser.GetValueRightToken(wState, UC2TOKEN);
					CTileMap* pTM = m_pStage->GetTileMap();
					CPoint ptC(pTM->GetCenter(ptTID.x, ptTID.y));
					pA->MoveToEarth(ptC);
					pA->SetState(wState, FALSE);	// Adjust Current State
				}
				if (nCmd < CMD_STATE)	// MOVE
					m_pStage->ActorMove(pA, nCmd == CMD_MOVEF);
				else
				{
					pA->Act(nCmd);
					if (nCmd == CMD_PUNCH)
					{
						CString strNickTo;
						if (gParser.GetValueRightToken(strNickTo, UC2TOKEN) &&
							!strNickTo.IsEmpty())
						{
							CActor* pABeaten = m_pStage->GetActor(strNickTo);
							if (pABeaten)
								pABeaten->Act(CMD_BEATEN);
						}
					}
				}
			}
		}
	}
	delete [] szBuf;
	return 0;
}

LRESULT CUC2Doc::OnCsWhisperText(WPARAM wParam, LPARAM lParam)
{
	PCS_MSGWHISPER pMsgW = (PCS_MSGWHISPER)lParam;
	// Obtain the sender's name
	ASSERT(pMsgW);
//	if (pMsg->dwcMem )
	PCS_MSG pMsg = (PCS_MSG)pMsgW->pcsMsg;
	ASSERT(pMsg);
	PICS_MEMBER pM = pMsg->picsFrom;
	ASSERT(m_pChannel);
	// if member is NULL, the message is from the channel
	CHAR* szName = (pM) ? m_pChannel->SzMemName(pM) : m_pChannel->SzName();
	ASSERT(szName);
	// Is this user a Host?
	CString strText;
	CString strVoice((LPCSTR)pMsg->pbData);
	if (pM->HrIsMemberHost() == NOERROR)
		strText = _T("*");
	strText += szName;
	strText += _T("=>");
	strText += strVoice;
	DisplayText(strText);

	if (!pM)
		return 0;
	if (pM->HrIsMemberIgnored() == NOERROR)	// This member is ignored...
		return 0;

	CActor* pA = GetActor(pM);
	if (pA)
	{
		if (strText.GetLength() > MAX_SEND_CHAR)
		{
//			strText.GetBufferSetLength(MAX_SEND_CHAR);
			strText.ReleaseBuffer(MAX_SEND_CHAR);
		}
		pA->m_mi.SetBubbleKind(2);	// Green for Whisper
		pA->Chat(strText);		// Later, consider DBCS...
//		if (pA->IsVoice())
//			GetView()->ChatVoice(strVoice, pA->GetGender());
	}
	return 0;
}

LRESULT CUC2Doc::OnCsWhisperData(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CUC2Doc::OnCsNewTopic(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CUC2Doc::OnCsNewNick(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BOOL CUC2Doc::SetChannel(PICS_CHANNEL picsChannel)
{
	// We got a new channel. Save it.
	ASSERT(m_pChannel == NULL);
	m_pChannel = new CUC2Channel(AfxGetMainWnd()->GetSafeHwnd());
	ASSERT(m_pChannel);
	// Save the ICSChannel pointer
	if (m_pChannel->FInit(picsChannel))	// PICS_CHANNEL
	{
		CString strTitle(m_strNick);
		strTitle += _T(":");
		strTitle += m_pChannel->SzName();
		SetTitle(strTitle);
		TRACE("You are now in channel %s\n", m_pChannel->SzName());
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUC2Doc commands

BOOL CUC2Doc::Connect()
{
	// Create a non-signaled, manual-reset event to synchronize destruction
//	m_pExitEvent = new CEvent(FALSE, TRUE);
	if (m_pSocket)
	{
		if (m_pSocket->FConnected())
		{
			AfxMessageBox("Error: Already connected.");
			return FALSE;
		}
		m_pSocket->SetReceiver(AfxGetMainWnd()->GetSafeHwnd());
	}
	else
	{
		m_pSocket = new CUC2Socket(AfxGetMainWnd()->GetSafeHwnd());
	}
	if (!m_pSocket->FInit())	// create a Socket Factory
	{
//		ExitPermitted();
		return FALSE;
	}

	CUC2App* pApp = (CUC2App*)AfxGetApp();
//	pApp->SetPause(TRUE);
//	if (m_pScript && m_pScript->IsPlaying())
//		m_pScript->Stop();

	CLoginDlg LoginDlg(m_pSocket);	// Connection (Login) Dialog
//	LoginDlg.SetDoc(this);
	pApp->RegGetNick(LoginDlg.m_strNickName);
	if (LoginDlg.DoModal() == IDOK)
	{
//		m_timeConnect = CTime::GetCurrentTime();
//		pApp->RegSetServer(ConnDlg.m_strServerIP);
		m_strNick = LoginDlg.m_strNickName;
		pApp->RegSetNick(m_strNick);
		ClearHistory();
		CString strMsg;
		AfxFormatString1(strMsg, IDS_WELCOME_TO_LOBBY, m_strNick);
		DisplayText(strMsg);

//		if (DownloadDataFiles())
//			return FALSE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

// Quit Connection
BOOL CUC2Doc::Disconnect()
{
	if (m_pChannel)
	{
		LeaveChannel();
	}
	if (m_pSocket)
	{
		m_pSocket->SetReceiver(NULL);
		m_pSocket->FDisconnect();
	}
	return TRUE;
}

BOOL CUC2Doc::ListChannels()	// Just list
{
	CMemberInfo mi;
	mi.LoadMyInfo();

	CString strTitle;
	strTitle.LoadString(IDS_JOIN_CHANNEL_TITLE);
	CPSJoinChannel	psjc(this, PS_JOIN_PAGE, strTitle);	// List Only
	psjc.SetMemberInfo(mi);

	if (psjc.DoModal() != IDOK)
	{
		return FALSE;
	}
	return TRUE;
}

void CUC2Doc::LeaveChannel()
{
	TRACE0("CUC2Doc::LeaveChannel()\n");
	m_pChannel->SetReceiver(NULL);	// Don't receive message
	m_pChannel->FLeave();
	delete m_pChannel;
	m_pChannel = NULL;
}

void CUC2Doc::MakeMudChannelInfo(EC_CHANNELINFO& ecInfo)
{
	static CString strTopic;
	strTopic = m_strStageName;
	gResMan.GetStageTitle(strTopic);
	::ZeroMemory(&ecInfo, sizeof(EC_CHANNELINFO));
	ecInfo.szName		= m_strStageName.GetBuffer(m_strStageName.GetLength() + 1);
	ecInfo.dwType		= CS_CHANNEL_PUBLIC;
	ecInfo.szTopic		= strTopic.GetBuffer(strTopic.GetLength() + 1); // UC2MUD_TOPIC;
	ecInfo.szPass		= _T("");
	ecInfo.cUsersMax	= MAX_MEMBERS_IN_CHANNEL;	// limit # of members in a channel
	ecInfo.dwFlags		= CS_CHANNEL_FLAG_MICONLY;
}

void CUC2Doc::OnConnectSync() 
{
	DownloadDataFiles();
}

// need to reload rit?
BOOL CUC2Doc::DownloadDataFiles()
{
	CProgressDlg DownloadDlg;	// Download data files
	DownloadDlg.DoModal();
	if (DownloadDlg.RITModified())
	{
		if (IsDemo())
			EndDemo();
		CCloseDlg dlg;
		dlg.m_strMessage.LoadString(IDS_CLOSE_ON_NEW_RIT);
		if (dlg.DoModal() != IDOK)
			return FALSE;
		CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
		pMF->SetAskBeforeClose(FALSE);
		pMF->PostMessage(WM_CLOSE);
		return TRUE;
	}
	return FALSE;
}

// Join a channel
// Specifying szChannelName means automatic navigation mode (No user inquiry).
BOOL CUC2Doc::JoinChannel(LPCTSTR szChannelName)
{
	if (!IsConnected())	// ON_UPDATE_UI will prevent this
	{
		if (!Connect())
		{
//			AfxMessageBox("Connection Failed!");
			return FALSE;
		}
	}

	EC_CHANNELINFO ecInfo;
	CString strTitle;
	strTitle.LoadString(IDS_JOIN_CHANNEL_TITLE);
	CPSJoinChannel	psjc(this, PS_ALL_PAGES, strTitle);

	if (szChannelName)	// UniChat MUD mode
	{
		m_strStageName = szChannelName;
		gResMan.MakeStageName(m_strStageName, FALSE);	// for MUD

		MakeMudChannelInfo(ecInfo);
	}
	else	// User-creatable channel
	{
		CMemberInfo mi;
		mi.LoadMyInfo();

		psjc.SetMemberInfo(mi);
	//	psjc.SetWizardMode();
		if (psjc.DoModal() != IDOK)
		{
			return FALSE;
		}
		psjc.GetMemberInfo(mi);
		mi.SaveMyInfo();
	
		if (!psjc.GetChannelInfo(ecInfo))	// Navigation mode
			return FALSE;
	}

	CString strMsg;

	HRESULT hr = ::HrVerifyCreateChannelNameA(ecInfo.szName, TRUE, FALSE);	// fMicOnly, fLocal
	if (FAILED(hr))
	{
		AfxFormatString1(strMsg, IDS_INVALID_CHANNEL_NAME, ecInfo.szName);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	if (IsInChannel())
	{
//		if (!szChannelName &&
//			(AfxMessageBox(IDS_LEAVE_THIS_CHANNEL, MB_OKCANCEL) != IDOK))
//			return FALSE;
		LeaveChannel();	// delete m_pChannel
	}
	
	CString strStageID(ecInfo.szName);	// "[u2/0000abcd]00" or "[p2/0000abcd]"
	gResMan.ExtractStageID(strStageID);	// "0000abcd"
	// Fetch strStageID file from the Host Computer
	LoadStage(strStageID);
	if (gResMan.GetStageType(ecInfo.szName) == ST_MUD)
	{
		CUC2App* pApp = (CUC2App*)AfxGetApp();
		pApp->RegSetLastStageID(strStageID);	// Save current Stage ID in the registry
	}

	// Set variables for OnChannelFullRetry()
	m_strStageName = ecInfo.szName;
	ASSERT(m_strStageName.GetLength() > 0);
	m_SNSuffix[0] = '0';	// Initialize
	m_SNSuffix[1] = '1';

	TRACE0("m_pSocket->FCreateJoinChannel(&ecInfo)\n");
	if (!m_pSocket->FCreateJoinChannel(&ecInfo))
	{
		AfxFormatString1(strMsg, IDS_CANNOT_JOIN_CHANNEL, ecInfo.szName);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}

LRESULT CUC2Doc::OnChannelFullRetry(WPARAM wParam, LPARAM lParam)
{
	EC_CHANNELINFO ecInfo;
	MakeMudChannelInfo(ecInfo);

	int n = lstrlen(ecInfo.szName);	// [u2/0000abcd]00
	if (n > 2)
	{
		ecInfo.szName[n-1] = m_SNSuffix[1];
		ecInfo.szName[n-2] = m_SNSuffix[0];
		if (m_SNSuffix[1]++ >= '9')
		{
			m_SNSuffix[1] = '0';
			m_SNSuffix[0]++;
			if (m_SNSuffix[0] > '2')
				return -1;
		}
	}
	TRACE0("m_pSocket->FCreateJoinChannel(&ecInfo)\n");
	if (!m_pSocket->FCreateJoinChannel(&ecInfo))
	{
		CString strMsg;
		AfxFormatString1(strMsg, IDS_CANNOT_JOIN_CHANNEL, ecInfo.szName);
		AfxMessageBox(strMsg);
		return -1;
	}
	return 0;
}

void CUC2Doc::OnViewDemo()
{
	m_wUC2Mode ^= UC2MODE_DEMO;	// Toggle demo bit
	if (!IsDemo() || !m_pStage)
		return;

	if (IsDemo())
	{
		m_bSound = TRUE;
		gResMan.SetMute(!m_bSound);
		if (IsInChannel())
		{
			if (AfxMessageBox(IDS_LEAVE_THIS_CHANNEL, MB_OKCANCEL) != IDOK)
				return;
			LeaveChannel();	// delete m_pChannel
		}
	}

	while (IsDemo())
	{
#ifdef _MALL
#ifdef _ENGLISH
#include "DemoMallE.cpp"
#else
#include "DemoMall.cpp"
#endif
	OnBtnCreate();
#else
#include "Demo.cpp"
#endif
	}
}

#ifdef	_MALL
void CUC2Doc::ShowMapDemo()
{
	CDlgAni	ani("wowmap.bmp", NULL);
	ani.SetAutoDestroy(TRUE);
	ani.SetTimeAttr(1000, 11000);
	ani.SetRelPosition(250, 50);
	ani.DoModal();
}

void CUC2Doc::ShowIMDemo()
{
	CDlgAni	aniB("wowblist.bmp", NULL);
	aniB.SetAutoDestroy(TRUE);
	aniB.SetTimeAttr(1000, 8000);
	aniB.SetRelPosition(550, 100);
	aniB.DoModal();
	CDlgAni	ani("imwin.bmp", "imani.bmp", 9);
	ani.SetAutoDestroy(TRUE);
	ani.SetTimeAttr(500, 10000);
	ani.SetRelPosition(250, 40);
	ani.SetLT(9, 50);
	ani.DoModal();
}

void CUC2Doc::ShowTitanicDemo()
{
	PlayWaveFile("titanic.wav");
	CDlgAni	ani("liquidad.bmp", NULL);
	ani.SetAutoDestroy(TRUE);
	ani.SetTimeAttr(1000, 30000L);
	ani.SetRelPosition(400, 10);
	ani.DoModal();
}
#endif