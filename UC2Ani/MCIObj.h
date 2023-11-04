//
//	CMCIObj
//
//	(C) Programmed by Kim, Soomin, 1995-96
//	SDS Media Lab
//	Information Technology Institute
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __MCIOBJ__
#define __MCIOBJ__

#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// CMCIObject object

class AFX_EXT_CLASS CMCIObject : public CObject
{
	DECLARE_SERIAL(CMCIObject)
public:
	CMCIObject();     
	~CMCIObject();
	BOOL	Load(const char* pszFileName);
	BOOL	OpenDevice(const char* pszDevName);
	void	Close();
	BOOL	Play();
	void	Stop();
	DWORD	GetPosition();

// Implementation
protected:
	virtual void Serialize(CArchive& ar);   // Overridden for document i/o

private:
	void MCIError(DWORD dwErr);

	MCI_OPEN_PARMS m_OpenParams; 
};

#endif // __MCIOBJ__
