// RotoDraw3DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "RotoDraw3DDlg.h"
#include <math.h>
#include "geometry.h"
#include "tetra.h"
#include "ClipTexture.h"
#include "PointSpaceDlg.h"
#include "color.h"
#include "MaterialDlg.h"
#include "readdirectx.h"
#include "D3DFile.h"
#include "hobwrite.h"
#include "grid.h"
#include "hobread.h"
#include "RotoSplash.h"
#include "CopyPosRotScaleCtrl.h"
#include "Scroll.h"
#include "BuyMeDlg.h"
#include "PicHelpDlg.h"
#include "SetObjectSizeDlg.h"
#include "process.h"

#include "CameraMoveRotationVars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MyTexture* tex;
CWin3D* pWin3d;
CMaterialDlg* m_matdlg;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
bool m_bMaterialDlgColorsSet = false;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DDlg dialog

CRotoDraw3DDlg::CRotoDraw3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotoDraw3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotoDraw3DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRotoDraw3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotoDraw3DDlg)
	DDX_Control(pDX, IDC_AXIS_CHECK, m_AxisCheck);
	DDX_Control(pDX, IDC_INTERIOR_FACES_CHECK, m_InteriorFacesCheck);
	DDX_Control(pDX, IDC_EXTERIOR_FACES_CHECK, m_ExteriorFacesCheck);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_Scroll1);
	DDX_Control(pDX, IDC_BOTTOM_OR_RIGHT_CHECK, m_BottomOrRight);
	DDX_Control(pDX, IDC_TOP_OR_LEFT_CHECK, m_TopOrLeft);
	DDX_Control(pDX, IDC_FIRST_TO_LAST_CHECK, m_FirstToLast);
	DDX_Control(pDX, IDC_EDIT1, m_RotoEdit);
	DDX_Control(pDX, IDC_CLIP_STATIC, m_Clip_Win);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRotoDraw3DDlg, CDialog)
	//{{AFX_MSG_MAP(CRotoDraw3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	ON_WM_CAPTURECHANGED()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_SET_COLORS_BUTTON, OnSetColorsButton)
	ON_BN_CLICKED(IDC_SET_POINTS_BUTTON, OnSetPointsButton)
	ON_BN_CLICKED(IDC_TOP_OR_LEFT_CHECK, OnTopOrLeftCheck)
	ON_BN_CLICKED(IDC_BOTTOM_OR_RIGHT_CHECK, OnBottomOrRightCheck)
	ON_BN_CLICKED(IDC_FIRST_TO_LAST_CHECK, OnFirstToLastCheck)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_EXTERIOR_FACES_CHECK, OnExteriorFacesCheck)
	ON_BN_CLICKED(IDC_INTERIOR_FACES_CHECK, OnInteriorFacesCheck)
	ON_BN_CLICKED(IDC_AXIS_CHECK, OnAxisCheck)
	ON_BN_CLICKED(IDC_ROTO_HELP_BUTTON, OnRotoHelpButton)
	ON_BN_CLICKED(IDC_SIZE_OBJECT_BUTTON, OnSizeObjectButton)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &CRotoDraw3DDlg::OnNMThemeChangedScrollbar1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotoDraw3DDlg message handlers
BOOL CRotoDraw3DDlg::Init()
{
	m_bBuyMe=false;
	HKEY phkResult;
	if(ERROR_SUCCESS==RegOpenKeyEx( HKEY_CURRENT_USER,
		L"Software\\Hot3DX2\\RotoDraw3D\\Log",
	0,  KEY_READ, &phkResult))
	m_bBuyMe=true;
	RegCloseKey( phkResult);

	if(m_bBuyMe==false)
		if(IDNO==MessageBox( L"You Agree to Use this software at your own risk without warranty or recourse of any kind.\n\nYou agree not to redistribute, or reverse engineer this software\n\nYou agree not to use any images made with this software until you have paid the license fee\n\nYou agree that using this software constitutes full acceptance of this license agreement",L"RotoDraw3D License Agreement",MB_YESNO))exit(0);

	// Simply see if D3D8.dll exists.
    HINSTANCE hD3D8DLL = LoadLibrary( L"D3D8.DLL" );
    if( hD3D8DLL == NULL )
    {
		MessageBox( L"Can't Find DirectX 8.0 or Higher\n\nThis program requires DirectX 8.0 or Higher\n\nGot to http://www.microsoft.com and download and install the newest version\n\nThis application will now terminate", L"Can't Find Proper DirectX",MB_OK);
		exit(0);
	}
		FreeLibrary( hD3D8DLL );

   	if(m_bClearAll ==true)
	{
				
		if(m_MeshPoints.m_iNumPoints>0)
		{
			m_MeshPoints.x.deallocate();
			m_MeshPoints.y.deallocate();
			m_MeshPoints.z.deallocate();
			m_MeshPoints.x.allocate(0);
			m_MeshPoints.y.allocate(0);
			m_MeshPoints.z.allocate(0);
			m_MeshPoints.m_iNumPoints=0;
		}
		
		if(m_PtGroups.m_iPointGroups>0)
		{
			if(m_PtGroups.m_iPtGroupCount>0)
			free(m_PtGroups.m_iPointGroups);
			m_PtGroups.m_iPtGroupCount=0;
			m_PtGroups.m_iPtMouseCount=0;
			m_PtGroups.m_iPtStatsCount=0;
		}

		if(m_MatCount>0)
		{
			m_MatArray.DeAllocate();
			m_MatCount = 0;
			m_MatArray.Allocate(0);
		}
		
		if(m_ListCount>0)
		{
			m_MatList.m_MatList.deallocate();
			m_ListCount = 0;
			m_MatList.m_MatList.allocate(0);
		}
		m_bClearAll=false;
	}
	is3DVisible = false;
	m_bFaceSelected = false;
	m_bLButtonDown = false;
	m_iPointCount=0;
	m_iTotalPointCount=0;
	m_iTempGroupCount = 0;
	m_iGroupCount = 0;
	m_iTotalPointCount=0;
	m_iLastPoint=0;
	int devSz = GetDeviceCaps( GetDC()->m_hDC, BITSPIXEL);
	if(devSz<24)
	{
		MessageBox( L"This program operates at either 24 bit or 32 bit per pixel. Please set your Display Setting to 24 or 32 bit.  The program will now exit.",L"Display Setting Incorrect",MB_OK);
		exit(0);
	}
		tex = new MyTexture(&m_Clip_Win, devSz);

	//GetDlgItem( IDC_POINTSPACING_STATIC)->SetWindowText(L"Spacing: 0.300000");
	

	distX = 0.0F;
	distY = 0.0F;
	distZ = 0.0F;
	
	m_iDrawMode=2;

	selMatFront = selMatBack = -1;

	GetDlgItem(IDC_EDIT1)->SetWindowText( L"20.00000");
	GetDlgItem(IDC_POINT_SPACE_STATIC)->SetWindowText( L"Space 0.30000");	
	m_bDoFrontFaces = true;
		m_InteriorFacesCheck.SetCheck( 1);
	m_bDoBackFaces = true;
		m_ExteriorFacesCheck.SetCheck( 1);
	m_bAddTopFaces = false;
		m_TopOrLeft.SetCheck(0);
	m_bAddBottomFaces = false;
		m_BottomOrRight.SetCheck(0);
	m_bIsYAxis = true;
		m_AxisCheck.SetCheck(1);
	m_bLastToFirstFaces=false;
		m_FirstToLast.SetCheck(0);
		m_iScrollMax=10000;
	m_iPos = m_iScrollPointSepPos;
	m_fScrollDist = 0.3F;
	m_iScrollPointSepPos = 150;
	m_Scroll1.EnableScrollBar(ESB_ENABLE_BOTH);
	m_Scroll1.SetScrollRange(0,m_iScrollMax,TRUE);
	m_Scroll1.SetScrollPos( m_iPos, TRUE);
		
	m_bObjectDrawn = false;
	return TRUE;
}

