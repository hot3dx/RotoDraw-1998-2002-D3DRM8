// RotoDraw3D.h : main header file for the ROTODRAW3D application
//

#if !defined(AFX_ROTODRAW3D_H__6B551325_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_ROTODRAW3D_H__6B551325_4FED_11D7_896C_00A0CCA2416E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DApp:
// See RotoDraw3D.cpp for the implementation of this class
//

class CRotoDraw3DApp : public CWinApp
{
public:
	CRotoDraw3DApp();
	CWnd* m_pMainWnd;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotoDraw3DApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRotoDraw3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTODRAW3D_H__6B551325_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
