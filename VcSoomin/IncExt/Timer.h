//
//	CTimer: Windows multimedia timer services
//
//	Original Source by Mark McCulley, Microsoft Corporation
//	(C) Programmed by Kim, Soomin, Sep 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//

#ifndef __TIMER_H
#define __TIMER_H


typedef BOOL(*TIMERCALLBACK)(DWORD);

// CTimer
//
// Wrapper class for Windows multimedia timer services.
// Provides both periodic and one-shot events.
// User must supply callback for periodic events.

class CTimer
{
public:
	CTimer();
	~CTimer();
	BOOL	Create(UINT nPeriod, UINT nRes, DWORD dwUser,  TIMERCALLBACK pfnCallback);
protected:
	static void CALLBACK TimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	TIMERCALLBACK	m_pfnCallback;
	DWORD	m_dwUser;
	UINT	m_nPeriod;
	UINT	m_nRes;
	UINT	m_nIDTimer;
};

#endif // __TIMER_H
