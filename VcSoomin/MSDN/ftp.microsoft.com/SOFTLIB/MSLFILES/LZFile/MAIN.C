//*************************************************************
//  File name: main.c
//
//  This sample demonstrates the use of the functions in LZEXPAND.DLL.
//  LZEXPAND.DLL contains functions to decompress data which was
//  previously compressed by COMPRESS.EXE, the DOS program based on the
//  Lempel-Ziv compression algorithm.
//  
//  The sample has three menu options for accessing files - Open, Copy 1,
//  and Copy Multiple.  The Open and Save As common dialogs are used get
//  the file names.  If the user selects to open a file, it is opened
//  with LZOpenFile, and read with LZRead.  If the file is compressed,
//  LZRead will decompress it.  The uncompressed file is displayed in a
//  read only edit control which fills the client area. The file is
//  closed with LZClose.
//  
//  If the user selects to copy 1 file, the source and destination are
//  opened with LZOpenFile, the source is copied (and decompressed if
//  necessary) with LZCopy, and both files are closed with LZClose.
//  
//  If the user selects to copy multiple files, the sample uses LZStart
//  to allocate memory for the multiple file copies, LZOpenFile to open
//  the source and destination files, CopyLZFile to copy, and LZClose to
//  close the files.  LZDone frees the memory allocated by LZStart.
//  
//
//  Functions:
//     WinMain - entry point
//     MainWndProc - main window procedure
//     About - About dialog box procedure
//     GetOpenFileHandle - puts up an Open common dialog, and opens 
//                         the selected file
//     GetSaveFileHandle - puts up a Save As common dialog, and opens 
//                         specified file.
//
//  LINK: lz32.lib
//
//  History:    Date       Author         Comment
//               2/13/92   Emily Brooks   Created
//
// Written by Microsoft Product Support Services, Windows Developer Support
// Copyright (c) 1992 Microsoft Corporation. All rights reserved.
//*************************************************************

#include "global.h"

HANDLE ghInst = NULL;   // instance
HWND ghWndMain = NULL;  // handle of main window
HWND ghWndEdit = NULL;  // handle of edit control filling main window's client area

char szMainMenu[] = "MainMenu";
char szMainClass[] = "MainClass";

//*************************************************************
//
//  WinMain()
//
//  Purpose:
//		Entry point for all windows apps
//
//
//  Parameters:
//      HANDLE hInstance
//      HANDLE hPrevInstance
//      LPSTR lpCmdLine
//      int nCmdShow
//      
//
//  Return: (int PASCAL)
//
//
//  Comments:
//
//
//  History:    Date       Author     Comment
//               2/16/92   EMB        Created
//
//*************************************************************

int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   MSG msg;

   if (!hPrevInstance && !InitApplication(hInstance))
      return (FALSE);

   if (!InitInstance(hInstance, nCmdShow))
      return (FALSE);

   while (GetMessage(&msg, NULL, NULL, NULL))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return (msg.wParam);
}   //*** WinMain()

//*************************************************************
//
//  MainWndProc()
//
//  Purpose:
//		Main Window procedure
//
//
//  Parameters:
//      HWND hWnd
//      unsigned msg
//      WORD wParam
//      LONG lParam
//      
//
//  Return: (long FAR PASCAL)
//
//
//  Comments:
//
//
//  History:    Date       Author     Comment
//               2/16/92   EMB        Created
//
//*************************************************************

