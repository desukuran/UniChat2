//
//	CBubbleListNotifyObj:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
// This is a class derived from CBubbleNotifyObj which is used in 
// CBubbleList to handle notification calls from CBubble objects.
//

#ifndef __BBLSTNO__
#define __BBLSTNO__

#include "BubbleNo.h"
class CBubbleList;
class COSBView;

class AFX_EXT_CLASS CBubbleListNotifyObj : public CBubbleNotifyObj
{
public:
	CBubbleListNotifyObj();
	~CBubbleListNotifyObj();
	void SetList(CBubbleList* pBubbleList)	{m_pBubbleList = pBubbleList;}
	void SetView(COSBView* pBufferView)		{m_pBufferView = pBufferView;}
	void Change(CBubble* pBubble, CHANGETYPE change,
				CRect* pRect1=NULL, CRect* pRect2=NULL);

protected:
	CBubbleList*	m_pBubbleList;
	COSBView*		m_pBufferView;
};
#endif // __BBLSTNO__
