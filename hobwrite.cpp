#include "stdafx.h"

#include "dxsdk8\include\d3drm.h"

#include "dxsdk8\include\dxfile.h"

#include "dxsdk8\include\rmxfguid.h"

#include <math.h>
#include "hobwrite.h"

#include "hdxdatatypes.h"
#include "myxtmpl.h"


HDXHOBWriter::HDXHOBWriter()
{
  return;
}

HDXHOBWriter::~HDXHOBWriter()
{
	
}

HRESULT save_templates(LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave)
{
    HRESULT hr;
	
    char *szMyTemplates = "xof 0303txt 0032\
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
			
	DWORD sz = strlen(szMyTemplates);
    hr = m_pxofapi->RegisterTemplates((void*) szMyTemplates, sz);
		
	if (SUCCEEDED(hr)) {
        const GUID *aIds[] = {
			&DXFILEOBJ_Morphs,
			&DXFILEOBJ_MorphArray,
            &DXFILEOBJ_Group,
            &DXFILEOBJ_GroupArray,
			&DXFILEOBJ_UserId,
            &DXFILEOBJ_HDXVector,
			&DXFILEOBJ_HDXNormals,
			&DXFILEOBJ_Mouse,
			&DXFILEOBJ_MouseArray,
			&DXFILEOBJ_CameraPos,
			&DXFILEOBJ_MeshVertices,
			&DXFILEOBJ_MeshFace,
			&DXFILEOBJ_MeshFaces,
			&DXFILEOBJ_V2,
			&DXFILEOBJ_TCoord
			};
			
        hr = m_pxofSave->SaveTemplates( 15, aIds);
	}

	  char *szMyTemplates2 = "xof 0303txt 0032\
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
	  
	
	DWORD sz2 = strlen(szMyTemplates2);
    hr = m_pxofapi->RegisterTemplates((void*) szMyTemplates2, sz2); 
	
	if (SUCCEEDED(hr)) {
        const GUID *aIds2[] = {
			&DXFILEOBJ_Spacer,
			&DXFILEOBJ_FaceData,
			&DXFILEOBJ_MyMaterialList,
			&DXFILEOBJ_MyMaterial,
			&DXFILEOBJ_INTARRAY,
			&DXFILEOBJ_Point2,
			&DXFILEOBJ_POINTARRAY,
			&DXFILEOBJ_CamGridStats,
			&DXFILEOBJ_PTGROUPS
            };
			
        hr = m_pxofSave->SaveTemplates( 9, aIds2);
    }

	
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave templates test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save templates test passed.\n");
//		OutputDebugString(s);
	}

    return hr;
}

HRESULT save_mesh( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh)
{
	
	HRESULT hr = 0;
	
	do{


	LPDIRECT3DRMMESHBUILDER3 mb = (LPDIRECT3DRMMESHBUILDER3)mesh;

	DWORD vCount = mb->GetVertexCount();
	if(vCount>0)
	{
	D3DVECTOR *verts = (D3DVECTOR*)malloc(vCount*sizeof(D3DVECTOR));
	THDXVector *vVerts = (THDXVector*)malloc(vCount*sizeof(THDXVector));
	hr = mb->GetVertices(0, &vCount, verts);
			
		if (FAILED(hr))
			break;

		for(DWORD g=0;g<vCount;g++)
		{
			vVerts[g].x = verts[g].x;
			vVerts[g].y = verts[g].y;
			vVerts[g].z = verts[g].z;
		}
	free(verts);
	
	LPVOID         pvData;	
	         
	DWORD meshSize = sizeof(DWORD) + vCount * sizeof(THDXVector);
                 

        pvData = new char[meshSize];
		
        if (!pvData)
            break;

		TMeshVertices *pVerts = (TMeshVertices *)pvData;

        pVerts->nVertices = vCount;
        
		for(DWORD g=0;g<vCount;g++)
		{
			pVerts->vertices[g].x = vVerts[g].x;
			pVerts->vertices[g].y = vVerts[g].y;
			pVerts->vertices[g].z = vVerts[g].z;
		}

        
        // Then call api to create data object.
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_MeshVertices,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();
		free(vVerts);
		}// eo if( vCount>0)
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave mesh test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save mesh test passed.\n");
//		OutputDebugString(s);
	}
	
	return hr;
}