long FAR PASCAL MainWndProc (HWND hWnd, unsigned msg, WORD wParam, LONG lParam)
{
   FARPROC lpProc;
   RECT rect;

   switch (msg)
   {
      case WM_CREATE:
      {
         // create read only edit control to display any file user opens.
         // make it fill the client area
         GetClientRect(hWnd, &rect);

         ghWndEdit = CreateWindow("edit",
                                  "",
                                  WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
                                  rect.left, rect.top, rect.right, rect.bottom,
                                  hWnd, NULL, ghInst, NULL);
      }
         break;

      case WM_SIZE:  // resize edit control to fill the resized client area
      {
         GetClientRect(hWnd, &rect);
         MoveWindow(ghWndEdit, 0, 0, rect.right, rect.bottom, TRUE);
      }
         break;

      case WM_COMMAND:
         switch (wParam)
         {
            case IDM_OPEN:  // read a possibly compressed file into the edit control
            {

               LONG lfilesize;
               char szOrigName[FILENAMELEN];
               HANDLE hFile;
               HANDLE hBuf;
               LPSTR lpBuf;
               LONG ltoread, lnumread;
               char szFileSize[LONGCHARLEN+9];


               // find out which file and open it
               hFile = GetOpenFileHandle(hWnd, (LPSTR)szOrigName, (LPSTR)"Open");
               if (hFile != -1)
               {
                  // what's the file size
                  lfilesize = LZSeek(hFile, 0L, 2);

                  // display the file name and size in the main window's caption
                  wsprintf(szFileSize, " - %ld bytes", lfilesize);
                  lstrcat(szOrigName, szFileSize);
                  SetWindowText(hWnd, szOrigName);

                  // read at most MAXREAD bytes of the file
                  ltoread = min(lfilesize,MAXREAD);
                  if (hBuf = GlobalAlloc(GMEM_MOVEABLE, ltoread + 1)) 
                  {
                     if (lpBuf = GlobalLock(hBuf))
                     {
                        LZSeek(hFile, 0L, 0);  // seek to beginning of file
                        lnumread = LZRead(hFile, lpBuf, (int)ltoread);  // read
                        lpBuf[lnumread] = '\0';

                        // display the file contents in the edit control
                        SetWindowText(ghWndEdit, lpBuf);
                        GlobalUnlock(hBuf);
                     }
                     GlobalFree(hBuf);
                  }
                  LZClose(hFile); // close the file
               }
            }
               break;

            case IDM_COPY:  // copy 1 file
            {
               char szOrigName[FILENAMELEN];
               HANDLE hSource, hDest;
               char buf[FILENAMELEN+8];


               // find out which file is to copied and open it
               if ((hSource = GetOpenFileHandle(hWnd, (LPSTR)szOrigName, (LPSTR)"Copy from")) == -1)
                  break;

               // find out destination file name, and open the file
               wsprintf(buf, "Copy %s to", (LPSTR)szOrigName);
               if ((hDest = GetSaveFileHandle(hWnd, buf)) == -1)  // abort
               {
                  LZClose(hSource);
                  break;
               }

               // copy source to dest, decompressing if necessary
               if (hSource != -1 && hDest != -1)
               {
                  LZCopy(hSource, hDest);  // copy 

                  // close both source and dest
                  LZClose(hSource);
                  LZClose(hDest);
               }
            }


               break;

            case IDM_MULTCOPY:  // copy multiple files
            {
               char szOrigName[FILENAMELEN];
               HANDLE hSource, hDest;
               char buf[FILENAMELEN+8];


               // allocate memory for multiple file copy
               LZStart();

               // find out which file is to copied and open it.
               // Do this till user hits cancel from either the Open or Save As common dialog
               while ((hSource = GetOpenFileHandle(hWnd, (LPSTR)szOrigName, (LPSTR)"Copy from")) != -1)
               {
                  // find out destination file name, and open the file
                  wsprintf(buf, "Copy %s to", (LPSTR)szOrigName);
                  if ((hDest = GetSaveFileHandle(hWnd, buf)) == -1) // abort
                  {
                     LZClose(hSource);
                     break;
                  }

                  // copy source to dest, decompressing if necessary
                  if (hSource != -1 && hDest != -1)
                  {
                     CopyLZFile(hSource, hDest);

                     // close both source and dest
                     LZClose(hSource);
                     LZClose(hDest);
                  }
               }
               // free memory allocated by LZStart
               LZDone();
            }
               break;

            case IDM_ABOUT:  // About box
               lpProc = MakeProcInstance(About, ghInst);
               DialogBox(ghInst, "AboutBox", hWnd, lpProc);
               FreeProcInstance(lpProc);
               break;
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);
         break;
   }
   return (DefWindowProc(hWnd, msg, wParam, lParam));
}   //*** MainWndProc()

//*************************************************************
//
//  About()
//
//  Purpose:
//		the About dialog box procedure
//
//
//  Parameters:
//      HWND hDlg
//      unsigned msg
//      WORD wParam
//      LONG lParam
//      
//
//  Return: (BOOL FAR PASCAL)  TRUE if message handled, FALSE otherwise
//
//
//  Comments:
//
//
//  History:    Date       Author     Comment
//              12/12/91   EMB        Created
//
//*************************************************************

