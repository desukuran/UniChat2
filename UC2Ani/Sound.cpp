//
//	CSound
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "sound.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSound

IMPLEMENT_SERIAL(CSound, CObject, 0 /* Schema number*/ )

CSound::CSound()
{
	m_pSoundImage = NULL;
}

CSound::~CSound()
{
    if (m_pSoundImage)
		delete [] m_pSoundImage;
}

/////////////////////////////////////////////////////////////////////////////
// CSound serialization

void CSound::Serialize(CArchive& ar)
{
	ASSERT(1); // Not supported
}

/////////////////////////////////////////////////////////////////////////////
// CSound commands

BOOL CSound::Load(const char* pszFileName)
{
	CString strFile;    

	if (lstrlen(pszFileName) == 0)
	{
		// Show an File Open dialog to get the name.
		CFileDialog dlg	(TRUE,    // Open
						NULL,    // No default extension
						NULL,    // No initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
						"Wave files (*.WAV)|*.WAV|All files (*.*)|*.*||");
		if (dlg.DoModal() == IDOK)
			strFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{    
		// Copy the supplied file path.
		strFile = pszFileName;                    
	}

	// Try to open the file for read access.
	CFile file;
	if (!file.Open(strFile, CFile::modeRead | CFile::shareDenyWrite))
	{
		TRACE("%s not found\n", strFile);
//		strFile += " not found!";
//		AfxMessageBox(strFile);
		return FALSE;
	}

	BOOL bResult = Load(&file);
	file.Close();
//	if (!bResult)
//		AfxMessageBox("Failed to load wave file");
	return bResult;
}

BOOL CSound::Load(CFile* fp)
{
    // Load the whole file into memory.
    // Free any existing memory.
    if (m_pSoundImage)
		delete [] m_pSoundImage;
    // Allocate a new block big enough for the entire file.
    int iLength = fp->GetLength();
    m_pSoundImage = new BYTE[iLength];
    ASSERT(m_pSoundImage);
    // Read the entire file into memory.
    int iBytes = fp->Read(m_pSoundImage, iLength);
    ASSERT(iBytes == iLength);        
    return TRUE;
}

BOOL CSound::Load(const WORD wResid)
{
	ASSERT(wResid);
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hrsrc = ::FindResource(hInst, MAKEINTRESOURCE(wResid), "WAVE");
	if (!hrsrc)
	{
		TRACE("WAVE resource not found");
		return FALSE;
	}
	HGLOBAL hg = LoadResource(hInst, hrsrc);
	if (!hg)
	{
		TRACE("Failed to load WAVE resource");
		return FALSE;
	}
	m_pSoundImage = (BYTE*)LockResource(hg);
	ASSERT(m_pSoundImage);
	return TRUE;
}

BOOL CSound::Play()
{
	if (!m_pSoundImage)
	{
		TRACE("Nothing to play");
		return FALSE;
	}
	return ::PlaySound((LPCSTR)m_pSoundImage, NULL,
					SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
}

