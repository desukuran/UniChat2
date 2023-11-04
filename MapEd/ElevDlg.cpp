// ElevDlg.cpp : implementation file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"
#include "ElevDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElevDlg dialog


CElevDlg::CElevDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CElevDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElevDlg)
	m_nElevNew = 0;
	m_strElevCur = _T("");
	//}}AFX_DATA_INIT
}


void CElevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElevDlg)
	DDX_Text(pDX, IDC_EDIT_NEW_ELEV, m_nElevNew);
	DDV_MinMaxInt(pDX, m_nElevNew, 0, 300);
	DDX_Text(pDX, IDC_ST_CURRENT_ELEV, m_strElevCur);
	DDV_MaxChars(pDX, m_strElevCur, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElevDlg, CDialog)
	//{{AFX_MSG_MAP(CElevDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElevDlg message handlers
