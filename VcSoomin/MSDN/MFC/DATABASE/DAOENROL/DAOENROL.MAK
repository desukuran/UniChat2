# Microsoft Developer Studio Generated NMAKE File, Based on daoenrol.dsp
!IF "$(CFG)" == ""
CFG=DaoEnrol - Win32 Release
!MESSAGE No configuration specified.  Defaulting to DaoEnrol - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DaoEnrol - Win32 Release" && "$(CFG)" !=\
 "DaoEnrol - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "daoenrol.mak" CFG="DaoEnrol - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DaoEnrol - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DaoEnrol - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\daoenrol.exe"

CLEAN : 
	-@erase "$(INTDIR)\addform.obj"
	-@erase "$(INTDIR)\coursese.obj"
	-@erase "$(INTDIR)\crsform.obj"
	-@erase "$(INTDIR)\DaoEnrol.obj"
	-@erase "$(INTDIR)\daoenrol.pch"
	-@erase "$(INTDIR)\DaoEnrol.res"
	-@erase "$(INTDIR)\denrldoc.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\daoenrol.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/daoenrol.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DaoEnrol.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/daoenrol.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/daoenrol.pdb" /machine:I386 /out:"$(OUTDIR)/daoenrol.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addform.obj" \
	"$(INTDIR)\coursese.obj" \
	"$(INTDIR)\crsform.obj" \
	"$(INTDIR)\DaoEnrol.obj" \
	"$(INTDIR)\DaoEnrol.res" \
	"$(INTDIR)\denrldoc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\daoenrol.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\daoenrol.exe" "$(OUTDIR)\daoenrol.bsc"

CLEAN : 
	-@erase "$(INTDIR)\addform.obj"
	-@erase "$(INTDIR)\addform.sbr"
	-@erase "$(INTDIR)\coursese.obj"
	-@erase "$(INTDIR)\coursese.sbr"
	-@erase "$(INTDIR)\crsform.obj"
	-@erase "$(INTDIR)\crsform.sbr"
	-@erase "$(INTDIR)\DaoEnrol.obj"
	-@erase "$(INTDIR)\daoenrol.pch"
	-@erase "$(INTDIR)\DaoEnrol.res"
	-@erase "$(INTDIR)\DaoEnrol.sbr"
	-@erase "$(INTDIR)\denrldoc.obj"
	-@erase "$(INTDIR)\denrldoc.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\sectform.obj"
	-@erase "$(INTDIR)\sectform.sbr"
	-@erase "$(INTDIR)\sectset.obj"
	-@erase "$(INTDIR)\sectset.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\daoenrol.bsc"
	-@erase "$(OUTDIR)\daoenrol.exe"
	-@erase "$(OUTDIR)\daoenrol.ilk"
	-@erase "$(OUTDIR)\daoenrol.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/daoenrol.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DaoEnrol.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/daoenrol.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addform.sbr" \
	"$(INTDIR)\coursese.sbr" \
	"$(INTDIR)\crsform.sbr" \
	"$(INTDIR)\DaoEnrol.sbr" \
	"$(INTDIR)\denrldoc.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\sectform.sbr" \
	"$(INTDIR)\sectset.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\daoenrol.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/daoenrol.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/daoenrol.exe" 
LINK32_OBJS= \
	"$(INTDIR)\addform.obj" \
	"$(INTDIR)\coursese.obj" \
	"$(INTDIR)\crsform.obj" \
	"$(INTDIR)\DaoEnrol.obj" \
	"$(INTDIR)\DaoEnrol.res" \
	"$(INTDIR)\denrldoc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\sectform.obj" \
	"$(INTDIR)\sectset.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\daoenrol.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "DaoEnrol - Win32 Release" || "$(CFG)" ==\
 "DaoEnrol - Win32 Debug"
