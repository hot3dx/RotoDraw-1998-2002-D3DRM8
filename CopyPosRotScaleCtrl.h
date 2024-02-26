#if !defined(AFX_COPYPOSROTSCALECTRL_H__9F7ED9A7_E649_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_COPYPOSROTSCALECTRL_H__9F7ED9A7_E649_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyPosRotScaleCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCopyPosRotScaleCtrl dialog

class CCopyPosRotScaleCtrl : public CDialog
{
// Construction
public:
	CCopyPosRotScaleCtrl(CWnd* pParent = NULL);   // standard constructor
	void GetOk();
// Dialog Data
	//{{AFX_DATA(CCopyPosRotScaleCtrl)
	enum { IDD = IDD_COPY_POS_ROT_SCALE_DIALOG1 };
	CStatic	m_CPRSStatic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyPosRotScaleCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCopyPosRotScaleCtrl)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPosButton();
	afx_msg void OnRotButton();
	afx_msg void OnScaleButton();
	afx_msg void OnXButton();
	afx_msg void OnYButton();
	afx_msg void OnXButton2();
	afx_msg void OnYButton2();
	afx_msg void OnCopyDragButton();
	afx_msg void OnCopyDragOffButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYPOSROTSCALECTRL_H__9F7ED9A7_E649_11D6_896C_00A0CCA2416E__INCLUDED_)
