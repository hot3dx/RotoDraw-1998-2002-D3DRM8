// 3dpic.h is to enable pic of other formats to be viewed 
// and set with directx settings

#ifndef _3DPIC_H
#define _3DPIC_H

#pragma once

#include "sceneobjects.h"
#include "dxsdk8/include/d3drmwin.h"
#include "dxsdk8/include/d3dtypes.h"
#include "d3dcamera.h"

#undef WINRELEASE
#ifdef __cplusplus
#define WINRELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
#else
#define WINRELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}
#endif

#define MSG(str) MessageBox( NULL, str, "Application Message", MB_OK )

#ifdef __cplusplus
extern "C" {
#endif

#define CAMFRONT 1
#define CAMBACK 2
#define CAMLEFT 3
#define CAMRIGHT 4
#define CAMTOP 5
#define CAMBOTTOM 6

#define FDIFFTEXTURES 1;
#define FSAMETEXTURES 2;

class CWin3D 
{
public:
	CWin3D();
	~CWin3D();
HWND m_hWnd;
CSceneObjects* m_SceneObjects;
bool win3dSetFlag;
LPDIRECT3DRMFRAME3 m_scene;
bool m_bMain_3d_Window;

MSG m_msg;

HRESULT Win3DInit( HWND hwnd );
HWND WinInstance( HWND win );
BOOL WinRender();
BOOL CreateDevice( HWND win, CWin3D* theWin);
void Idle();
LPGUID FindDevice(D3DCOLORMODEL cm, BOOL bSoftwareOnly);
BOOL CreateScene(CWin3D* theApp);
DWORD bppToddbd(int bpp);

HRESULT PutTextureCoords(LPDIRECT3DRMMESHBUILDER3 pMeshBuilder, int VertexCount, D3DVALUE *u, D3DVALUE *v);
void Close();
int	m_iDone;
// cam stuff
float m_fCameraRotationValue;
float m_fCameraSpeed;
float m_fCameraOffset;
float m_cameraMODE;
float m_fPointSpace;

void circleCamOnAxis( int direction, float m_fCameraOffset);
void DoKeyDown(UINT wparam,  HWND hwnd,  LPDIRECT3DRMFRAME3 sFrame, LPDIRECT3DRMVISUAL sVisual);
void DoKeyUp(UINT wparam,  LPDIRECT3DRMFRAME3 sFrame);
void GridVerticesRotationGrid();
BOOL build_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder );
LPDIRECT3DRM3 GetD3DRM();
void SetD3DRM(LPDIRECT3DRM3 rm);
LPDIRECT3DRMMESHBUILDER3 acube;
LPDIRECT3DRMFRAME3 win_frame;
D3DCOLOR m_mat_rgba;
D3DVECTOR CamDir(  float x, float y, float z );
void RotateMesh( int direction, float m_fCameraOffset);

LPDIRECT3DRMMESHBUILDER3 tempMeshBld;
LPDIRECT3DRMFRAME3 tempFrame;
};

void SetCWin3D( CWin3D win3d );

#ifdef __cplusplus
}
#endif

#endif // _3DPIC_H