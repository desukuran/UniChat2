//	CDirectSoundStream: 
//
//	Original Source by Mark McCulley, Microsoft Corporation
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __DSSTREAM_H
#define __DSSTREAM_H

#include <dsound.h>
#include "timer.h"
#include "wavefile.h"

class CDirectSound;

// Constants
#ifndef SUCCESS
#define SUCCESS TRUE        // Error returns for all member functions
#define FAILURE FALSE
#endif // SUCCESS

// CDirectSoundStream
//
// Audio stream interface class for playing WAV files using DirectSound.
// Users of this class must create DirectSound object before
// creating a CDirectSoundStream object.
//

class CDirectSoundStream
{
public:
	CDirectSoundStream();
	~CDirectSoundStream();
	BOOL	Create(CDirectSound* pds, LPCSTR pszFilename);
	BOOL	Destroy();
	void	Play(const BOOL bLoop=FALSE);
	void	Stop();
	void	SetLoop(const BOOL bLoop=TRUE) { m_bLoop = bLoop; }
	HRESULT	SetPan(LONG lPan) const			{ return m_pdsb->SetPan(lPan); }
	HRESULT	SetVolume(LONG lVolume) const	{ return m_pdsb->SetVolume(lVolume); }
	HRESULT	SetFrequency(LONG lFreq) const	{ return m_pdsb->SetFrequency(lFreq); }
protected:
	void	Cue();
	BOOL	WriteWaveData(UINT cbSize);
	BOOL	WriteSilence(UINT cbSize);
	DWORD	GetMaxWriteSize();
	BOOL	ServiceBuffer();
	static BOOL TimerCallback(DWORD dwUser);
	CDirectSound*			m_pds;				// ptr to DirectSound object
	LPDIRECTSOUNDBUFFER		m_pdsb;				// sound buffer
	CWaveFile*				m_pwavefile;		// ptr to WaveFile object
	CTimer*					m_ptimer;			// ptr to Timer object
	BOOL					m_fCued;			// semaphore(stream cued)
	BOOL					m_fPlaying;			// semaphore(stream playing)
	BOOL					m_bLoop;			// Play Loop?
	DSBUFFERDESC			m_dsbd;				// sound buffer description
	LONG					m_lInService;		// reentrancy semaphore
	UINT					m_cbBufOffset;		// last write position
	UINT					m_nBufLength;		// length of sound buffer in msec
	UINT					m_cbBufSize;		// size of sound buffer in bytes
	UINT					m_nBufService;		// service interval in msec
	UINT					m_nDuration;		// duration of wave file
	UINT					m_nTimeStarted;		// time(in system time) playback started
	UINT					m_nTimeElapsed;		// elapsed time in msec since playback started
	static const UINT DefBufferLength;			// default buffer length in msec
	static const UINT DefBufferServiceInterval;	// default buffer service interval in msec
};

#endif // __DSSTREAM_H