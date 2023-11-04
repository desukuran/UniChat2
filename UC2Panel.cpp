//
//	CUC2Panel: Control Panel for UniChat 2
//
//	(C) Programmed by Kim, Soomin, Feb 27, 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
// UC2Panel.cpp : implementation file
// On ToolTip support:
//		MFC42.dll 97-08-23 or MFC42d.dll (debug) 97-01-03
//		Later versions have the bug that do not display tooltips
//		for control bars in MainFrame.

#include "stdafx.h"
#include "UC2.h"
#include "UC2Panel.h"
#include "MainFrm.h"
#include "ResMan.h"

#include "UC2Ani/DIB.h"
#include "UC2Ani/DIBPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

const CRect RECT_EDIT(16, 15, 376, 38);

#ifdef _MALL
LPCTSTR BMP_PANEL_BACK	= "MPanelBk.bmp";
LPCTSTR FMT_BMP_BTN_CP	= "%sMBtnCP%d.bmp";
#else
LPCTSTR BMP_PANEL_BACK	= "U2Panel|PanelBk.bmp";
LPCTSTR FMT_BMP_BTN_CP	= "%sU2Panel|BtnCP%d.bmp";
#endif

/////////////////////////////////////////////////////////////////////////////
// CUC2Panel

CUC2Panel::CUC2Panel()
{
	TRACE("CUC2Panel::CUC2Panel()\n");
	m_bInitialized = FALSE;
	m_pDIB	= NULL;
}

CUC2Panel::~CUC2Panel()
{
	TRACE("CUC2Panel::~CUC2Panel()\n");
	if (m_pDIB)
		delete m_pDIB;
}

BEGIN_MESSAGE_MAP(CUC2Panel, CDialogBar)
	//{{AFX_MSG_MAP(CUC2Panel)
	ON_WM_SETFOCUS()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
//	ON_NOTIFY(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CUC2Panel::Create(CWnd* pParentWnd, UINT nStyle)
{
	TRACE0("CUC2Panel::Create()\n");
	BOOL bRes = CDialogBar::Create(pParentWnd, CG_IDD_CONTROLPANEL,
							nStyle, CG_ID_VIEW_CONTROLPANEL);
	// The DialogBar has been created.
	return bRes;
}

CPalette* CUC2Panel::GetPalette()
{
	return ((CMainFrame*)AfxGetMainWnd())->GetPalette();
}

/////////////////////////////////////////////////////////////////////////////
// CUC2Panel message handlers


void CUC2Panel::OnSetFocus(CWnd* pOldWnd) 
{
	CDialogBar::OnSetFocus(pOldWnd);
	
	m_eSend.SetFocus();
}

void CUC2Panel::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (!m_pDIB)
		return;
//	TRACE("CPXControlPanel::OnPaletteChanged\n");
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CUC2Panel::OnQueryNewPalette() 
{
	if (!m_pDIB)
		return FALSE;
//	TRACE("CPXControlPanel::OnQueryNewPalette\n");
	CPalette* pPal = GetPalette();
	if (pPal)
	{
		CDC* pdc = GetDC();
		CPalette* pPalOld = pdc->SelectPalette(pPal, TRUE);
		UINT u = pdc->RealizePalette();
		if (pPalOld)
			pdc->SelectPalette(pPalOld, FALSE);
		ReleaseDC(pdc);
//		if (u)
//		{	// Some colors changed so we need to do a repaint.
			Invalidate();	// Repaint the lot.
			return TRUE;	// Say we did something.
//		}
	}
	return FALSE; // Say we did nothing.
}

