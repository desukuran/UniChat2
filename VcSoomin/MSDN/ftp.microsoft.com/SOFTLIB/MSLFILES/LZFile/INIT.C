//*************************************************************
//  File name: init.c
//
//  Description: 
//      Initializes the app and instance
//
//  History:    Date       Author          Comment
//              2/12/91    Emily Brooks    Created
//
// Written by Microsoft Product Support Services, Windows Developer Support
// Copyright (c) 1992 Microsoft Corporation. All rights reserved.
//*************************************************************

#include "global.h"

//*************************************************************
//
//  InitApplication()
//
//  Purpose:
//		Initializes the application (window classes)
//
//
//  Parameters:
//      HANDLE hInstance - hInstance from WinMain
//      
//
//  Return: (BOOL) TRUE if class was created
//                 FALSE otherwise                   
//
//
//  Comments:
//
//
//  History:    Date       Author     Comment
//               2/12/91   EMB        Created
//
//*************************************************************

BOOL InitApplication (HANDLE hInstance)
{
   WNDCLASS wc;

   wc.style = NULL;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = LoadIcon(hInstance, "MAINICON");
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = COLOR_APPWORKSPACE + 1;
   wc.lpszMenuName = szMainMenu;
   wc.lpszClassName = szMainClass;

   if (!RegisterClass(&wc))
      return FALSE;

   return TRUE;
}   //*** InitApplication()

//*************************************************************
//
//  InitInstance()
//
//  Purpose:
//		Initializes each instance (window creation)
//
//
//  Parameters:
//      HANDLE hInstance
//      int nCmdShow
//      
//
//  Return: (BOOL) TRUE if window was created
//                 FALSE otherwise                   
//
//
//  Comments:
//
//
//  History:    Date       Author     Comment
//               2/12/91   EMB        Created
//
//*************************************************************

BOOL InitInstance (HANDLE hInstance, int nCmdShow)
{
   ghInst = hInstance;

   ghWndMain = CreateWindow(szMainClass,
                            "LZFile Sample Application",
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                            NULL, NULL, hInstance, NULL);

   if (!ghWndMain)
      return (FALSE);

   ShowWindow(ghWndMain, nCmdShow);
   UpdateWindow(ghWndMain);
   return (TRUE);
}   //*** InitInstance()

//*** EOF: init.c
