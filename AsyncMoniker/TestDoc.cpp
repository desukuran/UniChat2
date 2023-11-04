// TestDoc.cpp : implementation of the CTestDoc class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const LPCTSTR UNICHAT_FTP="ftp://203.241.132.83/UniChat/";
/////////////////////////////////////////////////////////////////////////////
// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
	//{{AFX_MSG_MAP(CTestDoc)
	ON_COMMAND(ID_CHANNELS_C1FOREST, OnChannelsC1forest)
	ON_COMMAND(ID_CHANNELS_C1GARDEN, OnChannelsC1garden)
	ON_COMMAND(ID_CHANNELS_CASTLE1, OnChannelsCastle1)
	ON_COMMAND(ID_CHANNELS_CEMETARY, OnChannelsCemetary)
	ON_COMMAND(ID_CHANNELS_HOUSA, OnChannelsHousa)
	ON_COMMAND(ID_CHANNELS_HOUSB, OnChannelsHousb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDoc construction/destruction

CTestDoc::CTestDoc()
{
	// TODO: add one-time construction code here
	m_bCurrentMIT = FALSE;
	m_bCurrentSIT = FALSE;
	m_strCurrentMIT.Empty();
	m_strCurrentSIT.Empty();
	m_nMITing = 0;
}

CTestDoc::~CTestDoc()
{
}

BOOL CTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	TRACE("CTestDoc::OnNewDocument\n");
	
	//m_dataPP.Open(_T("ftp://88.1.26.2/c1forest.sit"));

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestDoc serialization

void CTestDoc::Serialize(CArchive& ar)
{
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
// CTestDoc diagnostics

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestDoc commands

void CTestDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CTestDoc::OnCloseDocument\n");

	m_dataPPMIT.Close();

	CDocument::OnCloseDocument();
}

void CTestDoc::OnChannelsC1forest() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "0010csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}

}

void CTestDoc::OnChannelsC1garden() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "0020csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}
}

void CTestDoc::OnChannelsCastle1() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "0000csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}
}

void CTestDoc::OnChannelsCemetary() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "1000csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}
}

void CTestDoc::OnChannelsHousa() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "2000csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}
}

void CTestDoc::OnChannelsHousb() 
{
	// TODO: Add your command handler code here
	if(!m_nMITing)
	{
		m_strCurrentMIT = "30000csin.sit";
	
		CString URL(UNICHAT_FTP);
		URL += m_strCurrentMIT;
		m_bCurrentMIT = FALSE;
		m_nMITing = 1;
		m_dataPPMIT.Open(URL);
	}
	else
	{
		AfxMessageBox("Downloadng...");
	}
}

void CTestDoc::SetCurrentMIT(BOOL available)
{
	m_bCurrentMIT = available;	
}

void CTestDoc::SetCurrentSIT(BOOL available)
{
	m_bCurrentSIT = available;	
}

void CTestDoc::OnStopBinding(WPARAM wParam, LPARAM lParam)
{
	TRACE("CTestDoc::OnStopBinding\n");

	m_bCurrentMIT = TRUE;
	m_nMITing = 0;

}
