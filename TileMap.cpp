// TileMap.cpp: implementation of the CTileMap class.
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================
/* ===============================================================
; map000
#VERSION=1.00;
#TILESIZE=(64,32);	//(64,32)
#SCREENSIZE=(608,384);
#ROW=(0);
{
// nResID=nCellID,nElev,wImOp,T.nEA,wSpriteType,nMSPT,T.wDA,strHyperlink;
// -1=;	// NULL Tile
// nResID=nCellID;	// ,DEFAULT_IO,0,SPRITE_TILE,DA_OPEN;
11=7,0,4096,0,1,0,15,0010csin;
...
}
#ROW=(1);
{
...
==================================================================*/

#include "stdafx.h"
#include "TileMap.h"

#include "Parser.h"
#include "ResMan.h"
#include "UC2Ani/PhSprite.h"
#include "UC2Ani/OSBView.h"
#include "UC2Ani/SpritLst.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CParser gParser;
extern CResMan gResMan;

double GetMapEditorVersion();

const char* MAPFILE_FILTER = "Map Information Tables(*.MIT)|*.MIT|"
							"All files (*.*)|*.*||";
const char* MAPFILE_EXT = ".mit";		// should be lower case

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTileMap::CTileMap()
{
	TRACE0("CTileMap::CTileMap()\n");
	m_sScr		= CSize(0, 0);	// Screen Width, Height
	m_sT		= CSize(0, 0);	// Tile width, height
	m_sTH		= CSize(0, 0);	// Half Tile width, height
	m_sTiles	= CSize(0, 0);
	m_apTile		= NULL;
	m_pSpriteList	= NULL;
	m_pAniList		= NULL;
	m_pPalette		= NULL;
}

CTileMap::~CTileMap()
{
	TRACE0("CTileMap::~CTileMap()\n");
	DeleteTiles();
}

void CTileMap::DeleteTiles()
{
	if (!m_apTile)
		return;
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE& T = m_apTile[ny][nx];
			if (T.pPS)
			{
//				RemoveList(T.pPS);	// Time-consuming
				delete T.pPS;
				T.pPS = NULL;
			}
#ifdef MAPEDITOR
			if (T.pGridPS)
				delete T.pGridPS;
			T.pGridPS = NULL;
#endif
		}
		delete [] m_apTile[ny];
		m_apTile[ny] = NULL;
	}
	delete [] m_apTile;
	m_apTile = NULL;
	m_strMapFile.Empty();
}

// Feb 5, 1998
// PROBLEM: Get the nearest diamond (tile) center for a given point (x', y')
// Let a = w/2, b = h/2
// Cx/a + Cy/b = 2M, M=0,1,2,...				-(1)
// Cx/a - Cy/b = 2N, N=...,-2,-1,0,1,2,...	-(2)
// 2M-1 < x'/a + y'/b <= 2M+1
// 2N-1 < x'/a - y'/b <= 2N+1
// Let S=x'/a + y'/b, D=x'/a - y'/b, Here S and D may not be an integer!
// (S-1)/2 <= M < (S+1)/2		-(3)
// (D-1)/2 <= N < (D+1)/2		-(4)
// So the problem reduces to finding such an integer that
// satisfies above inequalities.
// If we find such integers M and N, we can solve for the center point
// By adding and subtracting equations (1) and (2), we get
// C = (a(M+N), b(M-N))		-(5)
CPoint CTileMap::GetNearestTileCenter(const CPoint& pt) const
{
	float fx = float(pt.x)/m_sTH.cx;	// x/a
	float fy = float(pt.y)/m_sTH.cy;	// y/b
	double fM = (fx + fy + 1.)/2.;	// (S-1)/2 <= M < (S+1)/2
	double fN = (fx - fy + 1.)/2.;	// (D-1)/2 <= N < (D+1)/2 can be negative
	if (fN <= 0.)	// Consider a problem to find an integer that satisfies
		fN--;		// -1.5 <= N < -0.5, But int(-0.5)=0
	int M = int(fM);
	int N = int(fN);
	return CPoint(m_sTH.cx*(M + N), m_sTH.cy*(M - N));
}

CPoint CTileMap::GetNearestTileIndex(const CPoint& pt) const
{
	CPoint ptCtr(GetNearestTileCenter(pt));
	int ny = ptCtr.y / m_sTH.cy;
	int nx = (ny%2 == 0)
			? ptCtr.x / m_sT.cx
			: (ptCtr.x / m_sTH.cx - 1) / 2;
	// Boundary conditions not to get any invalid indices
	if (nx >= m_sTiles.cx)
		nx = m_sTiles.cx - 1;
	if (nx < 0)
		nx = 0;
	if (ny >= m_sTiles.cy)
		ny = m_sTiles.cy - 1;
	if (ny < 0)
		ny = 0;
	return CPoint(nx, ny);
}

CPoint CTileMap::GetNearestTileIndex(CPhasedSprite* pPS) const
{
	CPoint point(pPS->GetCenter());
	point.y += pPS->GetElevation();	// Adjust for elevation!
	return GetNearestTileIndex(point);
}

