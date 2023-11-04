//
//	CSprite :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "DIB.h"
#include "SpriteNo.h"
#include "Sprite.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSprite

IMPLEMENT_SERIAL(CSprite, CObject, 0 /* Schema number */ )

CSprite::CSprite()
{
	m_pDIB			= NULL;
	m_bDeleteDIB	= TRUE;
	m_wImOp			= DEFAULT_IO;
	m_x = m_y = m_z = m_e = 0;
	m_sEarth		= CSize(0, 0);
	m_wType			= SPRITE_STATIC;
	m_btTransIndex	= 0;
	m_pNotifyObj	= NULL;
}

CSprite::~CSprite()
{
	if (m_bDeleteDIB && m_pDIB)
		delete m_pDIB;
}

CSprite& CSprite::operator=(CSprite& rhs)
{
	if (this == &rhs)
		return *this;
	SetZ(rhs.GetZ());
	if (rhs.IsResManUsed())
		SetDIB(rhs.GetDIB());
	else
	{
		ASSERT(rhs.GetDIB());
		if (m_pDIB)
			delete m_pDIB;
		m_pDIB = new CDIB;
		*m_pDIB = *rhs.GetDIB();
		Initialize();
	}
	SetLT(rhs.GetLT());
	SetImOp(rhs.GetImOp());
	SetElevation(rhs.GetElevation());
	SetType(rhs.GetType());
	m_pNotifyObj	= rhs.m_pNotifyObj;
	return *this;
}

BOOL CSprite::operator==(CSprite& rhs)
{
	return	((GetZ() ==				rhs.GetZ()) &&
			(GetDIB() ==			rhs.GetDIB()) &&
			(IsResManUsed() ==		rhs.IsResManUsed()) &&
			(GetLT() ==				rhs.GetLT()) &&
			(GetImOp() ==			rhs.GetImOp()) &&
			(GetElevation() ==		rhs.GetElevation()));
}

// Set the initial state of the sprite from its DIB image.
void CSprite::Initialize()
{
	// Get the address of the top-left pixel.
	BYTE* p = (BYTE*)GetDIB()->GetPixelAddress(0, 0);
	ASSERT(p);
	// Get the pixel value and save it.
	m_btTransIndex = *p;
}

void CSprite::SetDIB(CDIB* pDIB)
{
	m_pDIB = pDIB;
	m_bDeleteDIB = FALSE;
	Initialize();
}

// Set a new left-top x, y position.
// This will move m_rcBase by the displacements
// Notify to update the old and new rectangle area
void CSprite::SetLT(const int x, const int y)
{
	if (x == m_x && y == m_y)
		return;
	// Save the current position.
	CRect rcOld;
	GetRect(rcOld);
	// Move to new position.
	m_x = x;
	m_y = y;
	CRect rcNew;
	GetRect(rcNew);
	// Notify that we have moved from our old position to our new position.
	if (m_pNotifyObj)	// for sprites inserted into CSpriteList
		m_pNotifyObj->Change(this, CSpriteNotifyObj::POSITION, &rcOld, &rcNew);
}

/////////////////////////////////////////////////////////////////////////////
// CSprite serialization

