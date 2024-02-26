#if !defined(AFX_POINTSETCTRL_H__218AC926_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_POINTSETCTRL_H__218AC926_D882_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointSetCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointSetCtrl dialog

class CPointSetCtrl : public CDialog
{
// Construction
public:
	CPointSetCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPointSetCtrl)
	  enum { IDD = IDD_GROUP_SET_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointSetCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointSetCtrl)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAutoFaceButton();
	afx_msg void OnChooseFacesButton();
	afx_msg void OnSetFaceButton();
	afx_msg void OnGroupbutton1();
	afx_msg void OnGroupbutton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSETCTRL_H__218AC926_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
