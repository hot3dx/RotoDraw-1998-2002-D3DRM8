#include "readdirectx.h"
#include "xfiledefines.h"
#include <math.h>

FILEVARS::FILEVARS(){return;}
CReadDirectXFile::CReadDirectXFile()
{
	m_TMeshPoints.x.deallocate();
	m_TMeshPoints.y.deallocate();
	m_TMeshPoints.z.deallocate();
	m_TMeshPoints.x.allocate(0);
	m_TMeshPoints.y.allocate(0);
	m_TMeshPoints.z.allocate(0);
	m_TMeshPoints.m_iNumPoints=0;
	m_TMatArray.Allocate(0);
	return;
}



int CReadDirectXFile:: fsGet(void)
{
	CString s;
	if((linepos+1)>linecount)
	{
		linepos =0;
		fst.seekg(fpos);
			fst.getline( line, 256, '\n');
			linecount = fst.gcount();
				fpos+=linecount;
				s.Format("\n\tNEWLINE 0302:  lc: %d lp: %d fp: %d ch: %d\n\n",linecount,linepos,fpos,line[linepos]);
//				OutputDebugString(s);
			
	}

	//s.Format("\nlc: %d lp: %d fp: %d ch: %d",linecount,linepos,fpos,line[linepos]);
	//OutputDebugString(s);
	linepos++;
	readCount++;
	return line[linepos-1];
}



void  CReadDirectXFile::fsRead( unsigned char *arg, int count)
{
	int i = 0;
	while(i<count)
		arg[i++] = fsGet();
}

void  CReadDirectXFile::fsRead( signed char *arg, int count)
{
	int i = 0;
	while(i<count)
		arg[i++] = fsGet();
}

void  CReadDirectXFile::fsRead( char *arg, int count)
{
	int i = 0;
	while(i<count)
		arg[i++] = fsGet();
}



void CReadDirectXFile::ReadTokenTerminator(ifstream fs)
{
	
	if(fs.good())
	{
		char ch=fsGet();
		
	}
}


DWORD CReadDirectXFile::GetDWORDCount(ifstream fs, unsigned char *pch)
{
	DWORD val= ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	return val;
}

void CReadDirectXFile::ReadTwoBytesAsNullString(ifstream  fs, unsigned char *s)
{
	//change to signed char 0 to 255
	
	for(int i=0;i<2;i++)
	{
		if(fs.good()){
		s[i]=fsGet();
		}
	}
		s[3]='\0';
}

void CReadDirectXFile::ReadFourBytesNullString(ifstream  fs, unsigned char *s)
{
	//change to signed char 0 to 255
	
	for(int i=0;i<5;i++)
	{
		if(fs.good()){
		s[i]=fsGet();
		}
	}
}	
void CReadDirectXFile::ReadEightBytesAsNullString(ifstream  fs, unsigned char *s)
{
	//change to signed char 0 to 255
	for(int i=0;i<8;i++)
	{
		if(fs.good()){
			s[i]=fsGet();
			}
	}
		s[8]='\0';
}	

unsigned char * CReadDirectXFile::ReadFourBytesAddTerminator(ifstream  fs)
{
	//change to signed char 0 to 255
	static unsigned char s[5];
	
	for(int i=0;i<4;i++)
	{
		if(fs.good())
		{
		s[i]=fsGet();
		
		}
	}
		s[4]='\0';
		//CString t;t.Format("\nfloat bytes  %d   %d  %d  %d  %d", s[0], s[1], s[2], s[3], s[4]);
		//OutputDebugString(t);
		return s;
}	
float CReadDirectXFile::afloat( unsigned int a)
{
	return (float)a;
}

///////////////////////////////////////////////////////////////////
////////////  Read .x binary
///////////////////////////////////////////////////////////////////

char * CReadDirectXFile::GetHeader(ifstream fs)
{
	fpos=0;
	static char header[17];
	for(int i =0;i<16;i++)
	{
		char ch;
		fs.get(ch);
		header[i]=ch;
	}
	header[16]='\0';
	fpos+=16;
	GetFloatBits1(header);
	GetXFileType(header);
	GetVersion2(header);
	GetVersion1(header);
	GetMagic(header);
	
	return header;
}

char * CReadDirectXFile::GetMagic(char *  pch)
{
	static char t[4];
	for(int i=0;i<3;i++)
	{
		t[i]=pch[i];
	}
	t[3]='\0';

	return t;
}

char *  CReadDirectXFile::GetVersion1(char *  pch)
{
	static char t[3];
	for(int i=4;i<6;i++)
	{
		t[i-4]=pch[i];
	}
	t[2]='\0';
	return t;
}

char *  CReadDirectXFile::GetVersion2(char *  pch)
{
	static char t[3];
	for(int i=6;i<8;i++)
	{
		t[i-6]=pch[i];
	}
	t[2]='\0';

	return t;
}

char * CReadDirectXFile::GetXFileType(char *  pch)
{
	static char t[4];
	for(int i=8;i<11;i++)
	{
		t[i-8]=pch[i];
	}
	t[3]='\0';

	return t;
}

char * CReadDirectXFile::GetFloatBits1(char *  pch)
{
	static char t[3];
	for(int i=14;i<16;i++)
	{
		t[i-14]=pch[i];
	}
	t[2]='\0';

	return t;
}



float * CReadDirectXFile::GetRealNumbersFloat4(ifstream fs, int listCount, float *floats, char *s)
{
	floats = (float*)malloc(listCount*sizeof(float));
	// output
	
	for(int i=0;i<listCount;i++)
	{
		*(floats+i) = ReadBinaryFloatFourBytes(fs);	
	}
	
	return floats;
	
}

