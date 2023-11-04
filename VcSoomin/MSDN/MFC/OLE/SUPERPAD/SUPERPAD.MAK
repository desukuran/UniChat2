# Microsoft Developer Studio Generated NMAKE File, Based on superpad.dsp
!IF "$(CFG)" == ""
CFG=SuperPad - Win32 Release
!MESSAGE No configuration specified.  Defaulting to SuperPad - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "SuperPad - Win32 Release" && "$(CFG)" !=\
 "SuperPad - Win32 Debug" && "$(CFG)" != "SuperPad - Macintosh Release" &&\
 "$(CFG)" != "SuperPad - Macintosh Debug" && "$(CFG)" !=\
 "SuperPad - Power Macintosh Release" && "$(CFG)" !=\
 "SuperPad - Power Macintosh Debug" && "$(CFG)" !=\
 "SuperPad - Win32 Unicode Debug" && "$(CFG)" !=\
 "SuperPad - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "superpad.mak" CFG="SuperPad - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SuperPad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Macintosh Release" (based on "Macintosh Application")
!MESSAGE "SuperPad - Macintosh Debug" (based on "Macintosh Application")
!MESSAGE "SuperPad - Power Macintosh Release" (based on\
 "Power Macintosh Application")
!MESSAGE "SuperPad - Power Macintosh Debug" (based on\
 "Power Macintosh Application")
!MESSAGE "SuperPad - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Win32 Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SuperPad - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase "$(INTDIR)\aboutbox.obj"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\linkitem.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\paddoc.obj"
	-@erase "$(INTDIR)\padframe.obj"
	-@erase "$(INTDIR)\paditem.obj"
	-@erase "$(INTDIR)\padview.obj"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\superpad.obj"
	-@erase "$(INTDIR)\superpad.pch"
	-@erase "$(INTDIR)\superpad.res"
	-@erase "$(INTDIR)\tabstop.obj"
	-@erase "$(OUTDIR)\superpad.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/superpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/superpad.pdb" /machine:I386 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aboutbox.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\linkitem.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\paddoc.obj" \
	"$(INTDIR)\padframe.obj" \
	"$(INTDIR)\paditem.obj" \
	"$(INTDIR)\padview.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\superpad.obj" \
	"$(INTDIR)\superpad.res" \
	"$(INTDIR)\tabstop.obj"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase "$(INTDIR)\aboutbox.obj"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\linkitem.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\paddoc.obj"
	-@erase "$(INTDIR)\padframe.obj"
	-@erase "$(INTDIR)\paditem.obj"
	-@erase "$(INTDIR)\padview.obj"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\superpad.obj"
	-@erase "$(INTDIR)\superpad.pch"
	-@erase "$(INTDIR)\superpad.res"
	-@erase "$(INTDIR)\tabstop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\superpad.exe"
	-@erase "$(OUTDIR)\superpad.ilk"
	-@erase "$(OUTDIR)\superpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/superpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/superpad.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aboutbox.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\linkitem.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\paddoc.obj" \
	"$(INTDIR)\padframe.obj" \
	"$(INTDIR)\paditem.obj" \
	"$(INTDIR)\padview.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\superpad.obj" \
	"$(INTDIR)\superpad.res" \
	"$(INTDIR)\tabstop.obj"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

OUTDIR=.\MacRel
INTDIR=.\MacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/superpad.exe"

"$(OUTDIR)\superpad.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="SPAD"\
 /pdb:"$(OUTDIR)/superpad.pdb" /machine:M68K /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/superpad.rsc" \
	"$(INTDIR)/spadmac.rsc"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/superpad.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Gt1 /Q68s /W3 /GX /O2 /D "_WINDOWS" /D "_MAC" /D "_68K_"\
 /D "WIN32" /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\MacRel/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "NDEBUG" /mac 

CLEAN : 
	-@erase ".\MacRel\superpad.trg"
	-@erase ".\MacRel\superpad.exe"
	-@erase ".\MacRel\ipframe.obj"
	-@erase ".\MacRel\superpad.pch"
	-@erase ".\MacRel\padview.obj"
	-@erase ".\MacRel\padframe.obj"
	-@erase ".\MacRel\paditem.obj"
	-@erase ".\MacRel\paddoc.obj"
	-@erase ".\MacRel\superpad.obj"
	-@erase ".\MacRel\aboutbox.obj"
	-@erase ".\MacRel\tabstop.obj"
	-@erase ".\MacRel\pageset.obj"
	-@erase ".\MacRel\mainfrm.obj"
	-@erase ".\MacRel\linkitem.obj"
	-@erase ".\MacRel\stdafx.obj"
	-@erase ".\MacRel\superpad.rsc"
	-@erase ".\MacRel\spadmac.rsc"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

