// InputIntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "InputIntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputIntDlg dialog


CInputIntDlg::CInputIntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputIntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputIntDlg)
//	m_nVal = 0;
	//}}AFX_DATA_INIT
}


void CInputIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputIntDlg)
	DDX_Text(pDX, IDC_EDIT_INT, m_nVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputIntDlg, CDialog)
	//{{AFX_MSG_MAP(CInputIntDlg)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, OnBtnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputIntDlg message handlers

void CInputIntDlg::OnBtnDefault() 
{
	m_nVal = m_nDefaultVal;
	UpdateData(FALSE);	// initialize dialg box
}

BOOL CInputIntDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle);
	UpdateData(FALSE);	// initialize dialg box

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
