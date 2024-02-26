#if !defined(AFX_FACESCTRL_H__69600CC8_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_FACESCTRL_H__69600CC8_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FacesCtrl.h : header file
//

#include <d3drm.h>
/////////////////////////////////////////////////////////////////////////////
// CFacesCtrl dialog

class CFacesCtrl : public CDialog
{
// Construction
public:
	CFacesCtrl(CWnd* pParent = NULL);   // standard constructor
	CString faceString;
	int prevPnts[4];
	int prevPnt;
	int pntCnt;
	LPDIRECT3DRMFACE2 face;
	bool faceSelected;
	int currentFace;
	int	faceCnt;
	int oldFaceNums[4];
	int faceNums[4];
	bool faceAdded;
	void AddFaces();
	void SetFaceData3(int *l);
	void SetFaceData(int *l);
	void SetFaceDataMany(int *l, int pntCnt2);
	void SetFaceList(int matIndex);
	void DoTextureSetting3(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRMFACE2 face, LPDIRECT3DRMFACE2 bFace, LPDIRECT3DRMMATERIAL2 mat1, LPDIRECT3DRMMATERIAL2 mat2, LPDIRECT3DRMTEXTURE3 texture, LPDIRECT3DRMTEXTURE3 texture2);
	LPDIRECT3DRMMATERIAL2 MakeMaterialFace(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i);
	
	LPDIRECT3DRMFACE2 lastFrontFace, lastBackFace;
// Dialog Data
	//{{AFX_DATA(CFacesCtrl)
	enum { IDD = IDD_FACE_CTRL };
	CListCtrl	m_FacesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFacesCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFacesCtrl)
	afx_msg void OnClickFacesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACESCTRL_H__69600CC8_CF3F_11D6_896C_00A0CCA2416E__INCLUDED_)
