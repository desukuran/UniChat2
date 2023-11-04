//
//	CDIB :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
#include "stdafx.h"
#include "DIB.h"
#include "DIBPal.h"

#include <lzexpand.h>

#ifdef _VICTOR
#include <vicdefs.h>	// link Vic32ms.lib
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
//#if !defined(KSM_REPORT)
//	#define KSM_REPORT
//#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIB

IMPLEMENT_SERIAL(CDIB, CObject, 0 /* Schema number */)

// Create a small DIB here so m_pBMI and m_pBits are always valid.
CDIB::CDIB()
{
	m_pBMI		= NULL;
	m_pBits		= NULL;
	m_bMyBits	= TRUE;
	m_bMapColorsDone = FALSE;
	m_strName.Empty();
	Create(16, 16);
}

CDIB::~CDIB()
{
	// Free the memory.
	if (m_pBMI)
		free(m_pBMI);
	if (m_bMyBits && m_pBits)
		free(m_pBits);
}

CDIB& CDIB::operator=(CDIB& rhs)
{
	if (this == &rhs)
		return *this;
	ASSERT(rhs.m_pBMI);
	ASSERT(rhs.m_pBits);
	BITMAPINFOHEADER* pBI = (BITMAPINFOHEADER*)rhs.m_pBMI;

	int nBMISize = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	m_pBMI = (BITMAPINFO*)malloc(nBMISize);
	::CopyMemory(m_pBMI, rhs.m_pBMI, nBMISize);

	int iBitsSize = CountBitsSize(pBI->biWidth, pBI->biHeight);
	m_pBits = (BYTE*)malloc(iBitsSize);
	::CopyMemory(m_pBits, rhs.m_pBits, iBitsSize);

	m_bMyBits			= rhs.m_bMyBits;
	m_bMapColorsDone	= rhs.m_bMapColorsDone;
	m_strName			= rhs.m_strName;
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CDIB serialization

// We don't support this yet.
void CDIB::Serialize(CArchive& ar)
{
	ar.Flush();
	CFile* fp = ar.GetFile();

	if (ar.IsStoring())
	{
		Save(fp);
	}
	else
	{
		Load(fp);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Private functions

static BOOL IsWinDIB(const BITMAPINFOHEADER *pBIH)
{
	ASSERT(pBIH);
	if (((BITMAPCOREHEADER*)pBIH)->bcSize == sizeof(BITMAPCOREHEADER))
		return FALSE;
	return TRUE;
}

static int NumDIBColorEntries(BITMAPINFO* pBmpInfo) 
{
	BITMAPINFOHEADER* pBIH;
	BITMAPCOREHEADER* pBCH;
	int iColors, iBitCount;

	ASSERT(pBmpInfo);

	pBIH = &(pBmpInfo->bmiHeader);
	pBCH = (BITMAPCOREHEADER*)pBIH;

	// Start off by assuming the color table size from the bit-per-pixel field.
	iBitCount = IsWinDIB(pBIH) ? pBIH->biBitCount : pBCH->bcBitCount;

	switch (iBitCount)
	{
	case 1:		iColors = 2;	break;
	case 4:		iColors = 16;	break;
	case 8:		iColors = 256;	break;
	default:	iColors = 0;	break;
	}

	// If this is a Windows DIB, then the color table length is determined
	// by the biClrUsed field if the value in the field is nonzero.
	if (IsWinDIB(pBIH) && (pBIH->biClrUsed != 0))
		iColors = pBIH->biClrUsed;

	// BUGFIX 18 Oct 94 NigelT
	// Make sure the value is reasonable since some products
	// will write out more then 256 colors for an 8 bpp DIB!!!
	int iMax = 0;
	switch (iBitCount)
	{
	case 1:		iMax = 2;	break;
	case 4:		iMax = 16;	break;
	case 8:		iMax = 256;	break;
	default:	iMax = 0;	break;
	}
	if (iMax)
	{
		if (iColors > iMax)
		{
			TRACE("Invalid color count\n");
			iColors = iMax;
		}
	}
	return iColors;
}

/////////////////////////////////////////////////////////////////////////////
// CDIB commands
#ifdef _DEBUG

#endif
// Create a new empty 8bpp DIB with a 256 entry color table.
BOOL CDIB::Create(const iWidth, const iHeight, LPCSTR szPalFileName)
{
	// Delete any existing stuff.
	if (m_pBMI)
		free(m_pBMI);
	if (m_bMyBits && m_pBits)
		free(m_pBits);

	// Allocate memory for the header.
	m_pBMI = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
	if (!m_pBMI)
	{
		TRACE("Out of memory for DIB header\n");
		return FALSE;
	}

	// Allocate memory for the bits (DWORD aligned).
	int iBitsSize = CountBitsSize(iWidth, iHeight);
	m_pBits = (BYTE*)malloc(iBitsSize);
	if (!m_pBits)
	{
		TRACE("Out of memory for DIB bits\n");
		free(m_pBMI);
		m_pBMI = NULL;
		return FALSE;
	}
	m_bMyBits = TRUE;

	// Fill in the header info.
	BITMAPINFOHEADER* pBI = (BITMAPINFOHEADER*)m_pBMI;
	pBI->biSize		= sizeof(BITMAPINFOHEADER);
	pBI->biWidth	= iWidth;
	pBI->biHeight	= iHeight;
	pBI->biPlanes	= 1;
	pBI->biBitCount	= 8;
	pBI->biCompression		= BI_RGB;
	pBI->biSizeImage		= 0;
	pBI->biXPelsPerMeter	= 0;
	pBI->biYPelsPerMeter	= 0;
	pBI->biClrUsed			= 0;
	pBI->biClrImportant		= 0;

	// Create an arbitrary color table (gray scale).
	if (szPalFileName)
	{
		LoadPalette(szPalFileName);
	}
	else
	{
		RGBQUAD* prgb = GetClrTabAddress();
		for (int i=0; i < 256; i++)
		{
			prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE)i;
			prgb->rgbReserved = 0;
			prgb++;
		}
	}
	// Set all the bits to a known state (black).
	::ZeroMemory(m_pBits, iBitsSize);

	return TRUE;
}

int CDIB::GetBitsSize() const
{
	if (!m_pBMI)
		return 0;
	BITMAPINFOHEADER* pBI = (BITMAPINFOHEADER*)m_pBMI;
	return (((pBI->biWidth + 3) & ~3)*pBI->biHeight);
}

void CDIB::ClearImage()
{
	if (m_pBits)
	{
		::ZeroMemory(m_pBits, GetBitsSize());
	}
}

void CDIB::ClearRect(CRect& rcClear)
{
	if (!m_pBits)
		return;
	int w = rcClear.Width();
	int h = rcClear.Height();
	// Test for silly cases.
	if (w == 0 || h == 0)
		return;
	int xd = rcClear.left;
	int yd = rcClear.top;
	BYTE* pDest = (BYTE*)GetPixelAddress(xd, yd + h - 1);
	ASSERT(pDest);

	// Get the scan line widths of each DIB.
	int iDInc = StorageWidth(); // Source increment value
	while (h--)	// Fill the lines
	{
		::ZeroMemory(pDest, w);
		pDest	+= iDInc;
	}
}

// Create a CDIB structure from existing header and bits.
// The DIB won't delete the bits and makes a copy of the header.
BOOL CDIB::Create(BITMAPINFO* pBMI, BYTE* pBits)
{
	ASSERT(pBMI);
	ASSERT(pBits);
	if (m_pBMI)
		free(m_pBMI);
	m_pBMI = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 256*sizeof(RGBQUAD));
	ASSERT(m_pBMI);
	// Note: This will probably fail for < 256 color headers.
	::CopyMemory(m_pBMI, pBMI, sizeof(BITMAPINFOHEADER) + NumDIBColorEntries(pBMI)*sizeof(RGBQUAD));

	if (m_bMyBits && m_pBits)
		free(m_pBits);
	m_pBits		= pBits;
	m_bMyBits	= FALSE; // We can't delete the bits.
	return TRUE;
}

// Load a palette from the file and replace existing one
BOOL CDIB::LoadPalette(LPCSTR szPalFileName)
{
	CDIBPal			pal;
	PALETTEENTRY	PE[256];
	BOOL bRes = pal.Load(szPalFileName, PE);
	SetPaletteEntries(0, 256, PE);
/*
	CStdioFile f("Palette.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	CString str;
	for (int i=0; i < 256; i++)
	{
		str.Format("{%d,%d,%d,%d},	// %d\n",
					PE[i].peRed, PE[i].peGreen, PE[i].peBlue, PE[i].peFlags, i);
		f.WriteString(str);
	}
	f.Close();
*/
	return bRes;
}

// Load a DIB from an open file.
// Soomin Kim made the following BMP variations
// BMZ: LZ compressed BMP file
// BM: Excluding palette section from BMP
// BMC: Compressed BM file
BOOL CDIB::Load(CFile* const fp, LPCSTR szPalFileName, const BOOL bIsLZ, const DWORD dwFileStart)
{
	BOOL bIsPM = FALSE;
	BOOL bIsBMC = FALSE;
	BITMAPINFO* pBmpInfo = NULL;
	BYTE* pBits = NULL;
	UINT hLZFile;

	// Read the file header to get the file size and to find where the bits start in the file.
	BITMAPFILEHEADER BmpFileHdr;
	int iBytes;
	if (bIsLZ)	// (BmpFileHdr.bfType == 0x5a53)	// 'SZ'
	{
		hLZFile = ::LZInit(fp->m_hFile);
	//	long lFileSize = ::LZSeek(hFile, 0L, 2);	// points to the end of file
	//	TRACE("Compressed BMP: %ld bytes.\n", lFileSize);
		::LZSeek(hLZFile, dwFileStart, 0);  // seek to beginning of file
		iBytes = ::LZRead(hLZFile, (char*)&BmpFileHdr, sizeof(BmpFileHdr));
	}
	else
	{
		fp->Seek(dwFileStart, CFile::begin);	// Rewind
		iBytes = fp->Read(&BmpFileHdr, sizeof(BmpFileHdr));
	}
	if (iBytes != sizeof(BmpFileHdr))
	{
		TRACE("Failed to read file header\n");
		goto $abort;
	}

	if (BmpFileHdr.bfType == 0x4342)	// 'BC'
	{
		bIsBMC = TRUE;	// No palette
	} 
	else if (BmpFileHdr.bfType != 0x4d42)	// 'BM'
	{
		TRACE("Not a bitmap file\n");
		goto $abort;
	}

	// Make a wild guess that the file is in Windows DIB format and read the BITMAPINFOHEADER.
	// If the file turns out to be a PM DIB file we'll convert it later.
	BITMAPINFOHEADER BmpInfoHdr;
	if (bIsLZ)
		iBytes = ::LZRead(hLZFile, (char*)&BmpInfoHdr, sizeof(BmpInfoHdr));
	else
		iBytes = fp->Read(&BmpInfoHdr, sizeof(BmpInfoHdr)); 
	if (iBytes != sizeof(BmpInfoHdr))
	{
		TRACE("Failed to read BITMAPINFOHEADER\n");
		goto $abort;
	}

	// Check that we got a real Windows DIB file.
	if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER))
	{
		if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER))
		{
			TRACE(" File is not Windows or PM DIB format\n");
			goto $abort;
		}

		// Set a flag to convert PM file to Win format later.
		bIsPM = TRUE;

		// Back up the file pointer and read the BITMAPCOREHEADER
		// and create the BITMAPINFOHEADER from it.
		if (bIsLZ)
			::LZSeek(hLZFile, dwFileStart + sizeof(BITMAPFILEHEADER), 0);
		else
			fp->Seek(dwFileStart + sizeof(BITMAPFILEHEADER), CFile::begin);
		BITMAPCOREHEADER BmpCoreHdr;
		if (bIsLZ)
			iBytes = ::LZRead(hLZFile, (char*)&BmpCoreHdr, sizeof(BmpCoreHdr));
		else
			iBytes = fp->Read(&BmpCoreHdr, sizeof(BmpCoreHdr)); 
		if (iBytes != sizeof(BmpCoreHdr))
		{
			TRACE("Failed to read BITMAPCOREHEADER\n");
			goto $abort;
		}

		BmpInfoHdr.biSize			= sizeof(BITMAPINFOHEADER);
		BmpInfoHdr.biWidth			= (int)BmpCoreHdr.bcWidth;
		BmpInfoHdr.biHeight			= (int)BmpCoreHdr.bcHeight;
		BmpInfoHdr.biPlanes			= BmpCoreHdr.bcPlanes;
		BmpInfoHdr.biBitCount		= BmpCoreHdr.bcBitCount;
		BmpInfoHdr.biCompression	= BI_RGB;
		BmpInfoHdr.biSizeImage		= 0;
		BmpInfoHdr.biXPelsPerMeter	= 0;
		BmpInfoHdr.biYPelsPerMeter	= 0;
		BmpInfoHdr.biClrUsed		= 0;
		BmpInfoHdr.biClrImportant	= 0;
	}

	// Work out how much memory we need for the BITMAPINFO structure, color table
	// and then for the bits. Allocate the memory blocks.
	// Copy the BmpInfoHdr we have so far, and then read in the color table from the file.
	int iColors;
	int iColorTableSize;
	iColors			= NumDIBColorEntries((LPBITMAPINFO)&BmpInfoHdr);
	iColorTableSize	= iColors * sizeof(RGBQUAD);
	// Always allocate enough room for 256 entries.
	int iBISize;
	int iBitsSize;
	iBISize		= sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	iBitsSize	= BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;

