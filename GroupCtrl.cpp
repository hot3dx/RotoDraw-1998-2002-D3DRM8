// GroupCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "GroupCtrl.h"
#include "CopyPosRotScaleCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupCtrl dialog


CGroupCtrl::CGroupCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupCtrl)
	//}}AFX_DATA_INIT
}


void CGroupCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupCtrl)
	DDX_Control(pDX, IDC_LAST_TO_FIRST_CHECK, m_LastToFirstCheck);
	DDX_Control(pDX, IDC_GROUP_EDIT2, m_GroupTwoEdit);
	DDX_Control(pDX, IDC_GROUP_EDIT1, m_GRoupOneEdit);
	DDX_Control(pDX, IDC_GROUP_LIST, m_GroupList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupCtrl, CDialog)
	//{{AFX_MSG_MAP(CGroupCtrl)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_LIST, OnClickGroupList)
	ON_BN_CLICKED(IDC_COPY_BUTTON, OnCopyButton)
	ON_BN_CLICKED(IDC_GROUP_BUTTON1, OnGroupButton1)
	ON_BN_CLICKED(IDC_GROUP_BUTTON2, OnGroupButton2)
	ON_BN_CLICKED(IDC_CHOOSE_FACES_BUTTON, OnChooseFacesButton)
	ON_BN_CLICKED(IDC_AUTO_FACE_BUTTON, OnAutoFaceButton)
	ON_BN_CLICKED(IDC_SET_FACE_BUTTON, OnSetFaceButton)
	ON_BN_CLICKED(IDC_UNDO_BUTTON, OnUndoButton)
	ON_BN_CLICKED(IDC_DELETE_GROUP_BUTTON, OnDeleteGroupButton)
	ON_BN_CLICKED(IDC_LAST_TO_FIRST_CHECK, OnLastToFirstCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupCtrl message handlers

void CGroupCtrl::OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_GroupList.GetItemCount()>0)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	
			
		POSITION t = m_GroupList.GetFirstSelectedItemPosition();
		unsigned int i = (unsigned int)t-1;
	if((i==0)||i<(unsigned int)m_GroupList.GetItemCount())
	{
		arg->m_GroupListSelectedIndex = i;
		arg->win3dMat->m_SceneObjects->m_camera->SetPosition(NULL,
		arg->m_PtGroups.m_CamGridStats[i].m_CamPosX,
		arg->m_PtGroups.m_CamGridStats[i].m_CamPosY,
		arg->m_PtGroups.m_CamGridStats[i].m_CamPosZ);
		
		arg->win3dMat->m_SceneObjects->m_camera->SetOrientation(NULL,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrDirX,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrDirY,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrDirZ,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrUpX,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrUpY,
			arg->m_PtGroups.m_CamGridStats[i].m_CamOrUpZ);

		CWnd* han;
		CString s;
	
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamPos.x); 
	han=arg->GetDlgItem( IDC_CAMPOS_X_STATIC);
	han->SetWindowText( s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamPos.y); 
	han=arg->GetDlgItem( IDC_CAMPOS_Y_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamPos.z); 
	han=arg->GetDlgItem( IDC_CAMPOS_Z_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamRot.x); 
	han=arg->GetDlgItem( IDC_CAMROT_X_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamRot.y); 
	han=arg->GetDlgItem( IDC_CAMROT_Y_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamRot.z); 
	han=arg->GetDlgItem( IDC_CAMROT_Z_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamTheta[0]); 
	han=arg->GetDlgItem( IDC_CAMROT_T_STATIC);
	han->SetWindowText(s);

	
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamDir.x); 
	han=arg->GetDlgItem( IDC_GRIDPOS_X_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamDir.y); 
	han=arg->GetDlgItem( IDC_GRIDPOS_Y_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamDir.z); 
	han=arg->GetDlgItem( IDC_GRIDPOS_Z_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamUp.x); 
	han=arg->GetDlgItem( IDC_GRIDROT_X_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamUp.y); 
	han=arg->GetDlgItem( IDC_GRIDROT_Y_STATIC);
	han->SetWindowText(s);
	s.Format("%.6f", arg->win3dMat->m_SceneObjects->m_CamUp.z); 
	han=arg->GetDlgItem( IDC_GRIDROT_Z_STATIC);
	han->SetWindowText(s);

	unsigned int cnt = arg->m_PtGroups.m_iPointGroups[arg->m_GroupListSelectedIndex].intCount;
	
	LPUNKNOWN *temp=NULL;
	DWORD num = 0;
	arg->win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals( &num, temp);
	temp = (LPUNKNOWN*)malloc(num*sizeof(LPUNKNOWN));
	arg->win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals( &num, temp);
	LPDIRECT3DRMMESHBUILDER3 *mbArray = (LPDIRECT3DRMMESHBUILDER3*)malloc(cnt*sizeof(LPDIRECT3DRMMESHBUILDER3));
	for(unsigned int j = 0;j<num;j++)
	{
		
		LPDIRECT3DRMVISUAL vis; 
		temp[ j]->QueryInterface(IID_IDirect3DRMVisual, (void**)&vis);;
		DWORD nCnt;
		vis->GetName( &nCnt, NULL );
		char *name = (char*)malloc( nCnt*sizeof(char));
		vis->GetName( &nCnt, name );
		
			vis->Release();
		if(strstr(name,"finalMesh")==NULL)
		{
		int vert = atoi( name );
			for(unsigned int k = 0;k<cnt;k++)
			{
				if(vert == arg->m_PtGroups.m_iPointGroups[arg->m_GroupListSelectedIndex].value[k])
				{
					mbArray[k] = (LPDIRECT3DRMMESHBUILDER3)vis;
					mbArray[k]->SetQuality( D3DRMFILL_WIREFRAME);
				}// eo if( vert == arg->
			}//eokfor
		}// eo if(strstr( name, "finalMesh")
	}//eo jfor
			arg->win3dMat->WinRender();
			for(int l=0;l<2000000;l++){}
			for(unsigned int k = 0;k<cnt;k++)
			{
				int test = (int)mbArray[k];
				if(test!=0 && test!=3452816845)
				{
					mbArray[k]->SetQuality( D3DRMFILL_SOLID);
					mbArray[k]->Release();
				}
			}
			arg->win3dMat->WinRender();
			arg->win3dMat->m_SceneObjects->finalMesh->SetQuality( D3DRMFILL_SOLID);
	if(num>0)free(temp);	
	if(cnt>0)free(mbArray);
	}
	}
	*pResult = 0;
}