HRESULT save_meshFaces( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh)
{
	
	HRESULT hr = 0;
	
	do{

	LPDIRECT3DRMMESHBUILDER3 mb = (LPDIRECT3DRMMESHBUILDER3)mesh;

	DWORD fCount = mb->GetFaceCount();
 
	if(fCount>0)
	{

	DWORD faceDataSize = 0;
	for(DWORD i = 0;i<fCount;i++)
	{
		LPDIRECT3DRMFACE2 face;
		mb->GetFace( i, &face);
		DWORD fvCnt = face->GetVertexCount();
		faceDataSize+=(fvCnt+1);
		face->Release();
	}
	
	LPVOID pvData;	
	DWORD meshSize = sizeof(DWORD) + faceDataSize * sizeof(DWORD);

        pvData = new char[meshSize];
		if (!pvData)
            break;
			
	DWORD *arr = new DWORD[faceDataSize];
	DWORD n = 0;				
	for(DWORD i = 0;i<fCount;i++)
	{
		LPDIRECT3DRMFACE2 face;
		mb->GetFace( i, &face);
		DWORD fvCnt = face->GetVertexCount();
		arr[n]=fvCnt;n++;		
		for(DWORD j = 0;j<fvCnt;j++)
			{
				DWORD which = face->GetVertexIndex( j);
				arr[n] = which;n++;
			}
		
		face->Release();
	}
	TMeshFaces *pF = (TMeshFaces *)pvData;
	pF->nFaces=fCount;
	TMeshFace *pFaces = (TMeshFace *)pF->faces;
		memcpy(pFaces, arr, meshSize);
		CString s;
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_MeshFaces,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();
		
		}// eo if( vCount>0)
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave mesh faces test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save mesh faces test passed.\n");
		//OutputDebugString(s);
	}
	
	return hr;
}

HRESULT save_meshMaterialList( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh, HDXMaterialList list, HDXMaterialArray matArray)
{
	LPDIRECT3DRMMESHBUILDER3 mb = (LPDIRECT3DRMMESHBUILDER3)mesh;
	DWORD fCount = mb->GetFaceCount();
	HRESULT hr = 0;
	if(fCount>0){
	do{


		DWORD listSize = ((2  + fCount)*sizeof(DWORD));
		LPVOID pvData = new LPVOID[listSize];

		if(!pvData)break;

		TMyMaterialList *pL = (TMyMaterialList *)pvData;

		pL->nNumMaterials = matArray.m_Count;
		pL->nMaterialsPerFace = fCount;

		if(list.m_iMatsPerFace>0&&list.m_iMatsPerFace<40000)
		for(DWORD h=0;h<fCount;h++)
			pL->nMaterialList[h]= list.m_MatList.value[h];
		
		

		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_MyMaterialList,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        listSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();
		
		
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave material list test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save material list test passed.\n");
//		OutputDebugString(s);
	}
}
	return hr;
}

HRESULT save_meshMaterials( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh, HDXMaterialArray matArray)
{
	HRESULT hr = 0;

	for(DWORD k =0;k<matArray.m_Count;k++)
	{
		do{
		DWORD matSize = 15 *sizeof(DWORD) + matArray.m_Mats[k].fCount + sizeof(DWORD) + matArray.m_Mats[k].nCount;

		LPVOID pvData = new LPVOID[matSize];

		if(!pvData)break;

		TMyMaterial *pMat = (TMyMaterial *)pvData;

		pMat->r =matArray.m_Mats[k].r;
		pMat->g =matArray.m_Mats[k].g;
		pMat->b =matArray.m_Mats[k].b;
		pMat->a =matArray.m_Mats[k].a;
		pMat->power = matArray.m_Mats[k].args[0];
		pMat->sRed  = matArray.m_Mats[k].args[1];
		pMat->sGreen = matArray.m_Mats[k].args[2];
		pMat->sBlue = matArray.m_Mats[k].args[3];
		pMat->eRed = matArray.m_Mats[k].args[4];
		pMat->eGreen = matArray.m_Mats[k].args[5];
		pMat->eBlue = matArray.m_Mats[k].args[6];
		pMat->aRed = matArray.m_Mats[k].args[7];
		pMat->aGreen = matArray.m_Mats[k].args[8];
		pMat->aBlue = matArray.m_Mats[k].args[9];
		pMat->fNameCnt = matArray.m_Mats[k].fCount;
		pMat->fileName = matArray.m_Mats[k].file;
		pMat->nNameCNT = matArray.m_Mats[k].nCount;
		pMat->matName = matArray.m_Mats[k].matName;
		
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_MyMaterial,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        matSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);

        delete( pvData);
		
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
			
		if (FAILED(hr)){}
        else{pxofobj->Release();}
		
		
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave mesh material test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save mesh material test passed.\n");
//		OutputDebugString(s);
	}

	}//eo k for

	return hr;
}

