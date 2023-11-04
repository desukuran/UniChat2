/****************************************************************************\
*                                                                            *
*  FGWIN.H                                                                   *
*                                                                            *
*  This file contains the C and C++ function prototypes for Fastgraph 5.0    *
*  for Windows.                                                              *
*                                                                            *
*  Copyright (c) 1991-1998 Ted Gruber Software.  All rights reserved.        *
*                                                                            *
\****************************************************************************/

#ifndef __FGWIN_H

#define __FGWIN_H

#ifndef __WINDOWS_H
#include <windows.h>       /* Include WINDOWS.H if not already included */
#endif

#ifdef __BORLANDC__        /* Borland C++ (Win32) */
#ifdef __WIN32__
#define FG32
#endif
#endif

#ifdef _MSC_VER            /* Microsoft Visual C++ 32-bit Edition */
#if _M_IX86 >= 300
#define FG32
#define _export
#endif
#endif

#ifdef __SC__              /* Symantec C++ (Win16 and Win32) */
#ifdef __NT__              /* Symantec C++ (Win32) */
#define FG32
#endif
#endif

#ifdef __WATCOMC__         /* WATCOM C/C++ (Win16 and Win32) */
#ifdef __386__             /* WATCOM C/C++ (Win32) */
#define FG32
#ifdef _export
#undef _export
#define _export
#endif
#endif
#endif

#ifdef FG32                /* data types for Win32 environments */
#define FG_APIENTRY __cdecl
#define byteptr char *
#define dblptr  double *
#define hugeptr char *
#define intptr  int *
#define longptr long *
#define voidptr void *
#else                      /* data types for Win16 environments */
#define FG_APIENTRY _pascal
#define byteptr char far *
#define dblptr  double far *
#define hugeptr char huge *
#define intptr  int far *
#define longptr long far *
#define voidptr void far *
#endif

