/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 *	Modification:	Kim, Soomin		Nov 27 wed
 *					Added JPG, GIF, TIF support using Victor library
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++
#endif  // __cplusplus

extern IDirectDrawPalette*	DDLoadPalette(IDirectDraw* pdd, LPCSTR szBitmap);
extern IDirectDrawSurface*	DDLoadBitmap(IDirectDraw* pdd, LPCSTR szBitmap, const depth=8);
extern HRESULT				DDReLoadBitmap(IDirectDrawSurface* pdds, LPCSTR szBitmap, const int depth=8);
extern HBITMAP				DDLoadImageFile(LPCSTR szBitmap, const int depth);
extern HRESULT				DDCopyBitmap(IDirectDrawSurface* pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD				DDColorMatch(IDirectDrawSurface* pdds, COLORREF rgb);
extern HRESULT				DDSetColorKey(IDirectDrawSurface* pdds, COLORREF rgb);

#ifdef __cplusplus
}
#endif  // __cplusplus
