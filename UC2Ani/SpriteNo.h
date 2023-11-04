//
//	CSpriteNotifyObj :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
// spriteno.h : header file
//
// CSpriteNotifyObj class: Nigel Thompson
//
// This is a class of pure virtual functions with no data. It is used
// by sprite objects to make notification callbacks. A user of the CSprite
// class can derive an object from CSpriteNotifyObj and pass a pointer to this
// derived class object to the sprite object for notification calls.
// Just like OLE's IClientSite interface really.
//

#ifndef __SPRITENO_H
#define __SPRITENO_H

class CSprite;

class AFX_EXT_CLASS CSpriteNotifyObj : public CObject
{
public:
	enum CHANGETYPE {
		ZORDER      = 0x0001,
		POSITION    = 0x0002,
		IMAGE       = 0x0004
	};

public:
	virtual void Change(CSprite* pSprite, CHANGETYPE change,
						CRect* pRect1=NULL, CRect* pRect2=NULL) = 0;
};
#endif // __SPRITENO_H
