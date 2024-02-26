#include "stdafx.h"
#include "dxsdk8\include\d3drm.h"

#include "dxsdk8\include\dxfile.h"
#include "dxsdk8\include\rmxfguid.h"
#include "dxsdk8\include\rmxftmpl.h"
#include <math.h>
#include "D3DFile.h"


#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

DWORD m_iMeshCount;
DWORD m_iFrameCount;

//ZeroMemory(
D3DVALUE MySquareMagnitude ( const _D3DVECTOR& v);
//This function is defined as follows:

inline D3DVALUE MySquareMagnitude (const _D3DVECTOR& v)
{
   return ((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
}

D3DVALUE MyMagnitude (const _D3DVECTOR& v);
//This function is defined as follows:

inline D3DVALUE MyMagnitude (const _D3DVECTOR& v)
{
   return (D3DVALUE) sqrt(MySquareMagnitude(v));
}

_D3DVECTOR MyCrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
//This function is defined as follows:

inline _D3DVECTOR MyCrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
    D3DVECTOR result;
 
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
 
    return result;
}

_D3DVECTOR MyNormalize (const _D3DVECTOR& v);
//This function is defined as follows:

inline _D3DVECTOR MyNormalize ( const _D3DVECTOR& v)
{
	D3DVECTOR v1;
	v1.x= v.x/MyMagnitude(v);
	v1.y= v.y/MyMagnitude(v);
	v1.z= v.z/MyMagnitude(v);
   return v1;
}

inline VOID D3DUtil_SetIdentityMatrix( D3DMATRIX& m )
{
    m._12 = m._13 = m._14 = m._21 = m._23 = m._24 = 0.0f;
    m._31 = m._32 = m._34 = m._41 = m._42 = m._43 = 0.0f;
    m._11 = m._22 = m._33 = m._44 = 1.0f;
}

VOID D3DUtil_InitMaterial( D3DMATERIAL7& mtrl, FLOAT r=0.0f, FLOAT g=0.0f,
                           FLOAT b=0.0f, FLOAT a=1.0f );

VOID D3DUtil_InitMaterial( D3DMATERIAL7& mtrl, FLOAT r, FLOAT g, FLOAT b,
                           FLOAT a )
{
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL7) );
    mtrl.dcvDiffuse.r = mtrl.dcvAmbient.r = r;
    mtrl.dcvDiffuse.g = mtrl.dcvAmbient.g = g;
    mtrl.dcvDiffuse.b = mtrl.dcvAmbient.b = b;
    mtrl.dcvDiffuse.a = mtrl.dcvAmbient.a = a;
   
}



CD3DFileObject::CD3DFileObject(TCHAR* strName )
{
	
    m_pNext        = NULL;
    m_pChild       = NULL;
    m_strName[0]   = 0;
    m_bHasMeshData = FALSE;

    if( strName )
        lstrcpy( m_strName, strName );

    // Set a default matrix
    D3DUtil_SetIdentityMatrix( m_mat );

    // Set a default material
    D3DUtil_InitMaterial( m_Material[0].m_mtrl, 1.0f, 1.0f, 1.0f );
    ZeroMemory( m_Material, sizeof(m_Material) );
    m_dwNumMaterials = 0;
    m_bHasAlpha      = FALSE;

    // Clear out vertex data
    m_dwNumVertices = 0L;
    m_pVertices     = NULL;
    m_dwNumIndices  = 0L;
    m_pIndices      = NULL;
}

CD3DFileObject::~CD3DFileObject(void)
{
    SAFE_DELETE( m_pChild );
    SAFE_DELETE( m_pNext );

    for( DWORD i=0; i<m_dwNumMaterials; i++ )
        //D3DTextr_DestroyTexture( m_Material[i].m_strTexture );

    SAFE_DELETE( m_pVertices );
    SAFE_DELETE( m_pIndices );
}

DWORD GetNumIndices( DWORD* pFaceData, DWORD dwNumFaces )
{
    DWORD dwNumIndices = 0;
    while( dwNumFaces-- > 0 )
    {
        dwNumIndices += (*pFaceData-2)*3;
        pFaceData += *pFaceData + 1;
    }

    return dwNumIndices;
}

