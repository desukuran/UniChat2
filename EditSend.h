#if !defined(AFX_EDITSEND_H__E4B02724_B4CD_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_EDITSEND_H__E4B02724_B4CD_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditSend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditSend window

class CEditSend : public CEdit
{
// Construction
public:
	CEditSend();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditSend)
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		GetCurrentLine() const	{ return LineFromChar(LineIndex(-1)); }	// index from 0
	int		GetLastLine() const		{ return (GetLineCount() - 1); }
	void	ParseCommand(LPCSTR szText);
//	CBrush*	m_pEditBkBrush;

public:
	virtual ~CEditSend();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditSend)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITSEND_H__E4B02724_B4CD_11D1_80E2_080009B9F339__INCLUDED_)
