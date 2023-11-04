//
//	CDIBPal :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "DIBPal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBPal

CDIBPal::CDIBPal()
{
}

CDIBPal::~CDIBPal()
{
}

// Create a palette from the color table in a DIB.
BOOL CDIBPal::Create(CDIB* pDIB)
{
	DWORD dwColors = pDIB->GetNumClrEntries();
	// Check the DIB has a color table.
	if (!dwColors)
	{
		TRACE("No color table");   
		return FALSE;
	}

	// Get a pointer to the RGB quads in the color table.
	RGBQUAD* pRGB = pDIB->GetClrTabAddress();

	// Allocate a log pal and fill it with the color table info.
	LOGPALETTE* pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + dwColors * sizeof(PALETTEENTRY));
	if (!pPal)
	{
		TRACE("Out of memory for logpal");
		return FALSE;
	}
	pPal->palVersion	= 0x300;			// Windows 3.0
	pPal->palNumEntries	= (WORD)dwColors;	// Table size
	for (DWORD dw=0; dw < dwColors; dw++)
	{
		pPal->palPalEntry[dw].peRed		= pRGB[dw].rgbRed;
		pPal->palPalEntry[dw].peGreen	= pRGB[dw].rgbGreen;
		pPal->palPalEntry[dw].peBlue	= pRGB[dw].rgbBlue;
		pPal->palPalEntry[dw].peFlags	= 0;
	}
	BOOL bResult = CreatePalette(pPal);
	free(pPal);
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBPal commands

int CDIBPal::GetNumColors()
{
	int iColors = 0;
	if (!GetObject(sizeof(iColors), &iColors))
	{
		TRACE("Failed to get num pal colors");
		return 0;
	}
	return iColors;
}

// bBkgnd: Force Background
void CDIBPal::Draw(CDC* pDC, CRect& rect, const BOOL bBkgnd, const BOOL bShowIndex)
{
	int iColors = GetNumColors();
	CPalette* pOldPal = pDC->SelectPalette(this, bBkgnd);
	pDC->RealizePalette();
	int i, j, top, left, bottom, right;
	for (j=0, top=0; j<16 && iColors; j++, top=bottom)
	{
		bottom = (j+1) * rect.bottom / 16 + 1;
		for (i=0, left=0; i<16 && iColors; i++, left=right)
		{
			right = (i+1) * rect.right / 16 + 1;
			CBrush br(PALETTEINDEX(j * 16 + i));
			CBrush* brold = pDC->SelectObject(&br);
			pDC->Rectangle(left-1, top-1, right, bottom);
			pDC->SelectObject(brold);
			if (bShowIndex)
			{
				CString strIdx;
				strIdx.Format("%0x", j * 16 + i);
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(PALETTERGB(128, 128, 0));	// Dark Yellow
				pDC->TextOut(left, top, strIdx);
			}
			iColors--;
		}
	}
	pDC->SelectPalette(pOldPal, FALSE);
}

