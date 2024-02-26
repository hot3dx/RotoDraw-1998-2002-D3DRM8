#if !defined(AFX_BRUSHCREATECTRL_H__E43B7625_08F9_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_BRUSHCREATECTRL_H__E43B7625_08F9_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrushCreateCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrushCreateCtrl dialog

class CBrushCreateCtrl : public CDialog
{
// Construction
public:
	CBrushCreateCtrl(CWnd* pParent = NULL);   // standard constructor
	void CreateDimensions(D3DVECTOR *copier, int qCount);
	void makeBox(D3DVECTOR *copier, int qCount, float* b);
// Dialog Data
	//{{AFX_DATA(CBrushCreateCtrl)
	enum { IDD = IDD_BRUSH_DIALOG };
	CStatic	m_mystatic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrushCreateCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	float xbr[10000];
	float ybr[10000];
	float zbr[10000];
	int m_iBrushPtCount;
	float box[6];
	CPoint brMouse[10000];
	bool m_bSetFlatCheck;
	// Generated message map functions
	//{{AFX_MSG(CBrushCreateCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRefreshButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSetFlatCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRUSHCREATECTRL_H__E43B7625_08F9_11D7_896C_00A0CCA2416E__INCLUDED_)
