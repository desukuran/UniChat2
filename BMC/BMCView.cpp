// BMCView.cpp : implementation of the CBMCView class
//

#include "stdafx.h"
#include "BMC.h"

#include "BMCDoc.h"
#include "BMCView.h"
#include "MainFrm.h"

#include "../UC2Ani/DIB.h"
#include "../UC2Ani/DIBPal.h"
#include "../UC2Ani/PhSprite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBMCView

IMPLEMENT_DYNCREATE(CBMCView, COSBView)

BEGIN_MESSAGE_MAP(CBMCView, COSBView)
	//{{AFX_MSG_MAP(CBMCView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_640x480, OnVIEW640x480)
	ON_COMMAND(ID_VIEW_800x600, OnVIEW800x600)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMCView construction/destruction

CBMCView::CBMCView()
{
	m_bMouseCaptured = FALSE;
	m_pCapturedSprite = NULL;
	m_aSubPE = new PALETTEENTRY[256];
/*
	m_nPEs = 10;
	m_apPE = new LPPALETTEENTRY[m_nPEs];
	for (int i=0; i < m_nPEs; i++)
	{
		m_apPE[i] = new PALETTEENTRY[256];
	}
*/
}

CBMCView::~CBMCView()
{
	if (m_aSubPE)
		delete [] m_aSubPE;
/*
	if (m_apPE)
	{
		for (int i=0; i < m_nPEs; i++)
		{
			if (m_apPE[i])
				delete [] m_apPE[i];
			m_apPE[i] = NULL;
		}
		delete [] m_apPE;
		m_apPE = NULL;
	}
*/
}

BOOL CBMCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBMCView drawing

void CBMCView::OnDraw(CDC* pDC)
{
//	CBMCDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	COSBView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CBMCView printing

BOOL CBMCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBMCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBMCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBMCView diagnostics

#ifdef _DEBUG
void CBMCView::AssertValid() const
{
	CView::AssertValid();
}

void CBMCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBMCDoc* CBMCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBMCDoc)));
	return (CBMCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBMCView message handlers

void CBMCView::OnInitialUpdate() 
{
	COSBView::OnInitialUpdate();

}

// Create a new buffer and palette to match a new background DIB
BOOL CBMCView::NewBackground(CDIB* pDIB)
{
	m_pCapturedSprite = NULL;
/*
	CDIBPal pal;
	pal.Load((char*)NULL, m_aSubPE);
	pDIB->SetPaletteEntries(0, 256, m_aSubPE);

	static int nPer=10;
	pDIB->ShiftRGBPercent(0, 256, nPer);
	nPer += 10;
*/

	// Create a new buffer and an identity palette
	if (!CreateOSB(pDIB))
		return FALSE;

	// Map the colors of the background DIB to
	// the identity palette we just created for the background in COSBView::Create(CDIB* pDIB)
	pDIB->MapColorsToPalette((CPalette*)GetOSBPalette());

	// Resize the main frame window to fit the background image
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);	// Try shrinking first
	ResizeParentToFit(TRUE);	// Let's be daring

	// Render the entire scene to the off-screen buffer
	Render();
	// Paint the off-screen buffer to the window
	DrawOSB();

	return TRUE;
}

// A new sprite has been added to the document
void CBMCView::NewSprite(CSprite* pSprite)
{
//	CDIBPal pal;
//	pal.Load((char*)NULL, m_aSubPE);
//	pSprite->SetPaletteEntries(0, 256, m_aSubPE);
	static int n=1;
	pSprite->GetDIB()->RotatePaletteIndex(20, 4*4, n*4);
	pSprite->GetDIB()->RotatePaletteIndex(40, 4*4, n*4);
	n++;
	if (n > 4)
		n = 1;
/*
	m_aSubPE[0].peRed	= 0;
	m_aSubPE[0].peGreen	= 0;
	m_aSubPE[0].peBlue	= 0;
	m_aSubPE[0].peFlags = 0;
	m_pCapturedSprite->SetPaletteEntries(18, 1, m_aSubPE);
*/
	// map the colors in the sprite DIB to the
	// palette in the off-screen buffered view
	if (m_pOSBPal)
		pSprite->MapColorsToPalette((CPalette*)m_pOSBPal);

	// Render the scene
	Render();
	// Draw the new scene to the screen
	DrawOSB();
}

// Render the scene to the off-screen buffer
// pClipRect defaults to NULL
void CBMCView::Render(CRect* pClipRect)
{
	CBMCDoc* pDoc = GetDocument();
	CRect rcDraw;

	// get the background DIB and render it
	CDIB* pDIB = pDoc->GetBackground();
	if (pDIB)
	{
		pDIB->GetRect(rcDraw);
		// If a clip rect was supplied use it
		if (pClipRect)
		{
			rcDraw.IntersectRect(pClipRect, &rcDraw);
		}

		// draw the image of the DIB to the os buffer
		ASSERT(m_pOSB);
		pDIB->CopyBits(m_pOSB,       
						rcDraw.left,
						rcDraw.top,     
						rcDraw.right - rcDraw.left,
						rcDraw.bottom - rcDraw.top,
						rcDraw.left, 
						rcDraw.top);
	}

	// Render the sprite list from the bottom of the list to the top
	// Note that we always clip to the background DIB
	CSpriteList* pList = pDoc->GetSpriteList();
	POSITION pos = pList->GetTailPosition();
	CSprite* pSprite;
	while (pos)
	{
		pSprite = pList->GetPrev(pos);
		pSprite->Render(m_pOSB, &rcDraw);
	}                 
}

void CBMCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bMouseCaptured)
		return;

	CBMCDoc* pDoc = GetDocument();
	// See if it hit a sprite
	CSpriteList* pList = pDoc->GetSpriteList();
	CPhasedSprite* pSprite = (CPhasedSprite*)pList->HitTest(point);
	if (pSprite)
	{
		m_bMouseCaptured = TRUE;
		if (pSprite != m_pCapturedSprite)
		{
			m_pCapturedSprite = pSprite;
			TRACE("New Sprite %8.8XH\n", m_pCapturedSprite);
			CString* pstrFileBkg	= pDoc->GetBackground()->GetName();
			CString* pstrFileSprite	= pSprite->GetDIB()->GetName();
			CString strTitle;
			strTitle.Format("(B)%s,(S)%s", *pstrFileBkg, *pstrFileSprite);
			pDoc->SetTitle(strTitle);
		}
		SetCapture();
		m_ptOffset.x = point.x - m_pCapturedSprite->GetX();
		m_ptOffset.y = point.y - m_pCapturedSprite->GetY();
		ShowInfo(point, pSprite);
	}
//	COSBView::OnLButtonDown(nFlags, point);
}

void CBMCView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bMouseCaptured)
	{
		::ReleaseCapture();
		m_bMouseCaptured = FALSE;
	}
//	COSBView::OnLButtonUp(nFlags, point);
}

void CBMCView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bMouseCaptured)
	{
		ASSERT(m_pCapturedSprite);
		m_pCapturedSprite->SetLT(point.x - m_ptOffset.x,
								 point.y - m_ptOffset.y);

		// Render and draw the changes
		RenderAndDrawDirtyList();
		CBMCDoc* pDoc = GetDocument();
		pDoc->SetModifiedFlag(TRUE);
	}
	ShowInfo(point, m_pCapturedSprite);
//	COSBView::OnMouseMove(nFlags, point);
}

void CBMCView::ShowInfo(CPoint& point, CPhasedSprite* pSprite)
{
	// Show current state in the status bar
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	ASSERT(pFrame);
	char buf[256];
	wsprintf(buf, "Cursor: %d,%d. ", point.x, point.y);
	if (pSprite)
	{
		wsprintf(&buf[strlen(buf)], "Sprite: %d,%d,%d Cell: %d,%d.",
				pSprite->GetX(),
				pSprite->GetY(),
				pSprite->GetZ(),
				pSprite->GetCellRow(),
				pSprite->GetCellColumn());
	}
	pFrame->SetStatusBarText(buf);
}

void CBMCView::ToggleOutline()
{
	if (!m_pCapturedSprite)
	{
		AfxMessageBox("Select the Sprite to toggle the outline.");
		return;
	}

//	CDIBPal pal;
//	pal.Load((char*)NULL, m_apPE[0]);

/*
	RGBQUAD* pQ = m_pCapturedSprite->GetClrTabAddress();
	if ((pQ[18].rgbRed		== pQ[19].rgbRed) &&
		(pQ[18].rgbGreen	== pQ[19].rgbGreen) &&
		(pQ[18].rgbBlue		== pQ[19].rgbBlue))
	{
		pQ[18].rgbRed		= 255;
		pQ[18].rgbGreen		= 255;
		pQ[18].rgbBlue		= 0;
		pQ[18].rgbReserved	= 0;
	}
	else
	{
		m_pCapturedSprite->ReplacePaletteIndexValue(18, 19);
	}
*/
/*
	CClientDC dc(this);
	TRIVERTEX        vert [4] ;
	GRADIENT_TRIANGLE    gTri;
	vert [0] .x       =  0;
	vert [0] .y       =  0;
	vert [0] .Red     =  0x0000;
	vert [0] .Green   =  0x0000;
	vert [0] .Blue    =  0x0000;
	vert [0] .Alpha   =  0x0000;
	vert [1] .x       =  100;
	vert [1] .y       =  0;
	vert [1] .Red     =  0x0000;
	vert [1] .Green   =  0x0000;
	vert [1] .Blue    =  0xff00;
	vert [1] .Alpha   =  0x0000;
	vert [2] .x       =  100;
	vert [2] .y       =  32; 
	vert [2] .Red     =  0x0000;
	vert [2] .Green   =  0x0000;
	vert [2] .Blue    =  0xff00;
	vert [2] .Alpha   =  0x0000;
	vert [3] .x       =  0;
	vert [3] .y       =  32;
	vert [3] .Red     =  0xff00;
	vert [3] .Green   =  0xff00;
	vert [3] .Blue    =  0xff00;
	vert [3] .Alpha   =  0x0000;
	gTRi[0].Vertex1   = 0
	gTRi[0].Vertex2   = 1gTRi[0].Vertex3   = 2gTRi[1].Vertex1   = 0
	gTRi[1].Vertex2   = 2gTRi[1].Vertex3   = 3
	::GradientFill(dc.GetSafeHdc(), vert,4,&gTRI,1,GRADIENT_FILL_TRIANGLE);
*/
	m_aSubPE[0].peRed	+= 10;
	if (m_aSubPE[0].peRed > 255)
		m_aSubPE[0].peRed = 0;
	m_aSubPE[0].peGreen	+= 10;
	if (m_aSubPE[0].peGreen > 255)
		m_aSubPE[0].peGreen = 0;
	m_aSubPE[0].peBlue	+= 10;
	if (m_aSubPE[0].peBlue > 255)
		m_aSubPE[0].peBlue = 0;

	m_pCapturedSprite->GetDIB()->SetPaletteEntries(18, 1, m_aSubPE);
	NewSprite(m_pCapturedSprite);
}

void CBMCView::OnVIEW640x480() 
{
	CSize sizeTotal(640, 480);
	CDIB* pDIB;
	pDIB = new CDIB;
	pDIB->Create(sizeTotal.cx, sizeTotal.cy);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CBMCView::OnVIEW800x600() 
{
	// TODO: Add your command handler code here
	
}
