// UC2View.cpp : implementation of the CUC2View class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "UC2.h"

#include "UC2Doc.h"
#include "UC2View.h"
#include "MainFrm.h"
#include "ResMan.h"
#include "Stage.h"
#include "TileMap.h"
#include "Actor.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/PhSprite.h"
#include "UC2Ani/Sound.h"
#include "UC2Ani/MCIObj.h"
#include "EditSend.h"
#include "Parser.h"
#include "UC2CS.h"
#include "WhisperDlg.h"
#include "PPMemberInfo1.h"
#include "PSFrame.h"
//#include <hlink.h>		// "urlmon.h"  HlinkSimpleNavigateToString
#include "InputIntDlg.h"
#ifdef _MALL
#include "DlgPDA.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan	gResMan;
extern CParser	gParser;
const int	ACTOR_AREA_PIXEL=50;	// cursor display
const DWORD	TIMER_MSPT=1000L;
const DWORD PUNCH_MSPT=15*1000;

/////////////////////////////////////////////////////////////////////////////
// CUC2View

IMPLEMENT_DYNCREATE(CUC2View, COSBView)

BEGIN_MESSAGE_MAP(CUC2View, COSBView)
	//{{AFX_MSG_MAP(CUC2View)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_VIEW_ADJUST_WINDOW, OnViewAdjustWindow)
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ACTOR_VOICE, OnActorVoice)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(ID_IGNORE, OnIgnore)
	ON_COMMAND(ID_KICKOUT, OnKickout)
	ON_COMMAND(ID_MAKEHOST, OnMakehost)
	ON_COMMAND(ID_WHISPER, OnWhisper)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ADJUST_WINDOW, OnUpdateViewAdjustWindow)
	ON_COMMAND(ID_ACTOR_HYPERLINK, OnActorHyperlink)
	ON_COMMAND(ID_VIEW_BUBBLE_TEXTLIMIT, OnViewBubbleTextlimit)
	ON_COMMAND(ID_VIEW_BUBBLE_TIME, OnViewBubbleTime)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ACTOR_PROP, OnProperties)
	ON_COMMAND_RANGE(ID_ACTOR_ACTION_0, ID_ACTOR_ACTION_9, OnActorAction)
	ON_COMMAND_RANGE(ID_ACTOR_STATE_0, ID_ACTOR_STATE_2, OnActorState)
	ON_COMMAND_RANGE(ID_ACTOR_MOVE_F, ID_ACTOR_MOVE_B, OnActorMove)
	ON_COMMAND_RANGE(ID_ACTOR_TURN_L, ID_ACTOR_TURN_R, OnActorTurn)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
//	ON_NOTIFY(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()

/* MALL
	ON_COMMAND(ID_VIEW_PDA, OnViewPda)
	ON_COMMAND(ID_VIEW_IM, OnViewIm)
	ON_COMMAND(ID_VIEW_TITANIC, OnViewTitanic)
	ON_COMMAND(ID_VIEW_MAP, OnViewMap)
	ON_COMMAND(ID_VIEW_PDA_MUSIC, OnViewPdaMusic)
*/
/////////////////////////////////////////////////////////////////////////////
// CUC2View construction/destruction

CUC2View::CUC2View()
{
	TRACE0("CUC2View::CUC2View()\n");
	m_bFirstDraw	= TRUE;
	m_pActor		= NULL;
	m_uTimer		= 0;
	// for Stage
	m_dwChannelStartTick	= 0L;
	m_dwSoundAlarmTick		= 0L;
	m_dwLastHitTick			= 0L;
	m_bVoiceCap				= FALSE;
	m_pPropFrame			= NULL;
}

CUC2View::~CUC2View()
{
	TRACE0("CUC2View::~CUC2View()\n");
}

BOOL CUC2View::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE0("CUC2View::PreCreateWindow()\n");
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COSBView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUC2View drawing

