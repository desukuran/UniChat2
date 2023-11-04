//
//	CMCIObject :
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//

#include "stdafx.h"
#include "mciobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCIObject

IMPLEMENT_SERIAL(CMCIObject, CObject, 0 /* schema number*/ )

CMCIObject::CMCIObject()
{
	m_OpenParams.dwCallback = 0;
	m_OpenParams.wDeviceID = 0;
	m_OpenParams.lpstrDeviceType = NULL;
	m_OpenParams.lpstrElementName = NULL;
	m_OpenParams.lpstrAlias = NULL;
}

CMCIObject::~CMCIObject()
{
	// make sure the object is not in use
	if (m_OpenParams.wDeviceID)
		Close();
	ASSERT(m_OpenParams.wDeviceID == 0);
}


/////////////////////////////////////////////////////////////////////////////
// CMCIObject serialization

void CMCIObject::Serialize(CArchive& ar)
{
	ASSERT(1); // not supported
}

/////////////////////////////////////////////////////////////////////////////
// CMCIObject commands

void CMCIObject::MCIError(DWORD dwErr)
{
	char buf[256];

	buf[0] = '\0';
	mciGetErrorString(dwErr, buf, sizeof(buf));
	if (!strlen(buf))
	    strcpy(buf, "Unknown error");
	TRACE(buf);
}

BOOL CMCIObject::Load(const char* pszFileName)
{
	DWORD dwResult;

	if (m_OpenParams.wDeviceID)
		Close();
	ASSERT(m_OpenParams.wDeviceID == 0);
	m_OpenParams.lpstrDeviceType = NULL;
	m_OpenParams.lpstrElementName = pszFileName;
	dwResult = mciSendCommand(0,
						MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT,
						(DWORD)(LPVOID)&m_OpenParams);
	if (dwResult)
	{
		MCIError(dwResult);
		m_OpenParams.wDeviceID = 0;
		return FALSE;
	}

	// Set the time format to milliseconds
	MCI_SET_PARMS set;
	set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	dwResult = mciSendCommand(m_OpenParams.wDeviceID,
						MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT,
						(DWORD)(LPVOID)&set);
	if (dwResult)
	{
		MCIError(dwResult);
		m_OpenParams.wDeviceID = 0;
		return FALSE;
	}

	CString strName(pszFileName);
	strName.MakeLower();
	int i = strName.ReverseFind('.');
	if (strName[i+1] != 'm')	// only for wave
	{
		// Cue the file so it will play with no delay
		dwResult = mciSendCommand(m_OpenParams.wDeviceID,
							MCI_CUE, MCI_WAIT,
							(DWORD)(LPVOID)NULL);
		if (dwResult)
		{
			MCIError(dwResult);
			m_OpenParams.wDeviceID = 0;
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CMCIObject::OpenDevice(const char* pszDevName)
{
	DWORD dwResult;

	if (m_OpenParams.wDeviceID)
		Close();
	ASSERT(m_OpenParams.wDeviceID == 0);
	m_OpenParams.lpstrDeviceType = pszDevName;
	dwResult = mciSendCommand(0,
					MCI_OPEN, MCI_WAIT | MCI_OPEN_SHAREABLE | MCI_OPEN_TYPE,
					(DWORD)(LPVOID)&m_OpenParams);
	if (dwResult)
	{
		MCIError(dwResult);
		m_OpenParams.wDeviceID = 0;
		return FALSE;
	}

	// Set the time format to milliseconds
	MCI_SET_PARMS set;
	set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	dwResult = mciSendCommand(m_OpenParams.wDeviceID,
						MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT,
						(DWORD)(LPVOID)&set);
	if (dwResult)
	{
		MCIError(dwResult);
		m_OpenParams.wDeviceID = 0;
		return FALSE;
	}
	return TRUE;
}

void CMCIObject::Close()
{
	MCI_GENERIC_PARMS	gp;
	DWORD	dwResult;

	if (m_OpenParams.wDeviceID == 0)
		return; // already closed
	Stop(); // just in case
	dwResult = mciSendCommand(m_OpenParams.wDeviceID,
						MCI_CLOSE, MCI_WAIT,
						(DWORD)(LPVOID)&gp);
	if (dwResult)
		MCIError(dwResult);
	m_OpenParams.wDeviceID = 0;
}

BOOL CMCIObject::Play()
{
	MCI_PLAY_PARMS	play;
	DWORD	dwResult;

	if (m_OpenParams.wDeviceID == 0)
		return FALSE; // not open

	mciSendCommand(m_OpenParams.wDeviceID,
				MCI_SEEK, MCI_WAIT | MCI_SEEK_TO_START,
				0);
	dwResult = mciSendCommand(m_OpenParams.wDeviceID,
						MCI_PLAY, NULL,
						(DWORD)(LPVOID)&play);
	if (dwResult)
	{
		MCIError(dwResult);
		return FALSE;
	}
	return TRUE;
}

void CMCIObject::Stop()
{
	DWORD dwResult;

	if (m_OpenParams.wDeviceID == 0)
		return; // not open

	dwResult = mciSendCommand(m_OpenParams.wDeviceID,
						MCI_STOP, MCI_WAIT,
						(DWORD)(LPVOID)NULL);
	if (dwResult)
		MCIError(dwResult);
}

DWORD CMCIObject::GetPosition()
{
	if (m_OpenParams.wDeviceID == 0)
		return 0; // not open

	MCI_STATUS_PARMS status;
	status.dwItem = MCI_STATUS_POSITION;
	if (mciSendCommand(m_OpenParams.wDeviceID,
					MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM,
					(DWORD)(LPVOID)&status) != 0)
	{
		return 0; // some error
	}
	return status.dwReturn;
}
