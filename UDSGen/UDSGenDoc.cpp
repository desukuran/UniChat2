// UDSGenDoc.cpp : implementation of the CUDSGenDoc class
//

#include "stdafx.h"
#include "UDSGen.h"

#include "UDSGenDoc.h"
#include "UDSGenView.h"

#include "dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDSGenDoc

IMPLEMENT_DYNCREATE(CUDSGenDoc, CDocument)

BEGIN_MESSAGE_MAP(CUDSGenDoc, CDocument)
	//{{AFX_MSG_MAP(CUDSGenDoc)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDSGenDoc construction/destruction

CUDSGenDoc::CUDSGenDoc()
{
	// TODO: add one-time construction code here
	
	m_dsHeader.wType = 0x5344;
	m_dsHeader.dwFileSize = 0;
	m_dsHeader.wNumEntries = 0;
	m_dsHeader.bcReserved1 = 0; 
	m_dsHeader.bcReserved2 = 0;

	m_aDSEntry = NULL;

	//m_targetSize = 0; // Target file size.

	m_pFilePointers = NULL;
}

CUDSGenDoc::~CUDSGenDoc()
{
	if(m_aDSEntry)
		delete m_aDSEntry;

	if(m_pFilePointers)
		delete m_pFilePointers;
}

BOOL CUDSGenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUDSGenDoc serialization

void CUDSGenDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUDSGenDoc diagnostics

#ifdef _DEBUG
void CUDSGenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUDSGenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUDSGenDoc commands

CUDSGenView* CUDSGenDoc::GetView()
{
	POSITION pos;
    pos = GetFirstViewPosition();
    ASSERT(pos);
    CUDSGenView* pView = (CUDSGenView*)GetNextView(pos);
    ASSERT(pView);
    ASSERT(pView->IsKindOf(RUNTIME_CLASS(CUDSGenView)));
    return pView;
}

void CUDSGenDoc::OnFileNew() 
{
	// TODO: Add your command handler code here
	GetView()->m_lstSource.ResetContent();
	
	CFileDialog ofd(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT ,
		"Bitmap files|*.DIB;*.BMP;*.BM;*.gif;*.jpg;*.tif|All files (*.*)|*.*||");
	
	CString buffer;
	
	ofd.m_ofn.lpstrFile = (LPSTR)buffer.GetBuffer(4090);
	ofd.m_ofn.nMaxFile = 4090*2;
	if(ofd.DoModal() == IDOK)
	{
		POSITION pos = ofd.GetStartPosition();
		while(pos)
		{
			CString file = ofd.GetNextPathName(pos);
			GetView()->m_lstSource.AddString(file);
		}

		m_nDSEntries = GetView()->m_lstSource.GetCount();
		m_dsHeader.wNumEntries = m_nDSEntries; // How many Files?
		m_aDSEntry = new DATASOURCEENTRY[m_nDSEntries];
		m_pFilePointers = new DWORD[m_nDSEntries];
	}
	
}

BOOL CUDSGenDoc::Generate(CString fileName)
{
	TRACE("CUDSGenDoc::Generate\n");

	GetView()->SetFilename(fileName);

	CFile target;
	CFileException fileException;
	if ( !target.Open(fileName, CFile::modeCreate | CFile::modeWrite, &fileException))
	{
		TRACE( "Can't open file %s, error = %u\n", fileName, fileException.m_cause );
	}
		
	//target.SetLength(fileLength); // total target file size set.

	//example for CFile::Seek
	target.SeekToBegin(); // Move file pointer to beginning point.
	
	if(!SaveHeader(&target))
	{
		AfxMessageBox("Write header error");
	}

	m_dwEntryStartPoint = target.GetPosition();
	
	int offset = (sizeof(DATASOURCEENTRY))*m_nDSEntries;
	target.Seek(offset, CFile::current);

	for(int j=0 ; j<m_nDSEntries; j++)
	{
		//SaveWithCDIB(&target, j); // no palette.
		SaveContent(&target, j); // Rawdata to files.
	}
		
	int offsetentry = sizeof(DATASOURCEHEADER);
	target.Seek(offsetentry, CFile::begin);

	for(int i=0 ; i<m_nDSEntries; i++)
	{
		SaveEntry(&target, i);
		//SaveEntryBMP(&target, i);
	}

	GenerateDSI(fileName); // data source inforamtion file.
	return TRUE;
}

BOOL CUDSGenDoc::SaveHeader(CFile * fp)
{
	TRACE("CUDSGenDoc::SaveHeader\n");

	DATASOURCEHEADER dsh;
	
	// Construct the file header.
	dsh.wType = 0x5344; // 'DS'
	dsh.dwFileSize = GetFileSize();
	dsh.wNumEntries = m_nDSEntries;
	dsh.bcReserved1 = 0;
	dsh.bcReserved2 = 0;
	
	// Write the file header.
	WORD iSize = sizeof(dsh);
	TRY
	{
		fp->Write(&dsh, iSize);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write file header");
		return FALSE;
	} END_CATCH

	return TRUE;
}

