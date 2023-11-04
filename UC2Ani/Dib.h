//
//	CDIB:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
//	Nov 25mon '96	Added GIF, TIF, JPG support using Victor Library

// #include <mmsystem.h>	// link winmm.lib
#ifdef _VICTOR
#include <vicdefs.h>	// link Vic32ms.lib, runtime Vic32.dll
#endif

#ifndef __DIB_H
#define __DIB_H

// "DATASRC0|filename.ext"
typedef struct tagDATASOURCEFILEHEADER
{
	WORD	wType;			// 'DS' (0x5344)
	DWORD	dwFileSize;
	WORD	wNumEntries;	// Number of entries
	WORD	bcReserved1; 
	WORD	bcReserved2;
} DATASOURCEFILEHEADER;

typedef struct tagDATASOURCEENTRY
{
	char	id[13];		// org filename (with extension) + NULL
	DWORD	dwOffset;	// offset to the BITMAPFILEHEADER
} DATASOURCEENTRY;

enum IMAGE_OPERATION
{
	OPACITY_100		= 0x0000,	// 100% default
	OPACITY_75		= 0x0001,
	OPACITY_50		= 0x0002,	// 50%
	OPACITY_25		= 0x0004,	// 25%
	OPACITY_12		= 0x0008,	// 12.5% paint
	OPACITY_0		= 0x0010,	// 
	OPACITY_MASK	= 0x001F,
	IMAGE_FLIP		= 0x0100,	// change Mirror state
	IMAGE_VERTICAL	= 0x0200,
	ORIENT_MASK		= 0x0F00,
	NO_COLORKEY		= 0x1000,	// Colorkey
	COLORKEY_MASK	= 0xF000,
	DEFAULT_IO		= 0x0000
};

class AFX_EXT_CLASS CDIB : public CObject
{
	DECLARE_SERIAL(CDIB)
public:
	CDIB();
	// By using virtual destructor, derived classes' destructors can be called...
	virtual ~CDIB();
	CDIB& operator=(CDIB& rhs);

// Attributes
	BITMAPINFO*		GetBitmapInfoAddress() const { return m_pBMI; }	// Pointer to bitmap info
	void*			GetBitsAddress() const		 { return m_pBits; }	// Pointer to the bits
	int				GetBitsSize() const;
	RGBQUAD*		GetClrTabAddress() const			// Pointer to color table
					{ return (LPRGBQUAD)(((BYTE*)(m_pBMI)) + sizeof(BITMAPINFOHEADER)); }
	int				GetNumClrEntries() const;				// Number of color table entries
	void*			GetPixelAddress(const int x, const int y) const;
	int				GetBitCount() const	{ return m_pBMI->bmiHeader.biBitCount; }
	virtual int		GetWidth() const	{ return DibWidth(); }	// Image width
	virtual int		GetHeight()	const	{ return DibHeight(); }	// Image height
	virtual void	GetRect(CRect& rect) const;
	CString*		GetName()			{ return &m_strName; }
	enum BITMAP_FILE_TYPE
	{
		FILE_NONE,
		FILE_BMP,
		FILE_BM,	// without palette table
		FILE_BMZ,	// LZ compressed
		FILE_BMC,	// LZ compressed without palette table
		FILE_GIF,
		FILE_TIF,
		FILE_JPG
	};
	BITMAP_FILE_TYPE GetFileType(LPCSTR szFile);

// Operations
	virtual void	Serialize(CArchive& ar);
	BOOL	Create(const int iWidth, const int iHeight, LPCSTR szPalFileName=NULL);			// Create a new DIB
	BOOL	Create(BITMAPINFO* pBMI, BYTE* pBits);			// Create from existing mem
	virtual BOOL	Load(CFile* const fp, LPCSTR szPalFileName=NULL,
						const BOOL bIsLZ=FALSE,
						const DWORD dwFileStart=0L);	// Load from file
	virtual BOOL	Load(LPCSTR szFileName=NULL,
						LPCSTR szPalFileName=NULL);	// Load DIB from disk file
	virtual BOOL	Load(const WORD wResid);				// Load DIB from resource
	BOOL			LoadPalette(LPCSTR szPalFileName);
	virtual BOOL	Save(LPCSTR szFileName=NULL);		// Save DIB to disk file
	virtual BOOL	Save(CFile* const fp, const BOOL bPalette=TRUE);					// Save to file
	virtual void	Draw(CDC* pDC, const int x, const int y);
	void			Draw(CDC* pDC, const int xd, const int yd, const int w, int h, const int xs, const int ys);
	void			Tile(CDC* pDC, const int x0, const int y0, CRect& rcClient);
	virtual BOOL	MapColorsToPalette(const CPalette* pPal);
	virtual void	CopyBits(CDIB* pDIB,
						const int xd, const int yd,	const int w,  int h,
						const int xs, const int ys,	const COLORREF clrTrans=0,
						const WORD wImOp=DEFAULT_IO);
	void	CopyPaletteEntry(const UINT nDest, const UINT nSrc);
	UINT	SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
							const LPPALETTEENTRY lpPaletteColors);
	UINT	ShiftRGBPercent(UINT nStartIndex, UINT nNumEntries, int nPer);
	UINT	RotatePaletteIndex(UINT nStartIndex, UINT nNumEntries, UINT nBy);
	void	ClearImage();
	void	ClearRect(CRect& rcClear);

protected:
	int		CountBitsSize(const int nW, const int nH) const
			{ return (((nW + 3) & ~3) * nH); }
	BOOL	LoadDataSource(LPCSTR szSrcFileName,
						LPCSTR szFileName,
						LPCSTR szPalFileName=NULL);	// Load DIB from Data Source
//	BOOL	SaveDataSource(LPCSTR szSrcFileName=NULL,
//							LPCSTR szFileName=NULL);	// Save to Data Source

	BITMAPINFO*	m_pBMI;		// Pointer to BITMAPINFO struct
	BYTE*		m_pBits;	// Pointer to the bits
	BOOL		m_bMyBits;	// TRUE if DIB owns Bits memory
	BOOL		m_bMapColorsDone;
	CString		m_strName;	// BMP Filename, resource name

#ifdef _VICTOR
	// For Victor Library
	BOOL			LoadFromImage(LPVOID pImg);
	int				LoadGIF(LPCSTR fname, imgdes* image);
	int				LoadTIF(LPCSTR fname, imgdes* image);
	int				LoadJPG(LPCSTR fname, imgdes* image);
	int				CreateImage8(imgdes* srcimg, imgdes* desimg);
#endif // _VICTOR

private:
	int		DibWidth() const		{ return m_pBMI->bmiHeader.biWidth; }
	int		DibHeight() const		{ return m_pBMI->bmiHeader.biHeight; }
	int		StorageWidth() const	{ return (m_pBMI->bmiHeader.biWidth + 3) & ~3; }
};

/*
// CBmpUsage
class AFX_EXT_CLASS CBmpUsage : public CObject
{
	DECLARE_SERIAL(CBmpUsage)
public:
	CBmpUsage();
	~CBmpUsage();
	void		AddRef();	{ ++m_nRef; }
	int			Release()	{ return (--m_nRef); }

protected:
	CString		m_strName;	// Filename
	BITMAPINFO*	m_pBMI;		// Pointer to BITMAPINFO struct
	BYTE*		m_pBits;	// Pointer to the bits
	int			m_nRef;		// Reference Count
};

// CBUT : Bitmap Usage Table
class AFX_EXT_CLASS CBUT
{
public:
	CBUT();
	~CBUT();

};
*/
#endif // __DIB_H
