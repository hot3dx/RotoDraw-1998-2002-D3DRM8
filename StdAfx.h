// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6B551329_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
#define AFX_STDAFX_H__6B551329_4FED_11D7_896C_00A0CCA2416E__INCLUDED_
#endif

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#ifndef _AFXDLL
#define _AFXDLL
#endif

#ifndef AFX_DESIGN_TIME
#define AFX_DESIGN_TIME
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif

#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcolordialog.h>
#include <afxdialogex.h>
#include <afxdlgs.inl>
//#include <afxwinforms.h>
#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#include <afxsock.h>            // MFC socket extensions

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800
#endif

#include "dxsdk8\include\uuids.h"
#include "dxsdk8\include\rmxfguid.h"
#include "dxsdk8\include\rmxftmpl.h"
#include "dxsdk8\include\d3d8types.h"
#include "dxsdk8\include\d3d8caps.h"
#include "dxsdk8\include\d3d8.h"
#include "dxsdk8\include\d3d.h"
#include "dxsdk8\include\ddraw.h"
#include "dxsdk8\include\d3drm.h"
#include "dxsdk8\include\d3drmdef.h"

#define INITGUID

#define D3DCOLOR_MONO   1
#define D3DCOLOR_RGB    2

typedef struct _D3DMATERIAL7 {
    union {
        D3DCOLORVALUE   diffuse;        /* Diffuse color RGBA */
        D3DCOLORVALUE   dcvDiffuse;
    };
    union {
        D3DCOLORVALUE   ambient;        /* Ambient color RGB */
        D3DCOLORVALUE   dcvAmbient;
    };
    union {
        D3DCOLORVALUE   specular;       /* Specular 'shininess' */
        D3DCOLORVALUE   dcvSpecular;
    };
    union {
        D3DCOLORVALUE   emissive;       /* Emissive color RGB */
        D3DCOLORVALUE   dcvEmissive;
    };
    union {
        D3DVALUE        power;          /* Sharpness if specular highlight */
        D3DVALUE        dvPower;
    };
} D3DMATERIAL7, * LPD3DMATERIAL7;
//#include <pix.h>

#include <string>
//#include <wrl.h>
#include <shellapi.h>
#include <iosfwd>

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6B551329_4FED_11D7_896C_00A0CCA2416E__INCLUDED_)
