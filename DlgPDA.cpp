// DlgPDA.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "DlgPDA.h"
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

LPCTSTR BMP_PDA_BK			= "MPDABk.bmp";
LPCTSTR BMP_PDA_BTN_CLOSE	= "MPBtClos.bmp";
LPCTSTR BMP_PDA_BTN_BUY		= "MPBtBuy.bmp";
LPCTSTR BMP_PDA_BTN_MORE	= "MPBtMore.bmp";
LPCTSTR BMP_PDA_BTN_AUTO	= "MPBtAuto.bmp";
LPCTSTR BMP_PDA_BTN_LEFT	= "MPBtLeft.bmp";
LPCTSTR BMP_PDA_BTN_RIGHT	= "MPBtRght.bmp";

const CPoint	PTLT_ANI_PDA[2] = {CPoint(14, 8), CPoint(2, 151)};

/////////////////////////////////////////////////////////////////////////////
// CDlgPDA dialog

CDlgPDA::CDlgPDA(LPCTSTR strUpper, LPCTSTR strLower, const int nPages, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPDA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPDA)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_astrAniFile[0] = strUpper;
	m_astrAniFile[1] = strLower;
	m_nPages	= nPages;

	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + BMP_PDA_BK);
	m_pDIBBack = new CDIB;
	m_pPal	= NULL;	// initialize in case of failure
	if (!m_pDIBBack->Load(strFile))
	{
		delete m_pDIBBack;
		m_pDIBBack = NULL;
		return;
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

	strFile = strPath + BMP_PDA_BTN_CLOSE;
	m_btnClose.Load(strFile, 2);
	m_btnClose.SetPalette(m_pPal);

	strFile = strPath + BMP_PDA_BTN_BUY;
	m_btnBuy.Load(strFile, 2);
	m_btnBuy.SetPalette(m_pPal);

	strFile = strPath + BMP_PDA_BTN_MORE;
	m_btnMore.Load(strFile, 2);
	m_btnMore.SetPalette(m_pPal);

	strFile = strPath + BMP_PDA_BTN_AUTO;
	m_btnAuto.Load(strFile, 2);
	m_btnAuto.SetPalette(m_pPal);

	strFile = strPath + BMP_PDA_BTN_LEFT;
	m_btnLeft.Load(strFile, 2);
	m_btnLeft.SetPalette(m_pPal);

	strFile = strPath + BMP_PDA_BTN_RIGHT;
	m_btnRight.Load(strFile, 2);
	m_btnRight.SetPalette(m_pPal);

	for (int i=0; i < 2; i++)	// Upper and Lower
	{
		strFile = strPath + m_astrAniFile[i];
		m_apDIBAni[i] = new CPhasedSprite;
		if (!m_apDIBAni[i]->Load(strFile))
		{
			delete m_apDIBAni[i];
			m_apDIBAni[i] = NULL;
	//		return;	// skip
		}
		else
		{
			m_apDIBAni[i]->SetNumCells(1, m_nPages);	// Row, Col
			m_apDIBAni[i]->SetCell(0);
			m_apDIBAni[i]->GetRect(m_arcAni[i]);
			m_arcAni[i].OffsetRect(PTLT_ANI_PDA[i]);
		}
	}
	m_nCurPage = 0;

	m_uiTimer = 0;
	m_dwLastTick	= 0L;
	m_dwStartTick	= 0L;
	m_bAutoDestroy	= FALSE;
	m_bAutoPages	= FALSE;
	m_uiInterval	= 1500;
	m_dwDurationTick = 9000L;	// 9 sec
}

CDlgPDA::~CDlgPDA()
{
	if (m_pDIBBack)
		delete m_pDIBBack;
	if (m_pPal && m_bPaletteCreated)
		delete m_pPal;
	for (int i=0; i < 2; i++)
	{
		if (m_apDIBAni[i])
			delete m_apDIBAni[i];
	}
}

void CDlgPDA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPDA)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgPDA, CDialog)
	//{{AFX_MSG_MAP(CDlgPDA)
	ON_BN_CLICKED(IDC_PDA_BTN_AUTO, OnPdaBtnAuto)
	ON_BN_CLICKED(IDC_PDA_BTN_BUY, OnPdaBtnBuy)
	ON_BN_CLICKED(IDC_PDA_BTN_LEFT, OnPdaBtnLeft)
	ON_BN_CLICKED(IDC_PDA_BTN_MORE, OnPdaBtnMore)
	ON_BN_CLICKED(IDC_PDA_BTN_RIGHT, OnPdaBtnRight)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPDA message handlers