HRESULT save_meshNormals( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh)
{
	HRESULT hr = 0;
	do{


	LPDIRECT3DRMMESHBUILDER3 mb = (LPDIRECT3DRMMESHBUILDER3)mesh;

	DWORD vCount = mb->GetVertexCount();
	if(vCount>0)
	{
	D3DVECTOR *norms = (D3DVECTOR*)malloc(vCount*sizeof(D3DVECTOR));
	THDXVector *vNorms = (THDXVector*)malloc(vCount*sizeof(THDXVector));
	hr = mb->GetNormals(0, &vCount, norms);
			
		if (FAILED(hr))
			break;

		for(DWORD g=0;g<vCount;g++)
		{
			vNorms[g].x = norms[g].x;
			vNorms[g].y = norms[g].y;
			vNorms[g].z = norms[g].z;
		}
	free(norms);
	
	LPVOID         pvData;	
	         
	DWORD meshSize = sizeof(DWORD) + vCount * sizeof(THDXVector);
                 

        pvData = new char[meshSize];
		
        if (!pvData)
            break;

		THDXNormals *pNorms = (THDXNormals *)pvData;

        pNorms->nNormals = vCount;
        
		for(DWORD g=0;g<vCount;g++)
		{
			pNorms->normals[g].x = vNorms[g].x;
			pNorms->normals[g].y = vNorms[g].y;
			pNorms->normals[g].z = vNorms[g].z;
		}

        
        // Then call api to create data object.
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_HDXNormals,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();
		free(vNorms);
		}// eo if( vCount>0)
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave normals test failed.\n");
		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save normals test passed.\n");
//		OutputDebugString(s);
	}
	
	return hr;
}

HRESULT save_meshNormalFaces( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh)
{
	HRESULT hr = 0;

	return hr;
}

