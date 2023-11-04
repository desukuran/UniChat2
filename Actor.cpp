// Actor.cpp: implementation of the CActor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Actor.h"
#include "ResMan.h"
#include "Behavior.h"
#include "UC2Ani/Bubble.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CResMan	gResMan;
const DWORD LONGTIMELATER = 3600000L;	// 1 hour later
const int BUBBLEH=10;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CActor::CActor()
{
	m_pBeh		= NULL;
	m_bMoving	= FALSE;
	m_nRepeat	= 0;
	m_nColorSet	= 0;
	m_bVoice	= FALSE;
	m_pBB		= new CBubble;
// for movement
	m_ptDestEarth = CPoint(0, 0);
	m_nDestElev	= 0;
	m_bForward	= TRUE;
	m_pShadow	= NULL;	// CSprite
	m_pTM		= NULL;
}

CActor::~CActor()
{
	if (m_pShadow)
		delete m_pShadow;
	// CStage::DeleteActor will delete bubble
//	if (m_pBB)
//	{
//		if (m_pStage)
//			m_pStage->GetBubbleList()->Remove(m_pBB);	// remove this bubble
//		delete m_pBB;
//	}
}

BOOL CActor::SetBehavior(const int bi, const BOOL bAlarm)
{
	if (m_bMoving)
	{
		TRACE("CActor::SetBehavior() - Actor is moving...\n");
		return FALSE;
	}
	m_mi.SetBehavior(bi);
	m_pBeh	= gResMan.GetActorBehavior(m_mi.GetCharID(), bi);
	if (!m_pBeh)
	{
		TRACE1("Invalid behavior index %d\n", bi);
		return FALSE;
	}
	m_ai = 0;
	m_bMoving = ((bi >= AB_WALKF) && (bi <= AB_RES_MOVE2));
	m_nRepeat = m_pBeh->GetRepeat();	// save original repeat count
	if (bAlarm)
		SetAlarmTick();		// Respond immediately
	return TRUE;
}

// Basic behavior (stance) needed to be done after any behavior
BOOL CActor::BasicStance(const BOOL bChanging)
{
	switch (m_mi.GetState() & AS_MASK)
	{
	case AS_STAND:
		if (bChanging)
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_STANDINGF : AB_STANDINGB);
		else
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_STANDF : AB_STANDB);
	case AS_MORPH:
		if (bChanging)
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_MORPHINGF : AB_MORPHINGB);
		else
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_MORPHF : AB_MORPHB);
	case AS_DOZE:
		return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_DOZEF : AB_DOZEB);
	}
	TRACE("CActor - Invalid State %xh\n", m_mi.GetState());
	return FALSE;
}

//=========================================================================
// OnIdle
// Returning TRUE means we should render
BOOL CActor::HeartBeat(const DWORD dwCurTick)
{
	if (!m_pBeh)
	{
		TRACE("CActor(%x)::HeartBeat: m_pBeh = NULL\n", this);
		SetAlarmTick(dwCurTick + LONGTIMELATER);
		return FALSE;
	}
	CBehavior::Cell* pC = m_pBeh->GetCell(m_ai); // includes range check
	if (!pC)	// One behavior ended
	{
//		TRACE("CActor(%x)::HeartBeat: Behavior(%d) done.\n", this, m_pBeh->GetID());
		m_ai = 0;	// wrap index

		if (m_bMoving)
		{
			SetElevation(m_nDestElev);
			MoveToEarth(m_ptDestEarth);
			SetZByEarth();
			ASSERT(m_pBB);
			if (m_pBB->IsShown())
				AdjustBubblePosition();
		}
		// if repeat count is infinite(=0) or left, continue this action
		if (m_pBeh->GetRepeat() == 0)	// 0 means infinite loop
			return TRUE;
		if (--m_nRepeat <= 0)
		{
			m_bMoving = FALSE;
			if (m_mi.GetBehavior() >= AB_WALKF)	// otherwise it is a basic stance
				return BasicStance(FALSE);	// do not show changing cuts
			SetAlarmTick(dwCurTick + LONGTIMELATER);
		}
		return FALSE;
	}

	SetCell(pC->nID);	// update the view with the current cell(frame)
	SetImOp((m_mi.GetState() & DA_RIGHT) ? pC->wIO : (pC->wIO | IMAGE_FLIP));	// calls m_pNotifyObj->Change(...
	if (pC->nSI >= 0)
		gResMan.PlayWave(pC->nSI);
	if (pC->ptDisp.x || pC->ptDisp.y)
	{
		WORD wDA = m_mi.GetState() & DA_MASK;
		if (!m_bForward)	// Reverse direction
		{
			if (wDA <= DA_FL)	wDA <<= 2;
			else				wDA >>= 2;
		}
		switch (wDA)
		{
		case DA_FR:	MoveBy(-pC->ptDisp.x, +pC->ptDisp.y);	break;
		case DA_FL:	MoveBy(+pC->ptDisp.x, +pC->ptDisp.y);	break;
		case DA_BR:	MoveBy(+pC->ptDisp.x, -pC->ptDisp.y);	break;
		case DA_BL:	MoveBy(-pC->ptDisp.x, -pC->ptDisp.y);	break;
		}
		if (GetElevation())	// && ((wDA & DA_FORWARD) == wDA))	// increasing z-order
		{
			if (m_ai == 1)	// 0,1,2,3, half the way
				SetZ(GetZ() - 16);	// half the height of the tile
		}
		else
		{
			SetZByEarth();
		}
		ASSERT(m_pBB);
		if (m_pBB->IsShown())
			AdjustBubblePosition();
	}

	// Set Alarm time to be called for the next frame
	SetAlarmTick(dwCurTick + (DWORD)pC->nTicks * GetMSPT());
	m_ai++;
	return TRUE;	// call RenderAndDrawDirtyList() in CStage::TickAll()
}

