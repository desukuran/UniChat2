//
//	COSBView:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __OSBVIEW_H
#define __OSBVIEW_H

class CDIB;
class CDIBPal;
class CPhasedSprite;
class CBubble;

// Define the CreateDIBSection function.
typedef HBITMAP (APIENTRY CDSPROC)
				(HDC hDC, BITMAPINFO* pbmi, UINT iUsage,
				VOID** ppvBits, HANDLE hSection, DWORD dwOffset);

class AFX_EXT_CLASS COSBView : public CScrollView
{
protected: // create from serialization only
	COSBView();
	DECLARE_DYNCREATE(COSBView)

// Attributes
public:
	CDocument*	GetDocument();
	CDIB*		GetOSB()		{ return m_pOSB; }
	CDIBPal*	GetOSBPalette()	{ return m_pOSBPal; }
	HBITMAP		GetHBitmap() const	{ return m_hDIBSection; }

// Operations
public:
	virtual BOOL	CreateOSB(CDIB* pDIB);			// Create a new buffer
	void			DrawOSB(CRect* pClipRect=NULL);	// Draw off-screen buffer to screen
	virtual void	Render(CRect* pClipRect=NULL) { return; }
	void			AddDirtyRegion(CRect* pRect);
	void			AddDirtyRegion(CPhasedSprite* pPS);
	void			AddDirtyRegion(CBubble* pBB);
	void			RenderAndDrawDirtyList();

// Implementation
public:
	virtual ~COSBView();
	virtual void	OnDraw(CDC* pDC);	// Overridden to draw this view.
	virtual void	OnInitialUpdate();	// First time after construction.
	virtual void	OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

#ifdef _DEBUG
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext& dc) const;
#endif

protected:
	CDIB*		m_pOSB;			// The DIB buffer.
	CDIBPal*	m_pOSBPal;		// Palette for drawing.
	HBITMAP		m_hDIBSection;	// Bitmap from CreateDIBSection

private:
	BITMAPINFO*	m_pOneToOneClrTab;		// Pointer to 1-to-1 color table
//	BOOL		m_bUseCreateDIBSection;	// Flag
	CDSPROC*	m_pCreateDIBSection;	// Pointer to CreateDIBSection
	CObList		m_DirtyList;			// Dirty regions

	void	EmptyDirtyList();

// Generated message map functions
protected:
	//{{AFX_MSG(COSBView)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debug version in osbview.cpp
inline CDocument* COSBView::GetDocument()
	{ return (CDocument*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#endif // __OSBVIEW_H
