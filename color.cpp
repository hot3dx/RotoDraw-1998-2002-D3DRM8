/*==========================================================================
 *
 *  Copyright (C) 1995-1999 Microsoft Corporation. All Rights Reserved.
 *
 *  File: color.cpp
 *
 ***************************************************************************/

////#include <d3drmwin.h>
#include "stdafx.h"
#include "color.h"
//#include <windows.h>
#include <string.h>
#include <commdlg.h>
#include "dxsdk8\include\d3drm.h"
#include "resource.h"

static DWORD dwNewAlpha;

VOID
setAlphaDialog(HWND hdlg, DWORD dwVal)
{
    TCHAR szVal[5];

    wsprintf(szVal, L"%d", dwVal);
    SendDlgItemMessage(hdlg, COLOR_ALPHA, EM_SETSEL,
		       (WPARAM)0, (LPARAM)-1);
    SendDlgItemMessage(hdlg, COLOR_ALPHA, EM_REPLACESEL,
		       (WPARAM)FALSE, (LPARAM)szVal);
}

#define COLOR_OK	0
#define COLOR_BADVAL	1
#define COLOR_NONEWVAL	2

DWORD
getAlphaFromDialog(HWND hdlg, LPDWORD pdwAlpha)
{
    WORD cchAlpha;
    TCHAR szAlpha[5];
    TCHAR* pszStop;
    DWORD dwAlpha;

    cchAlpha = (WORD)SendDlgItemMessage(hdlg, COLOR_ALPHA,
					EM_LINELENGTH,
					(WPARAM)0, (LPARAM)0);
    if (cchAlpha > 3)
    {
	return (COLOR_BADVAL);
    }

    if (cchAlpha == 0)
    {
	return (COLOR_NONEWVAL);
    }

    memcpy( szAlpha, &cchAlpha, sizeof(WORD) );
    SendDlgItemMessage(hdlg, COLOR_ALPHA, EM_GETLINE,
		       (WPARAM)0, (LPARAM)szAlpha);
    szAlpha[cchAlpha] = '\0';
    pszStop = &szAlpha[cchAlpha];
    dwAlpha = strtoul((char*)szAlpha, (char**)pszStop, 10);
    if (dwAlpha > 255)
    {
	return (COLOR_BADVAL);
    }

    *pdwAlpha = dwAlpha;

    return (COLOR_OK);
}


/////////////////////////////////////////////////////////////////////////////
// ColorDlg

IMPLEMENT_DYNAMIC(ColorDlg, CColorDialog)

ColorDlg::ColorDlg(COLORREF clrInit, DWORD dwFlags, CWnd* pParentWnd) :
	CColorDialog(clrInit, dwFlags, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(ColorDlg, CColorDialog)
	//{{AFX_MSG_MAP(ColorDlg)
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ColorDlg::OnMove(int x, int y) 
{
	CColorDialog::OnMove(x, y);
	
	//m_corient.Render();
	
}

void ColorDlg::OnSize(UINT nType, int cx, int cy) 
{
	CColorDialog::OnSize(nType, cx, cy);
	
	//m_corient.Render();
	
}


void ColorDlg::OnClose() 
{
	//m_corient.Render();

	CColorDialog::OnClose();
}

D3DCOLOR CallColorDialog(D3DCOLOR c)
{
	/*
	 COLORREF aclrCust[16];
    int i;

    for (i = 0; i < 16; i++)
	aclrCust[i] = RGB(255, 255, 255);
*/
	COLORREF clr =
		RGB
		(   (int) (255 * D3DRMColorGetRed(c)),
	    (int) (255 * D3DRMColorGetGreen(c)),
	    (int) (255 * D3DRMColorGetBlue(c))
		);
		ColorDlg cdlg;
		cdlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
		cdlg.m_cc.rgbResult = clr;
				
		int result = cdlg.DoModal();
		if(result){
			clr = cdlg.GetColor();
			c = D3DRMCreateColorRGB//A
	    (	D3DVAL(GetRValue(clr) / D3DVAL(255.0)),
		D3DVAL(GetGValue(clr) / D3DVAL(255.0)),
		D3DVAL(GetBValue(clr) / D3DVAL(255.0))//,
		//D3DVAL(dwNewAlpha / D3DVAL(255.0))
		);
		}
	return c;
}
