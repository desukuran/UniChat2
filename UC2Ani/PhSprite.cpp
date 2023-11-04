//
//	CPhasedSprite
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "dib.h"
#include "spriteno.h"
#include "sprite.h"
#include "phsprite.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const DWORD LONGTIMELATER = 3600000L;

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite

IMPLEMENT_SERIAL(CPhasedSprite, CSprite, 0)

CPhasedSprite::CPhasedSprite()
{
	m_iNumCellRows	= m_iNumCellColumns	= 1;
	m_iCellRow		= m_iCellColumn		= 0;
	m_wType			= SPRITE_PHASED;
	m_ai			= 0;	// animation index
	m_dwAlarmTick	= ::GetTickCount() + LONGTIMELATER;	// Never call HeartBeat before Load
	m_nMSPT			= 0;
	m_strHLink.Empty();
}

CPhasedSprite::~CPhasedSprite()
{
}

CPhasedSprite& CPhasedSprite::operator=(const CPhasedSprite& rhs)
{
	if (this == &rhs)
		return *this;
	*(CSprite*)this = *((CSprite*)&rhs);
	m_iNumCellRows		= rhs.m_iNumCellRows;
	m_iNumCellColumns	= rhs.m_iNumCellColumns;
	m_iCellRow			= rhs.m_iCellRow;
	m_iCellColumn		= rhs.m_iCellColumn;
	m_iCellHeight		= rhs.m_iCellHeight;
	m_iCellWidth		= rhs.m_iCellWidth;
	m_ai				= rhs.m_ai;
	m_nMSPT				= rhs.m_nMSPT;
	m_dwAlarmTick		= rhs.m_dwAlarmTick;
	m_strHLink			= rhs.m_strHLink;
	return *this;
}

BOOL CPhasedSprite::operator==(const CPhasedSprite& rhs)
{
	return ((*(CSprite*)this == *((CSprite*)&rhs)) &&
			(GetCellID() == rhs.GetCellID()) &&
			(m_ai == rhs.m_ai));
}

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite serialization

