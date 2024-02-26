#include "stdafx.h"

//#include <d3drmwin.h>

#include "resource.h"
#include <math.h>
#include "3dpic.h"
#include "geometry.h"



short CtrlKeyState  = 0;
short AltKeyState   = 0;
short ShiftKeyState = 0;
D3DVALUE scaleShrink = 0.9F;
D3DVALUE scaleGrow = 1.1F;
D3DVALUE positionValue = 1.0F;
D3DVALUE rotationValue = 0.017453293005625408F;
D3DVALUE scaleValue = 0.1F;
float SetRotX;
float SetRotY;
float SetRotZ;
float angle;


float * CalcMeshBoxAndCenter(LPDIRECT3DRMMESHBUILDER3 mb)
{
	static float box[9];
	D3DVECTOR copier;
				
		mb->GetVertex( 0, &copier );
		box[0]=copier.x;
		box[1]=copier.x;
		box[2]=copier.y;
		box[3]=copier.y;
		box[4]=copier.z;
		box[5]=copier.z;
				
		int qCount = mb->GetVertexCount();
		for(int i=1;i<qCount;i++)
		{
			mb->GetVertex( i, &copier );
			if(copier.x<box[0]){box[0]=copier.x;}
			if(copier.x>box[1]){box[1]=copier.x;}
			if(copier.y<box[2]){box[2]=copier.y;}
			if(copier.y>box[3]){box[3]=copier.y;}
			if(copier.z<box[4]){box[4]=copier.z;}
			if(copier.z>box[5]){box[5]=copier.z;}
		}

		box[6] = box[0]+((box[1]-box[0])/2);
		box[7] = box[2]+((box[3]-box[2])/2);
		box[8] = box[4]+((box[5]-box[4])/2);

	return box;
		
}
// type = 1,x 2,y 3,z 4,all
// fr is scene
void ScaleMB3(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRMFRAME3 fr, float value, float *box, int type)
{
	
	LPUNKNOWN *temp=NULL;
	DWORD num = 0;
	fr->GetVisuals( &num, temp);
	temp = (LPUNKNOWN*)malloc(num*sizeof(LPUNKNOWN));
	fr->GetVisuals( &num, temp);
	LPDIRECT3DRMMESHBUILDER3 t;
	int lastFound = 0;

	int qCount = mb->GetVertexCount();
	switch(type)
		{
		case 1:
			mb->Scale(1.1F, 1.0F, 1.0F);
			break;
		case 2:
				mb->Scale(1.0F, 1.1F, 1.0F);
			break;
		case 3:
				mb->Scale(1.0F, 1.0F, 1.1F);
			break;
		case 4:
			mb->Scale(1.1F, 1.1F, 1.1F);
			break;
		case 5:
			mb->Scale(0.9F, 1.0F, 1.0F);
			break;
		case 6:
			mb->Scale(1.0F, 0.9F, 1.0F);
			break;
		case 7:
				mb->Scale(1.0F, 1.0F, 0.9F);
			break;
		case 8:
			mb->Scale(0.9F, 0.9F, 0.9F);
			break;
		default:break;
		}
	for(int i =0;i<qCount;i++)
	{
		D3DVECTOR v;
		mb->GetVertex( i, &v );
	
		
	
	for(unsigned int j = lastFound;j<num;j++)
	{
		
		LPDIRECT3DRMVISUAL vis; 
		temp[j]->QueryInterface(IID_IDirect3DRMVisual, (void**)&vis);;
		DWORD nCnt;
		vis->GetName( &nCnt, NULL );
		char *name = (char*)malloc( nCnt*sizeof(char));
		vis->GetName( &nCnt, name );
			
	
		if(strstr(name,"")==NULL)
		{
		if(strstr(name,"finalMesh")==NULL)
		{
			int vert = atoi( name );
			if(vert = i)
			{
				lastFound=i;
				if(SUCCEEDED(vis->QueryInterface(IID_IDirect3DRMMeshBuilder3, (void **) &t)))
				{
					
					t->SetVertex( 0, 0.5F+v.x,0.5F+v.y,-0.5F+v.z);
					t->SetVertex( 1, -0.5F+v.x,0.5F+v.y,-0.5F+v.z);
					t->SetVertex( 2, 0.0F+v.x,0.0F+v.y,0.5F+v.z);
					t->SetVertex( 3, 0.0F+v.x,-0.5F+v.y,-0.5F+v.z);
					t->Release();
				}
				break;

			}
		}
		}
		vis->Release();
	}//eo j for
	}// eo i for

}


////////////////////////////////////////////////
//// cam functions
////////////////////////////////////////////////
float yCoordofXRot2( float x, float z,  float a, float ctr){
	
	double ra = 0;
		double rb = 0;
		double rx = 0;
		
			if(x == 0){ra = 0;}else{
		        ra =  x* cos(a);
			}
			if(z == 0){rb = 0;}else{
				rb = z*sin(a);}
		rx =  ra + rb + ctr;  
			
		return (float)rx;
	}
//////////////////////////
float zCoordofXRot2(float x, float z, float a, float ctr){
	
	double ra = 0;
		double rb = 0;
		double rz = 0;
		
		if(x == 0){ra = 0;}
			else{
		        ra =  x*sin(a);
			}
			if(z == 0){rb = 0;}
			else{
				rb = z*cos(a);}
		rz =  (rb - ra) + ctr;  
		
			return (float)rz;
    }
////////////////////////////////////////////////
float xCoordofYRot2(float x, float z, float a, float ctr){
        
		double ra = 0;
		double rb = 0;
		double rx = 0;
		
			if(x == 0){ra = 0;}else{
		        ra =  x* cos(a);
			}
			if(z == 0){rb = 0;}else{
				rb = z*sin(a);}
		rx =  ra + rb + ctr;  
			
		return (float)rx;
    }
	
