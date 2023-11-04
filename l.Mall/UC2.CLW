; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUC2View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UC2.h"
LastPage=0

ClassCount=25
Class1=CUC2App
Class2=CUC2Doc
Class3=CUC2View
Class4=CMainFrame
ResourceCount=42
Resource1=IDD_DIALOG_LOGIN
Resource2=IDD_PP_PAYMENT
Class5=CAboutDlg
Class6=CSplashWnd
Class7=CUC2Panel
Class8=CCBSend
Resource3=CG_IDD_CONTROLPANEL
Class9=CLoginDlg
Resource4=IDD_INPUT_INT
Class10=CCloseDlg
Class11=CEditSend
Resource5=IDD_PP_CREATE_CHANNEL
Resource6=IDD_DLG_ANI
Class12=CUC2History
Resource7=IDD_DLG_PDA
Resource8=IDD_PP_MEMBER2
Class13=CPPActor
Class14=CPPChannel
Class15=CPPCreateChannel
Class16=CPSJoinChannel
Resource9=IDD_PP_CART
Resource10=IDR_MENU_ACTOR
Resource11=IDR_MENU_ACTOR_OTHER
Resource12=IDD_DLG_MEMBER
Resource13=IDD_PP_ACTOR
Class17=CMemberListDlg
Class18=CInputPassword
Resource14=IDD_PROGRESS_DIALOG
Class19=CWhisperDlg
Resource15=IDD_PP_MEMBER1
Class20=CProgressDlg
Resource16=IDD_CLOSE
Class21=CInputIntDlg
Resource17=IDD_PP_CHANNEL
Resource18=IDD_DIALOG_WHISPER
Resource19=IDD_INPUT_PASSWORD
Resource20=CG_IDD_HISTORYPANEL
Class22=CPPShoppingCart
Class23=CPPPaymentInfo
Class24=CDlgPDA
Class25=CDlgAni
Resource21=IDR_MAINFRAME
Resource22=IDD_INPUT_INT (English (U.S.))
Resource23=IDR_MENU_ACTOR (English (U.S.))
Resource24=IDR_MENU_ACTOR_OTHER (English (U.S.))
Resource25=IDD_PP_PAYMENT (English (U.S.))
Resource26=IDD_PP_CART (English (U.S.))
Resource27=IDD_DLG_PDA (English (U.S.))
Resource28=IDR_MAINFRAME (English (U.S.))
Resource29=CG_IDD_CONTROLPANEL (English (U.S.))
Resource30=IDD_DIALOG_LOGIN (English (U.S.))
Resource31=IDD_CLOSE (English (U.S.))
Resource32=CG_IDD_HISTORYPANEL (English (U.S.))
Resource33=IDD_PP_ACTOR (English (U.S.))
Resource34=IDD_PP_CHANNEL (English (U.S.))
Resource35=IDD_PP_CREATE_CHANNEL (English (U.S.))
Resource36=IDD_INPUT_PASSWORD (English (U.S.))
Resource37=IDD_DIALOG_WHISPER (English (U.S.))
Resource38=IDD_DLG_MEMBER (English (U.S.))
Resource39=IDD_PP_MEMBER1 (English (U.S.))
Resource40=IDD_PP_MEMBER2 (English (U.S.))
Resource41=IDD_PROGRESS_DIALOG (English (U.S.))
Resource42=IDD_DLG_ANI (English (U.S.))

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
LastObject=ID_VIEW_PDA_MUSIC
BaseClass=COSBView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDC_BTN_CREATE

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
Command14=ID_VIEW_PDA
Command15=ID_VIEW_PDA_MUSIC
Command16=ID_VIEW_TITANIC
Command17=ID_VIEW_MAP
Command18=ID_VIEW_IM
Command19=ID_VIEW_ADJUST_WINDOW
Command20=ID_VIEW_PAUSE
Command21=ID_VIEW_BUBBLE_TEXTLIMIT
Command22=ID_VIEW_BUBBLE_TIME
Command23=ID_APP_ABOUT
Command24=ID_HELP_HOMEPAGE
Command25=ID_VIEW_DEMO
CommandCount=25

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
Class=CLoginDlg
ControlCount=7
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_EDIT_NICKNAME,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1350631584
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
Class=CCloseDlg
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
Class=?
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
Class=CPPChannel
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
LastObject=CPPChannel
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
Class=CInputPassword
ControlCount=3
Control1=IDC_EDIT_PASSWORD,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_WHISPER]
Type=1
Class=CWhisperDlg
ControlCount=4
Control1=IDC_EDIT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC_TO,static,1342312448

[DLG:IDD_DLG_MEMBER]
Type=1
Class=CMemberListDlg
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

