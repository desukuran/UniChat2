; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGetTextDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapEd.h"
LastPage=0

ClassCount=12
Class1=CMapEdApp
Class2=CMapEdDoc
Class3=CMapEdView
Class4=CMainFrame

ResourceCount=30
Resource1=IDD_ENVIRONMENT
Resource2=IDD_PALETTE (English (U.S.))
Class5=CAboutDlg
Resource3=IDD_GETSTRING
Resource4=IDD_GETINT
Class6=CMapListView
Resource5=IDD_PALETTE
Resource6=IDR_MAINFRAME
Resource7=IDD_DIALOG_VIEW
Class7=CMapEnvDlg
Class8=CPalDlg
Resource8=IDD_ABOUTBOX
Class9=CCloseDlg
Class10=CElevDlg
Class11=CGetIntDlg
Resource9=IDR_MENU_TILE
Class12=CGetTextDlg
Resource10=IDD_CLOSE
Resource11=IDR_MENU_GRID
Resource12=IDD_GETINT (English (U.S.))
Resource13=IDD_ENVIRONMENT (English (U.S.))
Resource14=IDD_CLOSE (English (U.S.))
Resource15=IDD_GETSTRING (English (U.S.))
Resource16=IDR_MENU_TILE (English (U.S.))
Resource17=IDR_MENU_GRID (English (U.S.))
Resource18=IDD_ABOUTBOX (English (U.S.))
Resource19=IDD_DIALOG_VIEW (English (U.S.))
Resource20=IDR_MAINFRAME (English (U.S.))
Resource21=IDD_ABOUTBOX (âpåÍ (±“ÿ∂))
Resource22=IDD_DIALOG_VIEW (âpåÍ (±“ÿ∂))
Resource23=IDD_PALETTE (âpåÍ (±“ÿ∂))
Resource24=IDD_ENVIRONMENT (âpåÍ (±“ÿ∂))
Resource25=IDD_CLOSE (âpåÍ (±“ÿ∂))
Resource26=IDD_GETINT (âpåÍ (±“ÿ∂))
Resource27=IDD_GETSTRING (âpåÍ (±“ÿ∂))
Resource28=IDR_MENU_TILE (âpåÍ (±“ÿ∂))
Resource29=IDR_MENU_GRID (âpåÍ (±“ÿ∂))
Resource30=IDR_MAINFRAME (âpåÍ (±“ÿ∂))

[CLS:CMapEdApp]
Type=0
HeaderFile=MapEd.h
ImplementationFile=MapEd.cpp
Filter=N
LastObject=CMapEdApp

[CLS:CMapEdDoc]
Type=0
HeaderFile=MapEdDoc.h
ImplementationFile=MapEdDoc.cpp
Filter=N
LastObject=ID_MENU_ENTRY_POINT
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMapEdView]
Type=0
HeaderFile=MapEdView.h
ImplementationFile=MapEdView.cpp
Filter=W
BaseClass=COSBView
VirtualFilter=VWC
LastObject=CMapEdView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_MENU_ELEVATION



[CLS:CAboutDlg]
Type=0
HeaderFile=MapEd.cpp
ImplementationFile=MapEd.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_MODE
Command11=ID_EDIT_TILE_COORD
Command12=ID_EDIT_STAND
Command13=ID_EDIT_CREATE_MODE
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_GRID
Command21=ID_VIEW_EARTH
Command22=ID_VIEW_GRAPH
Command23=ID_VIEW_EA_GRAPH
Command24=ID_VIEW_PALETTE
Command25=ID_VIEW_NOELEV
Command26=ID_VIEW_MAP_ONLY
Command27=ID_VIEW_PAUSE
Command28=ID_OPTIONS_ENV
Command29=ID_MENU_STAGE_TITLE
Command30=ID_MENU_STAGE_MUSIC
Command31=ID_MENU_RECALC_DA
Command32=ID_MENU_SYNC_EA
Command33=ID_MENU_ELEVATION
Command34=ID_APP_ABOUT
CommandCount=34

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
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

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