float zCoordofYRot2(float x, float z, float a, float ctr){
		double ra = 0;
		double rb = 0;
		double rz = 0;
		
		if(x == 0){ra = 0;}
			else{
		        ra =  x*sin(a);
			}
			if(z == 0){rb = 0;}
			else{
				rb = z*cos(a);}
		rz =  (rb - ra) + ctr;  
		
			return (float)rz;
    }
	
float xCoordofZRot2(float x, float y,  float a, float ctr){
       
		double ra = 0;
		double rb = 0;
		double ry = 0;
		
			if(x == 0){ra = 0;}else{
		        ra =  x* cos(a);
			}
			if(y == 0){rb = 0;}else{
				rb =  y*(-sin(a));}
		ry =  ra + rb + ctr;  
		
		return (float)ry;
	}
	
float yCoordofZRot2(float x, float y, float a, float ctr){
       
			double ra = 0;
		double rb = 0;
		double ry = 0;
		
			if(x == 0){ra = 0;}else{
		        ra =  x* sin(a);
			}
			if(y == 0){rb = 0;}else{
				rb = y*cos(a);}
		ry =  ra + rb + ctr;  
		
		return (float)ry;
    }
	
float multiplycoordinate2(float n, float ndelta){
		float fl=0;
		if(n==0){fl=0;}
		else{ 
			if(ndelta==0){fl=0;}
			else{
				fl = n * ndelta;
			}}
		return fl;
}
void CWin3D::GridVerticesRotationGrid()
{


	D3DVECTOR *veb=NULL;
	DWORD lpdwCount=NULL;
	m_SceneObjects->grid->GetVertices(0,  &lpdwCount,  NULL);
	veb = new D3DVECTOR[lpdwCount];
	
	m_SceneObjects->grid->GetVertices(0,  &lpdwCount,  veb);
	
	
		D3DVECTOR ctr;
		m_SceneObjects->m_camera->GetPosition(NULL, &ctr);

		unsigned int i=0;						 
		if(SetRotX != 0.1F){
		while(i<lpdwCount+1){
			float x = veb[i].x;
			float y = veb[i].y - ctr.y;
			float z = veb[i].z - ctr.z;
			
			float yy = yCoordofXRot2(y,z, SetRotX, ctr.y);
		    float zz = zCoordofXRot2(y,z, SetRotX, ctr.z);
			
			m_SceneObjects->grid->SetVertex( i, x, yy, zz );
			veb[i].y = yy;
			veb[i].z = zz;
			i++;
		}}
		
		else if(SetRotY != 0.1F){
			while(i<lpdwCount+1){
			float x = veb[i].x - ctr.x;
			float y = veb[i].y;
			float z = veb[i].z - ctr.z;
			
			float xx = xCoordofYRot2(x,z, SetRotY, ctr.x);
			float zz = zCoordofYRot2(x,z, SetRotY, ctr.z);
			
			m_SceneObjects->grid->SetVertex( i, xx, y, zz );
			veb[i].x = xx;
			veb[i].z = zz;
			i++;
		}}
		else if(SetRotZ != 0.1F){
		while(i<lpdwCount+1){
			float x = veb[i].x - ctr.x;
			float y = veb[i].y - ctr.y;
			float z = veb[i].z;
			
			float xx = xCoordofZRot2(x, y, SetRotZ, ctr.x);
			float yy = yCoordofZRot2(x, y, SetRotZ, ctr.y);
			
			m_SceneObjects->grid->SetVertex(i, xx, yy, z );
			veb[i].x = xx;
			veb[i].y = yy;
			i++;
		}}
			SetRotX = 0.1F;
		    SetRotY = 0.1F;
		    SetRotZ = 0.1F;	
		
}
void doForwardBack( LPDIRECT3DRMFRAME3 fr, LPDIRECT3DRMFRAME3 grid, D3DVALUE value)
{
	D3DVECTOR dir, adir, up, right;

	    fr->GetOrientation(NULL, &dir, &up);
	    D3DRMVectorCrossProduct(&right, &up, &dir);
		D3DRMVectorScale(&adir, &dir, value);
	    fr->SetVelocity(NULL, adir.x, adir.y, adir.z, FALSE);
}

void doBack( LPDIRECT3DRMFRAME3 fr, LPDIRECT3DRMFRAME3 grid, D3DVALUE value)
{
	D3DVECTOR dir, adir, up, right;

	    fr->GetOrientation(NULL, &dir, &up);
	    D3DRMVectorCrossProduct(&right, &up, &dir);
		D3DRMVectorScale(&adir, &dir, value);
	    fr->SetVelocity(NULL, adir.x, adir.y, adir.z, FALSE);
				
}
	
void doZSpin( LPDIRECT3DRMFRAME3 fr, D3DVALUE arg, D3DVALUE z)
{
		fr->SetRotation(NULL,0,0,1,arg);
			
}
void spinY( LPDIRECT3DRMFRAME3 fr, D3DVALUE arg, D3DVALUE y)
{
		fr->SetRotation(NULL,0,1,0,-arg);
		SetRotY = SetRotY - y;
		
}
	
	
void doCamZero(LPDIRECT3DRMFRAME3 fr, float m_fCameraOffset)
{
		fr->SetPosition(NULL,0,0,-m_fCameraOffset);
		SetRotZ = SetRotZ + 1.0F;
}
	
	
	
void doXSpin(LPDIRECT3DRMFRAME3 fr,  D3DVALUE arg, D3DVALUE x)
{
		fr->SetRotation(NULL,1,0,0,arg);
		SetRotX = SetRotX + x;
}


void walkUpDown( LPDIRECT3DRMFRAME3 fr, D3DVALUE value)
{
		D3DVECTOR dir, adir, up, right;

	    fr->GetOrientation(NULL, &dir, &up);
	    D3DRMVectorCrossProduct(&right, &up, &dir);
		D3DRMVectorScale(&adir, &up, value);
	    fr->SetVelocity(NULL, adir.x, adir.y, adir.z, FALSE);
		D3DVECTOR pos;
		fr->GetPosition(NULL, &pos);
}
	
