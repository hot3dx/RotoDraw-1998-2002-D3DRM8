#if !defined(AFX_GEOMETRY_H__8DF8F7A7_6657_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_GEOMETRY_H__8DF8F7A7_6657_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Geometry.h : header file
//
//#include <d3drmwin.h>
/////////////////////////////////////////////////////////////////////////////
// Geometry window

class Geometry
{
// Construction
public:
	Geometry();

// Attributes
public:

// Operations
public:
	double distanceBetweenPoints(D3DVECTOR a, D3DVECTOR b);
	D3DVECTOR directionBetweenPoints(D3DVECTOR a, D3DVECTOR b);
	D3DVECTOR CenterOfFace(LPDIRECT3DRMFACE2 face);
	double Magnitude(D3DVECTOR v);
	double AngleBetweenTwoLines( D3DVECTOR v, D3DVECTOR s);
	void InitVector(D3DVECTOR v);
	double FindPlaneConstant(D3DVECTOR n, D3DVECTOR x);
	D3DVECTOR FindPlaneNormal(D3DVECTOR x, D3DVECTOR y, D3DVECTOR z);
	D3DVECTOR FindPointIntersectPlane(D3DVECTOR planeNormal, D3DVECTOR lineOrigin, D3DVECTOR lineDirection, float c);
	D3DVECTOR GetFaceVertex(LPDIRECT3DRMFACE2 face, int id);


public:
	virtual ~Geometry();

	// Generated message map functions
protected:
	
};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_GEOMETRY_H__8DF8F7A7_6657_11D6_896C_00A0CCA2416E__INCLUDED_)
