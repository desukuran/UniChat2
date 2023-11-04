; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCloseDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UC2.h"
LastPage=0

ClassCount=21
Class1=CUC2App
Class2=CUC2Doc
Class3=CUC2View
Class4=CMainFrame
ResourceCount=37
Resource1=IDD_INPUT_PASSWORD
Resource2=CG_IDD_CONTROLPANEL (Korean)
Class5=CAboutDlg
Class6=CSplashWnd
Class7=CUC2Panel
Class8=CCBSend
Resource3=IDD_PP_MEMBER1
Class9=CLoginDlg
Resource4=CG_IDD_CONTROLPANEL
Class10=CCloseDlg
Class11=CEditSend
Resource5=IDD_CLOSE
Resource6=IDD_DIALOG_WHISPER
Class12=CUC2History
Resource7=IDD_PROGRESS_DIALOG
Resource8=IDR_MENU_ACTOR_OTHER
Class13=CPPActor
Class14=CPPChannel
Class15=CPPCreateChannel
Class16=CPSJoinChannel
Resource9=IDD_DLG_MEMBER
Resource10=IDD_PP_CREATE_CHANNEL
Resource11=CG_IDD_HISTORYPANEL
Resource12=IDD_PP_ACTOR
Resource13=IDR_MENU_ACTOR_OTHER (Korean)
Class17=CMemberListDlg
Class18=CInputPassword
Resource14=IDD_DIALOG_LOGIN
Class19=CWhisperDlg
Resource15=IDR_MENU_ACTOR (Korean)
Class20=CProgressDlg
Resource16=CG_IDD_HISTORYPANEL (English (U.S.))
Class21=CInputIntDlg
Resource17=IDD_PP_CHANNEL
Resource18=IDD_PP_MEMBER2
Resource19=IDR_MENU_ACTOR
Resource20=IDD_INPUT_INT
Resource21=IDD_PP_CHANNEL (English (U.S.))
Resource22=IDR_MENU_ACTOR (English (U.S.))
Resource23=IDR_MENU_ACTOR_OTHER (English (U.S.))
Resource24=IDD_PP_CREATE_CHANNEL (English (U.S.))
Resource25=IDD_CLOSE (English (U.S.))
Resource26=IDD_DIALOG_WHISPER (English (U.S.))
Resource27=IDD_DLG_MEMBER (English (U.S.))
Resource28=IDD_PP_MEMBER1 (English (U.S.))
Resource29=IDD_PP_MEMBER2 (English (U.S.))
Resource30=IDD_PROGRESS_DIALOG (English (U.S.))
Resource31=IDR_MAINFRAME (English (U.S.))
Resource32=CG_IDD_CONTROLPANEL (English (U.S.))
Resource33=IDD_DIALOG_LOGIN (English (U.S.))
Resource34=IDR_MAINFRAME
Resource35=IDD_INPUT_PASSWORD (English (U.S.))
Resource36=IDD_PP_ACTOR (English (U.S.))
Resource37=IDD_INPUT_INT (English (U.S.))

[CLS:CUC2App]
Type=0
HeaderFile=UC2.h
ImplementationFile=UC2.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CUC2App

[CLS:CUC2Doc]
Type=0
HeaderFile=UC2Doc.h
ImplementationFile=UC2Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CUC2Doc

[CLS:CUC2View]
Type=0
HeaderFile=UC2View.h
ImplementationFile=UC2View.cpp
Filter=C
LastObject=ID_EDIT_NOTEPAD
BaseClass=COSBView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDC_COMBO_SEX

