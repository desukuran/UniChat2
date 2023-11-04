#if !defined(AFX_PALETTEDLG_H__460C5624_91A5_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_PALETTEDLG_H__460C5624_91A5_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PaletteDlg.h : header file
//

class CDIBPal;

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg dialog

class CPaletteDlg : public CDialog
{
// Construction
public:
	CPaletteDlg(CWnd* pParent = NULL);   // standard constructor

public:
	void	SetPalette(CDIBPal* pPal)	{ m_pPal = pPal; }

// Dialog Data
	//{{AFX_DATA(CPaletteDlg)
	enum { IDD = IDD_PALETTE };
	int		m_sbBlue;
	int		m_sbGreen;
	CString	m_stRGB;
	int		m_sbRed;
	BOOL	m_bShowIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDIBPal*	m_pPal;
	CRect		m_rcPal;

	// Generated message map functions
	//{{AFX_MSG(CPaletteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheckShowIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALETTEDLG_H__460C5624_91A5_11D1_80E2_080009B9F339__INCLUDED_)
