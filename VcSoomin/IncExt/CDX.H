//////////////////////////////////////////////////////////////////////////////////
// Project Name: [ CDX Class Library - CDX.lib ]
// Source File:  [ CDX Main header file ]
// Author:       [ Danny Farley - danny@jags.co.uk ]
// Revision:     [ 1.5 ]
//////////////////////////////////////////////////////////////////////////////////
#ifndef CDX_H
#define CDX_H

#pragma warning (disable : 4244)

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <dplay.h>
#include <dplobby.h>
#include <vfw.h>

//////////////////////////////////////////////////////////////////////////////////
// Globals
//////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	// CDX Functions
	extern void Clip(int *DestX, int *DestY, RECT *SrcRect, RECT *DestRect);

	// DDUTILS Functions
	extern IDirectDrawPalette* DDLoadPalette(IDirectDraw2 *pdd, LPCSTR szBitmap);
	extern IDirectDrawSurface* DDLoadBitmap(IDirectDraw2 *pdd, LPCSTR szBitmap, int dx, int dy);
	extern IDirectDrawSurface* DDLoadSizeBitmap(IDirectDraw2 *pdd, LPCSTR szBitmap, int *dx, int *dy);
	extern HRESULT             DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
	extern HRESULT             DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
	extern DWORD               DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
	extern HRESULT             DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);

	// DirectX Errors
	extern void DDError(HRESULT hErr, void* hWnd);
	extern void DSError(HRESULT hErr, void* hWnd);
}

class CDXSurface;

//////////////////////////////////////////////////////////////////////////////////
// CDXScreen Class
//////////////////////////////////////////////////////////////////////////////////
class CDXScreen
{
public:
	CDXScreen();
	CDXScreen(void *hWnd, DWORD Width, DWORD Height, DWORD BPP, BOOL bVGA = FALSE);
	CDXScreen(void *hWnd, int Width, int Height);
	~CDXScreen();

	BOOL CreateFullScreen(void *hWnd, DWORD Width, DWORD Height, DWORD BPP, BOOL bVGA = FALSE);
	BOOL CreateWindowed(void *hWnd, int Width, int Height);
	BOOL LoadBitmap(const char* szFilename);
	BOOL LoadPalette(const char* szFilename);
	void Fill(DWORD FillColor);
	void Restore(void);
	HRESULT Flip(void);

	void SetColor(int col, int r, int g, int b);
	void GetColor(int col, int *r, int *g, int *b);
	void SetPalette(int Start, int Count, LPPALETTEENTRY lpPE);
	void GetPalette(int Start, int Count, LPPALETTEENTRY lpPE);
	void FillPalette(int r, int g, int b);
	void GreyScale(void);
	void FadeIn(int delay, LPPALETTEENTRY lpPE);
	void FadeOut(int delay);
	void FadeTo(int r, int g, int b, int delay);

	int GetWidth(void) { return m_dwPixelWidth; }
	int GetHeight(void) { return m_dwPixelHeight; }
	int GetBPP(void) { return m_BPP; }
	LPDIRECTDRAW2 GetDD(void) { return m_lpDD; }
	CDXSurface* GetFront(void) { return m_lpDDSFront; }
	CDXSurface* GetBack(void) { return m_lpDDSBack; }
	LPDIRECTDRAWPALETTE GetPalette(void) { return m_lpDDPalette; }

public:
	LPDIRECTDRAW2 m_lpDD;
	CDXSurface* m_lpDDSFront;
	CDXSurface* m_lpDDSBack;
	LPDIRECTDRAWSURFACE m_ZBuffer;
	LPDIRECTDRAWPALETTE m_lpDDPalette;
	LPDIRECTDRAWCLIPPER m_lpClipper;

	DWORD m_dwPixelWidth;
	DWORD m_dwPixelHeight;
	DWORD m_BPP;
	void* m_hWnd;

	BOOL m_bFullScreen;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXSurface Class
//////////////////////////////////////////////////////////////////////////////////
class CDXSurface
{
public:
	CDXSurface();
	CDXSurface(CDXScreen *pScreen, int Width, int Height);
	CDXSurface(CDXScreen *pScreen, const char *szFilename);
	~CDXSurface();

