#ifndef _CLIPTEXTURE_H
#define _CLIPTEXTURE_H

#pragma once

#include "stdafx.h"

class CHDXFLOATARRAY
{
public:
	CHDXFLOATARRAY();
	~CHDXFLOATARRAY();
	unsigned int dwEmptyEnd;
	unsigned int floatCount;
	float *value;
	float * allocate(unsigned int size);
	void  deallocate();
	float   get(unsigned int);
	float * getRange(unsigned int, unsigned int);
	void  set(unsigned int, float);
	void  setRange(unsigned int, unsigned int, float *);
	float * shrink(unsigned int pos);
	float * shrinkBy(unsigned int pos, unsigned int end);
	float * grow(float aNum);
	float * growBy(unsigned int growth, float *aArray);
	float * growByEmptyEnd(unsigned int growth);
};

class CHDXINTARRAY
{
public:
	CHDXINTARRAY();
	unsigned int dwEmptyEnd;
	unsigned int intCount;
	int *value;

	int * allocate(unsigned int size);
	void  deallocate();
	int   get(unsigned int);
	int * getRange(unsigned int, unsigned int);
	void  set(unsigned int, int);
	void  setRange(unsigned int, unsigned int, CHDXINTARRAY newarray);
	int * shrink(unsigned int pos);
	int * shrinkBy(unsigned int pos, unsigned int end);
	int * grow(int aNum);
	int * growBy(unsigned int growth, int *aArray);
	int * growByEmptyEnd(unsigned int growth);

};

class CHDXPOINTARRAY
{
public:
	CHDXPOINTARRAY();
	unsigned int dwEmptyEnd;
	unsigned int intCount;
	CPoint *value;

	CPoint * allocate(unsigned int size);
	void  deallocate();
	CPoint   get(unsigned int);
	CPoint * getRange(unsigned int, unsigned int);
	void  set(unsigned int, CPoint);
	void  setRange(unsigned int, unsigned int, CHDXPOINTARRAY newarray);
	CPoint * shrink(unsigned int pos);
	CPoint * shrinkBy(unsigned int pos, unsigned int end);
	CPoint * grow(CPoint aNum);
	CPoint * growBy(unsigned int growth, CPoint *aArray);
	CPoint * growByEmptyEnd(unsigned int growth);
};
class CCamGridStats
{
public:
	CCamGridStats();
	float m_CamPosX;
	float m_CamPosY;
	float m_CamPosZ;
	float m_CamRotX;
	float m_CamRotY;
	float m_CamRotZ;

	float m_CamOrUpX;
	float m_CamOrUpY;
	float m_CamOrUpZ;
	float m_CamOrDirX;
	float m_CamOrDirY;
	float m_CamOrDirZ;

	float m_GridPosX;
	float m_GridPosY;
	float m_GridPosZ;
	float m_GridRotX;
	float m_GridRotY;
	float m_GridRotZ;
	float m_CamTheta[1];
	float m_GridTheta[1];
};
class CMAKERPTGROUPS
{
public:
	CMAKERPTGROUPS();
	unsigned int	m_iPtGroupCount;
	unsigned int	m_iPtMouseCount;
	unsigned int	m_iPtStatsCount;
	CHDXINTARRAY	*m_iPointGroups;
	CHDXPOINTARRAY	*m_Mouse;

	CCamGridStats   *m_CamGridStats;
	CHDXINTARRAY * Grow(CHDXINTARRAY arg);
	CHDXPOINTARRAY * GrowMouse(CHDXPOINTARRAY arg);
	CHDXPOINTARRAY * ShrinkMouse(unsigned int arg);
	CCamGridStats * GrowStats(CCamGridStats stats);
	CCamGridStats * ShrinkStats(unsigned int stats);
	CHDXINTARRAY * Shrink(unsigned int arg);
};

class CPoints
{
public:
	CPoints();
	unsigned int m_iNumPoints;
	CHDXFLOATARRAY x;
	CHDXFLOATARRAY y;
	CHDXFLOATARRAY z;
	void GrowByEmptyEnd(unsigned int size);
	void Set(unsigned int item, float x, float y, float z);
};

class MyTexture
{
public:
	MyTexture(CStatic* screen, int sizeBytes);
	~MyTexture();
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE m_alpha;
	CBitmap* m_BackGroundTexture;
	void SetScreenColorBits(int sizeBytes, int w, int h, BYTE r1, BYTE g1, BYTE b1, BYTE *bits);
	float x[10000];
	float y[10000];
	float z[10000];


};

class CHDXCHAR
{
public:
	CHDXCHAR();
	unsigned int m_iStringCount;
	char *string;


	char * allocate(unsigned int, char *);
	void deallocate(char *);
	void  set(char *);

};

class CHDXULONGARRAY
{
public:
	CHDXULONGARRAY();
	unsigned long dwEmptyEnd;
	unsigned long ulongCount;
	unsigned long *value;

	unsigned long * allocate(unsigned long size);
	void  deallocate();
	unsigned long get(unsigned long);
	unsigned long * getRange(unsigned long, unsigned long);
	void  set(unsigned long, unsigned long);
	void  setRange(unsigned long, unsigned long, CHDXULONGARRAY newarray);
	unsigned long * shrink(unsigned long pos);
	unsigned long * shrinkBy(unsigned long pos, unsigned long end);
	unsigned long * grow(unsigned long aNum);
	unsigned long * growBy(unsigned long growth, unsigned long *aArray);
	unsigned long * growByEmptyEnd(unsigned long growth);

};


#endif // _CLIPTEXTURE_H