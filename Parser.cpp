// Parser.cpp
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

//#ifndef _SDK
#include "stdafx.h"
//#endif
#include "Parser.h"
#include <lzexpand.h>

const int MAX_EXPANDED_FILESIZE = 120*1024;

CTextFileBuffer::CTextFileBuffer(const int nLineBufferLen)
{
	m_nLineBufferLen	= nLineBufferLen;	// Maximum String Length
	m_pLineBuffer		= m_nLineBufferLen ? new char[m_nLineBufferLen] : NULL;
	m_lFileSize			= 0L;
	m_pFileBuffer		= NULL;
	m_pCursor			= NULL;
}

CTextFileBuffer::~CTextFileBuffer()
{
	if (m_pLineBuffer)
		delete [] m_pLineBuffer;
	if (m_pFileBuffer)
		delete [] m_pFileBuffer;
}

BOOL CTextFileBuffer::Load(LPCSTR szFile)
{
	TRY
	{
		CFile f;
		if (!f.Open(szFile, CFile::modeRead | CFile::shareDenyWrite))	// | CFile::typeText))
		{
			CString strMsg;
			strMsg.Format("File Open Failure: %s", szFile);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		WORD	wFileType;
		int iBytes = f.Read(&wFileType, sizeof(wFileType));
		if (iBytes != sizeof(wFileType))
		{
			CString strMsg;
			strMsg.Format("File read failure! %s: %d bytes read", szFile, iBytes);
			AfxMessageBox(strMsg);
			return FALSE;
		}

		m_lFileSize = f.GetLength();	// points to the end of file
		TRACE("FileSize=%ld bytes\n", m_lFileSize);

		BOOL bLZ = (wFileType == 0x5a53);	// 'SZ'	LZ Compressed
		UINT hLZFile;
		if (bLZ)
		{
			f.Close();
			OFSTRUCT ofStructSrc;
			hLZFile = ::LZOpenFile((char*)szFile, &ofStructSrc, OF_READ);
		}
		if (bLZ)
			::LZSeek(hLZFile, 0, 0);  // seek to beginning of file
		else
			f.Seek(0, CFile::begin);
		if (bLZ)
		{
			// Set max. buffer 120KB since it is a text file...
			m_lFileSize = MAX_EXPANDED_FILESIZE;
			m_pFileBuffer = new char[m_lFileSize];
			iBytes = ::LZRead(hLZFile, m_pFileBuffer, m_lFileSize);
			ASSERT(iBytes < m_lFileSize);
			m_lFileSize = iBytes;
		}
		else
		{
			m_pFileBuffer = new char[m_lFileSize+1];
			iBytes = f.Read(m_pFileBuffer, m_lFileSize);
			if (iBytes != (int)m_lFileSize)
			{
				CString strMsg;
				strMsg.Format("File read failure! %s: %d bytes read", szFile, iBytes);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
		m_pFileBuffer[m_lFileSize] = NULL;
		if (bLZ)
		{
			::LZClose(hLZFile);		// Commenting out this line prevented error in NT system.
		}
		else
		{
			f.Close();
		}
		SeekToBegin();	// m_pCursor = m_pFileBuffer;
		return TRUE;	// Omitting this line was the bug! only for Release version.
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		CString strMsg;
		strMsg.Format("File read failure! %s", szFile);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	END_CATCH
}

char* CTextFileBuffer::ReadString()
{
	if (!m_pLineBuffer)
		return NULL;
	char* pNL = strstr(m_pCursor, "\r\n");
	if (!pNL)
		return NULL;
	int nSize = pNL - m_pCursor + 1;
	if (nSize > m_nLineBufferLen)
		nSize = m_nLineBufferLen;
	::CopyMemory(m_pLineBuffer, m_pCursor, nSize);
	m_pLineBuffer[nSize-1] = NULL;
	m_pCursor += (nSize + 1);
	return m_pLineBuffer;
}

//////////////////////////////////////////////////////////////////////////////////
CParser::CParser(const int mchars)
{
	m_bMsgOn	= TRUE;
	m_raw		= 0;
	m_MaxChars	= mchars;
	m_szBuf		= new char[mchars];
}

//#ifndef _SDK
// returns TRUE if the file exists
BOOL CParser::ExistFile(const char* szFile)
{
	CFileStatus	status;
	BOOL bFound = CFile::GetStatus(szFile, status);
	if (!bFound)
	{
		TRACE1("File(%s) not found!\n", szFile);
		if (m_bMsgOn)
		{
			CString	msg;
			msg.Format("File(%s) not found!", szFile);
			AfxMessageBox(msg);
		}
	}
	return bFound;
}
//#endif	// _SDK

// Initialization function to be called first
void CParser::CopyBuffer(const char* line)
{
	char* p = (char*)line;
	while (IsWhiteSpace(*p))	// remove heading spaces
		p++;
	m_raw = m_szBuf;		// set m_raw string to be parsed
	int len = lstrlen(p);
	if (len > m_MaxChars)
	{
		len = m_MaxChars;
		::CopyMemory(m_szBuf, p, len);
		m_szBuf[len-1] = NULL;
	}
	else
		lstrcpy(m_szBuf, p); 
}

char* CParser::SetLeftToken(const char lefttok)
{
	char* p	= strchr(m_raw, lefttok);	// Although lefttok was not found,
										// I don't want to lose m_raw.
	if (p)
	{
		p++;						// advance pointer to the next char
		while (IsWhiteSpace(*p))	// remove heading spaces for next parsing
			p++;
		m_raw = p;			// save current position
	}
	return p;				// If lefttok was not found, return NULL
}

char* CParser::SetLeftToken(char* lefttokstr)
{
	char* p = strstr(m_raw, lefttokstr);
	if (p)
	{
		p += strlen(lefttokstr);
		while (IsWhiteSpace(*p))	// remove heading spaces
			p++;
		m_raw = p;
	}
	return p;		// If lefttok was not found, return NULL
}

char* CParser::FindToken(const char rtok1, const char rtok2)
{
	char* p = strchr(m_raw, rtok1);
	if (rtok2)
	{
		char* q = strchr(m_raw, rtok2);
		// If rtok1 not found or found all two tokens then use the left one
		// In case, ")()()..."
		if (!p || (q && p && p > q))
			p = q;
	}
	m_lastToken = p ? *p : NULL;
	return p;
}

void CParser::RemoveSpaces(char** pp)
{
	char* p = *pp;
	char* q = p;		// remove trailing spaces
	q--;
	while (IsWhiteSpace(*q))
		*q-- = NULL;
	*p++ = NULL;		// Nullify the token char and advance to the next char
	while (IsWhiteSpace(*p))	// remove heading spaces
		p++;
	*pp = p;
}

// some bytes of buf will be overwritten!
// Get value before right token: character version
char* CParser::GetValueRightToken(char& cVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)		// found the 'right' token
	{
		RemoveSpaces(&p);
		cVal = *m_raw;
		m_raw = p;			// save current position
	}
	else				// for null-terminating string...
		cVal = *m_raw;	// Although righttok not found, try to convert...
	return p;	// if righttok was not found, return NULL
}

// integer version
char* CParser::GetValueRightToken(int& iVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)		// found the 'right' token
	{
		RemoveSpaces(&p);
		iVal = atoi(m_raw);
		m_raw = p;			// save current position
	}
	else
		iVal = atoi(m_raw);	// Although righttok not found, try to convert...
	return p;	// if righttok was not found, return NULL
}


// word version
char* CParser::GetValueRightToken(WORD& wVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)		// found the 'right' token
	{
		RemoveSpaces(&p);
		wVal = (WORD)atoi(m_raw);
		m_raw = p;			// save current position
	}
	else
		wVal = (WORD)atoi(m_raw);	// Although righttok not found, try to convert...
	return p;	// if righttok was not found, return NULL
}

// long version
char* CParser::GetValueRightToken(long& lVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)
	{
		RemoveSpaces(&p);
		lVal = atol(m_raw);
		m_raw = p;
	}
	else
		lVal = atol(m_raw);	// Although righttok not found, try to convert...
	return p;
}

