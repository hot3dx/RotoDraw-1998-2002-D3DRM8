#include "stdafx.h"
#include "d3dcamera.h"
#include "dxsdk8\include\d3drm.h"

D3DCamera::D3DCamera(){}


	LPDIRECT3DRMMESHBUILDER3 D3DCamera::CameraMesh(){ 

	LPDIRECT3DRMMESHBUILDER3 meshc;
	LPDIRECT3DRMMATERIAL2 mat;
    LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm);
	rm->CreateMaterial( 1.0f, &mat);
	mat->SetAmbient(1.0f, 1.0f, 1.0f);
	mat->SetEmissive(1.0f, 1.0f, 1.0f);
	rm->CreateMeshBuilder(&meshc);


D3DVECTOR vertArray[33];
D3DVECTOR normArray[33];
int color[33];
float tu[33];
float tv[33];


unsigned long fd[] = {3,0,0,1,1,2,2,
3,0,0,2,2,3,3,
3,0,0,4,4,5,5,
3,0,0,5,5,1,1,
3,1,1,5,5,6,6,
3,1,1,6,6,2,2,
3,2,2,6,6,7,7,
3,2,2,7,7,3,3,
3,3,3,7,7,4,4,
3,3,3,4,4,0,0,
3,4,4,7,7,6,6,
3,4,4,6,6,5,5,
3,8,8,17,17,9,9,
3,8,8,16,16,17,17,
3,9,9,18,18,10,10,
3,9,9,17,17,18,18,
3,10,10,19,19,11,11,
3,10,10,18,18,19,19,
3,11,11,20,20,12,12,
3,11,11,19,19,20,20,
3,12,12,21,21,13,13,
3,12,12,20,20,21,21,
3,13,13,22,22,14,14,
3,13,13,21,21,22,22,
3,14,14,23,23,15,15,
3,14,14,22,22,23,23,
3,15,15,16,16,8,8,
3,15,15,23,23,16,16,
3,16,16,24,24,17,17,
3,17,17,24,24,18,18,
3,18,18,24,24,19,19,
3,19,19,24,24,20,20,
3,20,20,24,24,21,21,
3,21,21,24,24,22,22,
3,22,22,24,24,23,23,
3,23,23,24,24,16,16,
3,25,25,27,27,26,26,
3,25,25,28,28,27,27,
3,26,26,31,31,30,30,
3,26,26,27,27,31,31,
3,27,27,32,32,31,31,
3,27,27,28,28,32,32,
3,28,28,29,29,32,32,
3,28,28,25,25,29,29,
3,29,29,31,31,32,32,
3,29,29,30,30,31,31,
};

vertArray[0].x = 0.296875f;
vertArray[0].y = 0.582031f;
vertArray[0].z = 0.253906f;
normArray[0].x = 0.66766363f;
normArray[0].y = 0.66766363f;
normArray[0].z = 0.32934883f;
tu[0] = 0.0f;
tv[0] = 0.0f;
color[0] = -1;
vertArray[1].x = 0.296875f;
vertArray[1].y = 0.578125f;
vertArray[1].z = -0.327881f;
normArray[1].x = 0.40733796f;
normArray[1].y = 0.40732893f;
normArray[1].z = -0.81740993f;
tu[1] = 0.0f;
tv[1] = 0.0f;
color[1] = -1;

vertArray[2].x = -0.281006f;
vertArray[2].y = 0.578125f;
vertArray[2].z = -0.327881f;
normArray[2].x = -0.66567427f;
normArray[2].y = 0.6656593f;
normArray[2].z = -0.33730614f;
tu[2] = 0.0f;
tv[2] = 0.0f;
color[2] = -1;

vertArray[3].x = -0.281006f;
vertArray[3].y = 0.582031f;
vertArray[3].z = 0.253906f;
normArray[3].x = -0.40916497f;
normArray[3].y = 0.40915596f;
normArray[3].z = 0.81558293f;
tu[3] = 0.0f;
tv[3] = 0.0f;
color[3] = -1;

vertArray[4].x = 0.296875f;
vertArray[4].y = 0.000000f;
vertArray[4].z = 0.253906f;
normArray[4].x = 0.3333329f;
normArray[4].y = -0.66666675f;
normArray[4].z = 0.66666675f;
tu[4] = 0.0f;
tv[4] = 0.0f;
color[4] = -1;

vertArray[5].x = 0.296875f;
vertArray[5].y = 0.000000f;
vertArray[5].z = -0.327881f;
normArray[5].x = 0.8164969f;
normArray[5].y = -0.40824795f;
normArray[5].z = -0.40824795f;
tu[5] = 0.0f;
tv[5] = 0.0f;
color[5] = -1;

