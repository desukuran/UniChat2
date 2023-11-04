//
//	CSprite:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __SPRITE_H
#define __SPRITE_H

class CSpriteNotifyObj;

#include "DIB.h"

enum SPRITE_TYPE
{
	SPRITE_TILE			= 0x0001,
	SPRITE_WALL			= 0x0002,
	SPRITE_STATIC		= 0x0004,
	SPRITE_PHASED		= 0x0008,
	SPRITE_ACTOR		= 0x0010,
	SPRITE_SRC_MASK		= 0x00FF,	// lower 1 byte
	SPRITE_ANI_REPEAT	= 0x0100,
	SPRITE_ANI_FADE		= 0x0200,
	SPRITE_ANI_RANDOM	= 0x0400,
	SPRITE_ANI_ACTOR	= 0x1000,
	SPRITE_ANI_MASK		= 0xFF00
};

class AFX_EXT_CLASS CSprite : public CObject
{
	DECLARE_SERIAL(CSprite)
public:
	CSprite();
	virtual ~CSprite();
	CSprite& operator=(CSprite& rhs);
	BOOL operator==(CSprite& rhs);

// Attributes
	CDIB*	GetDIB()	{ return m_pDIB; }
	virtual int		GetWidth() const	{ return m_pDIB->GetWidth(); }	// Image width
	virtual int		GetHeight()	const	{ return m_pDIB->GetHeight(); }	// Image height

	BOOL	IsImageFlip()	const		{ return m_wImOp & IMAGE_FLIP; }
	BOOL	IsImageVertical()	const	{ return m_wImOp & IMAGE_VERTICAL; }
	BOOL	IsSameDIB(CSprite* pS) const;
	WORD	GetImOp() const	{ return m_wImOp; }
	WORD	GetType() const	{ return m_wType; }
	WORD	GetSrcType() const	{ return (m_wType & SPRITE_SRC_MASK); }
	WORD	GetAniType() const	{ return (m_wType & SPRITE_ANI_MASK); }
	BOOL	IsResManUsed() const	{ return (!m_bDeleteDIB); }
	CString* GetName() { return (m_pDIB ? m_pDIB->GetName() : NULL); }

	int		GetX() const { return m_x; }	// Get x.
	int		GetY() const { return m_y; }	// Get y.
	int		GetZ() const { return m_z; }	// Get z-order.
	int		GetElevation() const { return m_e; }
	CPoint	GetLT() const	{ return CPoint(m_x, m_y); }
	CPoint	GetCenter() const	{ return CPoint(m_x + GetWidth()/2, m_y + GetHeight()/2); }
	virtual void	GetRect(CRect& rect) const;
	int		GetEarthPointY() const;
	CPoint	GetEarthPoint() const
			{ return CPoint(m_x + m_sEarth.cx, GetEarthPointY()); }
	CSize	GetEarth() const { return m_sEarth; }
	int		GetEarthCY() const { return m_sEarth.cy; }
//	int		GetZGroup() const { return (GetZ()/GetGroupHeight()); }

// Operations
	virtual void Serialize(CArchive& ar);
	void	SetDIB(CDIB* pDIB);
	virtual BOOL Load(CFile* const fp, const char* pszPalFileName=NULL);				// Load from file
	virtual BOOL Load(const char* pszFileName=NULL, const char* pszPalFileName=NULL);	// Load DIB from disk file
	virtual BOOL Load(const WORD wResid);				// Load DIB from resource
	void	SetNotificationObject(CSpriteNotifyObj* pNO)	{ m_pNotifyObj = pNO; }

// Bitmap
	virtual BOOL MapColorsToPalette(CPalette* pPal);
	virtual void Render(CDIB* pDIB, const CRect* pClipRect=NULL);
	virtual void SetImOp(const WORD wImOp);
	void	SetOpacity(const WORD wOpacity)
			{ SetImOp((m_wImOp & ~OPACITY_MASK) | wOpacity); }
	void	SetOrient(const WORD wOrient)	// Mirror Stage
			{ SetImOp((m_wImOp & ~ORIENT_MASK) | wOrient); }

	void	SetType(const WORD wSrcType, const WORD wAniType=0)
			{ m_wType = (wSrcType | wAniType); }
	void	SetSrcType(const WORD wSrcType)
			{ m_wType = (wSrcType | (m_wType & ~SPRITE_SRC_MASK)); }
	void	SetAniType(const WORD wAniType)
			{ m_wType = ((m_wType & ~SPRITE_ANI_MASK) | wAniType); }

// for Actors
	int		TickAll();		// CPXClientApp::OnIdle calls this function

// Coordinates
	virtual BOOL	HitTest(const CPoint& point) const;
	virtual void	SetLT(const int x, const int y);
	void	SetLT(const CPoint& point)	{ SetLT(point.x, point.y); }
	void	SetZ(const int z);
	void	Unelevate()	{ m_y += m_e; }	// Temporal use for rendering
	void	Elevate()	{ m_y -= m_e; }	// "
//	int		SetZByGroup(const int nG);
	void	SetZByEarth()	{ SetZ(-GetEarthPointY()); }
	void	SetEarth(const CSize sEarth)	{ m_sEarth = sEarth; }
	void	SetElevation(const int e)		{ m_e = e; }
	void	IncElevation(const int ie)		{ m_e += ie; }
	void	MoveBy(const int xs, const int ys)	{ SetLT(m_x + xs, m_y + ys); }
	void	MoveToEarth(CPoint& point)
			{ SetLT(point.x - m_sEarth.cx, point.y - m_sEarth.cy - m_e); }
	void	MoveToCenter(CPoint& point)
			{ SetLT(point.x - GetWidth()/2, point.y - GetHeight()/2); }

protected:
	virtual void	Initialize();
//	int		GetGroupHeight() const { return 1000; }		// > Screen.cy

	CDIB*	m_pDIB;
	BYTE	m_btTransIndex;	// Transparency index value
	WORD	m_wImOp;		// Bitmap operation options
	BOOL	m_bDeleteDIB;	// Delete DIB on exit?
	int		m_x;			// X Coordinate of top-left corner
	int		m_y;			// Y Coordinate of top-left corner
	int		m_e;			// Elevation
	int		m_z;			// Z-order for sprite
	CSize	m_sEarth;		// Center of Earth Point (offset)
	WORD	m_wType;		// Sprite Type
	CSpriteNotifyObj* m_pNotifyObj;	// Pointer to a notification object
//	CSize	m_offset;		// offset of the m_rcBase
//	CRect	m_rcBase;		// for hit-test between actors
};
#endif // __SPRITE_H