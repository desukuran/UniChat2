#if !defined(AFX_PPSHOPPINGCART_H__19BBF281_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_)
#define AFX_PPSHOPPINGCART_H__19BBF281_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPShoppingCart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPShoppingCart dialog

class CPPShoppingCart : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPShoppingCart)

// Construction
public:
	CPPShoppingCart();
	~CPPShoppingCart();

// Dialog Data
	//{{AFX_DATA(CPPShoppingCart)
	enum { IDD = IDD_PP_CART };
	CListCtrl	m_lcCart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPShoppingCart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPShoppingCart)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPSHOPPINGCART_H__19BBF281_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_)