void CGroupCtrl::OnCopyButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{
		POSITION t = m_GroupList.GetFirstSelectedItemPosition();
		if(t>0)
		{
		unsigned int i = (unsigned int)t-1;
		CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
		arg->m_GroupListSelectedIndex=i;
		
		unsigned int sz = arg->m_PtGroups.m_iPointGroups[i].intCount-1;
		D3DVECTOR *vs = (D3DVECTOR*)malloc(sz*sizeof(D3DVECTOR));
		for(unsigned int j=0;j<sz;j++)
		{
			D3DVECTOR v;
			arg->win3dMat->m_SceneObjects->finalMesh->GetVertex( arg->m_PtGroups.m_iPointGroups[i].value[j], &v);
			//CString ts;ts.Format("\n%d", arg->m_PtGroups.m_iPointGroups[i].value[j]);
4			//OutputDebugString(ts);
			D3DVECTOR t;
			arg->win3dMat->m_SceneObjects->gridFrame->InverseTransform( &t, &v );
			vs[j]=t;
		}//eojfor
		

		CreateDimensions(vs, sz);
		makeBox( vs, sz, box );

		if(sz>0)free(vs);
		

		
	CCopyPosRotScaleCtrl* ccprsctrl = new CCopyPosRotScaleCtrl();
	ccprsctrl->Create( IDD_COPY_POS_ROT_SCALE_DIALOG1);
	WINDOWPLACEMENT pwp;
	RECT r1;
	GetWindowRect(&r1);
	r1.left=350;
	r1.top=340;
	r1.bottom=440;
	r1.right=700;
	pwp.flags=WPF_RESTORETOMAXIMIZED;
	pwp.length=sizeof(WINDOWPLACEMENT);
	POINT max1;max1.x=0;max1.y=0;
	pwp.ptMaxPosition=max1;
	POINT min1;min1.x=0;min1.y=0;
	pwp.ptMinPosition=min1;
	pwp.rcNormalPosition=r1;
	pwp.showCmd=SW_SHOW;
				ccprsctrl->ShowWindow(SW_SHOW);
				ccprsctrl->SetWindowPlacement( &pwp );
	}//eo if(t>0)
		else{
			MessageBox("Please select an index of a group before pressing the copy button", "Failed to Select Group", MB_OK);
		}
	}
}

