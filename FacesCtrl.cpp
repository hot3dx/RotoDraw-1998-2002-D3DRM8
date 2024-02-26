// FacesCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "FacesCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFacesCtrl dialog


CFacesCtrl::CFacesCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CFacesCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFacesCtrl)
	//}}AFX_DATA_INIT
}


void CFacesCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFacesCtrl)
	DDX_Control(pDX, IDC_FACES_LIST, m_FacesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFacesCtrl, CDialog)
	//{{AFX_MSG_MAP(CFacesCtrl)
	ON_NOTIFY(NM_CLICK, IDC_FACES_LIST, OnClickFacesList)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFacesCtrl message handlers
void CFacesCtrl::AddFaces()
{
		faceString = "";
		
		pntCnt = 0;
		
		currentFace = m_FacesList.InsertItem( faceCnt,"");
		faceCnt++;
		
}
void CFacesCtrl::SetFaceData3(int *l)
{
		pntCnt=3;
		prevPnts[0]=l[0];
		prevPnts[1]=l[1];
		prevPnts[2]=l[2];
		
		faceString.Format("%d,%d,%d",l[0],l[1],l[2]);
}
void CFacesCtrl::SetFaceData(int *l)
{
		pntCnt=4;
		prevPnts[0]=l[0];
		prevPnts[1]=l[1];
		prevPnts[2]=l[2];
		prevPnts[3]=l[3];
		faceString.Format("%d,%d,%d,%d",l[0],l[1],l[2],l[3]);
}

void CFacesCtrl::SetFaceDataMany(int *l, int pntCnt2)
{
		pntCnt=pntCnt2;
		CString temp,list;
		for(int i = 0;i<pntCnt;i++)
		{
			temp.Format("%d, ", l[i]);
			list.Format("%s%s",faceString,temp);
			faceString.Format("%s",list);
		}
		
}


void CFacesCtrl::SetFaceList(int matIndex)
{
		CMakerC1Dlg* m = (CMakerC1Dlg*)GetParent()->GetParent();
		CString s;
		s.Format("%d",currentFace);
		m_FacesList.SetItemText( currentFace, 0, s);
		s.Format("%d",matIndex);
		m_FacesList.SetItemText( currentFace, 1, s);
		m->m_MatList.m_MatList.value=m->m_MatList.m_MatList.grow(matIndex);
		s.Format("%d",pntCnt);
		m_FacesList.SetItemText( currentFace, 2, s);
		m_FacesList.SetItemText( currentFace, 3, faceString);
		
}
LPDIRECT3DRMMATERIAL2 CFacesCtrl::MakeMaterialFace(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i)
{
	CMakerC1Dlg* m = (CMakerC1Dlg*)GetParent()->GetParent();
		 
		 rm->CreateMaterial(m->m_MatArray.m_Mats[i].args[0], &mat);
	     mat->SetEmissive(m->m_MatArray.m_Mats[i].args[1], m->m_MatArray.m_Mats[i].args[2], m->m_MatArray.m_Mats[i].args[3]);
	     mat->SetSpecular(m->m_MatArray.m_Mats[i].args[4],  m->m_MatArray.m_Mats[i].args[5], m->m_MatArray.m_Mats[i].args[6]);
		 mat->SetAmbient(m->m_MatArray.m_Mats[i].args[7],  m->m_MatArray.m_Mats[i].args[8], m->m_MatArray.m_Mats[i].args[9]);
		 return mat;
}
float * GetUFace( D3DVECTOR v, LPD3DRMBOX b, LPDIRECT3DRM3 rm, CMakerC1Dlg* arg)
{
	static float uv[2];
		
	float a = v.x;
	float c = v.y;
	float e = v.z;
	
	
	D3DVECTOR r;
	D3DVECTOR m;
	D3DVECTOR s;
	m.x = b->min.x;
	m.y = b->min.y;
	m.z = b->min.z;
	
	s.x=b->max.x;
	s.y=b->max.y;
	s.z=b->max.z;
	
	D3DRMVectorSubtract( &r, &m, &s);
	
		
		if(a==b->min.x)
		{
			uv[0]= 0.0F;
		}
	
	else{
		uv[0] = -1*((a- b->min.x)/r.x);
	   }
		if(c==b->max.y){
			uv[1]= 0.0F;
		}
	else{
		uv[1] = 1*((c-b->max.y)/r.y);	
	}

	return uv;
}