	BOOL Create(CDXScreen *pScreen, int Width, int Height);
	BOOL Create(CDXScreen *pScreen, const char *szFilename);
	void SetDest(int t, int l, int b, int r);
 	void SetSrc(int t, int l, int b, int r);
	void ColorKey(int col);
	void Restore(void);
	void Fill(DWORD FillColor);

	void ChangeFont(const char* FontName, int Width, int Height, int Attributes = FW_NORMAL);
	void SetFont(void);
	HRESULT Lock(void);
	HRESULT UnLock(void);
	void GetDC();
	void ReleaseDC();
	void TextXY(int X, int Y, COLORREF Col, LPCTSTR pString);
	void PutPixel(int X, int Y, int Col);
	int  GetPixel(int X, int Y);
	void Rect(int X1,int Y1,int X2,int Y2,int Col);
	void FillRect(int X1, int Y1, int X2, int Y2, int Col);
	void Line(int X1, int Y1, int X2, int Y2, int Col);
	void VLine(int Y1, int Y2, int X, int Col);
	void HLine(int X1, int X2, int Y, int Col);
	void Circle(int X, int Y, int Radius, int Col);

	virtual HRESULT Draw(CDXSurface* lpDDS);
	virtual HRESULT DrawFast(int X, int Y, CDXSurface* lpDDS);
	virtual HRESULT DrawTrans(int X, int Y, CDXSurface* lpDDS);
	virtual HRESULT DrawClipped(int X, int Y, CDXSurface* lpDDS, LPRECT ClipRect);
	virtual HRESULT DrawWindowed(CDXSurface* lpDDS);
	virtual HRESULT DrawScaled(int X, int Y, float Factor, CDXSurface* lpDDS);
	virtual HRESULT DrawHFlip(int X, int Y, CDXSurface* lpDDS);
	virtual HRESULT DrawVFlip(int X, int Y, CDXSurface* lpDDS);
	virtual void DrawRotated(int X, int Y, double Angle, CDXSurface* lpDDS);

public:
	int m_PixelWidth;
	int m_PixelHeight;
	const char* m_pFilename;

	HDC m_DC;
	int m_ColorKey;
	RECT SrcRect;
  RECT DestRect;
	HFONT m_Font;
	DDSURFACEDESC m_DDSD;
	LPDIRECTDRAWSURFACE m_lpDDS;
	CDXScreen *Screen;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXLayer Class
//////////////////////////////////////////////////////////////////////////////////
class CDXLayer : public CDXSurface
{
public:
  CDXLayer(CDXScreen *pScreen, char *szFilename);

	void ScrollUp(int Offset);
	void ScrollDown(int Offset);
	void ScrollLeft(int Offset);
	void ScrollRight(int Offset);
	void MoveTo(int XOffset, int YOffset);
	virtual HRESULT Draw(CDXSurface* lpDDS);

public:
	int m_XOffset;
	int m_YOffset;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXTile Class
//////////////////////////////////////////////////////////////////////////////////
class CDXTile : public CDXSurface
{
public:
	CDXTile();
	CDXTile(CDXScreen *pScreen, const char* szFilename, int w, int h, int num);

	BOOL Create(CDXScreen *pScreen, const char* szFilename, int w, int h, int num);

public:
	int m_BlockWidth;
	int m_BlockHeight;
	int m_BlockNum;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXMap Class
//////////////////////////////////////////////////////////////////////////////////
class CDXMap
{
public:
	CDXMap(CDXTile *pTiles, CDXScreen *pScreen);
  ~CDXMap();

