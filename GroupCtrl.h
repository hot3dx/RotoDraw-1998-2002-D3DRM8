#if !defined(AFX_GROUPCTRL_H__69600CC7_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_GROUPCTRL_H__69600CC7_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupCtrl.h : header file
//
#include "ClipTexture.h"
#include "data3d.h"
#include <d3drm.h>

/////////////////////////////////////////////////////////////////////////////
// CGroupCtrl dialog

class CGroupCtrl : public CDialog
{
// Construction
public:
	CGroupCtrl(CWnd* pParent = NULL);   // standard constructor
	int m_SelIndexOne, m_SelIndexTwo;
	void makeBox(D3DVECTOR *copier, int qCount, float* v);
	void CreateDimensions(D3DVECTOR *copier, int qCount);
	LPDIRECT3DRMMATERIAL2 MakeMaterial(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i);
	HDXUndoFacesArray undo;
	CHDXINTARRAY m_UndoList;
	float box[6];
	bool m_bLastPointInGroupToFirst;
// Dialog Data
	//{{AFX_DATA(CGroupCtrl)
	enum { IDD = IDD_GROUP_CTRL };
	CButton	m_LastToFirstCheck;
	CScrollBar	m_FacesScroll1;
	CEdit	m_GroupTwoEdit;
	CEdit	m_GRoupOneEdit;
	CListCtrl	m_GroupList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupCtrl)
	afx_msg void OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCopyButton();
	afx_msg void OnGroupButton1();
	afx_msg void OnGroupButton2();
	afx_msg void OnChooseFacesButton();
	afx_msg void OnAutoFaceButton();
	afx_msg void OnSetFaceButton();
	afx_msg void OnUndoButton();
	afx_msg void OnDeleteGroupButton();
	afx_msg void OnLastToFirstCheck();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPCTRL_H__69600CC7_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