//	TRACE("CDIB::Load(\"%s\") size=%ld\n", m_strName, BmpFileHdr.bfSize);

	// Allocate the memory for the header.
	// ======================================
	pBmpInfo = (LPBITMAPINFO)malloc(iBISize);
	if (!pBmpInfo)
	{
		TRACE("Out of memory for DIB header\n");
		goto $abort;
	}

	// Copy the header we already have.
	::CopyMemory(pBmpInfo, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

	// Now read the color table from the file.
	if (bIsBMC)
	{
		::ZeroMemory(((LPBYTE)pBmpInfo) + sizeof(BITMAPINFOHEADER), iColorTableSize);
	}
	else
	{
		if (!bIsPM)
		{
			// Read the color table from the file.
			if (bIsLZ)
				iBytes = ::LZRead(hLZFile, (char*)(((LPBYTE)pBmpInfo) + sizeof(BITMAPINFOHEADER)), iColorTableSize);
			else
				iBytes = fp->Read(((LPBYTE)pBmpInfo) + sizeof(BITMAPINFOHEADER), iColorTableSize);
			if (iBytes != iColorTableSize)
			{
				TRACE("Failed to read color table\n");
				goto $abort;
			}
		}
		else
		{
			// Read each PM color table entry in turn and convert it to Win DIB format as we go.
			LPRGBQUAD lpRGB = (LPRGBQUAD)((LPBYTE)pBmpInfo + sizeof(BITMAPINFOHEADER));
			RGBTRIPLE rgbt;
			for (int i=0; i < iColors; i++)
			{
				if (bIsLZ)
					iBytes = ::LZRead(hLZFile, (char*)&rgbt, sizeof(RGBTRIPLE));
				else
					iBytes = fp->Read(&rgbt, sizeof(RGBTRIPLE));
				if (iBytes != sizeof(RGBTRIPLE))
				{
					TRACE("Failed to read RGBTRIPLE\n");
					goto $abort;
				}
				lpRGB->rgbBlue	= rgbt.rgbtBlue;
				lpRGB->rgbGreen	= rgbt.rgbtGreen;
				lpRGB->rgbRed	= rgbt.rgbtRed;
				lpRGB->rgbReserved = 0;
				lpRGB++;
			}
		}
	}

	// Allocate the memory for the bits and read the bits from the file.
	// ======================================
	pBits = (BYTE*)malloc(iBitsSize);
	if (!pBits)
	{
		TRACE("Out of memory for DIB bits\n");
		goto $abort;
	}

	// Seek to the bits in the file.
	if (bIsLZ)
		::LZSeek(hLZFile, dwFileStart + BmpFileHdr.bfOffBits, 0);
	else
		fp->Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

	// Read the bits.
	if (bIsLZ)
		iBytes = ::LZRead(hLZFile, (char*)pBits, iBitsSize);
	else
		iBytes = fp->Read(pBits, iBitsSize);
	if (iBytes != iBitsSize)
	{
		TRACE("Failed to read bits\n");
		goto $abort;
	}

	// Everything went OK.
	if (bIsLZ)
		::LZClose(hLZFile);
	if (m_pBMI)
		free(m_pBMI);
	m_pBMI = pBmpInfo; 
	if (m_bMyBits && m_pBits)
		free(m_pBits);
	m_pBits		= pBits;
	m_bMyBits	= TRUE;

	if (szPalFileName)	// Overload the palette entries with that of the specified file
	{
		LoadPalette(szPalFileName);
	}
	return TRUE;
                
$abort: // Something went wrong.
	if (bIsLZ)		::LZClose(hLZFile);
	if (pBmpInfo)	free(pBmpInfo);
	if (pBits)		free(pBits);
	return FALSE;
}

// Load a DIB from a disk file.
// If no file name is given, show an Open File dialog to get one.
// m_strName == "DATASRC0:filename.ext"
BOOL CDIB::Load(LPCSTR szFileName, LPCSTR szPalFileName)
{
	if ((szFileName == NULL) || (strlen(szFileName) == 0))
	{
		// Show an Open File dialog to get the name.
		CFileDialog dlg(TRUE,	// Open
						NULL,	// No default extension
						NULL,	// No initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
#ifdef _VICTOR
						"Bitmap files|*.DIB;*.BMP;*.BM;*.gif;*.jpg;*.tif|All files (*.*)|*.*||");
#else
						"Bitmap files(*.DIB;*.BM*)|*.DIB;*.BM*|All files (*.*)|*.*||");
#endif // _VICTOR
        if (dlg.DoModal() == IDOK)
			m_strName = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{
		// Copy the supplied file path.
		m_strName = szFileName;
	}

	// Parse Data Source
	// tile0000|tcity000.bm
	int iDS = m_strName.Find('|');
	if (iDS > 0)
	{
		int nLen = m_strName.GetLength();
		CString strDS(m_strName.Left(iDS));
		strDS += ".uds";
		CString strBM(m_strName.Right(nLen - (iDS + 1)));
		return LoadDataSource(strDS, strBM, szPalFileName);
	}

	BOOL bResult;
#ifdef _VICTOR
	int nFT = GetBitmapFileType(m_strName);
	if ((nFT == FILE_BMP) || (nFT == FILE_BM) ||
		(nFT == FILE_BMZ) || (nFT == FILE_BMC))
	{
#endif // _VICTOR
		// Try to open the file for read access.
		CFile file;
		if (!file.Open(m_strName, CFile::modeRead | CFile::shareDenyWrite))
		{
			TRACE1("File Open Failure: %s\n", m_strName);
			return FALSE;
		}

		WORD	wFileType;
		int iBytes = file.Read(&wFileType, sizeof(wFileType));
		if (iBytes != sizeof(wFileType))
		{
			TRACE("Failed to read file\n");
			file.Close();
			return FALSE;
		}

		BOOL bIsLZ = (wFileType == 0x5a53);	// 'SZ'

		bResult = Load(&file, szPalFileName, bIsLZ, 0L);
		file.Close();
#ifdef _VICTOR
	}
	else
	{
		imgdes orgImg;	// original image
		imgdes cnvImg;	// converted image (24bit color -> 8bit color)
		switch (nFT)
		{
		case FILE_GIF:
			LoadGIF(m_strName, &orgImg);
			break;
		case FILE_TIF:
			LoadTIF(m_strName, &orgImg);
			break;
		case FILE_JPG:
			LoadJPG(m_strName, &orgImg);
			break;
		}
		if (orgImg.bmh->biBitCount != 8)
		{
			if (CreateImage8(&orgImg, &cnvImg) != NO_ERROR)
			{
				AfxMessageBox("Image color dithering failure.");
				return FALSE;
			}
			freeimage(&orgImg);
			bResult = LoadFromImage((LPVOID)cnvImg.bmh);
			freeimage(&cnvImg);
		}
		else
		{
			bResult = LoadFromImage((LPVOID)orgImg.bmh);
			freeimage(&orgImg);
		}
	}
#endif // _VICTOR

	return bResult;
}

