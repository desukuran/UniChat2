// Stage.h: interface for the CStage class.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_STAGE_H__D5010EC4_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_STAGE_H__D5010EC4_A1F9_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UC2Ani/SpritLst.h"
#include "UC2Ani/BubblLst.h"
#include "TileMap.h"
#include "Actor.h"

//////////////////////////////////////////////////////////////////////

class COSBView;
class CSprite;
class CPhasedSprite;
class CMCIObject;
class CMemberInfo;

enum RENDER_MODE
{
	RM_ELEV		= 0x0001,	// Show Elevation
	RM_TILE		= 0x0002,	// Show Tile
	RM_SPRITE	= 0x0004,	// Show Sprite
	RM_GRID		= 0x0008,
	RM_NORMAL	= RM_ELEV | RM_TILE | RM_SPRITE
};

class CStage : public CObject  
{
public:
	CStage();
	virtual ~CStage();

// Attributes
	CSpriteList*	GetSpriteList()		{ return &m_SpriteList; }
	int				GetNumSprites() const		{ return m_SpriteList.GetCount(); }
	int				GetNumAniSprites() const	{ return m_AniList.GetCount(); }
	CTileMap*		GetTileMap()		{ return m_pTiles; }
	CString*		GetFileName()		{ return &m_strStageFile; }
	CString*		GetMapFileName()
					{ return (m_pTiles) ? m_pTiles->GetFileName() : NULL; }
	CString*		GetPalFileName()	{ return &m_strPalFile; }
	CString*		GetTitle()			{ return &m_strTitle; }
	CString*		GetMusicSeq()		{ return &m_strMusicSeq; }
	CSize			GetScreenSize() const
					{ ASSERT(m_pTiles);	return m_pTiles->GetScreenSize(); }
	WORD			GetRenderMode()	const	{ return m_wRM; }
	CActor*			GetThisActor()		{ return m_pThisActor; }
	CActor*			GetFrontActor();
	BOOL			IsExitOpen() const	{ return m_bExitOpen; }

	CActor*			GetActor(CString& strNick);
	// ChatSock related
	CActor*			GetActor(PICS_MEMBER pMem);

// Operations
	BOOL			Initialize(COSBView* pView);
	void			DeleteStage();
	BOOL			CreateStage(CSize& szT, CSize& szScr);
	BOOL			CreateOSB(const CSize sScreen);
	BOOL			InitMap();
	BOOL			Load(const char* szStage=NULL);
	BOOL			Save(const char* szStage=NULL);
	void			Render(CRect* pClipRect=NULL);
//	void			RenderZOrder(CSprite* pSprite);

	CSprite*		SpriteHitTest(const CPoint& point)
					{ return m_SpriteList.HitTest(point); }
	CPhasedSprite*	TileHitTest(const CPoint& point)
					{ return (m_pTiles ? m_pTiles->HitTest(point) : NULL); }
	CPhasedSprite*	AnimatedHitTest(const CPoint& point)
					{ return (CPhasedSprite*)m_AniList.HitTest(point); }

	void			InsertSprite(CPhasedSprite* pPS);
	void			InsertBubble(CBubble* pBB);
	void			InsertAniSprite(CPhasedSprite* pPS);
	void			DeleteSprite(CPhasedSprite* pPS);
	CBubble*		RemoveBubble(CBubble* pBB);
	void			RemoveAniSprite(CPhasedSprite* pPS)
					{ m_AniList.Remove((CSprite*)pPS); }
#ifdef MAPEDITOR
	void			InsertTile(CPhasedSprite* pPS);
	void			DeleteTile(CPhasedSprite* pPS);
	BOOL			MoveTileSpriteTo(CPhasedSprite* pPS, CPoint& ptTo);
#endif
	CActor*			CreateActor(const int nCharID, const CPoint& point, const BOOL bTileID=TRUE,
								const WORD wState=(AS_STAND | DA_FR), const BOOL bThis=FALSE);
	CActor*			CreateActor(CMemberInfo& mi, const BOOL bThis=FALSE);
	void			DeleteActor(CActor* pActor);

//	int				SetZByYBottom(CPhasedSprite* pPS);

	void			SetRenderMode(const WORD wRM)	{ m_wRM = wRM; }
	void			SetPalFileName(const CString& strPalFile)	{ m_strPalFile = strPalFile; }
	void			ClearFilename()	{ m_strStageFile.Empty(); }
	void			SetTitle(const CString& strTitle)	{ m_strTitle = strTitle; }
	void			SetMusicSeq(const CString& strMS)	{ m_strMusicSeq = strMS; }

	int				TickAll();
	BOOL			PlayBGM();
	void			StopBGM();

	CString*		ActorMove(CActor* pActor, const BOOL bForward);
	void			SetExitOpen(const BOOL bOpen=TRUE);

protected:
	void			ParseBGMs();

	COSBView*		m_pOSBView;
	CSpriteList		m_SpriteList;	// sprite list
	CSpriteList		m_AniList;		// Animated (Phased) Sprites, Actors
	CBubbleList		m_BubbleList;
	CTileMap*		m_pTiles;
	CActor*			m_pThisActor;
	CString			m_strStageFile;		// filename.ext only
	CString			m_strPalFile;
	CString			m_strTitle;
	CString			m_strMusicSeq;
	int*			m_aBGM;
	int				m_nBGMs;	// Background Music
	int				m_iBGM;		// Current BGM sequence # 0,1,2,...
	CMCIObject*		m_pBGM;		// MIDI sound
	WORD			m_wRM;		// Render Mode
	BOOL			m_bExitOpen;
	BOOL			m_bMusicPlayOK;
	CString			m_strExitID;
	CString			m_strPrevID;
};

#endif // !defined(AFX_STAGE_H__D5010EC4_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
