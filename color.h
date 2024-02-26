#if !defined(AFX_COLOR_H__C92B1481_13F4_11D6_896C_00A0CCA2416E__INCLUDED_)
#define AFX_COLOR_H__C92B1481_13F4_11D6_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
//#include <d3drmwin.h>
#include "resource.h"

D3DCOLOR CallColorDialog(D3DCOLOR c);
/////////////////////////////////////////////////////////////////////////////
// ColorDlg dialog

class ColorDlg : public CColorDialog
{
	DECLARE_DYNAMIC(ColorDlg)

public:
	ColorDlg(COLORREF clrInit = 0, DWORD dwFlags = 0,
			CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(ColorDlg)
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // AFX_COLOR_H__C92B1481-13F4-11D6-896C-00A0CCA2416E__INCLUDED_