// FR(1) -> FL(2) -> BR(4) -> BL(8) -> FR(1)
// counter-clockwise
WORD CActor::GetTurnNextDA() const
{
	WORD wDA = m_mi.GetState() & DA_MASK;
	ASSERT(wDA);
	ASSERT(DA_FR == 0x0001);
	ASSERT(DA_BL == 0x0008);
	wDA <<= 1;
	if (wDA > DA_BL)
		wDA = DA_FR;
	return wDA;
}

WORD CActor::GetTurnPrevDA() const
{
	WORD wDA = m_mi.GetState() & DA_MASK;
	ASSERT(wDA);
	ASSERT(DA_FR == 0x0001);
	ASSERT(DA_BL == 0x0008);
	wDA >>= 1;
	if (wDA < DA_FR)
		wDA = DA_BL;
	return wDA;
}

BOOL CActor::Act(const int nCmd)
{
	if (m_bMoving)
	{
		TRACE("CActor::Act() - Actor is moving...\n");
		return FALSE;
	}
	switch (nCmd)
	{
// Position Move
//	case CMD_MOVEF:
//	case CMD_MOVEB:
// State Change
	case CMD_STAND:	return SetSA(AS_STAND);
	case CMD_MORPH:	return SetSA(AS_MORPH);
	case CMD_DOZE:	return SetSA(AS_DOZE);
	case CMD_TURNL:	return SetDA(GetTurnNextDA(), FALSE);
	case CMD_TURNR:	return SetDA(GetTurnPrevDA(), FALSE);
// Actions
	case CMD_CHAT:
	case CMD_HELLO:
		if ((m_mi.GetState() & AS_MORPH) == AS_MORPH)
			return TRUE;	// No behavior will be shown for morphed actor.
		return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_CHAT : AB_WIGGLEB);
	case CMD_ENTER:
	case CMD_EXIT:
	case CMD_SMILE:
	case CMD_MAD:
	case CMD_CRY:
//	case CMD_SCRATCH:
	case CMD_PICK:
	case CMD_SPECIAL:
		if ((m_mi.GetState() & AS_MORPH) == AS_MORPH)
			return TRUE;	// No behavior will be shown for morphed actor.
	case CMD_SCRATCH:
		return SetBehavior(AB_CHAT + nCmd - CMD_CHAT);
	case CMD_PUNCH:
		return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_PUNCHF : AB_PUNCHB);
	case CMD_BEATEN:
		return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_BEATENF : AB_BEATENB);
	}
	return FALSE;
}

BOOL CActor::MoveTo(const CPoint& ptDest, const int nEA, const BOOL bForward)
{
	if (m_bMoving)
	{
		TRACE("CActor::MoveTo() - Actor is moving...\n");
		return FALSE;
	}
	m_ptDestEarth	= ptDest;
	m_nDestElev		= nEA;
	m_bForward		= bForward;
	switch (m_mi.GetState() & AS_MASK)
	{
	case AS_STAND:
	case AS_DOZE:
		if (nEA == GetElevation())
		{
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_WALKF : AB_WALKB);
		}
		else if (nEA > GetElevation())
		{
			if (!bForward)
			{
				SetBehavior(AB_SCRATCH);
				return FALSE;	// can't go up backward
			}
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_UPF : AB_UPB);
		}
		else
		{
			return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_DOWNF : AB_DOWNB);
		}
	case AS_MORPH:
		return SetBehavior((m_mi.GetState() & DA_FORWARD) ? AB_MORPHWALKF : AB_MORPHWALKB);
	}
	return FALSE;
}

