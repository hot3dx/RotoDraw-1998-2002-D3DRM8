// PointCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "PointCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointCtrl dialog


CPointCtrl::CPointCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CPointCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPointCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointCtrl)
	DDX_Control(pDX, IDC_POINTS_LIST, m_PtsList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointCtrl, CDialog)
	//{{AFX_MSG_MAP(CPointCtrl)
	ON_NOTIFY(NM_CLICK, IDC_POINTS_LIST, OnClickPointsList)
	ON_BN_CLICKED(IDC_DELETE_VERTEX_BUTTON, OnDeleteVertexButton)
	ON_BN_CLICKED(IDC_CUSTOM_GROUP_BUTTON, OnCustomGroupButton)
	ON_BN_CLICKED(IDC_ADD_TO_GROUP_BUTTON, OnAddToGroupButton)
	ON_BN_CLICKED(IDC_SET_GROUP_BUTTON, OnSetGroupButton)
	ON_BN_CLICKED(IDC_SET_POINT_BUTTON, OnSetPointButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointCtrl message handlers

void CPointCtrl::OnClickPointsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(this->m_PtsList.GetItemCount()>0)
	{
		CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	
		POSITION t = this->m_PtsList.GetFirstSelectedItemPosition();
		int index = (int)t-1;
		arg->m_PtsListSelectedIndex=index;
		LPDIRECT3DRMMESHBUILDER3 mb;
		D3DVECTOR v;
		arg->win3dMat->m_SceneObjects->finalMesh->GetVertex( index, &v);
	LPUNKNOWN *temp=NULL;
	DWORD num = 0;
	arg->win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals( &num, temp);
	temp = (LPUNKNOWN*)malloc(num*sizeof(LPUNKNOWN));
	arg->win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals( &num, temp);
	
	D3DCOLOR color;
	for(unsigned int j = 0;j<num;j++)
	{
		
		LPDIRECT3DRMVISUAL vis; 
		temp[ j]->QueryInterface(IID_IDirect3DRMVisual, (void**)&vis);
		DWORD nCnt;
		vis->GetName( &nCnt, NULL );
		char *name = (char*)malloc( nCnt*sizeof(char));
		vis->GetName( &nCnt, name );
			vis->Release();
		
		if(strstr(name,"finalMesh")==NULL)
		{
		int vert = atoi( name );
			if(vert == index)
				{
					mb = (LPDIRECT3DRMMESHBUILDER3)vis;
					arg->selectedMesh = mb;
					mb->SetQuality( D3DRMFILL_WIREFRAME);
					color = mb->GetVertexColor(0);
					if(color!=RGBA_MAKE(255,0,0,255))
					{
						mb->SetVertexColor( 0, RGBA_MAKE(255,0,0,255));
						mb->SetVertexColor( 1, RGBA_MAKE(255,0,0,255));
						mb->SetVertexColor( 2, RGBA_MAKE(255,0,0,255));
						mb->SetVertexColor( 3, RGBA_MAKE(255,0,0,255));
					}
					else{
						mb->SetVertexColor( 0, RGBA_MAKE(0,255,0,255));
						mb->SetVertexColor( 1, RGBA_MAKE(0,255,0,255));
						mb->SetVertexColor( 2, RGBA_MAKE(0,255,0,255));
						mb->SetVertexColor( 3, RGBA_MAKE(0,255,0,255));
					}
						j=num;
				}// eo if( vert == arg->
			
		}// eo if(strstr( name, "finalMesh")
	
	}//eo jfor
			arg->win3dMat->WinRender();
			for(int k = 0;k<2000000;k++){}
			for( k = 0;k<2000000;k++){}
			for( k = 0;k<2000000;k++){}
				mb->SetQuality( D3DRMFILL_SOLID);
				mb->SetVertexColor(0,color);
				mb->SetVertexColor(1,color);
				mb->SetVertexColor(2,color);
				mb->SetVertexColor(3,color);
					mb->Release();
			
			arg->win3dMat->WinRender();
			arg->win3dMat->m_SceneObjects->finalMesh->SetQuality( D3DRMFILL_SOLID);
	if(num>0)free(temp);	

	CEdit* xe = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITX);
	xe->SetWindowText( this->m_PtsList.GetItemText(index, 1) );
	CEdit* ye = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITY);
	ye->SetWindowText( this->m_PtsList.GetItemText(index, 2) );
	CEdit* ze = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITZ);
	ze->SetWindowText( this->m_PtsList.GetItemText(index, 3) );
	}	
	*pResult = 0;
}

