#if !defined(AFX_MAPENVDLG_H__18238822_A15C_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_MAPENVDLG_H__18238822_A15C_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MapEnvDlg.h : header file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

/////////////////////////////////////////////////////////////////////////////
// CMapEnvDlg dialog

class CMapEnvDlg : public CDialog
{
// Construction
public:
	CMapEnvDlg(CWnd* pParent = NULL);   // standard constructor
	
	void	SetReadOnly()	{ m_bReadOnly = TRUE; }

// Dialog Data
	//{{AFX_DATA(CMapEnvDlg)
	enum { IDD = IDD_ENVIRONMENT };
	int		m_nTileHeight;
	int		m_nTileWidth;
	int		m_nScrHeight;
	int		m_nScrWidth;
	CString	m_strDataPath;
	CString	m_strPalFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEnvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL	m_bReadOnly;

	// Generated message map functions
	//{{AFX_MSG(CMapEnvDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPENVDLG_H__18238822_A15C_11D1_80E2_080009B9F339__INCLUDED_)
