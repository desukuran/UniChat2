//
//	CBubbleNotifyObj:
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
// ================= Nigel Thompson
// This is a class of pure virtual functions with no data.
// It is used by bubble objects to make notification callbacks.
// A user of the CBubble class can derive an object from CBubbleNotifyObj
// and pass a pointer to this derived class object to the bubble object for notification calls.
// Just like OLE's IClientSite interface really.
//

#ifndef __BUBBLENO_H
#define __BUBBLENO_H

class CBubble;

class AFX_EXT_CLASS CBubbleNotifyObj : public CObject
{
public:
	enum CHANGETYPE
	{
		ZORDER      = 0x0001,
		POSITION    = 0x0002,
		IMAGE       = 0x0004
	};

public:
	virtual void Change(CBubble* pBubble, CHANGETYPE change,
						CRect* pRect1=NULL, CRect* pRect2=NULL) = 0;
};
#endif // __BUBBLENO_H
