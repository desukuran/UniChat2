//-------------------------------------------------------------------------
//	CBaseChannel class
//
//	Copyright (C) 1996 Microsoft Corporation
//	All rights reserved.
//
//	Modification for MFC
//	(C) Programmed by Kim, Soomin, Nov 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//------------------------------------------------------------------------
#include "stdafx.h"
#include "BaseChan.h"

CBaseChannel::CBaseChannel()
{
	TRACE0("CBaseChannel::CBaseChannel()\n");
	m_picsChannel	= NULL;
	m_pThread		= NULL;
	m_hThread		= NULL;
	m_fGotMemList	= FALSE;
	m_nPICSChanRef	= 0;
}

CBaseChannel::~CBaseChannel()
{
	TRACE0("CBaseChannel::~CBaseChannel()\n");
	CleanUp();
}

//	Save the channel pointer returned by ChatSock, then start a message
BOOL CBaseChannel::FInit(PICS_CHANNEL pChannel)
{
	ASSERT(pChannel);

	WaitForMsgThread();

	SetChannel(pChannel);

	if (!FStartMessageThread())
	{
		CleanUp();
		return FALSE;
	}
	return TRUE;
}

//	Resets the object so it can be restarted with a new channel.
BOOL CBaseChannel::FReInit()
{
	CleanUp();

	return TRUE;
}

//	Release our channel pointer.
void CBaseChannel::CleanUp()
{
	m_fGotMemList	= FALSE;
	WaitForMsgThread();
	if (m_picsChannel)
	{
		m_picsChannel->Release();
		m_picsChannel = NULL;
	}
}

