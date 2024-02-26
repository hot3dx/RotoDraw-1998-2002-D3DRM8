// Geometry.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "Geometry.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Geometry

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

double Geometry::distanceBetweenPoints(D3DVECTOR v, D3DVECTOR pos)
{
	return sqrt((pow((v.x-pos.x),2.0))+(pow((v.y-pos.y),2.0))+(pow((v.z-pos.z),2.0)));
}
D3DVECTOR Geometry::directionBetweenPoints(D3DVECTOR from, D3DVECTOR to)
{
	D3DVECTOR v;
	v.x = (to.x-from.x);
	v.y = (to.y-from.y);
	v.z = (to.z-from.z);
	return v;
}

D3DVECTOR Geometry::CenterOfFace(LPDIRECT3DRMFACE2 face)
{
				D3DVECTOR n,v,g;
				face->GetVertex( 0, &v, &n);
				D3DVECTOR n1;
				D3DVECTOR v1;
				face->GetVertex( 2, &v1, &n1);
								
				g.x = (v.x + v1.x)/2;
				g.y = (v.y + v1.y)/2;
				g.z = (v.z + v1.z)/2;
				return g;
}

double Geometry::Magnitude(D3DVECTOR v)
{
	return sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));//sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
}

double Geometry::AngleBetweenTwoLines( D3DVECTOR v, D3DVECTOR s)
{
	double angle = (((v.x*s.x)+(v.y*s.y)+(v.z*s.z))/(Magnitude(v)*Magnitude(s)));
		return cos(angle);
}

void Geometry::InitVector(D3DVECTOR v)
{
	v.x=0.0F;
	v.y=0.0F;
	v.z=0.0F;
}
D3DVECTOR Geometry::FindPlaneNormal(D3DVECTOR a, D3DVECTOR b, D3DVECTOR c)
{
	
	D3DVECTOR n,j,k;
	j.x = a.x-b.x;
	j.y = a.y-b.x;
	j.z = a.z-b.z;
	k.x = c.x-b.x;
	k.y = c.y-b.y;
	k.z = c.z-b.z;	

	n.x = ((j.y*k.z)-(k.y*j.z));
	n.y = ((j.x*k.z)-(k.x*j.z));
	n.z = ((j.x*k.y)-(k.x*j.y));
	return n;
}
/**
*	a,b,c 3 points of a plane
  */
double Geometry::FindPlaneConstant(D3DVECTOR planeNormal, D3DVECTOR a)
{
	return (planeNormal.x*a.x)+(planeNormal.y*a.y)+(planeNormal.z*a.z);
}

D3DVECTOR Geometry::FindPointIntersectPlane(D3DVECTOR planeNormal, D3DVECTOR lineOrigin, D3DVECTOR lineDirection, float c)
{
	D3DVECTOR intersectPoint;
	intersectPoint.x=0.0F;
	intersectPoint.y=0.0F;
	intersectPoint.z=0.0F;
	float k= 0.0F;
	float denom = (planeNormal.x*(lineDirection.x-lineOrigin.x)+planeNormal.y*(lineDirection.y-lineOrigin.y)+planeNormal.z*(lineDirection.z-lineOrigin.z));
	if(denom==0.0F){k= 0.0F;}
	else{
	k = (-(planeNormal.x*lineOrigin.x)-(planeNormal.y*lineOrigin.y)-(planeNormal.z*lineOrigin.z)+c)/(planeNormal.x*(lineDirection.x-lineOrigin.x)+planeNormal.y*(lineDirection.y-lineOrigin.y)+planeNormal.z*(lineDirection.z-lineOrigin.z));
	}
	intersectPoint.x = lineOrigin.x+((lineDirection.x-lineOrigin.x)*k);
	intersectPoint.y = lineOrigin.y+((lineDirection.y-lineOrigin.y)*k);
	intersectPoint.z = lineOrigin.z+((lineDirection.z-lineOrigin.z)*k);

	return intersectPoint;
}

D3DVECTOR Geometry::GetFaceVertex(LPDIRECT3DRMFACE2 face, int id)
{
	D3DVECTOR v,n;
	face->GetVertex(id, &v, &n);
	return v;
}
/////////////////////////////////////////////////////////////////////////////
// Geometry message handlers
