// BuyMeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "BuyMeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuyMeDlg dialog


CBuyMeDlg::CBuyMeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuyMeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuyMeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBuyMeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuyMeDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuyMeDlg, CDialog)
	//{{AFX_MSG_MAP(CBuyMeDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuyMeDlg message handlers
void CBuyMeDlg::AddEventSource(){    
	HKEY hk;     
	DWORD dwData;     
	CHAR szBuf[26] = "ThankYouforBuyRotoDraw3D\0";//(CHAR*)malloc(16*sizeof(CHAR));  
    // Add your source name as a subkey under the Application 
    // key in the EventLog registry key.  
    if (!RegCreateKey(HKEY_CURRENT_USER, 
            L"Software\\Hot3DX2\\RotoDraw3D\\Log", &hk)) 
        
   // Add the name to the EventMessageFile subkey.  
    if (!RegSetValueEx(hk,             // subkey handle 
            L"EventFile",       // value name 
            0,                        // must be zero 
            REG_EXPAND_SZ,            // value type 
            (LPBYTE) szBuf,           // pointer to value data 
            strlen(szBuf) + 1))       // length of value data 
        
    // Set the supported event types in the TypesSupported subkey.  
    dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | 
        EVENTLOG_INFORMATION_TYPE;  
    if (!RegSetValueEx(hk,      // subkey handle 
            L"Paid",  // value name 
            0,                 // must be zero 
            REG_DWORD,         // value type 
            (LPBYTE) &dwData,  // pointer to value data 
            sizeof(DWORD)))    // length of value data 
        RegCloseKey(hk); 
} 
void CBuyMeDlg::OnChangeEdit1() 
{
	CString s,t;
	t.Format(L"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",0x34,0x38,0x34,0x32,0x33,0x34,0x35,0x64,0x72,0x35,0x74,0x36,0x79,0x38,0x39);
	m_Edit1.GetWindowText( s );
	if(strstr((CStringA)s.GetBuffer(), (CStringA)t.GetBuffer()))
	{
		AddEventSource();	
	}
}
