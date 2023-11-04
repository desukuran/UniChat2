# Microsoft Developer Studio Generated NMAKE File, Based on stdreg.dsp
!IF "$(CFG)" == ""
CFG=stdreg - Macintosh Release
!MESSAGE No configuration specified.  Defaulting to stdreg - Macintosh Release.
!ENDIF 

!IF "$(CFG)" != "stdreg - Macintosh Release" && "$(CFG)" !=\
 "stdreg - Macintosh Debug" && "$(CFG)" != "stdreg - Win32 Release" && "$(CFG)"\
 != "stdreg - Win32 Debug" && "$(CFG)" != "stdreg - Power Macintosh Release" &&\
 "$(CFG)" != "stdreg - Power Macintosh Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "stdreg.mak" CFG="stdreg - Macintosh Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stdreg - Macintosh Release" (based on "Macintosh Application")
!MESSAGE "stdreg - Macintosh Debug" (based on "Macintosh Application")
!MESSAGE "stdreg - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "stdreg - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "stdreg - Power Macintosh Release" (based on\
 "Power Macintosh Application")
!MESSAGE "stdreg - Power Macintosh Debug" (based on\
 "Power Macintosh Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "stdreg - Macintosh Release"

OUTDIR=.\MacRel
INTDIR=.\MacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/stdreg.exe"

"$(OUTDIR)\stdreg.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\stdreg.exe "$(MFILE32_DEST)"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\stdreg.exe "$(MFILE32_DEST)"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="STDR"\
 /pdb:"$(OUTDIR)/stdreg.pdb" /machine:M68K /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/sectset.obj" \
	"$(INTDIR)/instrset.obj" \
	"$(INTDIR)/enrolset.obj" \
	"$(INTDIR)/dsectset.obj" \
	"$(INTDIR)/dialog.obj" \
	"$(INTDIR)/coursset.obj" \
	"$(INTDIR)/columdlg.obj" \
	"$(INTDIR)/typeinfo.obj" \
	"$(INTDIR)/stdset.obj" \
	"$(INTDIR)/stdreg.obj" \
	"$(INTDIR)/stdrMac.rsc" \
	"$(INTDIR)/stdreg.rsc"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/stdreg.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /W3 /GX /O2 /D "_WINDOWS" /D "_MAC" /D "_68K_" /D\
 "WIN32" /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch" /Yu"stdafx.h"\
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
	-@erase ".\MacRel\stdreg.trg"
	-@erase ".\MacRel\stdreg.exe"
	-@erase ".\MacRel\stdafx.obj"
	-@erase ".\MacRel\sectset.obj"
	-@erase ".\MacRel\stdreg.pch"
	-@erase ".\MacRel\instrset.obj"
	-@erase ".\MacRel\enrolset.obj"
	-@erase ".\MacRel\dsectset.obj"
	-@erase ".\MacRel\dialog.obj"
	-@erase ".\MacRel\coursset.obj"
	-@erase ".\MacRel\columdlg.obj"
	-@erase ".\MacRel\typeinfo.obj"
	-@erase ".\MacRel\stdset.obj"
	-@erase ".\MacRel\stdreg.obj"
	-@erase ".\MacRel\stdrMac.rsc"
	-@erase ".\MacRel\stdreg.rsc"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

OUTDIR=.\MacDbg
INTDIR=.\MacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/stdreg.exe"

"$(OUTDIR)\stdreg.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\stdreg.exe "$(MFILE32_DEST)"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\stdreg.exe "$(MFILE32_DEST)"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="STDR"\
 /pdb:"$(OUTDIR)/stdreg.pdb" /debug /machine:M68K /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/sectset.obj" \
	"$(INTDIR)/instrset.obj" \
	"$(INTDIR)/enrolset.obj" \
	"$(INTDIR)/dsectset.obj" \
	"$(INTDIR)/dialog.obj" \
	"$(INTDIR)/coursset.obj" \
	"$(INTDIR)/columdlg.obj" \
	"$(INTDIR)/typeinfo.obj" \
	"$(INTDIR)/stdset.obj" \
	"$(INTDIR)/stdreg.obj" \
	"$(INTDIR)/stdrMac.rsc" \
	"$(INTDIR)/stdreg.rsc"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/stdreg.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /Q68m /W3 /GX /Zi /Od /D "_WINDOWS" /D "_MAC" /D\
 "_68K_" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch"\
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
	-@erase ".\MacDbg\stdreg.pch"
	-@erase ".\MacDbg\stdreg.pdb"
	-@erase ".\MacDbg\stdafx.obj"
	-@erase ".\MacDbg\sectset.obj"
	-@erase ".\MacDbg\instrset.obj"
	-@erase ".\MacDbg\enrolset.obj"
	-@erase ".\MacDbg\dsectset.obj"
	-@erase ".\MacDbg\dialog.obj"
	-@erase ".\MacDbg\coursset.obj"
	-@erase ".\MacDbg\columdlg.obj"
	-@erase ".\MacDbg\typeinfo.obj"
	-@erase ".\MacDbg\stdset.obj"
	-@erase ".\MacDbg\stdreg.obj"
	-@erase ".\MacDbg\stdrMac.rsc"
	-@erase ".\MacDbg\stdreg.rsc"
	-@erase ".\MacDbg\stdreg.trg"
	-@erase ".\MacDbg\stdreg.exe"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\stdreg.exe"

CLEAN : 
	-@erase "$(INTDIR)\columdlg.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dsectset.obj"
	-@erase "$(INTDIR)\enrolset.obj"
	-@erase "$(INTDIR)\instrset.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdreg.obj"
	-@erase "$(INTDIR)\stdreg.pch"
	-@erase "$(INTDIR)\stdreg.res"
	-@erase "$(INTDIR)\stdset.obj"
	-@erase "$(INTDIR)\typeinfo.obj"
	-@erase "$(OUTDIR)\stdreg.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stdreg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/stdreg.pdb" /machine:I386 /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\columdlg.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\dsectset.obj" \
	"$(INTDIR)\enrolset.obj" \
	"$(INTDIR)\instrset.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\stdreg.obj" \
	"$(INTDIR)\stdreg.res" \
	"$(INTDIR)\stdset.obj" \
	"$(INTDIR)\typeinfo.obj"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\stdreg.exe"

CLEAN : 
	-@erase "$(INTDIR)\columdlg.obj"
	-@erase "$(INTDIR)\coursset.obj"
	-@erase "$(INTDIR)\dialog.obj"
	-@erase "$(INTDIR)\dsectset.obj"
	-@erase "$(INTDIR)\enrolset.obj"
	-@erase "$(INTDIR)\instrset.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdreg.obj"
	-@erase "$(INTDIR)\stdreg.pch"
	-@erase "$(INTDIR)\stdreg.res"
	-@erase "$(INTDIR)\stdset.obj"
	-@erase "$(INTDIR)\typeinfo.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\stdreg.exe"
	-@erase "$(OUTDIR)\stdreg.ilk"
	-@erase "$(OUTDIR)\stdreg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stdreg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/stdreg.pdb" /debug /machine:I386 /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\columdlg.obj" \
	"$(INTDIR)\coursset.obj" \
	"$(INTDIR)\dialog.obj" \
	"$(INTDIR)\dsectset.obj" \
	"$(INTDIR)\enrolset.obj" \
	"$(INTDIR)\instrset.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\stdreg.obj" \
	"$(INTDIR)\stdreg.res" \
	"$(INTDIR)\stdset.obj" \
	"$(INTDIR)\typeinfo.obj"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

OUTDIR=.\PMacRel
INTDIR=.\PMacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/stdreg.exe"

"$(OUTDIR)\stdreg.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\stdreg.exe "$(MFILE32_DEST)"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\stdreg.exe "$(MFILE32_DEST)"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="STDR"\
 /incremental:no /pdb:"$(OUTDIR)/stdreg.pdb" /machine:MPPC\
 /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/sectset.obj" \
	"$(INTDIR)/instrset.obj" \
	"$(INTDIR)/enrolset.obj" \
	"$(INTDIR)/dsectset.obj" \
	"$(INTDIR)/dialog.obj" \
	"$(INTDIR)/coursset.obj" \
	"$(INTDIR)/columdlg.obj" \
	"$(INTDIR)/typeinfo.obj" \
	"$(INTDIR)/stdset.obj" \
	"$(INTDIR)/stdreg.obj" \
	"$(INTDIR)/stdrMac.rsc" \
	"$(INTDIR)/stdreg.rsc"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/stdreg.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" /d "_AFXDLL" 
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "_MAC" /D "_MPPC_" /D "_WINDOWS" /D "WIN32"\
 /D "NDEBUG" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/stdreg.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
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
	-@erase ".\PMacRel\stdreg.trg"
	-@erase ".\PMacRel\stdreg.exe"
	-@erase ".\PMacRel\stdafx.obj"
	-@erase ".\PMacRel\sectset.obj"
	-@erase ".\PMacRel\stdreg.pch"
	-@erase ".\PMacRel\instrset.obj"
	-@erase ".\PMacRel\enrolset.obj"
	-@erase ".\PMacRel\dsectset.obj"
	-@erase ".\PMacRel\dialog.obj"
	-@erase ".\PMacRel\coursset.obj"
	-@erase ".\PMacRel\columdlg.obj"
	-@erase ".\PMacRel\typeinfo.obj"
	-@erase ".\PMacRel\stdset.obj"
	-@erase ".\PMacRel\stdreg.obj"
	-@erase ".\PMacRel\stdrMac.rsc"
	-@erase ".\PMacRel\stdreg.rsc"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

OUTDIR=.\PMacDbg
INTDIR=.\PMacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/stdreg.exe"

"$(OUTDIR)\stdreg.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\stdreg.exe "$(MFILE32_DEST)"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\stdreg.exe "$(MFILE32_DEST)"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="STDR"\
 /incremental:yes /pdb:"$(OUTDIR)/stdreg.pdb" /debug /machine:MPPC\
 /out:"$(OUTDIR)/stdreg.exe" 
LINK32_OBJS= \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/sectset.obj" \
	"$(INTDIR)/instrset.obj" \
	"$(INTDIR)/enrolset.obj" \
	"$(INTDIR)/dsectset.obj" \
	"$(INTDIR)/dialog.obj" \
	"$(INTDIR)/coursset.obj" \
	"$(INTDIR)/columdlg.obj" \
	"$(INTDIR)/typeinfo.obj" \
	"$(INTDIR)/stdset.obj" \
	"$(INTDIR)/stdreg.obj" \
	"$(INTDIR)/stdrMac.rsc" \
	"$(INTDIR)/stdreg.rsc"

"$(OUTDIR)\stdreg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stdreg.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/stdreg.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" /d "_AFXDLL" 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "_MAC" /D "_MPPC_" /D "_WINDOWS" /D\
 "WIN32" /D "_DEBUG" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/stdreg.pch"\
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
	-@erase ".\PMacDbg\stdreg.pch"
	-@erase ".\PMacDbg\stdreg.ilk"
	-@erase ".\PMacDbg\stdafx.obj"
	-@erase ".\PMacDbg\sectset.obj"
	-@erase ".\PMacDbg\instrset.obj"
	-@erase ".\PMacDbg\enrolset.obj"
	-@erase ".\PMacDbg\dsectset.obj"
	-@erase ".\PMacDbg\dialog.obj"
	-@erase ".\PMacDbg\coursset.obj"
	-@erase ".\PMacDbg\columdlg.obj"
	-@erase ".\PMacDbg\typeinfo.obj"
	-@erase ".\PMacDbg\stdset.obj"
	-@erase ".\PMacDbg\stdreg.obj"
	-@erase ".\PMacDbg\stdrMac.rsc"
	-@erase ".\PMacDbg\stdreg.rsc"
	-@erase ".\PMacDbg\stdreg.pdb"
	-@erase ".\PMacDbg\stdreg.trg"
	-@erase ".\PMacDbg\stdreg.exe"

!ENDIF 


!IF "$(CFG)" == "stdreg - Macintosh Release" || "$(CFG)" ==\
 "stdreg - Macintosh Debug" || "$(CFG)" == "stdreg - Win32 Release" || "$(CFG)"\
 == "stdreg - Win32 Debug" || "$(CFG)" == "stdreg - Power Macintosh Release" ||\
 "$(CFG)" == "stdreg - Power Macintosh Debug"
SOURCE=.\columdlg.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_COLUM=\
	".\columdlg.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_COLUM=\
	".\columdlg.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_COLUM=\
	".\columdlg.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\columdlg.obj" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_COLUM) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\coursset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_COURS=\
	".\coursset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_COURS=\
	".\coursset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_COURS=\
	".\coursset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\coursset.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\dialog.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_DIALO=\
	".\dialog.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_DIALO=\
	".\dialog.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_DIALO=\
	".\dialog.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\dsectset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_DSECT=\
	".\dsectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_DSECT=\
	".\dsectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_DSECT=\
	".\dsectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\dsectset.obj" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_DSECT) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\enrolset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_ENROL=\
	".\enrolset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_ENROL=\
	".\enrolset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_ENROL=\
	".\enrolset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\enrolset.obj" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ENROL) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\instrset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_INSTR=\
	".\instrset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_INSTR=\
	".\instrset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_INSTR=\
	".\instrset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\instrset.obj" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_INSTR) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\sectset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_SECTS=\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_SECTS=\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_SECTS=\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	

