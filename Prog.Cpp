// ===========================================================================
// File: P R O G R E S S . C P P
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Description:
//
//  This sample demonstrates using a URL moniker to download information.
// The key routines include the implementation of IBindStatusCallback
// and the CDownload::DoDownload routine, which creates and binds to the
// URL moniker.
//
// Instructions:
//
//  To use this sample:
//   * build it using the NMAKE command. NMAKE will create PROGRESS.EXE.
//   * run PROGRESS.EXE. specify the resource to download by passing an
//     URL on the command-line. use no command-line argument to default to
//     downloading "http://www.msn.com".
//  * The program displays a dialog box containing information about the
//    download:
//     - a status message, describing the current status of the download
//     - a progress message, describing the amount of information that
//       has been downloaded.
//     - a text box, which displays chunks of the download information as
//       it arrives.
//  * Press the "GO" button to begin the download.
//
// Sample update:-
//   * New feature include Progress Bar to indicate progress of the download
//	 * Edit box replaces the old text box. Also the whole file can be viewed. 
//     If the file exceeds 32KB then only the first 32 KB from the last data
//	   pull will be displayed.  If the pull exceeds 32 KB, then only the first
//     32 KB of the last Read will be displayed.
// 
///
// File updated by Jason Strayer 27-Aug-1997
// File updated by Jobi George 19-June-1996
// File updated by Ramesha Gopalakrishna 28-June-1996
// File updated by Oliver Wallace 9-July-1996
// File updated by Soomin Kim 6-April-1998
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include "stdafx.h"
#include "urlmon.h"
#include "wininet.h"
#include "resource.h"
#include "Prog.h"

// ===========================================================================
//                     CBindStatusCallback Implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::CBindStatusCallback(HWND hwndFrame, LPCTSTR szFile)
{
	TRACE("CBindStatusCallback::CBindStatusCallback\n");
	m_hFrame		= hwndFrame;
	m_pbinding		= NULL;
	m_pstm			= NULL;
	m_cRef			= 1;
	m_pFile			= NULL;
	m_strFile		= szFile;
}  // CBindStatusCallback

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::~CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::~CBindStatusCallback()
{
	TRACE("CBindStatusCallback::~CBindStatusCallback\n");
}  // ~CBindStatusCallback

