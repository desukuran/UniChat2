//
//	CBubbleList :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "dib.h"
#include "bubbleno.h"
#include "bubble.h"
#include "bblstno.h"
#include "bubbllst.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBubbleList
//	Ascending order
//	[]	<- draws last
//	[]
//	[]
//	...
//	[]	<- draws first

IMPLEMENT_SERIAL(CBubbleList, CObList, 0 /* Schema number */ )

CBubbleList::CBubbleList()
{
	// Give the bubble notification object
	// a pointer to the list object.
	m_NotifyObj.SetList(this);
}

CBubbleList::~CBubbleList()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBubbleList serialization

void CBubbleList::Serialize(CArchive& ar)
{
	// Let the base class create the set of objects.
	CObList::Serialize(ar);

	// If we've just loaded, initialize each bubble.
	if (ar.IsLoading())
	{
		for (POSITION pos = GetHeadPosition(); pos != NULL;)
		{
			CBubble* pBubble = GetNext(pos); // Increment position.
			pBubble->SetNotificationObject(&m_NotifyObj);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBubbleList commands

// Add a bubble to the list, placing it according to its z-order value.
BOOL CBubbleList::Insert(CBubble* pNewBubble)
{
	// Set the notification object pointer in the bubble
	// to the bubble list's notification object.
	pNewBubble->SetNotificationObject(&m_NotifyObj);

	// Walk down the list until we either get to the end
	// or we find a bubble with the same or higher z-order
	// in which case we insert just before that one. Ascending order

	CBubble* pBubble;
	POSITION posThis;
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		posThis = pos;
		pBubble = GetNext(pos); // Increment position.
		InsertBefore(posThis, pNewBubble);
		return TRUE;
	}
	// Nothing with the same or a higher z-order, 
	// so add the bubble to the end.
	AddTail(pNewBubble); 
	return TRUE;
}

// Remove a bubble from the list, but do not delete it
CBubble* CBubbleList::Remove(CBubble* pBubble)
{
	POSITION pos = Find(pBubble);
	if (pos == NULL)
		return NULL;
	RemoveAt(pos);
	return pBubble;
}

// Remove everything from the list deleting all the bubbles we remove
void CBubbleList::RemoveAll()
{
	// Walk down the list deleting objects as we go.
	// We need to do this here because the base class simply deletes the pointers.
	CBubble* pBubble;
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		pBubble = GetNext(pos); // Increment position.
		if (pBubble)
		{
			ASSERT(pBubble->IsKindOf(RUNTIME_CLASS(CBubble)));
			delete pBubble;
		}
	}
	// Now call the base class to remove the pointers.
	CObList::RemoveAll();
}

// Move a bubble to its correct z-order position.
void CBubbleList::Reorder(CBubble* pBubble)
{
	// Remove the bubble from the list.
	if (!Remove(pBubble))
	{
		TRACE("Unable to find bubble");
		return; // Not there.
	}
	// Now insert it again in the right place.
	Insert(pBubble);
}

// Test for a mouse hit on any bubble in the list.
CBubble* CBubbleList::HitTest(const CPoint& point)
{
	// Walk the list top down.
	CBubble* pBubble;
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		pBubble = GetNext(pos); // Increment position.
		if (pBubble->HitTest(point))
			return pBubble;
	}
	return NULL;
}