"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stdreg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	
BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /Zi /Od /D "_MAC" /D "_MPPC_" /D "_WINDOWS" /D\
 "WIN32" /D "_DEBUG" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/stdreg.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdreg.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

SOURCE=.\stdreg.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_STDRE=\
	".\columdlg.h"\
	".\coursset.h"\
	".\dialog.h"\
	".\dsectset.h"\
	".\enrolset.h"\
	".\initdata.h"\
	".\instrset.h"\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_STDRE=\
	".\columdlg.h"\
	".\coursset.h"\
	".\dialog.h"\
	".\dsectset.h"\
	".\enrolset.h"\
	".\initdata.h"\
	".\instrset.h"\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_STDRE=\
	".\columdlg.h"\
	".\coursset.h"\
	".\dialog.h"\
	".\dsectset.h"\
	".\enrolset.h"\
	".\initdata.h"\
	".\instrset.h"\
	".\sectset.h"\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\stdreg.obj" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDRE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\stdreg.rc

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\stdreg.rsc" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\stdreg.rsc" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_RSC_STDREG=\
	".\RES\STDREG.ICO"\
	".\res\stdreg.rc2"\
	

"$(INTDIR)\stdreg.res" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_RSC_STDREG=\
	".\RES\STDREG.ICO"\
	".\res\stdreg.rc2"\
	

