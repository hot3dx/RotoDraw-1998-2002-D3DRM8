
#include "StdAfx.h"
#include "hdxpaletteio.h"
#include <stdio.h>
#include "math.h"
#include <iosfwd>
#include <istream>
#include <ostream>
#include "../../../../../../../Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include/WinCrypt.h"

using namespace std;

CWriteHDXPalette::CWriteHDXPalette()
{
	return;
}

int* CWriteHDXPalette::ConvertFloatToInt(void* a)
{
	return (int*)a;
}

void CWriteHDXPalette::WriteFourBytesAsNullString(CFile* fs, char* s)
{
	if(myFileWrite->Open(myFileWrite->GetFileName(),1,0)){
		myFileWrite->Write(s, 1);
		}
	myFileWrite->Write('\0', 1);
}

void CWriteHDXPalette::WriteBinaryFloatFourBytes(CFile* fs, float arg)
{
			int* a;

			a = ConvertFloatToInt((void*)&arg);
			int t = *a;
			int b[4];
			b[0] = (int)t << 24;
			b[0] = b[0] >> 24;


			b[1] = (int)t << 16;
			b[1] = b[1] >> 24;
			b[2] = (int)t << 8;
			b[2] = b[2] >> 24;
			b[3] = (int)t >> 24;

			char n[5];

			for (int i = 0; i < 4; i++){
				n[i] = b[i];
		    }
			// read the file and return 
			// a 5 char null terminated string
			WriteFourBytesAsNullString(fs, n);
		//test function
		//ReadBinaryFloatFourBytes(n);
}


void CWriteHDXPalette::WriteBinaryIntFourBytes(CFile* fs, int t)
{
		int b[4];
		b[0] = (int)t<<24;
		b[0] = b[0]>>24;
		

		b[1] = (int)t<<16;
		b[1] = b[1]>>24;
		b[2] = (int)t<<8;
		b[2] = b[2]>>24;
		b[3] = (int)t>>24;
        char n[5];

		for(int i=0;i<4;i++)n[i]=b[i];
			// read the file and return 
			// a 5 char null terminated string
			WriteFourBytesAsNullString(fs, n);
		//test function
		//ReadBinaryFloatFourBytes(n);
}

void CWriteHDXPalette::WriteHDXPaletteFileTxt( HDXMaterialArray arr, CString filename)
{
	HANDLE hFile = CreateFile(filename.GetBuffer(),
         GENERIC_WRITE, FILE_SHARE_READ,
         NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFile == INVALID_HANDLE_VALUE)
      AfxMessageBox(_T("Couldn't create the file!"));   
   else   
   {
      // Attach a CFile*object to the handle we have.      
	   CString paletteStr;
	   paletteStr.Format(L"%s","HOT3DX Material V358txt\n");
	   CFile myFile((HANDLE)hFile);
	   myFileWrite->Write( paletteStr, paletteStr.GetLength());
	   int n = arr.m_Count;
	   CString s;
	   s.Format(L"%d",n);
	   myFileWrite->Write(s, s.GetLength());
	   myFileWrite->Write("\r", 1);
		myFileWrite->Write("\n", 1);
      for(int i = 0; i<n; i++)
			{
				s.Format(L"%d:%s\r\n",arr.m_Mats[i].nCount,arr.m_Mats[i].matName);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%d:%d:%d:%d:\r\n",arr.m_Mats[i].r,arr.m_Mats[i].g,arr.m_Mats[i].b,arr.m_Mats[i].a);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%.6f\r\n",arr.m_Mats[i].args[0]);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%.6f:%.6f:%.6f:\r\n",arr.m_Mats[i].args[1],arr.m_Mats[i].args[2],arr.m_Mats[i].args[3]);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%.6f:%.6f:%.6f:\r\n",arr.m_Mats[i].args[4],arr.m_Mats[i].args[5],arr.m_Mats[i].args[6]);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%.6f:%.6f:%.6f:\r\n",arr.m_Mats[i].args[7],arr.m_Mats[i].args[8],arr.m_Mats[i].args[9]);
				myFileWrite->Write(s, s.GetLength());
				s.Format(L"%d:%s\r\n",arr.m_Mats[i].fCount,arr.m_Mats[i].file);
				myFileWrite->Write(s, s.GetLength());
			
			}
	  
       // We can call Close() explicitly, but the destructor would have
      // also closed the file for us. Note that there's no need to
      // call the CloseHandle() on the handle returned by the API because
      // MFC will close it for us.      
	  myFileWrite->Close();
	  }
}

