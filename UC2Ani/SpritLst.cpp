//
//	CSpriteList :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "dib.h"
#include "spriteno.h"
#include "sprite.h"
#include "splstno.h"
#include "spritlst.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteList

IMPLEMENT_SERIAL(CSpriteList, CObList, 0 /* Schema number */ )

CSpriteList::CSpriteList()
{
	// Give the sprite notification object
	// a pointer to the list object.
	m_NotifyObj.SetList(this);
}

CSpriteList::~CSpriteList()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList serialization

void CSpriteList::Serialize(CArchive& ar)
{
	// Let the base class create the set of objects.
	CObList::Serialize(ar);

	// If we've just loaded, initialize each sprite.
	if (ar.IsLoading() && (m_NotifyObj.GetView()))
	{
		POSITION pos = GetHeadPosition();
		while (pos)
		{
			CSprite* pSprite = GetNext(pos); // Increment position.
			pSprite->SetNotificationObject(&m_NotifyObj);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList commands

// Add a sprite to the list, placing it according to its z-order value.
BOOL CSpriteList::Insert(CSprite* pNewSprite)
{
	// Set the notification object pointer in the sprite
	// to the sprite list's notification object.
	if (m_NotifyObj.GetView())	// has associated view
		pNewSprite->SetNotificationObject(&m_NotifyObj);

	// Walk down the list until we either get to the end
	// or we find a sprite with the same or higher z-order
	// in which case we insert just before that one.

	POSITION pos = GetHeadPosition();
	POSITION posThis;
	CSprite* pSprite;
	while (pos)
	{
		posThis = pos;
		pSprite = GetNext(pos); // Increment position.
		if (pSprite->GetZ() >= pNewSprite->GetZ())
		{
			InsertBefore(posThis, pNewSprite);
			return TRUE;
		}
	}
	// Nothing with the same or a higher z-order, so add the sprite to
	// the end.
	AddTail(pNewSprite); 
	return TRUE;
}

// Remove a sprite from the list, but do not delete it
CSprite* CSpriteList::Remove(CSprite* pSprite)
{
	POSITION pos = Find(pSprite);
	if (pos == NULL)
		return NULL;
	RemoveAt(pos);
	return pSprite;
}

// Remove everything from the list deleting all the sprites we remove
void CSpriteList::RemoveAll(const BOOL bDelete)
{
	if (bDelete)
	{
		// Walk down the list deleting objects as we go.
		// We need to do this here because the base class simply deletes the pointers.
		POSITION pos = GetHeadPosition();
		CSprite* pSprite;
		while (pos)
		{
			pSprite = GetNext(pos); // Increment position.
			if (pSprite)
			{
				ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CSprite)));
				if (pSprite->GetSrcType() != SPRITE_TILE)
					delete pSprite;
			}
		}
	}
	// Now call the base class to remove the pointers.
	CObList::RemoveAll();
}

// Move a sprite to its correct z-order position.
void CSpriteList::Reorder(CSprite* pSprite)
{
	// Remove the sprite from the list.
	if (!Remove(pSprite))
	{
		TRACE("Unable to find sprite");
		return; // Not there.
	}
	// Now insert it again in the right place.
	Insert(pSprite);
}

// Test for a mouse hit on any sprite in the list.
CSprite* CSpriteList::HitTest(const CPoint& point)
{
	// Walk the list top down.
	POSITION pos = GetHeadPosition();
	CSprite* pSprite;
	while (pos)
	{
		pSprite = GetNext(pos); // Increment position.
		if (pSprite->HitTest(point))
			return pSprite;
	}
	return NULL;
}

void CSpriteList::RemoveRedundantSprite(CSprite* pSprite)
{
	POSITION pos = GetTailPosition();
	POSITION posOld = pos;
	CSprite* pS;
	while (pos)
	{
		pS = (CSprite*)GetPrev(pos);
		if ((pS->GetZ() >= pSprite->GetZ()) &&
			(pS->GetSrcType() != SPRITE_TILE) &&
			(pS != pSprite) &&	// skip for tile or itself
			(*pS == *pSprite))
		{
			TRACE("RemoveRedundantSprite - (%d,%d)\n", pS->GetX(), pS->GetY());
			pS = (CSprite*)GetAt(posOld);
			RemoveAt(posOld);
			delete pS;
		}
		posOld = pos;
	}
}