void walkLeftRight( LPDIRECT3DRMFRAME3 fr, D3DVALUE value)
{
	/*
		fr->SetRotation(NULL,0,0,0,0);
        fr->SetVelocity(fr, value, 0,0, 0);
		D3DVECTOR pos;
		fr->GetPosition(NULL, &pos);
		*/
		D3DVECTOR dir, adir, up, right;
	    fr->GetOrientation(NULL, &dir, &up);
	    D3DRMVectorCrossProduct(&right, &up, &dir);
		D3DRMVectorScale(&adir, &right, value);
	    fr->SetVelocity(NULL, adir.x, adir.y, adir.z, FALSE);
		D3DVECTOR pos;
		fr->GetPosition(NULL, &pos);
}

void StopWalk(LPDIRECT3DRMFRAME3 fr)
{
	
		fr->SetRotation(NULL,0,1,0,0);
		fr->SetVelocity(NULL, 0, 0,0, 0);
	
	
}

void DoScale( LPDIRECT3DRMVISUAL sVisual, LPDIRECT3DRMFRAME3 fr, unsigned int type, D3DVALUE delta)
{
	if(CtrlKeyState==1){
	if(fr)
	{
		if(AltKeyState==1){
		switch(type)
		{
		case 1://x
			{
				fr->AddScale(D3DRMCOMBINE_BEFORE, delta, D3DVAL(1.0), D3DVAL(1.0));
				
			}
			break;
		case 2://y
			{
				fr->AddScale(D3DRMCOMBINE_BEFORE, D3DVAL(1.0), delta, D3DVAL(1.0));
				
			}
			break;
		case 3://z
			{
				fr->AddScale(D3DRMCOMBINE_BEFORE, D3DVAL(1.0), D3DVAL(1.0), delta);
				
			}
			break;
		case 4://all
			{
				fr->AddScale(D3DRMCOMBINE_BEFORE, delta, delta, delta);
				
			}
			break;
		}//eoswitch
		
		}//eoaltkeystate
	}//eocontrolkeystate
	}
}

void moveFocusWithCamera(LPDIRECT3DRMFRAME3 m_FocusFrame, LPDIRECT3DRMFRAME3 camera, LPDIRECT3DRMFRAME3 scene, float m_fCameraOffset)
{
	if(m_FocusFrame)
		{
			m_FocusFrame->SetPosition(camera, 0.0F, 0.0F, m_fCameraOffset);
				D3DVECTOR origin;
			scene->GetPosition(m_FocusFrame, &origin);
			origin.x = -origin.x;
			origin.y = -origin.y;
			origin.z = -origin.z;
		}	
}

float * cameraLoc( float *camData, LPDIRECT3DRMFRAME3 m_camera, LPDIRECT3DRMFRAME3 scene)
{
	D3DVECTOR cpos;
	scene->GetPosition( m_camera, &cpos);
	D3DVECTOR crot;
	float theta[1];
	scene->GetRotation(m_camera, &crot, theta);
	camData[7];
	camData[0] = cpos.x;
	camData[1] = cpos.y;
	camData[2] = cpos.z;
	camData[3] = crot.x;
	camData[4] = crot.y;
	camData[5] = crot.z;
	camData[6] = theta[0];
	
	return camData;
	//o.statusBarPanel3.setText(o.oVars.cameraView+" pos: x: " + Float.toString( cpos.x) + " y: " + Float.toString(cpos.y) + " z: " + Float.toString( cpos.z));
}

void selFrameLoc( float *frameData, LPDIRECT3DRMFRAME3 fr, LPDIRECT3DRMFRAME3 scene)
{
	D3DVECTOR cpos;
	scene->GetPosition( fr, &cpos);
	D3DVECTOR crot;
	float theta[1];
	scene->GetRotation(fr, &crot, theta);
	frameData[7];
	frameData[0] = cpos.x;
	frameData[1] = cpos.y;
	frameData[2] = cpos.z;
	frameData[3] = crot.x;
	frameData[4] = crot.y;
	frameData[5] = crot.z;
	frameData[6] = theta[0];
}
D3DVECTOR CWin3D::CamDir( float x, float y, float z)
{
	
    D3DRMRAY rmRay;
    D3DRMVECTOR4D v4Src;

    rmRay.dvPos.x=x;
	rmRay.dvPos.y=y;
	rmRay.dvPos.z=z;

    v4Src.x = (float)(175);
    v4Src.y = (float)(175);
    v4Src.z = 0.0f;
    v4Src.w = 1.0f;
	
    m_SceneObjects->m_view->InverseTransform(&rmRay.dvDir, &v4Src);

	
			LPDIRECT3DRMFRAME3 pFrame3 = m_SceneObjects->gridFrame;
			
					
			D3DVECTOR pos2;
			m_SceneObjects->m_view->InverseTransform( &pos2, &v4Src);
									
			LPDIRECT3DRMFACE2 fc;
			GetD3DRM()->CreateFace(&fc);
			D3DVECTOR v1,v2,v3;
			m_SceneObjects->grid->GetVertex( 0, &v1 );
			m_SceneObjects->grid->GetVertex( 8, &v2 );
			m_SceneObjects->grid->GetVertex( 80, &v3 );
			fc->AddVertex(v1.x, v1.y, v1.z);
			fc->AddVertex(v2.x, v2.y, v2.z);
			fc->AddVertex(v3.x, v3.y, v3.z);
			
			int fvCnt = 3;
			double distxyz=0.0;
			Geometry geo;
				D3DVECTOR g=geo.CenterOfFace(fc);
						
			D3DVECTOR faceCenter;
			//transformtoworldcoord
			pFrame3->Transform( &faceCenter, &g );
						
			D3DVECTOR faceCenterDir = geo.directionBetweenPoints( rmRay.dvPos, faceCenter);
			CString s;
			s.Format(L"\n%.6f  %.6f   %.6f", faceCenterDir.x, faceCenterDir.y, faceCenterDir.z);
//			OutputDebugString(s);
			geo.~Geometry();
		return faceCenterDir;
}

