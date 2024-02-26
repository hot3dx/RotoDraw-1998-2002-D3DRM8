// BrushCreateCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "BrushCreateCtrl.h"
#include "CopyPosRotScaleCtrl.h"
#include "tetra.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrushCreateCtrl dialog


CBrushCreateCtrl::CBrushCreateCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CBrushCreateCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrushCreateCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBrushCreateCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrushCreateCtrl)
	DDX_Control(pDX, IDC_BRUSH_BITMAP_STATIC, m_mystatic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrushCreateCtrl, CDialog)
	//{{AFX_MSG_MAP(CBrushCreateCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_SET_FLAT_CHECK, OnSetFlatCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrushCreateCtrl message handlers
bool LButtonDown = false;
void CBrushCreateCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
	LButtonDown = true;
	CRect r;
		m_mystatic.GetWindowRect(&r);
		if(point.x>10&&point.x<234&&point.y>10&&point.y<234)
		{
			
			int px = point.x-=14;
			int py = point.y-=14;
			
			int w, h;
			float y, z, uw, uh;
			w = r.right-r.left;
			h=  r.bottom-r.top;
			uw=(float)w;
			uw/=40.0F;
			uh=(float)h;
			uh/=40.0F;
			y = (float)point.y-110;y/=uh;
			z =	(float)point.x-110;z/=uw;

			CString s;
			s.Format("z: %.6f     y: %.6f", z, -y);
			GetDlgItem(IDC_YZLOCSTATIC)->SetWindowText(s);

			if(LButtonDown==true)
			{
				CClientDC dc(&m_mystatic);
				dc.SetPixel( px, py, RGB(0,0,0));
				float x1,y1;
				x1=point.x/40.0F;
				y1=point.y/40.0F;
				arg->m_iTempGroup[arg->m_iTempGroupCount]=arg->m_iPointCount;
				arg->m_iTempMouse[arg->m_iTempGroupCount] = point;
				
				if(m_bSetFlatCheck == false)
				{
					zbr[m_iBrushPtCount]=z;	
					ybr[m_iBrushPtCount]=-y;	
					xbr[m_iBrushPtCount]=0.0F;
				}
				else
				{
					xbr[m_iBrushPtCount]=z;	
					ybr[m_iBrushPtCount]=-y;	
					zbr[m_iBrushPtCount]=0.0F;
				}

				brMouse[m_iBrushPtCount].x = point.x;
				brMouse[m_iBrushPtCount].y = point.y;
					arg->m_iTempGroupCount++;
					arg->m_iPointCount++;
					m_iBrushPtCount++;
					
				DeleteObject(dc);
			}
		}
	
	
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CBrushCreateCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_mystatic.ModifyStyle( SS_SIMPLE, SS_BITMAP|SS_SUNKEN);
	

	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
	arg->m_bFirstBrushDataToCopy=false;
	arg->m_iTempGroupCount=0;
	m_iBrushPtCount=0;
	m_bSetFlatCheck = false;
	
	HANDLE han = LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 220, 220, LR_DEFAULTCOLOR);
		m_mystatic.SetBitmap( HBITMAP(han) );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBrushCreateCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void CBrushCreateCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
		CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
		CRect r;
		m_mystatic.GetWindowRect(&r);
		if(point.x>10&&point.x<236&&point.y>10&&point.y<234)
		{
			
			int px = point.x-=14;
			int py = point.y-=14;
			
			int w, h;
			float y, z, uw, uh;
			w = r.right-r.left;
			h=  r.bottom-r.top;
			uw=(float)w;
			uw/=40.0F;
			uh=(float)h;
			uh/=40.0F;
			y = (float)point.y-110;y/=uh;
			z =	(float)point.x-110;z/=uw;

			CString s;
			s.Format("z: %.6f     y: %.6f", z, -y);
			GetDlgItem(IDC_YZLOCSTATIC)->SetWindowText(s);

			if(LButtonDown==true)
			{
				CClientDC dc(&m_mystatic);
				dc.SetPixel( px, py, RGB(0,0,0));
				float x1,y1;
				x1=point.x/40.0F;
				y1=point.y/40.0F;
				arg->m_iTempGroup[arg->m_iTempGroupCount]=arg->m_iPointCount;
				arg->m_iTempMouse[arg->m_iTempGroupCount] = point;
				
				if(m_bSetFlatCheck == false)
				{
					zbr[m_iBrushPtCount]=z;	
					ybr[m_iBrushPtCount]=-y;	
					xbr[m_iBrushPtCount]=0.0F;
				}
				else
				{
					xbr[m_iBrushPtCount]=z;	
					ybr[m_iBrushPtCount]=-y;	
					zbr[m_iBrushPtCount]=0.0F;
				}

				brMouse[m_iBrushPtCount].x = point.x;
				brMouse[m_iBrushPtCount].y = point.y;
					arg->m_iTempGroupCount++;
					arg->m_iPointCount++;
					m_iBrushPtCount++;
				DeleteObject(dc);
			}
		}
	

	CDialog::OnMouseMove(nFlags, point);
}

void CBrushCreateCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LButtonDown = false;
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CBrushCreateCtrl::OnRefreshButton() 
{
	m_mystatic.ModifyStyle( SS_SIMPLE, SS_BITMAP|SS_SUNKEN);
	HANDLE han = LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 220, 220, LR_DEFAULTCOLOR);
	m_mystatic.SetBitmap( HBITMAP(han) );
	m_iBrushPtCount=0;
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
	arg->m_bFirstBrushDataToCopy=false;
}

void CBrushCreateCtrl::CreateDimensions(D3DVECTOR *copier, int qCount)
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

void CBrushCreateCtrl::makeBox(D3DVECTOR *copier, int qCount, float* b)
	{
		CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent();
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

	for( int i = 0;i<8;i++)
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

void CBrushCreateCtrl::OnOK() 
{
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
	if(arg->m_iDrawMode==2)
	{
	
	/////////////////////////////////////////
	/// Copy
	/////////////////////////////////////////
		
		//unsigned int i = arg->m_iGroupCount-1;
		
		//arg->m_GroupListSelectedIndex=i;
		
		unsigned int sz = m_iBrushPtCount;//arg->m_PtGroups.m_iPointGroups[i].intCount-1;
		D3DVECTOR *vs = (D3DVECTOR*)malloc(sz*sizeof(D3DVECTOR));
		for(unsigned int j=0;j<sz;j++)
		{
			D3DVECTOR v;
			v.x=xbr[j];
			v.y=ybr[j];
			v.z=zbr[j];
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

	/////////////////////////////////////////////////////////////
	//////////
	/////////////////////////////////////////////////////////////

	CString s;
		
		unsigned int vCount = m_iBrushPtCount;
		
		arg->m_MeshPoints.GrowByEmptyEnd(vCount);
		
		for(unsigned int i = 8;i<vCount+8;i++)
		{
			
			D3DVECTOR s1,v;
			
			arg->win3dMat->tempMeshBld->GetVertex( i, &s1 );
			
			arg->win3dMat->m_SceneObjects->gridFrame->Transform(&v,&s1);
			
			arg->m_MeshPoints.Set( i-8, v.x, v.y, v.z );
			CTetra apoint;
			LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(v.x, v.y, v.z, arg->GetTexClass()->r, arg->GetTexClass()->g, arg->GetTexClass()->b);
			arg->win3dMat->m_SceneObjects->finalMeshFrame->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			s.Format("%d", i-8);
				tetra->SetName(s);
			
				s.Format("%d", arg->m_MeshPoints.m_iNumPoints);
				arg->cfpgdlg->ptCtrl->m_PtsList.InsertItem( arg->m_MeshPoints.m_iNumPoints, s);
				s.Format("%.6f", arg->m_MeshPoints.x.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 1, s);
				s.Format("%.6f", arg->m_MeshPoints.y.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 2, s);
				s.Format("%.6f", arg->m_MeshPoints.z.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 3, s);
				arg->m_MeshPoints.m_iNumPoints++;
			}
			s.Format("%d", arg->m_iGroupCount);
			arg->cfpgdlg->groupCtrl->m_GroupList.InsertItem( arg->m_iGroupCount, s);
			s.Format("%d", arg->m_iTempGroupCount);
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( arg->m_iGroupCount, 1, s);
			CString list;
			CString temp;
			CHDXINTARRAY arg1;
			arg1.allocate(0);
			arg1.value=arg1.growByEmptyEnd( arg->m_iTempGroupCount+1 ); 

			CHDXPOINTARRAY argmx;
			argmx.allocate(0);
			argmx.value=argmx.growByEmptyEnd( arg->m_iTempGroupCount+1 ); 

			

			for( j=0;j<arg->m_iTempGroupCount;j++)
			{
				arg1.set( j, arg->m_iTempGroup[j] );
				argmx.set( j, brMouse[j] );
				s.Format("%d, ", arg1.value[j]);
				temp.Format("%s%s", list, s);
				list.Format("%s", temp);
			}
			arg->m_PtGroups.m_iPointGroups=arg->m_PtGroups.Grow( arg1 );
			arg->m_PtGroups.m_Mouse=arg->m_PtGroups.GrowMouse( argmx );
			
	
			CCamGridStats stats;
			stats.m_CamPosX=arg->win3dMat->m_SceneObjects->m_CamPos.x;
			stats.m_CamPosY=arg->win3dMat->m_SceneObjects->m_CamPos.y;
			stats.m_CamPosZ=arg->win3dMat->m_SceneObjects->m_CamPos.z;
			stats.m_CamRotX=arg->win3dMat->m_SceneObjects->m_CamRot.x;
			stats.m_CamRotY=arg->win3dMat->m_SceneObjects->m_CamRot.y;
			stats.m_CamRotZ=arg->win3dMat->m_SceneObjects->m_CamRot.z;
			stats.m_CamTheta[0]=arg->win3dMat->m_SceneObjects->m_CamTheta[0];
			stats.m_CamOrDirX=arg->win3dMat->m_SceneObjects->m_CamDir.x;
			stats.m_CamOrDirY=arg->win3dMat->m_SceneObjects->m_CamDir.y;
			stats.m_CamOrDirZ=arg->win3dMat->m_SceneObjects->m_CamDir.z;
			stats.m_CamOrUpX=arg->win3dMat->m_SceneObjects->m_CamUp.x;
			stats.m_CamOrUpY=arg->win3dMat->m_SceneObjects->m_CamUp.y;
			stats.m_CamOrUpZ=arg->win3dMat->m_SceneObjects->m_CamUp.z;

			arg->m_PtGroups.m_CamGridStats=arg->m_PtGroups.GrowStats(stats );
	
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( arg->m_iGroupCount, 2, list);
			arg->m_iTempGroupCount=0;
			arg->m_iGroupCount++;
			arg->m_PtGroups.m_iPtStatsCount=arg->m_PtGroups.m_iPtMouseCount=arg->m_PtGroups.m_iPtGroupCount=arg->m_iGroupCount;
		arg->m_GroupListSelectedIndex = arg->m_iGroupCount-1;
		arg->m_PtGroups.m_iPointGroups[arg->m_GroupListSelectedIndex].intCount=vCount;
}
		
	CDialog::OnOK();
}

void CBrushCreateCtrl::OnCancel() 
{
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent();
	arg->m_iTempGroupCount=0;
	CDialog::OnCancel();
}

void CBrushCreateCtrl::OnSetFlatCheck() 
{
	CButton* but = (CButton*)GetDlgItem(IDC_SET_FLAT_CHECK);
	int checked = but->GetCheck();
	if(checked==1)
	{
		m_bSetFlatCheck = true;
	}
	if(checked==0)
	{
		m_bSetFlatCheck = false;
	}

}