HRESULT save_meshTextureCoordinates( LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, LPVOID mesh)
{
	HRESULT hr = 0;
	
	do{


	LPDIRECT3DRMMESHBUILDER3 mb = (LPDIRECT3DRMMESHBUILDER3)mesh;

	DWORD vCount = mb->GetVertexCount();
	if(vCount>0)
	{
	float u[1];
	float v[1];
	TV2 *vCoords = (TV2*)malloc(vCount*sizeof(TV2));

	for(DWORD h = 0;h<vCount;h++)
	{
		hr = mb->GetTextureCoordinates(h, u, v);
		vCoords[h].u = u[0];
		vCoords[h].v = v[0];
	}
			
		if (FAILED(hr))
			break;

	LPVOID         pvData;	
	         
	DWORD meshSize = sizeof(DWORD) + vCount * sizeof(TV2);
                 

        pvData = new char[meshSize];
		
        if (!pvData)
            break;

		TTCoord *pCoords = (TTCoord *)pvData;

        pCoords->C = vCount;
        
		for(DWORD g=0;g<vCount;g++)
		{
			pCoords->t[g].u = vCoords[g].u;
			pCoords->t[g].v = vCoords[g].v;
			
		}

        
        // Then call api to create data object.
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_TCoord,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))
		{ 
			break;
		}
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();
		free(vCoords);
		}// eo if( vCount>0)
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave coords test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save coords test passed.\n");
		//OutputDebugString(s);
	}
	
	return hr;
}
HRESULT saveCamStats(LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, CMAKERPTGROUPS Pt, DWORD i)
{
	HRESULT hr = 0;
	do{
		DWORD meshSize = 20 * sizeof(DWORD);
		LPVOID pvData = new char[meshSize];
		
			if (!pvData)break;

		TCamGridStats *t = (TCamGridStats *)pvData;

		t->m_CamPosX = Pt.m_CamGridStats[i].m_CamPosX;
		t->m_CamPosY = Pt.m_CamGridStats[i].m_CamPosY;
		t->m_CamPosZ = Pt.m_CamGridStats[i].m_CamPosZ;

		t->m_CamRotX = Pt.m_CamGridStats[i].m_CamRotX;
		t->m_CamRotY = Pt.m_CamGridStats[i].m_CamRotY;
		t->m_CamRotZ = Pt.m_CamGridStats[i].m_CamRotZ;
		t->m_CamTheta = Pt.m_CamGridStats[i].m_CamTheta[0];

		t->m_CamOrDirX = Pt.m_CamGridStats[i].m_CamOrDirX;
		t->m_CamOrDirY = Pt.m_CamGridStats[i].m_CamOrDirY;
		t->m_CamOrDirZ = Pt.m_CamGridStats[i].m_CamOrDirZ;

		t->m_CamOrUpX = Pt.m_CamGridStats[i].m_CamOrUpX;
		t->m_CamOrUpY = Pt.m_CamGridStats[i].m_CamOrUpY;
		t->m_CamOrUpZ = Pt.m_CamGridStats[i].m_CamOrUpZ;


		t->m_GridPosX = Pt.m_CamGridStats[i].m_GridPosX;
		t->m_GridPosY = Pt.m_CamGridStats[i].m_GridPosY;
		t->m_GridPosZ = Pt.m_CamGridStats[i].m_GridPosZ;

		t->m_GridRotX = Pt.m_CamGridStats[i].m_GridRotX;
		t->m_GridRotY = Pt.m_CamGridStats[i].m_GridRotY;
		t->m_GridRotZ = Pt.m_CamGridStats[i].m_GridRotZ;
		t->m_GridTheta = Pt.m_CamGridStats[i].m_GridTheta[0];

		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_CamGridStats,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))break;
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();

	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave CamStats test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save CamStats test passed.\n");
//		OutputDebugString(s);
	}
	return hr;
}
HRESULT savePoints(LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, CMAKERPTGROUPS Pt, DWORD i)
{
	HRESULT hr = 0;
	do{
		DWORD cnt = Pt.m_Mouse[i].intCount-1;
		DWORD meshSize = 2 * sizeof(DWORD) + (cnt*sizeof(TPoint2));
		LPVOID pvData = new char[meshSize];
		
			if (!pvData)break;

		TPOINTARRAY *t = (TPOINTARRAY *)pvData;
		
		t->dwEmptyEnd = Pt.m_Mouse[i].dwEmptyEnd;
		t->intCount   = cnt;
		
		
		memcpy(t->value, Pt.m_Mouse[i].value, cnt*sizeof(TPoint2));
		
		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_POINTARRAY,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))break;
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();


	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave Points test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save Points test passed.\n");