[CLS:CAboutDlg]
Type=0
HeaderFile=UC2.cpp
ImplementationFile=UC2.cpp
Filter=W
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CONNECT_SYNC
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_NOTEPAD
Command8=IDC_BTN_CREATE
Command9=IDC_BTN_ROOM
Command10=IDC_BTN_MEMBER
Command11=IDC_BTN_SOUND
Command12=IDC_BTN_QUIT
Command13=IDC_BTN_HISTORY
Command14=ID_VIEW_ADJUST_WINDOW
Command15=ID_VIEW_PAUSE
Command16=ID_VIEW_BUBBLE_TEXTLIMIT
Command17=ID_VIEW_BUBBLE_TIME
Command18=ID_APP_ABOUT
Command19=ID_HELP_DEVELOPERS
Command20=ID_HELP_HOMEPAGE
Command21=ID_VIEW_DEMO
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_ACTOR_STATE_0
Command2=ID_ACTOR_ACTION_0
Command3=ID_ACTOR_ACTION_1
Command4=ID_ACTOR_ACTION_2
Command5=ID_ACTOR_ACTION_3
Command6=ID_ACTOR_ACTION_4
Command7=ID_ACTOR_ACTION_5
Command8=ID_ACTOR_ACTION_6
Command9=ID_ACTOR_MOVE_B
Command10=ID_EDIT_COPY
Command11=ID_ACTOR_STATE_2
Command12=ID_ACTOR_TURN_R
Command13=ID_ACTOR_ACTION_7
Command14=ID_ACTOR_STATE_1
Command15=ID_ACTOR_TURN_L
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_UNDO
Command18=ID_EDIT_CUT
Command19=ID_ACTOR_MOVE_B
Command20=ID_HELP
Command21=ID_CONTEXT_HELP
Command22=ID_NEXT_PANE
Command23=ID_PREV_PANE
Command24=ID_EDIT_COPY
Command25=ID_EDIT_PASTE
Command26=ID_ACTOR_TURN_L
Command27=ID_ACTOR_TURN_R
Command28=ID_ACTOR_MOVE_F
Command29=ID_ACTOR_MOVE_F
Command30=ID_EDIT_CUT
Command31=ID_EDIT_UNDO
CommandCount=31

[DLG:CG_IDD_CONTROLPANEL]
Type=1
Class=CUC2Panel
ControlCount=7
Control1=IDC_BTN_CREATE,button,1342177291
Control2=IDC_BTN_ROOM,button,1342177291
Control3=IDC_BTN_MEMBER,button,1342177291
Control4=IDC_BTN_SOUND,button,1342177291
Control5=IDC_BTN_HISTORY,button,1342177291
Control6=IDC_BTN_QUIT,button,1342177291
Control7=IDC_EDIT_SEND,edit,1352728772

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CSplashWnd

[CLS:CUC2Panel]
Type=0
HeaderFile=UC2Panel.h
ImplementationFile=UC2Panel.cpp
BaseClass=CDialogBar
Filter=W
VirtualFilter=WC
LastObject=IDC_BTN_HISTORY

[CLS:CCBSend]
Type=0
HeaderFile=CBSend.h
ImplementationFile=CBSend.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC
LastObject=CCBSend

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_EDIT_NICKNAME,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1484849312
Control5=IDC_CB_HOST,combobox,1344274434
Control6=IDC_ST_MESSAGE,static,1342177281
Control7=IDC_ST_SECONDS,static,1342177281

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CLoginDlg

[DLG:IDD_CLOSE]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_ST_MESSAGE,static,1342308353
Control4=IDC_ST_TIME_REPORT,static,1342177281

[CLS:CCloseDlg]
Type=0
HeaderFile=CloseDlg.h
ImplementationFile=CloseDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=CCloseDlg
VirtualFilter=dWC

[CLS:CEditSend]
Type=0
HeaderFile=EditSend.h
ImplementationFile=EditSend.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CEditSend

[MNU:IDR_MENU_ACTOR]
Type=1
Class=?
Command1=ID_ACTOR_MOVE_F
Command2=ID_ACTOR_MOVE_B
Command3=ID_ACTOR_TURN_L
Command4=ID_ACTOR_TURN_R
Command5=ID_ACTOR_ACTION_0
Command6=ID_ACTOR_ACTION_1
Command7=ID_ACTOR_ACTION_2
Command8=ID_ACTOR_ACTION_3
Command9=ID_ACTOR_ACTION_4
Command10=ID_ACTOR_ACTION_5
Command11=ID_ACTOR_ACTION_6
Command12=ID_ACTOR_ACTION_7
Command13=ID_ACTOR_STATE_0
Command14=ID_ACTOR_STATE_1
Command15=ID_ACTOR_STATE_2
Command16=ID_ACTOR_VOICE
CommandCount=16

