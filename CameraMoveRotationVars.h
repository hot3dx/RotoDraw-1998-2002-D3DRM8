#ifndef _CAMERA_MOVE_ROTATION_VARS_H
#define _CAMERA_MOVE_ROTATION_VARS_H

#pragma once

// A structure for our custom vertex type
struct CUSTOMVERTEX
{

    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class CCameraXYMoveRotation
{
public:
	CCameraXYMoveRotation();

	float  m_fCamMove_north;
	float  m_fCamMove_northeast;
	float  m_fCamMove_east;
	float  m_fCamMove_southeast;
	float  m_fCamMove_south;
	float  m_fCamMove_southwest;
	float  m_fCamMove_west;
	float  m_fCamMove_northwest;
	float  m_fCamMove_anypointcamera;
	float  m_fCamMove_centerofsphere;
	float  m_fCamMove_camerapoint;
	float  m_fCamMove_cameradirection;
	double  m_fCamMove_camerarotation;
	double  m_fCamMove_cameraradius;
	float  m_fCamMove_gridcenter;
	double  m_fCamMove_degreeradian;
	double  m_fCamMove_anglerotation;
	bool    m_bArrayInit;
	double  *m_fCamMove_px;
	double  *m_fCamMove_py; 
	double  *m_fCamMove_pz;
	int      m_iCount;
	double  DegreesToRadians( double degree );
	void   InitSphereVars( void );
	void   CalculateSphere( int* count );
	CUSTOMVERTEX * CalculateSphereCV( CUSTOMVERTEX * vertices, int* n, DWORD color );
	void   MoveRotateCameraXY( int direction );
	void   MoveRotateCameraAny( float x, float y, float z );
	
	

	~CCameraXYMoveRotation();
};


#endif // _CAMERA_MOVE_ROTATION_VARS_H