#define PI2 6.28318f
#define XPOS 2.0f
#define INTERPOLATE_STEP 0.05f


/*
void CWin3D::circleCamOnAxis( int direction, float m_fCameraOffset)
	{

	D3DVECTOR origin, pos, n;
	    m_SceneObjects->m_camera->GetPosition(NULL, &pos);
       	m_SceneObjects->gridFrame->GetPosition(NULL, &origin);
				
					
		float x,y,z,xx,yy,zz;
		float r = m_fCameraRotationValue;//0.017453293005625408F*5.0F;
		D3DVECTOR result,dir;
				
		m_SceneObjects->m_camera->GetOrientation(NULL, &dir, &result);

		m_SceneObjects->m_camera->SetOrientation(NULL, D3DVAL(XPOS), D3DVAL(0),
                               D3DVAL(0), result.x,result.y,result.z);


		
		switch(direction)
		{
		case 1:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			yy = yCoordofXRot2(y,z, -r, origin.y);
		    zz = zCoordofXRot2(y,z, -r, origin.z);
			m_SceneObjects->m_camera->SetPosition(NULL, x, yy, zz);
			n.x = -x+origin.x;
			n.y = -yy+origin.y;
			n.z = -zz + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			}		
			break;
		case 2:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			
			yy = yCoordofXRot2(y,z, r, origin.y);
		    zz = zCoordofXRot2(y,z, r, origin.z);
			m_SceneObjects->m_camera->SetPosition(NULL, x, yy, zz);
			n.x = -x+origin.x;
			n.y = -yy+origin.y;
			n.z = -zz + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			}
			break;
		case 3:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			
			xx = xCoordofYRot2(x,z, -r, origin.x);
		    zz = zCoordofYRot2(x,z, -r, origin.z);
				
			m_SceneObjects->m_camera->SetPosition(NULL, xx, y, zz);
			n.x = -xx+origin.x;
			n.y = -y+origin.y;
			n.z = -zz + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			
			}
			break;
		case 4:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			
			xx = xCoordofYRot2(x,z, r, origin.x);
		    zz = zCoordofYRot2(x,z, r, origin.z);
			m_SceneObjects->m_camera->SetPosition(NULL, xx, y, zz);
			n.x = -xx+origin.x;
			n.y = -y+origin.y;
			n.z = -zz + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			}			
			break; 
		case 5:
			{
		
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;

			 xx = xCoordofZRot2(x,y, -r, origin.x);
		     yy = yCoordofZRot2(x,y, -r, origin.y);
			m_SceneObjects->m_camera->SetPosition(NULL, xx, yy, z);
			n.x = -xx+origin.x;
			n.y = -yy+origin.y;
			n.z = -z + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			}
			break;
		case 6:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			
			 xx = xCoordofZRot2(x,y, r, origin.x);
		     yy = yCoordofZRot2(x,y, r, origin.y);
			m_SceneObjects->m_camera->SetPosition(NULL, xx, yy, z);
			m_SceneObjects->m_camera->SetOrientation(NULL, -xx+origin.x, -yy+origin.y, z+origin.z, result.x, result.y, result.z);
			n.x = -xx+origin.x;
			n.y = -yy+origin.y;
			n.z = -z + origin.z;
			D3DRMVectorNormalize( &n );
			m_SceneObjects->m_camera->SetOrientation(NULL,  n.x, n.y, n.z, result.x, result.y, result.z);
			}
			break;
		default:	
			break;
		}//eoswitch
		
}
*/
void CWin3D::circleCamOnAxis( int direction, float m_fCameraOffset )
{
	D3DVECTOR o,dir,up,turnDeg,turn90,d;
	m_SceneObjects->gridFrame->GetPosition(NULL, &o);
	m_SceneObjects->m_camera->GetOrientation(NULL, &dir, &up);
	float DegRad = m_fCameraRotationValue;//(3.141592654f / 180.0f);
	float angle=0;
	switch(direction)
	{
	case 1:
		{
			angle = -DegRad;
			d = dir;
			m_SceneObjects->gridFrame->GetOrientation(NULL, &dir, &up );
			D3DRMVectorCrossProduct(&turn90, &up, &dir);
			D3DRMVectorRotate( &turnDeg, &up, &turn90, angle);
			D3DRMVectorRotate( &d, &dir, &turn90, angle);
			m_SceneObjects->m_camera->SetPosition( NULL, (m_fCameraOffset*-d.x)+o.x, (m_fCameraOffset*-d.y)+o.y, (m_fCameraOffset*-d.z)+o.z);
			m_SceneObjects->m_camera->SetOrientation( NULL, d.x, d.y, d.z, turnDeg.x, turnDeg.y, turnDeg.z );
		}
		break;
	case 2:
		{
			angle = DegRad;
			d = dir;
			m_SceneObjects->gridFrame->GetOrientation(NULL, &dir, &up );
			D3DRMVectorCrossProduct(&turn90, &up, &dir);
			D3DRMVectorRotate( &turnDeg, &up, &turn90, angle);
			D3DRMVectorRotate( &d, &dir, &turn90, angle);
			m_SceneObjects->m_camera->SetPosition( NULL, (m_fCameraOffset*-d.x)+o.x, (m_fCameraOffset*-d.y)+o.y, (m_fCameraOffset*-d.z)+o.z);
			m_SceneObjects->m_camera->SetOrientation( NULL, d.x, d.y, d.z, turnDeg.x, turnDeg.y, turnDeg.z );
		}
		break;
	case 3:
		{
			angle = -DegRad;
			m_SceneObjects->gridFrame->GetOrientation(NULL, &dir, &up );
			D3DRMVectorRotate( &turnDeg, &dir, &up, angle);
			m_SceneObjects->m_camera->SetPosition( NULL, (m_fCameraOffset*-turnDeg.x)+o.x, (m_fCameraOffset*-turnDeg.y)+o.y, (m_fCameraOffset*-turnDeg.z)+o.z);
			m_SceneObjects->m_camera->SetOrientation( NULL, turnDeg.x, turnDeg.y, turnDeg.z, up.x, up.y, up.z );
		}
		break;
	case 4:
		{
			angle = DegRad;
			m_SceneObjects->gridFrame->GetOrientation(NULL, &dir, &up );
			D3DRMVectorRotate( &turnDeg, &dir, &up, angle);
			m_SceneObjects->m_camera->SetPosition( NULL, (m_fCameraOffset*-turnDeg.x)+o.x, (m_fCameraOffset*-turnDeg.y)+o.y, (m_fCameraOffset*-turnDeg.z)+o.z);
			m_SceneObjects->m_camera->SetOrientation( NULL, turnDeg.x, turnDeg.y, turnDeg.z, up.x, up.y, up.z );
		}
		break;
	case 5:
		{
			angle = -DegRad;
			D3DRMVectorRotate( &turnDeg, &up, &dir, angle);
			m_SceneObjects->m_camera->SetOrientation(NULL,  dir.x, dir.y, dir.z, turnDeg.x, turnDeg.y, turnDeg.z);
		}
		break;
	case 6:
		{
			angle = DegRad;
			D3DRMVectorRotate( &turnDeg, &up, &dir, angle);
			m_SceneObjects->m_camera->SetOrientation(NULL,  dir.x, dir.y, dir.z, turnDeg.x, turnDeg.y, turnDeg.z);
		}
		break;
	}// eo switch
}
		
