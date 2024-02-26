#if !defined(AFX_POINTSMOVEBUTTONCTRL_H__F1DE22E1_0828_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_POINTSMOVEBUTTONCTRL_H__F1DE22E1_0828_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointsMoveButtonCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointsMoveButtonCtrl dialog

class CPointsMoveButtonCtrl : public CDialog
{
// Construction
public:
	CPointsMoveButtonCtrl(CWnd* pParent = NULL);   // standard constructor
	void MoveAPoint(float x, float y, float z);
	float m_fCPMBCRateOfChange;
// Dialog Data
	//{{AFX_DATA(CPointsMoveButtonCtrl)
	enum { IDD = IDD_POINTMOVE_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointsMoveButtonCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointsMoveButtonCtrl)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnXButtonminus();
	afx_msg void OnXButtonplus();
	afx_msg void OnYButtonminus();
	afx_msg void OnYButtonplus();
	afx_msg void OnZButtonminus();
	afx_msg void OnZButtonplus();
	afx_msg void OnEnablemoveboxCheck();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSMOVEBUTTONCTRL_H__F1DE22E1_0828_11D7_896C_00A0CCA2416E__INCLUDED_)
