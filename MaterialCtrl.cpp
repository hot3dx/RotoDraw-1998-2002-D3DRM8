// MaterialCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MakerC1.h"
#include "MakerC1Dlg.h"
#include "MaterialCtrl.h"
#include "ClipTexture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterialCtrl dialog


CMaterialCtrl::CMaterialCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaterialCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialCtrl)
	DDX_Control(pDX, IDC_FRONTMAT_EDIT, m_FrontMatEdit);
	DDX_Control(pDX, IDC_BACKMAT_EDIT, m_BackMatEdit);
	DDX_Control(pDX, IDC_MATERIAL_LIST, m_MaterialList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialCtrl, CDialog)
	//{{AFX_MSG_MAP(CMaterialCtrl)
	ON_BN_CLICKED(IDC_BAC_FACE_BUTTON, OnBacFaceButton)
	ON_BN_CLICKED(IDC_FRONT_FACE_BUTTON, OnFrontFaceButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialCtrl message handlers

void CMaterialCtrl::OnBacFaceButton() 
{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
		POSITION t = m_MaterialList.GetFirstSelectedItemPosition();
		
		//arg->m_GroupListSelectedIndex
		unsigned int i = (unsigned int)t-1;
		arg->backRed   = (float)arg->m_MatArray.m_Mats[i].r/255;
		arg->backGreen = (float)arg->m_MatArray.m_Mats[i].g/255;
		arg->backBlue  = (float)arg->m_MatArray.m_Mats[i].b/255;
		arg->backAlpha = (float)arg->m_MatArray.m_Mats[i].a/255;
		arg->selMatBack=i;
		arg->textureFillMode = FDIFFTEXTURES;
		arg->selTexBackPath = arg->m_MatArray.m_Mats[i].file;
		CString s;
		s.Format("%d",i);
		m_BackMatEdit.SetWindowText(s);

		CStatic* miniwin = (CStatic*)arg->GetDlgItem( IDC_BACK_FACE_STATIC );
		int bpp = GetDeviceCaps( GetDC()->m_hDC, BITSPIXEL );
		MyTexture* mytex = new MyTexture( miniwin, bpp);

			DWORD sz = (128*128*(bpp/8));
			BYTE *bits = (BYTE*)malloc(sz*sizeof(BYTE));
			mytex->m_BackGroundTexture->GetBitmapBits(sz, bits );
			mytex->SetScreenColorBits(bpp, 128,128,arg->m_MatArray.m_Mats[i].r, arg->m_MatArray.m_Mats[i].g, arg->m_MatArray.m_Mats[i].b, bits);
			mytex->m_BackGroundTexture->SetBitmapBits( sz, bits);
			miniwin->SetBitmap( (HBITMAP)*mytex->m_BackGroundTexture);
			free(bits);

		if(arg->m_MatArray.m_Mats[i].file>0)
		{
			if(arg->m_MatArray.m_Mats[i].fCount>5)
			{
				HBITMAP bmp = (HBITMAP)LoadImage( AfxGetInstanceHandle(), arg->m_MatArray.m_Mats[i].file, IMAGE_BITMAP, 48, 48, LR_LOADFROMFILE);
				miniwin->SetBitmap( bmp );
			}
		}
}

void CMaterialCtrl::OnFrontFaceButton() 
{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
		POSITION t = m_MaterialList.GetFirstSelectedItemPosition();
		
		//arg->m_GroupListSelectedIndex
		unsigned int i = (unsigned int)t-1;	
		arg->frontRed   = (float)arg->m_MatArray.m_Mats[i].r/255;
		arg->frontGreen = (float)arg->m_MatArray.m_Mats[i].g/255;
		arg->frontBlue  = (float)arg->m_MatArray.m_Mats[i].b/255;
		arg->frontAlpha = (float)arg->m_MatArray.m_Mats[i].a/255;
		arg->selMatFront=i;
		arg->textureFillMode = FSAMETEXTURES;
		arg->selTexFrontPath = arg->m_MatArray.m_Mats[i].file;
		CString s;
		s.Format("%d",i);
		m_FrontMatEdit.SetWindowText(s);

		CStatic* miniwin = (CStatic*)arg->GetDlgItem( IDC_FRONT_FACE_STATIC );
		int bpp = GetDeviceCaps( GetDC()->m_hDC, BITSPIXEL );
		MyTexture* mytex = new MyTexture( miniwin, bpp);

			DWORD sz = (128*128*(bpp/8));
			BYTE *bits = (BYTE*)malloc(sz*sizeof(BYTE));
			mytex->m_BackGroundTexture->GetBitmapBits(sz, bits );
			mytex->SetScreenColorBits(bpp, 128,128,arg->m_MatArray.m_Mats[i].r, arg->m_MatArray.m_Mats[i].g, arg->m_MatArray.m_Mats[i].b, bits);
			mytex->m_BackGroundTexture->SetBitmapBits( sz, bits);
			miniwin->SetBitmap( (HBITMAP)*mytex->m_BackGroundTexture);
			free(bits);
		if(arg->m_MatArray.m_Mats[i].file>0)
		{
			if(arg->m_MatArray.m_Mats[i].fCount>5)
			{
				HBITMAP bmp = (HBITMAP)LoadImage( AfxGetInstanceHandle(), arg->m_MatArray.m_Mats[i].file, IMAGE_BITMAP, 48, 48, LR_LOADFROMFILE);
				miniwin->SetBitmap( bmp );
			}
		}
}

void CMaterialCtrl::OnClearButton() 
{
	CMakerC1Dlg* arg=(CMakerC1Dlg*)GetParent()->GetParent();
	arg->selMatBack=-1;
	arg->textureFillMode = FSAMETEXTURES;
	m_BackMatEdit.SetWindowText("");
}
