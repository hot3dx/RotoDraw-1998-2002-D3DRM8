// RotoDraw3DDlg.h : header file
//

#if !defined(AFX_ROTODRAW3DDLG_H__6B551327_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_ROTODRAW3DDLG_H__6B551327_4FED_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3dpic.h"
#include "ClipTexture.h"
#include "PointSetCtrl.h"
#include "data3d.h"
/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DDlg dialog

class CRotoDraw3DDlg : public CDialog
{
// Construction
public:
	CRotoDraw3DDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL Init();
	void Dispose();
	bool is3DVisible;
	CWin3D* win3dMat;
	CPointSetCtrl *cptSetCtrl;
	//CPointsMoveButtonCtrl* cpmctrl;
	void Set3dMat();
	D3DVECTOR SelectGridFace(UINT nFlags, CPoint point);
	void DrawPointsOne( D3DVECTOR intersect, CPoint point);
	
	bool m_bFaceSelected;
	int m_iV;
	bool m_bLButtonDown;
	unsigned int m_iPointCount = 0;
	unsigned int m_iTotalPointCount;
	unsigned int m_iLastPoint;

	unsigned int m_iTempGroup[10000];
	CPoint m_iTempMouse[10000];
	
	unsigned int m_iTempGroupCount;
	unsigned int m_iGroupCount;

	float m_fScrollDist;
	int m_iScrollPointSepPos;
	float distX;
	float distY;
	float distZ;
	BOOL checkDistance(float x, float y, float z, float mouseMoveDistDelta);
	

	float Setrotx;
	float Setroty;
	float Setrotz;
	bool m_bClearAll;

	CPoints m_MeshPoints;
	CMAKERPTGROUPS m_PtGroups;

	unsigned int m_GroupListSelectedIndex;
	unsigned int m_FacesListSelectedIndex;
	unsigned int m_PtsListSelectedIndex;

	float frontRed, frontGreen, frontBlue, frontAlpha, backRed, backGreen, backBlue, backAlpha;


	int textureFillMode;
	bool m_bSetFacesButtonPushed;
	bool m_bColorSet;
	CStringA selTexFrontPath, selTexBackPath;
	int selMatFront, selMatBack;
	DWORD renderType, lightStatus, fillType;

	HDXMaterialArray m_MatArray;
	unsigned int m_MatCount;

	HDXMaterialList m_MatList;
	unsigned int m_ListCount;

	MyTexture* GetMyTexture();
	void SetCopyVertex(UINT nFlags, CPoint point);
	void Select(UINT nFlags, CPoint point);
	void CopyVertex(UINT nFlags, CPoint point);

	unsigned int m_iDrawMode;
	LPDIRECT3DRMMESHBUILDER3 selectedMesh;

	bool m_bFirstBrushDataToCopy;

	MyTexture* GetTexClass();

	void Copy();
	void CreateDimensions(D3DVECTOR *copier, int qCount);
	LPDIRECT3DRMMATERIAL2 MakeMaterial(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i);
	void makeBox(D3DVECTOR *copier, int qCount, float* b);
	void DoFaces();
	float box[6];
	LPDIRECT3DRMFACE2 lastFrontFace, lastBackFace;
	unsigned int m_SelIndexOne, m_SelIndexTwo;
	void DoTextureSetting3(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRMFACE2 frontFace, LPDIRECT3DRMFACE2 backFace, LPDIRECT3DRMMATERIAL2 mat1, LPDIRECT3DRMMATERIAL2 mat2, LPDIRECT3DRMTEXTURE3 texture, LPDIRECT3DRMTEXTURE3 texture2);
	bool faceAdded;

	bool m_bAddTopFaces;
	bool m_bAddBottomFaces;
	bool m_bLastToFirstFaces;
	bool m_bIsYAxis;

	int m_iScrollMax;
	int m_iPos;

	bool m_bDoFrontFaces;
	bool m_bDoBackFaces;

	bool m_bBuyMe;

	bool 	m_bObjectDrawn;

// Dialog Data
	//{{AFX_DATA(CRotoDraw3DDlg)
	enum { IDD = IDD_ROTODRAW3D_DIALOG };
	CButton	m_AxisCheck;
	CButton	m_InteriorFacesCheck;
	CButton	m_ExteriorFacesCheck;
	CScrollBar	m_Scroll1;
	CButton	m_BottomOrRight;
	CButton	m_TopOrLeft;
	CButton	m_FirstToLast;
	CEdit	m_RotoEdit;
	CStatic	m_Clip_Win;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotoDraw3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRotoDraw3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSaveButton();
	afx_msg void OnClearButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetColorsButton();
	afx_msg void OnSetPointsButton();
	afx_msg void OnTopOrLeftCheck();
	afx_msg void OnBottomOrRightCheck();
	afx_msg void OnFirstToLastCheck();
	afx_msg void OnChangeEdit1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnExteriorFacesCheck();
	afx_msg void OnInteriorFacesCheck();
	afx_msg void OnAxisCheck();
	afx_msg void OnRotoHelpButton();
	afx_msg void OnSizeObjectButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTODRAW3DDLG_H__6B551327_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
