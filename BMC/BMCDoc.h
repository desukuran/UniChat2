// BMCDoc.h : interface of the CBMCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMCDOC_H__C193E4AE_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
#define AFX_BMCDOC_H__C193E4AE_88DD_11D1_ACEA_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../UC2Ani/SpritLst.h"

class CDIB;
class CBMCView;

class CBMCDoc : public CDocument
{
protected: // create from serialization only
	CBMCDoc();
	DECLARE_DYNCREATE(CBMCDoc)

// Attributes
public:
    CDIB*			GetBackground()	{ return m_pBkgndDIB; }
    CSpriteList*	GetSpriteList()	{ return &m_SpriteList; }
    void			GetSceneRect(CRect& prc);

// Operations
public:
    BOOL			SetBackground(CDIB* pDIB);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBMCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	CDIB*		m_pBkgndDIB;	// ptr to background DIB
    CSpriteList	m_SpriteList;	// sprite list

	CBMCView*	GetBMCView();

// Generated message map functions
protected:
	//{{AFX_MSG(CBMCDoc)
	afx_msg void OnFileLoadsprite();
	afx_msg void OnFileLoadbkgnd();
	afx_msg void OnViewPalette();
	afx_msg void OnViewOutline();
	afx_msg void OnFileSaveBkg();
	afx_msg void OnFileSaveSprite();
	afx_msg void OnUpdateFileSaveBkg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveSprite(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMCDOC_H__C193E4AE_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