BOOL CRotoDraw3DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CSplashWnd::EnableSplashScreen(TRUE);
	CSplashWnd::ShowSplashScreen(this);
	Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRotoDraw3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CRotoDraw3DDlg::Set3dMat()
{
	win3dMat = new CWin3D();
	win3dMat->m_bMain_3d_Window = true;
	win3dMat->m_fCameraOffset= 81.0F;
	CString s;
	win3dMat->m_fCameraSpeed = 1.1F;
			win3dMat->m_fCameraRotationValue = 0.017453293005625408F*20.0F;//*5.0F;
			win3dMat->m_fPointSpace = 0.3F;
	SetCWin3D( *win3dMat );
		win3dMat->win3dSetFlag = false;
		
		win3dMat->m_cameraMODE=CAMFRONT;
	
	if(win3dMat->win3dSetFlag==false)
	{
		win3dMat->win3dSetFlag=true;
			
	win3dMat->Win3DInit( this->m_hWnd);
	win3dMat->m_cameraMODE=CAMFRONT;
	
	pWin3d = win3dMat;
	}
	
	
}

void CRotoDraw3DDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if(is3DVisible==false)
		{
			is3DVisible=true;
			Set3dMat();
		}

		CDialog::OnPaint();
	}
}


HCURSOR CRotoDraw3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRotoDraw3DDlg::OnSaveButton() 
{

	if(m_bBuyMe==false)
	{
		//CBuyMeDlg bmdlg;
		//bmdlg.DoModal();
	}
	if(	m_bObjectDrawn==true)
	{
	BOOL bOpenFileDialog = false;
	LPCTSTR fileType = L".hob";
	LPCTSTR filter =  L"Text Hot3DX Object Files (*.hob)|*.hob|Binary Hot3DX Object Files (*.hob)|*.hob|TEXT DirectX Files (*.x)|*.x|Binary DirectX Files (*.x)|*.x||";
	CFileDialog ofn(FALSE, fileType, NULL, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter);
			ofn.m_ofn.lpstrInitialDir=L"c:\\dx7sdk\\samples\\multimedia\\d3drm\\media";
			if(IDOK ==ofn.DoModal())
			{
				CStringA s = (CStringA)ofn.GetFileName();// gets just file with ext
				CStringA p = (CStringA)ofn.GetPathName();// gets path and file
				
				//LPCSTR st = static_cast<LPCSTR>(file);
				HDXHOBWriter wr;
							
				switch(ofn.m_ofn.nFilterIndex){
				case 1://DXFILEFORMAT_TEXT 1
					{
					wr.WriteHob(1, s.GetBuffer(s.GetLength()),
							win3dMat->m_SceneObjects->finalMesh, 
							m_MatArray, m_MatList, m_MeshPoints, 
							m_PtGroups);
						
					}break;
				case 2://DXFILEFORMAT_BINARY 0
					{
						HDXHOBWriter wr;
						wr.WriteHob(0, s.GetBuffer(s.GetLength()),
							win3dMat->m_SceneObjects->finalMesh, 
							m_MatArray, m_MatList, m_MeshPoints, 
							m_PtGroups);
					}break;
				case 3:
					{
						win3dMat->m_SceneObjects->finalMesh->SetName("FinalMesh");
						win3dMat->m_SceneObjects->finalMesh->Save(s.GetBuffer(s.GetLength()), D3DRMXOF_TEXT,  D3DRMXOFSAVE_ALL);
					}break;
				case 4:
					{
						win3dMat->m_SceneObjects->finalMesh->SetName("FinalMesh");
						win3dMat->m_SceneObjects->finalMesh->Save(s.GetBuffer(s.GetLength()), D3DRMXOF_BINARY, D3DRMXOFSAVE_ALL);
					}break;
				}//eoswitch
			}// eo if(IDOK ==ofn.DoModal())
	}// eo if(	m_bObjectDrawn==true)
	
}

void CRotoDraw3DDlg::OnClearButton() 
{
	WinExec( GetCommandLineA(), SW_SHOW );
	OnOK();
	
}

void CRotoDraw3DDlg::OnOK() 
{
	Dispose();
	CDialog::OnOK();
}
#include "CameraMoveRotationDialog.h"
void CRotoDraw3DDlg::OnCancel() 
{
	//CCameraMoveRotationDialog cmrd;
	//cmrd.DoModal();
	//win3dMat->WinRender();
	Dispose();
	CDialog::OnCancel();
}

void CRotoDraw3DDlg::OnCaptureChanged(CWnd *pWnd) 
{
	CDialog::OnCaptureChanged(pWnd);
}