DWORD CUDSGenDoc::GetFileSize()
{
	TRACE("CUDSGenDoc::GetFileSize\n");

	DWORD fileLength;
	fileLength = 0;
	for(int i=0; i<m_nDSEntries; i++)
	{
		CString tmpfile;
		GetView()->m_lstSource.GetText(i, tmpfile);
		CFile temp(tmpfile, CFile::modeRead);
		fileLength += temp.GetLength(); // size of all file selected.
		temp.Close();
	}
	
	fileLength += sizeof(DATASOURCEHEADER);
	fileLength += m_nDSEntries * sizeof(DATASOURCEENTRY);
	
	return fileLength;
}

BOOL CUDSGenDoc::SaveEntry(CFile * fp, int index)
{
	TRACE("CUDSGenDoc::SaveEntry\n");

	DATASOURCEENTRY dse;
	DWORD fpos = 0; 
	CString tmpfile;
	GetView()->m_lstSource.GetText(index, tmpfile);
	
	CFile temp(tmpfile, CFile::modeRead);
	// Construct the file header.
	CString strFN(temp.GetFileName());
	//strFN += ".bmp"; // What kind of file?
	strFN.MakeLower();

	//ASSERT(strFN.GetLength() <= 12);
	::ZeroMemory(&dse, sizeof(dse));

	lstrcpy(dse.id, strFN);

	/*
	for(int i=0; i<index; i++)
	{
		CString tmpfile;
		GetView()->m_lstSource.GetText(i, tmpfile);
		CFile temp(tmpfile, CFile::modeRead);
		fpos += temp.GetLength(); // size of all file selected.
		temp.Close();
	}
	
	DWORD off = sizeof(DATASOURCEHEADER) + 
		sizeof(DATASOURCEENTRY)*m_nDSEntries + fpos;
	*/
	dse.dwOffset = m_pFilePointers[index];
	
	// Write the file header.
	int iSize = sizeof(DATASOURCEENTRY);
	TRACE("sizeof(dse)=%d\n", iSize);
	TRY
	{
		fp->Write(&dse, iSize);
		return TRUE;
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write file header");
		return FALSE;
	} END_CATCH

}

BOOL CUDSGenDoc::SaveEntryNoPal(CFile * fp, int index)
{
	TRACE("CUDSGenDoc::SaveEntry\n");

	DATASOURCEENTRY dse;
	DWORD fpos = 0; 
	CString tmpfile;
	GetView()->m_lstSource.GetText(index, tmpfile);
	
	CFile temp(tmpfile, CFile::modeRead);
	// Construct the file header.
	CString strFN(temp.GetFileName());
	//strFN += ".bmp"; // What kind of file?
	strFN.MakeLower();

	//ASSERT(strFN.GetLength() <= 12);
	::ZeroMemory(&dse, sizeof(dse));

	lstrcpy(dse.id, strFN);

	/*
	for(int i=0; i<index; i++)
	{
		CString tmpfile;
		GetView()->m_lstSource.GetText(i, tmpfile);
		CFile temp(tmpfile, CFile::modeRead);
		fpos += temp.GetLength(); // size of all file selected.
		temp.Close();
	}
	
	DWORD off = sizeof(DATASOURCEHEADER) + 
		sizeof(DATASOURCEENTRY)*m_nDSEntries + fpos;
	*/
	dse.dwOffset = m_pFilePointers[index];
	
	// Write the file header.
	int iSize = sizeof(DATASOURCEENTRY);
	TRACE("sizeof(dse)=%d\n", iSize);
	TRY
	{
		fp->Write(&dse, iSize);
		return TRUE;
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write file header");
		return FALSE;
	} END_CATCH


}

BOOL CUDSGenDoc::SaveContent(CFile * fp, int index)
{
	TRACE("CUDSGenDoc::SaveContent\n");
	// Any kind of files to UDS. just binding.

	m_pFilePointers[index] = fp->GetPosition();

	CString tmpfile;
	GetView()->m_lstSource.GetText(index, tmpfile);
	
	CFile temp(tmpfile, CFile::modeRead);
	int nSize = temp.GetLength();
	BYTE* buffer = (BYTE*)malloc(nSize);
	temp.Read(buffer, nSize);

	fp->Write(buffer, nSize);

	free(buffer);
	return TRUE;
}

