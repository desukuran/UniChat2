// PPActor.cpp : implementation file
//
//==================================================
//	(C) Programmed by Kim, Soomin, Mar 1998
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================

#include "stdafx.h"
#include "resource.h"
#include "PPActor.h"
#include "PSJoinChannel.h"
#include "UC2Ani/DIB.h"
#include "UC2Ani/PhSprite.h"
#include "ResMan.h"
#include "Behavior.h"	// CActorDesc

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CResMan gResMan;

IMPLEMENT_DYNCREATE(CPPActor, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CPPActor property page

CPPActor::CPPActor() : CPropertyPage(CPPActor::IDD)
{
	TRACE0("CPPActor::CPPActor()\n");
	//{{AFX_DATA_INIT(CPPActor)
	m_nAge = 20;
	//}}AFX_DATA_INIT
/*
	m_strName = _T("");
	m_strProfile = _T("");
	m_strSex = _T("");
	m_strHomePage = _T("");
	m_strChatID = _T("");
	m_strUnitelID = _T("");
	m_strVersion = _T("");
*/
	m_nCharID	= 0;
	m_nCellID	= 0;
	m_nSex		= 0;
	m_pPSActor	= NULL;
}

CPPActor::~CPPActor()
{
	TRACE0("CPPActor::~CPPActor()\n");
	if (m_pPSActor)
		delete m_pPSActor;
}

void CPPActor::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPActor)
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
	DDX_Control(pDX, IDC_LB_ACTORS, m_lbActors);
	DDX_Control(pDX, IDC_SB_ACTOR, m_sbActor);
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDV_MinMaxUInt(pDX, m_nAge, 0, 200);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 20);
	DDX_Text(pDX, IDC_EDIT_PROFILE, m_strProfile);
	DDV_MaxChars(pDX, m_strProfile, 256);
	DDX_Text(pDX, IDC_EDIT_HOMEPAGE, m_strHomePage);
	DDX_Text(pDX, IDC_EDIT_CHAT_ID, m_strChatID);
	DDV_MaxChars(pDX, m_strChatID, 20);
	DDX_Text(pDX, IDC_EDIT_UNITEL_ID, m_strUnitelID);
	DDV_MaxChars(pDX, m_strUnitelID, 12);
	DDX_Text(pDX, IDC_ST_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPPActor, CPropertyPage)
	//{{AFX_MSG_MAP(CPPActor)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT_AGE, OnChangeEditAge)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_PROFILE, OnChangeEditProfile)
	ON_LBN_SELCHANGE(IDC_LB_ACTORS, OnSelchangeLbActors)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, OnSelchangeComboSex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPPActor::OnEraseBkgnd(CDC* pDC) 
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	return pPSJC->OnPageEraseBkgnd(pDC);
}

BOOL CPPActor::OnInitDialog() 
{
	TRACE0("CPPActor::OnInitDialog()\n");
	CPropertyPage::OnInitDialog();
	
	m_cbSex.SetCurSel(m_nSex);

	for (int i=0; i < gResMan.GetNumActorDescs(); i++)
	{
		CActorDesc* pAD = gResMan.GetActorDesc(i);
		if (pAD)
		{
			CString* pNick = pAD->GetNick();
			if (pNick)
				m_lbActors.AddString(*pNick);
		}
	}
	m_lbActors.SetCurSel(0);

	m_rcActor.left = 10;
	m_rcActor.top = 10;
	UpdateActorImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
HBRUSH CPPActor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)*pPSJC->GetNullBrush();
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
*/

void CPPActor::OnSize(UINT nType, int cx, int cy) 
{
	TRACE("CPPActor::OnSize(%d,%d,%d)\n", nType, cx, cy);
	CPropertyPage::OnSize(nType, cx, cy);
/*
	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	if (pPSJC->GetDIBBack())
	{
		SetWindowPos(NULL, 0, 0, pPSJC->GetDIBBack()->GetWidth(), pPSJC->GetDIBBack()->GetHeight(),
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
*/
}

void CPPActor::OnChangeEditAge() 
{
	SetModified();
}

void CPPActor::OnChangeEditName() 
{
	SetModified();
}

void CPPActor::OnChangeEditProfile() 
{
	SetModified();
}

void CPPActor::OnSelchangeLbActors()
{
	m_nCharID = m_lbActors.GetCurSel();
	m_nCellID = 0;
	UpdateActorImage();
	SetModified();
}

