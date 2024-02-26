#include "stdafx.h"
#include "ClipTexture.h"

void DoClipDataMessageBox( CString c )
{
	CString s;
	s.Format(  L"Out of Memory Error: %s", c); 
	MessageBox(NULL,   L"The computer has insufficient memory to perform this operation", s, MB_OK);
			exit(0);
}
/////////////////////////////////////////////////////////////////
////// CHDXFLOATARRAY
/////////////////////////////////////////////////////////////////
CHDXFLOATARRAY::CHDXFLOATARRAY()
{
	dwEmptyEnd=0;
	floatCount=0;
	return;
}

CHDXFLOATARRAY::~CHDXFLOATARRAY()
{
	dwEmptyEnd = 0;
	floatCount = 0;
}


float * CHDXFLOATARRAY::allocate(unsigned int num)
{		
	floatCount = num;
	value = (float*) malloc(num*sizeof(float));
	if(value==NULL)
	{
		floatCount = 0;
		DoClipDataMessageBox( L"CHDXFLOATARRAY::allocate" );
	}
	else{memset(value, 0, num*sizeof(float));}
	return value;
}

void CHDXFLOATARRAY::deallocate()
{
	dwEmptyEnd=0;
	floatCount=0;
	free(value);
}
float CHDXFLOATARRAY::get(unsigned int num)
{
	return *( value+num);
}
float * CHDXFLOATARRAY::getRange(unsigned int num, unsigned int to)
{
	float *sTex = (float*)malloc((to-num)*sizeof(float));
	if(sTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::getRange" );
	}
	else{memset( sTex, 0, ((to-num)*sizeof(float)));
	
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(sTex+j) = *(value + i); 
		j++;
	}
	}
	return sTex;
}

void CHDXFLOATARRAY::set(unsigned int pos, float val)
{
	
	if(pos<(floatCount-1)){
		*(value+pos) = val;
	
	}
}

void CHDXFLOATARRAY::setRange(unsigned int num, unsigned int to, float *newgroup)
{
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(value + i) = *(newgroup +j);
		j++;
	}
}

float * CHDXFLOATARRAY::shrink(unsigned int pos)
{
	unsigned int size = floatCount;
	float *pTex = (float*)malloc((size-1)*sizeof(float));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::shrink" );
	}
	else{memset( pTex, 0, ((size-1)*sizeof(float)));
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i) = *(value +i+1); 
	}
	free(value);
	}
	floatCount--;
	return pTex;

}
float * CHDXFLOATARRAY::shrinkBy(unsigned int pos, unsigned int end)
{
	unsigned int size = floatCount;
	float *pTex = (float*)malloc((size-(end-pos))*sizeof(float));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::shrinkBy" );
	}
	else{memset( pTex, 0, ((size-(end-pos))*sizeof(float)));
	int j = 0;
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	for(unsigned int i = end;i<size;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	free(value);
	}
	floatCount=size-(end-pos);
	return pTex;
}
float * CHDXFLOATARRAY::grow(float aTex)
{
	unsigned int size = floatCount;
	float *pTex = (float*)malloc((size+1)*sizeof(float));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::grow" );
	}
	else{memset( pTex, 0, ((size+1)*sizeof(float)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	*(pTex + size) = aTex;
	if(floatCount>0)free(value);

	}
	if(floatCount>0)free(value);
	floatCount++;
	return pTex;
}
float * CHDXFLOATARRAY::growBy( unsigned int growth, float *aTex)
{
	unsigned int size = floatCount;
	float *pTex=(float*)malloc((size+growth)*sizeof(float));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::growBy" );
	}
	else{memset( pTex, 0, ((size+growth)*sizeof(float)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	int j=0;
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = *(aTex +j);
		j++;
	}
	free(value);
	}
	if(floatCount>0)free(value);
	floatCount = size+growth;
	return pTex;
}

float * CHDXFLOATARRAY::growByEmptyEnd( unsigned int growth)
{
	unsigned int size = floatCount;
	float *pTex = (float*)malloc((size+growth)*sizeof(float));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXFLOATARRAY::growByEmptyEnd" );
	}
	else{
		memset( pTex, 0, (size+growth)*sizeof(float));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = 0.0F;
	}
	if(floatCount>0)free(value);
	dwEmptyEnd = size;
	floatCount +=growth;
	}
	
	return pTex;
}

