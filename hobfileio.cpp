#include "StdAfx.h"
#include "hobfileio.h"


CHDXHOBFileReader::CHDXHOBFileReader()
{
	return;
}

LPDIRECT3DRMFRAME3 CHDXHOBFileReader::ReadHOBFile( CString fileName, LPDIRECT3DRMFRAME3 f)
{
	HANDLE hFile = CreateFile(fileName.GetBuffer(),
		GENERIC_READ, FILE_SHARE_READ,
		NULL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("Couldn't create the file!"));
	}
	else
	{
		char* lpbuff = {};
		CFile file(hFile);
		file.Read(lpbuff, (UINT)file.GetLength());
		hobFilePlaceTracker = 0;
		char* header = GetHeader(lpbuff);

		char* m_fileType = GetXFileType(header);


		if (strstr(m_fileType, "bin"))
		{
			LPDIRECT3DRMFRAME3 fr = NULL;
			//ReadXBinaryHDXMesh(  info, fstrm, fr );
			//CHDXANIMATIONARRAY* anims = new CHDXANIMATIONARRAY();
			//anims->allocate(0);
			//ReadHOBAnimations( fstrm, info, anims );
			return fr;
		}//eoif bin
		return NULL;
	}
	return NULL;
}

char * CHDXHOBFileReader::GetHeader(char * fs)
{
	static char header[17];
	for(int i =0;i<16;i++)
	{
		//fs.get(header[i]);
		hobFilePlaceTracker++;
	}
	header[16]='\0';

	GetFloatBits1(header);
	GetXFileType(header);
	GetVersion2(header);
	GetVersion1(header);
	GetMagic(header);
	
	return header;
}

char * CHDXHOBFileReader::GetMagic(char *  pch)
{
	static char t[4];
	for(int i=0;i<3;i++)
	{
		t[i]=pch[i];
	}
	t[3]='\0';

	return t;
}

char *  CHDXHOBFileReader::GetVersion1(char *  pch)
{
	static char t[3];
	for(int i=4;i<6;i++)
	{
		t[i-4]=pch[i];
	}
	t[2]='\0';
	return t;
}

char *  CHDXHOBFileReader::GetVersion2(char *  pch)
{
	static char t[3];
	for(int i=6;i<8;i++)
	{
		t[i-6]=pch[i];
	}
	t[2]='\0';

	return t;
}

char * CHDXHOBFileReader::GetXFileType(char *  pch)
{
	static char t[4];
	for(int i=8;i<11;i++)
	{
		t[i-8]=pch[i];
	}
	t[3]='\0';

	return t;
}

char * CHDXHOBFileReader::GetFloatBits1(char *  pch)
{
	static char t[3];
	for(int i=14;i<16;i++)
	{
		t[i-14]=pch[i];
	}
	t[2]='\0';

	return t;
}
/////////////////////////////////////////////////////////////////////
//// CHDXHOBFileWriter
/////////////////////////////////////////////////////////////////////
CHDXHOBFileWriter::CHDXHOBFileWriter()
{
	return;
}

void CHDXHOBFileWriter::WriteHOBFile(  char *filename, LPDIRECT3DRMFRAME3 f)
{

}