"$(INTDIR)\stdreg.res" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\stdreg.rsc" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_RSC_STDREG=\
	".\RES\STDREG.ICO"\
	".\res\stdreg.rc2"\
	

"$(INTDIR)\stdreg.rsc" : $(SOURCE) $(DEP_RSC_STDREG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\stdrMac.r

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\stdrMac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/stdrMac.rsc" /D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\stdrMac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/stdrMac.rsc" /D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\stdrMac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/stdrMac.rsc" /D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

"$(INTDIR)\stdrMac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/stdrMac.rsc" /D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ENDIF 

SOURCE=.\stdset.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_STDSE=\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_STDSE=\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_STDSE=\
	".\stdafx.h"\
	".\stdreg.h"\
	".\stdset.h"\
	

"$(INTDIR)\stdset.obj" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDSE) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\typeinfo.cpp

!IF  "$(CFG)" == "stdreg - Macintosh Release"

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Macintosh Debug"

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Win32 Release"

DEP_CPP_TYPEI=\
	".\stdafx.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Win32 Debug"

DEP_CPP_TYPEI=\
	".\stdafx.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"


!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Release"

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ELSEIF  "$(CFG)" == "stdreg - Power Macintosh Debug"

DEP_CPP_TYPEI=\
	".\stdafx.h"\
	".\typeinfo.h"\
	

"$(INTDIR)\typeinfo.obj" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TYPEI) "$(INTDIR)"\
 "$(INTDIR)\stdreg.pch"

!ENDIF 

SOURCE=.\columdlg.h
SOURCE=.\coursset.h
SOURCE=.\dialog.h
SOURCE=.\dsectset.h
SOURCE=.\enrolset.h
SOURCE=.\initdata.h
SOURCE=.\instrset.h
SOURCE=.\sectset.h
SOURCE=.\stdafx.h
SOURCE=.\stdreg.h
SOURCE=.\stdset.h
SOURCE=.\typeinfo.h
SOURCE=.\RES\STDREG.ICO
SOURCE=.\res\stdreg.rc2

!ENDIF 