//-----------------------------------------------------------------------------
// Name: SetMeshGeometry()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CD3DFileObject::SetMeshGeometry( D3DVECTOR* pVertexData,
                                     DWORD dwNumVertices, DWORD* pFaceData,
                                     DWORD dwNumFaces )
{
    // Set up vertices
    m_dwNumVertices = dwNumVertices;
    m_pVertices     = new D3DVERTEX[m_dwNumVertices];
    if( NULL == m_pVertices )
        return E_FAIL;

    for( DWORD i=0; i< m_dwNumVertices; i++ )
    {
        ZeroMemory( &m_pVertices[i], sizeof(D3DVERTEX) );
        m_pVertices[i].x = pVertexData[i].x;
        m_pVertices[i].y = pVertexData[i].y;
        m_pVertices[i].z = pVertexData[i].z;
    }

    // Count the number of indices (converting n-sided faces to triangles)
    m_dwNumIndices = GetNumIndices( pFaceData, dwNumFaces );

    // Allocate memory for the indices, you must call AddFace() to set the vertices
    m_pIndices = new WORD[m_dwNumIndices];

    if( NULL == m_pIndices )
        return E_FAIL;

    m_bHasMeshData  = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DFileObject::AddChild( CD3DFileObject* pChild )
{
    if( m_pChild )
        m_pChild->AddNext( pChild );
    else
        m_pChild = pChild;
}

//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DFileObject::AddNext( CD3DFileObject* pNext )
{
    if( m_pNext )
        m_pNext->AddNext( pNext );
    else
        m_pNext = pNext;
}

VOID CD3DFileObject::SetMaterialData( DWORD dwMaterial, D3DMATERIAL7* pmtrl,
                                      TCHAR* strName )
{
    if( dwMaterial < MAX_MATERIAL )
    {
        m_Material[dwMaterial].m_mtrl = *pmtrl;
        lstrcpyn( m_Material[dwMaterial].m_strTexture, strName, MAX_TEXTURE_NAME );
		
		// for alpha
        if( pmtrl->diffuse.a < 1.0f )
		m_bHasAlpha = TRUE;
    }
}




//-----------------------------------------------------------------------------
// Name: AddFace()
// Desc: Adds one or more faces to a material slot in a Mesh. Note: this must
//       be called in order (material 0 first, then 1, ...)
//-----------------------------------------------------------------------------
VOID CD3DFileObject::AddFace( DWORD dwMaterial, DWORD* pFaceData,
                              DWORD dwNumFaces )
{
	m_dwNumFaces = dwNumFaces;
    // Make sure dwMaterial is in range
    if( dwMaterial >= MAX_MATERIAL)
        return;

    // Update the material count
    if( m_dwNumMaterials < dwMaterial+1 )
        m_dwNumMaterials = dwMaterial+1;

    // add indices to the end
    WORD* pIndices = m_pIndices;
    for( DWORD i=0; i<=dwMaterial; i++ )
        pIndices += m_Material[i].m_dwNumIndices;

    // Assign the indices (build a triangle fan for high-order polygons)
    while( dwNumFaces-- )
    {
        DWORD dwNumVerticesPerFace = *pFaceData++;

        for( DWORD i=2; i<dwNumVerticesPerFace; i++ )
        {
            m_Material[dwMaterial].m_dwNumIndices += 3;
            *pIndices++ = (WORD)pFaceData[0];
            *pIndices++ = (WORD)pFaceData[i-1];
            *pIndices++ = (WORD)pFaceData[i];
        }

        pFaceData += dwNumVerticesPerFace;
    }
}

const TCHAR* D3DUtil_GetDXSDKMediaPath()
{
    static TCHAR strNull[2] = _T("");
    static TCHAR strPath[512];
    HKEY  key;
    DWORD type, size = 512;

    // Open the appropriate registry key
    LONG result = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                _T("Software\\Microsoft\\DirectX"),
                                0, KEY_READ, &key );
    if( ERROR_SUCCESS != result )
        return strNull;

    result = RegQueryValueEx( key, _T("DXSDK Samples Path"), NULL,
                              &type, (BYTE*)strPath, &size );
    RegCloseKey( key );

    if( ERROR_SUCCESS != result )
        return strNull;

    lstrcat( strPath, _T("\\D3DRM\\Media\\") );

    return strPath;
}

