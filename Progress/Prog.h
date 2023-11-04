#ifndef	__PROG_H
#define __PROG_H

#include "urlmon.h"
#include "wininet.h"

#define BASE	(WM_USER + 200 + 100)
const UINT	CMD_BIND_START			= BASE;
const UINT	CMD_BIND_FAILED			= BASE+1;
const UINT	CMD_BIND_FILE_OPENED	= BASE+2;
const UINT	CMD_BIND_FILE_CLOSED	= BASE+3;
const UINT	CMD_BIND_PROGRESS_MSG	= BASE+4;	// SendMessage(CMD_BIND_PROGRESS_MSG, 0, (LPARAM)msg);
const UINT	CMD_BIND_PROGRESS_BAR	= BASE+5;	// SendMessage(CMD_BIND_PROGRESS_BAR, (WPARAM)ulProgress, (LPARAM)ulProgressMax);	// by value
const UINT	CMD_BIND_DOWNLOAD_DONE	= BASE+6;
#undef BASE

// %%Classes: ----------------------------------------------------------------
class CBindStatusCallback : public IBindStatusCallback
{
public:
	// IUnknown methods
	STDMETHODIMP    QueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP_(ULONG)    AddRef()    { return m_cRef++; }
	STDMETHODIMP_(ULONG)    Release()   { return m_cRef--; }
	//if (--m_cRef == 0) { delete this; return 0; } return m_cRef; }

	// IBindStatusCallback methods
	STDMETHODIMP    OnStartBinding(DWORD dwReserved, IBinding* pbinding);
	STDMETHODIMP    GetPriority(LONG* pnPriority);
	STDMETHODIMP    OnLowResource(DWORD dwReserved);
	STDMETHODIMP    OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode,
								LPCWSTR pwzStatusText);
	STDMETHODIMP    OnStopBinding(HRESULT hrResult, LPCWSTR szError);
	STDMETHODIMP    GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindinfo);
	STDMETHODIMP    OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pfmtetc,
								STGMEDIUM* pstgmed);
	STDMETHODIMP    OnObjectAvailable(REFIID riid, IUnknown* punk);

    // constructors/destructors
    CBindStatusCallback(HWND hwndFrame, LPCTSTR szFile);
    ~CBindStatusCallback();

	BOOL	PostMessage(UINT message, WPARAM wParam=0L, LPARAM lParam=0L) const
			{ return ::PostMessage(m_hFrame, message, wParam, lParam); }
	BOOL	SendMessage(UINT message, WPARAM wParam=0L, LPARAM lParam=0L) const
			{ return ::SendMessage(m_hFrame, message, wParam, lParam); }
	void CloseFile();

	// data members
	DWORD		m_cRef;
	IBinding*	m_pbinding;
	IStream*	m_pstm;
	HWND		m_hFrame;
	CFile*		m_pFile;
	CString		m_strFile;
};

class CDownload
{
public:
	CDownload(LPCWSTR szURL);
	~CDownload();
	HRESULT		DoDownload(HWND hwndFrame, LPCTSTR szFile);
	void		CancelDownload();
	LPCWSTR		m_url;

private:
	IMoniker*				m_pmk;
	IBindCtx*				m_pbc;
	CBindStatusCallback*	m_pbsc;	
};

#endif // __PROG_H