// CloseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "CloseDlg.h"
#include "ResMan.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/DIBPal.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

#ifdef _MALL
LPCTSTR BMP_CLOSE_BK		= "MClose.bmp";
//const CRect		RECT_MESSAGE(47, 175, 367, 270);
//const CRect		RECT_TIME(98, 300, 321, 320);
const CRect		RECT_MESSAGE(47, 63, 280, 160);
const CRect		RECT_TIME(114, 145, 222, 165);
#else
LPCTSTR BMP_CLOSE_BK		= "U2Login|LoginBk.bmp";
LPCTSTR BMP_CLOSE_BTN_OK	= "U2Login|BtnOK.bmp";
LPCTSTR BMP_CLOSE_BTN_NO	= "U2Login|BtnNo.bmp";
const CRect		RECT_MESSAGE(47, 145, 367, 240);
const CRect		RECT_TIME(98, 270, 321, 290);
#endif

const int NUM_EPILOGUES=2;

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg dialog

CCloseDlg::CCloseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCloseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCloseDlg)
//	m_strTimeReport = _T("");
	//}}AFX_DATA_INIT
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMF);
	CTimeSpan tsElapsed = CTime::GetCurrentTime() - pMF->m_tmStart;
	CString strTime(tsElapsed.Format("%H:%M:%S"));
	m_strTimeReport.LoadString(IDS_TIME_REPORT);
	m_strTimeReport += strTime;

	m_nMsgCur = 0;

	m_NullBrush.CreateStockObject(NULL_BRUSH);
	m_ftMessage.CreateFont(-13, 0, 0, 0, FW_BOLD,	// NORMAL,
				FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
				"±¼¸²Ã¼");
#else
				"Times New Roman");
#endif

	m_pPal = NULL;	// Set it NULL before loading DIB

	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + BMP_CLOSE_BK);
	m_pDIBBack = new CDIB;
	if (!m_pDIBBack->Load(strFile))
	{
		delete m_pDIBBack;
		m_pDIBBack = NULL;
		return;
	}

	if (pMF->Is256Palette())
	{	// Use mainframe's palette to avoid color flickering
		m_pPal = pMF->GetPalette();
		m_pDIBBack->MapColorsToPalette(m_pPal);
		m_bPaletteCreated = FALSE;
	}
	else	// Use original palette in the file for TRUE color system
	{		// Create the palette from the DIB.
		CDIBPal* pDIBPal;
		pDIBPal = new CDIBPal;
		ASSERT(pDIBPal);
		if (!pDIBPal->Create(m_pDIBBack))
		{
			AfxMessageBox("Failed to create palette from DIB file");
			delete pDIBPal;
		}
		m_pPal = pDIBPal;	// type casting to parent class
		m_bPaletteCreated = TRUE;
	}

#ifndef _MALL
	strFile = strPath + BMP_CLOSE_BTN_OK;
	m_btnOK.Load(strFile);
	m_btnOK.SetPalette(m_pPal);

	strFile = strPath + BMP_CLOSE_BTN_NO;
	m_btnCancel.Load(strFile);
	m_btnCancel.SetPalette(m_pPal);
#endif
}

CCloseDlg::~CCloseDlg()
{
	if (m_pDIBBack)
		delete m_pDIBBack;
	if (m_pPal && m_bPaletteCreated)
		delete m_pPal;
}

void CCloseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCloseDlg)
	DDX_Text(pDX, IDC_ST_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_ST_TIME_REPORT, m_strTimeReport);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCloseDlg, CDialog)
	//{{AFX_MSG_MAP(CCloseDlg)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	// ON_WM_NCHITTEST()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg message handlers

void CCloseDlg::InitControl(const int nCtrlID, const CRect& rcCtrl)
{
	CWnd* pW = GetDlgItem(nCtrlID);
	ASSERT(pW);
	pW->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top,
					rcCtrl.Width(), rcCtrl.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);
	pW->SetFont(&m_ftMessage, FALSE);	// do not Redraw
}

BOOL CCloseDlg::OnInitDialog() 
{
	if (!m_pDIBBack)
		return FALSE;
	CDialog::OnInitDialog();
	
#ifndef _MALL
	m_btnOK.SubclassDlgItem(IDOK, this);
	m_btnCancel.SubclassDlgItem(IDCANCEL, this);

	CPoint ptLT(349, 238);
	m_btnOK.MoveResize(ptLT);
	ptLT.x = 17;
	m_btnCancel.MoveResize(ptLT);
#endif
	
	InitControl(IDC_ST_MESSAGE,		RECT_MESSAGE);
	InitControl(IDC_ST_TIME_REPORT,	RECT_TIME);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCloseDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CCloseDlg::OnQueryNewPalette() 
{
	if (m_pPal)
	{
		CDC* pdc = GetDC();
		CPalette* pPalOld = pdc->SelectPalette(m_pPal, FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (pPalOld)
			pdc->SelectPalette(pPalOld, FALSE);
		ReleaseDC(pdc);
//		if (u)
//		{	// Some colors changed so we need to do a repaint.
			Invalidate(); // Repaint the lot.
			return TRUE; // Say we did something.
//		}
	}
	return FALSE; // Say we did nothing.
}

void CCloseDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pDIBBack)
	{
		SetWindowPos(NULL, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

BOOL CCloseDlg::OnEraseBkgnd(CDC* pDC) 
{
	CDialog::OnEraseBkgnd(pDC);

	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)
	{
		TRACE("CLoginDlg: No DIB!\n");
		return FALSE;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = pDC->SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	m_pDIBBack->Draw(pDC, 0, 0);
	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
	
	return TRUE;
}

HBRUSH CCloseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)m_NullBrush;
}

UINT CCloseDlg::OnNcHitTest(CPoint point) 
{
    UINT nHitTest = CDialog::OnNcHitTest(point);
#ifndef _MALL
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
#endif
    return nHitTest;
}

void CCloseDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (nFlags & MK_CONTROL)
	{
		// Authority Check
		if (RECT_MESSAGE.PtInRect(point))
		{
			UINT nID = IDS_EPILOGUE00 + m_nMsgCur;
			if (m_nMsgCur++ == NUM_EPILOGUES)
				m_nMsgCur = 0;
			m_strMessage.LoadString(nID);
			UpdateData(FALSE);
			InvalidateRect(RECT_MESSAGE, TRUE);
		}
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CCloseDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#ifdef _MALL
	CDialog::OnOK();
#else
	CDialog::OnLButtonDblClk(nFlags, point);
#endif
}
