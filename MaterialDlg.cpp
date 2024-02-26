// MaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RotoDraw3D.h"
#include "RotoDraw3DDlg.h"
#include "MaterialDlg.h"
#include "3dpic.h"
#include <commdlg.h>
#include "resource.h"
#include "hdxpaletteio.h"
#include "MaterialDlgHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDialog* m_MaterialDlg;
CPoint m_matMousePoint;
int sizeBytes;
HRESULT d3result;


/////////////////////////////////////////////////////////////////////////////
// CMaterialDlg dialog


CMaterialDlg::CMaterialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialDlg)
	//}}AFX_DATA_INIT
}


void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialDlg)
	DDX_Control(pDX, IDC_CURRENT_MATERIAL_EDIT, m_CurrentMatEdit);
	DDX_Control(pDX, IDC_NUM_MATERIALS_EDIT, m_NumMaterialsEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialog)
	//{{AFX_MSG_MAP(CMaterialDlg)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_LBN_SELCHANGE(IDC_MATERIAL_LISTDLG, OnSelchangeMaterialListdlg)
	ON_WM_SIZE()
	ON_LBN_KILLFOCUS(IDC_MATERIAL_LISTDLG, OnKillfocusMaterialListdlg)
	ON_BN_CLICKED(COLOR_LUMSCROLL, OnLumscroll)
	ON_EN_CHANGE(COLOR_HUE, OnChangeHue)
	ON_BN_CLICKED(IDC_TEXTURE_FILENAME_BUTTON, OnTextureFilenameButton)
	ON_BN_CLICKED(COLOR_MAPPIXELS, OnMappixels)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CREATE_BUTTON, OnCreateButton)
	//ON_BN_CLICKED(IDC_SET_COLOR_BUTTON, OnSetColorButton)
	//ON_BN_CLICKED(IDC_ADD_PALETTE_BUTTON, OnAddPaletteButton)
	ON_BN_CLICKED(IDC_ADD_MATERIAL_BUTTON, OnAddMaterialButton)
	ON_BN_CLICKED(IDC_SET_MATERIAL_BUTTON, OnSetMaterialButton)
	ON_BN_CLICKED(COLOR_ADD, OnDeleteMaterial)
	ON_BN_CLICKED(IDC_ADD_DELETEMATERIAL_BUTTON, OnDeleteMaterialButton)
	ON_BN_CLICKED(IDC_NAME_SET_BUTTON, OnNameSetButton)
	ON_BN_CLICKED(IDC_CLEAR_TEXTURE_FILENAME_BUTTON, OnClearTextureFilenameButton)
	ON_BN_CLICKED(IDC_SAVE_PALETTE_BUTTON2, OnSavePaletteButton2)
	ON_BN_CLICKED(IDC_OPEN_PALETTE_BUTTON, OnOpenPaletteButton)
	ON_BN_CLICKED(IDC_MAT_DLG_HELP_BUTTON, OnMatHelpButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialDlg message handlers

BOOL CMaterialDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_MaterialDlg = this;
	
	m_bInit=true;
	int bpp = GetDeviceCaps( GetDC()->m_hDC, BITSPIXEL );
	
	sizeBytes = 0;
	if(bpp==24){sizeBytes = 3;}
	else if(bpp==32){sizeBytes = 4;}
	
	sv1=0;sv2=0;sv3=0;sv4=0;sv5=0;sv6=0;sv7=0;
	CRotoDraw3DDlg* maker =  (CRotoDraw3DDlg*)GetParent();
	for(unsigned int i = 0;i<maker->m_MatArray.m_Count;i++)
	{
		m_TMats.m_Mats = m_TMats.Grow(maker->m_MatArray.m_Mats[i]);
	}
	POSITION t = 0;//maker->cfpgdlg->matCtrl->m_MaterialList.GetFirstSelectedItemPosition();
	int n = (int)t-1;
	m_MatIndex= n;

	CString s;
	s.Format(L"%d", m_TMats.m_Count);
	m_NumMaterialsEdit.SetWindowText(s);
	vScroll1 = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_SCROLLBAR1);
	vScroll2 = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_SCROLLBAR2);
	vScroll8 = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_SCROLLBAR8);
	vScroll9 = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_SCROLLBAR9);
	vScroll10 = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_SCROLLBAR10);
	hSlider = ( CScrollBar*)m_MaterialDlg->GetDlgItem(IDC_CURRENT_MATERIAL_SCROLL);
	vScroll1->EnableScrollBar(ESB_ENABLE_BOTH);
	vScroll2->EnableScrollBar(ESB_ENABLE_BOTH);
	vScroll8->EnableScrollBar(ESB_ENABLE_BOTH);
	vScroll9->EnableScrollBar(ESB_ENABLE_BOTH);
	vScroll10->EnableScrollBar(ESB_ENABLE_BOTH);
	hSlider->EnableScrollBar(ESB_ENABLE_BOTH);
	vScroll1->SetScrollRange(0, 255, TRUE);
	vScroll2->SetScrollRange(0, 255, TRUE);
	vScroll8->SetScrollRange(0, 255, TRUE);
	vScroll9->SetScrollRange(0, 255, TRUE);
	vScroll10->SetScrollRange(0, 255, TRUE);
	hSlider->SetScrollRange(0, m_TMats.m_Count-1, TRUE);
	hSlider->SetScrollPos( m_MatIndex, TRUE);
	SetColorMapPixels(sizeBytes);
	SetColorLumScroll(sizeBytes);
	colorValList = ( CListBox*)m_MaterialDlg->GetDlgItem( IDC_MATERIAL_LISTDLG );
	if(t==0)
	{
		colorValList->AddString(L"default");//name
		colorValList->AddString(L"1.000000");//alpha
		colorValList->AddString(L"1.000000");//power
		colorValList->AddString(L"0.000000");//sred
		colorValList->AddString(L"0.000000");//sg
		colorValList->AddString(L"0.000000");//sb
		colorValList->AddString(L"0.000000");//emmr
		colorValList->AddString(L"0.000000");//emmg
		colorValList->AddString(L"0.000000");//emmb
		colorValList->AddString(L"0.000000");//ar
		colorValList->AddString(L"0.000000");//ag
		colorValList->AddString(L"0.000000");//amb
		colorValList->AddString(L"none");//texture file name
		colorValList->SetHorizontalExtent(500);
		m_Mat.r=255;m_Mat.g=0;m_Mat.b=0;m_Mat.a=255;
		m_Mat.args[0] = 1.0F;
		m_Mat.args[1] = 0.0F;
		m_Mat.args[2] = 0.0F;
		m_Mat.args[3] = 0.0F;
		m_Mat.args[4] = 0.0F;
		m_Mat.args[5] = 0.0F;
		m_Mat.args[6] = 0.0F;
		m_Mat.args[7] = 0.0F;
		m_Mat.args[8] = 0.0F;
		m_Mat.args[9] = 0.0F;
		m_Mat.nCount=8;
		m_Mat.matName=(char*)malloc(8*sizeof(char));
		m_Mat.matName= "default\0";
		m_Mat.fCount=5;
		m_Mat.file=(char*)malloc(5*sizeof(char));
		m_Mat.file= "none\0";
	}//eo if(t==0)
	else
	{
		int nPos = n;
		CString s;
				s.Format(L"%s",m_TMats.m_Mats[nPos].matName);
			colorValList->AddString(s);//name
				s.Format(L"%.6f",((float)m_TMats.m_Mats[nPos].a/255));
			colorValList->AddString(s);//alpha
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[0]);
			colorValList->AddString(s);//power
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[1]);
			colorValList->AddString(s);//sred
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[2]);
			colorValList->AddString(s);//sg
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[3]);
			colorValList->AddString(s);//sb
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[4]);
			colorValList->AddString(s);//emmr
				s.Format(L"%.6fL",m_TMats.m_Mats[nPos].args[5]);
			colorValList->AddString(s);//emmg
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[6]);
			colorValList->AddString(s);//emmb
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[7]);
			colorValList->AddString(s);//ar
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[8]);
			colorValList->AddString(s);//ag
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[9]);
			colorValList->AddString(s);//amb
				s.Format(L"%s",m_TMats.m_Mats[nPos].file);
			colorValList->AddString(s);//texture file name
			colorValList->SetHorizontalExtent(500);

			m_Mat.r=m_TMats.m_Mats[nPos].r;
			m_Mat.g=m_TMats.m_Mats[nPos].g;
			m_Mat.b=m_TMats.m_Mats[nPos].b;
			m_Mat.a=m_TMats.m_Mats[nPos].a;
			m_Mat.args[0] = m_TMats.m_Mats[nPos].args[0];
			m_Mat.args[1] = m_TMats.m_Mats[nPos].args[1];
			m_Mat.args[2] = m_TMats.m_Mats[nPos].args[2];
			m_Mat.args[3] = m_TMats.m_Mats[nPos].args[3];
			m_Mat.args[4] = m_TMats.m_Mats[nPos].args[4];
			m_Mat.args[5] = m_TMats.m_Mats[nPos].args[5];
			m_Mat.args[6] = m_TMats.m_Mats[nPos].args[6];
			m_Mat.args[7] = m_TMats.m_Mats[nPos].args[7];
			m_Mat.args[8] = m_TMats.m_Mats[nPos].args[8];
			m_Mat.args[9] = m_TMats.m_Mats[nPos].args[9];
			m_Mat.nCount=m_TMats.m_Mats[nPos].nCount;
			m_Mat.matName=(char*)malloc(m_TMats.m_Mats[nPos].nCount*sizeof(char));
			m_Mat.matName= m_TMats.m_Mats[nPos].matName;
			m_Mat.fCount=m_TMats.m_Mats[nPos].fCount;
			m_Mat.file=(char*)malloc(m_TMats.m_Mats[nPos].fCount*sizeof(char));
			m_Mat.file= m_TMats.m_Mats[nPos].file;
	}//eo if(t==0)
	SetD3DMaterialWin();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CMaterialDlg::OnMove(int x, int y) 
{
	CRotoDraw3DDlg* maker = (CRotoDraw3DDlg*)GetParent();
	maker->win3dMat->WinRender();
	CDialog::OnMove(x, y);
	maker->win3dMat->WinRender();
	
	
}

void CMaterialDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_bInit==true)
	{
		
		m_bInit=false;
		
		win3d->m_SceneObjects->m_camera->DeleteChild(win3d->m_SceneObjects->gridFrame);
		if( FAILED( win3d->GetD3DRM()->CreateFrame( win3d->m_scene, &win3d->win_frame ) ) )
		{
		MessageBox(  L" cube mesh failed ", L" error ", MB_OK );
	goto generic_error;
	
	}

	if( FAILED( win3d->GetD3DRM()->CreateMeshBuilder( &win3d->acube ) ) )
		{
		MessageBox(  L" cube mesh failed ", L" error ", MB_OK );
	goto generic_error;
	
	}
	if( !win3d->build_cube1(win3d->acube ) )
		{
		MessageBox(  L" scene color failed ", L" error ", MB_OK );
	goto generic_error;
	
	}
	else{
		LPDIRECT3DRMMATERIAL2 m2;
		win3d->GetD3DRM()->CreateMaterial( 1.0F, &m2);
			win3d->acube->SetName("cube1_builder");
		D3DCOLOR c5 = RGBA_MAKE(255, 255, 255, 255);
		win3d->acube->SetMaterial(m2);
		win3d->acube->SetColor(c5);
		LPDIRECT3DRMFACE2 fac;
		win3d->acube->GetFace(0, &fac);
		fac->SetMaterial(m2);
		win3d->m_scene->SetSceneBackground(RGBA_MAKE(255, 255, 0, 255));
		m2->Release();
		fac->Release();
	}

	if( FAILED( win3d->win_frame->AddVisual( (LPDIRECT3DRMVISUAL)	win3d->acube ) ) )
		{
		MessageBox( L" scene color failed ", L" error ", MB_OK );
	goto generic_error;
	}
	
	win3d->win_frame->SetPosition( win3d->m_scene, -9.0F, 9.0F, 0.0F );
	win3d->m_SceneObjects->m_camera->SetPosition( win3d->m_scene, 0.0F, 0.0F, -35.75F );
	generic_error:
	//MessageBox( NULL, L" eo createscene ", L"  error ", MB_OK );
    //Msg("A failure occurred while creating the scene.\n");
//ret_with_error:
    
  
    WINRELEASE(win3d->m_SceneObjects->win_mat);
	}
	
}

void CMaterialDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRotoDraw3DDlg* maker = (CRotoDraw3DDlg*)GetParent();
	maker->win3dMat->WinRender();
	
}


void CMaterialDlg::OnSelchangeMaterialListdlg() 
{
	m_MatListIndex = colorValList->GetCurSel();
	int nCount = colorValList->GetCount();
	if ((m_MatListIndex != LB_ERR) && (nCount > 1))
	{   
		if (++m_MatListIndex < nCount)
			colorValList->SetCurSel(m_MatListIndex-1);
		else      
			colorValList->SetCurSel(0);
	}
	
}


void CMaterialDlg::OnKillfocusMaterialListdlg() 
{
	// TODO: Add your control notification handler code here
	
}

void CMaterialDlg::OnLumscroll() 
{
	
}

void CMaterialDlg::OnChangeHue() 
{
	
}

