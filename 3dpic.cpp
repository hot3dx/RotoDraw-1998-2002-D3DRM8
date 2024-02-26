// 3dpic.cpp is to enable pic of other formats to be viewed 
// and set with directx settings
#include "stdafx.h"
#include "3dpic.h"
#include "d3dcamera.h"
#include "grid.h"
#include "d3d.h"


LPDIRECTDRAWCLIPPER m_lpDDClipper;
LPDIRECT3DRM3 m_lpD3DRM;
BOOL m_bQuit;

BOOL m_bMinimized;


CWin3D* theWin;



CWin3D::~CWin3D(){}

HRESULT CWin3D::Win3DInit( HWND hwnd )
{
	
	int		idle;
    m_iDone = FALSE;
    HRESULT	rval;
	HACCEL accel;
	
	LPDIRECT3DRM lpD3DRM1;
	
    rval = Direct3DRMCreate(&lpD3DRM1);
    
    rval = lpD3DRM1->QueryInterface( IID_IDirect3DRM3, (LPVOID*)&lpD3DRM1);
    if (rval != D3DRM_OK) {
		MessageBox( NULL, L" lpd3drm1 failed ", L"error", MB_OK);
		return 1;
    }
 
	WINRELEASE( lpD3DRM1 );
        
	WinInstance( hwnd );
    if (!(hwnd))
	{
		MessageBox(NULL, L" no HWND ", L"error", MB_OK);
	return 1;
	}
	accel = LoadAccelerators(AfxGetInstanceHandle(), L"ViewerAccel");
	
   while(!m_iDone) {
	idle = TRUE;
	
	while (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE)) {
	    idle = FALSE;
		if (m_msg.message == WM_KEYDOWN)
		{
			DoKeyDown(m_msg.wParam, hwnd, NULL, NULL );
		}
		if (m_msg.message == WM_KEYUP)
		{
				CString n;
			n.Format(L"\n % d % d % d\n",m_msg.message,m_msg.lParam, m_msg.wParam);
			OutputDebugString(n);
			DoKeyUp(m_msg.wParam, NULL );
		}
	    if (m_msg.message == WM_QUIT || m_bQuit) {
		m_iDone = TRUE;
		break;
	    }
	    if (!TranslateAccelerator(m_msg.hwnd, accel, &m_msg)) {
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	    }
	}
	if (m_iDone) {
	    break;
	} else if (!m_bMinimized && !m_bQuit) {
	    if (idle) Idle();
	    if (!WinRender()) {
		m_iDone = TRUE;
		break;
	    }
	} else {
	    WaitMessage();
	}
    }

   
	
    WINRELEASE(m_scene);
    WINRELEASE(m_SceneObjects->m_camera);
	if(m_SceneObjects->win_shape)
		
	//WINRELEASE(win_shape);
	// shape must be released before builder
	if(m_SceneObjects->win_cube1_builder)
	WINRELEASE(m_SceneObjects->win_cube1_builder);
	if(m_SceneObjects->win_builder)
	WINRELEASE(m_SceneObjects->win_builder);
	if(m_SceneObjects->win_cube1_mesh)
	WINRELEASE(m_SceneObjects->win_cube1_mesh);
	if(m_SceneObjects->win_frame1)
	WINRELEASE(m_SceneObjects->win_frame1);
	m_SceneObjects->win_frame=NULL;
	//WINRELEASE(win_frame);// this will crash the computer 
	//because it does not matter which is released frame1
	//or frame, the other is destroyed at the same time;
	
	if(m_SceneObjects->win_mat)
	WINRELEASE(m_SceneObjects->win_mat);
	if(m_SceneObjects->win_light)
	WINRELEASE(m_SceneObjects->win_light);
	if(m_SceneObjects->win_light1)
	WINRELEASE(m_SceneObjects->win_light1);
    WINRELEASE(m_SceneObjects->m_view);
    WINRELEASE(m_SceneObjects->m_dev);
    WINRELEASE(m_lpD3DRM);
    WINRELEASE(m_lpDDClipper);
	
	if(m_bMain_3d_Window == true )
	{
		delete [] &m_SceneObjects->m_CamTheta;
		delete [] &m_SceneObjects->m_GridTheta;
	}
	delete this;
	DestroyWindow( hwnd );

    return m_msg.wParam;
}

HWND CWin3D::WinInstance( HWND win)
{
	if (FAILED( DirectDrawCreateClipper( 0, &m_lpDDClipper, NULL))) {
		MessageBox(NULL, L" clipper create failed 1", L"error", MB_OK);
	return FALSE;
    }
    if (FAILED(m_lpDDClipper->SetHWnd(0, win))) {
		MessageBox(NULL, L" clipper set failed 2", L"error", MB_OK);
	WINRELEASE(m_lpDDClipper);
	return FALSE;
    }
    
    SetWindowLong( win, 0, (long) theWin);
    m_SceneObjects->m_model = D3DCOLOR_RGB;
	
	if (!CreateDevice(win, theWin)) {
		MessageBox(NULL, L"  createdevice failed 1", L"error", MB_OK);
	return FALSE;
    }

    return win;
}