void CGroupCtrl::CreateDimensions(D3DVECTOR *copier, int qCount)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
				
		box[0]=copier[0].x;
		box[1]=copier[0].x;
		box[2]=copier[0].y;
		box[3]=copier[0].y;
		box[4]=copier[0].z;
		box[5]=copier[0].z;
				
		for(int i=1;i<qCount;i++)
		{
			if(copier[i].x<box[0]){box[0]=copier[i].x;}
			if(copier[i].x>box[1]){box[1]=copier[i].x;}
			if(copier[i].y<box[2]){box[2]=copier[i].y;}
			if(copier[i].y>box[3]){box[3]=copier[i].y;}
			if(copier[i].z<box[4]){box[4]=copier[i].z;}
			if(copier[i].z>box[5]){box[5]=copier[i].z;}
		}
		
}

float * GetU( D3DVECTOR v, LPD3DRMBOX b, LPDIRECT3DRM3 rm, CMakerC1Dlg* arg)
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

void SetTextCoords(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRM3 rm, CMakerC1Dlg* arg)
{
	D3DRMBOX box;
		mb->GetBox(&box);
		
				
		for(int i = 0;i<mb->GetVertexCount();i++)
		{
			D3DVECTOR v;
			mb->GetVertex( i, &v );
			float *u = GetU( v, &box, rm, arg);
			
			mb->SetTextureCoordinates(i, u[0], u[1]);
		
		
		}
}
LPDIRECT3DRMMATERIAL2 CGroupCtrl::MakeMaterial(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i)
	{
		 CMakerC1Dlg* m = (CMakerC1Dlg*)GetParent()->GetParent();
			
		 rm->CreateMaterial(m->m_MatArray.m_Mats[i].args[0], &mat);
	     mat->SetEmissive(m->m_MatArray.m_Mats[i].args[1], m->m_MatArray.m_Mats[i].args[2], m->m_MatArray.m_Mats[i].args[3]);
	     mat->SetSpecular(m->m_MatArray.m_Mats[i].args[4],  m->m_MatArray.m_Mats[i].args[5], m->m_MatArray.m_Mats[i].args[6]);
		 mat->SetAmbient(m->m_MatArray.m_Mats[i].args[7],  m->m_MatArray.m_Mats[i].args[8], m->m_MatArray.m_Mats[i].args[9]);
		 
		 return mat;
	}