void CRotoDraw3DDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	if(point.x>3&&point.x<345&&point.y>3&&point.y<345)
	{
		
		SetCursor( AfxGetApp()->LoadCursor(IDC_CROSSHAIR1));
		m_bLButtonDown=true;
		D3DVECTOR isect = SelectGridFace(nFlags, point);
		if(m_iDrawMode==2)
		{
			DrawPointsOne( isect, point );
		}
	else
	{
		Select(nFlags, point);

	}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CRotoDraw3DDlg::Select(UINT nFlags, CPoint point)
{
	LPDIRECT3DRMFRAME3 pCamera, pScene;
	LPDIRECT3DRMPICKED2ARRAY picked;
    D3DRMRAY rmRay;
    D3DRMVECTOR4D v4Src;

    win3dMat->m_SceneObjects->m_view->GetCamera(&pCamera);
    pCamera->GetPosition(NULL, &rmRay.dvPos);
    pCamera->GetScene(&pScene);
    pCamera->Release();

    v4Src.x = (float)(point.x);
    v4Src.y = (float)(point.y);
    v4Src.z = 0.0f;
    v4Src.w = 1.0f;

    win3dMat->m_SceneObjects->m_view->InverseTransform(&rmRay.dvDir, &v4Src);
	
    rmRay.dvDir.x -= rmRay.dvPos.x;
    rmRay.dvDir.y -= rmRay.dvPos.y;
    rmRay.dvDir.z -= rmRay.dvPos.z;

    pScene->RayPick(NULL, &rmRay, D3DRMRAYPICK_IGNOREFURTHERPRIMITIVES|
D3DRMRAYPICK_INTERPOLATEUV|D3DRMRAYPICK_INTERPOLATECOLOR|D3DRMRAYPICK_INTERPOLATENORMAL , &picked);
    pScene->Release();

	if(picked){
		if(picked->GetSize()){
			LPDIRECT3DRMFRAMEARRAY frames;
			LPDIRECT3DRMFRAME frame;
			LPDIRECT3DRMFRAME3 pFrame3;
			LPDIRECT3DRMVISUAL visual;
			LPDIRECT3DRMMESHBUILDER3 mesh;
			D3DRMPICKDESC2 pickDesc;

	    picked->GetPick(0, &visual, &frames, &pickDesc);
	    frames->GetElement(frames->GetSize() - 1, &frame);
		
	    frame->QueryInterface(IID_IDirect3DRMFrame3, (LPVOID*)&pFrame3);

		if(SUCCEEDED(visual->QueryInterface(IID_IDirect3DRMMeshBuilder3, (void **) &mesh)))
		{
			DWORD sz;
				char *name;
				mesh->GetName(&sz, NULL);
				name=(char*)malloc(sz*sizeof(char));
				mesh->GetName(&sz, name);
				if(sz>0)
				{
				  if(strstr(name, "selMesh")||strstr(name, "grid"))
				  {
					  free(name);
					  mesh->Release();
					  frames->Release();
						frame->Release();
						pFrame3->Release();
						visual->Release();
						return;

				  }
				  selectedMesh = mesh;
					unsigned int vNum = atoi(name);
					m_PtsListSelectedIndex=vNum;
					m_iTempGroup[m_iTempGroupCount] = vNum;
					m_iTempMouse[m_iTempGroupCount]=point;
					m_iTempGroupCount++;
					
					CString s;
					for(int k = 0;k<2;k++)
					{
						time_t timer;
							time( &timer );
							time_t timer2 = 0;
							while(timer2<timer+1)
							{
								time( &timer2 );
							}
								s.Format(L"Point: %d", vNum);
							
							while(timer2<timer+2)
							{
								time( &timer2 );
							}
								s.Format(L"Point:  ");
					}
					s.Format(L"Point: %d", vNum);
				free(name);
				}
				else
				{
					mesh->Release();
					  frames->Release();
						frame->Release();
						pFrame3->Release();
						visual->Release();
						return;
				}
			D3DVECTOR pnt;
			win3dMat->m_SceneObjects->m_view->InverseTransform( &pnt, &v4Src);
			
			LPDIRECT3DRMFACE2 face;
			if(D3DRM_OK==mesh->GetFace(pickDesc.ulFaceIdx, &face))
			{
				int fvCnt = face->GetVertexCount();
			}
			}}}
}

D3DVECTOR CRotoDraw3DDlg::SelectGridFace(UINT nFlags, CPoint point )
{
	D3DVECTOR v1,v2,v3,pn,intersect,pos,dvCamPos; 
	if(m_bLButtonDown==true){
	LPDIRECT3DRMFRAME3 pCamera;
	
    D3DRMVECTOR4D v4Src;
	
    win3dMat->m_SceneObjects->m_view->GetCamera(&pCamera);
   
	pCamera->GetPosition(NULL, &dvCamPos );
    pCamera->Release();

	
    v4Src.x = (float)(point.x);
    v4Src.y = (float)(point.y);
    v4Src.z = 0.0f;
    v4Src.w = 1.0f;

	
   
			LPDIRECT3DRMFRAME3 pFrame3 = win3dMat->m_SceneObjects->gridFrame;
			
			win3dMat->m_SceneObjects->m_view->InverseTransform( &pos, &v4Src);
					
			win3dMat->m_SceneObjects->grid->GetVertex( 0, &v1 );
			win3dMat->m_SceneObjects->grid->GetVertex( 8, &v2 );
			win3dMat->m_SceneObjects->grid->GetVertex( 80, &v3 );
			pFrame3->Transform( &v1, &v1);
			pFrame3->Transform( &v2, &v2);
			pFrame3->Transform( &v3, &v3);
			Geometry geo;
			pn = geo.FindPlaneNormal( v1, v2, v3 );
			
			//transformtoworldcoord
			double camToMouseDist = geo.distanceBetweenPoints(dvCamPos, pos);
			
			pFrame3->Release();
			double t = geo.FindPlaneConstant(pn,v2);
			
				intersect = geo.FindPointIntersectPlane(pn, dvCamPos, pos,//camToMouseDir, 
					(float)t);
				
			geo.~Geometry();		

			CStatic* xstat = (CStatic*)GetDlgItem(IDC_MOUSE_POS_STATIC);
		CString s;
		s.Format(L"Mouse Position X: %.6f Y: %.6f Z: %.6f",intersect.x, intersect.y, intersect.z);
		xstat->SetWindowText(s);
			return intersect;

	}
	intersect.x=0;intersect.y=0;intersect.z=0;
	return intersect;
} 

void CRotoDraw3DDlg::DrawPointsOne( D3DVECTOR intersect, CPoint point)
{
	if(m_bLButtonDown==true)
	{
		if(win3dMat->m_fPointSpace>0.0F){
			
			if(m_fScrollDist>0.0F){
			if(checkDistance(intersect.x, intersect.y, intersect.z, m_fScrollDist))
			{
			CTetra apoint;
			LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(intersect.x, intersect.y, intersect.z, tex->r, tex->g, tex->b);
			win3dMat->m_scene->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			
				tex->x[m_iPointCount]=intersect.x;	
				tex->y[m_iPointCount]=intersect.y;	
				tex->z[m_iPointCount]=intersect.z;
				
				win3dMat->m_SceneObjects->finalMesh->AddVertex( intersect.x, intersect.y, intersect.z );
				win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 1.0F, 0.0F );
				m_iTempGroup[m_iTempGroupCount]=m_iPointCount;
				m_iTempMouse[m_iTempGroupCount] = point;
				CString s;
				s.Format(L"%d", m_iPointCount);
				LPCSTR p = (CStringA)s;
				tetra->SetName(p);
				m_iTempGroupCount++;
				m_iPointCount++;
			
			}//eo if(checkDistance(intersect.x, intersect.y, intersect.zz, m_fScrollDist)==true)
			}// eo if(m_fScrollDist>0.0F)
			else
			{
				CTetra apoint;
			LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(intersect.x, intersect.y, intersect.z, tex->r, tex->g, tex->b);
			win3dMat->m_scene->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			CString p;
				tex->x[m_iPointCount]=intersect.x;	
				tex->y[m_iPointCount]=intersect.y;	
				tex->z[m_iPointCount]=intersect.z;
				
				win3dMat->m_SceneObjects->finalMesh->AddVertex( intersect.x, intersect.y, intersect.z );
				win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 1.0F, 0.0F );
				m_iTempGroup[m_iTempGroupCount]=m_iPointCount;
				m_iTempMouse[m_iTempGroupCount] = point;
				m_iTempGroupCount++;
			m_iPointCount++;
			p.Format(L"%d",m_iPointCount);
			tetra->SetName("p");
			}// eo else if(m_fScrollDist>0.0F)
			
			win3dMat->WinRender();
					
		//}//eoif(SUCCEEDED(visual->Q
		
			//pSect=intersect;

	}// eo if(m_bLButtonDown==true){		
	}
}

void CRotoDraw3DDlg::Copy() 
{
		unsigned int i = 0;
		
		m_GroupListSelectedIndex=i;
		
		unsigned int sz = m_PtGroups.m_iPointGroups[i].intCount-1;
		D3DVECTOR *vs = (D3DVECTOR*)malloc(sz*sizeof(D3DVECTOR));
		if( vs != NULL )
		{
			for(unsigned int j=0;j<sz;j++)
			{
				D3DVECTOR v;
				DWORD n = m_PtGroups.m_iPointGroups[i].value[j];
				win3dMat->m_SceneObjects->finalMesh->GetVertex( n, &v);
			
				D3DVECTOR t;
				win3dMat->m_SceneObjects->gridFrame->InverseTransform( &t, &v );
				vs[j]=t;
			}//eojfor
		
			CreateDimensions(vs, sz);
			makeBox( vs, sz, box );

			if(sz>0)free(vs);
		}
}

void CRotoDraw3DDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLButtonDown=false;
	// This enables the demo clip
	//BitmapBrush(&m_Clip_Win, m_iPointCount, 0);
	

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CRotoDraw3DDlg::checkDistance(float x, float y, float z, float mouseMoveDistDelta)
{
	BOOL tf = false;
	float xx = x - distX;
	if(xx<0)xx=-xx;
	float yy = y - distY;
	if(yy<0)yy=-yy;
	float zz = z - distZ;
	if(zz<0)zz=-zz;

	if(( xx >= mouseMoveDistDelta) ||
		(yy >= mouseMoveDistDelta) ||
		(zz >= mouseMoveDistDelta))
		{
				distX=x;distY=y;distZ=z;
				tf = true;
		}
	return tf;
				
}

