//
//	CEditHistory
//
//	(C) Programmed by Kim, Soomin, Feb 2, 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
/////////////////////////////////////////////////////////////////////////////
// CEditHistory window

#ifndef __EDITHISTORY_H
#define __EDITHISTORY_H

// Subclassing CEdit has the problem to halt the system for a while
// when the input data are sth. as "........................................."

class CEditHistory : public CEdit	// CRichEditCtrl
{
// Construction
public:
	CEditHistory();

// Attributes
public:

// Operations
public:
	HWND			GetNotepad();
	void			SendTextToNotepad();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditHistory)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditHistory();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditHistory)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif