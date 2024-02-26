// PointsMoveButtonCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "PointsMoveButtonCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointsMoveButtonCtrl dialog


CPointsMoveButtonCtrl::CPointsMoveButtonCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CPointsMoveButtonCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointsMoveButtonCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPointsMoveButtonCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointsMoveButtonCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointsMoveButtonCtrl, CDialog)
	//{{AFX_MSG_MAP(CPointsMoveButtonCtrl)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_X_BUTTONMINUS, OnXButtonminus)
	ON_BN_CLICKED(IDC_X_BUTTONPLUS, OnXButtonplus)
	ON_BN_CLICKED(IDC_Y_BUTTONMINUS, OnYButtonminus)
	ON_BN_CLICKED(IDC_Y_BUTTONPLUS, OnYButtonplus)
	ON_BN_CLICKED(IDC_Z_BUTTONMINUS, OnZButtonminus)
	ON_BN_CLICKED(IDC_Z_BUTTONPLUS, OnZButtonplus)
	ON_BN_CLICKED(IDC_ENABLEMOVEBOX_CHECK, OnEnablemoveboxCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointsMoveButtonCtrl message handlers
int doCPMBCHScroll (HWND hw, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar, int max)
{
	ASSERT(pScrollBar != NULL);
	int nCurPos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LEFT: //    Scroll to far left.
		nCurPos--;
		break;
	case SB_LINELEFT: //    Scroll left.
		nCurPos--;
		break;
	case SB_LINERIGHT: //    Scroll right.
		nCurPos++;
		break;
	case SB_PAGELEFT: //    Scroll one page left.
		nCurPos--;
		break;
	case SB_PAGERIGHT: //    Scroll one page right.
		nCurPos++;
		break;
	case SB_RIGHT: //    Scroll to far right.
		nCurPos++;
		break;
	case SB_THUMBPOSITION:
		nCurPos = nPos;
		break;
	case SB_THUMBTRACK:
		nCurPos = nPos;
		break;
	}
	
	if (nCurPos < 1)
		nCurPos = 1;
	if (nCurPos > max)
		nCurPos = max;
		
	pScrollBar->SetScrollPos( nCurPos, TRUE);
	pScrollBar->UpdateWindow();
	return nCurPos;
	
}

void CPointsMoveButtonCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int pos = doCPMBCHScroll( NULL, nSBCode, nPos, pScrollBar, 10000);
	m_fCPMBCRateOfChange = pos*0.00001F;
	CString s;
	s.Format("Dist: %.6f", m_fCPMBCRateOfChange);
	GetDlgItem( IDC_POINTMOVECHANGEVALUE_STATIC )->SetWindowText(s);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPointsMoveButtonCtrl::MoveAPoint(float x, float y, float z)
{
	CMakerC1Dlg* arg = (CMakerC1Dlg*)GetParent( );
	D3DVECTOR v1,v2,v3,v4;
	arg->selectedMesh->GetVertex( 0, &v1);
	arg->selectedMesh->GetVertex( 1, &v2);
	arg->selectedMesh->GetVertex( 2, &v3);
	arg->selectedMesh->GetVertex( 3, &v4);
	arg->selectedMesh->SetVertex( 0, v1.x+x, v1.y+y, v1.z+z);
	arg->selectedMesh->SetVertex( 1, v2.x+x, v2.y+y, v2.z+z);
	arg->selectedMesh->SetVertex( 2, v3.x+x, v3.y+y, v3.z+z);
	arg->selectedMesh->SetVertex( 3, v4.x+x, v4.y+y, v4.z+z);
	DWORD nCnt;
	char *name;
	arg->selectedMesh->GetName( &nCnt, NULL);
	name = (char*)malloc(nCnt*sizeof(char));
	arg->selectedMesh->GetName( &nCnt, name);
	int id = atoi( name );

	arg->win3dMat->m_SceneObjects->finalMesh->SetVertex( id, x, y, z);
}

void CPointsMoveButtonCtrl::OnXButtonminus() 
{
	MoveAPoint(-m_fCPMBCRateOfChange, 0.0F, 0.0F);
	
}

void CPointsMoveButtonCtrl::OnXButtonplus() 
{
	MoveAPoint(m_fCPMBCRateOfChange, 0.0F, 0.0F);
}

void CPointsMoveButtonCtrl::OnYButtonminus() 
{
	MoveAPoint(0.0F, -m_fCPMBCRateOfChange, 0.0F);	
}

void CPointsMoveButtonCtrl::OnYButtonplus() 
{
	MoveAPoint(0.0F, m_fCPMBCRateOfChange, 0.0F);	
}

void CPointsMoveButtonCtrl::OnZButtonminus() 
{
	MoveAPoint(0.0F, 0.0F, -m_fCPMBCRateOfChange);
}

void CPointsMoveButtonCtrl::OnZButtonplus() 
{
	MoveAPoint(0.0F, 0.0F, m_fCPMBCRateOfChange);
}

void CPointsMoveButtonCtrl::OnEnablemoveboxCheck() 
{
	
}

void CPointsMoveButtonCtrl::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CPointsMoveButtonCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CScrollBar* scroll = (CScrollBar*)GetDlgItem( IDC_MOVEPOINTVALUE_SCROLLBAR );
	
	scroll->SetScrollRange( 0, 10000, TRUE);
	scroll->SetScrollPos( 5000, TRUE);
	scroll->EnableScrollBar(ESB_ENABLE_BOTH);
	m_fCPMBCRateOfChange=5000*0.00001F;
	CString s;
	s.Format("Dist: %.6f", m_fCPMBCRateOfChange);
	GetDlgItem( IDC_POINTMOVECHANGEVALUE_STATIC )->SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