void CUC2View::OnDraw(CDC* pDC)
{
//	CUC2Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	if (m_bFirstDraw)	// This is the moment when the user can apparently see this window.
	{
		TRACE0("CUC2View::OnDraw() - First call\n");
		m_bFirstDraw = FALSE;
		CEditSend* pES = GetDocument()->GetEditSend();
		if (pES)
			pES->SetFocus();
//		CSplashWnd::HideSplashScreen();
//		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COMMAND, (WPARAM)IDC_BTN_CREATE, (LPARAM)0);
#ifdef _MALL
		GetDocument()->ToggleDemo();
#endif
	}
	COSBView::OnDraw(pDC);
}

void CUC2View::OnInitialUpdate()
{
	TRACE0("CUC2View::OnInitialUpdate()\n");
	COSBView::OnInitialUpdate();
	
	CMainFrame* pMF = (CMainFrame*)GetParentFrame();
	ASSERT(pMF);
	CDIB* pDIB = GetOSB();
	ASSERT(pDIB);
	pMF->AdjustFrame(pDIB->GetWidth(), pDIB->GetHeight());
	pMF->InitControlPanel((CPalette*)GetOSBPalette());

	m_dwStageMSPT = ((CUC2App*)AfxGetApp())->RegGetStageSec();
	m_dwStageMSPT *= 1000;
	TRACE("m_dwStageMSPT = %ld\n", m_dwStageMSPT);
	m_uTimer = SetTimer(4001, TIMER_MSPT, NULL);	// 1 sec. term
	if (!m_uTimer)
	{
		AfxMessageBox(IDS_ERROR_TIMER);
	}
	::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COMMAND, (WPARAM)IDC_BTN_CREATE, (LPARAM)0);
//	EnableToolTips();
}

/////////////////////////////////////////////////////////////////////////////
// CUC2View printing

BOOL CUC2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUC2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUC2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUC2View diagnostics

#ifdef _DEBUG
void CUC2View::AssertValid() const
{
	COSBView::AssertValid();
}

void CUC2View::Dump(CDumpContext& dc) const
{
	COSBView::Dump(dc);
}

CUC2Doc* CUC2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUC2Doc)));
	return (CUC2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUC2View message handlers

////////////////////////////////////////////////////////////////////////////
// Frame

// Adjust the frame window to be fit to this OSB
void CUC2View::AdjustFrameWindow()
{
	CMainFrame* pMF = (CMainFrame*)GetParentFrame();
	ASSERT(pMF);
	if (GetDocument()->IsHistoryPanel())
		return;
	CDIB* pDIB = GetOSB();
	ASSERT(pDIB);
	pMF->AdjustFrame(pDIB->GetWidth(), pDIB->GetHeight());
}

////////////////////////////////////////////////////////////////////////////
// OSB: Off-Screen Buffered View

// Create a new buffer and palette to match a new background DIB
// virtual in COSBView
BOOL CUC2View::CreateOSB(CDIB* pDIB)
{
//	m_pCS	= NULL;
//	m_pMS	= NULL;

	// Create a new buffer and palette
	if (!COSBView::CreateOSB(pDIB))
		return FALSE;

	// Map the colors of the background DIB to
	// the identity palette we just created for the background
	pDIB->MapColorsToPalette((CPalette*)GetOSBPalette());

	// Resize the main frame window to fit the background image
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);	// Try shrinking first
	ResizeParentToFit(TRUE);	// Let's be daring

	Render();	// Render the entire scene to the off-screen buffer
//	DrawOSB();	// Paint the off-screen buffer to the window
	Invalidate(FALSE);

	return TRUE;
}

// Render the scene to the off-screen buffer pClipRect defaults to NULL
// virtual in COSBView
void CUC2View::Render(CRect* pClipRect)
{
	CStage* pStage = GetDocument()->GetStage();
	if (pStage)
		pStage->Render(pClipRect);
}

void CUC2View::NewStageLoaded()
{
	m_dwChannelStartTick = m_dwSoundAlarmTick = ::GetTickCount();
}

////////////////////////////////////////////////////////////////////////////
// User Interface
void CUC2View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);

	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;

