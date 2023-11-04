#if !defined(AFX_JUNASYNCMF_H__7F6B9704_B810_11D1_9169_444553540001__INCLUDED_)
#define AFX_JUNASYNCMF_H__7F6B9704_B810_11D1_9169_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JunAsyncMF.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CJunAsyncMF command target

class CJunAsyncMF : public CAsyncMonikerFile
{
// Attributes
public:

// Operations
public:
	CJunAsyncMF();
	virtual ~CJunAsyncMF();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJunAsyncMF)
	protected:
	virtual void OnDataAvailable(DWORD dwSize, DWORD bscfFlag);
	virtual void OnStartBinding(DWORD grfBSCOPTION);
	virtual void OnStopBinding(HRESULT hresult, LPCTSTR szError);
	virtual void OnProgress(ULONG ulProgress, ULONG ulProgressMax,
		ULONG ulStatusCode, LPCTSTR szStatusText);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CJunAsyncMF)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNASYNCMF_H__7F6B9704_B810_11D1_9169_444553540001__INCLUDED_)
