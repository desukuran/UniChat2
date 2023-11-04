//
//	CSound
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __SOUND__
#define __SOUND__

#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// CSound object

class AFX_EXT_CLASS CSound : public CObject
{
	DECLARE_SERIAL(CSound)
public:
	CSound();     
	virtual ~CSound();
	BOOL	Load(const char* pszFileName=NULL);
	BOOL	Load(CFile* fp);
	BOOL	Load(const WORD wResid);
	BOOL	Play();

// Implementation
protected:
	// Overridden for document i/o
	virtual void Serialize(CArchive& ar);

private:
	BYTE*	m_pSoundImage;
};

#endif // __SOUND__
