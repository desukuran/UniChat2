//
//	COSBView: Off-Screen Buffered View
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "DIB.h"
#include "DIBPal.h"
#include "OSBView.h"
#include "PhSprite.h"	// 	AddDirtyRegion(CPhasedSprite* pPS);
#include "Bubble.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
//#if !defined(KSM_REPORT)
//	#define KSM_REPORT
//#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// COSBView

IMPLEMENT_DYNCREATE(COSBView, CScrollView)

BEGIN_MESSAGE_MAP(COSBView, CScrollView)
	//{{AFX_MSG_MAP(COSBView)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSBView construction/destruction

COSBView::COSBView()
{
	m_pOSB			= NULL;
	m_pOSBPal		= NULL;
	m_hDIBSection	= NULL;
	m_pOneToOneClrTab = NULL;

	BOOL	bUseCreateDIBSection = FALSE;
	// See if we are on Win32s which exports CreateDIBSection but does not support it
	DWORD dwVer = ::GetVersion();
	if ((dwVer & 0x800000FF) != 0x080000003)
	{
		// Not on Win32s so try to get the CreateDIBSection procedure address.
		HANDLE hMod = ::GetModuleHandle("gdi32");
		if (hMod)
		{
			m_pCreateDIBSection = (CDSPROC*)GetProcAddress((HMODULE)hMod, "CreateDIBSection");
			if (m_pCreateDIBSection)
				bUseCreateDIBSection = TRUE;
		}
	}
	if (!bUseCreateDIBSection)
	{
		AfxMessageBox("Sorry, This Program is only for Windows 95 and NT.");
		PostMessage(WM_CLOSE);
	}
}

COSBView::~COSBView()
{
	if (m_pOSB)				delete m_pOSB;
	if (m_pOSBPal)			delete m_pOSBPal;
	if (m_pOneToOneClrTab)	free(m_pOneToOneClrTab);
	if (m_hDIBSection)		::DeleteObject(m_hDIBSection);
	EmptyDirtyList();
}