void CActor::Chat(const CString& strText)
{
	CString strBubble(strText);
	if (strBubble.GetLength() > gResMan.GetBubbleTextLimit())
	{
		strBubble.GetBufferSetLength(gResMan.GetBubbleTextLimit());
		strBubble.ReleaseBuffer();
		strBubble += "...";
	}

	CRect rcA;	// This Actor's Rectangle
	GetRect(rcA);
	m_pBB->SetKind(m_mi.GetBubbleKind());
	WORD wDA = m_mi.GetState() & DA_MASK;
	if ((wDA == DA_FL) || (wDA == DA_BR))
	{
		m_pBB->SetTextAlign(TA_RIGHT);
		m_pBB->TextOut(rcA.right, rcA.top-BUBBLEH, strBubble);
	}
	else
	{
		m_pBB->SetTextAlign(TA_LEFT);
		m_pBB->TextOut(rcA.left, rcA.top-BUBBLEH, strBubble);
	}
	m_pBB->SetZ(-GetEarthPointY());
	m_pBB->Show(TRUE);

	// Set duration somewhat proportional to the length of the talk
	DWORD dwDelay = gResMan.GetBubbleTime() + strBubble.GetLength() * 80;
//	if (dwDelay > 8000)	// in 1/10 sec unit
//		dwDelay = 8000;
	m_pBB->SetAlarmTick(::GetTickCount() + dwDelay);

	if (m_bMoving)
		return;
#ifdef _KOREAN
	if (strText.Find("¾û¾E) >= 0)			Act(CMD_CRY);
	else if ((strText.Find("ÇÏÇÏ") >= 0) ||
			 (strText.Find("È£È£") >= 0))	Act(CMD_SMILE);
	else if (strText.Find("´çÈ²") >= 0)		Act(CMD_SCRATCH);
	else if (strText.Find("¾È³E) >= 0)		Act(CMD_HELLO);
	else if (strText.Find("¾¾¹ß") >= 0)		Act(CMD_MAD);
	else									Act(CMD_CHAT);	// includes range check
#endif
	SetAlarmTick();		// Force immediate action
}

void CActor::AdjustBubblePosition()
{
	CRect rcA;
	GetRect(rcA);
	if (m_pBB->GetTextAlign() == TA_LEFT)
		m_pBB->MovePosition(rcA.left, rcA.top-BUBBLEH);
	else
		m_pBB->MovePosition(rcA.right, rcA.top-BUBBLEH);
	m_pBB->SetZ(-GetEarthPointY());
}

// virtual
void CActor::Render(CDIB* pDIB, const CRect* pClipRect)
{
	// The sprite Shadow need not have z-order
	// since it is always rendered with CActor
	if (m_pShadow)
		m_pShadow->Render(pDIB, pClipRect);
	CPhasedSprite::Render(pDIB, pClipRect);
}

// virtual in CSprite
void CActor::SetLT(const int x, const int y)
{
	CPhasedSprite::SetLT(x, y);
	if (m_pTM)
	{
		m_mi.SetTileID(m_pTM->GetNearestTileIndex(GetEarthPoint()));
	}
	if (m_pShadow)
	{
		CSize sE(GetEarth());	// of this actor
		CSize sS(m_pShadow->GetWidth()/2, m_pShadow->GetHeight()/2);
		m_pShadow->SetLT(x + sE.cx - sS.cx, y + sE.cy - sS.cy + 2);
	}
}

// virtual
void CActor::SetImOp(const WORD wImOp)
{
	CPhasedSprite::SetImOp(wImOp);
	if (m_pShadow)
		m_pShadow->SetImOp(wImOp);
}

void CActor::InitState(CMemberInfo& mi)
{
	m_mi = mi;
	m_pBB->SetKind(m_mi.GetBubbleKind());
}

void CActor::GetMemberInfo(CMemberInfo& mi)
{
	mi = m_mi;
}

BOOL CActor::IsMemberIgnored() const
{
	PICS_MEMBER pM = m_mi.GetMember();
	if (pM)
	{
		BOOL bIgnored = (pM->HrIsMemberIgnored() == NOERROR);
		pM->Release();
		return bIgnored;
	}
	return TRUE;	// Ignored? Ya~
}

BOOL CActor::IsMemberHost() const
{
	PICS_MEMBER pM = m_mi.GetMember();
	if (pM)
	{
		BOOL fRet = (pM->HrIsMemberHost() == NOERROR);
		pM->Release();
		return fRet;
	}
	return FALSE;
}
