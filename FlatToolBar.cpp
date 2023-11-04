//***************************************************************
// FlatToolBar.cpp
// (c) 1997, Roger Onslow
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "FlatToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CFlatToolBar, CToolBar)
//{{AFX_MSG_MAP(CFlatToolBar)
ON_WM_WINDOWPOSCHANGING()
ON_WM_PAINT()
ON_WM_NCPAINT()
ON_WM_NCCALCSIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CFlatToolBar,CToolBar)


void CFlatToolBar::SetFlatLookStyle()
{
	// Set flat style (transparent)
	ModifyStyle(0,TBSTYLE_FLAT);
	// others are...
	// #define TBSTYLE_TOOLTIPS        0x0100
	// #define TBSTYLE_WRAPABLE        0x0200
	// #define TBSTYLE_ALTDRAG         0x0400
	// #define TBSTYLE_FLAT            0x0800
	// #define TBSTYLE_LIST            0x1000
}

void CFlatToolBar::RepaintBackground() 
{
	CRect rc;
	GetWindowRect(&rc); // get rect for toolbar
	CWnd* pParent = GetParent();  // get parent windows
	pParent->ScreenToClient(&rc); // convert to parent coords
	pParent->InvalidateRect(&rc); // paint rectangle underneath
}

void CFlatToolBar::DrawSeparators() 
{
	CClientDC dc(this);		// get a dc for the client area
	DrawSeparators(&dc);    // draw the separators on it
}

void CFlatToolBar::DrawSeparators(CClientDC* pDC) 
{
	// horizontal vs vertical
	bool ishorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	// get number of buttons
	int nIndexMax = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	int nIndex;
	// try each button
	for (nIndex = 0; nIndex < nIndexMax; nIndex++) 
	{
		UINT dwStyle = GetButtonStyle(nIndex);
		UINT wStyle = LOWORD(dwStyle);
		// if it is a separator
		if (wStyle == TBBS_SEPARATOR) 
		{
			// get it's rectangle and width
			CRect rect;
			GetItemRect(nIndex,rect);
			// if small enough to be a true separator
			int w = rect.Width();
			if (w <= 8) 
			{
				if (ishorz) 
				{
					// draw the separator bar in the middle
					CRect rectbar = rect;
					int x = (rectbar.left+rectbar.right)/2;
					rectbar.left = x-1; rectbar.right = x+1;
					pDC->Draw3dRect(rectbar,::GetSysColor(COLOR_3DSHADOW),
						::GetSysColor(COLOR_3DHILIGHT));
				} 
				else 
				{
					// draw the separator bar in the middle
					CRect rectbar = rect;
					rectbar.left = rectbar.left - m_sizeButton.cx;
					rectbar.right = rectbar.left + m_sizeButton.cx;
					rectbar.top = rectbar.bottom+1;
					rectbar.bottom = rectbar.top+3;
					int y = (rectbar.top+rectbar.bottom)/2;
					rectbar.top = y-1; rectbar.bottom = y+1;
					pDC->Draw3dRect(rectbar,::GetSysColor(COLOR_3DSHADOW),
						::GetSysColor(COLOR_3DHILIGHT));
				}
			}
		}
	}
}

void CFlatToolBar::DrawGripper(CWindowDC *pDC, CRect& rectWindow) 
{
	CRect gripper = rectWindow;
	gripper.DeflateRect(1,1);
	if (m_dwStyle & CBRS_FLOATING) 
	{
		// no grippers
	} 
	else if (m_dwStyle & CBRS_ORIENT_HORZ) 
	{
		// gripper at left
		gripper.right = gripper.left+3;
		pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),
			::GetSysColor(COLOR_3DSHADOW));
		gripper.OffsetRect(+4,0);
		pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),
			::GetSysColor(COLOR_3DSHADOW));
		rectWindow.left += 8;
	} 
	else 
	{
		// gripper at top
		gripper.bottom = gripper.top+3;
		pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),
			::GetSysColor(COLOR_3DSHADOW));
		gripper.OffsetRect(0,+4);
		pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),
			::GetSysColor(COLOR_3DSHADOW));
		rectWindow.top += 8;
	}
}

void CFlatToolBar::EraseNonClient() 
{
	// get window DC that is clipped to the non-client area
	CWindowDC dc(this);
	CRect rectClient;
	GetClientRect(rectClient);
	CRect rectWindow;
	GetWindowRect(rectWindow);
	ScreenToClient(rectWindow);
	rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
	dc.ExcludeClipRect(rectClient);
	
	// draw borders in non-client area
	rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
	DrawBorders(&dc, rectWindow);
	
	// erase parts not drawn
	dc.IntersectClipRect(rectWindow);
	SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);
	
	DrawGripper(&dc, rectWindow); // <-- my addition to draw gripper
}

void CFlatToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) 
{
	static CUIntArray styles;
	// save styles
	int nIndexMax = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	int nIndex;
	for (nIndex = 0; nIndex < nIndexMax; nIndex++) 
	{
		UINT dwStyle = GetButtonStyle(nIndex);
		styles.SetAtGrow(nIndex,dwStyle);
	}
	// default processing
	CToolBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
	// check for changes to style (buttons presssed/released)
	for (nIndex = 0; nIndex < nIndexMax; nIndex++) 
	{
		UINT dwStyle = GetButtonStyle(nIndex);
		if (styles[nIndex] != dwStyle) 
		{
			RepaintBackground();    // need to take care of button background
			Invalidate();            // repaint toolbar (not just this button)
			break;
		}
	}
}

void CFlatToolBar::OnWindowPosChanging(LPWINDOWPOS lpwp) 
{
	// default processing
	CToolBar::OnWindowPosChanging(lpwp);
	// repaint background if size or move
	if (!(lpwp->flags & SWP_NOMOVE) || !(lpwp->flags & SWP_NOSIZE)) 
	{   // if moved:
		RepaintBackground();
		PostMessage(WM_NCPAINT);
	}
}

void CFlatToolBar:: OnPaint() 
{
	// standard tolbar
	CToolBar::OnPaint();
	// plus separators
	DrawSeparators();
}

void CFlatToolBar:: OnNcPaint() 
{
	EraseNonClient();
}

void CFlatToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp) 
{
	CToolBar::OnNcCalcSize(bCalcValidRects,lpncsp);
	// adjust non-client area for gripper at left or top
	if (m_dwStyle & CBRS_FLOATING) 
	{
		// no grippers
	} 
	else if (m_dwStyle & CBRS_ORIENT_HORZ) 
	{
		lpncsp->rgrc[0].left += 2;
		lpncsp->rgrc[0].right += 2;
	} 
	else 
	{
		lpncsp->rgrc[0].top += 4;
		lpncsp->rgrc[0].bottom += 4;
	}
}

/*
C++ 5.0에 보시면 Developer Studio의 ToolBar가 좀 신기하게 되어있죠?
           마우스를 버튼위에 갖다 놓으면 위로 툭튀어 나오는거 말입니다.
           다음은 그 구현방법입니다.
           1. 자신의 project workspace를 연다
           2. 아래에 덧붙여진 두개의 파일을 project에 insert한다.
           3. MainFrame.h에 
             #include "FlatToolBar.h"를 추가한다.
           4. ToolBar를 CFlatToolBar 형으로 선언한다.
           5. 다음의 코드를 CMainFrame::OnCreate의 ToolBar생성 이후에 추가한다.
             m_wndToolBar.SetFlatLookStyle();
           ※단, vc++ 5.0이상이라야 한다.
*/