OUTDIR=.\MacDbg
INTDIR=.\MacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/superpad.exe"

"$(OUTDIR)\superpad.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="SPAD"\
 /pdb:"$(OUTDIR)/superpad.pdb" /debug /machine:M68K\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/spadmac.rsc" \
	"$(INTDIR)/superpad.rsc"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/superpad.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Gt1 /Q68s /Q68m /W3 /GX /Zi /Od /D "_WINDOWS" /D "_MAC"\
 /D "_68K_" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\MacDbg/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "_DEBUG" /mac 

CLEAN : 
	-@erase ".\MacDbg\vc40.pdb"
	-@erase ".\MacDbg\superpad.pch"
	-@erase ".\MacDbg\superpad.pdb"
	-@erase ".\MacDbg\mainfrm.obj"
	-@erase ".\MacDbg\padframe.obj"
	-@erase ".\MacDbg\paddoc.obj"
	-@erase ".\MacDbg\ipframe.obj"
	-@erase ".\MacDbg\padview.obj"
	-@erase ".\MacDbg\superpad.obj"
	-@erase ".\MacDbg\aboutbox.obj"
	-@erase ".\MacDbg\paditem.obj"
	-@erase ".\MacDbg\linkitem.obj"
	-@erase ".\MacDbg\tabstop.obj"
	-@erase ".\MacDbg\stdafx.obj"
	-@erase ".\MacDbg\pageset.obj"
	-@erase ".\MacDbg\spadmac.rsc"
	-@erase ".\MacDbg\superpad.rsc"
	-@erase ".\MacDbg\superpad.trg"
	-@erase ".\MacDbg\superpad.exe"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

OUTDIR=.\PMacRel
INTDIR=.\PMacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/superpad.exe"

"$(OUTDIR)\superpad.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="SPAD"\
 /incremental:no /pdb:"$(OUTDIR)/superpad.pdb" /machine:MPPC\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/spadmac.rsc" \
	"$(INTDIR)/superpad.rsc"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/superpad.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MAC" /D "_MPPC_" /D\
 "_WINDOWS" /D "WIN32" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/superpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\PMacRel/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "NDEBUG" 

CLEAN : 
	-@erase ".\PMacRel\superpad.trg"
	-@erase ".\PMacRel\superpad.exe"
	-@erase ".\PMacRel\mainfrm.obj"
	-@erase ".\PMacRel\superpad.pch"
	-@erase ".\PMacRel\superpad.obj"
	-@erase ".\PMacRel\aboutbox.obj"
	-@erase ".\PMacRel\paddoc.obj"
	-@erase ".\PMacRel\ipframe.obj"
	-@erase ".\PMacRel\padview.obj"
	-@erase ".\PMacRel\linkitem.obj"
	-@erase ".\PMacRel\paditem.obj"
	-@erase ".\PMacRel\padframe.obj"
	-@erase ".\PMacRel\tabstop.obj"
	-@erase ".\PMacRel\stdafx.obj"
	-@erase ".\PMacRel\pageset.obj"
	-@erase ".\PMacRel\spadmac.rsc"
	-@erase ".\PMacRel\superpad.rsc"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

OUTDIR=.\PMacDbg
INTDIR=.\PMacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/superpad.exe"

"$(OUTDIR)\superpad.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\superpad.exe\
 "$(MFILE32_DEST):superpad.exe">"$(OUTDIR)\superpad.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="SPAD"\
 /incremental:yes /pdb:"$(OUTDIR)/superpad.pdb" /debug /machine:MPPC\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/spadmac.rsc" \
	"$(INTDIR)/superpad.rsc"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/superpad.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "_MAC" /D "_MPPC_" /D\
 "_WINDOWS" /D "WIN32" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/superpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\PMacDbg/
CPP_SBRS=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "_DEBUG" 