void CSprite::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (DWORD)m_x;
		ar << (DWORD)m_y;
		ar << (DWORD)m_z;
	}
	else
	{
		DWORD dw;
		ar >> dw; m_x = (int)dw;
		ar >> dw; m_y = (int)dw;
		ar >> dw; m_z = (int)dw;
		// Now generate the other parameters from the DIB.
		Initialize();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSprite commands

// Render a sprite to a DIB.
void CSprite::Render(CDIB* pDIB, const CRect* pClipRect)
{
	ASSERT(pDIB);
	// Get the sprite rectangle.
	CRect rcThis;	// This sprite's region
	GetRect(rcThis);
	CRect rcDraw;
	// See if the sprite is visible inside the rectangle.
	if (pClipRect)
	{
		if (!rcDraw.IntersectRect(pClipRect, &rcThis))
			return; // not visible
	}
	else
	// For images with opacity,
	// set drawing area to contain the whole sprite rectangle.
	// So, withdraw pClipRect. pClipRect is just for hit test.
	// This is to prevent "different initial position problem" Feb 21 '98
//	if (!pClipRect || (m_wImOp & OPACITY_MASK))
	{
		CRect rcOSB;
		pDIB->GetRect(rcOSB);
		rcDraw.IntersectRect(&rcOSB, &rcThis);
	}

	// Copy the image of the sprite.
	GetDIB()->CopyBits(pDIB,			// Dest DIB
		rcDraw.left, rcDraw.top,		// Dest x, y
		rcDraw.right - rcDraw.left,		// Width
		rcDraw.bottom - rcDraw.top,		// Height
		rcDraw.left - m_x,				// Source x
		rcDraw.top - m_y,				// Source y
		PALETTEINDEX(m_btTransIndex),
		m_wImOp);		// Transparent color index, Image Operation
}

// Load a sprite image from a disk file.
BOOL CSprite::Load(const char* pszFileName, const char* pszPalFileName)
{
	if (!m_pDIB)
		m_pDIB = new CDIB;
	if (!GetDIB()->Load(pszFileName, pszPalFileName))
	{
		delete m_pDIB;
		m_pDIB = NULL;
		return FALSE;
	}
	// Make sure this is an 8 bpp DIB
	if (GetDIB()->GetBitCount() != 8)
	{
		AfxMessageBox("Only 8 bpp DIBs are supported");
		delete m_pDIB;
		m_pDIB = NULL;
		return FALSE;
	}

	Initialize();
	return TRUE;
}

// Load a sprite image from a disk file.
BOOL CSprite::Load(CFile* const fp, const char* pszPalFileName)
{
	if (!m_pDIB)
		m_pDIB = new CDIB;
	if (!GetDIB()->Load(fp, pszPalFileName))
	{
		delete m_pDIB;
		m_pDIB = NULL;
		return FALSE;
	}
	Initialize();
	return TRUE;
}

// Load a sprite image from a resource.
BOOL CSprite::Load(const WORD wResid)
{
	if (!m_pDIB)
		m_pDIB = new CDIB;
	if (!GetDIB()->Load(wResid))
	{
		delete m_pDIB;
		m_pDIB = NULL;
		return FALSE;
	}
	Initialize();
	return TRUE;
}

// Map colors to palette.
BOOL CSprite::MapColorsToPalette(CPalette* pPal)
{
	BOOL bResult = GetDIB()->MapColorsToPalette(pPal);
	// Get the transparency info again.
	// Note: Local call only; don't call any derived class.
	CSprite::Initialize();
	return bResult;
}

// Get the bounding rectangle.
void CSprite::GetRect(CRect& rect) const
{
	rect.left	= m_x;
	rect.top	= m_y;
	rect.right	= m_x + GetWidth();
	rect.bottom	= m_y + GetHeight();
}

// Test for a hit in a non-transparent area
BOOL CSprite::HitTest(const CPoint& point) const
{
	// Test if the point is inside the sprite rectangle
	if ((point.x > m_x) && (point.x < m_x + GetWidth())
	 && (point.y > m_y) && (point.y < m_y + GetHeight()))
	{
		// See if this point is transparent by testing whether the pixel value
		// is the same as the top left corner value.
		// Note that top left of the image is bottom left in the DIB.
		BYTE* p = (BYTE*)m_pDIB->GetPixelAddress(point.x - m_x, point.y - m_y);
		if (*p != m_btTransIndex)
			return TRUE; // hit
	}
	return FALSE;
}

// Set a new Z-order.
void CSprite::SetZ(const int z)
{
	if (m_z != z)
	{
		m_z = z;
		// See if we have to notify anyone.
		if (m_pNotifyObj)
		{
			CRect rc;
			GetRect(rc);
			m_pNotifyObj->Change(this, CSpriteNotifyObj::ZORDER, &rc);
		}
	}
}

/*
int CSprite::SetZByGroup(const int nG)
{
	int nZO = -nG*GetGroupHeight() - GetEarthPointY();
//	TRACE("Z Order=%d\n", nZO);
	SetZ(nZO);
	return nZO;
}
*/
// virtual
void CSprite::SetImOp(const WORD wImOp)
{
	if (m_wImOp != wImOp)
	{
		m_wImOp = wImOp;
		// See if we have to notify anyone.
		if (m_pNotifyObj)
		{
			CRect rc;
			GetRect(rc);
			m_pNotifyObj->Change(this, CSpriteNotifyObj::IMAGE, &rc);
		}
	}
}

BOOL CSprite::IsSameDIB(CSprite* pS) const
{
	if (!m_pDIB || !pS)
		return FALSE;
	if (IsResManUsed())
		return (m_pDIB->GetName() == pS->GetDIB()->GetName());
	CString* pS1 = m_pDIB->GetName();
	CString* pS2 = pS->GetDIB()->GetName();
	return (*pS1 == *pS2);	// Compare the string value
}

// The y pixel coord. of the ground (earth)
int CSprite::GetEarthPointY() const
{
	if (GetSrcType() == SPRITE_TILE)
	{
		if (m_e > 0)	// For an elevated tile, look it as a normal sprite
			return (m_y + GetHeight()/2 - 1 + m_e);
		// for a tile with elev<=0, give it somewhat high priority in rendering
		return (m_y - GetHeight()*4 + m_e);
	}
	return (m_y + m_sEarth.cy + m_e);
}