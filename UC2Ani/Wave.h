//
//	CWave
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __WAVE__
#define __WAVE__

#include "waveodev.h"

/////////////////////////////////////////////////////////////////////////////
// CWave object

class AFX_EXT_CLASS CWave : public CObject
{
	DECLARE_SERIAL(CWave)
public:
	CWave();     
	~CWave();
	BOOL	Create(const int nsamples, const int samprate=11025, const int sampsize=8);
	BOOL	Play(CWaveOutDevice* pWaveOutDevice = NULL);
	void	Stop();
	BOOL	Load(const char* pszFileName=NULL);
	BOOL	Load(CFile* fp);  
	BOOL	Load(const UINT hFile);
	BOOL	Load(const HMMIO hmmio);
	BOOL	LoadResource(const WORD wID);

// Attributes
public:
	WAVEFORMATEX*	GetFormat()		{ return (WAVEFORMATEX*)&m_pcmfmt; }
	CWaveOutDevice*	GetOutDevice()	{ return m_pOutDev; }
	int		GetSize() const			{ return m_iSize; }
	int		GetNumSamples() const;
	int		GetSample(const int index) const;
	virtual void	OnWaveOutDone();
	virtual void	OnWaveInData();
	void			SetSample(const int index, const int iValue);

// Implementation
public:
	void* GetSamples()			{ return m_pSamples; }
	BOOL IsBusy() const			{ return m_bBusy; }
	void SetBusy(const BOOL b)	{ m_bBusy = b; }

protected:
	virtual void Serialize(CArchive& ar);	// Overridden for document I/O

private:
	WAVEFORMATEX	m_pcmfmt;	// PCM wave format header; PCMWAVEFORMAT-->WAVEFORMATEX
	void*			m_pSamples;	// Pointer to the samples
	int				m_iSize;	// Size in bytes
	CWaveOutDevice*	m_pOutDev;	// Output device
	BOOL			m_bBusy;	// Set to TRUE if playing or recording
};

#endif // __WAVE__
