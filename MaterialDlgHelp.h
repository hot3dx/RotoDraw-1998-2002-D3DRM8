#if !defined(AFX_MATERIALDLGHELP_H__46BC7021_559D_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_MATERIALDLGHELP_H__46BC7021_559D_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialDlgHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MaterialDlgHelp dialog

class MaterialDlgHelp : public CDialog
{
// Construction
public:
	MaterialDlgHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MaterialDlgHelp)
	enum { IDD = IDD_MATERIAL_HELP_DIALOG };
	CEdit	m_Edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MaterialDlgHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MaterialDlgHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALDLGHELP_H__46BC7021_559D_11D7_896C_00A0CCA2416E__INCLUDED_)
