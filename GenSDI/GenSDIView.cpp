// GenSDIView.cpp : implementation of the CGenSDIView class
//

#include "stdafx.h"
#include "GenSDI.h"

#include "GenSDIDoc.h"
#include "GenSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView

IMPLEMENT_DYNCREATE(CGenSDIView, CView)

BEGIN_MESSAGE_MAP(CGenSDIView, CView)
	//{{AFX_MSG_MAP(CGenSDIView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView construction/destruction

CGenSDIView::CGenSDIView()
{
	TRACE("CGenSDIView::CGenSDIView()\n");
}

CGenSDIView::~CGenSDIView()
{
	TRACE("CGenSDIView::~CGenSDIView()\n");
}

BOOL CGenSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE("CGenSDIView::PreCreateWindow(CREATESTRUCT& cs)\n");
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	TRACE("\tCView::PreCreateWindow(cs);\n");
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView drawing

void CGenSDIView::OnDraw(CDC* pDC)
{
	TRACE("CGenSDIView::OnDraw(CDC* %lx)\n", pDC);
	CGenSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView printing

BOOL CGenSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	TRACE("CGenSDIView::OnPreparePrinting(CPrintInfo* %lx)\n", pInfo);
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGenSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	TRACE("CGenSDIView::OnBeginPrinting(CDC*, CPrintInfo*)\n");
	// TODO: add extra initialization before printing
}

void CGenSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	TRACE("CGenSDIView::OnEndPrinting(CDC*, CPrintInfo*)\n");
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView diagnostics

#ifdef _DEBUG
void CGenSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGenSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGenSDIDoc* CGenSDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenSDIDoc)));
	return (CGenSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenSDIView message handlers
