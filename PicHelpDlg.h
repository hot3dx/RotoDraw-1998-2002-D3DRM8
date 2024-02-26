#if !defined(AFX_PICHELPDLG_H__5B59D1C4_55DF_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_PICHELPDLG_H__5B59D1C4_55DF_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicHelpDlg dialog

class CPicHelpDlg : public CDialog
{
// Construction
public:
	CPicHelpDlg(CWnd* pParent = NULL);   // standard constructor
	void SetPic();

// Dialog Data
	//{{AFX_DATA(CPicHelpDlg)
	enum { IDD = IDD_PIC_HELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPicHelpDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICHELPDLG_H__5B59D1C4_55DF_11D7_896C_00A0CCA2416E__INCLUDED_)