CLEAN : 
	-@erase ".\PMacDbg\vc40.pdb"
	-@erase ".\PMacDbg\superpad.pch"
	-@erase ".\PMacDbg\superpad.ilk"
	-@erase ".\PMacDbg\tabstop.obj"
	-@erase ".\PMacDbg\superpad.obj"
	-@erase ".\PMacDbg\aboutbox.obj"
	-@erase ".\PMacDbg\pageset.obj"
	-@erase ".\PMacDbg\paddoc.obj"
	-@erase ".\PMacDbg\mainfrm.obj"
	-@erase ".\PMacDbg\linkitem.obj"
	-@erase ".\PMacDbg\ipframe.obj"
	-@erase ".\PMacDbg\padview.obj"
	-@erase ".\PMacDbg\padframe.obj"
	-@erase ".\PMacDbg\stdafx.obj"
	-@erase ".\PMacDbg\paditem.obj"
	-@erase ".\PMacDbg\spadmac.rsc"
	-@erase ".\PMacDbg\superpad.rsc"
	-@erase ".\PMacDbg\superpad.pdb"
	-@erase ".\PMacDbg\superpad.trg"
	-@erase ".\PMacDbg\superpad.exe"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase "$(INTDIR)\aboutbox.obj"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\linkitem.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\paddoc.obj"
	-@erase "$(INTDIR)\padframe.obj"
	-@erase "$(INTDIR)\paditem.obj"
	-@erase "$(INTDIR)\padview.obj"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\superpad.obj"
	-@erase "$(INTDIR)\superpad.pch"
	-@erase "$(INTDIR)\superpad.res"
	-@erase "$(INTDIR)\tabstop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\superpad.exe"
	-@erase "$(OUTDIR)\superpad.ilk"
	-@erase "$(OUTDIR)\superpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniDebug/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/superpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/superpad.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aboutbox.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\linkitem.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\paddoc.obj" \
	"$(INTDIR)\padframe.obj" \
	"$(INTDIR)\paditem.obj" \
	"$(INTDIR)\padview.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\superpad.obj" \
	"$(INTDIR)\superpad.res" \
	"$(INTDIR)\tabstop.obj"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase "$(INTDIR)\aboutbox.obj"
	-@erase "$(INTDIR)\ipframe.obj"
	-@erase "$(INTDIR)\linkitem.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\paddoc.obj"
	-@erase "$(INTDIR)\padframe.obj"
	-@erase "$(INTDIR)\paditem.obj"
	-@erase "$(INTDIR)\padview.obj"
	-@erase "$(INTDIR)\pageset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\superpad.obj"
	-@erase "$(INTDIR)\superpad.pch"
	-@erase "$(INTDIR)\superpad.res"
	-@erase "$(INTDIR)\tabstop.obj"
	-@erase "$(OUTDIR)\superpad.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniRelease/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/superpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/superpad.pdb" /machine:I386\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\aboutbox.obj" \
	"$(INTDIR)\ipframe.obj" \
	"$(INTDIR)\linkitem.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\paddoc.obj" \
	"$(INTDIR)\padframe.obj" \
	"$(INTDIR)\paditem.obj" \
	"$(INTDIR)\padview.obj" \
	"$(INTDIR)\pageset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\superpad.obj" \
	"$(INTDIR)\superpad.res" \
	"$(INTDIR)\tabstop.obj"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SuperPad - Win32 Release" || "$(CFG)" ==\
 "SuperPad - Win32 Debug" || "$(CFG)" == "SuperPad - Macintosh Release" ||\
 "$(CFG)" == "SuperPad - Macintosh Debug" || "$(CFG)" ==\
 "SuperPad - Power Macintosh Release" || "$(CFG)" ==\
 "SuperPad - Power Macintosh Debug" || "$(CFG)" ==\
 "SuperPad - Win32 Unicode Debug" || "$(CFG)" ==\
 "SuperPad - Win32 Unicode Release"
SOURCE=.\aboutbox.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_ABOUT=\
	".\aboutbox.h"\
	".\stdafx.h"\
	

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_ABOUT=\
	".\aboutbox.h"\
	".\stdafx.h"\
	

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_ABOUT=\
	".\aboutbox.h"\
	".\stdafx.h"\
	

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_ABOUT=\
	".\aboutbox.h"\
	".\stdafx.h"\
	

