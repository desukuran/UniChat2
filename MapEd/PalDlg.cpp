// PalDlg.cpp : implementation file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"
#include "PalDlg.h"

#include "MapEdView.h"
#include "../UC2Ani/DIBPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CDIBPal;

/////////////////////////////////////////////////////////////////////////////
// CPalDlg dialog


CPalDlg::CPalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPalDlg)
	m_bShowIndex = FALSE;
	m_stRGB = _T("");
	m_sbBlue = 0;
	m_sbGreen = 0;
	m_sbRed = 0;
	//}}AFX_DATA_INIT
	m_bCaptured = FALSE;
}


void CPalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPalDlg)
	DDX_Check(pDX, IDC_CHECK_SHOW_INDEX, m_bShowIndex);
	DDX_Text(pDX, IDC_ST_PAL_RGB, m_stRGB);
	DDX_Scroll(pDX, IDC_SB_PAL_BLUE, m_sbBlue);
	DDX_Scroll(pDX, IDC_SB_PAL_GREEN, m_sbGreen);
	DDX_Scroll(pDX, IDC_SB_PAL_RED, m_sbRed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPalDlg, CDialog)
	//{{AFX_MSG_MAP(CPalDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SHOW_INDEX, OnCheckShowIndex)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPalDlg message handlers

BOOL CPalDlg::OnInitDialog() 
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

void CPalDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    if (!m_pPal)
		return;

    m_pPal->Draw(&dc, m_rcPal, FALSE, m_bShowIndex);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CPalDlg::OnCheckShowIndex() 
{
	CButton* pB = (CButton*)GetDlgItem(IDC_CHECK_SHOW_INDEX);
	ASSERT(pB);
	m_bShowIndex = (pB->GetCheck() == 1);
	InvalidateRect(&m_rcPal, FALSE);
}

void CPalDlg::ShowRGB(CPoint point)
{
    HDC hDC = ::GetDC(NULL);
    ClientToScreen(&point);
    COLORREF crRGB = ::GetPixel(hDC, point.x, point.y);
    ::ReleaseDC(NULL, hDC);

    char buf[64];
	char name[30]="";
	int	r = GetRValue(crRGB);
	int	g = GetGValue(crRGB);
	int	b = GetBValue(crRGB);
	int i = -1;
	if (m_pPal)
		i = (BYTE)m_pPal->GetNearestPaletteIndex(crRGB);

    if		(r==0	&& g==0		&& b==0)		wsprintf(name, "%s", "Black");
    else if (r==128	&& g==0		&& b==0)		wsprintf(name, "%s", "Dark Red");
    else if (r==0	&& g==128	&& b==0)		wsprintf(name, "%s", "Dark Green");
    else if (r==128	&& g==128	&& b==0)		wsprintf(name, "%s", "Dark Yellow");
    else if (r==0	&& g==0		&& b==128)		wsprintf(name, "%s", "Dark Blue");
    else if (r==128	&& g==0		&& b==128)		wsprintf(name, "%s", "Dark Magenta");
    else if (r==0	&& g==128	&& b==128)		wsprintf(name, "%s", "Dark Cyan");
    else if (r==192	&& g==192	&& b==192)		wsprintf(name, "%s", "Light Gray");
    else if (r==192	&& g==220	&& b==192)		wsprintf(name, "%s", "Money Green");
    else if (r==166	&& g==202	&& b==240)		wsprintf(name, "%s", "Sky Blue");
    else if	(r==255	&& g==251	&& b==240)		wsprintf(name, "%s", "Cream");
    else if (r==160	&& g==160	&& b==164)		wsprintf(name, "%s", "Medium Gray");
    else if	(r==128	&& g==128	&& b==128)		wsprintf(name, "%s", "Dark Gray");
    else if (r==255	&& g==0		&& b==0)		wsprintf(name, "%s", "Red");
    else if (r==0	&& g==255	&& b==0)		wsprintf(name, "%s", "Green");
    else if (r==255	&& g==255	&& b==0)		wsprintf(name, "%s", "Yellow");
    else if (r==0	&& g==0		&& b==255)		wsprintf(name, "%s", "Blue");
    else if (r==255	&& g==0		&& b==255)		wsprintf(name, "%s", "Magenta");
    else if (r==0	&& g==255	&& b==255)		wsprintf(name, "%s", "Cyan");
    else if (r==255	&& g==255	&& b==255)		wsprintf(name, "%s", "White");

    wsprintf(buf, "#%d (%03d,%03d,%03d) %s", i, r, g, b, name);
    SetWindowText(buf);
}

void CPalDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::SetCursor(AfxGetApp()->LoadCursor(IDC_PIXEL));
    SetCapture();
    m_bCaptured = TRUE;
	ShowRGB(point);
	CDialog::OnLButtonDown(nFlags, point);
}

void CPalDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) 
	{
		ReleaseCapture();
		m_bCaptured = FALSE;
//		SetWindowText("SysPal"); // Restore title.
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CPalDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bCaptured)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_PIXEL));
        ShowRGB(point);
	}
	CDialog::OnMouseMove(nFlags, point);
}