[DLG:IDD_PP_PAYMENT]
Type=1
Class=?
ControlCount=43
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_EDIT_CARDNUM,edit,1350631552
Control4=IDC_EDIT_EXPDATE,edit,1350631552
Control5=IDC_EDIT4,edit,1350631552
Control6=IDC_EDIT5,edit,1350631552
Control7=IDC_EDIT6,edit,1350631552
Control8=IDC_EDIT7,edit,1350631552
Control9=IDC_EDIT10,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT11,edit,1350631552
Control12=IDC_EDIT9,edit,1350631552
Control13=IDC_EDIT12,edit,1350631552
Control14=IDC_EDIT13,edit,1350631552
Control15=IDC_EDIT14,edit,1350631552
Control16=IDC_EDIT17,edit,1350631552
Control17=IDC_EDIT15,edit,1350631552
Control18=IDC_EDIT18,edit,1350631552
Control19=IDC_EDIT16,edit,1350631552
Control20=IDC_EDIT19,edit,1350631552
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352

[DLG:IDD_PP_CART]
Type=1
Class=?
ControlCount=2
Control1=IDC_CART,SysListView32,1350631425
Control2=IDC_STATIC,button,1342177287

[CLS:CPPShoppingCart]
Type=0
HeaderFile=PPShoppingCart.h
ImplementationFile=PPShoppingCart.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPPShoppingCart

[CLS:CPPPaymentInfo]
Type=0
HeaderFile=PPPaymentInfo.h
ImplementationFile=PPPaymentInfo.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPPPaymentInfo

[DLG:IDD_DLG_PDA]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242827
Control2=IDC_PDA_BTN_MORE,button,1342242827
Control3=IDC_PDA_BTN_BUY,button,1342242827
Control4=IDC_PDA_BTN_AUTO,button,1342242827
Control5=IDC_PDA_BTN_LEFT,button,1342242827
Control6=IDC_PDA_BTN_RIGHT,button,1342242827

[CLS:CDlgPDA]
Type=0
HeaderFile=DlgPDA.h
ImplementationFile=DlgPDA.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CDlgPDA

[DLG:IDD_DLG_ANI]
Type=1
Class=CDlgAni
ControlCount=0

[CLS:CDlgAni]
Type=0
HeaderFile=DlgAni.h
ImplementationFile=DlgAni.cpp
BaseClass=CDialog
Filter=W
LastObject=ID_VIEW_PDA
VirtualFilter=dWC

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
Command14=ID_VIEW_PDA
Command15=ID_VIEW_PDA_MUSIC
Command16=ID_VIEW_TITANIC
Command17=ID_VIEW_MAP
Command18=ID_VIEW_IM
Command19=ID_VIEW_ADJUST_WINDOW
Command20=ID_VIEW_PAUSE
Command21=ID_VIEW_BUBBLE_TEXTLIMIT
Command22=ID_VIEW_BUBBLE_TIME
Command23=ID_APP_ABOUT
Command24=ID_HELP_HOMEPAGE
Command25=ID_VIEW_DEMO
CommandCount=25

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
Control4=IDC_EDIT_PASSWORD,edit,1350631584
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
Class=?
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
Class=?
ControlCount=4
Control1=IDC_EDIT_INT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_BTN_DEFAULT,button,1342242816

[DLG:IDD_PP_PAYMENT (English (U.S.))]
Type=1
Class=?
ControlCount=43
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_EDIT_CARDNUM,edit,1350631552
Control4=IDC_EDIT_EXPDATE,edit,1350631552
Control5=IDC_EDIT4,edit,1350631552
Control6=IDC_EDIT5,edit,1350631552
Control7=IDC_EDIT6,edit,1350631552
Control8=IDC_EDIT7,edit,1350631552
Control9=IDC_EDIT10,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT11,edit,1350631552
Control12=IDC_EDIT9,edit,1350631552
Control13=IDC_EDIT12,edit,1350631552
Control14=IDC_EDIT13,edit,1350631552
Control15=IDC_EDIT14,edit,1350631552
Control16=IDC_EDIT17,edit,1350631552
Control17=IDC_EDIT15,edit,1350631552
Control18=IDC_EDIT18,edit,1350631552
Control19=IDC_EDIT16,edit,1350631552
Control20=IDC_EDIT19,edit,1350631552
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352

[DLG:IDD_PP_CART (English (U.S.))]
Type=1
Class=?
ControlCount=2
Control1=IDC_CART,SysListView32,1350631425
Control2=IDC_STATIC,button,1342177287

[DLG:IDD_DLG_PDA (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242827
Control2=IDC_PDA_BTN_MORE,button,1342242827
Control3=IDC_PDA_BTN_BUY,button,1342242827
Control4=IDC_PDA_BTN_AUTO,button,1342242827
Control5=IDC_PDA_BTN_LEFT,button,1342242827
Control6=IDC_PDA_BTN_RIGHT,button,1342242827

[DLG:IDD_DLG_ANI (English (U.S.))]
Type=1
Class=?
ControlCount=0

