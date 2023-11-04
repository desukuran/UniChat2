// InputPassword.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "InputPassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputPassword dialog


CInputPassword::CInputPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CInputPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputPassword)
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CInputPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputPassword)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputPassword, CDialog)
	//{{AFX_MSG_MAP(CInputPassword)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputPassword message handlers
