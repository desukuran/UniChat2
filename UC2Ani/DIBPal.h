//
//	CDIBPal
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __DIBPAL__
#define __DIBPAL__

#include "DIB.h"
#include <mmsystem.h>

class AFX_EXT_CLASS CDIBPal : public CPalette
{
public:
	CDIBPal();
	virtual ~CDIBPal();
	BOOL	Create(CDIB* pDIB);	// Create from a DIB
	int		GetNumColors();		// Get the number of colors in the palette.
	void	Draw(CDC* pDC, CRect& rect, const BOOL bBkgnd=FALSE, const BOOL bShowIndex=FALSE); 
	BOOL	SetSysPalColors();
	BOOL	Load(const char* pszFileName=NULL, PALETTEENTRY* pPE=NULL);
	BOOL	Load(CFile* const fp, PALETTEENTRY* pPE=NULL);
	BOOL	Load(const UINT hFile, PALETTEENTRY* pPE=NULL);
	BOOL	Load(const HMMIO hmmio, PALETTEENTRY* pPE=NULL);
	BOOL	Save(CFile* const fp);  
	BOOL	Save(const UINT hFile);
	BOOL	Save(const HMMIO hmmio);
	int		GetEntries(PALETTEENTRY* pPE);
};

#endif // __DIBPAL__