void CGroupCtrl::makeBox(D3DVECTOR *copier, int qCount, float* b)
	{
		CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
		LPDIRECT3DRM rm;
		Direct3DRMCreate( &rm);
		LPDIRECT3DRM3 rm3 = NULL;
		rm->QueryInterface( IID_IDirect3DRM3, (void**)&rm3);
		
		
		rm3->CreateMeshBuilder( &arg->win3dMat->tempMeshBld );

		DWORD adwFace1Data[] = {  4,4,4,0,0,2,2,6,6,
							  4,4,4,6,6,2,2,0,0,
	                          4,4,4,5,5,1,1,0,0,
							  4,4,4,0,0,1,1,5,5,
	                          4,4,4,6,6,7,7,5,5,
							  4,4,4,5,5,7,7,6,6,
	                          4,0,0,1,1,3,3,2,2,
							  4,0,0,2,2,3,3,1,1,
	                          4,1,1,5,5,7,7,3,3,
							  4,1,1,3,3,7,7,5,5,
	                          4,3,3,7,7,6,6,2,2,
							  4,3,3,2,2,6,6,7,7,0 };
		D3DVECTOR avCubeVertices[] = { box[0], box[2], box[4],  box[0], box[2],  box[5],
									   box[0],  box[3], box[4],  box[0],  box[3],  box[5],
									   box[1], box[2], box[4],   box[1], box[2],  box[5],
									   box[1],  box[3], box[4],   box[1],  box[3],  box[5] };



	D3DVECTOR avCube1Normals[8];

	for(int i = 0;i<8;i++)
	{
		
		avCube1Normals[i]=avCubeVertices[i];
			D3DRMVectorNormalize(&avCube1Normals[i]);
	}

	arg->win3dMat->tempMeshBld->AddFaces( 8, avCubeVertices, 8, avCube1Normals,
			                            adwFace1Data, NULL );
	
		
		LPDIRECT3DRMFACE2 copyFace, copyFace2;
			rm3->CreateFace(&copyFace);
		arg->win3dMat->tempMeshBld->AddFace(copyFace);
		rm3->CreateFace(&copyFace2);
		arg->win3dMat->tempMeshBld->AddFace(copyFace2);
		int cnt = qCount-1;
		for( i =0;i<qCount;i++)
		{
			D3DVECTOR v1;
			v1.x = copier[i].x;
			v1.y = copier[i].y;
			v1.z = copier[i].z;
			arg->win3dMat->tempMeshBld->AddVertex(copier[i].x,copier[i].y,copier[i].z);
			D3DRMVectorNormalize(&v1);
			arg->win3dMat->tempMeshBld->AddNormal(v1.x,v1.y,v1.z);
			
			copyFace->AddVertexAndNormalIndexed(i,i);
			copyFace2->AddVertexAndNormalIndexed(cnt,cnt);cnt--;

		}
		
		BYTE fBlue=0;
		BYTE fGreen=255;
		BYTE fRed=0;
		BYTE bBlue=255;
		BYTE bGreen=0;
		BYTE bRed=0;
		//texture group1
		LPDIRECT3DRMMATERIAL2 mat1 = NULL;
			rm3->CreateMaterial(0.0F, &mat1);
		copyFace->SetMaterial(mat1);
		copyFace->SetColor(RGBA_MAKE(bRed, bGreen, bBlue, 128));
		copyFace2->SetMaterial(mat1);
		copyFace2->SetColor(RGBA_MAKE(bRed, bGreen, bBlue, 128));
			arg->win3dMat->tempMeshBld->SetMaterial(mat1);
			arg->win3dMat->tempMeshBld->SetColor(RGBA_MAKE(fRed, fGreen, fBlue, 128));
	
		arg->renderType = D3DRMRENDER_UNLITFLAT;
		arg->fillType = D3DRMFILL_SOLID;
		arg->lightStatus = D3DRMLIGHT_ON;
			
		arg->win3dMat->tempMeshBld->SetQuality(
						 arg->renderType+
						 arg->lightStatus+
						 arg->fillType
						 );
		copyFace->Release();
		copyFace2->Release();
		arg->win3dMat->m_SceneObjects->gridFrame->AddVisual(arg->win3dMat->tempMeshBld);
		
		
		mat1->Release();
		rm3->Release();
		rm->Release();
				
		arg->win3dMat->WinRender();


}

void CGroupCtrl::OnGroupButton1() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	POSITION t = m_GroupList.GetFirstSelectedItemPosition();
	int n = (int)t;
	CString s;
	s.Format("%d", n-1);
	m_GRoupOneEdit.SetWindowText(s);
	m_SelIndexOne = n - 1;
	

	}
}

void CGroupCtrl::OnGroupButton2() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	POSITION t = m_GroupList.GetFirstSelectedItemPosition();
	int n = (int)t;
	CString s;
	s.Format("%d", n-1);
	m_GroupTwoEdit.SetWindowText(s);
	m_SelIndexTwo = n - 1;
	}
	
}

void CGroupCtrl::OnChooseFacesButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	int len = arg->m_PtGroups.m_iPointGroups[m_SelIndexOne].intCount;
	m_FacesScroll1.SetScrollRange( 0, len-1, TRUE);
		m_FacesScroll1.SetScrollPos( 0, TRUE );
	}
}

