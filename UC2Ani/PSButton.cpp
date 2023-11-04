//
//	CPSButton
//
//	(C) Programmed by Kim, Soomin, Dec.1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "PSButton.h"
#include "PhSprite.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSButton

CPSButton::CPSButton()
{
	Init();
}

CPSButton::~CPSButton()
{
	if (m_pPS)
		delete m_pPS;
}

void CPSButton::Init()
{
	m_pPS = NULL;
	m_pPal = NULL;
}

BOOL CPSButton::Load(const CString& filename, const int nRows)
{
//	TRACE("%s\n", filename);
	if (m_pPS)
		delete m_pPS;
	m_pPS = new CPhasedSprite;
	if (!m_pPS->Load(filename))
	{
		delete m_pPS;
		m_pPS = NULL;
		AfxMessageBox("Failed to load Button DIB file");
		return FALSE;
	}
	m_pPS->SetNumCells(nRows, 1);
	return TRUE;
}

BOOL CPSButton::Load(const WORD wResid, const int nRows)
{
	if (m_pPS)
		delete m_pPS;
	m_pPS = new CPhasedSprite;
	if (!m_pPS->Load(wResid))
	{
		delete m_pPS;
		m_pPS = NULL;
		AfxMessageBox("Failed to load Button DIB file");
		return FALSE;
	}
	m_pPS->SetNumCells(nRows, 1);
	return TRUE;
}

void CPSButton::Resize()
{
	if (m_pPS)
		SetWindowPos(NULL, -1, -1, m_pPS->GetWidth(), m_pPS->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
}

void CPSButton::MoveResize(const int x, const int y)
{
	if (m_pPS)
		SetWindowPos(NULL, x, y, m_pPS->GetWidth(), m_pPS->GetHeight(),
					SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
}

// virtual D:\MsDev\MFC\src\WINBTN.CPP(113)
void CPSButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	if (!m_pPS)
		return;
	m_pPS->SetCell(PSBTN_NORMAL, 0);
	UINT state = lpDIS->itemState;
	if ((state & ODS_SELECTED) && (PSBTN_SELECTED < m_pPS->GetNumCellRows()))
		m_pPS->SetCell(PSBTN_SELECTED, 0);
	else if (state & ODS_FOCUS)
	{
		if (PSBTN_FOCUS < m_pPS->GetNumCellRows())
			m_pPS->SetCell(PSBTN_FOCUS, 0);
		else
			m_pPS->SetCell(PSBTN_NORMAL, 0);
	}
	else if (state & ODS_DISABLED)
	{
		if (PSBTN_DISABLED < m_pPS->GetNumCellRows())
			m_pPS->SetCell(PSBTN_DISABLED, 0);
		else
			m_pPS->SetCell(PSBTN_NORMAL, 0);
	}

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CPalette* pPalOld = NULL;
	if (m_pPal)
		pPalOld = pDC->SelectPalette(m_pPal, FALSE);

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);
	if (m_pPS)
		m_pPS->Draw(pDC, rect.TopLeft());
	if (pPalOld)
		pDC->SelectPalette(pPalOld, FALSE);
}

BEGIN_MESSAGE_MAP(CPSButton, CButton)
	//{{AFX_MSG_MAP(CPSButton)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSButton message handlers

BOOL CPSButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
//	if (!(GetState() & 0x0008))	// check if it doesn't have a focus yet
//		SetState(TRUE);			// then highlights it.
// commented out due to flickering problems on Rendering
//	::SetCursor(AfxGetApp()->LoadCursor(IDC_HARROW));
	return TRUE;
//	return CButton::OnSetCursor(pWnd, nHitTest, message);
}