void CWriteHDXPalette::WriteHDXPaletteFileBin(HDXMaterialArray arr, CString filename)
{
	HANDLE hFile = CreateFile(filename.GetBuffer(),
		GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("Couldn't create the file!"));
	}
	else
	{
		CString paletteStr;
		CFile myFile((HANDLE)hFile);

		paletteStr.Format(L"%s", "HOT3DX Material V358bin");
		myFileWrite->Write(paletteStr.GetBuffer(paletteStr.GetLength()), paletteStr.GetLength());
		WriteBinaryIntFourBytes(&myFile, arr.m_Count);
		myFileWrite->Write("\n", 1);
		for (unsigned int i = 0; i < arr.m_Count; i++)
		{
			// material name
			WriteBinaryIntFourBytes(&myFile, arr.m_Mats[i].nCount);
			myFileWrite->Write(arr.m_Mats[i].matName, arr.m_Mats[i].nCount);
			myFileWrite->Write("\n", 1);
			// rgba vals
			WriteByteAsNullString(&myFile, (char*)arr.m_Mats[i].r);
			WriteByteAsNullString(&myFile, (char*)arr.m_Mats[i].g);
			WriteByteAsNullString(&myFile, (char*)arr.m_Mats[i].b);
			WriteByteAsNullString(&myFile, (char*)arr.m_Mats[i].a);
			myFileWrite->Write("\n", 1);
			// power, emm, spec, amb
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[0]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[1]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[2]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[3]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[4]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[5]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[6]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[7]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[8]);
			WriteBinaryFloatFourBytes(&myFile, arr.m_Mats[i].args[9]);
			myFileWrite->Write("\n", 1);
			WriteBinaryIntFourBytes(&myFile, arr.m_Mats[i].fCount);
			myFileWrite->Write(arr.m_Mats[i].file, arr.m_Mats[i].fCount);
			myFileWrite->Write("\n", 1);
			myFileWrite->Write("\n", 1);
		}//eo i for
		myFileWrite->Close();
	}
	
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/////
/////
/////CReadHDXPalette
/////
/////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
CReadHDXPalette::CReadHDXPalette()
{
	return;
}

HDXMaterialArray  CReadHDXPalette::ReadHDXPaletteFileTxt( CFile* fs, HDXMaterialArray arr, CString filename )
{
	HANDLE hFile = CreateFile((CString)filename.GetBuffer(),
		GENERIC_READ, FILE_SHARE_READ,
		NULL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("Couldn't create the file!"));
	}
	else
	{
		myFile = new CFile(hFile);
		unsigned char* p = (unsigned char*)malloc(23 * sizeof(unsigned char));
		myFile->Read(p, 23);
		CString paletteStr;
		paletteStr.Format(L"%s", p);
		CStringA pa = (CStringA)paletteStr;
		arr.m_Mats->matName = pa.GetBuffer();// This is not what it is to be set to I think
		myFile->Read("\n", 1);//newline
		
	}
	return arr;
}

char* CReadHDXPalette::ReadStringNullTerminated( CFile* fs, char *s, int count)
{
	s = (char*)malloc((count)*sizeof(char));
	myFile->Read( s, count);// orig count - 1 );
	//char t = (char)myFile->Read(NULL, 1);
	//s[count]=t;
	return s;
}