void CGroupCtrl::OnAutoFaceButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	BeginWaitCursor();
	if(m_SelIndexOne>=0&&m_SelIndexTwo>=0)
	{
	if(m_SelIndexOne!=m_SelIndexTwo)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	if(arg->m_MatArray.m_Count>0)
	{

	//waitcursor
			undo.Deallocate();
			undo.m_FacesArray=undo.Allocate(0);
			m_UndoList.deallocate();
			m_UndoList.value=m_UndoList.allocate(0);
	
	
	
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm3 = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm3);
	SetTextCoords( arg->win3dMat->m_SceneObjects->finalMesh, rm3, arg);
	LPDIRECT3DRMTEXTURE3 texture  = NULL;
	LPDIRECT3DRMTEXTURE3 texture2 = NULL;
	LPDIRECT3DRMMATERIAL2 mat1 = NULL;
	LPDIRECT3DRMMATERIAL2 mat2 = NULL;
		mat1 = MakeMaterial(rm3, mat1, arg->selMatFront);
		if(arg->selMatBack>=0)
		mat2 = MakeMaterial(rm3, mat2, arg->selMatBack);
	if(	arg->selTexFrontPath.GetLength()>0)
			{
				
				rm3->LoadTexture(arg->selTexFrontPath, &texture);
			}
	if(	arg->selTexBackPath.GetLength()>0)
			{
				
				rm3->LoadTexture(arg->selTexBackPath, &texture2);
				
			}
	
	int len = arg->m_PtGroups.m_iPointGroups[m_SelIndexOne].intCount;
	int len2 =	arg->m_PtGroups.m_iPointGroups[m_SelIndexTwo].intCount;
	int num = 0;
	bool grOneHangFlag = false;
	bool grTwoHangFlag = false;
	if(len>len2)
	{
		grOneHangFlag = true;
		grTwoHangFlag = false;
		num = len2;
	}
	else if(len2>len)
	{
		grOneHangFlag = false;
		grTwoHangFlag = true;
		num=len;
	}
	else{
		
		num=len;
	}
	

		for(int i = 1;i<num-1;i++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			rm3->CreateFace(&face);
				undo.m_FacesArray=undo.Grow( face);
			arg->win3dMat->m_SceneObjects->finalMesh->AddFace(face);
			int v1 = arg->m_PtGroups.m_iPointGroups[m_SelIndexOne].value[i];
			int v2 = arg->m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[i];
			int pts[4];
			arg->cfpgdlg->facesCtrl->AddFaces();
				m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			face->AddVertexAndNormalIndexed( v1-1, v1-1);
			pts[0]=v1-1;
			face->AddVertexAndNormalIndexed(v1, v1);
			pts[1]=v1;
			face->AddVertexAndNormalIndexed(v2, v2);
			pts[2]=v2;
			face->AddVertexAndNormalIndexed(v2-1 , v2-1 );
			pts[3]= v2-1;
			arg->cfpgdlg->facesCtrl->SetFaceData(pts);
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatFront);
			//own.oVars.aboutToSetEdge = true;

			
			if(arg->textureFillMode==1)//FDIFFTEXTURES
			{
				
				rm3->CreateFace(&bface);
					undo.m_FacesArray=undo.Grow( bface);
				arg->win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
				arg->cfpgdlg->facesCtrl->AddFaces();
					m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			bface->AddVertexAndNormalIndexed( v1-1, v1-1);
			pts[0]=v1-1;
			bface->AddVertexAndNormalIndexed(v2-1 , v2-1 );
			pts[1]= v2-1;
			bface->AddVertexAndNormalIndexed(v2, v2);
			pts[2]=v2;
			bface->AddVertexAndNormalIndexed(v1, v1);
			pts[3]=v1;
			arg->cfpgdlg->facesCtrl->SetFaceData( pts);
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatBack);
				arg->m_bSetFacesButtonPushed = true;

			}
			arg->cfpgdlg->facesCtrl->DoTextureSetting3(arg->win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
		
		if(grOneHangFlag==true)
		{
			
		for(int j = len2-2;j<len-1;j++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			rm3->CreateFace(&face);
				undo.m_FacesArray=undo.Grow( face);
			arg->win3dMat->m_SceneObjects->finalMesh->AddFace(face);
			arg->cfpgdlg->facesCtrl->AddFaces();
				m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			int v1 = arg->m_PtGroups.m_iPointGroups[m_SelIndexOne].value[j];
			int v2 = arg->m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[(len2-2)];
			
			int pts[3];
			face->AddVertexAndNormalIndexed(v2 , v2 );
			pts[0]= v2;
			face->AddVertexAndNormalIndexed( v1-1, v1-1);
			pts[1]=v1-1;
			face->AddVertexAndNormalIndexed(v1, v1);
			pts[2]=v1;
			arg->cfpgdlg->facesCtrl->SetFaceData3(pts);
			
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatFront);
			//own.oVars.aboutToSetEdge = true;

			if(arg->textureFillMode==1)//FDIFFTEXTURES
			{
				
				rm3->CreateFace(&bface);
					undo.m_FacesArray=undo.Grow( bface);
				arg->win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
				arg->cfpgdlg->facesCtrl->AddFaces();
					m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			
			bface->AddVertexAndNormalIndexed(v2 , v2 );
			pts[0]= v2;
			bface->AddVertexAndNormalIndexed(v1, v1);
			pts[1]=v1;
			bface->AddVertexAndNormalIndexed( v1-1, v1-1);
			pts[2]=v1-1;
			arg->cfpgdlg->facesCtrl->SetFaceData3(pts);
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatBack);
				arg->m_bSetFacesButtonPushed = true;

			}
			arg->cfpgdlg->facesCtrl->DoTextureSetting3(arg->win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
			
		}// eo if(grOneHangFlag==true)

		else if(grTwoHangFlag==true)
		{
			
		for( i = len-2;i<len2-1;i++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			rm3->CreateFace(&face);
				undo.m_FacesArray=undo.Grow( face);
			arg->win3dMat->m_SceneObjects->finalMesh->AddFace(face);
			arg->cfpgdlg->facesCtrl->AddFaces();
				m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			int v1 = arg->m_PtGroups.m_iPointGroups[m_SelIndexOne].value[len-2];
			int v2 = arg->m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[i];
			int pts[3];
			face->AddVertexAndNormalIndexed( v1, v1);
			pts[0]=v1;
			face->AddVertexAndNormalIndexed(v2 , v2 );
			pts[1]= v2;
			face->AddVertexAndNormalIndexed(v2-1, v2-1);
			pts[2]=v2-1;
			arg->cfpgdlg->facesCtrl->SetFaceData3(pts);
			
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatFront);
			//own.oVars.aboutToSetEdge = true;

			if(arg->textureFillMode==1)//FDIFFTEXTURES
			{
				
				rm3->CreateFace(&bface);
					undo.m_FacesArray=undo.Grow( bface);
				arg->win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
				arg->cfpgdlg->facesCtrl->AddFaces();
					m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
			
			bface->AddVertexAndNormalIndexed( v1, v1);
			pts[0]=v1;
			bface->AddVertexAndNormalIndexed(v2-1 , v2-1 );
			pts[1]= v2-1;
			bface->AddVertexAndNormalIndexed(v2, v2);
			pts[2]=v2;
			arg->cfpgdlg->facesCtrl->SetFaceData3(pts);
			arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatBack);
				arg->m_bSetFacesButtonPushed = true;

			}
			arg->cfpgdlg->facesCtrl->DoTextureSetting3(arg->win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
			
		}//eo if(grTwoHangFlag==true)
		arg->win3dMat->m_SceneObjects->finalMesh->GenerateNormals( 0.0F, 2);
	rm3->Release();
	rm1->Release();
	GetDlgItem(IDC_UNDO_BUTTON)->EnableWindow(TRUE);
	arg->m_GroupListSelectedIndex=-858993460;
	m_SelIndexOne=m_SelIndexTwo=-858993460;
	}// eo  if(m_MatCount>)
	else{
		
		MessageBox( "Objects cannot be made without first loading a set of materials using the material editor", "No Materials Loaded", MB_OK);
	}//eo if(arg->m_MatArray.m_Count<=0)
	}// eo if(m_SelIndexOne!=m_SelIndexTwo)
	else{
		MessageBox( "1) Select an index of a group.\n2)Push the Group 1 button.\n3)Select an index of a different group.\n4) Push the Group 2 button.\n5) Make sure you have at least one material selected from the material list.\n6)Press the auto face button", "Not Enough Groups Selected", MB_OK);
	}
	}// eo if(m_SelIndexOne>=0&&m_SelIndexTwo>=0)
	else{
		MessageBox( "1) Select an index of a group.\n2)Push the Group 1 button.\n3)Select an index of a different group.\n4) Push the Group 2 button.\n5) Make sure you have at least one material selected from the material list.\n6)Press the auto face button", "Not Enough Groups Selected", MB_OK);
	}
	EndWaitCursor();	
	}
}

