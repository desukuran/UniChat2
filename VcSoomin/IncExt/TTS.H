//
//	CTTS: Class Implementation for Samsung Text-to-Text Speech
//
//	(C) Programmed by Kim, Soomin, Nov 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __TTS_H
#define __TTS_H

#include "MTalker.h"   // Include this header so all TTS routines are known.
#include <afxmt.h>

#include <dsound.h>
#include <speech.h>

#define	TTS_NUM_VOICES	2

class CTTS
{
public:
	CTTS();
	~CTTS();

	typedef struct
	{
		char	szRiff[4];
		long	lFileSize;
		char	szWave[8];
		long	lUnknown;
		short	nFormat;
		short	nChannels;
		long	lSamplesPerSec;
		long	lAvgBytesPerSec;
		short	lBlockAlign;
		short	nBits;
		char	szID3[4];
		long	lDataSize;
	} WAVEFILEHEADER;

	int		Create(LPCSTR szRoot);
	int		Destroy();
	int		Speak(LPCSTR szText, const int nGender);
	int		Stop();
	int		Pause() const	{ return Pause_TTSSystem(); }
	int		Resume() const	{ return Resume_TTSSystem(); }
	BOOL	IsBusy() const	{ return IsTTSBusy(); }
//	void	SetBufSize(const int nBufSize)	{ m_nBufSize = nBufSize; }
	int		GenWaveFile(LPCSTR szText, LPCSTR filename);
	LPBYTE	GenPcmBuffer(LPCSTR szText);	// Do not set nBufSize too large.
//	int		GetGenSize() const	{ return m_nGenSize; }
	void	SetDirectSound(LPDIRECTSOUND pDS);
	int		IsDBCS(LPCSTR szText);
	BOOL	IsMVCreateOK() const	{ return m_bCreateOK; }
	BOOL	IsMSCreateOK() const	{ return m_bMSCreateOK; }

protected:
	BOOL			BeginOLE(void);
	BOOL			EndOLE(void);
	PITTSCENTRAL	FindAndSelect(PTTSMODEINFO pTTSInfo);
	PITTSCENTRAL	FindAndSelect(PTTSMODEINFO pTTSInfo, PIAUDIODIRECT* ppIAD);

	PITTSCENTRAL	m_apITTSCentral[TTS_NUM_VOICES];
	PIAUDIODIRECT	m_apIAD[TTS_NUM_VOICES];

	LPDIRECTSOUND		m_pDSObj;
	CCriticalSection	m_cs;
	BOOL				m_bCreateOK;
	BOOL				m_bMSCreateOK;
//	int				m_nBufSize;
//	int				m_nGenSize;
};

#endif	// __TTS_H