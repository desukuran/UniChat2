// WhisperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "WhisperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhisperDlg dialog


CWhisperDlg::CWhisperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWhisperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWhisperDlg)
	m_strText = _T("");
	m_strToID = _T("");
	//}}AFX_DATA_INIT
}


void CWhisperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhisperDlg)
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Text(pDX, IDC_STATIC_TO, m_strToID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWhisperDlg, CDialog)
	//{{AFX_MSG_MAP(CWhisperDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhisperDlg message handlers
