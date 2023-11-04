//--------------------------------------------------------------------------
//	CBaseSocket class
//
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
//  Copyright (C) 1996 Microsoft Corporation
//  All rights reserved.
//
//	Modified and trouble-shooted for MFC
//	::CreateThread ----> CWinThread* AfxBeginThread
//--------------------------------------------------------------------------
#include "stdafx.h"
#include "BaseSock.h"
#include "resource.h"       // main symbols

//DWORD __stdcall DwSocketThreadProc(PVOID pvData);

CBaseSocket::CBaseSocket()
{
	TRACE0("CBaseSocket::CBaseSocket()\n");
	m_pics			= NULL;
	m_pFactory		= NULL;
	m_pThread		= NULL;
	m_hThread		= NULL;
	m_bCanceled		= FALSE;
	m_nPICSRef		= 0;
}

CBaseSocket::~CBaseSocket()
{
	TRACE0("CBaseSocket::~CBaseSocket()\n");
	CleanUp();
}

//	Close the socket and kill the worker thread.
void CBaseSocket::CleanUp()
{
	if (!m_bCanceled)
		FCloseChatSocket();

	if (m_pFactory)
	{
		m_pFactory->Release();
	}
	if (m_pics)
	{
		m_pics->Release();
	}
	WaitForMsgThread();
}

// We need to make sure to wait for the thread to exit, so we
// can be sure all the resources have been cleaned up.
void CBaseSocket::WaitForMsgThread()
{
	if (m_hThread)
	{
		TRACE("CBaseSocket - ::WaitForSingleObject(0x%lx, 5000L);\n", m_hThread);
		DWORD dwRc = ::WaitForSingleObject(m_hThread, 5000L);
		switch (dwRc)
		{
		case WAIT_OBJECT_0:
			TRACE0("Thread: WAIT_OBJECT_0\n");
			break;
		case WAIT_ABANDONED:
			TRACE0("Thread: WAIT_ABANDONED\n");
			break;
		case WAIT_TIMEOUT:
			TRACE0("Thread Hung! Deleting...\n");
			::MessageBox(NULL, "Error: Cannot terminate socket thread.\n", "CBaseSocket", MB_OK);
//			delete m_pThread;
			break;
		case WAIT_FAILED:
			PrintWin32Error("Thread: WAIT_FAILED ");
			break;
		default:
			TRACE0("Thread Hung!\n");
			break;
		}
		//::CloseHandle(m_hThread);
		m_pThread = NULL;	// CWinThread auto-deleted
		m_hThread = NULL;
	}
}

//	Log off and close the socket.
BOOL CBaseSocket::FCloseChatSocket()
{
	if (m_pics)
	{
		TRACE0("CBaseSocket::FCloseChatSocket(): m_pics->HrLogOff()\n");
		// After a successful log off,
		m_pics->HrLogOff();
		// IChatSocket::HrWaitForMsg method will return a CS_E_QUEEMPTY message/
		// You should then terminate your message loop.
		WaitForMsgThread();		// Soomin Kim
		TRACE0("CBaseSocket::FCloseChatSocket(): m_pics->HrCloseSocket()\n");
		m_pics->HrCloseSocket();	// A thread in ChatSock.dll exits. (0x80004601C)
		m_pics->Release();
		if (m_nPICSRef)
		{
			m_pics->Release();
			m_nPICSRef--;
		}
		m_pics = NULL;
		// Don't set m_pics = NULL here. Since CBaseSocket::FWaitForMessage() may still
		// be running.
	}
	return TRUE;
}

PICS CBaseSocket::PChatSocket()
{
	ASSERT(m_pics);

	if (m_pics)
		m_pics->AddRef();
	return m_pics;
}

