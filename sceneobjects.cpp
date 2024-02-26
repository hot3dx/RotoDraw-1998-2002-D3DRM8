#include "stdafx.h"
#include "sceneobjects.h"
#include "D3DCamera.h"
#include "grid.h"
#include "cubedx.h"


CSceneObjects::CSceneObjects()
{
	return;
}

CSceneObjects::~CSceneObjects()
{
	delete this;
}

BOOL CSceneObjects::InitScene(LPDIRECT3DRMFRAME3 m_scene, LPDIRECT3DRM3 m_lpD3DRM)
{
	m_iMainGroupFrameCount = 0;
	if (FAILED(m_lpD3DRM->CreateFrame( m_scene, &m_MainGroupFrame)))
	{
		MessageBox( NULL, L" scene group creation failed ",  L" error ", MB_OK );
	return FALSE;
	}
	if (FAILED(m_lpD3DRM->CreateFrame( m_scene, &finalMeshFrame)))
	{
		MessageBox( NULL, L" temp mesh frame creation failed ",  L" error ", MB_OK );
	return FALSE;
	}
	CCubeDX dxCube;
	// scene objects init code here
	if (FAILED(m_scene->SetSceneBackground(D3DCOLOR( 16777215))))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}

	
    //SCENEOBJRELEASE(light);

    if (FAILED(m_lpD3DRM->CreateFrame(m_scene, &win_frame)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	win_frame->SetName("frame");
	}

	if (FAILED(win_frame->SetPosition(m_scene, D3DVAL(0.0F), D3DVAL(0.0F), D3DVAL(0.0F))))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	
    if (FAILED(m_lpD3DRM->CreateMeshBuilder(&win_builder)))
	return FALSE;
	win_builder->SetName("builder");
	
	if( FAILED( m_lpD3DRM->CreateFrame( m_scene, &win_frame1 ) ) )
		{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	win_frame1->SetName("frame1");
	}
	if( FAILED( m_lpD3DRM->CreateMeshBuilder( &win_cube1_builder ) ) )
		{
		MessageBox( NULL, L" cube mesh failed ",  L" error ", MB_OK );
	return FALSE;
	
	}

	if( !dxCube.build_cube1(win_cube1_builder ) )
		{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	
	}
	else{
		win_cube1_builder->SetName("cube1_builder");
	D3DCOLOR c5 = RGBA_MAKE(255, 0, 0, 255);
	win_cube1_builder->SetColor(c5);
	}
	
	if( FAILED( win_cube1_builder->CreateMesh( &win_cube1_mesh ) ) )
		{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	
	//SCENEOBJRELEASE( cube1_builder );

	if( FAILED( win_frame1->AddVisual( (LPDIRECT3DRMVISUAL)win_cube1_mesh ) ) )
		{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	
	win_frame1->SetPosition( m_scene, 0.0f, 0.0f, 0.0f );
	
    if (FAILED(m_lpD3DRM->CreateMaterial(D3DVAL(10.0), &win_mat)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
    if (FAILED(win_cube1_builder->SetMaterial(win_mat)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}

	
    SCENEOBJRELEASE(win_mat);
    if (FAILED(win_frame->AddVisual(win_cube1_builder)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	
	if( FAILED( m_lpD3DRM->CreateMeshBuilder( &finalMesh ) ) )
		{
		MessageBox( NULL, L" drawing object mesh failed ",  L" error ", MB_OK );
	return FALSE;
	
	}
	if (FAILED(m_scene->AddVisual(finalMesh)))
	{
		MessageBox( NULL, L" drawing mesh add failed ",  L" error ", MB_OK );
	return FALSE;
	}
	finalMesh->SetName("finalMesh");
	win_shape=win_cube1_builder;
	win_shape->SetName("cube");
	win_frame1=win_frame;
	win_frame1->SetName("frame1");
	win_frame1->SetPosition(NULL, -3.0F, -3.0F, 3.0F);
	
    //SCENEOBJRELEASE(builder);
    //SCENEOBJRELEASE(frame);
	

    if (FAILED(m_lpD3DRM->CreateFrame(m_scene, &m_camera)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	else{
	m_camera->SetName("m_camera");
	if (FAILED(m_lpD3DRM->CreateFrame(m_camera, &win_light)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	win_light->SetName("light");
	}
	if (FAILED(m_lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &win_light1)))
	return FALSE;
    win_light1->SetName("light1");
		
    
    if (FAILED(win_light->SetPosition(m_camera, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(-1.0))))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	if (FAILED(win_light->SetOrientation(m_scene, D3DVAL(-1.0), D3DVAL(-1.0), D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0))))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
    
    if (FAILED(m_lpD3DRM->CreateMeshBuilder(&win_builder)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	
	}
	else
	{
		D3DCamera cam;
		win_builder = cam.CameraMesh();
		win_builder->SetName("cammesh");

	}
	
    if (FAILED(win_builder->SetQuality(D3DRMRENDER_UNLITFLAT)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
    if (FAILED(win_light->AddVisual(win_builder)))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
    SCENEOBJRELEASE(win_builder);
	m_camera->AddLight(win_light1);
	CGrid agrid;
			grid = agrid.MakeGrid();
			m_lpD3DRM->CreateFrame(m_camera, &gridFrame);
			gridFrame->AddVisual(grid);
			
			grid->SetQuality(D3DRMFILL_WIREFRAME);
			grid->SetName("grid");
			gridFrame->SetName("GridFrame");
			gridFrame->SetPosition(NULL,0.0F,0.0F,81.0F);
			m_GridVisible=true;
	}
    if (FAILED(m_camera->SetPosition(m_scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(-81.0F))))
	{
		MessageBox( NULL, L" scene color failed ",  L" error ", MB_OK );
	return FALSE;
	}
	
	return TRUE;
	
}


