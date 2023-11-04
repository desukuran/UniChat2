//
//	CDirectSound: Class for IDIRECTSOUND* interfaces
//
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __CDIRECTSOUND_H
#define __CDIRECTSOUND_H

#include <mmsystem.h>
#include "dsound.h"

class CDirectSound : public CObject
{
public:
	CDirectSound();
	virtual ~CDirectSound();
	DECLARE_DYNCREATE(CDirectSound)

	LPDIRECTSOUND	GetPDS() const	{ return m_pDSObj; }
	BOOL	Create(const CWnd* pWnd);
	BOOL	Destroy();

protected:
	LPDIRECTSOUND		m_pDSObj;		// DirectSound Object
};

class CDirectSoundBuffer : public CObject
{
public:
	CDirectSoundBuffer();
	virtual ~CDirectSoundBuffer();
	DECLARE_DYNCREATE(CDirectSoundBuffer)

	LPDIRECTSOUNDBUFFER	GetPDSB() const	{ return m_pDSB; }

	BOOL	Create(CDirectSound* pds, LPCSTR pszFilename);
	BOOL	CreateMem(CDirectSound* pds, LPBYTE pbWaveData);
	BOOL	Destroy();
	BOOL	Play(const BOOL bLoop=FALSE);
	void	SetLoop(const BOOL bLoop=TRUE)	{ m_bLoop = bLoop; }
	BOOL	Stop();
	HRESULT SetPan(LONG lPan) const
			{
				if (m_pDSB)
					return m_pDSB->SetPan(lPan);
				return 0;
			}
	HRESULT	SetVolume(LONG lVolume) const
			{
				if (m_pDSB)
					return m_pDSB->SetVolume(lVolume);
				return 0;
			}
	HRESULT	SetFrequency(LONG lFreq) const
			{
				if (m_pDSB)
					return m_pDSB->SetFrequency(lFreq);
				return 0;
			}
protected:
	CDirectSound*			m_pDS;			// ptr to AudioStreamServices object
	LPDIRECTSOUNDBUFFER		m_pDSB;			// sound buffer
//	DSBUFFERDESC			m_DSBD;			// sound buffer description
	CString					m_str;			// filename or resource name
	BOOL					m_bLoop;
};

#endif
