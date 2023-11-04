; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUDSGenDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UDSGen.h"
LastPage=0

ClassCount=6
Class1=CUDSGenApp
Class2=CUDSGenDoc
Class3=CUDSGenView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource7=IDD_TARGETNAME (English (U.S.))
Class5=CAboutDlg
Resource3=IDD_UDSGEN_FORM
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDD_UDSGEN_FORM (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))
Class6=CTargetDlg

[CLS:CUDSGenApp]
Type=0
HeaderFile=UDSGen.h
ImplementationFile=UDSGen.cpp
Filter=N

[CLS:CUDSGenDoc]
Type=0
HeaderFile=UDSGenDoc.h
ImplementationFile=UDSGenDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_FILE_OPEN

[CLS:CUDSGenView]
Type=0
HeaderFile=UDSGenView.h
ImplementationFile=UDSGenView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CUDSGenView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=UDSGen.cpp
ImplementationFile=UDSGen.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE

[DLG:IDD_UDSGEN_FORM]
Type=1
Class=CUDSGenView

[DLG:IDD_UDSGEN_FORM (English (U.S.))]
Type=1
Class=CUDSGenView
ControlCount=7
Control1=IDC_STATIC,static,1342308353
Control2=IDC_LIST1,listbox,1352728835
Control3=IDC_STATIC,static,1342308353
Control4=IDC_TARGET,static,1342308353
Control5=IDC_PROGRESS1,msctls_progress32,1350565888
Control6=IDC_GENERATE,button,1342242816
Control7=IDC_QUIT,button,1342242816

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TARGETNAME (English (U.S.))]
Type=1
Class=CTargetDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CTargetDlg]
Type=0
HeaderFile=TargetDlg.h
ImplementationFile=TargetDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

