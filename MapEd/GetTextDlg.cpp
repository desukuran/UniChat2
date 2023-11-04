// GetTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEd.h"
#include "GetTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetTextDlg dialog

CGetTextDlg::CGetTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetTextDlg)
	m_strText = _T("");
	//}}AFX_DATA_INIT
	m_strCaption.Empty();
}

void CGetTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetTextDlg)
	DDX_Text(pDX, IDC_EDIT_STRING, m_strText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetTextDlg, CDialog)
	//{{AFX_MSG_MAP(CGetTextDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetTextDlg message handlers

BOOL CGetTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!m_strCaption.IsEmpty())
		SetWindowText(m_strCaption);

	UpdateData(FALSE);	// Initialize Dialog
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