D3DVECTOR pSect;
void CRotoDraw3DDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	if(point.x>3&&point.x<345&&point.y>3&&point.y<345)
	{
		SetCursor( AfxGetApp()->LoadCursor(IDC_CROSSHAIR1));
		D3DVECTOR isect = SelectGridFace(nFlags, point);
		if(m_iDrawMode==2)
		{
				DrawPointsOne( isect, point );
		}
		else if(m_iDrawMode==3)
		{
			if(m_bLButtonDown==true)
			{
	LPDIRECT3DRMFRAME3 pCamera;
	
    D3DRMVECTOR4D v4Src;
	D3DVECTOR dvCamPos; 
    win3dMat->m_SceneObjects->m_view->GetCamera(&pCamera);
   
	pCamera->GetPosition(NULL, &dvCamPos );
    pCamera->Release();

	
    v4Src.x = (float)(point.x);
    v4Src.y = (float)(point.y);
    v4Src.z = 0.0f;
    v4Src.w = 1.0f;

	
   
			LPDIRECT3DRMFRAME3 pFrame3 = win3dMat->m_SceneObjects->gridFrame;
			D3DVECTOR pos;
			win3dMat->m_SceneObjects->m_view->InverseTransform( &pos, &v4Src);
		
			D3DVECTOR v1,v2,v3,pn,intersect;
			
			win3dMat->m_SceneObjects->grid->GetVertex( 0, &v1 );
			win3dMat->m_SceneObjects->grid->GetVertex( 8, &v2 );
			win3dMat->m_SceneObjects->grid->GetVertex( 80, &v3 );
			
			Geometry geo;
			pn = geo.FindPlaneNormal( v1, v2, v3 );
			
			//transformtoworldcoord
			//D3DVECTOR camToMouseDir = geo.directionBetweenPoints( dvCamPos, pos);
			double camToMouseDist = geo.distanceBetweenPoints(dvCamPos, pos);
			
			
			pFrame3->Transform( &v1, &v1);
			pFrame3->Transform( &v2, &v2);
			pFrame3->Transform( &v3, &v3);
			
			pFrame3->Release();
			double t = geo.FindPlaneConstant(pn,v2);
				intersect = geo.FindPointIntersectPlane(pn, dvCamPos, pos,//camToMouseDir, 
					(float)t);
			
			geo.~Geometry();
			if(win3dMat->m_fPointSpace>0.0F){
			/*
			if(m_fScrollDist>0.0F){
			if(checkDistance(intersect.x, intersect.y, intersect.z, m_fScrollDist))
			{
			CTetra apoint;
			LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(intersect.x, intersect.y, intersect.z, tex->r, tex->g, tex->b);
			win3dMat->m_scene->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			CString p;
				tex->x[m_iPointCount]=intersect.x;	
				tex->y[m_iPointCount]=intersect.y;	
				tex->z[m_iPointCount]=intersect.z;
				
				win3dMat->m_SceneObjects->finalMesh->AddVertex( intersect.x, intersect.y, intersect.z );
				win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 1.0F, 0.0F );
				m_iTempGroup[m_iTempGroupCount]=m_iPointCount;
				m_iTempMouse[m_iTempGroupCount] = point;
				p.Format(L"%d",m_iPointCount);
				tetra->SetName(p);
				m_iTempGroupCount++;
				m_iPointCount++;
			
			}//eo if(checkDistance(intersect.x, intersect.y, intersect.zz, m_fScrollDist)==true)
			}// eo if(m_fScrollDist>0.0F)
			else
			{
				CTetra apoint;
			LPDIRECT3DRMMESHBUILDER3 tetra = apoint.MakeTetra(intersect.x, intersect.y, intersect.z, tex->r, tex->g, tex->b);
			win3dMat->m_scene->AddVisual(tetra);
			tetra->SetQuality(D3DRMFILL_SOLID);
			CString p;
				tex->x[m_iPointCount]=intersect.x;	
				tex->y[m_iPointCount]=intersect.y;	
				tex->z[m_iPointCount]=intersect.z;
				
				win3dMat->m_SceneObjects->finalMesh->AddVertex( intersect.x, intersect.y, intersect.z );
				win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 1.0F, 0.0F );
				m_iTempGroup[m_iTempGroupCount]=m_iPointCount;
				m_iTempMouse[m_iTempGroupCount] = point;
				m_iTempGroupCount++;
			m_iPointCount++;
			p.Format(L"%d",m_iPointCount);
			tetra->SetName("p");
			}// eo else if(m_fScrollDist>0.0F)
			
			win3dMat->WinRender();
			}//eo if(D3DRM_OK==mesh->GetFace(pickDesc.ulFaceIdx, &face))
			//win3dMat->m_SceneObjects->grid=mesh;
			//mesh->Release();
			*/
		}//eoif(SUCCEEDED(visual->Q
			
			DWORD n = win3dMat->tempMeshBld->GetVertexCount();
			D3DVECTOR p;
			D3DRMVectorSubtract( &p, &pSect, &intersect);
			for(unsigned int i = 0;i<n;i++)
			{
				D3DVECTOR s,v;
				win3dMat->tempMeshBld->GetVertex( i, &s );
				win3dMat->m_SceneObjects->gridFrame->Transform(&v,&s);
				win3dMat->tempMeshBld->SetVertex( i, v.x-p.x, v.y-p.y,v.z-p.z );

			}
			
			pSect=intersect;
			}
		}
	
	}// extra for add in
	CDialog::OnMouseMove(nFlags, point);
}

void CRotoDraw3DDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CRotoDraw3DDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//m_bRButtonDown=false;
	CDialog::OnRButtonUp(nFlags, point);
}

void CRotoDraw3DDlg::Dispose()
{
	win3dMat->Close();
	AfxPostQuitMessage(0);
	
	
	
}

////////////////////////
///////////////////////
//

void CRotoDraw3DDlg::CreateDimensions(D3DVECTOR *copier, int qCount)
{
	
				
		box[0]=copier[0].x;
		box[1]=copier[0].x;
		box[2]=copier[0].y;
		box[3]=copier[0].y;
		box[4]=copier[0].z;
		box[5]=copier[0].z;
				
		for(int i=1;i<qCount;i++)
		{
			if(copier[i].x<box[0]){box[0]=copier[i].x;}
			if(copier[i].x>box[1]){box[1]=copier[i].x;}
			if(copier[i].y<box[2]){box[2]=copier[i].y;}
			if(copier[i].y>box[3]){box[3]=copier[i].y;}
			if(copier[i].z<box[4]){box[4]=copier[i].z;}
			if(copier[i].z>box[5]){box[5]=copier[i].z;}
		}
		
}

float * GetU( D3DVECTOR v, LPD3DRMBOX b, LPDIRECT3DRM3 rm, CRotoDraw3DDlg* arg)
{
	static float uv[2];
		
	float a = v.x;
	float c = v.y;
	float e = v.z;
	
	
	D3DVECTOR r;
	D3DVECTOR m;
	D3DVECTOR s;
	m.x = b->min.x;
	m.y = b->min.y;
	m.z = b->min.z;
	
	s.x=b->max.x;
	s.y=b->max.y;
	s.z=b->max.z;
	
	D3DRMVectorSubtract( &r, &m, &s);
	
		
		if(a==b->min.x)
		{
			uv[0]= 0.0F;
		}
	
	else{
		uv[0] = -1*((a- b->min.x)/r.x);
	   }
		if(c==b->max.y){
			uv[1]= 0.0F;
		}
	else{
		uv[1] = 1*((c-b->max.y)/r.y);	
	}

	return uv;
}

void SetTextCoords(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRM3 rm, CRotoDraw3DDlg* arg)
{
	D3DRMBOX box;
		mb->GetBox(&box);
		
				
		for(int i = 0;i<mb->GetVertexCount();i++)
		{
			D3DVECTOR v;
			mb->GetVertex( i, &v );
			float *u = GetU( v, &box, rm, arg);
			
			mb->SetTextureCoordinates(i, u[0], u[1]);
		
		
		}
}
LPDIRECT3DRMMATERIAL2 CRotoDraw3DDlg::MakeMaterial(LPDIRECT3DRM3 rm, LPDIRECT3DRMMATERIAL2 mat, int i)
{
		 rm->CreateMaterial(m_MatArray.m_Mats[i].args[0], &mat);
	     mat->SetEmissive(m_MatArray.m_Mats[i].args[1], m_MatArray.m_Mats[i].args[2], m_MatArray.m_Mats[i].args[3]);
	     mat->SetSpecular(m_MatArray.m_Mats[i].args[4],  m_MatArray.m_Mats[i].args[5], m_MatArray.m_Mats[i].args[6]);
		 mat->SetAmbient(m_MatArray.m_Mats[i].args[7],  m_MatArray.m_Mats[i].args[8], m_MatArray.m_Mats[i].args[9]);
		 
		 return mat;
	}