void SetTextCoordsFace(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRM3 rm, CMakerC1Dlg* arg)
{
	D3DRMBOX box;
		mb->GetBox(&box);
		
				
		for(int i = 0;i<mb->GetVertexCount();i++)
		{
			D3DVECTOR v;
			mb->GetVertex( i, &v );
			float *u = GetUFace( v, &box, rm, arg);
			
			mb->SetTextureCoordinates(i, u[0], u[1]);
		
		
		}
}
void CFacesCtrl::DoTextureSetting3(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRMFACE2 frontFace, LPDIRECT3DRMFACE2 backFace, LPDIRECT3DRMMATERIAL2 mat1, LPDIRECT3DRMMATERIAL2 mat2, LPDIRECT3DRMTEXTURE3 texture, LPDIRECT3DRMTEXTURE3 texture2)
{
	
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 d3drmb = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&d3drmb);
	
	if(arg->m_bColorSet == false)
	{
		MessageBox("Please choose the appropriate textures or materials from the color select and then hit yes, \n\na continue button will show on the color select bar once you are done", "no colors chosen", MB_OK);
		
	}
	else
	{
	//SetTextCoordsFace(mb, d3drmb, arg);		
	switch(arg->textureFillMode){
		case 1://FDIFFTEXTURES
			{	
				
			frontFace->SetMaterial(mat1);
			//frontFace->SetColorRGB(arg->frontRed, arg->frontGreen, arg->frontBlue);
			D3DCOLOR col = RGBA_MAKE((int)(arg->frontRed*255), (int)(arg->frontGreen*255), (int)(arg->frontBlue*255), (int)(arg->frontAlpha*255));
			frontFace->SetColor(col);
			if(	arg->selTexFrontPath.GetLength()>0)
			{
				frontFace->SetTexture(texture);
			}
			
			backFace->SetMaterial(mat2);
			//backFace->SetColorRGB(arg->backRed, arg->backGreen, arg->backBlue);
			D3DCOLOR bcol = RGBA_MAKE((int)(arg->backRed*255), (int)(arg->backGreen*255), (int)(arg->backBlue*255), (int)(arg->backAlpha*255));
			backFace->SetColor(bcol);
			if(	arg->selTexBackPath.GetLength()>0)
			{
				backFace->SetTexture(texture2);
			}
			
			}
			break;
		case 2://FSAMETEXTURES
			{
				if(	arg->selTexFrontPath.GetLength()>0)
				{
					LPDIRECT3DRMTEXTURE3 texture;
					d3drmb->LoadTexture(arg->selTexFrontPath, &texture);
			
					mb->SetTexture(texture);
				}
			mb->SetMaterial(mat1);
			//mb->SetColorRGB(arg->frontRed, arg->frontGreen, arg->frontBlue);
			D3DCOLOR mbcol = RGBA_MAKE((int)(arg->frontRed*255), (int)(arg->frontGreen*255), (int)(arg->frontBlue*255), (int)(arg->frontAlpha*255));
			mb->SetColor(mbcol);

			break;
		 } //end of texture fillmode switch
		

		
		lastFrontFace = frontFace;
		lastBackFace  = backFace;
			
		faceAdded = true;
		mb->SetQuality(
						 arg->renderType+
						 arg->lightStatus+
						 arg->fillType
						 );
		
		arg->win3dMat->WinRender();
		
	}//eoelse
}
	
	d3drmb->Release();
	rm1->Release();
}


void CFacesCtrl::OnClickFacesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_FacesList.GetItemCount()>0)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	faceSelected = false;
		POSITION t = m_FacesList.GetFirstSelectedItemPosition();
		int index = (int)t-1;
		if(index>=0)
		{
		
		HRESULT hr = arg->win3dMat->m_SceneObjects->finalMesh->GetFace( index, &face);
		if(hr==D3DRM_OK)
		{
			faceSelected = true;
		}
			D3DCOLOR color = face->GetColor();
			if(color!=RGBA_MAKE(255,255,255,255))
			{
				face->SetColor(RGBA_MAKE(255,255,255,255 ));
			}
			else{
				face->SetColor(RGBA_MAKE(0,255,0,255));
			}
	
			arg->win3dMat->WinRender();
			for(int l=0;l<2000000;l++){}
			for( l=0;l<2000000;l++){}
			 face->SetColor(color);
			arg->win3dMat->WinRender();

	}		}	
	*pResult = 0;
}

void CFacesCtrl::OnButton1() 
{
	if(m_FacesList.GetItemCount()>0)
	{
	if(faceSelected==true)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	if(arg->m_MatArray.m_Count>0)
	{
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm3 = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm3);
	LPDIRECT3DRMTEXTURE3 texture  = NULL;
	LPDIRECT3DRMMATERIAL2 mat1 = NULL;
	
		mat1 = MakeMaterialFace(rm3, mat1, arg->selMatFront);
		face->SetMaterial(mat1);
		face->SetColor(RGBA_MAKE((int)arg->frontRed*255, (int)arg->frontGreen*255, (int)arg->frontBlue*255, (int)arg->frontAlpha*255));
	if(	arg->selTexFrontPath.GetLength()>0)
			{
				HRESULT hr = rm3->LoadTexture(arg->selTexFrontPath, &texture);
				if(hr==D3DRM_OK)
				{
				face->SetTexture(texture);
				texture->Release();
				}
			}
	face->Release();
	mat1->Release();
	rm3->Release();
	rm1->Release();

	}// eo  if(m_MatCount>)
	else{
		
		MessageBox( "Objects cannot be made without first loading a set of materials using the material editor", "No Materials Loaded", MB_OK);
	}//eo if(arg->m_MatArray.m_Count<=0)

	}
	}
}

void CFacesCtrl::OnButton2() 
{
	if(m_FacesList.GetItemCount()>0)
	{
	if(faceSelected==true)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	if(arg->m_MatArray.m_Count>0)
	{
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm3 = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm3);
	LPDIRECT3DRMTEXTURE3 texture  = NULL;
	LPDIRECT3DRMMATERIAL2 mat1 = NULL;
	
		mat1 = MakeMaterialFace(rm3, mat1, arg->selMatBack);
		face->SetMaterial(mat1);
		face->SetColor(RGBA_MAKE((int)arg->backRed*255, (int)arg->backGreen*255, (int)arg->backBlue*255, (int)arg->backAlpha*255));
	if(	arg->selTexBackPath.GetLength()>0)
	{
				HRESULT hr = rm3->LoadTexture(arg->selTexBackPath, &texture);
				if(hr==D3DRM_OK)
				{
				face->SetTexture(texture);
				texture->Release();
				}
			}
	face->Release();
	mat1->Release();
	rm3->Release();
	rm1->Release();
	}// eo  if(m_MatCount>)
	else{
		
		MessageBox( "Objects cannot be made without first loading a set of materials using the material editor", "No Materials Loaded", MB_OK);
	}//eo if(arg->m_MatArray.m_Count<=0)

	}
	}	
}