//	CPhasedSprite* pPS = pStage->AnimatedHitTest(lpt);
	// Assume that we have not CSprite, we have only CPhasedSprite and derived...
	CPhasedSprite* pPS = (CPhasedSprite*)pStage->SpriteHitTest(lpt);
	if (pPS && pPS->HasHyperlink() &&
		(pPS->GetLinkType() == CPhasedSprite::HLINK_HTTP))
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_HGREP_DOWN));
		int n = pPS->GetCellID();
		gParser.CopyBuffer(*pPS->GetHyperlink());
		CString strHL;
		while (gParser.GetValueRightToken(strHL, '|') && n--)
		;

		if (!strHL.IsEmpty())
		{
			((CMainFrame*)AfxGetMainWnd())->ShellBrowseURL(strHL);
			return;
		}
	}

	CActor* pA = pStage->GetThisActor();
	if (pA)
	{
		CRect rcA2;
		pA->GetRect(rcA2);
		rcA2.InflateRect(ACTOR_AREA_PIXEL, ACTOR_AREA_PIXEL);
		if (!rcA2.PtInRect(lpt))
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return;
		}
		CPoint ptA(pA->GetCenter());

		WORD wDA = pA->GetDA();
		WORD wDACursor;
		if (lpt.y < ptA.y)	// Backward
		{
			if (lpt.x < ptA.x)	// DA_BL
			{
				::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW_LT));
				wDACursor = DA_BL;
			}
			else	// DA_BR
			{
				::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW_RT));
				wDACursor = DA_BR;
			}
		}
		else	// Forward
		{
			if (lpt.x < ptA.x)	// DA_FR
			{
				::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW_LB));
				wDACursor = DA_FR;
			}
			else	// DA_FL
			{
				::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW_RB));
				wDACursor = DA_FL;
			}
		}

		if (wDACursor == wDA)
			OnActorMove(ID_ACTOR_MOVE_F);
		else
		{
			int nID;
			switch (wDACursor)
			{
			case DA_FR:	nID = (wDA == DA_BL) ?  ID_ACTOR_TURN_L : ID_ACTOR_TURN_R;	break;
			case DA_FL:	nID = (wDA == DA_FR) ?  ID_ACTOR_TURN_L : ID_ACTOR_TURN_R;	break;
			case DA_BR:	nID = (wDA == DA_FL) ?  ID_ACTOR_TURN_L : ID_ACTOR_TURN_R;	break;
			case DA_BL:	nID = (wDA == DA_BR) ?  ID_ACTOR_TURN_L : ID_ACTOR_TURN_R;	break;
			default:	nID = ID_ACTOR_TURN_L;
			}
			OnActorTurn(nID);
		}
	}
	else
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
//	COSBView::OnLButtonDown(nFlags, point);
}

void CUC2View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);
/*
	CUC2Doc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;
// For Demo
	static int nChar=0;
	CActor* pActor = pStage->CreateActor(nChar, lpt, FALSE);// AS_STAND | DA_FR, (nChar%4 == 0));
	pActor->Act(CMD_STAND + nChar % 24);
	if (++nChar >= 18)
		nChar = 0;
	m_pActor = pActor;

	RenderAndDrawDirtyList();
*/
//	COSBView::OnLButtonDblClk(nFlags, point);
}

void CUC2View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);
	
	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;