char * CReadDirectXFile::FloatToStringNull(float floatArg, int precision)
{
	static char final[32];
		int fdec, fsign;
		int flen, decimal;
		int frontpad=0;
				
		char *sfloat = fcvt( floatArg, precision, &fdec, &fsign);
		if(fdec<-10)
		{
			strcpy(final, "0.000000");
		}
		else{
		if(fsign == 1)
		{
			strcpy(final, "-");
		}
		else
		{
			strcpy(final, "\0");
		}

		if(fdec==0)
			{
				strcat(final, "0.");
				strcat(final, sfloat);
				frontpad=1;
			}//eoif
		else
		{
			flen = strlen(sfloat);
			decimal = fdec;
			
			for(int i=0;i<flen;i++)
			{
				if(i==decimal){strcat(final, ".");}
				else
				{
				char t[2];
				t[0]=sfloat[i];
				t[1]='\0';
			    strcat(final, t);
				}
			}//eofor
		}//eoelse
		
		const unsigned int pad = frontpad+fsign+decimal+6;
		char t[2];
		t[0]='0';
		t[1]='\0';
		for(int j=pad;j<flen+1;j++)
		{
			strcat(final, t);
		}
		}
		return final;
}

char * CReadDirectXFile::GetDotXNameCount(ifstream fs)
{
	ReadTokenTerminator(fs);
	unsigned char pch[5];
	int nCount=4;
	
	ReadFourBytesNullString( fs, pch);
	int val= ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	char *namestr;
	if(val<256)
	{
		namestr = (char*)malloc((val+1)*sizeof(char));
		if(namestr==NULL)
		{
		nCount=val;
	
		for(int i=0;i<nCount;i++)
		{
			if(fs.good())
			{
				char ch=fsGet();
				namestr[i]=ch;
				
			}
		}
	namestr[i]='\0';
	}}
	return namestr;
}
int CReadDirectXFile::ReadDotXFileBinaryCount( char *m_sOpenFileName )
{
	ifstream fs(m_sOpenFileName, ios::binary);
	int count = 0;
	int nCount = 0;	
		if(fs)
		{
			CString s;
			OutputDebugString("\nBegin ");
			fs.seekg( 0 );
			while(fs.good())
			{
				char ch;
				fs.get( ch );
				count++;
			}
		}
		else{
			count = 0;
			MessageBox(NULL, "File could not be opened", "File Access Error", MB_OK);
		}

	fs.close();
	return count;
	
}