// You must call SetTileSize() before calling this
BOOL CTileMap::Create(const int W, const int H)
{
	DeleteTiles();
	if ((m_sT.cx < 4) || (m_sT.cy < 2))
		SetTileSize(CSize(64, 32));
	m_sScr = CSize(W, H);
	m_sTiles = CSize(m_sScr.cx / m_sT.cx + 1, m_sScr.cy / m_sTH.cy + 1);
	TRACE("# of tiles (%d,%d) => %d\n", m_sTiles.cx, m_sTiles.cy, m_sTiles.cx*m_sTiles.cy);
	m_apTile = new LPTILE[m_sTiles.cy];
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		m_apTile[ny] = new TILE[m_sTiles.cx];
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE& T = m_apTile[ny][nx];
			T.pPS		= NULL;
#ifdef MAPEDITOR
			T.pGridPS	= NULL;
#endif
			T.nEA		= 0;
			T.wDA		= DA_CLOSED;
		}
	}
	return TRUE;
}

// Synchronize actor elevation with sprite elevation
void CTileMap::SynchronizeEA(const CPoint& ptID)
{
	int nEA = GetPS(ptID) ? GetPS(ptID)->GetElevation() : 0;
	SetEA(ptID,  nEA);
}

void CTileMap::IncreaseElevations(const int nPixelBy)
{
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE& T = m_apTile[ny][nx];
			if (T.pPS)
			{
				T.pPS->IncElevation(nPixelBy);
				T.pPS->MoveBy(0, -nPixelBy);
				T.pPS->SetZByEarth();
				T.nEA += nPixelBy;
			}
		}
	}
}

// Can the actor go further with his direction attribute?
BOOL CTileMap::GetActorNextTileID(CPoint& ptTID, const WORD wDA) const
{
	const int& x = ptTID.x;
	const int& y = ptTID.y;
	// Check if this tile has the same direction attribute with the actor
	if ((m_apTile[y][x].wDA != DA_CLOSED) &&	// we should escape!
		((m_apTile[y][x].wDA & wDA) != wDA))
		return FALSE;

	switch (wDA)
	{
	case DA_BL:	ptTID = (y % 2) ? CPoint(x, y-1)	: CPoint(x-1, y-1);	break;
	case DA_BR:	ptTID =	(y % 2) ? CPoint(x+1, y-1)	: CPoint(x, y-1);	break;
	case DA_FR:	ptTID =	(y % 2) ? CPoint(x, y+1)	: CPoint(x-1, y+1);	break;
	case DA_FL:	ptTID = (y % 2) ? CPoint(x+1, y+1)	: CPoint(x, y+1);	break;
	}
	if ((ptTID.x >= 0) && (ptTID.y >= 0) &&
		(ptTID.x < m_sTiles.cx) && (ptTID.y < m_sTiles.cy))
		return TRUE;	// Valid tile id
	return FALSE;
}

// Load tiles info from text file
// Only for Version with 0.99 or below
BOOL CTileMap::Load(const char* path)	// obslete for Ver 1.0 or above
{
	if ((path == NULL) || (lstrlen(path) == 0))
	{
		::SetCurrentDirectory(*gResMan.GetResPath());
		// Show an Open File dialog to get the name.
		CFileDialog dlg(TRUE,	// Open
						NULL,	// No default extension
						m_strMapFile,	// Initial file name
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
						MAPFILE_FILTER);
        if (dlg.DoModal() == IDOK)
			m_strMapFile = dlg.GetPathName();
		else
			return FALSE;
	}
	else
	{
		// Copy the supplied file path.
		m_strMapFile = path;
		gResMan.ExpandResName(m_strMapFile, MAPFILE_EXT);
	}

	CTextFileBuffer tfb(gParser.GetMaxBuffer());
	if (!tfb.Load(m_strMapFile))
	{
		return FALSE;
	}
	gResMan.ExpandResName(m_strMapFile, MAPFILE_EXT);
	
	double	fVersion;	// file version

	while (tfb.ReadString())
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())
			continue;
		if (!gParser.SetLeftToken('#'))
			continue;
		CString strBuf;
		if (!gParser.GetValueRightToken(strBuf, '='))
			continue;

		///////////////////////////////////////
		if (lstrcmpi(strBuf, "VERSION") == 0)
		{
			gParser.SetLeftToken('=');
			gParser.GetValueRightToken(fVersion, ';');
			if (fVersion <= 0.90)
			{
				CString strMsg;
				strMsg.Format("MIT: Old Version %.2f", fVersion);
				AfxMessageBox(strMsg);
			}
		}
		else if (lstrcmpi(strBuf, "TILESIZE") == 0)
		{
			gParser.SetLeftToken('=');
			CSize sT;
			gParser.GetValueRightToken(sT, ';');
			SetTileSize(sT);
		}
		else if (lstrcmpi(strBuf, "SCREENSIZE") == 0)	// matching!
		{
			gParser.SetLeftToken('=');
			CSize sScr;
			gParser.GetValueRightToken(sScr, ';');
			Create(sScr);	// Create Tiles
		}
		else if (lstrcmpi(strBuf, "ROW") == 0)
		{
			gParser.SetLeftToken('(');
			int ny;
			gParser.GetValueRightToken(ny, ')');
			if (ny >= m_sTiles.cy)
			{
				TRACE("TILE Invalid row (%d)!\n", ny);
				continue;
			}
			if (!LoadRow(tfb, ny, fVersion))
				continue;
		}
		else
		{
			TRACE1("Unknown Data type in Map file(%s)!\n", strBuf);
		}
	}
#ifdef MAPEDITOR
	LoadGrid();
#endif
	return TRUE;
}

