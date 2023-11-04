// GenSDIView.h : interface of the CGenSDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENSDIVIEW_H__74B93990_AA95_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_GENSDIVIEW_H__74B93990_AA95_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGenSDIView : public CView
{
protected: // create from serialization only
	CGenSDIView();
	DECLARE_DYNCREATE(CGenSDIView)

// Attributes
public:
	CGenSDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenSDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGenSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGenSDIView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GenSDIView.cpp
inline CGenSDIDoc* CGenSDIView::GetDocument()
   { return (CGenSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENSDIVIEW_H__74B93990_AA95_11D1_80E2_080009B9F339__INCLUDED_)