void CRotoDraw3DDlg::makeBox(D3DVECTOR *copier, int qCount, float* b)
	{
		
		LPDIRECT3DRM rm;
		Direct3DRMCreate( &rm);
		LPDIRECT3DRM3 rm3 = NULL;
		rm->QueryInterface( IID_IDirect3DRM3, (void**)&rm3);
		
		
		rm3->CreateMeshBuilder( &win3dMat->tempMeshBld );

		DWORD adwFace1Data[] = {  4,4,4,0,0,2,2,6,6,
							  4,4,4,6,6,2,2,0,0,
	                          4,4,4,5,5,1,1,0,0,
							  4,4,4,0,0,1,1,5,5,
	                          4,4,4,6,6,7,7,5,5,
							  4,4,4,5,5,7,7,6,6,
	                          4,0,0,1,1,3,3,2,2,
							  4,0,0,2,2,3,3,1,1,
	                          4,1,1,5,5,7,7,3,3,
							  4,1,1,3,3,7,7,5,5,
	                          4,3,3,7,7,6,6,2,2,
							  4,3,3,2,2,6,6,7,7,0 };
		D3DVECTOR avCubeVertices[] = { box[0], box[2], box[4],  box[0], box[2],  box[5],
									   box[0],  box[3], box[4],  box[0],  box[3],  box[5],
									   box[1], box[2], box[4],   box[1], box[2],  box[5],
									   box[1],  box[3], box[4],   box[1],  box[3],  box[5] };



	D3DVECTOR avCube1Normals[8];

	for(int i = 0;i<8;i++)
	{
		
		avCube1Normals[i]=avCubeVertices[i];
			D3DRMVectorNormalize(&avCube1Normals[i]);
	}

	win3dMat->tempMeshBld->AddFaces( 8, avCubeVertices, 8, avCube1Normals,
			                            adwFace1Data, NULL );
	
		
		LPDIRECT3DRMFACE2 copyFace, copyFace2;
			rm3->CreateFace(&copyFace);
		win3dMat->tempMeshBld->AddFace(copyFace);
		rm3->CreateFace(&copyFace2);
		win3dMat->tempMeshBld->AddFace(copyFace2);
		int cnt = qCount-1;
		for(int i =0;i<qCount;i++)
		{
			D3DVECTOR v1;
			v1.x = copier[i].x;
			v1.y = copier[i].y;
			v1.z = copier[i].z;
			win3dMat->tempMeshBld->AddVertex(copier[i].x,copier[i].y,copier[i].z);
			D3DRMVectorNormalize(&v1);
			win3dMat->tempMeshBld->AddNormal(v1.x,v1.y,v1.z);
			
			copyFace->AddVertexAndNormalIndexed(i,i);
			copyFace2->AddVertexAndNormalIndexed(cnt,cnt);cnt--;

		}
		
		BYTE fBlue=0;
		BYTE fGreen=255;
		BYTE fRed=0;
		BYTE bBlue=255;
		BYTE bGreen=0;
		BYTE bRed=0;
		//texture group1
		LPDIRECT3DRMMATERIAL2 mat1 = NULL;
			rm3->CreateMaterial(0.0F, &mat1);
		copyFace->SetMaterial(mat1);
		copyFace->SetColor(RGBA_MAKE(bRed, bGreen, bBlue, 128));
		copyFace2->SetMaterial(mat1);
		copyFace2->SetColor(RGBA_MAKE(bRed, bGreen, bBlue, 128));
			win3dMat->tempMeshBld->SetMaterial(mat1);
			win3dMat->tempMeshBld->SetColor(RGBA_MAKE(fRed, fGreen, fBlue, 128));
	
		renderType = D3DRMRENDER_UNLITFLAT;
		fillType = D3DRMFILL_SOLID;
		lightStatus = D3DRMLIGHT_ON;
			
		win3dMat->tempMeshBld->SetQuality(
						 renderType+
						 lightStatus+
						 fillType
						 );
		copyFace->Release();
		copyFace2->Release();
		win3dMat->m_SceneObjects->gridFrame->AddVisual(win3dMat->tempMeshBld);
		
		
		mat1->Release();
		rm3->Release();
		rm->Release();
				
		win3dMat->WinRender();
}

MyTexture* CRotoDraw3DDlg::GetMyTexture()
{
	return tex;
}

void CRotoDraw3DDlg::DoFaces()
{
	if(m_MatArray.m_Count>0)
	{

	//waitcursor
			
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm3 = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm3);
	SetTextCoords( win3dMat->m_SceneObjects->finalMesh, rm3, this);
	LPDIRECT3DRMTEXTURE3 texture  = NULL;
	LPDIRECT3DRMTEXTURE3 texture2 = NULL;
	LPDIRECT3DRMMATERIAL2 mat1 = NULL;
	LPDIRECT3DRMMATERIAL2 mat2 = NULL;
		mat1 = MakeMaterial(rm3, mat1, selMatFront);
		if(selMatBack>=0)
		mat2 = MakeMaterial(rm3, mat2, selMatBack);
	if(	selTexFrontPath.GetLength()>0)
			{
				
				rm3->LoadTexture(selTexFrontPath, &texture);
			}
	if(	selTexBackPath.GetLength()>0)
			{
				
				rm3->LoadTexture(selTexBackPath, &texture2);
				
			}
	
	int len = m_PtGroups.m_iPointGroups[m_SelIndexOne].intCount;
	int len2 =	m_PtGroups.m_iPointGroups[m_SelIndexTwo].intCount;
	int num = 0;
	bool grOneHangFlag = false;
	bool grTwoHangFlag = false;
	if(len>len2)
	{
		grOneHangFlag = true;
		grTwoHangFlag = false;
		num = len2;
	}
	else if(len2>len)
	{
		grOneHangFlag = false;
		grTwoHangFlag = true;
		num=len;
	}
	else{
		
		num=len;
	}
	

		for(int i = 1;i<num-1;i++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			
			int v1 = m_PtGroups.m_iPointGroups[m_SelIndexOne].value[i];
			int v2 = m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[i];
			int pts[4];

			if(m_bDoFrontFaces==true)
			{
				rm3->CreateFace(&face);
				win3dMat->m_SceneObjects->finalMesh->AddFace(face);
				face->AddVertexAndNormalIndexed( v1-1, v1-1);
				pts[0]=v1-1;
				face->AddVertexAndNormalIndexed(v1, v1);
				pts[1]=v1;
				face->AddVertexAndNormalIndexed(v2, v2);
				pts[2]=v2;
				face->AddVertexAndNormalIndexed(v2-1 , v2-1 );
				pts[3]= v2-1;
			}

			
			if(textureFillMode==1)//FDIFFTEXTURES
			{
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&bface);
					win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
					bface->AddVertexAndNormalIndexed( v1-1, v1-1);
					pts[0]=v1-1;
					bface->AddVertexAndNormalIndexed(v2-1 , v2-1 );
					pts[1]= v2-1;
					bface->AddVertexAndNormalIndexed(v2, v2);
					pts[2]=v2;
					bface->AddVertexAndNormalIndexed(v1, v1);
					pts[3]=v1;
					m_bSetFacesButtonPushed = true;
				}

			}
			DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
		
		if(grOneHangFlag==true)
		{
			
		for(int j = len2-2;j<len-1;j++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			
			int v1 = m_PtGroups.m_iPointGroups[m_SelIndexOne].value[j];
			int v2 = m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[(len2-2)];
			
			int pts[3];
			if(m_bDoFrontFaces==true)
			{
				rm3->CreateFace(&face);
				win3dMat->m_SceneObjects->finalMesh->AddFace(face);
				face->AddVertexAndNormalIndexed(v2 , v2 );
				pts[0]= v2;
				face->AddVertexAndNormalIndexed( v1-1, v1-1);
				pts[1]=v1-1;
				face->AddVertexAndNormalIndexed(v1, v1);
				pts[2]=v1;
			}
			if(textureFillMode==1)//FDIFFTEXTURES
			{
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&bface);
					win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
					bface->AddVertexAndNormalIndexed(v2 , v2 );
					pts[0]= v2;
					bface->AddVertexAndNormalIndexed(v1, v1);
					pts[1]=v1;
					bface->AddVertexAndNormalIndexed( v1-1, v1-1);
					pts[2]=v1-1;
					m_bSetFacesButtonPushed = true;
				}
			}
			DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
			
		}// eo if(grOneHangFlag==true)

		else if(grTwoHangFlag==true)
		{
			
		for(int i = len-2;i<len2-1;i++)
		{
			LPDIRECT3DRMFACE2 face;
			LPDIRECT3DRMFACE2 bface;
			int v1 = m_PtGroups.m_iPointGroups[m_SelIndexOne].value[len-2];
			int v2 = m_PtGroups.m_iPointGroups[m_SelIndexTwo].value[i];
			int pts[3];
			if(m_bDoFrontFaces==true)
			{
				rm3->CreateFace(&face);
				win3dMat->m_SceneObjects->finalMesh->AddFace(face);
					face->AddVertexAndNormalIndexed( v1, v1);
					pts[0]=v1;
					face->AddVertexAndNormalIndexed(v2 , v2 );
					pts[1]= v2;
					face->AddVertexAndNormalIndexed(v2-1, v2-1);
					pts[2]=v2-1;
					//cfpgdlg->facesCtrl->SetFaceData3(pts);
			
					//cfpgdlg->facesCtrl->SetFaceList(selMatFront);
					//own.oVars.aboutToSetEdge = true;
			}
			if(textureFillMode==1)//FDIFFTEXTURES
			{
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&bface);
						//undo.m_FacesArray=undo.Grow( bface);
					win3dMat->m_SceneObjects->finalMesh->AddFace(bface);
						//cfpgdlg->facesCtrl->AddFaces();
						//	m_UndoList.value= m_UndoList.grow(cfpgdlg->facesCtrl->currentFace);
			
					bface->AddVertexAndNormalIndexed( v1, v1);
					pts[0]=v1;
					bface->AddVertexAndNormalIndexed(v2-1 , v2-1 );
					pts[1]= v2-1;
					bface->AddVertexAndNormalIndexed(v2, v2);
					pts[2]=v2;
					//cfpgdlg->facesCtrl->SetFaceData3(pts);
					//cfpgdlg->facesCtrl->SetFaceList(selMatBack);
					m_bSetFacesButtonPushed = true;
				}
			}
			DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, face, bface, mat1, mat2, texture, texture2);
		}//eofor
			
		}//eo if(grTwoHangFlag==true)
		win3dMat->m_SceneObjects->finalMesh->GenerateNormals( 0.0F, 2);
	rm3->Release();
	rm1->Release();
	//GetDlgItem(IDC_UNDO_BUTTON)->EnableWindow(TRUE);
	m_GroupListSelectedIndex=-858993460;
	m_SelIndexOne=m_SelIndexTwo=-858993460;
	}// eo  if(m_MatCount>)
	else{
		
		MessageBox( L"Objects cannot be made without first loading a set of materials using the material editor", L"No Materials Loaded", MB_OK);
	}//eo if(m_MatArray.m_Count<=0)
}

