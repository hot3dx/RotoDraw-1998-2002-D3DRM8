#if !defined(AFX_MATERIALCTRL_H__218AC924_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_MATERIALCTRL_H__218AC924_D882_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialCtrl dialog

class CMaterialCtrl : public CDialog
{
// Construction
public:
	CMaterialCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaterialCtrl)
	enum { IDD = IDD_MATERIAL_CTRL };
	CEdit	m_FrontMatEdit;
	CEdit	m_BackMatEdit;
	CListCtrl	m_MaterialList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialCtrl)
	afx_msg void OnBacFaceButton();
	afx_msg void OnFrontFaceButton();
	afx_msg void OnClearButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALCTRL_H__218AC924_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
