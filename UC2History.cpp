//	CUC2History: History Panel for UniChat 2
//
//==========================================================
//	(C) Programmed by Kim, Soomin, Mar 18, 1996
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "UC2.h"
#include "UC2History.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CRect RECT_PANEL(0, 0, 180, 372);
/////////////////////////////////////////////////////////////////////////////
// CUC2History

CUC2History::CUC2History()
{
	m_bInitialized = FALSE;
}

CUC2History::~CUC2History()
{
}

BEGIN_MESSAGE_MAP(CUC2History, CDialogBar)
	//{{AFX_MSG_MAP(CUC2History)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUC2History message handlers
BOOL CUC2History::Create(CWnd* pParentWnd, UINT nStyle)
{
	TRACE0("CUC2History::Create()\n");
	BOOL bRes = CDialogBar::Create(pParentWnd, CG_IDD_HISTORYPANEL,
							nStyle, CG_ID_VIEW_HISTORYPANEL);
	// The DialogBar has been created.
	return bRes;
}

// Called by the parent after creation of CUC2History object and window
BOOL CUC2History::InitControls()
{
	CWnd* pW = GetDlgItem(IDC_EDIT_HISTORY);
	CRect rcEdit(4, 6, RECT_PANEL.Width()-4, RECT_PANEL.Height()-4);
	pW->SetWindowPos(NULL, rcEdit.left, rcEdit.top, rcEdit.Width(), rcEdit.Height(),
					SWP_NOZORDER | SWP_NOACTIVATE);

	// Window has been created...
//	if (!m_eHistory.SubclassDlgItem(IDC_EDIT_HISTORY, this))
//	{
//		TRACE0("m_EditHistory.SubclassDlgItem failed!\n");
//		return FALSE;
//	}
	m_bInitialized = TRUE;
	return TRUE;
}

void CUC2History::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	SetWindowPos(NULL, RECT_PANEL.left, RECT_PANEL.top,
		RECT_PANEL.Width(), RECT_PANEL.Height(),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}
