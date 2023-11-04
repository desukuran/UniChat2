// MapEd.h : main header file for the MAPED application
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_MAPED_H__7ECC1E06_9C09_11D1_80E2_288A06C10000__INCLUDED_)
#define AFX_MAPED_H__7ECC1E06_9C09_11D1_80E2_288A06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapEdApp:
// See MapEd.cpp for the implementation of this class
//

class CStage;

class CMapEdApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	CMapEdApp();

	void	SetStage(CStage* pStage)	{ m_pStage = pStage; }
	void	SetPause(const BOOL bPause)	{ m_bPause = bPause; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStage*		m_pStage;
	BOOL		m_bPause;

	//{{AFX_MSG(CMapEdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPED_H__7ECC1E06_9C09_11D1_80E2_288A06C10000__INCLUDED_)