// Load each tile row from memory buffer
// nResID=nCellID,nElev,wImOp,T.nEA,wType,nMSPT,T.wDA,strHyperlink;
// -1=;	// NULL Tile
// nResID=nCellID;	// ,DEFAULT_IO,0,SPRITE_TILE,DA_OPEN;
BOOL CTileMap::LoadRow(CTextFileBuffer& tfb, const int ny, const double fVersion)
{
	int nx=0;
	if (ny >= m_sTiles.cy)
	{
		TRACE("TILE Invalid row (%d)!\n", ny);
		return FALSE;
	}
	while (tfb.ReadString())
	{
		gParser.CopyBuffer(tfb.GetString());
		if (gParser.IsCommentLine())
			continue;
		if (gParser.SetLeftToken('{'))
		{
			if (gParser.SetLeftToken('}'))
				break;
			continue;
		}
		if (gParser.SetLeftToken('}'))
			break;

		if (nx >= m_sTiles.cx)
		{
			TRACE("TILE Invalid column (%d)!\n", nx);
			continue;
		}
		CString strResName;
		TILE&	T = m_apTile[ny][nx];
		ASSERT(!T.pPS);	// already initialized as a NULL
		ASSERT(T.nEA == 0);
//		ASSERT(T.wDA == DA_CLOSED);
		int		nCellID;
		int		nElev = 0;
		WORD	wImOp = DEFAULT_IO;
		WORD	wType = SPRITE_TILE;
		int		nMSPT = 0;
		CString strHyperlink;

/*		if (fVersion <= 0.90)	// Version 0.90 (before Mar 7,'98)
		{
			gParser.GetValueRightToken(strResName, '=');
			if (strResName[0] == '0')	// NULL tile
			{
				T.wDA = DA_CLOSED;
				nx++;
				continue;
			}
			gResMan.PrefixUDS00(strResName);
		}
		else	// New Version
		{
*/
			int nResID;
			gParser.GetValueRightToken(nResID, '=');
			if (nResID < 0)	// -1 for NULL Tile
			{
				if (fVersion < 1.01)
				{
					T.wDA = DA_CLOSED;
				}
				else	// V1.01
				{
					if (!gParser.GetValueRightToken(T.nEA, ',', ';'))
						T.nEA = nElev;
					else if (!gParser.GetValueRightToken(T.wDA, ',', ';'))
						T.wDA = DA_CLOSED;	// default for NULL tile
				}
				nx++;
				continue;
			}
			CString* pStr = gResMan.GetSpriteName(nResID);
			if (!pStr)
			{
				strResName.Format("ResID=%d in Map not found!", nResID);
				AfxMessageBox(strResName);
				continue;
			}
			strResName = *pStr;
//		}

		T.nEA = nElev;		// default
		T.wDA = DA_OPEN;	// default condition

		gParser.GetValueRightToken(nCellID, ',', ';');
		if (!gParser.GetValueRightToken(nElev, ',', ';'))
			nElev = 0;
		else	// continue to the next delimeter
		{
			if (!gParser.GetValueRightToken(wImOp, ',', ';'))
				wImOp = DEFAULT_IO;
			else
			{
				if (!gParser.GetValueRightToken(T.nEA, ',', ';'))
					T.nEA = nElev;
				else
				{
					if (!gParser.GetValueRightToken(wType, ',', ';'))
						wType = SPRITE_TILE;
					else
					{
						if (!gParser.GetValueRightToken(nMSPT, ',', ';'))
							nMSPT = 0;
						else
						{
							if (!gParser.GetValueRightToken(T.wDA, ',', ';'))
								T.wDA = DA_OPEN;
							else
							{
								if (!gParser.GetValueRightToken(strHyperlink, ',', ';'))
									strHyperlink.Empty();
							}
						}
					}
				}
			}
		}

		// Resource Allocation via Resource Manager
		CPhasedSprite* pPS = gResMan.LoadPhasedSprite(strResName);
		if (!pPS)
		{
			strResName += " not found!";
			AfxMessageBox(strResName);
			continue;
		}

		pPS->SetCell(nCellID);
		CPoint ptLT(GetLT(nx, ny));
		if (nElev)
		{
			pPS->SetElevation(nElev);
			ptLT.y -= nElev;
		}
		pPS->SetLT(ptLT);
		pPS->SetType(wType);
		if (fVersion < 1.01)
		{
			wImOp &= ~NO_COLORKEY;
			if (nMSPT && !pPS->GetAniType())
				nMSPT = 0;
		}
		pPS->SetImOp(wImOp);
		pPS->SetZByEarth();
		if (nMSPT > 0)
			pPS->SetMSPT(nMSPT);
		if (!strHyperlink.IsEmpty())
			pPS->SetHyperlink(strHyperlink);
		T.pPS = pPS;

		InsertList(pPS);
		if (m_pPalette)
			pPS->MapColorsToPalette(m_pPalette);
		nx++;
	}
	return TRUE;
}

