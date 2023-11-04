//
//	CWaveOutDevice
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __WAVEODEV__
#define __WAVEODEV__

#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// CWaveOutDevice object

class CWave;

class AFX_EXT_CLASS CWaveOutDevice : public CWnd
{

// Attributes
public:
	BOOL	IsOpen(); 
	BOOL	CanDoFormat(WAVEFORMATEX* pFormat);

// Operations
public:
	CWaveOutDevice();
	BOOL	Open(WAVEFORMATEX* pFormat);
	BOOL	Close();
	BOOL	Play(CWave* pWave);
	void	Stop();
	void	WaveOutDone(CWave* pWave, WAVEHDR* pHdr);

// Implementation
public:
	virtual ~CWaveOutDevice();

private:
	BOOL	Create();

	HWAVEOUT	m_hOutDev;		// Output device handle
	int			m_iBlockCount;	// Number of blocks in the queue

	// Generated message map functions
protected:
	//{{AFX_MSG(CWaveDevWnd)
	afx_msg LRESULT OnWomDone(WPARAM w, LPARAM l);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// some global items
extern CWaveOutDevice theDefaultWaveOutDevice;

/////////////////////////////////////////////////////////////////////////////
#endif // __WAVEODEV__