//	Initialize the object.  We create the socket factory here, so we can
// allow disconnecting during the process of connecting; a connection attempt
// can take a long time, so if the caller wants to cancel the process, 
// it can call HrDisconnect() in another thread.
BOOL CBaseSocket::FInit()
{
//	ASSERT(!m_pics);
	if (m_pics)
	{
		TRACE0("CBaseSocket::FInit() - m_pics != NULL\n");
		return FALSE;
	}

	if (m_pFactory)
	{
		m_pFactory->Release();
	}
	TRACE0("CBaseSocket: ::HrCreateChatSocketFactory(IID_CHATSOCKVER1, &m_pFactory)\n");
	HRESULT hr = ::HrCreateChatSocketFactory(IID_CHATSOCKVER1, &m_pFactory);
	if (FAILED(hr))
	{
		FOnSocketError(hr);		// virtual function call
		m_pFactory = NULL;
		return FALSE;
	}
//	m_pFactory->AddRef();	// by Kim, Soomin
	return TRUE;
}

//	Connecting to a chat server via ChatSock is a 2-step process.
// Since we don't know if the chat server is a MIC or IRC server, 
// we call the socket factory and let it sort out the protocol issues.
// The socket factory will create a socket.
// Once we have the socket, we can then connect and log into the server.
BOOL CBaseSocket::FConnect(PEC_CONNINFO pcInfo, HWND hNotifyWnd)
{
	HRESULT		hr = NOERROR;
	BOOL		fDoneBak = FALSE;	// have we tried the backup nick?
	BOOL		fLoop = TRUE;
	TCHAR		cBackupIDSuffix = '0';

	ASSERT(pcInfo && m_pFactory);

	if (FConnected())
		return TRUE;

	if (hNotifyWnd)
		::PostMessage(hNotifyWnd, CMD_CONNECT_CONNECTING, 0, 0);

	m_bCanceled = FALSE;
	TRACE("CBaseSocket: m_pFactory->HrMakeSocket(%s, %lx)\n", pcInfo->szServer, &m_pics);
	hr = m_pFactory->HrMakeSocket(pcInfo->szServer, &m_pics);
	if (FAILED(hr))
		goto LReturn;

	if (m_pics->HrIsMicSocket() != NOERROR)
	{
		::MessageBox(NULL, "This is not an MIC socket!\n", "CBaseSocket", MB_OK);
		goto LReturn;
	}

	if (hNotifyWnd)
		::PostMessage(hNotifyWnd, CMD_CONNECT_LOGIN, 0, 0);

	CS_CONNINFO	cInfo;
	::ZeroMemory(&cInfo, sizeof(CS_CONNINFO));
	cInfo.dwcb		= sizeof(CS_CONNINFO);
	cInfo.bType		= pcInfo->fAuthenticate ? CS_CONNECT_AUTHENTICATE : CS_CONNECT_ANONYMOUS;
	cInfo.pvNick	= (PVOID)pcInfo->szNick;
	cInfo.pvUser	= (PVOID)pcInfo->szUserName;
	cInfo.pvPass	= (PVOID)pcInfo->szPass;

	// Loop till we have a result on the login
	while (fLoop)
	{
		TRACE0("CBaseSocket::FConnect: m_pics->HrLoginA(&cInfo);\n");
		hr = m_pics->HrLoginA(&cInfo);
		if (FAILED(hr))
		{
			goto LReturn;
		}
		
		// Now check the Wait Q for acknowledgement
		PCS_MSGBASE pcsMsg;
		TRACE0("CBaseSocket::FConnect: m_pics->HrWaitForMsg(&pcsMsg, INFINITE);\n");
		hr = m_pics->HrWaitTillMsgType(CSMSG_TYPE_LOGIN, &pcsMsg, pcInfo->dwTimeOut);
		TRACE("CBaseSocket::FConnect: m_pics->HrWaitForMsg returned %lx\n", hr);

		if (FAILED(hr))
		{
			// Did we log in or get an error?
//			ASSERT(pcsMsg);
//			switch (pcsMsg->csMsgType)
//			{
//			case CSMSG_TYPE_ERROR:
//				{
//				TRACE0("CBaseSocket: CSMSG_TYPE_ERROR\n");
//				PCS_ERROR	pErr = (PCS_ERROR)(pcsMsg + 1);
//				hr = pErr->hr;
				if (hr == CS_E_ILLEGALUSER)
				{
					FOnSocketError(hr);
					continue;
				}
				if ((hr == CS_E_ALIASINUSE) && !fDoneBak && pcInfo->szNickBak)
				{
					int n = lstrlen(pcInfo->szNickBak);
					if (n > 1)
					{
						pcInfo->szNickBak[n-1] = cBackupIDSuffix;
						cInfo.pvNick = (PVOID)pcInfo->szNickBak;
						if (cBackupIDSuffix++ >= '9')
						{
							fDoneBak = TRUE;
						}
						if (hNotifyWnd)
						{
							::PostMessage(hNotifyWnd, CMD_CONNECT_BACKUPID, 0, 0);
						}
					}
					continue;
				}
//				}
//				break;

//			case CSMSG_TYPE_LOGIN:
//				TRACE0("CBaseSocket: CSMSG_TYPE_LOGIN\n");
//				hr = NOERROR;
//				break;

//			default:
//				ASSERT(FALSE);
//				break;
//			}
			goto LReturn;
		}

		FOnLogin();		// call the virtual function
		fLoop = FALSE;
		::HrFreeMsg(pcsMsg);
	}

LReturn:
	// If successful, save the socket
	if (SUCCEEDED(hr))
	{
		TRACE0("CBaseSocket::FConnect: FStartMessageThread();\n");
		// Start a thread to read messages from the message que
		if (!FStartMessageThread())
		{
			FOnSocketError(E_OUTOFMEMORY);	// virtual function call
			CleanUp();
			return FALSE;
		}
		return TRUE;
	}

	// Failure
	// On Cancel, m_pics->HrCloseSocket() may already been called by FCloseChatSocket().
	if (!m_bCanceled && m_pics)
	{
		TRACE0("CBaseSocket::FConnect: m_pics->HrCloseSocket()\n");
		m_pics->HrCloseSocket();
		TRACE0("CBaseSocket::FConnect: m_pics->Release()\n");
		m_pics->Release();
		m_pics = NULL;
	}

//	FOnSocketError(hr);	// virtual function call	// Doesn't work for OnCancel...
//	TRACE0("CBaseSocket::FConnect returned FALSE\n");
	return FALSE;
}

