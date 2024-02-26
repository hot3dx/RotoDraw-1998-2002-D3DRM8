#ifndef _READDIRECTX_H
#define _READDIRECTX_H

#include "stdafx.h"
#include <iosfwd>
#include "dxsdk8\include\d3drm.h"
#include "cliptexture.h"
#include "data3d.h"

using namespace std;

class FILEVARS
{
public:
	FILEVARS();
unsigned int m_iMeshCoordCount;
float *m_fAMeshCoords;
unsigned int m_iMeshNormalCount;
float *m_fAMeshNormals;
unsigned int m_iMeshTextCount;
float *m_fAMeshTextCoords;
int filePlaceTracker;
int m_iMeshIntegerCount;
int *m_iIntegerList;
char *m_cNumberList;
int m_iLastName;
int m_iFaceCnt;
int *m_iVFacesList;
int m_iVFacesListCount;
int m_iVFacesListNumFaces;
int *m_iNFacesList;
int m_iNFacesListCount;
int m_iNFacesListNumFaces;
int m_iNumMaterials;
int m_iMaterialsPerFace;
int m_iMaterialListCount;
int *m_iMaterialList;

};

class CReadDirectXFile
{
public:
	CReadDirectXFile();
	int linepos;
	int fpos;
	int linecount;
	int readCount;
	char line[256];
	istream fst();
	int fsGet(void);
	void  fsRead( unsigned char *arg, int count);
	void  fsRead( signed char *arg, int count);
	void  fsRead( char *arg, int count);
	
	void ReadTokenTerminator(istream fs);
	DWORD GetDWORDCount(istream fs, unsigned char *pch);
	void ReadTwoBytesAsNullString(istream  fs, unsigned char *s);
	void ReadFourBytesNullString(istream  fs, unsigned char *s);
	void ReadEightBytesAsNullString(istream  fs, unsigned char *s);
	unsigned char * ReadFourBytesAddTerminator(istream  fs);
	float afloat( unsigned int a);
	float ReadBinaryFloatFourBytes(istream fs);
	
//////////////////////////////////////////////////////
	///////// .x file
	//////////////////////////////////////////////////
	unsigned int m_totalItemCount;
	unsigned int hTreeItemCount;
	unsigned int m_rootCount;
	char *m_magic;
	char *m_version1;
	char *m_version2;
	char *m_fileType;
	char *m_floatBits;

	char * GetHeader(istream fs);
	char * GetMagic(char *  pch);
	char * GetVersion1(char *  pch);
	char * GetVersion2(char *  pch);
	char * GetXFileType(char *  pch);
	char * GetFloatBits1(char *  pch);
	int GetRealNumListCount(istream fs);
	float * GetRealNumbersFloat4(istream fs, int listCount, float *floats, char *s);
	char * FloatToStringNull(float floatArg, int precision);
	char * GetDotXNameCount(istream fs);
	int ReadDotXFileBinaryCount( char *m_sOpenFileName );
	int ReadDotXBinaryFile( char *m_sOpenFileName, int count );
	float * ReadFloatArray(istream fs, float *fl, unsigned int* num, char *s);
	int * ReadFacesIntList( istream fs, int *ilist, int* numFaces, int* listsize );
	void ReadMesh(istream fs, FILEVARS f);
	void ReadMeshNormals(istream fs, FILEVARS f);
	void ReadMeshMaterialList(istream fs, FILEVARS f);
	void ReadMaterial(istream fs, FILEVARS f);
	void ReadMeshTextureCoords(istream fs, FILEVARS f);
	
void ReadHeader(istream fs, FILEVARS f);
void ReadFrame(istream fs, FILEVARS f);
void ReadFrameTransformMatrix(istream fs, FILEVARS f);
void ReadTextureFileName(istream fs, FILEVARS, char* *tex, int* arg);
void ReadVertexDuplicationIndices(istream fs, FILEVARS f); 

	CMAKERPTGROUPS m_TPtGroups;
	HDXMaterialArray m_TMatArray;
	CPoints m_TMeshPoints;

	bool mesh0302Flag;
	bool mesh0303Flag;

	HDXMaterialArray m_RTMat;

	bool isFrame;

	LPDIRECT3DRMMESHBUILDER3 LoadMesh;

};

#endif //_READDIRECTX_H
