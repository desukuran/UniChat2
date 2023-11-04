// UDSGen.h : main header file for the UDSGEN application
//

#if !defined(AFX_UDSGEN_H__C3C37D05_AD07_11D1_9169_0000F0610C92__INCLUDED_)
#define AFX_UDSGEN_H__C3C37D05_AD07_11D1_9169_0000F0610C92__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDSGenApp:
// See UDSGen.cpp for the implementation of this class
//

class CUDSGenApp : public CWinApp
{
public:
	CUDSGenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDSGenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDSGenApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDSGEN_H__C3C37D05_AD07_11D1_9169_0000F0610C92__INCLUDED_)
