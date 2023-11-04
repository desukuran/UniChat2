// UDSGenDoc.h : interface of the CUDSGenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDSGENDOC_H__C3C37D0B_AD07_11D1_9169_0000F0610C92__INCLUDED_)
#define AFX_UDSGENDOC_H__C3C37D0B_AD07_11D1_9169_0000F0610C92__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef struct tagDATASOURCEHEADER
{
	WORD	wType;			// 'DS' for Data Source.
	DWORD	dwFileSize;     // Total file size.
	WORD	wNumEntries;	// Number of entries
	WORD	bcReserved1; 
	WORD	bcReserved2;
} DATASOURCEHEADER;

typedef struct tagDATASOURCEENTRY
{
	char	id[13];		// org filename (with extension) + NULL // 13 bytes. 
	DWORD	dwOffset;	// offset to the BITMAPFILEHEADER // 4 bytes.
} DATASOURCEENTRY, FAR *LPDATASOURCEENTRY; // total 17 bytes.

class CUDSGenView;

class CUDSGenDoc : public CDocument
{
protected: // create from serialization only
	CUDSGenDoc();
	DECLARE_DYNCREATE(CUDSGenDoc)

// Attributes
public:
	DATASOURCEHEADER* GetHeader() { return &m_dsHeader;}
	LPDATASOURCEENTRY GetEntry() { return m_aDSEntry;}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDSGenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GenerateNoPal(CString fileName);
	BOOL Generate(CString fileName);
	virtual ~CUDSGenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL SaveHeaderNoPal(CFile* fp);
	DWORD GetFileSizeNoPal();
	DWORD* m_pFilePointers;
	DWORD m_dwEntryStartPoint;
	BOOL SaveWithCDIB(CFile* fp, int index);
	void GenerateDSI(CString fileName);
	BOOL SaveContentNoPal(CFile* fp, int index);
	BOOL SaveContent(CFile* fp, int index);
	BOOL SaveEntry(CFile* fp, int index);
	BOOL SaveEntryNoPal(CFile* fp, int index);
	DWORD GetFileSize();
	BOOL SaveHeader(CFile* fp);
	//DWORD m_targetSize;
	CUDSGenView* GetView();
	LPDATASOURCEENTRY	m_aDSEntry;
	int					m_nDSEntries;
	DATASOURCEHEADER	m_dsHeader;
	//{{AFX_MSG(CUDSGenDoc)
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDSGENDOC_H__C3C37D0B_AD07_11D1_9169_0000F0610C92__INCLUDED_)
