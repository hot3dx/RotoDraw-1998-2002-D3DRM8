#include "stdafx.h"
#include "data3d.h"

void DoDataMessageBox( CString c )
{
	CString s;
	s.Format( L"Out of Memory Error: %s", c); 
	MessageBox(NULL, L"The computer has insufficient memory to perform this operation", s, MB_OK);
			exit(0);
}

HDXMaterial::HDXMaterial()
{
	fCount=0;
	nCount=0;
	return;
}

HDXMaterial::~HDXMaterial()
{
	return;
}

HDXMaterialArray::HDXMaterialArray()
{
	m_Count = 0;
	m_Mats=(HDXMaterial*)malloc(0*sizeof(HDXMaterial));
	if(m_Mats==NULL)
	{
		DoDataMessageBox( L"HDXMaterialArray" );
	}
	return;
}
HDXMaterial * HDXMaterialArray::Allocate(unsigned int size)
{
	m_Count = size;
	HDXMaterial *value = (HDXMaterial*) malloc(size*sizeof(HDXMaterial));

	if(value==NULL)
	{
		m_Count=0;
		DoDataMessageBox( L"HDXMaterialArray:Allocate" );
	}
	else{memset( value, 0, (size*sizeof(HDXMaterial)));}
	return value;
}
void HDXMaterialArray::DeAllocate()
{
	if(m_Count>0)
		free(m_Mats);
}
HDXMaterial * HDXMaterialArray::Grow(HDXMaterial arg)
{
	unsigned int size = m_Count;
	HDXMaterial *pTex = (HDXMaterial*)malloc((size+1)*sizeof(HDXMaterial));
	if(pTex==NULL)
	{
		DoDataMessageBox( L"HDXMaterialArray:Grow" );
	}
	else{memset( pTex, 0, ((size+1)*sizeof(HDXMaterial)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(m_Mats +i); 
	}
	*(pTex + size) = arg;
	
	if(m_Count>0)free(m_Mats);
	m_Count++;
	}
	return pTex;
}

void HDXMaterialArray::Set( unsigned int item, HDXMaterial arg)
{
	m_Mats[item]=arg;
}

HDXMaterial HDXMaterialArray::Get( unsigned int item)
{
	return m_Mats[item];
}

HDXMaterial * HDXMaterialArray::Shrink(unsigned int pos)
{
	unsigned int size = m_Count;
	HDXMaterial *pTex = (HDXMaterial*)malloc((size-1)*sizeof(HDXMaterial));
	if(pTex==NULL)
	{
		DoDataMessageBox( L"HDXMaterialArray:Shrink" );
	}
	else{memset( pTex, 0, ((size-1)*sizeof(HDXMaterial)));
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + i) = *(m_Mats +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i) = *(m_Mats +i+1); 
	}
	free(m_Mats);
	}
	m_Count--;
	return pTex;

}

LPDIRECT3DRMMATERIAL2 HDXMaterialArray::CreateHDXMaterial( LPDIRECT3DRM3 rm, unsigned int item)
{
	LPDIRECT3DRMMATERIAL2 mat = NULL;

	rm->CreateMaterial( m_Mats[item].args[0], &mat );
	mat->SetAmbient( m_Mats[item].args[7], m_Mats[item].args[8], m_Mats[item].args[9]);
	//mat->SetColor( RGBA_MAKE(m_Mats[item].r,m_Mats[item].g,m_Mats[item].b,m_Mats[item].a));
	mat->SetEmissive( m_Mats[item].args[1], m_Mats[item].args[2], m_Mats[item].args[3]);
	mat->SetSpecular( m_Mats[item].args[4], m_Mats[item].args[5], m_Mats[item].args[6]);
	
	if(m_Mats[item].nCount>0)
	mat->SetName(m_Mats[item].matName);
	
	return mat;
}

LPDIRECT3DRMTEXTURE3 HDXMaterialArray::CreateHDXTextue( LPDIRECT3DRM3 rm, unsigned int item)
{
	LPDIRECT3DRMTEXTURE3 texture=NULL;

		if(D3DRM_OK==rm->LoadTexture( m_Mats[item].file, &texture))
		{
//			OutputDebugString("\nD3DRM_OK tex loaded\n");
		}
	
	return texture;
}

HDXUndoFacesArray::HDXUndoFacesArray(){m_Count=0;return;}