//	Wait for our message thread to terminate; we need to do this
// so we can be sure the thread is cleaned up so we can exit or reinitialize the object.
void CBaseChannel::WaitForMsgThread()
{
	if (m_hThread)
	{
		TRACE("CBaseChannel - ::WaitForSingleObject(0x%lx, 5000L);\n", m_hThread);
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
			::MessageBox(NULL, "Error: Cannot terminate channel thread.\n", "CBaseChannel", MB_OK);
//			delete m_pThread;
			break;
		case WAIT_FAILED:
			PrintWin32Error("Thread: WAIT_FAILED ");
			break;
		default:
			TRACE0("Thread Hung!\n");
			break;
		}
		//::CloseHandle(m_hThread);	// CWinThread may have done this for us.
		m_pThread = NULL;	// CWinThread auto-deleted
		m_hThread = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBaseChannel accessors

// Don't miss calling Release() after using the returned pointer.
PICS_CHANNEL CBaseChannel::PChannel()
{
	if (m_picsChannel)
		m_picsChannel->AddRef();
	
	return m_picsChannel;
}

BOOL CBaseChannel::FInChannel()
{
	return (NULL != m_picsChannel);
}

// FLeave() will Release()
void CBaseChannel::SetChannel(PICS_CHANNEL pics)
{
	ASSERT(!m_picsChannel);
	
	pics->AddRef();
	m_picsChannel = pics;
}

// Get Channel name
char* CBaseChannel::SzName()
{
	ASSERT(m_picsChannel);

	BYTE*	pb;
	BOOL	fAnsi;
	HRESULT hr = m_picsChannel->HrGetName(&pb, &fAnsi);

	// For simplicity, ignore non-ANSI...
	if (FAILED(hr) || !fAnsi)
		return NULL;
	
	return (char*)pb;
}

//	Returns the name of the specified member.
char* CBaseChannel::SzMemName(PICS_MEMBER pMember)
{
	ASSERT(pMember);

	BYTE*	pb;
	BOOL	fAnsi;
	HRESULT hr = pMember->HrGetName(&pb, &fAnsi);

	// For simplicity, ignore non-ANSI...
	if (FAILED(hr) || !fAnsi)
		return NULL;
	
	return (char*)pb;
}

char* CBaseChannel::SzTopic()
{
	ASSERT(m_picsChannel);

	BYTE*	pb;
	BOOL	fAnsi;
	HRESULT hr = m_picsChannel->HrGetTopic(&pb, &fAnsi);

	// For simplicity, ignore non-ANSI...
	if (FAILED(hr) || !fAnsi)
		return NULL;
	
	return (char*)pb;
}

// Is the specified member myself?
BOOL CBaseChannel::FIsMemberMe(PICS_MEMBER pMember)
{
	ASSERT(m_picsChannel);
//	ASSERT(pMember);

	PICS_MEMBER pMem;
	if (FAILED(m_picsChannel->HrGetMe(&pMem)))
	{
		return FALSE;
	}
	BOOL fRet = (pMember == pMem);
	if (pMem)
	{
		pMem->Release();
	}
	return fRet;
}

BOOL CBaseChannel::FAmIHost()
{
	ASSERT(m_picsChannel);

	PICS_MEMBER pMem;
	if (FAILED(m_picsChannel->HrGetMe(&pMem)))
	{
		return FALSE;
	}
	if (pMem)
	{
		BOOL fRet = (NOERROR == pMem->HrIsMemberHost());
		pMem->Release();
		return fRet;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseChannel operations

BOOL CBaseChannel::FSendAnsiText(char* szText)
{
	ASSERT(m_picsChannel);

	HRESULT hr = m_picsChannel->HrSendTextA(szText);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseChannel::FSendData(BYTE* pbData, DWORD dwcb)
{
	ASSERT(m_picsChannel);

	HRESULT hr = m_picsChannel->HrSendData(pbData, dwcb);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseChannel::FWhisperTo(PICS_MEMBER pM, char* szText)
{
	ASSERT(m_picsChannel);

	HRESULT hr = m_picsChannel->HrSendTextListA(szText, &pM, 1);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL  CBaseChannel::FSendInvite(PCS_INVITEINFO piInfo)
{
	ASSERT(m_picsChannel);

	HRESULT hr = m_picsChannel->HrSendInviteA(piInfo);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

DWORD CBaseChannel::DwUserCount()
{
	ASSERT(m_picsChannel);

	DWORD	cUser;
	HRESULT hr = m_picsChannel->HrGetUserCount(&cUser);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return 0;
	}
	return cUser;
}

DWORD CBaseChannel::DwType()
{
	ASSERT(m_picsChannel);

	DWORD	dwMode;
	HRESULT hr = m_picsChannel->HrGetType(&dwMode);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return 0;
	}
	return dwMode;
}

BOOL CBaseChannel::FSetTopic(char* szTopic)
{
	ASSERT(m_picsChannel);

	HRESULT hr = m_picsChannel->HrSetTopicA(szTopic);
	if (FAILED(hr))
	{
		FOnChannelError(hr);	// virtual function call
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseChannel::FLeave()
{
	ASSERT(m_picsChannel);

	if (m_picsChannel)
	{
		if (FAILED(m_picsChannel->HrLeave(FALSE)))
			return FALSE;

		WaitForMsgThread();
		m_picsChannel->Release();
		if (m_nPICSChanRef)
			m_picsChannel->Release();
		m_picsChannel = NULL;
	}
	return NOERROR;
}

//	Waits for a message to arrive on the message queue.
// Calling FLeave on the channel will cause this method to return FALSE immediately.
// Dispatches the received message using the overrideable virtual methods of CBaseChannel.
BOOL CBaseChannel::FWaitForMessage()
{
	if (!m_picsChannel)
		return FALSE;
	m_picsChannel->AddRef();				// increase the ref count so that we can be sure that
	TRACE0("m_picsChannel->AddRef();\n");	// the channel object doesn't go away until this function ends...
	m_nPICSChanRef++;

	PCS_MSGBASE		pcsMsg;
	while (SUCCEEDED(m_picsChannel->HrWaitForMsg(&pcsMsg, INFINITE)))
	{
		DebugMessageType("=> CBaseChannel::FWaitForMessage", pcsMsg->csMsgType);
		switch (pcsMsg->csMsgType)
		{
		default:
			FUnknownMessage(pcsMsg);
			break;

		case CSMSG_TYPE_ERROR:
			{
			PCS_ERROR	pErr = MSGBASE_TO_MSG(pcsMsg, PCS_ERROR);
			FOnChannelError(pErr->hr);	// virtual function call
			}
			break;

		case CSMSG_TYPE_ADDMEMBER:
			{
			PCS_MSGMEMBER	pAddMsg = MSGBASE_TO_MSG(pcsMsg, PCS_MSGMEMBER);
			FOnAddMember(pAddMsg);		// virtual function call
			}
			break;

		case CSMSG_TYPE_GOTMEMLIST:
			m_fGotMemList = TRUE;
//			FOnGotMemList();
			break;

		case CSMSG_TYPE_DELMEMBER:
			{
			PCS_MSGMEMBER	pDelMsg = MSGBASE_TO_MSG(pcsMsg, PCS_MSGMEMBER);
			FOnDelMember(pDelMsg);		// virtual function call
			}
			break;

		case CSMSG_TYPE_DELCHANNEL:
			{
			PCS_MSGCHANNEL	pMsgChan = MSGBASE_TO_MSG(pcsMsg, PCS_MSGCHANNEL);
			FOnDelChannel(pMsgChan);	// virtual function call
			}
			break;

		case CSMSG_TYPE_MODEMEMBER:
			{
			PCS_MSGMEMBER	pModeMsg = MSGBASE_TO_MSG(pcsMsg, PCS_MSGMEMBER);
			FOnMemberModeChange(pModeMsg);	// virtual function call
			}
			break;
		
		case CSMSG_TYPE_MODECHANNEL:
			FOnChannelModeChange();			// virtual function call
			break;
		
		case CSMSG_TYPE_TEXT_A:
			{
			PCS_MSG pMsgText = MSGBASE_TO_MSG(pcsMsg, PCS_MSG);
			FOnAnsiTextMsg(pMsgText);		// virtual function call
			}
			break;
		
		case CSMSG_TYPE_DATA:
			{
			PCS_MSG pMsgData = MSGBASE_TO_MSG(pcsMsg, PCS_MSG);
			FOnDataMsg(pMsgData);			// virtual function call
			}
			break;

		case CSMSG_TYPE_WHISPERTEXT_A:
			{
			PCS_MSGWHISPER pMsgWhisper = MSGBASE_TO_MSG(pcsMsg, PCS_MSGWHISPER);
			FOnAnsiWhisperTextMsg(pMsgWhisper);	// virtual function call
			}
			break;

		case CSMSG_TYPE_WHISPERDATA:
			{
			PCS_MSGWHISPER	pMsgWhisperData = MSGBASE_TO_MSG(pcsMsg, PCS_MSGWHISPER);
			FOnAnsiWhisperDataMsg(pMsgWhisperData);	// virtual function call
			}
			break;

		case CSMSG_TYPE_NEWTOPIC:
			FOnNewTopic();			// virtual function call
			break;

		case CSMSG_TYPE_NEWNICK:
			{
			PCS_NEWNICK pNickMsg = MSGBASE_TO_MSG(pcsMsg, PCS_NEWNICK);
			FOnNewNick(pNickMsg);	// virtual function call
			}
			break;
		}
		// Free the msg
		::HrFreeMsg(pcsMsg);
	}
	if (m_picsChannel)
	{
		m_picsChannel->Release();
		m_nPICSChanRef--;
		TRACE0("m_picsChannel->Release();\n");
	}
	TRACE0("End of CBaseChannel::FWaitForMessage()\n");

	return TRUE;
}

BOOL CBaseChannel::FStartMessageThread()
{
	ASSERT(!m_hThread);
	
//	m_hThread = ::CreateThread(NULL, 0, DwChannelThreadProc, this, 0, &dwID);
	m_pThread = AfxBeginThread(ChannelThreadProc, (LPVOID)this);
	ASSERT(m_pThread);
	m_hThread = m_pThread->m_hThread;	// Save the handle
	// We need to save the handle since the object m_pThread points to may already
	// be deleted away. And pass this handle to ::WaitSingleObject.
	TRACE("CBaseChannel created a thread for DwChannelThreadProc [%lx]\n",
			m_pThread->m_nThreadID);
	return (m_pThread != NULL);
}

// static
UINT CBaseChannel::ChannelThreadProc(LPVOID pvData)
{
	ASSERT(pvData);
	CBaseChannel* pbasechannel = (CBaseChannel*)pvData;
	return pbasechannel->FWaitForMessage();
}
