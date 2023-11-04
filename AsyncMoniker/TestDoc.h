// TestDoc.h : interface of the CTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDOC_H__0BCFBAAC_B807_11D1_9169_444553540001__INCLUDED_)
#define AFX_TESTDOC_H__0BCFBAAC_B807_11D1_9169_444553540001__INCLUDED_

#include "JunAsyncMF.h"	// Added by ClassView
#include "JunDataPathProp.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestDoc : public CDocument
{
protected: // create from serialization only
	CTestDoc();
	DECLARE_DYNCREATE(CTestDoc)

// Attributes
public:
	CJunDataPathProp*	GetJunDPPMIT() { return &m_dataPPMIT; }
	BOOL				IsCurrentMITOK() { return m_bCurrentMIT;}

// Operations
public:

	int m_nMITing; // 1:MIT, 2:SIT, 0:Default

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnStopBinding(WPARAM wParam, LPARAM lParam);
	void SetCurrentMIT(BOOL available);
	void SetCurrentSIT(BOOL available);
	virtual ~CTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_bCurrentMIT;
	BOOL m_bCurrentSIT;
	CString m_strCurrentMIT;
	CString m_strCurrentSIT;
	CJunDataPathProp m_dataPPMIT;
	CJunDataPathProp m_dataPPSIT;
		
	//{{AFX_MSG(CTestDoc)
	afx_msg void OnChannelsC1forest();
	afx_msg void OnChannelsC1garden();
	afx_msg void OnChannelsCastle1();
	afx_msg void OnChannelsCemetary();
	afx_msg void OnChannelsHousa();
	afx_msg void OnChannelsHousb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDOC_H__0BCFBAAC_B807_11D1_9169_444553540001__INCLUDED_)
