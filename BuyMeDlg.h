#if !defined(AFX_BUYMEDLG_H__8EC414E7_549E_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_BUYMEDLG_H__8EC414E7_549E_11D7_896C_00A0CCA2416E__INCLUDED_
#pragma once
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuyMeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuyMeDlg dialog

class CBuyMeDlg : public CDialog
{
// Construction
public:
	CBuyMeDlg(CWnd* pParent = NULL);   // standard constructor
	void AddEventSource();
// Dialog Data
	//{{AFX_DATA(CBuyMeDlg)
	enum { IDD = IDD_BUY_ME_DLG };
	CEdit	m_Edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuyMeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuyMeDlg)
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYMEDLG_H__8EC414E7_549E_11D7_896C_00A0CCA2416E__INCLUDED_)