BOOL CWin3D::WinRender() {
	
    if (FAILED( m_scene->Move(D3DVAL(1.0))))
	return FALSE;
	if(FAILED( m_SceneObjects->m_view->ForceUpdate(0, 0, m_SceneObjects->m_view->GetWidth(), m_SceneObjects->m_view->GetHeight())))
	return FALSE;
    if (FAILED( m_SceneObjects->m_view->Clear(D3DRMCLEAR_ALL)))
	return FALSE;
	if (FAILED( m_SceneObjects->m_view->Render(m_scene)))
	return FALSE;
    if (FAILED( m_SceneObjects->m_dev->Update()))
	return FALSE;
	m_SceneObjects->m_camera->GetPosition(NULL, &m_SceneObjects->m_CamPos);
	m_SceneObjects->m_camera->GetRotation(NULL, &m_SceneObjects->m_CamRot, m_SceneObjects->m_CamTheta);
	m_SceneObjects->m_camera->GetOrientation(NULL, &m_SceneObjects->m_CamDir, &m_SceneObjects->m_CamUp );
	
    return TRUE;
	
}

BOOL CWin3D::CreateDevice(HWND win, CWin3D* theWin)
{
	RECT r;
    int bpp;
    HDC hdc;

    GetClientRect(win, &r);
	r.right=350;r.bottom=350;
    if (FAILED( m_lpD3DRM->CreateDeviceFromClipper(m_lpDDClipper,
						FindDevice(m_SceneObjects->m_model, FALSE),
						r.right, r.bottom,
						&m_SceneObjects->m_dev)))
    {
	if (FAILED(m_lpD3DRM->CreateDeviceFromClipper(m_lpDDClipper,
						    FindDevice(m_SceneObjects->m_model, TRUE),
						    r.right, r.bottom,
						    &m_SceneObjects->m_dev)))
	{
		MessageBox( NULL, L" CreateDeviceFromClipper failed ", L" error ", MB_OK );
	    goto generic_error;
	}
    }
    m_SceneObjects->m_dev->SetRenderMode(D3DRMRENDERMODE_BLENDEDTRANSPARENCY|D3DRMRENDERMODE_SORTEDTRANSPARENCY);
    
    hdc = GetDC(win);
    bpp = GetDeviceCaps(hdc, BITSPIXEL);
    ReleaseDC(win, hdc);
    switch (bpp)
    {
    case 1:
	if (FAILED(m_SceneObjects->m_dev->SetShades(4)))
	    goto generic_error;
	if (FAILED(m_lpD3DRM->SetDefaultTextureShades(4)))
	    goto generic_error;
	break;
    case 16:
	if (FAILED(m_SceneObjects->m_dev->SetShades(32)))
	    goto generic_error;
	if (FAILED(m_lpD3DRM->SetDefaultTextureColors(64)))
	    goto generic_error;
	if (FAILED(m_lpD3DRM->SetDefaultTextureShades(32)))
	    goto generic_error;
	if (FAILED(m_SceneObjects->m_dev->SetDither(FALSE)))
	    goto generic_error;
	break;
    case 24:
    case 32:
	if (FAILED(m_SceneObjects->m_dev->SetShades(256)))
	    goto generic_error;
	if (FAILED(m_lpD3DRM->SetDefaultTextureColors(64)))
	    goto generic_error;
	if (FAILED(m_lpD3DRM->SetDefaultTextureShades(256)))
	    goto generic_error;
	if (FAILED(m_SceneObjects->m_dev->SetDither(FALSE)))
	    goto generic_error;
	break;
    default:
	if (FAILED(m_SceneObjects->m_dev->SetDither(FALSE)))
	    goto generic_error;
    }
    if (!CreateScene(theWin))
	{
		MessageBox( NULL, L" create scene is not ", L" error ", MB_OK );
	goto generic_error;
	}
    if (FAILED(m_lpD3DRM->CreateViewport(m_SceneObjects->m_dev, m_SceneObjects->m_camera, 0, 0,
	m_SceneObjects->m_dev->GetWidth(),
	m_SceneObjects->m_dev->GetHeight(), &m_SceneObjects->m_view)))
	{
		MessageBox( NULL, L" viewport create failed ", L" error ", MB_OK );
	goto generic_error;
	}
    if (FAILED(m_SceneObjects->m_view->SetBack(D3DVAL(500.0))))
	{
		MessageBox( NULL, L" viewport setback failed ", L" error ", MB_OK );
	goto generic_error;
	}

	
    return TRUE;
generic_error:
    //Msg("An error occurred while creating the device.\n");
   MessageBox( NULL, L" create device end totally failed ", L" error ", MB_OK );
	
///ret_with_error:
    return FALSE;
}

void CWin3D::Idle()
{
    if (theWin == NULL){ return;}
	else{
	WinRender();
	}
}

