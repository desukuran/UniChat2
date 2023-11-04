// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "resource.h"

#include <lzexpand.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_TEST_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	WORD wOp = 0x0010;
	for (int i=0; i < 50; i++)
	{
		wOp <<= 1;
		TRACE("%2d)%08x\n", i, wOp);
	}
/*
	CFile f;
	!f.Open("test.z", CFile::modeRead | CFile::shareDenyWrite);	// | CFile::typeText))
	char* pBuf;
	char pLine[2048];
	WORD	wFileType;
	f.Read(&wFileType, sizeof(wFileType));
	BOOL bLZ = (wFileType == 0x5a53);	// 'SZ'	LZ Compressed
	UINT hLZFile;
	if (bLZ)
		hLZFile = ::LZInit(f.m_hFile);
	long lFileSize = bLZ	? ::LZSeek(f.m_hFile, 0L, 2)
							: f.GetLength();	// points to the end of file
	TRACE("FileSize=%ld bytes\n",  lFileSize);
	if (bLZ)
		::LZSeek(hLZFile, 0, 0);  // seek to beginning of file
	else
		f.Seek(0, CFile::begin);
	lFileSize *= 5;
	pBuf = new char[lFileSize];
	::ZeroMemory(pBuf, lFileSize);
	int iBytes = bLZ	? ::LZRead(hLZFile, pBuf, lFileSize)
						: f.Read(pBuf, lFileSize);
	TRACE("%d bytes read\n", iBytes);
//	pBuf[iBytes] = NULL;
	::LZClose(hLZFile);
	f.Close();
	char* pBegin = pBuf;
	char* pNL;
	while (pNL = strstr(pBegin, "\r\n"))
	{
		int nSize = pNL - pBegin + 1;
		::CopyMemory(pLine, pBegin, nSize);
		pLine[nSize-1] = NULL;
		TRACE(pLine);
		TRACE("\n");
		pBegin += (nSize + 1);
	}
	TRACE("%x,%x", '\r', '\n');
	delete [] pBuf;
*/
	CTime t(1998,4,19,12,10,0);
	CFileStatus fs;
	if (CFile::GetStatus("test.txt", fs))
	{
		fs.m_mtime = t;
		CFile::SetStatus("test.txt", fs);
	}
}