[DLG:IDD_DIALOG_VIEW]
Type=1
Class=CMapListView
ControlCount=3
Control1=IDC_LIST_OBJ,SysListView32,1350633477
Control2=IDC_ST_CELL_INFO,static,1342312448
Control3=IDC_SB_CELL_ID,scrollbar,1342177280

[CLS:CMapListView]
Type=0
HeaderFile=MapListView.h
ImplementationFile=MapListView.cpp
BaseClass=CFormView
Filter=W
LastObject=CMapListView
VirtualFilter=VWC

[MNU:IDR_MENU_TILE]
Type=1
Class=?
Command1=ID_SPRITE_DELETE
Command2=ID_SPRITE_FLIP
Command3=ID_SPRITE_VERTICAL
Command4=ID_SPRITE_FLIPVERT
Command5=ID_SPRITE_ELEVATION
Command6=ID_SPRITE_OPACITY100
Command7=ID_SPRITE_OPACITY75
Command8=ID_SPRITE_OPACITY50
Command9=ID_SPRITE_OPACITY25
Command10=ID_SPRITE_OPACITY12
Command11=ID_MENU_NOANI
Command12=ID_MENU_ANI_REPEAT
Command13=ID_MENU_ANI_FADE
Command14=ID_MENU_ANI_RANDOM
Command15=ID_MENU_EXIT_POINT
Command16=ID_MENU_ENTRY_POINT
CommandCount=16

[DLG:IDD_PALETTE]
Type=1
Class=CPalDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SB_PAL_RED,scrollbar,1342177280
Control4=IDC_SB_PAL_GREEN,scrollbar,1342177280
Control5=IDC_SB_PAL_BLUE,scrollbar,1342177280
Control6=IDC_ST_PAL_RGB,static,1342312448
Control7=IDC_CHECK_SHOW_INDEX,button,1342242819

[DLG:IDD_ENVIRONMENT]
Type=1
Class=CMapEnvDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SCREEN_W,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SCREEN_H,edit,1350631552
Control6=IDC_EDIT_TILE_W,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_TILE_H,edit,1350631552
Control9=IDC_EDIT_DATA_PATH,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_PALFILE,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[CLS:CMapEnvDlg]
Type=0
HeaderFile=MapEnvDlg.h
ImplementationFile=MapEnvDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_TILE_DELETE

[CLS:CPalDlg]
Type=0
HeaderFile=PalDlg.h
ImplementationFile=PalDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPalDlg
VirtualFilter=dWC

[DLG:IDD_CLOSE]
Type=1
Class=CCloseDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342312448

[CLS:CCloseDlg]
Type=0
HeaderFile=CloseDlg.h
ImplementationFile=CloseDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCloseDlg

[TB:IDR_MAINFRAME]
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
Command9=ID_VIEW_GRID
Command10=ID_VIEW_NOELEV
Command11=ID_VIEW_MAP_ONLY
Command12=ID_VIEW_EARTH
Command13=ID_VIEW_GRAPH
Command14=ID_VIEW_EA_GRAPH
Command15=ID_VIEW_PAUSE
Command16=ID_MENU_RECALC_DA
Command17=ID_EDIT_CREATE_MODE
Command18=ID_EDIT_MODE
Command19=ID_EDIT_TILE_COORD
Command20=ID_EDIT_STAND
CommandCount=20

[CLS:CElevDlg]
Type=0
HeaderFile=ElevDlg.h
ImplementationFile=ElevDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_SPRITE_OPACITY75

[DLG:IDD_GETINT]
Type=1
Class=CGetIntDlg
ControlCount=7
Control1=IDC_EDIT_NEW_INT,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177334
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_ST_CURRENT_INT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CGetIntDlg]
Type=0
HeaderFile=GetIntDlg.h
ImplementationFile=GetIntDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_GETSTRING]
Type=1
Class=CGetTextDlg
ControlCount=3
Control1=IDC_EDIT_STRING,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CGetTextDlg]
Type=0
HeaderFile=GetTextDlg.h
ImplementationFile=GetTextDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_STRING