int CReadDirectXFile::ReadDotXBinaryFile( char *m_sOpenFileName, int count )
{
	FILEVARS xfileVars;
	
	ifstream fstrm(m_sOpenFileName, ios::binary);		
		if(fstrm)
		{
	streampos u = fstrm.tellg();
		fst = fstrm;
		linecount = 0;
		linepos = 0;
		readCount=0;
		fpos=u;
	xfileVars.filePlaceTracker =0;
	char *header = GetHeader( fstrm);
		m_magic = GetMagic( header);
		m_version1 = GetVersion1( header );
		m_version2 = GetVersion2( header );
			mesh0302Flag=false;
			mesh0303Flag=false;
			if(strstr(m_version2,"02"))
			{
				mesh0302Flag=true;
			}
			else if(strstr(m_version2,"03"))
			{
				mesh0303Flag=true;
			}

		m_fileType = GetXFileType( header  );
		m_floatBits = GetFloatBits1( header );
	
	if(strstr(m_fileType,"bin"))
	{
		
	char ch=0;
	while(readCount<count)
	{
		if(xfileVars.m_iLastName!=XPMXTOX){
		//gets 1 char
		 
		switch(fsGet())
		{
			
		case TOKEN_ZERO:
			break;
		case TOKEN_NAME:{
			fsGet();
			unsigned char pch[5];
			ReadFourBytesNullString( fstrm, pch);
			DWORD SZsz = GetDWORDCount( fstrm, pch);
			CString s;
			s.Format("\nTOKEN_NAME GetDWORDCount:  %d\n", SZsz);
//			OutputDebugString(s);
			//MessageBox(NULL, s, "NAMECOUNT",MB_OK);
			if(SZsz>1&&SZsz<256){
				
			char *templateName = (char*)malloc(SZsz*sizeof(char));
			linepos--;
			for(unsigned int j=0;j<SZsz;j++)
			{
				templateName[j]=fsGet();
				
			}
			templateName[SZsz]='\0';
			
			s.Format("%s", templateName);
//			OutputDebugString(s);
			//MessageBox(NULL, s,"NAME TOKEN",MB_OK);
			int len = s.GetLength();
			if(len>0){
									
			if(strstr(templateName, "Header")!=NULL){ReadHeader( fstrm, xfileVars);}
			else if(strstr(templateName, "MeshMaterialList")!=NULL){xfileVars.m_iLastName=XMESHMATERIALLIST;ReadMeshMaterialList(fstrm, xfileVars);}
			else if(strstr(templateName, "Material")!=NULL){xfileVars.m_iLastName=XMATERIAL;ReadMaterial(fstrm, xfileVars);}
			else if(strstr(templateName, "MeshNormals")!=NULL){
				//OutputDebugString("\nReadMeshNormals(fstrm, xfileVars)\n");
			ReadMeshNormals(fstrm, xfileVars);}
			
			else if(strstr(templateName, "MeshTextureCoords")!=NULL){xfileVars.m_iLastName=XMESHTEXTURECOORDINATES;ReadMeshTextureCoords(fstrm, xfileVars);}
			
			else if(strstr(templateName, "FrameTransformMatrix")!=NULL){ReadFrameTransformMatrix( fstrm, xfileVars);}
			else if(strstr(templateName, "Frame")!=NULL){ReadFrame( fstrm, xfileVars);}
			else if(strstr(templateName, "ProgressiveMesh")!=NULL){xfileVars.m_iLastName=XPROGESSIVEMESH;}
			else if(strstr(templateName, "Morph")!=NULL){xfileVars.m_iLastName=XMORPH;}
			else if(strstr(templateName, "Light")!=NULL){xfileVars.m_iLastName=XLIGHT;}
			else if(strstr(templateName, "Shadow")!=NULL){xfileVars.m_iLastName=XSHADOW;}
			else if(strstr(templateName, "Animation")!=NULL){xfileVars.m_iLastName=XANIMATION;}
			else if(strstr(templateName, "Sound")!=NULL){xfileVars.m_iLastName=XSOUND;}
			else if(strstr(templateName, "AnimationSet")!=NULL){xfileVars.m_iLastName=XANIMATIONSET;}
			else if(strstr(templateName, "InlineData")!=NULL){xfileVars.m_iLastName=XINLINEDATA;}
			else if(strstr(templateName, "pmxtox")!=NULL){xfileVars.m_iLastName=XPMXTOX;}
			//mustbelast because mesh is a part of other strings
			else if(strstr(templateName, "Mesh")!=NULL){
//				OutputDebugString("\nReadMesh(fstrm, xfileVars)\n");
				ReadMesh(fstrm, xfileVars);
			}
			else if(strstr(templateName, "mesh")!=NULL){
//				OutputDebugString("\nReadLittleMesh(fstrm, xfileVars)\n");
				ReadMesh(fstrm, xfileVars);
			}
			else{}
			}//eo if(len>0)
			}//eo if(SZsz>0)
			}break;
		case TOKEN_STRING:{
			ReadTokenTerminator(fstrm);
			unsigned char stringLen[5];
			ReadFourBytesNullString( fstrm, stringLen);//stringlength
			DWORD stringSize = GetDWORDCount( fstrm, stringLen );
			char *asciiString = (char*)malloc((stringSize+1)*sizeof(char));
			fsRead(asciiString, stringSize+1);
			unsigned char tokenTerminator[5];
			ReadFourBytesNullString( fstrm, tokenTerminator);
			DWORD tokenValue = GetDWORDCount( fstrm, tokenTerminator );// works out to be either TOKEN_SEMICOLON or TOKEN_COMMA
			//MessageBox(NULL,"TOKEN STRING", asciiString,MB_OK);
			}break;
		case TOKEN_INTEGER:{
			
			ReadTokenTerminator(fstrm);
			unsigned char stringInteger[5];
			ReadFourBytesNullString( fstrm, stringInteger);
			DWORD singleInt = GetDWORDCount( fstrm, stringInteger );// the number
			char singInt[10];
			itoa( singleInt, singInt, 10);
			//InsertChild( GetHTREEITEM( m_rootCount-1 ), singInt );
			}
			break;
		case TOKEN_GUID:{
				ReadTokenTerminator(fstrm);
				char cguid[50];
				unsigned char datafield1[5];
				ReadFourBytesNullString( fstrm, datafield1);
				int da1 = GetDWORDCount( fstrm, datafield1);
				char d1[8];
				itoa( da1, d1, 16);
				
				unsigned char datafield2[3];
				ReadTwoBytesAsNullString( fstrm, datafield2);
				
				short da2 = (short)datafield2+((short)datafield2<<8);
				char d2[10];
				itoa( da2, d2, 16);
				char r1[5];int l1=strlen(d2);r1[0]=d2[l1-4];r1[1]=d2[l1-3];r1[2]=d2[l1-2];r1[3]=d2[l1-1];r1[4]='\0';

				unsigned char datafield3[3];
				ReadTwoBytesAsNullString( fstrm, datafield3);
				
				short da3 = (int)datafield3+((int)datafield3<<8);
				char d3[10];
				itoa( da3, d3, 16);
				char r2[5];int l2=strlen(d3);r2[0]=d3[l2-4];r2[1]=d3[l2-3];r2[2]=d3[l2-2];r2[3]=d3[l2-1];r2[4]='\0';
				
				unsigned char datafield4[9];
				ReadEightBytesAsNullString( fstrm, datafield4);
				char df4[20];
				char dtc[16];
				int j = 0;
				for(int i = 0;i<8;i++)
				{
					if(j==4){df4[j]= '-';j++;}
					char dt = datafield4[i];
					//MessageBox( NULL,dtc, " Hex", MB_OK);
					itoa(dt, dtc, 16);
					int len = strlen(dtc);
					
					if((isdigit(dtc[len-1])==0&&isalpha(dtc[len-1])==0)||(isdigit(dtc[len-2])==0&&isalpha(dtc[len-2])==0))
					{
						df4[j]='0';
						j++;
						df4[j]='0';
						j++;
					}
					else
					{
					df4[j]=dtc[len-2];
					j++;
					df4[j]=dtc[len-1];
					j++;
					}
				}

				df4[j]='\0';
				strcpy(cguid, "<");
				strcat(cguid, d1);
				strcat(cguid, "-");
				strcat(cguid, r1);
				strcat(cguid, "-");
				strcat(cguid, r2);
				strcat(cguid, "-");
				strcat(cguid, df4);
				strcat(cguid, ">\0");
				//InsertChild(GetHTREEITEM(m_rootCount-1),cguid);
			}break;
		case TOKEN_INTEGER_LIST:{
			}break;
		case TOKEN_REALNUM_LIST:
			{}break;
				

		case TOKEN_OBRACE:{}break;////InsertChild( GetHTREEITEM( m_rootCount-1), "obrace {");}break;
		case TOKEN_CBRACE:{}break;////InsertChild( GetHTREEITEM( m_rootCount-1), "cbrace }");}break;
		case TOKEN_OPAREN:{}break;//MessageBox( "oparen (","reader", MB_OK);}break;
		case TOKEN_CPAREN:{}break;//MessageBox( "cparen )","reader", MB_OK);}break;
		case TOKEN_OBRACKET:{//MessageBox( NULL, "obracket [","reader", MB_OK);
							}break;

		case TOKEN_CBRACKET:{}break;//{MessageBox( NULL, "cbracket ]","reader", MB_OK);}break;
		case TOKEN_OANGLE:{}break;//{MessageBox( NULL, "oangle <","reader", MB_OK);}break;
		case TOKEN_CANGLE:{}break;//{MessageBox( NULL, "cangle >","reader", MB_OK);}break;
		case TOKEN_DOT:{}break;//{MessageBox( NULL, "dot .","reader", MB_OK);}break;
		case TOKEN_COMMA:{}break;//{MessageBox( NULL, "comma ,","reader", MB_OK);}break;
		case TOKEN_SEMICOLON:{}break;//{MessageBox( NULL, "semicolon ;","reader", MB_OK);}break;
		case TOKEN_TEMPLATE:
			{
				ReadTokenTerminator(fstrm);
				//InsertRoot( 1, "template", GetHTREEITEM(0));
				m_rootCount++;
			
			}break;
		case TOKEN_WORD:{}break;//{MessageBox( NULL, "word","reader", MB_OK);}break;
		case TOKEN_DWORD:{}break;//{MessageBox( NULL, "dword","reader", MB_OK);}break;
		case TOKEN_FLOAT:{}break;//{MessageBox( NULL, "float","reader", MB_OK);}break;
		case TOKEN_DOUBLE:{}break;//{MessageBox( NULL, "double","reader", MB_OK);}break;
		case TOKEN_CHAR:{}break;//{MessageBox( NULL, "char","reader", MB_OK);}break;
		case TOKEN_UCHAR:{}break;//{MessageBox( NULL, "uchar","reader", MB_OK);}break;
		case TOKEN_SWORD:{
			ReadTokenTerminator( fstrm);
			//MessageBox( NULL, "sword","reader", MB_OK);
			unsigned char csword[3];
			ReadTwoBytesAsNullString(fstrm, csword);
			int sd =	(csword[0]+(csword[1]<<8));
			char csdw[10];
			itoa(sd, csdw, 10);    
			//InsertChild( GetHTREEITEM( m_rootCount-1), csdw);
						 }
			break;
		case TOKEN_SDWORD:{
			ReadTokenTerminator(fstrm);
						
			unsigned char csdword[5];
			ReadFourBytesNullString(fstrm, csdword);
			int sd =	(csdword[0]+(csdword[1]<<8)+(csdword[2]<<16)+(csdword[3]<<24));
			char csdw[10];
			itoa(sd, csdw, 10);
			//InsertChild( GetHTREEITEM( m_rootCount-1), csdw);
			//ReadTokenTerminator(fstrm);
			}
			break;
		case TOKEN_VOID:{}break;//{MessageBox( NULL, "void 48","reader", MB_OK);}break;
		case TOKEN_LPSTR:
			{
				ReadTokenTerminator(fstrm);
				//unsigned char lpLen[4];
				//DWORD len = GetDWORDCount( fstrm, lpLen);
				char lpstr[50];
				strcpy( lpstr, "lpstr ");
				int i = 6;
				while((fstrm.good()))
				{
//TODO:
					//if(fsGet(lpstr[i])==0||i>49)break;

					xfileVars.filePlaceTracker++;
					i++;
				}
				//InsertChild( GetHTREEITEM(m_rootCount-1), lpstr);
			
			}break;
		case TOKEN_UNICODE:{}break;//{MessageBox( NULL, "unicode","reader", MB_OK);}break;
		case TOKEN_CSTRING:
			{
			ReadTokenTerminator(fstrm);
			char cstr[50];
			fsRead(cstr, 49);
			xfileVars.filePlaceTracker+=strlen( cstr );
			}
			break;
		case TOKEN_ARRAY:{}break;//{MessageBox( NULL, "array","reader", MB_OK);}break;
		default:
			{
				if(ch!=-1)
				{
				//do data reading
				char df[20];
				char cnt1[10];
				//cnt1[0]= ch;
				int tch = ch;
				itoa(tch, cnt1, 10);
				strcpy(df, "ch ");
				strcat(df, cnt1);
				strcat(df, "  default  ");
				itoa(fstrm.tellg(), cnt1, 10);
				strcat(df, cnt1);
				
				//InsertChild( GetHTREEITEM( m_rootCount-1), df );
				}
				
			}break;
		
		}//eo switch
		}// eoif(xfileVars.m_iLastName!=XPMXTOX)
		else
		{
			char cpmx[5];
			for(int k = 0;k<4;k++)
			{
				if(fstrm.good())
				cpmx[k]=fsGet();
				xfileVars.filePlaceTracker++;
			}
			cpmx[4]='\0';
			//ReadFourBytesAsNullString( fstrm, cpmx);
			//if(fstrm.good())
			char tint[10];
			int tk = cpmx[0]+(cpmx[1]<<8)+(cpmx[2]<<16)+(cpmx[3]<<24);
			itoa(tk, tint, 10);
			//InsertChild( GetHTREEITEM( m_rootCount-1), tint );
		}
			
	}// eo while
	fstrm.close();
	}// eo if( strstr(m_fileType, "bin"))
	else if ( strstr(m_fileType, "txt"))
	{
		fstrm.close();
		fstrm.open(m_sOpenFileName, ios::in);
		while(fstrm.good())
		{
			char ch[2];
			ch[0]=fsGet();
			ch[1]='\0';
			
		}
		
		fstrm.close();
	
	}
	}// eo fstrm.good(0
	
	return 0;
}