void CMaterialDlg::OnTextureFilenameButton() 
{
	//for palette files
	LPCTSTR filter = L"Windows Bitmap Files (*.bmp)|*.bmp|ZSoft Files (*.pcx)|*.pcx|PaintBrush Files (*.ppm)|*.ppm||";
	CFileDialog ofn( TRUE, L".bmp", NULL, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter);
	if(IDOK ==ofn.DoModal())
	{
		CStringA s = (CStringA)ofn.GetFileName().GetBuffer();// gets just file with ext
		LPCTSTR p = ofn.GetPathName();// gets path and file
		colorValList->InsertString(12, p);
		colorValList->DeleteString(13);
		LPDIRECT3DRMTEXTURE3 tex;
		LPDIRECT3DRM lpD3DRM1;
		LPDIRECT3DRM3 rm;
	
		Direct3DRMCreate(&lpD3DRM1);
		const char* pc = s.GetBuffer();
		lpD3DRM1->QueryInterface( IID_IDirect3DRM3, (LPVOID*)&rm);
		rm->LoadTexture(pc, &tex);
		m_Mat.fCount= s.GetLength()+1;
		m_Mat.file=(char*)malloc( m_Mat.fCount*sizeof(char));
		
		for( int i=0;i<s.GetLength();i++)
		{
			m_Mat.file[i]=s.GetAt(i);
		}
		m_Mat.file[s.GetLength()]='\0';
		win3d->acube->SetTexture(tex);
		WINRELEASE( lpD3DRM1 );
		WINRELEASE( rm );
		WINRELEASE( tex );
	}
	
}

void CMaterialDlg::OnOK() 
{
	CRotoDraw3DDlg* maker = (CRotoDraw3DDlg*)GetParent();
	//maker->cfpgdlg->matCtrl->m_MaterialList.DeleteAllItems();
	maker->m_MatArray.Allocate(0);
	CString s;

	if(m_TMats.m_Count>0){
	for(unsigned int i=0;i<m_TMats.m_Count;i++)
	{
		s.Format(L"%d", i);
		/*
		maker->cfpgdlg->matCtrl->m_MaterialList.InsertItem( i, s);
		s.Format(L"%s", m_TMats.m_Mats[i].matName);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 1, s);
		s.Format(L"%d", m_TMats.m_Mats[i].r);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 2, s);
		s.Format(L"%d", m_TMats.m_Mats[i].g);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 3, s);
		s.Format(L"%d", m_TMats.m_Mats[i].b);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 4, s);
		s.Format(L"%d", m_TMats.m_Mats[i].a);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 5, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[0]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 6, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[1]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 7, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[2]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 8, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[3]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 9, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[4]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 10, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[5]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 11, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[6]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 12, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[7]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 13, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[8]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 14, s);
		s.Format(L"%.6f", m_TMats.m_Mats[i].args[9]);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 15, s);
		s.Format(L"%s", m_TMats.m_Mats[i].file);
		maker->cfpgdlg->matCtrl->m_MaterialList.SetItemText( i, 16, s);
		*/
		maker->m_MatArray.m_Mats=maker->m_MatArray.Grow(m_TMats.m_Mats[i]);
		maker->m_MatCount++;
	
	}//eoifor
		if(FALSE==m_CurrentPalletFileName.IsEmpty())
		{
			CWriteHDXPalette pal;
			pal.WriteHDXPaletteFileBin( maker->m_MatArray, m_CurrentPalletFileName);
		}
	}//eoif
	// next four lines of code refresh 3d win in maker
	
	maker->PostMessage( WM_SYSCOMMAND,0,0);
	maker->PostMessage( WM_CAPTURECHANGED,0,0);
	maker->PostMessage( WM_WINDOWPOSCHANGING,0,0);
	maker->win3dMat->WinRender();	
	win3d->m_iDone=TRUE;
	CDialog::OnOK();
}

void CMaterialDlg::OnCancel() 
{
	
	if ( AfxMessageBox(L"Are you sure you want to cancel the changes?", 
         MB_YESNO) == IDNO )
	{
		 return; 
	}
	else
		{
		
		CRotoDraw3DDlg* maker = (CRotoDraw3DDlg*)GetParent();
		maker->PostMessage( WM_SYSCOMMAND,0,0);
		maker->PostMessage( WM_CAPTURECHANGED,0,0);
		maker->PostMessage( WM_WINDOWPOSCHANGING,0,0);
		maker->win3dMat->WinRender();
	win3d->m_iDone=TRUE;	
	
	
	}
	
	CDialog::OnCancel();
	
}
void CMaterialDlg::SetColorMapPixels(int sizeBytes)
{
	rainbows =  ( CStatic*)m_MaterialDlg->GetDlgItem(COLOR_MAPPIXELS);//COLOR_RAINBOW);
	rainbows->ModifyStyle(SS_SIMPLE, SS_SUNKEN|SS_BITMAP);
	
	CRect* rect = new CRect();
	rainbows->GetWindowRect( rect );
	int w, h;
	w = rect->Width();//189
	h = rect->Height();//177 188?
	int hsize = w*h*sizeBytes;
	CClientDC dc(rainbows);
	
	CDC dcMem;

	BYTE *bits = (BYTE*)malloc((hsize)*sizeof(BYTE));
	memset(bits, 0, hsize);

   
	    CBitmap* cbm = new CBitmap();
		dcMem.CreateCompatibleDC(&dc);
		cbm->CreateCompatibleBitmap(&dc, w, h);
		ASSERT(cbm->m_hObject != NULL);
		
	BYTE red =255;
	BYTE green = 255;
	BYTE blue = 255;
	BYTE r,g,b;
	
	int rx,gx,bx,step,var;
	step = 1;
	var = 31;
	
	int rxl,rxg,gxl,gxg,bxl,bxg,ccnt,zeroval;
	rxl=31;rxg=155;
	gxl=31;gxg=95;
	bxl=95;bxg=155;
	ccnt=0;
	zeroval=0;
	 int p = 0;		
    for(int y=0;y<h;y++)
	{
		red=275-var;green=275-var;blue=275-var;
			var++;
			if(y>10)zeroval++;
			if(var>=61){var=61;}
		if(ccnt==6)
		{
			ccnt=0;
			rxg--;rxl++;
			gxl--;gxg++;
			bxl--;bxg++;
		}else{ccnt++;}
		//r=red;g=green;b=blue;
		for(int x=0;x<w;x++)
		{
			rx=x;bx=x;gx=x;

			if(rx<rxl){r=(red--) -step;}
			else if(rx>rxg){r=(red++) +step;}
			else if(rx>=rxl&&rx<=rxg){r=zeroval;}

			if(gx<gxl){g=zeroval;}
			else if(gx>=gxl&&gx<62){g=(green++)+step;}
			else if(gx>=62&&gx<gxg){g=(green--)-step;}
			else if(gx>=gxg){g=zeroval;}

			if(bx<bxl){b=zeroval;}
			else if(bx>=bxl&&bx<124){b=(blue++)+step;}
			else if(bx>=124&&bx<=bxg){b=(blue--)-step;}
			else if(bx>bxg){b=zeroval;}
			
			COLORREF c = RGB(r,g,b);
			bits[p]= GetBValue(c);
			bits[p+1]= GetGValue(c);
			bits[p+2]= GetRValue(c);
			if(sizeBytes == 4)
			{
				bits[p+3]= 255;
				p+=4;
			}
			else{p+=3;}
			
			}//eoforx
		}//eofory
		
	cbm->SetBitmapBits( hsize, bits);
	
	rainbows->SetBitmap((HBITMAP) *cbm );
	
	free(bits);


}

void CMaterialDlg::SetColorLumScroll(int sizeBytes)
{
	lumeRainbow =  ( CStatic*)m_MaterialDlg->GetDlgItem(COLOR_LUMSCROLL);
	lumeRainbow->ModifyStyle(SS_SIMPLE, SS_SUNKEN|SS_BITMAP);
	CRect* lrect = new CRect();
	lumeRainbow->GetWindowRect( lrect );
	int lw, lh;
	lw = lrect->Width();//8
	lh = lrect->Height();//116
	int lhsize = lw*lh*sizeBytes;
	CClientDC ldc(lumeRainbow);
	CDC ldcMem;

	BYTE *lbits = (BYTE*)malloc((lhsize)*sizeof(BYTE));
	memset(lbits, 0, lhsize);
   
	    CBitmap* cbml = new CBitmap();
		ldcMem.CreateCompatibleDC(&ldc);
		cbml->CreateCompatibleBitmap(&ldc, lw, lh);
		ASSERT(cbml->m_hObject != NULL);
	int lr,lg,lb;
	int lp = 0;
	int lh2 = lh/2;
	lr = GetRValue(selectedColor);
	lg = GetGValue(selectedColor);
	lb = GetBValue(selectedColor);
	int rpp,gpp,bpp;
	rpp = 5;gpp = 5;bpp = 5;
	int pos = (lh2)*sizeBytes*lw;
	pos-=1;
	for(int ly=lh2;ly>0;ly--)
	{
		lr+=rpp;lg+=gpp;lb+=bpp;
		if(lr>255)lr=255;if(lg>255)lg=255;if(lb>255)lb=255;
		for(int lx=0;lx<lw;lx++)
		{
			COLORREF lc = RGB( lr, lg, lb);
			lbits[pos]= GetRValue(lc);
			pos--;
			lbits[pos]= GetGValue(lc);
			pos--;
			lbits[pos]= GetBValue(lc);
			pos--;
			if(sizeBytes == 4)
			{
				lbits[lp+3]=255;
				lp+=4;
				pos--;
			}
			else{lp+=3;}
			
		}//eoforx
		//pos-=sizeBytes;
	}//eofory
	lr = GetRValue(selectedColor);
	lg = GetGValue(selectedColor);
	lb = GetBValue(selectedColor);
	
	for(int ly=lh;ly>lh2;ly--)
	{
		lr-=rpp;lg-=gpp;lb-=bpp;
		if(lr<0)lr=0;if(lg<0)lg=0;if(lb<0)lb=0;
		for(int lx=0;lx<lw;lx++)
		{
			COLORREF lc = RGB( lr, lg, lb);
			lbits[lp]= GetBValue(lc);
			lbits[lp+1]= GetGValue(lc);
			lbits[lp+2]= GetRValue(lc);
			if(sizeBytes == 4)
			{
				lbits[lp+3]=255;
				lp+=4;
			}
			else{lp+=3;}
		}//eoforx
	}//eofory
	lr = GetRValue(selectedColor);
	lg = GetGValue(selectedColor);
	lb = GetBValue(selectedColor);

	cbml->SetBitmapBits( lhsize, lbits);
	lumeRainbow->SetBitmap((HBITMAP) *cbml );
	free(lbits);

}

void CMaterialDlg::SetColorCurrent(int sizeBytes)
{
	colorCurrent =  ( CStatic*)m_MaterialDlg->GetDlgItem(COLOR_CURRENT);
	colorCurrent->ModifyStyle(SS_SIMPLE, SS_SUNKEN|SS_BITMAP);
	CRect* lrect = new CRect();
	colorCurrent->GetWindowRect( lrect );
	int lw, lh;
	lw = lrect->Width()-2;//8
	lh = lrect->Height()-2;//116
	int lhsize = lw*lh*sizeBytes;
	CClientDC ldc(colorCurrent);
	CDC ldcMem;

	BYTE *lbits = (BYTE*)malloc((lhsize)*sizeof(BYTE));
	memset(lbits, 0, lhsize);
   
	    CBitmap* cbml = new CBitmap();
		ldcMem.CreateCompatibleDC(&ldc);
		cbml->CreateCompatibleBitmap(&ldc, lw, lh);
		ASSERT(cbml->m_hObject != NULL);
	
	int lp = 0;		
    for(int ly=0;ly<lh;ly++)
	{
		for(int lx=0;lx<lw;lx++)
		{
			lbits[lp]= GetBValue(selectedColor);
			lbits[lp+1]= GetGValue(selectedColor);
			lbits[lp+2]= GetRValue(selectedColor);
			if(sizeBytes == 4)
			{
				lbits[lp+3]=255;
				lp+=4;
			}
			else{lp+=3;}
		}//eoforx
		}//eofory
	cbml->SetBitmapBits( lhsize, lbits);
	colorCurrent->SetBitmap((HBITMAP) *cbml );
	free(lbits);
	
}

void CMaterialDlg::OnMappixels() 
{
	
}
static BOOL MapRainbow(CPoint point)
{
	BOOL t= FALSE;
	if(((point.x>224)&&(point.x<412))){
	if((point.y>16)&&(point.y<212))
	{
		t = TRUE;
	}}
	return t;
}

char * GetFrameName(LPDIRECT3DRMFRAME3 fr, char *nameBuf)
{
	unsigned long bufLen;
	
	fr->GetName( &bufLen, NULL  );
	//
	char isz[10];
	_itoa_s(bufLen, isz, 10);
	nameBuf = (char*)malloc(bufLen*sizeof(char));
	memset(nameBuf, 0, bufLen);
	
	fr->GetName( &bufLen, nameBuf  );
	return nameBuf;

}

static BOOL MapLumScroll(CPoint point)
{
	BOOL t= FALSE;
	if(((point.x>420)&&(point.x<430))){
	if((point.y>16)&&(point.y<212))
	{
		t = TRUE;
	}}
	return t;
}

void CMaterialDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_matMousePoint = point;
	
	BOOL Rain = MapRainbow(point);
	BOOL Lume = MapLumScroll(point);
	if((Rain==TRUE)||(Lume==TRUE))
	{
	COLORREF c = 
		GetDC()->GetPixel(point.x, point.y);
	
	GetDlgItem(COLOR_RED)->SetWindowText(std::to_wstring(GetRValue(c)).c_str());
	vScroll8->SetScrollPos(GetRValue(c),TRUE);
		m_Mat.r=GetRValue(c);
	GetDlgItem(COLOR_GREEN)->SetWindowText(std::to_wstring(GetGValue(c)).c_str());
	vScroll9->SetScrollPos(GetGValue(c),TRUE);
		m_Mat.g=GetGValue(c);
	GetDlgItem(COLOR_BLUE)->SetWindowText(std::to_wstring(GetBValue(c)).c_str());
	vScroll10->SetScrollPos(GetBValue(c),TRUE);
		m_Mat.b=GetBValue(c);
	GetDlgItem(COLOR_HUE)->SetWindowText(std::to_wstring(GetHue(c)).c_str());
	GetDlgItem(COLOR_SAT)->SetWindowText(std::to_wstring(GetSaturation(c)).c_str());
	GetDlgItem(COLOR_LUM)->SetWindowText(std::to_wstring(GetBrightness(c)).c_str());

	selectedColor=c;
	if(Lume==FALSE){
	SetColorLumScroll(sizeBytes);
	}
	SetColorCurrent(sizeBytes);
	COLORREF c1 = RGB(GetBValue(c), GetGValue(c), GetRValue(c));
	int r2 =  GetRValue(c);
	int g2 =  GetGValue(c);
	int b2 =  GetBValue(c);
	int a2 =255;
	//char alpha[10];
	LPWSTR alpha = {};
	
	//CString f = std::to_wstring(a2).c_str();
	win3d->m_mat_rgba = RGBA_MAKE( r2, g2, b2, a2 );
		GetDlgItem(714)->GetWindowText(alpha, 10);
		CString f = alpha;
	if((f.GetLength())!=0){
		a2 = atoi((CStringA)f.GetBuffer());
		RGBA_SETALPHA(win3d->m_mat_rgba, a2);
	}
	if(win3d->win3dSetFlag==true)
	{
	if(!win3d->acube){MessageBox(L"no mesh", L"color set failure", MB_OK);}
	else{win3d->acube->SetColor( win3d->m_mat_rgba );}
	}//eo if(win3dSetFlag==true)
	}//eo if((Rain==TRUE)||(Lume==TRUE))

	CDialog::OnLButtonDown(nFlags, point);
}

void CMaterialDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_matMousePoint = point;
	
	BOOL Rain = MapRainbow(point);
	BOOL Lume = MapLumScroll(point);
	if((Rain==TRUE)||(Lume==TRUE))
	{
	COLORREF c = 
		GetDC()->GetPixel(point.x, point.y);
	GetDlgItem(COLOR_RED)->SetWindowText(std::to_wstring(GetRValue(c)).c_str());
	vScroll8->SetScrollPos(GetRValue(c), TRUE);
	m_Mat.r = GetRValue(c);
	GetDlgItem(COLOR_GREEN)->SetWindowText(std::to_wstring(GetGValue(c)).c_str());
	vScroll9->SetScrollPos(GetGValue(c), TRUE);
	m_Mat.g = GetGValue(c);
	GetDlgItem(COLOR_BLUE)->SetWindowText(std::to_wstring(GetBValue(c)).c_str());
	vScroll10->SetScrollPos(GetBValue(c), TRUE);
	m_Mat.b = GetBValue(c);
	GetDlgItem(COLOR_HUE)->SetWindowText(std::to_wstring(GetHue(c)).c_str());
	GetDlgItem(COLOR_SAT)->SetWindowText(std::to_wstring(GetSaturation(c)).c_str());
	GetDlgItem(COLOR_LUM)->SetWindowText(std::to_wstring(GetBrightness(c)).c_str());

	selectedColor=c;
	if(Lume==FALSE){
	SetColorLumScroll(sizeBytes);
	}
	SetColorCurrent(sizeBytes);
	COLORREF c1 = RGB(GetBValue(c), GetGValue(c), GetRValue(c));
	int r2 =  GetRValue(c);
	int g2 =  GetGValue(c);
	int b2 =  GetBValue(c);
	int a2 =255;
	LPWSTR alpha = {};

	//CString f = std::to_wstring(a2).c_str();
	win3d->m_mat_rgba = RGBA_MAKE(r2, g2, b2, a2);
	GetDlgItem(714)->GetWindowText(alpha, 10);
	CString f = alpha;
	if ((f.GetLength()) != 0) {
		a2 = atoi((CStringA)f.GetBuffer());
		RGBA_SETALPHA(win3d->m_mat_rgba, a2);
	}
	if(win3d->win3dSetFlag==true)
	{
	if(!win3d->acube){MessageBox(L"no mesh", L"color set failure", MB_OK);}
	else{win3d->acube->SetColor( win3d->m_mat_rgba );}
	}//eo if(win3dSetFlag==true)
	}//eo if((Rain==TRUE)||(Lume==TRUE))
	
	CDialog::OnRButtonDown(nFlags, point);
}

int CMaterialDlg::GetBrightness(COLORREF c)
    {
        float f = (float)GetRValue(c) / 255.0F;
        float f1 = (float)GetGValue(c) / 255.0F;
        float f2 = (float)GetBValue(c) / 255.0F;
        float f3 = f;
        float f4 = f;
        if(f1 > f3)
            f3 = f1;
        if(f2 > f3)
            f3 = f2;
        if(f1 < f4)
            f4 = f1;
        if(f2 < f4)
            f4 = f2;
		float cf = ((f3 + f4) / 2.0F)*1000.0F;
		int ci = (int)cf;
        return ci;
    }

int CMaterialDlg::GetSaturation(COLORREF c)
    {
        float f = (float)GetRValue(c) / 255.0F;
        float f1 = (float)GetGValue(c) / 255.0F;
        float f2 = (float)GetBValue(c) / 255.0F;
        float f6 = 0.0F;
        float f3 = f;
        float f4 = f;
        if(f1 > f3)
            f3 = f1;
        if(f2 > f3)
            f3 = f2;
        if(f1 < f4)
            f4 = f1;
        if(f2 < f4)
            f4 = f2;
        if(f3 != f4)
        {
            float f5 = (f3 + f4) / 2.0F;
            if((double)f5 <= 0.5)
                f6 = (f3 - f4) / (f3 + f4);
            else
                f6 = (f3 - f4) / (2.0F - f3 - f4);
        }
		f6*=1000.0F;
        return (int)f6;
    }

int CMaterialDlg::GetHue(COLORREF c)
    {
        float f = (float)GetRValue(c) / 255.0F;
        float f1 = (float)GetGValue(c) / 255.0F;
        float f2 = (float)GetBValue(c) / 255.0F;
        float f6 = 0.0F;
        float f3 = f;
        float f4 = f;
        if(f1 > f3)
            f3 = f1;
        if(f2 > f3)
            f3 = f2;
        if(f1 < f4)
            f4 = f1;
        if(f2 < f4)
            f4 = f2;
        float f5 = f3 - f4;
        if(f == f3)
            f6 = (f1 - f2) / f5;
        else
        if(f1 == f3)
            f6 = 2.0F + (f2 - f) / f5;
        else
        if(f2 == f3)
            f6 = 4.0F + (f - f1) / f5;
        f6 *= 60.0F;
        if(f6 < 0.0F)
            f6 += 360.0F;
		f*=1000.0F;
        return (int)f6;
    }
