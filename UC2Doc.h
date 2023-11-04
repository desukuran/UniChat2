// UC2Doc.h : interface of the CUC2Doc class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_UC2DOC_H__A131386F_A610_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_UC2DOC_H__A131386F_A610_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2.h"
#include "UC2CS.h"	// EC_CHANNELINFO, CUC2Socket, CUC2Channel

class CStage;
class CUC2View;
class CEditSend;
class CEditHistory;
class CActor;

enum UC2MODE
{
	UC2MODE_OFFLINE	= 0x0000,
	UC2MODE_DEMO	= 0x0001,
	UC2MODE_ONLINE	= 0x0002
};

class CUC2Doc : public CDocument
{
protected: // create from serialization only
	CUC2Doc();
	DECLARE_DYNCREATE(CUC2Doc)

// Attributes
public:
	CUC2View*		GetUC2View();
	CStage*			GetStage()		{ return m_pStage; }
	CActor*			GetThisActor() const;

	BOOL			GetPause() const
					{ return ((CUC2App*)AfxGetApp())->GetPause(); }
	BOOL			IsSoundOn() const		{ return m_bSound; }
	WORD			GetUC2Mode() const		{ return m_wUC2Mode; }
	BOOL			IsDemo() const	{ return (m_wUC2Mode & UC2MODE_DEMO); }
	BOOL			IsHistoryPanel() const	{ return m_bHPanel; }

	CEditSend*		GetEditSend() const;
//	CEditHistory*	GetEditHistory() const;
	CEdit*			GetEditHistory() const;
	void			ClearHistory();
	void			DisplayText(LPCTSTR lpszText);
	void			SendCommand(const int nCmd);
	void			SendMoveCommand(const int nCmd);
	BOOL			WhisperTo(CActor* pA, LPCTSTR szText);

	// ChatSock
	CUC2Socket*		GetSocket()		{ return m_pSocket; }
	CUC2Channel*	GetChannel()	{ return m_pChannel; }
	BOOL			IsInChannel();
	BOOL			IsConnected();

	BOOL			Connect();
	BOOL			Disconnect();
	BOOL			ListChannels();
	BOOL			JoinChannel(LPCTSTR szChannelName=NULL);
	BOOL			SetChannel(PICS_CHANNEL picsChannel);

// Operations
public:
	void			BeginAnimation() const
					{ ((CUC2App*)AfxGetApp())->SetStage(m_pStage); }
	void			EndAnimation() const
					{ ((CUC2App*)AfxGetApp())->SetStage(NULL); }
	void			PauseAnimation(const BOOL bPause) const
					{ ((CUC2App*)AfxGetApp())->SetPause(bPause); }
	void			SetUC2Mode(const WORD wM)	{ m_wUC2Mode = wM; }
	long			Wait(const DWORD dwInterval);	// for demo
	void			ToggleDemo()	{ OnViewDemo(); }	// to expose
	void			EndDemo();

#ifdef	_MALL
	void			ShowMapDemo();
	void			ShowIMDemo();
	void			ShowTitanicDemo();
#endif

	BOOL			SendText(LPCTSTR szText, const BOOL bWhisper=FALSE);
	BOOL			SendData(LPCTSTR szText);

	void			PlayWaveFile(LPCTSTR szFile);
	// ChatSock related methods
	CActor*			GetActor(PICS_MEMBER pMem)	const;

	// ChatSock messages
	LRESULT OnCsAddChannel(WPARAM, LPARAM);
	LRESULT OnCsPrivateMsg(WPARAM, LPARAM);
	LRESULT OnCsQueryData(WPARAM, LPARAM);
	LRESULT OnCsInvite(WPARAM, LPARAM);
	LRESULT OnCsGotMemList(WPARAM, LPARAM);
	LRESULT OnCsAddMember(WPARAM, LPARAM);
	LRESULT OnCsDelMember(WPARAM, LPARAM);
	LRESULT OnCsDelChannel(WPARAM, LPARAM);
	LRESULT OnCsModeMember(WPARAM, LPARAM);
	LRESULT OnCsModeChannel(WPARAM, LPARAM);
	LRESULT OnCsTextA(WPARAM, LPARAM);
	LRESULT OnCsData(WPARAM, LPARAM);
	LRESULT OnCsWhisperText(WPARAM, LPARAM);
	LRESULT OnCsWhisperData(WPARAM, LPARAM);
	LRESULT OnCsNewTopic(WPARAM, LPARAM);
	LRESULT OnCsNewNick(WPARAM, LPARAM);
	LRESULT OnChannelFullRetry(WPARAM, LPARAM);

protected:
	void			LoadStage(LPCTSTR szStageID);
	void			LeaveChannel();
	void			MakeMudChannelInfo(EC_CHANNELINFO& ecInfo);
	BOOL			CreateNewStage();
	BOOL			DownloadDataFiles();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUC2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUC2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CStage*			m_pStage;
	BOOL			m_bSound;
	BOOL			m_bHPanel;	// Is History Panel
	WORD			m_wUC2Mode;
	WORD			m_wSavedState;
	CString			m_strNick;
	CString			m_strStageName;		// to join the channel
	char			m_SNSuffix[2];		// StageName suffix

	// ChatSock API
	CUC2Socket*		m_pSocket;
	CUC2Channel*	m_pChannel;

// Generated message map functions
protected:
	//{{AFX_MSG(CUC2Doc)
	afx_msg void OnViewPause();
	afx_msg void OnUpdateViewPause(CCmdUI* pCmdUI);
	afx_msg void OnViewDemo();
	afx_msg void OnUpdateViewDemo(CCmdUI* pCmdUI);
	afx_msg void OnConnectSync();
	//}}AFX_MSG
	void OnBtnCreate();
	void OnUpdateBtnCreate(CCmdUI* pCmdUI);
	void OnBtnRoom();
	void OnUpdateBtnRoom(CCmdUI* pCmdUI);
	void OnBtnMember();
	void OnUpdateBtnMember(CCmdUI* pCmdUI);
	void OnBtnSound();
	void OnUpdateBtnSound(CCmdUI* pCmdUI);
	void OnBtnHistory();
	void OnUpdateBtnHistory(CCmdUI* pCmdUI);
	void OnBtnQuit();
	void OnUpdateBtnQuit(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UC2DOC_H__A131386F_A610_11D1_80E2_080009B9F339__INCLUDED_)