float CReadDirectXFile::ReadBinaryFloatFourBytes(ifstream fs)
{
	
		unsigned char *n;
			// read the file and return 
			// a 5 char null terminated string
			n = ReadFourBytesAddTerminator(fs);
			
			CString fv;
		
		int b[4];
		// switch the string to ints
		for(int i=0;i<4;i++)b[i]=n[i];
		
		unsigned int integerArg= (b[0])|(b[1]<<8)|(b[2]<<16)|(b[3]<<24);
		
		int sign=integerArg>>31;//get the sign	
		unsigned int mantissa = 0;
			mantissa= integerArg<<9;mantissa>>=9;// get the mantissa
		unsigned int exponent = integerArg<<1;exponent>>=24;// get the exponent
			exponent-=127; // subtract bias
		static double floatArg = (double)mantissa;  // convert mantissa to float
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
			//fv.Format("\n %.6f,", floatArg);
			//OutputDebugString( fv.GetBuffer(50));
			return (float)floatArg;
			}
			
			floatArg+=1.0; // add the leading 1
			double delta = pow((double)2, (double)exponent);
			floatArg= floatArg* delta;//(float) // calculate the float

		if(sign==1)floatArg*=-1;//floatArg; // set the sign

		//Type Minimum value Maximum value 
/////////float 1.175494351 E – 38 3.402823466 E + 38 
/////////double 2.2250738585072014 E – 308 1.7976931348623158 E + 308 
		if(/*floatArg<=pow(2.2250738585072014, -308))||*/floatArg>=pow(1.7976931348623158, 308))
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
			//fv.Format("\n %.6f,", floatArg);
			//OutputDebugString( fv.GetBuffer(50));
			return (float)floatArg;
			}
			
		fv.Format("\n %.6f,", floatArg);
		if(strstr(fv.GetBuffer(50),"-1.#INF00"))
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