[MNU:IDR_MENU_GRID]
Type=1
Class=?
Command1=ID_MENU_DA_FR
Command2=ID_MENU_DA_FL
Command3=ID_MENU_DA_BR
Command4=ID_MENU_DA_BL
Command5=ID_MENU_DA_OPEN
Command6=ID_MENU_DA_CLOSED
CommandCount=6

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

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
Command9=ID_VIEW_GRID
Command10=ID_VIEW_NOELEV
Command11=ID_VIEW_MAP_ONLY
Command12=ID_VIEW_EARTH
Command13=ID_VIEW_GRAPH
Command14=ID_VIEW_EA_GRAPH
Command15=ID_VIEW_PAUSE
Command16=ID_MENU_RECALC_DA
Command17=ID_EDIT_CREATE_MODE
Command18=ID_EDIT_MODE
Command19=ID_EDIT_TILE_COORD
Command20=ID_EDIT_STAND
CommandCount=20

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
Command10=ID_EDIT_MODE
Command11=ID_EDIT_TILE_COORD
Command12=ID_EDIT_STAND
Command13=ID_EDIT_CREATE_MODE
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_GRID
Command21=ID_VIEW_EARTH
Command22=ID_VIEW_GRAPH
Command23=ID_VIEW_EA_GRAPH
Command24=ID_VIEW_PALETTE
Command25=ID_VIEW_NOELEV
Command26=ID_VIEW_MAP_ONLY
Command27=ID_VIEW_PAUSE
Command28=ID_OPTIONS_ENV
Command29=ID_MENU_STAGE_TITLE
Command30=ID_MENU_STAGE_MUSIC
Command31=ID_MENU_RECALC_DA
Command32=ID_MENU_SYNC_EA
Command33=ID_MENU_ELEVATION
Command34=ID_APP_ABOUT
CommandCount=34

[MNU:IDR_MENU_TILE (English (U.S.))]
Type=1
Class=?
Command1=ID_SPRITE_DELETE
Command2=ID_SPRITE_FLIP
Command3=ID_SPRITE_VERTICAL
Command4=ID_SPRITE_FLIPVERT
Command5=ID_SPRITE_ELEVATION
Command6=ID_SPRITE_OPACITY100
Command7=ID_SPRITE_OPACITY75
Command8=ID_SPRITE_OPACITY50
Command9=ID_SPRITE_OPACITY25
Command10=ID_SPRITE_OPACITY12
Command11=ID_MENU_NOANI
Command12=ID_MENU_ANI_REPEAT
Command13=ID_MENU_ANI_FADE
Command14=ID_MENU_ANI_RANDOM
Command15=ID_MENU_EXIT_POINT
Command16=ID_MENU_ENTRY_POINT
CommandCount=16

[MNU:IDR_MENU_GRID (English (U.S.))]
Type=1
Class=?
Command1=ID_MENU_DA_FR
Command2=ID_MENU_DA_FL
Command3=ID_MENU_DA_BR
Command4=ID_MENU_DA_BL
Command5=ID_MENU_DA_OPEN
Command6=ID_MENU_DA_CLOSED
CommandCount=6