	void Create(int Width, int Height, int Fill);
	BOOL Load(const char *szFilename);
	BOOL Save(const char *szFilename);
  void Clear(void);
	void Fill(int TileNum);
	void BltTile(CDXSurface* lpDDS, int xdest, int ydest, int w, int h, int xoff, int yoff);
	void BltTileTrans(CDXSurface* lpDDS, int xdest, int ydest, int w, int h, int xoff, int yoff);
	void Draw(CDXSurface* lpDDS);
	void DrawTrans(CDXSurface* lpDDS);
  void DrawClipped(CDXSurface* lpDDS, LPRECT ClipRect);
	void MoveTo(int PosX, int PosY);
	void ScrollUp(int Offset);
	void ScrollDown(int Offset);
	void ScrollLeft(int Offset);
	void ScrollRight(int Offset);
	void WrapScrollUp(int Offset);
	void WrapScrollDown(int Offset);
	void WrapScrollLeft(int Offset);
	void WrapScrollRight(int Offset);
	void ScreenTileSize(int Width, int Height);
	int  GetTile(int MapX, int MapY);
	void SetTile(int MapX, int MapY, int Tile);
	void LoadTiles(CDXTile *pTiles);

public:
	int m_PosX, m_PosY;
	int m_Width, m_Height;
	int m_TileWidth, m_TileHeight;
	int m_PixelWidth, m_PixelHeight;
	int SCREEN_TW, SCREEN_TH;
	int SCREEN_W, SCREEN_H;
	int SIZE;
	int *DATA;
  CDXScreen *Screen;
	CDXTile *Tiles;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXSprite Class
//////////////////////////////////////////////////////////////////////////////////
class CDXSprite
{
public:
	CDXSprite(void) {}
	CDXSprite(CDXTile* pTile);
	CDXSprite(CDXScreen *pScreen, const char* Filename, int w, int h, int num);
	~CDXSprite(void);

	BOOL Create(CDXTile* pTile);
	BOOL Create(CDXScreen *pScreen, const char* Filename, int w, int h, int num);

	void SetPos(int pX, int pY) { m_PosX = pX; m_PosY = pY; }
	void SetVel(int vX, int vY) { m_VelX = vX; m_VelY = vY; }
	void SetFrame(int Frame) { m_Frame = Frame; }
	void SetDelay(int Delay) { m_Delay = Delay; }
	void SetState(int State) { m_State = State; }
	void SetType(int Type) { m_Type = Type; }

	void Lock(void) { m_Tile->Lock(); }
	void UnLock(void) { m_Tile->UnLock(); }
	void ColorKey(int Col) { m_Tile->ColorKey(Col); }
	void SelectFrame(void);
	BOOL SpriteHit(CDXSprite* pSprite);
	BOOL TileHit(CDXMap* pMap, int Tile);

	HRESULT Draw(CDXSurface* lpDDS);
	HRESULT DrawFast(CDXSurface* lpDDS);
	HRESULT DrawTrans(CDXSurface* lpDDS);
	HRESULT DrawClipped(CDXSurface* lpDDS, LPRECT ClipRect);
	HRESULT DrawWindowed(CDXSurface* lpDDS);
	HRESULT DrawScaled(float Factor, CDXSurface* lpDDS);
	void DrawRotated(float Angle, CDXSurface* lpDDS);
	void DrawHFlip(CDXSurface* lpDDS);
	void DrawVFlip(CDXSurface* lpDDS);

public:
	int m_PosX, m_PosY, m_PosZ;
	int m_VelX, m_VelY;
	int m_Frame;
	int m_Delay;
	int m_State;
	int m_Type;
	int m_Angle;
	BOOL m_Flipped;

	CDXTile* m_Tile;
	CDXSprite* m_Next;
	CDXSprite* m_Prev;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXSpriteList Class
//////////////////////////////////////////////////////////////////////////////////
class CDXSpriteList
{
public:
	CDXSpriteList(void);
	~CDXSpriteList(void);

	void AddSprite(CDXTile* pTile, int Type=0,
		                             int PosX=0, int PosY=0,
																 int VelX=0, int VelY=0,
																 int State=0, int Frame=0,
																 int Delay=0);
	void DelSprite(CDXSprite* pNode);

	CDXSprite* Next(void) { return m_List.m_Next; }
	CDXSprite* Prev(void) { return m_List.m_Prev; }
	CDXSprite* List(void) { return &m_List; }

	void Draw(CDXSurface* lpDDS);
	void DrawFast(CDXSurface* lpDDS);
	void DrawTrans(CDXSurface* lpDDS);
	void DrawClipped(CDXSurface* lpDDS, LPRECT ClipRect);
	void DrawWindowed(CDXSurface* lpDDS);
	void DrawScaled(float Factor, CDXSurface* lpDDS);
	void DrawRotated(float Angle, CDXSurface* lpDDS);
	void DrawHFlip(CDXSurface* lpDDS);
	void DrawVFlip(CDXSurface* lpDDS);

public:
	CDXSprite m_List;
	int m_nSprites;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXSound Class
//////////////////////////////////////////////////////////////////////////////////
class CDXSound
{
public:
	CDXSound(void);
	~CDXSound(void);

