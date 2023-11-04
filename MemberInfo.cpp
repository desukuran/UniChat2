// MemberInfo.cpp : implementation of the classes for protocol
//

#include "stdafx.h"
#include "MemberInfo.h"
#include "Parser.h"
#include "Actor.h"
#include "Behavior.h"
#ifndef MAPEDITOR
#include "UC2.h"
#include "MainFrm.h"	// GetUserID
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CParser gParser;

/////////////////////////////////////////////////////////////////////////////
// CMemberInfo
CMemberInfo::CMemberInfo()
{
	m_pMember		= NULL;
	m_nCharID		= 0;
	m_nSex			= SEX_MAN;
	m_nAge			= 20;
	m_nBubbleKind	= m_nSex;
	m_nVersion		= CLIENT_VERSION;
	m_nBehavior		= AB_STANDINGF;
	m_wState		= AS_STAND | DA_FR;
	m_ptTID			= CPoint(5,11);
}

CMemberInfo::~CMemberInfo()
{
	if (m_pMember)
		m_pMember->Release();
}

CMemberInfo& CMemberInfo::operator=(const CMemberInfo& mi)	// mi from
{
	if (this == &mi)
		return *this;

	if (m_pMember)
		m_pMember->Release();
	m_pMember		= mi.GetMember();	// NULL for actors in script mode
	m_nVersion		= mi.GetVersion();
	m_nCharID		= mi.GetCharID();
	m_nSex			= mi.GetSex();
	m_nAge			= mi.GetAge();
	m_nBubbleKind	= mi.GetBubbleKind();
	m_strNick		= *mi.GetNick();
	m_strRealName	= *mi.GetRealName();
	m_strProfile	= *mi.GetProfile();
	m_strUserID		= *mi.GetUserID();
	m_strHyperlink	= *mi.GetHyperlink();
	m_nBehavior		= mi.GetBehavior();
	m_wState		= mi.GetState();
	m_ptTID			= mi.GetTileID();
	return *this;
}

CMemberInfo::CMemberInfo(const CMemberInfo& mi)	// Copy Constructor
{
	*this = mi;
}

BOOL CMemberInfo::SetMember(PICS_MEMBER pMember)
{
	if (m_pMember)
	{
		m_pMember->Release();
	}
	m_pMember = pMember;
	if (m_pMember)
	{
		m_pMember->AddRef();
		BYTE*	pb;
		BOOL	fAnsi;
		HRESULT hr = m_pMember->HrGetName(&pb, &fAnsi);
		if (!FAILED(hr) && fAnsi)
			m_strNick = (char*)pb;
		return TRUE;
	}
	return FALSE;
}

const PICS_MEMBER CMemberInfo::GetMember() const
{
	if (m_pMember)
		m_pMember->AddRef();
	return m_pMember;
}

// Set this member info from the specified string
BOOL CMemberInfo::SetMemberInfo(const char* src)
{
//`nActorID`nBubbleKind`strHandle`strRealName`strProfile`ptBase`nHDir`strUserID(`)
	gParser.CopyBuffer(src);
	if (!gParser.GetValueRightToken(m_nVersion,		UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_nCharID,		UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_nSex,			UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_nAge,			UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_nBubbleKind,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_strNick,		UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_strRealName,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_strProfile,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_strUserID,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_strHyperlink,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_nBehavior,	UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_wState,		UC2TOKEN))	return FALSE;
	if (!gParser.GetValueRightToken(m_ptTID,		UC2TOKEN))	return FALSE;
	return TRUE;
}

// Get this member info to the specified string
void CMemberInfo::GetMemberInfo(CString& str) const
{
	str.Format("%d`%d`%d`%d`%d,`%s`%s`%s`%s`%s`%d`%d`(%d,%d)`",
		m_nVersion, m_nCharID, m_nSex, m_nAge, m_nBubbleKind,
		m_strNick, m_strRealName, m_strProfile, m_strUserID, m_strHyperlink,
		m_nBehavior, m_wState, m_ptTID.x, m_ptTID.y);
}

void CMemberInfo::SetNick(LPCSTR szNick)
{
	m_strNick = szNick;
	if (m_strNick.GetLength() > 20)
		m_strNick.ReleaseBuffer(20);
}

void CMemberInfo::SetRealName(LPCSTR szRN)
{
	m_strRealName = szRN;
	if (m_strRealName.GetLength() > 20)
		m_strRealName.ReleaseBuffer(20);
}

void CMemberInfo::SetProfile(LPCSTR szProf)
{
	m_strProfile = szProf;
	if (m_strProfile.GetLength() > 256)
		m_strProfile.ReleaseBuffer(256);
}

#ifndef MAPEDITOR
// Load my member information from the system registry
BOOL CMemberInfo::LoadMyInfo()
{
#ifdef _UNITEL
//	m_strRealName = *((CMainFrame*)AfxGetMainWnd())->GetUserName();
#endif // _UNITEL
//	m_strUserID = *((CMainFrame*)AfxGetMainWnd())->GetUserID();
	return ((CUC2App*)AfxGetApp())->RegGetMemberInfo(*this);
}

BOOL CMemberInfo::SaveMyInfo()
{
	return ((CUC2App*)AfxGetApp())->RegSetMemberInfo(*this);
}
#endif // MAPEDITOR