[DLG:CG_IDD_HISTORYPANEL]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT_HISTORY,edit,1352730692

[CLS:CUC2History]
Type=0
HeaderFile=UC2History.h
ImplementationFile=UC2History.cpp
BaseClass=CDialogBar
Filter=W
LastObject=CUC2History
VirtualFilter=dWC

[DLG:IDD_PP_ACTOR]
Type=1
Class=CPPActor
ControlCount=20
Control1=IDC_LB_ACTORS,listbox,1352728577
Control2=IDC_EDIT_CHAT_ID,edit,1350631552
Control3=IDC_EDIT_UNITEL_ID,edit,1350631552
Control4=IDC_EDIT_NAME,edit,1350631552
Control5=IDC_EDIT_HOMEPAGE,edit,1350631552
Control6=IDC_COMBO_SEX,combobox,1344339970
Control7=IDC_EDIT_AGE,edit,1350631552
Control8=IDC_SPIN_AGE,msctls_updown32,1342177334
Control9=IDC_EDIT_PROFILE,edit,1350635716
Control10=IDC_STATIC,button,1342177543
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_SB_ACTOR,scrollbar,1342177280
Control20=IDC_ST_VERSION,static,1342312450

[DLG:IDD_PP_CREATE_CHANNEL]
Type=1
Class=?
ControlCount=8
Control1=IDC_EDIT_CHANNEL_NAME,edit,1350631552
Control2=IDC_LB_BACKGROUND,listbox,1352728833
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO_PUBLIC,button,1342242825
Control6=IDC_RADIO_PRIVATE,button,1342242825
Control7=IDC_EDIT_PASSWORD,edit,1350631584
Control8=IDC_STATIC,static,1342308354

[DLG:IDD_PP_CHANNEL]
Type=1
Class=?
ControlCount=7
Control1=IDC_LIST_CHANNEL,SysListView32,1350631425
Control2=IDC_BTN_MEMBER,button,1342242816
Control3=IDC_BTN_RENEW,button,1342242816
Control4=IDC_STATIC_MESSAGE,static,1342181388
Control5=IDC_STATIC_CHANNEL_COUNT,static,1350569986
Control6=IDC_BTN_MUD,button,1342242816
Control7=IDC_ST_STAGEID,static,1342312460

[CLS:CPPActor]
Type=0
HeaderFile=PPActor.h
ImplementationFile=PPActor.cpp
BaseClass=CPropertyPage
Filter=W
LastObject=CPPActor
VirtualFilter=dWC

[CLS:CPPChannel]
Type=0
HeaderFile=PPChannel.h
ImplementationFile=PPChannel.cpp
BaseClass=CPropertyPage
Filter=W
LastObject=IDC_ST_STAGEID
VirtualFilter=dWC

[CLS:CPPCreateChannel]
Type=0
HeaderFile=PPCreateChannel.h
ImplementationFile=PPCreateChannel.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPPCreateChannel
VirtualFilter=dWC

[CLS:CPSJoinChannel]
Type=0
HeaderFile=PSJoinChannel.h
ImplementationFile=PSJoinChannel.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CG_ID_VIEW_CONTROLPANEL
VirtualFilter=dWC

[DLG:IDD_INPUT_PASSWORD]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_WHISPER]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC_TO,static,1342312448

[DLG:IDD_DLG_MEMBER]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_MEMBER,SysListView32,1350631425
Control4=IDC_STATIC_MESSAGE,static,1342181376
Control5=IDC_BTN_RENEW,button,1342242816
Control6=IDC_STATIC_MEMBER_COUNT,static,1350701058
Control7=IDC_BTN_INVITE,button,1342242816

[DLG:IDD_PP_MEMBER1]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342177280
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC_NICK,static,1342246912
Control4=IDC_STATIC_REALNAME,static,1342246912
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_UNITEL_ID,static,1342312448
Control7=IDC_STATIC_SEXAGE,static,1342312448
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC_VERSION,static,1342312448

