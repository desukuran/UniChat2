//--------------------------------------------------------------------------
//	CBaseSocket class
//
//  Copyright (C) 1996 Microsoft Corporation
//  All rights reserved.
//
//	Modification for MFC
//	(C) Programmed by Kim, Soomin, Nov 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//--------------------------------------------------------------------------
#ifndef _BASESOCK_H
#define _BASESOCK_H

/////////////////////////////////////////////////////////////////////////////
// class CBaseSocket

// Pointer to this structure is passed to CBaseSocket::HrConnect
typedef struct conninfo
{
	char*	szServer;		// server to connect to
	char*	szNick;			// Nickname to use
	char*	szNickBak;		// A backup nick - optional
	char*	szUserName;		// user name to use 
	char*	szPass;			// if szUserName is provided, so must szPass
	BOOL	fAuthenticate;	// should the connection be authenticated?
	DWORD	dwTimeOut;
} EC_CONNINFO, *PEC_CONNINFO;

// Pointer to this structure is passed to CBaseSocket::HrCreateJoinChannel
typedef struct channelinfo
{
	CHAR*	szName;			// name of the channel to join
	CHAR*	szTopic;		// if channel did not exist, and was therefore
							// created for you, set the topic to this value
	CHAR*	szPass;			// password on this channel
	DWORD	cUsersMax;		// how many users at max...0 if default
	DWORD	dwType;			// channel type
	DWORD	dwFlags;		// channel flags.
} EC_CHANNELINFO, *PEC_CHANNELINFO;

// CBaseSocket
// CBaseSocket is a wrapper around IChatSocket.  It provides message-handling code
// and wrappers around some IChatSocket functionality.  If you need more
// functionality from ChatSock, use CBaseSocket::PSocket() to obtain a socket
// interface and then call ChatSock directly.
// Note: if you intend to keep that pointer around in other data structures,
// you should AddRef() it and then Release() it when that particular data structure
// goes away.  This will make your cleanup logic a lot more robust.

class CBaseSocket : public CObject
{
public:
	BOOL ChangeNick(LPCSTR nick);
	CBaseSocket();
	virtual ~CBaseSocket();

	BOOL			FInit();
	BOOL			FConnect(PEC_CONNINFO pcInfo, HWND hNotifyWnd=NULL);
	BOOL			FDisconnect();
	BOOL			FCloseChatSocket();

	BOOL			FCreateJoinChannel(PEC_CHANNELINFO pChanInfo);

	BOOL			FCanAnonymous();
	BOOL			FConnected();
	PICS			PChatSocket();

	BOOL			FSendPrivAnsiText(char* szNickTo, char* szText);
	BOOL			FSendPrivData(char* szNickTo, BYTE* pbData, DWORD dwcb);

	// Overrideables
	virtual BOOL	FOnLogin()							{ return TRUE; }
	virtual BOOL	FOnSocketError(HRESULT hr)			{ return TRUE; }
	virtual BOOL	FOnAddChannel(PCS_MSGCHANNEL pMsg)	{ return TRUE; }
	virtual BOOL	FOnPrivateMsg(PCS_MSGPRIVATE pMsg)	{ return TRUE; }
	virtual BOOL	FOnInvite(PCS_MSGINVITE	pcsInvite)	{ return TRUE; }
//	virtual BOOL	FOnPropString(CSPROP_TYPE csType, char* sz)	{ return TRUE; }
//	virtual BOOL	FOnPropBuffer(CSPROP_TYPE csType, BYTE* pbBuffer, DWORD dwcb)	{ return TRUE; }
	virtual BOOL	FParseQueryData(PCS_PROPERTY pcsProp);
	// and if we got something we don't really handle..
	virtual BOOL	FUnknownMessage(PCS_MSGBASE pMsg)	{ return TRUE; }

protected:
	static UINT		SocketThreadProc(LPVOID pvData);
	void			CleanUp();

//	BOOL			FCloseChatSocket();
	void			SetSocket(PICS pics);
	BOOL			FStartMessageThread();
	BOOL			FWaitForMessage();
	void			WaitForMsgThread();

	PICS			m_pics;
	PICS_FACTORY	m_pFactory;
	CWinThread*		m_pThread;
	HANDLE			m_hThread;	// Save the handle for ::WaitSingleObject
	BOOL			m_bCanceled;
	int				m_nPICSRef;
};

#ifdef _DEBUG
	void DebugMessageType(LPCSTR t, CSMSG_TYPE c);
	DWORD PrintWin32Error(LPCSTR pszErrorString);
#else
	#define DebugMessageType(t, c)	// Do nothing
	#define PrintWin32Error(t)
#endif

#endif // _BASESOCK_H
