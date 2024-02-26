#ifndef _HDXPALETTEIO_H
#define _HDXPALETTEIO_H

#pragma once

#include "stdafx.h"
#include "data3d.h"
// version xmf 358

class CWriteHDXPalette
{
public:
	CWriteHDXPalette();
	int* ConvertFloatToInt(void* a); 
	void WriteByteAsNullString(CFile* fs, char* s);
	void WriteFourBytesAsNullString(CFile* fs, char* s);
	void WriteBinaryFloatFourBytes(CFile* fs, float arg);
	void WriteBinaryIntFourBytes(CFile* fs, int t);
	void WriteHDXPaletteFileTxt( HDXMaterialArray arr, CString filename);
	void WriteHDXPaletteFileBin(HDXMaterialArray arr, CString filename);
private:

	char* lpBuffer;
	HANDLE hFile;
	CFile* myFileWrite;
	
};

class CReadHDXPalette
{
public:
	CReadHDXPalette();
	HDXMaterialArray ReadHDXPaletteFileTxt(CFile* fs, HDXMaterialArray arr, CString filename);
	HDXMaterialArray ReadHDXPaletteFileBin( CFile* fs, HDXMaterialArray arr, CString filename );
	float afloat( unsigned int a);
	float ReadBinaryFloatFourBytes();
	char* ReadFourBytesAddTerminator(CFile*  fs, char* s);
	int ReadFourBytesInteger(CFile* fs );
	void ReadFourBytesAsNullString(CFile*  fs, char *s);
	BYTE ReadByteAsNullString(CFile*  fs);
	char* ReadStringNullTerminated( CFile* fs, char *s, int count);
	HDXMaterialArray ReadHeaderInitStream( HDXMaterialArray arr, CString filename );

private:
	void* lpBuffer;
	HANDLE hFile;
	CFile* myFile;
};
#endif //_HDXPALETTEIO_H