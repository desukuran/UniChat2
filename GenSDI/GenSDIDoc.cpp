// GenSDIDoc.cpp : implementation of the CGenSDIDoc class
//

#include "stdafx.h"
#include "GenSDI.h"

#include "GenSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenSDIDoc

IMPLEMENT_DYNCREATE(CGenSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGenSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGenSDIDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenSDIDoc construction/destruction

CGenSDIDoc::CGenSDIDoc()
{
	TRACE("CGenSDIDoc::CGenSDIDoc()\n");
}

CGenSDIDoc::~CGenSDIDoc()
{
	TRACE("CGenSDIDoc::~CGenSDIDoc()\n");
}

BOOL CGenSDIDoc::OnNewDocument()
{
	TRACE("CGenSDIDoc::OnNewDocument()\n");
	if (!CDocument::OnNewDocument())
		return FALSE;
	TRACE("\tCDocument::OnNewDocument();\n");

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGenSDIDoc serialization

void CGenSDIDoc::Serialize(CArchive& ar)
{
	TRACE("CGenSDIDoc::Serialize(CArchive& ar)\n");
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGenSDIDoc diagnostics

#ifdef _DEBUG
void CGenSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGenSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenSDIDoc commands

void CGenSDIDoc::OnFileOpen() 
{
	TRACE("CGenSDIDoc::OnFileOpen()\n");
	CFileDialog dlg(TRUE,	// Open
					NULL,	// No default extension
					NULL,	// Initial file name
					OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
					"CPP Files|*.CPP| All files (*.*)|*.*||");
//    if (dlg.DoModal() == IDOK)
	dlg.DoModal();
}
