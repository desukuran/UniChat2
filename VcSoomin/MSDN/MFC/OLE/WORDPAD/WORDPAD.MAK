# Microsoft Developer Studio Generated NMAKE File, Based on wordpad.dsp
!IF "$(CFG)" == ""
CFG=WordPad - Win32 Release
!MESSAGE No configuration specified.  Defaulting to WordPad - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "WordPad - Win32 Release" && "$(CFG)" !=\
 "WordPad - Win32 Debug" && "$(CFG)" != "WordPad - Win32 Unicode Release" &&\
 "$(CFG)" != "WordPad - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "wordpad.mak" CFG="WordPad - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WordPad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WordPad - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\wordpad.exe" "$(OUTDIR)\wordpad.bsc"

CLEAN : 
	-@erase "$(INTDIR)\buttondi.obj"
	-@erase "$(INTDIR)\buttondi.sbr"
	-@erase "$(INTDIR)\chicdial.obj"
	-@erase "$(INTDIR)\chicdial.sbr"
	-@erase "$(INTDIR)\cntritem.obj"
	-@erase "$(INTDIR)\cntritem.sbr"
	-@erase "$(INTDIR)\colorlis.obj"
	-@erase "$(INTDIR)\colorlis.sbr"
	-@erase "$(INTDIR)\datedial.obj"
	-@erase "$(INTDIR)\datedial.sbr"
	-@erase "$(INTDIR)\ddxm.obj"
	-@erase "$(INTDIR)\ddxm.sbr"
	-@erase "$(INTDIR)\docopt.obj"
	-@erase "$(INTDIR)\docopt.sbr"
	-@erase "$(INTDIR)\doctype.obj"
	-@erase "$(INTDIR)\doctype.sbr"
	-@erase "$(INTDIR)\filenewd.obj"
	-@erase "$(INTDIR)\filenewd.sbr"
	-@erase "$(INTDIR)\formatba.obj"
	-@erase "$(INTDIR)\formatba.sbr"
	-@erase "$(INTDIR)\formatpa.obj"
	-@erase "$(INTDIR)\formatpa.sbr"
	-@erase "$(INTDIR)\formatta.obj"
	-@erase "$(INTDIR)\formatta.sbr"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\ipframe.sbr"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\key.sbr"
	-@erase "$(INTDIR)\listdlg.obj"
	-@erase "$(INTDIR)\listdlg.sbr"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mainfrm.sbr"
	-@erase "$(INTDIR)\multconv.obj"
	-@erase "$(INTDIR)\multconv.sbr"
	-@erase "$(INTDIR)\options.obj"
	-@erase "$(INTDIR)\options.sbr"
	-@erase "$(INTDIR)\optionsh.obj"
	-@erase "$(INTDIR)\optionsh.sbr"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\pageset.sbr"
	-@erase "$(INTDIR)\ruler.obj"
	-@erase "$(INTDIR)\ruler.sbr"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\splash.sbr"
	-@erase "$(INTDIR)\srvritem.obj"
	-@erase "$(INTDIR)\srvritem.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\strings.obj"
	-@erase "$(INTDIR)\strings.sbr"
	-@erase "$(INTDIR)\unitspag.obj"
	-@erase "$(INTDIR)\unitspag.sbr"
	-@erase "$(INTDIR)\wordpad.obj"
	-@erase "$(INTDIR)\wordpad.pch"
	-@erase "$(INTDIR)\wordpad.res"
	-@erase "$(INTDIR)\wordpad.sbr"
	-@erase "$(INTDIR)\wordpdoc.obj"
	-@erase "$(INTDIR)\wordpdoc.sbr"
	-@erase "$(INTDIR)\wordpvw.obj"
	-@erase "$(INTDIR)\wordpvw.sbr"
	-@erase "$(OUTDIR)\wordpad.bsc"
	-@erase "$(OUTDIR)\wordpad.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(OUTDIR)\WordPad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)

"$(OUTDIR)\WordPad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wordpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wordpad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\buttondi.sbr" \
	"$(INTDIR)\chicdial.sbr" \
	"$(INTDIR)\cntritem.sbr" \
	"$(INTDIR)\colorlis.sbr" \
	"$(INTDIR)\datedial.sbr" \
	"$(INTDIR)\ddxm.sbr" \
	"$(INTDIR)\docopt.sbr" \
	"$(INTDIR)\doctype.sbr" \
	"$(INTDIR)\filenewd.sbr" \
	"$(INTDIR)\formatba.sbr" \
	"$(INTDIR)\formatpa.sbr" \
	"$(INTDIR)\formatta.sbr" \
	"$(INTDIR)\ipframe.sbr" \
	"$(INTDIR)\key.sbr" \
	"$(INTDIR)\listdlg.sbr" \
	"$(INTDIR)\mainfrm.sbr" \
	"$(INTDIR)\multconv.sbr" \
	"$(INTDIR)\options.sbr" \
	"$(INTDIR)\optionsh.sbr" \
	"$(INTDIR)\pageset.sbr" \
	"$(INTDIR)\ruler.sbr" \
	"$(INTDIR)\splash.sbr" \
	"$(INTDIR)\srvritem.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\strings.sbr" \
	"$(INTDIR)\unitspag.sbr" \
	"$(INTDIR)\wordpad.sbr" \
	"$(INTDIR)\wordpdoc.sbr" \
	"$(INTDIR)\wordpvw.sbr"

"$(OUTDIR)\wordpad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/wordpad.pdb" /machine:I386 /out:"$(OUTDIR)/wordpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\buttondi.obj" \
	"$(INTDIR)\chicdial.obj" \
	"$(INTDIR)\cntritem.obj" \
	"$(INTDIR)\colorlis.obj" \
	"$(INTDIR)\datedial.obj" \
	"$(INTDIR)\ddxm.obj" \
	"$(INTDIR)\docopt.obj" \
	"$(INTDIR)\doctype.obj" \
	"$(INTDIR)\filenewd.obj" \
	"$(INTDIR)\formatba.obj" \
	"$(INTDIR)\formatpa.obj" \
	"$(INTDIR)\formatta.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\listdlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\multconv.obj" \
	"$(INTDIR)\options.obj" \
	"$(INTDIR)\optionsh.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\ruler.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\srvritem.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\strings.obj" \
	"$(INTDIR)\unitspag.obj" \
	"$(INTDIR)\wordpad.obj" \
	"$(INTDIR)\wordpad.res" \
	"$(INTDIR)\wordpdoc.obj" \
	"$(INTDIR)\wordpvw.obj"

"$(OUTDIR)\wordpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\wordpad.exe" "$(OUTDIR)\wordpad.bsc"

CLEAN : 
	-@erase "$(INTDIR)\buttondi.obj"
	-@erase "$(INTDIR)\buttondi.sbr"
	-@erase "$(INTDIR)\chicdial.obj"
	-@erase "$(INTDIR)\chicdial.sbr"
	-@erase "$(INTDIR)\cntritem.obj"
	-@erase "$(INTDIR)\cntritem.sbr"
	-@erase "$(INTDIR)\colorlis.obj"
	-@erase "$(INTDIR)\colorlis.sbr"
	-@erase "$(INTDIR)\datedial.obj"
	-@erase "$(INTDIR)\datedial.sbr"
	-@erase "$(INTDIR)\ddxm.obj"
	-@erase "$(INTDIR)\ddxm.sbr"
	-@erase "$(INTDIR)\docopt.obj"
	-@erase "$(INTDIR)\docopt.sbr"
	-@erase "$(INTDIR)\doctype.obj"
	-@erase "$(INTDIR)\doctype.sbr"
	-@erase "$(INTDIR)\filenewd.obj"
	-@erase "$(INTDIR)\filenewd.sbr"
	-@erase "$(INTDIR)\formatba.obj"
	-@erase "$(INTDIR)\formatba.sbr"
	-@erase "$(INTDIR)\formatpa.obj"
	-@erase "$(INTDIR)\formatpa.sbr"
	-@erase "$(INTDIR)\formatta.obj"
	-@erase "$(INTDIR)\formatta.sbr"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\ipframe.sbr"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\key.sbr"
	-@erase "$(INTDIR)\listdlg.obj"
	-@erase "$(INTDIR)\listdlg.sbr"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mainfrm.sbr"
	-@erase "$(INTDIR)\multconv.obj"
	-@erase "$(INTDIR)\multconv.sbr"
	-@erase "$(INTDIR)\options.obj"
	-@erase "$(INTDIR)\options.sbr"
	-@erase "$(INTDIR)\optionsh.obj"
	-@erase "$(INTDIR)\optionsh.sbr"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\pageset.sbr"
	-@erase "$(INTDIR)\ruler.obj"
	-@erase "$(INTDIR)\ruler.sbr"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\splash.sbr"
	-@erase "$(INTDIR)\srvritem.obj"
	-@erase "$(INTDIR)\srvritem.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\strings.obj"
	-@erase "$(INTDIR)\strings.sbr"
	-@erase "$(INTDIR)\unitspag.obj"
	-@erase "$(INTDIR)\unitspag.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wordpad.obj"
	-@erase "$(INTDIR)\wordpad.pch"
	-@erase "$(INTDIR)\wordpad.res"
	-@erase "$(INTDIR)\wordpad.sbr"
	-@erase "$(INTDIR)\wordpdoc.obj"
	-@erase "$(INTDIR)\wordpdoc.sbr"
	-@erase "$(INTDIR)\wordpvw.obj"
	-@erase "$(INTDIR)\wordpvw.sbr"
	-@erase "$(OUTDIR)\wordpad.bsc"
	-@erase "$(OUTDIR)\wordpad.exe"
	-@erase "$(OUTDIR)\wordpad.ilk"
	-@erase "$(OUTDIR)\wordpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(OUTDIR)\WordPad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)

"$(OUTDIR)\WordPad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wordpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wordpad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\buttondi.sbr" \
	"$(INTDIR)\chicdial.sbr" \
	"$(INTDIR)\cntritem.sbr" \
	"$(INTDIR)\colorlis.sbr" \
	"$(INTDIR)\datedial.sbr" \
	"$(INTDIR)\ddxm.sbr" \
	"$(INTDIR)\docopt.sbr" \
	"$(INTDIR)\doctype.sbr" \
	"$(INTDIR)\filenewd.sbr" \
	"$(INTDIR)\formatba.sbr" \
	"$(INTDIR)\formatpa.sbr" \
	"$(INTDIR)\formatta.sbr" \
	"$(INTDIR)\ipframe.sbr" \
	"$(INTDIR)\key.sbr" \
	"$(INTDIR)\listdlg.sbr" \
	"$(INTDIR)\mainfrm.sbr" \
	"$(INTDIR)\multconv.sbr" \
	"$(INTDIR)\options.sbr" \
	"$(INTDIR)\optionsh.sbr" \
	"$(INTDIR)\pageset.sbr" \
	"$(INTDIR)\ruler.sbr" \
	"$(INTDIR)\splash.sbr" \
	"$(INTDIR)\srvritem.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\strings.sbr" \
	"$(INTDIR)\unitspag.sbr" \
	"$(INTDIR)\wordpad.sbr" \
	"$(INTDIR)\wordpdoc.sbr" \
	"$(INTDIR)\wordpvw.sbr"

"$(OUTDIR)\wordpad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/wordpad.pdb" /debug /machine:I386 /out:"$(OUTDIR)/wordpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\buttondi.obj" \
	"$(INTDIR)\chicdial.obj" \
	"$(INTDIR)\cntritem.obj" \
	"$(INTDIR)\colorlis.obj" \
	"$(INTDIR)\datedial.obj" \
	"$(INTDIR)\ddxm.obj" \
	"$(INTDIR)\docopt.obj" \
	"$(INTDIR)\doctype.obj" \
	"$(INTDIR)\filenewd.obj" \
	"$(INTDIR)\formatba.obj" \
	"$(INTDIR)\formatpa.obj" \
	"$(INTDIR)\formatta.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\listdlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\multconv.obj" \
	"$(INTDIR)\options.obj" \
	"$(INTDIR)\optionsh.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\ruler.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\srvritem.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\strings.obj" \
	"$(INTDIR)\unitspag.obj" \
	"$(INTDIR)\wordpad.obj" \
	"$(INTDIR)\wordpad.res" \
	"$(INTDIR)\wordpdoc.obj" \
	"$(INTDIR)\wordpvw.obj"

"$(OUTDIR)\wordpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\wordpad.exe" "$(OUTDIR)\wordpad.bsc"

CLEAN : 
	-@erase "$(INTDIR)\buttondi.obj"
	-@erase "$(INTDIR)\buttondi.sbr"
	-@erase "$(INTDIR)\chicdial.obj"
	-@erase "$(INTDIR)\chicdial.sbr"
	-@erase "$(INTDIR)\cntritem.obj"
	-@erase "$(INTDIR)\cntritem.sbr"
	-@erase "$(INTDIR)\colorlis.obj"
	-@erase "$(INTDIR)\colorlis.sbr"
	-@erase "$(INTDIR)\datedial.obj"
	-@erase "$(INTDIR)\datedial.sbr"
	-@erase "$(INTDIR)\ddxm.obj"
	-@erase "$(INTDIR)\ddxm.sbr"
	-@erase "$(INTDIR)\docopt.obj"
	-@erase "$(INTDIR)\docopt.sbr"
	-@erase "$(INTDIR)\doctype.obj"
	-@erase "$(INTDIR)\doctype.sbr"
	-@erase "$(INTDIR)\filenewd.obj"
	-@erase "$(INTDIR)\filenewd.sbr"
	-@erase "$(INTDIR)\formatba.obj"
	-@erase "$(INTDIR)\formatba.sbr"
	-@erase "$(INTDIR)\formatpa.obj"
	-@erase "$(INTDIR)\formatpa.sbr"
	-@erase "$(INTDIR)\formatta.obj"
	-@erase "$(INTDIR)\formatta.sbr"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\ipframe.sbr"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\key.sbr"
	-@erase "$(INTDIR)\listdlg.obj"
	-@erase "$(INTDIR)\listdlg.sbr"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mainfrm.sbr"
	-@erase "$(INTDIR)\multconv.obj"
	-@erase "$(INTDIR)\multconv.sbr"
	-@erase "$(INTDIR)\options.obj"
	-@erase "$(INTDIR)\options.sbr"
	-@erase "$(INTDIR)\optionsh.obj"
	-@erase "$(INTDIR)\optionsh.sbr"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\pageset.sbr"
	-@erase "$(INTDIR)\ruler.obj"
	-@erase "$(INTDIR)\ruler.sbr"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\splash.sbr"
	-@erase "$(INTDIR)\srvritem.obj"
	-@erase "$(INTDIR)\srvritem.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\strings.obj"
	-@erase "$(INTDIR)\strings.sbr"
	-@erase "$(INTDIR)\unitspag.obj"
	-@erase "$(INTDIR)\unitspag.sbr"
	-@erase "$(INTDIR)\wordpad.obj"
	-@erase "$(INTDIR)\wordpad.pch"
	-@erase "$(INTDIR)\wordpad.res"
	-@erase "$(INTDIR)\wordpad.sbr"
	-@erase "$(INTDIR)\wordpdoc.obj"
	-@erase "$(INTDIR)\wordpdoc.sbr"
	-@erase "$(INTDIR)\wordpvw.obj"
	-@erase "$(INTDIR)\wordpvw.sbr"
	-@erase "$(OUTDIR)\wordpad.bsc"
	-@erase "$(OUTDIR)\wordpad.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniRelease/
CPP_SBRS=.\UniRelease/
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wordpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wordpad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\buttondi.sbr" \
	"$(INTDIR)\chicdial.sbr" \
	"$(INTDIR)\cntritem.sbr" \
	"$(INTDIR)\colorlis.sbr" \
	"$(INTDIR)\datedial.sbr" \
	"$(INTDIR)\ddxm.sbr" \
	"$(INTDIR)\docopt.sbr" \
	"$(INTDIR)\doctype.sbr" \
	"$(INTDIR)\filenewd.sbr" \
	"$(INTDIR)\formatba.sbr" \
	"$(INTDIR)\formatpa.sbr" \
	"$(INTDIR)\formatta.sbr" \
	"$(INTDIR)\ipframe.sbr" \
	"$(INTDIR)\key.sbr" \
	"$(INTDIR)\listdlg.sbr" \
	"$(INTDIR)\mainfrm.sbr" \
	"$(INTDIR)\multconv.sbr" \
	"$(INTDIR)\options.sbr" \
	"$(INTDIR)\optionsh.sbr" \
	"$(INTDIR)\pageset.sbr" \
	"$(INTDIR)\ruler.sbr" \
	"$(INTDIR)\splash.sbr" \
	"$(INTDIR)\srvritem.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\strings.sbr" \
	"$(INTDIR)\unitspag.sbr" \
	"$(INTDIR)\wordpad.sbr" \
	"$(INTDIR)\wordpdoc.sbr" \
	"$(INTDIR)\wordpvw.sbr"

