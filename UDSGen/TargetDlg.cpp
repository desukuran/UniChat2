// TargetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDSGen.h"
#include "TargetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTargetDlg dialog


CTargetDlg::CTargetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTargetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTargetDlg)
	m_strTargetFile = _T("");
	//}}AFX_DATA_INIT
}


void CTargetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTargetDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctlTarget);
	DDX_Text(pDX, IDC_EDIT1, m_strTargetFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTargetDlg, CDialog)
	//{{AFX_MSG_MAP(CTargetDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTargetDlg message handlers

int CTargetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ctlTarget.GetFocus();
	return 0;
}
