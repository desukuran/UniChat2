// MapEdDoc.cpp : implementation of the CMapEdDoc class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#include "stdafx.h"
#include "MapEd.h"

#include "MapEdDoc.h"
#include "MapEdView.h"
#include "MapListView.h"
#include "../Stage.h"
#include "../TileMap.h"
#include "PalDlg.h"
#include "MapEnvDlg.h"
#include "GetTextDlg.h"
#include "GetIntDlg.h"

#include "../UC2Ani/DIB.h"
#include "../UC2Ani/PhSprite.h"

#include "../ResMan.h"
#include "../Parser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CParser	gParser(1024*4);	// to be used as an extern variable in other files
CResMan	gResMan;

double GetMapEditorVersion();

/////////////////////////////////////////////////////////////////////////////
// CMapEdDoc

IMPLEMENT_DYNCREATE(CMapEdDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEdDoc, CDocument)
	//{{AFX_MSG_MAP(CMapEdDoc)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_VIEW_EARTH, OnViewEarth)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EARTH, OnUpdateViewEarth)
	ON_COMMAND(ID_VIEW_PALETTE, OnViewPalette)
	ON_COMMAND(ID_OPTIONS_ENV, OnOptionsEnv)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_EDIT_MODE, OnEditMode)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODE, OnUpdateEditMode)
	ON_COMMAND(ID_VIEW_MAP_ONLY, OnViewMapOnly)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MAP_ONLY, OnUpdateViewMapOnly)
	ON_COMMAND(ID_VIEW_GRAPH, OnViewGraph)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRAPH, OnUpdateViewGraph)
	ON_COMMAND(ID_EDIT_TILE_COORD, OnEditTileCoord)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TILE_COORD, OnUpdateEditTileCoord)
	ON_COMMAND(ID_VIEW_PAUSE, OnViewPause)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE, OnUpdateViewPause)
	ON_COMMAND(ID_MENU_STAGE_TITLE, OnMenuStageTitle)
	ON_COMMAND(ID_EDIT_STAND, OnEditStand)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STAND, OnUpdateEditStand)
	ON_COMMAND(ID_EDIT_CREATE_MODE, OnEditCreateMode)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CREATE_MODE, OnUpdateEditCreateMode)
	ON_COMMAND(ID_MENU_RECALC_DA, OnMenuRecalcDa)
	ON_COMMAND(ID_MENU_SYNC_EA, OnMenuSyncEa)
	ON_COMMAND(ID_VIEW_NOELEV, OnViewNoelev)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NOELEV, OnUpdateViewNoelev)
	ON_COMMAND(ID_MENU_STAGE_MUSIC, OnMenuStageMusic)
	ON_COMMAND(ID_VIEW_EA_GRAPH, OnViewEaGraph)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EA_GRAPH, OnUpdateViewEaGraph)
	ON_COMMAND(ID_MENU_ELEVATION, OnMenuElevation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEdDoc construction/destruction

CMapEdDoc::CMapEdDoc()
{
	TRACE0("CMapEdDoc::CMapEdDoc()\n");
	m_pStage		= NULL;
	m_bViewEarth	= FALSE;
	m_bViewGraph	= FALSE;
	m_bViewEAGraph	= FALSE;
	m_nEditMode		= SPRITE_EDIT_MODE;
	m_bCreateMode	= TRUE;
	m_bTileCoord	= TRUE;
	m_bPause		= FALSE;
	m_bStandEdit	= FALSE;
}

CMapEdDoc::~CMapEdDoc()
{
	TRACE0("CMapEdDoc::~CMapEdDoc()\n");
	if (m_pStage)
	{
		EndAnimation();
		delete m_pStage;
	}
}

BOOL CMapEdDoc::OnNewDocument()
{
	TRACE0("CMapEdDoc::OnNewDocument()\n");
	EndAnimation();
	if (!CDocument::OnNewDocument())
		return FALSE;

    CMapEdView* pView = GetMapEdView();
    ASSERT(pView);

	if (m_pStage)
	{
		m_pStage->DeleteStage();
		m_pStage->ClearFilename();
	}
	else
	{
		m_pStage = new CStage;
		m_pStage->Initialize(pView);
	}

	CMapEnvDlg	dlg;
	dlg.m_strDataPath = *gResMan.GetResPath();
	dlg.m_strPalFile = *m_pStage->GetPalFileName();
	CTileMap* pTM = m_pStage->GetTileMap();
	CSize szT	= pTM ? pTM->GetTileSize() : CSize(64, 32);
	CSize szScr	= pTM ? pTM->GetScreenSize() : CSize(640, 368);	//640, 384);
	dlg.m_nTileWidth	= szT.cx;
	dlg.m_nTileHeight	= szT.cy;
	dlg.m_nScrWidth		= szScr.cx;
	dlg.m_nScrHeight	= szScr.cy;
	if (pTM)
	{
		if (AfxMessageBox("Delete current Stage?") == IDCANCEL)
			return FALSE;
		m_pStage->ClearFilename();
		m_pStage->DeleteStage();
	}
	if (dlg.DoModal() == IDOK)
	{
		szT		= CSize(dlg.m_nTileWidth, dlg.m_nTileHeight);
		szScr	= CSize(dlg.m_nScrWidth, dlg.m_nScrHeight);
		gResMan.SetResPath(dlg.m_strDataPath);
		m_pStage->SetPalFileName(dlg.m_strPalFile);
	}

	if (!m_pStage->CreateStage(szT, szScr))
		return FALSE;
	pView->AdjustFrameWindow();
	BeginAnimation();

	UpdateAllViews(NULL);	// COSBView::OnUpdate() - Render & Draw
							// CMapListView::OnUpdate - UpdateList()
//    SetModifiedFlag(FALSE);
	return TRUE;
}

void CMapEdDoc::DeleteContents() 
{
	TRACE("CMapEdDoc::DeleteContents()\n");
	SetModifiedFlag(FALSE);
	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// CMapEdDoc serialization

void CMapEdDoc::Serialize(CArchive& ar)
{
    CDocument::Serialize(ar);
	if (ar.IsStoring())
	{
/*
        m_SpriteList.Serialize(ar);
*/
	}
	else	// Reading
	{
/*
        // read the sprite list
        CMapEdView* pView = GetMapEdView();
        ASSERT(pView);
        m_SpriteList.m_NotifyObj.SetView(pView);
        m_SpriteList.Serialize(ar);

		SetModifiedFlag(FALSE);
        UpdateAllViews(NULL, 0, NULL);
*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEdDoc diagnostics

#ifdef _DEBUG
void CMapEdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEdDoc commands

CMapEdView* CMapEdDoc::GetMapEdView()
{
	POSITION pos = GetFirstViewPosition();
	ASSERT(pos);
	CMapEdView* pView = (CMapEdView*)GetNextView(pos);
	ASSERT(pView);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CMapEdView)));
	return pView;
}

CMapListView* CMapEdDoc::GetMapListView()
{
	POSITION pos = GetFirstViewPosition();
	ASSERT(pos);
	GetNextView(pos);
	CMapListView* pView = (CMapListView*)GetNextView(pos);
	ASSERT(pView);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CMapListView)));
	return pView;
}

void CMapEdDoc::SetTitle(LPCTSTR lpszTitle) 
{
//	UNREFERENCED_PARAMETER(lpszTitle);

	CString strTitle;
	strTitle.Format("Turtle Quarter View Editor V%.2f ", GetMapEditorVersion());
	if (lpszTitle)
		strTitle += lpszTitle;
	CDocument::SetTitle(strTitle);
}

void CMapEdDoc::OnOptionsEnv() 
{
	if (!m_pStage)
		return;
	CMapEnvDlg	dlg;
	dlg.m_strDataPath = *gResMan.GetResPath();
	dlg.m_strPalFile = *m_pStage->GetPalFileName();
	CTileMap* pTM = m_pStage->GetTileMap();
	if (!pTM)
		return;
	CSize szT(pTM->GetTileSize());
	CSize szScr(pTM->GetScreenSize());
	dlg.m_nTileWidth	= szT.cx;
	dlg.m_nTileHeight	= szT.cy;
	dlg.m_nScrWidth		= szScr.cx;
	dlg.m_nScrHeight	= szScr.cy;
	dlg.SetReadOnly();
	if (dlg.DoModal() == IDOK)
	{
		gResMan.SetResPath(dlg.m_strDataPath);
		m_pStage->SetPalFileName(dlg.m_strPalFile);
	}
}

void CMapEdDoc::OnFileOpen() 
{
	if (!m_pStage)
		return;
	EndAnimation();
	m_pStage->Load();
    CMapEdView* pView = GetMapEdView();
	pView->AdjustFrameWindow();
	BeginAnimation();
	UpdateAllViews(NULL);
	UpdateTitle();
}

void CMapEdDoc::OnFileSave() 
{
	if (!m_pStage)
		return;
	m_pStage->Save(*m_pStage->GetFileName());
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
	UpdateTitle();
}

void CMapEdDoc::OnFileSaveAs() 
{
	if (!m_pStage)
		return;
	m_pStage->Save();
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
	UpdateTitle();
}

void CMapEdDoc::UpdateTitle()
{
	CString strTitle;
	CString* pS1 = m_pStage->GetFileName();
	CString* pS2 = m_pStage->GetMapFileName();
	CString* pS3 = m_pStage->GetPalFileName();
	if (pS1)
	{
		strTitle = "[" + *pS1 + "]";
	}
	if (pS2)
	{
		strTitle += "[";
		strTitle += *pS2;
		strTitle += "]";
	}
	if (pS3)
	{
		strTitle += "[";
		strTitle += *pS3;
		strTitle += "]";
	}
	SetTitle(strTitle);
}

/////////////////////////////////////////////////////////////////////////////
// Edit Mode

void CMapEdDoc::OnEditMode() 
{
	m_nEditMode = (m_nEditMode == TILE_EDIT_MODE) ?
				SPRITE_EDIT_MODE :
				TILE_EDIT_MODE;
}

void CMapEdDoc::OnUpdateEditMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nEditMode == TILE_EDIT_MODE);
}

void CMapEdDoc::OnEditTileCoord() 
{
	m_bTileCoord = !m_bTileCoord;
}

void CMapEdDoc::OnUpdateEditTileCoord(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bTileCoord);
}

void CMapEdDoc::OnViewNoelev()		// No Elevation
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	wRM ^= RM_ELEV;
	m_pStage->SetRenderMode(wRM);
	m_bPause = ((wRM & RM_ELEV) != RM_ELEV);
	PauseAnimation();
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
}

void CMapEdDoc::OnUpdateViewNoelev(CCmdUI* pCmdUI) 
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	pCmdUI->SetCheck((wRM & RM_ELEV) == RM_ELEV);
}

void CMapEdDoc::OnViewMapOnly() 
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	wRM ^= RM_SPRITE;
	m_pStage->SetRenderMode(wRM);

	m_nEditMode = ((wRM & RM_SPRITE) == RM_SPRITE) ? SPRITE_EDIT_MODE : TILE_EDIT_MODE;
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
}

void CMapEdDoc::OnUpdateViewMapOnly(CCmdUI* pCmdUI) 
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	pCmdUI->Enable((wRM & RM_ELEV) != RM_ELEV);	// enable only for no elevation mode
	pCmdUI->SetCheck((wRM & RM_SPRITE) != RM_SPRITE);
}

void CMapEdDoc::OnViewGraph() 
{
	m_bViewGraph = !m_bViewGraph;
	m_bPause = m_bViewGraph;
	PauseAnimation();
	CMapEdView* pView = GetMapEdView();
	if (pView)
		pView->Invalidate(FALSE);
}

void CMapEdDoc::OnUpdateViewGraph(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewGraph);
}

void CMapEdDoc::OnViewEaGraph() 
{
	m_bViewEAGraph = !m_bViewEAGraph;
	m_bPause = m_bViewEAGraph;
	PauseAnimation();
	CMapEdView* pView = GetMapEdView();
	if (pView)
		pView->Invalidate(FALSE);
}

void CMapEdDoc::OnUpdateViewEaGraph(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewEAGraph);
}

void CMapEdDoc::OnViewGrid() 
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	wRM ^= RM_GRID;
	m_pStage->SetRenderMode(wRM);
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
}

void CMapEdDoc::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	if (!m_pStage)
		return;
	WORD wRM = m_pStage->GetRenderMode();
	pCmdUI->SetCheck((wRM & RM_GRID) == RM_GRID);
}

void CMapEdDoc::OnViewEarth() 
{
}

void CMapEdDoc::OnUpdateViewEarth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewEarth);
}

void CMapEdDoc::OnViewPalette() 
{
	CPalDlg		palDlg;

	CMapEdView* pView = GetMapEdView();
	if (pView)
		palDlg.SetPalette(pView->GetOSBPalette());
	palDlg.DoModal();
}

void CMapEdDoc::OnViewPause() 
{
	m_bPause = !m_bPause;
	PauseAnimation();
}

void CMapEdDoc::OnUpdateViewPause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bPause);
}

void CMapEdDoc::OnMenuStageTitle() 
{
	if (!m_pStage)
		return;
	CGetTextDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_STAGE_TITLE);
	CString strTitle(*m_pStage->GetTitle());
	CString strFile(*m_pStage->GetFileName());
	gResMan.MakeResName(strFile);
	if (strTitle.IsEmpty())
	{
		strTitle.Format("[u2/%s]", strFile);
	}
	else
	{
		int i = strTitle.Find('/');
		if (i <= 0)
		{
			if (strTitle[0] == '[')	// [U2] or [u2]
			{
				CString strTemp;
				int nCount = strTitle.GetLength();
				if (nCount >= 4)
				{
					strTemp = strTitle.Right(nCount-4);
					strTemp.TrimLeft();
					strTitle.Format("[u2/%s]", strFile);
					strTitle += strTemp;
				}
			}
		}
	}
	dlg.m_strText = strTitle;
	if (dlg.DoModal() == IDOK)
		m_pStage->SetTitle(dlg.m_strText);
}

void CMapEdDoc::OnMenuStageMusic() 
{
	if (!m_pStage)
		return;
	CGetTextDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_STAGE_MUSIC);
	dlg.m_strText = *m_pStage->GetMusicSeq();	// "[U2]"
	if (dlg.DoModal() == IDOK)
		m_pStage->SetMusicSeq(dlg.m_strText);
}

void CMapEdDoc::OnEditStand() 
{
	m_bStandEdit = !m_bStandEdit;
	if (!m_pStage)
		return;

	WORD wRM = m_pStage->GetRenderMode();
	if (m_bStandEdit)
		wRM |= RM_GRID;
	else
		wRM &= ~RM_GRID;
	m_pStage->SetRenderMode(wRM);
	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
}

void CMapEdDoc::OnUpdateEditStand(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bStandEdit);
}

void CMapEdDoc::OnEditCreateMode() 
{
	m_bCreateMode = !m_bCreateMode;
}

void CMapEdDoc::OnUpdateEditCreateMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bCreateMode);
}

void CMapEdDoc::OnMenuRecalcDa() 
{
	CMapEdView* pView = GetMapEdView();
	pView->RecalculateDA();
	CMapListView* pMLV = GetMapListView();
	UpdateAllViews(pMLV);
	AfxMessageBox("Recalculating DA(Direction Attribute) - Done");
}

void CMapEdDoc::OnMenuSyncEa() 
{
	CMapEdView* pView = GetMapEdView();
	pView->SynchronizeEA();
	CMapListView* pMLV = GetMapListView();
	UpdateAllViews(pMLV);
	AfxMessageBox("Synchronizing EA(Elevation for Actor) with sprite elevation - Done");
}

void CMapEdDoc::OnMenuElevation() 
{
	CGetIntDlg dlg;
	dlg.m_strCaption.LoadString(IDS_ENTER_TILE_ELEVS);
	dlg.m_nNew = 0;
	if (dlg.DoModal() != IDOK)
		return;

	CTileMap* pTM = m_pStage->GetTileMap();
	pTM->IncreaseElevations(dlg.m_nNew * ELEVATION_UNIT);

	CMapListView* pView = GetMapListView();
	UpdateAllViews(pView);
}