"$(OUTDIR)\wordpad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/wordpad.pdb" /machine:I386\
 /out:"$(OUTDIR)/wordpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\buttondi.obj" \
	"$(INTDIR)\chicdial.obj" \
	"$(INTDIR)\cntritem.obj" \
	"$(INTDIR)\colorlis.obj" \
	"$(INTDIR)\datedial.obj" \
	"$(INTDIR)\ddxm.obj" \
	"$(INTDIR)\docopt.obj" \
	"$(INTDIR)\doctype.obj" \
	"$(INTDIR)\filenewd.obj" \
	"$(INTDIR)\formatba.obj" \
	"$(INTDIR)\formatpa.obj" \
	"$(INTDIR)\formatta.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\listdlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\multconv.obj" \
	"$(INTDIR)\options.obj" \
	"$(INTDIR)\optionsh.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\ruler.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\srvritem.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\strings.obj" \
	"$(INTDIR)\unitspag.obj" \
	"$(INTDIR)\wordpad.obj" \
	"$(INTDIR)\wordpad.res" \
	"$(INTDIR)\wordpdoc.obj" \
	"$(INTDIR)\wordpvw.obj"

"$(OUTDIR)\wordpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\wordpad.exe" "$(OUTDIR)\wordpad.bsc"

CLEAN : 
	-@erase "$(INTDIR)\buttondi.obj"
	-@erase "$(INTDIR)\buttondi.sbr"
	-@erase "$(INTDIR)\chicdial.obj"
	-@erase "$(INTDIR)\chicdial.sbr"
	-@erase "$(INTDIR)\cntritem.obj"
	-@erase "$(INTDIR)\cntritem.sbr"
	-@erase "$(INTDIR)\colorlis.obj"
	-@erase "$(INTDIR)\colorlis.sbr"
	-@erase "$(INTDIR)\datedial.obj"
	-@erase "$(INTDIR)\datedial.sbr"
	-@erase "$(INTDIR)\ddxm.obj"
	-@erase "$(INTDIR)\ddxm.sbr"
	-@erase "$(INTDIR)\docopt.obj"
	-@erase "$(INTDIR)\docopt.sbr"
	-@erase "$(INTDIR)\doctype.obj"
	-@erase "$(INTDIR)\doctype.sbr"
	-@erase "$(INTDIR)\filenewd.obj"
	-@erase "$(INTDIR)\filenewd.sbr"
	-@erase "$(INTDIR)\formatba.obj"
	-@erase "$(INTDIR)\formatba.sbr"
	-@erase "$(INTDIR)\formatpa.obj"
	-@erase "$(INTDIR)\formatpa.sbr"
	-@erase "$(INTDIR)\formatta.obj"
	-@erase "$(INTDIR)\formatta.sbr"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\ipframe.sbr"
	-@erase "$(INTDIR)\key.obj"
	-@erase "$(INTDIR)\key.sbr"
	-@erase "$(INTDIR)\listdlg.obj"
	-@erase "$(INTDIR)\listdlg.sbr"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mainfrm.sbr"
	-@erase "$(INTDIR)\multconv.obj"
	-@erase "$(INTDIR)\multconv.sbr"
	-@erase "$(INTDIR)\options.obj"
	-@erase "$(INTDIR)\options.sbr"
	-@erase "$(INTDIR)\optionsh.obj"
	-@erase "$(INTDIR)\optionsh.sbr"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\pageset.sbr"
	-@erase "$(INTDIR)\ruler.obj"
	-@erase "$(INTDIR)\ruler.sbr"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\splash.sbr"
	-@erase "$(INTDIR)\srvritem.obj"
	-@erase "$(INTDIR)\srvritem.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\strings.obj"
	-@erase "$(INTDIR)\strings.sbr"
	-@erase "$(INTDIR)\unitspag.obj"
	-@erase "$(INTDIR)\unitspag.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wordpad.obj"
	-@erase "$(INTDIR)\wordpad.pch"
	-@erase "$(INTDIR)\wordpad.res"
	-@erase "$(INTDIR)\wordpad.sbr"
	-@erase "$(INTDIR)\wordpdoc.obj"
	-@erase "$(INTDIR)\wordpdoc.sbr"
	-@erase "$(INTDIR)\wordpvw.obj"
	-@erase "$(INTDIR)\wordpvw.sbr"
	-@erase "$(OUTDIR)\wordpad.bsc"
	-@erase "$(OUTDIR)\wordpad.exe"
	-@erase "$(OUTDIR)\wordpad.ilk"
	-@erase "$(OUTDIR)\wordpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/wordpad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c\
 
CPP_OBJS=.\UniDebug/
CPP_SBRS=.\UniDebug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/wordpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wordpad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\buttondi.sbr" \
	"$(INTDIR)\chicdial.sbr" \
	"$(INTDIR)\cntritem.sbr" \
	"$(INTDIR)\colorlis.sbr" \
	"$(INTDIR)\datedial.sbr" \
	"$(INTDIR)\ddxm.sbr" \
	"$(INTDIR)\docopt.sbr" \
	"$(INTDIR)\doctype.sbr" \
	"$(INTDIR)\filenewd.sbr" \
	"$(INTDIR)\formatba.sbr" \
	"$(INTDIR)\formatpa.sbr" \
	"$(INTDIR)\formatta.sbr" \
	"$(INTDIR)\ipframe.sbr" \
	"$(INTDIR)\key.sbr" \
	"$(INTDIR)\listdlg.sbr" \
	"$(INTDIR)\mainfrm.sbr" \
	"$(INTDIR)\multconv.sbr" \
	"$(INTDIR)\options.sbr" \
	"$(INTDIR)\optionsh.sbr" \
	"$(INTDIR)\pageset.sbr" \
	"$(INTDIR)\ruler.sbr" \
	"$(INTDIR)\splash.sbr" \
	"$(INTDIR)\srvritem.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\strings.sbr" \
	"$(INTDIR)\unitspag.sbr" \
	"$(INTDIR)\wordpad.sbr" \
	"$(INTDIR)\wordpdoc.sbr" \
	"$(INTDIR)\wordpvw.sbr"