void CWin3D::RotateMesh( int direction, float m_fCameraOffset)
{

	int cnt = tempMeshBld->GetVertexCount();
	D3DVECTOR origin, pos, n;
	float *box=CalcMeshBoxAndCenter(tempMeshBld);
	origin.x=box[6];origin.y=box[7];origin.z=box[8];
	for(int i = 0;i<cnt;i++)
	{
	
	    
				tempMeshBld->GetVertex( i, &pos);
					
		float x,y,z,xx,yy,zz;
		float r = m_fCameraRotationValue;//0.017453293005625408F*5.0F;
	
				
				
		switch(direction)
		{
		case 1:
			{
			x = pos.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			yy = yCoordofXRot2(y,z, -r, origin.y);
		    zz = zCoordofXRot2(y,z, -r, origin.z);
			n.x = x;
			n.y = yy;
			n.z = zz;
			}		
			break;
		case 2:
			{
			x = pos.x;
			y = pos.y - origin.y;
			z = pos.z - origin.z;
			
			yy = yCoordofXRot2(y,z, r, origin.y);
		    zz = zCoordofXRot2(y,z, r, origin.z);
			n.x = x;
			n.y = yy;
			n.z = zz;
			}
			break;
		case 3:
			{
			x = pos.x - origin.x;
			y = pos.y;
			z = pos.z - origin.z;
			
			xx = xCoordofYRot2(x,z, -r, origin.x);
		    zz = zCoordofYRot2(x,z, -r, origin.z);
				
			n.x = xx;
			n.y = y;
			n.z = zz;
			}
			break;
		case 4:
			{
			x = pos.x - origin.x;
			y = pos.y;
			z = pos.z - origin.z;
			
			xx = xCoordofYRot2(x,z, r, origin.x);
		    zz = zCoordofYRot2(x,z, r, origin.z);
			n.x = xx;
			n.y = y;
			n.z = zz;
			}			
			break; 
		case 5:
			{
		
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z;

			 xx = xCoordofZRot2(x,y, -r, origin.x);
		     yy = yCoordofZRot2(x,y, -r, origin.y);
			n.x = xx;
			n.y = yy;
			n.z = z;
			}
			break;
		case 6:
			{
			x = pos.x - origin.x;
			y = pos.y - origin.y;
			z = pos.z;
			
			 xx = xCoordofZRot2(x,y, r, origin.x);
		     yy = yCoordofZRot2(x,y, r, origin.y);
			n.x = xx;
			n.y = yy;
			n.z = z;
			}
			break;
		default:	
			break;
		}//eoswitch
		tempMeshBld->SetVertex( i, n.x,n.y,n.z);
		}

}
////////////////
void CWin3D::DoKeyDown(UINT wparam,  HWND hwnd, LPDIRECT3DRMFRAME3 sFrame, LPDIRECT3DRMVISUAL sVisual)
{
		D3DVECTOR dir, up, right;

	    m_SceneObjects->m_camera->GetOrientation(m_scene, &dir, &up);
	    D3DRMVectorCrossProduct(&right, &up, &dir);
	    up.x /= D3DVAL(4.0);
	    up.y /= D3DVAL(4.0);
	    up.z /= D3DVAL(4.0);
	    right.x /= D3DVAL(4.0);
	    right.y /= D3DVAL(4.0);
	    right.z /= D3DVAL(4.0);

		switch (wparam)
	    {
		case VK_CONTROL:{CtrlKeyState=1;}break;
		case VK_MENU:{AltKeyState=1;}break;
		case VK_SHIFT:{ShiftKeyState=1;}break;
	    	
		case VK_INSERT:
			//MessageBox(NULL,"","",MB_OK);
			break;
		case VK_END://ID_NONUM1:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
				//DoScale( sVisual, sFrame, 1, scaleShrink);
				
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 1);
			}else if(CtrlKeyState==1&&AltKeyState==1){
				
				
			}else if(CtrlKeyState==1&&AltKeyState==0){
				doXSpin(m_SceneObjects->m_camera, m_fCameraRotationValue, 1.0F);
			}}
			break;
		case VK_DOWN://ID_NONUM2:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
			//DoScale( sVisual, sFrame, 4, scaleShrink);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 8);
			}else if(CtrlKeyState==1&&AltKeyState==1){
				//doForwardBack(  sFrame, -positionValue);//doForwardBackSelFr( sFrame, -positionValue);
				}else if(CtrlKeyState==1&&AltKeyState==0){doBack(  m_SceneObjects->m_camera, m_SceneObjects->gridFrame, -m_fCameraSpeed);
			}}
			break;
		case VK_NEXT://ID_NONUM3:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
			//DoScale( sVisual, sFrame, 1, scaleGrow);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 5);
			}else if(CtrlKeyState==1&&AltKeyState==1){
			//doXSpinSelFr(sFrame,  -rotationValue, -1.0F);
				
			}else if(CtrlKeyState==1&&AltKeyState==0){doXSpin(m_SceneObjects->m_camera, -m_fCameraRotationValue, -1.0F);
			}}
			break;
		case VK_LEFT:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
			//DoScale( sVisual, sFrame, 2, scaleShrink);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 2);
			}else if(CtrlKeyState==1&&AltKeyState==1){
			//spinYSelFr(sFrame,  rotationValue, 1.0F);
				
			}else if(CtrlKeyState==1&&AltKeyState==0){spinY(m_SceneObjects->m_camera, m_fCameraRotationValue, 1.0F);
			}}
			break;
		case VK_CLEAR:
			doCamZero(m_SceneObjects->m_camera, m_fCameraOffset);
			break;
		case VK_RIGHT:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
			//DoScale( sVisual, sFrame, 2, scaleGrow);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 6);
			}else if(CtrlKeyState==1&&AltKeyState==1){
				/*spinYSelFr(sFrame,  -rotationValue, -1.0F);*/
				
			}else if(CtrlKeyState==1&&AltKeyState==0){spinY(m_SceneObjects->m_camera, -m_fCameraRotationValue, -1.0F);
			}}
			break;
		case VK_HOME:
			{
				if(CtrlKeyState==1&&ShiftKeyState==1){
				//DoScale( sVisual, sFrame, 3, scaleShrink);
					ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 3);
			}else if(CtrlKeyState==1&&AltKeyState==1){
			//doZSpinSelFr(sFrame,  -rotationValue, -1.0F);
					
			}else if(CtrlKeyState==1&&AltKeyState==0){doZSpin(m_SceneObjects->m_camera, -m_fCameraRotationValue, -1.0F);
			}}
			break;
		case VK_UP:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
			//DoScale( sVisual, sFrame, 4, scaleGrow);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 4);
			}else if(CtrlKeyState==1&&AltKeyState==1){
				//doForwardBack(  sFrame, positionValue);//doForwardBackSelFr( sFrame, positionValue);
			}else if(CtrlKeyState==1&&AltKeyState==0){
				doForwardBack(  m_SceneObjects->m_camera, m_SceneObjects->gridFrame, m_fCameraSpeed);
				
			}}
			break;
		case VK_PRIOR:
			{if(CtrlKeyState==1&&ShiftKeyState==1){
				//DoScale( sVisual, sFrame, 3, scaleGrow);
				ScaleMB3( m_SceneObjects->finalMesh, m_scene, 1.0F, CalcMeshBoxAndCenter( m_SceneObjects->finalMesh ), 7);
			}else if(CtrlKeyState==1&&AltKeyState==1){
			//doZSpinSelFr(sFrame,  rotationValue, 1.0F);
				
			}else if(CtrlKeyState==1&&AltKeyState==0){doZSpin(m_SceneObjects->m_camera, m_fCameraRotationValue, 1.0F);
			}}
			break;
		case 'Z'://add animation
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 5, m_fCameraOffset );
				}
				
			}
			break;
		case 'X'://add animation
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 6, m_fCameraOffset );
				}
				
			}
			break;
		case 'A'://add animation
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 3, m_fCameraOffset );
				}
				
			}
			break;
		case 'S'://add animation
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 4, m_fCameraOffset );
				}
				
			}
			break;
		case 'Q':
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 1, m_fCameraOffset );
				}
			}
			break;
		case 'W':
			{
				if(CtrlKeyState==1&&AltKeyState==0){
			
				//	RotateMesh( 2, m_fCameraOffset );
				}
			}
			break;
		case 'U'://left:
			{	if(CtrlKeyState==1 && AltKeyState==0){
			 walkLeftRight(  m_SceneObjects->m_camera, -m_fCameraSpeed);
			 }else if(CtrlKeyState==1 && AltKeyState==1){
			 walkLeftRight(  sFrame, -positionValue);
			 }}
			break;
		case 'J'://right:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				walkLeftRight( m_SceneObjects->m_camera, m_fCameraSpeed);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 walkLeftRight(  sFrame, positionValue);
			 }}
			break;
		case 'K'://down:
			{	if(CtrlKeyState==1 && AltKeyState==0){
			walkUpDown( m_SceneObjects->m_camera, m_fCameraSpeed);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 walkUpDown(  sFrame, positionValue);
			 }}
			break;
		case 'I'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
			walkUpDown( m_SceneObjects->m_camera, -m_fCameraSpeed);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 walkUpDown(  sFrame, -positionValue);
			}}
			break;
		///// camrot
		case 'E'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 1, m_fCameraOffset);//circleFrameOnAxis( 1);
				//SetRotX=rotationValue;
				//GridVerticesRotationGrid();
				//doXSpin( gridFrame,-m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
				circleCamOnAxis( 1, m_fCameraOffset);
			 
			}}
			break;
		case 'R'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 2, m_fCameraOffset);//circleFrameOnAxis( 2);
				//doXSpin( gridFrame,m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 circleCamOnAxis( 2, m_fCameraOffset);
			}}
			break;
		case 'D'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 3, m_fCameraOffset);//circleFrameOnAxis( 3);
				//spinY( gridFrame,-m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 circleCamOnAxis( 3, m_fCameraOffset);
			}}
			break;
		case 'F'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 4, m_fCameraOffset);//circleFrameOnAxis( 4);
				//spinY( gridFrame,m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 circleCamOnAxis( 4, m_fCameraOffset);
			}}
			break;
		case 'C'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 5, m_fCameraOffset);//circleFrameOnAxis( 5);
				//doZSpin( gridFrame,-m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 circleCamOnAxis( 5, m_fCameraOffset);
			}}
			break;
		case 'V'://up:
			{	if(CtrlKeyState==1 && AltKeyState==0){
				circleCamOnAxis( 6, m_fCameraOffset);//circleFrameOnAxis( 6);
				//doZSpin( gridFrame,m_fCameraRotationValue, -1.0F);
			}else if(CtrlKeyState==1 && AltKeyState==1){
			 circleCamOnAxis( 6, m_fCameraOffset);
			}}
			break;
			//////
		case 'G':
			{	if(CtrlKeyState==1 && AltKeyState==0){
				//m_bGroupOrSingleSelectFlag = TRUE;
				
			}else if(CtrlKeyState==1 && AltKeyState==1){
				//m_bGroupOrSingleSelectFlag = FALSE;
			}}break;
		
		
		case 48://ID_ALT0:
			{	if(CtrlKeyState==1){
			m_fCameraOffset=81.0F;
			}}
			break;
			
		case 49://front cam view
			{	if(CtrlKeyState==1){
			m_SceneObjects->m_camera->SetPosition( NULL,0.0F,0.0F, -m_fCameraOffset);
			m_SceneObjects->m_camera->LookAt( m_scene, NULL, D3DRMCONSTRAIN_Z );
			m_cameraMODE = CAMFRONT;
			}}
			break;
		case 50://back cam view
			{
			if(CtrlKeyState==1)
			{
			m_SceneObjects->m_camera->SetPosition( NULL,0.0F,0.0F, m_fCameraOffset);
			m_SceneObjects->m_camera->LookAt( m_scene, NULL, D3DRMCONSTRAIN_Z );
			m_cameraMODE = CAMBACK;
			}}
			break;
		case 51://left cam view
			{if(CtrlKeyState==1){
			m_SceneObjects->m_camera->SetPosition( NULL,-m_fCameraOffset,0.0F,0.0F);
			m_SceneObjects->m_camera->LookAt( m_scene,NULL, D3DRMCONSTRAIN_X );
			m_cameraMODE = CAMLEFT;
			}}
			break;
		case 52://right cam view
			{	if(CtrlKeyState==1){
			m_SceneObjects->m_camera->SetPosition( NULL,m_fCameraOffset,0.0F,0.0F);
			m_SceneObjects->m_camera->LookAt( m_scene,NULL, D3DRMCONSTRAIN_X );
			m_SceneObjects->m_camera->SetRotation( NULL, 3.141592583F,0.0F,0.0F, 1.0F);
			m_SceneObjects->m_camera->Move( 3.141592583F);
			m_SceneObjects->m_camera->SetRotation(NULL,0.0F,1.0F,0.0F,0.0F);
            m_SceneObjects->m_camera->SetVelocity( NULL,0.0F,0.0F,0.0F, FALSE);
			m_cameraMODE = CAMRIGHT;
			}}
			break;
		case 53://top cam view
			{	if(CtrlKeyState==1){
			m_SceneObjects->m_camera->SetPosition( NULL,0.0F,-m_fCameraOffset,0.0F);
			m_SceneObjects->m_camera->LookAt( m_scene,NULL, D3DRMCONSTRAIN_Y );
			m_cameraMODE = CAMTOP;
			}}
			break;
		case 54://bottom cam view
			{	if(CtrlKeyState==1){
			m_SceneObjects->m_camera->SetPosition( NULL,0.0F,m_fCameraOffset,0.0F);
			m_SceneObjects->m_camera->LookAt( m_scene,NULL, D3DRMCONSTRAIN_Y );
			m_cameraMODE = CAMBOTTOM;
			}}
			break;
		case 55:
			break;
		case 56:
			{
				//DialogBox( (HINSTANCE) GetWindowLong(win, GWL_HINSTANCE),"MOVEDLG", win, (DLGPROC)MoveDlgProc);
			}
			break;
		case 57:
				//DialogBox( (HINSTANCE) GetWindowLong(win, GWL_HINSTANCE),"CAMERADLG", win, (DLGPROC)CameraDlgProc);
			break;
		case VK_F4:
			{
				if(AltKeyState==1)
				{
				int choice=MessageBox( NULL,L"Exit the 3D Sculptor?",L"Safety Check", MB_OKCANCEL);
				if(choice==IDOK)
				{PostQuitMessage(0);}}}
			
			break;
		case 188:
			{
				
				if(CtrlKeyState==1){
					/*
				CString str;
				HWND hand;
				hand=GetDlgItem( hwnd, IDC_POINTSPACING_STATIC);
				char lp[20];
				GetWindowText( hand, lp, 20 );
				str.Format("%s",lp);
				int l = str.GetLength();
				str.Delete(0,9);
				m_fPointSpace=(float)atof( str.GetBuffer(str.GetLength()));
				m_fPointSpace-=0.02F;
				
				str.Format("Spacing: %.6f", m_fPointSpace); 
				SetWindowText(hand,str);
				*/
				}
			}
			break;
		case 190:
			{
				if(CtrlKeyState==1){
					/*
				CString str;
				HWND hand;
				hand=GetDlgItem( hwnd, IDC_POINTSPACING_STATIC);
				char lp[20];
				GetWindowText( hand, lp, 20 );
				str.Format("%s",lp);
				int l = str.GetLength();
				str.Delete(0,9);
				m_fPointSpace=(float)atof( str.GetBuffer(str.GetLength()));
				m_fPointSpace+=0.02F;
				
				str.Format("Spacing: %.6f", m_fPointSpace); 
				SetWindowText(hand,str);
				*/
				}
			}
			break;
		case 186:
			{
				
				if(CtrlKeyState==1){
				float f = m_fCameraSpeed-0.02F;
				if(f>0.001F){
				CString str;
				m_fCameraSpeed-=0.02F;
				//HWND hand = GetDlgItem(hwnd, IDC_CAMSPEED_STATIC);
				//str.Format("Camera:       Speed:   %.6f", m_fCameraSpeed); 
				//SetWindowText(hand,str);
				}
				}
			}
			break;
		case 222:
			{
				if(CtrlKeyState==1){
				CString str;
				m_fCameraSpeed+=0.02F;
				//HWND hand = GetDlgItem(hwnd, IDC_CAMSPEED_STATIC);
				//str.Format("Camera:       Speed:   %.6f", m_fCameraSpeed); 
				//SetWindowText(hand,str);
				}
			}
			break;
		case 219:
			{
				
				if(CtrlKeyState==1){
					float f = (m_fCameraRotationValue-0.017453293005625408F)/0.017453293005625408F;
					if(f>1){
						CString str;
						m_fCameraRotationValue-=0.017453293005625408F;
						//HWND hand = GetDlgItem(hwnd, IDC_CAMROT_STATIC);
						//str.Format("Camera:       Rotation: %.6f", m_fCameraRotationValue/0.017453293005625408F); 
						//SetWindowText(hand,str);
					}
				}
			}
			break;
		case 221:
			{
				if(CtrlKeyState==1){
					float f = (m_fCameraRotationValue+0.017453293005625408F)/0.017453293005625408F;
					if(f<181){
						CString str;			
						m_fCameraRotationValue+=0.017453293005625408F;
						//HWND hand = GetDlgItem(hwnd, IDC_CAMROT_STATIC);
						//str.Format("Camera:       Rotation: %.6f", m_fCameraRotationValue/0.017453293005625408F); 
						//SetWindowText(hand,str);
					}
				}
			}
			break;
					
	    }//eoswitch
	/*
	CString s;
	s.Format("\n%d",wparam);
	OutputDebugString(s);
	*/
	/*
	HWND han;
	s.Format("%.6f", m_SceneObjects->m_CamPos.x); 
	han=GetDlgItem( hwnd, IDC_CAMPOS_X_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamPos.y); 
	han=GetDlgItem( hwnd, IDC_CAMPOS_Y_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamPos.z); 
	han=GetDlgItem( hwnd, IDC_CAMPOS_Z_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamRot.x); 
	han=GetDlgItem( hwnd, IDC_CAMROT_X_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamRot.y); 
	han=GetDlgItem( hwnd, IDC_CAMROT_Y_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamRot.z); 
	han=GetDlgItem( hwnd, IDC_CAMROT_Z_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamTheta[0]); 
	han=GetDlgItem( hwnd, IDC_CAMROT_T_STATIC);
	SetWindowText(han,s);
	*/
	/*
	s.Format("%.6f", m_SceneObjects->m_CamDir.x); 
	han=GetDlgItem( hwnd, IDC_GRIDPOS_X_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamDir.y); 
	han=GetDlgItem( hwnd, IDC_GRIDPOS_Y_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamDir.z); 
	han=GetDlgItem( hwnd, IDC_GRIDPOS_Z_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamUp.x); 
	han=GetDlgItem( hwnd, IDC_GRIDROT_X_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamUp.y); 
	han=GetDlgItem( hwnd, IDC_GRIDROT_Y_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", m_SceneObjects->m_CamUp.z); 
	han=GetDlgItem( hwnd, IDC_GRIDROT_Z_STATIC);
	SetWindowText(han,s);
	*/
	D3DVECTOR cvert;
	m_SceneObjects->gridFrame->GetPosition(NULL, &cvert);
	/*
	s.Format("%.6f", cvert.x); 
	han=GetDlgItem( hwnd, IDC_GRID_X_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", cvert.y); 
	han=GetDlgItem( hwnd, IDC_GRID_Y_STATIC);
	SetWindowText(han,s);
	s.Format("%.6f", cvert.z); 
	han=GetDlgItem( hwnd, IDC_GRID_Z_STATIC);
	SetWindowText(han,s);
	*/
}

