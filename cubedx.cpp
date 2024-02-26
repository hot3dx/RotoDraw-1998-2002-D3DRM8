#include "stdafx.h"
#include "cubedx.h"
CCubeDX::CCubeDX()
{
	return;
}

CCubeDX::~CCubeDX()
{
}

D3DVECTOR avCubeVertices[] = { -0.1f, -0.1f, -0.1f,  -0.1f, -0.1f,  0.1f,
                               -0.1f,  0.1f, -0.1f,  -0.1f,  0.1f,  0.1f,
                                0.1f, -0.1f, -0.1f,   0.1f, -0.1f,  0.1f,
                                0.1f,  0.1f, -0.1f,   0.1f,  0.1f,  0.1f };


BOOL CCubeDX::build_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder )
{
    // cube 1 has planar faces, one normal is shared by all vertices of a
    // face
    DWORD adwFace1Data[] = {  4,  1,  0,  5,  1,  7,  2,  3,  3,
	                          4,  2,  4,  3,  5,  7,  6,  6,  7,
	                          4,  5,  8,  4,  9,  6, 10,  7, 11,
	                          4,  0, 12,  2, 13,  6, 14,  4, 15,
	                          4,  0, 16,  4, 17,  5, 18,  1, 19,
	                          4,  0, 20,  1, 21,  3, 22,  2, 23, 0 };

    D3DVECTOR avCube1Normals[] = { 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, 
		                           0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, 
		                           0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 
		                           0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 
		                           1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, 
		                           1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, 
		                           0.0f, 0.0f,-1.0f,   0.0f, 0.0f,-1.0f, 
		                           0.0f, 0.0f,-1.0f,   0.0f, 0.0f,-1.0f, 
		                           0.0f,-1.0f, 0.0f,   0.0f,-1.0f, 0.0f, 
		                           0.0f,-1.0f, 0.0f,   0.0f,-1.0f, 0.0f, 
		                          -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f, 
								  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f };

	D3DVALUE u[] =	{0.012150F,0.012150F,0.012150F,0.012150F,0.467794F,0.467794F,0.467794F,0.467794F};
	D3DVALUE v[] =	{-0.008693F,-0.311270F,-0.311270F,-0.008693F,-0.008693F,-0.311270F,-0.311270F,-0.008693F};

    if( FAILED( pMeshBuilder->AddFaces( 8, avCubeVertices, 6*4, avCube1Normals,
			                            adwFace1Data, NULL ) ) )
		return FALSE;

	PutTextureCoords(pMeshBuilder, 8, u, v);
	pMeshBuilder->SetColor(RGBA_MAKE(0,0,255,255));
	pMeshBuilder->SetQuality(D3DRMRENDER_UNLITFLAT);
    return TRUE;
}

HRESULT CCubeDX::PutTextureCoords(LPDIRECT3DRMMESHBUILDER3 pMeshBuilder, int VertexCount, D3DVALUE *u, D3DVALUE *v)
{
	if(VertexCount>pMeshBuilder->GetVertexCount()||
		VertexCount<0){return D3DRMERR_BADVALUE;}
	else
	{
		if(!pMeshBuilder){return D3DRMERR_BADVALUE;}
		else{
			for(int i = 0;i<VertexCount;i++)
			{
				pMeshBuilder->SetTextureCoordinates( i, u[i], v[i]);
			}// eo for
		}// eo else
	}// eo else
	return D3DRM_OK;
}

BOOL CCubeDX::sel_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder )
{
    // cube 1 has planar faces, one normal is shared by all vertices of a
    // face
    DWORD adwFace1Data[] = {  4,4,4,0,0,2,2,6,6,
	                          4,4,4,5,5,1,1,0,0,
	                          4,4,4,6,6,7,7,5,5,
	                          4,0,0,1,1,3,3,2,2,
	                          4,1,1,5,5,7,7,3,3,
	                          4,3,3,7,7,6,6,2,2,
							  4,4,4,6,6,2,2,0,0,
							  4,4,4,0,0,1,1,5,5,
							  4,4,4,5,5,7,7,6,6,
							  4,0,0,2,2,3,3,1,1,
							  4,1,1,3,3,7,7,5,5,
							  4,3,3,2,2,6,6,7,7,0 };

    D3DVECTOR avCube1Normals[8];

	for(int i = 0;i<8;i++)
	{
		avCube1Normals[i]=avCubeVertices[i];
			D3DRMVectorNormalize(&avCube1Normals[i]);
	}


	D3DVALUE u[] =	{0.012150F,0.012150F,0.012150F,0.012150F,0.467794F,0.467794F,0.467794F,0.467794F};
	D3DVALUE v[] =	{-0.008693F,-0.311270F,-0.311270F,-0.008693F,-0.008693F,-0.311270F,-0.311270F,-0.008693F};

    if( FAILED( pMeshBuilder->AddFaces( 8, avCubeVertices, 8, avCube1Normals,
			                            adwFace1Data, NULL ) ) )
		return FALSE;

	PutTextureCoords(pMeshBuilder, 8, u, v);

    return TRUE;
}

BOOL CCubeDX::build_face1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder )
{
    // Add a single face with all normals pointing in the same direction.
    D3DVECTOR avVertices[4] = { 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		                        1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f };
    D3DVECTOR avNormals[4] =  { 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		                        0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f };
    DWORD adwFaceData[] = { 4, 0, 0, 1, 1, 2, 2, 3, 3, 0 };

    if( FAILED( pMeshBuilder->AddFaces( 4, avVertices, 4, avNormals,
										adwFaceData, NULL ) ) )
		return FALSE;
   	return TRUE;
}

BOOL CCubeDX::build_face2( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder )
{
    // Add a single face with normals pointing in different directions to
    // approximate a curved surface.
    D3DVECTOR avVertices[4] = { 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, 
		                        1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f };
    D3DVECTOR avNormals[4]  = { 0.5f, 0.7f, 0.5f,   0.5f, 0.7f,-0.5f, 
		                       -0.5f, 0.7f,-0.5f,  -0.5f, 0.7f, 0.5f };
    DWORD adwFaceData[] = {4, 0, 0, 1, 1, 2, 2, 3, 3, 0};

    if( FAILED( pMeshBuilder->AddFaces( 4, avVertices, 4, avNormals,
		                                adwFaceData, NULL ) ) )
		return FALSE;
    return TRUE;
}