void CPointCtrl::OnDeleteVertexButton() 
{
	if(this->m_PtsList.GetItemCount()>0)
	{
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent()->GetParent();
	unsigned int cnt = arg->win3dMat->m_SceneObjects->finalMesh->GetVertexCount();
	D3DVECTOR *v = (D3DVECTOR*)malloc((cnt-1)*sizeof(D3DVECTOR));
	D3DVECTOR *n = (D3DVECTOR*)malloc((cnt-1)*sizeof(D3DVECTOR));
	float *u =(float*)malloc((cnt-1)*sizeof(float));
	float *t =(float*)malloc((cnt-1)*sizeof(float));
	LPDIRECT3DRMMESHBUILDER3 mb;
	unsigned int f1 = arg->win3dMat->m_SceneObjects->finalMesh->GetFaceCount();
		LPDIRECT3DRMFACE2 *faceArray = (LPDIRECT3DRMFACE2*)malloc(f1*sizeof(LPDIRECT3DRMFACE2));
	unsigned int n1 = 0;
	unsigned int index = arg->m_PtsListSelectedIndex;
	for(unsigned int i = 0;i<cnt;i++)
	{
		if(i!=index)
		{
			arg->win3dMat->m_SceneObjects->finalMesh->GetVertex(i, &v[n1]);
			arg->win3dMat->m_SceneObjects->finalMesh->GetNormal(i, &n[n1++]);
			arg->win3dMat->m_SceneObjects->finalMesh->GetTextureCoordinates( i, &t[i], &u[i] );

		}
	}
	// save face data;
	for(i=0;i<f1;i++)
	{
		arg->win3dMat->m_SceneObjects->finalMesh->GetFace( i, &faceArray[i]);
	}
	arg->win3dMat->m_scene->DeleteVisual(arg->win3dMat->m_SceneObjects->finalMesh);
	
	//Delete tetra
		LPUNKNOWN *temp=NULL;
	DWORD num = 0;
	arg->win3dMat->m_scene->GetVisuals( &num, temp);
	temp = (LPUNKNOWN*)malloc(num*sizeof(LPUNKNOWN));
	arg->win3dMat->m_scene->GetVisuals( &num, temp);
	
	int newid = 0;
	bool delVis = false;
	for(unsigned int j = 0;j<num;j++)
	{
		
		LPDIRECT3DRMVISUAL vis; 
		temp[ j]->QueryInterface(IID_IDirect3DRMVisual, (void**)&vis);;
		DWORD nCnt;
		vis->GetName( &nCnt, NULL );
		char *name = (char*)malloc( nCnt*sizeof(char));
		vis->GetName( &nCnt, name );
			
		CString s;
		s.Format("%d", index);
		if(strstr(name,"finalMesh")==NULL)
		{
		unsigned int vert = atoi( name );
			s.Format("%s", name);
			
		
			vis->QueryInterface(IID_IDirect3DRMMeshBuilder3,(void**)&mb);
			if(vert == index)
				{
					
				for(unsigned int m=0;m<4;m++)
					{
						
						LPDIRECT3DRMFACE2 df2;
							mb->GetFace(m,&df2);
					
						mb->DeleteFace(df2);
						
						df2->Release();
					}
					int dn=mb->DeleteNormals(0,4);
					int dv=mb->DeleteVertices(0,4);
					HRESULT hr = arg->win3dMat->m_scene->DeleteVisual(mb);
							hr = arg->win3dMat->m_scene->DeleteVisual(vis);
					
				
					delVis=true;
									
				}// eo if( vert == arg->
			if(vert>index){
			s.Format("%d", vert-1);
			mb->SetName(s);
			
			}
		}// eo if(strstr( name, "finalMesh")
		if(delVis==false)
			vis->Release();
		else delVis=false;
	}
	/////////////////////////////////////
	//// recreate mesh
	///////////////////////////////////
	LPDIRECT3DRM rm;
	Direct3DRMCreate(&rm);
	LPDIRECT3DRM3 rm3;
	rm->QueryInterface(IID_IDirect3DRM3, (void**)&rm3);
		rm3->CreateMeshBuilder(&arg->win3dMat->m_SceneObjects->finalMesh);
		
	rm->Release();
	rm3->Release();
	// add verts, norms, textcoords
	for(i = 0;i<cnt-1;i++)
	{
		arg->win3dMat->m_SceneObjects->finalMesh->AddVertex(v[i].x, v[i].y, v[i].z);
		arg->win3dMat->m_SceneObjects->finalMesh->AddNormal(n[i].x, n[i].y, n[i].z);
		arg->win3dMat->m_SceneObjects->finalMesh->SetTextureCoordinates( i, t[i], u[i]);
	}
	// add faces
	if(f1>0)
	{
		for(i=0;i<f1;i++)
		{
			
			
		//	arg->win3dMat->m_SceneObjects->finalMesh->
		}
	}
	arg->win3dMat->m_scene->AddVisual(arg->win3dMat->m_SceneObjects->finalMesh);
	
	if(cnt==1)
	{
		m_PtsList.DeleteItem( index );
		arg->m_MeshPoints.x.deallocate();
		arg->m_MeshPoints.y.deallocate();
		arg->m_MeshPoints.z.deallocate();
		arg->m_MeshPoints.m_iNumPoints=0;
		
		arg->m_iPointCount=0;
		arg->m_iTempGroupCount=0;

			arg->m_PtGroups.m_iPointGroups = arg->m_PtGroups.Shrink(0);
			arg->m_PtGroups.m_Mouse        = arg->m_PtGroups.ShrinkMouse(0);
			arg->m_PtGroups.m_CamGridStats = arg->m_PtGroups.ShrinkStats(0);
			arg->cfpgdlg->groupCtrl->m_GroupList.DeleteItem(i);
			arg->m_iGroupCount=0;
			arg->m_PtGroups.m_iPtStatsCount=arg->m_PtGroups.m_iPtMouseCount=arg->m_PtGroups.m_iPtGroupCount=0;


	}
	else{
		m_PtsList.DeleteItem( index );
		CString s;
		arg->m_MeshPoints.x.value = arg->m_MeshPoints.x.shrink(index);
		arg->m_MeshPoints.y.value = arg->m_MeshPoints.y.shrink(index);
		arg->m_MeshPoints.z.value = arg->m_MeshPoints.z.shrink(index);
		arg->m_MeshPoints.m_iNumPoints--;
		
				
		for(i = index;i<cnt-1;i++)
		{
			CString s;
			s.Format("%d",i);
			m_PtsList.SetItemText( i, 0, s);
		}
	}

	if((cnt-1)>0)free(temp);
	// redo group lists;
	//
	unsigned int iNumOfGroups = arg->m_PtGroups.m_iPtGroupCount;
	arg->cfpgdlg->groupCtrl->m_GroupList.DeleteAllItems();
	for(i=0;i<iNumOfGroups;i++)
	{
		CString s;
		unsigned int ic = arg->m_PtGroups.m_iPointGroups[i].intCount;
		if(ic>2)
		{
			arg->cfpgdlg->groupCtrl->m_GroupList.InsertItem( i, "");
	
			s.Format("%d", i);
			arg->cfpgdlg->groupCtrl->m_GroupList.InsertItem( i, s);
			s.Format("%d", ic-2);
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( i, 1, s);
			CString list;
			CString temp;
			bool removeValueFlag = false;
			for(unsigned int j=0;j<ic;j++)
			{
				// if one of the points in a group is the index
				int t = arg->m_PtGroups.m_iPointGroups[i].value[j];
				if(t==(int)index)
				{
					// remove that value from the group
					removeValueFlag = true;
					
				}// eo if(t==(int)index)
				else if(t>(int)index)
				{
					arg->m_PtGroups.m_iPointGroups[i].value[j]-=1;
					s.Format("%d, ", arg->m_PtGroups.m_iPointGroups[i].value[j]);
					temp.Format("%s%s", list, s);
					list.Format("%s", temp);
				}
				else{

				s.Format("%d, ", arg->m_PtGroups.m_iPointGroups[i].value[j]);
				temp.Format("%s%s", list, s);
				list.Format("%s", temp);
				}
				
			} // eo for(unsigned int j=0;j<ic;j++)
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( i, 2, list);
			if(removeValueFlag==true)
			{
				arg->m_PtGroups.m_iPointGroups[i].value	= arg->m_PtGroups.m_iPointGroups[i].shrink( index );
				arg->m_PtGroups.m_Mouse[i].value		= arg->m_PtGroups.m_Mouse[i].shrink( index );
				removeValueFlag=false;
			}
		}// eo if(ic>1)
	}// eo for(i=0;i<iNumOfGroups;i++)
	}
}



