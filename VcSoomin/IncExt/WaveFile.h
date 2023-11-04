//
//	CWaveFile:
//
//	Original Source by Mark McCulley, Microsoft Corporation
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __WAVEFILE_H
#define __WAVEFILE_H


// Constants
#ifndef SUCCESS
#define SUCCESS TRUE		// Error returns for all member functions
#define FAILURE FALSE
#endif // SUCCESS


// CWaveFile
// WAV file class(read-only).
//

class CWaveFile
{
public:
	CWaveFile(void);
	~CWaveFile(void);
	BOOL	Open(LPCSTR pszFilename);
	BOOL	Cue(void);
	UINT	Read(BYTE* pbDest, UINT cbSize);
	UINT	GetNumBytesRemaining(void)	{ return (m_nDataSize - m_nBytesPlayed); }
	UINT	GetAvgDataRate(void)		{ return (m_nAvgDataRate); }
	UINT	GetDataSize(void)			{ return (m_nDataSize); }
	UINT	GetNumBytesPlayed(void)		{ return (m_nBytesPlayed); }
	UINT	GetDuration(void)			{ return (m_nDuration); }
	BYTE	GetSilenceData(void);
	WAVEFORMATEX*	m_pwfmt;
protected:
	HMMIO		m_hmmio;
	MMRESULT	m_mmr;
	MMCKINFO	m_mmckiRiff;
	MMCKINFO	m_mmckiFmt;
	MMCKINFO	m_mmckiData;
	UINT		m_nDuration;		// duration of sound in msec
	UINT		m_nBlockAlign; 		// wave data block alignment spec
	UINT		m_nAvgDataRate;		// average wave data rate
	UINT		m_nDataSize;		// size of data chunk
	UINT		m_nBytesPlayed;		// offset into data chunk
};

#endif // __WAVEFILE_H