BOOL FAR PASCAL About (HWND hDlg, unsigned msg, WORD wParam, LONG lParam)
{
   switch (msg)
   {
      case WM_INITDIALOG:
         return (TRUE);

      case WM_COMMAND:
         if (wParam == IDOK || wParam == IDCANCEL)
         {
            EndDialog(hDlg, TRUE);
            return (TRUE);
         }
         break;
   }
   return (FALSE); /* Didn't process a message    */
}   //*** About()


//*************************************************************
//
//  GetOpenFileHandle
//
//  Purpose:
//    Puts up an Open common dialog.  Opens the
//    file the user specifies with LZOpenFile.  
//      
//
//
//  Parameters:
//      HWND hWnd - handle of common dialog's owner
//      LPSTR szOrigName - original file name of opened file
//      LPSTR szTitle - title to be displayed in the common dialog
//      
//
//  Return: (HANDLE FAR) Handle to the opened file.
//
//
//  Comments:
//
//
//  History:    Date       Author          Comment
//               2/16/92   EMB             created
//
//*************************************************************

HANDLE FAR GetOpenFileHandle (HWND hWnd, LPSTR szOrigName, LPSTR szTitle)
{
   HANDLE ret;
   OFSTRUCT ofStructSrc;
   OPENFILENAME ofn;
   char szFile[FILENAMELEN];

   szOrigName[0] = '\0';

   /* Initialize the OPENFILENAME members */
   memset(&ofn, 0, sizeof(OPENFILENAME));
   szFile[0] = '\0';
   ofn.lStructSize = sizeof(OPENFILENAME);
   ofn.hwndOwner = hWnd;
   ofn.hInstance = ghInst;
   ofn.lpstrFilter = (LPSTR)"All Files (*.*)\0*.*\0";
   ofn.lpstrCustomFilter = (LPSTR)NULL;
   ofn.nMaxCustFilter = 0L;
   ofn.nFilterIndex = 0L;
   ofn.lpstrFile = szFile;
   ofn.nMaxFile = FILENAMELEN;
   ofn.lpstrTitle = szTitle;
   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
   ofn.lpstrDefExt = (LPSTR)NULL;

   // put up the Open common dialog
   if (GetOpenFileName(&ofn))
   {
      // try to open the file
      ret = LZOpenFile(ofn.lpstrFile, (LPOFSTRUCT)&ofStructSrc, OF_READ);

      // get the expanded name of the compressed file 
      GetExpandedName(ofn.lpstrFile, szOrigName);

      return (ret);
   }
   else
      return -1;
}


//*************************************************************
//
//  GetSaveFileHandle
//
//  Purpose:
//    Puts up a Save As common dialog.  Tries to open the 
//    file the user specifies with LZOpenFile.  
//      
//
//
//  Parameters:
//      HWND hWnd - handle of common dialog's owner
//      LPSTR szTitle - title to be displayed in the common dialog
//      
//
//  Return: (HANDLE FAR) - Handle to the file to be saved to.
//
//
//  Comments:
//
//
//  History:    Date       Author          Comment
//               2/16/92   EMB             Created
//
//*************************************************************

HANDLE FAR GetSaveFileHandle (HWND hWnd, LPSTR szTitle)
{
   OPENFILENAME ofn;
   char szFile[FILENAMELEN];
   OFSTRUCT ofStructSrc;

   /* Initialize the OPENFILENAME members */

   memset(&ofn, 0, sizeof(OPENFILENAME));
   szFile[0] = '\0';
   ofn.lStructSize = sizeof(OPENFILENAME);
   ofn.hwndOwner = hWnd;
   ofn.hInstance    = ghInst;
   ofn.lpstrFilter = (LPSTR)NULL;
   ofn.lpstrCustomFilter = (LPSTR)NULL;
   ofn.nMaxCustFilter = 0L;
   ofn.nFilterIndex = 0L;
   ofn.lpstrFile = szFile;
   ofn.nMaxFile = FILENAMELEN;
   ofn.lpstrTitle = szTitle;
   ofn.Flags = OFN_OVERWRITEPROMPT;

   // put up the Save As common dialog
   if (GetSaveFileName(&ofn))
   {
      // try to open the file
      return (LZOpenFile(ofn.lpstrFile, (LPOFSTRUCT)&ofStructSrc, OF_READWRITE | OF_CREATE));
   }
   else
      return -1;
}
//*** EOF: main.c
