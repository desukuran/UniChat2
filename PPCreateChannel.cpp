// PPCreateChannel.cpp : implementation file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#include "stdafx.h"
#include "resource.h"
#include "PPCreateChannel.h"
#include "PSJoinChannel.h"
#include "ResMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

IMPLEMENT_DYNCREATE(CPPCreateChannel, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CPPCreateChannel property page

CPPCreateChannel::CPPCreateChannel() : CPropertyPage(CPPCreateChannel::IDD)
{
	TRACE0("CPPCreateChannel::CPPCreateChannel()\n");
	//{{AFX_DATA_INIT(CPPCreateChannel)
	m_strPassword = _T("");
	m_strTopic = _T("");
	//}}AFX_DATA_INIT
	m_bPublic = TRUE;
}

CPPCreateChannel::~CPPCreateChannel()
{
	TRACE0("CPPCreateChannel::~CPPCreateChannel()\n");
}

void CPPCreateChannel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPCreateChannel)
	DDX_Control(pDX, IDC_LB_BACKGROUND, m_lbBackground);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 12);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NAME, m_strTopic);
	DDV_MaxChars(pDX, m_strTopic, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPCreateChannel, CPropertyPage)
	//{{AFX_MSG_MAP(CPPCreateChannel)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RADIO_PRIVATE, OnRadioPrivate)
	ON_BN_CLICKED(IDC_RADIO_PUBLIC, OnRadioPublic)
	ON_LBN_SELCHANGE(IDC_LB_BACKGROUND, OnSelchangeLbBackground)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CPPCreateChannel::OnEraseBkgnd(CDC* pDC) 
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	return pPSJC->OnPageEraseBkgnd(pDC);
}
/*
HBRUSH CPPCreateChannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)*pPSJC->GetNullBrush();
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
*/
void CPPCreateChannel::OnRadioPrivate() 
{
	m_bPublic = FALSE;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
	pEdit->EnableWindow();
	pEdit->SetFocus();
}

void CPPCreateChannel::OnRadioPublic() 
{
	m_bPublic = TRUE;
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CHANNEL_NAME)->SetFocus();
}

void CPPCreateChannel::OnSelchangeLbBackground()
{
	m_lbBackground.GetText(m_lbBackground.GetCurSel(), m_strStageName);
//	gResMan.MakeStageName(m_strStageName, TRUE);	// Public
	GetDlgItem(IDC_EDIT_CHANNEL_NAME)->SetFocus();
}

BOOL CPPCreateChannel::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	GetDlgItem(IDC_EDIT_CHANNEL_NAME)->SetFont(pPSJC->GetFont(), FALSE);

	((CButton*)GetDlgItem(IDC_RADIO_PUBLIC))->SetCheck(BST_CHECKED);
	OnRadioPublic();

	// 0 is for MUD beginning stage
	for (int i=1; i < gResMan.GetNumStageNames(); i++)
	{
		CString* pS = gResMan.GetStageName(i);
		if (pS)
		{
			m_lbBackground.AddString(*pS);
		}
	}
	m_lbBackground.SetCurSel(0);
	OnSelchangeLbBackground();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPCreateChannel::OnApply()
{
	if (!IsPublic() && m_strPassword.IsEmpty())
	{
		AfxMessageBox(IDS_ENTER_PASSWORD);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		return FALSE;
	}
	
	if (m_strStageName.IsEmpty())
	{
		TRACE0("CPPCreateChannel::OnApply() - m_strStageName is Empty!\n");
		AfxMessageBox(IDS_SELECT_STAGE);
		GetDlgItem(IDC_LB_BACKGROUND)->SetFocus();
		return FALSE;
	}

	if (!m_strTopic.IsEmpty())
	{
// "[p2/csin000] Inside the Castle" ==> "[p2/csin000] My topic goes here"
		gResMan.ExtractStageID(m_strStageName);
		gResMan.MakeStageName(m_strStageName, TRUE);
		m_strStageName += m_strTopic;
	}

	return CPropertyPage::OnApply();
}