void CUDSGenDoc::GenerateDSI(CString fileName)
{
	int l = fileName.GetLength();
	CString dsi = fileName.Left(l-4);
	dsi += ".dsi";
	CFile fnDSI;
	CFileException fileException;
	if ( !fnDSI.Open(dsi, CFile::modeCreate | CFile::modeWrite, &fileException))
	{
		TRACE( "Can't open file %s, error = %u\n", fileName, fileException.m_cause );
	}
	for(int i=0; i<m_nDSEntries; i++)
	{
		//char line[13];
		CString tmpfile;
		GetView()->m_lstSource.GetText(i, tmpfile);
		CFile temp(tmpfile, CFile::modeRead);
		
		CString strFN(temp.GetFileName());
		strFN.MakeLower();
		//lstrcpy(dse.id, strFN);
		strFN += "\r\n";
		fnDSI.Write(strFN, strFN.GetLength());
		temp.Close();
	}
}

void CUDSGenDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	//GetView()->m_lstSource.ResetContent();
	
	CFileDialog ofd(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"DSI files|*.dsi|*.*||");
	if(ofd.DoModal() == IDOK)
	{
		CStdioFile dsiFile(ofd.GetFileName(), CFile::modeRead);
		CString strTemp;
		while(dsiFile.ReadString(strTemp))
		{
			GetView()->m_lstSource.AddString(strTemp);
		}
	}

}

BOOL CUDSGenDoc::SaveContentNoPal(CFile * fp, int index)
{
	TRACE("CUDSGenDoc::SaveContentNoPal\n");

	m_pFilePointers[index] = fp->GetPosition();

	CString tmpfile;
	GetView()->m_lstSource.GetText(index, tmpfile);
	
	CDIB* dib = new CDIB;
	dib->Load(tmpfile);

	dib->Save(fp, FALSE); // no palette.

	delete dib;

	
	return TRUE;
	
}

BOOL CUDSGenDoc::SaveWithCDIB(CFile * fp, int index)
{
	TRACE("CUDSGenDoc::SaveWithCDIB\n");

	m_pFilePointers[index] = fp->GetPosition();

	CString tmpfile;
	GetView()->m_lstSource.GetText(index, tmpfile);
	
	CDIB* dib = new CDIB;
	dib->Load(tmpfile);

	dib->Save(fp, FALSE); // no palette.

	delete dib;

	
	return TRUE;
}

DWORD CUDSGenDoc::GetFileSizeNoPal()
{
	TRACE("CUDSGenDoc::GetFileSize\n");

	DWORD fileLength;
	fileLength = 0;
	for(int i=0; i<m_nDSEntries; i++)
	{
		CString tmpfile;
		GetView()->m_lstSource.GetText(i, tmpfile);
		CFile temp(tmpfile, CFile::modeRead);
		fileLength += temp.GetLength(); // size of all file selected.
		temp.Close();
	}
	
	fileLength += sizeof(DATASOURCEHEADER);
	fileLength += m_nDSEntries * sizeof(DATASOURCEENTRY);
	fileLength -= m_nDSEntries * (sizeof(RGBQUAD)*255);

	return fileLength;

}

BOOL CUDSGenDoc::SaveHeaderNoPal(CFile * fp)
{
	TRACE("CUDSGenDoc::SaveHeader\n");

	DATASOURCEHEADER dsh;
	
	// Construct the file header.
	dsh.wType = 0x5344; // 'DS'
	dsh.dwFileSize = GetFileSizeNoPal();
	dsh.wNumEntries = m_nDSEntries;
	dsh.bcReserved1 = 0;
	dsh.bcReserved2 = 0;
	
	// Write the file header.
	WORD iSize = sizeof(dsh);
	TRY
	{
		fp->Write(&dsh, iSize);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed to write file header");
		return FALSE;
	} END_CATCH

	return TRUE;

}

BOOL CUDSGenDoc::GenerateNoPal(CString fileName)
{
	TRACE("CUDSGenDoc::GenerateNoPal\n");

	GetView()->SetFilename(fileName);

	CFile target;
	CFileException fileException;
	if ( !target.Open(fileName, CFile::modeCreate | CFile::modeWrite, &fileException))
	{
		TRACE( "Can't open file %s, error = %u\n", fileName, fileException.m_cause );
	}
		
	//target.SetLength(fileLength); // total target file size set.

	//example for CFile::Seek
	target.SeekToBegin(); // Move file pointer to beginning point.
	
	if(!SaveHeaderNoPal(&target))
	{
		AfxMessageBox("Write header error");
	}

	m_dwEntryStartPoint = target.GetPosition();
	
	int offset = (sizeof(DATASOURCEENTRY))*m_nDSEntries;
	target.Seek(offset, CFile::current);

	for(int j=0 ; j<m_nDSEntries; j++)
	{
		SaveContentNoPal(&target, j);
	}
		
	int offsetentry = sizeof(DATASOURCEHEADER);
	target.Seek(offsetentry, CFile::begin);

	for(int i=0 ; i<m_nDSEntries; i++)
	{
		SaveEntryNoPal(&target, i);
		//SaveEntryBMP(&target, i);
	}

	GenerateDSI(fileName); // data source inforamtion file.
	return TRUE;

}