void CPPActor::OnSelchangeComboSex() 
{
	m_nSex = m_cbSex.GetCurSel();
	TRACE("Sex:%d\n", m_nSex);
	SetModified();
}

void CPPActor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_ACTOR);

	if (pScrollBar == pSB)
	{
		if (!m_pPSActor)
			return;
		int nCells = m_pPSActor->GetNumCells();
		int nMin, nMax;
		pSB->GetScrollRange(&nMin, &nMax);
		switch (nSBCode)
		{
		case SB_THUMBPOSITION:
			m_nCellID = nPos;
			pSB->SetScrollPos(nPos);
			break;
		case SB_LINELEFT:
			m_nCellID = pSB->GetScrollPos() - 1;
			if (m_nCellID < nMin)
				m_nCellID = nMax;	// Wrap
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_LINERIGHT:
			m_nCellID = pSB->GetScrollPos() + 1;
			if (m_nCellID > nMax)
				m_nCellID = nMin;	// Wrap
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_PAGELEFT:
			m_nCellID = pSB->GetScrollPos() - (nMax - nMin) / 5;
			if (m_nCellID < nMin)
				m_nCellID = nMin;
			pSB->SetScrollPos(m_nCellID);
			break;
		case SB_PAGERIGHT:
			m_nCellID = pSB->GetScrollPos() + (nMax - nMin) / 5;
			if (m_nCellID > nMax)
				m_nCellID = nMax;
			pSB->SetScrollPos(m_nCellID);
			break;
		}
		InvalidateRect(&m_rcActor, FALSE);
		UpdateData(FALSE);
	}
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

// m_nCharID can be set externally by calling CPSJoinChannel::SetMemberInfo
void CPPActor::UpdateActorImage()
{
	CActorDesc* pAD = gResMan.GetActorDesc(m_nCharID);
	if (!pAD)
	{
		TRACE0("CPPActor - ActorDesc not found!\n");
		return;
	}
	CString* pstrRes = pAD->GetResName();
	if (!pstrRes)
	{
		TRACE0("CPPActor - ActorDesc - ResName not found!\n");
		return;
	}
	CString strResName(*pstrRes);
	// We'll not reuse DIB here:
	// Since this image is not necessary to be resident in memory.
	CPhasedSprite* pPS = gResMan.LoadPhasedSprite(strResName, FALSE);
	if (!pPS)
	{
		delete pPS;
		strResName += " not found!";
		AfxMessageBox(strResName);
		return;
	}

	if (m_pPSActor)
		delete m_pPSActor;	// Delete previously allocated resource
	m_pPSActor = pPS;
	m_nCellID = 0;
	m_pPSActor->SetCell(m_nCellID);
	CRect rc;
	m_pPSActor->GetRect(rc);
	m_rcActor.right = m_rcActor.left + rc.Width();
	m_rcActor.bottom = m_rcActor.top + rc.Height();

	CScrollBar* pSB = (CScrollBar*)GetDlgItem(IDC_SB_ACTOR);
	ASSERT(pSB);
	pSB->SetWindowPos(NULL, m_rcActor.left, m_rcActor.bottom+2,
					m_rcActor.Width()*2, 15,
					SWP_NOZORDER | SWP_NOACTIVATE);
	pSB->SetScrollRange(0, m_pPSActor->GetNumCells()-1);
	pSB->SetScrollPos(0);

	m_lbActors.SetCurSel(m_nCharID);

	InvalidateRect(&m_rcActor);
}

void CPPActor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CPSJoinChannel* pPSJC = (CPSJoinChannel*)GetParent();
	ASSERT(pPSJC);
	// If we have a palette, select and realize it.
	CPalette* pPalOld = NULL;
	if (pPSJC->GetPalette())
	{
		pPalOld = dc.SelectPalette(pPSJC->GetPalette(), FALSE);	// bForceBackground = FALSE
	//	pDC->RealizePalette();	// we realize in response to WM_QUERYNEWPALETTE
	}

	if (m_pPSActor)
	{
		m_pPSActor->SetCell(m_nCellID);
		CPoint ptLT(m_rcActor.left, m_rcActor.top);
		m_pPSActor->Draw(&dc, ptLT);
	}

	if (pPalOld)
		dc.SelectPalette(pPalOld, FALSE);
	// Do not call CPropertyPage::OnPaint() for painting messages
}