LPGUID CWin3D::FindDevice(D3DCOLORMODEL cm, BOOL bSoftwareOnly)
{
    LPDIRECTDRAW lpDDAPP;
	LPDIRECT3D lpD3DAPP;

    D3DFINDDEVICESEARCH search;
    static D3DFINDDEVICERESULT result;
    HRESULT error;
    HDC hdc;
    int bpp;

    hdc = GetDC(NULL);
    bpp = GetDeviceCaps(hdc, BITSPIXEL);
    ReleaseDC(NULL, hdc);

	
    if (DirectDrawCreate(NULL, &lpDDAPP, NULL))
    	return NULL;

    if (lpDDAPP->QueryInterface(IID_IDirect3D, (void**) &lpD3DAPP)) {
    	lpDDAPP->Release();
		return NULL;
    }
    
    memset(&search, 0, sizeof search);
    search.dwSize = sizeof search;
    search.dwFlags = D3DFDS_COLORMODEL;
    search.dcmColorModel = (cm == D3DCOLOR_MONO) ? D3DCOLOR_MONO : D3DCOLOR_RGB;
    if (bSoftwareOnly)
    {
	search.dwFlags |= D3DFDS_HARDWARE;
	search.bHardware = FALSE;
    }

    memset(&result, 0, sizeof result);
    result.dwSize = sizeof result;

    error = lpD3DAPP->FindDevice(&search, &result);

    if (error == DD_OK) {

		
	/*
	 * If the device found is hardware but cannot support the current
	 * bit depth, then fall back to software rendering.
	 */
	if (result.ddHwDesc.dwFlags
	    && !(result.ddHwDesc.dwDeviceRenderBitDepth & bppToddbd(bpp))) {
	    
	    search.dwFlags |= D3DFDS_HARDWARE;
	    search.bHardware = FALSE;
	    memset(&result, 0, sizeof result);
	    result.dwSize = sizeof result;
	    error = lpD3DAPP->FindDevice(&search, &result);
	}
    }

    lpD3DAPP->Release();
    lpDDAPP->Release();

    if (error)
	return NULL;
    else
	return &result.guid;
}

BOOL CWin3D::CreateScene(CWin3D* theApp)
{
	
    m_SceneObjects->win_frame = NULL;
    m_SceneObjects->win_light = NULL;
	m_SceneObjects->win_light1 = NULL;
    m_SceneObjects->win_builder = NULL;
    m_SceneObjects->win_mat = NULL;
//    HRESULT rval;
	
    if (FAILED(m_lpD3DRM->CreateFrame(NULL, &m_scene)))
	goto generic_error;
	m_scene->SetName("m_scene");
	m_SceneObjects->InitScene(m_scene, m_lpD3DRM);
	return TRUE;
generic_error:
	//MessageBox( NULL, L" eo createscene ", L"  error ", MB_OK );
    //Msg(L"A failure occurred while creating the scene.\n");
//ret_with_error:
    WINRELEASE(m_SceneObjects->win_frame);
    WINRELEASE(m_SceneObjects->win_light);
	WINRELEASE(m_SceneObjects->win_light1);
    WINRELEASE(m_SceneObjects->win_builder);
    WINRELEASE(m_SceneObjects->win_mat);
	
	
    return FALSE;
}

DWORD CWin3D::bppToddbd(int bpp)
{
    switch(bpp) {
    case 1:
	return DDBD_1;
    case 2:
	return DDBD_2;
    case 4:
	return DDBD_4;
    case 8:
	return DDBD_8;
    case 16:
	return DDBD_16;
    case 24:
	return DDBD_24;
    case 32:
	return DDBD_32;
    }
    return 0;
}





void SetCWin3D( CWin3D win3d )
{
	theWin = &win3d;
	m_bQuit = FALSE;
}

CWin3D::CWin3D()
{
	m_SceneObjects = new CSceneObjects();
	return;
}

HRESULT CWin3D::PutTextureCoords(LPDIRECT3DRMMESHBUILDER3 pMeshBuilder, int VertexCount, D3DVALUE *u, D3DVALUE *v)
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

void CWin3D::Close()
{
	m_bQuit=TRUE;
}

LPDIRECT3DRM3 CWin3D::GetD3DRM()
{
	return m_lpD3DRM;
}

void CWin3D::SetD3DRM(LPDIRECT3DRM3 rm)
{
	m_lpD3DRM = rm;
}

D3DVECTOR avCubeVerts[] = { -5.5f, -5.5f, -5.5f,  -5.5f, -5.5f,  5.5f,
                               -5.5f,  5.5f, -5.5f,  -5.5f,  5.5f,  5.5f,
                                5.5f, -5.5f, -5.5f,   5.5f, -5.5f,  5.5f,
                                5.5f,  5.5f, -5.5f,   5.5f,  5.5f,  5.5f };

BOOL CWin3D::build_cube1( LPDIRECT3DRMMESHBUILDER3 pMeshBuilder )
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

    if( FAILED( pMeshBuilder->AddFaces( 8, avCubeVerts, 6*4, avCube1Normals,
			                            adwFace1Data, NULL ) ) )
		return FALSE;

	PutTextureCoords(pMeshBuilder, 8, u, v);

    return TRUE;
}