#ifndef _HOBREAD_H
#define _HOBREAD_H

#pragma once

#define HOBMAX_MATERIAL        300
#define HOBMAX_TEXTURE_NAME    256
#define HOBMAX_MAT_NAME        20

#include "data3d.h"

struct HOBMeshMaterialData
{
    D3DMATERIAL7 m_mtrl;
    TCHAR        m_strTexture[HOBMAX_TEXTURE_NAME];
    DWORD        m_dwNumIndices;
	TCHAR        m_MatName[HOBMAX_MAT_NAME];
};




//-----------------------------------------------------------------------------
// Name: class CHOBFileObject
// Desc: Internal class for objects in a .hob file
//-----------------------------------------------------------------------------
class CHOBFileObject
{
public:
    // Common data
    TCHAR            m_strName[80];
    //CHOBFileObject*  m_pNext;
    //CHOBFileObject*  m_pChild;

    // For file frames
    D3DMATRIX        m_mat;

    // For file meshes
    BOOL             m_bHasMeshData;
	DWORD            m_dwNumVertices;
    D3DVERTEX*       m_pVertices;
	DWORD            m_dwNumFaces;
    DWORD            m_dwNumIndices;
    WORD*            m_pIndices;
    DWORD            m_dwNumMaterials;
    HOBMeshMaterialData m_Material[HOBMAX_MATERIAL];
    BOOL             m_bHasAlpha;
	DWORD            m_dwNumMatFaces;
	DWORD*           m_pMatFaces;
	DWORD*           m_pFaceIndices;
	LPDIRECT3DRMMESHBUILDER3 mb;


    // Initializing functions
    //VOID    AddNext( CHOBFileObject* );
    //VOID    AddChild( CHOBFileObject* );
    VOID    SetName( TCHAR* strName )     { strcpy_s( (char*)m_strName, 80, (char*)strName ); }
    VOID    SetMatrix( D3DMATRIX* pmat ) { m_mat = *pmat; }
    VOID    SetNormals( D3DVECTOR* pNormals );
    VOID    SetTextureCoords( FLOAT* pTexCoords );
    VOID    SetMaterialData( DWORD dwMaterial, D3DMATERIAL7* pmtrl, TCHAR* strName );
	void	SetFaceData(DWORD* pFaceData);
	VOID    SetMeshMaterialData( DWORD* wList, DWORD dwNumMatFaces );
    VOID    AddFace( DWORD dwMaterial, DWORD* pFaceData, DWORD dwNumFaces );
    HRESULT ComputeNormals();
    HRESULT SetMeshGeometry( D3DVECTOR* pvVertices, DWORD dwNumVertices,
                             DWORD* pFaces, DWORD dwNumFaces );
    
    // Access functions
    TCHAR*          GetName()   { return m_strName; }
    //CHOBFileObject* GetNext()   { return m_pNext; }
    //CHOBFileObject* GetChild()  { return m_pChild; }
    D3DMATRIX*      GetMatrix() { return &m_mat; }
    HRESULT         GetMeshGeometry( D3DVERTEX** ppVertices,
                                     DWORD* pdwNumVertices, WORD** ppIndices,
                                     DWORD* pdwNumIndices );

    // Common functions
    //VOID    Render( LPDIRECT3DDEVICE7 pd3dDevice , BOOL bAlpha );
    BOOL    EnumObjects( BOOL (*fnCallback)(CHOBFileObject*,D3DMATRIX*,VOID*),
                         D3DMATRIX* pmat, VOID* pContext );

    // Constuctor / destructor
    CHOBFileObject( TCHAR* strName );
    ~CHOBFileObject();
};


class HDXHOBReader
{
	char *filename;
public:
	CHOBFileObject* m_pRoot;
	HDXHOBReader();
	~HDXHOBReader();
	HRESULT ReadHob( char *name, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3, CPoints* meshPoints, CMAKERPTGROUPS* groups  );

	HRESULT    GetMeshVertices( TCHAR* strName, D3DVERTEX** ppVertices,
                                DWORD* pdwNumVertices );
    HRESULT    GetMeshIndices( TCHAR* strName, WORD** ppIndices,
                               DWORD* pdwNumIndices );
    
    CHOBFileObject* FindObject( TCHAR* strName );
    VOID            EnumObjects( BOOL (*fnCallback)(CHOBFileObject*,D3DMATRIX*,VOID*),
                                 D3DMATRIX* pmat, VOID* pContext );
    VOID            Scale( FLOAT fScale );

    void SetMeshCount( DWORD cnt );
	void SetFrameCount( DWORD cnt );
	DWORD GetMeshCount();
	DWORD GetFrameCount();

	

};
#endif // _HOBREAD_H