/*
inline void CBindStatusCallback::SetWndText(HWND hwnd, LPCWSTR szText)
{
	if (IsWindow(hwnd))
	{
		char	rgchBuf[INTERNET_MAX_PATH_LENGTH];
		WideCharToMultiByte(CP_ACP, 0, szText, -1, rgchBuf, INTERNET_MAX_PATH_LENGTH, 0, 0);
		SetWindowText(hwnd, rgchBuf);
	}
}
*/

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::QueryInterface
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::QueryInterface(REFIID riid, void** ppv)
{
	*ppv = NULL;

	if (riid==IID_IUnknown || riid==IID_IBindStatusCallback)
	{
		*ppv = this;
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}  // CBindStatusCallback::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnStartBinding
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnStartBinding(DWORD dwReserved, IBinding* pbinding)
{
	TRACE("CBindStatusCallback::OnStartBinding\n");
	if (m_pbinding)
		m_pbinding->Release();
	m_pbinding = pbinding;
	if (m_pbinding)
	{
		m_pbinding->AddRef();
		PostMessage(CMD_BIND_START);	// SetStatus(L"Status: Starting to bind...");
	}
	TRACE0("m_pFile = new CFile;\n");
	m_pFile = new CFile;
	if (!m_pFile->Open(m_strFile, CFile::modeReadWrite | CFile::modeCreate | CFile::shareExclusive))
	{
		delete m_pFile;
		m_pFile = NULL;
		AfxMessageBox("Failed to open file");
		return FALSE;
	}
	PostMessage(CMD_BIND_FILE_OPENED);
	return S_OK;
}  // CBindStatusCallback::OnStartBinding

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnStopBinding
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnStopBinding(HRESULT hrStatus, LPCWSTR pszError)
{
	TRACE("CBindStatusCallback::OnStopBinding\n");
	if (hrStatus)
		PostMessage(CMD_BIND_FAILED);	// SetStatus(L"Status: File download Failed.");

	if (m_pbinding)
	{
		m_pbinding->Release();
		m_pbinding = NULL;
	}

	CloseFile();
	return S_OK;
}  // CBindStatusCallback::OnStopBinding

void CBindStatusCallback::CloseFile()
{
	if (m_pFile)
	{
		TRACE("m_pFile->Close();\n");
		m_pFile->Close();
		delete m_pFile;
		m_pFile = NULL;
		PostMessage(CMD_BIND_FILE_CLOSED);
	}
}

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetPriority
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::GetPriority(LONG* pnPriority)
{
	return E_NOTIMPL;
}  // CBindStatusCallback::GetPriority

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnLowResource
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnLowResource(DWORD dwReserved)
{
	return E_NOTIMPL;
}  // CBindStatusCallback::OnLowResource

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnProgress
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
											ULONG ulStatusCode, LPCWSTR szStatusText)
{
	TRACE("CBindStatusCallback::OnProgress(%lu)\n", ulProgress);
	char	sz[255];

	if (szStatusText)
		WideCharToMultiByte(CP_ACP, 0, szStatusText, -1, sz, 255, 0, 0);

	if (lstrlen(sz) > 0)
	{
		char    msg[256];
		char	buf[256];
	//	WCHAR   out[256*2];

		char* p = strrchr(sz, '/');
		if (p)
		{
			p++;
			strcpy_s(buf, p);
			wsprintf(msg, "%s %d of %d", buf, ulProgress, (ulProgress > ulProgressMax) ? ulProgress : ulProgressMax);
		//	MultiByteToWideChar(CP_ACP, 0, msg, -1, out, sizeof(out));

			SendMessage(CMD_BIND_PROGRESS_MSG, 0, (LPARAM)msg);
		}
		TRACE("%lu, %lu\n", ulProgress, ulProgressMax);
		SendMessage(CMD_BIND_PROGRESS_BAR, (WPARAM)ulProgress, (LPARAM)ulProgressMax);	// by value
	}
	return NOERROR;
}  // CBindStatusCallback::OnProgress

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetBindInfo
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindInfo)
{
	if (!pbindInfo || !pbindInfo->cbSize || !pgrfBINDF)
		return E_INVALIDARG;

	*pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA |
				 BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;

	// remember incoming cbSize
	ULONG cbSize = pbindInfo->cbSize;
	// zero out structure
	::ZeroMemory(pbindInfo, cbSize);

	// restore cbSize
	pbindInfo->cbSize = cbSize;
	pbindInfo->dwBindVerb = BINDVERB_GET;

	return S_OK;
}	// CBindStatusCallback::GetBindInfo

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnDataAvailable
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pfmtetc, STGMEDIUM* pstgmed)
{
	TRACE("CBindStatusCallback::OnDataAvailable(%ld)\n", dwSize);
	HRESULT hr=S_OK;

	// Get the Stream passed
	if (BSCF_FIRSTDATANOTIFICATION & grfBSCF)
	{
		if (!m_pstm && (pstgmed->tymed == TYMED_ISTREAM))
		{
			m_pstm = pstgmed->pstm;
			if (m_pstm)
				m_pstm->AddRef();
		}
	}

	// If there is some data to be read then go ahead and read them
	if (m_pstm && (dwSize > 0))
	{
		DWORD dwRead = dwSize;		// Minimum amount available that hasn't been read
		DWORD dwActuallyRead = 0;	// Placeholder for amount read during this pull

		if (dwRead > 0)
		{
			do
			{
				char* pNewstr = new char[dwRead + 1];
				if (!pNewstr)
					return S_FALSE;
				hr = m_pstm->Read(pNewstr, dwRead, &dwActuallyRead);
				pNewstr[dwActuallyRead] = 0;
				// If we really read something then lets add it to the Edit box
				if (m_pFile && (dwActuallyRead > 0))
				{
					TRY
					{
						m_pFile->Write(pNewstr, dwActuallyRead);
					}
					CATCH(CFileException, e)
					{
						TRACE0("Failed to write file.\n");
						return FALSE;
					} END_CATCH
				}
				delete [] pNewstr;
			} while (!(hr == E_PENDING || hr == S_FALSE) && SUCCEEDED(hr));
		}
	}	//	if (m_pstm && dwSize > 0)

	if (BSCF_LASTDATANOTIFICATION & grfBSCF)
	{
		if (m_pstm)
			m_pstm->Release();
		hr = S_OK;	// If it was the last data then we should return S_OK as we just finished reading everything
		PostMessage(CMD_BIND_DOWNLOAD_DONE);	// SetStatus(L"Status: File downloaded.");
		TRACE0("Status: File downloaded.\n");
	}
	return hr;
}	// CBindStatusCallback::OnDataAvailable

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnObjectAvailable
// ---------------------------------------------------------------------------
STDMETHODIMP CBindStatusCallback::OnObjectAvailable(REFIID riid, IUnknown* punk)
{
	return E_NOTIMPL;
}	// CBindStatusCallback::OnObjectAvailable

