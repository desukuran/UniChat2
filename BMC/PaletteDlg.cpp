// PaletteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BMC.h"
#include "PaletteDlg.h"

#include "BMCView.h"
#include "../UC2Ani/DIBPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg dialog

CPaletteDlg::CPaletteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaletteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaletteDlg)
	m_sbBlue = 0;
	m_sbGreen = 0;
	m_stRGB = _T("");
	m_sbRed = 0;
	m_bShowIndex = FALSE;
	//}}AFX_DATA_INIT
}

void CPaletteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaletteDlg)
	DDX_Scroll(pDX, IDC_SB_PAL_BLUE, m_sbBlue);
	DDX_Scroll(pDX, IDC_SB_PAL_GREEN, m_sbGreen);
	DDX_Text(pDX, IDC_ST_PAL_RGB, m_stRGB);
	DDX_Scroll(pDX, IDC_SB_PAL_RED, m_sbRed);
	DDX_Check(pDX, IDC_CHECK_SHOW_INDEX, m_bShowIndex);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaletteDlg, CDialog)
	//{{AFX_MSG_MAP(CPaletteDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SHOW_INDEX, OnCheckShowIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg message handlers

BOOL CPaletteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetClientRect(&m_rcPal);

	CWnd* pW = GetDlgItem(IDC_SB_PAL_RED);
	ASSERT(pW);
	CRect rcSB;
	pW->GetClientRect(&rcSB);
	m_rcPal.right -= (rcSB.Width() + 10);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaletteDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    if (!m_pPal)
		return;

    m_pPal->Draw(&dc, m_rcPal, FALSE, m_bShowIndex);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CPaletteDlg::OnCheckShowIndex() 
{
	CButton* pB = (CButton*)GetDlgItem(IDC_CHECK_SHOW_INDEX);
	ASSERT(pB);
	m_bShowIndex = (pB->GetCheck() == 1);
	InvalidateRect(&m_rcPal, FALSE);
}
