#include "stdafx.h"
#include "dxsdk8\include\d3drm.h"
#include "dxsdk8\include\dxfile.h"
#include "dxsdk8\include\rmxfguid.h"
#include <math.h>
#include "hobread.h"
#include "hdxdatatypes.h"
#include "myxtmpl.h"


#define SAFE_HOB_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_HOB_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

DWORD m_iMeshCountHOB = 0;
DWORD m_iFrameCountHOB = 0;
//ZeroMemory(
D3DVALUE HOBSquareMagnitude ( const _D3DVECTOR& v);
//This function is defined as follows:

inline D3DVALUE HOBSquareMagnitude (const _D3DVECTOR& v)
{
   return v.x*v.x + v.y*v.y + v.z*v.z;
}

D3DVALUE HOBMagnitude (const _D3DVECTOR& v);
//This function is defined as follows:

inline D3DVALUE HOBMagnitude (const _D3DVECTOR& v)
{
   return (D3DVALUE) sqrt(HOBSquareMagnitude(v));
}

_D3DVECTOR HOBCrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
//This function is defined as follows:

inline _D3DVECTOR HOBCrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
    D3DVECTOR result;
 
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
 
    return result;
}

_D3DVECTOR HOBNormalize (const _D3DVECTOR& v);
//This function is defined as follows:

inline _D3DVECTOR HOBNormalize ( const _D3DVECTOR& v)
{
	D3DVECTOR v1;
	v1.x= v.x/HOBMagnitude(v);
	v1.y= v.y/HOBMagnitude(v);
	v1.z= v.z/HOBMagnitude(v);
   return v1;
}

inline VOID D3DHOB_SetIdentityMatrix( D3DMATRIX& m )
{
    m._12 = m._13 = m._14 = m._21 = m._23 = m._24 = 0.0f;
    m._31 = m._32 = m._34 = m._41 = m._42 = m._43 = 0.0f;
    m._11 = m._22 = m._33 = m._44 = 1.0f;
}

VOID D3DHOB_InitMaterial( D3DMATERIAL7& mtrl, FLOAT r=0.0f, FLOAT g=0.0f,
                           FLOAT b=0.0f, FLOAT a=1.0f );

VOID D3DHOB_InitMaterial( D3DMATERIAL7& mtrl, FLOAT r, FLOAT g, FLOAT b,
                           FLOAT a )
{
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL7) );
    mtrl.dcvDiffuse.r = mtrl.dcvAmbient.r = r;
    mtrl.dcvDiffuse.g = mtrl.dcvAmbient.g = g;
    mtrl.dcvDiffuse.b = mtrl.dcvAmbient.b = b;
    mtrl.dcvDiffuse.a = mtrl.dcvAmbient.a = a;
   
}

CHOBFileObject::CHOBFileObject(TCHAR* strName )
{
	
    //m_pNext        = NULL;
    //m_pChild       = NULL;
    m_strName[0]   = 0;
    m_bHasMeshData = FALSE;

    if( strName )
        lstrcpy( m_strName, strName );

    // Set a default matrix
    D3DHOB_SetIdentityMatrix( m_mat );

    // Set a default material
    D3DHOB_InitMaterial( m_Material[0].m_mtrl, 1.0f, 1.0f, 1.0f );
    ZeroMemory( m_Material, sizeof(m_Material) );
    m_dwNumMaterials = 0;
    m_bHasAlpha      = FALSE;

    // Clear out vertex data
    m_dwNumVertices = 0L;
    m_pVertices     = NULL;
    m_dwNumIndices  = 0L;
    m_pIndices      = NULL;
}

CHOBFileObject::~CHOBFileObject(void)
{
    //SAFE_HOB_DELETE( m_pChild );
    //SAFE_HOB_DELETE( m_pNext );

    //for( DWORD i=0; i<m_dwNumMaterials; i++ )
        //D3DTextr_DestroyTexture( m_Material[i].m_strTexture );

//    SAFE_HOB_DELETE( m_pVertices );
 //   SAFE_HOB_DELETE( m_pIndices );
}

