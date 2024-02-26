#include "dxsdk8\include\d3drmwin.h"

#pragma once

class CCubeDX
{
public:
	CCubeDX();
	BOOL build_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder );
	HRESULT PutTextureCoords(LPDIRECT3DRMMESHBUILDER3 pMeshBuilder, int VertexCount, D3DVALUE *u, D3DVALUE *v);
	BOOL sel_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder );
	BOOL build_face1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder );
	BOOL build_face2( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder );
	~CCubeDX();

};