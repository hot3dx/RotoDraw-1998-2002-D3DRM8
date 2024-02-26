#include "stdafx.h"
#include "CameraMoveRotationVars.h"
#include "math.h"

CCameraXYMoveRotation::CCameraXYMoveRotation()
{
	m_fCamMove_degreeradian = 0.017453293005625408F;
	// radian 57.29577791868204900000
	m_fCamMove_camerarotation=10.0F;
	m_fCamMove_anglerotation = m_fCamMove_camerarotation*m_fCamMove_degreeradian;
	m_fCamMove_cameraradius = 81.0F;
	m_bArrayInit=false;
	return;
}

CCameraXYMoveRotation::~CCameraXYMoveRotation()
{
	free(m_fCamMove_px);
	free(m_fCamMove_py);
	free(m_fCamMove_pz);
}

double  CCameraXYMoveRotation::DegreesToRadians( double degree )
{
	m_fCamMove_camerarotation = m_fCamMove_anglerotation*m_fCamMove_degreeradian;
	return m_fCamMove_camerarotation;
}

void   CCameraXYMoveRotation::InitSphereVars( void )
{
	
}

void   CCameraXYMoveRotation::CalculateSphere( int* n )
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
	ox = (double*) malloc((num+1)*sizeof(double));
	if(ox!=NULL)
	{
		
	
	oy = (double*) malloc((num+1)*sizeof(double));
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


	if(m_bArrayInit==true)
	{
		free(m_fCamMove_px);free(m_fCamMove_py);free(m_fCamMove_pz);
	}
	///////////////////////////////////////
	m_fCamMove_px =(double*)malloc(cnt*sizeof(double));
	if(m_fCamMove_px!=NULL)
	{
		m_fCamMove_py =(double*)malloc(cnt*sizeof(double));
	if(m_fCamMove_py!=NULL)
	{
		m_fCamMove_pz =(double*)malloc(cnt*sizeof(double));
	if(m_fCamMove_pz!=NULL)
	{
		m_bArrayInit=true;
	angle = 0.0F;
	cnt=0;
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
				m_fCamMove_px[cnt] = ox[i];
				m_fCamMove_py[cnt] = radius*(1.0*cos(zangle));
				m_fCamMove_pz[cnt] = radius*(1.0*sin(zangle));
				cnt++;
				zangle+=addangle;
			}// eo j for
		}// eo if i < 0
		else
		{
			
			m_fCamMove_px[cnt] = ox[i];
			m_fCamMove_py[cnt] = 0.0F; 
			m_fCamMove_pz[cnt] = 0.0F;
			cnt++;
			
		}
		angle += m_fCamMove_anglerotation;
	
	}// eo i for
	m_iCount=n[0]=cnt;
	}}}
	free(ox);}free(oy);}// eo ox and oy != NULL
	

}

void   CCameraXYMoveRotation::MoveRotateCameraXY( int direction )
{

}

void   CCameraXYMoveRotation::MoveRotateCameraAny( float x, float y, float z )
{

}