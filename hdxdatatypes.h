#ifndef _HDXDATATYPES_H
#define _HDXDATATYPES_H

#pragma once

////////////////////////////////////////////////////////////////////
// class defs
////////////////////////////////////////////////////////////////////

class TMorphs {
public:
	DWORD time;
    DWORD nCount;
    DWORD List[1];
};

class TMorphArray {
public:
	
    DWORD cItems;
    TMorphs morphList[1];
};

class TGroup {
public:
    DWORD nCount;
    DWORD List[1];
    
};

class TGroupArray {
public:
    DWORD cItems;
    TGroup groupList[1];
};

class TUserId {
public:
	DWORD nNameCount;
	char name[1];
	DWORD nAddrCount;
	char address[1];
	DWORD nDateCount;
	char date[1];
};

class THDXVector
{
public:
	float x;
	float y;
	float z;
};

class TV2
{
public:
	float u;
	float v;
};

class TTCoord
{
public:
	DWORD C;
	TV2 t[1];

};

class THDXNormals
{
public:
	DWORD nNormals;
	THDXVector normals[1];
};

class TSpacer
{
public:
	DWORD i;
};

class TMouse 
{
public:
	WORD x;
	WORD y;
};

class TMouseArray
{
public:
	DWORD nCount;
	TMouse positions[1];
};

class TCameraPos
{
public:
	DWORD nCount;
	THDXVector pos[1];
	THDXVector rot[1];
	float theta[1];
	THDXVector orDir[1];
	THDXVector orUp[1];
};

class Vector
{
public:
	float x;
	float y;
	float z;
};

class TMeshVertices
{
public:
    DWORD nVertices;
    THDXVector vertices[1];
};
class TFaceData
{
public:
	DWORD vertexId;
};
class TMeshFace
{
public:
    DWORD nFaceVertexIndices;
    DWORD faceVertexIndices[1];
};

class TMeshFaces
{
public:
    DWORD nFaces;
    TMeshFace faces[1];
};

class TMyMaterialList
{
public:
	DWORD nNumMaterials;
	DWORD nMaterialsPerFace;
	DWORD nMaterialList[1];
};

class TMyMaterial
{
public:
	DWORD r;
	DWORD g;
	DWORD b;
	DWORD a;
	float power;
	float sRed;
	float sGreen;
	float sBlue;
	float eRed;
	float eGreen;
	float eBlue;
	float aRed;
	float aGreen;
	float aBlue;
	DWORD fNameCnt;
	CHAR *fileName;
	DWORD nNameCNT;
	CHAR *matName;
};

class TINTARRAY
{
public:
	DWORD dwEmptyEnd;
	DWORD intCount;
	DWORD value[1];
		
};
class TPoint2
{
public:
	DWORD x;
	DWORD y;
};

class TPOINTARRAY
{
public:
	DWORD dwEmptyEnd;
	DWORD intCount;
	TPoint2 value[1];
};
class TCamGridStats
{
public:
	float m_CamPosX;
	float m_CamPosY;
	float m_CamPosZ;
	float m_CamRotX;
	float m_CamRotY;
	float m_CamRotZ;

	float m_CamOrUpX;
	float m_CamOrUpY;
	float m_CamOrUpZ;
	float m_CamOrDirX;
	float m_CamOrDirY;
	float m_CamOrDirZ;

	float m_GridPosX;
	float m_GridPosY;
	float m_GridPosZ;
	float m_GridRotX;
	float m_GridRotY;
	float m_GridRotZ;
	float m_CamTheta;
	float m_GridTheta;
};
class TPTGROUPS 
{
public:
	DWORD			m_iPtGroupCount;
};

#endif // _HDXDATATYPES_H