vertArray[6].x = -0.281006f;
vertArray[6].y = 0.000000f;
vertArray[6].z = -0.327881f;
normArray[6].x = -0.3333329f;
normArray[6].y = -0.66666675f;
normArray[6].z = -0.66666675f;
tu[6] = 0.0f;
tv[6] = 0.0f;
color[6] = -1;

vertArray[7].x = -0.281006f;
vertArray[7].y = 0.000000f;
vertArray[7].z = 0.253906f;
normArray[7].x = -0.8164969f;
normArray[7].y = -0.40824795f;
normArray[7].z = 0.40824795f;
tu[7] = 0.0f;
tv[7] = 0.0f;
color[7] = -1;

vertArray[8].x = 0.167969f;
vertArray[8].y = 0.175781f;
vertArray[8].z = 0.250000f;
normArray[8].x = 0.728453f;
normArray[8].y = -0.6850953f;
normArray[8].z = 0.0000000f;
tu[8] = 0.0f;
tv[8] = 0.0f;
color[8] = -1;

vertArray[9].x = 0.039063f;
vertArray[9].y = 0.09375f;
vertArray[9].z = 0.250000f;
normArray[9].x = 0.026955f;
normArray[9].y = -0.999636f;
normArray[9].z = 0.000000f;
tu[9] = 0.0f;
tv[9] = 0.0f;
color[9] = -1;

vertArray[10].x = -0.109131f;
vertArray[10].y = 0.128906f;
vertArray[10].z = 0.250000f;
normArray[10].x = -0.694764f;
normArray[10].y = -0.719236f;
normArray[10].z = 0.000000f;
tu[10] = 0.0f;
tv[10] = 0.0f;
color[10] = -1;

vertArray[11].x = -0.187256f;
vertArray[11].y = 0.257813f;
vertArray[11].z = 0.250000f;
normArray[11].x = -0.999790f;
normArray[11].y = -0.020475f;
normArray[11].z = 0.000000f;
tu[11] = 0.0f;
tv[11] = 0.0f;
color[11] = -1;

vertArray[12].x = -0.152100f;
vertArray[12].y = 0.406250f;
vertArray[12].z = 0.250000f;
normArray[12].x = -0.729735f;
normArray[12].y = 0.68373f;
normArray[12].z = 0.000000f;
tu[12] = 0.0f;
tv[12] = 0.0f;
color[12] = -1;

vertArray[13].x = -0.023193f;
vertArray[13].y = 0.488281f;
vertArray[13].z = 0.250000f;
normArray[13].x = -0.026955f;
normArray[13].y = 0.999636f;
normArray[13].z = 0.000000f;
tu[13] = 0.0f;
tv[13] = 0.0f;
color[13] = -1;

vertArray[14].x = 0.125000f;
vertArray[14].y = 0.453125f;
vertArray[14].z = 0.250000f;
normArray[14].x = 0.701282f;
normArray[14].y = 0.712883f;
normArray[14].z = 0.000000f;
tu[14] = 0.0f;
tv[14] = 0.0f;
color[14] = -1;

vertArray[15].x = 0.203125f;
vertArray[15].y = 0.320313f;
vertArray[15].z = 0.250000f;
normArray[15].x = 0.999925f;
normArray[15].y = 0.012232f;
normArray[15].z = 0.000000f;
tu[15] = 0.0f;
tv[15] = 0.0f;
color[15] = -1;

vertArray[16].x = 0.167969f;
vertArray[16].y = 0.175781f;
vertArray[16].z = 0.558594f;
normArray[16].x = 0.7194528f;
normArray[16].y = -0.38184795f;
normArray[16].z = 0.580154f;
tu[16] = 0.0f;
tv[16] = 0.0f;
color[16] = -1;

vertArray[17].x = 0.0f;
vertArray[17].y = -0.2f;
vertArray[17].z = 0.558594f;
normArray[17].x = 0.24551198f;
normArray[17].y = -0.774848f;
normArray[17].z = 0.582523f;
tu[17] = 0.0f;
tv[17] = 0.0f;
color[17] = -1;

vertArray[18].x = -0.109131f;
vertArray[18].y = 0.128906f;
vertArray[18].z = 0.558594f;
normArray[18].x = -0.383238f;
normArray[18].y = -0.717175f;
normArray[18].z = 0.582053f;
tu[18] = 0.0f;
tv[18] = 0.0f;
color[18] = -1;

vertArray[19].x = -0.2f;
vertArray[19].y = 0.0f;
vertArray[19].z = 0.558594f;
normArray[19].x = -0.779510f;
normArray[19].y = -0.234170f;
normArray[19].z = 0.5809708f;
tu[19] = 0.0f;
tv[19] = 0.0f;
color[19] = -1;