void CGroupCtrl::OnSetFaceButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	BeginWaitCursor();
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	if(arg->m_GroupListSelectedIndex>=0&&arg->m_GroupListSelectedIndex<arg->m_PtGroups.m_iPtGroupCount)
	{
	if(arg->m_MatArray.m_Count>0)
	{
	
	//waitcursor
			undo.Deallocate();
			undo.m_FacesArray=undo.Allocate(0);
			m_UndoList.deallocate();
			m_UndoList.value=m_UndoList.allocate(0);
	
	//waitcursor
	
	LPDIRECT3DRM rm2;
	LPDIRECT3DRM3 rm4 = NULL;
	Direct3DRMCreate(&rm2);
	rm2->QueryInterface(IID_IDirect3DRM3, (void**)&rm4);
	SetTextCoords( arg->win3dMat->m_SceneObjects->finalMesh, rm4, arg);
	LPDIRECT3DRMTEXTURE3 texture  = NULL;
	LPDIRECT3DRMTEXTURE3 texture2 = NULL;
	LPDIRECT3DRMMATERIAL2 mat1 = NULL;
	LPDIRECT3DRMMATERIAL2 mat2 = NULL;
		mat1 = MakeMaterial(rm4, mat1, arg->selMatFront);
		//if(arg->selMatBack>=0)
		mat2 = MakeMaterial(rm4, mat2, arg->selMatBack);
	if(	arg->selTexFrontPath.GetLength()>0)
			{
				rm4->LoadTexture(arg->selTexFrontPath, &texture);
			}
	if(	arg->selTexBackPath.GetLength()>0)
			{
				rm4->LoadTexture(arg->selTexBackPath, &texture2);
			}
		
		int chosen = arg->m_GroupListSelectedIndex;
		int cnt = arg->m_PtGroups.m_iPointGroups[chosen].intCount;
		
		// Assign the indices (build a triangle fan for high-order polygons)
	DWORD dwNumVerticesPerFace = cnt;
	LPDIRECT3DRMFACE2 face,bface;
		    rm4->CreateFace(&face);
			arg->win3dMat->m_SceneObjects->finalMesh->AddFace(face);
			undo.m_FacesArray=undo.Grow( face);
			arg->cfpgdlg->facesCtrl->AddFaces();	
			m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
		if( arg->textureFillMode == 1)//FDIFFTEXTURES
		{
			rm4->CreateFace( &bface );
				arg->win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
				undo.m_FacesArray=undo.Grow( bface);
			arg->cfpgdlg->facesCtrl->AddFaces();
			m_UndoList.value= m_UndoList.grow(arg->cfpgdlg->facesCtrl->currentFace);
		}
			int *fp = new int[cnt];
			int *bp = new int[cnt];
			
    int n = dwNumVerticesPerFace-2;
	for( DWORD i=0; i<dwNumVerticesPerFace-1; i++ )
	{
		 
			int a = (WORD)arg->m_PtGroups.m_iPointGroups[chosen].value[i];
			fp[i]=a;
				face->AddVertexAndNormalIndexed(a,a);
				if( arg->textureFillMode == 1)//FDIFFTEXTURES
				{
					bp[i] = a = (WORD)arg->m_PtGroups.m_iPointGroups[chosen].value[n];
					bface->AddVertexAndNormalIndexed(a,a);
					n--;
				}
	}
			face->SetMaterial(mat1);
				D3DCOLOR col = RGBA_MAKE((int)(arg->frontRed*255), (int)(arg->frontGreen*255), (int)(arg->frontBlue*255), (int)(arg->frontAlpha*255));
				face->SetColor(col);
			if(	arg->selTexFrontPath.GetLength()>0)
			{
				face->SetTexture(texture);
			}
				arg->cfpgdlg->facesCtrl->SetFaceDataMany(fp, cnt);
				arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatFront);
		if( arg->textureFillMode == 1)//FDIFFTEXTURES
		{
			bface->SetMaterial(mat2);
			D3DCOLOR bcol = RGBA_MAKE((int)(arg->backRed*255), (int)(arg->backGreen*255), (int)(arg->backBlue*255), (int)(arg->backAlpha*255));
			//bface->SetColorRGB(arg->backRed, arg->backGreen, arg->backBlue);
			bface->SetColor(bcol);
			if(	arg->selTexBackPath.GetLength()>0)
			{
				bface->SetTexture(texture2);
			}
				arg->cfpgdlg->facesCtrl->SetFaceDataMany(bp, cnt);
				arg->cfpgdlg->facesCtrl->SetFaceList(arg->selMatBack);

		}
		delete fp;
		delete bp;
		
		rm2->Release();
		rm4->Release();
		GetDlgItem(IDC_UNDO_BUTTON)->EnableWindow(TRUE);
	// normalcursor
		arg->m_GroupListSelectedIndex=-858993460;
	}// eo if(arg->m_MatArray.m_Count>0)
	else{
		
		MessageBox( "Objects cannot be made without first loading a set of materials using the material editor", "No Materials Loaded", MB_OK);
	}//eo if(arg->m_MatArray.m_Count<=0)
	}
	else{
		MessageBox("Oops, you failed to select a group index before pressing this button", "No Group Selected", MB_OK);
	}
	EndWaitCursor();
	}
}