///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

DWORD GetNumIndicesHOB( DWORD* pFaceData, DWORD dwNumFaces )
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
HRESULT CHOBFileObject::SetMeshGeometry( D3DVECTOR* pVertexData,
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

	m_dwNumFaces = dwNumFaces;
    // Count the number of indices (converting n-sided faces to triangles)
    m_dwNumIndices = GetNumIndicesHOB( pFaceData, dwNumFaces );

    // Allocate memory for the indices, you must call AddFace() to set the vertices
    m_pIndices = new WORD[m_dwNumIndices];

    if( NULL == m_pIndices )
        return E_FAIL;

    m_bHasMeshData  = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: AddFace()
// Desc: Adds one or more faces to a material slot in a Mesh. Note: this must
//       be called in order (material 0 first, then 1, ...)
//-----------------------------------------------------------------------------
VOID CHOBFileObject::AddFace( DWORD dwMaterial, DWORD* pFaceData,
                              DWORD dwNumFaces )
{
    // Make sure dwMaterial is in range
    if( dwMaterial >= HOBMAX_MATERIAL)
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

HRESULT ParseMaterial( LPDIRECTXFILEDATA pFileData, CHOBFileObject* pMesh,
                       DWORD item, LONG pData )
{
	TMyMaterial *mat = (TMyMaterial *)pData;

	
    // Set the material properties for the mesh
    D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
	mtrl.diffuse.r = (float)mat->r/255;
	mtrl.diffuse.g = (float)mat->g/255;
	mtrl.diffuse.b = (float)mat->b/255;
	mtrl.diffuse.a = (float)mat->a/255;
	
	mtrl.power = mat->power;
    mtrl.specular.r = mat->sRed;
	mtrl.specular.g = mat->sGreen;
	mtrl.specular.b = mat->sBlue;

	mtrl.emissive.r = mat->eRed;
	mtrl.emissive.g = mat->eGreen;
	mtrl.emissive.b = mat->eBlue;

	mtrl.ambient.r = mat->aRed;
	mtrl.ambient.g = mat->aGreen;
	mtrl.ambient.b = mat->aBlue;
	
	char *t = new char[mat->fNameCnt];

	int cnt = 0;
	for( DWORD i = 0;i<mat->fNameCnt;i++)
	{
		switch(mat->fileName[i])
		{
		case 7:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='a';cnt++;
			}
			break;
		case 8:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='b';cnt++;
			}
			break;
		case 9:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='t';cnt++;
			}
			break;
		case 10:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='n';cnt++;
			}
			break;
		case 11:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='v';cnt++;
			}
			break;
		case 12:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='f';cnt++;
			}
			break;
		case 13:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='r';cnt++;
			}
			break;
		case 0x3a:
			{
			t[cnt]=':';cnt++;
			t[cnt]='\\';cnt++;
			}
			break;
		case 0x5c:
			{
			t[cnt]='\\';cnt++;
			t[cnt]='\\';cnt++;
			}
			break;
		
		default:
			{
				t[cnt] = mat->fileName[i];cnt++;
					
			}break;
		
		}
	

	}

	lstrcpyn( pMesh->m_Material[item].m_strTexture, (CString)t, cnt );
		cnt=0;
	TCHAR *m = new TCHAR[mat->nNameCNT];
	for(DWORD i = 0;i<mat->nNameCNT;i++)
	{
		m[cnt] = mat->matName[i];cnt++;
	}

	lstrcpyn( pMesh->m_Material[item].m_MatName, m, cnt );
		
	if( item < HOBMAX_MATERIAL )
    {
        pMesh->m_Material[item].m_mtrl = mtrl;
    }
   
    return S_OK;
}

DWORD* GetFaceHOB( DWORD* pFaceData, DWORD dwFace )
{
    for( DWORD i=0; i<dwFace; i++ )
        pFaceData += (*pFaceData) + 1;

    return pFaceData;
}