void CRotoDraw3DDlg::DoTextureSetting3(LPDIRECT3DRMMESHBUILDER3 mb, LPDIRECT3DRMFACE2 frontFace, LPDIRECT3DRMFACE2 backFace, LPDIRECT3DRMMATERIAL2 mat1, LPDIRECT3DRMMATERIAL2 mat2, LPDIRECT3DRMTEXTURE3 texture, LPDIRECT3DRMTEXTURE3 texture2)
{
	
	LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 d3drmb = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&d3drmb);
	
	if(m_bColorSet == false)
	{
		MessageBox(L"Please choose the appropriate textures or materials from the color select and then hit yes, \n\na continue button will show on the color select bar once you are done", L"no colors chosen", MB_OK);
	}
	else
	{
	switch(textureFillMode){
		case 1://FDIFFTEXTURES
			{	
				if(m_bDoFrontFaces==true)
				{
					frontFace->SetMaterial(mat1);
					//frontFace->SetColorRGB(frontRed, frontGreen, frontBlue);
					D3DCOLOR col = RGBA_MAKE((int)(frontRed*255), (int)(frontGreen*255), (int)(frontBlue*255), (int)(frontAlpha*255));
					frontFace->SetColor(col);
						if(	selTexFrontPath.GetLength()>0)
						{
							frontFace->SetTexture(texture);
						}
				}
				if(m_bDoBackFaces==true)
				{
					backFace->SetMaterial(mat2);
					//backFace->SetColorRGB(backRed, backGreen, backBlue);
					D3DCOLOR bcol = RGBA_MAKE((int)(backRed*255), (int)(backGreen*255), (int)(backBlue*255), (int)(backAlpha*255));
					backFace->SetColor(bcol);
						if(	selTexBackPath.GetLength()>0)
						{
							backFace->SetTexture(texture2);
						}
				}
			}
			break;
		case 2://FSAMETEXTURES
			{
				if(	selTexFrontPath.GetLength()>0)
				{
					LPDIRECT3DRMTEXTURE3 texture;
					d3drmb->LoadTexture(selTexFrontPath, &texture);
			
					mb->SetTexture(texture);
				}
			mb->SetMaterial(mat1);
			//mb->SetColorRGB(frontRed, frontGreen, frontBlue);
			D3DCOLOR mbcol = RGBA_MAKE((int)(frontRed*255), (int)(frontGreen*255), (int)(frontBlue*255), (int)(frontAlpha*255));
			mb->SetColor(mbcol);

			break;
		 } //end of texture fillmode switch
		

		
		lastFrontFace = frontFace;
		lastBackFace  = backFace;
			
		faceAdded = true;
		mb->SetQuality(
						 renderType+
						 lightStatus+
						 fillType
						 );
		
		win3dMat->WinRender();
		
	}//eoelse
}
	
	d3drmb->Release();
	rm1->Release();
}

void CRotoDraw3DDlg::OnSetColorsButton() 
{
	//CMaterialDlg* 
		m_matdlg=new CMaterialDlg();
	m_matdlg->Create(VIEWERCHOOSECOLOR);
	m_matdlg->ShowWindow( SW_SHOW);
	m_matdlg->Set3dbutton();
	win3dMat->WinRender();
	
	m_bMaterialDlgColorsSet = true;
	
}