HRESULT ParseMaterial( LPDIRECTXFILEDATA pFileData, CD3DFileObject* pMesh,
                       DWORD dwMaterial )
{
    // Read data from the file
    LONG  pData;
    DWORD dwSize;
    TCHAR strTexture[128];

    if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return NULL;

    // Set the material properties for the mesh
    D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    memcpy( &mtrl.diffuse,  (VOID*)(pData+0),  sizeof(FLOAT)*4 );
    memcpy( &mtrl.ambient,  (VOID*)(pData+0),  sizeof(FLOAT)*3 );
    memcpy( &mtrl.power,    (VOID*)(pData+16), sizeof(FLOAT)*1 );
    memcpy( &mtrl.specular, (VOID*)(pData+20), sizeof(FLOAT)*3 );
    memcpy( &mtrl.emissive, (VOID*)(pData+32), sizeof(FLOAT)*3 );
    strTexture[0] = 0;

    LPDIRECTXFILEOBJECT pChildObj;
    if( SUCCEEDED( pFileData->GetNextObject(&pChildObj) ) )
    {
        LPDIRECTXFILEDATA pChildData;

        if( SUCCEEDED( pChildObj->QueryInterface( IID_IDirectXFileData,
                                                    (VOID**)&pChildData) ) )
        {
            const GUID* pguid;
            pChildData->GetType( &pguid );

            if( TID_D3DRMTextureFilename == *pguid )
            {
                TCHAR** string;

                if( FAILED( pChildData->GetData( NULL, &dwSize, (VOID**)&string ) ) )
                    return NULL;
				
                lstrcpyn( strTexture, *string, 128 );
            }

            pChildData->Release();
        }

        pChildObj->Release();
    }

    pMesh->SetMaterialData( dwMaterial, &mtrl, strTexture );

    return S_OK;
}


HRESULT ParseMeshMaterialList( LPDIRECTXFILEDATA pFileData,
                               CD3DFileObject* pMesh )
{
    LPDIRECTXFILEOBJECT        pChildObj;
    LPDIRECTXFILEDATA          pChildData;
    LPDIRECTXFILEDATAREFERENCE pChildDataRef;
    DWORD                      dwMaterial = 0;

    while( SUCCEEDED( pFileData->GetNextObject( &pChildObj ) ) )
    {
        if( SUCCEEDED( pChildObj->QueryInterface( IID_IDirectXFileData,
                                                    (VOID**)&pChildData) ) )
        {
            const GUID* pguid;
            pChildData->GetType( &pguid );

            if( TID_D3DRMMaterial == *pguid )
            {
                ParseMaterial(pChildData, pMesh, dwMaterial++);
            }

            pChildData->Release();
        }

        if( SUCCEEDED( pChildObj->QueryInterface( IID_IDirectXFileDataReference,
                                                    (VOID**)&pChildDataRef) ) )
        {
            if( SUCCEEDED( pChildDataRef->Resolve( &pChildData ) ) )
            {
                const GUID* pguid;
                pChildData->GetType( &pguid );

                if( TID_D3DRMMaterial == *pguid )
                {
                    ParseMaterial( pChildData, pMesh, dwMaterial++ );
                }

                pChildData->Release();
            }
            pChildDataRef->Release();
        }

        pChildObj->Release();
    }
    return S_OK;
}

DWORD* GetFace( DWORD* pFaceData, DWORD dwFace )
{
    for( DWORD i=0; i<dwFace; i++ )
        pFaceData += (*pFaceData) + 1;

    return pFaceData;
}

