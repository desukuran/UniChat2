//
//	CParser: General Line Parser
//==================================================
//	(C) Programmed by Kim, Soomin, Feb 1996
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//==================================================
//
#ifndef __PARSER_H
#define __PARSER_H

//#ifndef _SDK
#include "stdafx.h"
//#endif
#include <windows.h>

///////////////////////////////////////////////////////////////////////////
// Read whole texts in the file into the memory
class CTextFileBuffer : public CObject
{
public:
	CTextFileBuffer(const int nLineBufferLen=0);
	virtual ~CTextFileBuffer();

	BOOL	Load(LPCSTR szFile);
	char*	GetString()		{ return m_pLineBuffer; }
	char*	ReadString();
	char*	GetWholeText()	{ return m_pFileBuffer; }
	void	SeekToBegin()	{ m_pCursor = m_pFileBuffer; }

protected:
	int		m_nLineBufferLen;	// Maximum String Length
	char*	m_pLineBuffer;		// Current text line
	long	m_lFileSize;
	char*	m_pFileBuffer;
	char*	m_pCursor;
};

///////////////////////////////////////////////////////////////////////////
// Line by line parser
class CParser
{
public:
	CParser(const int mchars = 1024);
	~CParser() { delete [] m_szBuf; }

	int		GetMaxBuffer() const { return m_MaxChars; }
	void	CopyBuffer(const char* line);
	char	GetLastToken()		{ return m_lastToken; }
	void	SetMessageBoxOption(BOOL bMsgOn=TRUE)	{ m_bMsgOn = bMsgOn; }
	BOOL	IsMsgOn() const	{ return m_bMsgOn; }
//#ifndef _SDK
	BOOL	ExistFile(const char* szFile);
//#endif
	char*	GetCurrent()			{ return m_raw; }
	void	SetCurrent(char* p)		{ m_raw = p; }
	char*	FindToken(const char rtok1, const char rtok2=NULL);
	char*	FindChar(const char tok);
	char*	SetLeftToken(const char lefttok);
	char*	SetLeftToken(char* lefttokstr);
	// You can assign primary token and secondary token
	char*	GetValueRightToken(char& cVal,	const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(int& iVal,	const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(WORD& wVal,	const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(long& lVal,	const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(double& fVal, const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(char* szVal,	const char rtok1, const char rtok2 = 0);
//#ifndef _SDK
	char*	GetValueRightToken(CString& strVal,	const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(CPoint& ptVal, const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(CSize& ptVal, const char rtok1, const char rtok2 = 0);
	char*	GetValueRightToken(CRect& ptVal, const char rtok1, const char rtok2 = 0);
	int		GetStruct(CPoint& ptVal);
	int		GetStruct(CSize&  sVal);
	int		GetStruct(CRect&  rcVal);
//#endif
	int		CountOccurrencesUpto(const char ch, const char upto);
	virtual BOOL IsCommentLine() const;
	BOOL	IsWhiteSpace(const char c) const { return (c == ' ' || c == '\t'); }

protected:
	void	RemoveSpaces(char** pp);
	BOOL	m_bMsgOn;	// reports error messages through MessageBoxes
	char	m_lastToken;
private:
	char*	m_raw; 		// raw points to the raw string to be parsed
	char*	m_szBuf;	// Buffer for one line
	int		m_MaxChars;	// maximum chars per line
};

#endif	// __PARSER_H

/* ### Usage ############################################################

CParser parser(256);
...

BOOL CTestDoc::OnNewDocument()
{
	...
	TRY
	{
		CStdioFile f("sample.txt", CFile::modeRead | CFile::typeText);
		char*	szVal = new char[parser.GetMaxBuffer()];
		int		iVal;
		double	fVal;
		CPoint	ptVal;
		while(f.ReadString(szBuf, parser.GetMaxBuffer()))
		{
			parser.CopyBuffer(szBuf);	// "°ÅºÏ=1,3.4,(12,345);"
			if (parser.IsCommentLine())
				continue;

			parser.GetValueRightToken(szVal, '=');
			parser.SetLeftToken('=');
			parser.GetValueRightToken(iVal, ',');
			parser.GetValueRightToken(fVal, ',');
			parser.GetValueRightToken(ptVal);
		}
		return TRUE;
		f.Close();
		delete [] szBuf;
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		delete [] szBuf;
		return FALSE;
	}
	END_CATCH
}
*/
