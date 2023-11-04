//
//	CLHTTS: Class Implementation for L&H Text-to-Text Speech
//
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __LHTTS_H
#define __LHTTS_H

#include "TTSSDK32.H"   // Include this header so all TTS routines are known.

class CLHTTS
{
public:
	CLHTTS();
	~CLHTTS();

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

	int		Create(HANDLE hThread, LPCSTR strEngine="Korean", BOOL bSpeech=TRUE);
	int		Destroy();
	int		SetFrequency(const int Freq);
	int		Speak(LPCSTR str);
	int		Stop();
//	void	SetBufSize(const int nBufSize)	{ m_nBufSize = nBufSize; }
	int		GenPcmFile(LPCSTR str, LPCSTR filename,
						const int nOutMode=M_OUT_8WAVE,
						const int nTextMode=M_ANSI_TEXT,
						const int nOutType=M_OUT_STANDARD);
//	int		GenPcmBuf(LPCSTR str,
//						const int nOutMode=M_OUT_8LINEAR,
//						const int nTextMode=M_ANSI_TEXT);
//	int		GenNextPcmBuf(LPCSTR str,
//						const int nOutMode=M_OUT_8LINEAR,
//						const int nTextMode=M_ANSI_TEXT);
	LPBYTE	GenPcmBuffer(LPCSTR str,
						const int nOutMode=M_OUT_8LINEAR,
						const int nTextMode=M_ANSI_TEXT,
						const int nBufSize=1024*11);	// Do not set nBufSize too large.
//	int		GetGenSize() const	{ return m_nGenSize; }
	HTTSINSTANCE GetHandle()	{ return m_hInst; }		// For the development period

protected:
	HTTSINSTANCE	m_hInst;
	TTSSYSTEMINFO	m_SysInfo;
	int 			m_nEngineId;
	BOOL			m_bBusy;
//	int				m_nBufSize;
//	int				m_nGenSize;
};

#endif	// __LHTTS_H