BOOL CTileMap::Save(CStdioFile& f)
{
	CString str;
	str.Format("\n#TILESIZE=(%d,%d);\n", m_sT.cx, m_sT.cy);	// (64,32)
	f.WriteString(str);

	str.Format("#SCREENSIZE=(%d,%d);\n", m_sScr.cx, m_sScr.cy);
	f.WriteString(str);

	int n=0;
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		str.Format("#ROW=(%d);\n{\n", ny);
		f.WriteString(str);
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE& T = m_apTile[ny][nx];
			if (T.pPS)
			{
				CString strResName(*T.pPS->GetDIB()->GetName());
				gResMan.MakeResName(strResName);
//					str.Format("%s=%d,%d,%d,%d,%d,%d;\n", strResName,	// #VERSION=0.90
				int nResID = gResMan.GetSpriteID(strResName);
				if (nResID < 0)
				{
					strResName += " not found";
					AfxMessageBox(strResName);
				}
				if ((T.pPS->GetElevation() == 0) &&
					(T.pPS->GetImOp() == DEFAULT_IO) &&
					(T.nEA == 0) &&
					(T.pPS->GetType() == SPRITE_TILE) &&
					(T.wDA == DA_OPEN) &&
					(!T.pPS->HasHyperlink()))
				{	// typical case
					str.Format("%d=%d", nResID, T.pPS->GetCellID());
				}
				else
				{
					str.Format("%d=%d,%d,%d,%d,%d,%d,%d", nResID,
						T.pPS->GetCellID(),
						T.pPS->GetElevation(),
						T.pPS->GetImOp(), T.nEA,
						T.pPS->GetType(), T.pPS->GetMSPT(),
						T.wDA);
					if (T.pPS->HasHyperlink())
					{
						str += ',';
						str += *T.pPS->GetHyperlink();
					}
				}
				str += ";\n";
			}
			else	// NULL Tile, V1.01
			{
				str.Format("-1=%d,%d;\n", T.nEA, T.wDA);
			}
			f.WriteString(str);
			n++;
		}
		f.WriteString("}\n");
	}
	str.Format("; %d tiles.\n", n);
	f.WriteString(str);
//	str.Format("%s: %d sprites written.", m_strMapFile, n);
//	AfxMessageBox(str);
	return TRUE;
}

void CTileMap::DrawHyperlink(CDC* pDC, const CPoint& ptC, const int nType)
{
	CPen penRed(PS_SOLID, 1, (nType == CPhasedSprite::HLINK_U2_EXIT) ?
								PALETTERGB(255,0,0) :
								PALETTERGB(0,255,0));
	CBrush brush((nType == CPhasedSprite::HLINK_U2_EXIT) ?
					PALETTERGB(255,0,0) :
					PALETTERGB(255,255,0));	// Yellow HS_CROSS
	CPen* penOld = pDC->SelectObject(&penRed);
	CBrush* brOld = pDC->SelectObject(&brush);
	pDC->SetBkMode(TRANSPARENT);

	CRect rc(ptC.x-5, ptC.y-5, ptC.x+5, ptC.y+5);
	pDC->Ellipse(rc);

	pDC->SelectObject(brOld);
	pDC->SelectObject(penOld);
}

// ptC0 / ptC1 ` ptC3 (draw next time)
//		` ptC2 /
void CTileMap::DrawElevationGraph(CDC* pDC)
{
	CRect rcDraw;
//	OnPrepareDC(pDC);	// CScroll changes the viewport origin and mapping mode.
	pDC->GetClipBox(rcDraw);

	CPen penRed(PS_SOLID, 1, PALETTERGB(255,0,0));
	CPen penRedDot(PS_DOT, 1, PALETTERGB(255,0,0));
	CPen penGreen(PS_SOLID, 1, PALETTERGB(0,255,0));
	CPen penGreenDot(PS_DOT, 1, PALETTERGB(0,255,0));
//	CBrush brush(HS_CROSS, PALETTERGB(255,255,0));	// Yellow

	CPen* penOld = pDC->SelectObject(&penRed);
	pDC->SetBkMode(TRANSPARENT);
//	CBrush* brOld = pDC->SelectObject(&brush);

//	pDC->Rectangle(&rcDraw);
	for (int ny=0; ny < m_sTiles.cy; ny += 2)
	{
		int nx2 = m_sTiles.cx - 1;
		for (int nx=0; nx < nx2; nx++)
		{
			TILE &T0 = m_apTile[ny][nx];
			CPoint ptC0(GetCenter(nx, ny));
			if (T0.pPS && T0.pPS->GetElevation())
			{
				CPoint ptC00(ptC0);	// Save before elevation
				ptC0.y -= T0.pPS->GetElevation();
				pDC->MoveTo(ptC00);
				pDC->SelectObject((T0.pPS->GetElevation() < 0) ? &penRed : &penRedDot);
				pDC->LineTo(ptC0);
			}
			if (T0.pPS && T0.pPS->HasHyperlink())
				DrawHyperlink(pDC, ptC0, T0.pPS->GetLinkType());

			TILE &T3 = m_apTile[ny][nx+1];
			CPoint ptC3(GetCenter(nx+1, ny));
			if (T3.pPS && T3.pPS->GetElevation())
			{
				ptC3.y -= T3.pPS->GetElevation();
			}

			if (ny >= 1)
			{
				TILE &T1 = m_apTile[ny-1][nx];	// upper line
				CPoint ptC1(GetCenter(nx, ny-1));
				if (T1.pPS && T1.pPS->GetElevation())
				{
					CPoint ptC10(ptC1);	// Save before elevation
					ptC1.y -= T1.pPS->GetElevation();
					pDC->MoveTo(ptC10);
					pDC->SelectObject((T1.pPS->GetElevation() < 0) ? &penRed : &penRedDot);
					pDC->LineTo(ptC1);
				}
				if (T1.pPS && T1.pPS->HasHyperlink())
					DrawHyperlink(pDC, ptC1, T1.pPS->GetLinkType());
				pDC->MoveTo(ptC0);
				pDC->SelectObject(T1.pPS ? &penGreen : &penGreenDot);
				pDC->LineTo(ptC1);
				pDC->SelectObject(T3.pPS ? &penGreen : &penGreenDot);
				pDC->LineTo(ptC3);
			}
			if (ny < (m_sTiles.cy-1))
			{
				TILE &T2 = m_apTile[ny+1][nx];	// lower line
				CPoint ptC2(GetCenter(nx, ny+1));
				if (T2.pPS && T2.pPS->GetElevation())
				{
					CPoint ptC20(ptC2);	// Save before elevation
					ptC2.y -= T2.pPS->GetElevation();
					pDC->MoveTo(ptC20);
					pDC->SelectObject((T2.pPS->GetElevation() < 0) ? &penRed : &penRedDot);
					pDC->LineTo(ptC2);
				}
				if (T2.pPS && T2.pPS->HasHyperlink())
					DrawHyperlink(pDC, ptC2, T2.pPS->GetLinkType());
				pDC->MoveTo(ptC0);
				pDC->SelectObject(T2.pPS ? &penGreen : &penGreenDot);
				pDC->LineTo(ptC2);
				pDC->SelectObject(T3.pPS ? &penGreen : &penGreenDot);
				pDC->LineTo(ptC3);
			}
/*
			CPoint ptC(GetCenter(nx, ny));
			pDC->LineTo(ptC.x + m_sTH.cx, ptC.y + m_sTH.cy);
			pDC->LineTo(ptC.x + m_sT.cx, ptC.y);
			pDC->MoveTo(ptC.x, ptC.y);
			pDC->LineTo(ptC.x + m_sTH.cx, ptC.y - m_sTH.cy);
			pDC->LineTo(ptC.x + m_sT.cx, ptC.y);
*/
		}
	}
	pDC->SelectObject(penOld);
//	pDC->SelectObject(brOld);
}

