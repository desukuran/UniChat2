//	ResMan: Resource Manager
//
//==========================================================
//	(C) Programmed by Soomin Kim, Feb 1998
//	Information Technology Institute
//	Samsung SDS, Co., Seoul, South Korea
//==========================================================

#ifndef __RESMAN_H
#define __RESMAN_H

#include "Behavior.h"
///////////////////////////////////////////////////////////////////
class CDIB;
class CPhasedSprite;
class CActor;
class CTextFileBuffer;
class CSound;

enum UC2CHANNEL_TYPE
{
	ST_INVALID,
	ST_OLD,		// Old version
	ST_MUD,		// MUD mode
	ST_PUBLIC	// User Creatable
};

class CResMan : public CObject
{
public:
	CResMan();
	virtual ~CResMan();

	class CSpriteInfo
	{
	public:
		WORD		GetType();
		CString		m_strName;	// should be an internal resource ID
		CSize		m_sColRow;	// # of Columns and Rows of the Cells
		CSize		m_sEarth;	// Center of Earth (offset)
		CString		m_strHyperlink;
	};

	class CWaveData
	{
	public:
		CString		m_strName;	// resource name
		CSound*		m_pWave;
	};
// Attributes
	int			GetNumSprites()	const		{ return m_nSprites; }

	int			GetSpriteID(const CString& strName) const;
	WORD		GetSpriteType(const int nID) const
					{ return m_aSI[nID].GetType(); }
	// C++ cannot differentiate const int and const CString& ?
	WORD		GetSpriteTypeByName(const CString& strName) const;
	CString*	GetSpriteName(const int nID)
				{ return ((nID >= 0) && (nID < m_nSprites)) ? &(m_aSI[nID].m_strName) : NULL; }
	CSize		GetSpriteColRow(const int nID) const
					{ return m_aSI[nID].m_sColRow; }
	CPoint		GetSpriteEarth(const int nID) const
					{ return m_aSI[nID].m_sEarth; }
	CString*	GetSpriteHyperlink(const int nID)
					{ return &(m_aSI[nID].m_strHyperlink); }
	CString*	GetFileName()		{ return &m_strResFile; }
	CString*	GetResPath()		{ return &m_strResPath; }
	int			GetNumResFiles() const	{ return m_nResFiles; }
	int			GetNumActorDescs() const { return m_nActorDescs; }
	CActorDesc*	GetActorDesc(const WORD nCharID)
				{ return (nCharID < m_nActorDescs) ? &m_aActorDesc[nCharID] : NULL; }
	CBehavior*	GetActorBehavior(const WORD nCharID, const int bi);

	int			GetWaveID(const CString& strName) const;
	int			GetMIDIID(const CString& strName) const;
	CString*	GetMIDIName(const int nID)
				{ return (nID < m_nMIDIs) ? &m_aMIDI[nID] : NULL; }

	int			GetNumStageNames() const	{ return m_nStageNames; }
	CString*	GetStageName(const int nID)
				{ return (nID < m_nStageNames) ? &m_aStageName[nID] : NULL; }
	int			GetStageType(LPCTSTR szName) const;

	int			GetNumServerIPs() const		{ return m_nServerIPs; }
	CString*	GetServerIP(const int n)
				{ return (n < m_nServerIPs) ? &m_aServerIP[n] : NULL; }

	int			GetBubbleTextLimit() const			{ return m_nBubbleTextLimit; }
#ifdef _MALL
	int			GetDefaultBubbleTextLimit() const	{ return 255; }
#else
	int			GetDefaultBubbleTextLimit() const	{ return 100; }
#endif
	int			GetBubbleTime() const				{ return m_nBubbleTime; }
	int			GetDefaultBubbleTime() const		{ return 4000; }

// Operations
	void		DeleteResources();
	BOOL		Load(LPCSTR path="u2res000.rit");
	BOOL		SetResPath(LPCSTR path=NULL);
	void		MakeResName(CString& strName) const;	// Extract filename only
	void		ExpandResName(CString& strName, LPCSTR szExt=NULL) const;
	void		ExcludePath(CString& strName) const;
	void		IncludePath(CString& strName) const;
	BOOL		ExtractStageID(CString& strName) const;
	void		MakeStageName(CString& strName, const BOOL bPublic) const;
	BOOL		GetStageTitle(CString& strTitle) const;

	void		PrefixUDS00(CString& strName) const;

	BOOL		PlayWave(const int nID) const;
	void		SetMute(const BOOL bMute)	{ m_bMute = bMute; }

// DIB Management
	CDIB*			LoadDIB(LPCSTR szResName);
	CDIB*			LoadDIB(const WORD wResid, const BOOL bMasterPalette=FALSE);
	CPhasedSprite*	LoadPhasedSprite(LPCSTR szResName, const BOOL bDIBReuse=TRUE);
	CActor*			LoadActor(const int nCharID, const int nColorSet=0, const BOOL bME=FALSE);
	void			DeleteDIB(CDIB* pDIB);
	void			RemoveAllDIBs();
	UINT			LoadMasterPalette(CDIB* pDIB) const;
	void			ShowOutline(CDIB* pDIB) const;
	void			RotateActorColorSet(CDIB* pDIB, const int nColorSet) const;
	int				SetBubbleTextLimit(const int nBTL)	{ return m_nBubbleTextLimit = nBTL; }
	int				SetBubbleTime(const int nBT)		{ return m_nBubbleTime = nBT; }

protected:
	BOOL	LoadWave();
	int		CountHeaders(CTextFileBuffer& tfb, const char* szToken);
	void	CountItems(CTextFileBuffer& tfb);
	int		CountContents(CTextFileBuffer& tfb, const char token='=');
	BOOL	Initialize(CTextFileBuffer& tfb);

	int				m_nSprites;
	CSpriteInfo*	m_aSI;
	CObList			m_olDIB;
	CActorDesc*		m_aActorDesc;
	int				m_nActorDescs;
	CString*		m_aStageName;	// list of User-creatable stages' file name
	int				m_nStageNames;
	CString*		m_aServerIP;
	int				m_nServerIPs;
	CWaveData*		m_aWave;
	int				m_nWaves;
	CString*		m_aMIDI;
	int				m_nMIDIs;
	CString			m_strResFile;	// Resource Information: filename.ext only
	CString			m_strResPath;	// Resource Path: with trailing '\\'
	int				m_nResFiles;
	BOOL			m_bMute;		// Turn Sound Off
	int				m_nBubbleTextLimit;	// Limit to the length of the text in a bubble
	int				m_nBubbleTime;		// in millisec
};

#endif // __RESMAN_H