HRESULT ParseMeshVertices( CHOBFileObject* pMesh, LPDIRECTXFILEDATA pFileData, LPDIRECTXFILEENUMOBJECT pEnumObj, CHOBFileObject* pParentFrame, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3, CPoints* meshPoints, CMAKERPTGROUPS* groups )
{
	HRESULT hr = 0;
	
	rm3->CreateMeshBuilder( &pMesh->mb );
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

	DWORD  dwNumPointGroups;

	DWORD  dwMaterial = 0;

    DWORD dwNameLen=80;
    TCHAR strName[80];
    if( FAILED( pFileData->GetName( (LPSTR)strName, &dwNameLen ) ) )
	{
        return E_FAIL;
	}
	else
	{
		pMesh->mb->SetName( (LPCSTR)strName );
	}

    // Read the Mesh data from the file
    LONG  pData;
    DWORD dwSize;
    if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;

	dwNumVertices  =  *((DWORD*)pData); pData += 4;
	pVertices     = ((D3DVECTOR*)pData); pData += 12*dwNumVertices;	

	if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
		const GUID*  pGUID;
	if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;
	    pFileData->GetType( &pGUID );
	
        if( *pGUID == DXFILEOBJ_MeshFaces )
		{
			dwNumFaces    =    *((DWORD*)pData); pData += 4;
			pFaceData     =      (DWORD*)pData;
			pMesh->SetFaceData(pFaceData);
		}
	
	}

	// Create the Mesh object
    //CHOBFileObject* pMesh = new CHOBFileObject( strName );
	
    pMesh->SetMeshGeometry( pVertices, dwNumVertices, pFaceData, dwNumFaces );

		meshPoints->x.deallocate();
		meshPoints->y.deallocate();
		meshPoints->z.deallocate();
		meshPoints->x.value = meshPoints->x.allocate(0);
		meshPoints->y.value = meshPoints->y.allocate(0);
		meshPoints->z.value = meshPoints->z.allocate(0);
		meshPoints->m_iNumPoints = pMesh->m_dwNumVertices;
		
		meshPoints->x.value = meshPoints->x.growByEmptyEnd( pMesh->m_dwNumVertices );
		meshPoints->y.value = meshPoints->y.growByEmptyEnd( pMesh->m_dwNumVertices );
		meshPoints->z.value = meshPoints->z.growByEmptyEnd( pMesh->m_dwNumVertices );
		
		for(DWORD vs=0;vs<pMesh->m_dwNumVertices;vs++)
		{
			meshPoints->x.set( vs, pMesh->m_pVertices[vs].x );
			meshPoints->y.set( vs, pMesh->m_pVertices[vs].y );
			meshPoints->z.set( vs, pMesh->m_pVertices[vs].z );
		}
	BOOL bHasNormals = FALSE;
	if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
		const GUID*  pGUID;
	if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;
	    pFileData->GetType( &pGUID );
	
        if( *pGUID == DXFILEOBJ_HDXNormals )
		{
			dwNumNormals =    *((DWORD*)pData); pData += 4;
			pNormals     = ((D3DVECTOR*)pData); pData += 12*dwNumNormals;
			bHasNormals = TRUE;
		}
	
	}

	if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
		const GUID*  pGUID;
	if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;
	    pFileData->GetType( &pGUID );
	
        if( *pGUID == DXFILEOBJ_TCoord )
		{
			dwNumTexCoords =    *((DWORD*)pData); pData += 4;
			pTexCoords     = ((float*)pData); pData += 12*dwNumNormals;
			 pMesh->SetTextureCoords( pTexCoords );
		}
	
	}
    

	BOOL bHasMaterials = FALSE;

	if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
		const GUID*  pGUID;
	if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;
	    pFileData->GetType( &pGUID );
	
        if( *pGUID == DXFILEOBJ_MyMaterialList )
		{
				dwNumMaterials = *((DWORD*)pData);   pData += 4;
                dwNumMatFaces  = *((DWORD*)pData);   pData += 4;
                pMatFace       =   (DWORD*)pData;
				

				pMesh->SetMeshMaterialData( pMatFace, dwNumMatFaces );

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
                                pMesh->AddFace( mat, GetFaceHOB( pFaceData, face ), 1 );
                        }
                    }
                }// eo else
		}
	
	}

	for( DWORD i = 0;i<dwNumMaterials;i++)
	{
		if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
		{
			const GUID*  pGUID;
			if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
				return E_FAIL;
				pFileData->GetType( &pGUID );
	
				if( *pGUID == DXFILEOBJ_MyMaterial )
				{
					hr = ParseMaterial( pFileData, pMesh, i, pData);	
				}
	
			}

				bHasMaterials = TRUE;
		}// eo i for



	if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
		const GUID*  pGUID;
	if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
        return E_FAIL;
	    pFileData->GetType( &pGUID );
	
        if( *pGUID == DXFILEOBJ_PTGROUPS )
		{

			TPTGROUPS *tgr = (TPTGROUPS *)pData;
			dwNumPointGroups =  tgr->m_iPtGroupCount;
		}
	}
	
	for(DWORD pg = 0;pg<dwNumPointGroups;pg++)
	{
		
		if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
		{
			const GUID*  pGUID;
			if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
				return E_FAIL;
			pFileData->GetType( &pGUID );
	
			if( *pGUID == DXFILEOBJ_CamGridStats )
			{
				TCamGridStats *tcgs = (TCamGridStats *)pData;

				CCamGridStats stats;
				stats.m_CamOrDirX = tcgs->m_CamOrDirX;
				stats.m_CamOrDirY = tcgs->m_CamOrDirY;
				stats.m_CamOrDirZ = tcgs->m_CamOrDirZ;
				stats.m_CamOrUpX = tcgs->m_CamOrUpX;
				stats.m_CamOrUpY = tcgs->m_CamOrUpY;
				stats.m_CamOrUpZ = tcgs->m_CamOrUpZ;
				stats.m_CamPosX = tcgs->m_CamPosX;
				stats.m_CamPosY = tcgs->m_CamPosY;
				stats.m_CamPosZ = tcgs->m_CamPosZ;
				stats.m_CamRotX = tcgs->m_CamRotX;
				stats.m_CamRotY = tcgs->m_CamRotY;
				stats.m_CamRotZ = tcgs->m_CamRotZ;
				stats.m_CamTheta[0] = tcgs->m_CamTheta;
				
				stats.m_GridPosX = tcgs->m_GridPosX;
				stats.m_GridPosY = tcgs->m_GridPosY;
				stats.m_GridPosZ = tcgs->m_GridPosZ;
				stats.m_GridRotX = tcgs->m_GridRotX;
				stats.m_GridRotY = tcgs->m_GridRotY;
				stats.m_GridRotZ = tcgs->m_GridRotZ;
				stats.m_GridTheta[0] = tcgs->m_GridTheta;
				
				groups->m_CamGridStats=groups->GrowStats(stats);
				
			}
	
		}

		if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
		{
			const GUID*  pGUID;
			if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
				return E_FAIL;
			pFileData->GetType( &pGUID );
	
			if( *pGUID == DXFILEOBJ_INTARRAY )
			{
				TINTARRAY *tin = (TINTARRAY *)pData;

				CHDXINTARRAY arg;
				arg.value=arg.allocate(0);
				arg.value = arg.growByEmptyEnd( tin->intCount );
				
				for(DWORD i = 0;i<tin->intCount;i++)
				{
					arg.value[i] = tin->value[i];
				}


				groups->m_iPointGroups = groups->Grow(arg);
				
			
						
			}
	
		}

		if( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
		{
			const GUID*  pGUID;
			if( FAILED( pFileData->GetData( NULL, &dwSize, (VOID**)&pData ) ) )
				return E_FAIL;
			pFileData->GetType( &pGUID );
	
			if( *pGUID == DXFILEOBJ_POINTARRAY )
			{
				TPOINTARRAY *tpin = (TPOINTARRAY *)pData;
				CHDXPOINTARRAY arg;
				arg.value=arg.allocate(0);
				arg.value = arg.growByEmptyEnd( tpin->intCount );
				
				for(DWORD i = 0;i<tpin->intCount;i++)
				{
					arg.value[i].x = tpin->value[i].x;
					arg.value[i].y = tpin->value[i].y;
				}


				groups->m_Mouse=groups->GrowMouse(arg);
			
						
			}
	
		}
		
	}//eo ptgroups for
	groups->m_iPtGroupCount=groups->m_iPtMouseCount=groups->m_iPtStatsCount=dwNumPointGroups;

    if( FALSE == bHasMaterials )
        pMesh->AddFace( 0, pFaceData, dwNumFaces );

    if( FALSE == bHasNormals )
        pMesh->ComputeNormals();
	
	for(DWORD i = 0;i<dwNumVertices;i++)
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
							if(D3DRM_OK==rm3->LoadTexture((char*)pMesh->m_Material[0].m_strTexture, &tex))
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
							if(D3DRM_OK==rm3->LoadTexture((char*)pMesh->m_Material[n].m_strTexture, &tex))
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

    //pParentFrame->AddChild( pMesh );
	f->AddVisual(pMesh->mb);
	m_iMeshCountHOB++;
    return S_OK;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

HDXHOBReader::HDXHOBReader()
{
  return;
}

HDXHOBReader::~HDXHOBReader(){}

HRESULT reg_template( LPDIRECTXFILE pDXFile )
{
	HRESULT hr = 0;

	char *HOBXTEMPLATES1 = "xof 0303txt 0032\
		template Morphs { \
            <BA5FE6A0-F92D-11d6-896C-00A0CCA2416E> \
            DWORD time;DWORD item;array DWORD items[item]; [...] } \
        template MorphArray { \
            <BA5FE6A2-F92D-11d6-896C-00A0CCA2416E> \
            DWORD cItems;array Morphs morphList[cItems]; [...] } \
        template Group { \
            <BA5FE6A3-F92D-11d6-896C-00A0CCA2416E> \
            DWORD item;array DWORD List[item]; [...] } \
        template GroupArray { \
            <BA5FE6A4-F92D-11d6-896C-00A0CCA2416E> \
            DWORD cItems;array Group groupList[cItems]; [...] } \
		template UserId { \
            <BA5FE6A5-F92D-11d6-896C-00A0CCA2416E> \
            DWORD nNameCount;array char name[nNameCount];DWORD nAddrCount;array char address[nAddrCount];DWORD nDateCount;array char date[nDateCount]; } \
		template HDXVector { \
            <BA5FE6A7-F92D-11d6-896C-00A0CCA2416E> \
            float x; float y;float z; } \
		template HDXNormals { \
            <BA5FE6A6-F92D-11d6-896C-00A0CCA2416E> \
            DWORD nNormals;array HDXVector normals[nNormals]; [...] } \
		template Mouse { \
			<BA5FE6A9-F92D-11d6-896C-00A0CCA2416E> \
			WORD x;WORD y; } \
		template MouseArray { \
			<BA5FE6AA-F92D-11d6-896C-00A0CCA2416E> \
			DWORD nCount;array Mouse positions[nCount]; } \
		template CameraPos { \
			<BA5FE6AB-F92D-11d6-896C-00A0CCA2416E> \
			DWORD nCount;array HDXVector pos[nCount];array HDXVector rot[nCount];array float theta[nCount];array HDXVector orDir[nCount];array HDXVector orUp[nCount]; } \
		template MeshVertices { \
		    <82540CE1-FA37-11d6-896C-00A0CCA2416E> \
			DWORD nVertices;array HDXVector vertices[nVertices]; [...] } \
		template MeshFace { \
			<82540CE2-FA37-11d6-896C-00A0CCA2416E> \
			DWORD nFaceVertexIndices;array DWORD faceVertexIndices[nFaceVertexIndices]; } \
		template MeshFaces { \
			<82540CE3-FA37-11d6-896C-00A0CCA2416E> \
			DWORD nFaces;array MeshFace faces[nFaces]; } \
		template V2 { \
		    <2B929801-FAF4-11d6-896C-00A0CCA2416E> \
			float u;float v; } \
		template TCoord { \
			<2B929802-FAF4-11d6-896C-00A0CCA2416E> \
			DWORD C;array V2 t[C];}";

char *HOBXTEMPLATES2 = "xof 0303txt 0032\
		template FaceData { \
		    <82540CE4-FA37-11d6-896C-00A0CCA2416E> \
			DWORD vertexId; } \
		template Spacer { \
			<BA5FE6A8-F92D-11d6-896C-00A0CCA2416E> \
			DWORD i;} \
		template MyMaterialList { \
			<52DC77A1-FB3F-11d6-896C-00A0CCA2416E> \
			DWORD nNumMaterials;DWORD nMaterialsPerFace;array DWORD nMaterialList[nMaterialsPerFace]; } \
		template MyMaterial { \
			<52DC77A2-FB3F-11d6-896C-00A0CCA2416E> \
			DWORD r;DWORD g;DWORD b;DWORD a;float power;float sRed;float sGreen;float sBlue;float eRed;float eGreen;float eBlue;float aRed;float aGreen;float aBlue;DWORD fNameCnt;STRING fileName;DWORD nNameCnt;STRING matName; } \
		template INTARRAY { \
			<7A9DB6E3-FB9A-11d6-896C-00A0CCA2416E> \
			DWORD dwEmptyEnd;DWORD intCount;array DWORD value[intCount];} \
		template Point2 { \
			<D8FA6701-FB9B-11d6-896C-00A0CCA2416E> \
			DWORD x;DWORD y; } \
		template POINTARRAY { \
			<7A9DB6E4-FB9A-11d6-896C-00A0CCA2416E> \
			DWORD dwEmptyEnd;DWORD intCount;array Point2 value[intCount]; } \
		template CamGridStats { \
			<7A9DB6E2-FB9A-11d6-896C-00A0CCA2416E> \
			float m_CamPosX;float m_CamPosY;float m_CamPosZ;float m_CamRotX;float m_CamRotY;float m_CamRotZ;float m_CamOrUpX;float m_CamOrUpY;float m_CamOrUpZ;float m_CamOrDirX;float m_CamOrDirY;float m_CamOrDirZ;float m_GridPosX;float m_GridPosY;float m_GridPosZ;float m_GridRotX;float m_GridRotY;float m_GridRotZ;float m_CamTheta;float m_GridTheta; } \
		template PTGROUPS { \
			<7A9DB6E1-FB9A-11d6-896C-00A0CCA2416E> \
			DWORD m_iPtGroupCount;}";

	DWORD sz1 = strlen(HOBXTEMPLATES1);
	DWORD sz2 = strlen(HOBXTEMPLATES2);
	if( FAILED( pDXFile->RegisterTemplates( (void*) HOBXTEMPLATES1, sz1 ) ) )
    {
        pDXFile->Release();
        return E_FAIL;
    }

	hr =  pDXFile->RegisterTemplates( (void*)HOBXTEMPLATES2, sz2 );
            
    CString s;
    if (FAILED(hr))
	{
		pDXFile->Release();
        s.Format( L"\nRegister templates test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Register templates test passed.\n");
//		OutputDebugString(s);
	}

	return hr;
}
const TCHAR* HOB_GetDXSDKMediaPath()
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

HRESULT HDXHOBReader::ReadHob( char *name, LPDIRECT3DRMFRAME3 f, LPDIRECT3DRM3 rm3, CPoints* meshPoints, CMAKERPTGROUPS* groups )
{
	HRESULT                 hr = 0;
    LPDIRECTXFILE           pDXFile;
    LPDIRECTXFILEENUMOBJECT pEnumObj;
    LPDIRECTXFILEDATA       pFileData;
    const GUID*             pGUID;
    //CHOBFileObject*         pFrame = NULL;
	
    // Cleanup any existing object
    //SAFE_HOB_DELETE( m_pRoot );

    // Create the file object, and register the D3DRM templates for .X files
    if( FAILED( DirectXFileCreate( &pDXFile ) ) )
        return E_FAIL;
	
    if( FAILED( reg_template( pDXFile ) ) )
		return E_FAIL;

	// Create an enumerator object, to enumerate through the .X file objects.
    // This will open the file in the current directory.
    hr = pDXFile->CreateEnumObject( name, DXFILELOAD_FROMFILE, &pEnumObj );

	if( FAILED(hr) )
    {
        TCHAR strPath[512] = _T("");
        lstrcat( strPath, HOB_GetDXSDKMediaPath() );
        lstrcat( strPath, (TCHAR*)name );
        
        hr = pDXFile->CreateEnumObject( strPath, DXFILELOAD_FROMFILE,
                                        &pEnumObj );
        if( FAILED(hr) )
        {
            pDXFile->Release();
            return hr;
        }
    }

	// Create a root object for the X file object
    m_pRoot = new CHOBFileObject( _T("HOBFile_Root") );

    // Cycle through each object. Parse meshes and frames as appropriate
    while( SUCCEEDED( hr = pEnumObj->GetNextDataObject( &pFileData ) ) )
    {
        pFileData->GetType( &pGUID );

        
        if( *pGUID == DXFILEOBJ_MeshVertices )
		{
           HRESULT hr = ParseMeshVertices( m_pRoot, pFileData, pEnumObj, m_pRoot, f, rm3, meshPoints, groups );
			
		}

        pFileData->Release();
    }

    // Success will result in hr == DXFILEERR_NOMOREOBJECTS
    if( DXFILEERR_NOMOREOBJECTS == hr ) 
        hr = S_OK;
    else
        SAFE_HOB_DELETE( m_pRoot );

    pEnumObj->Release();
    pDXFile->Release();
	


	if (FAILED(hr))
	{
		pDXFile->Release();
//        OutputDebugString("\nSave File failed.\n");
	}
    else
	{
//       OutputDebugString("Save File test passed.\n");
		
	}

	return hr;
}

//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CHOBFileObject::GetMeshGeometry( D3DVERTEX** ppVertices, DWORD* pdwNumVertices,
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
HRESULT CHOBFileObject::ComputeNormals()
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

        D3DVECTOR n = HOBNormalize( HOBCrossProduct( r1, r2 ) );

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
        if( HOBMagnitude( pNormals[i] ) < 0.1f ) 
            pNormals[i].x = 0.0f;
			pNormals[i].y = 0.0f;
			pNormals[i].z = 1.0f;

        
        pNormals[i] = HOBNormalize( pNormals[i] );
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
VOID CHOBFileObject::SetNormals( D3DVECTOR* pNormals )
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
VOID CHOBFileObject::SetTextureCoords( FLOAT* pTexCoords )
{
    for( DWORD i=0; i<m_dwNumVertices; i++ )
    {
        m_pVertices[i].tu = pTexCoords[2*i+0];
        m_pVertices[i].tv = pTexCoords[2*i+1];
    }
}

VOID   CHOBFileObject::SetMeshMaterialData( DWORD* wList, DWORD dwNumMatFaces )
{
	m_dwNumMatFaces = dwNumMatFaces;
	if(dwNumMatFaces>1)
	{
		
		m_pMatFaces = new DWORD[dwNumMatFaces];
	for( DWORD i=0; i<dwNumMatFaces; i++ )
    {
        m_pMatFaces[i] = wList[i];
	}
	}
}

HRESULT HDXHOBReader::GetMeshVertices( TCHAR* strName, D3DVERTEX** ppVertices,
                                   DWORD* pdwNumVertices )
{
    CHOBFileObject* pObject = FindObject( strName );
    if( pObject )
        return pObject->GetMeshGeometry( ppVertices, pdwNumVertices, NULL, NULL );

    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: GetMeshVertices()
// Desc: Traverse the hierarchy of frames and meshes that make up the file
//       object, and retrieves the vertices for the specified mesh.
//-----------------------------------------------------------------------------
HRESULT HDXHOBReader::GetMeshIndices( TCHAR* strName, WORD** ppIndices,
                                  DWORD* pdwNumIndices )
{
    CHOBFileObject* pObject = FindObject( strName );
    if( pObject )
        return pObject->GetMeshGeometry( NULL, NULL, ppIndices, pdwNumIndices );

    return E_FAIL;
}

//-----------------------------------------------------------------------------
// Name: FindMeshCB()
// Desc: Callback to scale a mesh
//-----------------------------------------------------------------------------
BOOL FindMeshCB( CHOBFileObject* pFileObject, D3DMATRIX*, VOID* pContext )
{
    struct FINDMESHRECORD
    {
        TCHAR*          strName;
        CHOBFileObject* pObject;
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

CHOBFileObject* HDXHOBReader::FindObject( TCHAR* strName )
{
    if( NULL == strName )
        return m_pRoot;

    struct FINDMESHRECORD
    {
        TCHAR*          strName;
        CHOBFileObject* pObject;
    };

    FINDMESHRECORD data = { strName, NULL };

    EnumObjects( FindMeshCB, NULL, (VOID*)&data );
    return data.pObject;
}


VOID D3DMath_MatrixMultiplyHOB( D3DMATRIX& q, D3DMATRIX& a, D3DMATRIX& b )
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
BOOL CHOBFileObject::EnumObjects( BOOL (*fnCallback)(CHOBFileObject*,D3DMATRIX*,VOID*),
                                  D3DMATRIX* pmat, VOID* pContext )
{
    if( fnCallback( this, pmat, pContext ) == TRUE )
        return TRUE;
/*
    if( m_pChild )
    {
        // Concat matrix set
        D3DMATRIX matSave = (*pmat);
		D3DMath_MatrixMultiplyHOB( *pmat, *pmat, m_mat );
        //(*pmat) = (*pmat) * m_mat;
    
        if( m_pChild->EnumObjects( fnCallback, pmat, pContext ) == TRUE )
            return TRUE;

        // Restore matrix set
        (*pmat) = matSave;
    }

    if( m_pNext )
        if( m_pNext->EnumObjects( fnCallback, pmat, pContext ) == TRUE )
            return TRUE;
*/
    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: EnumObjects()
// Desc: Enumerates all objects in the file.
//-----------------------------------------------------------------------------
VOID HDXHOBReader::EnumObjects( BOOL (*fnCallback)(CHOBFileObject*,D3DMATRIX*,VOID*),
                            D3DMATRIX* pmat, VOID* pContext )
{
    if( m_pRoot )
    {
        D3DMATRIX mat;

        if( pmat )
            mat = *pmat;
        else
            D3DHOB_SetIdentityMatrix( mat );

        m_pRoot->EnumObjects( fnCallback, &mat, pContext );
    }
}

void HDXHOBReader::SetMeshCount( DWORD cnt )
{
	m_iMeshCountHOB=cnt;
}
void HDXHOBReader::SetFrameCount( DWORD cnt )
{
	m_iFrameCountHOB = cnt;
}

DWORD HDXHOBReader::GetMeshCount()
{
	return m_iMeshCountHOB;
}
DWORD HDXHOBReader::GetFrameCount()
{
	return m_iFrameCountHOB;
}

void CHOBFileObject::SetFaceData(DWORD* pFaceData)
{
	m_pFaceIndices = pFaceData;
}