HWND hWnd;
void CMaterialDlg::SetD3DMaterialWin()
{
	
	winD3DMaterialWin = (CStatic*)m_MaterialDlg->GetDlgItem(IDC_D3DMATERIAL_DISPLAY);
	//winD3DMaterialWin->ModifyStyle(SS_SIMPLE, SS_SUNKEN);//|SS_BITMAP);
		
}

void CMaterialDlg::Set3dbutton() 
{
	win3d = new CWin3D();
	SetCWin3D( *win3d );
	win3d->m_bMain_3d_Window = false;
	win3d->win3dSetFlag = false;
	if(win3d->win3dSetFlag==false)
	{
		win3d->win3dSetFlag=true;
	
	winD3DMaterialWin->m_hWnd = m_MaterialDlg->GetDlgItem(IDC_D3DMATERIAL_DISPLAY)->m_hWnd;
	hWnd = winD3DMaterialWin->m_hWnd;
	win3d->m_hWnd = hWnd;
	d3result = win3d->Win3DInit( hWnd );

	
	}

}
afx_msg int doVScroll(HWND, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar, int max);

void CMaterialDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int lpMinPos;
	int lpMaxPos;
	pScrollBar->GetScrollRange( &lpMinPos, &lpMaxPos );
	int tn = doVScroll( pScrollBar->m_hWnd, nSBCode, nPos, pScrollBar, lpMaxPos);
	nPos=tn;
	if(nPos<0)nPos=0;
		if(pScrollBar==hSlider)
		{
			m_MatIndex=tn;
			if(m_TMats.m_Count>0)
			{
			CString s;
				s.Format(L"%s",m_TMats.m_Mats[nPos].matName);
			colorValList->InsertString( 0, s );
			colorValList->DeleteString( 1);
				s.Format(L"%.6f",((float)m_TMats.m_Mats[nPos].a/255));
			colorValList->InsertString( 1, s );//alpha
			colorValList->DeleteString( 2);
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[0]);
			colorValList->InsertString( 2, s );
			colorValList->DeleteString( 3);//power
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[1]);
			colorValList->InsertString( 3, s );
			colorValList->DeleteString( 4);//sred
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[2]);
			colorValList->InsertString( 4, s );
			colorValList->DeleteString( 5);//sg
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[3]);
			colorValList->InsertString( 5, s );
			colorValList->DeleteString( 6);//sb
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[4]);
			colorValList->InsertString( 6, s );
			colorValList->DeleteString( 7);//emmr
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[5]);
			colorValList->InsertString( 7, s );
			colorValList->DeleteString( 8);//emmg
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[6]);
			colorValList->InsertString( 8, s );
			colorValList->DeleteString( 9);//emmb
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[7]);
			colorValList->InsertString( 9, s );
			colorValList->DeleteString( 10);//ar
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[8]);
			colorValList->InsertString( 10, s );
			colorValList->DeleteString( 11);//ag
				s.Format(L"%.6f",m_TMats.m_Mats[nPos].args[9]);
			colorValList->InsertString( 11, s );
			colorValList->DeleteString( 12);//amb
				s.Format(L"%s",m_TMats.m_Mats[nPos].file);
			colorValList->InsertString( 12, s );
			colorValList->DeleteString( 13);//texture file name
			
			m_Mat.r=m_TMats.m_Mats[nPos].r;
			m_Mat.g=m_TMats.m_Mats[nPos].g;
			m_Mat.b=m_TMats.m_Mats[nPos].b;
			m_Mat.a=m_TMats.m_Mats[nPos].a;
			m_Mat.args[0] = m_TMats.m_Mats[nPos].args[0];
			m_Mat.args[1] = m_TMats.m_Mats[nPos].args[1];
			m_Mat.args[2] = m_TMats.m_Mats[nPos].args[2];
			m_Mat.args[3] = m_TMats.m_Mats[nPos].args[3];
			m_Mat.args[4] = m_TMats.m_Mats[nPos].args[4];
			m_Mat.args[5] = m_TMats.m_Mats[nPos].args[5];
			m_Mat.args[6] = m_TMats.m_Mats[nPos].args[6];
			m_Mat.args[7] = m_TMats.m_Mats[nPos].args[7];
			m_Mat.args[8] = m_TMats.m_Mats[nPos].args[8];
			m_Mat.args[9] = m_TMats.m_Mats[nPos].args[9];
			m_Mat.nCount=m_TMats.m_Mats[nPos].nCount;
			m_Mat.matName=(char*)malloc(m_TMats.m_Mats[nPos].nCount*sizeof(char));
			m_Mat.matName= m_TMats.m_Mats[nPos].matName;
			m_Mat.fCount=m_TMats.m_Mats[nPos].fCount;
			m_Mat.file=(char*)malloc(m_TMats.m_Mats[nPos].fCount*sizeof(char));
			m_Mat.file= m_TMats.m_Mats[nPos].file;
			s.Format(L"%d", nPos+1);
			GetDlgItem( IDC_CURRENT_MATERIAL_EDIT)->SetWindowText(s);
			win3d->m_mat_rgba = RGBA_MAKE( m_Mat.r, m_Mat.g, m_Mat.b, m_Mat.a );
			win3d->acube->SetColor( win3d->m_mat_rgba );
			LPDIRECT3DRMMATERIAL2 mat = m_TMats.CreateHDXMaterial( win3d->GetD3DRM(), m_MatIndex);
			win3d->acube->SetMaterial(mat);
			if(m_Mat.fCount>5)
			{
				LPDIRECT3DRMTEXTURE3 tex=m_TMats.CreateHDXTextue( win3d->GetD3DRM(), m_MatIndex);
				win3d->acube->SetTexture(tex);
			}
			}//eo if(m_TMats.m_Count>0)
			if( pScrollBar == vScroll8)
			{
				m_Mat.r = (BYTE)nPos;
				win3d->acube->SetColor(RGBA_MAKE(m_Mat.r, m_Mat.g, m_Mat.b, m_Mat.a));
				win3d->WinRender();
			}
			if( pScrollBar == vScroll9)
			{
				m_Mat.g = (BYTE)nPos;
				win3d->acube->SetColor(RGBA_MAKE(m_Mat.r, m_Mat.g, m_Mat.b, m_Mat.a));
				win3d->WinRender();
			}
			if( pScrollBar == vScroll10)
			{
				m_Mat.b = (BYTE)nPos;
				win3d->acube->SetColor(RGBA_MAKE(m_Mat.r, m_Mat.g, m_Mat.b, m_Mat.a));
				win3d->WinRender();
			}
		}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int doVScroll (HWND hw, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar, int max)
{
	ASSERT( pScrollBar != NULL);
	int nCurPos = pScrollBar->GetScrollPos();
	//MessageBox(NULL, L"Clicked", L"ScrollBar", MB_OK);
	switch (nSBCode)
	{
	case SB_LEFT: //    Scroll to far left.
		nCurPos--;
		break;
	case SB_LINELEFT: //    Scroll left.
		nCurPos--;
		break;
	case SB_LINERIGHT: //    Scroll right.
		nCurPos++;
		break;
	case SB_PAGELEFT: //    Scroll one page left.
		nCurPos--;
		break;
	case SB_PAGERIGHT: //    Scroll one page right.
		nCurPos++;
		break;
	case SB_RIGHT: //    Scroll to far right.
		nCurPos++;
		break;
	case SB_THUMBPOSITION:
		nCurPos = nPos;
		break;
	case SB_THUMBTRACK:
		nCurPos = nPos;
		break;
	}
	
	//if (nCurPos < 1)
	//	nCurPos = 1;
	if (nCurPos > max)
		nCurPos = max;
	if (nCurPos < 0)
		nCurPos = 0;
		
	pScrollBar->SetScrollPos( nCurPos, TRUE);
	
	pScrollBar->UpdateWindow();
	return nCurPos;
}


void CMaterialDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int lpMinPos;
	int lpMaxPos;
	pScrollBar->GetScrollRange( &lpMinPos, &lpMaxPos ); 
	doVScroll( pScrollBar->m_hWnd, nSBCode, nPos, pScrollBar, lpMaxPos);
	float pos = (float)pScrollBar->GetScrollPos();
	CString s;
	
	LPDIRECT3DRMMATERIAL2 mat;
	LPDIRECT3DRMFACE2 fac;
	win3d->acube->GetFace( 0, &fac);
	fac->GetMaterial(&mat);
	fac->SetColor(win3d->m_mat_rgba);
	if(pScrollBar==vScroll1)
	{
		sv1=pos/1;
		CString t;
		colorValList->GetText( 2, t );
		sv1 = (float)atof((CStringA) t.GetBuffer() );
		s.Format(L"%.6f", sv1);
		colorValList->InsertString( 2, s );
		colorValList->DeleteString( 3);
			m_Mat.args[0]=sv1;
		mat->SetPower( sv1 );
		win3d->acube->SetMaterial( mat);
		win3d->acube->SetColor(win3d->m_mat_rgba);

		win3d->WinRender();
	}
	else if(pScrollBar==vScroll2)sv2=pos/255;
		
	float num = sv2;
	s.Format(L"%.6f", num);
	
	if(m_MatListIndex == 2)
	{
		colorValList->InsertString( 1, s );
		colorValList->DeleteString( 2);

		COLORREF c = RGBA_MAKE( GetRValue(win3d->m_mat_rgba), GetGValue(win3d->m_mat_rgba), GetBValue(win3d->m_mat_rgba), (int)pos);
			m_Mat.a=(BYTE)pos;
		win3d->m_mat_rgba=c;
		win3d->acube->SetColor( win3d->m_mat_rgba);
		win3d->WinRender();
	}
	if(m_MatListIndex == 4)
	{
		colorValList->InsertString( 3, s );
		colorValList->DeleteString( 4);

		CString g,b;
		colorValList->GetText( 4, g );
		colorValList->GetText( 5, b );

		mat->SetSpecular( num, (float)atof( (CStringA)g ), (float)atof((CStringA)b ) );
			m_Mat.args[1]=num;
		win3d->acube->SetMaterial( mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 5)
	{
		colorValList->InsertString( 4, s );
		colorValList->DeleteString( 5);

		CString g,b;
		colorValList->GetText( 4, g );
		colorValList->GetText( 6, b );

		mat->SetSpecular( (float)atof((CStringA)g ), num, (float)atof((CStringA)b ) );
			m_Mat.args[2]=num;
		win3d->acube->SetMaterial( mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 6)
	{
		colorValList->InsertString( 5, s );
		colorValList->DeleteString( 6);

		CString g,b;
		colorValList->GetText( 4, g );
		colorValList->GetText( 5, b );

		mat->SetSpecular( (float)atof((CStringA)g ), (float)atof((CStringA)b ), num );
			m_Mat.args[3]=num;
		win3d->acube->SetMaterial( mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 7)
	{
		colorValList->InsertString( 6, s );
		colorValList->DeleteString( 7);

		CString g,b;
		colorValList->GetText( 7, g );
		colorValList->GetText( 8, b );

		mat->SetEmissive( num, (float)atof((CStringA)g ), (float)atof((CStringA)b ) );
			m_Mat.args[4]=num;
		win3d->acube->SetMaterial( mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 8)
	{
		colorValList->InsertString( 7, s );
		colorValList->DeleteString( 8);

		CString g,b;
		colorValList->GetText( 6, g );
		colorValList->GetText( 8, b );

		mat->SetEmissive( (float)atof((CStringA)g ), num, (float)atof((CStringA)b ) );
			m_Mat.args[5]=num;
		win3d->acube->SetMaterial(mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 9)
	{
		colorValList->InsertString( 8, s );
		colorValList->DeleteString( 9);
		CString g,b;
		colorValList->GetText( 6, g );
		colorValList->GetText( 7, b );

		mat->SetEmissive( (float)atof((CStringA)g ), (float)atof((CStringA)b ), num );
			m_Mat.args[6]=num;
		win3d->acube->SetMaterial(mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 10)
	{
		colorValList->InsertString( 9, s );
		colorValList->DeleteString( 10);

		CString g,b;
		colorValList->GetText( 11, g );
		colorValList->GetText( 12, b );

		mat->SetAmbient( num, (float)atof((CStringA)g ), (float)atof((CStringA)b ) );
			m_Mat.args[7]=num;
		win3d->acube->SetMaterial(mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 11)
	{
		colorValList->InsertString( 10, s );
		colorValList->DeleteString( 11);

		CString g,b;
		colorValList->GetText( 10, g );
		colorValList->GetText( 12, b );

		mat->SetAmbient( (float)atof((CStringA)g ), num, (float)atof((CStringA)b ) );
			m_Mat.args[8]=num;
		win3d->acube->SetMaterial(mat);
		win3d->WinRender();
	}
	else if(m_MatListIndex == 12)
	{
		colorValList->InsertString( 11, s );
		colorValList->DeleteString( 12);

		CString g,b;
		colorValList->GetText( 10, g );
		colorValList->GetText( 11, b );

		mat->SetAmbient( (float)atof((CStringA)g ), (float)atof((CStringA)b ), 9 );
			m_Mat.args[9]=num;
		win3d->acube->SetMaterial(mat);
		win3d->WinRender();
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMaterialDlg::OnClose() 
{
	CDialog::OnClose();
}

BOOL CMaterialDlg::DestroyWindow() 
{
	win3d->Close();
	delete win3d;
	delete this;
	return CDialog::DestroyWindow();
	return TRUE;	
	
}

void CMaterialDlg::OnCreateButton() 
{
	LPCTSTR filter = L"Hot3DX Palette Files (*.xmf)|*.xmf||"; 
	//CFileDialog ofn( TRUE, "*.xmf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Hot3DX Palette Files (*.xmf)\0*.xmf\0""All Files (*.*)\0*.*\0");
	CFileDialog ofn( TRUE, L".xmf", NULL, NULL, filter);
	if(IDOK ==ofn.DoModal())
	{
		CString s = ofn.GetFileName();// gets just file with ext
		m_CurrentPalletFileName.Format(L"%s",ofn.GetPathName());// gets path and file
		GetDlgItem(IDC_PALETTE_FILE_NAME_EDIT)->SetWindowText(m_CurrentPalletFileName);
		

	}
		win3d->WinRender();
}

void CMaterialDlg::OnSetColorButton() 
{
	m_TMats.m_Mats[ m_MatIndex].r =GetRValue(selectedColor);
	m_TMats.m_Mats[ m_MatIndex].g =GetGValue(selectedColor);
	m_TMats.m_Mats[ m_MatIndex].b =GetBValue(selectedColor);
	CString s;
	CStringA s1 = (CStringA)s.GetBuffer();
	GetDlgItem(714)->GetWindowText(s);
	int a=atoi( s1.GetBuffer(s1.GetLength()));
	m_TMats.m_Mats[ m_MatIndex].a =a;
	
}

void CMaterialDlg::OnAddPaletteButton() 
{
	
	
}

void CMaterialDlg::OnAddMaterialButton() 
{

	m_TMats.m_Mats = m_TMats.Grow( m_Mat );
	hSlider->SetScrollRange( 0, m_TMats.m_Count-1, TRUE );
	hSlider->SetScrollPos( m_TMats.m_Count-1, TRUE );
	m_MatIndex = m_TMats.m_Count-1;
	CString s;
	s.Format(L"%d", m_TMats.m_Count);
	GetDlgItem( IDC_NUM_MATERIALS_EDIT )->SetWindowText(s);

}

void CMaterialDlg::OnSetMaterialButton() 
{
	m_TMats.Set( m_MatIndex, m_Mat );
	
}
// COLORADD
void CMaterialDlg::OnDeleteMaterial() 
{
		
}

void CMaterialDlg::OnDeleteMaterialButton() 
{
	m_TMats.m_Mats=m_TMats.Shrink(m_MatIndex);
	
}

void CMaterialDlg::OnNameSetButton() 
{
	CString s;
	GetDlgItem(IDC_NAME_SET_EDIT)->GetWindowText( s);
	colorValList->InsertString( 0, s );
	colorValList->DeleteString( 1);
	m_Mat.nCount=s.GetLength()+1;
	m_Mat.matName=(char*)malloc( m_Mat.nCount*sizeof(char));
	for( int i=0;i<s.GetLength();i++)
	{
		m_Mat.matName[i] = (char)s.GetAt(i);
	}
	m_Mat.matName[s.GetLength()]='\0';
}

void CMaterialDlg::OnClearTextureFilenameButton() 
{
	win3d->win_frame->DeleteVisual(win3d->acube);
	win3d->GetD3DRM()->CreateFrame( win3d->m_scene, &win3d->win_frame);
	if( FAILED( win3d->GetD3DRM()->CreateMeshBuilder( &win3d->acube ) ) )
		{
		MessageBox(  L" cube mesh failed ", L" error ", MB_OK );
	goto generic_error;
	
	}
	if( !win3d->build_cube1(win3d->acube ) )
		{
		MessageBox(  L" scene color failed ", L" error ", MB_OK );
	goto generic_error;
	
	}
	else{
		LPDIRECT3DRMMATERIAL2 m2;
		win3d->GetD3DRM()->CreateMaterial( 1.0F, &m2);
			win3d->acube->SetName("cube1_builder");
		D3DCOLOR c5 = RGBA_MAKE(255, 255, 255, 255);
		win3d->acube->SetMaterial(m2);
		win3d->acube->SetColor(c5);
		LPDIRECT3DRMFACE2 fac;
		win3d->acube->GetFace(0, &fac);
		fac->SetMaterial(m2);
		win3d->m_scene->SetSceneBackground(RGBA_MAKE(255, 255, 0, 255));
		m2->Release();
		fac->Release();
	}

	if( FAILED( win3d->win_frame->AddVisual( (LPDIRECT3DRMVISUAL)	win3d->acube ) ) )
		{
		MessageBox( L" scene color failed ", L" error ", MB_OK );
	goto generic_error;
	}
	
	win3d->win_frame->SetPosition( win3d->m_scene, -9.0F, 9.0F, 0.0F );
	//win3d->m_SceneObjects->m_camera->SetPosition( win3d->m_scene, 0.0F, 0.0F, -35.75F );
	generic_error:
	//MessageBox( NULL, L" eo createscene ", L"  error ", MB_OK );
    //Msg("A failure occurred while creating the scene.\n");
//ret_with_error:
	WINRELEASE(win3d->m_SceneObjects->win_mat);

	m_Mat.fCount=5;
	m_Mat.file=(char*)malloc(5*sizeof(char));
	m_Mat.file= "none\0";
    colorValList->InsertString( 12, L"none\0L");
	colorValList->DeleteString( 13 );
	win3d->WinRender();
	
}

void CMaterialDlg::OnSavePaletteButton2() 
{
	if(FALSE==m_CurrentPalletFileName.IsEmpty())
		{
		CRotoDraw3DDlg* maker = (CRotoDraw3DDlg*)GetParent();
			CWriteHDXPalette pal;
			pal.WriteHDXPaletteFileBin( maker->m_MatArray, m_CurrentPalletFileName);
			MessageBox( L"Palette Saved", m_CurrentPalletFileName, MB_OK);
		}
	else{
		MessageBox( L"Before a palette can be saved, you must have pressed the <Create Palette> button and entered a save name", L"File Name Error", MB_OK);
	}
	
}

void CMaterialDlg::OnOpenPaletteButton() 
{
	LPCTSTR filter = L"Hot3DX Palette Files (*.xmf)|*.xmf||"; 
	CFileDialog ofn( TRUE, L".xmf", NULL, NULL, filter);
	if(IDOK ==ofn.DoModal())
	{
		CString s = ofn.GetFileName();// gets just file with ext
		m_CurrentPalletFileName.Format(L"%s",ofn.GetPathName());// gets path and file
		GetDlgItem(IDC_PALETTE_FILE_NAME_EDIT)->SetWindowText(m_CurrentPalletFileName);
		
		CReadHDXPalette pal;
		//m_TMats.DeAllocate();
		//m_TMats.Allocate(0);
		m_TMats.DeAllocate();
		m_TMats.m_Count = 0;
		
		m_TMats = pal.ReadHeaderInitStream( m_TMats, m_CurrentPalletFileName );
		if(m_TMats.m_Count>0)
		{
			s.Format(L"%d", m_TMats.m_Count);
			m_NumMaterialsEdit.SetWindowText(s);

			hSlider->SetScrollRange( 0, m_TMats.m_Count-1, TRUE);
			hSlider->SetScrollPos(1, TRUE);
		
			m_Mat = m_TMats.m_Mats[1];
		}
	
	}
		win3d->WinRender();
	
}

void CMaterialDlg::OnMatHelpButton() 
{
	MaterialDlgHelp cmdhdlg;
	cmdhdlg.DoModal();
}