HDXMaterialArray CReadHDXPalette::ReadHDXPaletteFileBin( CFile* fs, HDXMaterialArray arr, CString filename )
{
	void* lpBuffer;
	HANDLE hFile = CreateFile(filename.GetBuffer(),
		GENERIC_READ, FILE_SHARE_READ,
		NULL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("Couldn't create the file!"));
	}
	else
	{
		myFile = new CFile(hFile);
		lpBuffer = {};
		
		//filename.GetBuffer()
		// number of materials
		myFile->Read(lpBuffer, 1);
		unsigned int n = (unsigned int)ReadFourBytesInteger(fs);

		myFile->Read(NULL, 1);// newline
		for (unsigned int i = 0; i < n; i++)
		{

			HDXMaterial m;
			int mn = ReadFourBytesInteger(fs);
			m.nCount = mn;
			m.matName = ReadStringNullTerminated(fs, m.matName, mn + 1);
			//myFile->Read(NULL, 1);//null
			m.r = ReadByteAsNullString(fs);
			m.g = ReadByteAsNullString(fs);
			m.b = ReadByteAsNullString(fs);
			m.a = ReadByteAsNullString(fs);

			myFile->Read(NULL, 1);//newline

			// get power, emm, spec, amb
			m.args[0] = ReadBinaryFloatFourBytes();
			m.args[1] = ReadBinaryFloatFourBytes();
			m.args[2] = ReadBinaryFloatFourBytes();
			m.args[3] = ReadBinaryFloatFourBytes();
			m.args[4] = ReadBinaryFloatFourBytes();
			m.args[5] = ReadBinaryFloatFourBytes();
			m.args[6] = ReadBinaryFloatFourBytes();
			m.args[7] = ReadBinaryFloatFourBytes();
			m.args[8] = ReadBinaryFloatFourBytes();
			m.args[9] = ReadBinaryFloatFourBytes();
			myFile->Read(NULL, 1);//newline

			// read texture file name
			int fn = ReadFourBytesInteger(fs);
			m.fCount = fn;

			m.file = ReadStringNullTerminated(fs, m.file, fn + 1);
			myFile->Read(NULL, 1);//newline

			arr.m_Mats = arr.Grow(m);
		}

	}
	return arr;
}
HDXMaterialArray CReadHDXPalette::ReadHeaderInitStream( HDXMaterialArray arr, CString filename )
{
	CFile f;
	void* lpBuffer = filename.GetBuffer();
	CFile* fs = new CFile(filename, f.bufferRead | f.modeRead , 0);
	myFile->Read(lpBuffer, filename.GetLength() );
	char *p = (char*)malloc(22*sizeof(char));
	myFile->Read( p, 22 );
	CString s;s.Format(L"\n  %send\n",p);
	//OutputDebugString(s);
	if(NULL!=strstr(p,"HOT3DX Material V358b"))
	{
		
		arr = ReadHDXPaletteFileBin( fs, arr, filename.GetBuffer() );
		
	}
	else if(p[20]=='t')
	{
		
		myFile->Read(filename.GetBuffer(), filename.GetLength());
		arr = ReadHDXPaletteFileTxt( fs, arr, filename.GetBuffer());
	}
	
	return arr;
}
BYTE CReadHDXPalette::ReadByteAsNullString(CFile* fs)
{
	BYTE a = (BYTE)myFile->Read(NULL, 1);
	myFile->Read(NULL, 1);//Null terminator
	return a;
}

void CReadHDXPalette::ReadFourBytesAsNullString(CFile*  fs, char *s)
{
	//change to signed char 0 to 255
	/*
	for(int i=0;i<5;i++)
	{
		if(myFile->good()){
		myFile->get(s[i]);
		if(s[i]=='\n')myFile->get(s[i]);
		
		}
	}
	*/	//s[4]='\0';
}	

int CReadHDXPalette::ReadFourBytesInteger(CFile* fs )
{
	char pch[5];// strings are followed by 0 terminators
	ReadFourBytesAsNullString( fs, pch);
	
	return ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
}
char* CReadHDXPalette::ReadFourBytesAddTerminator(CFile* fs, char* s)
{
	//change to signed char 0 to 255
	char c[5] = {};
	
	for(int i=0;i<4;i++)
	{
		//if(myFile->good()){
		//myFile->get(s[i]);
		//if(s[i]=='\n')myFile->get(s[i]);
		c[i] = s[i];
	}
     CString t = (CString)s;
	t.Format(L"\n%s", s);//
	OutputDebugString(t);
	//myFile->Read(NULL, 1);
	
		return s;
}	

