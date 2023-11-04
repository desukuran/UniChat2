#if !defined(AFX_WHISPERDLG_H__4E6B0EC2_C674_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_WHISPERDLG_H__4E6B0EC2_C674_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WhisperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWhisperDlg dialog

class CWhisperDlg : public CDialog
{
// Construction
public:
	CWhisperDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWhisperDlg)
	enum { IDD = IDD_DIALOG_WHISPER };
	CString	m_strText;
	CString	m_strToID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhisperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWhisperDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHISPERDLG_H__4E6B0EC2_C674_11D1_80E2_080009B9F339__INCLUDED_)