// double version
char* CParser::GetValueRightToken(double& fVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)
	{
		RemoveSpaces(&p);
		fVal = atof(m_raw);
		m_raw = p;
	}
	else
		fVal = atof(m_raw);	// Although righttok not found, try to convert...
	return p;
}

// char string version
// The parameter szVal should have enough spaces to get the characters from buf
//	ABCD   ,  123,
//     <-- ^p -->	remove white spaces surrounding token
//       ^q   ^m_raw
char* CParser::GetValueRightToken(char* szVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)
	{
		RemoveSpaces(&p);
		lstrcpy(szVal, m_raw);
		m_raw = p;
	}
	else
		lstrcpy(szVal, m_raw);	// Although righttok not found, try to convert...
	return p;
}

//////////////////////////////////////////////////////////////////////////////////////
// MFC Specific
//#ifndef _SDK
char* CParser::GetValueRightToken(CString& strVal, const char rtok1, const char rtok2)
{
	char* p = FindToken(rtok1, rtok2);
	if (p)
	{
		RemoveSpaces(&p);
		strVal = m_raw;		// CString will prepare space...
		m_raw = p;
	}
	else
		strVal = m_raw;	// Although righttok not found, try to convert...
	return p;
}

char* CParser::GetValueRightToken(CPoint& ptVal, const char rtok1, const char rtok2)
{
	if (GetStruct(ptVal) != 0)
		return NULL;
	char c;
	return GetValueRightToken(c, rtok1, rtok2);	// to remove rtok?
}