LPDIRECT3DRMFACE2 * HDXUndoFacesArray::Allocate(unsigned int size)
{
		m_Count = size;
	LPDIRECT3DRMFACE2 *value = (LPDIRECT3DRMFACE2*) malloc(size*sizeof(LPDIRECT3DRMFACE2));

	if(value==NULL)
	{
		m_Count=0;
		DoDataMessageBox( L"HDXUndoFacesArray" );
	}
	else{memset( value, 0, (size*sizeof(LPDIRECT3DRMFACE2)));}
	return value;
}
void HDXUndoFacesArray::Deallocate()
{
	if(m_Count>0)free(m_FacesArray);
	m_Count=0;
}
LPDIRECT3DRMFACE2 * HDXUndoFacesArray::Grow(LPDIRECT3DRMFACE2 face)
{
	unsigned int size = m_Count;
	LPDIRECT3DRMFACE2 *pTex = (LPDIRECT3DRMFACE2*)malloc((size+1)*sizeof(LPDIRECT3DRMFACE2));
	if(pTex==NULL)
	{
		DoDataMessageBox( L"HDXUndoFacesArray::Grow" );
	}
	else{memset( pTex, 0, ((size+1)*sizeof(LPDIRECT3DRMFACE2)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(m_FacesArray +i); 
	}
	*(pTex + size) = face;
	
	if(m_Count>0)free(m_FacesArray);
	m_Count++;
	}
	return pTex;
}

////////////////////////////////////////////////////////////////////
/////
///// HDXMaterialList & HDXMaterialListArray
/////
////////////////////////////////////////////////////////////////////

HDXMaterialList::HDXMaterialList()
{
	m_iListCount = 0;
	return;
}

HDXMaterialList::~HDXMaterialList()
{
	return;
}

HDXMaterialListArray::HDXMaterialListArray()
{
	m_iCount = 0;
	return;
}

HDXMaterialList * HDXMaterialListArray::Allocate( unsigned int size )
{
	m_iCount = size;
	HDXMaterialList *value = (HDXMaterialList*) malloc(size*sizeof(HDXMaterialList));

	if(value==NULL)
	{
		m_iCount=0;
		DoDataMessageBox( L"HDXMaterialListArray::Allocate" );
	}
	else{memset( value, 0, (size*sizeof(HDXMaterialList)));}
	return value;
}

void HDXMaterialListArray::DeAllocate()
{
	if(m_iCount>0)
		free(m_Lists);
}

HDXMaterialList * HDXMaterialListArray::Grow(HDXMaterialList arg)
{
	unsigned int size = m_iCount;
	HDXMaterialList *pTex = (HDXMaterialList*)malloc((size+1)*sizeof(HDXMaterialList));
	if(pTex==NULL)
	{
		DoDataMessageBox(L"HDXMaterialList:Grow");
			
	}
	else{memset( pTex, 0, ((size+1)*sizeof(HDXMaterialList)));
	for(unsigned int i = 0;i<size;i++)
	{
		*(pTex + i) = *(m_Lists +i); 
	}
	*(pTex + size) = arg;
	
	if(m_iCount>0)free(m_Lists);
	m_iCount++;
	}
	return pTex;
}

void HDXMaterialListArray::Set( unsigned int item, HDXMaterialList arg)
{
	m_Lists[item]=arg;
}

HDXMaterialList HDXMaterialListArray::Get( unsigned int item)
{
	return m_Lists[item];
}

HDXMaterialList * HDXMaterialListArray::Shrink(unsigned int pos)
{
	unsigned int size = m_iCount;
	HDXMaterialList *pTex = (HDXMaterialList*)malloc((size-1)*sizeof(HDXMaterialList));
	if(pTex==NULL)
	{
		DoDataMessageBox( L"HDXMaterialListArray::Shrink" );
	}
	else{memset( pTex, 0, ((size-1)*sizeof(HDXMaterialList)));
	for(unsigned int i = 0;i<pos;i++)
	{
		*(pTex + i) = *(m_Lists +i); 
	}
	for(unsigned int i = pos;i<size-1;i++)
	{
		*(pTex + i) = *(m_Lists +i+1); 
	}
	free(m_Lists);
	}
	m_iCount--;
	return pTex;

}

LPVOIDDATA::LPVOIDDATA()
{
	m_uiCount = 0;
	return;
}

LPVOIDDATA::~LPVOIDDATA()
{
	if(m_uiCount>0)delete arg;
	return;
}

void * LPVOIDDATA::Allocate(unsigned int size )
{
	m_uiCount = size;
	arg = new LPVOID[size];
	if(arg==NULL)
	{
		DoDataMessageBox( L"LPVOIDDATA::Allocate" );
		return NULL;
	}
	return arg;
}

void LPVOIDDATA::Deallocate()
{
	if(m_uiCount > 0) delete arg;
	m_uiCount = 0;
}

void * LPVOIDDATA::Grow( unsigned int size, unsigned int sizeOfItem, LPVOID data)
{
	unsigned int sz = size*sizeOfItem;

	void *d = new LPVOID[sz];
	if(d==NULL)
	{
		DoDataMessageBox( L"LPVOIDDATA::Grow" );
		return NULL;
	}
	if(m_uiCount>0)
	{

		LPVOID *d = (LPVOID*)arg;
			data = (LPVOID*)arg;
		
		
		delete arg;
		m_uiCount += sz;
		return d;
	}
	else
	{
		data = (LPVOID*)d;
		m_uiCount=sz;
		return d;
	}
}