float * CReadDirectXFile::ReadFloatArray(ifstream fs, float *fl, unsigned int* num, char *str)
{
	CString c;
	unsigned char s[5];
	fsRead( s, 4);
	int numInts = (int)s[0]+((int)s[1]<<8)+((int)s[2]<<16)+((int)s[3]<<24);
	c.Format("\nnumInts:  %d", numInts);
//	OutputDebugString(c);
	fsRead( s, 4);
	int cVerts = (int)s[0]+((int)s[1]<<8)+((int)s[2]<<16)+((int)s[3]<<24);
	c.Format("\ncVerts:  %d", cVerts);
//	OutputDebugString(c);
	if(fsGet()==7)fsGet();
	fsRead( s, 4);
	int numVerts = (int)s[0]+((int)s[1]<<8)+((int)s[2]<<16)+((int)s[3]<<24);
	c.Format("\nNumVerts:  %d", numVerts);
//	OutputDebugString(c);
	*num=cVerts;
	
	fl = GetRealNumbersFloat4( fs, numVerts, fl, str);
	return fl;
}

int * CReadDirectXFile::ReadFacesIntList( ifstream fs, int *ilist, int* faceCount, int* listsize )
{
	CString c;
	unsigned char pch[5];
		
	fsRead( pch, 4);
	// actual num of faces
	
	int cFaces = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	c.Format("\nList Size: %d;\n", cFaces);
//	OutputDebugString(c);
		*listsize = cFaces;

		ilist=(int*)malloc(cFaces*sizeof(int));

	fsRead( pch, 4);
	// actual num of faces
	int numFace = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	c.Format("\nNumber of Faces: %d\n", numFace);
//	OutputDebugString(c);
	*faceCount = numFace;
	c.Format("\nNumber of Faces: %d\n", faceCount);
//	OutputDebugString(c);

	int m =0;
		ilist[m++]=numFace;
	for(int j = 0;j<numFace;j++)
	{
		// Vertices per faces
		fsRead( pch, 4);
		int faceVCnt = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
		c.Format("\nfaceVCnt:%d:", faceVCnt);
		OutputDebugString(c);
			ilist[m++]=faceVCnt;

		for(int k = 0;k<faceVCnt;k++)
		{
			fsRead( pch, 4);
			int vertid = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
			c.Format("%d,", vertid);
//			OutputDebugString(c);
			ilist[m++]=vertid;
		}
	}
	return ilist;
}

void CReadDirectXFile::ReadMesh(ifstream fs, FILEVARS f)
{
	
	/*  Mesh template
		DWORD nVertices;
		array Vector vertices[nVertices];
		DWORD nFaces;
		array MeshFace faces[nFaces];
	*/
	CString c;
	
	//c.Format("\nNormals  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);
	//0  0  0  24  0  7  0  0  0  8  0  0  0  1  0  6  0  10
	//Normals  0  168  0  7  0  0  0  56  0  0  0  1  0  6  0  10  13  104  115  101  77  108  97  110  105  70  0  0  0  9  0  1
	//0  183  0  7  0  0  0  61  0  0  0  1  0  6  0  10  115  108  105  97  115  45  104  115  101  109  0  0  0  10  0  1
	// no name Normals  240  7  191  126  240  7  63  128  0  0  63  127  0  4  0  0  0  24  0  7  0  0  0  8  0  0  0  1  0  6  0  10
	char ch=fsGet();
	bool isName = false;
	char *name;
	if(ch==1)
	{

		fsGet();//0
		unsigned char p[5];
		fsRead( p, 4);
		int sz = (int)p[0]+((int)p[1]<<8)+((int)p[2]<<16)+((int)p[3]<<24);
		if(sz==0)sz=10;
		if(sz>0)
		{
			name =(char*)malloc((sz+1)*sizeof(char));

			fsRead( name, sz);
			name[sz]='\0';
//			OutputDebugString(name);
			fsGet();//NULL
			isName = true;
			
	}
	}
	fsGet();
	if(fsGet()==6)
	{
		fsGet();
//		OutputDebugString("\nInteger_LIST");
		
		f.m_fAMeshCoords = ReadFloatArray( fs, f.m_fAMeshCoords, &f.m_iMeshCoordCount, f.m_cNumberList); 
		// debug or load mesh
		if(f.m_iMeshCoordCount>0)
		{

			LPDIRECT3DRM rm;
			Direct3DRMCreate( &rm);
			LPDIRECT3DRM3 rm3;
			rm->QueryInterface( IID_IDirect3DRM3, (void**)&rm3);

			rm3->CreateMeshBuilder( &LoadMesh );
			if(isName==true)LoadMesh->SetName(name);

		
		for(unsigned int i=0;i<f.m_iMeshCoordCount*3;i+=3)
		{
			//c.Format("\nfloat: %d:   %.6f   %.6f   %.6f", i/3, f.m_fAMeshCoords[i], f.m_fAMeshCoords[i+1], f.m_fAMeshCoords[i+2]);
			//OutputDebugString(c);
			LoadMesh->AddVertex(f.m_fAMeshCoords[i], f.m_fAMeshCoords[i+1], f.m_fAMeshCoords[i+2]);
			LoadMesh->AddNormal(f.m_fAMeshCoords[i], f.m_fAMeshCoords[i+1], f.m_fAMeshCoords[i+2]);
		}
	
		if(fsGet()==6)
		{
			fsGet();// NULL Terminator
//			OutputDebugString("\nTOKEN_TOKEN_INTEGER_LIST");
		}
	
		f.m_iVFacesList = ReadFacesIntList( fs, f.m_iVFacesList, &f.m_iVFacesListNumFaces, &f.m_iVFacesListCount );
		if(f.m_iVFacesListNumFaces>0)
		{
			int cnt = 1;
			for( int j = 0; j< f.m_iVFacesListNumFaces;j++)
			{
				LPDIRECT3DRMFACE2 face;
				rm3->CreateFace( &face );
				LoadMesh->AddFace(face);
				int vperFace = f.m_iVFacesList[cnt++];
				for(int k = 0;k< vperFace;k++)
					face->AddVertexAndNormalIndexed( f.m_iVFacesList[cnt], f.m_iVFacesList[cnt++]);
				
				face->Release();
			}
		}
		rm3->Release();
		rm->Release();
	}
	
	}// eo if(f.m_iMeshCoordCount>0)
		
}

