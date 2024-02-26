// MaterialDlgHelp.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "MaterialDlgHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MaterialDlgHelp dialog


MaterialDlgHelp::MaterialDlgHelp(CWnd* pParent /*=NULL*/)
	: CDialog(MaterialDlgHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(MaterialDlgHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MaterialDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MaterialDlgHelp)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MaterialDlgHelp, CDialog)
	//{{AFX_MSG_MAP(MaterialDlgHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MaterialDlgHelp message handlers

BOOL MaterialDlgHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString s;
	s.Format(L"Palette\r\n\r\n\tThe palette supports up to 300 materials in any given file.\r\n\tWith RotoDraw, you should create palette files with only one\r\n\t\tor two materials as Rotodraw only uses up to the\r\n\t\tfirst two colors.\r\n\r\nCreate\r\n\r\n\t1) Press the \"Create\" button\r\n\t2) Type in a name for the palette\r\n\t3) Press the \"Add\" button\r\n\t4) Select the Color and Material values\r\n\t5) Press the \"Set\" button\r\n\t6) Repeat \"Add\", adjust propeties, \"Set\" for each Material\r\n\t7) Press \"Save\" button to save the palette\r\n\t8) Press \"OK\" button to load the palette into RotoDraw3D\r\n\r\nLoad\r\n\r\n\t1) Press \"Open Palette\" Button\r\n\t2) Choose a palette you have already created\r\n\t3) Press \"OK\" button to load the palette into RotoDraw3D"
		);	
	m_Edit1.SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
