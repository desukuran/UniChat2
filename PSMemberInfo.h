// PSMemberInfo.h : header file
//
// CPSMemberInfo is a modeless property sheet that is 
// created once and not destroyed until the application
// closes.  It is initialized and controlled from
// CPSFrame.
 
#ifndef __PSMEMBERINFO_H__
#define __PSMEMBERINFO_H__

#include "PPMemberInfo1.h"

/////////////////////////////////////////////////////////////////////////////
// CPSMemberInfo

class CPSMemberInfo : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSMemberInfo)

// Construction
public:
	CPSMemberInfo(CWnd* pWndParent = NULL);

// Attributes
public:
	CPPMemberInfo1 m_Page1;
	CPPMemberInfo2 m_Page2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSMemberInfo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSMemberInfo();
	 virtual void PostNcDestroy();

// Generated message map functions
protected:
	//{{AFX_MSG(CPSMemberInfo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PSMEMBERINFO_H__