#ifdef __cplusplus
extern "C" {
#endif

void     FG_APIENTRY fg_arc (int, int, int);
void     FG_APIENTRY fg_arcw (double, int, int);

int      FG_APIENTRY fg_bmphead (byteptr, voidptr);
int      FG_APIENTRY fg_bmppal (byteptr, voidptr);
void     FG_APIENTRY fg_bmpsize (voidptr, intptr, intptr);
void     FG_APIENTRY fg_box (int, int, int, int);
void     FG_APIENTRY fg_boxdepth (int, int);
void     FG_APIENTRY fg_boxw (double, double, double, double);
void     FG_APIENTRY fg_boxx (int, int, int, int);
void     FG_APIENTRY fg_boxxw (double, double, double, double);

void     FG_APIENTRY fg_circle (int);
void     FG_APIENTRY fg_circlef (int);
void     FG_APIENTRY fg_circlefw (double);
void     FG_APIENTRY fg_circlew (double);
int      FG_APIENTRY fg_clip2vb (int, int, int, int, int);
void     FG_APIENTRY fg_clipdcb (voidptr, int, int);
void     FG_APIENTRY fg_clipmap (voidptr, int, int);
void     FG_APIENTRY fg_clipmask (voidptr, int, int);
void     FG_APIENTRY fg_clpimage (voidptr, int, int);
void     FG_APIENTRY fg_clprect (int, int, int, int);
void     FG_APIENTRY fg_clprectw (double, double, double, double);
void     FG_APIENTRY fg_clprectx (int, int, int, int);
int      FG_APIENTRY fg_colors (void);
void     FG_APIENTRY fg_copypage (int, int);

void     FG_APIENTRY fg_dash (int, int, int);
void     FG_APIENTRY fg_dashrel (int, int, int);
void     FG_APIENTRY fg_dashrw (double, double, int);
void     FG_APIENTRY fg_dashw (double, double, int);
int      FG_APIENTRY fg_ddflip (void);
int      FG_APIENTRY fg_ddflipnw (void);
void     FG_APIENTRY fg_ddfreedc (HDC);
HDC      FG_APIENTRY fg_ddgetdc (void);
int      FG_APIENTRY fg_ddgetobj (int);
int      FG_APIENTRY fg_ddlock (void);
void     FG_APIENTRY fg_ddsetup (int, int, int, int);
int      FG_APIENTRY fg_ddstatus (void);
void     FG_APIENTRY fg_ddunlock (void);
void     FG_APIENTRY fg_defcolor (int, int);
HPALETTE FG_APIENTRY fg_defpal (void);
void     FG_APIENTRY fg_dispfile (byteptr, int, int);
void     FG_APIENTRY fg_display (voidptr, int, int);
void     FG_APIENTRY fg_displayp (voidptr, int, int);
void     FG_APIENTRY fg_draw (int, int);
void     FG_APIENTRY fg_drawdcb (voidptr, int, int);
void     FG_APIENTRY fg_drawmap (voidptr, int, int);
void     FG_APIENTRY fg_drawmask (voidptr, int, int);
void     FG_APIENTRY fg_drawrel (int, int);
void     FG_APIENTRY fg_drawrelx (int, int);
void     FG_APIENTRY fg_drawrw (double, double);
void     FG_APIENTRY fg_drawrxw (double, double);
void     FG_APIENTRY fg_draww (double, double);
void     FG_APIENTRY fg_drawx (int, int);
void     FG_APIENTRY fg_drawxw (double, double);
void     FG_APIENTRY fg_drect (int, int, int, int, voidptr);
void     FG_APIENTRY fg_drectw (double, double, double, double, voidptr);
void     FG_APIENTRY fg_drwimage (voidptr, int, int);

void     FG_APIENTRY fg_ellipse (int, int);
void     FG_APIENTRY fg_ellipsef (int, int);
void     FG_APIENTRY fg_ellipsew (double, double);
void     FG_APIENTRY fg_ellipsfw (double, double);
void     FG_APIENTRY fg_erase (void);

void     FG_APIENTRY fg_fillpage (void);
int      FG_APIENTRY fg_findrgb (int, int, int);
long     FG_APIENTRY fg_fixdiv (long, long);
long     FG_APIENTRY fg_fixed (double);
long     FG_APIENTRY fg_fixmul (long, long);
void     FG_APIENTRY fg_fixtrig (int, longptr, longptr);
void     FG_APIENTRY fg_flicdone (voidptr);
int      FG_APIENTRY fg_flichead (byteptr, voidptr);
int      FG_APIENTRY fg_flicopen (byteptr, voidptr);
int      FG_APIENTRY fg_flicplay (voidptr, int, int);
void     FG_APIENTRY fg_flicsize (voidptr, intptr, intptr);
int      FG_APIENTRY fg_flicskip (voidptr, int);
void     FG_APIENTRY fg_flipdcb (voidptr, int, int);
void     FG_APIENTRY fg_flipmask (voidptr, int, int);
double   FG_APIENTRY fg_float (long);
void     FG_APIENTRY fg_flood (int, int);
void     FG_APIENTRY fg_floodw (double, double);
void     FG_APIENTRY fg_flpimage (voidptr, int, int);
void     FG_APIENTRY fg_fontdc (HDC);
void     FG_APIENTRY fg_fontload (int);

void     FG_APIENTRY fg_getblock (voidptr, int, int, int, int);
void     FG_APIENTRY fg_getclip (intptr, intptr, intptr, intptr);
long     FG_APIENTRY fg_getclock (void);
int      FG_APIENTRY fg_getcolor (void);
void     FG_APIENTRY fg_getdacs (int, int, voidptr);
HDC      FG_APIENTRY fg_getdc (void);
void     FG_APIENTRY fg_getdcb (voidptr, int, int);
int      FG_APIENTRY fg_getdepth (void);
int      FG_APIENTRY fg_gethpage (void);
void     FG_APIENTRY fg_getimage (voidptr, int, int);
int      FG_APIENTRY fg_getindex (int);
long     FG_APIENTRY fg_getline (int);
int      FG_APIENTRY fg_getlines (void);
void     FG_APIENTRY fg_getmap (voidptr, int, int);
int      FG_APIENTRY fg_getmaxx (void);
int      FG_APIENTRY fg_getmaxy (void);
int      FG_APIENTRY fg_getpage (void);
int      FG_APIENTRY fg_getpixel (int, int);
void     FG_APIENTRY fg_getrgb (int, intptr, intptr, intptr);
void     FG_APIENTRY fg_getview (intptr, intptr, intptr, intptr, intptr, intptr, intptr, intptr);
void     FG_APIENTRY fg_getworld (dblptr, dblptr, dblptr, dblptr);
int      FG_APIENTRY fg_getxbox (void);
int      FG_APIENTRY fg_getxjust (void);
int      FG_APIENTRY fg_getxpos (void);
int      FG_APIENTRY fg_getybox (void);
int      FG_APIENTRY fg_getyjust (void);
int      FG_APIENTRY fg_getypos (void);
void     FG_APIENTRY fg_gouraud (intptr, byteptr, int);

void     FG_APIENTRY fg_imagebuf (voidptr, UINT);
long     FG_APIENTRY fg_imagesiz (int, int);
void     FG_APIENTRY fg_initw (void);
int      FG_APIENTRY fg_inside (intptr, int, int, int);
void     FG_APIENTRY fg_invdcb (voidptr, int, int);
void     FG_APIENTRY fg_invert (voidptr, int, int);

void     FG_APIENTRY fg_jpegbuf (voidptr, UINT);
int      FG_APIENTRY fg_jpeghead (byteptr, voidptr);
int      FG_APIENTRY fg_jpegmem (voidptr);
void     FG_APIENTRY fg_jpegsize (voidptr, intptr, intptr);
void     FG_APIENTRY fg_justify (int, int);

int      FG_APIENTRY fg_kbtest (int);

int      FG_APIENTRY fg_loadpcx (byteptr, int);
void     FG_APIENTRY fg_locate (int, int);
void     FG_APIENTRY fg_logfont (HFONT);
HPALETTE FG_APIENTRY fg_logpal (int, int, voidptr);

int      FG_APIENTRY fg_makebmp (int, int, int, int, int, byteptr);
int      FG_APIENTRY fg_makepcx (int, int, int, int, byteptr);
int      FG_APIENTRY fg_makeppr (int, int, int, int, byteptr);
int      FG_APIENTRY fg_makespr (int, int, int, int, byteptr);
void     FG_APIENTRY fg_mapdacs (voidptr, voidptr, int);
int      FG_APIENTRY fg_maprgb (int, int, int);
UINT     FG_APIENTRY fg_measure (void);
long     FG_APIENTRY fg_memavail (void);
int      FG_APIENTRY fg_modeset (int, int, int, int);
int      FG_APIENTRY fg_modetest (int, int, int);
void     FG_APIENTRY fg_mousecur (HCURSOR);
int      FG_APIENTRY fg_mouseini (void);
void     FG_APIENTRY fg_mouselim (int, int, int, int);
void     FG_APIENTRY fg_mousemov (int, int);
void     FG_APIENTRY fg_mousepos (intptr, intptr);
HCURSOR  FG_APIENTRY fg_mouseptr (voidptr, int, int);
void     FG_APIENTRY fg_mousesiz (int);
void     FG_APIENTRY fg_mousevis (int);
void     FG_APIENTRY fg_move (int, int);
void     FG_APIENTRY fg_move3d (longptr, long, long, long, int);
void     FG_APIENTRY fg_moverel (int, int);
void     FG_APIENTRY fg_moverw (double, double);
void     FG_APIENTRY fg_movew (double, double);

void     FG_APIENTRY fg_pack (voidptr, voidptr, int, int);
long     FG_APIENTRY fg_pagesize (int, int);
void     FG_APIENTRY fg_paint (int, int);
void     FG_APIENTRY fg_paintw (double, double);
int      FG_APIENTRY fg_pcxhead (byteptr, voidptr);
int      FG_APIENTRY fg_pcxpal (byteptr, voidptr);
void     FG_APIENTRY fg_pcxrange (voidptr, intptr, intptr, intptr, intptr);
void     FG_APIENTRY fg_pcxsize (voidptr, intptr, intptr);
void     FG_APIENTRY fg_point (int, int);
void     FG_APIENTRY fg_pointw (double, double);
void     FG_APIENTRY fg_pointx (int, int);
void     FG_APIENTRY fg_pointxw (double, double);
void     FG_APIENTRY fg_polyedge (int);
void     FG_APIENTRY fg_polyfill (intptr, voidptr, int);
void     FG_APIENTRY fg_polygon (intptr, intptr, int);
void     FG_APIENTRY fg_polygonw (dblptr, dblptr, int);
void     FG_APIENTRY fg_polyline (intptr, int);
void     FG_APIENTRY fg_polyoff (int, int);
void     FG_APIENTRY fg_print (byteptr, int);
int      FG_APIENTRY fg_printer (int);
void     FG_APIENTRY fg_project (longptr, longptr, intptr, int);
void     FG_APIENTRY fg_putblock (voidptr, int, int, int, int);
void     FG_APIENTRY fg_putdcb (voidptr, int, int);
void     FG_APIENTRY fg_putimage (voidptr, int, int);
void     FG_APIENTRY fg_putpixel (int, int);

void     FG_APIENTRY fg_realize (HPALETTE);
void     FG_APIENTRY fg_rect (int, int, int, int);
void     FG_APIENTRY fg_rectw (double, double, double, double);
void     FG_APIENTRY fg_rectx (int, int, int, int);
void     FG_APIENTRY fg_reduce (int, int, voidptr);
void     FG_APIENTRY fg_restore (int, int, int, int);
void     FG_APIENTRY fg_restorew (double, double, double, double);
void     FG_APIENTRY fg_revdcb (voidptr, int, int);
void     FG_APIENTRY fg_revimage (voidptr, int, int);
void     FG_APIENTRY fg_revmask (voidptr, int, int);
void     FG_APIENTRY fg_rotate (voidptr, voidptr, int, int, int);
void     FG_APIENTRY fg_rotate3d (longptr, int, int, int, int);
void     FG_APIENTRY fg_rotdcb (voidptr, voidptr, int, int, int);
void     FG_APIENTRY fg_rotsize (int, int, int, intptr, intptr);

void     FG_APIENTRY fg_save (int, int, int, int);
void     FG_APIENTRY fg_savew (double, double, double, double);
void     FG_APIENTRY fg_scale (voidptr, voidptr, int, int, int, int);
void     FG_APIENTRY fg_scaledcb (voidptr, voidptr, int, int, int, int);
void     FG_APIENTRY fg_scroll (int, int, int, int, int, int);
void     FG_APIENTRY fg_setalpha (int);
void     FG_APIENTRY fg_setangle (double);
void     FG_APIENTRY fg_setclip (int, int, int, int);
void     FG_APIENTRY fg_setclipw (double, double, double, double);
void     FG_APIENTRY fg_setcolor (int);
void     FG_APIENTRY fg_setdacs (int, int, voidptr);
void     FG_APIENTRY fg_setdc (HDC);
void     FG_APIENTRY fg_sethpage (int);
void     FG_APIENTRY fg_setpage (int);
void     FG_APIENTRY fg_setratio (double);
void     FG_APIENTRY fg_setrgb (int, int, int, int);
void     FG_APIENTRY fg_setsize (int);
void     FG_APIENTRY fg_setsizew (double);
void     FG_APIENTRY fg_setview (int, int, int, int, int, int, int, int);
void     FG_APIENTRY fg_setworld (double, double, double, double);
void     FG_APIENTRY fg_shear (voidptr, voidptr, int, int, int, int);
void     FG_APIENTRY fg_sheardcb (voidptr, voidptr, int, int, int, int);
int      FG_APIENTRY fg_showbmp (byteptr, int);
int      FG_APIENTRY fg_showflic (byteptr, int, int);
int      FG_APIENTRY fg_showjpeg (byteptr, int);
int      FG_APIENTRY fg_showpcx (byteptr, int);
int      FG_APIENTRY fg_showppr (byteptr, int);
int      FG_APIENTRY fg_showspr (byteptr, int);
void     FG_APIENTRY fg_stall (int);
void     FG_APIENTRY fg_swchar (byteptr, int, int);
double   FG_APIENTRY fg_swlength (byteptr, int);
void     FG_APIENTRY fg_swtext (byteptr, int, int);

void     FG_APIENTRY fg_tcdefine (int, int);
void     FG_APIENTRY fg_tcmask (int);
void     FG_APIENTRY fg_tcxfer (int, int, int, int, int, int, int, int);
void     FG_APIENTRY fg_texmap (intptr, intptr, int);
void     FG_APIENTRY fg_text (byteptr, int);
void     FG_APIENTRY fg_texture (voidptr, int);
void     FG_APIENTRY fg_transfer (int, int, int, int, int, int, int, int);

void     FG_APIENTRY fg_unmaprgb (int, intptr, intptr, intptr);
void     FG_APIENTRY fg_unpack (voidptr, voidptr, int);

int      FG_APIENTRY fg_vb2clip (int, int, int, int);
long     FG_APIENTRY fg_vbaddr (int);
int      FG_APIENTRY fg_vballoc (int, int);
void     FG_APIENTRY fg_vbclose (void);
void     FG_APIENTRY fg_vbcolors (void);
void     FG_APIENTRY fg_vbcopy (int, int, int, int, int, int, int, int);
int      FG_APIENTRY fg_vbdefine (hugeptr, int, int);
void     FG_APIENTRY fg_vbdepth (int);
void     FG_APIENTRY fg_vbfin (void);
void     FG_APIENTRY fg_vbfree (int);
int      FG_APIENTRY fg_vbhandle (void);
void     FG_APIENTRY fg_vbinit (void);
int      FG_APIENTRY fg_vbopen (int);
void     FG_APIENTRY fg_vbpaste (int, int, int, int, int, int);
void     FG_APIENTRY fg_vbprint (int, int, int, int, int, int, int, int, int);
void     FG_APIENTRY fg_vbscale (int, int, int, int, int, int, int, int);
long     FG_APIENTRY fg_vbsize (int, int);
void     FG_APIENTRY fg_vbtccopy (int, int, int, int, int, int, int, int);
void     FG_APIENTRY fg_vbundef (int);
void     FG_APIENTRY fg_version (intptr, intptr);
void     FG_APIENTRY fg_view3d (int, int, int, int, long);

void     FG_APIENTRY fg_waitfor (int);
void     FG_APIENTRY fg_where (intptr, intptr);

int      FG_APIENTRY fg_xalpha (int);
int      FG_APIENTRY fg_xclient (int);
int      FG_APIENTRY fg_xconvert (int);
int      FG_APIENTRY fg_xscreen (double);
int      FG_APIENTRY fg_xvb (int);
int      FG_APIENTRY fg_xview (int);
double   FG_APIENTRY fg_xworld (int);

int      FG_APIENTRY fg_yalpha (int);
int      FG_APIENTRY fg_yclient (int);
int      FG_APIENTRY fg_yconvert (int);
int      FG_APIENTRY fg_yscreen (double);
int      FG_APIENTRY fg_yvb (int);
int      FG_APIENTRY fg_yview (int);
double   FG_APIENTRY fg_yworld (int);

#ifdef __cplusplus
}
#endif

#endif                     /* of #ifndef __FGWIN_H */