void CTileMap::DrawActorElevationGraph(CDC* pDC)
{
	CRect rcDraw;
//	OnPrepareDC(pDC);	// CScroll changes the viewport origin and mapping mode.
	pDC->GetClipBox(rcDraw);

	CPen penRed(PS_SOLID, 1, PALETTERGB(255,0,0));
	CPen penRedDot(PS_DOT, 1, PALETTERGB(255,0,0));
	CPen penBlue(PS_SOLID, 1, PALETTERGB(0,0,255));
	CPen penBlueDot(PS_DOT, 1, PALETTERGB(0,0,255));
//	CBrush brush(HS_CROSS, PALETTERGB(255,255,0));	// Yellow

	CPen* penOld = pDC->SelectObject(&penRed);
	pDC->SetBkMode(TRANSPARENT);
//	CBrush* brOld = pDC->SelectObject(&brush);

//	pDC->Rectangle(&rcDraw);
	for (int ny=0; ny < m_sTiles.cy; ny += 2)
	{
		int nx2 = m_sTiles.cx - 1;
		for (int nx=0; nx < nx2; nx++)
		{
			TILE &T0 = m_apTile[ny][nx];
			CPoint ptC0(GetCenter(nx, ny));
			if (T0.nEA)
			{
				CPoint ptC00(ptC0);	// Save before elevation
				ptC0.y -= T0.nEA;
				pDC->MoveTo(ptC00);
				pDC->SelectObject((T0.nEA < 0) ? &penRed : &penRedDot);
				pDC->LineTo(ptC0);
			}

			TILE &T3 = m_apTile[ny][nx+1];
			CPoint ptC3(GetCenter(nx+1, ny));
			if (T3.nEA)
			{
				ptC3.y -= T3.nEA;
			}

			if (ny >= 1)
			{
				TILE &T1 = m_apTile[ny-1][nx];
				CPoint ptC1(GetCenter(nx, ny-1));
				if (T1.nEA)
				{
					CPoint ptC10(ptC1);	// Save before elevation
					ptC1.y -= T1.nEA;
					pDC->MoveTo(ptC10);
					pDC->SelectObject((T1.nEA < 0) ? &penRed : &penRedDot);
					pDC->LineTo(ptC1);
				}
				pDC->MoveTo(ptC0);
				pDC->SelectObject(T1.pPS ? &penBlue : &penBlueDot);
				pDC->LineTo(ptC1);
				pDC->SelectObject(T3.pPS ? &penBlue : &penBlueDot);
				pDC->LineTo(ptC3);
			}
			if (ny < (m_sTiles.cy-1))
			{
				TILE &T2 = m_apTile[ny+1][nx];
				CPoint ptC2(GetCenter(nx, ny+1));
				if (T2.nEA)
				{
					CPoint ptC20(ptC2);	// Save before elevation
					ptC2.y -= T2.nEA;
					pDC->MoveTo(ptC20);
					pDC->SelectObject((T2.nEA < 0) ? &penRed : &penRedDot);
					pDC->LineTo(ptC2);
				}
				pDC->MoveTo(ptC0);
				pDC->SelectObject(T2.pPS ? &penBlue : &penBlueDot);
				pDC->LineTo(ptC2);
				pDC->SelectObject(T3.pPS ? &penBlue : &penBlueDot);
				pDC->LineTo(ptC3);
			}
/*
			CPoint ptC(GetCenter(nx, ny));
			pDC->LineTo(ptC.x + m_sTH.cx, ptC.y + m_sTH.cy);
			pDC->LineTo(ptC.x + m_sT.cx, ptC.y);
			pDC->MoveTo(ptC.x, ptC.y);
			pDC->LineTo(ptC.x + m_sTH.cx, ptC.y - m_sTH.cy);
			pDC->LineTo(ptC.x + m_sT.cx, ptC.y);
*/
		}
	}
	pDC->SelectObject(penOld);
//	pDC->SelectObject(brOld);
}