void CRotoDraw3DDlg::OnSetPointsButton() 
{
	if( m_bMaterialDlgColorsSet == true ){
	if(m_iDrawMode==2)
	{
	if(m_iPointCount>0)
	{
		if(m_iTempGroupCount>0)
		{
			
			CString s;
			unsigned int curNum = m_MeshPoints.m_iNumPoints;
			m_MeshPoints.GrowByEmptyEnd(m_iPointCount);
			for(unsigned int i = curNum;i<m_iPointCount;i++)
			{
				m_MeshPoints.Set( m_MeshPoints.m_iNumPoints, tex->x[i], tex->y[i], tex->z[i] );
		
				m_MeshPoints.m_iNumPoints++;
			}
			
			CString list;
			CString temp;
			CHDXINTARRAY arg;
			arg.allocate(0);
			arg.value=arg.growByEmptyEnd( m_iTempGroupCount+1 ); 

			CHDXPOINTARRAY argmx;
			argmx.allocate(0);
			argmx.value=argmx.growByEmptyEnd( m_iTempGroupCount+1 ); 

			
			for(unsigned int j=0;j<m_iTempGroupCount;j++)
			{
				arg.set( j, m_iTempGroup[j] );
				argmx.set( j, m_iTempMouse[j] );
				s.Format(L"%d, ", arg.value[j]);
				temp.Format(L"%s%s", list, s);
				list.Format(L"%s", temp);
			}
			m_PtGroups.m_iPointGroups=m_PtGroups.Grow( arg );
			m_PtGroups.m_Mouse=m_PtGroups.GrowMouse( argmx );
			
	
			CCamGridStats stats;
			stats.m_CamPosX=win3dMat->m_SceneObjects->m_CamPos.x;
			stats.m_CamPosY=win3dMat->m_SceneObjects->m_CamPos.y;
			stats.m_CamPosZ=win3dMat->m_SceneObjects->m_CamPos.z;
			stats.m_CamRotX=win3dMat->m_SceneObjects->m_CamRot.x;
			stats.m_CamRotY=win3dMat->m_SceneObjects->m_CamRot.y;
			stats.m_CamRotZ=win3dMat->m_SceneObjects->m_CamRot.z;
			stats.m_CamTheta[0]=win3dMat->m_SceneObjects->m_CamTheta[0];
			stats.m_CamOrDirX=win3dMat->m_SceneObjects->m_CamDir.x;
			stats.m_CamOrDirY=win3dMat->m_SceneObjects->m_CamDir.y;
			stats.m_CamOrDirZ=win3dMat->m_SceneObjects->m_CamDir.z;
			stats.m_CamOrUpX=win3dMat->m_SceneObjects->m_CamUp.x;
			stats.m_CamOrUpY=win3dMat->m_SceneObjects->m_CamUp.y;
			stats.m_CamOrUpZ=win3dMat->m_SceneObjects->m_CamUp.z;

			m_PtGroups.m_CamGridStats=m_PtGroups.GrowStats(stats );
	
			m_iTempGroupCount=0;
			m_iGroupCount++;
			m_PtGroups.m_iPtStatsCount=m_PtGroups.m_iPtMouseCount=m_PtGroups.m_iPtGroupCount=m_iGroupCount;
		}//eo if(m_iGroupCount>0)
	}//eo if(m_iPointCount>0)
	}//eo if(m_iDrawMode==2)		
	
	frontRed   = (float)m_MatArray.m_Mats[0].r/255;
	frontGreen = (float)m_MatArray.m_Mats[0].g/255;
	frontBlue  = (float)m_MatArray.m_Mats[0].b/255;
	frontAlpha = (float)m_MatArray.m_Mats[0].a/255;
	selMatFront=0;
	textureFillMode = FSAMETEXTURES;
	selTexFrontPath = m_MatArray.m_Mats[0].file;
	if(m_MatArray.m_Count>1)
	{
	backRed   = (float)m_MatArray.m_Mats[1].r/255;
	backGreen = (float)m_MatArray.m_Mats[1].g/255;
	backBlue  = (float)m_MatArray.m_Mats[1].b/255;
	backAlpha = (float)m_MatArray.m_Mats[1].a/255;
	selMatBack=1;
	textureFillMode = FDIFFTEXTURES;
	selTexBackPath = m_MatArray.m_Mats[1].file;
	}
	float threesixty = 360.0F*0.017453293005625408F;
	int rotCount = (int)(threesixty/win3dMat->m_fCameraRotationValue);

	Copy();
	CCopyPosRotScaleCtrl* ccprsctrl = new CCopyPosRotScaleCtrl();

	// Num of Points
	unsigned int m_iTotalPointCount=0;
	// Num of Faces
	unsigned int m_iNumFaces = 0;

	m_iTotalPointCount = rotCount * m_MeshPoints.m_iNumPoints;
	m_iNumFaces = rotCount * (m_MeshPoints.m_iNumPoints-1);
	if(m_bAddTopFaces==true)
	{
		m_iTotalPointCount++;
		m_iNumFaces += rotCount;
	}
	if(m_bAddBottomFaces==true)
	{
		m_iTotalPointCount++;
		m_iNumFaces += rotCount;
	}

	for(int i = 0;i<rotCount-1;i++)
	{
		m_GroupListSelectedIndex = 0;
		if(m_bIsYAxis == true)
		{
			win3dMat->circleCamOnAxis( 4, win3dMat->m_fCameraOffset);
		}
		else
		{
			win3dMat->circleCamOnAxis( 2, win3dMat->m_fCameraOffset);
		}
		ccprsctrl->GetOk();

		m_SelIndexOne = i;
		m_SelIndexTwo = i+1;
		DoFaces();
	}// eo i for

	//m_SelIndexOne = i;
	//	m_SelIndexTwo = 0;
	//	DoFaces();
	win3dMat->m_SceneObjects->gridFrame->DeleteVisual(win3dMat->tempMeshBld);

	
	
	int frontId=0;
	int backId=0;
	if(m_bIsYAxis==true)
	{
		float y;
		if(m_bAddTopFaces==true)
		{
			y = m_MeshPoints.y.value[0];
			win3dMat->m_SceneObjects->finalMesh->AddVertex( 0.0F, y, 0.0F );
			win3dMat->m_SceneObjects->finalMesh->AddNormal( -1.0F, 0.0F, 0.0F );
			frontId = win3dMat->m_SceneObjects->finalMesh->GetVertexCount()-1;

		}// eo if(m_bAddTopFaces==true)
		if(m_bAddBottomFaces==true)
		{
			y = m_MeshPoints.y.value[m_MeshPoints.m_iNumPoints-2];
			win3dMat->m_SceneObjects->finalMesh->AddVertex( 0.0F, y, 0.0F );
			win3dMat->m_SceneObjects->finalMesh->AddNormal( -1.0F, 0.0F, 0.0F );
			backId = win3dMat->m_SceneObjects->finalMesh->GetVertexCount()-1;

		}// eo if(m_bAddBottomFaces==true)

	}//eo
	else if(m_bIsYAxis==false)
	{
		float x;
		if(m_bAddTopFaces==true)
		{
			x = m_MeshPoints.y.value[0];
			win3dMat->m_SceneObjects->finalMesh->AddVertex( x, 0.0F, 0.0F );
			win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 0.0F, 0.0F );
			frontId = win3dMat->m_SceneObjects->finalMesh->GetVertexCount()-1;

		}// eo if(m_bAddTopFaces==true)
		if(m_bAddBottomFaces==true)
		{
				x = m_MeshPoints.y.value[m_MeshPoints.m_iNumPoints-2];
			win3dMat->m_SceneObjects->finalMesh->AddVertex( x, 0.0F, 0.0F );
			win3dMat->m_SceneObjects->finalMesh->AddNormal( 1.0F, 0.0F, 0.0F );
			backId = win3dMat->m_SceneObjects->finalMesh->GetVertexCount()-1;

		}// eo if(m_bAddBottomFaces==true)
	}//eo if(m_bIsYAxis==true)
	LPDIRECT3DRM rm;
	Direct3DRMCreate( &rm );
	LPDIRECT3DRM3 rm3;
	rm->QueryInterface( IID_IDirect3DRM3, (void**)&rm3);
	LPDIRECT3DRMMATERIAL2 mat = NULL;
				mat = MakeMaterial( rm3, mat, 0);
	LPDIRECT3DRMMATERIAL2 mat2 = NULL;
				mat2 = MakeMaterial( rm3, mat2, 0);
	LPDIRECT3DRMTEXTURE3 texture=NULL;
	LPDIRECT3DRMTEXTURE3 texture2=NULL;
	if(	selTexBackPath.GetLength()>0)
	{
		rm3->LoadTexture( selTexBackPath, &texture2 );
	}
	if(	selTexFrontPath.GetLength()>0)
	{
		rm3->LoadTexture( selTexFrontPath, &texture );
	}
						
		int a, b, i;
		for( i = 0;i<rotCount-1;i++)
		{
			
			if(m_bAddTopFaces==true)
			{
				LPDIRECT3DRMFACE2 face = {};
				LPDIRECT3DRMFACE2 face2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&face);
					win3dMat->m_SceneObjects->finalMesh->AddFace( face);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[i+1].value[0];
					face->AddVertexAndNormalIndexed( frontId, frontId );
					face->AddVertexAndNormalIndexed( a, a );
					face->AddVertexAndNormalIndexed( b, b );
				}
				if(m_bDoBackFaces==true)
				{
					
					rm3->CreateFace(&face2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( face2);
					b = m_PtGroups.m_iPointGroups[i].value[0];
					a = m_PtGroups.m_iPointGroups[i+1].value[0];
					face2->AddVertexAndNormalIndexed( frontId, frontId );
					face2->AddVertexAndNormalIndexed( a, a );
					face2->AddVertexAndNormalIndexed( b, b );
				}
					DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, face, face2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)face->Release();
					if(m_bDoBackFaces==true)face2->Release();
						
			}
			if(m_bAddBottomFaces==true)
			{
				LPDIRECT3DRMFACE2 fac = {};
				LPDIRECT3DRMFACE2 fac2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&fac);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac);
					a = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					b = m_PtGroups.m_iPointGroups[i+1].value[m_PtGroups.m_iPointGroups[i+1].intCount-2];
					fac->AddVertexAndNormalIndexed( backId, backId );
					fac->AddVertexAndNormalIndexed( b, b );
					fac->AddVertexAndNormalIndexed( a, a );
				}
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&fac2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac2);
					b = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					a = m_PtGroups.m_iPointGroups[i+1].value[m_PtGroups.m_iPointGroups[i+1].intCount-2];
					fac2->AddVertexAndNormalIndexed( backId, backId );
					fac2->AddVertexAndNormalIndexed( b, b );
					fac2->AddVertexAndNormalIndexed( a, a );
				}
				DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, fac, fac2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)fac->Release();
					if(m_bDoBackFaces==true)fac2->Release();
			}

			if(m_bLastToFirstFaces==true)
			{
				LPDIRECT3DRMFACE2 fac = {};
				LPDIRECT3DRMFACE2 fac2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&fac);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[i+1].value[0];
					fac->AddVertexAndNormalIndexed( a, a );
					fac->AddVertexAndNormalIndexed( b, b );
				
					a = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					b = m_PtGroups.m_iPointGroups[i+1].value[m_PtGroups.m_iPointGroups[i+1].intCount-2];
					fac->AddVertexAndNormalIndexed( b, b );
					fac->AddVertexAndNormalIndexed( a, a );
				}
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&fac2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac2);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					fac2->AddVertexAndNormalIndexed( a, a );
					fac2->AddVertexAndNormalIndexed( b, b );
				
					b = m_PtGroups.m_iPointGroups[i+1].value[m_PtGroups.m_iPointGroups[i+1].intCount-2];
					a = m_PtGroups.m_iPointGroups[i+1].value[0];
					fac2->AddVertexAndNormalIndexed( b, b );
					fac2->AddVertexAndNormalIndexed( a, a );
				}
				DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, fac, fac2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)fac->Release();
					if(m_bDoBackFaces==true)fac2->Release();
			}
		}// eo i for

		if(m_bAddTopFaces==true)
			{
				LPDIRECT3DRMFACE2 face = {};
				LPDIRECT3DRMFACE2 face2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&face);
					win3dMat->m_SceneObjects->finalMesh->AddFace( face);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[0].value[0];
					face->AddVertexAndNormalIndexed( frontId, frontId );
					face->AddVertexAndNormalIndexed( a, a );
					face->AddVertexAndNormalIndexed( b, b );
				}
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&face2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( face2);
					b = m_PtGroups.m_iPointGroups[i].value[0];
					a = m_PtGroups.m_iPointGroups[0].value[0];
					face2->AddVertexAndNormalIndexed( frontId, frontId );
					face2->AddVertexAndNormalIndexed( a, a );
					face2->AddVertexAndNormalIndexed( b, b );
				}
				DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, face, face2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)face->Release();
					if(m_bDoBackFaces==true)face2->Release();
			}
			if(m_bAddBottomFaces==true)
			{
				LPDIRECT3DRMFACE2 fac = {};
				LPDIRECT3DRMFACE2 fac2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&fac);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac);
					b = m_PtGroups.m_iPointGroups[0].value[m_PtGroups.m_iPointGroups[0].intCount-2];
					a = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					fac->AddVertexAndNormalIndexed( backId, backId );
					fac->AddVertexAndNormalIndexed( b, b );
					fac->AddVertexAndNormalIndexed( a, a );
				}
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&fac2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac2);
					a = m_PtGroups.m_iPointGroups[0].value[m_PtGroups.m_iPointGroups[0].intCount-2];
					b = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					fac2->AddVertexAndNormalIndexed( backId, backId );
					fac2->AddVertexAndNormalIndexed( b, b );
					fac2->AddVertexAndNormalIndexed( a, a );
				}
				DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, fac, fac2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)fac->Release();
					if(m_bDoBackFaces==true)fac2->Release();
			}
			if(m_bLastToFirstFaces==true)
			{
				LPDIRECT3DRMFACE2 fac = {};
				LPDIRECT3DRMFACE2 fac2 = {};
				if(m_bDoFrontFaces==true)
				{
					rm3->CreateFace(&fac);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[0].value[0];
					fac->AddVertexAndNormalIndexed( a, a );
					fac->AddVertexAndNormalIndexed( b, b );
				
					a = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					b = m_PtGroups.m_iPointGroups[0].value[m_PtGroups.m_iPointGroups[0].intCount-2];
					fac->AddVertexAndNormalIndexed( b, b );
					fac->AddVertexAndNormalIndexed( a, a );
				}
				if(m_bDoBackFaces==true)
				{
					rm3->CreateFace(&fac2);
					win3dMat->m_SceneObjects->finalMesh->AddFace( fac2);
					a = m_PtGroups.m_iPointGroups[i].value[0];
					b = m_PtGroups.m_iPointGroups[i].value[m_PtGroups.m_iPointGroups[i].intCount-2];
					fac2->AddVertexAndNormalIndexed( a, a );
					fac2->AddVertexAndNormalIndexed( b, b );
				
					b = m_PtGroups.m_iPointGroups[0].value[m_PtGroups.m_iPointGroups[0].intCount-2];
					a = m_PtGroups.m_iPointGroups[0].value[0];
					fac2->AddVertexAndNormalIndexed( b, b );
					fac2->AddVertexAndNormalIndexed( a, a );
				}
				DoTextureSetting3(win3dMat->m_SceneObjects->finalMesh, fac, fac2, mat, mat2, texture, texture2);
					if(m_bDoFrontFaces==true)fac->Release();
					if(m_bDoBackFaces==true)fac2->Release();
			}
	if(mat!=NULL)mat->Release();
	if(mat2!=NULL)mat2->Release();
	if(texture!=NULL)texture->Release();
	if(texture2!=NULL)texture2->Release();
	rm3->Release();
	rm->Release();	
	m_bObjectDrawn=true;

	
	DWORD sz;
	LPUNKNOWN *array;
	win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals(&sz, NULL);
	array=(LPUNKNOWN*)malloc(sz*sizeof(LPUNKNOWN));
	win3dMat->m_SceneObjects->finalMeshFrame->GetVisuals(&sz, array);
	for(DWORD l=0;l<sz;l++)
	{
		LPDIRECT3DRMVISUAL vis; 
		array[ l]->QueryInterface(IID_IDirect3DRMVisual, (void**)&vis);;
		DWORD nCnt;
		vis->GetName( &nCnt, NULL );
		char *name = (char*)malloc( nCnt*sizeof(char));
		vis->GetName( &nCnt, name );
		if(strstr(name, "finalMesh")==NULL)
		{
			win3dMat->m_SceneObjects->finalMeshFrame->DeleteVisual(vis);	
		}// eo if(strstr( name, "finalMesh")
		vis->Release();
		if(NULL!=name)free(name);
	}//eo lfor
	if(NULL!=array)free(array);
	
  }// eo if(m_bMaterialDlgColorsSet)
  else{MessageBox( L"You must first set colors and add points before setting points",L"Error",MB_OK);
  }

}