//	CPhasedSprite* pPS = pStage->AnimatedHitTest(lpt);
	CPhasedSprite* pPS = (CPhasedSprite*)pStage->SpriteHitTest(lpt);
	if (pPS && pPS->HasHyperlink() &&
		(pPS->GetLinkType() == CPhasedSprite::HLINK_HTTP))
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_HGREP_UP));
		return;
	}

	CActor* pA = pStage->GetThisActor();
	if (pA)
	{
		CRect rcA;
		pA->GetRect(rcA);
		CRect rcA2(rcA);
		rcA2.InflateRect(ACTOR_AREA_PIXEL, ACTOR_AREA_PIXEL);
		if (!rcA2.PtInRect(lpt) || rcA.PtInRect(lpt))
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return;
		}
		CPoint ptA(pA->GetCenter());
		if (lpt.x < ptA.x)
		{
			::SetCursor(AfxGetApp()->LoadCursor((lpt.y < ptA.y) ?
						IDC_ARROW_LT : IDC_ARROW_LB));
		}
		else
		{
			::SetCursor(AfxGetApp()->LoadCursor((lpt.y < ptA.y) ?
						IDC_ARROW_RT : IDC_ARROW_RB));
		}
	}
	else
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
//	COSBView::OnMouseMove(nFlags, point);
}

void CUC2View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScrollView changes the viewport origin and mapping mode.
	CPoint lpt(point);
	dc.DPtoLP(&lpt);

	CUC2Doc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;

	CPhasedSprite* pPS = pStage->AnimatedHitTest(lpt);
	if (!pPS || (pPS->GetSrcType() != SPRITE_ACTOR))
		return;
//	ASSERT(pPS->IsKindOf(RUNTIME_CLASS(CActor)));
	m_pActor = (CActor*)pPS;

	BOOL bThis = (m_pActor == pDoc->GetThisActor());
	CMenu menu;
	VERIFY(menu.LoadMenu(bThis ? IDR_MENU_ACTOR : IDR_MENU_ACTOR_OTHER));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);

	CString strVer;
	int nVer = m_pActor->m_mi.GetVersion();
	strVer.Format(" V%d.%02d", nVer / 100, nVer % 100);
	CString strInfo(*(m_pActor->m_mi.GetNick()) + _T("(") + *(m_pActor->m_mi.GetRealName()) + _T(")"));
	if (strInfo.GetLength() > 30)
	{
		strInfo.ReleaseBuffer(30);
	}
	strInfo += strVer;
	if (m_pActor->IsMemberHost())
		strInfo += "<HOST>";
	pPopup->ModifyMenu(ID_ACTOR_PROP, MF_BYCOMMAND | MF_STRING,
						ID_ACTOR_PROP, strInfo);

	if (HasVoiceCap())
	{
		if (m_pActor->IsVoice())
			pPopup->CheckMenuItem(ID_ACTOR_VOICE, MF_CHECKED);
	}
	else
	{
		pPopup->EnableMenuItem(ID_ACTOR_VOICE, MF_GRAYED);
	}

	if (bThis)
	{
		switch (m_pActor->GetState() & AS_MASK)
		{
		case AS_STAND:
			pPopup->CheckMenuItem(ID_ACTOR_STATE_0, MF_CHECKED);	break;
		case AS_MORPH:
			{
			pPopup->CheckMenuItem(ID_ACTOR_STATE_1, MF_CHECKED);
			for (int i=ID_ACTOR_ACTION_0; i < ID_ACTOR_ACTION_7; i++)
				pPopup->EnableMenuItem(ID_ACTOR_ACTION_0, MF_GRAYED);
			}
			break;
		case AS_DOZE:
			pPopup->CheckMenuItem(ID_ACTOR_STATE_2, MF_CHECKED);	break;
		}
	}
	else
	{
		if (m_pActor->IsMemberIgnored())
			pPopup->CheckMenuItem(ID_IGNORE, MF_CHECKED);

		CUC2Channel* pChannel = pDoc->GetChannel();
		if (pChannel && !pChannel->FAmIHost())
		{
			pPopup->EnableMenuItem(ID_KICKOUT, MF_GRAYED);
			pPopup->EnableMenuItem(ID_MAKEHOST, MF_GRAYED);
		}
		if (m_pActor->IsMemberHost())
			pPopup->CheckMenuItem(ID_MAKEHOST, MF_CHECKED);
		pPopup->EnableMenuItem(ID_ACTOR_HYPERLINK,
				m_pActor->m_mi.HasHyperlink() ? MF_CHECKED : MF_GRAYED);
	}

	ClientToScreen(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
//	COSBView::OnRButtonDown(nFlags, point);
}

void CUC2View::OnViewAdjustWindow() 
{
	AdjustFrameWindow();
}

void CUC2View::OnUpdateViewAdjustWindow(CCmdUI* pCmdUI) 
{
	GetDocument()->IsHistoryPanel();
}

void CUC2View::OnSetFocus(CWnd* pOldWnd) 
{
	COSBView::OnSetFocus(pOldWnd);

	if (m_bFirstDraw)	// not initialized yet
		return;
	CEditSend* pES = GetDocument()->GetEditSend();
	if (pES)
		pES->SetFocus();
}
/*
int CUC2View::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	CRect rc(0, 0, 300, 300);
	if (rc.PtInRect(point))
	{
		ASSERT(pTI);
		pTI->hwnd = m_hWnd;
		pTI->rect = rc;
		pTI->uId = IDC_BTN_CREATE;
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		return 1;
	}
	return CView::OnToolHitTest(point, pTI);
}

void CUC2View::OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult)
{
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMH;
	UINT nID = pNMH->idFrom;
	if (pTTT->uFlags & TTF_IDISHWND)
	{
		nID = ::GetDlgCtrlID((HWND)nID);
		ASSERT(nID);
	}
	pTTT->lpszText = MAKEINTRESOURCE(nID);
	pTTT->hinst = AfxGetResourceHandle();
}
*/

BOOL CUC2View::PunchAvailable() const
{
	return ((::GetTickCount() - m_dwLastHitTick) >= PUNCH_MSPT);
}

void CUC2View::OnActorAction(UINT nID) 
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->SendCommand(CMD_SMILE + nID - ID_ACTOR_ACTION_0);
/*//	For Demo
	if (!m_pActor)
		return;
	m_pActor->Act(CMD_SMILE + nID - ID_ACTOR_ACTION_0);
*/
}

void CUC2View::OnActorState(UINT nID) 
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->SendCommand(CMD_STAND + nID - ID_ACTOR_STATE_0);
/*//	For Demo
	if (!m_pActor)
		return;
	m_pActor->Act(CMD_STAND + nID - ID_ACTOR_STATE_0);
*/
}

void CUC2View::OnActorMove(UINT nID) 
{
	CUC2Doc* pDoc = GetDocument();
	if (pDoc->IsDemo())
		return;
	pDoc->SendMoveCommand(CMD_MOVEF + nID - ID_ACTOR_MOVE_F);
/*//	For Demo
	if (!m_pActor)
		return;

	CStage* pStage = GetDocument()->GetStage();
	if (!pStage)
		return;
	pStage->ActorMove(m_pActor, nID == ID_ACTOR_MOVE_F);
*/
}

void CUC2View::OnActorTurn(UINT nID)
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->SendCommand(CMD_TURNL + nID - ID_ACTOR_TURN_L);
/*//	For Demo
	if (!m_pActor)
		return;
	m_pActor->Act(CMD_TURNL + nID - ID_ACTOR_TURN_L);
*/
}

void CUC2View::OnActorVoice()
{
	if (!m_pActor)
		return;
}

void CUC2View::OnDestroy()
{
	COSBView::OnDestroy();
	if (m_uTimer)
		KillTimer(m_uTimer);
}

void CUC2View::OnTimer(UINT nIDEvent)
{
	CUC2Doc* pDoc = GetDocument();
	CStage* pStage = pDoc->GetStage();
	if (!pStage)
		return;

	DWORD dwCurTick = ::GetTickCount();
	if (dwCurTick > m_dwSoundAlarmTick)
	{
		if (pDoc->IsSoundOn())
			pStage->PlayBGM();

		DWORD dwRand = (DWORD)(1*90*1000 + rand() % (3*60*1000));
		m_dwSoundAlarmTick = dwCurTick + dwRand;
		TRACE("Music play queued after %.2f min.\n",
				float(m_dwSoundAlarmTick - dwCurTick)/(60*1000L));
	}
	if (!pStage->IsExitOpen() &&
		(dwCurTick - m_dwChannelStartTick) > m_dwStageMSPT)
	{
		pStage->SetExitOpen();	// Open passages to other channels
	}
/*
	if (pDoc->GetUC2Mode() & UC2MODE_DEMO)
	{
		UC2Demo();
	}
*/
//	COSBView::OnTimer(nIDEvent);
}