vertArray[20].x = -0.1521f;
vertArray[20].y = 0.40625f;
vertArray[20].z = 0.558594f;
normArray[20].x = -0.72078294f;
normArray[20].y = 0.37870196f;
normArray[20].z = 0.5805659f;
tu[20] = 0.0f;
tv[20] = 0.0f;
color[20] = -1;

vertArray[21].x = 0.0f;
vertArray[21].y = 0.2f;
vertArray[21].z = 0.558594f;
normArray[21].x = -0.24551198f;
normArray[21].y = 0.77484894f;
normArray[21].z = 0.582523f;
tu[21] = 0.0f;
tv[21] = 0.0f;
color[21] = -1;

vertArray[22].x = 0.125f;
vertArray[22].y = 0.453125f;
vertArray[22].z = 0.558594f;
normArray[22].x = 0.3858161f;
normArray[22].y = 0.7150343f;
normArray[22].z = 0.5829853f;
tu[22] = 0.0f;
tv[22] = 0.0f;
color[22] = -1;

vertArray[23].x = 0.2f;
vertArray[23].y = 0.0f;
vertArray[23].z = 0.558594f;
normArray[23].x = 0.7823599f;
normArray[23].y = 0.22571898f;
normArray[23].z = 0.5804859f;
tu[23] = 0.0f;
tv[23] = 0.0f;
color[23] = -1;

vertArray[24].x = 0.0f;
vertArray[24].y = 0.0f;
vertArray[24].z = 0.558594f;
normArray[24].x = 0.0f;
normArray[24].y = 0.0f;
normArray[24].z = 1.0f;
tu[24] = 0.0f;
tv[24] = 0.0f;
color[24] = -1;

vertArray[25].x = 0.15625f;
vertArray[25].y = 0.578125f;
vertArray[25].z = -0.331787f;
normArray[25].x = 0.894427f;
normArray[25].y = 0.0f;
normArray[25].z = -0.447214f;
tu[25] = 0.0f;
tv[25] = 0.0f;
color[25] = -1;

vertArray[26].x = 0.15625f;
vertArray[26].y = 0.578125f;
vertArray[26].z = 0.121094f;
normArray[26].x = 0.44721404f;
normArray[26].y = 0.54480606f;
normArray[26].z = 0.70935607f;
tu[26] = 0.0f;
tv[26] = 0.0f;
color[26] = -1;

vertArray[27].x = 0.15625f;
vertArray[27].y = 0.78125f;
vertArray[27].z = -0.034912f;
normArray[27].x = 0.591404f;
normArray[27].y = 0.77152f;
normArray[27].z = 0.23451698f;
tu[27] = 0.0f;
tv[27] = 0.0f;
color[27] = -1;

vertArray[28].x = 0.15625f;
vertArray[28].y = 0.78125f;
vertArray[28].z = -0.331787f;
normArray[28].x = 0.40824795f;
normArray[28].y = 0.40824795f;
normArray[28].z = -0.8164969f;
tu[28] = 0.0f;
tv[28] = 0.0f;
color[28] = -1;

vertArray[29].x = -0.136475f;
vertArray[29].y = 0.578125f;
vertArray[29].z = -0.331787f;
normArray[29].x = -0.7071068f;
normArray[29].y = 0.0f;
normArray[29].z = -0.70710677f;
tu[29] = 0.0f;
tv[29] = 0.0f;
color[29] = -1;

vertArray[30].x = -0.136475f;
vertArray[30].y = 0.578125f;
vertArray[30].z = 0.121094f;
normArray[30].x = -0.70710707f;
normArray[30].y = 0.43070704f;
normArray[30].z = 0.560795f;
tu[30] = 0.0f;
tv[30] = 0.0f;
color[30] = -1;

vertArray[31].x = -0.136475f;
vertArray[31].y = 0.78125f;
vertArray[31].z = -0.034912f;
normArray[31].x = -0.5914044f;
normArray[31].y = 0.65593344f;
normArray[31].z = 0.46903327f;
tu[31] = 0.0f;
tv[31] = 0.0f;
color[31] = -1;

vertArray[32].x = -0.136475f;
vertArray[32].y = 0.78125f;
vertArray[32].z = -0.331787f;
normArray[32].x = -0.40824795f;
normArray[32].y = 0.8164969f;
normArray[32].z = -0.40824795f;
tu[32] = 0.0f;
tv[32] = 0.0f;
color[32] = -1;

int retid[] = {0,};
//mesh->AddGroup(33, 46,  3,  &fd, retid);
meshc->AddFaces(33, vertArray, 33, normArray, fd, NULL);



meshc->SetMaterial(mat);//must have to show material
for(int i =0;i<= 32;i++){
	meshc->SetTextureCoordinates( i, tu[i], tv[i] );
}
	rm1->Release();
	rm->Release();
	mat->Release();
return meshc;
 

}//eomethod
