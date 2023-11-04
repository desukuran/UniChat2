//
//	CMemberInfo
//
//	(C) Programmed by Kim, Soomin, Dec, 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
/////////////////////////////////////////////////////////////////////////////

#ifndef	__MEMBERINFO_H_
#define __MEMBERINFO_H_

class CMemberInfo	// : public CObject
{
public:
	CMemberInfo();
	CMemberInfo(const CMemberInfo& mi);	// Copy Constructor
	virtual ~CMemberInfo();
	CMemberInfo& operator=(const CMemberInfo& mi);

// Attributes
	const PICS_MEMBER	GetMember() const;
	const PICS_MEMBER	RefMember() const	{ return m_pMember; }	// Just reference
	void			GetMemberInfo(CString& str) const;
	int				GetVersion() const		{ return m_nVersion; }
	int				GetCharID() const		{ return m_nCharID; }
	int				GetSex() const			{ return m_nSex; }
	int				GetAge() const			{ return m_nAge; }
	int				GetBubbleKind() const	{ return m_nBubbleKind; }
	const CString*	GetNick() const			{ return &m_strNick; }
	const CString*	GetRealName() const		{ return &m_strRealName; }
	const CString*	GetProfile() const		{ return &m_strProfile; }
	const CString*	GetUserID() const		{ return &m_strUserID; }
	const CString*	GetHyperlink() const	{ return &m_strHyperlink; }
	BOOL			HasHyperlink() const	{ return (!m_strHyperlink.IsEmpty()); }
	int				GetBehavior() const		{ return m_nBehavior; }
	WORD			GetState() const		{ return m_wState; }
	CPoint			GetTileID() const		{ return m_ptTID; }

// Operations
	// For script-created actor object, set pMember=NULL, and assign a handle
	BOOL		SetMember(PICS_MEMBER pMember);
	BOOL		SetMemberInfo(const char* src);	// set member data from string
	void		SetVersion(const int nVer)	{ m_nVersion = nVer; }
	void		SetCharID(const int nID)	{ m_nCharID = nID; }
	void		SetSex(const int n)			{ m_nSex = n; }
	void		SetAge(const int n)			{ m_nAge = n; }
	void		SetBubbleKind(const int n)	{ m_nBubbleKind = n; }
	void		SetNick(LPCSTR szNick);
	void		SetRealName(LPCSTR szRN);
	void		SetProfile(LPCSTR szProf);
	void		SetUserID(LPCSTR szUID)		{ m_strUserID = szUID; }
	void		SetHyperlink(LPCSTR szHL)	{ m_strHyperlink = szHL; }
	void		SetBehavior(const int beh)	{ m_nBehavior = beh; }
	void		SetState(const WORD wS)		{ m_wState = wS; }
	void		SetSA(const WORD wSA)		{ m_wState = (wSA | (m_wState & ~AS_MASK)); }
	void		SetDA(const WORD wDA)		{ m_wState = (wDA | (m_wState & ~DA_MASK)); }
	void		SetTileID(const CPoint& pt)	{ m_ptTID = pt; }
#ifndef MAPEDITOR
	BOOL		LoadMyInfo();
	BOOL		SaveMyInfo();
#endif

protected:
	enum SEX
	{
		SEX_MAN,
		SEX_WOMAN
	};
	PICS_MEMBER	m_pMember;			// NULL for actors in script mode
	int			m_nVersion;			// Client Version of this member
	int			m_nCharID;			// Actor ID, 0,1,..., the kind of actors
	int			m_nSex;				// 0 man, 1 woman
	int			m_nAge;
	int			m_nBubbleKind;
	CString		m_strNick;			// Chat ID
	CString		m_strRealName;
	CString		m_strProfile;
	CString		m_strUserID;
	CString		m_strHyperlink;
	int			m_nBehavior;
	WORD		m_wState;			// Actor State and Direction Attribute
	CPoint		m_ptTID;			// Tile ID the actor stands on
//	int			m_nElev;
};

#endif