// Synchronize EA (Actor Elevation) with Sprite Elevation
BOOL CTileMap::SynchronizeAllEA()
{
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE &T = m_apTile[ny][nx];
			T.nEA = T.pPS ? T.pPS->GetElevation() : 0;
		}
	}
	return TRUE;
}

/*
void CTileMap::RenderGrid(const HBITMAP hbm, const CRect* pClipRect)
{
	CRect rcDraw;
	rcDraw = (!pClipRect)
			? CRect(0, 0, m_sScr.cx-1, m_sScr.cy-1)
			: *pClipRect;

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);	// create a memory dc that is compatible with current screen
	CBitmap* pbmOld	= dcMem.SelectObject(CBitmap::FromHandle(hbm));

	CPen penOdd(PS_SOLID, 1, PALETTERGB(255,0,0));
	CPen penEven(PS_SOLID, 1, PALETTERGB(0,0,255));

	CPen* penOld = (CPen*)dcMem.SelectObject(&penOdd);

	int ny = rcDraw.top / m_sTH.cy;
	int ny2 = rcDraw.bottom / m_sTH.cy + 2;
	if (ny2 > m_sTiles.cy)
		ny2 = m_sTiles.cy;
	int nx1 = rcDraw.left / m_sT.cx;
	int nx2 = (m_sTH.cx + rcDraw.right) / m_sT.cx + 1;
	if (nx2 > m_sTiles.cx)
		nx2 = m_sTiles.cx;
	for (; ny < ny2; ny++)
	{
		CPoint ptLT;
		ptLT.y = GetLTy(ny);
		dcMem.SelectObject((ny % 2 == 0) ? &penEven : &penOdd);
		for (int nx = nx1; nx < nx2; nx++)
		{
			ptLT.x = GetLTx(nx, ny);
			int x1 = ptLT.x + m_sTH.cx - 2;
			int x2 = x1 + 1;
			int x3 = ptLT.x + m_sT.cx - 3;
			int y1 = ptLT.y + m_sTH.cy - 1;
			int y2 = y1 + 1;
			int y3 = ptLT.y + m_sT.cy - 1;
			dcMem.MoveTo(ptLT.x,	y1);
			dcMem.LineTo(x1,	ptLT.y);
			dcMem.MoveTo(x2,	ptLT.y);
			dcMem.LineTo(x3,	y1);
			dcMem.MoveTo(x3,	y2);
			dcMem.LineTo(x2,	y3);
			dcMem.MoveTo(x1,	y3);
			dcMem.LineTo(ptLT.x,	y2);
		}
	}
	dcMem.SelectObject(penOld);
	dcMem.SelectObject(pbmOld);
}
*/

///////////////////////////////////////////////////////////////////////
// Tile Manipulations

CPhasedSprite* CTileMap::HitTest(const CPoint& point)
{
	CPoint ptId(GetNearestTileIndex(point));
	return m_apTile[ptId.y][ptId.x].pPS;
}

BOOL CTileMap::InsideTile(const CPoint& ptTileID, const CPoint& point) const
{
	CPoint	pt(point);
	CPoint	ptLT(GetLT(ptTileID.x, ptTileID.y));
	if ((pt.x < ptLT.x) || (pt.x >= (ptLT.x+m_sT.cx)))
		return FALSE;
	TILE& T = m_apTile[ptTileID.y][ptTileID.x];
	if (T.pPS && T.pPS->GetElevation())
		pt.y -= T.pPS->GetElevation();
	if ((pt.y < ptLT.y) || (pt.y > (ptLT.y+m_sT.cy)))
		return FALSE;
	CPoint ptID(GetNearestTileIndex(pt));
	return (ptID == ptTileID);
}

// Sprite elevation
// returns 0 for NULL tile
int CTileMap::GetElevation(const CPoint& ptID) const
{
	TILE& T = m_apTile[ptID.y][ptID.x];
	return T.pPS ? T.pPS->GetElevation() : 0;
}

void CTileMap::InsertList(CPhasedSprite* pPS)
{
	if (!pPS)
		return;
	if (m_pSpriteList)
		m_pSpriteList->Insert(pPS);
	if (m_pAniList && pPS->GetAniType())
		m_pAniList->Insert(pPS);
}

void CTileMap::RemoveList(CPhasedSprite* pPS)
{
	if (!pPS)
		return;
	if (m_pAniList)	//  && pPS->GetAniType())
		m_pAniList->Remove(pPS);
	if (m_pSpriteList)
		m_pSpriteList->Remove(pPS);
}

// Find the entry tile matching szFromID
// If not found, return any other entry point found last
CPoint CTileMap::GetEntryID(LPCTSTR szFromID) const
{
	CPoint ptID(10/2, 24/2);
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			CPhasedSprite*& pPS = m_apTile[ny][nx].pPS;
			if (pPS && (pPS->GetLinkType() == CPhasedSprite::HLINK_U2_ENTRY))
			{
				ptID = CPoint(nx, ny);
				char szName[256];
				lstrcpy(szName, *pPS->GetHyperlink());
				ASSERT((szName[0] == 'e') && (szName[1] == ':'));
				if (lstrcmpi(&szName[2], szFromID) == 0)	// found
				{
					TRACE("Entry(From %s) found.\n", szFromID);
					return ptID;
				}
			}
		}
	}
	TRACE("Entry(From %s) not found!\n", szFromID);
	return ptID;	// Not found, but anyway return another entry
}