//		OutputDebugString(s);
	}
	return hr;
}
HRESULT saveGroups(LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, CMAKERPTGROUPS Pt, DWORD i)
{
	HRESULT hr = 0;
	do{
		DWORD cnt = Pt.m_iPointGroups[i].intCount-1;
		DWORD meshSize = (2 * sizeof(DWORD))+(cnt * sizeof(DWORD));
		LPVOID pvData = new char[meshSize];
			if (!pvData)break;
		
		TINTARRAY *t = (TINTARRAY *)pvData;
		t->dwEmptyEnd = Pt.m_iPointGroups[i].dwEmptyEnd;
		t->intCount   = cnt;

		for(DWORD j=0;j<cnt;j++)
		{
			t->value[j] = Pt.m_iPointGroups[i].value[j];
			
		}

		//memcpy(t->value, Pt.m_iPointGroups[i].value, Pt.m_iPointGroups[i].intCount*sizeof(DWORD));

		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_INTARRAY,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))break;
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();

			
	}while(FALSE);
	CString s;
    if (FAILED(hr))
	{
        s.Format( L"\nSave Groups test failed.\n");
//		OutputDebugString(s);
	}
    else
	{
       s.Format(L"Save Groups test passed.\n");
//		OutputDebugString(s);
	}
	return hr;
}
HRESULT savePTGroups(LPDIRECTXFILE m_pxofapi, LPDIRECTXFILESAVEOBJECT m_pxofSave, CMAKERPTGROUPS Pt)
{
	HRESULT hr = 0;

	do{

		DWORD meshSize = sizeof(DWORD);
		LPVOID pvData = new char[meshSize];
		
			if (!pvData)break;

		TPTGROUPS *p = (TPTGROUPS *)pvData;

		p->m_iPtGroupCount = Pt.m_iPtGroupCount;

		LPDIRECTXFILEDATA pxofobj = NULL;
        hr = m_pxofSave->CreateDataObject(DXFILEOBJ_PTGROUPS,
                                        NULL,    // meshname
                                        NULL,       // uuid *
                                        meshSize,     // data chunk size.
                                        pvData,     // pointer to data chunk.
                                        &pxofobj);
        delete( pvData);
        if (FAILED(hr))break;
		
		hr = m_pxofSave->SaveData(pxofobj);
        pxofobj->Release();

		for(DWORD i = 0;i<Pt.m_iPtGroupCount;i++)
		{
			hr = saveCamStats( m_pxofapi, m_pxofSave, Pt, i );

			hr = saveGroups( m_pxofapi, m_pxofSave, Pt, i );

			hr = savePoints( m_pxofapi, m_pxofSave, Pt, i );
		}

	}while(FALSE);
	return hr;
}

void HDXHOBWriter::WriteHob(int xFormat, char* name, LPVOID mesh, HDXMaterialArray matArray, HDXMaterialList matList, CPoints m_Points, CMAKERPTGROUPS m_PtGrps)
{
	LPDIRECTXFILE m_mypxofapi;
	LPDIRECTXFILESAVEOBJECT m_mypxofSave = {};
	

	HRESULT hr;

    do {
        hr = DirectXFileCreate( &m_mypxofapi);

        if (FAILED(hr))
            break;

		DXFILEFORMAT typeFormat;
		if(xFormat==0)
		{
			typeFormat = DXFILEFORMAT_BINARY;
		}
		else {typeFormat = DXFILEFORMAT_TEXT;}
        hr = m_mypxofapi->CreateSaveObject( name,
                                         typeFormat,
                                         &m_mypxofSave);

        if (FAILED(hr))
            break;

        hr = save_templates( m_mypxofapi, m_mypxofSave );

        if (FAILED(hr))
            break;

		hr = save_mesh( m_mypxofapi, m_mypxofSave, mesh );

        if (FAILED(hr))
            break;

		hr = save_meshFaces( m_mypxofapi, m_mypxofSave, mesh );

        if (FAILED(hr))
            break;

		hr = save_meshNormals( m_mypxofapi, m_mypxofSave, mesh );

		if (FAILED(hr))
            break;

		hr = save_meshTextureCoordinates( m_mypxofapi, m_mypxofSave, mesh );

		if (FAILED(hr))
            break;
		
		hr = save_meshMaterialList( m_mypxofapi, m_mypxofSave, mesh, matList, matArray);

		if (FAILED(hr))
            break;

		hr = save_meshMaterials(  m_mypxofapi, m_mypxofSave, mesh, matArray);

		if (FAILED(hr))
            break;

		hr =  savePTGroups(m_mypxofapi, m_mypxofSave, m_PtGrps);

		if (FAILED(hr))
            break;
				
	} while (FALSE);
	if (m_mypxofSave)
        m_mypxofSave->Release();

    if (m_mypxofapi)
        m_mypxofapi->Release();
}