	BOOL Create(void *hWnd);
	BOOL GetCaps(void);

public:
	LPDIRECTSOUND m_lpDS;
	DSCAPS m_DSCaps;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXSoundBuffer Class
//////////////////////////////////////////////////////////////////////////////////
class CDXSoundBuffer
{
public:
	CDXSoundBuffer(void);
	~CDXSoundBuffer(void);

	BOOL Load(CDXSound* pDS, const char* Filename, int Num = 1);
	BOOL Play(int Pan = 0, DWORD dwFlags = 0);
	BOOL Stop(void);
	void SetVolume(LONG Volume);

	BOOL LoadFromFile(void);
	BOOL CreateSoundBuffer(DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample,
												 DWORD dwBlkAlign, BOOL bStereo);
	BOOL ReadData(FILE* fp, DWORD dwSize, DWORD dwPos);
	LPDIRECTSOUNDBUFFER GetFreeBuffer(void);

public:
	int m_nBuffers;
	int m_Current;
	const char* m_Filename;
	CDXSound* m_pDS;
	LPDIRECTSOUNDBUFFER m_lpDSB[1];
};

//////////////////////////////////////////////////////////////////////////////////
// CDXMusic Class
//////////////////////////////////////////////////////////////////////////////////
class CDXMusic
{
public:
	CDXMusic(void *hWnd);

	BOOL Play(const char *Filename);
	BOOL Stop(void);
	BOOL Pause(void);
	BOOL Resume(void);
	BOOL Restart(void);

public:
	HWND m_hWnd;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXInput Class
//////////////////////////////////////////////////////////////////////////////////
class CDXInput
{
public:
	CDXInput(void);
	~CDXInput(void);

	BOOL Create(void *hInst, void *hWnd);
	void ReAcquire(void);
	void UnAcquire(void);
	void Update(void);

	void SetActiveDevices(BOOL bMouse, BOOL bKeyboard, BOOL bJoystick);
	void SetMouseAbs(void);
	void SetJoystickAbs(void);
	void RunMouseControlPanel(void *hWnd = NULL);
	void RunJoystickControlPanel(void *hWnd = NULL);

public:
	LPDIRECTINPUT m_lpDI;
	LPDIRECTINPUTDEVICE m_lpDIDKeyboard;
	LPDIRECTINPUTDEVICE m_lpDIDMouse;
	LPDIRECTINPUTDEVICE2 m_lpDIDJoystick;

	POINT Mouse;
	POINT Joystick;
	BOOL JoystickB1, JoystickB2;
	BOOL MouseLB, MouseMB, MouseRB;
	BYTE Keys[256];

	BOOL m_bMouse;
	BOOL m_bKeyboard;
	BOOL m_bJoystick;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXLinkSession Structure
//////////////////////////////////////////////////////////////////////////////////
struct CDXLinkSession
{
	char *m_Name;
	GUID  m_Guid;
	GUID  m_AppGuid;
	DWORD m_Flags;
	DWORD m_MaxPlayers;
	DWORD m_CurrentPlayers;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXLinkPlayer Structure
//////////////////////////////////////////////////////////////////////////////////
struct CDXLinkPlayer
{
	DPID m_ID;
	char *m_Name;
	DWORD m_Flags;
	HANDLE m_Event;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXLink Class
//////////////////////////////////////////////////////////////////////////////////
class CDXLink
{
public:
	CDXLink(void);
	~CDXLink(void);

	BOOL CreateIPX(void* hWnd);
	BOOL CreateTCPIP(void* hWnd, char* IPAddress);
	BOOL CreateModem(void* hWnd, char* PhoneNo);
	BOOL CreateSerial(void* hWnd);

	BOOL EnumSessions(CDXLinkSession* Sessions, GUID APP_GUID);
	BOOL HostSession(CDXLinkSession* Session);
	BOOL JoinSession(CDXLinkSession* Session);
	BOOL CloseSession(void);