// ===========================================================================
//                           CDownload Implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CDownload::CDownload
// ---------------------------------------------------------------------------
CDownload::CDownload(LPCTSTR szURL)
{
	TRACE("CDownload::CDownload\n");
	static WCHAR	szwURL[MAX_PATH];			//	L"http://www.msn.com";
	MultiByteToWideChar(CP_ACP, 0, szURL, -1, szwURL, MAX_PATH);
	m_url	= szwURL;
	m_pmk	= 0;
	m_pbc	= 0;
	m_pbsc	= 0;
}	// CDownload

// ---------------------------------------------------------------------------
// %%Function: CDownload::~CDownload
// ---------------------------------------------------------------------------
CDownload::~CDownload()
{
	TRACE("CDownload::~CDownload\n");
	if (m_pmk)
		m_pmk->Release();
	if (m_pbc)
		m_pbc->Release();
	if (m_pbsc)
	{
		m_pbsc->Release();
		delete m_pbsc;
	}
}	// ~CDownload

// ---------------------------------------------------------------------------
// %%Function: CDownload::DoDownload
// ---------------------------------------------------------------------------
HRESULT CDownload::DoDownload(HWND hwndFrame, LPCTSTR szFile)
{
	TRACE("CDownload::DoDownload\n");
	IStream* pstm = NULL;

	HRESULT hr = CreateURLMoniker(NULL, m_url, &m_pmk);
	if (FAILED(hr))
		goto LErrExit;

	m_pbsc = new CBindStatusCallback(hwndFrame, szFile);
	if (!m_pbsc)
	{
		hr = E_OUTOFMEMORY;
		goto LErrExit;
	}

	hr = CreateBindCtx(0, &m_pbc);
	if (FAILED(hr))
		goto LErrExit;

	hr = RegisterBindStatusCallback(m_pbc, m_pbsc, 0, 0L);
	if (FAILED(hr))
		goto LErrExit;

	hr = m_pmk->BindToStorage(m_pbc, 0, IID_IStream, (void**)&pstm);
	if (FAILED(hr))
		goto LErrExit;

	return hr;

LErrExit:
	if (m_pbc)
	{
		m_pbc->Release();
		m_pbc = NULL;
	}
	if (m_pbsc)
	{
		m_pbsc->Release();
		m_pbsc = NULL;
	}
	if (m_pmk)
	{
		m_pmk->Release();
		m_pmk = NULL;
	}
	if (pstm)
	{
		pstm->Release();
		pstm = NULL;
	}
	return hr;
}	// CDownload::DoDownload

void CDownload::CancelDownload()
{
	if (m_pbsc)
	{
		m_pbsc->CloseFile();
	}
}
