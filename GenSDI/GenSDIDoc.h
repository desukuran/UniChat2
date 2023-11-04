// GenSDIDoc.h : interface of the CGenSDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENSDIDOC_H__74B9398E_AA95_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_GENSDIDOC_H__74B9398E_AA95_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGenSDIDoc : public CDocument
{
protected: // create from serialization only
	CGenSDIDoc();
	DECLARE_DYNCREATE(CGenSDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenSDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGenSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGenSDIDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENSDIDOC_H__74B9398E_AA95_11D1_80E2_080009B9F339__INCLUDED_)