void CUC2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
/*	CUC2Doc* pDoc = GetDocument();
//	if (pDoc->GetThisActor() == NULL)
//		return;
	// switch for input key
	switch (nChar)
	{
//	case VK_UP:		pDoc->SendCommand(CMD_MOVE_NORTH);	break;
//	case VK_LEFT:	pDoc->SendCommand(CMD_MOVE_WEST);	break;
//	case VK_DOWN:	pDoc->SendCommand(CMD_MOVE_SOUTH);	break;
//	case VK_RIGHT:	pDoc->SendCommand(CMD_MOVE_EAST);	break;
//	case VK_F5:		SetMode(0);	break;
//	case VK_F6:		SetMode(1);	break;
//	case VK_F7:		SetMode(1);	break;
//	case VK_F8:		SetMode(2);	break;
//	case VK_F9:		SetMode(3);	break;
//	case VK_F10:	SetMode(4);	break;
	}
	// Show current state in the status bar
//	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
//	ASSERT(pFrame);
//	pFrame->m_wndStatusBar.SetWindowText(buf);
*/	COSBView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CUC2View::OnIgnore()
{
	if (!m_pActor)
		return;
	PICS_MEMBER pM = m_pActor->m_mi.GetMember();
	if (!pM)
		return;
	BOOL bIgnored = (pM->HrIsMemberIgnored() == NOERROR);
	bIgnored = !bIgnored;
	pM->HrSetIgnoreMember(bIgnored);	// returns NOERROR if successful
	m_pActor->Act(bIgnored ? CMD_DOZE : CMD_STAND);
//	GetDocument()->WhisperTo(m_pActor, _T("무시 중입니다."));
	pM->Release();
}

void CUC2View::OnKickout()
{
	if (!m_pActor)
		return;
	PICS_MEMBER pM = m_pActor->m_mi.GetMember();
	if (!pM)
		return;
	CWhisperDlg dlg;
	dlg.m_strToID = _T("To ") + *m_pActor->m_mi.GetNick();
	if ((dlg.DoModal() == IDOK) && !dlg.m_strText.IsEmpty())
	{
		int len = dlg.m_strText.GetLength();
		char* pSz = dlg.m_strText.GetBuffer(len);
		pM->HrCloseA(pSz);
	}
	pM->Release();
}

void CUC2View::OnMakehost()
{
	if (!m_pActor)
		return;
	PICS_MEMBER pM = m_pActor->m_mi.GetMember();
	if (!pM)
		return;
	pM->HrMakeHost();
	pM->Release();
}

void CUC2View::OnWhisper()
{
	if (!m_pActor)
		return;
	CWhisperDlg dlg;
	dlg.m_strToID = *m_pActor->m_mi.GetNick();
	if ((dlg.DoModal() == IDOK) && !dlg.m_strText.IsEmpty())
	{
		GetDocument()->WhisperTo(m_pActor, dlg.m_strText);
	}
}

