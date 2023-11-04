#if !defined(AFX_JUNDATAPATHPROP_H__5959C5C2_B813_11D1_9169_444553540001__INCLUDED_)
#define AFX_JUNDATAPATHPROP_H__5959C5C2_B813_11D1_9169_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JunDataPathProp.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CJunDataPathProp command target

class CJunDataPathProp : public CDataPathProperty
{
// Attributes
public:

// Operations
public:
	CJunDataPathProp();
	virtual ~CJunDataPathProp();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJunDataPathProp)
	protected:
	virtual void OnStartBinding();
	virtual void OnStopBinding(HRESULT hresult, LPCTSTR szError);
	virtual void OnDataAvailable(DWORD dwSize, DWORD bscfFlag);
	virtual void OnProgress(ULONG ulProgress, ULONG ulProgressMax,
		ULONG ulStatusCode, LPCTSTR szStatusText);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CJunDataPathProp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNDATAPATHPROP_H__5959C5C2_B813_11D1_9169_444553540001__INCLUDED_)
