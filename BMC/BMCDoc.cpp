// BMCDoc.cpp : implementation of the CBMCDoc class
//

#include "stdafx.h"
#include "BMC.h"

#include "BMCDoc.h"
#include "BMCView.h"

#include "../UC2Ani/DIB.h"
#include "../UC2Ani/PhSprite.h"

#include "PaletteDlg.h"
#include "InputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBMCDoc

IMPLEMENT_DYNCREATE(CBMCDoc, CDocument)

BEGIN_MESSAGE_MAP(CBMCDoc, CDocument)
	//{{AFX_MSG_MAP(CBMCDoc)
	ON_COMMAND(ID_FILE_LOADSPRITE, OnFileLoadsprite)
	ON_COMMAND(ID_FILE_LOADBKGND, OnFileLoadbkgnd)
	ON_COMMAND(ID_VIEW_PALETTE, OnViewPalette)
	ON_COMMAND(ID_VIEW_OUTLINE, OnViewOutline)
	ON_COMMAND(ID_FILE_SAVE_BKG, OnFileSaveBkg)
	ON_COMMAND(ID_FILE_SAVE_SPRITE, OnFileSaveSprite)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_BKG, OnUpdateFileSaveBkg)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_SPRITE, OnUpdateFileSaveSprite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMCDoc construction/destruction

CBMCDoc::CBMCDoc()
{
    m_pBkgndDIB = NULL;
}

CBMCDoc::~CBMCDoc()
{
    if (m_pBkgndDIB)
        delete m_pBkgndDIB;
    m_SpriteList.RemoveAll();
}

BOOL CBMCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    // Tell the sprite list notification object where the view is
    // so when we add sprites the dirty list can be maintained automatically.
    CBMCView* pView = GetBMCView();
    ASSERT(pView);
    m_SpriteList.m_NotifyObj.SetView(pView);

    // Create a new default background DIB just so
	// there will be something to look at
    CDIB* pDIB = new CDIB;
    pDIB->Create(320, 240);
    SetBackground(pDIB);
    SetModifiedFlag(FALSE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBMCDoc serialization

void CBMCDoc::Serialize(CArchive& ar)
{
    CDocument::Serialize(ar);
    if (ar.IsStoring())
	{
        if (m_pBkgndDIB)
		{
            ar << (DWORD) 1; // say we have a bkgnd
            m_pBkgndDIB->Serialize(ar);
        }
		else
		{
            ar << (DWORD) 0; // say we have no bkgnd
        }
        m_SpriteList.Serialize(ar);
    }
	else
	{
        DWORD dw;
        // see if we have a background to load
        ar >> dw;
        if (dw != 0)
		{
            CDIB* pDIB = new CDIB;
            pDIB->Serialize(ar);
            // Attach it to the document
            SetBackground(pDIB);
        }
        // read the sprite list
        CBMCView* pView = GetBMCView();
        ASSERT(pView);
        m_SpriteList.m_NotifyObj.SetView(pView);
        m_SpriteList.Serialize(ar);

        SetModifiedFlag(FALSE);
        UpdateAllViews(NULL, 0, NULL);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CBMCDoc diagnostics

#ifdef _DEBUG
void CBMCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBMCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBMCDoc commands

void CBMCDoc::SetTitle(LPCTSTR lpszTitle) 
{
//	UNREFERENCED_PARAMETER(lpszTitle);

//	CString strTitle("UniChat 2.0");
//	if (lpszTitle)
//		strTitle += lpszTitle;
//	CDocument::SetTitle(strTitle);
	CDocument::SetTitle(lpszTitle);
}

/////////////////////////////////////////////////////////////////////////////
// return a pointer to the off-screen buffered view
CBMCView* CBMCDoc::GetBMCView()
{
	POSITION pos = GetFirstViewPosition();
	ASSERT(pos);
	CBMCView* pView = (CBMCView*)GetNextView(pos);
	ASSERT(pView);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CBMCView)));
	return pView;
}

