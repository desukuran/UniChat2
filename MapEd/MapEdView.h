// MapEdView.h : interface of the CMapEdView class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_MAPEDVIEW_H__7ECC1E0E_9C09_11D1_80E2_288A06C10000__INCLUDED_)
#define AFX_MAPEDVIEW_H__7ECC1E0E_9C09_11D1_80E2_288A06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../UC2Ani/OSBView.h"

class CSprite;
class CPhasedSprite;
class CMapEdDoc;
class CStage;

class CMapEdView : public COSBView
{
protected: // create from serialization only
	CMapEdView();
	DECLARE_DYNCREATE(CMapEdView)

// Attributes
public:
	CMapEdDoc* GetDocument();

// Operations
public:
	virtual BOOL	CreateOSB(CDIB* pDIB);			// COSBView
	virtual void	Render(CRect* pClipRect=NULL);	// COSBView
	CPhasedSprite*	GetCapturedSprite() { return m_pCS;	}
	void			AdjustFrameWindow();
	void			RecalculateDA();
	void			SynchronizeEA();

private:
	void	SetEntryExitPoint(const BOOL bEntry);
	void	ShowInfo(const CPoint& point, const CPoint& ptTID);

	BOOL			m_bMouseCaptured;	// TRUE if mouse captured
	CPhasedSprite*	m_pCS;				// pointer to captured sprite (for drag)
	CSize			m_sOffset;			// offset into hit sprite
	CPhasedSprite*	m_pMS;				// pointer to current sprite
	CPoint			m_ptHit;			// Hit point
	WORD			m_wCurResType;		// Current Resource Type

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEdView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapEdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	void	ChangeSpriteImOp(const int nMenu);
	void	AnimateSprite(CPhasedSprite* pS, const WORD wAniType);
	void	OnMenuDirectionAttribute(const WORD wDA);

	//{{AFX_MSG(CMapEdView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSpriteDelete();
	afx_msg void OnSpriteElevation();
	afx_msg void OnSpriteFlip();
	afx_msg void OnSpriteOpacity100();
	afx_msg void OnSpriteOpacity12();
	afx_msg void OnSpriteOpacity25();
	afx_msg void OnSpriteOpacity50();
	afx_msg void OnSpriteVertical();
	afx_msg void OnSpriteFlipvert();
	afx_msg void OnSpriteType();
	afx_msg void OnMenuAniRepeat();
	afx_msg void OnMenuAniFade();
	afx_msg void OnMenuNoani();
	afx_msg void OnSpriteOpacity75();
	afx_msg void OnActorElevation();
	afx_msg void OnMenuAniRandom();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMenuDaFr();
	afx_msg void OnMenuDaBl();
	afx_msg void OnMenuDaBr();
	afx_msg void OnMenuDaFl();
	afx_msg void OnMenuDaOpen();
	afx_msg void OnMenuDaClosed();
	afx_msg void OnMenuExitPoint();
	afx_msg void OnMenuEntryPoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEdView.cpp
inline CMapEdDoc* CMapEdView::GetDocument()
   { return (CMapEdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDVIEW_H__7ECC1E0E_9C09_11D1_80E2_288A06C10000__INCLUDED_)