void CReadDirectXFile::ReadMeshNormals(ifstream fs, FILEVARS f)
{
	/*  Mesh template
		DWORD nVertices;
		array Vector vertices[nVertices];
		DWORD nFaces;
		array MeshFace faces[nFaces];
	*/
	streampos u = fs.tellg();
	CString c;
	int obr=fsGet();//openbrace;
	fsGet();// null terminator
	// TOKEN_INTEGER_LIST
	if(fsGet()==6)
	{
		fsGet();
//		OutputDebugString("\nInteger_LIST");
		
		f.m_fAMeshNormals = ReadFloatArray( fs, f.m_fAMeshNormals, &f.m_iMeshNormalCount, f.m_cNumberList); 
		// debug or load mesh
		c.Format("\nf.m_iMeshNormalCount: %d",f.m_iMeshNormalCount);
//			OutputDebugString(c);
		
		for(unsigned int i=0;i<f.m_iMeshNormalCount*3;i+=3)
		{
			//c.Format("\nfloat: %d:   %.6f   %.6f   %.6f", i/3, f.m_fAMeshNormals[i], f.m_fAMeshNormals[i+1], f.m_fAMeshNormals[i+2]);
			//OutputDebugString(c);
			LoadMesh->SetNormal( i, f.m_fAMeshNormals[i], f.m_fAMeshNormals[i+1], f.m_fAMeshNormals[i+2]);
		}
	
	if(fsGet()==6){
		fsGet();// NULL Terminator
//		OutputDebugString("\nTOKEN_TOKEN_INTEGER_LIST");
	}
	
		f.m_iNFacesList = ReadFacesIntList( fs, f.m_iNFacesList, &f.m_iNFacesListNumFaces, &f.m_iNFacesListCount );
	}
}

void CReadDirectXFile::ReadMeshMaterialList(ifstream fs, FILEVARS f)
{
	CString c;
		
	// Normal  0  0  0  0  0  0  0  1  0  0  0  1  0  0  0  3  0  6  0  0
	// dlphin  115  100  51  120  0  0  0  19 | 0  1  0  0 | 0  0  0  0  |0  0  0  1   |0  0  0  1  |0  0  0  3   |0  6  0  0
	// testmb		   0  0  0  1  0  0  0  0 | 0  0  0  1 | 0  0  0  0  |0  0  0  34  |0  0  0  2  |0  0  0  36  |0  6  0  0
	int a = fsGet();// 0?
	int b = fsGet();// 0?
	if(fsGet()==6)
	{
		fsGet();// 0
	CString s;
	char pch[4];
	fsRead( pch, 4);
	int listsz = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	s.Format("\nMaterials: listsz: %d", listsz);
//		OutputDebugString(s);

	fsRead( pch, 4);
	f.m_iNumMaterials = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	s.Format("\nf.m_iNumMaterials: %d", f.m_iNumMaterials);
//		OutputDebugString(s);
	fsRead( pch, 4);
	f.m_iMaterialsPerFace = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	s.Format("\nf.m_iMaterialsPerFace:  %d\n", f.m_iMaterialsPerFace);
//		OutputDebugString(s);
	
	f.m_iMaterialList=(int*)malloc(f.m_iMaterialsPerFace*sizeof(int));
				fsRead( pch, 4);
				f.m_iMaterialList[0]= ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
				s.Format("\n%d,", f.m_iMaterialList[0]);
//				OutputDebugString(s);
			if(f.m_iNumMaterials == 1 )
			{
				f.m_iMaterialListCount=0;
				s.Format("\n%d,", f.m_iMaterialList[0]);
//				OutputDebugString(s);
			}
	// actual num of faces
		else{
			
			f.m_iMaterialListCount=f.m_iMaterialsPerFace;
			for(int i = 1;i<f.m_iMaterialsPerFace;i++)
			{
				fsRead( pch, 4);
				*(f.m_iMaterialList+i) = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
				s.Format("%d,", *(f.m_iMaterialList+i));
//				OutputDebugString(s);
			}// eo i for
		}
	
	int u = fs.tellg();
	int check = (int)fs.get()+((int)fs.get())+((int)fs.get());
	fs.seekg(u);
	if(check==1)
		{
				int a = fsGet();//0
				 a = fsGet();//0
				 a = fsGet();//1
				 a = fsGet();//0
				fsRead(pch,4);
				int cnt = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
				char mname[256];
				if(cnt<255)
				{
					fsRead(mname, cnt);
					mname[cnt]='\0';
					c.Format("\nmat id: %s",mname);
//					OutputDebugString(c);
				//0  11  0  11
				fsRead(pch,4);
				}
	}// eo 	if(check==0)
	}//eo if(fsGet()==6)
	
}