HRESULT ParseMesh( LPDIRECTXFILEDATA pFileData, CD3DFileObject* pParentFrame, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3 )
{
	
	
	DWORD* pMatFace;
	DWORD      dwNumVertices;
    D3DVECTOR* pVertices;
    DWORD      dwNumFaces;
    DWORD*     pFaceData; 
	DWORD      dwNumNormals;
    D3DVECTOR* pNormals;
	DWORD  dwNumTexCoords;
    FLOAT* pTexCoords;
	DWORD  dwNumMaterials;
    DWORD  dwNumMatFaces;

    DWORD dwNameLen=80;
    TCHAR strName[80];
	// Create the Mesh object
    CD3DFileObject* pMesh;
    if( FAILED( pFileData->GetName((LPSTR)strName, &dwNameLen ) ) )
	{
        return E_FAIL;
	}
	else
	{
		pMesh = new CD3DFileObject( strName );
		
		rm3->CreateMeshBuilder( &pMesh->mb );
		pMesh->mb->SetName( (LPCSTR)strName );
	}

    // Read the Mesh data from the file
    LONG  pData;
    DWORD dwSize;
    if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;

		dwNumVertices =    *((DWORD*)pData); pData += 4;
		pVertices     = ((D3DVECTOR*)pData); pData += 12*dwNumVertices;
		dwNumFaces    =    *((DWORD*)pData); pData += 4;
		pFaceData     =      (DWORD*)pData;
	
	
    // Create the Mesh object
   
		pMesh->m_dwFaceCount = dwNumFaces;
		
    pMesh->SetMeshGeometry( pVertices, dwNumVertices, pFaceData, dwNumFaces );
	
	
    BOOL bHasNormals = FALSE;
    BOOL bHasMaterials = FALSE;

    // Enumerate child objects.
    LPDIRECTXFILEOBJECT pChildObj;
    while( SUCCEEDED( pFileData->GetNextObject( &pChildObj ) ) )
    {
        LPDIRECTXFILEDATA pChildData;

        if( SUCCEEDED( pChildObj->QueryInterface( IID_IDirectXFileData,
                                                  (VOID**)&pChildData ) ) )
        {
            const GUID* pGUID;
            LONG        pData;
            DWORD       dwSize;

            pChildData->GetType( &pGUID );
            if( FAILED( pChildData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
            {
                delete pMesh;
                return NULL;
            }

            if( TID_D3DRMMeshMaterialList == *pGUID )
            {
                dwNumMaterials = *((DWORD*)pData);   pData += 4;
                dwNumMatFaces  = *((DWORD*)pData);   pData += 4;
                pMatFace       =   (DWORD*)pData;
				pMesh->m_pMatFaces = new DWORD[dwNumMatFaces];
				for(DWORD tm = 0;tm<dwNumMatFaces;tm++)
					pMesh->m_pMatFaces[tm]=pMatFace[tm];
				pMesh->SetMeshMaterialData( pMatFace );

                if( dwNumMaterials == 1 || dwNumMatFaces != dwNumFaces )
                {
                    // Only one material add all faces at once
					pMesh->AddFace( 0, pFaceData, dwNumFaces );
					
                }
                else
                {
                    // Multiple materials, add in sorted order
                    for( DWORD mat=0; mat<dwNumMaterials; mat++ )
                    {
                        for( DWORD face=0; face<dwNumMatFaces; face++ )
                        {
                            if( pMatFace[face] == mat )
                                pMesh->AddFace( mat, GetFace( pFaceData, face ), 1 );
                        }
                    }
                }

                ParseMeshMaterialList( pChildData, pMesh );
                bHasMaterials = TRUE;
            }

            if( TID_D3DRMMeshNormals == *pGUID )
            {
                dwNumNormals = *((DWORD*)pData);
                pNormals     = (D3DVECTOR*)(pData+4);

                if( dwNumNormals == dwNumVertices )
                {
                    pMesh->SetNormals( pNormals );
                    bHasNormals = TRUE;
				}
            }

            if( TID_D3DRMMeshTextureCoords == *pGUID )
            {
                // Copy the texture coords into the mesh's vertices
					dwNumTexCoords = *((DWORD*)pData);
					pTexCoords     = (FLOAT*)(pData+4);

                if( dwNumTexCoords == dwNumVertices )
				{
                    pMesh->SetTextureCoords( pTexCoords );
									
				}
				}

            pChildData->Release();
        }

        pChildObj->Release();
    }

    if( FALSE == bHasMaterials )
        pMesh->AddFace( 0, pFaceData, dwNumFaces );

    if( FALSE == bHasNormals )
        pMesh->ComputeNormals();
	
	for( DWORD i = 0;i<dwNumVertices;i++)
	{
		D3DVECTOR v = *(pVertices+i);
			pMesh->mb->AddVertex( v.x, v.y, v.z );
		D3DVECTOR n = *(pNormals+i);
			pMesh->mb->AddNormal( n.x, n.y, n.z );
	}

	if(dwNumFaces>0)
	{
					
					DWORD num = 0;
					for(DWORD j=0;j<dwNumFaces;j++)
					{
						LPDIRECT3DRMFACE2 face;
						rm3->CreateFace(&face);
						pMesh->mb->AddFace(face);
							DWORD vCnt = *(pFaceData+num);
							num++;
						for(DWORD k =0;k<vCnt;k++)
						{
							face->AddVertexAndNormalIndexed( *(pFaceData+num), *(pFaceData+num));
							num++;
						}

						LPDIRECT3DRMMATERIAL2 m2;
						rm3->CreateMaterial( 10.0F, &m2 );
						
						if(pMesh->m_dwNumMaterials==0)
						{
							
						}
						else if(pMesh->m_dwNumMaterials==1)
						{
							m2->SetPower(pMesh->m_Material[0].m_mtrl.power);
							m2->SetSpecular(pMesh->m_Material[0].m_mtrl.specular.r, pMesh->m_Material[0].m_mtrl.specular.g, pMesh->m_Material[0].m_mtrl.specular.b );
							m2->SetEmissive(pMesh->m_Material[0].m_mtrl.emissive.r, pMesh->m_Material[0].m_mtrl.emissive.g, pMesh->m_Material[0].m_mtrl.emissive.b );
							m2->SetAmbient(pMesh->m_Material[0].m_mtrl.ambient.r, pMesh->m_Material[0].m_mtrl.ambient.g, pMesh->m_Material[0].m_mtrl.ambient.b );
							face->SetMaterial(m2);
							face->SetColor(RGBA_MAKE((int)(pMesh->m_Material[0].m_mtrl.diffuse.r*255), 
								(int)(pMesh->m_Material[0].m_mtrl.diffuse.g*255), 
								(int)(pMesh->m_Material[0].m_mtrl.diffuse.b*255), 
								(int)(pMesh->m_Material[0].m_mtrl.diffuse.a*255)));
							LPDIRECT3DRMTEXTURE3 tex;
							if(D3DRM_OK==rm3->LoadTexture((LPSTR)pMesh->m_Material[0].m_strTexture, &tex))
							{
								face->SetTexture(tex);
							}
						}
						else if(pMesh->m_dwNumMaterials>1)
						{
							DWORD n = pMatFace[j];
							
							m2->SetPower(pMesh->m_Material[n].m_mtrl.power);
							m2->SetSpecular(pMesh->m_Material[n].m_mtrl.specular.r, pMesh->m_Material[n].m_mtrl.specular.g, pMesh->m_Material[n].m_mtrl.specular.b );
							m2->SetEmissive(pMesh->m_Material[n].m_mtrl.emissive.r, pMesh->m_Material[n].m_mtrl.emissive.g, pMesh->m_Material[n].m_mtrl.emissive.b );
							m2->SetAmbient(pMesh->m_Material[n].m_mtrl.ambient.r, pMesh->m_Material[n].m_mtrl.ambient.g, pMesh->m_Material[n].m_mtrl.ambient.b );
							face->SetMaterial(m2);
							face->SetColor(RGBA_MAKE((int)(pMesh->m_Material[n].m_mtrl.diffuse.r*255), 
								(int)(pMesh->m_Material[n].m_mtrl.diffuse.g*255), 
								(int)(pMesh->m_Material[n].m_mtrl.diffuse.b*255), 
								(int)(pMesh->m_Material[n].m_mtrl.diffuse.a*255)));
							LPDIRECT3DRMTEXTURE3 tex;
							if(D3DRM_OK==rm3->LoadTexture((LPSTR)pMesh->m_Material[n].m_strTexture, &tex))
							{
								face->SetTexture(tex);
							}

						}
						m2->Release();
					face->Release();
					}
					
	}// eo if(dwNumFaces>0)
	DWORD tc = 0;
	if( dwNumTexCoords == dwNumVertices )
	{
		for( DWORD i = 0;i<dwNumTexCoords;i++)
		{
			pMesh->mb->SetTextureCoordinates( i, pTexCoords[tc], pTexCoords[tc+1] );
			tc+=2;
		}

	}

    pParentFrame->AddChild( pMesh );
	f->AddVisual(pMesh->mb);
	m_iMeshCount++;
    return S_OK;
}


HRESULT ParseFrame( LPDIRECTXFILEDATA pFileData, CD3DFileObject* pParentFrame, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3, LPDIRECT3DRMMESHBUILDER3 mb )
{

	m_iFrameCount++;
    DWORD dwNameLen=80;
    TCHAR strName[80];


    if( FAILED( pFileData->GetName((LPSTR)strName, &dwNameLen ) ) )
	{
        return E_FAIL;
	}
	else{ 
		f->SetName((LPSTR)strName);
	}

    CD3DFileObject* pFrame = new CD3DFileObject( strName );
	
    // Enumerate child objects.
    LPDIRECTXFILEOBJECT pChildObj;
    while( SUCCEEDED( pFileData->GetNextObject( &pChildObj ) ) )
    {
        LPDIRECTXFILEDATA pChildData;
        if( SUCCEEDED( pChildObj->QueryInterface( IID_IDirectXFileData,
                            (VOID**)&pChildData ) ) )
        {
            const GUID* pGUID;
            pChildData->GetType( &pGUID );


            if( TID_D3DRMFrame == *pGUID )
			{
				LPDIRECT3DRMFRAME3 child;
				rm3->CreateFrame( f, &child);
                ParseFrame( pChildData, pFrame, child, rm3, mb );
			}

            if( TID_D3DRMMesh == *pGUID )
                ParseMesh( pChildData, pFrame, f, rm3 );

            if( TID_D3DRMFrameTransformMatrix == *pGUID )
            {
                DWORD dwSize;
                VOID* pData;
                if( FAILED( pChildData->GetData( NULL, &dwSize, &pData ) ) )
                {
                    delete pFrame;
                    return NULL;
                }

                if( dwSize == sizeof(D3DMATRIX) )
                {
                    // Convert from a left- to a right-handed cordinate system
                    D3DMATRIX* pmatFrame = (D3DMATRIX*)pData;
                    pmatFrame->_13 *= -1.0f;
                    pmatFrame->_31 *= -1.0f;
                    pmatFrame->_23 *= -1.0f;
                    pmatFrame->_32 *= -1.0f;
                    pmatFrame->_43 *= -1.0f;
					float m[4][4];
					m[0][0]=pmatFrame->_11;
					m[0][1]=pmatFrame->_12;
					m[0][2]=pmatFrame->_13;
					m[0][3]=pmatFrame->_14;
					m[1][0]=pmatFrame->_21;
					m[1][1]=pmatFrame->_22;
					m[1][2]=pmatFrame->_23;
					m[1][3]=pmatFrame->_24;
					m[2][0]=pmatFrame->_31;
					m[2][1]=pmatFrame->_32;
					m[2][2]=pmatFrame->_33;
					m[2][3]=pmatFrame->_34;
					m[3][0]=pmatFrame->_41;
					m[3][1]=pmatFrame->_42;
					m[3][2]=pmatFrame->_43;
					m[3][3]=pmatFrame->_44;

					f->AddTransform( D3DRMCOMBINE_REPLACE, m);
                    pFrame->SetMatrix( pmatFrame );
                }
            }

            pChildData->Release();
        }

        pChildObj->Release();
    }

    pParentFrame->AddChild( pFrame );
    return S_OK;
}

CD3DFile::CD3DFile()
{
	m_iMeshCount = 0;
    m_pRoot = NULL;
}

//-----------------------------------------------------------------------------
// Name: ~CD3DFile()
// Desc: Class destructor
//-----------------------------------------------------------------------------
CD3DFile::~CD3DFile()
{
    SAFE_DELETE( m_pRoot );
}

HRESULT CD3DFile::Load( TCHAR* strFilename, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3, LPDIRECT3DRMMESHBUILDER3 mb )
{
    HRESULT                 hr;
    LPDIRECTXFILE           pDXFile;
    LPDIRECTXFILEENUMOBJECT pEnumObj;
    LPDIRECTXFILEDATA       pFileData;
    const GUID*             pGUID;
    CD3DFileObject*         pFrame = NULL;
	
    // Cleanup any existing object
    SAFE_DELETE( m_pRoot );

    // Create the file object, and register the D3DRM templates for .X files
    if( FAILED( DirectXFileCreate( &pDXFile ) ) )
        return E_FAIL;
    if( FAILED( pDXFile->RegisterTemplates( (VOID*)D3DRM_XTEMPLATES,
                                            D3DRM_XTEMPLATE_BYTES ) ) )
    {
        pDXFile->Release();
        return E_FAIL;
    }

    // Create an enumerator object, to enumerate through the .X file objects.
    // This will open the file in the current directory.
    hr = pDXFile->CreateEnumObject( strFilename, DXFILELOAD_FROMFILE, &pEnumObj );

    if( FAILED(hr) )
    {
        TCHAR strPath[512] = _T("");
        lstrcat( strPath, D3DUtil_GetDXSDKMediaPath() );
        lstrcat( strPath, strFilename );
        
        hr = pDXFile->CreateEnumObject( strPath, DXFILELOAD_FROMFILE,
                                        &pEnumObj );
        if( FAILED(hr) )
        {
            pDXFile->Release();
            return hr;
        }
    }

    // Create a root object for the X file object
    m_pRoot = new CD3DFileObject( _T("D3DFile_Root") );

    // Cycle through each object. Parse meshes and frames as appropriate
    while( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
        pFileData->GetType( &pGUID );

        if( *pGUID == TID_D3DRMFrame )
		{
			LPDIRECT3DRMFRAME3 fr;
			rm3->CreateFrame( f, &fr );
            ParseFrame( pFileData, m_pRoot, fr, rm3, mb );
		}

        if( *pGUID == TID_D3DRMMesh )
		{
            HRESULT hr = ParseMesh( pFileData, m_pRoot, f, rm3 );
			
		}

        pFileData->Release();
    }

    // Success will result in hr == DXFILEERR_NOMOREOBJECTS
    if( DXFILEERR_NOMOREOBJECTS == hr ) 
        hr = S_OK;
    else
        SAFE_DELETE( m_pRoot );

    pEnumObj->Release();
    pDXFile->Release();

    return hr;
}

//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DFileObject::GetMeshGeometry( D3DVERTEX** ppVertices, DWORD* pdwNumVertices,
                                         WORD** ppIndices, DWORD* pdwNumIndices )
{
    if( ppVertices )     *ppVertices     = m_pVertices;
    if( pdwNumVertices ) *pdwNumVertices = m_dwNumVertices;
    if( ppIndices )      *ppIndices      = m_pIndices;
    if( pdwNumIndices )  *pdwNumIndices  = m_dwNumIndices;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DFileObject::ComputeNormals()
{
    D3DVECTOR* pNormals = new D3DVECTOR[m_dwNumVertices];
    ZeroMemory( pNormals, sizeof(D3DVECTOR)*m_dwNumVertices );

    for( DWORD i=0; i<m_dwNumIndices; i+=3 )
    {
        WORD a = m_pIndices[i+0];
        WORD b = m_pIndices[i+1];
        WORD c = m_pIndices[i+2];

        D3DVECTOR* v1 = (D3DVECTOR*)&m_pVertices[a];
        D3DVECTOR* v2 = (D3DVECTOR*)&m_pVertices[b];
        D3DVECTOR* v3 = (D3DVECTOR*)&m_pVertices[c];
		D3DVECTOR r1;
		D3DVECTOR r2;
		D3DRMVectorSubtract( &r1, v2, v1);
		D3DRMVectorSubtract( &r2, v3, v2);

        D3DVECTOR n = MyNormalize( MyCrossProduct( r1, r2 ) );

        pNormals[a].x += n.x;
        pNormals[b].x += n.x;
        pNormals[c].x += n.x;
		pNormals[a].y += n.y;
        pNormals[b].y += n.y;
        pNormals[c].y += n.y;
		pNormals[a].z += n.z;
        pNormals[b].z += n.z;
        pNormals[c].z += n.z;
    }

    // Assign the newly computed normals back to the vertices
    for(DWORD i=0; i<m_dwNumVertices; i++ )
    {
        // Provide some relief to bogus normals
        if( MyMagnitude( pNormals[i] ) < 0.1f ) 
            pNormals[i].x = 0.0f;
			pNormals[i].y = 0.0f;
			pNormals[i].z = 1.0f;

        
        pNormals[i] = MyNormalize( pNormals[i] );
        m_pVertices[i].nx = pNormals[i].x;
        m_pVertices[i].ny = pNormals[i].y;
        m_pVertices[i].nz = pNormals[i].z;
    }

    delete pNormals;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DFileObject::SetNormals( D3DVECTOR* pNormals )
{
    for( DWORD i=0; i<m_dwNumVertices; i++ )
    {
        m_pVertices[i].nx = pNormals[i].x;
        m_pVertices[i].ny = pNormals[i].y;
        m_pVertices[i].nz = pNormals[i].z;
    }
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DFileObject::SetTextureCoords( FLOAT* pTexCoords )
{
    for( DWORD i=0; i<m_dwNumVertices; i++ )
    {
        m_pVertices[i].tu = pTexCoords[2*i+0];
        m_pVertices[i].tv = pTexCoords[2*i+1];
    }
}

VOID   CD3DFileObject::SetMeshMaterialData( DWORD* wList )
{
	if(m_dwNumMaterials>1)
	for( DWORD i=0; i<m_dwNumIndices; i++ )
    {
        m_pMatFaces[i] = wList[i];
	}
}

HRESULT CD3DFile::GetMeshVertices( TCHAR* strName, D3DVERTEX** ppVertices,
                                   DWORD* pdwNumVertices )
{
    CD3DFileObject* pObject = FindObject( strName );
    if( pObject )
        return pObject->GetMeshGeometry( ppVertices, pdwNumVertices, NULL, NULL );

    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: GetMeshVertices()
// Desc: Traverse the hierarchy of frames and meshes that make up the file
//       object, and retrieves the vertices for the specified mesh.
//-----------------------------------------------------------------------------
HRESULT CD3DFile::GetMeshIndices( TCHAR* strName, WORD** ppIndices,
                                  DWORD* pdwNumIndices )
{
    CD3DFileObject* pObject = FindObject( strName );
    if( pObject )
        return pObject->GetMeshGeometry( NULL, NULL, ppIndices, pdwNumIndices );

    return E_FAIL;
}

//-----------------------------------------------------------------------------
// Name: FindMeshCB()
// Desc: Callback to scale a mesh
//-----------------------------------------------------------------------------
BOOL FindMeshCB( CD3DFileObject* pFileObject, D3DMATRIX*, VOID* pContext )
{
    struct FINDMESHRECORD
    {
        TCHAR*          strName;
        CD3DFileObject* pObject;
    };

    FINDMESHRECORD* data = (FINDMESHRECORD*)pContext;
    
    if( 0 == lstrcmpi( data->strName, pFileObject->GetName() ) )
    {
        data->pObject = pFileObject;
        return TRUE;
    }

    // Keep enumerating
    return FALSE;
}

CD3DFileObject* CD3DFile::FindObject( TCHAR* strName )
{
    if( NULL == strName )
        return m_pRoot;

    struct FINDMESHRECORD
    {
        TCHAR*          strName;
        CD3DFileObject* pObject;
    };

    FINDMESHRECORD data = { strName, NULL };

    EnumObjects( FindMeshCB, NULL, (VOID*)&data );
    return data.pObject;
}


VOID D3DMath_MatrixMultiply( D3DMATRIX& q, D3DMATRIX& a, D3DMATRIX& b )
{
    FLOAT* pA = (FLOAT*)&a;
    FLOAT* pB = (FLOAT*)&b;
    FLOAT  pM[16];

    ZeroMemory( pM, sizeof(D3DMATRIX) );

    for( WORD i=0; i<4; i++ ) 
        for( WORD j=0; j<4; j++ ) 
            for( WORD k=0; k<4; k++ ) 
                pM[4*i+j] +=  pA[4*i+k] * pB[4*k+j];

    memcpy( &q, pM, sizeof(D3DMATRIX) );
}

//-----------------------------------------------------------------------------
// Name: EnumObjects()
// Desc: Enumerates all objects in the file.
//-----------------------------------------------------------------------------
BOOL CD3DFileObject::EnumObjects( BOOL (*fnCallback)(CD3DFileObject*,D3DMATRIX*,VOID*),
                                  D3DMATRIX* pmat, VOID* pContext )
{
    if( fnCallback( this, pmat, pContext ) == TRUE )
        return TRUE;

    if( m_pChild )
    {
        // Concat matrix set
        D3DMATRIX matSave = (*pmat);
		D3DMath_MatrixMultiply( *pmat, *pmat, m_mat );
        //(*pmat) = (*pmat) * m_mat;
    
        if( m_pChild->EnumObjects( fnCallback, pmat, pContext ) == TRUE )
            return TRUE;

        // Restore matrix set
        (*pmat) = matSave;
    }

    if( m_pNext )
        if( m_pNext->EnumObjects( fnCallback, pmat, pContext ) == TRUE )
            return TRUE;

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: EnumObjects()
// Desc: Enumerates all objects in the file.
//-----------------------------------------------------------------------------
VOID CD3DFile::EnumObjects( BOOL (*fnCallback)(CD3DFileObject*,D3DMATRIX*,VOID*),
                            D3DMATRIX* pmat, VOID* pContext )
{
    if( m_pRoot )
    {
        D3DMATRIX mat;

        if( pmat )
            mat = *pmat;
        else
            D3DUtil_SetIdentityMatrix( mat );

        m_pRoot->EnumObjects( fnCallback, &mat, pContext );
    }
}

void CD3DFile::SetMeshCount( DWORD cnt )
{
	m_iMeshCount=cnt;
}
void CD3DFile::SetFrameCount( DWORD cnt )
{
	m_iFrameCount = cnt;
}

DWORD CD3DFile::GetMeshCount()
{
	return m_iMeshCount;
}
DWORD CD3DFile::GetFrameCount()
{
	return m_iFrameCount;
}
 