"$(OUTDIR)\wordpad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/wordpad.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/wordpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\buttondi.obj" \
	"$(INTDIR)\chicdial.obj" \
	"$(INTDIR)\cntritem.obj" \
	"$(INTDIR)\colorlis.obj" \
	"$(INTDIR)\datedial.obj" \
	"$(INTDIR)\ddxm.obj" \
	"$(INTDIR)\docopt.obj" \
	"$(INTDIR)\doctype.obj" \
	"$(INTDIR)\filenewd.obj" \
	"$(INTDIR)\formatba.obj" \
	"$(INTDIR)\formatpa.obj" \
	"$(INTDIR)\formatta.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\key.obj" \
	"$(INTDIR)\listdlg.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\multconv.obj" \
	"$(INTDIR)\options.obj" \
	"$(INTDIR)\optionsh.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\ruler.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\srvritem.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\strings.obj" \
	"$(INTDIR)\unitspag.obj" \
	"$(INTDIR)\wordpad.obj" \
	"$(INTDIR)\wordpad.res" \
	"$(INTDIR)\wordpdoc.obj" \
	"$(INTDIR)\wordpvw.obj"

"$(OUTDIR)\wordpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  


!IF "$(CFG)" == "WordPad - Win32 Release" || "$(CFG)" ==\
 "WordPad - Win32 Debug" || "$(CFG)" == "WordPad - Win32 Unicode Release" ||\
 "$(CFG)" == "WordPad - Win32 Unicode Debug"