// Called by the parent after creation of CUC2Panel object and window
// Load images and initializes controls
BOOL CUC2Panel::InitControls()
{
	TRACE("CUC2Panel::InitControls()\n");
	CString strPath(*gResMan.GetResPath());
	CString strBtnBmp;
	for (int i=0; i < 6; i++)
	{	// Two States (Normal, Selected)
		strBtnBmp.Format(FMT_BMP_BTN_CP, strPath, i);
		if (!m_aButton[i].Load(strBtnBmp, 2))
		{
			strBtnBmp += " not found!";
			AfxMessageBox(strBtnBmp);
			return FALSE;
		}
		gResMan.LoadMasterPalette(m_aButton[i].GetDIB());
		m_aButton[i].SetPalette(GetPalette());
	}
	if (m_pDIB)
		delete m_pDIB;
	strPath += BMP_PANEL_BACK;
//	TRACE("%s\n", strPath);
	m_pDIB = new CDIB;
	if (!m_pDIB->Load(strPath))
	{
		delete m_pDIB;
		m_pDIB = NULL;
		strPath + " not found!";
		AfxMessageBox(strPath);
		return FALSE;
	}
	gResMan.LoadMasterPalette(m_pDIB);
	SetWindowPos(NULL, 0, 0, m_pDIB->GetWidth(), m_pDIB->GetHeight(),
				SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	CWnd* pW = GetDlgItem(IDC_EDIT_SEND);
	pW->SetWindowPos(NULL, RECT_EDIT.left, RECT_EDIT.top,
					RECT_EDIT.Width(), RECT_EDIT.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);

	// Window has been created...
	if (!m_eSend.SubclassDlgItem(IDC_EDIT_SEND, this))
	{
		TRACE0("m_eSend.SubclassDlgItem failed!\n");
		return FALSE;
	}

	// Subclass 6 buttons
#ifdef _MALL
	CPoint ptLT(383, 6);
	int w = 42;
#else
	CPoint ptLT(390, 11);
	int w = 30+11;
#endif
	for (int i=0; i < 6; i++)
	{
		if (!m_aButton[i].SubclassDlgItem(IDC_BTN_CREATE + i, this))
		{
			TRACE("m_aButton[%d].SubclassDlgItem failed!\n", i);
			return FALSE;
		}
		m_aButton[i].MoveResize(ptLT);
		ptLT.x += w;
	}
//	EnableToolTips();
	m_bInitialized = TRUE;
	return TRUE;
}

void CUC2Panel::OnSize(UINT nType, int cx, int cy) 
{
	TRACE("CUC2Panel::OnSize(%d,%d)\n", cx, cy);
	CDialogBar::OnSize(nType, cx, cy);
	
	SetWindowPos(NULL, 0, 0, 636, 49-1, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void CUC2Panel::OnMove(int x, int y) 
{
	TRACE("CUC2Panel::OnMove(%d,%d)\n", x, y);
	CDialogBar::OnMove(x, y);
}

BOOL CUC2Panel::OnEraseBkgnd(CDC* pDC) 
{
	CDialogBar::OnEraseBkgnd(pDC);

	// Make sure we have what we need to do a paint.
	if (!m_pDIB)
	{
		TRACE("CUC2Panel::OnPaint() - No DIB.\n");
		return FALSE;
	}

	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	CPalette* pPal = GetPalette();
	if (pPal)
	{
		pPalOld = pDC->SelectPalette(pPal, FALSE);	// bForceBackground = FALSE
		pDC->RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}
	m_pDIB->Draw(pDC, 0, 0);

	// Select old palette if we altered it.
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
	return TRUE;
}

/*
int CUC2Panel::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	CRect rc(390, 11, 390+30, 11+30);
	if (rc.PtInRect(point))
	{
		ASSERT(pTI);
		pTI->hwnd = m_hWnd;
		pTI->rect = rc;
		pTI->uId = IDC_BTN_CREATE;
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		return 1;
	}
	return CDialogBar::OnToolHitTest(point, pTI);
}

void CUC2Panel::OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult)
{
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMH;
	UINT nID = pNMH->idFrom;
	if (pTTT->uFlags & TTF_IDISHWND)
	{
		nID = ::GetDlgCtrlID((HWND)nID);
		ASSERT(nID);
	}
	pTTT->lpszText = MAKEINTRESOURCE(nID);
	pTTT->hinst = AfxGetResourceHandle();
}
*/
