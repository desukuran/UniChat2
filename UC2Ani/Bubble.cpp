//
//	CBubble : 
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "BubbleNo.h"
#include "Bubble.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const DWORD LONGTIMELATER = 3600000L;	// 1 hour later

/////////////////////////////////////////////////////////////////////////////
// CBubble

IMPLEMENT_SERIAL(CBubble, CObject, 0 /* Schema number */ )

CBubble::CBubble()
{
	m_bShow = FALSE;
	m_z		= 0;
	m_rcBB.SetRectEmpty();
	m_rcDT.SetRectEmpty();
	m_strText.Empty();
	m_pNotifyObj	= NULL;
	// later change by using property page
	m_RREllipse	= CPoint(12, 12);//16, 16);
	m_maxWidth	= 100;//120;
	m_TA		= TA_LEFT;
	m_textcolor	= PALETTERGB(0,0,0);
	m_brush.CreateSolidBrush(PALETTERGB(255,235,187));
//	m_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(255,255,128));
//	m_brush.CreateStockObject(NULL_BRUSH);
	m_font.CreateFont(-12, 0, 0, 0, FW_NORMAL,
				FALSE, FALSE, 0,	// bItalic, bUnderline, cStrikeOut
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH || FF_DONTCARE,
#ifdef _KOREAN
				"±º∏≤√º");// πŸ≈¡√º, ±º∏≤√º, µ∏øÚ√º
#else
				"Times New Roman");
#endif
	m_dwAlarmTick = ::GetTickCount() + LONGTIMELATER;
}

CBubble::~CBubble()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBubble serialization

void CBubble::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << (DWORD)m_z;
		ar << m_rcBB;
		ar << m_strText;
		ar << m_RREllipse;
		ar << (DWORD)m_maxWidth;
		ar << m_textcolor;
	}
	else
	{
		DWORD dw;
		ar >> dw; m_z = (int)dw;
		ar >> m_rcBB;
		ar >> m_strText;
		ar >> m_RREllipse;
		ar >> dw; m_maxWidth	= (int)dw;
		ar >> m_textcolor;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBubble commands

void CBubble::SetKind(const int n)
{
	switch (n)
	{
	case 0:	// Yellow
		if (HBRUSH(m_brush))
			m_brush.DeleteObject();
		m_brush.CreateSolidBrush(PALETTERGB(255,255,195));	//255,239,191
		break;
	case 1:	// White
		if (HBRUSH(m_brush))
			m_brush.DeleteObject();
		m_brush.CreateSolidBrush(PALETTERGB(222,231,231));
		break;
	case 2:	// Green
		if (HBRUSH(m_brush))
			m_brush.DeleteObject();
		m_brush.CreateSolidBrush(PALETTERGB(206,255,90));
		break;
	}
}

void CBubble::Render(const HBITMAP hbm, CPalette* pPal, const CRect* pClipRect)
{
	if (!m_bShow)
		return;
	if (m_strText.IsEmpty())
		return;

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);	// create a memory dc that is compatible with current screen
	CBitmap* pbmOld	= dcMem.SelectObject(CBitmap::FromHandle(hbm));
	// If a clip rectangle was supplied, see if the bubble is visible inside the rectangle.
	if (pClipRect)
	{
		CRect rcDraw;
		if (!rcDraw.IntersectRect(pClipRect, &m_rcBBT))
			return; // not visible
	}
/*
	CPalette* ppalOld = NULL;
	if (pPal)
	{
		ppalOld = dcMem.SelectPalette(pPal, FALSE);	// foreground
		dcMem.RealizePalette();
	}
*/
	CBrush* brOld = dcMem.SelectObject(&m_brush);
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(m_textcolor);

	dcMem.RoundRect(&m_rcBB, m_RREllipse);

	static POINT aP[7];
	aP[6].y = aP[0].y = m_rcBB.bottom - 1;
	aP[5].y = aP[1].y = aP[0].y + 2;
	aP[4].y = aP[2].y = aP[1].y + 2;
	aP[3].y = aP[2].y + 1;
	if (m_TA == TA_RIGHT)	// shape ))
	{
		aP[0].x = m_rcBB.right - 15;
		aP[1].x = aP[0].x - 1;
		aP[2].x = aP[1].x - 2;
		aP[3].x = aP[2].x - 1;
		aP[4].x = aP[3].x + 3;
		aP[5].x = aP[4].x + 4;
		aP[6].x = aP[5].x + 2;
	}
	else	// TA_LEFT	shape ((
	{
		aP[0].x = m_rcBB.left + 15;
		aP[1].x = aP[0].x + 1;
		aP[2].x = aP[1].x + 2;
		aP[3].x = aP[2].x + 1;
		aP[4].x = aP[3].x - 3;
		aP[5].x = aP[4].x - 4;
		aP[6].x = aP[5].x - 2;
	}
	CPen* penOld = (CPen*)dcMem.SelectStockObject(NULL_PEN);
	dcMem.Polygon(aP, sizeof(aP)/sizeof(aP[0]));	// draw Polygon (2D) without border
	dcMem.SelectObject(penOld);
	dcMem.Polyline(aP, sizeof(aP)/sizeof(aP[0]));	// draw border with default pen

	CFont* pOldFont = dcMem.SelectObject(&m_font);
	dcMem.DrawText(m_strText, -1, &m_rcDT, DT_LEFT | DT_WORDBREAK);
	dcMem.SelectObject(pOldFont);
//	if (ppalOld)
//		dcMem.SelectPalette(ppalOld, FALSE);
//	GdiFlush();
	dcMem.SelectObject(brOld);
	dcMem.SelectObject(pbmOld);
}

