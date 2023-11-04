// UDSGenView.h : interface of the CUDSGenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDSGENVIEW_H__C3C37D0D_AD07_11D1_9169_0000F0610C92__INCLUDED_)
#define AFX_UDSGENVIEW_H__C3C37D0D_AD07_11D1_9169_0000F0610C92__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUDSGenView : public CFormView
{
protected: // create from serialization only
	CUDSGenView();
	DECLARE_DYNCREATE(CUDSGenView)

public:
	//{{AFX_DATA(CUDSGenView)
	enum { IDD = IDD_UDSGEN_FORM };
	CProgressCtrl	m_ctlProgress;
	CListBox	m_lstSource;
	//}}AFX_DATA

// Attributes
public:
	CUDSGenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDSGenView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetFilename(CString fileName);
	virtual ~CUDSGenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUDSGenView)
	afx_msg void OnGenerate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in UDSGenView.cpp
inline CUDSGenDoc* CUDSGenView::GetDocument()
   { return (CUDSGenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDSGENVIEW_H__C3C37D0D_AD07_11D1_9169_0000F0610C92__INCLUDED_)