void CReadDirectXFile::ReadMaterial(ifstream fs, FILEVARS f)
{
	HDXMaterial arg;
	
	unsigned char s[5];
	CString c;
	char ch=fsGet();// 0
	c.Format("\n CH is? = : %d",ch);
//	OutputDebugString(c);
	int nCount=0;
	if(ch==TOKEN_NAME)
	{
//		OutputDebugString("\nTOKEN_NAME Material");
			fsGet();//NULL
			unsigned char nc[5];
			ReadFourBytesNullString( fs, nc );
			arg.nCount = GetDWORDCount( fs, nc );
			fs.seekg(fs.tellg()-1);
			arg.matName=(char*)malloc((arg.nCount+1)*sizeof(char));
			fsRead( arg.matName, arg.nCount);
			arg.matName[arg.nCount]='\0';
			
	}
	else{fsGet();// 0
	}
	//c.Format("\nNormals  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);
	//Material cube  0  0  0  0  0  0  0  0  0  63  128  0  0  63  128  0  0  63  128  0  0  63  128  0  0  0  0  0  11  0  7  0
	//Material camx  0  0  0  0  0  0  0  63  128  0  0  62  252  252  254  62  252  252  254  62  252  252  254  0  0  0  10  13  0  7  0  10

	fsRead(s, 2);
		int numInts = (int)s[0]+((int)s[1]<<8);//+((int)s[2]<<16)+((int)s[3]<<24);
		c.Format("\n Is RealNum List 7 = : %d",numInts);
//		OutputDebugString(c);

	fsRead(s, 4);
	int n = (int)s[0]+((int)s[1]<<8)+((int)s[2]<<16)+((int)s[3]<<24);
	
	c.Format("\n Material List Count: %d",n);
//	OutputDebugString(c);
	n=11;
	
	
	float *m = (float*)malloc(n*sizeof(float));
	
	m = GetRealNumbersFloat4(fs, n, m, f.m_cNumberList);

	arg.r = (int)(m[0]*255);
	arg.g = (int)(m[1]*255);
	arg.b = (int)(m[2]*255);
	arg.a = (int)(m[3]*255);
	arg.args[0] = m[4];//power
	arg.args[1] = m[5];//r
	arg.args[2] = m[6];//g
	arg.args[3] = m[7];//b
	arg.args[4] = m[8];//r
	arg.args[5] = m[9];//r
	arg.args[6] = m[10];//g
	arg.args[7] = m[11];//b
	arg.args[8] = 0.0F;//ar
	arg.args[9] = 0.0F;//ag
	arg.args[10] = 0.0F;//ab
	

	
	for(int i = 0;i<n;i++)
	{
			c.Format("\n%.6f,", m[i]);
//			OutputDebugString(c);
	}
	
	//c.Format("\nNormals  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);
	// cube 0  0  8  0  0  0  1  0  6  0  10  115  108  97  109  114  111  78  104  115  101  77  0  0  0  11  0  1  0  11  0  11
	// camera 0  0  1  0  6  0  10  13  115  108  97  109  114  111  78  104  115  101  77  0  0  0  10  13  0  1  0  10  13  0  10  13
	// 6 bytes for TOKEN_NAME and SIZEOF NAME

	ch=fsGet();//get token
	
	if(ch==TOKEN_NAME)
	{
		fsGet();//terminator
		
		ReadTextureFileName( fs, f, &arg.file, &arg.fCount);

	}
	else if(ch==TOKEN_CBRACE)
	{
		// there are 4 zero bytes
		fsGet();//fsGet();fsGet();
	}
	m_RTMat.m_Mats = m_RTMat.Grow(arg);

}

void CReadDirectXFile::ReadMeshTextureCoords(ifstream fs, FILEVARS f)
{
	CString c;
	//c.Format("\nNormals  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);

	int obr=fsGet();//openbrace;
	fsGet();//0
	if(fsGet()==6)
	{
		fsGet();
//		OutputDebugString("\nInteger_LIST");
		
		f.m_fAMeshTextCoords = ReadFloatArray( fs, f.m_fAMeshTextCoords, &f.m_iMeshTextCount, f.m_cNumberList); 
		// debug or load mesh
		c.Format("\nf.m_iMeshTextCount: %d",f.m_iMeshTextCount);
//			OutputDebugString(c);
		for(unsigned int i=0;i<f.m_iMeshTextCount*2;i+=2)
		{
			//c.Format("\nfloat: %d:   t: %.6f   u: %.6f", i/2, f.m_fAMeshTextCoords[i], f.m_fAMeshTextCoords[i+1]);
			//OutputDebugString(c);
			LoadMesh->SetTextureCoordinates( i, f.m_fAMeshTextCoords[i], f.m_fAMeshTextCoords[i+1] );
		}
		
		
		LPDIRECT3DRMMATERIAL2 *mat = (LPDIRECT3DRMMATERIAL2*)malloc(m_RTMat.m_Count*sizeof(LPDIRECT3DRMMATERIAL2));
		LPDIRECT3DRMTEXTURE3 *tex = (LPDIRECT3DRMTEXTURE3*)malloc(m_RTMat.m_Count*sizeof(LPDIRECT3DRMTEXTURE3));
		LPDIRECT3DRM rm;
		Direct3DRMCreate(&rm);
		LPDIRECT3DRM3 rm3;
		rm->QueryInterface( IID_IDirect3DRM3, (void**)&rm3);
		for(unsigned int j=0;j<m_RTMat.m_Count;j++)
		{
			
			mat[j] = m_RTMat.CreateHDXMaterial( rm3, j);
			if(m_RTMat.m_Mats[j].fCount>0)
				tex[j] = m_RTMat.CreateHDXTextue( rm3, j);
		}
		
		rm3->Release();
		rm->Release();

		unsigned int fcnt = LoadMesh->GetFaceCount();
		if(f.m_iMaterialListCount>1)
		{

			for( j = 0;j< fcnt;j++)
			{
				LPDIRECT3DRMFACE2 face;
				LoadMesh->GetFace( j, &face);
				face->SetMaterial(mat[f.m_iMaterialList[j]]);
				face->SetColor(RGBA_MAKE(m_RTMat.m_Mats[f.m_iMaterialList[j]].r, m_RTMat.m_Mats[f.m_iMaterialList[j]].g, m_RTMat.m_Mats[f.m_iMaterialList[j]].b, m_RTMat.m_Mats[f.m_iMaterialList[j]].a));
				if(m_RTMat.m_Mats[f.m_iMaterialList[j]].fCount>0)
					face->SetTexture( tex[f.m_iMaterialList[j]]);
				face->Release();
			}
		}
		else
		{
			for( j = 0;j< fcnt;j++)
			{
				LPDIRECT3DRMFACE2 face;
				LoadMesh->GetFace( j, &face);
				face->SetMaterial(mat[0]);
				face->SetColor(RGBA_MAKE(m_RTMat.m_Mats[0].r, m_RTMat.m_Mats[0].g, m_RTMat.m_Mats[0].b, m_RTMat.m_Mats[0].a));
				
				if(m_RTMat.m_Mats[0].fCount>0)
					face->SetTexture( tex[0]);
				face->Release();

			}
			
		}

		if(m_RTMat.m_Count>0)
		{
			free(mat);
			free(tex);
		}	
	}
	
		
}

void CReadDirectXFile::ReadHeader(ifstream fs, FILEVARS f)
{
	CString c;
	fsGet();//obrace
	// 0
	char ch=fsGet();
	ch=fsGet();
	ch=fsGet();
	if(ch==TOKEN_INTEGER_LIST)
	{
		unsigned char p[3];
		fsRead( p, 2);
		int cnt = (int)p[1]+((int)p[0]<<8);
				c.Format("\nHeader cnt:  %d", cnt);
//				OutputDebugString(c);
			unsigned char pch[5];
			for(int i = 0;i<cnt;i++)
			{
				fsRead( pch, 4);
				int arg = ((int)pch[3]+((int)pch[2]<<8)+((int)pch[1]<<16)+((int)pch[0]<<24));
				c.Format("\nHeader arg:  %d", arg);
				OutputDebugString(c);
			}
	}
}

