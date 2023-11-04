// UDSGenView.cpp : implementation of the CUDSGenView class
//

#include "stdafx.h"
#include "UDSGen.h"

#include "UDSGenDoc.h"
#include "UDSGenView.h"
#include "TargetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDSGenView

IMPLEMENT_DYNCREATE(CUDSGenView, CFormView)

BEGIN_MESSAGE_MAP(CUDSGenView, CFormView)
	//{{AFX_MSG_MAP(CUDSGenView)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDSGenView construction/destruction

CUDSGenView::CUDSGenView()
	: CFormView(CUDSGenView::IDD)
{
	//{{AFX_DATA_INIT(CUDSGenView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CUDSGenView::~CUDSGenView()
{
}

void CUDSGenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDSGenView)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgress);
	DDX_Control(pDX, IDC_LIST1, m_lstSource);
	//}}AFX_DATA_MAP
}

BOOL CUDSGenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUDSGenView printing

BOOL CUDSGenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUDSGenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUDSGenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CUDSGenView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CUDSGenView diagnostics

#ifdef _DEBUG
void CUDSGenView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUDSGenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CUDSGenDoc* CUDSGenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUDSGenDoc)));
	return (CUDSGenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUDSGenView message handlers

void CUDSGenView::OnGenerate() 
{
	TRACE("CUDSGenView::OnGenerate\n");

	// TODO: Add your control notification handler code here
	CTargetDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString fn = dlg.m_strTargetFile;
		fn += ".uds";
		GetDocument()->Generate(fn);
	}
}


void CUDSGenView::SetFilename(CString fileName)
{
	CStatic* title = (CStatic*)GetDlgItem(IDC_TARGET);
	title->SetWindowText(fileName);
}
