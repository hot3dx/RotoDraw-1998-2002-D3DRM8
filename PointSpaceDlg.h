#if !defined(AFX_POINTSPACEDLG_H__218AC925_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_POINTSPACEDLG_H__218AC925_D882_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointSpaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointSpaceDlg dialog

class CPointSpaceDlg : public CDialog
{
// Construction
public:
	CPointSpaceDlg(CWnd* pParent = NULL);   // standard constructor
	int m_iScrollMax2;
	float m_fScrollDist2;
	int m_iPos;
// Dialog Data
	//{{AFX_DATA(CPointSpaceDlg)
	enum { IDD = IDD_POINTSPACE_DIALOG };
	CScrollBar	m_PointSepScroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointSpaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointSpaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSPACEDLG_H__218AC925_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
