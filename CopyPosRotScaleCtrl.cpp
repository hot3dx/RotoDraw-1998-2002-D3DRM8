// CopyPosRotScaleCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "RotoDraw3DDlg.h"
#include "CopyPosRotScaleCtrl.h"
#include "tetra.h"
#include "Geometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyPosRotScaleCtrl dialog


CCopyPosRotScaleCtrl::CCopyPosRotScaleCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyPosRotScaleCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyPosRotScaleCtrl)
	//}}AFX_DATA_INIT
}


void CCopyPosRotScaleCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyPosRotScaleCtrl)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopyPosRotScaleCtrl, CDialog)
	//{{AFX_MSG_MAP(CCopyPosRotScaleCtrl)
	ON_BN_CLICKED(IDC_X_BUTTON, OnXButton)
	ON_BN_CLICKED(IDC_Y_BUTTON, OnYButton)
	ON_BN_CLICKED(IDC_X_BUTTON2, OnXButton2)
	ON_BN_CLICKED(IDC_Y_BUTTON2, OnYButton2)
	ON_BN_CLICKED(IDC_COPY_DRAG_BUTTON, OnCopyDragButton)
	ON_BN_CLICKED(IDC_COPY_DRAG_OFF_BUTTON, OnCopyDragOffButton)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyPosRotScaleCtrl message handlers
// Set Button
void CCopyPosRotScaleCtrl::OnOK() 
{
	BeginWaitCursor();
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)AfxGetMainWnd();
	MyTexture* tex = arg->GetMyTexture();
	
	unsigned int n = arg->m_PtGroups.m_Mouse[arg->m_GroupListSelectedIndex].intCount-1;
	
	for(unsigned int i = 8;i<n+8;i++)
	{
		D3DVECTOR s,v;
		arg->win3dMat->tempMeshBld->GetVertex( i, &s );
		arg->win3dMat->m_SceneObjects->gridFrame->Transform(&v,&s);

		CTetra apoint;
		LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(v.x, v.y, v.z, tex->r, tex->g, tex->b);
			arg->win3dMat->m_SceneObjects->finalMeshFrame->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			CString p;
				tex->x[arg->m_iPointCount]=v.x;	
				tex->y[arg->m_iPointCount]=v.y;	
				tex->z[arg->m_iPointCount]=v.z;
				
				arg->win3dMat->m_SceneObjects->finalMesh->AddVertex( v.x, v.y, v.z );
				arg->win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 1.0F, 0.0F );
				arg->m_iTempGroup[arg->m_iTempGroupCount]=arg->m_iPointCount;
				arg->m_iTempMouse[arg->m_iTempGroupCount] = arg->m_PtGroups.m_Mouse[arg->m_GroupListSelectedIndex].value[i];
				p.Format(L"%d",arg->m_iPointCount);
				tetra->SetName((CStringA)p);
				arg->m_iTempGroupCount++;
				arg->m_iPointCount++;

	}
	arg->win3dMat->WinRender();
	
	if(arg->m_iPointCount>0)
	{
		if(arg->m_iTempGroupCount>0)
		{
			CString s;
			unsigned int curNum = arg->m_MeshPoints.m_iNumPoints;
			arg->m_MeshPoints.GrowByEmptyEnd(arg->m_iPointCount);
			for(unsigned int i = curNum;i<arg->m_iPointCount;i++)
			{
				arg->m_MeshPoints.Set( arg->m_MeshPoints.m_iNumPoints, tex->x[i], tex->y[i], tex->z[i] );
				/*
				s.Format("%d", i);
				arg->cfpgdlg->ptCtrl->m_PtsList.InsertItem( arg->m_MeshPoints.m_iNumPoints, s);
				s.Format("%.6f", arg->m_MeshPoints.x.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 1, s);
				s.Format("%.6f", arg->m_MeshPoints.y.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 2, s);
				s.Format("%.6f", arg->m_MeshPoints.z.value[arg->m_MeshPoints.m_iNumPoints]);
				arg->cfpgdlg->ptCtrl->m_PtsList.SetItemText( arg->m_MeshPoints.m_iNumPoints, 3, s);
				*/
				arg->m_MeshPoints.m_iNumPoints++;
			}
			/*
			s.Format("%d", arg->m_iGroupCount);
			arg->cfpgdlg->groupCtrl->m_GroupList.InsertItem( arg->m_iGroupCount, s);
			s.Format("%d", arg->m_iTempGroupCount);
			arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( arg->m_iGroupCount, 1, s);
			*/
			CString list;
			CString temp;
			CHDXINTARRAY arg1;
			arg1.allocate(0);
			arg1.value=arg1.growByEmptyEnd( arg->m_iTempGroupCount+1 ); 

			CHDXPOINTARRAY argmx;
			argmx.allocate(0);
			argmx.value=argmx.growByEmptyEnd( arg->m_iTempGroupCount+1 ); 

			

			for(unsigned int j=0;j<arg->m_iTempGroupCount;j++)
			{
				arg1.set( j, arg->m_iTempGroup[j] );
				argmx.set( j, arg->m_iTempMouse[j] );
				s.Format(L"%d, ", arg1.value[j]);
				temp.Format(L"%s%s", list, s);
				list.Format(L"%s", temp);
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
	
			//arg->cfpgdlg->groupCtrl->m_GroupList.SetItemText( arg->m_iGroupCount, 2, list);
			arg->m_iTempGroupCount=0;
			arg->m_iGroupCount++;
			arg->m_PtGroups.m_iPtStatsCount=arg->m_PtGroups.m_iPtMouseCount=arg->m_PtGroups.m_iPtGroupCount=arg->m_iGroupCount;
		}//eo if(m_iGroupCount>0)
	}//eo if(m_iPointCount>0)
	
	EndWaitCursor();
}
void CCopyPosRotScaleCtrl::GetOk()
{
	OnOK();
}
void CCopyPosRotScaleCtrl::OnCancel() 
{
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
	
	arg->win3dMat->m_SceneObjects->gridFrame->DeleteVisual(arg->win3dMat->tempMeshBld);
	//arg->win3dMat->m_SceneObjects->gridFrame->DeleteChild(arg->win3dMat->tempFrame);
	CDialog::OnCancel();
}


void CCopyPosRotScaleCtrl::OnXButton() 
{
		CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
		arg->win3dMat->tempMeshBld->Scale( 0.9F, 1.0F, 1.0F);
		arg->win3dMat->WinRender();
}

void CCopyPosRotScaleCtrl::OnYButton() 
{
		CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
		arg->win3dMat->tempMeshBld->Scale( 1.0F, 0.9F, 1.0F);
		arg->win3dMat->WinRender();
	
}



void CCopyPosRotScaleCtrl::OnXButton2() 
{
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
	arg->win3dMat->tempMeshBld->Scale( 1.1F, 1.0F, 1.0F);
	
}

void CCopyPosRotScaleCtrl::OnYButton2() 
{
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
		arg->win3dMat->tempMeshBld->Scale( 1.0F, 1.1F, 1.0F);
	
}

void CCopyPosRotScaleCtrl::OnCopyDragButton() 
{
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
	arg->m_iDrawMode = 3;
}

void CCopyPosRotScaleCtrl::OnCopyDragOffButton() 
{
	CRotoDraw3DDlg* arg = (CRotoDraw3DDlg*)GetParent();
	arg->m_iDrawMode = 1;
}


