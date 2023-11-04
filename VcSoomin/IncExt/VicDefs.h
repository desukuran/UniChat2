// VICDEFS.H -- Useful and necessary definitions for 
//   Victor Image Processing Library for Windows

#ifndef _VICDEFS_H_
#define _VICDEFS_H_

#if defined WIN32 || defined _WIN32
# define huge 
# define _export
#endif

#if defined(__TCPLUSPLUS__) || defined(__TURBOC__) \
 || defined(__BCPLUSPLUS__) || defined(__BORLANDC__)
#  define BC_COMP_
#else
#  define MSC_COMP_
#endif

/* Limits of an image Victor will process */
#if defined WIN32 || defined _WIN32
# define  XLIMIT	32768U
#else
# if defined MSC_COMP_
#  define  XLIMIT	  4048U
# else
#  define  XLIMIT	  4048
# endif
#endif
#define  YLIMIT    32768U

/* Useful definitions, values */
//#ifndef UCHAR
//#	define UCHAR unsigned char
//#endif
//#ifndef ULONG
//#	define ULONG unsigned long
//#endif

/* 32-bit platform defines */
#define WIN32SOS 1 
#define WINNTOS  2
#define WIN95OS  4

/* fseek constants */
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0

/* Digitizer Models */
#define HRTDIGI  1
#define IDCDIGI  2
#define SVIADIGI 3
#define QVIADIGI 4
#define WVPRDIGI 5

// Macros
// Convert segment, offset to far pointer
#define  MAKE_FPTR(mseg,ofs)	((void far *)\
								(((unsigned long)(mseg)<<16) | (unsigned)(ofs)))
#define beep()				MessageBeep(0)
#define inrange(a,x,b)		((a)<=(x)&&(x)<=(b))		// Check range of x
#define ofssetof(typ,mem)	((size_t)&(((typ *)NULL)->mem))
#define outrange(a,x,b)		((x)<(a)||(x)>(b))			// Check range of x
#define dim(x)				(sizeof(x) / sizeof(x[0]))	// Returns no. of elements

// Image descriptor
typedef struct
{
	UCHAR huge *ibuff;				// Image buffer address
	unsigned stx, sty, endx, endy;	// Image area to be processed (pixel coords)
	unsigned buffwidth;				// Image buffer width in bytes
	RGBQUAD far *palette;			// Address of palette associated with the image
	int colors;						// Palette colors
	int imgtype; 					// Image type: bit 0 = 1 if image is grayscale
	BITMAPINFOHEADER far *bmh;		// BITMAPINFOHEADER header and DIB address
} imgdes;

// Bit definitions for imgtype
#define IMGTYPE_GRAYSCALE 1 	// Image is grayscale

// TIFF file format info structure definition (used by tiffinfo)
typedef struct
{
	unsigned ByteOrder;		// Byte order -- II or MM
	unsigned width, length;	// TIF image width, length
	unsigned BitsPSample;	// TIF bits per sample
	unsigned Comp;			// Compression scheme code
	unsigned SamplesPPixel;	// Samples per pixel
	unsigned PhotoInt;		// Photo interpretation
	unsigned PlanarCfg;		// Planar configuration
	int vbitcount;			// Victor bits per pixel
} TiffData;

/* PCX file format info structure definition (used by pcxinfo) */
typedef struct
{
	int PCXvers; 	/* PCX version number */
	unsigned width, length; /* PCX image width, length */
	int BPPixel;		/* PCX bits per pixel */
	int Nplanes;		/* Number of planes */
	int BytesPerLine;	/* Bytes per line */
	int PalInt; 		/* Palette info interpretation: 1 = color, 2 = gray scale */
	int vbitcount;		/* Victor bits per pixel */
} PcxData;

/* GIF file format info structure definition (used by gifinfo) */
typedef struct
{
	unsigned width, length; /* GIF image width, length */
	int BitsColRes; 		/* Bits of color resolution */
	int BitsPPixel; 		/* Bits per pixel */
	int BckCol; 				/* Background color */
	int Laceflag;				/* Interlace flag */
	int Codesize;				/* Code size */
	int GIFvers;				/* GIF version, 87 or 89 */
	int vbitcount;		   /* Victor bits per pixel */
} GifData;