[DLG:IDD_DIALOG_VIEW (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_LIST_OBJ,SysListView32,1350633477
Control2=IDC_ST_CELL_INFO,static,1342312448
Control3=IDC_SB_CELL_ID,scrollbar,1342177280

[DLG:IDD_PALETTE (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SB_PAL_RED,scrollbar,1342177280
Control4=IDC_SB_PAL_GREEN,scrollbar,1342177280
Control5=IDC_SB_PAL_BLUE,scrollbar,1342177280
Control6=IDC_ST_PAL_RGB,static,1342312448
Control7=IDC_CHECK_SHOW_INDEX,button,1342242819

[DLG:IDD_ENVIRONMENT (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SCREEN_W,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SCREEN_H,edit,1350631552
Control6=IDC_EDIT_TILE_W,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_TILE_H,edit,1350631552
Control9=IDC_EDIT_DATA_PATH,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_PALFILE,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_CLOSE (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342312448

[DLG:IDD_GETINT (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_EDIT_NEW_INT,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177334
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_ST_CURRENT_INT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_GETSTRING (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT_STRING,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[TB:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
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
Command9=ID_VIEW_GRID
Command10=ID_VIEW_NOELEV
Command11=ID_VIEW_MAP_ONLY
Command12=ID_VIEW_EARTH
Command13=ID_VIEW_GRAPH
Command14=ID_VIEW_EA_GRAPH
Command15=ID_VIEW_PAUSE
Command16=ID_MENU_RECALC_DA
Command17=ID_EDIT_CREATE_MODE
Command18=ID_EDIT_MODE
Command19=ID_EDIT_TILE_COORD
Command20=ID_EDIT_STAND
CommandCount=20

[MNU:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
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
Command10=ID_EDIT_MODE
Command11=ID_EDIT_TILE_COORD
Command12=ID_EDIT_STAND
Command13=ID_EDIT_CREATE_MODE
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_GRID
Command21=ID_VIEW_EARTH
Command22=ID_VIEW_GRAPH
Command23=ID_VIEW_EA_GRAPH
Command24=ID_VIEW_PALETTE
Command25=ID_VIEW_NOELEV
Command26=ID_VIEW_MAP_ONLY
Command27=ID_VIEW_PAUSE
Command28=ID_OPTIONS_ENV
Command29=ID_MENU_STAGE_TITLE
Command30=ID_MENU_STAGE_MUSIC
Command31=ID_MENU_RECALC_DA
Command32=ID_MENU_SYNC_EA
Command33=ID_MENU_ELEVATION
Command34=ID_APP_ABOUT
CommandCount=34

[MNU:IDR_MENU_TILE (âpåÍ (±“ÿ∂))]
Type=1
Class=?
Command1=ID_SPRITE_DELETE
Command2=ID_SPRITE_FLIP
Command3=ID_SPRITE_VERTICAL
Command4=ID_SPRITE_FLIPVERT
Command5=ID_SPRITE_ELEVATION
Command6=ID_SPRITE_OPACITY100
Command7=ID_SPRITE_OPACITY75
Command8=ID_SPRITE_OPACITY50
Command9=ID_SPRITE_OPACITY25
Command10=ID_SPRITE_OPACITY12
Command11=ID_MENU_NOANI
Command12=ID_MENU_ANI_REPEAT
Command13=ID_MENU_ANI_FADE
Command14=ID_MENU_ANI_RANDOM
Command15=ID_MENU_EXIT_POINT
Command16=ID_MENU_ENTRY_POINT
CommandCount=16

[MNU:IDR_MENU_GRID (âpåÍ (±“ÿ∂))]
Type=1
Class=?
Command1=ID_MENU_DA_FR
Command2=ID_MENU_DA_FL
Command3=ID_MENU_DA_BR
Command4=ID_MENU_DA_BL
Command5=ID_MENU_DA_OPEN
Command6=ID_MENU_DA_CLOSED
CommandCount=6

[DLG:IDD_ABOUTBOX (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_VIEW (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=3
Control1=IDC_LIST_OBJ,SysListView32,1350633477
Control2=IDC_ST_CELL_INFO,static,1342312448
Control3=IDC_SB_CELL_ID,scrollbar,1342177280

[DLG:IDD_PALETTE (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SB_PAL_RED,scrollbar,1342177280
Control4=IDC_SB_PAL_GREEN,scrollbar,1342177280
Control5=IDC_SB_PAL_BLUE,scrollbar,1342177280
Control6=IDC_ST_PAL_RGB,static,1342312448
Control7=IDC_CHECK_SHOW_INDEX,button,1342242819

[DLG:IDD_ENVIRONMENT (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SCREEN_W,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SCREEN_H,edit,1350631552
Control6=IDC_EDIT_TILE_W,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_TILE_H,edit,1350631552
Control9=IDC_EDIT_DATA_PATH,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_PALFILE,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_CLOSE (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342312448

[DLG:IDD_GETINT (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=7
Control1=IDC_EDIT_NEW_INT,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177334
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_ST_CURRENT_INT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_GETSTRING (âpåÍ (±“ÿ∂))]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT_STRING,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[ACL:IDR_MAINFRAME (âpåÍ (±“ÿ∂))]
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

