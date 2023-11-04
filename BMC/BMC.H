// BMC.h : main header file for the BMC application
//

#if !defined(AFX_BMC_H__C193E4A8_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
#define AFX_BMC_H__C193E4A8_88DD_11D1_ACEA_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBMCApp:
// See BMC.cpp for the implementation of this class
//

class CBMCApp : public CWinApp
{
public:
	CBMCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBMCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMC_H__C193E4A8_88DD_11D1_ACEA_080009B9F339__INCLUDED_)
