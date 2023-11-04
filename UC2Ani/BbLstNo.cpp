//
//	CBubbleListNotifyObj :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "dib.h"
#include "dibpal.h"
#include "bubbleno.h"
#include "bblstno.h"
#include "bubble.h"
#include "bubbllst.h"
#include "osbview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBubbleListNotifyObj

CBubbleListNotifyObj::CBubbleListNotifyObj()
{
	m_pBubbleList = NULL;
	m_pBufferView = NULL;
}

CBubbleListNotifyObj::~CBubbleListNotifyObj()
{
}

// Notification callback from a CBubble object.
void CBubbleListNotifyObj::Change(CBubble* pBubble, CHANGETYPE change,
								CRect* pRect1, CRect* pRect2)
{
	if (change & CBubbleNotifyObj::ZORDER)
	{
		// Reposition the bubble in the z-order list.
		ASSERT(m_pBubbleList);
		m_pBubbleList->Reorder(pBubble);
		// Add the bubble position to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
	}
	if (change & CBubbleNotifyObj::POSITION)
	{
		// pRect1 and pRect2 point to old and new rectangle positions;
		// add these rectangles to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
		m_pBufferView->AddDirtyRegion(pRect2);
	}
	if (change & CBubbleNotifyObj::IMAGE)
	{
		// redraw the bubble
		// Add the bubble position to the dirty list.
		ASSERT(m_pBufferView);
		m_pBufferView->AddDirtyRegion(pRect1);
	}
}
