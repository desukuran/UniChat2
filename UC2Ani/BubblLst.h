//
//	CBubbleList:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __BUBBLELST__
#define __BUBBLELST__

#include "BbLstNo.h"

class CBubble;

class AFX_EXT_CLASS CBubbleList : private CObList
{
	DECLARE_SERIAL(CBubbleList)
public:
	CBubbleList();
	~CBubbleList();
	BOOL		Insert(CBubble* pBubble);
	void		Reorder(CBubble* pBubble);
	CBubble*	Remove(CBubble* pBubble);
	void		RemoveAll();
	CBubble*	GetNext(POSITION &pos)	{ return (CBubble*) CObList::GetNext(pos); }
	CBubble*	GetPrev(POSITION &pos)	{ return (CBubble*) CObList::GetPrev(pos); }
	POSITION	GetTailPosition() const	{ return CObList::GetTailPosition(); }
	POSITION	GetHeadPosition() const	{ return CObList::GetHeadPosition(); }
	CBubble*	HitTest(const CPoint& point);
	BOOL		IsEmpty()	{ return CObList::IsEmpty(); }
	virtual	void	Serialize(CArchive& ar);

public:
	CBubbleListNotifyObj m_NotifyObj;
};
#endif // __SPRITELST__