void CBubble::Show(const BOOL bShow)
{
	m_bShow = bShow ? TRUE : FALSE;
	if (m_pNotifyObj)
		m_pNotifyObj->Change(this, CBubbleNotifyObj::IMAGE, &m_rcBBT);
}

// Test for a hit in a non-transparent area
BOOL CBubble::HitTest(const CPoint& point) const
{
	// Test if the point is inside the sprite rectangle
	if (m_rcBB.PtInRect(point))
		return TRUE; // hit
	return FALSE;
}

// Set a new Z-order.
void CBubble::SetZ(const int z)
{
	if (m_z == z)
		return;
	m_z = z;
	// See if we have to notify anyone.
	if (m_pNotifyObj)
		m_pNotifyObj->Change(this, CBubbleNotifyObj::ZORDER, &m_rcBBT);
}

// call this function before SetLT, lr=left or right according to ta
void CBubble::TextOut(const int lr, const int bottom, const CString& str)
{
	// Save the current position.
	CRect rcOld = m_rcBBT;
	m_strText = str;	// Although str is a NULL, that means she said nothing...
	// Move to new position.
	m_rcDT.bottom	= bottom;
	m_rcDT.top		= m_rcDT.bottom;
	if (m_TA == TA_LEFT)
	{
		m_rcDT.left		= lr;
		m_rcDT.right	= m_rcDT.left + m_maxWidth;	// specify maximum width
	}
	else
	{
		m_rcDT.right	= lr;
		m_rcDT.left		= m_rcDT.right - m_maxWidth;
	}
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);	// create a memory dc that is compatible with current screen
	CFont* pOldFont = dcMem.SelectObject(&m_font);
	dcMem.DrawText(m_strText, -1, &m_rcDT, DT_CALCRECT | DT_WORDBREAK);	// only left-aligns m_rcDT
	dcMem.SelectObject(pOldFont);

	// adjust for too small bubbles
	if (m_rcDT.Width() < (m_maxWidth / 2))
	{
		if (m_TA == TA_LEFT)
			m_rcDT.right = m_rcDT.left + m_maxWidth / 2;
		else
			m_rcDT.left = m_rcDT.right - m_maxWidth / 2;
	}
	// since DrawText only left-aligns m_rcDT, we need to right-align
	if (m_TA == TA_RIGHT)
	{
		int w = m_rcDT.Width();	// save width
		m_rcDT.right = lr;
		m_rcDT.left = m_rcDT.right - w;
	}
	m_rcDT.OffsetRect(0, -m_rcDT.Height());


	SetRectangles();

	// Notify that we have moved from our old position to our new position.
	if (m_pNotifyObj)
		m_pNotifyObj->Change(this, CBubbleNotifyObj::POSITION, &rcOld, &m_rcBBT);
}

void CBubble::SetRectangles()
{
	// Adjust for bubbles outside screen area
	if (m_rcDT.left < 0)
		m_rcDT.OffsetRect(-m_rcDT.left, 0);
	if (m_rcDT.top < 0)
		m_rcDT.OffsetRect(0, -m_rcDT.top);

	m_rcBB = m_rcDT;
	m_rcBB.InflateRect(m_RREllipse.x/2, m_RREllipse.y/2);
	
	m_rcBBT = m_rcBB;
	m_rcBBT.bottom += 8;	// BUBBLE_TAIL
}

// left-bottom position
void CBubble::MovePosition(const int lr, const int bottom)
{
	CRect rcOld = m_rcBBT;
	int dx = (m_TA == TA_LEFT) ? lr - m_rcDT.left : lr - m_rcDT.right;
	int dy = bottom - m_rcDT.bottom;

	m_rcDT.OffsetRect(dx, dy);

	SetRectangles();

	// Notify that we have moved from our old position to our new position.
	if (m_pNotifyObj)
		m_pNotifyObj->Change(this, CBubbleNotifyObj::POSITION, &rcOld, &m_rcBBT);
}

void CBubble::SetAlarmTick(const DWORD dwAlarm)
{
	m_dwAlarmTick = dwAlarm ? dwAlarm : ::GetTickCount();
}

