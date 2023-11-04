// MapEdDoc.h : interface of the CMapEdDoc class
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#if !defined(AFX_MAPEDDOC_H__7ECC1E0C_9C09_11D1_80E2_288A06C10000__INCLUDED_)
#define AFX_MAPEDDOC_H__7ECC1E0C_9C09_11D1_80E2_288A06C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDIB;
class CMapEdView;
class CMapListView;
class CResMan;
class CTiles;
class CStage;

enum MAP_EDIT_MODE
{
	TILE_EDIT_MODE,
	SPRITE_EDIT_MODE,
	STAND_EDIT_MODE
};

class CMapEdDoc : public CDocument
{
protected: // create from serialization only
	CMapEdDoc();
	DECLARE_DYNCREATE(CMapEdDoc)

// Attributes
public:
	CMapEdView*		GetMapEdView();
	CMapListView*	GetMapListView();
	CStage*			GetStage()		{ return m_pStage; }
	void			UpdateTitle();
	BOOL			IsTileEditMode() const
					{ return (m_nEditMode == TILE_EDIT_MODE); }
	BOOL			IsStandEditMode() const
					{ return m_bStandEdit; }
	BOOL			IsViewGraph() const { return m_bViewGraph; }
	BOOL			IsViewEAGraph() const { return m_bViewEAGraph; }
	BOOL			IsTileCoordMode() const { return m_bTileCoord; }
	BOOL			IsCreateMode() const { return m_bCreateMode; }

// Operations
public:
	void			SetEditMode(const int nMode)	{ m_nEditMode = nMode; }
	void			SetTileCoordMode(const BOOL bTC)	{ m_bTileCoord = bTC; }
	void			BeginAnimation() const
					{ ((CMapEdApp*)AfxGetApp())->SetStage(m_pStage); }
	void			EndAnimation() const
					{ ((CMapEdApp*)AfxGetApp())->SetStage(NULL); }
	void			PauseAnimation() const
					{ ((CMapEdApp*)AfxGetApp())->SetPause(m_bPause); }

private:
	BOOL			m_bViewEarth;
	BOOL			m_bViewGraph;
	BOOL			m_bViewEAGraph;
	int				m_nEditMode;	// 0: Tile Edit, 1: Sprite Edit
	BOOL			m_bStandEdit;
	BOOL			m_bCreateMode;	// LBUTTONDONW => Create sprite
	BOOL			m_bTileCoord;
	BOOL			m_bPause;		// Pause Animation
	CStage*			m_pStage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapEdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapEdDoc)
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnViewEarth();
	afx_msg void OnUpdateViewEarth(CCmdUI* pCmdUI);
	afx_msg void OnViewPalette();
	afx_msg void OnOptionsEnv();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnEditMode();
	afx_msg void OnUpdateEditMode(CCmdUI* pCmdUI);
	afx_msg void OnViewMapOnly();
	afx_msg void OnUpdateViewMapOnly(CCmdUI* pCmdUI);
	afx_msg void OnViewGraph();
	afx_msg void OnUpdateViewGraph(CCmdUI* pCmdUI);
	afx_msg void OnEditTileCoord();
	afx_msg void OnUpdateEditTileCoord(CCmdUI* pCmdUI);
	afx_msg void OnViewPause();
	afx_msg void OnUpdateViewPause(CCmdUI* pCmdUI);
	afx_msg void OnMenuStageTitle();
	afx_msg void OnEditStand();
	afx_msg void OnUpdateEditStand(CCmdUI* pCmdUI);
	afx_msg void OnEditCreateMode();
	afx_msg void OnUpdateEditCreateMode(CCmdUI* pCmdUI);
	afx_msg void OnMenuRecalcDa();
	afx_msg void OnMenuSyncEa();
	afx_msg void OnViewNoelev();
	afx_msg void OnUpdateViewNoelev(CCmdUI* pCmdUI);
	afx_msg void OnMenuStageMusic();
	afx_msg void OnViewEaGraph();
	afx_msg void OnUpdateViewEaGraph(CCmdUI* pCmdUI);
	afx_msg void OnMenuElevation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDDOC_H__7ECC1E0C_9C09_11D1_80E2_288A06C10000__INCLUDED_)
