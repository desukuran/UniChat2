; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProgressDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Progress.h"

ClassCount=3
Class1=CProgressApp
Class2=CProgressDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_PROGRESS_DIALOG

[CLS:CProgressApp]
Type=0
HeaderFile=Progress.h
ImplementationFile=Progress.cpp
Filter=N

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DISPLAY

[CLS:CAboutDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
Filter=D

[DLG:IDD_PROGRESS_DIALOG]
Type=1
Class=CProgressDlg
ControlCount=6
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_DISPLAY,static,1342308608
Control4=IDC_PROGRESS,static,1342308352
Control5=IDC_PROGRESSBAR,msctls_progress32,1350565888
Control6=IDC_EDIT_MSG,edit,1353777348

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

