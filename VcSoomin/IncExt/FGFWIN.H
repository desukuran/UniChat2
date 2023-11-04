/****************************************************************************\
*                                                                            *
*  FGFWIN.H                                                                  *
*                                                                            *
*  This file contains the C and C++ function prototypes for Fastgraph/Fonts  *
*  5.0 for Windows.                                                          *
*                                                                            *
*  Copyright (c) 1992-1997 Ted Gruber Software.  All rights reserved.        *
*                                                                            *
\****************************************************************************/

#ifndef __FGFWIN_H

#define __FGFWIN_H

#ifndef __FGWIN_H
#include <fgwin.h>         /* Include FGWIN.H if not already included */
#endif

#ifdef __cplusplus
extern "C" {
#endif

int  FG_APIENTRY fgf_define (voidptr);
int  FG_APIENTRY fgf_drop (void);
int  FG_APIENTRY fgf_getxjust (void);
int  FG_APIENTRY fgf_getyjust (void);
int  FG_APIENTRY fgf_handle (void);
int  FG_APIENTRY fgf_height (byteptr, int);
void FG_APIENTRY fgf_justify (int, int);
void FG_APIENTRY fgf_kerning (int);
int  FG_APIENTRY fgf_load (byteptr);
void FG_APIENTRY fgf_print (byteptr, int);
void FG_APIENTRY fgf_printc (byteptr, int);
void FG_APIENTRY fgf_select (int);
void FG_APIENTRY fgf_space (int);
void FG_APIENTRY fgf_undefine (int);
void FG_APIENTRY fgf_under (int);
void FG_APIENTRY fgf_unload (int);
void FG_APIENTRY fgf_version (intptr, intptr);
int  FG_APIENTRY fgf_width (byteptr, int);

#ifdef __cplusplus
}
#endif

#endif                     /* of #ifndef __FGFWIN_H */
