#if !defined(AFX_FACEPTGRPDLG_H__69600CC1_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_FACEPTGRPDLG_H__69600CC1_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FacePtGrpDlg.h : header file
//

#include "PointCtrl.h"
#include "FacesCtrl.h"
#include "GroupCtrl.h"
#include "MaterialCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CFacePtGrpDlg dialog

class CFacePtGrpDlg : public CDialog
{
// Construction
public:
	CFacePtGrpDlg(CWnd* pParent = NULL);   // standard constructor
	CTabCtrl* tabCtrl;
	CPointCtrl* ptCtrl;
	CFacesCtrl* facesCtrl;
	CGroupCtrl* groupCtrl;
	CMaterialCtrl* matCtrl;
// Dialog Data
	//{{AFX_DATA(CFacePtGrpDlg)
	enum { IDD = IDD_FACEPTGRP_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFacePtGrpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFacePtGrpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFaceptgrpTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEPTGRPDLG_H__69600CC1_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
