//
//	CSpriteList :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __SPRITELST__
#define __SPRITELST__

#include "SpLstNo.h"

class AFX_EXT_CLASS CSpriteList : private CObList
{
	DECLARE_SERIAL(CSpriteList)
public:
	CSpriteList();
	virtual ~CSpriteList();
	int			GetCount() const	{ return CObList::GetCount(); }
	BOOL		Insert(CSprite* pSprite);
	void		Reorder(CSprite* pSprite);
	CSprite*	Remove(CSprite* pSprite);
	void		RemoveAll(const BOOL bDelete=TRUE);
	CSprite*	GetNext(POSITION &pos)		{ return (CSprite*)CObList::GetNext(pos); }
	CSprite*	GetPrev(POSITION &pos)		{ return (CSprite*)CObList::GetPrev(pos); }
	POSITION	GetTailPosition() const		{ return CObList::GetTailPosition(); }
	POSITION	GetHeadPosition() const		{ return CObList::GetHeadPosition(); }
	CSprite*	HitTest(const CPoint& point);
	virtual void Serialize(CArchive& ar);
	BOOL		IsEmpty()	{ return CObList::IsEmpty(); }
	void		RemoveRedundantSprite(CSprite* pSprite);

public:
	CSpriteListNotifyObj m_NotifyObj;
};
#endif // __SPRITELST__