char* CParser::GetValueRightToken(CSize& ptVal, const char rtok1, const char rtok2)
{
	if (GetStruct(ptVal) != 0)
		return NULL;
	char c;
	return GetValueRightToken(c, rtok1, rtok2);	// to remove rtok?
}

char* CParser::GetValueRightToken(CRect& ptVal, const char rtok1, const char rtok2)
{
	if (GetStruct(ptVal) != 0)
		return NULL;
	char c;
	return GetValueRightToken(c, rtok1, rtok2);	// to remove rtok?
}

// Be sure NOT to call SetLeftToken before calling this function!
int CParser::GetStruct(CPoint& ptVal)
{
	if (!SetLeftToken('('))	return -1;
	if (!GetValueRightToken(ptVal.x, ','))	return -1;
	if (!GetValueRightToken(ptVal.y, ')'))	return -1;
	return 0;
}

int CParser::GetStruct(CSize& sVal)
{
	if (!SetLeftToken('('))	return -1;
	if (!GetValueRightToken(sVal.cx, ','))	return -1;
	if (!GetValueRightToken(sVal.cy, ')'))	return -1;
	return 0;
}

// Be sure not to call SetLeftToken before calling this function!
int CParser::GetStruct(CRect& rcVal)
{
	if (!SetLeftToken('('))	return -1;
	if (!GetValueRightToken(rcVal.left, 	','))	return -1;
	if (!GetValueRightToken(rcVal.top,		','))	return -1;
	if (!GetValueRightToken(rcVal.right,	','))	return -1;
	if (!GetValueRightToken(rcVal.bottom,	')'))	return -1;
	return 0;
}
//#endif // _SDK

// Count occurrences of a specified char in m_raw string up to 'upto' char
// Ex.) count = CountOccurrencesUpto(')', ';')
int	CParser::CountOccurrencesUpto(const char ch, const char upto)
{
	int		count = 0;
	char*	p = m_raw;

	while (*p && (*p != upto))
		if (*p++ == ch)
			count++;
	return count;
}

// Default Implementation
// comment line is a string that begins with ';' or "//"
BOOL CParser::IsCommentLine() const
{
	char* p = m_szBuf;
	while (IsWhiteSpace(*p))	// skip heading spaces
		p++;
	return(*p == 0 || *p == ';' ||(*p == '/' && *(p+1) == '/'));
}
