#if !defined(AFX_CAMERAMOVEROTATIONDIALOG_H__D8E0CB4F_D2C1_470A_B547_D5C8763AF29A__INCLUDED_)
#define AFX_CAMERAMOVEROTATIONDIALOG_H__D8E0CB4F_D2C1_470A_B547_D5C8763AF29A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraMoveRotationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraMoveRotationDialog dialog

class CCameraMoveRotationDialog : public CDialog
{
// Construction
public:
	CCameraMoveRotationDialog(CWnd* pParent = NULL);   // standard constructor

	bool is3DCamVisible;
	HRESULT Pick();
// Dialog Data
	//{{AFX_DATA(CCameraMoveRotationDialog)
	enum { IDD = IDD_CAMERA_MOVEMENT_VARS_CTRL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraMoveRotationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCameraMoveRotationDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnCamMoveRotHelpButton();
	afx_msg void OnCameraMoveWindowStatic();
	afx_msg void OnSetCamSphereButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERAMOVEROTATIONDIALOG_H__D8E0CB4F_D2C1_470A_B547_D5C8763AF29A__INCLUDED_)
