// EditSend.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "EditSend.h"
#include "MainFrm.h"
#include "UC2Doc.h"
#include "UC2Messages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const COLORREF crBKCOLOR = PALETTERGB(255,255,255);
/////////////////////////////////////////////////////////////////////////////
// CEditSend

CEditSend::CEditSend()
{
//	m_pEditBkBrush = new CBrush(crBKCOLOR);	// 255,255,255));
}

CEditSend::~CEditSend()
{
}

BEGIN_MESSAGE_MAP(CEditSend, CEdit)
	//{{AFX_MSG_MAP(CEditSend)
	ON_WM_CHAR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditSend message handlers

void CEditSend::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case VK_ESCAPE:
		{
		CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
		CUC2Doc* pDoc = (CUC2Doc*)pMF->GetActiveDocument();
		ASSERT_VALID(pDoc);
		if (pDoc->IsDemo())
			pDoc->SetUC2Mode(UC2MODE_OFFLINE);
		}
		break;

//	case VK_BACK:
//		break;

	case VK_RETURN:
		if (nRepCnt == 1)
		{
			// Get current string
			CString str;
			int cl	= GetCurrentLine();	// current line (where the caret is)
			int len = GetLine(cl, str.GetBuffer(255), 255);
			str.GetBufferSetLength(len);
			str.ReleaseBuffer();
			if (str.IsEmpty())
				return;

			ParseCommand(str);

			// Append new line char
			len = GetWindowTextLength();
			SetSel(len, len);		// starting position, ending position
			if (cl == GetLastLine())
				ReplaceSel(_T("\r\n"));		// insert newline
		}
		break;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEditSend::OnDestroy() 
{
	CEdit::OnDestroy();
//	delete m_pEditBkBrush;	
}

void CEditSend::ParseCommand(LPCSTR szText)
{

#ifdef _KOREAN
	static char* szMove[] =
	{
		"ﾀ・, "ﾈﾄ", "ﾁﾂ", "ｿ・
	};
	static char* szEmotion[] =
	{
		"ｿ・, "ﾈｭ", "ﾀﾎ", "ｿ・, "ｴ・, "ﾁﾝ", "ｽｺ", "ｶｧ"
	};
#else	// English
	static char* szMove[] =
	{
		"go", "back", "left", "right"
	};
	static char* szEmotion[] =
	{
		"smile", "mad", "hello", "cry", "scratch", "pick", "special", "hit"
	};
#endif

	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	CUC2Doc* pDoc = (CUC2Doc*)pMF->GetActiveDocument();
	ASSERT_VALID(pDoc);
	int len = lstrlen(szText);

	if ((len > 2) && (szText[0] == '/'))
	{
		for (int i=0; i < (sizeof(szMove)/sizeof(szMove[0])); i++)
		{
			if ((szText[1] == szMove[i][0]) && (szText[2] == szMove[i][1]))
			{
				switch (i)
				{
				case 0:
				case 1:	pDoc->SendMoveCommand(CMD_MOVEF + i);	break;
				case 2:
				case 3:	pDoc->SendCommand(CMD_TURNL + i - 2);	break;
				}
				return;
			}
		}
		for (int i=0; i < (sizeof(szEmotion)/sizeof(szEmotion[0])); i++)
		{
			if ((szText[1] == szEmotion[i][0]) && (szText[2] == szEmotion[i][1]))
			{
				pDoc->SendCommand(CMD_SMILE + i);
				return;
			}
		}
	}
	// No commands
	pDoc->SendText(szText);
}

/*
HBRUSH CEditSend::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
	case CTLCOLOR_MSGBOX:
		pDC->SetTextColor(PALETTERGB(0,0,0));	// Yellow
		pDC->SetBkColor(crBKCOLOR);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	default:
		return CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}
*/