//	Disconnect from the server.
// Cancels any in-progress connection attempts or other blocking operations.
BOOL CBaseSocket::FDisconnect()
{
	// As long as m_pFactory is alive, HrCancelMakeSocket() will have
	// the same effect as calling HrCloseSocket() on a ChatSocket.
	m_bCanceled = TRUE;
	FCloseChatSocket();
	if (m_pFactory)
	{
		TRACE0("CBaseSocket: m_pFactory->HrCancelMakeSocket()\n");
		HRESULT hr = m_pFactory->HrCancelMakeSocket();
//		m_pFactory->Release();
//		m_pFactory = NULL;	// to prevent calling m_pFactory->HrCancelMakeSocket() again
		if (FAILED(hr))
		{
			FOnSocketError(hr);	// virtual function call
			return FALSE;
		}
	}
//	m_pThread = NULL;
//	m_hThread = FALSE;
	return TRUE;
}

// Does this server support anonymous logins?
BOOL CBaseSocket::FCanAnonymous()
{
	// Grab security details
	PCS_SECURITY	pcsSecurity;
	HRESULT hr = m_pics->HrGetSecurityInfo(&pcsSecurity);
	if (FAILED(hr))
	{
		return TRUE;	// assume anon
	}
	return pcsSecurity->fAnonAllowed;
}