/* Targa file format info structure definition (used by tgainfo) */
typedef struct
{
	int IDfieldchars;	   /* Chars in ID field */
	unsigned width, length; /* Targa image width, length */
	int ColorMapType;	   /* Color map type: 0=no, 1=yes */
	int ImageType;		   /* Image type */
	int ColorMapEntryBits;  /* No. bits in color map entry */
	int Xorigin, Yorigin;   /* X,Y origin of image */
	int BPerPix; 		   /* Bits per pixel */
	int ABPerPix;		   /* Attribute bits per pixel */
	int ScreenOrigin;	   /* 0=lower left corner, 2=upper left */
	int Interleave;		   /* Data storage interleave: 0=none */
	int vbitcount;		   /* Victor bits per pixel */
} TgaData;

/* JPEG file format info structure definition (used by jpeginfo) */
typedef struct
{
	int ftype;					/* JPEG file type: -1 or 0 - 15 */
	unsigned width, length; /* JPEG image width, length */
	unsigned comps; 		/* Number of components */
	unsigned precision; 	/* Sample precision, 8 or 16 */
	unsigned sampFac[4];		/* Horiz * 16 + Vert */
	int vbitcount;		   /* Victor bits per pixel */
} JpegData;

/* HSV structure */
typedef struct tagHSVTRIPLE
{
	UCHAR hue;
	UCHAR saturation;
	UCHAR value;
} HSVTRIPLE;

/* Related, useful data struct */
typedef struct
{
	unsigned char rgbBlue, rgbGreen, rgbRed, palno;
} RGB_DATA;

