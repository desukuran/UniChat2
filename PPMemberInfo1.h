// PPMemberInfo1.h : header file
//

#ifndef __PPMEMBERINFO1_H__
#define __PPMEMBERINFO1_H__

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CPPMemberInfo1 dialog

class CPPMemberInfo1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPMemberInfo1)

// Construction
public:
	CPPMemberInfo1();
	~CPPMemberInfo1();

// Dialog Data
	//{{AFX_DATA(CPPMemberInfo1)
	enum { IDD = IDD_PP_MEMBER1 };
	CString	m_strNick;
	CString	m_strRealName;
	CString	m_strUserID;
	CString	m_strVersion;
	CString	m_strSexAge;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPMemberInfo1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPMemberInfo1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPPMemberInfo2 dialog

class CPPMemberInfo2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPMemberInfo2)

// Construction
public:
	CPPMemberInfo2();
	~CPPMemberInfo2();

// Dialog Data
	//{{AFX_DATA(CPPMemberInfo2)
	enum { IDD = IDD_PP_MEMBER2 };
	CString	m_strProfile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPMemberInfo2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPMemberInfo2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // __PPMEMBERINFO1_H__