SOURCE=.\buttondi.cpp
DEP_CPP_BUTTO=\
	".\buttondi.h"\
	".\chicdial.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\buttondi.obj"	"$(INTDIR)\buttondi.sbr" : $(SOURCE) $(DEP_CPP_BUTTO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\buttondi.obj"	"$(INTDIR)\buttondi.sbr" : $(SOURCE) $(DEP_CPP_BUTTO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\buttondi.obj"	"$(INTDIR)\buttondi.sbr" : $(SOURCE) $(DEP_CPP_BUTTO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\buttondi.obj"	"$(INTDIR)\buttondi.sbr" : $(SOURCE) $(DEP_CPP_BUTTO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\chicdial.cpp
DEP_CPP_CHICD=\
	".\chicdial.h"\
	".\doctype.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\chicdial.obj"	"$(INTDIR)\chicdial.sbr" : $(SOURCE) $(DEP_CPP_CHICD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\chicdial.obj"	"$(INTDIR)\chicdial.sbr" : $(SOURCE) $(DEP_CPP_CHICD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\chicdial.obj"	"$(INTDIR)\chicdial.sbr" : $(SOURCE) $(DEP_CPP_CHICD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\chicdial.obj"	"$(INTDIR)\chicdial.sbr" : $(SOURCE) $(DEP_CPP_CHICD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\cntritem.cpp
DEP_CPP_CNTRI=\
	".\chicdial.h"\
	".\cntritem.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\cntritem.obj"	"$(INTDIR)\cntritem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\cntritem.obj"	"$(INTDIR)\cntritem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\cntritem.obj"	"$(INTDIR)\cntritem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\cntritem.obj"	"$(INTDIR)\cntritem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\colorlis.cpp
DEP_CPP_COLOR=\
	".\chicdial.h"\
	".\colorlis.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\colorlis.obj"	"$(INTDIR)\colorlis.sbr" : $(SOURCE) $(DEP_CPP_COLOR)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\colorlis.obj"	"$(INTDIR)\colorlis.sbr" : $(SOURCE) $(DEP_CPP_COLOR)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\colorlis.obj"	"$(INTDIR)\colorlis.sbr" : $(SOURCE) $(DEP_CPP_COLOR)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\colorlis.obj"	"$(INTDIR)\colorlis.sbr" : $(SOURCE) $(DEP_CPP_COLOR)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\datedial.cpp
DEP_CPP_DATED=\
	".\chicdial.h"\
	".\datedial.h"\
	".\doctype.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\datedial.obj"	"$(INTDIR)\datedial.sbr" : $(SOURCE) $(DEP_CPP_DATED)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\datedial.obj"	"$(INTDIR)\datedial.sbr" : $(SOURCE) $(DEP_CPP_DATED)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\datedial.obj"	"$(INTDIR)\datedial.sbr" : $(SOURCE) $(DEP_CPP_DATED)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\datedial.obj"	"$(INTDIR)\datedial.sbr" : $(SOURCE) $(DEP_CPP_DATED)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\ddxm.cpp
DEP_CPP_DDXM_=\
	".\chicdial.h"\
	".\ddxm.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\ddxm.obj"	"$(INTDIR)\ddxm.sbr" : $(SOURCE) $(DEP_CPP_DDXM_)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\ddxm.obj"	"$(INTDIR)\ddxm.sbr" : $(SOURCE) $(DEP_CPP_DDXM_)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\ddxm.obj"	"$(INTDIR)\ddxm.sbr" : $(SOURCE) $(DEP_CPP_DDXM_)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\ddxm.obj"	"$(INTDIR)\ddxm.sbr" : $(SOURCE) $(DEP_CPP_DDXM_)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\docopt.cpp
DEP_CPP_DOCOP=\
	".\chicdial.h"\
	".\docopt.h"\
	".\doctype.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\docopt.obj"	"$(INTDIR)\docopt.sbr" : $(SOURCE) $(DEP_CPP_DOCOP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\docopt.obj"	"$(INTDIR)\docopt.sbr" : $(SOURCE) $(DEP_CPP_DOCOP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\docopt.obj"	"$(INTDIR)\docopt.sbr" : $(SOURCE) $(DEP_CPP_DOCOP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\docopt.obj"	"$(INTDIR)\docopt.sbr" : $(SOURCE) $(DEP_CPP_DOCOP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\doctype.cpp
DEP_CPP_DOCTY=\
	".\chicdial.h"\
	".\doctype.h"\
	".\multconv.h"\
	".\stdafx.h"\
	".\strings.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\doctype.obj"	"$(INTDIR)\doctype.sbr" : $(SOURCE) $(DEP_CPP_DOCTY)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\doctype.obj"	"$(INTDIR)\doctype.sbr" : $(SOURCE) $(DEP_CPP_DOCTY)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\doctype.obj"	"$(INTDIR)\doctype.sbr" : $(SOURCE) $(DEP_CPP_DOCTY)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\doctype.obj"	"$(INTDIR)\doctype.sbr" : $(SOURCE) $(DEP_CPP_DOCTY)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\filenewd.cpp
DEP_CPP_FILEN=\
	".\chicdial.h"\
	".\doctype.h"\
	".\filenewd.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\filenewd.obj"	"$(INTDIR)\filenewd.sbr" : $(SOURCE) $(DEP_CPP_FILEN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\filenewd.obj"	"$(INTDIR)\filenewd.sbr" : $(SOURCE) $(DEP_CPP_FILEN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\filenewd.obj"	"$(INTDIR)\filenewd.sbr" : $(SOURCE) $(DEP_CPP_FILEN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\filenewd.obj"	"$(INTDIR)\filenewd.sbr" : $(SOURCE) $(DEP_CPP_FILEN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\formatba.cpp
DEP_CPP_FORMA=\
	".\chicdial.h"\
	".\doctype.h"\
	".\formatba.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\formatba.obj"	"$(INTDIR)\formatba.sbr" : $(SOURCE) $(DEP_CPP_FORMA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\formatba.obj"	"$(INTDIR)\formatba.sbr" : $(SOURCE) $(DEP_CPP_FORMA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\formatba.obj"	"$(INTDIR)\formatba.sbr" : $(SOURCE) $(DEP_CPP_FORMA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\formatba.obj"	"$(INTDIR)\formatba.sbr" : $(SOURCE) $(DEP_CPP_FORMA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\formatpa.cpp
DEP_CPP_FORMAT=\
	".\chicdial.h"\
	".\ddxm.h"\
	".\doctype.h"\
	".\formatpa.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\formatpa.obj"	"$(INTDIR)\formatpa.sbr" : $(SOURCE) $(DEP_CPP_FORMAT)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\formatpa.obj"	"$(INTDIR)\formatpa.sbr" : $(SOURCE) $(DEP_CPP_FORMAT)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\formatpa.obj"	"$(INTDIR)\formatpa.sbr" : $(SOURCE) $(DEP_CPP_FORMAT)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\formatpa.obj"	"$(INTDIR)\formatpa.sbr" : $(SOURCE) $(DEP_CPP_FORMAT)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\formatta.cpp
DEP_CPP_FORMATT=\
	".\chicdial.h"\
	".\ddxm.h"\
	".\doctype.h"\
	".\formatta.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\formatta.obj"	"$(INTDIR)\formatta.sbr" : $(SOURCE)\
 $(DEP_CPP_FORMATT) "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\formatta.obj"	"$(INTDIR)\formatta.sbr" : $(SOURCE)\
 $(DEP_CPP_FORMATT) "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\formatta.obj"	"$(INTDIR)\formatta.sbr" : $(SOURCE)\
 $(DEP_CPP_FORMATT) "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\formatta.obj"	"$(INTDIR)\formatta.sbr" : $(SOURCE)\
 $(DEP_CPP_FORMATT) "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\ipframe.cpp
DEP_CPP_IPFRA=\
	".\chicdial.h"\
	".\colorlis.h"\
	".\doctype.h"\
	".\formatba.h"\
	".\ipframe.h"\
	".\options.h"\
	".\ruler.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\ipframe.obj"	"$(INTDIR)\ipframe.sbr" : $(SOURCE) $(DEP_CPP_IPFRA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\ipframe.obj"	"$(INTDIR)\ipframe.sbr" : $(SOURCE) $(DEP_CPP_IPFRA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\ipframe.obj"	"$(INTDIR)\ipframe.sbr" : $(SOURCE) $(DEP_CPP_IPFRA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\ipframe.obj"	"$(INTDIR)\ipframe.sbr" : $(SOURCE) $(DEP_CPP_IPFRA)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\key.cpp
DEP_CPP_KEY_C=\
	".\chicdial.h"\
	".\doctype.h"\
	".\key.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\key.obj"	"$(INTDIR)\key.sbr" : $(SOURCE) $(DEP_CPP_KEY_C)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\key.obj"	"$(INTDIR)\key.sbr" : $(SOURCE) $(DEP_CPP_KEY_C)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\key.obj"	"$(INTDIR)\key.sbr" : $(SOURCE) $(DEP_CPP_KEY_C)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\key.obj"	"$(INTDIR)\key.sbr" : $(SOURCE) $(DEP_CPP_KEY_C)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\listdlg.cpp
DEP_CPP_LISTD=\
	".\chicdial.h"\
	".\doctype.h"\
	".\listdlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\listdlg.obj"	"$(INTDIR)\listdlg.sbr" : $(SOURCE) $(DEP_CPP_LISTD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\listdlg.obj"	"$(INTDIR)\listdlg.sbr" : $(SOURCE) $(DEP_CPP_LISTD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\listdlg.obj"	"$(INTDIR)\listdlg.sbr" : $(SOURCE) $(DEP_CPP_LISTD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\listdlg.obj"	"$(INTDIR)\listdlg.sbr" : $(SOURCE) $(DEP_CPP_LISTD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\chicdial.h"\
	".\colorlis.h"\
	".\doctype.h"\
	".\formatba.h"\
	".\mainfrm.h"\
	".\options.h"\
	".\ruler.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\mainfrm.obj"	"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\mainfrm.obj"	"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\mainfrm.obj"	"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\mainfrm.obj"	"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\multconv.cpp
DEP_CPP_MULTC=\
	".\chicdial.h"\
	".\doctype.h"\
	".\mswd6_32.h"\
	".\multconv.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\multconv.obj"	"$(INTDIR)\multconv.sbr" : $(SOURCE) $(DEP_CPP_MULTC)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\multconv.obj"	"$(INTDIR)\multconv.sbr" : $(SOURCE) $(DEP_CPP_MULTC)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\multconv.obj"	"$(INTDIR)\multconv.sbr" : $(SOURCE) $(DEP_CPP_MULTC)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\multconv.obj"	"$(INTDIR)\multconv.sbr" : $(SOURCE) $(DEP_CPP_MULTC)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\options.cpp
DEP_CPP_OPTIO=\
	".\chicdial.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\options.obj"	"$(INTDIR)\options.sbr" : $(SOURCE) $(DEP_CPP_OPTIO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\options.obj"	"$(INTDIR)\options.sbr" : $(SOURCE) $(DEP_CPP_OPTIO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\options.obj"	"$(INTDIR)\options.sbr" : $(SOURCE) $(DEP_CPP_OPTIO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\options.obj"	"$(INTDIR)\options.sbr" : $(SOURCE) $(DEP_CPP_OPTIO)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\optionsh.cpp
DEP_CPP_OPTION=\
	".\chicdial.h"\
	".\docopt.h"\
	".\doctype.h"\
	".\options.h"\
	".\optionsh.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\unitspag.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\optionsh.obj"	"$(INTDIR)\optionsh.sbr" : $(SOURCE) $(DEP_CPP_OPTION)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\optionsh.obj"	"$(INTDIR)\optionsh.sbr" : $(SOURCE) $(DEP_CPP_OPTION)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\optionsh.obj"	"$(INTDIR)\optionsh.sbr" : $(SOURCE) $(DEP_CPP_OPTION)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\optionsh.obj"	"$(INTDIR)\optionsh.sbr" : $(SOURCE) $(DEP_CPP_OPTION)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\pageset.cpp
DEP_CPP_PAGES=\
	".\chicdial.h"\
	".\ddxm.h"\
	".\doctype.h"\
	".\helpids.h"\
	".\options.h"\
	".\pageset.h"\
	".\ruler.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\pageset.obj"	"$(INTDIR)\pageset.sbr" : $(SOURCE) $(DEP_CPP_PAGES)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\pageset.obj"	"$(INTDIR)\pageset.sbr" : $(SOURCE) $(DEP_CPP_PAGES)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\pageset.obj"	"$(INTDIR)\pageset.sbr" : $(SOURCE) $(DEP_CPP_PAGES)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\pageset.obj"	"$(INTDIR)\pageset.sbr" : $(SOURCE) $(DEP_CPP_PAGES)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\ruler.cpp
DEP_CPP_RULER=\
	".\chicdial.h"\
	".\doctype.h"\
	".\options.h"\
	".\ruler.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\ruler.obj"	"$(INTDIR)\ruler.sbr" : $(SOURCE) $(DEP_CPP_RULER)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\ruler.obj"	"$(INTDIR)\ruler.sbr" : $(SOURCE) $(DEP_CPP_RULER)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\ruler.obj"	"$(INTDIR)\ruler.sbr" : $(SOURCE) $(DEP_CPP_RULER)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\ruler.obj"	"$(INTDIR)\ruler.sbr" : $(SOURCE) $(DEP_CPP_RULER)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\splash.cpp
DEP_CPP_SPLAS=\
	".\chicdial.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\splash.obj"	"$(INTDIR)\splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\splash.obj"	"$(INTDIR)\splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\splash.obj"	"$(INTDIR)\splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\splash.obj"	"$(INTDIR)\splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\srvritem.cpp
DEP_CPP_SRVRI=\
	".\chicdial.h"\
	".\doctype.h"\
	".\options.h"\
	".\splash.h"\
	".\srvritem.h"\
	".\stdafx.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\srvritem.obj"	"$(INTDIR)\srvritem.sbr" : $(SOURCE) $(DEP_CPP_SRVRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\srvritem.obj"	"$(INTDIR)\srvritem.sbr" : $(SOURCE) $(DEP_CPP_SRVRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\srvritem.obj"	"$(INTDIR)\srvritem.sbr" : $(SOURCE) $(DEP_CPP_SRVRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\srvritem.obj"	"$(INTDIR)\srvritem.sbr" : $(SOURCE) $(DEP_CPP_SRVRI)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\chicdial.h"\
	".\doctype.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\wordpad.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\wordpad.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\wordpad.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wordpad.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\wordpad.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/wordpad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c\
 $(SOURCE)


!ENDIF 

SOURCE=.\strings.cpp
DEP_CPP_STRIN=\
	".\chicdial.h"\
	".\doctype.h"\
	".\stdafx.h"\
	".\strings.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\strings.obj"	"$(INTDIR)\strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\strings.obj"	"$(INTDIR)\strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\strings.obj"	"$(INTDIR)\strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\strings.obj"	"$(INTDIR)\strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\unitspag.cpp
DEP_CPP_UNITS=\
	".\chicdial.h"\
	".\doctype.h"\
	".\helpids.h"\
	".\options.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\unitspag.h"\
	".\wordpad.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\unitspag.obj"	"$(INTDIR)\unitspag.sbr" : $(SOURCE) $(DEP_CPP_UNITS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\unitspag.obj"	"$(INTDIR)\unitspag.sbr" : $(SOURCE) $(DEP_CPP_UNITS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\unitspag.obj"	"$(INTDIR)\unitspag.sbr" : $(SOURCE) $(DEP_CPP_UNITS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\unitspag.obj"	"$(INTDIR)\unitspag.sbr" : $(SOURCE) $(DEP_CPP_UNITS)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\wordpad.cpp
DEP_CPP_WORDP=\
	".\chicdial.h"\
	".\doctype.h"\
	".\filenewd.h"\
	".\formatba.h"\
	".\ipframe.h"\
	".\key.h"\
	".\mainfrm.h"\
	".\options.h"\
	".\ruler.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\wordpad.obj"	"$(INTDIR)\wordpad.sbr" : $(SOURCE) $(DEP_CPP_WORDP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\wordpad.obj"	"$(INTDIR)\wordpad.sbr" : $(SOURCE) $(DEP_CPP_WORDP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\wordpad.obj"	"$(INTDIR)\wordpad.sbr" : $(SOURCE) $(DEP_CPP_WORDP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\wordpad.obj"	"$(INTDIR)\wordpad.sbr" : $(SOURCE) $(DEP_CPP_WORDP)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\wordpad.rc
DEP_RSC_WORDPA=\
	".\res\font.bmp"\
	".\res\formatba.bmp"\
	".\res\formatbg.bmp"\
	".\res\main1.bmp"\
	".\res\main1b.bmp"\
	".\res\rtfdoc.ico"\
	".\res\rulerbl.bmp"\
	".\res\rulerblm.bmp"\
	".\res\rulerdo.bmp"\
	".\res\rulerdom.bmp"\
	".\res\rulerta.bmp"\
	".\res\rulertam.bmp"\
	".\res\rulerup.bmp"\
	".\res\rulerupm.bmp"\
	".\res\srvr.bmp"\
	".\res\srvrbig.bmp"\
	".\res\textdoc.ico"\
	".\res\wordp48.bmp"\
	".\res\wordpad.ico"\
	".\res\wordpad.rc2"\
	".\res\write.ico"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\wordpad.res" : $(SOURCE) $(DEP_RSC_WORDPA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\wordpad.res" : $(SOURCE) $(DEP_RSC_WORDPA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\wordpad.res" : $(SOURCE) $(DEP_RSC_WORDPA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\wordpad.res" : $(SOURCE) $(DEP_RSC_WORDPA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\wordpdoc.cpp
DEP_CPP_WORDPD=\
	".\buttondi.h"\
	".\chicdial.h"\
	".\cntritem.h"\
	".\docopt.h"\
	".\doctype.h"\
	".\formatba.h"\
	".\helpids.h"\
	".\ipframe.h"\
	".\mainfrm.h"\
	".\multconv.h"\
	".\options.h"\
	".\optionsh.h"\
	".\ruler.h"\
	".\splash.h"\
	".\srvritem.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\unitspag.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\wordpdoc.obj"	"$(INTDIR)\wordpdoc.sbr" : $(SOURCE) $(DEP_CPP_WORDPD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\wordpdoc.obj"	"$(INTDIR)\wordpdoc.sbr" : $(SOURCE) $(DEP_CPP_WORDPD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\wordpdoc.obj"	"$(INTDIR)\wordpdoc.sbr" : $(SOURCE) $(DEP_CPP_WORDPD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\wordpdoc.obj"	"$(INTDIR)\wordpdoc.sbr" : $(SOURCE) $(DEP_CPP_WORDPD)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\wordpvw.cpp
DEP_CPP_WORDPV=\
	".\chicdial.h"\
	".\cntritem.h"\
	".\colorlis.h"\
	".\datedial.h"\
	".\doctype.h"\
	".\formatba.h"\
	".\formatpa.h"\
	".\formatta.h"\
	".\options.h"\
	".\pageset.h"\
	".\ruler.h"\
	".\splash.h"\
	".\srvritem.h"\
	".\stdafx.h"\
	".\strings.h"\
	".\wordpad.h"\
	".\wordpdoc.h"\
	".\wordpvw.h"\
	

!IF  "$(CFG)" == "WordPad - Win32 Release"


"$(INTDIR)\wordpvw.obj"	"$(INTDIR)\wordpvw.sbr" : $(SOURCE) $(DEP_CPP_WORDPV)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"


"$(INTDIR)\wordpvw.obj"	"$(INTDIR)\wordpvw.sbr" : $(SOURCE) $(DEP_CPP_WORDPV)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"


"$(INTDIR)\wordpvw.obj"	"$(INTDIR)\wordpvw.sbr" : $(SOURCE) $(DEP_CPP_WORDPV)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"


"$(INTDIR)\wordpvw.obj"	"$(INTDIR)\wordpvw.sbr" : $(SOURCE) $(DEP_CPP_WORDPV)\
 "$(INTDIR)" "$(INTDIR)\wordpad.pch"


!ENDIF 

SOURCE=.\buttondi.h
SOURCE=.\chicdial.h
SOURCE=.\cntritem.h
SOURCE=.\colorlis.h
SOURCE=.\datedial.h
SOURCE=.\ddxm.h
SOURCE=.\docopt.h
SOURCE=.\doctype.h
SOURCE=.\filenewd.h
SOURCE=.\formatba.h
SOURCE=.\formatpa.h
SOURCE=.\formatta.h
SOURCE=.\helpids.h
SOURCE=.\ipframe.h
SOURCE=.\key.h
SOURCE=.\listdlg.h
SOURCE=.\mainfrm.h
SOURCE=.\mswd6_32.h
SOURCE=.\multconv.h
SOURCE=.\options.h
SOURCE=.\optionsh.h
SOURCE=.\pageset.h
SOURCE=.\ruler.h
SOURCE=.\splash.h
SOURCE=.\srvritem.h
SOURCE=.\stdafx.h
SOURCE=.\strings.h
SOURCE=.\unitspag.h
SOURCE=.\wordpad.h
SOURCE=.\wordpdoc.h
SOURCE=.\wordpvw.h
SOURCE=.\res\font.bmp
SOURCE=.\res\formatba.bmp
SOURCE=.\res\formatbg.bmp
SOURCE=.\res\main1.bmp
SOURCE=.\res\main1b.bmp
SOURCE=.\res\rtfdoc.ico
SOURCE=.\res\rulerbl.bmp
SOURCE=.\res\rulerblm.bmp
SOURCE=.\res\rulerdo.bmp
SOURCE=.\res\rulerdom.bmp
SOURCE=.\res\rulerta.bmp
SOURCE=.\res\rulertam.bmp
SOURCE=.\res\rulerup.bmp
SOURCE=.\res\rulerupm.bmp
SOURCE=.\res\srvr.bmp
SOURCE=.\res\srvrbig.bmp
SOURCE=.\res\textdoc.ico
SOURCE=.\res\wordp48.bmp
SOURCE=.\res\wordpad.ico
SOURCE=.\res\wordpad.rc2
SOURCE=.\res\write.ico

!ENDIF 