[DLG:IDD_PP_MEMBER2]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT_PROFILE,edit,1353713860

[CLS:CMemberListDlg]
Type=0
HeaderFile=MemberListDlg.h
ImplementationFile=MemberListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMemberListDlg

[CLS:CInputPassword]
Type=0
HeaderFile=InputPassword.h
ImplementationFile=InputPassword.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputPassword
VirtualFilter=dWC

[MNU:IDR_MENU_ACTOR_OTHER]
Type=1
Class=?
Command1=ID_ACTOR_VOICE
Command2=ID_WHISPER
Command3=ID_IGNORE
Command4=ID_KICKOUT
Command5=ID_MAKEHOST
Command6=ID_ACTOR_HYPERLINK
CommandCount=6

[CLS:CWhisperDlg]
Type=0
HeaderFile=WhisperDlg.h
ImplementationFile=WhisperDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CWhisperDlg
VirtualFilter=dWC

[DLG:IDD_PROGRESS_DIALOG]
Type=1
Class=?
ControlCount=6
Control1=IDCANCEL,button,1342242827
Control2=IDOK,button,1342242827
Control3=IDC_EDIT_MSG,edit,1353777348
Control4=IDC_DISPLAY,static,1342308608
Control5=IDC_PROGRESS,static,1342308352
Control6=IDC_PROGRESSBAR,msctls_progress32,1350565888

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=CProgressDlg
VirtualFilter=dWC

[DLG:IDD_INPUT_INT]
Type=1
Class=CInputIntDlg
ControlCount=4
Control1=IDC_EDIT_INT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_BTN_DEFAULT,button,1342242816

[CLS:CInputIntDlg]
Type=0
HeaderFile=InputIntDlg.h
ImplementationFile=InputIntDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputIntDlg
VirtualFilter=dWC

[MNU:IDR_MAINFRAME (Korean)]
Type=1
Command1=ID_CONNECT_SYNC
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_NOTEPAD
Command8=IDC_BTN_CREATE
Command9=IDC_BTN_ROOM
Command10=IDC_BTN_MEMBER
Command11=IDC_BTN_SOUND
Command12=IDC_BTN_QUIT
Command13=IDC_BTN_HISTORY
Command14=ID_VIEW_ADJUST_WINDOW
Command15=ID_VIEW_PAUSE
Command16=ID_VIEW_BUBBLE_TEXTLIMIT
Command17=ID_VIEW_BUBBLE_TIME
Command18=ID_HELP_FINDER
Command19=ID_APP_ABOUT
Command20=ID_HELP_HOMEPAGE
Command21=ID_VIEW_DEMO
CommandCount=21

[MNU:IDR_MENU_ACTOR (Korean)]
Type=1
Command1=ID_ACTOR_MOVE_F
Command2=ID_ACTOR_MOVE_B
Command3=ID_ACTOR_TURN_L
Command4=ID_ACTOR_TURN_R
Command5=ID_ACTOR_ACTION_0
Command6=ID_ACTOR_ACTION_1
Command7=ID_ACTOR_ACTION_2
Command8=ID_ACTOR_ACTION_3
Command9=ID_ACTOR_ACTION_4
Command10=ID_ACTOR_ACTION_5
Command11=ID_ACTOR_ACTION_6
Command12=ID_ACTOR_ACTION_7
Command13=ID_ACTOR_STATE_0
Command14=ID_ACTOR_STATE_1
Command15=ID_ACTOR_STATE_2
Command16=ID_ACTOR_VOICE
CommandCount=16

[MNU:IDR_MENU_ACTOR_OTHER (Korean)]
Type=1
Command1=ID_ACTOR_VOICE
Command2=ID_WHISPER
Command3=ID_IGNORE
Command4=ID_KICKOUT
Command5=ID_MAKEHOST
Command6=ID_ACTOR_HYPERLINK
CommandCount=6