BOOL CDlgPDA::OnInitDialog() 
{
	if (!m_pDIBBack)
		return FALSE;
	CDialog::OnInitDialog();
	
	m_btnClose.SubclassDlgItem(IDOK, this);
	m_btnBuy.SubclassDlgItem(IDC_PDA_BTN_BUY, this);
	m_btnMore.SubclassDlgItem(IDC_PDA_BTN_MORE, this);
	m_btnAuto.SubclassDlgItem(IDC_PDA_BTN_AUTO, this);
	m_btnLeft.SubclassDlgItem(IDC_PDA_BTN_LEFT, this);
	m_btnRight.SubclassDlgItem(IDC_PDA_BTN_RIGHT, this);

	CPoint ptLT(132, 245);
	m_btnClose.MoveResize(ptLT);
	ptLT.x = 66;
	m_btnBuy.MoveResize(ptLT);
	ptLT.x = 0;
	m_btnMore.MoveResize(ptLT);
	ptLT = CPoint(63, 120);
	m_btnAuto.MoveResize(ptLT);
	ptLT.x = 0;
	m_btnLeft.MoveResize(ptLT);
	ptLT.x = 135;
	m_btnRight.MoveResize(ptLT);

	m_uiTimer = SetTimer(4003, m_uiInterval, NULL);
	m_dwStartTick = ::GetTickCount();

	ptLT = CPoint(435, 104);
	ClientToScreen(&ptLT);	// CWnd::
	SetWindowPos(NULL, ptLT.x, ptLT.y, 0, 0, 
				SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPDA::PlayCameraSound()
{
	CString strPath(*gResMan.GetResPath());
	CString strFile(strPath + "Camera.wav");
	::sndPlaySound(strFile, SND_ASYNC);
}

void CDlgPDA::OnPdaBtnAuto() 
{
	m_bAutoPages = !m_bAutoPages;
}

void CDlgPDA::OnPdaBtnBuy() 
{
}

void CDlgPDA::OnPdaBtnLeft() 
{
	PlayCameraSound();
	m_nCurPage--;
	if (m_nCurPage < 0)
		m_nCurPage = m_nPages - 1;
	for (int i=0; i < 2; i++)
	{
		InvalidateRect(m_arcAni[i], FALSE);
	}
}

void CDlgPDA::OnPdaBtnMore() 
{
}

void CDlgPDA::OnPdaBtnRight() 
{
	PlayCameraSound();
	m_nCurPage++;
	if (m_nCurPage >= m_nPages)
		m_nCurPage = 0;
	for (int i=0; i < 2; i++)
	{
		InvalidateRect(m_arcAni[i], FALSE);
	}
}

void CDlgPDA::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_pDIBBack)
	{
		SetWindowPos(NULL, 0, 0, m_pDIBBack->GetWidth(), m_pDIBBack->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

BOOL CDlgPDA::OnEraseBkgnd(CDC* pDC) 
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

void CDlgPDA::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Make sure we have what we need to do a paint.
	if (!m_pDIBBack)	// || !m_pDIBOval)
	{
		TRACE("CLoginDlg: No DIB!\n");
		return;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = dc.SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	for (int i=0; i < 2; i++)
	{
		if (m_apDIBAni[i])
		{
			m_apDIBAni[i]->SetCell(m_nCurPage);
			m_apDIBAni[i]->Draw(&dc, PTLT_ANI_PDA[i]);
		}
	}
	// Select old palette if we altered it.
	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
}

UINT CDlgPDA::OnNcHitTest(CPoint point) 
{
    UINT nHitTest = CDialog::OnNcHitTest(point);
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState(MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;
}

void CDlgPDA::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CDlgPDA::OnQueryNewPalette() 
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

void CDlgPDA::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
}

void CDlgPDA::OnTimer(UINT nIDEvent) 
{
	if (m_bAutoDestroy && ((::GetTickCount() - m_dwStartTick) > m_dwDurationTick))
		EndDialog(TRUE);
	if (m_bAutoPages)
		OnPdaBtnRight();
//	CDialog::OnTimer(nIDEvent);
}

void CDlgPDA::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_uiTimer)
	{
		KillTimer(m_uiTimer);
//		m_uiTimer = 0;
	}
}

