# Microsoft Developer Studio Generated NMAKE File, Based on chatter.dsp
!IF "$(CFG)" == ""
CFG=Chatter - Win32 Release
!MESSAGE No configuration specified.  Defaulting to Chatter - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Chatter - Win32 Release" && "$(CFG)" !=\
 "Chatter - Win32 Debug" && "$(CFG)" != "Chatter - Win32 Unicode Release" &&\
 "$(CFG)" != "Chatter - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "chatter.mak" CFG="Chatter - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Chatter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Chatter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Chatter - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "Chatter - Win32 Unicode Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Chatter - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\chatter.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatdoc.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Chatter.obj"
	-@erase "$(INTDIR)\chatter.pch"
	-@erase "$(INTDIR)\Chatter.res"
	-@erase "$(INTDIR)\Chatvw.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Sendvw.obj"
	-@erase "$(INTDIR)\Setupdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\chatter.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatter.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/chatter.pdb" /machine:I386 /out:"$(OUTDIR)/chatter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatdoc.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Chatter.obj" \
	"$(INTDIR)\Chatter.res" \
	"$(INTDIR)\Chatvw.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Sendvw.obj" \
	"$(INTDIR)\Setupdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\chatter.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatdoc.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Chatter.obj"
	-@erase "$(INTDIR)\chatter.pch"
	-@erase "$(INTDIR)\Chatter.res"
	-@erase "$(INTDIR)\Chatvw.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Sendvw.obj"
	-@erase "$(INTDIR)\Setupdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\chatter.exe"
	-@erase "$(OUTDIR)\chatter.ilk"
	-@erase "$(OUTDIR)\chatter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yu"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatter.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/chatter.pdb" /debug /machine:I386 /out:"$(OUTDIR)/chatter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatdoc.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Chatter.obj" \
	"$(INTDIR)\Chatter.res" \
	"$(INTDIR)\Chatvw.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Sendvw.obj" \
	"$(INTDIR)\Setupdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\chatter.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatdoc.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Chatter.obj"
	-@erase "$(INTDIR)\chatter.pch"
	-@erase "$(INTDIR)\Chatter.res"
	-@erase "$(INTDIR)\Chatvw.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Sendvw.obj"
	-@erase "$(INTDIR)\Setupdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\chatter.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yu"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniRelease/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatter.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/chatter.pdb" /machine:I386\
 /out:"$(OUTDIR)/chatter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatdoc.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Chatter.obj" \
	"$(INTDIR)\Chatter.res" \
	"$(INTDIR)\Chatvw.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Sendvw.obj" \
	"$(INTDIR)\Setupdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\chatter.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatdoc.obj"
	-@erase "$(INTDIR)\Chatsock.obj"
	-@erase "$(INTDIR)\Chatter.obj"
	-@erase "$(INTDIR)\chatter.pch"
	-@erase "$(INTDIR)\Chatter.res"
	-@erase "$(INTDIR)\Chatvw.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Sendvw.obj"
	-@erase "$(INTDIR)\Setupdlg.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\chatter.exe"
	-@erase "$(OUTDIR)\chatter.ilk"
	-@erase "$(OUTDIR)\chatter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yu"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniDebug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatter.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/chatter.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/chatter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatdoc.obj" \
	"$(INTDIR)\Chatsock.obj" \
	"$(INTDIR)\Chatter.obj" \
	"$(INTDIR)\Chatter.res" \
	"$(INTDIR)\Chatvw.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Sendvw.obj" \
	"$(INTDIR)\Setupdlg.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "Chatter - Win32 Release" || "$(CFG)" ==\
 "Chatter - Win32 Debug" || "$(CFG)" == "Chatter - Win32 Unicode Release" ||\
 "$(CFG)" == "Chatter - Win32 Unicode Debug"
SOURCE=.\Chatdoc.cpp
DEP_CPP_CHATD=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Chatvw.h"\
	".\Msg.h"\
	".\Setupdlg.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Chatdoc.obj" : $(SOURCE) $(DEP_CPP_CHATD) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Chatdoc.obj" : $(SOURCE) $(DEP_CPP_CHATD) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Chatdoc.obj" : $(SOURCE) $(DEP_CPP_CHATD) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Chatdoc.obj" : $(SOURCE) $(DEP_CPP_CHATD) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Chatsock.cpp
DEP_CPP_CHATS=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Chatsock.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Chatter.cpp
DEP_CPP_CHATT=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Chatvw.h"\
	".\Mainfrm.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Chatter.obj" : $(SOURCE) $(DEP_CPP_CHATT) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Chatter.obj" : $(SOURCE) $(DEP_CPP_CHATT) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Chatter.obj" : $(SOURCE) $(DEP_CPP_CHATT) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Chatter.obj" : $(SOURCE) $(DEP_CPP_CHATT) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Chatter.rc
DEP_RSC_CHATTE=\
	".\Res\Chatter.ico"\
	".\Res\Chatter.rc2"\
	".\Res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Chatter.res" : $(SOURCE) $(DEP_RSC_CHATTE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Chatter.res" : $(SOURCE) $(DEP_RSC_CHATTE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Chatter.res" : $(SOURCE) $(DEP_RSC_CHATTE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Chatter.res" : $(SOURCE) $(DEP_RSC_CHATTE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Chatvw.cpp
DEP_CPP_CHATV=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Chatvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Chatvw.obj" : $(SOURCE) $(DEP_CPP_CHATV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Chatvw.obj" : $(SOURCE) $(DEP_CPP_CHATV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Chatvw.obj" : $(SOURCE) $(DEP_CPP_CHATV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Chatvw.obj" : $(SOURCE) $(DEP_CPP_CHATV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Chatvw.h"\
	".\Mainfrm.h"\
	".\Sendvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Msg.cpp
DEP_CPP_MSG_C=\
	".\Msg.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Sendvw.cpp
DEP_CPP_SENDV=\
	".\Chatdoc.h"\
	".\Chatsock.h"\
	".\Chatter.h"\
	".\Sendvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Sendvw.obj" : $(SOURCE) $(DEP_CPP_SENDV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Sendvw.obj" : $(SOURCE) $(DEP_CPP_SENDV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Sendvw.obj" : $(SOURCE) $(DEP_CPP_SENDV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Sendvw.obj" : $(SOURCE) $(DEP_CPP_SENDV) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Setupdlg.cpp
DEP_CPP_SETUP=\
	".\Chatter.h"\
	".\Setupdlg.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Setupdlg.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Setupdlg.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Setupdlg.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Setupdlg.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\chatter.pch"


!ENDIF 

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Chatter - Win32 Release"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatter.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yc /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Debug"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatter.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yc"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Release"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatter.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yc\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Chatter - Win32 Unicode Debug"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatter.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatter.pch" /Yc\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\Chatdoc.h
SOURCE=.\Chatsock.h
SOURCE=.\Chatter.h
SOURCE=.\Chatvw.h
SOURCE=.\Mainfrm.h
SOURCE=.\Msg.h
SOURCE=.\Resource.h
SOURCE=.\Sendvw.h
SOURCE=.\Setupdlg.h
SOURCE=.\Stdafx.h
SOURCE=.\Res\Chatter.ico
SOURCE=.\Res\Chatter.rc2
SOURCE=.\Res\Toolbar.bmp

!ENDIF 

