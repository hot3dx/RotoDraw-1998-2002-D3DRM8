// FacePtGrpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "FacePtGrpDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFacePtGrpDlg dialog


CFacePtGrpDlg::CFacePtGrpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFacePtGrpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFacePtGrpDlg)
	//}}AFX_DATA_INIT
}


void CFacePtGrpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFacePtGrpDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFacePtGrpDlg, CDialog)
	//{{AFX_MSG_MAP(CFacePtGrpDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_FACEPTGRP_TAB, OnSelchangeFaceptgrpTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFacePtGrpDlg message handlers

BOOL CFacePtGrpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	tabCtrl = (CTabCtrl*)GetDlgItem( IDC_FACEPTGRP_TAB );;
		
		TC_ITEM TabCtrlItem;
		TabCtrlItem.mask = TCIF_TEXT;
		TabCtrlItem.pszText = "Points";
		tabCtrl->InsertItem( 0, &TabCtrlItem );
		TabCtrlItem.pszText = "Faces";
		tabCtrl->InsertItem( 1, &TabCtrlItem );
		TabCtrlItem.pszText = "Groups";
		tabCtrl->InsertItem( 2, &TabCtrlItem );
		TabCtrlItem.pszText = "Materials";
		tabCtrl->InsertItem( 3, &TabCtrlItem );
		
		ptCtrl = new CPointCtrl();
		ptCtrl->Create(IDD_POINT_CRTL, this);

		facesCtrl = new CFacesCtrl();
		facesCtrl->Create(IDD_FACE_CTRL, this);
		facesCtrl->faceCnt=0;


		groupCtrl = new CGroupCtrl();
		groupCtrl->Create( IDD_GROUP_CTRL, this);
		groupCtrl->GetDlgItem(IDC_UNDO_BUTTON)->EnableWindow(FALSE);

		matCtrl = new CMaterialCtrl();
		matCtrl->Create( IDD_MATERIAL_CTRL, this);

		CRect m_tabCtrlRect;
		tabCtrl->GetWindowRect(&m_tabCtrlRect);
		

	int x,y,cx,cy;
	int width  = GetDeviceCaps( GetDC()->m_hDC, HORZRES );
	int height = GetDeviceCaps( GetDC()->m_hDC, VERTRES );

	if(width==640&&height == 480)
	{
		x = m_tabCtrlRect.left;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==720&&height == 480)
	{
		x = m_tabCtrlRect.left+5;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right-35;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==720&&height == 576)
	{
		x = m_tabCtrlRect.left+5;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right-35;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==800&&height == 600)
	{
		x = m_tabCtrlRect.left-30;
		y = m_tabCtrlRect.top-10;
		cx = m_tabCtrlRect.right-76;
		cy = m_tabCtrlRect.bottom-96;
	}
	
		ptCtrl->SetWindowPos( tabCtrl, x, y, cx, cy, SWP_SHOWWINDOW );
		
	
				
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFacePtGrpDlg::OnSelchangeFaceptgrpTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CRect m_tabCtrlRect;
		tabCtrl->GetWindowRect(&m_tabCtrlRect);
	int nType = tabCtrl->GetCurSel();
	ptCtrl->ShowWindow( SW_HIDE);
	facesCtrl->ShowWindow( SW_HIDE);
	groupCtrl->ShowWindow( SW_HIDE);
	matCtrl->ShowWindow( SW_HIDE);
	int x,y,cx,cy;
	int width  = GetDeviceCaps( GetDC()->m_hDC, HORZRES );
	int height = GetDeviceCaps( GetDC()->m_hDC, VERTRES );

	if(width==640&&height == 480)
	{
		x = m_tabCtrlRect.left-338;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right-417;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==720&&height == 480)
	{
		x = m_tabCtrlRect.left-338;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right-380;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==720&&height == 576)
	{
		x = m_tabCtrlRect.left-338;
		y = m_tabCtrlRect.top+10;
		cx = m_tabCtrlRect.right-380;
		cy = m_tabCtrlRect.bottom-86;
	}
	if(width==800&&height == 600)
	{
		x = m_tabCtrlRect.left-374;
		y = m_tabCtrlRect.top-10;
		cx = m_tabCtrlRect.right-417;
		cy = m_tabCtrlRect.bottom-96;
	}
	switch(nType)
	{
	case 0:
		ptCtrl->SetWindowPos( tabCtrl, x, y, cx, cy, SWP_SHOWWINDOW );
		break;
	case 1:
		{
			facesCtrl->SetWindowPos( tabCtrl, x, y, cx, cy, SWP_SHOWWINDOW );
		}
		break;
	case 2:
			groupCtrl->SetWindowPos( tabCtrl, x, y, cx, cy, SWP_SHOWWINDOW );
		break;
	case 3:
			matCtrl->SetWindowPos( tabCtrl, x, y, cx, cy, SWP_SHOWWINDOW );
		break;
	default:break;
	}
	*pResult = 0;
}