BOOL CDIBPal::SetSysPalColors()
{
	BOOL bResult = FALSE;
	int i, iSysColors, iPalEntries;
	HPALETTE hpalOld;

	// Get a screen DC to work with.
	HWND hwndActive = ::GetActiveWindow();
	HDC hdcScreen = ::GetDC(hwndActive);
	ASSERT(hdcScreen);

	// Make sure we are on a palettized device.
	if (!(::GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE))
	{
		TRACE("Not a palettized device\n");
		goto abort;
	}

	// Get the number of system colors and the number of palette
	// entries. Note that on a palletized device the number of
	// colors is the number of guaranteed colors, i.e., the number
	// of reserved system colors.
	iSysColors = ::GetDeviceCaps(hdcScreen, NUMCOLORS);
	iPalEntries = ::GetDeviceCaps(hdcScreen, SIZEPALETTE);

	// If there are more than 256 colors we are wasting our time.
	if (iSysColors < 0 || iSysColors > 256) goto abort;

	// Now we force the palette manager to reset its tables so that
	// the next palette to be realized will get its colors in the order they are 
	// in the logical palette. This is done by changing the number of
	// reserved colors.
	::SetSystemPaletteUse(hdcScreen, SYSPAL_NOSTATIC);
	::SetSystemPaletteUse(hdcScreen, SYSPAL_STATIC);

	// Select our palette into the screen DC and realize it so that
	// its colors will be entered into the free slots in the physical palette.
	hpalOld = ::SelectPalette(hdcScreen, (HPALETTE)m_hObject, // Our hpal
							FALSE);
#ifdef _DEBUG
	UINT nColorsRemap;
	nColorsRemap = ::RealizePalette(hdcScreen);
	TRACE("CDIBPal::SetSysPalColors() returned %d.\n", nColorsRemap);
#else
	::RealizePalette(hdcScreen);
#endif
	// Now replace the old palette (but don't realize it)
	::SelectPalette(hdcScreen, hpalOld, FALSE);

	// The physical palette now has our colors set in place and its own
	// reserved colors at either end. We can grab the lot now.
	PALETTEENTRY pe[256];
	GetSystemPaletteEntries(hdcScreen, 0, iPalEntries, pe);

	// Set the PC_NOCOLLAPSE flag for each of our colors so that the GDI
	// won't merge them. Be careful not to set PC_NOCOLLAPSE for the 
	// system color entries so that we won't get multiple copies of these
	// colors in the palette when we realize it.
	for (i = 0; i < iSysColors/2; i++)
		pe[i].peFlags = 0;
	for (; i < iPalEntries-iSysColors/2; i++)
		pe[i].peFlags = PC_NOCOLLAPSE;
	for (; i < iPalEntries; i++)
		pe[i].peFlags = 0;

	// Resize the palette in case it was smaller.
	ResizePalette(iPalEntries);

	// Update the palette entries with what is now in the physical palette.
	SetPaletteEntries(0, iPalEntries, pe);
	bResult = TRUE;

abort:
	::ReleaseDC(hwndActive, hdcScreen);
	return bResult;
}