//	Uses m_pics->HrCreateChannelA() to create a channel; if a channel
// with the specified name already exists, this function simply joins it.
BOOL CBaseSocket::FCreateJoinChannel(PEC_CHANNELINFO pChanInfo)
{
	ASSERT(pChanInfo);
	ASSERT(m_pics);

	CS_CINFO	cInfo;
	::ZeroMemory(&cInfo, sizeof(CS_CINFO));	// This line was missing!!!! It's was the BUG! Nov 21thu'96
	cInfo.dwcb			= sizeof(CS_CINFO);
	cInfo.dwType		= pChanInfo->dwType;
	cInfo.dwFlags		= pChanInfo->dwFlags;
	// if channel exists, join it, else create a new one
	cInfo.bCreateFlags	= CS_CHANNEL_CREATE_JOIN;
	cInfo.pvChannelName = (PVOID)pChanInfo->szName;
	cInfo.pvTopic		= (PVOID)pChanInfo->szTopic;
	cInfo.pvPassword	= pChanInfo->szPass;
	cInfo.dwcUserMax	= pChanInfo->cUsersMax;

	TRACE("CBaseSocket: m_pics->HrCreateChannelA(&cInfo) - %s\n", (char*)cInfo.pvChannelName);
	HRESULT hr = m_pics->HrCreateChannelA(&cInfo);

	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseSocket::FConnected()
{
	return (m_pics && (NOERROR == m_pics->HrIsConnected()));
}

BOOL CBaseSocket::ChangeNick(LPCSTR nick)
{
	ASSERT(m_pics);

	HRESULT hr = m_pics->HrChangeNickA((char*)nick);	
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

//	Waits for a message to arrive on the message queue.
// Calling FCloseChatSocket on the socket will cause this method to return FALSE immediately.
//	Dispatches the received message using the overrideable virtual methods of CBaseSocket.
BOOL CBaseSocket::FWaitForMessage()
{
	if (!m_pics)
		return FALSE;
	m_pics->AddRef();				// increase the ref count so that we can be sure that
	TRACE0("m_pics->AddRef();\n");	// the socket object doesn't go away until this function ends...
	m_nPICSRef++;

	PCS_MSGBASE	pcsMsg;
	while (SUCCEEDED(m_pics->HrWaitForMsg(&pcsMsg, INFINITE)))
	{
		DebugMessageType("=> CBaseSocket::FWaitForMessage", pcsMsg->csMsgType);
		switch (pcsMsg->csMsgType)	// BYTE
		{
		default:
			FUnknownMessage(pcsMsg);	// virtual function call
			break;

		case CSMSG_TYPE_ERROR:
			{
			PCS_ERROR	pErr = MSGBASE_TO_MSG(pcsMsg, PCS_ERROR);
			FOnSocketError(pErr->hr);	// virtual function call
			}
			break;
		
		case CSMSG_TYPE_ADDCHANNEL:
			{
			PCS_MSGCHANNEL pMsgCh = MSGBASE_TO_MSG(pcsMsg, PCS_MSGCHANNEL);
			FOnAddChannel(pMsgCh);		// virtual function call; Ref++
			}
			break;

		case CSMSG_TYPE_PRIVATEMSG:
			{
			PCS_MSGPRIVATE pMsgPrivate = MSGBASE_TO_MSG(pcsMsg, PCS_MSGPRIVATE);
			FOnPrivateMsg(pMsgPrivate);	// virtual function call
			}
			break;

		case CSMSG_TYPE_QUERYDATA:
			{
			PCS_PROPERTY	pcsProp = MSGBASE_TO_MSG(pcsMsg, PCS_PROPERTY);
			FParseQueryData(pcsProp);	// virtual function call
			}
			break;
		
		case CSMSG_TYPE_INVITE:
			{
			PCS_MSGINVITE	pcsInvite = MSGBASE_TO_MSG(pcsMsg, PCS_MSGINVITE);
			FOnInvite(pcsInvite);		// virtual function call
			}
			break;
		}
		::HrFreeMsg(pcsMsg);
	}
	if (m_pics)
	{
		m_pics->Release();
		m_nPICSRef--;
		TRACE0("m_pics->Release();\n");	// the socket object doesn't go away until this function ends...
//		m_pics = NULL;
	}
	TRACE0("End of CBaseSocket::FWaitForMessage()\n");
	return TRUE;
}

//	Performs default parsing on query data messages.
// If this method is not overridden, it will call FOnPropString and FOnPropBuffer
// as appropriate for the query data.
BOOL CBaseSocket::FParseQueryData(PCS_PROPERTY pcsProp)
{
	return TRUE;
/*
	ASSERT(pcsProp);

	if (!pcsProp->picsProperty)
		return FALSE;

	DWORD dwc;
	if (FAILED((pcsProp->picsProperty)->HrGetCount(&dwc)))
		return FALSE;
	
	BOOL fRet = TRUE;
	for (DWORD dwi=1; dwi <= dwc && fRet; dwi++)
	{
		CS_PROPDATA	cspd;
		if (SUCCEEDED((pcsProp->picsProperty)->HrGetProperty(&cspd, dwi)))
		{
			if (!cspd.pbData || !cspd.fAnsi) // For simplicity's sake, ANSI only.
			{
				continue;
			}
			fRet = (cspd.fString)
				? FOnPropString(cspd.csPropType, (CHAR*)cspd.pbData)
				: FOnPropBuffer(cspd.csPropType, cspd.pbData, cspd.dwcb);
		}
	}
	if (pcsProp->fLastRecord)
	{
		TRACE("This was the last record.\n");
		// What should I do?
	}
	return fRet;
*/
}

BOOL CBaseSocket::FStartMessageThread()
{
	WaitForMsgThread();

	m_pThread = AfxBeginThread(SocketThreadProc, (LPVOID)this);
	ASSERT(m_pThread);
	m_hThread = m_pThread->m_hThread;	// Save the handle
	TRACE("CBaseSocket created a thread for SocketThreadProc [%lx]\n",
			m_pThread->m_nThreadID);
	return (m_pThread != NULL);
}

// static
UINT CBaseSocket::SocketThreadProc(LPVOID pvData)
{
	ASSERT(pvData);
	CBaseSocket* pbasesocket = (CBaseSocket*)pvData;
	return pbasesocket->FWaitForMessage();
}

//////////////////////////////////////////////////////////////////////////////////
// Operations via Chat Socket

BOOL CBaseSocket::FSendPrivAnsiText(char* szNickTo, char* szText)
{
	ASSERT(m_pics);

	CS_PRIVMSGINFO	msg;
	msg.dwcb		= sizeof(CS_PRIVMSGINFO);
	msg.dwUserID	= 0;				// 0 if not available
	msg.pvNickTo	= szNickTo;			// name of the user to send this msg to
	msg.fData		= FALSE;			// 
	msg.pbData		= (BYTE*)szText;	// data to send
	msg.dwcbData	= 0;				// 0 means null terminated string
	HRESULT hr = m_pics->HrSendPrivMsgA(&msg);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseSocket::FSendPrivData(char* szNickTo, BYTE* pbData, DWORD dwcb)
{
	ASSERT(m_pics);

	CS_PRIVMSGINFO	msg;
	msg.dwcb		= sizeof(CS_PRIVMSGINFO);
	msg.dwUserID	= 0;			// 0 if not available
	msg.pvNickTo	= szNickTo;		// name of the user to send this msg to
	msg.fData		= TRUE;			// 
	msg.pbData		= pbData;		// data to send
	msg.dwcbData	= dwcb;			// 0 means null terminated string
	HRESULT hr = m_pics->HrSendPrivMsgA(&msg);
	if (FAILED(hr))
	{
		FOnSocketError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
// Debugging

#if defined(_DEBUG)
void DebugMessageType(LPCSTR t, CSMSG_TYPE c)
{
	switch (c)
	{
	case CSMSG_TYPE_NONE:			TRACE1("%s\tCSMSG_TYPE_NONE\n", t);		break;
	// socket, channel
	case CSMSG_TYPE_ERROR:			TRACE1("%s\tCSMSG_TYPE_ERROR\n", t);	break;
	// socket
	case CSMSG_TYPE_LOGIN:			TRACE1("%s\tCSMSG_TYPE_LOGIN\n", t);	break;
	// channel
	case CSMSG_TYPE_TEXT_A:			TRACE1("%s\tCSMSG_TYPE_TEXT_A\n", t);	break;
	case CSMSG_TYPE_TEXT_W:			TRACE1("%s\tCSMSG_TYPE_TEXT_W\n", t);	break;
	case CSMSG_TYPE_DATA:			TRACE1("%s\tCSMSG_TYPE_DATA\n", t);		break;
	// socket
	case CSMSG_TYPE_ADDCHANNEL:		TRACE1("%s\tCSMSG_TYPE_ADDCHANNEL\n", t);	break;
	// channel
	case CSMSG_TYPE_ADDMEMBER:		TRACE1("%s\tCSMSG_TYPE_ADDMEMBER\n", t);		break;
	case CSMSG_TYPE_GOTMEMLIST:		TRACE1("%s\tCSMSG_TYPE_GOTMEMLIST\n", t);		break;
	case CSMSG_TYPE_DELMEMBER:		TRACE1("%s\tCSMSG_TYPE_DELMEMBER\n", t);		break;
	case CSMSG_TYPE_DELCHANNEL:		TRACE1("%s\tCSMSG_TYPE_DELCHANNEL\n", t);		break;
	case CSMSG_TYPE_MODEMEMBER:		TRACE1("%s\tCSMSG_TYPE_MODEMEMBER\n", t);		break;
	case CSMSG_TYPE_MODECHANNEL:	TRACE1("%s\tCSMSG_TYPE_MODECHANNEL\n", t);		break;
	case CSMSG_TYPE_WHISPERTEXT_A:	TRACE1("%s\tCSMSG_TYPE_WHISPERTEXT_A\n", t);	break;
	case CSMSG_TYPE_WHISPERTEXT_W:	TRACE1("%s\tCSMSG_TYPE_WHISPERTEXT_W\n", t);	break;
	case CSMSG_TYPE_WHISPERDATA:	TRACE1("%s\tCSMSG_TYPE_WHISPERDATA\n", t);		break;
	case CSMSG_TYPE_NEWTOPIC:		TRACE1("%s\tCSMSG_TYPE_NEWTOPIC\n", t);			break;
	// socket,channel
	case CSMSG_TYPE_PROPERTYDATA:	TRACE1("%s\tCSMSG_TYPE_PROPERTYDATA\n", t);		break;
	// socket, channel
	case CSMSG_TYPE_QUERYDATA:		TRACE0(".");	break;
							//		TRACE1("%s\tCSMSG_TYPE_QUERYDATA\n", t);	break;
	// socket
	case CSMSG_TYPE_PRIVATEMSG:		TRACE1("%s\tCSMSG_TYPE_PRIVATEMSG\n", t);		break;
	// channel
	case CSMSG_TYPE_NEWNICK:		TRACE1("%s\tCSMSG_TYPE_NEWNICK\n", t);			break;
	// socket
	case CSMSG_TYPE_INVITE:			TRACE1("%s\tCSMSG_TYPE_INVITE\n", t);			break;
	case CSMSG_TYPE_SERVERMSG_TEXT_A:	TRACE1("%s\tCSMSG_TYPE_SERVERMSG_TEXT_A\n", t);	break;
	case CSMSG_TYPE_SERVERMSG_TEXT_W:	TRACE1("%s\tCSMSG_TYPE_SERVERMSG_TEXT_W\n", t);	break;
	default:
		TRACE2("%s\tError! Beyond CSMSG_TYPE range(%d)!\n", t, c);	break;
	}
}

DWORD PrintWin32Error(LPCSTR pszErrorString)
{
	LPVOID lpMsgBuf[FORMAT_MESSAGE_MAX_WIDTH_MASK + 1];
	// Retrieve the error code
	DWORD dwRc = ::GetLastError();
	// Search system message tables and resources for an error message
	// associated with the error returned
	if (::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
						NULL,		// Message source
						dwRc,		// Error Code
						0,			// Language Specifier
						(LPTSTR)lpMsgBuf,	// Message buffer
						FORMAT_MESSAGE_MAX_WIDTH_MASK,	// Message Buffer Size
						NULL))
		TRACE("%s (%ld: %s)\n", pszErrorString, dwRc, lpMsgBuf);
	return dwRc;
}
#endif	// _DEBUG