"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\ipframe.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_IPFRA=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_IPFRA=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_IPFRA=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_IPFRA=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\linkitem.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_LINKI=\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_LINKI=\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_LINKI=\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_LINKI=\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\mainfrm.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_MAINF=\
	".\aboutbox.h"\
	".\mainfrm.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_MAINF=\
	".\aboutbox.h"\
	".\mainfrm.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_MAINF=\
	".\aboutbox.h"\
	".\mainfrm.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_MAINF=\
	".\aboutbox.h"\
	".\mainfrm.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\paddoc.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_PADDO=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_PADDO=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_PADDO=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_PADDO=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\padframe.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_PADFR=\
	".\aboutbox.h"\
	".\padframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_PADFR=\
	".\aboutbox.h"\
	".\padframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_PADFR=\
	".\aboutbox.h"\
	".\padframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_PADFR=\
	".\aboutbox.h"\
	".\padframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\paditem.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_PADIT=\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_PADIT=\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_PADIT=\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_PADIT=\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\padview.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_PADVI=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_PADVI=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_PADVI=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_PADVI=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\pageset.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_PAGES=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_PAGES=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_PAGES=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_PAGES=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\spadmac.r

!IF  "$(CFG)" == "SuperPad - Win32 Release"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

NODEP_MRC_SPADM=\
	".\mrc\balloons.r"\
	".\mrc\types.r"\
	

"$(INTDIR)\spadmac.rsc" : $(SOURCE) $(DEP_MRC_SPADM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/spadmac.rsc" /D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

NODEP_MRC_SPADM=\
	".\mrc\balloons.r"\
	".\mrc\types.r"\
	

"$(INTDIR)\spadmac.rsc" : $(SOURCE) $(DEP_MRC_SPADM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/spadmac.rsc" /D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

NODEP_MRC_SPADM=\
	".\mrc\balloons.r"\
	".\mrc\types.r"\
	

"$(INTDIR)\spadmac.rsc" : $(SOURCE) $(DEP_MRC_SPADM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/spadmac.rsc" /D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

NODEP_MRC_SPADM=\
	".\mrc\balloons.r"\
	".\mrc\types.r"\
	

"$(INTDIR)\spadmac.rsc" : $(SOURCE) $(DEP_MRC_SPADM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/spadmac.rsc" /D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\superpad.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_SUPER=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\mainfrm.h"\
	".\paddoc.h"\
	".\padframe.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_SUPER=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\mainfrm.h"\
	".\paddoc.h"\
	".\padframe.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_SUPER=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\mainfrm.h"\
	".\paddoc.h"\
	".\padframe.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_SUPER=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\mainfrm.h"\
	".\paddoc.h"\
	".\padframe.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\superpad.rc

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_RSC_SUPERP=\
	".\res\itoolbar.bmp"\
	".\res\paddoc.ico"\
	".\res\superpad.ico"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\superpad.res" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_RSC_SUPERP=\
	".\res\itoolbar.bmp"\
	".\res\paddoc.ico"\
	".\res\superpad.ico"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\superpad.res" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\superpad.rsc" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\superpad.rsc" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\superpad.rsc" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\superpad.rsc" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_RSC_SUPERP=\
	".\res\itoolbar.bmp"\
	".\res\paddoc.ico"\
	".\res\superpad.ico"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\superpad.res" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_RSC_SUPERP=\
	".\res\itoolbar.bmp"\
	".\res\paddoc.ico"\
	".\res\superpad.ico"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\superpad.res" : $(SOURCE) $(DEP_RSC_SUPERP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\tabstop.cpp

!IF  "$(CFG)" == "SuperPad - Win32 Release"

DEP_CPP_TABST=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

DEP_CPP_TABST=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Release"

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Macintosh Debug"

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Release"

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Power Macintosh Debug"

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

DEP_CPP_TABST=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

DEP_CPP_TABST=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

SOURCE=.\aboutbox.h
SOURCE=.\ipframe.h
SOURCE=.\linkitem.h
SOURCE=.\mainfrm.h
SOURCE=.\paddoc.h
SOURCE=.\padframe.h
SOURCE=.\paditem.h
SOURCE=.\padview.h
SOURCE=.\pageset.h
SOURCE=.\stdafx.h
SOURCE=.\superpad.h
SOURCE=.\tabstop.h
SOURCE=.\res\itoolbar.bmp
SOURCE=.\res\paddoc.ico
SOURCE=.\res\superpad.ico
SOURCE=.\res\toolbar.bmp

!ENDIF 