void CPhasedSprite::Serialize(CArchive& ar)
{
	CSprite::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << (DWORD) m_iNumCellRows;
		ar << (DWORD) m_iNumCellColumns;
		ar << (DWORD) m_iCellRow;
		ar << (DWORD) m_iCellColumn;
	}
	else
	{
		DWORD dw;
		ar >> dw;	SetNumCellRows(dw);
		ar >> dw;	SetNumCellColumns(dw);
		ar >> dw;	SetCellRow(dw);
		ar >> dw;	SetCellColumn(dw);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite commands

// Do any initialization after file load of a new image etc.
void CPhasedSprite::Initialize()
{
	CSprite::Initialize();
	m_iNumCellRows	= m_iNumCellColumns	= 1;
	m_iCellRow		= m_iCellColumn		= 0;
	m_iCellHeight	= CSprite::GetHeight();
	m_iCellWidth	= CSprite::GetWidth();
}

// Divide the image into a given number of rows.
BOOL CPhasedSprite::SetNumCellRows(const int iRows)
{
	if (iRows < 1)
	{
		TRACE1("Invalid number of rows(%d)\n", iRows);
		return FALSE;
	}
	// Compute the height of each row.
	int iCellHeight = CSprite::GetHeight() / iRows;
	if (iCellHeight < 1)
	{
		TRACE0("Can't make them that small.\n");
		return FALSE;
	}
	// Set the new height and row count.
	m_iNumCellRows	= iRows;
	m_iCellRow		= 0;
	m_iCellHeight	= iCellHeight;
	return TRUE;
}

// Divide the image into a given number of columns.
BOOL CPhasedSprite::SetNumCellColumns(const int iColumns)
{
	if (iColumns < 1)
	{
		TRACE1("Invalid number of columns(%d)\n", iColumns);
		return FALSE;
	}
	// Compute the width of each column.
	int iCellWidth = CSprite::GetWidth() / iColumns;
	if (iCellWidth < 1)
	{
		TRACE("Can't make them that small.\n");
		return FALSE;
	}
	// Set the new width and column count.
	m_iNumCellColumns	= iColumns;
	m_iCellColumn		= 0;
	m_iCellWidth		= iCellWidth;
	return TRUE;
}

BOOL CPhasedSprite::SetNumCells(const int iRows, const int iColumns)
{
	SetNumCellRows(iRows);
	return (SetNumCellColumns(iColumns));
}

// Set the current column.
BOOL CPhasedSprite::SetCellColumn(const int iColumn)
{
	if ((iColumn >= m_iNumCellColumns) || (iColumn < 0))
	{
		TRACE1("Invalid column(%d)\n", iColumn);
		return FALSE;
	}
	if (iColumn == m_iCellColumn) return FALSE; // Nothing to do
	m_iCellColumn = iColumn;
	// Send a notification to redraw.
	if (m_pNotifyObj)
	{
		CRect rcPos;
		GetRect(rcPos);
		m_pNotifyObj->Change(this, CSpriteNotifyObj::IMAGE, &rcPos);
	}
	return TRUE;
}

// Set the current row.
BOOL CPhasedSprite::SetCellRow(const int iRow)
{
	if ((iRow >= m_iNumCellRows) || (iRow < 0))
	{
		TRACE("%x CPhasedSprite::SetCellRow - Invalid row(%d)\n", this, iRow);
		return FALSE;
	}
	if (iRow == m_iCellRow) return FALSE; // Nothing to do
	m_iCellRow = iRow;
	// Send a notification to redraw.
	if (m_pNotifyObj)
	{
		CRect rcPos;
		GetRect(rcPos);
		m_pNotifyObj->Change(this, CSpriteNotifyObj::IMAGE, &rcPos);
	}
	return TRUE;
}

BOOL CPhasedSprite::SetCell(const int iRow, const int iColumn)
{
	if (iRow == m_iCellRow && iColumn == m_iCellColumn)
		return FALSE;	// Nothing to do
	if ((iRow >= m_iNumCellRows) || (iRow < 0))
	{
		TRACE("%x CPhasedSprite::SetCell - Invalid row(%d)\n", this, iRow);
		return FALSE;
	}
	m_iCellRow = iRow;
	if ((iColumn >= m_iNumCellColumns) || (iColumn < 0))
	{
		TRACE("%x CPhasedSprite::SetCell - Invalid column(%d)\n", this, iColumn);
		return FALSE;
	}
	m_iCellColumn = iColumn;
	// Send a notification to redraw.
	if (m_pNotifyObj)
	{
		CRect rcPos;
		GetRect(rcPos);
		m_pNotifyObj->Change(this, CSpriteNotifyObj::IMAGE, &rcPos);
	}
	return TRUE;
}

BOOL CPhasedSprite::SetNextCell()
{
	int nID = GetCellID();
	nID++;
	if (nID >= GetNumCells())
		nID = 0;
	return SetCell(nID);
}


// Test for a hit in a non-transparent area.
BOOL CPhasedSprite::HitTest(const CPoint& point) const
{
	// Test if the point is inside the sprite rectangle.
	if ((point.x > m_x) && (point.x < m_x + GetWidth()) &&
		(point.y > m_y) && (point.y < m_y + GetHeight()))
	{
		// Hit is in sprite rectangle.
		// See if this point is transparent by testing if the pixel value
		// is the same as the top-left corner value.
		// Note that top-left of the image is bottom-left in the DIB.
		// Get the address of the top-left pixel of the cell, not the DIB.
		// Note that the GetPixelAddress function refers to addresses in the DIB, not the cell.
		int x = point.x - m_x + (m_iCellColumn * m_iCellWidth);
		int y = point.y - m_y + (m_iCellRow * m_iCellHeight);
		BYTE* p = (BYTE*)m_pDIB->GetPixelAddress(x, y);
		ASSERT(p);
		if (*p != m_btTransIndex)
			return TRUE;
	}
	return FALSE;
}

// Render a sprite to a DIB (usually an OSB).
void CPhasedSprite::Render(CDIB* pDIB, const CRect* pClipRect)
{
	ASSERT(pDIB);
	// Get the sprite rect and see if it's visible.
	CRect rcThis;	// This sprite's region
	GetRect(rcThis);	// CSprite::GetRect		{m_x, m_y, m_x+GetWidth(), m_y+GetHeight()}
	CRect rcDraw;
	if (pClipRect)
	{
		if (!rcDraw.IntersectRect(pClipRect, &rcThis))
			return; // Not visible
	}
	else
//	if (!pClipRect || (m_wImOp & OPACITY_MASK))
	{
		CRect rcOSB;
		pDIB->GetRect(rcOSB);
		rcDraw.IntersectRect(&rcOSB, &rcThis);
	}

//	TRACE("(%d,%d)Rendering: %s %d\n", rcDraw.Width(), rcDraw.Height(),
//					*(GetDIB()->GetName()), m_wImOp & OPACITY_MASK);

	// Modify the source x and y values for the current phase of the sprite.
	// IMAGE_VERTICAL added Feb 9 mon '98
	// I found these formula by the law of 'symmetry'!
	// What a wonderful thing the symmetry is!!!
	int ys = (m_wImOp & IMAGE_VERTICAL)
			? (m_iCellRow + 1) * m_iCellHeight - (rcDraw.bottom - m_y)
			: m_iCellRow * m_iCellHeight + rcDraw.top - m_y;
	ASSERT(ys >= 0 && ys < CSprite::GetHeight());
	int xs = (m_wImOp & IMAGE_FLIP)
			? (m_iCellColumn + 1) * m_iCellWidth - (rcDraw.right - m_x)
			: m_iCellColumn * m_iCellWidth + rcDraw.left - m_x;
	ASSERT(xs >= 0 && xs < CSprite::GetWidth());
	GetDIB()->CopyBits(pDIB,		// Destination DIB
		rcDraw.left, rcDraw.top,	// Destination x, y
		rcDraw.right - rcDraw.left,	// Width
		rcDraw.bottom - rcDraw.top,	// Height
		xs,	ys,						// Source x, y
		PALETTEINDEX(m_btTransIndex),
		m_wImOp);	// Transparent color index
}

// Added by Kim, Soomin, Dec3 tue'96, to use for frame animation as in Login Screen
// Draw the DIB to a given DC.
void CPhasedSprite::Draw(CDC* pDC, const CPoint& point)
{
	int ys = CSprite::GetHeight() - (m_iCellRow + 1) * m_iCellHeight;	// bottom-up aligned DIB
	ASSERT(ys >= 0 && ys < CSprite::GetHeight());
	int xs = m_iCellColumn * m_iCellWidth;
	ASSERT(xs >= 0 && xs < CSprite::GetWidth());
	::StretchDIBits(pDC->GetSafeHdc(),
			point.x, point.y, GetWidth(), GetHeight(),	// Destination x, y, width, height
			xs, ys, GetWidth(), GetHeight(),	// Source x, y, width, height
			GetDIB()->GetBitsAddress(),			// Pointer to bits
			GetDIB()->GetBitmapInfoAddress(),	// BITMAPINFO
			DIB_RGB_COLORS,						// Options
			SRCCOPY);							// Raster operation code (ROP)
}

/////////////////////////////////////////////////////////////////////
// Animation

void CPhasedSprite::SetAlarmTick(const DWORD dwAlarm)
{
	m_dwAlarmTick = dwAlarm ? dwAlarm : ::GetTickCount();
}

//=========================================================================
// OnIdle
// We use m_bi for animation type and m_ci for animation indices.
BOOL CPhasedSprite::HeartBeat(const DWORD dwCurTick)
{
	const static wIOSeq[] =
	{
		OPACITY_12, OPACITY_25, OPACITY_50, OPACITY_75, OPACITY_100,
		OPACITY_75, OPACITY_50, OPACITY_25, OPACITY_12, OPACITY_0
	};
	switch (GetAniType())
	{
	case SPRITE_ANI_REPEAT:
		SetNextCell();
		SetAlarmTick(dwCurTick + GetMSPT());
		break;
	case SPRITE_ANI_FADE:
		{
		WORD wIO = GetImOp();
		SetImOp((wIO & ~OPACITY_MASK) | wIOSeq[m_ai++]);
		if (m_ai >= sizeof(wIOSeq)/sizeof(wIOSeq[0]))
		{
			m_ai = 0;
			SetNextCell();
		}
		// Set Alarm time to be called for the next frame
		if (m_ai == 5)	// OPACITY_100
			SetAlarmTick(dwCurTick + GetMSPT()*20);
		else
			SetAlarmTick(dwCurTick + GetMSPT());
		break;
		}
	case SPRITE_ANI_RANDOM:
		if ((m_iCellRow == 0) && (m_iCellColumn == 0))
			SetAlarmTick(dwCurTick + GetMSPT()*(1 + rand() % 100));
		else
			SetAlarmTick(dwCurTick + GetMSPT());
		SetNextCell();
		break;
	default:	return FALSE;
	}
	return TRUE;
}

int CPhasedSprite::GetLinkType() const
{
	if (m_strHLink.GetLength() < 3)
		return HLINK_EMPTY;
	switch (m_strHLink[0])
	{
	case 'e':	if (m_strHLink[1] == ':')	return HLINK_U2_ENTRY;	// e:
	case 'x':	if (m_strHLink[1] == ':')	return HLINK_U2_EXIT;	// x:
	case 'h':
	case 'f':	return HLINK_HTTP;		// http://, ftp://
	}
	return HLINK_EMPTY;
}
/*
BOOL CPhasedSprite::ParseHyperlink(CString& strHL, const int n)
{
	int nID = n;
	strHL = m_strHLink;

	while (nID--)
	{
		int i = strHL.Find('|');
		if (i >= 0)
			strHL = strHL.Left(i);
	}
}
*/