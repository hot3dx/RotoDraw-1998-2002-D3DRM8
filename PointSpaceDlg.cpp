// PointSpaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "PointSpaceDlg.h"
#include "scroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointSpaceDlg dialog


CPointSpaceDlg::CPointSpaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPointSpaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointSpaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPointSpaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointSpaceDlg)
	DDX_Control(pDX, IDC_PT_SEP_SCROLLBAR, m_PointSepScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointSpaceDlg, CDialog)
	//{{AFX_MSG_MAP(CPointSpaceDlg)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointSpaceDlg message handlers

BOOL CPointSpaceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iScrollMax2=10000;
	CMakerC1Dlg* maker = (CMakerC1Dlg*)GetParent();
	m_fScrollDist2=maker->m_fScrollDist;
	m_iPos = maker->m_iScrollPointSepPos;
	CString s;
	s.Format("%.6f", m_fScrollDist2);
	GetDlgItem( IDC_PT_SEP_VALUE_STATIC )->SetWindowText(s);
	m_PointSepScroll.EnableScrollBar(ESB_ENABLE_BOTH);
	m_PointSepScroll.SetScrollRange(0,m_iScrollMax2,TRUE);
	
	m_PointSepScroll.SetScrollPos( m_iPos, TRUE);
	//s.Format("\npos  %d\n", m_iPos);
	//OutputDebugString(s);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPointSpaceDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_iPos = doHScroll( m_hWnd, nSBCode, nPos, pScrollBar, m_iScrollMax2);
	
	//SetScrollRange( 0, m_iScrollMax2, TRUE);
	//pScrollBar->SetScrollPos( pos, TRUE);
	
	m_fScrollDist2=m_iPos*0.002F;
	m_fScrollDist2-=0.002F;
	CString s;
	s.Format("%.6f", m_fScrollDist2);
	GetDlgItem( IDC_PT_SEP_VALUE_STATIC )->SetWindowText(s);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPointSpaceDlg::OnOK() 
{
	CMakerC1Dlg* maker = (CMakerC1Dlg*)GetParent();
	maker->m_fScrollDist=m_fScrollDist2;
	maker->m_iScrollPointSepPos=m_iPos;
	CString str;
	str.Format("Spacing: %.6f", m_fScrollDist2); 
	maker->GetDlgItem( IDC_POINTSPACING_STATIC)->SetWindowText(str);
	
				
	CDialog::OnOK();
}
