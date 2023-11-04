// JunAsyncMF.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "JunAsyncMF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJunAsyncMF

CJunAsyncMF::CJunAsyncMF()
{
}

CJunAsyncMF::~CJunAsyncMF()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CJunAsyncMF, CAsyncMonikerFile)
	//{{AFX_MSG_MAP(CJunAsyncMF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CJunAsyncMF member functions

void CJunAsyncMF::OnDataAvailable(DWORD dwSize, DWORD bscfFlag) 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunAsyncMF::OnDataAvailable\n");
	TRACE("dwSize = %ld , bscfFlag = %ld\n", dwSize, bscfFlag);
	
	CAsyncMonikerFile::OnDataAvailable(dwSize, bscfFlag);
}

void CJunAsyncMF::OnStartBinding(DWORD grfBSCOPTION) 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunAsyncMF::OnStartBinding\n");
	
	//CAsyncMonikerFile::OnStartBinding(grfBSCOPTION);
}

void CJunAsyncMF::OnStopBinding(HRESULT hresult, LPCTSTR szError) 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunAsyncMF::OnStopBinding\n");
	TRACE("hresult = %d\n", hresult);
	CAsyncMonikerFile::OnStopBinding(hresult, szError);
}

void CJunAsyncMF::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
		ULONG ulStatusCode, LPCTSTR szStatusText)
{
	TRACE("CJunAsyncMF::OnProgress\n");
	TRACE("ulProgress : %ld\n", ulProgress);
	TRACE("ulProgressMax : %ld\n", ulProgressMax);
	TRACE("ulStatusCode :  %ld\n", ulStatusCode);
	TRACE("szStatusText : %s\n", szStatusText);

	CAsyncMonikerFile::OnProgress(ulProgress, ulProgressMax, ulStatusCode, szStatusText);
}

