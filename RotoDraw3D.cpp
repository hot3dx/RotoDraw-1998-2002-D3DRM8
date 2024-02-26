// RotoDraw3D.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "RotoDraw3DDlg.h"
#include "RotoSplash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DApp

BEGIN_MESSAGE_MAP(CRotoDraw3DApp, CWinApp)
	//{{AFX_MSG_MAP(CRotoDraw3DApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DApp construction

CRotoDraw3DApp::CRotoDraw3DApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRotoDraw3DApp object

CRotoDraw3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DApp initialization

BOOL CRotoDraw3DApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
/*
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
*/
	CRotoDraw3DDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		dlg.Dispose();
	}
	else if (nResponse == IDCANCEL)
	{
		dlg.Dispose();
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CRotoDraw3DApp::ExitInstance() 
{
	//if(this)
	//delete this;
	return CWinApp::ExitInstance();
}

BOOL CRotoDraw3DApp::PreTranslateMessage(MSG* pMsg) 
{
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
	return CWinApp::PreTranslateMessage(pMsg);
}