[DLG:CG_IDD_CONTROLPANEL (Korean)]
Type=1
ControlCount=7
Control1=IDC_BTN_CREATE,button,1342177291
Control2=IDC_BTN_ROOM,button,1342177291
Control3=IDC_BTN_MEMBER,button,1342177291
Control4=IDC_BTN_SOUND,button,1342177291
Control5=IDC_BTN_HISTORY,button,1342177291
Control6=IDC_BTN_QUIT,button,1342177291
Control7=IDC_EDIT_SEND,edit,1352728772

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_CONNECT_SYNC
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_NOTEPAD
Command8=IDC_BTN_CREATE
Command9=IDC_BTN_ROOM
Command10=IDC_BTN_MEMBER
Command11=IDC_BTN_SOUND
Command12=IDC_BTN_QUIT
Command13=IDC_BTN_HISTORY
Command14=ID_VIEW_ADJUST_WINDOW
Command15=ID_VIEW_PAUSE
Command16=ID_VIEW_BUBBLE_TEXTLIMIT
Command17=ID_VIEW_BUBBLE_TIME
Command18=ID_APP_ABOUT
Command19=ID_HELP_DEVELOPERS
Command20=ID_HELP_HOMEPAGE
Command21=ID_VIEW_DEMO
CommandCount=21

[MNU:IDR_MENU_ACTOR (English (U.S.))]
Type=1
Class=?
Command1=ID_ACTOR_MOVE_F
Command2=ID_ACTOR_MOVE_B
Command3=ID_ACTOR_TURN_L
Command4=ID_ACTOR_TURN_R
Command5=ID_ACTOR_ACTION_0
Command6=ID_ACTOR_ACTION_1
Command7=ID_ACTOR_ACTION_2
Command8=ID_ACTOR_ACTION_3
Command9=ID_ACTOR_ACTION_4
Command10=ID_ACTOR_ACTION_5
Command11=ID_ACTOR_ACTION_6
Command12=ID_ACTOR_ACTION_7
Command13=ID_ACTOR_STATE_0
Command14=ID_ACTOR_STATE_1
Command15=ID_ACTOR_STATE_2
Command16=ID_ACTOR_VOICE
CommandCount=16

[MNU:IDR_MENU_ACTOR_OTHER (English (U.S.))]
Type=1
Class=?
Command1=ID_ACTOR_VOICE
Command2=ID_WHISPER
Command3=ID_IGNORE
Command4=ID_KICKOUT
Command5=ID_MAKEHOST
Command6=ID_ACTOR_HYPERLINK
CommandCount=6

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_ACTOR_STATE_0
Command2=ID_ACTOR_ACTION_0
Command3=ID_ACTOR_ACTION_1
Command4=ID_ACTOR_ACTION_2
Command5=ID_ACTOR_ACTION_3
Command6=ID_ACTOR_ACTION_4
Command7=ID_ACTOR_ACTION_5
Command8=ID_ACTOR_ACTION_6
Command9=ID_ACTOR_MOVE_B
Command10=ID_EDIT_COPY
Command11=ID_ACTOR_STATE_2
Command12=ID_ACTOR_TURN_R
Command13=ID_ACTOR_ACTION_7
Command14=ID_ACTOR_STATE_1
Command15=ID_ACTOR_TURN_L
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_UNDO
Command18=ID_EDIT_CUT
Command19=ID_ACTOR_MOVE_B
Command20=ID_HELP
Command21=ID_CONTEXT_HELP
Command22=ID_NEXT_PANE
Command23=ID_PREV_PANE
Command24=ID_EDIT_COPY
Command25=ID_EDIT_PASTE
Command26=ID_ACTOR_TURN_L
Command27=ID_ACTOR_TURN_R
Command28=ID_ACTOR_MOVE_F
Command29=ID_ACTOR_MOVE_F
Command30=ID_EDIT_CUT
Command31=ID_EDIT_UNDO
CommandCount=31

