//==========================================================================
//	CUC2Socket
//	CUC2Channel
//
//	(C) Programmed by Kim, Soomin, Mar 23, 1998
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
//	You should not call other thread's functions except simple ones
//	like inline. That can be the cause of the deadlock between a main thread
//	which is just waiting for this thread to terminate. But, ...
//	Do not call a complex function through m_pDoc.
//	But you should AddRef ChatSock objects before posting them with
//	WM_COMMAND, since it's become out of scope and the stack will be
//	destroyed.
//==========================================================================
#include "stdafx.h"
#include <csface.h>
#include "UC2CS.h"
#include "resource.h"

const char* szUC2Socket		= _T("UniChat Socket");		// MessageBox title
const char* szUC2Channel	= _T("UniChat Channel");	// MessageBox title
//--------------------------------------------------------------------------+
// class CUC2Socket
//--------------------------------------------------------------------------+
CUC2Socket::CUC2Socket(const HWND hWnd)
{
	TRACE0("CUC2Socket::CUC2Socket()\n");
	ASSERT(hWnd);
	m_hFrame = hWnd;
	m_hQClient = NULL;
	m_bQueryOK = TRUE;
}

CUC2Socket::~CUC2Socket()
{
	TRACE0("CUC2Socket::~CUC2Socket()\n");
}

BOOL CUC2Socket::FOnLogin()
{
	TRACE0("CUC2Socket::FOnLogin() - Connection Successful\n");
	return TRUE;
}

BOOL CUC2Socket::FOnAddChannel(PCS_MSGCHANNEL pMsg)
{
	TRACE0("CUC2Socket::FOnAddChannel\n");
	if (!m_hFrame)
		return FALSE;
	ASSERT(pMsg->picsChannel);		// ICSChannel*
	(pMsg->picsChannel)->AddRef();	// To survive asynchronous messages
	PostMessage(CSMSG_CMD_ADDCHANNEL, 0, (LPARAM)pMsg->picsChannel);
	return TRUE;
}

// Message from the host?
BOOL CUC2Socket::FOnPrivateMsg(PCS_MSGPRIVATE pMsg)
{
	TRACE0("CUC2Socket::FOnPrivateMsg\n");
	if (!m_hFrame)
		return FALSE;
	ASSERT(pMsg->picsPrivMsg);		// ICSPrivateMsg*
	(pMsg->picsPrivMsg)->AddRef();
	PostMessage(CSMSG_CMD_PRIVATEMSG, 0, (LPARAM)pMsg->picsPrivMsg);
	return TRUE;
}

BOOL CUC2Socket::FOnInvite(PCS_MSGINVITE	pcsInvite)
{
	TRACE0("CUC2Socket::FOnInvite\n");
	if (!m_hFrame)
		return FALSE;
	// pcsInvite->picsInvite	// ICSInvitation*
	(pcsInvite->picsInvite)->AddRef();
	PostMessage(CSMSG_CMD_INVITE, 0, (LPARAM)pcsInvite->picsInvite);
	return TRUE;
}