/////////////////////////////////////////////////////////////////
////// CHDXINTARRAY
/////////////////////////////////////////////////////////////////
CHDXINTARRAY::CHDXINTARRAY()
{
	dwEmptyEnd=0;
	intCount=0;
	return;
}

int * CHDXINTARRAY::allocate(unsigned int num)
{		
	intCount = num;
	value = (int*) malloc(num*sizeof(int));

	if(value==NULL)
	{
		intCount=num;
		DoClipDataMessageBox( L"CHDXINTARRAY::allocate" );
	}
	else{memset( value, 0, (num*sizeof(int)));}
	return value;
}

void CHDXINTARRAY::deallocate()
{

	intCount = 0;
	dwEmptyEnd=0;
	if(intCount>0)
	free(value);
		
}
int CHDXINTARRAY::get(unsigned int num)
{
	return *( value+num);
}
int * CHDXINTARRAY::getRange(unsigned int num, unsigned int to)
{
	int *sTex = (int*)malloc((to-num)*sizeof(int));
	if(sTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::getRange" );
	}
	else{memset( sTex, 0, ((to-num)*sizeof(int)));
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(sTex+j) = *(value + i); 
		j++;
	}
	}
	return sTex;
}

void CHDXINTARRAY::set(unsigned int pos, int val)
{
	if(pos<(intCount-1)){
		*(value + pos) = val;
	}
}

void CHDXINTARRAY::setRange(unsigned int num, unsigned int to, CHDXINTARRAY newgroup)
{
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(newgroup.value +j) = *(value + i);
		j++;
	}
}

int * CHDXINTARRAY::shrink(unsigned int pos)
{
	unsigned int size = intCount;
	
	int *pTex = (int*)malloc(size-1*sizeof(int));
	
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::shrink" );
		return NULL;
	}
	else{
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + i)=*(value +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i)=*(value + i+1); 
	}
	free(value);
	}
	intCount--;
	return pTex;
}