void CReadDirectXFile::ReadFrame(ifstream fs, FILEVARS f)
{

	//c.Format("\nFrame  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);
	if(fsGet()==1)
	{
		fsGet();// 0
	char pch[4];
	fsRead( pch, 4);
	int m_iSzsz = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	char *name =(char*)malloc((m_iSzsz+1)*sizeof(char));
	fsRead( name, m_iSzsz);
		name[m_iSzsz]='\0';
	CString c;
	c.Format("\nFrame:  %s", name);

//	OutputDebugString(c);
	}
	//c.Format("\nFrame  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d", fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet(), fsGet());
	//OutputDebugString(c);
	
}

void CReadDirectXFile::ReadFrameTransformMatrix(ifstream fs, FILEVARS f)
{
	D3DRMMATRIX4D matrix;
	if(fsGet()==0)
	{
		fsGet();// NULL
	}
	if( fsGet()==7)
	{
		
		fsGet();//NULL terminator
	
		unsigned char p[5];
		int listCnt = 0;
		fsRead(p, 4);
		listCnt = (int)p[0]+((int)p[1]<<8)+((int)p[2]<<16)+((int)p[3]<<24);

		matrix[0][0] = ReadBinaryFloatFourBytes( fs );
		matrix[0][1] = ReadBinaryFloatFourBytes( fs );
		matrix[0][2] = ReadBinaryFloatFourBytes( fs );
		matrix[0][3] = ReadBinaryFloatFourBytes( fs );

		if( fsGet()==7)
		{
			fsGet();//NULL terminator
			fsRead(p, 4);
			listCnt = (int)p[0]+((int)p[1]<<8)+((int)p[2]<<16)+((int)p[3]<<24);
			
			matrix[1][0] = ReadBinaryFloatFourBytes( fs );
			matrix[1][1] = ReadBinaryFloatFourBytes( fs );
			matrix[1][2] = ReadBinaryFloatFourBytes( fs );
			matrix[1][3] = ReadBinaryFloatFourBytes( fs );

			if( fsGet()==7)
			{
				fsGet();//NULL terminator
				fsRead(p, 4);
				listCnt = (int)p[0]+((int)p[1]<<8)+((int)p[2]<<16)+((int)p[3]<<24);

				matrix[2][0] = ReadBinaryFloatFourBytes( fs );
				matrix[2][1] = ReadBinaryFloatFourBytes( fs );
				matrix[2][2] = ReadBinaryFloatFourBytes( fs );
				matrix[2][3] = ReadBinaryFloatFourBytes( fs );
				
				if( fsGet()==7)
				{
					fsGet();//NULL terminator
					fsRead(p, 4);
					listCnt = (int)p[0]+((int)p[1]<<8)+((int)p[2]<<16)+((int)p[3]<<24);

					matrix[3][0] = ReadBinaryFloatFourBytes( fs );
					matrix[3][1] = ReadBinaryFloatFourBytes( fs );
					matrix[3][2] = ReadBinaryFloatFourBytes( fs );
					matrix[3][3] = ReadBinaryFloatFourBytes( fs );



					if(fsGet()==11)
					{
						fsGet();//NULL)
					}

				}// eo if( fsGet()==7)
			}// eo if( fsGet()==7)
		}// eo if( fsGet()==7)
	}// eo if( fsGet()==7)

	
}

void CReadDirectXFile::ReadTextureFileName(ifstream fs, FILEVARS f, char* *tex, int* arg)
{
	unsigned char p[5];
	fsRead( p, 4);
	int SZsz = GetDWORDCount( fs, p );
	
	char *t =(char*)malloc((SZsz+1)*sizeof(char));
	fsRead(t, SZsz);
	t[SZsz]='\0';
	if(strstr( t, "TextureFilename")!=NULL)
	{
		fsGet();//NULL
		fsGet();//NULL
		if(fsGet()==2)
		{
			fsGet();//NULL
			unsigned char stringLen[5];
			fsRead(stringLen, 4);//ReadFourBytesNullString( fs, stringLen);//stringlength
			DWORD stringSize = GetDWORDCount( fs, stringLen );
			*tex = (char*)malloc((stringSize+1)*sizeof(char));
			fsRead( *tex, stringSize);
			*(*tex+stringSize)='\0';
			*arg = stringSize;

			unsigned char tokenTerminator[5];
			ReadFourBytesNullString( fs, tokenTerminator);
			DWORD tokenValue = GetDWORDCount( fs, tokenTerminator );// works out to be either TOKEN_SEMICOLON or TOKEN_COMMA
			//MessageBox(NULL,"TOKEN STRING", asciiString,MB_OK);
		}
	}
}

void CReadDirectXFile::ReadVertexDuplicationIndices(ifstream fs, FILEVARS f)
{
	int u = fs.tellg();
	fs.seekg(u+8);
	CString s;
	char pch[4];

	fsRead( pch, 4);
	int m_iNumVerts = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	s.Format("\nm_iNumVerts: %d", m_iNumVerts);
//		OutputDebugString(s);
	fsRead( pch, 4);
	int nOriginalVertices = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
	s.Format("\nnOriginalVertices:  %d\n", nOriginalVertices);
//		OutputDebugString(s);

	// actual num of faces
	if(m_iNumVerts>1&&nOriginalVertices>1)
	{
		int *List =(int*)malloc(m_iNumVerts*sizeof(int));
		int ListCount=m_iNumVerts;
		for(int i = 0;i<m_iNumVerts;i++)
		{
			fsRead( pch, 4);
			*(List+i) = ((int)pch[0])+((int)pch[1]<<8)+((int)pch[2]<<16)+((int)pch[3]<<24);
			s.Format("%d,", *(List+i));
			//OutputDebugString(s);
		}
	}
	else{
		int *List=(int*)malloc(1*sizeof(int));;
		List[0]=0;
		int ListCount=0;
		s.Format("%d,", List[0]);
			//OutputDebugString(s);
	}
}
////////////////////////////////////////////////////////////////////
////////////
////////////
////////////
/////////////////////////////////////////////////////////////////////

