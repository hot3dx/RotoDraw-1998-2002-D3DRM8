// SetObjectSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "RotoDraw3DDlg.h"
#include "SetObjectSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetObjectSizeDlg dialog


CSetObjectSizeDlg::CSetObjectSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetObjectSizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetObjectSizeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetObjectSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetObjectSizeDlg)
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetObjectSizeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetObjectSizeDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetObjectSizeDlg message handlers
float chx,chy,chz;
BOOL CSetObjectSizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRotoDraw3DDlg* rdlg = (CRotoDraw3DDlg*)GetParent();

	D3DRMBOX box;
		rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
		chx = box.max.x-box.min.x;
		chy = box.max.y-box.min.y;
		chz = box.max.z-box.min.z;
		CString s;
		s.Format(L"%.6f", chx);
		m_Edit1.SetWindowText(s);
		s.Format(L"%.6f", chy );
		m_Edit2.SetWindowText(s);
		s.Format(L"%.6f", chz );
		m_Edit3.SetWindowText(s);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetObjectSizeDlg::OnChangeEdit1() 
{
	CString s;
	m_Edit1.GetWindowText(s);
	chx = (float)atof((CStringA)s.GetBuffer());
	
}

void CSetObjectSizeDlg::OnChangeEdit2() 
{
	CString s;
	m_Edit2.GetWindowText(s);
	chy = (float)atof((CStringA)s.GetBuffer());
	
}

void CSetObjectSizeDlg::OnChangeEdit3() 
{
	CString s;
	m_Edit3.GetWindowText(s);
	chz = (float)atof((CStringA)s.GetBuffer());
}

void CSetObjectSizeDlg::OnOK() 
{
	BeginWaitCursor();
	CRotoDraw3DDlg* rdlg = (CRotoDraw3DDlg*)GetParent();

	D3DRMBOX box;
		rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
		float a = box.max.x-box.min.x;
		float b = box.max.y-box.min.y;
		float c = box.max.z-box.min.z;
		float d,e,f;
		bool ab,bb,cb;
		if(a>chx)
		{
			d=0.99F;
			ab = true;
		}
		if(a<chx)
		{
			d=1.01F;
			ab=false;
		}
		if(b>chy)
		{
			e=0.99F;
			bb=true;
		}
		if(b<chy)
		{
			e=1.01F;
			bb=false;
		}
		if(c>chz)
		{
			f=0.99F;
			cb=true;
		}
		if(c<chz)
		{
			f=1.01F;
			cb=false;
		}

		if(ab==true)
		while(a>chx)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( d, 1.0F, 1.0F);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
				a = box.max.x-box.min.x;
		}
		if(ab==false)
		while(a<chx)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( d, 1.0F, 1.0F);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
				a = box.max.x-box.min.x;
		}
		if(bb==true)
		while(b>chy)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( 1.0F, e, 1.0F);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
			b = box.max.y-box.min.y;
		}
		if(bb==false)
		while(b<chy)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( 1.0F, e, 1.0F);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
			b = box.max.y-box.min.y;
		}
		if(cb==true)
		while(c>chz)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( 1.0F, 1.0F, f);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
			c = box.max.z-box.min.z;
		}
		if(cb==false)
		while(c<chz)
		{
			rdlg->win3dMat->m_SceneObjects->finalMesh->Scale( 1.0F, 1.0F, f);
			rdlg->win3dMat->WinRender();
			rdlg->win3dMat->m_SceneObjects->finalMesh->GetBox(&box);
			c = box.max.z-box.min.z;

		}

		EndWaitCursor();

}

void CSetObjectSizeDlg::OnCancel() 
{
		
	CDialog::OnCancel();
}
