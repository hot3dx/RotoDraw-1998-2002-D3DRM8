// PicHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "PicHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicHelpDlg dialog


CPicHelpDlg::CPicHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPicHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPicHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CPicHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicHelpDlg message handlers

void CPicHelpDlg::OnOK() 
{
		
	CDialog::OnOK();
}

BOOL CPicHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPicHelpDlg::SetPic()
{

	SetWindowText(L"KeyBoard Controls Help");
	CStatic* bmpWin =  ( CStatic*)this->GetDlgItem(IDC_PIC_STATIC);//COLOR_RAINBOW);
	bmpWin->ModifyStyle(SS_SIMPLE, SS_SUNKEN|SS_BITMAP);
	CRect* rect = new CRect();
	bmpWin->GetWindowRect( rect );
	int w, h;
	w = rect->Width();//189
	h = rect->Height();//177
	    HANDLE han = LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, w, h
			, LR_DEFAULTCOLOR);
		bmpWin->SetBitmap( HBITMAP(han) );
		
}

