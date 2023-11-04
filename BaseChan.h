//-------------------------------------------------------------------------
//	CBaseChannel class
//
//	(C) Programmed by Kim, Soomin, Nov 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
//	Original Copyright (C) 1996 Microsoft Corporation
//	All rights reserved.
//
//	Modified and trouble-shooted for MFC
//	::CreateThread ----> CWinThread* AfxBeginThread
//------------------------------------------------------------------------
#ifndef _BASECHAN_H
#define _BASECHAN_H

////////////////////////////////////////////////////////////////////////////
// class CBaseChannel

//	CBaseChannel is a wrapper around ICSChannel.
// It provides message-handling code and wrappers around some ICSChannel functionality.
// If you need more functionality from ChatSock, use CBaseChannel::PChannel()
// to obtain a channel interface and then call ChatSock directly.
// Note: if you intend to keep that pointer around in other data structures,
// you should AddRef() it and then Release() it when that particular data structure
// goes away. This will make your cleanup logic a lot more robust.

class CBaseChannel : public CObject
{
public:
	CBaseChannel();
	virtual ~CBaseChannel();

	BOOL			FInit(PICS_CHANNEL pChannel); 
	BOOL			FReInit();

	PICS_CHANNEL	PChannel();
	BOOL			FInChannel();
					
	BOOL			FGotMemList() const		{ return m_fGotMemList; }
	BOOL			FAmIHost();
	BOOL			FIsMemberMe(PICS_MEMBER pMember);
	char*			SzName();
	char*			SzMemName(PICS_MEMBER pMember);
	char*			SzTopic();
			
	BOOL			FGotMemberList()				{ return m_fGotMemList; }
	BOOL			FSendAnsiText(char* szText);
	BOOL			FSendData(BYTE* pbData, DWORD dwcb);
	BOOL			FWhisperTo(PICS_MEMBER pM, char* szText);
	BOOL			FSendInvite(PCS_INVITEINFO piInfo);

	DWORD			DwUserCount();
	DWORD			DwType();
	BOOL			FSetTopic(char* szText);
	BOOL			FLeave();

	// Overrideables
	virtual BOOL	FOnChannelError(HRESULT hr)					{ return TRUE; }
	virtual BOOL	FOnAddMember(PCS_MSGMEMBER pMsg)			{ return TRUE; }
	virtual BOOL	FOnDelMember(PCS_MSGMEMBER pMsg)			{ return TRUE; }
	virtual BOOL	FOnDelChannel(PCS_MSGCHANNEL pMsg)			{ return TRUE; }
	virtual BOOL	FOnMemberModeChange(PCS_MSGMEMBER pMsg)		{ return TRUE; }
	virtual BOOL	FOnChannelModeChange()						{ return TRUE; }
	virtual BOOL	FOnNewTopic()								{ return TRUE; }
	virtual BOOL	FOnAnsiTextMsg(PCS_MSG pMsg)				{ return TRUE; }
	virtual BOOL	FOnDataMsg(PCS_MSG pMsg)					{ return TRUE; }
	virtual BOOL	FOnAnsiWhisperTextMsg(PCS_MSGWHISPER pMsg)	{ return TRUE; }
	virtual BOOL	FOnAnsiWhisperDataMsg(PCS_MSGWHISPER pMsg)	{ return TRUE; }
	virtual BOOL	FOnNewNick(PCS_NEWNICK pMsg)				{ return TRUE; }
	// and if we got something we don't really handle...
	virtual BOOL	FUnknownMessage(PCS_MSGBASE pMsg)			{ return TRUE; }
	
protected:
//	friend DWORD __stdcall ChannelThreadProc(PVOID pvData);
	static UINT		ChannelThreadProc(LPVOID pvData);

	void			CleanUp();
	void			SetChannel(PICS_CHANNEL pics);
	BOOL			FWaitForMessage();
	BOOL			FStartMessageThread();
	void			WaitForMsgThread();

	PICS_CHANNEL	m_picsChannel;
	BOOL			m_fGotMemList;
	CWinThread*		m_pThread;
	HANDLE			m_hThread;
	int				m_nPICSChanRef;
};

#ifdef _DEBUG
	void DebugMessageType(LPCSTR t, CSMSG_TYPE c);
	DWORD PrintWin32Error(LPCSTR pszErrorString);
#else
	#define DebugMessageType(t, c)	// Do nothing
	#define PrintWin32Error(t)
#endif

#endif // _BASECHAN_H
