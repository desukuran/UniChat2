# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Async - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Async - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Async - Win32 Release" && "$(CFG)" != "Async - Win32 MinCRT"\
 && "$(CFG)" != "Async - Win32 Debug" && "$(CFG)" !=\
 "Async - Win32 Unicode Release" && "$(CFG)" != "Async - Win32 Unicode MinCRT"\
 && "$(CFG)" != "Async - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Async.mak" CFG="Async - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Async - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Async - Win32 MinCRT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Async - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Async - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Async - Win32 Unicode MinCRT" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Async - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Async - Win32 Unicode Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Async - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Async.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Async.pdb" /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\Async.dll
InputPath=.\Release\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MinRel"
# PROP BASE Intermediate_Dir "MinRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MinRel"
# PROP Intermediate_Dir "MinRel"
# PROP Target_Dir ""
OUTDIR=.\MinRel
INTDIR=.\MinRel
# Begin Custom Macros
OutDir=.\MinRel
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL"\
 /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)/Async.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\MinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Async.pdb" /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\MinRel
TargetPath=.\MinRel\Async.dll
InputPath=.\MinRel\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.ilk"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\Async.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Async.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Async.pdb" /debug /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\Async.dll
InputPath=.\Debug\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release"
# PROP BASE Intermediate_Dir "Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Async.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Async.pdb" /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Async.dll
InputPath=.\ReleaseU\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release MinCRT"
# PROP BASE Intermediate_Dir "Unicode Release MinCRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MinRelU"
# PROP Intermediate_Dir "MinRelU"
# PROP Target_Dir ""
OUTDIR=.\MinRelU
INTDIR=.\MinRelU
# Begin Custom Macros
OutDir=.\MinRelU
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL"\
 /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)/Async.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\MinRelU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Async.pdb" /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\MinRelU
TargetPath=.\MinRelU\Async.dll
InputPath=.\MinRelU\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode Debug"
# PROP BASE Intermediate_Dir "Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Async.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Async.obj"
	-@erase "$(INTDIR)\Async.pch"
	-@erase "$(INTDIR)\Async.res"
	-@erase "$(INTDIR)\ATLAsync.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Async.dll"
	-@erase "$(OUTDIR)\Async.exp"
	-@erase "$(OUTDIR)\Async.ilk"
	-@erase "$(OUTDIR)\Async.lib"
	-@erase "$(OUTDIR)\Async.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Async.h"
	-@erase ".\Async.tlb"
	-@erase ".\Async_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Async.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Async.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Async.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Async.pdb" /debug /machine:I386 /def:".\Async.def"\
 /out:"$(OUTDIR)/Async.dll" /implib:"$(OUTDIR)/Async.lib" 
DEF_FILE= \
	".\Async.def"
LINK32_OBJS= \
	"$(INTDIR)\Async.obj" \
	"$(INTDIR)\Async.res" \
	"$(INTDIR)\ATLAsync.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Async.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\Async.dll
InputPath=.\DebugU\Async.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ENDIF 

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

################################################################################
# Begin Target

# Name "Async - Win32 Release"
# Name "Async - Win32 MinCRT"
# Name "Async - Win32 Debug"
# Name "Async - Win32 Unicode Release"
# Name "Async - Win32 Unicode MinCRT"
# Name "Async - Win32 Unicode Debug"

!IF  "$(CFG)" == "Async - Win32 Release"

!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"

!ELSEIF  "$(CFG)" == "Async - Win32 Debug"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.cpp"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atlctl.cpp"\
	{$(INCLUDE)}"\atlctl.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	{$(INCLUDE)}"\atlwin.cpp"\
	{$(INCLUDE)}"\atlwin.h"\
	{$(INCLUDE)}"\objsafe.h"\
	

!IF  "$(CFG)" == "Async - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Async.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL"\
 /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)/Async.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Async - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Async.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Async.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL"\
 /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)/Async.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Async.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Async.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Async.cpp
DEP_CPP_ASYNC=\
	".\Async.h"\
	".\Async_i.c"\
	".\ATLAsync.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atlctl.h"\
	{$(INCLUDE)}"\atlwin.h"\
	{$(INCLUDE)}"\objsafe.h"\
	{$(INCLUDE)}"\ocidl.h"\
	

!IF  "$(CFG)" == "Async - Win32 Release"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ELSEIF  "$(CFG)" == "Async - Win32 Debug"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"


"$(INTDIR)\Async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h" ".\Async_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Async.def

!IF  "$(CFG)" == "Async - Win32 Release"

!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"

!ELSEIF  "$(CFG)" == "Async - Win32 Debug"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Async.rc
DEP_RSC_ASYNC_=\
	".\Async.tlb"\
	".\ATLAsync.rgs"\
	

!IF  "$(CFG)" == "Async - Win32 Release"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Async - Win32 Debug"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"


"$(INTDIR)\Async.res" : $(SOURCE) $(DEP_RSC_ASYNC_) "$(INTDIR)" ".\Async.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Async.idl

!IF  "$(CFG)" == "Async - Win32 Release"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Debug"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"

# Begin Custom Build
InputPath=.\Async.idl

BuildCmds= \
	midl /h Async.h /iid Async_i.c Async.idl \
	

"Async.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Async_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATLAsync.cpp
DEP_CPP_ATLAS=\
	".\Async.h"\
	".\ATLAsync.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlconv.h"\
	{$(INCLUDE)}"\atlctl.h"\
	{$(INCLUDE)}"\atlwin.h"\
	{$(INCLUDE)}"\objsafe.h"\
	{$(INCLUDE)}"\ocidl.h"\
	

!IF  "$(CFG)" == "Async - Win32 Release"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ELSEIF  "$(CFG)" == "Async - Win32 MinCRT"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ELSEIF  "$(CFG)" == "Async - Win32 Debug"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Release"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode MinCRT"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ELSEIF  "$(CFG)" == "Async - Win32 Unicode Debug"


"$(INTDIR)\ATLAsync.obj" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\Async.pch" ".\Async.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
