// PPMemberInfo1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PPMemberInfo1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPPMemberInfo1, CPropertyPage)
IMPLEMENT_DYNCREATE(CPPMemberInfo2, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CPPMemberInfo1 property page

CPPMemberInfo1::CPPMemberInfo1() : CPropertyPage(CPPMemberInfo1::IDD)
{
	//{{AFX_DATA_INIT(CPPMemberInfo1)
	m_strUserID = _T("");
	m_strVersion = _T("");
	m_strSexAge = _T("");
	//}}AFX_DATA_INIT
}

CPPMemberInfo1::~CPPMemberInfo1()
{
}

void CPPMemberInfo1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPMemberInfo1)
	DDX_Text(pDX, IDC_STATIC_NICK, m_strNick);
	DDX_Text(pDX, IDC_STATIC_REALNAME, m_strRealName);
	DDX_Text(pDX, IDC_STATIC_UNITEL_ID, m_strUserID);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_STATIC_SEXAGE, m_strSexAge);
	//}}AFX_DATA_MAP
}

BOOL CPPMemberInfo1::OnSetActive() 
{
	UpdateData(FALSE);	// Update dialog items
	
	return CPropertyPage::OnSetActive();
}

BEGIN_MESSAGE_MAP(CPPMemberInfo1, CPropertyPage)
	//{{AFX_MSG_MAP(CPPMemberInfo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPPMemberInfo2 property page

CPPMemberInfo2::CPPMemberInfo2() : CPropertyPage(CPPMemberInfo2::IDD)
{
	//{{AFX_DATA_INIT(CPPMemberInfo2)
	m_strProfile = _T("");
	//}}AFX_DATA_INIT
}

CPPMemberInfo2::~CPPMemberInfo2()
{
}

void CPPMemberInfo2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPMemberInfo2)
	DDX_Text(pDX, IDC_EDIT_PROFILE, m_strProfile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPMemberInfo2, CPropertyPage)
	//{{AFX_MSG_MAP(CPPMemberInfo2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CPPMemberInfo2::OnSetActive() 
{
	UpdateData(FALSE);	// Update dialog items
	
	return CPropertyPage::OnSetActive();
}
