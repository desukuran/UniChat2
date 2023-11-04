// Behavior.h: interface for the CBehavior class.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_BEHAVIOR_H__C78B9065_A908_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_BEHAVIOR_H__C78B9065_A908_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum ACTOR_BEHAVIORS
{
	AB_STANDF=0,	// State
	AB_STANDB,
	AB_STANDINGF,
	AB_STANDINGB,
	AB_MORPHF,
	AB_MORPHB,
	AB_MORPHINGF,
	AB_MORPHINGB,
	AB_DOZEF,
	AB_DOZEB,
	AB_RES_STATE1,		// reserved
	AB_RES_STATE2,
	AB_WALKF,		// Moving
	AB_WALKB,
	AB_UPF,
	AB_UPB,
	AB_DOWNF,
	AB_DOWNB,
	AB_MORPHWALKF,
	AB_MORPHWALKB,
	AB_RES_MOVE1,
	AB_RES_MOVE2,
	AB_CHAT,		// Gestures
	AB_ENTER,
	AB_EXIT,
	AB_SMILE,
	AB_MAD,
	AB_HELLO,
	AB_CRY,
	AB_SCRATCH,
	AB_PICK,
	AB_SPECIAL,
	AB_WIGGLEB,
	AB_PUNCHF,
	AB_PUNCHB,
	AB_BEATENF,
	AB_BEATENB,
//	AB_TURN180,
//	AB_TURN360,
	AB_RES_ACTION1,
	AB_RES_ACTION2
};

///////////////////////////////////////////////////////////////////
class CBehavior	// Actor Behavior Description
{
public:
	CBehavior();
	~CBehavior();

	typedef struct
	{
		int		nID;		// ID for the cut (frame)
		WORD	wIO;		// IMAGE_OPTION
		int		nTicks;		// ticks for duration
		CPoint	ptDisp;		// displacement
		int		nSI;		// Sound Index
	} Cell;

	BOOL	Load(const int nID);	// Behavior ID
	int		GetID() const			{ return m_nID; }
	Cell*	GetCell(const int n)	{ return (n < m_nCells && n >= 0) ? &m_aCell[n] : NULL; }
	int		GetNumCells()	const	{ return m_nCells; }
	int		GetRepeat()	const		{ return (m_nRepeat > 0) ? m_nRepeat : -m_nRepeat; }
//	BOOL	GetPendulum() const		{ return (m_nRepeat < 0); }
	CSize	GetDisplacement() const	{ return m_sDisp; }
	BOOL	IsNum(const char c) const	{ return (c >= '0' && c <= '9'); }

protected:
	int		m_nID;			// Behavior ID
	int		m_nCells;
	Cell*	m_aCell;		// array of cells
	int		m_nRepeat;		// Repeat count, if (m_nRepeat < 0) bPendulum should be set TRUE
//	BOOL	m_bReturn;		// Return to Original position after repetition.
//	DWORD	m_nRand;		// Random waiting range
	CSize	m_sDisp;		// accumulated displacement
};

///////////////////////////////////////////////////////////////////
// Actor Description
class CTextFileBuffer;

class CActorDesc
{
public:
	CActorDesc();
	~CActorDesc();

	BOOL		Load(CTextFileBuffer& tfb);
	void		SetNumBehaviors(const int n)	{ m_nBehs = n; }
	int			GetNumBehaviors() const		{ return m_nBehs; }
	CString*	GetNick()					{ return &m_strNick; }
	CString*	GetResName()				{ return &m_strResName; }
	int			GetMSPT() const				{ return m_nMSPT; }
	CBehavior*	GetBehavior(const int nID);

protected:
	int			GetIDFromString(const CString& strName) const;

	CString		m_strNick;
	CString		m_strResName;
	int			m_nMSPT;		// Milliseconds per Tick
	int			m_nBehs;
	CBehavior*	m_aBeh;
};

#endif // !defined(AFX_BEHAVIOR_H__C78B9065_A908_11D1_80E2_080009B9F339__INCLUDED_)
