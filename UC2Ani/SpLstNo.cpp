//
//	CSpriteNotifyObj :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "dib.h"
#include "dibpal.h"
#include "spriteno.h"
#include "splstno.h"
#include "sprite.h"
#include "spritlst.h"
#include "osbview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteListNotifyObj

CSpriteListNotifyObj::CSpriteListNotifyObj()
{
	m_pSpriteList = NULL;
	m_pBufferView = NULL;
}

CSpriteListNotifyObj::~CSpriteListNotifyObj()
{
}

// Notification callback from a CSprite object.
void CSpriteListNotifyObj::Change(CSprite* pSprite, CHANGETYPE change,
								CRect* pRect1, CRect* pRect2)
{
	if (change & CSpriteNotifyObj::ZORDER)
	{
		// Reposition the sprite in the z-order list.
		ASSERT(m_pSpriteList);
		m_pSpriteList->Reorder(pSprite);
		// Add the sprite position to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
	}
	if (change & CSpriteNotifyObj::POSITION)
	{
		// pRect1 and pRect2 point to old and new rectangle positions;
		// add these rectangles to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
		m_pBufferView->AddDirtyRegion(pRect2);
	}
	if (change & CSpriteNotifyObj::IMAGE)
	{
		// redraw the sprite
		// Add the sprite position to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
	}
}