BOOL CDIB::LoadDataSource(LPCSTR szSrcFileName,
						LPCSTR szFileName,
						LPCSTR szPalFileName)
{
	BOOL bResult;
	// Try to open the file for read access.
	CFile file;
	if (!file.Open(szSrcFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
		TRACE1("File Open Failure: %s\n", szSrcFileName);
		return FALSE;
	}

	BOOL	bIsLZ = FALSE;
	UINT	hLZFile;
	DATASOURCEFILEHEADER dsFH;

	int iBytes = file.Read(&dsFH, sizeof(dsFH));
	if (iBytes != sizeof(dsFH))
	{
		TRACE("Failed to read file header\n");
		file.Close();
		return FALSE;
	}

	if (dsFH.wType == 0x5a53)	// 'SZ'	- test for compression
	{
		bIsLZ = TRUE;
		hLZFile = ::LZInit(file.m_hFile);
	//	long lFileSize = ::LZSeek(hFile, 0L, 2);	// points to the end of file
	//	TRACE("Compressed BMP: %ld bytes.\n", lFileSize);
		::LZRead(hLZFile, (char*)&dsFH, sizeof(dsFH));	// read again
	}
	else if (dsFH.wType != 0x5344)	// 'DS'
	{
		TRACE("Wrong filetype.\n");
		file.Close();
		return FALSE;
	}

//	TRACE("Data Source F. Size: %ld\n", dsFH.dwFileSize);
//	TRACE("Data Source Entries: %d\n", dsFH.wNumEntries);
	DATASOURCEENTRY*	aDSE = new DATASOURCEENTRY[dsFH.wNumEntries];

	if (bIsLZ)
		::LZRead(hLZFile, (char*)aDSE, sizeof(DATASOURCEENTRY) * dsFH.wNumEntries);
	else
		file.Read(aDSE, sizeof(DATASOURCEENTRY) * dsFH.wNumEntries);

	for (WORD i=0; i < dsFH.wNumEntries; i++)
	{
		if (lstrcmpi(aDSE[i].id, szFileName) == 0)	// matching!
		{
//			if (bIsLZ)
//				::LZClose(hLZFile);
			bResult = Load(&file, szPalFileName, bIsLZ, aDSE[i].dwOffset);
			delete [] aDSE;
			file.Close();
			return bResult;
		}
	}
	TRACE("CDIB: %s not found in data source %s", szFileName, szSrcFileName);
	delete [] aDSE;
	file.Close();
	return FALSE;
}

// Load a DIB from a resource id.
BOOL CDIB::Load(const WORD wResid)
{
	ASSERT(wResid);
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hrsrc = ::FindResource(hInst, MAKEINTRESOURCE(wResid), "DIB");
	if (!hrsrc)
	{
		TRACE1("DIB resource not found(HRSRC:%x)", hrsrc);
		return FALSE;
	}
	HGLOBAL hg = ::LoadResource(hInst, hrsrc);
	if (!hg)
	{
		TRACE1("Failed to load DIB resource(HGLOBAL:%x)", hg);
		return FALSE;
	}

	m_strName.Format("RES:%d", wResid);

	BYTE* pRes = (BYTE*)::LockResource(hg);
	ASSERT(pRes);
	int iSize = ::SizeofResource(hInst, hrsrc);

	// Mark the resource pages as read/write so the mmioOpen won't fail
	DWORD dwOldProt;
	BOOL b = ::VirtualProtect(pRes, iSize, PAGE_READWRITE, &dwOldProt);
	ASSERT(b);

	// Now create the CDIB object. We will create a new header from the data
	// in the resource image and copy the bits from the resource to a new block of memory.
	// We can't use the resource image as-is because we might want to map the DIB colors
	// and the resource memory is write protected in Win32.
	BITMAPFILEHEADER* pFileHdr = (BITMAPFILEHEADER*)pRes;
	ASSERT(pFileHdr->bfType == 0x4D42); // BM file
	BITMAPINFOHEADER* pInfoHdr = (BITMAPINFOHEADER*)(pRes + sizeof(BITMAPFILEHEADER));
	ASSERT(pInfoHdr->biSize == sizeof(BITMAPINFOHEADER));  // must be a Win DIB
	BYTE* pBits = pRes + pFileHdr->bfOffBits;
	BOOL bResult = Create((BITMAPINFO*)pInfoHdr, pBits);
	return bResult;
	// Note: not required to unlock or free the resource in Win32
}

// Draw the DIB to a given DC.
void CDIB::Draw(CDC* pDC, const x, const y)
{
	::StretchDIBits(pDC->GetSafeHdc(),
			x, y, DibWidth(), DibHeight(),	// Destination x, y, width, height
			0, 0, DibWidth(), DibHeight(),	// Source x, y, width, height
			GetBitsAddress(),				// Pointer to bits
			GetBitmapInfoAddress(),			// BITMAPINFO
			DIB_RGB_COLORS,					// Options
			SRCCOPY);						// Raster operation code (ROP)
}

// Draw a portion of source DIB to the destination
void CDIB::Draw(CDC* pDC, const xd, const yd, const w, int h, const xs, const ys)
{
	::StretchDIBits(pDC->GetSafeHdc(),
			xd, yd, w, h,					// Destination x, y, width, height
			xs, DibHeight()-(ys+h), w, h,	// Source x, y, width, height
			GetBitsAddress(),				// Pointer to bits
			GetBitmapInfoAddress(),			// BITMAPINFO
			DIB_RGB_COLORS,					// Options
			SRCCOPY);						// Raster operation code (ROP)
}

// Tile
void CDIB::Tile(CDC* pDC, const x0, const y0, CRect& rcClient)
{
	for (int y=y0; y <= rcClient.bottom; y += DibHeight())
		for (int x=x0; x <= rcClient.right; x += DibWidth())
			Draw(pDC, x, y);
}

// Get the number of color table entries.
int CDIB::GetNumClrEntries() const
{
	return NumDIBColorEntries(m_pBMI);
}

// map the colors in this DIB to the identity palette specified
// NOTE: This assumes all CDIB objects have 256 color table entries.
BOOL CDIB::MapColorsToPalette(const CPalette* pPal)
{
	if (m_bMapColorsDone)
		return TRUE;
	if (!pPal)
	{
		TRACE("No palette to map to\n");
		return FALSE;
	}
	ASSERT(m_pBMI);
	ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
	ASSERT(m_pBits);
	LPRGBQUAD pctThis = GetClrTabAddress();	// We can redirect the palette address
											// with SetClrTabAddress(...) function.
	ASSERT(pctThis);
	// Build an index translation table to map this DIBs colors to those of the reference DIB.
	BYTE imap[256];
#ifdef _DEBUG
	int iChanged = 0; // For debugging only
#endif
	for (int i=0; i < 256; i++)
	{ 
		imap[i] = (BYTE)pPal->GetNearestPaletteIndex(
							RGB(pctThis->rgbRed,
								pctThis->rgbGreen,
								pctThis->rgbBlue));
		pctThis++;
#ifdef _DEBUG
		if (imap[i] != i)
			iChanged++; // For debugging
	}
//	TRACE("CDIB::MapColorsToPalette changed %d colors.\n", iChanged);
#else
	}
#endif
	// Now map the DIB bits.
	BYTE* pBits = (BYTE*)GetBitsAddress();
	int iSize = StorageWidth() * DibHeight();
	while (iSize--)
	{
		*pBits = imap[*pBits];
		pBits++;
	}
	// Now reset the DIB color table so that its RGB values match those in the palette.
	PALETTEENTRY pe[256];
	pPal->GetPaletteEntries(0, 256, pe);
	pctThis = GetClrTabAddress();
	for (i=0; i < 256; i++)
	{
		pctThis->rgbRed		= pe[i].peRed;    
		pctThis->rgbGreen	= pe[i].peGreen;    
		pctThis->rgbBlue	= pe[i].peBlue;
		pctThis++;    
	}
	// Now say all the colors are in use
	m_pBMI->bmiHeader.biClrUsed = 256;
	m_bMapColorsDone = TRUE;
	return TRUE;
}

