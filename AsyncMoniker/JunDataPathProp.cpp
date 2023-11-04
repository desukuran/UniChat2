// JunDataPathProp.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "JunDataPathProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_STOPBINDING	WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CJunDataPathProp

CJunDataPathProp::CJunDataPathProp()
{
}

CJunDataPathProp::~CJunDataPathProp()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CJunDataPathProp, CDataPathProperty)
	//{{AFX_MSG_MAP(CJunDataPathProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CJunDataPathProp member functions

void CJunDataPathProp::OnStartBinding() 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunDataPathProp::OnStartBinding\n\n");
	CDataPathProperty::OnStartBinding();
}

void CJunDataPathProp::OnStopBinding(HRESULT hresult, LPCTSTR szError) 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunDataPathProp::OnStopBinding\n\n");
	
	AfxGetMainWnd()->PostMessage(WM_STOPBINDING, 0, 0);

	CDataPathProperty::OnStopBinding(hresult, szError);
}

void CJunDataPathProp::OnDataAvailable(DWORD dwSize, DWORD bscfFlag) 
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("CJunDataPathProp::OnDataAvailable\n");
	TRACE("dwSize : %ld  ", dwSize);
	TRACE("  bscfFlag : %ld\n", bscfFlag);

	if( (bscfFlag & BSCF_FIRSTDATANOTIFICATION) != 0)
	{
		TRACE("BSCF_FIRSTDATANOTIFICATION\n\n");
	}

	if( (bscfFlag & BSCF_INTERMEDIATEDATANOTIFICATION) != 0)
	{
		TRACE("BSCF_INTERMEDIATEDATANOTIFICATION\n\n");
	}

	if( (bscfFlag & BSCF_LASTDATANOTIFICATION) != 0)
	{
		TRACE("BSCF_LASTDATANOTIFICATION\n\n");
	}

	if( (bscfFlag & BSCF_DATAFULLYAVAILABLE) != 0)
	{
		TRACE("BSCF_DATAFULLYAVAILABLE\n\n");
	}

	if( (bscfFlag & BSCF_AVAILABLEDATASIZEUNKNOWN) != 0)
	{
		TRACE("BSCF_AVAILABLEDATASIZEUNKNOWN\n\n");
	}

	CDataPathProperty::OnDataAvailable(dwSize, bscfFlag);
}

void CJunDataPathProp::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
		ULONG ulStatusCode, LPCTSTR szStatusText)
{
	TRACE("CJunDataPathProp::OnProgress\n");
	TRACE("ulProgress : %ld\n", ulProgress);
	TRACE("ulProgressMax : %ld\n", ulProgressMax);
	TRACE("ulStatusCode : %ld\n", ulStatusCode);

	if(ulStatusCode == BINDSTATUS_FINDINGRESOURCE)
	{
		TRACE("ulStatusCode :  BINDSTATUS_FINDINGRESOURCE\n");
	}
	else if(ulStatusCode == BINDSTATUS_MIMETYPEAVAILABLE)
	{
		TRACE("ulStatusCode : BINDSTATUS_MIMETYPEAVAILABLE\n");
	}
	else if(ulStatusCode == BINDSTATUS_CONNECTING)
	{
		TRACE("ulStatusCode : BINDSTATUS_CONNECTING\n");
	}
	else if(ulStatusCode == BINDSTATUS_SENDINGREQUEST)
	{	
		TRACE("ulStatusCode : BINDSTATUS_SENDINGREQUEST\n");
	}
	else if(ulStatusCode == BINDSTATUS_REDIRECTING)
	{
		TRACE("ulStatusCode : BINDSTATUS_REDIRECTING\n");
	}
	else if(ulStatusCode == BINDSTATUS_USINGCACHEDCOPY)
	{
		TRACE("ulStatusCode : BINDSTATUS_USINGCACHEDCOPY\n");
	}
	else if(ulStatusCode == BINDSTATUS_BEGINDOWNLOADDATA)
	{
		TRACE("ulStatusCode : BINDSTATUS_BEGINDOWNLOADDATA\n");
	}
	else if(ulStatusCode == BINDSTATUS_DOWNLOADINGDATA)
	{
		TRACE("ulStatusCode : BINDSTATUS_DOWNLOADINGDATA\n");
	}
	else if(ulStatusCode == BINDSTATUS_ENDDOWNLOADDATA)
	{
		TRACE("ulStatusCode : BINDSTATUS_ENDDOWNLOADDATA\n");
	}
	else if(ulStatusCode == BINDSTATUS_CACHEFILENAMEAVAILABLE)
	{
		TRACE("ulStatusCode : BINDSTATUS_CACHEFILENAMEAVAILABLE\n");
	}

	TRACE("szStatusText : %s\n\n", szStatusText);

	CDataPathProperty::OnProgress(ulProgress, ulProgressMax, ulStatusCode, szStatusText);
}