/////////////////////////////////////////////////////////////////////////////
#ifdef MAPEDITOR

BOOL CTileMap::LoadGrid(const WORD wResId)
{
	BOOL bResult = TRUE;
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE &T = m_apTile[ny][nx];
			// Resource Allocation via Resource Manager
			CDIB* pDIB = gResMan.LoadDIB(wResId, TRUE);	// LoadMasterPalette
			if (!pDIB)
			{
				TRACE("Grid resource load error!\n");
				if (T.pGridPS)
					delete T.pGridPS;
				T.pGridPS = NULL;
				bResult = FALSE;
			}
			else	// DIB found
			{
				CPhasedSprite* pPS = new CPhasedSprite;
				pPS->SetDIB(pDIB);	// link DIB resource to this sprite
				if (T.pGridPS)
					delete T.pGridPS;
				T.pGridPS = pPS;
				
				pPS->SetType(SPRITE_TILE);
				pPS->SetNumCells(8, 1);

				CPoint ptID(nx, ny);
				SetGridImage(ptID, T.wDA);

				CPoint ptLT(GetLT(nx, ny));
				pPS->SetLT(ptLT);
				pPS->SetZByEarth();
				if (m_pPalette)
					pPS->MapColorsToPalette(m_pPalette);
			}
		}
	}
	return bResult;
}

// Recalculate all DAs from the left top tile
BOOL CTileMap::RecalculateDA()
{
	for (int ny=0; ny < m_sTiles.cy; ny++)
	{
		for (int nx=0; nx < m_sTiles.cx; nx++)
		{
			TILE &T = m_apTile[ny][nx];
			CPoint ptID(nx, ny);
			SetDA(ptID, T.pPS ? T.wDA : DA_CLOSED);
		}
	}
	return TRUE;
}

// Overwrites existing tile
BOOL CTileMap::Insert(CPhasedSprite* pPS)
{
	if (!pPS)
		return FALSE;
	CPoint ptID(GetNearestTileIndex(pPS));
	TILE& T = m_apTile[ptID.y][ptID.x];
	if (T.pPS)
	{
		RemoveList(T.pPS);
		delete T.pPS;	// Replace existing sprite
	}
	CPoint ptLT(GetLT(ptID.x, ptID.y));
	ptLT.y -= pPS->GetElevation();
	pPS->SetLT(ptLT);
	pPS->SetZByEarth();
	T.pPS		= pPS;	// Newly assign the tile sprite
	T.nEA		= pPS->GetElevation();
	SetDA(ptID, DA_OPEN);
	InsertList(pPS);
	return TRUE;
}

void CTileMap::Delete(CPhasedSprite* pPS)
{
	if (!pPS)
		return;
	CPoint ptID(GetNearestTileIndex(pPS));
	TILE& T = m_apTile[ptID.y][ptID.x];
	ASSERT(T.pPS == pPS);
	if (T.pPS)
	{
		RemoveList(T.pPS);
		delete T.pPS;
		T.pPS		= NULL;
		T.nEA		= 0;
		SetDA(ptID, DA_CLOSED);
	}
	return;
}

BOOL CTileMap::MoveSpriteTo(CPhasedSprite* pPS, CPoint& ptTo)
{
	if (!pPS)
		return FALSE;
	// Get the Sprite's Center point
	CPoint ptIdFrom(GetNearestTileIndex(pPS));
	CPoint ptIdTo(GetNearestTileIndex(ptTo));
	if (ptIdFrom == ptIdTo)	// Same Indices
		return FALSE;

	TILE& TFrom	= m_apTile[ptIdFrom.y][ptIdFrom.x];
	TILE& TTo	= m_apTile[ptIdTo.y][ptIdTo.x];
	ASSERT(TFrom.pPS == pPS);
	
	if (TTo.pPS)
	{
		RemoveList(TTo.pPS);
		delete TTo.pPS;	// Delete Destination Sprite
	}
	TTo.pPS	= TFrom.pPS;	// Newly assign the tile sprite
	TTo.nEA = TFrom.nEA;
	ASSERT(TFrom.pPS);

	TFrom.pPS	= NULL;	// Do not delete TFrom.pPS!
	TFrom.nEA	= 0;
	TFrom.wDA	= DA_OPEN;

	CPoint ptLT = GetLT(ptIdTo.x, ptIdTo.y);
	ptLT.y -= pPS->GetElevation();
	pPS->SetLT(ptLT);
	pPS->SetZByEarth();
	return TRUE;
}

