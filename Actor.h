// Actor.h: interface for the CActor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTOR_H__C78B9066_A908_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_ACTOR_H__C78B9066_A908_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2Ani/PhSprite.h"
#include "UC2Messages.h"
#include "TileMap.h"	// DA_...
#include "MemberInfo.h"

class CBehavior;
class CBubble;
class CSprite;

class CActor : public CPhasedSprite
{
public:
	CActor();
	virtual ~CActor();
// Attributes
	int				GetCharID() const	{ return m_mi.GetCharID(); }
	int				GetColorSet() const	{ return m_nColorSet; }
	CBubble*		GetBubble()	const	{ return m_pBB; }
	WORD			GetState() const	{ return m_mi.GetState(); }
	WORD			GetDA() const	{ return (m_mi.GetState() & DA_MASK); }
	WORD			GetTurnNextDA() const;
	WORD			GetTurnPrevDA() const;
	BOOL			IsMoving() const	{ return m_bMoving; }
	void			SetShadow(CSprite* pS)	{ m_pShadow = pS; }
	BOOL			IsVoice() const		{ return m_bVoice; }

	PICS_MEMBER		GetMember()			{ return m_mi.GetMember(); }
	const CString*	GetNick() const		{ return m_mi.GetNick(); }
	void			GetMemberInfo(CMemberInfo& mi);
	int				GetGender() const	{ return m_mi.GetSex(); }	// 0: Male, 1: Female, 2: Child, ...
	BOOL			IsMemberIgnored() const;
	BOOL			IsMemberHost() const;

// Operations
	virtual void	SetLT(const int x, const int y);	// For Shadow
	virtual void	SetImOp(const WORD wImOp);			// For Shadow
	virtual void	Render(CDIB* pDIB, const CRect* pClipRect=NULL);	// For Shadow

	void			SetTileMap(CTileMap* pTM)		{ m_pTM = pTM; }
	void			SetCharID(const int nCharID)	{ m_mi.SetCharID(nCharID); }
	void			SetColorSet(const int nCS)	{ m_nColorSet = nCS; }
	BOOL			SetBehavior(const int bi, const BOOL bAlarm=TRUE);
	BOOL			SetState(const WORD wState, const BOOL bChanging=TRUE)
					{ m_mi.SetState(wState); return BasicStance(bChanging); }
	BOOL			SetSA(const WORD wSA, const BOOL bChanging=TRUE)
					{ m_mi.SetSA(wSA); return BasicStance(bChanging); }
	BOOL			SetDA(const WORD wDA, const BOOL bChanging=TRUE)
					{ m_mi.SetDA(wDA); return BasicStance(bChanging); }
	virtual BOOL	HeartBeat(const DWORD dwCurTick);	// ticker
	BOOL			Act(const int nCmd);
	BOOL			MoveTo(const CPoint& ptDest, const int nEA, const BOOL bForward=TRUE);
	void			Chat(const CString& strText);

	// Attach the PICS member interface object to this CActor object
	BOOL			Attach(PICS_MEMBER pMem)	{ return m_mi.SetMember(pMem); }
	void			InitState(CMemberInfo& mi);

	CMemberInfo	m_mi;

protected:
	BOOL			BasicStance(const BOOL bChanging=TRUE);	// Show changing cuts
	void			AdjustBubblePosition();

	BOOL		m_bMoving;	// Actor is moving, do not interrupt
	int			m_nColorSet;
	CBehavior*	m_pBeh;		// pointer to the CBehavior obj
	int			m_nRepeat;	// current Repeat count for behavior
	CBubble*	m_pBB;		// holds an instance for the CBubble
//	CQueue		m_ActionQ;
	BOOL		m_bVoice;
// for movement
	CPoint		m_ptDestEarth;
	int			m_nDestElev;
	BOOL		m_bForward;
	CSprite*	m_pShadow;
	CTileMap*	m_pTM;
};

#endif // !defined(AFX_ACTOR_H__C78B9066_A908_11D1_80E2_080009B9F339__INCLUDED_)