void CWin3D::DoKeyUp(UINT wparam,  LPDIRECT3DRMFRAME3 sFrame)
{
	switch (wparam)
	{
	case VK_CONTROL:CtrlKeyState=0;break;
	case VK_MENU:AltKeyState=0;break;
	case VK_SHIFT:ShiftKeyState=0;break;

	case 'U'://left:
	case 'J'://right:
	case 'K'://down:
	case 'I'://up:
			{
			if(AltKeyState==1){//StopWalkSelFr(sFrame);
			}else{
				StopWalk( m_SceneObjects->m_camera);
				StopWalk(m_SceneObjects->gridFrame);
			}
			}
			break;
	case 'E':
	case 'R':
	case 'D':
	case 'F':
	case 'C':
	case 'V':{
		if(AltKeyState==1){StopWalk(m_SceneObjects->m_camera);
			StopWalk(m_SceneObjects->gridFrame);
		}else{
				//StopWalkSelFr(sFrame);
			StopWalk(m_SceneObjects->gridFrame);
		}
			}
	break;

		case VK_INSERT:
		case VK_END:
		case VK_DOWN:
		case VK_NEXT:
		case VK_LEFT:
		case VK_CLEAR:
		case VK_RIGHT:
		case VK_HOME:
		case VK_UP:
		case VK_PRIOR:{
			if(AltKeyState==1){//StopWalkSelFr(sFrame);
			}else{
				StopWalk(m_SceneObjects->m_camera);
				StopWalk(m_SceneObjects->gridFrame);
			}
					  }
			break;
		
	}
}

