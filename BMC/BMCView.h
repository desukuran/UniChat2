// BMCView.h : interface of the CBMCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMCVIEW_H__C193E4B0_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
#define AFX_BMCVIEW_H__C193E4B0_88DD_11D1_ACEA_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../UC2Ani/OSBView.h"

class CSprite;
class CPhasedSprite;
class CBMCDoc;

class CBMCView : public COSBView
{
protected: // create from serialization only
	CBMCView();
	DECLARE_DYNCREATE(CBMCView)

// Attributes
public:
	CBMCDoc* GetDocument();
	CPhasedSprite*	GetCapturedSprite()		{ return m_pCapturedSprite; }

// Operations
public:
	BOOL			NewBackground(CDIB* pDIB);
	virtual void	Render(CRect* pClipRect=NULL);
	void			NewSprite(CSprite* pSprite);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMCView)
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
	void ToggleOutline();
	virtual ~CBMCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	BOOL			m_bMouseCaptured;	// TRUE if mouse captured
	CPhasedSprite*	m_pCapturedSprite;	// Pointer to captured sprite (for drag)
	CPoint			m_ptOffset;			// offset into hit sprite
	CPhasedSprite*	m_pMenuSprite;		// ptr to current sprite

//	typedef PALETTEENTRY* LPPALETTEENTRY;
//	LPPALETTEENTRY*	m_apPE;			// array of pointers to the palette entries
//	int				m_nPEs;
	PALETTEENTRY*	m_aSubPE;		// array of palette entries (Substitutional palette)

	void	SetSpriteZ(int z);
	void	SetSpriteCols(int i);
	void	SetSpriteRows(int i);
	void	ShowInfo(CPoint& point, CPhasedSprite* pSprite);

// Generated message map functions
protected:
	//{{AFX_MSG(CBMCView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVIEW640x480();
	afx_msg void OnVIEW800x600();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BMCView.cpp
inline CBMCDoc* CBMCView::GetDocument()
   { return (CBMCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMCVIEW_H__C193E4B0_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