BOOL CUC2Socket::FOnSocketError(HRESULT hr)
{
	CHAR*	szError;

	switch (hr)
	{
	case E_NOTIMPL:						szError = "Not implemented";	break;
	case E_UNEXPECTED:					szError = "An internal error occurred";	break;
	case E_OUTOFMEMORY:					szError = "Ran out of memory";	break;
	case E_INVALIDARG:					szError = "One or more arguments are invalid";	break;
	case E_FAIL:						szError = "Unspecified error";	break;
	case S_FALSE:						szError = "wrong version of chatsock";	break;
	// Generic errors
	case CS_E_VERSION:					szError = "wrong version of chatsock";	break;
	case CS_E_WAIT:						szError = "wait error";	break;
	case CS_E_EVENT:					szError = "event error";	break;
	case CS_E_SZTOOLONG:				szError = "string too long";	break;
	case CS_E_EXITING:					szError = "dll in process of exiting";	break;
	case CS_E_NOTANSI:					szError = "ANSI used instead of Unicode!";	break;
	case CS_E_NOTUNICODE:				szError = "Unicode used instead of Ansi!";	break;
	case CS_E_TOOMUCHDATA:				szError = "data size exceeds max buffer bounds";	break;
	case CS_E_ILLEGAL_CHARS:			szError = "illegal chars in string";	break;
	case CS_E_FIRSTCHAR:				szError = "first char error in IRC";	break;
	// List management errors
	case CS_E_ALREADYINLIST:			szError = "inserted element is already in list";	break;
	case CS_E_NOTINLIST:				szError = "element not found";	break;
	case CS_E_QUEEMPTY:					szError = "no msgs in wait q.";	break;
	// Connection errors
	case CS_E_NOTCONNECTED:				szError = "online operation attempted on an off-line socket";	break;
	case CS_E_WINSOCKDLL:				szError = "could not load WinSock.dll"; break;
	case CS_E_HOSTNOTFOUND:				szError = "server not found by DNS"; break;
	case CS_E_SOCKETCREATE:				szError = "WinSock failure"; break;
	case CS_E_CANTCONNECT:				szError = "can't connect..server down?"; break;
	case CS_E_CANTSEND:					szError = "trouble sending buffer.. usually a WinSock problem"; break;
	case CS_E_TIMEOUT:					szError = "generic timeout"; break;
	case CS_E_NODATA:					szError = "NODATA"; break;
	case CS_E_SOCKETERROR:				szError = "generic WinSock error"; break;
	case CS_E_INVALIDSOCKET:			szError = "operation attempted on bad ICSSocket"; break;
	case CS_E_LOSTCONNECTION:			szError = "connection lost"; break;
	case CS_E_SOCKETCLOSED:				szError = "somebody closed the socket"; break;
	case CS_E_NETWORKDOWN:				szError = "NETWORKDOWN"; break;
	case CS_E_HOSTDROPPEDCONNECTION:	szError = "the host server dropped your connection"; break;
		// catch above error!
	// Login errors
	case CS_E_NOTLOGGEDIN:				szError = "chat operation attempted without logging into server"; break;
	case CS_E_UNKNOWNUSER:				szError = "server does not know you"; break;
	case CS_E_ALIASINUSE:				szError = "somebody else is already using this alias"; break;
	case CS_E_ILLEGALUSER:				szError = "server does not like authenticating you"; break;
	// Channel Errors
	case CS_E_CHANNELCANCEL:			szError = "CHANNELCANCEL"; break;
	case CS_E_CREATEFAIL:				szError = "channel create failed"; break;
	case CS_E_JOINFAIL:					szError = "channel join failed"; break;
	case CS_E_CANCELFAIL:				szError = "CANCELFAIL"; break;
	case CS_E_CHANNELEXISTS:			szError = "channel already exists"; break;
	case CS_E_CHANNELNOTFOUND:			szError = "attempt to join a bogus channel"; break;
	case CS_E_CANTMAKEUNIQUECHANNEL:	szError = "Can't make unique Channel"; break;
	case CS_E_CHANNELFULL:				szError = "room is full"; break;
	case CS_E_ALREADYONCHANNEL:			szError = "you are joining a channel you are already on"; break;
	case CS_E_CLOSE:					szError = "error closing a channel"; break;
	case CS_E_NOTINCHANNEL:				szError = "operation attempted on a channel you are not on"; break;
	case CS_E_TOOMANYCHANNELS:			szError = "server has a limit on # of channels a user can be in at a time"; break;
	case CS_E_INVITEONLYCHANNEL:		szError = "you were not invited to this channel"; break;
	case CS_E_CHANNELBADPASS:			szError = "bad password on the channel"; break;	// "bad password on the channel"
	case CS_E_NOMATCHES:				szError = "No query data.";	break; // On return for query
	default:							szError = "This task cannot be completed.";	break;
	}

	SetQueryOK();
	if (m_hQClient)	// If we have a query client
	{
		::SendMessage(m_hQClient, (hr == CS_E_NOMATCHES) ? CMD_QUERY_NOMATCHES : CMD_QUERY_ERROR, 0, (LPARAM)szError);
		m_hQClient = NULL;
	}
	else
	{
		CString str;
		str.Format("ChatSock ERROR %lx: %s\n", hr, szError);
		if (hr == CS_E_CHANNELFULL)
		{
			PostMessage(CMD_CHANNELFULL_RETRY, 0, 0);
		}
		else
		{
			::MessageBox(NULL, str, szUC2Socket, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		}
	}
	return TRUE;
}

void CUC2Socket::SetLastQueryType(const int nType)
{
	m_LastQType = nType;
	SetQueryOK(FALSE);
	m_iItem = 0;
}

///////////////////////////////////////////////////////////////////////////////////
// Initiates queries

BOOL CUC2Socket::FQueryListAllUsers(char* szFind)
{
	ASSERT(m_pics);

	if (!IsQueryOK())
	{
		CString strMsg;
		strMsg.LoadString(IDS_QUERY_LINE_BUSY);
		::MessageBox(NULL, strMsg, szUC2Socket, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	HRESULT hr = m_pics->HrListAllUsersA(szFind, CSPROP_QUERY_CONTAINS);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	SetLastQueryType(Q_LIST_USERS);
	return TRUE;
}

//	Lists all channels that meet the following criteria:
//	a) the channel name must contain szChannel, and
//	b) the channel must have a number of members within the specified range.
BOOL CUC2Socket::FQueryListChannels(char* szChannel, DWORD dwcMin, DWORD dwcMax)
{
	ASSERT(m_pics);

	if (!IsQueryOK())
	{
		CString strMsg;
		strMsg.LoadString(IDS_QUERY_LINE_BUSY);
		::MessageBox(NULL, strMsg, szUC2Socket, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	HRESULT hr = m_pics->HrListAllChannelsA(dwcMin, dwcMax, szChannel, CSPROP_QUERY_CONTAINS);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	SetLastQueryType(Q_LIST_CHANNELS);
	return TRUE;
}

//	Lists all members in the specified channel.
BOOL CUC2Socket::FQueryMembersInChannel(const DWORD dwID)
{
	ASSERT(m_pics);

	if (!IsQueryOK())
	{
		CString strMsg;
		strMsg.LoadString(IDS_QUERY_LINE_BUSY);
		::MessageBox(NULL, strMsg, szUC2Socket, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	HRESULT hr = m_pics->HrListAllMembersA(dwID);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	SetLastQueryType(Q_CHANNEL_MEMBERS);
	return TRUE;
}

BOOL CUC2Socket::FQueryMembersInChannelName(char* szChannel)
{
	ASSERT(m_pics);

	if (!IsQueryOK())
	{
		CString strMsg;
		strMsg.LoadString(IDS_QUERY_LINE_BUSY);
		::MessageBox(NULL, strMsg, szUC2Socket, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	HRESULT hr = m_pics->HrListAllMembersFromNameA(szChannel);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	SetLastQueryType(Q_CHANNEL_MEMBERS);
	return TRUE;
}

BOOL CUC2Socket::FQueryRealName(char* szNick)
{
	ASSERT(m_pics);

//	if (!IsQueryOK())
//	{
//		CString strMsg;
//		strMsg.LoadString(IDS_QUERY_LINE_BUSY);
//		::MessageBox(NULL, strMsg, szUC2Socket, MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
	HRESULT hr = m_pics->HrGetRealNameA(szNick);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	SetLastQueryType(Q_GET_REALNAME);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////

BOOL CUC2Socket::FParseQueryData(PCS_PROPERTY pcsProp)
{
	BOOL	fRet = TRUE;
	ASSERT(pcsProp);
	if (!pcsProp->picsProperty)
	{
		// Null Property pointers indicate that
		// this is the last record in a data set returned by a query
		return TRUE;
	}

//	TRACE0(":::\n"); // next line

	switch (GetLastQueryType())
	{
	case Q_LIST_CHANNELS:	// CPPChannel inqures
		{
			if (!m_hQClient)
			{
				TRACE0("CPPChannel is gone\n");
				return FALSE;	// CPPChannel dialog may be destructed...
			}
			if (FAILED(pcsProp->picsProperty->HrSetPrivateData((PVOID)m_iItem)))
			{
				TRACE0("HrSetPrivateData\n");
				return FALSE;
			}
//			TRACE("SEND=>0x%lx\n", (LPARAM)pcsProp->picsProperty);
			// ::SendMessage - The function calls the window procedure for the specified window
			// and does not return until the window procedure has processed the message.
			::SendMessage(m_hQClient, CMD_QUERY_CHANNELS, 0, (LPARAM)pcsProp->picsProperty);
			m_iItem++;
			if (pcsProp->fLastRecord)
			{
				TRACE("\nQ_LIST_CHANNELS: Got last data.(%d)\n", m_iItem);
				SetQueryOK();
				::SendMessage(m_hQClient, CMD_QUERY_CHANNELS_END, 0, (LPARAM)0);
				m_hQClient = NULL;	// clear the query client
			}
		}
		break;
	case Q_LIST_USERS:		//
	case Q_CHANNEL_MEMBERS:	// CMemberDlg inqures
		{
			if (!m_hQClient)
			{
				TRACE0("CDlgMemberList is gone\n");
				return FALSE;
			}
			if (FAILED(pcsProp->picsProperty->HrSetPrivateData((PVOID)m_iItem)))
			{
				TRACE0("HrSetPrivateData\n");
				return FALSE;
			}
			::SendMessage(m_hQClient, CMD_QUERY_MEMBERS, 0, (LPARAM)pcsProp->picsProperty);
			m_iItem = 0;
			if (pcsProp->fLastRecord)
			{
				TRACE("\nQ_LIST_USERS or Q_CHANNEL_MEMBERS: Got last data.(%d)\n", m_iItem);
				SetQueryOK();
				HWND hDlg = m_hQClient;
				m_hQClient = NULL;	// clear the client in the Doc
				::SendMessage(hDlg, CMD_QUERY_MEMBERS_END, 0, (LPARAM)0);
			}
		}
		break;
	case Q_GET_REALNAME:	// CSINDEX_PROP_REALNAME_NAME
		{
			SetQueryOK();
			if (!m_hQClient)
			{
				TRACE0("CDlgMemberList is gone\n");
				return FALSE;
			}
			CS_PROPDATA	cspd;
			if (FAILED(pcsProp->picsProperty->HrGetProperty(&cspd, CSINDEX_PROP_REALNAME_REALNAME)))
				return FALSE;
			CHAR* szName = (CHAR*)cspd.pbData;
			TRACE("Q_GET_REALNAME =>(%s)\n", szName);
			::SendMessage(m_hQClient, CMD_QUERY_GET_REALNAME, 0, (LPARAM)szName);
		}
		break;
	default:
		break;
	}
	return fRet;
}

BOOL CUC2Socket::FUnknownMessage(PCS_MSGBASE pMsg)
{
	TRACE("CUC2Socket::FUnknownMessage\n");
	return TRUE;
}

//--------------------------------------------------------------------------+
// class CUC2Channel
//--------------------------------------------------------------------------+
CUC2Channel::CUC2Channel(const HWND hWnd)
{
	TRACE0("CUC2Channel::CUC2Channel()\n");
	ASSERT(hWnd);
	m_hFrame = hWnd;
}

CUC2Channel::~CUC2Channel()
{
	TRACE0("CUC2Channel::~CUC2Channel()\n");
}

BOOL CUC2Channel::FOnChannelError(HRESULT hr)
{
	// Error returned asynchronously
	CString str;
	str.Format("Channel Error %lx.\n", hr);
	TRACE(str);
//	::MessageBox(NULL, str, szUC2Channel, MB_OK | MB_ICONEXCLAMATION);
	return TRUE;
}

BOOL CUC2Channel::FOnAddMember(PCS_MSGMEMBER pMsg)
{
	TRACE0("CUC2Channel::FOnAddMember\n");
	if (!m_hFrame)
		return FALSE;
	PICS_MEMBER pM = pMsg->picsMember;
	ASSERT(pM);
	TRACE("[%s]\n", SzMemName(pM));
	pM->AddRef();
	PostMessage(CSMSG_CMD_ADDMEMBER, 0, (LPARAM)pM);
	return TRUE;
}

BOOL CUC2Channel::FOnDelMember(PCS_MSGMEMBER pMsg)
{
	TRACE0("CUC2Channel::FOnDelMember\n");
	if (!m_hFrame)
		return FALSE;
//	PICS_MEMBER pM = pMsg->picsMember;
//	ASSERT(pM);
//	pM->AddRef();
	SendMessage(CSMSG_CMD_DELMEMBER, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnDelChannel(PCS_MSGCHANNEL pMsg)
{
	TRACE0("CUC2Channel::FOnDelChannel\n");
	if (!m_hFrame)
		return FALSE;
	PICS_CHANNEL pC = pMsg->picsChannel;
	ASSERT(pC);
	pC->AddRef();
	PostMessage(CSMSG_CMD_DELCHANNEL, 0, (LPARAM)pC);
	return TRUE;
}

BOOL CUC2Channel::FOnMemberModeChange(PCS_MSGMEMBER pMsg)
{
	TRACE0("CUC2Channel::FOnMemberModeChange\n");
	if (!m_hFrame)
		return FALSE;
	SendMessage(CSMSG_CMD_MODEMEMBER, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnChannelModeChange()
{
	TRACE0("CUC2Channel::FOnChannelModeChange\n");
	if (!m_hFrame)
		return FALSE;
	SendMessage(CSMSG_CMD_MODECHANNEL, 0, 0);
	return TRUE;
}

BOOL CUC2Channel::FOnNewTopic()
{
	TRACE0("CUC2Channel::FOnNewTopic()\n");
	if (!m_hFrame)
		return FALSE;
	CString str("The topic is now: ");
	str += SzTopic();
	str += "\n";
	TRACE(str);
//	SendMessage(CSMSG_CMD_NEWNICK, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnAnsiTextMsg(PCS_MSG pMsg)
{
	TRACE0("CUC2Channel::FOnAnsiTextMsg\n");
	if (!m_hFrame)
		return FALSE;
//	ASSERT(pMsg->picsFrom);
	SendMessage(CSMSG_CMD_TEXT_A, 0, (LPARAM)pMsg);
	return FALSE;
}

BOOL CUC2Channel::FOnDataMsg(PCS_MSG pMsg)
{
	TRACE0("CUC2Channel::FOnDataMsg\n");
	if (!m_hFrame)
		return FALSE;
	ASSERT(pMsg->picsFrom);
	SendMessage(CSMSG_CMD_DATA, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnAnsiWhisperTextMsg(PCS_MSGWHISPER pMsg)
{
	TRACE0("CUC2Channel::FOnAnsiWhisperTextMsg\n");
	if (!m_hFrame)
		return FALSE;
	SendMessage(CSMSG_CMD_WHISPERTEXT_A, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnAnsiWhisperDataMsg(PCS_MSGWHISPER pMsg)
{
	TRACE0("CUC2Channel::FOnAnsiWhisperDataMsg\n");
	if (!m_hFrame)
		return FALSE;
	SendMessage(CSMSG_CMD_WHISPERDATA, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FOnNewNick(PCS_NEWNICK pMsg)
{
	TRACE0("CUC2Channel::FOnNewNick\n");
	if (!m_hFrame)
		return FALSE;
	SendMessage(CSMSG_CMD_NEWNICK, 0, (LPARAM)pMsg);
	return TRUE;
}

BOOL CUC2Channel::FUnknownMessage(PCS_MSGBASE pMsg)
{
	TRACE0("CUC2Channel::UnknownMessage\n");
	if (!m_hFrame)
		return FALSE;
	return TRUE;
}
