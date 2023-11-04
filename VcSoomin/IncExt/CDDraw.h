//
//	CDirectDraw: Class for IDIRECTDRAW* interfaces
//
//	(C) Programmed by Kim, Soomin, July 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __CDIRECTDRAW_H
#define __CDIRECTDRAW_H

#include "ddraw.h"

class CDirectDraw : public CObject
{
public:
	CDirectDraw();
	virtual ~CDirectDraw();
	DECLARE_DYNCREATE(CDirectDraw)

// Attributes
protected:
	LPDIRECTDRAW			m_pDDObj;		// CDirectDraw Object
	LPDIRECTDRAWCLIPPER		m_pClipper;		// Clipper
	LPDIRECTDRAWPALETTE		m_pDDPal;		// Palette

// Operations
public:
	BOOL				IsNormal() const	{ return m_nMode == 0; }
	HRESULT				CreateNormal(const CWnd* pWnd);
	HRESULT				CreateFS(const CWnd* pWnd, const int width, const int height, const int depth);
	LPDIRECTDRAW		GetObject()		{ return m_pDDObj; }
	LPDIRECTDRAWCLIPPER	GetClipper()	{ return m_pClipper; }
	LPDIRECTDRAWPALETTE	GetPalette()	{ return m_pDDPal; }
	void				Release();
	HRESULT				LoadPalette(LPCSTR szBitmap);
protected:
	int		m_nMode;	// Enumerated mode 0 for Normal
	int		m_nWidth;
	int		m_nHeight;
	int		m_nDepth;
};

#endif