#ifdef __cplusplus
   extern "C" {
#endif	/* __cplusplus */
/* Function declarations for Victor Image Processing Library */
int  _export FAR PASCAL addimage(imgdes far *srcimg, imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL allocimage(imgdes far *image, int width, int length, int bppixel);
int  _export FAR PASCAL andimage(imgdes far *srcimg, imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL blur(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL blurthresh(const int thres, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL bmpinfo(const char far *fname, BITMAPINFOHEADER far *bdat);
int  _export FAR PASCAL brightenmidrange(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL calcavglevel(imgdes far *srcimg, int far *redavg, int far *grnavg, 
	int far *bluavg);
int  _export FAR PASCAL calchisto(imgdes far *srcimg, long far *redtab, long far *grntab, 
	long far *blutab);
int  _export FAR PASCAL changebright(const int amt, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL colordither(imgdes far *srcimg, imgdes far *desimg, int colorMode);
int  _export FAR PASCAL colorscatter(imgdes far *srcimg, imgdes far *desimg, int colorMode);
int  _export FAR PASCAL colortogray(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL convert1bitto8bit(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL convert8bitto1bit(int mode, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL convertpaltorgb(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL convertrgbtopal(int palcolors, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL copyimage(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL copyimagebits(imgdes far *srcimg, imgdes far *desimg);
void _export FAR PASCAL copyimagepalette(imgdes far *srcimg, imgdes far *desimg);
void _export FAR PASCAL copyimgdes(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL cover(const int thres, imgdes far *srcimg, imgdes far *oprimg, 
	imgdes far *desimg);
int  _export FAR PASCAL defaultpalette(imgdes far *srcimg);
int  _export FAR PASCAL dibtobitmap(HDC hdc, UCHAR huge *dib, HBITMAP far *hBitmap);
int  _export FAR PASCAL dibtoimage(UCHAR huge *dib, imgdes far *desimg);
int  _export FAR PASCAL divide(const int divsr, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL drawhisto(HDC hdc, RECT far *rect, int bppixel, 
	long far *redtab, long far *grntab, long far *blutab);
int  _export FAR PASCAL exchangelevel(int min, int max, const int newval, 
	imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL expandcontrast(int min, int max, imgdes far *srcimg, 
	imgdes far *desimg);
int  _export FAR PASCAL flipimage(imgdes far *srcimg, imgdes far *desimg);
void _export FAR PASCAL freeimage(imgdes far *image);
int  _export FAR PASCAL gammabrighten(const double amt, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL getgifcomment(const char far *fname, char far *buff, int maxbuf);
long _export FAR PASCAL getpixelcolor(imgdes far *image, int xcoord, int ycoord);
int  _export FAR PASCAL gifinfo(const char far *fname, GifData far *gdat);
int  _export FAR PASCAL histobrighten(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL histoequalize(imgdes far *srcimg, imgdes far *desimg);
void _export FAR PASCAL hsv2rgb(HSVTRIPLE far *hsvpal, RGBQUAD far *rgbpal, int colors);
void _export FAR PASCAL imageareatorect(imgdes far *image, RECT far *rect);
int  _export FAR PASCAL imagetodib(imgdes far *srcimg, UCHAR huge * far *dib);
int  _export FAR PASCAL jpeginfo(const char far *fname, JpegData far *jdat);
int  _export FAR PASCAL kodalith(const int thres, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL limitlevel(const int thres, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL loadbif(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadbmp(const char far *fname, imgdes far *image);
int  _export FAR PASCAL loadbmppalette(const char far *fname, RGBQUAD far *paltab);
int  _export FAR PASCAL loadgif(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadgifpalette(const char far *fname, RGBQUAD far *paltab);
int  _export FAR PASCAL loadjpg(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadpcx(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadpcxpalette(const char far *fname, RGBQUAD far *paltab);
int  _export FAR PASCAL loadtga(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadtgapalette(const char far *fname, RGBQUAD far *paltab);
int  _export FAR PASCAL loadtif(const char far *fname, imgdes far *desimg);
int  _export FAR PASCAL loadtifpage(const char far *fname, imgdes far *desimg, int page);
int  _export FAR PASCAL loadtifpalette(const char far *fname, RGBQUAD far *paltab);
int  _export FAR PASCAL matchcolorimage(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL matrixconv(const char far *kernal, 
	imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL mirrorimage(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL multiply(const int multr, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL negative(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL orimage(imgdes far *srcimg, imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL outline(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL pcxinfo(const char far *fname, PcxData far *pdata);
int  _export FAR PASCAL pixelcount(int min, int max, long far *redct, 
	long far *grnct, long far *bluct, imgdes far *srcimg);
int  _export FAR PASCAL pixellize(const int factr, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL printimage(HWND hwnd, HDC hdcprn, int mode, 
	imgdes far *image, RECT far *rect, int boxsiz, int (FAR PASCAL *dspfct)());
int  _export FAR PASCAL rainbowpalette(imgdes far *srcimg);
void _export FAR PASCAL recttoimagearea(RECT far *rect, imgdes far *image);
int  _export FAR PASCAL reduceimagecolors(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL removenoise(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL resize(imgdes far *srcimg, imgdes far *desimg);
void _export FAR PASCAL rgb2hsv(RGBQUAD far *rgbpal, HSVTRIPLE far *hsvpal, int colors);
int  _export FAR PASCAL rotate90(const int dir, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL savebif(const char far *fname, imgdes far *srcimg);
int  _export FAR PASCAL savebmp(const char far *fname, imgdes far *srcimg, int cmp);
int  _export FAR PASCAL saveeps(const char far *fname, imgdes far *srcimg);
int  _export FAR PASCAL savegif(const char far *fname, imgdes far *srcimg);
int  _export FAR PASCAL savejpg(const char far *fname, imgdes far *srcimg, int cmp);
int  _export FAR PASCAL savepcx(const char far *fname, imgdes far *srcimg);
int  _export FAR PASCAL savetga(const char far *fname, imgdes far *srcimg, int cmp);
int  _export FAR PASCAL savetif(const char far *fname, imgdes far *srcimg, int cmp);
void _export FAR PASCAL setgifcomment(int version, char far *comment);
void _export FAR PASCAL setimagearea(imgdes far *image, unsigned stx, 
	unsigned sty, unsigned endx, unsigned endy);
int  _export FAR PASCAL setpixelcolor(imgdes far *image, int xcoord, int ycoord, ULONG level);
int  _export FAR PASCAL setupimgdes(UCHAR huge *dib, imgdes far *image);
int  _export FAR PASCAL sharpen(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL sharpengentle(imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL SJadfchangepaper(int handle);
int  _export FAR PASCAL SJadfdetect(int handle);
int  _export FAR PASCAL SJadfhaspaper(int handle);
int  _export FAR PASCAL SJadflidclosed(int handle);
int  _export FAR PASCAL SJadfscanimage(int sjhandle, imgdes far *desimg);
int  _export FAR PASCAL SJadfunloadpaper(int handle);
void _export FAR PASCAL SJclose(int handle);
int  _export FAR PASCAL SJdetect(int far *handle);
int  _export FAR PASCAL SJdetectdriver(void);
int  _export FAR PASCAL SJerrno(int handle);
int  _export FAR PASCAL SJgetcurrent(int handle, int code);
int  _export FAR PASCAL SJgetdatatype(int handle);
int  _export FAR PASCAL SJgetdatawidth(int handle);
int  _export FAR PASCAL SJgetmax(int handle, int code);
int  _export FAR PASCAL SJgetmin(int handle, int code);
int  _export FAR PASCAL SJgetscanbytes(int handle);
int  _export FAR PASCAL SJgetscanrows(int handle);
int  _export FAR PASCAL SJmodel(int handle);
int  _export FAR PASCAL SJscanimage(int handle, imgdes far *desimg);
int  _export FAR PASCAL SJsetcontrast(int handle, int contrast);
int  _export FAR PASCAL SJsetdatatype(int handle, int type);
int  _export FAR PASCAL SJsetdatawidth(int handle, int width);
int  _export FAR PASCAL SJsetintensity(int handle, int contrast);
int  _export FAR PASCAL SJwinsize(int handle, RECT far *scanrect);
int  _export FAR PASCAL SJxyres(int handle, int xval, int yval);
int  _export FAR PASCAL subimage(imgdes far *srcimg, imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL tgainfo(const char far *fname, TgaData far *tdat);
int  _export FAR PASCAL threshold(const int thres, imgdes far *srcimg, imgdes far *desimg);
int  _export FAR PASCAL tiffgetpageinfo(LPCSTR fname, int far *totalPages, 
	int far *pageArray, int arrayElems);
int  _export FAR PASCAL tiffgetxyresolution(const char far *fname, 
	unsigned far *xres, unsigned far *yres, unsigned far *resUnit);
int  _export FAR PASCAL tiffinfo(const char far *fname, TiffData far *tdat);
int  _export FAR PASCAL tiffinfopage(const char far *fname, TiffData far *tdat, int page);
void _export FAR PASCAL tiffsetxyresolution(unsigned xres, unsigned yres, unsigned resUnit);
int  _export FAR PASCAL usetable(const UCHAR far *redtab, const UCHAR far *grntab,
   const UCHAR far *blutab, imgdes far *srcimg, imgdes far *desimg);
WORD _export FAR PASCAL VicSJversion(void);
WORD _export FAR PASCAL Victorversion(void);
int  _export FAR PASCAL victowinpal(imgdes far *srcimg, HPALETTE far *hPal);
int  _export FAR PASCAL viewimage(HWND hwnd, HDC hdc, HPALETTE far *hPal, 
	int xpos, int ypos, imgdes far *image);
int  _export FAR PASCAL wintovicpal(HPALETTE hPal, imgdes far *desimg);
int  _export FAR PASCAL wtaverage(const int prct, imgdes far *srcimg, 
	imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL xorimage(imgdes far *srcimg, imgdes far *oprimg, imgdes far *desimg);
int  _export FAR PASCAL zeroimage(const int level, imgdes far *image);
void _export FAR PASCAL zeroimgdes(imgdes far *image);
int  _export FAR PASCAL checkrange_(imgdes far *image);
int  _export FAR PASCAL checkrange1_(imgdes far *image);
void _export FAR PASCAL CreateDefaultPalette_(imgdes far *image);
void _export FAR PASCAL Align1bppBits_(UCHAR far *dbuff, UCHAR huge *src, int stx, int bits2mov);
void _export FAR PASCAL Store1bppBits_(UCHAR huge *des, UCHAR far *sbuff, int stx, int bits2mov);

#if defined WIN32 || defined _WIN32
#define fmemcpy_ memcpy
#define fmemset_ memset
#define fmemmove_ memmove
#define _fmemcmp memcmp
#define setGlobalCompactFlag(flag)
#else
/* String functions to handle huge pointers */
void far * _export FAR PASCAL fmemcpy_(void huge *des, const void huge *src, unsigned count);
void far * _export FAR PASCAL fmemmove_(void huge *des, const void huge *src, unsigned count);
void far * _export FAR PASCAL fmemset_(void huge *des, int mchr, unsigned count);
void _export FAR PASCAL setGlobalCompactFlag(BOOL flag);
void _export FAR PASCAL chirp(void);

void PASCAL memcpy32_(void huge *des, const void huge *src, unsigned count);
void PASCAL memmove32_(void huge *des, const void huge *src, unsigned count);
void PASCAL memset32_(void huge *des, int mchr, unsigned count);
extern unsigned _AHINCR;
#endif

/* Local routines */
int  PASCAL calc_DIBcolors_(BITMAPINFOHEADER far *bmHdr);
void PASCAL drawRepBits_(int bitpos, UCHAR near *dbuff, 
	int bits2wrt, int bits2unpack);
int  PASCAL matrixall_(imgdes far *srcimg, imgdes far *desimg,
	void (_cdecl *matfct)(int,UCHAR near *,UCHAR near *,int,int,int far *),
	int far *varaddr);
int PASCAL modifyImage_(int flag, imgdes far *srcimg, imgdes far *desimg,
	void (_cdecl *modifyRow)(UCHAR near *,UCHAR near *,int,void far *), void far *vars);
void PASCAL ConvertPalToRGB_(UCHAR far *buff, unsigned pels2conv, RGBQUAD far *palette);
void PASCAL set_rows_cols_(imgdes far *srcimg, imgdes far *desimg,
   unsigned far *rows, unsigned far *cols);
int  PASCAL table_mod_(const UCHAR far *redtab, const UCHAR far *grntab,
	const UCHAR far *blutab, imgdes far *srcimg, imgdes far *desimg);
int  PASCAL twoimagefcts_(imgdes far *srcimg,
	imgdes far *oprimg, imgdes far *desimg,
	void (_cdecl *twofct)(UCHAR near *,UCHAR near *,UCHAR near *,int));
#ifdef __cplusplus
 }
#endif		// __cplusplus

/* Error codes for Victor Image Processing Library for Windows */
// NO_ERROR is already defined by WINDOWS.H
#if !defined(NO_ERROR)
#define  NO_ERROR	  0 	  /* No error */
#endif
#define  BAD_RANGE	  -1	  /* Range error */
#define  NO_DIG 	  -2	  /* Digitizer board not detected */
#define  BAD_DSK	  -3	  /* Disk full, file not written */
#define  BAD_OPN	  -4	  /* Filename not found */
#define  BAD_FAC	  -5	  /* Non-dimensional variable out of range */
#define  BAD_TIFF	  -6	  /* Unreadable TIF format */
#define  TIFF_NOPAGE -51	  /* TIF page not found */
#define  BAD_BPS	  -8	  /* TIF bits per sample not supported */
#define  BAD_CMP	  -9	  /* Unreadable compression scheme */
#define  BAD_CRT	 -10	  /* Cannot create file */
#define  BAD_FTPE	 -11	  /* Unknown file format */

#define  BAD_DIB	 -12	  /* Device independent bitmap is compressed */
#define  VMODE_ERR	 -13	  /* Invalid video mode */
#define  BAD_MEM	 -14	  /* Insufficient memory for function */
#define  BAD_PIW	 -15	  /* Not PIW format */
#define  BAD_PCX	 -16	  /* Unreadable PCX format */
#define  BAD_GIF	 -17	  /* Unreadable GIF format */
#define  PRT_ERR	 -18	  /* Print error */
#define  PRT_BUSY	 -41	  /* Printimage() is busy */
#define  SCAN_ERR	 -19	  /* Scanner error */

/* Expanded/Extended/Conventional memory error codes */
#define  CM_ERR 	 -20	  /* Conventional memory handle overflow */
#define  NO_EMM 	 -21	  /* Expanded memory manager not found */
#define  EMM_ERR	 -22	  /* Expanded memory manager error */
#define  NO_XMM 	 -23	  /* Expanded memory manager not found */
#define  XMM_ERR	 -24	  /* Expanded memory manager error */

#define  BAD_TGA	 -25	  /* Unreadable TGA format */
#define  BAD_BPP	 -26	  /* Bits per pixel not supported */
#define  BAD_BMP	 -27	  /* Unreadable BMP format */
#define  BAD_JPEG	 -43	  /* Unreadable JPEG format */
#define  TOO_CPLX	 -44	  /* Image is too complex to complete operation */
#define  NOT_AVAIL	 -50	  /* Function not available due to missing module */

/* Scanner ADF error codes */
#define  SCAN_UNLOAD		-45 // paper could not be unloaded from ADF
#define  SCAN_LIDUP 	-46 // ADF lid was opened
#define  SCAN_NOPAPER	-47 // ADF bin is empty
#define  SCAN_NOADF 	-48 // ADF is not connected,
#define  SCAN_NOTREADY	-49 // ADF is connected but not ready

/* Device error codes */
#define  COM_ERR	 -31	  /* Serial data reception error */
#define  BAD_COM	 -32	  /* No data from COM port */
#define  NO_DEV_DATA -33	  /* No data from device */
#define  TIMEOUT	 -34	  /* Function timed out */

/* Windows related */
/* Could not lock memory (invalid handle or memory discarded) */
#define BAD_LOCK	-40
#define BAD_IBUF	-42 	  /* Invalid image buffer address */

/* Error codes specifically for TI Graphics Architecture (TIGA) interface */
#define TIGA_BAD_BPP -37	  /* Bits per pixel of TIGA mode not 8 */
#define TIGA_BAD_MEM -38	  /* Could not allocate enough GSP memory */
#define TIGA_NO_EXT  -39	  /* Could not load TIGA extended primitives */

/* Printimage() print modes */
#define PRTDEFAULT	0
#define PRTHALFTONE 1
#define PRTSCATTER	2

/* Colordither, colorscatter modes */
#define COLORSCATTER16	0
#define COLORSCATTER256 1
#define COLORDITHER16  COLORSCATTER16
#define COLORDITHER256 COLORSCATTER256

/* File save defines */
#define TIFUNC 0
#define TIFLZW 1
#define TIFPB  2
#define TIFG3  3
#define TIFG4  4
#define BMPUNC 0
#define BMPRKE 1
#define TGAUNC 0
#define TGARLE 1
#define PIWUNC 0
#define PIWRLE 1

/* ScanJet models */
#define SCNJET 0
#define SJPLUS 1
#define SJIIC  2
/* Image output data types */
#define LINEART 0
#define BWDITH	3
#define BWGRAY	4
#define COL24	5
#define COLDITH 7
/* ScanJet parameter codes */
#define SJXRES		 0		/* X resolution */
#define SJYRES		 1		/* Y resolution */
#define SJXEXTENT	 2		/* X extent */
#define SJYEXTENT	 3		/* Y extent */
#define SJDATATYPE	 4		/* Output data type */
#define SJINTENSITY  5		/* Intensity */
#define SJCONTRAST	 6		/* Contrast */
#define SJRESET 	 7		/* Reset scanner to default conditions */
#define SJBPLINE	 8		/* Bytes per scanline */
#define SJSLINES	 9		/* Scanline in a window */
#define SJDWIDTH	 10 	/* Data width */
#define SJMODEL1	 11 	/* Model 1 */
#define SJMODEL2	 12 	/* Model 2 */
#define SJERRSTACK	 13 	/* Get error stack depth */
#define SJGETERRNO	 14 	/* Get error number */
#define SJCLRERR	 15 	/* Clear last error */
#define SJSCNWIN	 16 	/* Scan the window */
#define SJSTDWID	 17 	/* Set data width */
#define SJSTDTYP	 18 	/* Set output data type, invert image */
#define SJSTXYRS	 19 	/* Set X,Y resolution */
#define SJSTINTENS	 20 	/* Set intensity */
#define SJSTCONTRAST 21 	/* Set contrast */
#define SJWINSIZ	 22 	/* Set scan window size */
#define SJERR		 23 	/* No match, return string to generate error */
#define SJADFSCNWIN   24	// ADF scan window
#define SJADFCHANGE   25	// ADF change doc
#define SJADFUNLOAD   26	// ADF unload doc
#define SJADFREADY	  27	// ADF is ready
#define SJADFCONNECTED 28	// ADF is connected
#define SJADFHASPAPER  29	// ADF has paper
#define SJADFOPENED   30	// ADF opened since last change/scan
#define SJADFREADYTOUNLOAD 31 // ADF is ready to unload
#define SJMAXSTR	 31

#endif	/* _VICDEFS_H_ */
