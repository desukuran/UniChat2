// UC2.h : main header file for the UC2 application
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_UC2_H__A1313869_A610_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_UC2_H__A1313869_A610_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUC2App:
// See UC2.cpp for the implementation of this class
//
class CStage;
class CMemberInfo;

class CUC2App : public CWinApp
{
public:
	CUC2App();

// Attributes
	BOOL	GetPause() const	{ return m_bPause; }

// Operations
	void	SetStage(CStage* pStage)	{ m_pStage = pStage; }
	void	SetPause(const BOOL bPause)	{ m_bPause = bPause; }

//	BOOL	GetMagicVoicePath(CString& str);
	BOOL	GetUniChatKey(PHKEY phkey, REGSAM samDesired=KEY_READ);
	BOOL	CreateUniChatKey();
	BOOL	GetUniChatRoot(CString& str);
	BOOL	RegSetMemberInfo(CMemberInfo& mi);
	BOOL	RegGetMemberInfo(CMemberInfo& mi);
	BOOL	RegGetNick(CString& strNick);
	BOOL	RegSetNick(const CString& strNick);
	int		RegGetConnType();
	BOOL	RegSetConnType(const int nConnType);
	int		RegGetTimeOut();
	int		RegGetStageSec();	// delay in a stage
	BOOL	RegGetUserID(CString& strID);
	BOOL	RegGetLastStageID(CString& strSID);
	BOOL	RegSetLastStageID(const CString& strSID);
	BOOL	RegGetServer(CString& strServer);
	BOOL	RegSetServer(const CString& strServer);
	int		RegGetBubbleTextLength();
	BOOL	RegSetBubbleTextLength(const int nLen);
	int		RegGetBubbleTime();
	BOOL	RegSetBubbleTime(const int nMS);

	CString	m_strUniChatRoot;
	CString	m_strVersion;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUC2App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStage*		m_pStage;
	BOOL		m_bPause;

	//{{AFX_MSG(CUC2App)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpDevelopers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UC2_H__A1313869_A610_11D1_80E2_080009B9F339__INCLUDED_)
