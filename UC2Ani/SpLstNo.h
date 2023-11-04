//
//	CSpriteListNotifyObj;
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
// This is a class derived from CSpriteNotifyObj which is used in 
// CSpriteList to handle notification calls from CSprite objects.
//

#ifndef __SPLSTNO_H
#define __SPLSTNO_H

class CSpriteList;
class COSBView;

#include "SpriteNo.h"

class AFX_EXT_CLASS CSpriteListNotifyObj : public CSpriteNotifyObj
{
public:
	CSpriteListNotifyObj();
	~CSpriteListNotifyObj();
	void SetList(CSpriteList* pSpriteList)	{ m_pSpriteList = pSpriteList; }
	void SetView(COSBView* pBufferView)		{ m_pBufferView = pBufferView; }
	COSBView* GetView()	{ return m_pBufferView; }
	void Change(CSprite* pSprite, CHANGETYPE change,
				CRect* pRect1=NULL, CRect* pRect2=NULL);

protected:
	CSpriteList*	m_pSpriteList;
	COSBView*		m_pBufferView;
};
#endif // __SPLSTNO_H