// Create a new buffer, tables and palette to match a supplied DIB.
BOOL COSBView::CreateOSB(CDIB* pDIB)
{
	TRACE("COSBView::CreateOSB(%lx)\n", pDIB);
	// Create the 1-to-1 palette index table.
	if (m_pOneToOneClrTab)
		free(m_pOneToOneClrTab);
	m_pOneToOneClrTab = (LPBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(WORD));
	if (!m_pOneToOneClrTab)
	{
		TRACE("Failed to create color table\n");
		return FALSE;
	}

	// Set up the table header to match the DIB by copying the header
	// and then constructing the 1-to-1 index translation table.
	::CopyMemory(m_pOneToOneClrTab, pDIB->GetBitmapInfoAddress(), sizeof(BITMAPINFOHEADER));
	// make sure the length of the table is set to 256 not to
	// the number of colors in the DIB which is irrelevant
	m_pOneToOneClrTab->bmiHeader.biClrUsed = 0; // default (256) 
	WORD* pIndex = (LPWORD)((LPBYTE)m_pOneToOneClrTab + sizeof(BITMAPINFOHEADER));
	for (int i = 0; i < 256; i++)
		*pIndex++ = (WORD)i;

	// Create a palette from the DIB so that we can use it to do screen drawing.
	if (m_pOSBPal)
		delete m_pOSBPal;
	m_pOSBPal = new CDIBPal;
	ASSERT(m_pOSBPal);
	if (m_pOSBPal->Create(pDIB))
	{	// Map the colors so that we get an identity palette.
		m_pOSBPal->SetSysPalColors();
	}
	else
	{
		TRACE("Failed to create palette\n");
		delete m_pOSBPal;
		m_pOSBPal = NULL;
		return FALSE;
	}

	// Delete any existing DIB and create a new one.
	if (m_pOSB)
		delete m_pOSB;
	m_pOSB = new CDIB;
	BOOL bResult = FALSE;
//	if (m_bUseCreateDIBSection)
//	{
	if (m_hDIBSection)
		::DeleteObject(m_hDIBSection);
	ASSERT(m_pCreateDIBSection);
	CDC* pDC = GetDC();
	CPalette* pPalOld = pDC->SelectPalette(m_pOSBPal, FALSE);	// foreground
	pDC->RealizePalette();
	BYTE* pBits = NULL;
	// The CreateDIBSection function creates a device-independent bitmap (DIB)
	// that applications can write to directly.
	m_hDIBSection = (*m_pCreateDIBSection)(pDC->GetSafeHdc(),	// CreateDIBSection
				m_pOneToOneClrTab, DIB_PAL_COLORS, (VOID**)&pBits, NULL, 0);
	pDC->SelectPalette(pPalOld, FALSE);
	ASSERT(m_hDIBSection);
	ASSERT(pBits);
	ReleaseDC(pDC);	// int CWnd::ReleaseDC(CDC* pDC);
  	bResult = m_pOSB->Create(pDIB->GetBitmapInfoAddress(), pBits);
//	}
//	else
//	{
//		bResult = m_pOSB->Create(pDIB->GetWidth(), pDIB->GetHeight());
//	} 
	if (!bResult)
	{
		TRACE("Failed to create off-screen DIB\n");
		delete m_pOSB;
		m_pOSB = NULL;
		return FALSE;
	}

	CSize sizeTotal(m_pOSB->GetWidth(), m_pOSB->GetHeight());
	SetScrollSizes(MM_TEXT, sizeTotal);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// COSBView drawing

void COSBView::OnInitialUpdate()
{
	CSize sizeTotal;
	if (m_pOSB)
	{
		sizeTotal.cx = m_pOSB->GetWidth();
		sizeTotal.cy = m_pOSB->GetHeight();
	}
	else
	{
		sizeTotal.cx = 640;
		sizeTotal.cy = 480;
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
	CScrollView::OnInitialUpdate();
}

// Updated Feb 16 '98 Soomin, Kim
void COSBView::OnDraw(CDC* pDC)
{
//	CView::OnDraw(pDC);	// OnPrepareDC
	CRect rc;	// Invalid Rect
	pDC->GetClipBox(rc);
//	TRACE("COSBView::OnDraw(%d,%d,%d,%d) W:%d,H:%d\n",
//			rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height());
	DrawOSB(&rc);
}

/////////////////////////////////////////////////////////////////////////////
// COSBView diagnostics

#ifdef _DEBUG
void COSBView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COSBView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDocument* COSBView::GetDocument() // Non-debug version is inline
{
	return m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSBView message handlers

// Draw a section of the off-screen image buffer to the screen.
void COSBView::DrawOSB(CRect* pClipRect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);	// CScroll changes the viewport origin and mapping mode.
	CRect rcDraw;

	// Make sure we have what we need to do a paint.
	if (!m_pOSB || !m_pOneToOneClrTab)
	{
		TRACE("COSBView::DrawOSB() - No DIB or color table to paint from.\n");
		return;
	}
	// See if a clip rect was supplied, and use the client area if not.
	if (pClipRect)
	{
		rcDraw = *pClipRect;
	}
	else
	{
		GetClientRect(rcDraw);
		dc.DPtoLP(&rcDraw);		// THIS WAS THE KEY!
	}

	// Get the clip box.
	CRect rcClip;
	dc.GetClipBox(rcClip);

	// Create a rect for the DIB.
	CRect rcDIB(0, 0, m_pOSB->GetWidth()-1, m_pOSB->GetHeight()-1);

	// Find a rectangle that describes the intersection of the draw rect,
	// clip rect, and DIB rect.
	CRect rcBlt = rcDraw & rcClip & rcDIB;

	// Copy the update rectangle from the off-screen DC to the window DC.
	// Note that the DIB origin is the bottom-left corner.
	int w = rcBlt.right - rcBlt.left;
	int h = rcBlt.bottom - rcBlt.top;
	if (w == 0 && h == 0)
		return;		// nothing to draw
	int xs, ys, xd, yd;
	xs = xd = rcBlt.left;
//	ys = (m_bUseCreateDIBSection) ? rcBlt.top : m_pOSB->GetHeight() - rcBlt.bottom;
	ys = yd = rcBlt.top;

	// If we have a palette, select and realize it.
	CPalette* ppalOld = NULL;
	if (m_pOSBPal)
	{
		ppalOld = dc.SelectPalette(m_pOSBPal, FALSE);	// foreground
		dc.RealizePalette();
	}

//	if (m_bUseCreateDIBSection)
//	{
	HDC dcMem = ::CreateCompatibleDC(dc.GetSafeHdc());
	HBITMAP hbmOld = (HBITMAP)::SelectObject(dcMem, m_hDIBSection);

	// Note: you do not need to select the palette into the memory DC
	// because the DIB section is using palette index values not colors.
	::BitBlt(dc.GetSafeHdc(), xd, yd, w, h,	dcMem, xs, ys, SRCCOPY);
	::SelectObject(dcMem, hbmOld);
	::DeleteDC(dcMem);
//		CDC dcMem;
//		dcMem.CreateCompatibleDC(&dc);	// pass NULL to be compatible with system display
//		CBitmap* bmpOld = dcMem.SelectObject(CBitmap::FromHandle(m_hDIBSection));
//		dc.BitBlt(xd, yd, w, h, &dcMem, xs, ys,	SRCCOPY);
//		dcMem.SelectObject(bmpOld);
//		dcMem.DeleteDC();
/*	}
	else
	{
		BYTE* pBits = (BYTE*)m_pOSB->GetBitsAddress();
		::StretchDIBits(dc.GetSafeHdc(),
				xd, yd, w, h,		// Destination	x, y, width, height
				xs,	ys,	w, h,		// Source		x, y, width, height
				pBits,				// Pointer to bits
				m_pOneToOneClrTab,	// BITMAPINFO
				DIB_PAL_COLORS,		// Options
				SRCCOPY);			// ROP
	}
*/
	// Select old palette if we altered it.
	if (ppalOld)
		dc.SelectPalette(ppalOld, FALSE);
#ifdef _DEBUG_RENDER
	static int D_DrawCount = 0;
	if (D_DrawCount++ % 100 == 0)
		TRACE3("COSBView::Draw(W:%d,H:%d)=%d times\n", w, h, D_DrawCount);
#endif
}

// Add a region to the dirty list.
void COSBView::AddDirtyRegion(CRect* prcNew)
{
	// Get the rectangle currently at the top of the list.
	POSITION pos = m_DirtyList.GetHeadPosition();
	if (pos)
	{
		CRect* prcTop = (CRect*)m_DirtyList.GetNext(pos);
		CRect rcTest;
		// If the new one intersects the top one merge them.
		if (rcTest.IntersectRect(prcTop, prcNew))
		{
			prcTop->UnionRect(prcTop, prcNew);
			return;
		}
	}
	// List is empty, or there was no intersection.
	CRect* prc = new CRect;
	*prc = *prcNew; // Copy the data.
	// Add a new rectangle to the list.
	m_DirtyList.AddHead((CObject*)prc);
}

void COSBView::AddDirtyRegion(CPhasedSprite* pPS)
{
//	if (!pPS)
//		return;
	CRect rcDirty;
	pPS->GetRect(rcDirty);
	AddDirtyRegion(&rcDirty);
}

void COSBView::AddDirtyRegion(CBubble* pBB)
{
	CRect rcDirty;
	pBB->GetRect(rcDirty);
	AddDirtyRegion(&rcDirty);
}

// Render and draw all the dirty regions.
void COSBView::RenderAndDrawDirtyList()
{
	POSITION pos = m_DirtyList.GetHeadPosition();
	// Render all the dirty regions.
	while (pos)
	{
		// Get the next region.
		CRect* pRect = (CRect*)m_DirtyList.GetNext(pos);
		// Render it.
		Render(pRect);
	}
	// Draw all the dirty regions to the screen.
	while (!m_DirtyList.IsEmpty())
	{
		// Get the next region.
		CRect* pRect = (CRect*)m_DirtyList.RemoveHead();
		DrawOSB(pRect);
//		InvalidateRect(pRect, FALSE);	// Convert to LP
		// Done with it.
		delete pRect;
	}
}

// Empty the dirty list.
void COSBView::EmptyDirtyList()
{
	while (!m_DirtyList.IsEmpty())
	{
		CRect* prc = (CRect*)m_DirtyList.RemoveHead();
		delete prc;
	}
}

// Update the view to reflect some change in the doc.
void COSBView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Render and draw everything.
	Render();
//	DrawOSB();
	Invalidate(FALSE);
}

///////////////////////////////////////////////////////////////////////////////////
// Palette Control

void COSBView::OnPaletteChanged(CWnd* pFocusWnd)
{
	TRACE0("COSBView::OnPaletteChanged\n");
	// See if the change was caused by us and ignore it if not.
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

// Note: Windows actually ignores the return value.
BOOL COSBView::OnQueryNewPalette()
{
	TRACE0("COSBView::OnQueryNewPalette\n");
	// We are going active so realize our palette.
	if (m_pOSBPal)
	{
		CDC* pdc = GetDC();
		CPalette* poldpal = pdc->SelectPalette(m_pOSBPal, FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (poldpal)
			pdc->SelectPalette(poldpal, FALSE);
		ReleaseDC(pdc);
		if (u)
		{	// Some colors changed so we need to do a repaint.
			Invalidate(); // Repaint the lot.
			return TRUE; // Say we did something.
		}
	}
	return FALSE; // Say we did nothing.
}