void CBMCDoc::OnFileLoadbkgnd() 
{
	// Create a DIB to hold the image
	CDIB* pDIB = new CDIB;
	// Show the file open dialog for a DIB
	CInputDlg dlg;
	dlg.m_strData = "DataSource|file";
	if (dlg.DoModal() != IDOK)
		return;

	if (!pDIB->Load(dlg.m_strData, "c:\\uc2\\bmc\\master.pal"))
	{
		delete pDIB;
		return;
	}
/*
	if (!pDIB->Load((char*)NULL, "master.pal"))
	{
		delete pDIB;
		return;
	}
*/	CString* pstrFile = pDIB->GetName();
	SetTitle(*pstrFile);
	// Make sure this is an 8 bpp DIB
	BITMAPINFO* pBMI = pDIB->GetBitmapInfoAddress();
	ASSERT(pBMI);
	if (pBMI->bmiHeader.biBitCount != 8)
	{
		AfxMessageBox("Only 8 bpp DIBs are supported");
		delete pDIB;
		return;
	}
	// replace any existing background DIB with the new one
	if (!SetBackground(pDIB))
		delete pDIB;
}

void CBMCDoc::OnFileLoadsprite() 
{
	// Create a sprite to hold the image
	CPhasedSprite* pSprite = new CPhasedSprite;
	// Show the file open dialog for a Sprite
	if (!pSprite->Load((char*)NULL, "master.pal"))
	{
		delete pSprite;
		return;
	}
	CString* pstrFileBkg	= m_pBkgndDIB->GetName();
	CString* pstrFileSprite	= pSprite->GetDIB()->GetName();
	CString strTitle;
	strTitle.Format("(B)%s,(S)%s", *pstrFileBkg, *pstrFileSprite);
	SetTitle(strTitle);
	// Make sure this is an 8 bpp DIB
	BITMAPINFO* pBMI = pSprite->GetDIB()->GetBitmapInfoAddress();
	ASSERT(pBMI);
	if (pBMI->bmiHeader.biBitCount != 8)
	{
		AfxMessageBox("Only 8 bpp DIBs are supported");
		delete pSprite;
		return;
	}
	// add it to the sprite list
	m_SpriteList.Insert(pSprite);
//	SetModifiedFlag(TRUE);

	// Tell the view about the new sprite
	GetBMCView()->NewSprite(pSprite);
}

// Set a new background DIB
BOOL CBMCDoc::SetBackground(CDIB* pDIB)
{
	// Delete any existing sprites
	m_SpriteList.RemoveAll();

	// Delete any existing background DIB and set the new one
	if (m_pBkgndDIB)
		delete m_pBkgndDIB;
	m_pBkgndDIB = pDIB;

	// Note that the doc has changed
//	SetModifiedFlag(TRUE);

	// Tell the view that it needs to create a new buffer and palette
	CBMCView* pView = GetBMCView();
	ASSERT(pView);
	return pView->NewBackground(m_pBkgndDIB);
}

void CBMCDoc::GetSceneRect(CRect& prc)
{
	if (!m_pBkgndDIB)
		return;
	m_pBkgndDIB->GetRect(prc);
}

void CBMCDoc::OnViewPalette() 
{
	CPaletteDlg		palDlg;

	CBMCView* pView = GetBMCView();
	if (pView)
		palDlg.SetPalette(pView->GetOSBPalette());
	palDlg.DoModal();
}

void CBMCDoc::OnViewOutline() 
{
	CBMCView* pView = GetBMCView();
	pView->ToggleOutline();
}

void CBMCDoc::OnFileSaveBkg() 
{
	if (m_pBkgndDIB)
	{
		CString* pstrFile = m_pBkgndDIB->GetName();
		// Reload to restore original bitmaps
		CDIB* pDIB = new CDIB;
		// Show the file open dialog for a DIB
		if (!pDIB->Load(*pstrFile))
		{
			delete pDIB;
			return;
		}
		pDIB->Save();
		delete pDIB;
	}
}

void CBMCDoc::OnFileSaveSprite() 
{
	CPhasedSprite* pS = GetBMCView()->GetCapturedSprite();
	if (pS)
	{
		CString* pstrFile = pS->GetDIB()->GetName();
		// Reload to restore original bitmaps
		CDIB* pDIB = new CDIB;
		// Show the file open dialog for a DIB
		if (!pDIB->Load(*pstrFile))
		{
			delete pDIB;
			return;
		}
		pDIB->Save();
		delete pDIB;
	}
}

void CBMCDoc::OnUpdateFileSaveBkg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pBkgndDIB != NULL);
}

void CBMCDoc::OnUpdateFileSaveSprite(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetBMCView()->GetCapturedSprite() != NULL);
}
