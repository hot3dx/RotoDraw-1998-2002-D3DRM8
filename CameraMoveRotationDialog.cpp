// CameraMoveRotationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "CameraMoveRotationDialog.h"
#include "CameraMoveRotationVars.h"
#include "dxsdk8\include\d3d.h"
#include "dxsdk8\include\d3dtypes.h"
#include "dxsdk8\include\d3d8.h"
#include "dxsdk8\include\d3d8types.h"
#include "dxsdk8\include\d3dx8.h"

#include "../../../../../../../Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include/WinError.h"
#include "../../../../../../../Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include/intsafe.h"

//#include "dxsdk8\include\D3DX8Math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3DRM             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DRMDEVICE       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DRMMESHBUILDER3 g_pVB        = NULL; // Buffer to hold vertices
CCameraXYMoveRotation m_CamXYMoveRotate;
LPDIRECT3DDEVICE8 dev8;
CEdit* m_CamEd1;
CEdit* m_CamEd2;




//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm);// (DIRECT3D_VERSION) ) )
        return E_FAIL;

		//LPDIRECT3DRMDEVICE* g_pd3dDevice;
    // Create the D3DDevice
    if( FAILED( rm1->CreateDevice( (DWORD)hWnd, (DWORD)hWnd, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
CUSTOMVERTEX * vertices;
VOID* pVertices;

CUSTOMVERTEX * CCameraXYMoveRotation::CalculateSphereCV( CUSTOMVERTEX * v, int* n, DWORD dwcolor )
{
	// all points on sphere at origin
	// x^2 + y^2 + z^2 = r^2 
	// x^2 + y^2 + z^2 - r^2 = 0
	// add x, y, z to position sphere in 3D space
	int cnt = 0;
	double pi = 3.1415926535897932F;
	double repCount = (360.0F*m_fCamMove_degreeradian)/m_fCamMove_anglerotation;
	double *ox;
	double *oy;
	int num = (int)repCount;
	ox = (double*) malloc(num*sizeof(double));
	if(ox!=NULL)
	{
		
	
	oy = (double*) malloc(num*sizeof(double));
	if(oy!=NULL)
	{
		
	
	double angle = 0.0F;
	double distance;
	int half = 1+num/2;

	for(int i = 0;i<half;i++)
	{
		ox[i]= m_fCamMove_cameraradius*(1.0*cos(angle));
		oy[i]= sqrt(pow(m_fCamMove_cameraradius,2.0)-pow(ox[i],2.0));//*sin(angle);

		if(oy[i]!=0.0F)
		{
			distance = sqrt(pow((ox[i-1]-ox[i]),2.0)
				+pow((oy[i-1]-oy[i]),2.0));
			double radius = fabs(oy[i]);
			double circum = 2*pi*radius;
			int rep = (int)(circum/distance);
			double zangle = 0.0F;
			double addangle = (360.0F/rep)*m_fCamMove_degreeradian;
			
			for( int j = 0;j<rep;j++)
			{
				cnt++;
				zangle+=addangle;
			}// eo j for
		}// eo if i < 0
		else
		{
			cnt++;
			
		}
		angle += m_fCamMove_anglerotation;
	
	}// eo i for


	if(m_bArrayInit==true){}
		//delete v;
	///////////////////////////////////////
	v =(CUSTOMVERTEX*)malloc(cnt*sizeof(CUSTOMVERTEX));
	if(v!=NULL)
	{
		m_bArrayInit=true;
	angle = 0.0F;
	cnt=0;
	distance = 0.0F;
	for(int i = 0;i<half;i++)
	{
		ox[i]= m_fCamMove_cameraradius*(1.0*cos(angle));
		oy[i]= sqrt(pow(m_fCamMove_cameraradius,2.0)-pow(ox[i],2.0));//*sin(angle);

		if(oy[i]!=0.0F)
		{
			distance = sqrt(pow((ox[i-1]-ox[i]),2.0)
				+pow((oy[i-1]-oy[i]),2.0));
			double radius = fabs(oy[i]);
			double circum = 2*pi*radius;
			int rep = (int)(circum/distance);
			double zangle = 0.0F;
			double addangle = (360.0F/rep)*m_fCamMove_degreeradian;
			
			for( int j = 0;j<rep;j++)
			{
				v[cnt].x = (float)ox[i]+150.0f;
				v[cnt].y = (float)(radius*(1.0*cos(zangle)))+150.0f;
				v[cnt].z = (float)(radius*(1.0*sin(zangle)));
				v[cnt].rhw=1.0f;
				v[cnt].color=dwcolor;
				cnt++;
				zangle+=addangle;
			}// eo j for
		}// eo if i < 0
		else
		{
			
			v[cnt].x = (float)ox[i]+150.0F;
			v[cnt].y = 150.0F;
 			v[cnt].z = 0.0F;
			v[cnt].rhw=1.0f;
			v[cnt].color=dwcolor;
			cnt++;
			
		}
		angle += m_fCamMove_anglerotation;
	
	}// eo i for
	m_iCount=n[0]=cnt;
	return v;
	}//eo v  !=NULL
	free(ox);}free(oy);}// eo ox and oy != NULL
	return NULL;

}

HRESULT InitVB()
{
	DWORD color = 0xff00ff00;
	int n[1];
	vertices = m_CamXYMoveRotate.CalculateSphereCV(vertices,n, color);
    // Initialize vertices for rendering
	// Both methods work
	
    vertices = //new CUSTOMVERTEX[m_CamXYMoveRotate.m_iCount];// = 
		(CUSTOMVERTEX*)malloc((m_CamXYMoveRotate.m_iCount)*sizeof(CUSTOMVERTEX));
    //{
		
        //{ 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
        //{ 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
       // {  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
    //};
	DWORD c = 0xff00ff00;
		for(int i = 0;i<m_CamXYMoveRotate.m_iCount;i++)
		{
			vertices[i].x=(float)m_CamXYMoveRotate.m_fCamMove_px[i]+150.0f;
			vertices[i].y=(float)m_CamXYMoveRotate.m_fCamMove_py[i]+150.0f;
			vertices[i].z=(float)m_CamXYMoveRotate.m_fCamMove_pz[i];
			vertices[i].rhw=1.0f;
			vertices[i].color=c;
		}
		
    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if( FAILED(dev8->CreateVertexBuffer( m_CamXYMoveRotate.m_iCount*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    
    if( FAILED( g_pVB->Lock( 0, 0/*m_CamXYMoveRotate.m_iCount*sizeof(*vertices)*/, (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, m_CamXYMoveRotate.m_iCount*sizeof(*vertices) );
    g_pVB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pVB != NULL )        
        g_pVB->Release();

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 256 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        g_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, m_CamXYMoveRotate.m_iCount );

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

/////////////////////////////////////////////////////////////////////////////
// CCameraMoveRotationDialog dialog


CCameraMoveRotationDialog::CCameraMoveRotationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraMoveRotationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameraMoveRotationDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCameraMoveRotationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraMoveRotationDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraMoveRotationDialog, CDialog)
	//{{AFX_MSG_MAP(CCameraMoveRotationDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CAM_MOVE_ROT_HELP_BUTTON, OnCamMoveRotHelpButton)
	ON_BN_CLICKED(IDC_CAMERA_MOVE_WINDOW_STATIC, OnCameraMoveWindowStatic)
	ON_BN_CLICKED(IDC_SET_CAM_SPHERE_BUTTON, OnSetCamSphereButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraMoveRotationDialog message handlers

BOOL CCameraMoveRotationDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CamEd1 = (CEdit*)GetDlgItem(IDC_CAMERA_RADIUS_EDIT);
	m_CamEd2 = (CEdit*)GetDlgItem(IDC_CAMERA_ROTATION_EDIT);
	
	CString s;
	s.Format(L"%.6f",m_CamXYMoveRotate.m_fCamMove_cameraradius);//=81.0F;
	m_CamEd1->SetWindowText(s);

	s.Format(L"%.6f",m_CamXYMoveRotate.m_fCamMove_camerarotation);//=1.0F;
	m_CamEd2->SetWindowText(s);
	
	
	
	is3DCamVisible = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCameraMoveRotationDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CCameraMoveRotationDialog::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CCameraMoveRotationDialog::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CCameraMoveRotationDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CCameraMoveRotationDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CCameraMoveRotationDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CCameraMoveRotationDialog::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDblClk(nFlags, point);
}

float yCoordofXRot3( float y, float z,  float radAngle){
	return (float)((y*cos(radAngle)) + (z*sin(radAngle)));  
}
//////////////////////////
float zCoordofXRot3(float y, float z, float radAngle){
	return (float)((z*cos(radAngle))-(y*sin(radAngle)));  
}

float xCoordofYRot3(float x, float z, float a){
	return (float)((x* cos(a)) + (z*sin(a)));
}
	
float zCoordofYRot3(float x, float z, float a){
return (float)((z*cos(a)) - (x*sin(a)));  
}

float xCoordofZRot3(float x, float y,  float radAngle){
	//	return (float)((x* cos(a))+(y*(-sin(a))));
	return (float)((x* cos(radAngle))-(y*sin(radAngle)));
}
	
float yCoordofZRot3(float x, float y, float radAngle){
	return (float)((x* sin(radAngle))+(y*cos(radAngle)));
}

float * CalculateMeshBoxAndCenterCV( CUSTOMVERTEX * v, int count)
{
	static float box[9];
	box[0]=v[0].x;
	box[1]=v[0].x;
	box[2]=v[0].y;
	box[3]=v[0].y;
	box[4]=v[0].z;
	box[5]=v[0].z;
	int i = 1;	
	while(i<count)
	{
		if(v[i].x<box[0]){box[0]=v[i].x;}
		if(v[i].x>box[1]){box[1]=v[i].x;}
		if(v[i].y<box[2]){box[2]=v[i].y;}
		if(v[i].y>box[3]){box[3]=v[i].y;}
		if(v[i].z<box[4]){box[4]=v[i].z;}
		if(v[i].z>box[5]){box[5]=v[i].z;}
		i++;
	}

	box[6] = box[0]+((box[1]-box[0])/2);
	box[7] = box[2]+((box[3]-box[2])/2);
	box[8] = box[4]+((box[5]-box[4])/2);

	return box;
		
}
int RotateOnMeshZeroAxisCV( CUSTOMVERTEX * v, VOID * pV, int Count, float a, float b, float c )
{
	// storage values to vertices
	v = (CUSTOMVERTEX*)pV;
	// Find box and center of Mesh
	float *box = CalculateMeshBoxAndCenterCV( v, Count);
	if(box!= NULL)
	{
					int i = 0;
					v[Count/2].color=0xffffffff;
				float mag1 = (float)sqrt(
					 (v[i].x * v[i].x)
					+(v[i].y * v[i].y)
					+(v[i].z * v[i].z));

	if(mag1!=0.0)
	{
		while(i<Count)
		{
		// center it on point of rotation
			v[i].x-=box[6];
			v[i].y-=box[7];
			v[i].z-=box[8];
			float x,y,z;
			
			// x axis
			if(a!=0.0f)
			{
				y=v[i].y/mag1;
				z=v[i].z/mag1;
				v[i].y=mag1*yCoordofXRot3( y,z,a*(3.141592654f / 180.0f));
				v[i].z=mag1*zCoordofXRot3( y,z,a*(3.141592654f / 180.0f));
			}
			// y axis
			if(b!=0.0f)
			{
				x=v[i].x/mag1;
				z=v[i].z/mag1;
				v[i].x=mag1*xCoordofYRot3( x,z,b*(3.141592654f / 180.0f));
				v[i].z=mag1*zCoordofYRot3( x,z,b*(3.141592654f / 180.0f));
			}
			// z axis
			if(c!=0.0f)
			{
				x=v[i].x/mag1;
				y=v[i].y/mag1;
				v[i].x=mag1*xCoordofZRot3( x,y,c*(3.141592654f / 180.0f));
				v[i].y=mag1*yCoordofZRot3( x,y,c*(3.141592654f / 180.0f));
			}
			// add in offset
			v[i].x+=box[6];
			v[i].y+=box[7];
			v[i].z+=box[8];
			i++;
		}// eo i while

	// set vertices values to storage
	pV = (VOID*)v;
	return 1;
	}//if(mag!=0.0)
	}//if(box!= NULL)
	return 0;
}

int RotateMeshOnAnyAxisCV( float ox, float oy, float oz, // origin axis
				CUSTOMVERTEX * v, VOID * pV, int Count, // mesh info
				float a, float b, float c ) // angle rotation: x,y.z
{
	// storage values to vertices
	v = (CUSTOMVERTEX*)pV;
	// Find box and center of Mesh
	float DegRad = 3.141592654f / 180.0f;
	int i = 0;
	
		while(i<Count)
		{
			float mag1 = (float)sqrt(
				((v[i].x-ox) * (v[i].x-ox))
				+((v[i].y-oy) * (v[i].y-oy))
				+((v[i].z-oz) * (v[i].z-oz)));
		// center it on point of rotation
			v[i].x-=ox;
			v[i].y-=oy;
			v[i].z-=oz;
			
			if(mag1!=0.0)
			{
			float x,y,z;
			// x axis
			if(a!=0.0f)
			{
				y=v[i].y/mag1;
				z=v[i].z/mag1;
				v[i].y=mag1*yCoordofXRot3( y,z,a*DegRad);
				v[i].z=mag1*zCoordofXRot3( y,z,a*DegRad);
			}
			// y axis
			if(b!=0.0f)
			{
				x=v[i].x/mag1;
				z=v[i].z/mag1;
				v[i].x=mag1*xCoordofYRot3( x,z,b*DegRad);
				v[i].z=mag1*zCoordofYRot3( x,z,b*DegRad);
			}
			// z axis
			if(c!=0.0f)
			{
				x=v[i].x/mag1;
				y=v[i].y/mag1;
				v[i].x=mag1*xCoordofZRot3( x,y,c*DegRad);
				v[i].y=mag1*yCoordofZRot3( x,y,c*DegRad);
			}
			}//if(mag!=0.0)
			// add in offset
			v[i].x+=ox;
			v[i].y+=oy;
			v[i].z+=oz;
			i++;
		}// eo i while

	// set vertices values to storage
	pV = (VOID*)v;
	return 1;
}

void CCameraMoveRotationDialog::OnPaint() 
{
	CPaintDC dc(this);
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
	
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if(is3DCamVisible==false)
		{
			is3DCamVisible=true;
			
		
		CStatic* win = (CStatic*)GetDlgItem(IDC_CAMERA_MOVE_WINDOW_STATIC);
		if( SUCCEEDED( InitD3D( win->m_hWnd ) ) )
		{
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
            // Show the window
            win->ShowWindow( SW_SHOWDEFAULT );
            win->UpdateWindow( );
			
            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( true )
            {
                if( PeekMessage( &msg, m_hWnd, 0U, 0U, PM_REMOVE ) )
                {
					//CString s;
					//s.Format("\nid: %d  %d  %d", msg.message, msg.wParam, msg.lParam);
					//OutputDebugString(s);
					//No idea what 514 is
					// happens when ok button hit
					// 273 happens when corner "x" button hit

					if(msg.message == 514||msg.message==273)
						break;
										
					TranslateMessage( &msg );
                    DispatchMessage( &msg );
				}
                else
				{
					
					RotateMeshOnAnyAxisCV( 100,160,10, // origin axis
				vertices, pVertices, m_CamXYMoveRotate.m_iCount, // mesh info
				1, 0, 0 ); // angle rotation: x,y.z
				RotateOnMeshZeroAxisCV( vertices, pVertices, m_CamXYMoveRotate.m_iCount, -5, 0, 0 );
				Render();
				}
			}
       }
    }
		Cleanup();
		}

		CDialog::OnPaint();
	}
}

void CCameraMoveRotationDialog::OnOK() 
{
	
	CDialog::OnOK();
}

void CCameraMoveRotationDialog::OnCamMoveRotHelpButton() 
{
	// TODO: Add your control notification handler code here
	
}

void CCameraMoveRotationDialog::OnCameraMoveWindowStatic() 
{
	
}

void CCameraMoveRotationDialog::OnSetCamSphereButton() 
{
	CString str;
	m_CamEd1->GetWindowText( str );
	m_CamXYMoveRotate.m_fCamMove_cameraradius=(float)atof( (const char*)str.GetBuffer(str.GetLength()));
	m_CamEd2->GetWindowText( str );
	m_CamXYMoveRotate.m_fCamMove_camerarotation=(float)atof((const char*)str.GetBuffer(str.GetLength()));
	m_CamXYMoveRotate.m_fCamMove_anglerotation = m_CamXYMoveRotate.m_fCamMove_camerarotation*m_CamXYMoveRotate.m_fCamMove_degreeradian;
	m_CamXYMoveRotate.m_iCount = 0;
	SendMessage( 514, 0,0);
	is3DCamVisible = false;
	OnPaint();

}

//-----------------------------------------------------------------------------
// Name: Pick()
// Desc: Checks if mouse point hits geometry
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CCameraMoveRotationDialog::Pick()
{
    //HRESULT hr;
    D3DXVECTOR3 vPickRayDir;
    D3DXVECTOR3 vPickRayOrig;

    DWORD m_dwNumIntersections = 0L;

    // Get the pick ray from the mouse position
    if( GetCapture() )
    {
        D3DXMATRIXA16 matProj;
        g_pd3dDevice->GetTransform( D3DTS_PROJECTION, &matProj );

        POINT ptCursor;
        GetCursorPos( &ptCursor );
        ScreenToClient( &ptCursor );//m_hWnd, &ptCursor );
		/*
        // Compute the vector of the pick ray in screen space
        D3DXVECTOR3 v;
        v.x =  ( ( ( 2.0f * ptCursor.x ) / m_d3dsdBackBuffer.Width  ) - 1 ) / matProj._11;
        v.y = -( ( ( 2.0f * ptCursor.y ) / m_d3dsdBackBuffer.Height ) - 1 ) / matProj._22;
        v.z =  1.0f;

        // Get the inverse view matrix
        D3DXMATRIXA16 matView, m;
        g_pd3dDevice->GetTransform( D3DTS_VIEW, &matView );
        D3DXMatrixInverse( &m, NULL, &matView );

        // Transform the screen space pick ray into 3D space
        vPickRayDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
        vPickRayDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32;
        vPickRayDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;
        vPickRayOrig.x = m._41;
        vPickRayOrig.y = m._42;
        vPickRayOrig.z = m._43;
    }

    // Get the picked triangle
    if( GetCapture() )
    {
        LPD3DXBASEMESH          pMesh = m_pObject->GetLocalMesh();
        LPDIRECT3DVERTEXBUFFER9 pVB;
        LPDIRECT3DINDEXBUFFER9  pIB;

        pMesh->GetVertexBuffer( &pVB );
        pMesh->GetIndexBuffer( &pIB );

        WORD*      pIndices;
        D3DVERTEX*    pVertices;

        pIB->Lock( 0, 0, (void**)&pIndices, 0 );
        pVB->Lock( 0, 0, (void**)&pVertices, 0 );

        if( m_bUseD3DX )
        {
            // When calling D3DXIntersect, one can get just the closest intersection and not
            // need to work with a D3DXBUFFER.  Or, to get all intersections between the ray and 
            // the mesh, one can use a D3DXBUFFER to receive all intersections.  We show both
            // methods.
            if( m_bClosestOnly )
            {
                // Collect only the closest intersection
                BOOL bHit;
                DWORD dwFace;
                FLOAT fBary1, fBary2, fDist;
                D3DXIntersect(pMesh, &vPickRayOrig, &vPickRayDir, &bHit, &dwFace, &fBary1, &fBary2, &fDist, 
                    NULL, NULL);
                if( bHit )
                {
                    m_dwNumIntersections = 1;
                    m_IntersectionArray[0].dwFace = dwFace;
                    m_IntersectionArray[0].fBary1 = fBary1;
                    m_IntersectionArray[0].fBary2 = fBary2;
                    m_IntersectionArray[0].fDist = fDist;
                }
                else
                {
                    m_dwNumIntersections = 0;
                }
            }
            else 
            {
                // Collect all intersections
                BOOL bHit;
                LPD3DXBUFFER pBuffer = NULL;
                D3DXINTERSECTINFO* pIntersectInfoArray;
                if( FAILED( hr = D3DXIntersect(pMesh, &vPickRayOrig, &vPickRayDir, &bHit, NULL, NULL, NULL, NULL, 
                    &pBuffer, &m_dwNumIntersections) ) )
                {
                    return hr;
                }
                if( m_dwNumIntersections > 0 )
                {
                    pIntersectInfoArray = (D3DXINTERSECTINFO*)pBuffer->GetBufferPointer();
                    if( m_dwNumIntersections > MAX_INTERSECTIONS )
                        m_dwNumIntersections = MAX_INTERSECTIONS;
                    for( DWORD iIntersection = 0; iIntersection < m_dwNumIntersections; iIntersection++ )
                    {
                        m_IntersectionArray[iIntersection].dwFace = pIntersectInfoArray[iIntersection].FaceIndex;
                        m_IntersectionArray[iIntersection].fBary1 = pIntersectInfoArray[iIntersection].U;
                        m_IntersectionArray[iIntersection].fBary2 = pIntersectInfoArray[iIntersection].V;
                        m_IntersectionArray[iIntersection].fDist = pIntersectInfoArray[iIntersection].Dist;
                    }
                }
                SAFE_RELEASE( pBuffer );
            }

        }
        else
        {
            // Not using D3DX
            DWORD dwNumFaces = m_pObject->GetLocalMesh()->GetNumFaces();
            FLOAT fBary1, fBary2;
            FLOAT fDist;
            for( DWORD i=0; i<dwNumFaces; i++ )
            {
                D3DXVECTOR3 v0 = pVertices[pIndices[3*i+0]].p;
                D3DXVECTOR3 v1 = pVertices[pIndices[3*i+1]].p;
                D3DXVECTOR3 v2 = pVertices[pIndices[3*i+2]].p;

                // Check if the pick ray passes through this point
                if( IntersectTriangle( vPickRayOrig, vPickRayDir, v0, v1, v2,
                                       &fDist, &fBary1, &fBary2 ) )
                {
                    if( !m_bClosestOnly || m_dwNumIntersections == 0 || fDist < m_IntersectionArray[0].fDist )
                    {
                        if( m_bClosestOnly )
                            m_dwNumIntersections = 0;
                        m_IntersectionArray[m_dwNumIntersections].dwFace = i;
                        m_IntersectionArray[m_dwNumIntersections].fBary1 = fBary1;
                        m_IntersectionArray[m_dwNumIntersections].fBary2 = fBary2;
                        m_IntersectionArray[m_dwNumIntersections].fDist = fDist;
                        m_dwNumIntersections++;
                        if( m_dwNumIntersections == MAX_INTERSECTIONS )
                            break;
                    }
                }
            }
        }

        // Now, for each intersection, add a triangle to m_pVB and compute texture coordinates
        if( m_dwNumIntersections > 0 )
        {
            D3DVERTEX* v;
            D3DVERTEX* vThisTri;
            WORD* iThisTri;
            D3DVERTEX  v1, v2, v3;
            INTERSECTION* pIntersection;

            m_pVB->Lock( 0, 0, (void**)&v, 0 );

            for( DWORD iIntersection = 0; iIntersection < m_dwNumIntersections; iIntersection++ )
            {
                pIntersection = &m_IntersectionArray[iIntersection];

                vThisTri = &v[iIntersection * 3];
                iThisTri = &pIndices[3*pIntersection->dwFace];
                // get vertices hit
                vThisTri[0] = pVertices[iThisTri[0]];
                vThisTri[1] = pVertices[iThisTri[1]];
                vThisTri[2] = pVertices[iThisTri[2]];

                // If all you want is the vertices hit, then you are done.  In this sample, we
                // want to show how to infer texture coordinates as well, using the BaryCentric
                // coordinates supplied by D3DXIntersect
                FLOAT dtu1 = vThisTri[1].tu - vThisTri[0].tu;
                FLOAT dtu2 = vThisTri[2].tu - vThisTri[0].tu;
                FLOAT dtv1 = vThisTri[1].tv - vThisTri[0].tv;
                FLOAT dtv2 = vThisTri[2].tv - vThisTri[0].tv;
                pIntersection->tu = vThisTri[0].tu + pIntersection->fBary1 * dtu1 + pIntersection->fBary2 * dtu2;
                pIntersection->tv = vThisTri[0].tv + pIntersection->fBary1 * dtv1 + pIntersection->fBary2 * dtv2;
            }
            m_pVB->Unlock();
        }

        pVB->Unlock();
        pIB->Unlock();

        pVB->Release();
        pIB->Release();
*/
    }


    return S_OK;
}