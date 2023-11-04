//
//	CDirectSurface: Class for IDIRECTDRAWSURFACE* interfaces
//
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __CDDRAWSURFACE_H
#define __CDDRAWSURFACE_H

#include "ddraw.h"

class CDSurface : public CObject
{
public:
	CDSurface();
	virtual ~CDSurface();
	DECLARE_DYNCREATE(CDSurface)

// Attributes
protected:
//protected:
	LPDIRECTDRAWSURFACE		m_pSurface;
	CDirectDraw*			m_pDD;			// pointer to a DirectDraw Object
	DDSURFACEDESC			m_ddsd;			// surface description
	BOOL					m_bBackBuffer;	// then you should not Release
// Operations
public:
	HRESULT Create(CDirectDraw* pDD, const BOOL bUseClipper=FALSE);
	HRESULT Create(CDirectDraw* pDD, LPCSTR szBitmap, const int dx, const int dy);
	HRESULT GetBackBuffer(CDSurface* pDS);	// if this is an attached back buffer
	LPDIRECTDRAWSURFACE		GetSurface()	{ return m_pSurface; }
	HRESULT GetDC(HDC* pdc)		{ return m_pSurface->GetDC(pdc); }
	HRESULT ReleaseDC(HDC& hdc)	{ return m_pSurface->ReleaseDC(hdc); }
	void	Release();

	HRESULT	LoadBitmap(LPCSTR szBitmap, const int dx, const int dy);
	HRESULT	ReLoadBitmap(LPCSTR szBitmap);
	HRESULT	CopyBitmap(HBITMAP hbm, const int x=0, const int y=0, const int dx=0, const int dy=0);
	DWORD	ColorMatch(COLORREF rgb);
	HRESULT	SetColorKey(COLORREF rgb);

// Encapsulation
	HRESULT SetPalette()	{ return m_pSurface->SetPalette(m_pDD->GetPalette()); }
	HRESULT BltFast(DWORD dwX, DWORD dwY, CDSurface* pSrcSurface, LPRECT lpSrcRect, DWORD dwTrans)
		{ return m_pSurface->BltFast(dwX, dwY, pSrcSurface->GetSurface(), lpSrcRect, dwTrans); }
	HRESULT Blt(LPRECT lpDestRect, CDSurface* pSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
		{ return m_pSurface->Blt(lpDestRect, pSrcSurface->GetSurface(), lpSrcRect, dwFlags, lpDDBltFx); }
	HRESULT Restore()	{ return m_pSurface->Restore(); }
};

#endif