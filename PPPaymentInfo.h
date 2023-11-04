#if !defined(AFX_PPPAYMENTINFO_H__19BBF282_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_)
#define AFX_PPPAYMENTINFO_H__19BBF282_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPPaymentInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPPaymentInfo dialog

class CPPPaymentInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPPaymentInfo)

// Construction
public:
	CPPPaymentInfo();
	~CPPPaymentInfo();

// Dialog Data
	//{{AFX_DATA(CPPPaymentInfo)
	enum { IDD = IDD_PP_PAYMENT };
	CComboBox	m_cbCredit;
	CString	m_strCardNum;
	CString	m_strExpDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPPaymentInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPPaymentInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPPAYMENTINFO_H__19BBF282_474C_11D2_BCFD_0080C7EADFBB__INCLUDED_)
