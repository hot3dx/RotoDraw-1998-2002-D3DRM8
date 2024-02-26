#ifndef _HOBFILEIO_H
#define _HOBFILEIO_H

#pragma once

#include <iosfwd>
#include <fstream>
#include "dxsdk8\include\d3drm.h"
using namespace std;

class CHDXHOBFileReader
{
public:
	CHDXHOBFileReader();

	unsigned int hobFilePlaceTracker;
	
	LPDIRECT3DRMFRAME3 ReadHOBFile( CString fileName, LPDIRECT3DRMFRAME3 f);
	char * GetHeader(char * pch);
	char * GetMagic(char *  pch);
	char * GetVersion1(char *  pch);
	char * GetVersion2(char *  pch);
	char * GetXFileType(char *  pch);
	char * GetFloatBits1(char *  pch);
//void ReadHOBAnimations( istream outstr, CHDXANIMATIONARRAY* animArray);
};

class CHDXHOBFileWriter
{
public:
	CHDXHOBFileWriter();
void WriteHOBFile( char *filename, LPDIRECT3DRMFRAME3 f);
//void WriteHOBAnimationArray( ostream outstr, CHDXANIMATIONARRAY* animArray);

};

#endif // _HOBFILEIO_H