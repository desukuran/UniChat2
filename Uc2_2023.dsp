# Microsoft Developer Studio Project File - Name="Uc2_2023" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Uc2_2023 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Uc2_2023.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Uc2_2023.mak" CFG="Uc2_2023 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Uc2_2023 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Uc2_2023 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Uc2_2023 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ENGLISH" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 UC2Ani/Release/UC2Ani.lib winmm.lib lz32.lib CSGUID.lib ChatSock.lib uuid.lib /nologo /subsystem:windows /machine:I386 /out:"Release/UC2.exe"

!ELSEIF  "$(CFG)" == "Uc2_2023 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_ENGLISH" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 UC2Ani/Debug/UC2Ani.lib winmm.lib lz32.lib CSGUID.lib ChatSock.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Uc2_2023 - Win32 Release"
# Name "Uc2_2023 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Actor.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseChan.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseSock.cpp
# End Source File
# Begin Source File

SOURCE=.\Behavior.cpp
# End Source File
# Begin Source File

SOURCE=.\CloseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\EditSend.cpp
# End Source File
# Begin Source File

SOURCE=.\InputIntDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\PPActor.cpp
# End Source File
# Begin Source File

SOURCE=.\PPChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\PPCreateChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\PPMemberInfo1.cpp
# End Source File
# Begin Source File

SOURCE=.\Prog.Cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PSFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\PSJoinChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\PSMemberInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ResMan.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\Stage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Uc2_2023 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Uc2_2023 - Win32 Debug"

# ADD CPP /Yc

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TileMap.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2.rc
# End Source File
# Begin Source File

SOURCE=.\Uc2cs.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2History.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2Panel.cpp
# End Source File
# Begin Source File

SOURCE=.\UC2View.cpp
# End Source File
# Begin Source File

SOURCE=.\WhisperDlg.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\ARROW_LB.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\ARROW_LT.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\ARROW_RB.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\ARROW_RT.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\BITMAP1.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\BMP00001.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\HARROW.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\HGREP_DO.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\UC2.ico
# End Source File
# Begin Source File

SOURCE=.\RES\UC2.RC2
# End Source File
# Begin Source File

SOURCE=.\RES\UC2Doc.ico
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Actor.h
# End Source File
# Begin Source File

SOURCE=.\BaseChan.h
# End Source File
# Begin Source File

SOURCE=.\BaseSock.h
# End Source File
# Begin Source File

SOURCE=.\Behavior.h
# End Source File
# Begin Source File

SOURCE=.\CloseDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditHistory.h
# End Source File
# Begin Source File

SOURCE=.\EditSend.h
# End Source File
# Begin Source File

SOURCE=.\InputIntDlg.h
# End Source File
# Begin Source File

SOURCE=.\InputPassword.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MemberInfo.h
# End Source File
# Begin Source File

SOURCE=.\MemberListDlg.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\PPActor.h
# End Source File
# Begin Source File

SOURCE=.\PPChannel.h
# End Source File
# Begin Source File

SOURCE=.\PPCreateChannel.h
# End Source File
# Begin Source File

SOURCE=.\PPMemberInfo1.h
# End Source File
# Begin Source File

SOURCE=.\Prog.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\PSFrame.h
# End Source File
# Begin Source File

SOURCE=.\PSJoinChannel.h
# End Source File
# Begin Source File

SOURCE=.\PSMemberInfo.h
# End Source File
# Begin Source File

SOURCE=.\ResMan.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\Stage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TileMap.h
# End Source File
# Begin Source File

SOURCE=.\UC2.h
# End Source File
# Begin Source File

SOURCE=.\UC2CS.H
# End Source File
# Begin Source File

SOURCE=.\UC2Doc.h
# End Source File
# Begin Source File

SOURCE=.\UC2History.h
# End Source File
# Begin Source File

SOURCE=.\UC2Messages.h
# End Source File
# Begin Source File

SOURCE=.\UC2Panel.h
# End Source File
# Begin Source File

SOURCE=.\UC2View.h
# End Source File
# Begin Source File

SOURCE=.\WhisperDlg.h
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
