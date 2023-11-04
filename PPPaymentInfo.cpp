// PPPaymentInfo.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "PPPaymentInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPPaymentInfo property page

IMPLEMENT_DYNCREATE(CPPPaymentInfo, CPropertyPage)

CPPPaymentInfo::CPPPaymentInfo() : CPropertyPage(CPPPaymentInfo::IDD)
{
	//{{AFX_DATA_INIT(CPPPaymentInfo)
	m_strCardNum = _T("");
	m_strExpDate = _T("");
	//}}AFX_DATA_INIT
}

CPPPaymentInfo::~CPPPaymentInfo()
{
}

void CPPPaymentInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPPaymentInfo)
	DDX_Control(pDX, IDC_COMBO1, m_cbCredit);
	DDX_Text(pDX, IDC_EDIT_CARDNUM, m_strCardNum);
	DDX_Text(pDX, IDC_EDIT_EXPDATE, m_strExpDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPPaymentInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPPPaymentInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPPaymentInfo message handlers

BOOL CPPPaymentInfo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_cbCredit.SetCurSel(0);
	m_strExpDate = _T("MM/YY");
	m_strCardNum = _T("XXXX-XXXX-XXXX-XXXX");
	UpdateData(FALSE);	// Write
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