SOURCE=.\addform.cpp
DEP_CPP_ADDFO=\
	".\addform.h"\
	".\DaoEnrol.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\addform.obj" : $(SOURCE) $(DEP_CPP_ADDFO) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\addform.obj"	"$(INTDIR)\addform.sbr" : $(SOURCE) $(DEP_CPP_ADDFO)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\coursese.cpp
DEP_CPP_COURS=\
	".\coursese.h"\
	".\DaoEnrol.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\coursese.obj" : $(SOURCE) $(DEP_CPP_COURS) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\coursese.obj"	"$(INTDIR)\coursese.sbr" : $(SOURCE) $(DEP_CPP_COURS)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\crsform.cpp
DEP_CPP_CRSFO=\
	".\addform.h"\
	".\coursese.h"\
	".\crsform.h"\
	".\DaoEnrol.h"\
	".\denrldoc.h"\
	".\MainFrm.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\crsform.obj" : $(SOURCE) $(DEP_CPP_CRSFO) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\crsform.obj"	"$(INTDIR)\crsform.sbr" : $(SOURCE) $(DEP_CPP_CRSFO)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\DaoEnrol.cpp
DEP_CPP_DAOEN=\
	".\coursese.h"\
	".\DaoEnrol.h"\
	".\denrldoc.h"\
	".\MainFrm.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\DaoEnrol.obj" : $(SOURCE) $(DEP_CPP_DAOEN) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\DaoEnrol.obj"	"$(INTDIR)\DaoEnrol.sbr" : $(SOURCE) $(DEP_CPP_DAOEN)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\DaoEnrol.rc
DEP_RSC_DAOENR=\
	".\res\DaoEnrol.ico"\
	".\res\DaoEnrol.rc2"\
	".\res\denrldoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\DaoEnrol.res" : $(SOURCE) $(DEP_RSC_DAOENR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\denrldoc.cpp
DEP_CPP_DENRL=\
	".\coursese.h"\
	".\DaoEnrol.h"\
	".\denrldoc.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\denrldoc.obj" : $(SOURCE) $(DEP_CPP_DENRL) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\denrldoc.obj"	"$(INTDIR)\denrldoc.sbr" : $(SOURCE) $(DEP_CPP_DENRL)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\addform.h"\
	".\coursese.h"\
	".\crsform.h"\
	".\DaoEnrol.h"\
	".\denrldoc.h"\
	".\MainFrm.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\ReadMe.txt
SOURCE=.\sectform.cpp
DEP_CPP_SECTF=\
	".\coursese.h"\
	".\DaoEnrol.h"\
	".\denrldoc.h"\
	".\sectform.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\sectform.obj" : $(SOURCE) $(DEP_CPP_SECTF) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\sectform.obj"	"$(INTDIR)\sectform.sbr" : $(SOURCE) $(DEP_CPP_SECTF)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\sectset.cpp
DEP_CPP_SECTS=\
	".\DaoEnrol.h"\
	".\sectset.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\sectset.obj" : $(SOURCE) $(DEP_CPP_SECTS) "$(INTDIR)"\
 "$(INTDIR)\daoenrol.pch"


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\sectset.obj"	"$(INTDIR)\sectset.sbr" : $(SOURCE) $(DEP_CPP_SECTS)\
 "$(INTDIR)" "$(INTDIR)\daoenrol.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoEnrol - Win32 Release"


"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daoenrol.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/daoenrol.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "DaoEnrol - Win32 Debug"


"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\daoenrol.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/daoenrol.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\addform.h
SOURCE=.\coursese.h
SOURCE=.\crsform.h
SOURCE=.\DaoEnrol.h
SOURCE=.\denrldoc.h
SOURCE=.\MainFrm.h
SOURCE=.\sectform.h
SOURCE=.\sectset.h
SOURCE=.\StdAfx.h
SOURCE=.\res\DaoEnrol.ico
SOURCE=.\res\DaoEnrol.rc2
SOURCE=.\res\denrldoc.ico
SOURCE=.\res\Toolbar.bmp

!ENDIF 

