// UC2View.h : interface of the CUC2View class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_UC2VIEW_H__A1313871_A610_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_UC2VIEW_H__A1313871_A610_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2Ani/OSBView.h"

class CActor;
class CPSFrame;

class CUC2View : public COSBView
{
protected: // create from serialization only
	CUC2View();
	DECLARE_DYNCREATE(CUC2View)

// Attributes
public:
	CUC2Doc* GetDocument();
	BOOL			HasVoiceCap() const		{ return m_bVoiceCap; }

// Operations
public:
	virtual BOOL	CreateOSB(CDIB* pDIB);			// COSBView
	virtual void	Render(CRect* pClipRect=NULL);	// COSBView
	void			AdjustFrameWindow();
	void			NewStageLoaded();
	void			SetActor(CActor* pA)	{ m_pActor = pA; }
	BOOL			PunchAvailable() const;
	void			SaveLastHitTick()	{ m_dwLastHitTick = ::GetTickCount(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUC2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	int			OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	void		OnProperties();

private:
	CActor*		m_pActor;	// pointer to current sprite (menu)
	BOOL		m_bFirstDraw;
	UINT		m_uTimer;
	DWORD		m_dwChannelStartTick;	// Ticks on starting this channel
	DWORD		m_dwSoundAlarmTick;
	DWORD		m_dwStageMSPT;			// Delay in a stage
	DWORD		m_dwLastHitTick;		// Last punch
	BOOL		m_bVoiceCap;
	CPSFrame*	m_pPropFrame;

// Generated message map functions
protected:
	//{{AFX_MSG(CUC2View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewAdjustWindow();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActorVoice();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnIgnore();
	afx_msg void OnKickout();
	afx_msg void OnMakehost();
	afx_msg void OnWhisper();
	afx_msg void OnUpdateViewAdjustWindow(CCmdUI* pCmdUI);
	afx_msg void OnActorHyperlink();
	afx_msg void OnViewBubbleTextlimit();
	afx_msg void OnViewBubbleTime();
	//}}AFX_MSG
	afx_msg void OnActorAction(UINT nID);
	afx_msg void OnActorState(UINT nID);
	afx_msg void OnActorMove(UINT nID);
	afx_msg void OnActorTurn(UINT nID);
//	void	OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/* MALL
	afx_msg void OnViewPda();
	afx_msg void OnViewIm();
	afx_msg void OnViewTitanic();
	afx_msg void OnViewMap();
	afx_msg void OnViewPdaMusic();
*/

#ifndef _DEBUG  // debug version in UC2View.cpp
inline CUC2Doc* CUC2View::GetDocument()
   { return (CUC2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UC2VIEW_H__A1313871_A610_11D1_80E2_080009B9F339__INCLUDED_)
