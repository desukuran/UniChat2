// TileMap.h: interface for the CTileMap class.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_TILEMAP_H__D5010EC6_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
#define AFX_TILEMAP_H__D5010EC6_A1F9_11D1_80E2_080009B9F339__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef	MAPEDITOR
#include "MapEd/resource.h"	// DIB_GRID_64X32
#else
#include "resource.h"
#endif

enum ELEVATION_UNITS
{
	ELEVATION_UNIT	= 8,
	ELEVATION_DIFF	= 16,	// Max Elevation an actor can go on it
	ELEVATION_LIMIT	= 999
};

class CDIB;
class CPhasedSprite;
class CSpriteList;
class CTextFileBuffer;

class CTileMap : public CObject  
{
public:
	CTileMap();
	virtual ~CTileMap();

	typedef struct
	{
		CPhasedSprite* pPS;	// includes nCellID, nImOp
#ifdef	MAPEDITOR
		CPhasedSprite* pGridPS;	// for Grid Cell
#endif
		int		nEA;		// Elevation for Actors
		WORD	wDA;		// Direction Attributes
//		int		nResID;		// DIB Resource ID in ResMan
//		int		nCellID;
//		int		nElev;		// Elevation, z = f(x,y)
//		int		nImOp;		// IMAGE_OPERATION
	} TILE;					// DEFAULT_IO, IMAGE_FLIP, IMAGE_VERTICAL
	typedef TILE* LPTILE;

// Attributes
	CSize		GetTileSize() const		{ return m_sT; }
	CSize		GetHalfTileSize() const	{ return m_sTH; }
	CSize		GetScreenSize() const	{ return m_sScr; }
	CString*	GetFileName()			{ return &m_strMapFile; }

	CPoint	GetLT(const int nx, const int ny) const
			{ return (GetCenter(nx, ny) - m_sTH); }
	int		GetLTx(const int nx, const int ny) const
			{ return (GetCx(nx, ny) - m_sTH.cx); }
	int		GetLTy(const int ny) const
			{ return (GetCy(ny) - m_sTH.cy); }
	CPoint	GetCenter(const CPoint& point) const
			{ return GetCenter(point.x, point.y); }
	CPoint	GetCenter(const int nx, const int ny) const
			{ return CPoint(GetCx(nx, ny), GetCy(ny)); }
	int		GetCx(const int nx, const int ny) const
			{ return ((ny%2 == 0) ? nx * m_sT.cx : (2*nx + 1) * m_sTH.cx); }
	int		GetCy(const int ny) const	{ return ny * m_sTH.cy; }
	BOOL	InsideTile(const CPoint& ptTileID, const CPoint& point) const;
	int		GetElevation(const CPoint& ptID) const;
	CPhasedSprite*	GetPS(const CPoint& ptID)
			{ return m_apTile[ptID.y][ptID.x].pPS; }
	int		GetEA(const CPoint& ptID) const	// Elevation for Actors
			{ return m_apTile[ptID.y][ptID.x].nEA; }
	WORD	GetDA(const CPoint& ptID) const	// Direction Attribute
			{ return m_apTile[ptID.y][ptID.x].wDA; }
	BOOL	CanStandOn(const CPoint& ptID) const
			{ return (GetDA(ptID) != DA_CLOSED); }
	BOOL	GetActorNextTileID(CPoint& ptTID, const WORD wDA) const;
	CPoint	GetEntryID(LPCTSTR szFromID) const;
	BOOL	IsValidTileID(const CPoint& ptTID) const
			{ return ((ptTID.x >= 0) && (ptTID.x < m_sTiles.cx) &&
					  (ptTID.y >= 0) && (ptTID.y < m_sTiles.cy)); }

// Operations
	CPoint		GetNearestTileCenter(const CPoint& pt) const;
	CPoint		GetNearestTileLT(const CPoint& pt) const
				{	CPoint ptCtr(GetNearestTileCenter(pt));
					return CPoint(ptCtr - m_sTH);	}
	CPoint		GetNearestTileIndex(const CPoint& pt) const;
	CPoint		GetNearestTileIndex(CPhasedSprite* pPS) const;

	void		SetTileSize(const CSize sT)
				{ m_sT = sT; m_sTH.cx = m_sT.cx/2; m_sTH.cy = m_sT.cy/2; }
	BOOL		Create(const int W, const int H);
	BOOL		Create(const CSize sScr)	{ return Create(sScr.cx, sScr.cy); }
	void		SetSpriteList(CSpriteList* pSL)	{ m_pSpriteList = pSL; }
	void		SetAniList(CSpriteList* pAL)	{ m_pAniList = pAL; }
	void		SetPalette(CPalette* pPal)	{ m_pPalette = pPal; }

	BOOL		Load(const char* path=NULL);
	BOOL		LoadRow(CTextFileBuffer& tfb, const int ny, const double fVersion);
	BOOL		Save(CStdioFile& f);
	void		DrawElevationGraph(CDC* pDC);
	void		DrawActorElevationGraph(CDC* pDC);
	void		SetEA(const CPoint& ptID, const int nEA)
				{ m_apTile[ptID.y][ptID.x].nEA = nEA; }
	void		IncEA(const CPoint& ptID, const int nEABy)
				{ m_apTile[ptID.y][ptID.x].nEA += nEABy; }
	void		SynchronizeEA(const CPoint& ptID);	// with sprite elevation
	BOOL		SynchronizeAllEA();
	void		IncreaseElevations(const int nPixelBy);
	CPhasedSprite*	HitTest(const CPoint& point);
protected:
	void		InsertList(CPhasedSprite* pPS);
	void		RemoveList(CPhasedSprite* pPS);

#ifdef	MAPEDITOR
public:
	void		RenderGrid(CDIB* pDIB, const CRect* pClipRect);
	void		SetDA(const CPoint& ptID, const WORD wDA);
	BOOL		RecalculateDA();
	BOOL		Insert(CPhasedSprite* pPS);
//	BOOL		CopyInsert(CPhasedSprite* pPS);
	void		Delete(CPhasedSprite* pPS);
	BOOL		MoveSpriteTo(CPhasedSprite* pPS, CPoint& ptTo);
	BOOL		LoadGrid(const WORD wResId=DIB_GRID_64X32);
protected:
	void		SetGridImage(const CPoint& ptID, const WORD wDA);
#endif

private:
	void	DeleteTiles();
	void	DrawHyperlink(CDC* pDC, const CPoint& ptC, const int nType);

	CSize	m_sScr;		// Screen Width, Height
	CSize	m_sT;		// Tile width, height
	CSize	m_sTH;		// Half Tile width, height

	LPTILE*	m_apTile;	// 2-dim array of TILEs
	CSize	m_sTiles;	// # of tiles
	CString	m_strMapFile;	// filename.ext only for Version 0.99 and below
//	BOOL	m_bGrid;

	CSpriteList*	m_pSpriteList;
	CSpriteList*	m_pAniList;
	CPalette*		m_pPalette;
};

#endif // !defined(AFX_TILEMAP_H__D5010EC6_A1F9_11D1_80E2_080009B9F339__INCLUDED_)
