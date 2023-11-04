//
//	UNIWIN DDE API
//
//	(C) Programmed by Kim, Soomin, Jan 19, 1997
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
//	Counter Part: UNITEL Sangho Shim
/////////////////////////////////////////////////////////////////////////////
#ifndef __UNIDDE_H
#define __UNIDDE_H

/////////////////////////////////////////////////////////////////////////////
// UNIWIN API:	DDEAPI16.DLL, DDEAPI32.DLL
//	ordinal hint   name
//		3    0   UICleanup32		(0000101E)
//		4    1   UIDownLoad32		(0000100A)
//		1    2   UIGetUserID		(000013A3)
//		5    3   UIGetUserID32		(0000100F)
//		6    4   UIGetUserInfo32	(00001023)
//		2    5   UIGetUserName		(0000139F)
//		7    6   UIGetUserName32	(00001014)
//		8    7   UISendPacket32		(00001019)
//		9    8   UIStartup32		(00001000)
//		10   9   thk_ThunkData32	(00011B4C)

#ifdef __cplusplus
extern "C"
{
#endif

typedef WORD	(WINAPI* LPUIStartup)(HWND hWnd, LPSTR startSID, LPSTR startBILL);
typedef WORD	(* LPUICleanup)(HWND hWnd, LPSTR endSID, LPSTR endBILL);
typedef WORD	(WINAPI* LPUISendPacket)(HWND hWnd, LPSTR SID, WORD FID, LPSTR Data, LONG DataLength);
typedef LPSTR	(WINAPI* LPUIGetUserName)();
typedef LPSTR	(WINAPI* LPUIGetUserID)();
typedef WORD	(WINAPI* LPUIDownLoad)(HWND hWnd, LPSTR SID, int DownloadListNumber, LPSTR DownLoadPath);

#ifdef __cplusplus
};

#define WM_COMMREAD		(WM_USER+10)
#define UM_EXIT			(WM_USER+1003)
#define UM_DOWNLOAD		(WM_USER+532)

#endif

#endif	// __UNIDDE_H

/*
	// UNIDDE functions
	BOOL			InitUniDDE();
	BOOL			CleanupUniDDE();
	LPUIStartup		m_pUIStartup;
	LPUICleanup		m_pUICleanup;
	LPUISendPacket	m_pUISendPacket;
	LPUIGetUserName	m_pUIGetUserName;
	LPUIGetUserID	m_pUIGetUserID;
	LPUIDownLoad	m_pUIDownLoad;
	HMODULE			m_hUniDDE;
	TCHAR*			m_szServiceID;
 */