	BOOL EnumPlayers(CDXLinkPlayer* Players, DWORD Flags = 0);
	BOOL CreatePlayer(CDXLinkPlayer* Player);
	BOOL DestroyPlayer(CDXLinkPlayer* Player);

	HRESULT Send(DPID idFrom, DPID idTo, DWORD dwFlags,
							 LPVOID lpData, DWORD dwDataSize);
	HRESULT Receive(LPDPID lpidFrom, LPDPID lpidTo,	DWORD dwFlags,
									LPVOID lpData, LPDWORD lpdwDataSize);

public:
	HRESULT rval;
	LPDIRECTPLAY3A m_DP;
	LPDIRECTPLAYLOBBY2A m_DPLobby;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXResource FILEENTRY Structure
//////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	long offset;
	char name[13];
} FILEENTRY, *LPFILEENTRY;

//////////////////////////////////////////////////////////////////////////////////
// CDXResource Class
//////////////////////////////////////////////////////////////////////////////////
class CDXResource
{
public:
	CDXResource(void);
	~CDXResource(void);

	BOOL Open(const char *Filename);
	void Close(void);
	char* GetFile(const char *Filename);

public:
	LPFILEENTRY m_pFE;
	int m_Infile;
	int m_Outfile;
	int m_nFiles;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXAvi Class
//////////////////////////////////////////////////////////////////////////////////
class CDXAvi : public CDXSurface
{
public:
	CDXAvi(void);
	~CDXAvi(void);

	BOOL Create(CDXScreen* pScreen, CDXSound* pSound, const char* Filename, BOOL bLoop = FALSE);
	BOOL Start(void);
	void Stop(void);
	void NextFrame(void);
	void ReadFrame(LONG Frame);
	BOOL GetSound(void);
	HRESULT DrawBuffer(void);

	virtual HRESULT Draw(CDXSurface* Dest);
	virtual HRESULT DrawFast(int X, int Y, CDXSurface* Dest);

public:
	BOOL m_bPlaying;
	BOOL m_bLoop;
	LONG m_Index;
	LONG m_nFrames;
	DWORD m_Fps;
	int m_TimerID;
	int m_TimeTick;

	CRITICAL_SECTION m_AccessBuffer;
	PAVISTREAM m_AviStream;
	AVISTREAMINFO m_StreamInfo;
	LPBYTE m_Input;
	LPBYTE m_Output;
	HIC  m_Decompressor;
	LONG m_Length;
	LONG m_LinePitch;
	LPBITMAPINFOHEADER m_InputFormat;
	LPBITMAPV4HEADER m_TargetFormat;

	PAVISTREAM m_AviSound;
	AVISTREAMINFO m_SoundInfo;
	WAVEFORMATEX* m_SoundFormat;
	LPDIRECTSOUNDBUFFER m_SoundBuffer;
	DWORD m_LoadPos;
	DWORD m_LoadSize;
	int m_SoundFramesAhead;
};

//////////////////////////////////////////////////////////////////////////////////
// CDXMusicCd Class
//////////////////////////////////////////////////////////////////////////////////
class CDXMusicCd
{
public:
	CDXMusicCd(void);
	~CDXMusicCd(void);

	short	Read(void);
	short	GetNumberOfTracks(void)	{ return m_nNumberOfTracks; }
	void  SetNumberOfTracks(short nTracks) { m_nNumberOfTracks = nTracks; }
	short	GetTrackLength(short nTrack);
	void  SetTrackLength(short nTrack, short nNewLength);
	short	GetTotalLength(void);
	void  Play(short nTrack);
	void  Stop(void);

private:
	short	m_nNumberOfTracks;
	short	m_nTrackLength[100];
	MCI_STATUS_PARMS m_MCIStatus;
	MCI_OPEN_PARMS m_MCIOpen;
};

//////////////////////////////////////////////////////////////////////////////////
// MACROS
//////////////////////////////////////////////////////////////////////////////////
#define RELEASE(x) if(x != NULL) { x->Release(); x = NULL; }
#define ODS(a) OutputDebugString(a)

#endif