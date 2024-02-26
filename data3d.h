#ifndef _DATA3D_H
#define _DATA3D_H

# pragma once

#include "stdafx.h"

//#include <d3drm.h>
#include "ClipTexture.h"


class HDXMaterial
{
public:
	HDXMaterial();
	BYTE r,g,b,a;
	float args[10];
	int fCount;
	char *file;
	int nCount;
	char *matName;
	~HDXMaterial();
	

};

class HDXMaterialArray
{
public:
	HDXMaterialArray();
	unsigned int m_Count;
	HDXMaterial *m_Mats;
	HDXMaterial * Allocate(unsigned int size);
	void DeAllocate();
	HDXMaterial * Grow(HDXMaterial arg);
	void Set( unsigned int item, HDXMaterial arg);
	HDXMaterial Get( unsigned int item);
	HDXMaterial * Shrink(unsigned int pos);
	LPDIRECT3DRMMATERIAL2 CreateHDXMaterial( LPDIRECT3DRM3 rm, unsigned int item);
	LPDIRECT3DRMTEXTURE3 CreateHDXTextue( LPDIRECT3DRM3 rm, unsigned int item);
};

class HDXUndoFacesArray
{
public:
	HDXUndoFacesArray();
	unsigned int m_Count;
	LPDIRECT3DRMFACE2 *m_FacesArray;
	
	LPDIRECT3DRMFACE2 * Allocate(unsigned int size);
	void Deallocate();
	LPDIRECT3DRMFACE2 * Grow(LPDIRECT3DRMFACE2 face);

};

class HDXMaterialList
{
public:
	HDXMaterialList();
	int m_iNumMats;
	int m_iMatsPerFace;
	int m_iListCount;
	CHDXINTARRAY m_MatList;
	~HDXMaterialList();
	

};

class HDXMaterialListArray
{
public:
	HDXMaterialListArray();
	unsigned int m_iCount;
	HDXMaterialList *m_Lists;
	HDXMaterialList * Allocate(unsigned int size);
	void DeAllocate();
	HDXMaterialList * Grow(HDXMaterialList arg);
	void Set( unsigned int item, HDXMaterialList arg);
	HDXMaterialList Get( unsigned int item);
	HDXMaterialList * Shrink(unsigned int pos);
};

class LPVOIDDATA
{
public:
	LPVOIDDATA();
	~LPVOIDDATA();
	unsigned int m_uiCount;
	LPVOID arg;
	void * Allocate(unsigned int size);
	void Deallocate();
	void * Grow( unsigned int size, unsigned int sizeOfItem, LPVOID data);
};
#endif //_DATA3D_H