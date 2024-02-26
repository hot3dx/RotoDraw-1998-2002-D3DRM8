#if !defined(AFX_POINTCTRL_H__69600CC6_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_POINTCTRL_H__69600CC6_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointCtrl dialog

class CPointCtrl : public CDialog
{
// Construction
public:
	CPointCtrl(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CPointCtrl)
	enum { IDD = IDD_POINT_CRTL };
	CListCtrl	m_PtsList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointCtrl)
	afx_msg void OnClickPointsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteVertexButton();
	afx_msg void OnCustomGroupButton();
	afx_msg void OnAddToGroupButton();
	afx_msg void OnSetGroupButton();
	afx_msg void OnSetPointButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTCTRL_H__69600CC6_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