float CReadHDXPalette::afloat( unsigned int a)
{
	return (float)a;
}
float CReadHDXPalette::ReadBinaryFloatFourBytes()
{
		
	char* n = {};
			// read the file and return 
			// a 5 char null terminated string
			n = ReadFourBytesAddTerminator(myFile, n);
			CString fv;
		
		int b[4];
		// switch the string to ints
		for (int i = 0; i < 4; i++) { b[i] = n[i]; }
		
		unsigned int integerArg= (b[0])|(b[1]<<8)|(b[2]<<16)|(b[3]<<24);
		
		int sign=integerArg>>31;//get the sign	
		unsigned int mantissa = 0;
			mantissa= integerArg<<9;mantissa>>=9;// get the mantissa
		unsigned int exponent = integerArg<<1;exponent>>=24;// get the exponent
			exponent-=127; // subtract bias
		double floatArg = (double)mantissa;  // convert mantissa to float
			floatArg = floatArg*pow(2,-23); // shift the float -23;
			//1's and 0's
			
			if(floatArg<=pow(2.2250738585072014, -308)||floatArg>=pow(1.7976931348623158, 308))
			{
				//OutputDebugString("foundit");
				floatArg=0.0;		
				unsigned int integer= (b[0])+(b[1]<<8)+(b[2]<<16)+(b[3]<<24);
		
		
		    unsigned int mant = 0;
			mant= integer<<9;mant>>=9;// get the mantissa
		    signed int exp = integer<<1;exp>>=24;// get the exponent
			exp-=127; // subtract bias
			floatArg = (double)mant;  // convert mantissa to float
			floatArg = floatArg*pow(2,-23); // shift the float -23;
			floatArg+=1.0F; // add the leading 1
			floatArg= floatArg*pow(2, exp); // calculate the float

			if(sign==1)floatArg=-floatArg; // set the sign
			//fv.Format(L"\n %.6f,", floatArg);
			//OutputDebugString( fv.GetBuffer(50));
			return (float)floatArg;
			}
			
			floatArg+=1.0; // add the leading 1
			double delta = pow((double)2, (double)exponent);
			floatArg = floatArg* delta;//(float) // calculate the float

		if(sign==1)floatArg*=-1;//floatArg; // set the sign

		//Type Minimum value Maximum value 
/////////float 1.175494351 E – 38 3.402823466 E + 38 
/////////double 2.2250738585072014 E – 308 1.7976931348623158 E + 308 
		//if(floatArg<=pow(2.2250738585072014, -308))||
		if(	floatArg>=pow(1.7976931348623158, 308))
			{
				//OutputDebugString("foundit2");
				floatArg=0.0;		
				unsigned int integer= (b[0])+(b[1]<<8)+(b[2]<<16)+(b[3]<<24);
		
		
		unsigned int mant = 0;
			mant= integer<<9;mant>>=9;// get the mantissa
		signed int exp = integer<<1;exp>>=24;// get the exponent
			exp-=127; // subtract bias
			 floatArg = (double)mant;  // convert mantissa to float
			floatArg = floatArg*pow(2,-23); // shift the float -23;
			floatArg+=1.0F; // add the leading 1
			floatArg= floatArg*pow(2, exp); // calculate the float

			if(sign==1)floatArg=-floatArg; // set the sign
			//fv.Format(L"\n %.6f,", floatArg);
			//OutputDebugString( fv.GetBuffer(50));
			return (float)floatArg;
			}
			
		fv.Format(L"\n %.6f,", floatArg);
		if(strstr((CStringA)fv.GetBuffer(50),"-1.#INF00"))
		{
			floatArg=0.0;		
				unsigned int integer= (b[0])+(b[1]<<8)+(b[2]<<16)+(b[3]<<24);
		
		
		unsigned int mant = 0;
			mant= integer<<9;mant>>=9;// get the mantissa
		signed int exp = integer<<1;exp>>=24;// get the exponent
			exp-=127; // subtract bias
			 floatArg = (double)mant;  // convert mantissa to float
			floatArg = floatArg*pow(2,-23); // shift the float -23;
			floatArg+=1.0F; // add the leading 1
			floatArg= floatArg*pow(2, exp); // calculate the float

			if(sign==1)floatArg=-floatArg; // set the sign
		}
		//if(floatArg< -40000000000000000000000000000000000000.000000)floatArg=0.0F;
		//OutputDebugString( fv.GetBuffer(50));
		
	return (float)floatArg;
}