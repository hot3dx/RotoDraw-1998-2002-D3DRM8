
#pragma once
//#include <d3drmwin.h>

#undef SCENEOBJRELEASE
#ifdef __cplusplus
#define SCENEOBJRELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
#else
#define SCENEOBJRELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}
#endif

class CSceneObjects
{
public:
	CSceneObjects();

LPDIRECT3DRMFRAME3 m_camera;
LPDIRECT3DRMVIEWPORT2 m_view;
LPDIRECT3DRMDEVICE3 m_dev;
D3DRMCOLORMODEL m_model;
LPDIRECT3DRMMESHBUILDER3 win_cube1_builder;
LPDIRECT3DRMMESHBUILDER3 win_builder;
LPDIRECT3DRMMESH         win_cube1_mesh;
LPDIRECT3DRMFRAME3       win_frame1;
LPDIRECT3DRMMESHBUILDER3 win_shape;
LPDIRECT3DRMMATERIAL2 win_mat;
LPDIRECT3DRMFRAME3 win_frame;
LPDIRECT3DRMFRAME3 win_light;
LPDIRECT3DRMLIGHT  win_light1;
D3DCOLOR m_mat_rgba;

LPDIRECT3DRMFRAME3       box_frame;
LPDIRECT3DRMMESHBUILDER3 box_mesh;
LPDIRECT3DRMMESHBUILDER3 grid;
LPDIRECT3DRMFRAME3 gridFrame;

LPDIRECT3DRMFRAME3 copyFrame;
LPDIRECT3DRMFRAME3 m_MainGroupFrame;
	DWORD m_iMainGroupFrameCount;
LPDIRECT3DRMMESHBUILDER3 finalMesh;
LPDIRECT3DRMFRAME3 finalMeshFrame;
	// include any scene objects here
	BOOL InitScene(LPDIRECT3DRMFRAME3 scene, LPDIRECT3DRM3 m_lpD3DRM);
	D3DVECTOR m_CamPos, m_CamRot, m_CamDir, m_CamUp;
	float m_CamTheta[1];
	float m_GridTheta[1];
	bool m_GridVisible;
	~CSceneObjects();
};