void CGroupCtrl::OnUndoButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{
	if(undo.m_Count>0)
	{
		CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
		for(unsigned int i = 0;i<undo.m_Count;i++)
		{
			arg->win3dMat->m_SceneObjects->finalMesh->DeleteFace( undo.m_FacesArray[i]);
			
		}
		for(unsigned int j = 0;j<undo.m_Count;j++)
		{
			int k = (undo.m_Count-1)-j;
			arg->cfpgdlg->facesCtrl->m_FacesList.DeleteItem( m_UndoList.value[k]);
			//CString s;s.Format("\ntest  %d",m_UndoList.value[k]);
			//OutputDebugString(s);
		}
		arg->cfpgdlg->facesCtrl->faceCnt-=undo.m_Count;
		arg->win3dMat->WinRender();
		
		
	}
	GetDlgItem(IDC_UNDO_BUTTON)->EnableWindow(FALSE);
	}
}

void CGroupCtrl::OnDeleteGroupButton() 
{
	if(m_GroupList.GetItemCount()>0)
	{

	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	if(arg->m_GroupListSelectedIndex>=0)
	{
		arg->m_PtGroups.m_iPointGroups=arg->m_PtGroups.Shrink(arg->m_GroupListSelectedIndex);
		arg->m_PtGroups.m_Mouse=arg->m_PtGroups.ShrinkMouse(arg->m_GroupListSelectedIndex);
		arg->m_PtGroups.m_CamGridStats = arg->m_PtGroups.ShrinkStats(arg->m_GroupListSelectedIndex);
		arg->m_iGroupCount--;
		
		arg->cfpgdlg->groupCtrl->m_GroupList.DeleteItem( arg->m_GroupListSelectedIndex);
		CString s;
		for(unsigned int i = 0;i<arg->m_iGroupCount;i++)
		{
			s.Format("%d",i);
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( i, 0, s);
		}
	}
	}
}

void CGroupCtrl::OnLastToFirstCheck() 
{

	if(m_LastToFirstCheck.GetCheck()==1)
	{
		m_bLastPointInGroupToFirst 	= true;
	}
	else if(m_LastToFirstCheck.GetCheck()==0){
		m_bLastPointInGroupToFirst 	= false;
	}	
}

BOOL CGroupCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LastToFirstCheck.SetCheck(0);
	m_bLastPointInGroupToFirst 	= false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