void CRotoDraw3DDlg::OnTopOrLeftCheck() 
{
	int check = m_TopOrLeft.GetCheck();
	if(check==0)
	{
		m_bAddTopFaces = false;
	}
	if(check==1)
	{
		m_bAddTopFaces = true;
	}
	
}

void CRotoDraw3DDlg::OnBottomOrRightCheck() 
{
	int check = m_BottomOrRight.GetCheck();
	if(check==0)
	{
		m_bAddBottomFaces = false;
	}
	else{
		m_bAddBottomFaces = true;
	}
	
}

void CRotoDraw3DDlg::OnFirstToLastCheck() 
{
	int check = m_FirstToLast.GetCheck();
	if(check==0)
	{
		m_bLastToFirstFaces = false;
	}
	else{
		m_bLastToFirstFaces = true;
	}
}

void CRotoDraw3DDlg::OnChangeEdit1() 
{
	CString s;
	m_RotoEdit.GetWindowText( s );	
	CStringA s1 = (CStringA)s.GetBuffer(s.GetLength());
	float f = (float)atof( s1.GetBuffer(s.GetLength()));
	if(is3DVisible==true)
		win3dMat->m_fCameraRotationValue = 0.017453293005625408F*f;
}

void CRotoDraw3DDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	m_iPos = doHScroll( m_hWnd, nSBCode, nPos, pScrollBar, m_iScrollMax);
	m_fScrollDist=m_iPos*0.002F;
	m_fScrollDist-=0.002F;
	CString s;
	s.Format(L"Point:  %.6f", m_fScrollDist);
	GetDlgItem( IDC_POINT_SPACE_STATIC )->SetWindowText(s);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRotoDraw3DDlg::OnExteriorFacesCheck() 
{
	
	int check = m_ExteriorFacesCheck.GetCheck();
	if(check==0)
	{
		m_bDoFrontFaces = false;
	}
	else{
		m_bDoFrontFaces = true;
	}
	
}

void CRotoDraw3DDlg::OnInteriorFacesCheck() 
{
	
	int check = m_InteriorFacesCheck.GetCheck();
	if(check==0)
	{
		m_bDoBackFaces = false;
	}
	else{
		m_bDoBackFaces = true;
	}
	
}

void CRotoDraw3DDlg::OnAxisCheck() 
{
	int check = m_AxisCheck.GetCheck();
		
	if( check==0)
	{
		m_bIsYAxis = false;
	}
	else
	{
		m_bIsYAxis = true;
	}
}

void CRotoDraw3DDlg::OnRotoHelpButton() 
{
	CPicHelpDlg* cphdlg=new CPicHelpDlg();
	cphdlg->Create(IDD_PIC_HELP_DIALOG);
	cphdlg->ShowWindow( SW_SHOW);
	cphdlg->SetPic();
}

void CRotoDraw3DDlg::OnSizeObjectButton() 
{
	
				CSetObjectSizeDlg* csosdlg = new CSetObjectSizeDlg();
				csosdlg->Create(IDD_FINAL_SIZE_DIALOG);
				csosdlg->ShowWindow( SW_SHOW);
	
}


void CRotoDraw3DDlg::OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