void CUC2View::OnProperties()
{
	if (!m_pActor)
		return;

	if (!m_pPropFrame)
	{
		m_pPropFrame = new CPSFrame;
		CRect rect(0, 0, 0, 0);
		CString strTitle;
		VERIFY(strTitle.LoadString(IDS_ACTOR_PROPSHT_CAPTION));

		if (!m_pPropFrame->Create(NULL, strTitle, WS_POPUP | WS_CAPTION | WS_SYSMENU, rect, this))
		{
			delete m_pPropFrame;
			m_pPropFrame = NULL;
			return;
		}
		m_pPropFrame->CenterWindow();
	}

	if (m_pPropFrame)	// After creation
	{
		// Before unhiding the modeless property sheet, update its settings appropriately.
		// For example, if you are reflecting the state of the currently selected item,
		// pick up that information from the active view and change the property sheet settings now.
		CPPMemberInfo1& page1 = m_pPropFrame->m_pModelessPropSheet->m_Page1;
		page1.m_strNick		= *m_pActor->m_mi.GetNick();
		page1.m_strUserID	= *m_pActor->m_mi.GetUserID();
		page1.m_strRealName	= *m_pActor->m_mi.GetRealName();
		page1.m_strSexAge.Format("%s %d", (m_pActor->m_mi.GetSex() == 0) ? _T("M") : _T("F"),
								m_pActor->m_mi.GetAge());
		int nVer = m_pActor->m_mi.GetVersion();
		page1.m_strVersion.Format("%d.%02d", nVer / 100, nVer % 100);
		page1.UpdateData(FALSE);
		m_pPropFrame->m_pModelessPropSheet->SetActivePage(&page1);

		CPPMemberInfo2& page2 = m_pPropFrame->m_pModelessPropSheet->m_Page2;
		page2.m_strProfile	= *m_pActor->m_mi.GetProfile();

		if (!m_pPropFrame->IsWindowVisible())
			m_pPropFrame->ShowWindow(SW_SHOW);
	}
}

void CUC2View::OnActorHyperlink() 
{
	if (m_pActor && m_pActor->m_mi.HasHyperlink())
	{
		CMainFrame* pMF = (CMainFrame*)GetParentFrame();
		ASSERT(pMF);
		pMF->ShellBrowseURL(*m_pActor->m_mi.GetHyperlink());
	}
}

void CUC2View::OnViewBubbleTextlimit() 
{
	CInputIntDlg dlg;
	CString strTitle;
	strTitle.LoadString(IDS_ENTER_BUBBLE_TEXT_LIMIT);
	dlg.SetTitle(strTitle);
	CUC2App* pApp = (CUC2App*)AfxGetApp();
	dlg.m_nVal = pApp->RegGetBubbleTextLength();
	dlg.SetDefaultVal(gResMan.GetDefaultBubbleTextLimit());
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_nVal < 0)
			dlg.m_nVal = 0;
		gResMan.SetBubbleTextLimit(dlg.m_nVal);
		pApp->RegSetBubbleTextLength(dlg.m_nVal);
	}
}

void CUC2View::OnViewBubbleTime() 
{
	CInputIntDlg dlg;
	CString strTitle;
	strTitle.LoadString(IDS_ENTER_BUBBLE_TIME);
	dlg.SetTitle(strTitle);
	CUC2App* pApp = (CUC2App*)AfxGetApp();
	dlg.m_nVal = pApp->RegGetBubbleTime()/1000;
	dlg.SetDefaultVal(gResMan.GetDefaultBubbleTime()/1000);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_nVal < 0)
			dlg.m_nVal = 0;
		gResMan.SetBubbleTime(dlg.m_nVal*1000);
		pApp->RegSetBubbleTime(gResMan.GetBubbleTime());
	}
}

#ifdef _MALL
void CUC2View::OnViewPda() 
{
	CDlgPDA pda("MPAniU.bmp", "MPAniL.bmp", 6);
	pda.SetMode(TRUE, TRUE);
	if (pda.DoModal() == IDOK)
	{
	}
}

void CUC2View::OnViewPdaMusic() 
{
	CDlgPDA pda("MPAniUM.bmp", "MPAniLM.bmp", 4);
	pda.SetMode(TRUE, TRUE);
	if (pda.DoModal() == IDOK)
	{
	}
}

void CUC2View::OnViewIm() 
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->ShowIMDemo();
}

void CUC2View::OnViewTitanic() 
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->ShowTitanicDemo();
}

void CUC2View::OnViewMap() 
{
	CUC2Doc* pDoc = GetDocument();
	pDoc->ShowMapDemo();
}
#endif
