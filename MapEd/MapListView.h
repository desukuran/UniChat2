#if !defined(AFX_MAPLISTVIEW_H__7ECC1E16_9C09_11D1_80E2_288A06C10000__INCLUDED_)
#define AFX_MAPLISTVIEW_H__7ECC1E16_9C09_11D1_80E2_288A06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MapListView.h : header file
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

/////////////////////////////////////////////////////////////////////////////
// CMapListView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMapEdDoc;
class CPhasedSprite;

class CMapListView : public CFormView
{
protected:
	CMapListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMapListView)

	enum
	{
		IL_TILE=0,
		IL_STATIC,
		IL_ANIMATED,
		IL_AVATAR
	} OBJECT_IL_INDEX;

// Form Data
public:
	//{{AFX_DATA(CMapListView)
	enum { IDD = IDD_DIALOG_VIEW };
	CListCtrl	m_lcObject;
	CString	m_strCellInfo;
	int		m_nCellID;
	//}}AFX_DATA

// Attributes
public:
	CMapEdDoc*	GetDocument();
	int			GetSelectedResName(CString& strName) const;
	WORD		GetSelectedResType() const;

// Operations
public:
	void		UpdateList();
	void		UpdateItemImage(const int nIndex);
	void		SetSelectedItem(const int nIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMapListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void Initialize();
	CImageList		m_ilObject;
	int				m_nIndex;	// Current selected item
	CPhasedSprite*	m_pPS;		// Selected item's image
	CRect			m_rcDraw;	// Draw Region

	// Generated message map functions
	//{{AFX_MSG(CMapListView)
	afx_msg void OnClickListObj(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDblclkListObj(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bFirst;
};

#ifndef _DEBUG  // debug version in MapEdView.cpp
inline CMapEdDoc* CMapListView::GetDocument()
   { return (CMapEdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPLISTVIEW_H__7ECC1E16_9C09_11D1_80E2_288A06C10000__INCLUDED_)
