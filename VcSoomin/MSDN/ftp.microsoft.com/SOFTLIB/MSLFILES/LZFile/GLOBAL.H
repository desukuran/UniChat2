//*************************************************************
//  File name: global.h
//
//  Description: 
//      Global include file for #defines and prototypes
//
//  History:    Date       Author     Comment
//               2/16/92   EMB        Created
//                 
//  Copyright (c) 1992 Microsoft Corporation. All rights reserved.
//*************************************************************

#include <windows.h>
#include <lzexpand.h>
#include <commdlg.h>
#include <memory.h>

//*** Constants
#define FILENAMELEN 68
        // 64 (max MS DOS path+filename length) + 3 (drive) + 1 (NULL terminator)
#define LONGCHARLEN 12
        // number of chars needed for "longest" long (-2147483648) + NULL terminator
#define MAXREAD 4000
        // maximum bytes to read from file
   
//*** Menu Defines
    #define IDM_ABOUT 200
    #define IDM_OPEN 201
    #define IDM_COPY 202
    #define IDM_MULTCOPY 203


//*** Function Prototypes
//*** Main.c
    int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
    long FAR PASCAL MainWndProc(HWND, unsigned, WORD, LONG);
    BOOL FAR PASCAL About(HWND, unsigned, WORD, LONG);
    HANDLE FAR GetOpenFileHandle(HWND,LPSTR,LPSTR);
    HANDLE FAR GetSaveFileHandle(HWND,LPSTR);

//*** Init.c
    BOOL InitApplication(HANDLE);
    BOOL InitInstance(HANDLE, int);

//*** EXTERNS for Global Variables
    extern HANDLE       ghInst;
    extern HWND         ghWndMain;
    extern HWND ghWndEdit;

    extern char         szMainMenu[];
    extern char         szMainClass[];

//*** EOF: global.h