[DLG:CG_IDD_CONTROLPANEL (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_BTN_CREATE,button,1342177291
Control2=IDC_BTN_ROOM,button,1342177291
Control3=IDC_BTN_MEMBER,button,1342177291
Control4=IDC_BTN_SOUND,button,1342177291
Control5=IDC_BTN_HISTORY,button,1342177291
Control6=IDC_BTN_QUIT,button,1342177291
Control7=IDC_EDIT_SEND,edit,1352728772

[DLG:IDD_DIALOG_LOGIN (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_EDIT_NICKNAME,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1484849312
Control5=IDC_CB_HOST,combobox,1344274434
Control6=IDC_ST_MESSAGE,static,1342177281
Control7=IDC_ST_SECONDS,static,1342177281

[DLG:IDD_CLOSE (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_ST_MESSAGE,static,1342308353
Control4=IDC_ST_TIME_REPORT,static,1342177281

[DLG:CG_IDD_HISTORYPANEL (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT_HISTORY,edit,1352730692

[DLG:IDD_PP_ACTOR (English (U.S.))]
Type=1
Class=CPPActor
ControlCount=20
Control1=IDC_LB_ACTORS,listbox,1352728577
Control2=IDC_EDIT_CHAT_ID,edit,1350631552
Control3=IDC_EDIT_UNITEL_ID,edit,1350631552
Control4=IDC_EDIT_NAME,edit,1350631552
Control5=IDC_EDIT_HOMEPAGE,edit,1350631552
Control6=IDC_COMBO_SEX,combobox,1344339970
Control7=IDC_EDIT_AGE,edit,1350631552
Control8=IDC_SPIN_AGE,msctls_updown32,1342177334
Control9=IDC_EDIT_PROFILE,edit,1350635716
Control10=IDC_STATIC,button,1342177543
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_SB_ACTOR,scrollbar,1342177280
Control20=IDC_ST_VERSION,static,1342312450

[DLG:IDD_PP_CHANNEL (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_LIST_CHANNEL,SysListView32,1350631425
Control2=IDC_BTN_MEMBER,button,1342242816
Control3=IDC_BTN_RENEW,button,1342242816
Control4=IDC_STATIC_MESSAGE,static,1342181388
Control5=IDC_STATIC_CHANNEL_COUNT,static,1350569986
Control6=IDC_BTN_MUD,button,1342242816
Control7=IDC_ST_STAGEID,static,1342312460

[DLG:IDD_PP_CREATE_CHANNEL (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_EDIT_CHANNEL_NAME,edit,1350631552
Control2=IDC_LB_BACKGROUND,listbox,1352728833
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO_PUBLIC,button,1342242825
Control6=IDC_RADIO_PRIVATE,button,1342242825
Control7=IDC_EDIT_PASSWORD,edit,1350631584
Control8=IDC_STATIC,static,1342308354

[DLG:IDD_INPUT_PASSWORD (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_WHISPER (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC_TO,static,1342312448

[DLG:IDD_DLG_MEMBER (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_MEMBER,SysListView32,1350631425
Control4=IDC_STATIC_MESSAGE,static,1342181376
Control5=IDC_BTN_RENEW,button,1342242816
Control6=IDC_STATIC_MEMBER_COUNT,static,1350701058
Control7=IDC_BTN_INVITE,button,1342242816

[DLG:IDD_PP_MEMBER1 (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342177280
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC_NICK,static,1342246912
Control4=IDC_STATIC_REALNAME,static,1342246912
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_UNITEL_ID,static,1342312448
Control7=IDC_STATIC_SEXAGE,static,1342312448
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC_VERSION,static,1342312448

[DLG:IDD_PP_MEMBER2 (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT_PROFILE,edit,1353713860

[DLG:IDD_PROGRESS_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDCANCEL,button,1342242827
Control2=IDOK,button,1342242827
Control3=IDC_EDIT_MSG,edit,1353777348
Control4=IDC_DISPLAY,static,1342308608
Control5=IDC_PROGRESS,static,1342308352
Control6=IDC_PROGRESSBAR,msctls_progress32,1350565888

[DLG:IDD_INPUT_INT (English (U.S.))]
Type=1
Class=CInputIntDlg
ControlCount=4
Control1=IDC_EDIT_INT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_BTN_DEFAULT,button,1342242816

