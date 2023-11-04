// MapEnvDlg.cpp : implementation file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"
#include "MapEnvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEnvDlg dialog


CMapEnvDlg::CMapEnvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapEnvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapEnvDlg)
	m_nTileHeight = 0;
	m_nTileWidth = 0;
	m_nScrHeight = 0;
	m_nScrWidth = 0;
	m_strDataPath = _T("");
	m_strPalFile = _T("");
	//}}AFX_DATA_INIT
	m_bReadOnly = FALSE;
}


void CMapEnvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapEnvDlg)
	DDX_Text(pDX, IDC_EDIT_TILE_H, m_nTileHeight);
	DDV_MinMaxInt(pDX, m_nTileHeight, 4, 480);
	DDX_Text(pDX, IDC_EDIT_TILE_W, m_nTileWidth);
	DDV_MinMaxInt(pDX, m_nTileWidth, 4, 640);
	DDX_Text(pDX, IDC_EDIT_SCREEN_H, m_nScrHeight);
	DDV_MinMaxInt(pDX, m_nScrHeight, 32, 768);
	DDX_Text(pDX, IDC_EDIT_SCREEN_W, m_nScrWidth);
	DDV_MinMaxInt(pDX, m_nScrWidth, 64, 1024);
	DDX_Text(pDX, IDC_EDIT_DATA_PATH, m_strDataPath);
	DDX_Text(pDX, IDC_EDIT_PALFILE, m_strPalFile);
	DDV_MaxChars(pDX, m_strPalFile, 12);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapEnvDlg, CDialog)
	//{{AFX_MSG_MAP(CMapEnvDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEnvDlg message handlers

BOOL CMapEnvDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_bReadOnly)
	{
		GetDlgItem(IDC_EDIT_TILE_W)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TILE_H)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCREEN_W)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCREEN_H)->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
