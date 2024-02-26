#include "StdAfx.h"
#include "Tetra.h"
#include "dxsdk8\include\d3drm.h"

CTetra::CTetra()
{
	m_TPosX=0.0F;
	m_TPosY=0.0F;
	m_TPosZ=0.0F;
	m_TScale=1.0F;
	
	return;
}

CTetra::~CTetra()
{
	//m_Tetra->Release();
}

LPDIRECT3DRMMESHBUILDER3 CTetra::MakeTetra(float x, float y, float z, int r, int g, int b)
{
	LPDIRECT3DRMMESHBUILDER3 meshc;
	LPDIRECT3DRMMATERIAL2 mat;
    LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm);
	rm->CreateMaterial( 1.0F, &mat);
	mat->SetAmbient(1.0F, 1.0F, 1.0F);
	mat->SetEmissive(1.0F, 1.0F, 1.0F);
	rm->CreateMeshBuilder(&meshc);


D3DVECTOR vertArray[4];
D3DVECTOR normArray[4];
int color[4];
float tu[4];
float tv[4];

unsigned long fd[] = {3,0,0,1,1,2,2,
3,0,0,2,2,3,3,
3,0,0,3,3,1,1,
3,1,1,3,3,2,2,
3,2,2,1,1,0,0,
3,3,3,2,2,0,0,
3,1,1,3,3,0,0,
3,2,2,3,3,1,1,0,
};

vertArray[0].x = 0.5F+x;
vertArray[0].y = 0.5F+y;
vertArray[0].z = -0.5F+z;
normArray[0].x = -1.0F;
normArray[0].y = 0.0F;
normArray[0].z = 0.0F;
tu[0] = -1.0F;
tv[0] = -1.05F;
color[0] = -1;

vertArray[1].x = -0.5F+x;
vertArray[1].y = 0.5F+y;
vertArray[1].z = -0.5F+z;
normArray[1].x = 0.0F;
normArray[1].y = 1.0F;
normArray[1].z = 0.0F;
tu[1] = -0.9F;
tv[1] = -1.15F;
color[1] = -1;

vertArray[2].x = 0.0F+x;
vertArray[2].y = 0.0F+y;
vertArray[2].z = 0.5F+z;
normArray[2].x = -0.5345225F;
normArray[2].y = 0.80178374F;
normArray[2].z = 0.26726124F;
tu[2] = -1.0F;
tv[2] = -1.0F;
color[2] = -1;

vertArray[3].x = 0.0F+x;
vertArray[3].y = -0.5F+y;
vertArray[3].z = -0.5F+z;
normArray[3].x =  -0.5F;
normArray[3].y = 0.8320503F;
normArray[3].z = 0.0F;
tu[3] = -0.9F;
tv[3] = -1.15F;
color[3] = -1;

int retid[] = {0,};
//mesh->AddGroup(33, 46,  3,  &fd, retid);
meshc->AddFaces(4, vertArray, 4, normArray, fd, NULL);



meshc->SetMaterial(mat);//must have to show material
meshc->SetColor(RGBA_MAKE(r,g,b,255));

	rm1->Release();
	rm->Release();
	mat->Release();
return meshc;
 
}//eom