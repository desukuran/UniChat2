//
//	CBubble:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __BUBBLE_H
#define __BUBBLE_H

class CBubbleNotifyObj;

class AFX_EXT_CLASS CBubble : public CObject
{
	DECLARE_SERIAL(CBubble)
public:
	CBubble();
	~CBubble();

// Attributes
	int		GetZ() const				{ return m_z; }	// Get z-order.
	int		GetWidth() const			{ return m_rcBB.Width(); }
	int		GetHeight() const			{ return m_rcBB.Height(); }
	void	GetRect(CRect& rect) const	{ rect = m_rcBBT; }
	UINT	GetTextAlign() const		{ return m_TA; }
	DWORD	GetAlarmTick() const		{ return m_dwAlarmTick; }

// Operations
	void	Show(const BOOL bShow);
	BOOL	IsShown() const		{ return m_bShow; }
	void	SetKind(const int n);
	void	Serialize(CArchive& ar);
	void	Render(const HBITMAP hbm, CPalette* pPal, const CRect* pClipRect = NULL);
	BOOL	HitTest(const CPoint& point) const;
	void	SetZ(const int z);
	void	SetTextAlign(const UINT ta)	{ m_TA = ta; }
	void	TextOut(const int lr, const int bottom, const CString& str);
	void	MovePosition(const int lr, const int bottom);
	void	SetNotificationObject(CBubbleNotifyObj* pNO)	{ m_pNotifyObj = pNO; }
	void	SetAlarmTick(const DWORD dwAlarm);

protected:
	void	SetRectangles();

	int			m_z;		// Z-order for this bubble
	CRect		m_rcBB;		// rectangle surrounds this bubble
	CRect		m_rcBBT;	// rectangle including bubble's tail
	CRect		m_rcDT;		// used for DrawText
	CString		m_strText;
	CBubbleNotifyObj* m_pNotifyObj;	// Pointer to a notification object

private:
	CPoint		m_RREllipse;	// width, height of the ellipse for the CDC::RoundRect
	int			m_maxWidth;		// maximum width for this bubble (only width matters)
	COLORREF	m_textcolor;
	CFont		m_font;
	CBrush		m_brush;
	UINT		m_TA;			// SetTextAlign
	BOOL		m_bShow;
	DWORD		m_dwAlarmTick;	// Alarm for bubble erasing
};
#endif __BUBBLE_H