// Get a pointer to a pixel.
// NOTE: DIB scan lines are DWORD aligned.
// The scan line storage width may be wider than the scan line image width
// so calc the storage width by rounding the image width to the next highest DWORD value.
void* CDIB::GetPixelAddress(const x, const y) const
{
	// Note: This version deals only with 8 bpp DIBs.
	ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
	// Make sure it's in range and if it isn't return zero.
	if ((x >= DibWidth()) || (y >= DibHeight()))
	{
		TRACE("Attempt to get out of range pixel address\n");
		return NULL;
	}

	// Calculate the scan line storage width.
	int iWidth = StorageWidth();
	return m_pBits + (DibHeight()-y-1) * iWidth + x;
}

// Get the bounding rectangle.
void CDIB::GetRect(CRect& rect) const
{
	rect.left = rect.top = 0;
	rect.right	= DibWidth();
	rect.bottom	= DibHeight();
}

// Copy a rectangle of the DIB to another DIB.
// Note: We only support 8bpp DIBs here.
void CDIB::CopyBits(CDIB* pdibDest, const xd, const yd,
				const w, int h, const xs, const ys, const COLORREF clrTrans,
				const WORD wImOp)
{
	ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
	ASSERT(pdibDest);
	WORD opacity = wImOp & OPACITY_MASK;
	// Test for silly cases.
	if (!w || !h || (opacity == OPACITY_0))
		return;

	BOOL bMirror		= wImOp & IMAGE_FLIP;
	BOOL bVT			= wImOp & IMAGE_VERTICAL;	// Vertical Transformation

	// Get pointers to the start points in the source and destination DIBs.
	// Note that the start points will be the bottom-left corner of the DIBs
	// because the scan lines are reversed in memory.
	BYTE* pSrc = (BYTE*)GetPixelAddress(xs, ys+h-1);
	ASSERT(pSrc);
	BYTE* pDest = (BYTE*)pdibDest->GetPixelAddress(xd, (bVT) ? yd : (yd+h-1));
	ASSERT(pDest);

	// Get the scan line widths of each DIB.
	int iScanS = StorageWidth();
	int iScanD = pdibDest->StorageWidth();
	int iSInc = bMirror ? iScanS : (iScanS - w); // Source increment value
	int iDInc = bVT ? (-iScanD - w) : (iScanD - w); // Destination increment value
	int iCount;
	BYTE pixel;

	if (wImOp & NO_COLORKEY)	// && opacity == OPACITY_100)
	{
		if (bMirror)
		{
			while (h--)	// Copy the lines
			{
				iCount	= w;    // Number of pixels to scan.
				pSrc	+= w;
				while (iCount--)
				{
					pixel		= *(--pSrc);
					*pDest++	= pixel;
				}
				pSrc	+= iSInc;
				pDest	+= iDInc;
			}
		}
		else // !Mirror
		{
			while (h--)	// Copy the lines
			{
				::CopyMemory(pDest, pSrc, w);
				pSrc	+= iScanS;
				if (bVT)
					pDest	-= iScanD;
				else
					pDest	+= iScanD;
			}
		}
	}
	else // Use Colorkey
	{
		// Copy lines with transparency.
		// Note: We accept only a PALETTEINDEX description for the color definition.
		ASSERT((clrTrans & 0xFF000000) == 0x01000000);
		BYTE bTransClr = LOBYTE(LOWORD(clrTrans));

		if (opacity == OPACITY_100)
		{
			if (bMirror)
			{
				while (h--)
				{
					iCount = w;    // Number of pixels to scan.
					pSrc += w;
					while (iCount--)
					{
						pixel = *(--pSrc);		// *pSrc-- was THE BUG!!! 22:30 Oct 12 Sat '96 at ImKwang
						// Copy pixel only if it isn't transparent.
						if (pixel != bTransClr)	*pDest++ = pixel;
						else					pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}
			}
			else	// !bMirror
			{
				while (h--)
				{
					iCount = w;    // Number of pixels to scan.
					while (iCount--)
					{
						pixel = *pSrc++;
						// Copy pixel only if it isn't transparent.
						if (pixel != bTransClr)	*pDest++ = pixel;
						else					pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}
			}
		}
		else if (opacity == OPACITY_75)
		{
			int r;
			int d=4;	// 3/4

			if (bMirror)
			{
				while (h--)
				{
					iCount = w;		// Number of pixels to scan.
					r = h % d;		// 0,1,2,3,0,... => 0,2,1,3,0,...
					if (r==1)
						r = 2;
					else if (r==2)
						r = 1;
					pSrc += w;
					while (iCount--)
					{
						pixel = *(--pSrc);
						// Copy pixel only if it isn't transparent.
						if ((iCount % d != r) && (pixel != bTransClr))
							*pDest++ = pixel;
						else
							pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}
			}
			else	// !bMirror
			{
				while (h--)
				{
					iCount = w;    // Number of pixels to scan.
					r = h % d;
					if (r==1)
						r = 2;
					else if (r==2)
						r = 1;
					while (iCount--)
					{
						pixel = *pSrc++;
						// Copy pixel only if it isn't transparent.
						if ((iCount % d != r) && (pixel != bTransClr))
							*pDest++ = pixel;
						else
							pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}
			}
		}
		else //	!(OPACITY_100, OPACITY_75)
		{
			int r;
			int d;

			switch (opacity)
			{
			case OPACITY_12:	d = 4;	break;	//	1/64 paint
			case OPACITY_25:					//	1/4
			case OPACITY_50:	d = 2;	break;	//	1/2
			default:			d = 2;	break;
			}

			if (bMirror)
			{
				while (h--)
				{
					iCount = w;	// Number of pixels to scan.
					r = h % d;	// Since adjacent lines should be different
					pSrc += w;
					while (iCount--)
					{
						if ((opacity != OPACITY_50) && (r != 0))
						{
							pSrc	-= (iCount+1);
							pDest	+= (iCount+1);
							break;		// skip this scan line
						}
						pixel = *(--pSrc);
						// Copy pixel only if it isn't transparent.
						if ((iCount % d == r) && (pixel != bTransClr))
							*pDest++ = pixel;
						else
							pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}	
			}
			else	// !Mirror
			{
				while (h--)
				{
					iCount = w;    // Number of pixels to scan.
					r = h % d;
					while (iCount--)
					{
						if ((opacity != OPACITY_50) && (r != 0))
						{
							pSrc	+= (iCount+1);	// since 1 decreased in while statement
							pDest	+= (iCount+1);
							break;		// skip this scan line
						}
						pixel = *pSrc++;
						// Copy pixel only if it isn't transparent.
						if ((iCount % d == r) && (pixel != bTransClr))
							*pDest++ = pixel;
						else
							pDest++;
					}
					// Move on to the next line.
					pSrc	+= iSInc;
					pDest	+= iDInc;
				}
			}
		}
	}
#ifdef KSM_REPORT
	static int D_CopyBitsCount = 0;
	TRACE3("CDIB::CopyBits(%d,%d)=%d\n", w, h, ++D_CopyBitsCount);
#endif
}

// Save a DIB to a disk file.
// This is somewhat simplistic because we only deal with 256 color DIBs
// and we always write a 256 color table.
BOOL CDIB::Save(CFile* const fp, const BOOL bPalette)
{
	BITMAPFILEHEADER bfh;

	// Construct the file header.
	bfh.bfType = (bPalette) ? 0x4D42 : 0x4342; // 'BM' or 'BC'
	bfh.bfSize =
		sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		StorageWidth() * DibHeight();
	if (bPalette)
		bfh.bfSize += 256 * sizeof(RGBQUAD);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	if (bPalette)
		bfh.bfOffBits += 256 * sizeof(RGBQUAD);

	// Write the file header.
	int iSize = sizeof(bfh);
	TRY
	{
		fp->Write(&bfh, iSize);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write file header");
		return FALSE;
	} END_CATCH

	// Write the BITMAPINFO structure.
	// Note: we assume that there are always 256 colors in the color table.
	ASSERT(m_pBMI);
	iSize = sizeof(BITMAPINFOHEADER);
	if (bPalette)
		iSize += 256 * sizeof(RGBQUAD);
	TRY
	{
		fp->Write(m_pBMI, iSize);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write BITMAPINFO");
		return FALSE;
	} END_CATCH

	// Write the bits.
	iSize = StorageWidth() * DibHeight();
	TRY
	{
		fp->Write(m_pBits, iSize);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write bits");
		return FALSE;
	} END_CATCH

	return TRUE;
}

// Save a DIB to a disk file. If no file name is given, show a File Save dialog to get one.
BOOL CDIB::Save(LPCSTR szFileName)
{
	CString strFile;    

	if ((szFileName == NULL) || (strlen(szFileName) == 0))
	{
		// Show a File Save dialog to get the name.
		CFileDialog dlg(FALSE,   // Save
						NULL,    // No default extension
						m_strName,    // No initial file name
						OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
						"Image files (*.DIB;*.BM*)|*.DIB;*.BM*|All files (*.*)|*.*||");
		if (dlg.DoModal() == IDOK)
		{
			strFile = dlg.GetPathName();
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		// Copy the supplied file path.
		strFile = szFileName;                    
	}

	// Try to open the file for write access.
	CFile file;
	if (!file.Open(strFile,	CFile::modeReadWrite | CFile::modeCreate | CFile::shareExclusive))
	{
		AfxMessageBox("Failed to open file");
		return FALSE;
	}

	BOOL bResult = Save(&file, (GetFileType(strFile) != FILE_BM));
	file.Close();
	if (!bResult)
		AfxMessageBox("Failed to save file");
	return bResult;
}

CDIB::BITMAP_FILE_TYPE CDIB::GetFileType(LPCSTR szFile)
{
	char* p = strrchr(szFile, '.');	// .extension
	if (p)
	{
		p++;
		if (lstrcmpi(p, "BM") == 0)	// BMP, BMZ, BMC,...
		{
			switch (toupper(p[2]))
			{
			case NULL:	return FILE_BM;
			case 'Z':	return FILE_BMZ;
			case 'C':	return FILE_BMC;
			default:	return FILE_BMP;	// 'P'
			}
		}
		if (lstrcmpi(p, "GIF") == 0)
			return FILE_GIF;
		if (lstrcmpi(p, "TIF") == 0)
			return FILE_TIF;
		if (lstrcmpi(p, "JPG") == 0)
			return FILE_JPG;
	}
	char szMsg[256];
	wsprintf(szMsg, "Unrecognized bitmap file type - \"%s\"", szFile);
	AfxMessageBox(szMsg);
	return FILE_NONE;
}

#ifdef _VICTOR
/////////////////////////////////////////////////////////////////////////////////////////////
// Victor

// Load a DIB from an open file.
BOOL CDIB::LoadFromImage(LPVOID pImg)
{
	BYTE* pSrc = (BYTE*)pImg;
	// Work out how much memory we need for the BITMAPINFO structure, color table
	// and then for the bits. Allocate the memory blocks.
	// Always allocate enough room for 256 entries.
	// Allocate the memory for the header.
	BITMAPINFO* pBmpInfo = (LPBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
	if (!pBmpInfo)
	{
		TRACE("Out of memory for DIB header");
		return FALSE;
	}
	// Copy the header
	::CopyMemory(pBmpInfo, pSrc, sizeof(BITMAPINFOHEADER));
	pSrc += sizeof(BITMAPINFOHEADER);

	int iBitsSize	= pBmpInfo->bmiHeader.biSizeImage;
	// Copy the BmpInfoHdr we have so far, and then read in the color table from the file.
	int iColorTableSize	= NumDIBColorEntries(pBmpInfo) * sizeof(RGBQUAD);

	// Read the color table from the file.
	::CopyMemory(((LPBYTE)pBmpInfo) + sizeof(BITMAPINFOHEADER), pSrc, iColorTableSize);
	pSrc += iColorTableSize;

	// Allocate the memory for the bits and read the bits from the file.
	BYTE* pBits = (BYTE*)malloc(iBitsSize);
	if (!pBits)
	{
		TRACE("Out of memory for DIB bits");
		if (pBmpInfo)
			free(pBmpInfo);
		return FALSE;
	}

	// Read the bits.
	::CopyMemory(pBits, pSrc, iBitsSize);

	// Everything went OK.
	if (m_pBMI)
		free(m_pBMI);
	m_pBMI = pBmpInfo; 
	if (m_bMyBits && m_pBits)
		free(m_pBits);
	m_pBits		= pBits;
	m_bMyBits	= TRUE;
	return TRUE;
}

int CDIB::LoadGIF(LPCSTR fname, imgdes* image)
{
	// Get info on the file we're to load
	GifData gdat;
	CString str;
	int rcode = gifinfo((char*)fname, &gdat);
	if (rcode != NO_ERROR)	// Fill structure
	{
		str.Format("Error in reading %s", fname);
		AfxMessageBox(str);
		return rcode;
	}	// Allocate space for an 8-bit image
	rcode = allocimage(image, gdat.width, gdat.length, gdat.vbitcount);
	if (rcode != NO_ERROR)
	{
		str.Format("Not enough memory to load %s", fname);
		AfxMessageBox(str);
		return rcode;
	}
	// Load image
	rcode = loadgif(fname, image);
	if (rcode != NO_ERROR)
	{
		freeimage(image); // Free image on error
		str.Format("Could not load %s", fname);
		AfxMessageBox(str);
	}
	return rcode;
}

int CDIB::LoadTIF(LPCSTR fname, imgdes* image)
{
	// Get info on the file we're to load
	TiffData tdat;
	CString str;
	int rcode = tiffinfo((char*)fname, &tdat);
	if (rcode != NO_ERROR)	// Fill structure
	{
		str.Format("Error in reading %s", fname);
		AfxMessageBox(str);
		return rcode;
	}
	// Allocate space for an image
	rcode = allocimage(image, tdat.width, tdat.length, tdat.vbitcount);
	if (rcode != NO_ERROR)
	{
		str.Format("Not enough memory to load %s", fname);
		AfxMessageBox(str);
		return rcode;
	}
	rcode = loadtif(fname, image);
	if (rcode != NO_ERROR) // Free image on error
	{
		freeimage(image);
		str.Format("Could not load %s", fname);
		AfxMessageBox(str);
	}
	return rcode;
}

int CDIB::LoadJPG(LPCSTR fname, imgdes* image)
{
	// Get info on the file we're to load
	JpegData jdat;
	CString str;
	int rcode = jpeginfo(fname, &jdat);
	if (rcode != NO_ERROR)	// Fill structure
	{
		str.Format("Error in reading %s", fname);
		AfxMessageBox(str);
		return rcode;
	}
	// Allocate space for an image
	rcode = allocimage(image, (int)jdat.width, (int)jdat.length, jdat.vbitcount);
	if (rcode != NO_ERROR)
	{
		str.Format("Not enough memory to load %s", fname);
		AfxMessageBox(str);
		return rcode;
	}
	// Load image
	rcode = loadjpg((char*)fname, image);
	if (rcode != NO_ERROR)
	{
		freeimage(image); // Free image on error
		str.Format("Could not load %s", fname);
		AfxMessageBox(str);
	}
	return rcode;
}

// Source image will remain intact.
// Destination image should be a pointer to an imgdes object.
// You should call freeimage(desimg) on success
int CDIB::CreateImage8(imgdes* srcimg, imgdes* desimg)
{
	int rcode;
	//To view the entire image, use a temporary image descriptor
	// and set the image area to the entire image
	imgdes timage;
	copyimgdes(srcimg, &timage);
	setimagearea(&timage, 0, 0,
		(unsigned)timage.bmh->biWidth - 1,
		(unsigned)timage.bmh->biHeight - 1);

	// If we're displaying a 24-bit image on an 8-bit
	// display adapter, create a temporary 8-bit image for display
	if (srcimg->bmh->biBitCount == 24)
	{
		rcode = allocimage(desimg, (int)timage.bmh->biWidth, (int)timage.bmh->biHeight, 8);
		if (rcode == NO_ERROR)
		{
			// Quick dither representation of 24-bit image
			// (Or use colorscatter)
//			rcode = colordither(&timage, desimg, COLORDITHER256);
			rcode = convertrgbtopal(256, &timage, desimg);
			// If error, free allocated memory
			if (rcode != NO_ERROR)
				freeimage(desimg); 
		}
	}
	else 
		copyimgdes(&timage, desimg);
	return rcode;
}
#endif	// _VICTOR

/*
void CDIB::ReplaceColor(const int nI, const RGBQUAD& rgbQ)
{
	ASSERT(m_pBMI);
	ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
	ASSERT(m_pBits);

	BYTE* pBits = (BYTE*)GetBitsAddress();
	int iSize = StorageWidth() * DibHeight();
	while (iSize--)
	{
		*pBits = imap[*pBits];
		pBits++;
	}
	LPRGBQUAD pctThis = GetClrTabAddress();
	ASSERT(pctThis);
	RGBQUAD oc = pctThis[nWhat];
	pctThis[nWhat] = pctThis[nWith];
	TRACE("CDIB::ReplaceColor (%d,%d,%d)->(%d,%d,%d)\n",
		oc.rgbRed, oc.rgbGreen, oc.rgbBlue,
		pctThis[nWith].rgbRed, pctThis[nWith].rgbGreen, pctThis[nWith].rgbBlue);
}
*/

UINT CDIB::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
							 const LPPALETTEENTRY lpPaletteColors)
{
	RGBQUAD* pctThis = GetClrTabAddress();
//	::CopyMemory(pctThis, lpPaletteColors + nStartIndex, nNumEntries * sizeof(PALETTEENTRY));
// We can't use CopyMemory function, because the byte order of PALETTEENTRY (R,G,B,f)
// is different with that of RGBQUAD (B,G,R,res).
// RGBQUAD		<- when read from the file (byte order reversed in word)
// PALETTEENTRY <- in memory
	for (UINT i=0; i < nNumEntries; i++)
	{
		int k = nStartIndex + i;
		pctThis[k].rgbRed		= lpPaletteColors[i].peRed;
		pctThis[k].rgbGreen		= lpPaletteColors[i].peGreen;
		pctThis[k].rgbBlue		= lpPaletteColors[i].peBlue;
		pctThis[k].rgbReserved	= lpPaletteColors[i].peFlags;
	}
	return 0;
}

void CDIB::CopyPaletteEntry(const UINT nDest, const UINT nSrc)
{
	RGBQUAD* pctThis = GetClrTabAddress();
	pctThis[nDest] = pctThis[nSrc];
}
/*
UINT CDIB::SetPaletteEntriesFileIndex(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
{
	RGBQUAD* pctThis = GetClrTabAddress();
//	::CopyMemory(pctThis, lpPaletteColors + nStartIndex, nNumEntries * sizeof(PALETTEENTRY));
// We can't use CopyMemory function, because the byte order of PALETTEENTRY (R,G,B,f)
// is different with that of RGBQUAD (B,G,R,res).
	for (UINT i=0; i < nNumEntries; i++)
	{
		int k = m_imap[nStartIndex + i];
		pctThis[k].rgbRed		= lpPaletteColors[i].peRed;
		pctThis[k].rgbGreen		= lpPaletteColors[i].peGreen;
		pctThis[k].rgbBlue		= lpPaletteColors[i].peBlue;
		pctThis[k].rgbReserved	= lpPaletteColors[i].peFlags;
	}
	return 0;
}
*/
UINT CDIB::ShiftRGBPercent(UINT nStartIndex, UINT nNumEntries, int nPer)
{
	RGBQUAD* pctThis = GetClrTabAddress();
	if (nPer < -100)
		nPer = -100;
	float fFactor = (float)nPer / 100;
	for (UINT i=0; i < nNumEntries; i++)
	{
		int k = nStartIndex + i;
		int nVal;
		nVal = pctThis[k].rgbRed + (int)(pctThis[k].rgbRed * fFactor);
		if (nVal > 255)
			nVal = 255;
		pctThis[k].rgbRed		= nVal;
		nVal = pctThis[k].rgbGreen + (int)(pctThis[k].rgbGreen * fFactor);
		if (nVal > 255)
			nVal = 255;
		pctThis[k].rgbGreen		= nVal;
		nVal = pctThis[k].rgbBlue + (int)(pctThis[k].rgbBlue * fFactor);
		if (nVal > 255)
			nVal = 255;
		pctThis[k].rgbBlue		= nVal;
	}
	return 0;
}

UINT CDIB::RotatePaletteIndex(UINT nStartIndex, UINT nNumEntries, UINT nBy)
{
	while (nBy >= nNumEntries)
		nBy -= nNumEntries;
	if (nBy == 0)	// original state
		return 0;
	RGBQUAD* pctSt = GetClrTabAddress();
	pctSt += nStartIndex;
	RGBQUAD* pRGBBuf = new RGBQUAD[nNumEntries];
	int nTotalSize	= nNumEntries * sizeof(RGBQUAD);
	int nBySize		= nBy * sizeof(RGBQUAD);
	::CopyMemory(pRGBBuf + nBy,	pctSt,						nTotalSize - nBySize);
	::CopyMemory(pRGBBuf,		pctSt + nNumEntries - nBy,	nBySize);
	::CopyMemory(pctSt,			pRGBBuf,					nTotalSize);
	delete [] pRGBBuf;
	return 0;
}
/*
void CDIB::SaveResourceName(LPCSTR szPath)
{
	if (!szPath)
		return;
	int nLen = lstrlen(szPath);
	char* p = strrchr(szPath, '\\');	// Exclude path
	if (!p)
		return;
	char* q = strrchr(szPath, '.');	// Exclude extension
	if (q)
		*q = NULL;
	p++;
	m_strName = (char*)p;
}
*/