// Set DA of the specified tile and other four tiles in its neighbor
void CTileMap::SetDA(const CPoint& ptID, const WORD wDA)
{
	const int& x = ptID.x;
	const int& y = ptID.y;
	m_apTile[y][x].wDA = wDA;
	SetGridImage(ptID, wDA);
	if ((y % 2) == 0)	// y = 2n
	{
		if (y > 0)
		{
			if (x > 0)
			{
				WORD& wBL = m_apTile[y-1][x-1].wDA;
				if ((wDA & DA_BL) == DA_BL)
					wBL |= DA_FL;
				else
					wBL &= ~DA_FL;
				SetGridImage(CPoint(x-1, y-1), wBL);
			}
			WORD& wBR = m_apTile[y-1][x].wDA;
			if ((wDA & DA_BR) == DA_BR)
				wBR |= DA_FR;
			else
				wBR &= ~DA_FR;
			SetGridImage(CPoint(x, y-1), wBR);
		}
		if ((y+1) < m_sTiles.cy)
		{
			if (x > 0)
			{
				WORD& wFR = m_apTile[y+1][x-1].wDA;
				if ((wDA & DA_FR) == DA_FR)
					wFR |= DA_BR;
				else
					wFR &= ~DA_BR;
				SetGridImage(CPoint(x-1, y+1), wFR);
			}
			WORD& wFL = m_apTile[y+1][x].wDA;
			if ((wDA & DA_FL) == DA_FL)
				wFL |= DA_BL;
			else
				wFL &= ~DA_BL;
			SetGridImage(CPoint(x, y+1), wFL);
		}
	}
	else		// y = 2n + 1
	{
		if (y > 0)
		{
			WORD& wBL = m_apTile[y-1][x].wDA;
			if ((wDA & DA_BL) == DA_BL)
				wBL |= DA_FL;
			else
				wBL &= ~DA_FL;
			SetGridImage(CPoint(x, y-1), wBL);
			if ((x+1) < m_sTiles.cx)
			{
				WORD& wBR = m_apTile[y-1][x+1].wDA;
				if ((wDA & DA_BR) == DA_BR)
					wBR |= DA_FR;
				else
					wBR &= ~DA_FR;
				SetGridImage(CPoint(x+1, y-1), wBR);
			}
		}
		if ((y+1) < m_sTiles.cy)
		{
			WORD& wFR = m_apTile[y+1][x].wDA;
			if ((wDA & DA_FR) == DA_FR)
				wFR |= DA_BR;
			else
				wFR &= ~DA_BR;
			SetGridImage(CPoint(x, y+1), wFR);
			if ((x+1) < m_sTiles.cx)
			{
				WORD& wFL = m_apTile[y+1][x+1].wDA;
				if ((wDA & DA_FL) == DA_FL)
					wFL |= DA_BL;
				else
					wFL &= ~DA_BL;
				SetGridImage(CPoint(x+1, y+1), wFL);
			}
		}
	}
}

void CTileMap::SetGridImage(const CPoint& ptID, const WORD wDA)
{
	TILE& T = m_apTile[ptID.y][ptID.x];
	ASSERT(T.pGridPS);
	int nCellID=0;
	WORD wImOp = T.pGridPS->GetImOp() & ~ORIENT_MASK;
	switch (wDA)
	{
	case DA_OPEN:	nCellID = 1 + ptID.y % 2;	break;
	case DA_CLOSED:	nCellID = 0;	break;
	case DA_FR:		nCellID = 3;	break;
	case DA_FL:		nCellID = 3;	wImOp |= IMAGE_FLIP;	break;
	case DA_BR:		nCellID = 3;	wImOp |= (IMAGE_FLIP | IMAGE_VERTICAL);	break;
	case DA_BL:		nCellID = 3;	wImOp |= IMAGE_VERTICAL;	break;
	case (DA_FR | DA_FL):	nCellID = 4;	break;
	case (DA_BR | DA_BL):	nCellID = 4;	wImOp |= IMAGE_VERTICAL;	break;
	case (DA_FR | DA_BL):	nCellID = 5;	break;
	case (DA_FL | DA_BR):	nCellID = 5;	wImOp |= IMAGE_FLIP;	break;
	case (DA_FR | DA_BR):	nCellID = 6;	break;
	case (DA_FL | DA_BL):	nCellID = 6;	wImOp |= IMAGE_FLIP;	break;
	case (DA_FR | DA_FL | DA_BR):	nCellID = 7;	break;
	case (DA_FR | DA_FL | DA_BL):	nCellID = 7;	wImOp |= IMAGE_FLIP;	break;
	case (DA_FR | DA_BR | DA_BL):	nCellID = 7;	wImOp |= (IMAGE_FLIP | IMAGE_VERTICAL);	break;
	case (DA_FL | DA_BR | DA_BL):	nCellID = 7;	wImOp |= IMAGE_VERTICAL;	break;
	default:	TRACE("Invalid DA: %0x\n", wDA);
	}
	T.pGridPS->SetCell(nCellID);
	T.pGridPS->SetImOp(wImOp);
}

// Render the tiles to the given DIB within specified region
// I'll not use this method.
// Tiles will be rendered as normal sprites in the CSpriteList.
// Grid tiles will use this render method
void CTileMap::RenderGrid(CDIB* pDIB, const CRect* pClipRect)
{
	CRect rcDraw;
	if (!pClipRect)		// pClipRect == NULL means drawing on the entire area
		pDIB->GetRect(rcDraw);
	else
		rcDraw = *pClipRect;

	int ny = 0;	// = rcDraw.top / m_sTH.cy;
	int ny2 = m_sTiles.cy;	//	= rcDraw.bottom / m_sTH.cy + 2;
	if (ny2 > m_sTiles.cy)
		ny2 = m_sTiles.cy;
	int nx1 = rcDraw.left / m_sT.cx;
	int nx2 = (m_sTH.cx + rcDraw.right) / m_sT.cx + 1;
	if (nx2 > m_sTiles.cx)
		nx2 = m_sTiles.cx;

	for (; ny < ny2; ny++)
	{
		for (int nx=nx1; nx < nx2; nx++)
		{
			TILE& T = m_apTile[ny][nx];
			if (T.pGridPS)
				T.pGridPS->Render(pDIB, &rcDraw);
		}
	}
}

#endif // MAPEDITOR