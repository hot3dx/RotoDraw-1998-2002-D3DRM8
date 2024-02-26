// PointSetCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "PointSetCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointSetCtrl dialog


CPointSetCtrl::CPointSetCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CPointSetCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointSetCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPointSetCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointSetCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointSetCtrl, CDialog)
	//{{AFX_MSG_MAP(CPointSetCtrl)
	ON_BN_CLICKED(IDC_AUTO_FACE_BUTTON, OnAutoFaceButton)
	ON_BN_CLICKED(IDC_CHOOSE_FACES_BUTTON, OnChooseFacesButton)
	ON_BN_CLICKED(IDC_SET_FACE_BUTTON, OnSetFaceButton)
	ON_BN_CLICKED(IDC_GROUPBUTTON1, OnGroupbutton1)
	ON_BN_CLICKED(IDC_GROUPBUTTON2, OnGroupbutton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointSetCtrl message handlers

void CPointSetCtrl::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CPointSetCtrl::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CPointSetCtrl::OnAutoFaceButton() 
{
	// TODO: Add your control notification handler code here
	
}

void CPointSetCtrl::OnChooseFacesButton() 
{
	// TODO: Add your control notification handler code here
	
}

void CPointSetCtrl::OnSetFaceButton() 
{
	// TODO: Add your control notification handler code here
	
}

void CPointSetCtrl::OnGroupbutton1() 
{
	// TODO: Add your control notification handler code here
	
}

void CPointSetCtrl::OnGroupbutton2() 
{
	// TODO: Add your control notification handler code here
	
}
