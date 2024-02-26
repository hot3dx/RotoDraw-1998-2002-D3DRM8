#if !defined(AFX_MATERIALDLG_H__218AC92A_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_MATERIALDLG_H__218AC92A_D882_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialDlg.h : header file
//
#include "3dpic.h"
#include "data3d.h"
/////////////////////////////////////////////////////////////////////////////
// CMaterialDlg dialog

class CMaterialDlg : public CDialog
{
// Construction
public:
	CMaterialDlg(CWnd* pParent = NULL);   // standard constructor
		int m_MatListIndex;
	float sv1,sv2,sv3,sv4,sv5,sv6,sv7;
	 
	CStatic* rainbows;
	CStatic* lumeRainbow;
	CStatic* colorCurrent;
	CStatic* winD3DMaterialWin;
	CScrollBar* vScroll1;
	CScrollBar* vScroll2;
	CScrollBar* vScroll8;
	CScrollBar* vScroll9;
	CScrollBar* vScroll10;
	CScrollBar* hSlider;
	
	CListBox* colorValList;
	COLORREF selectedColor;
	void SetColorMapPixels(int sizeBytes);
	void SetColorLumScroll(int sizeBytes);
	void SetColorCurrent(int sizeBytes);
	void SetD3DMaterialWin();
	int GetBrightness(COLORREF c);
	int GetSaturation(COLORREF c);
	int GetHue(COLORREF c);
	void Set3dbutton();

	bool m_bInit;

	HDXMaterialArray m_TMats;
	HDXMaterial m_Mat;
	int m_MatIndex;

	CString m_CurrentPalletFileName;

	CWin3D* win3d;
// Dialog Data
	//{{AFX_DATA(CMaterialDlg)
	enum { IDD = VIEWERCHOOSECOLOR };
	CEdit	m_CurrentMatEdit;
	CEdit	m_NumMaterialsEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSelchangeMaterialListdlg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillfocusMaterialListdlg();
	afx_msg void OnLumscroll();
	afx_msg void OnChangeHue();
	afx_msg void OnTextureFilenameButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMappixels();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	afx_msg void OnCreateButton();
	afx_msg void OnSetColorButton();
	afx_msg void OnAddPaletteButton();
	afx_msg void OnAddMaterialButton();
	afx_msg void OnSetMaterialButton();
	afx_msg void OnDeleteMaterial();
	afx_msg void OnDeleteMaterialButton();
	afx_msg void OnNameSetButton();
	afx_msg void OnClearTextureFilenameButton();
	afx_msg void OnSavePaletteButton2();
	afx_msg void OnOpenPaletteButton();
	afx_msg void OnMatHelpButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALDLG_H__218AC92A_D882_11D6_896C_00A0CCA2416E__INCLUDED_)
