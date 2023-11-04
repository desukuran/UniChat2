// GetIntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEd.h"
#include "GetIntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetIntDlg dialog


CGetIntDlg::CGetIntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetIntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetIntDlg)
	m_nNew = 0;
	m_strCur = _T("");
	//}}AFX_DATA_INIT
	m_strCaption.Empty();
}


void CGetIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetIntDlg)
	DDX_Text(pDX, IDC_EDIT_NEW_INT, m_nNew);
	DDX_Text(pDX, IDC_ST_CURRENT_INT, m_strCur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetIntDlg, CDialog)
	//{{AFX_MSG_MAP(CGetIntDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetIntDlg message handlers

BOOL CGetIntDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!m_strCaption.IsEmpty())
		SetWindowText(m_strCaption);

	m_strCur.Format("%d", m_nNew);	// So, set m_nNew before calling DoModal
	UpdateData(FALSE);	// Initialize Dialog

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