// Load a palette from a named file.
// To get the PALETTEENTRY only, allocate a memory for it and pass it.
BOOL CDIBPal::Load(const char* pszFileName, PALETTEENTRY* pPE)
{
	CString strFile;    

	if ((pszFileName == NULL) || (strlen(pszFileName) == 0))
	{
		// Show an File Open dialog to get the name.
		CFileDialog dlg	(TRUE,    // Open
						NULL,    // No default extension
						NULL,    // No initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
						"Palette files (*.PAL)|*.PAL|All files (*.*)|*.*||");
		if (dlg.DoModal() == IDOK)
			strFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{    
		// Copy the supplied file path.
		strFile = pszFileName;                    
	}

	// Try to open the file for read access.
	CFile file;
	if (!file.Open(strFile, CFile::modeRead | CFile::shareDenyWrite))
	{
		strFile += " not found!";
		AfxMessageBox(strFile);
		return FALSE;
	}

	BOOL bResult = Load(&file, pPE);
	file.Close();
	if (!bResult)
		AfxMessageBox("Failed to load palette file");
	return bResult;
}

// Load a palette from an open CFile object.
BOOL CDIBPal::Load(CFile* const fp, PALETTEENTRY* pPE)
{
	return Load(fp->m_hFile, pPE);
}

// Load a palette from an open file handle.
BOOL CDIBPal::Load(const UINT hFile, PALETTEENTRY* pPE)
{
	MMIOINFO info;
	memset(&info, 0, sizeof(info));
	info.adwInfo[0] = hFile;
	HMMIO hmmio = mmioOpen(NULL, &info, MMIO_READ | MMIO_ALLOCBUF);
	if (!hmmio)
	{
		TRACE("mmioOpen failed\n");
		return FALSE;
	}
	BOOL bResult = Load(hmmio, pPE);
	mmioClose(hmmio, MMIO_FHOPEN);
	return bResult;
}

// Load a palette from an open MMIO handle.
BOOL CDIBPal::Load(const HMMIO hmmio, PALETTEENTRY* pPE)
{
	// Check whether it's a RIFF PAL file.
	MMCKINFO ckFile;
	ckFile.fccType = mmioFOURCC('P','A','L',' ');
	if (mmioDescend(hmmio, &ckFile, NULL, MMIO_FINDRIFF) != 0)
	{
		TRACE("Not a RIFF or PAL file\n");
		return FALSE;
	}
	// Find the 'data' chunk.
	MMCKINFO ckChunk;
	ckChunk.ckid = mmioFOURCC('d','a','t','a');
	if (mmioDescend(hmmio, &ckChunk, &ckFile, MMIO_FINDCHUNK) != 0)
	{
		TRACE("No data chunk in file\n");
		return FALSE;
	}
	// Allocate some memory for the data chunk.
	int iSize = ckChunk.cksize;
	void* pdata = malloc(iSize);
	if (!pdata)
	{
		TRACE("No mem for data\n");
		return FALSE;
	}
	// Read the data chunk.
	if (mmioRead(hmmio, (char*)pdata, iSize) != iSize)
	{
		TRACE("Failed to read data chunk\n");
		free(pdata);
		return FALSE;
	}
	// The data chunk should be a LOGPALETTE structure
	// that we can create a palette from.
	LOGPALETTE* pLogPal = (LOGPALETTE*)pdata;
	if (pLogPal->palVersion != 0x300)
	{
		TRACE("Invalid palette version number\n");
		free(pdata);
		return FALSE;
	}
	// Get the number of entries.
	int iColors = pLogPal->palNumEntries;
	if (iColors <= 0)
	{
		TRACE("No colors in palette\n");
		free(pdata);
		return FALSE;
	}
	// If pPE is specified, do not really create the palette
	if (pPE)
	{
		if (iColors > 256)
		{
			TRACE("Colors in this palette exceeds 256: %dn\n", iColors);
			iColors = 256;
		}
		::CopyMemory(pPE, &pLogPal->palPalEntry[0], iColors*sizeof(PALETTEENTRY));
		free(pdata);
		return TRUE;
	}
	else
	{
		return CreatePalette(pLogPal);
	}
}

// Save a palette to an open CFile object.
BOOL CDIBPal::Save(CFile* const fp)
{
	return Save(fp->m_hFile);
}

// Save a palette to an open file handle.
BOOL CDIBPal::Save(const UINT hFile)
{
	MMIOINFO info;
	memset(&info, 0, sizeof(info));
	info.adwInfo[0] = hFile;
	HMMIO hmmio = mmioOpen(NULL, &info, MMIO_WRITE | MMIO_CREATE | MMIO_ALLOCBUF);
	if (!hmmio)
	{
		TRACE("mmioOpen failed\n");
		return FALSE;
	}
	BOOL bResult = Save(hmmio);
	mmioClose(hmmio, MMIO_FHOPEN);
	return bResult;
}

// Save a palette to an open MMIO handle.
BOOL CDIBPal::Save(const HMMIO hmmio)
{
	// Create a RIFF chunk for a PAL file.
	MMCKINFO ckFile;
	ckFile.cksize = 0; // Corrected later
	ckFile.fccType = mmioFOURCC('P','A','L',' ');
	if (mmioCreateChunk(hmmio, &ckFile, MMIO_CREATERIFF) != 0)
	{
		TRACE("Failed to create RIFF-PAL chunk\n");
		return FALSE;
	}
	// Create the LOGPALETTE data which will become the data chunk.
	int iColors = GetNumColors();
	ASSERT(iColors > 0);
	int iSize = sizeof(LOGPALETTE) + (iColors-1) * sizeof(PALETTEENTRY);
	LOGPALETTE* plp = (LOGPALETTE*)malloc(iSize);
	ASSERT(plp);
	plp->palVersion = 0x300;
	plp->palNumEntries = iColors;
	GetPaletteEntries(0, iColors, plp->palPalEntry);
	// create the data chunk.
	MMCKINFO ckData;
	ckData.cksize = iSize; 
	ckData.ckid = mmioFOURCC('d','a','t','a');
	if (mmioCreateChunk(hmmio, &ckData, 0) != 0)
	{
		TRACE("Failed to create data chunk\n");
		return FALSE;
	}
	// Write the data chunk.
	if (mmioWrite(hmmio, (char*)plp, iSize) != iSize)
	{
		TRACE("Failed to write data chunk\n");
		free(plp);
		return FALSE;
	}
	free(plp);
	// Ascend from the data chunk which will correct the length.
	mmioAscend(hmmio, &ckData, 0);
	// Ascend from the RIFF-PAL chunk.
	mmioAscend(hmmio, &ckFile, 0);

	return TRUE;
}
