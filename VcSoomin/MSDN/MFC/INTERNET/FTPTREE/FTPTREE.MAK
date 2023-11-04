# Microsoft Developer Studio Generated NMAKE File, Based on FTPTREE.DSP
!IF "$(CFG)" == ""
CFG=FTPTREE - Win32 Release
!MESSAGE No configuration specified.  Defaulting to FTPTREE - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "FTPTREE - Win32 Release" && "$(CFG)" !=\
 "FTPTREE - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "FTPTREE.MAK" CFG="FTPTREE - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FTPTREE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FTPTREE - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "FTPTREE - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\FTPTREE.exe"

CLEAN : 
	-@erase "$(INTDIR)\FtpTrCtl.obj"
	-@erase "$(INTDIR)\FTPtrDlg.obj"
	-@erase "$(INTDIR)\FTPTREE.obj"
	-@erase "$(INTDIR)\FTPTREE.pch"
	-@erase "$(INTDIR)\FTPTREE.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\FTPTREE.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/FTPTREE.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FTPTREE.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FTPTREE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=uuid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/FTPTREE.pdb" /machine:I386 /out:"$(OUTDIR)/FTPTREE.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FtpTrCtl.obj" \
	"$(INTDIR)\FTPtrDlg.obj" \
	"$(INTDIR)\FTPTREE.obj" \
	"$(INTDIR)\FTPTREE.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FTPTREE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FTPTREE - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\FTPTREE.exe"

CLEAN : 
	-@erase "$(INTDIR)\FtpTrCtl.obj"
	-@erase "$(INTDIR)\FTPtrDlg.obj"
	-@erase "$(INTDIR)\FTPTREE.obj"
	-@erase "$(INTDIR)\FTPTREE.pch"
	-@erase "$(INTDIR)\FTPTREE.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\FTPTREE.exe"
	-@erase "$(OUTDIR)\FTPTREE.ilk"
	-@erase "$(OUTDIR)\FTPTREE.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/FTPTREE.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FTPTREE.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FTPTREE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=uuid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/FTPTREE.pdb" /debug /machine:I386 /out:"$(OUTDIR)/FTPTREE.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FtpTrCtl.obj" \
	"$(INTDIR)\FTPtrDlg.obj" \
	"$(INTDIR)\FTPTREE.obj" \
	"$(INTDIR)\FTPTREE.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FTPTREE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "FTPTREE - Win32 Release" || "$(CFG)" ==\
 "FTPTREE - Win32 Debug"
SOURCE=.\FtpTrCtl.cpp

!IF  "$(CFG)" == "FTPTREE - Win32 Release"

DEP_CPP_FTPTR=\
	".\FTPtrCtl.h"\
	".\FTPTREE.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FtpTrCtl.obj" : $(SOURCE) $(DEP_CPP_FTPTR) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ELSEIF  "$(CFG)" == "FTPTREE - Win32 Debug"

DEP_CPP_FTPTR=\
	".\FTPtrCtl.h"\
	".\FTPTREE.h"\
	

"$(INTDIR)\FtpTrCtl.obj" : $(SOURCE) $(DEP_CPP_FTPTR) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ENDIF 

SOURCE=.\FTPtrDlg.cpp

!IF  "$(CFG)" == "FTPTREE - Win32 Release"

DEP_CPP_FTPTRD=\
	".\FTPtrCtl.h"\
	".\FTPtrDlg.h"\
	".\FTPTREE.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FTPtrDlg.obj" : $(SOURCE) $(DEP_CPP_FTPTRD) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ELSEIF  "$(CFG)" == "FTPTREE - Win32 Debug"

DEP_CPP_FTPTRD=\
	".\FTPtrCtl.h"\
	".\FTPtrDlg.h"\
	".\FTPTREE.h"\
	

"$(INTDIR)\FTPtrDlg.obj" : $(SOURCE) $(DEP_CPP_FTPTRD) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ENDIF 

SOURCE=.\FTPTREE.cpp

!IF  "$(CFG)" == "FTPTREE - Win32 Release"

DEP_CPP_FTPTRE=\
	".\FTPtrCtl.h"\
	".\FTPtrDlg.h"\
	".\FTPTREE.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FTPTREE.obj" : $(SOURCE) $(DEP_CPP_FTPTRE) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ELSEIF  "$(CFG)" == "FTPTREE - Win32 Debug"

DEP_CPP_FTPTRE=\
	".\FTPtrCtl.h"\
	".\FTPtrDlg.h"\
	".\FTPTREE.h"\
	

"$(INTDIR)\FTPTREE.obj" : $(SOURCE) $(DEP_CPP_FTPTRE) "$(INTDIR)"\
 "$(INTDIR)\FTPTREE.pch"


!ENDIF 

SOURCE=.\FTPTREE.rc
DEP_RSC_FTPTREE=\
	".\res\bmdir.bmp"\
	".\res\bmerror.bmp"\
	".\res\bmfile.bmp"\
	".\res\FTPTREE.ico"\
	".\res\FTPTREE.rc2"\
	

"$(INTDIR)\FTPTREE.res" : $(SOURCE) $(DEP_RSC_FTPTREE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FTPTREE - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FTPTREE.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/FTPTREE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "FTPTREE - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"c:\msdev\vc\include\zmouse.h"\
	

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FTPTREE.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/FTPTREE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\FTPtrCtl.h
SOURCE=.\FTPtrDlg.h
SOURCE=.\FTPTREE.h
SOURCE=.\StdAfx.h
SOURCE=.\res\bmdir.bmp
SOURCE=.\res\bmerror.bmp
SOURCE=.\res\bmfile.bmp
SOURCE=.\res\FTPTREE.ico
SOURCE=.\res\FTPTREE.rc2

!ENDIF 