void CPointCtrl::OnCustomGroupButton() 
{
	
}

void CPointCtrl::OnAddToGroupButton() 
{
	
	
}

void CPointCtrl::OnSetGroupButton() 
{
	
}

void CPointCtrl::OnSetPointButton() 
{
	if(this->m_PtsList.GetItemCount()>0)
	{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	int index = arg->m_PtsListSelectedIndex;

	D3DVECTOR v;
	arg->win3dMat->m_SceneObjects->finalMesh->GetVertex( index, &v );
		CEdit* xe = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITX);
		CString* s1 = new CString();
		CString* s2 = new CString();
		CString* s3 = new CString();
		xe->GetWindowText( *s1 );
		float x,y,z;
		
		x = (float)atof(s1->GetBuffer(s1->GetLength()));
		CEdit* ye = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITY);
		ye->GetWindowText( *s2 );
		y = (float)atof(s2->GetBuffer(s2->GetLength()));
		CEdit* ze = (CEdit*)GetDlgItem(IDC_SET_POINT_EDITZ);
		ze->GetWindowText( *s3 );
		z = (float)atof(s3->GetBuffer(s3->GetLength()));

		this->m_PtsList.SetItemText( index, 1, s1->GetBuffer(s1->GetLength()) );
		this->m_PtsList.SetItemText( index, 2, s2->GetBuffer(s2->GetLength()) );
		this->m_PtsList.SetItemText( index, 3, s3->GetBuffer(s3->GetLength()) );
		arg->win3dMat->m_SceneObjects->finalMesh->SetVertex( index, x, y, z);


	arg->selectedMesh->SetVertex( 0, 0.5F+x, 0.5F+y, -0.5F+z);
	arg->selectedMesh->SetVertex( 1, -0.5F+x, 0.5F+y, -0.5F+z);
	arg->selectedMesh->SetVertex( 2, 0.0F+x, 0.0F+y, 0.5F+z);
	arg->selectedMesh->SetVertex( 3, -0.0F+x, -0.5F+y, -0.5F+z);
	
	}			
}
