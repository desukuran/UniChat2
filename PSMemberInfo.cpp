// PSMemberInfo.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PSMemberInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSMemberInfo

IMPLEMENT_DYNAMIC(CPSMemberInfo, CPropertySheet)

CPSMemberInfo::CPSMemberInfo(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CPSMemberInfo::~CPSMemberInfo()
{
}


BEGIN_MESSAGE_MAP(CPSMemberInfo, CPropertySheet)
	//{{AFX_MSG_MAP(CPSMemberInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPSMemberInfo message handlers

void CPSMemberInfo::PostNcDestroy()
{
	CPropertySheet::PostNcDestroy();
	delete this;
}
