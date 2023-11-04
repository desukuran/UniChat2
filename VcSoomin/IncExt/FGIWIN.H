/****************************************************************************\
*                                                                            *
*  FGIWIN.H                                                                  *
*                                                                            *
*  This file contains the C and C++ function prototypes for Fastgraph/Image  *
*  5.0 for Windows.                                                          *
*                                                                            *
*  Copyright (c) 1992-1997 Ted Gruber Software.  All rights reserved.        *
*                                                                            *
\****************************************************************************/

#ifndef __FGIWIN_H

#define __FGIWIN_H

#ifndef __FGWIN_H
#include <fgwin.h>         /* Include FGWIN.H if not already included */
#endif

#ifdef __cplusplus
extern "C" {
#endif

int  FG_APIENTRY fgi_bmphead (byteptr, voidptr, int);
int  FG_APIENTRY fgi_bmppal (byteptr, voidptr, int);
void FG_APIENTRY fgi_close (int);
int  FG_APIENTRY fgi_display (byteptr, int, int);
long FG_APIENTRY fgi_filesize (byteptr, int);
int  FG_APIENTRY fgi_flichead (byteptr, voidptr, int);
int  FG_APIENTRY fgi_flicopen (byteptr, voidptr, int);
int  FG_APIENTRY fgi_flicskip (voidptr, int);
int  FG_APIENTRY fgi_jpeghead (byteptr, voidptr, int);
int  FG_APIENTRY fgi_loadpcx (byteptr, int, int);
int  FG_APIENTRY fgi_open (byteptr);
int  FG_APIENTRY fgi_pcxhead (byteptr, voidptr, int);
int  FG_APIENTRY fgi_pcxpal (byteptr, voidptr, int);
int  FG_APIENTRY fgi_read (byteptr, voidptr, int);
int  FG_APIENTRY fgi_readnext (voidptr, unsigned int, int);
int  FG_APIENTRY fgi_seek (byteptr, int);
int  FG_APIENTRY fgi_showbmp (byteptr, int, int);
int  FG_APIENTRY fgi_showflic (byteptr, int, int, int);
int  FG_APIENTRY fgi_showjpeg (byteptr, int, int);
int  FG_APIENTRY fgi_showpcx (byteptr, int, int);
int  FG_APIENTRY fgi_showppr (byteptr, int);
int  FG_APIENTRY fgi_showspr (byteptr, int);
void FG_APIENTRY fgi_version (intptr, intptr);

#ifdef __cplusplus
}
#endif

#endif                     /* of #ifndef __FGIWIN_H */
