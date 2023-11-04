// DlgAni.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "DlgAni.h"
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

/////////////////////////////////////////////////////////////////////////////
// CDlgAni dialog

CDlgAni::CDlgAni(LPCTSTR strBack, LPCTSTR strAni, const int nPages, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAni::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAni)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nNumPages	= nPages;
	m_nCurPage	= 0;

	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + strBack);
	m_pPal		= NULL;	// initialize in case of failure
	m_pDIBBack	= NULL;
	m_pPSAni	= NULL;
	if (strBack)
	{
		m_pDIBBack = new CDIB;
		if (!m_pDIBBack->Load(strFile))
		{
			delete m_pDIBBack;
			m_pDIBBack = NULL;
			return;
		}
	}

	if (strAni)
	{
		strFile = strPath + strAni;
		m_pPSAni = new CPhasedSprite;
		if (!m_pPSAni->Load(strFile))
		{
			delete m_pPSAni;
			m_pPSAni = NULL;
			return;
		}
		m_pPSAni->SetNumCells(nPages, 1);
		if (!m_pDIBBack)
		{
			m_pDIBBack = m_pPSAni->GetDIB();
		}
	}

	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMF);
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
	m_nCurPage = 0;

	m_uiTimer = 0;
	m_dwLastTick	= 0L;
	m_dwStartTick	= 0L;

	m_bAutoDestroy		= FALSE;
	m_dwDurationTick	= 9000L;	// 9 sec
	m_uiElapse			= 1000;
	m_ptLTAni			= CPoint(0, 0);
	m_ptLeftTop			= CPoint(200, 200);
}

CDlgAni::~CDlgAni()
{
	if (m_pDIBBack)
	{
		if (m_pPSAni)
		{
			if (m_pDIBBack != m_pPSAni->GetDIB())
				delete m_pDIBBack;
		}
		else
		{
			delete m_pDIBBack;
		}
	}
	if (m_pPSAni)
		delete m_pPSAni;

	if (m_pPal && m_bPaletteCreated)
		delete m_pPal;
}


void CDlgAni::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAni)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAni, CDialog)
	//{{AFX_MSG_MAP(CDlgAni)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAni message handlers

BOOL CDlgAni::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!m_pDIBBack)
		return FALSE;
	CDialog::OnInitDialog();

	m_uiTimer = SetTimer(4004, m_uiElapse, NULL);	// CWnd::
	m_dwStartTick = ::GetTickCount();
	
	ClientToScreen(&m_ptLeftTop);	// CWnd::
	SetWindowPos(NULL, m_ptLeftTop.x, m_ptLeftTop.y, 0, 0, 
				SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgAni::OnEraseBkgnd(CDC* pDC) 
{
	CDialog::OnEraseBkgnd(pDC);

	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)
	{
		TRACE("CDlgAni: No DIB!\n");
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

void CDlgAni::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)
	{
		TRACE("CDlgAni: No DIB!\n");
		return;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = dc.SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	if (m_pPSAni)
	{
		m_pPSAni->SetCell(m_nCurPage);
		m_pPSAni->Draw(&dc, m_ptLTAni);
	}
	// Select old palette if we altered it.
	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
}

UINT CDlgAni::OnNcHitTest(CPoint point) 
{
    UINT nHitTest = CDialog::OnNcHitTest(point);
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;
}

void CDlgAni::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CDlgAni::OnQueryNewPalette() 
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

void CDlgAni::OnTimer(UINT nIDEvent) 
{
	if (m_bAutoDestroy && ((::GetTickCount() - m_dwStartTick) > m_dwDurationTick))
		EndDialog(TRUE);
	if (m_nNumPages > 1)
		ShowNextPage();
//	CDialog::OnTimer(nIDEvent);
}

void CDlgAni::ShowNextPage()
{
	m_nCurPage++;
	if (m_nCurPage >= m_nNumPages)
		m_nCurPage = 0;
	CRect rcAni;
	m_pPSAni->GetRect(rcAni);
	InvalidateRect(&rcAni, FALSE);
}

void CDlgAni::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pDIBBack)
	{
		SetWindowPos(NULL, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CDlgAni::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_uiTimer)
	{
		KillTimer(m_uiTimer);
//		m_uiTimer = 0;
	}
}

void CDlgAni::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#ifdef _MALL
	EndDialog(TRUE);
//	CDialog::OnOK();
#else
	CDialog::OnLButtonDblClk(nFlags, point);
#endif
}