int * CHDXINTARRAY::shrinkBy(unsigned int pos, unsigned int end)
{
	unsigned int size = intCount;
	int *pTex = (int*)malloc((size-(end-pos))*sizeof(int));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::shrinkBy" );
	}
	else{memset( pTex, 0, ((size-(end-pos))*sizeof(int)));
	int j = 0;
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	for(unsigned int i = end;i<size;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	free(value);
	}
	intCount=size-(end-pos);
	return pTex;
}
int * CHDXINTARRAY::grow( int aTex)
{
	unsigned int size = intCount;
	int *pTex = (int*)malloc((size+1)*sizeof(int));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::grow" );
	}
	else{memset( pTex, 0, ((size+1)*sizeof(int)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	*(pTex + size) = aTex;
	if(intCount>0)free(value);
	intCount++;
	}
	return pTex;
}
int * CHDXINTARRAY::growBy(unsigned int growth, int *aTex)
{
	unsigned int size = intCount;
	int *pTex=(int*)malloc((size+growth)*sizeof(int));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::growBy" );
	}
	else{memset( pTex, 0, ((size+growth)*sizeof(int)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	int j=0;
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = *(aTex +j);
		j++;
	}
	free(value);
	}
	intCount = size+growth;
	return pTex;
}

int * CHDXINTARRAY::growByEmptyEnd(unsigned int growth)
{
	unsigned int size = intCount;
	int *pTex=(int*)malloc((size+growth)*sizeof(int));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXINTARRAY::growByEmptyEnd" );
	}
	else{memset( pTex, 0, ((size+growth)*sizeof(int)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	
	free(value);
	}
	dwEmptyEnd=size;
	intCount = size+growth;
	return pTex;
}
/////////////////////////////

/////////////////////////////////////////////////////////////////
////// CHDXPOINTARRAY
/////////////////////////////////////////////////////////////////
CHDXPOINTARRAY::CHDXPOINTARRAY()
{
	dwEmptyEnd=0;
	intCount=0;
	return;
}

CPoint * CHDXPOINTARRAY::allocate(unsigned int num)
{		
	intCount = num;
	value = (CPoint*) malloc(num*sizeof(CPoint));

	if(value==NULL)
	{
		intCount=num;
		DoClipDataMessageBox( L"CHDXPOINTARRAY::allocate" );
	}
	else{memset( value, 0, (num*sizeof(CPoint)));}
	return value;
}

void CHDXPOINTARRAY::deallocate()
{

	intCount = 0;
	dwEmptyEnd=0;
	if(intCount>0)
	free(value);
		
}
CPoint CHDXPOINTARRAY::get(unsigned int num)
{
	return *( value+num);
}
CPoint * CHDXPOINTARRAY::getRange(unsigned int num, unsigned int to)
{
	CPoint *sTex = (CPoint*)malloc((to-num)*sizeof(CPoint));
	if(sTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::getRange" );
	}
	else{memset( sTex, 0, ((to-num)*sizeof(CPoint)));
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(sTex+j) = *(value + i); 
		j++;
	}
	}
	return sTex;
}

void CHDXPOINTARRAY::set(unsigned int pos, CPoint val)
{
	if(pos<(intCount-1)){
		*(value + pos) = val;
	}
}

void CHDXPOINTARRAY::setRange(unsigned int num, unsigned int to, CHDXPOINTARRAY newgroup)
{
	int j = 0;
	for(unsigned int i = num;i<to;i++)
	{
		*(newgroup.value +j) = *(value + i);
		j++;
	}
}

CPoint * CHDXPOINTARRAY::shrink(unsigned int pos)
{
	unsigned int size = intCount;
	CPoint *pTex = (CPoint*)malloc((size-1)*sizeof(CPoint));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::shrink" );
	}
	else{memset( pTex, 0, ((size-1)*sizeof(CPoint)));
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i) = *(value +i+1); 
	}
	// this was removed because of a bug 1/26/03
	// it may need to be put back in
	// i do not know
	//free(value);
	}
	intCount--;
	return pTex;

}
CPoint * CHDXPOINTARRAY::shrinkBy(unsigned int pos, unsigned int end)
{
	unsigned int size = intCount;
	CPoint *pTex = (CPoint*)malloc((size-(end-pos))*sizeof(CPoint));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::shrinkBy" );
	}
	else{memset( pTex, 0, ((size-(end-pos))*sizeof(CPoint)));
	int j = 0;
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	for(unsigned int i = end;i<size;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	free(value);
	}
	intCount=size-(end-pos);
	return pTex;
}
CPoint * CHDXPOINTARRAY::grow( CPoint aTex)
{
	unsigned int size = intCount;
	CPoint *pTex = (CPoint*)malloc((size+1)*sizeof(CPoint));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::grow" );
	}
	else{memset( pTex, 0, ((size+1)*sizeof(CPoint)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	*(pTex + size) = aTex;
	if(intCount>0)free(value);
	intCount++;
	}
	return pTex;
}
CPoint * CHDXPOINTARRAY::growBy(unsigned int growth, CPoint *aTex)
{
	unsigned int size = intCount;
	CPoint *pTex=(CPoint*)malloc((size+growth)*sizeof(CPoint));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::growBy" );
	}
	else{memset( pTex, 0, ((size+growth)*sizeof(CPoint)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	int j=0;
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = *(aTex +j);
		j++;
	}
	free(value);
	}
	intCount = size+growth;
	return pTex;
}

CPoint * CHDXPOINTARRAY::growByEmptyEnd(unsigned int growth)
{
	unsigned int size = intCount;
	CPoint *pTex=(CPoint*)malloc((size+growth)*sizeof(CPoint));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXPOINTARRAY::growByEmptyEnd" );
	}
	else{memset( pTex, 0, ((size+growth)*sizeof(CPoint)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	
	free(value);
	}
	dwEmptyEnd=size;
	intCount = size+growth;
	return pTex;
}




CCamGridStats::CCamGridStats(){return;}
CMAKERPTGROUPS::CMAKERPTGROUPS()
{
	m_iPtGroupCount=0;
	m_iPtMouseCount=0;
	m_iPtStatsCount=0;
	return;
}

CHDXINTARRAY * CMAKERPTGROUPS::Grow( CHDXINTARRAY arg)
{
	unsigned int size = m_iPtGroupCount;
	CHDXINTARRAY *pA = (CHDXINTARRAY*)malloc((size+1)*sizeof(CHDXINTARRAY));
	if(pA==NULL)
	{
		DoClipDataMessageBox( L"CMAKERPTGROUPS::Grow" );
	}
	else{
		memset( pA, 0 , (size+1)*sizeof(CHDXINTARRAY) );
	if(size>0)
	{
		for(unsigned int i = 0;i<size;i++)
		{
			*(pA + i) = *( m_iPointGroups+i);
		}
	}//eo if(size>0)
	*(pA + size) = arg;
	if(m_iPtGroupCount>0)
	{
		free(m_iPointGroups);
		
	}
	}
	m_iPtGroupCount++;
	return pA;
}
CHDXINTARRAY * CMAKERPTGROUPS::Shrink( unsigned int arg)
{
	unsigned int size = m_iPtGroupCount;

	CHDXINTARRAY *pA = (CHDXINTARRAY*)malloc((size-1)*sizeof(CHDXINTARRAY));
	if(pA==NULL){
		DoClipDataMessageBox( L"CMAKERPTGROUPS::Shrink" );
	}
	else{
		memset( pA, 0 , (size-1)*sizeof(CHDXINTARRAY) );
	
	for(unsigned int i = 0;i<arg+1;i++)
	{
		if(i!=arg)
		*(pA + i) = *( m_iPointGroups+i);
		
	}
	for(unsigned int i = arg;i<size-1;i++)
	{
		*(pA + i) = *(m_iPointGroups +i+1); 
	}
	if(m_iPtGroupCount>0)
	{
		free(m_iPointGroups);
	}
	}
	m_iPtGroupCount--;
	return pA;
	
}
CCamGridStats * CMAKERPTGROUPS::ShrinkStats( unsigned int stats)
{
	unsigned int size = m_iPtStatsCount;
	CCamGridStats *pA = (CCamGridStats*)malloc((size-1)*sizeof(CCamGridStats));
	if(pA==NULL){
		DoClipDataMessageBox( L"CMAKERPTGROUPS::ShrinkStats" );
	}
	else{
		memset( pA, 0 , (size-1)*sizeof(CCamGridStats) );
	
	for(unsigned int i = 0;i<stats+1;i++)
	{
		if(i!=stats)
		*(pA + i) = *( m_CamGridStats+i);
		
	}
	for(unsigned int i = stats;i<size-1;i++)
	{
		*(pA + i) = *(m_CamGridStats +i+1); 
	}
	if(m_iPtStatsCount>0)
	{
		free(m_CamGridStats);
		
	}
	m_iPtStatsCount--;
	}
	
	return pA;
}
CHDXPOINTARRAY * CMAKERPTGROUPS::ShrinkMouse( unsigned int arg)
{
	unsigned int size = m_iPtMouseCount;
	CHDXPOINTARRAY *pA = (CHDXPOINTARRAY*)malloc((size-1)*sizeof(CHDXPOINTARRAY));
	if(pA==NULL){
		DoClipDataMessageBox( L"CMAKERPTGROUPS::ShrinkMouse" );
	}
	else{
		memset( pA, 0 , (size-1)*sizeof(CHDXPOINTARRAY) );
	
	for(unsigned int i = 0;i<arg+1;i++)
	{
		if(i!=arg)
		*(pA + i) = *( m_Mouse+i);
		
	}
	for(unsigned int i = arg;i<size-1;i++)
	{
		*(pA + i) = *(m_Mouse +i+1); 
	}
	if(m_iPtMouseCount>0)
	{
		free(m_Mouse);
		
	}
	m_iPtMouseCount--;
	}
	
	return pA;
}
CHDXPOINTARRAY * CMAKERPTGROUPS::GrowMouse( CHDXPOINTARRAY arg)
{
	unsigned int size = m_iPtMouseCount;
	CHDXPOINTARRAY *pA = (CHDXPOINTARRAY*)malloc((size+1)*sizeof(CHDXPOINTARRAY));
	if(pA==NULL){
		DoClipDataMessageBox( L"CMAKERPTGROUPS::GrowMouse" );
	}
	else{
		memset( pA, 0 , (size+1)*sizeof(CHDXPOINTARRAY) );
	
	for(unsigned int i = 0;i<size;i++)
	{
		*(pA + i) = *( m_Mouse+i);
		
	}
	*(pA + size) = arg;
	if(size>0)
	{
		free(m_Mouse);
		
	}
	m_iPtMouseCount++;
	}
	
	return pA;
}


CCamGridStats * CMAKERPTGROUPS::GrowStats( CCamGridStats stats)
{
	unsigned int size = m_iPtStatsCount;
	CCamGridStats *pS = (CCamGridStats*)malloc((size+1)*sizeof(CCamGridStats));
	if(pS==NULL){
		DoClipDataMessageBox( L"CMAKERPTGROUPS::GrowStats" );
	}
	else{
		memset( pS, 0 , (size+1)*sizeof(CCamGridStats) );
	for(unsigned int i = 0;i<size;i++)
	{
		*(pS + i) = *( m_CamGridStats+i);
	}
	*(pS + size) = stats;
	if(size>0)
	{
		free(m_CamGridStats);
	}
	m_iPtStatsCount++;
	}
	
	return pS;
}

CPoints::CPoints()
{
	m_iNumPoints = 0;
	x.allocate(0);
	y.allocate(0);
	z.allocate(0);
}

void CPoints::GrowByEmptyEnd( unsigned int size )
{
	x.value = x.growByEmptyEnd( size );
	y.value = y.growByEmptyEnd( size );
	z.value = z.growByEmptyEnd( size );
}

void CPoints::Set( unsigned int item, float x1, float y1, float z1 )
{
	x.value[item]=x1;
	y.value[item]=y1;
	z.value[item]=z1;
}

MyTexture::MyTexture(CStatic* screen, int sizeBytes)
{
	
	BYTE m_alpha = 255;

	screen->ModifyStyle(SS_SIMPLE, SS_SUNKEN|SS_BITMAP);
	CRect rect;
	screen->GetWindowRect( &rect );
	int w, h;
	w = rect.Width()-4;//189
	h = rect.Height()-4;//177
	int hsize = w*h*(sizeBytes/8);
	CClientDC dc(screen);
	CDC dcMem;

	BYTE *bits = (BYTE*)malloc((hsize)*sizeof(BYTE));
	memset(bits, 0, hsize);
	
	SetScreenColorBits( sizeBytes, w, h, 0, 0, 255, bits);
	    
	m_BackGroundTexture = new CBitmap();
		dcMem.CreateCompatibleDC(&dc);
		m_BackGroundTexture->CreateCompatibleBitmap(&dc, w, h);
		ASSERT(m_BackGroundTexture->m_hObject != NULL);
	
	m_BackGroundTexture->SetBitmapBits( hsize, bits);
	screen->SetBitmap((HBITMAP) *m_BackGroundTexture );
	free(bits);

	DeleteObject(dc);
	DeleteObject(dcMem);
	
	return;
}

MyTexture::~MyTexture(){}

void MyTexture::SetScreenColorBits( int sizeBytes, int w, int h, BYTE r1, BYTE g1, BYTE b1, BYTE *bits)
{
	r=r1;b=b1;g=g1;
	int p = 0;
	int x,y=0;

    while(y<h)
	{
		x=0;
		while(x<w)
		{
						
			COLORREF c = RGB(r,g,b);
			bits[p]= GetBValue(c);
			bits[p+1]= GetGValue(c);
			bits[p+2]= GetRValue(c);
			if(sizeBytes == 32)
			{
				bits[p+3]= m_alpha;
				p+=4;
			}
			else{p+=3;}
			x++;
			}//eoforx
		y++;
		}//eofory
};

CHDXCHAR::CHDXCHAR(){m_iStringCount=0;return;}

char * CHDXCHAR::allocate(unsigned int num, char * s)
{
	string = (char*)malloc(num*sizeof(char));
	m_iStringCount = num;
	string = s;
	if(s==NULL)
	{
		m_iStringCount = 0;
		DoClipDataMessageBox( L"CHDXCHAR::allocate" );
	}
	
	return string;
}
void CHDXCHAR::deallocate(char * s){free(s);}
void CHDXCHAR::set( char *s){string=s;}

CHDXULONGARRAY::CHDXULONGARRAY()
{
	ulongCount = 0;
	dwEmptyEnd = 0;
	return;
}
unsigned long * CHDXULONGARRAY::allocate(unsigned long size)
{
	ulongCount = size;
	value = (unsigned long*) malloc(size*sizeof(unsigned long));
	if(value==NULL)
	{
		ulongCount = 0;
		DoClipDataMessageBox( L"CHDXULONGARRAY::allocate" );
	}
	else{memset(value, 0, size*sizeof(unsigned long));}
	return value;
}
void  CHDXULONGARRAY::deallocate()
{
	free(value);
}
unsigned long CHDXULONGARRAY::get(unsigned long i)
{
	return value[i];
}
unsigned long * CHDXULONGARRAY::getRange(unsigned long num, unsigned long to)
{
	unsigned long *sTex = (unsigned long*)malloc((to-num)*sizeof(unsigned long));
	if(sTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::getRange" );
	}
	else{memset( sTex, 0, ((to-num)*sizeof(unsigned long)));
	
	int j = 0;
	for(unsigned long i = num;i<to;i++)
	{
		*(sTex+j) = *(value + i); 
		j++;
	}
	}
	return sTex;
}
void  CHDXULONGARRAY::set(unsigned long i, unsigned long val)
{
	value[i] = val;
}
void  CHDXULONGARRAY::setRange(unsigned long num, unsigned long to, CHDXULONGARRAY newarray)
{
	unsigned long j = 0;
	for(unsigned long i = num;i<to;i++)
	{
		*(value + i) = *(newarray.value +j);
		j++;
	}
}
unsigned long * CHDXULONGARRAY::shrink(unsigned long pos)
{
	unsigned long size = ulongCount;
	unsigned long *pTex = (unsigned long*)malloc((size-1)*sizeof(unsigned long));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::shrink" );
	}else{memset( pTex, 0, ((size-1)*sizeof(unsigned long)));
	for(unsigned long i = 0;i<pos;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i) = *(value +i+1); 
	}
	free(value);
	}
	ulongCount--;
	return pTex;
}
unsigned long * CHDXULONGARRAY::shrinkBy(unsigned long pos, unsigned long end)
{
	unsigned long size = ulongCount;
	unsigned long *pTex = (unsigned long*)malloc((size-(end-pos))*sizeof(unsigned long));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::shrinkBy" );
	}else{memset( pTex, 0, ((size-(end-pos))*sizeof(unsigned long)));
	unsigned long j = 0;
	for(unsigned long i = 0;i<pos;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	for(unsigned int i = end;i<size;i++)
	{
		*(pTex + j) = *(value +i); 
		j++;
	}
	free(value);
	}
	ulongCount=size-(end-pos);
	return pTex;
}
unsigned long * CHDXULONGARRAY::grow(unsigned long aNum)
{
	unsigned long size = ulongCount;
	unsigned long *pTex = (unsigned long*)malloc((size+1)*sizeof(unsigned long));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::grow" );
	}	else{memset( pTex, 0, ((size+1)*sizeof(unsigned long)));
	for(unsigned long i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	*(pTex + size) = aNum;
	if(ulongCount>0)free(value);

	}
	ulongCount++;
	return pTex;
}
unsigned long * CHDXULONGARRAY::growBy(unsigned long growth, unsigned long *aArray)
{
	unsigned long int size = ulongCount;
	unsigned long *pTex=(unsigned long*)malloc((size+growth)*sizeof(unsigned long));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::growBy" );
	}else{memset( pTex, 0, ((size+growth)*sizeof(unsigned long)));
	for(unsigned long i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	int j=0;
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = *(aArray +j);
		j++;
	}
	if(ulongCount>0)free(value);
	}
	ulongCount = size+growth;
	return pTex;
}
unsigned long * CHDXULONGARRAY::growByEmptyEnd( unsigned long growth)
{
	unsigned long size = ulongCount;
	unsigned long *pTex = (unsigned long*)malloc((size+growth)*sizeof(unsigned long));
	if(pTex==NULL)
	{
		DoClipDataMessageBox( L"CHDXULONGARRAY::growByEmptyEnd" );
	}
	else{memset( pTex, 0, (size+growth)*sizeof(unsigned long));
	for(unsigned long i = 0;i<size;i++)
	{
		*(pTex + i) = *(value +i); 
	}
	for(unsigned int i = size;i<(size+growth);i++)
	{
		*(pTex + i) = 0;
	}
	if(ulongCount>0)free(value);
	}
	dwEmptyEnd = size;
	ulongCount +=growth;
	return pTex;
}