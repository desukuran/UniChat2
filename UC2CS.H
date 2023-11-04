//==========================================================================
//	CUC2Socket
//	CUC2Channel
//
//	(C) Programmed by Kim, Soomin, Mar 23, 1998
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//==========================================================================
#ifndef __UC2CS_H
#define __UC2CS_H

#include "BaseSock.h"
#include "BaseChan.h"

//--------------------------------------------------------------------------+
// class CUC2Socket

class CUC2Socket : public CBaseSocket
{
public:
	CUC2Socket(const HWND hWnd);
	virtual ~CUC2Socket();

	void			SetReceiver(const HWND hWnd)	{ m_hFrame = hWnd; }
	void			SetQueryClient(const HWND hWnd)	{ m_hQClient = hWnd; }

	enum
	{
		Q_LIST_USERS,
		Q_LIST_CHANNELS,
		Q_CHANNEL_MEMBERS,
		Q_GET_REALNAME
	} QUERY_TYPE;

	BOOL			IsQueryOK() const					{ return m_bQueryOK; }
	void			SetQueryOK(const BOOL bQOK=TRUE)	{ m_bQueryOK = bQOK; }
	int				GetLastQueryType() const			{ return m_LastQType; }
	void			SetLastQueryType(const int nType);
	
	BOOL			FQueryMembersInChannel(const DWORD dwID);
	BOOL			FQueryMembersInChannelName(char* szChannel=NULL);
	BOOL			FQueryListChannels(char* szChannel=NULL, DWORD dwcMin=1, DWORD dwcMax=1000);
	BOOL			FQueryListAllUsers(char* szFind=NULL);
	BOOL			FQueryRealName(char* szNick);
	// Overrides
	virtual BOOL	FOnLogin();
	virtual BOOL	FOnSocketError(HRESULT hr);
	virtual BOOL	FOnAddChannel(PCS_MSGCHANNEL pMsg);
	virtual BOOL	FOnPrivateMsg(PCS_MSGPRIVATE pMsg);
	virtual BOOL	FOnInvite(PCS_MSGINVITE	pcsInvite);
	virtual BOOL	FParseQueryData(PCS_PROPERTY pcsProp);
	virtual BOOL	FUnknownMessage(PCS_MSGBASE pMsg);

	BOOL			PostMessage(UINT message, WPARAM wParam, LPARAM lParam) const
						{ return ::PostMessage(m_hFrame, message, wParam, lParam); }
	BOOL			SendMessage(UINT message, WPARAM wParam, LPARAM lParam) const
						{ return ::SendMessage(m_hFrame, message, wParam, lParam); }

protected:
	HWND			m_hFrame;		// Frame Window to receive messages
	HWND			m_hQClient;		// Query Client to receive query results
	BOOL			m_bQueryOK;		// Limit query if we didn't get the answer yet...
	int				m_LastQType;	// What was the last query type?
	int				m_iItem;		// current item
};

//--------------------------------------------------------------------------+
// class CUC2Channel
class CUC2Channel : public CBaseChannel
{
public:
	CUC2Channel(const HWND hWnd);
	virtual ~CUC2Channel();

	void			SetReceiver(HWND hWnd)		{ m_hFrame = hWnd; }
	// Overrides
	virtual BOOL	FOnChannelError(HRESULT hr);
	virtual BOOL	FOnAddMember(PCS_MSGMEMBER pMsg);
	virtual BOOL	FOnDelMember(PCS_MSGMEMBER pMsg);
	virtual BOOL	FOnDelChannel(PCS_MSGCHANNEL pMsg);
	virtual BOOL	FOnMemberModeChange(PCS_MSGMEMBER pMsg);
	virtual BOOL	FOnChannelModeChange();
	virtual BOOL	FOnNewTopic();
	virtual BOOL	FOnAnsiTextMsg(PCS_MSG pMsg);
	virtual BOOL	FOnDataMsg(PCS_MSG pMsg);
	virtual BOOL	FOnAnsiWhisperTextMsg(PCS_MSGWHISPER pMsg);
	virtual BOOL	FOnAnsiWhisperDataMsg(PCS_MSGWHISPER pMsg);
	virtual BOOL	FOnNewNick(PCS_NEWNICK pMsg);
	virtual BOOL	FUnknownMessage(PCS_MSGBASE pMsg);

	BOOL			PostMessage(UINT message, WPARAM wParam, LPARAM lParam) const
						{ return ::PostMessage(m_hFrame, message, wParam, lParam); }
	BOOL			SendMessage(UINT message, WPARAM wParam, LPARAM lParam) const
						{ return ::SendMessage(m_hFrame, message, wParam, lParam); }

protected:
	HWND			m_hFrame;	// Frame Window to receive messages
};

#endif	// __UC2CS_H