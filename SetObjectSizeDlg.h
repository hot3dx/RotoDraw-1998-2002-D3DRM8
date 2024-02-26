#if !defined(AFX_SETOBJECTSIZEDLG_H__5B59D1C8_55DF_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_SETOBJECTSIZEDLG_H__5B59D1C8_55DF_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetObjectSizeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetObjectSizeDlg dialog

class CSetObjectSizeDlg : public CDialog
{
// Construction
public:
	CSetObjectSizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetObjectSizeDlg)
	enum { IDD = IDD_FINAL_SIZE_DIALOG };
	CEdit	m_Edit3;
	CEdit	m_Edit2;
	CEdit	m_Edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetObjectSizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetObjectSizeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETOBJECTSIZEDLG_H__5B59D1C8_55DF_11D7_896C_00A0CCA2416E__INCLUDED_)
