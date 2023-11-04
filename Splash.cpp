//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================
// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//

#include "stdafx.h"  // e. g. stdafx.h
#include "resource.h"  // e.g. resource.h

#include "Splash.h"  // e.g. splash.h
#include "ResMan.h"

#include "UC2Ani/DIBPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

#ifdef _MALL
LPCTSTR BMP_SPLASH = "MSplash.bmp";
#else
LPCTSTR BMP_SPLASH = "U2Panel|U2Splash.bmp";
#endif

/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;
CSplashWnd::CSplashWnd()
{
	TRACE0("CSplashWnd::CSplashWnd()\n");
	m_pPal = NULL;
	m_pDIB = NULL;
}

CSplashWnd::~CSplashWnd()
{
	TRACE0("CSplashWnd::~CSplashWnd()\n");
    if (m_pDIB)
		delete m_pDIB;
    if (m_pPal)
		delete m_pPal;
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
	{
		delete c_pSplashWnd;
		c_pSplashWnd = NULL;
	}
	else
	{
		c_pSplashWnd->UpdateWindow();
	}
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{
	TRACE("CSplashWnd::Create(%lx)\n", pParentWnd);
	CString strFile(*gResMan.GetResPath());
//	CString strPal(strFile);
	strFile += BMP_SPLASH;
//	strPal += "U2Login.pal";

//	CFileStatus	status;
//	BOOL bFound = CFile::GetStatus(strFile, status);
//	if (!bFound)
//		return FALSE;	// To avoid file not found message dialog box

	m_pDIB = new CDIB;
	if (!m_pDIB->Load(strFile))//, strPal))
	{
		delete m_pDIB;
		m_pDIB = NULL;
		return FALSE;
	}
#ifndef _MALL
	gResMan.LoadMasterPalette(m_pDIB);
#endif
	// Create the palette from the DIB.
	m_pPal = new CDIBPal;
	ASSERT(m_pPal);
	if (!m_pPal->Create(m_pDIB))
	{
		AfxMessageBox("Failed to create palette from DIB file");
		delete m_pPal;
		m_pPal = NULL;
	}

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, m_pDIB->GetWidth(), m_pDIB->GetHeight(),
		pParentWnd->GetSafeHwnd(), NULL);
}

void CSplashWnd::HideSplashScreen()
{
	TRACE0("CSplashWnd::HideSplashScreen()\n");
	// Destroy the window, and update the mainframe.
	if (c_pSplashWnd)
	{
		c_pSplashWnd->DestroyWindow();
		AfxGetMainWnd()->UpdateWindow();
	}
}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
//	SetTimer(1, 750, NULL);

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	// Make sure we have what we need to do a paint.
	if (!m_pDIB)
	{
		TRACE("No DIB or color table to paint from.\n");
		return;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (m_pPal)
	{
		pPalOld = dc.SelectPalette(m_pPal, FALSE);	// bForceBackground = FALSE
	//	dc.RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	m_pDIB->Draw(&dc, 0, 0);
	// Select old palette if we altered it.
	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
}

void CSplashWnd::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
	HideSplashScreen();
}

void CSplashWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
//	CDialog::OnPaletteChanged(pFocusWnd);
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CSplashWnd::OnQueryNewPalette() 
{
	if (m_pPal)
	{
		CDC* pdc = GetDC();
		CPalette* pPalOld = pdc->SelectPalette(m_pPal, FALSE);	// foreground
		UINT u = pdc->RealizePalette();
		if (pPalOld)
			pdc->SelectPalette(pPalOld, FALSE);
		ReleaseDC(pdc);
		if (u)
		{	// Some colors changed so we need to do a repaint.
			Invalidate(); // Repaint the lot.
			return TRUE; // Say we did something.
		}
	}
	return FALSE; // Say we did nothing.
//	return CDialog::OnQueryNewPalette();
}
