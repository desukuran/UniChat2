//
//	CPhasedSprite:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __PHSPRITE_H
#define __PHSPRITE_H

// index counts from 0
// i = r * Nc + c
// r = i / Nc
// c = i % Nc

#include "Sprite.h"

class CDIB;

class AFX_EXT_CLASS CPhasedSprite : public CSprite
{
	DECLARE_SERIAL(CPhasedSprite)
public:
	CPhasedSprite();
	virtual ~CPhasedSprite();

	CPhasedSprite& operator=(const CPhasedSprite& rhs);
	BOOL operator==(const CPhasedSprite& rhs);

	enum HYPERLINK_TYPE
	{
		HLINK_EMPTY,
		HLINK_U2_ENTRY,
		HLINK_U2_EXIT,
		HLINK_HTTP
	};
// Attributes
	int		GetNumCells() const		{ return m_iNumCellRows*m_iNumCellColumns; }
	int		GetNumCellRows() const		{ return m_iNumCellRows; }
	int		GetNumCellColumns() const	{ return m_iNumCellColumns; }
	int		GetCellRow() const			{ return m_iCellRow; }
	int		GetCellColumn() const		{ return m_iCellColumn; }
	int		GetCellID() const
			{ return (m_iCellRow*m_iNumCellColumns + m_iCellColumn); }
	// from base classes
	virtual int GetHeight() const	{ return m_iCellHeight; }
	virtual int GetWidth() const	{ return m_iCellWidth; }
	BOOL		HasHyperlink() const { return (!m_strHLink.IsEmpty()); }
	int			GetLinkType() const;
	CString*	GetHyperlink()		{ return &m_strHLink; }
//	BOOL		ParseHyperlink(CString& strHL, const int n);

// Operations
	virtual void Serialize(CArchive& ar);

	BOOL	SetNumCells(const int iNumRows, const int iNumColumns);
	BOOL	SetNumCells(const CSize s)	{ return SetNumCells(s.cy, s.cx); }
	BOOL	SetNumCellRows(const int iNumRows);
	BOOL	SetNumCellColumns(const int iNumColumns);
	BOOL	SetCell(const int nID)
			{ return SetCell(nID / m_iNumCellColumns, nID % m_iNumCellColumns); }
	BOOL	SetCell(const int iRow, const int iColumn);
	BOOL	SetCell(const CPoint pt)	{ return SetCell(pt.y, pt.x); }
	BOOL	SetCellRow(const int iRow);
	BOOL	SetCellColumn(const int iColumn);
	BOOL	SetNextCell();
	virtual void	Draw(CDC* pDC, const CPoint& point);

	// from base classes
	virtual BOOL	HitTest(const CPoint& point) const;
	virtual void	Render(CDIB* pDIB, const CRect* pClipRect=NULL);
	virtual void	Initialize();
	void			SetHyperlink(const CString& strHL)	{ m_strHLink = strHL; }

// for Animation
	DWORD			GetAlarmTick() const	{ return m_dwAlarmTick; }
	int				GetMSPT() const			{ return m_nMSPT; }
	void			SetMSPT(const int nMSPT)
					{ m_nMSPT = nMSPT;	SetAlarmTick(); }
	void			SetAlarmTick(const DWORD dwAlarm=0L);
	virtual BOOL	HeartBeat(const DWORD dwCurTick);	// ticker

protected:
	int m_iNumCellRows;		// Number of rows in the image grid
	int m_iNumCellColumns;	// Number of columns in the image grid
	int m_iCellRow;			// Current cell row
	int m_iCellColumn;		// Current cell column
	int m_iCellHeight;		// Height of a row
	int m_iCellWidth;		// Width of a column
// for Animation
	int		m_ai;			// current animation index
	int		m_nMSPT;		// Milliseconds per Tick
	DWORD	m_dwAlarmTick;	// to set alarm tick to be entered next
	CString	m_strHLink;		// Hyperlink "http://www.unichat.com/|http://..."
};
#endif // __PHSPRITE_H
