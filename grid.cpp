#include "stdafx.h"
#include "grid.h"
#include "dxsdk8\include\d3drm.h"

CGrid::CGrid()
{
	return;
}

LPDIRECT3DRMMESHBUILDER3 CGrid::MakeGrid()
{
	LPDIRECT3DRMMESHBUILDER3 meshc;
	LPDIRECT3DRMMATERIAL2 mat;
    LPDIRECT3DRM rm1;
	LPDIRECT3DRM3 rm = NULL;
	Direct3DRMCreate(&rm1);
	rm1->QueryInterface(IID_IDirect3DRM3, (void**)&rm);
	rm->CreateMaterial( 1.0F, &mat);
	mat->SetAmbient(1.0F, 0.0F, 0.0F);
	mat->SetEmissive(1.0F, 0.0F, 0.0F);
	rm->CreateMeshBuilder(&meshc);

D3DVECTOR vertArray[81];
D3DVECTOR normArray[81];
int color[81];
float tu[81];
float tv[81];

unsigned long fd[]={4,0,0,1,1,10,10,9,9,
4,1,1,2,2,11,11,10,10,
4,2,2,3,3,12,12,11,11,
4,3,3,4,4,13,13,12,12,
4,4,4,5,5,14,14,13,13,
4,5,5,6,6,15,15,14,14,
4,6,6,7,7,16,16,15,15,
4,7,7,8,8,17,17,16,16,
//row1
4,9,9,10,10,19,19,18,18,
4,10,10,11,11,20,20,19,19,
4,11,11,12,12,21,21,20,20,
4,12,12,13,13,22,22,21,21,
4,13,13,14,14,23,23,22,22,
4,14,14,15,15,24,24,23,23,
4,15,15,16,16,25,25,24,24,
4,16,16,17,17,26,26,25,25,
//row2
4,18,18,19,19,28,28,27,27,
4,19,19,20,20,29,29,28,28,
4,20,20,21,21,30,30,29,29,
4,21,21,22,22,31,31,30,30,
4,22,22,23,23,32,32,31,31,
4,23,23,24,24,33,33,32,32,
4,24,24,25,25,34,34,33,33,
4,25,25,26,26,35,35,34,34,
//row3
4,27,27,28,28,37,37,36,36,
4,28,28,29,29,38,38,37,37,
4,29,29,30,30,39,39,38,38,
4,30,30,31,31,40,40,39,39,
4,31,31,32,32,41,41,40,40,
4,32,32,33,33,42,42,41,41,
4,33,33,34,34,43,43,42,42,
4,34,34,35,35,44,44,43,43,
//row4
4,36,36,37,37,46,46,45,45,
4,37,37,38,38,47,47,46,46,
4,38,38,39,39,48,48,47,47,
4,39,39,40,40,49,49,48,48,
4,40,40,41,41,50,50,49,49,
4,41,41,42,42,51,51,50,50,
4,42,42,43,43,52,52,51,51,
4,43,43,44,44,53,53,52,52,
//row
4,45,45,46,46,55,55,54,54,
4,46,46,47,47,56,56,55,55,
4,47,47,48,48,57,57,56,56,
4,48,48,49,49,58,58,57,57,
4,49,49,50,50,59,59,58,58,
4,50,50,51,51,60,60,59,59,
4,51,51,52,52,61,61,60,60,
4,52,52,53,53,62,62,61,61,
//row
4,54,54,55,55,64,64,63,63,
4,55,55,56,56,65,65,64,64,
4,56,56,57,57,66,66,65,65,
4,57,57,58,58,67,67,66,66,
4,58,58,59,59,68,68,67,67,
4,59,59,60,60,69,69,68,68,
4,60,60,61,61,70,70,69,69,
4,61,61,62,62,71,71,70,70,
//row
4,63,63,64,64,73,73,72,72,
4,64,64,65,65,74,74,73,73,
4,65,65,66,66,75,75,74,74,
4,66,66,67,67,76,76,75,75,
4,67,67,68,68,77,77,76,76,
4,68,68,69,69,78,78,77,77,
4,69,69,70,70,79,79,78,78,
4,70,70,71,71,80,80,79,79,
//back side
4,1,1,0,0,9,9,10,10,
4,2,2,1,1,10,10,11,11,
4,3,3,2,2,11,11,12,12,
4,4,4,3,3,12,12,13,13,
4,5,5,4,4,13,13,14,14,
4,6,6,5,5,14,14,15,15,
4,7,7,6,6,15,15,16,16,
4,8,8,7,7,16,16,17,17,
//row1
4,10,10,9,9,18,18,19,19,
4,11,11,10,10,19,19,20,20,
4,12,12,11,11,20,20,21,21,
4,13,13,12,12,21,21,22,22,
4,14,14,13,13,22,22,23,23,
4,15,15,14,14,23,23,24,24,
4,16,16,15,15,24,24,25,25,
4,17,17,16,16,25,25,26,26,
//row2//
4,19,19,18,18,27,27,28,28,
4,20,20,19,19,28,28,29,29,
4,21,21,20,20,29,29,30,30,
4,22,22,21,21,30,30,31,31,
4,23,23,22,22,31,31,32,32,
4,24,24,23,23,32,32,33,33,
4,25,25,24,24,33,33,34,34,
4,26,26,25,25,34,34,35,35,
//row3
4,28,28,27,27,36,36,37,37,
4,29,29,28,28,37,37,38,38,
4,30,30,29,29,38,38,39,39,
4,31,31,30,30,39,39,40,40,
4,32,32,31,31,40,40,41,41,
4,33,33,32,32,41,41,42,42,
4,34,34,33,33,42,42,43,43,
4,35,35,34,34,43,43,44,44,
//row5
4,37,37,36,36,45,45,46,46,
4,38,38,37,37,46,46,47,47,
4,39,39,38,38,47,47,48,48,
4,40,40,39,39,48,48,49,49,
4,41,41,40,40,49,49,50,50,
4,42,42,41,41,50,50,51,51,
4,43,43,42,42,51,51,52,52,
4,44,44,43,43,52,52,53,53,
//row6
4,46,46,45,45,54,54,55,55,
4,47,47,46,46,55,55,56,56,
4,48,48,47,47,56,56,57,57,
4,49,49,48,48,57,57,58,58,
4,50,50,49,49,58,58,59,59,
4,51,51,50,50,59,59,60,60,
4,52,52,51,51,60,60,61,61,
4,53,53,52,52,61,61,62,62,
//row 7
4,55,55,54,54,63,63,64,64,
4,56,56,55,55,64,64,65,65,
4,57,57,56,56,65,65,66,66,
4,58,58,57,57,66,66,67,67,
4,59,59,58,58,67,67,68,68,
4,60,60,59,59,68,68,69,69,
4,61,61,60,60,69,69,70,70,
4,62,62,61,61,70,70,71,71,
//row8
4,64,64,63,63,72,72,73,73,
4,65,65,64,64,73,73,74,74,
4,66,66,65,65,74,74,75,75,
4,67,67,66,66,75,75,76,76,
4,68,68,67,67,76,76,77,77,
4,69,69,68,68,77,77,78,78,
4,70,70,69,69,78,78,79,79,
4,71,71,70,70,79,79,80,80,0};


vertArray[0].x = -40.0F;
vertArray[0].y = 40.0F;
vertArray[0].z = 0.0F;
normArray[0].x = 0.0F;
normArray[0].y = 0.0F;
normArray[0].z = 0.0F;
tu[0] = 2.0F;
tv[0] = 0.99648285F;
color[0] = 0;

vertArray[1].x = -30.0F;
vertArray[1].y = 40.0F;
vertArray[1].z = 0.0F;
normArray[1].x = 0.0F;
normArray[1].y = 0.0F;
normArray[1].z = 0.0F;
tu[1] = 0.12455868F;
tv[1] = 0.99692184F;
color[1] = 0;

vertArray[2].x = -20.0F;
vertArray[2].y = 40.0F;
vertArray[2].z = 0.0F;
normArray[2].x = 0.0F;
normArray[2].y = 0.0F;
normArray[2].z = 0.0F;
tu[2] = 0.24912F;
tv[2] = 0.9973619F;
color[2] = 0;

vertArray[3].x = -10.0F;
vertArray[3].y = 40.0F;
vertArray[3].z = 0.0F;
normArray[3].x = 0.0F;
normArray[3].y = 0.0F;
normArray[3].z = 0.0F;
tu[3] = 0.37368023F;
tv[3] = 0.9978026F;
color[3] = 0;

vertArray[4].x = 0.0F;
vertArray[4].y = 40.0F;
vertArray[4].z = 0.0F;
normArray[4].x = 0.0F;
normArray[4].y = 0.0F;
normArray[4].z = 0.0F;
tu[4] = 0.4982407F;
tv[4] = 0.9982424F;
color[4] = 0;

vertArray[5].x = 10.0F;
vertArray[5].y = 40.0F;
vertArray[5].z = 0.0F;
normArray[5].x = 0.0F;
normArray[5].y = 0.0F;
normArray[5].z = 0.0F;
tu[5] = 0.6228014F;
tv[5] = 0.9986807F;
color[5] = 0;

vertArray[6].x = 20.0F;
vertArray[6].y = 40.0F;
vertArray[6].z = 0.0F;
normArray[6].x = 0.0F;
normArray[6].y = 0.0F;
normArray[6].z = 0.0F;
tu[6] = 0.7473596F;
tv[6] = 0.99912125F;
color[6] = 0;

vertArray[7].x = 30.0F;
vertArray[7].y = 40.0F;
vertArray[7].z = 0.0F;
normArray[7].x = 0.0F;
normArray[7].y = 0.0F;
normArray[7].z = 0.0F;
tu[7] = 0.8719211F;
tv[7] = 0.9995609F;
color[7] = 0;

vertArray[8].x = 40.0F;
vertArray[8].y = 40.0F;
vertArray[8].z = 0.0F;
normArray[8].x = 0.0F;
normArray[8].y = 0.0F;
normArray[8].z = 0.0F;
tu[8] = 0.99648273F;
tv[8] = 1.0F;
color[8] = 0;

vertArray[9].x = -40.0F;
vertArray[9].y = 30.0F;
vertArray[9].z = 0.0F;
normArray[9].x = 0.0F;
normArray[9].y = 0.0F;
normArray[9].z = 0.0F;
tu[9] = 0.0043986202F;
tv[9] = 0.871922F;
color[9] = 0;

vertArray[10].x = -30.0F;
vertArray[10].y = 30.0F;
vertArray[10].z = 0.0F;
normArray[10].x = 0.0F;
normArray[10].y = 0.0F;
normArray[10].z = 0.0F;
tu[10] = 0.12499824F;
tv[10] = 0.87236273F;
color[10] = 0;

vertArray[11].x = -20.0F;
vertArray[11].y = 30.0F;
vertArray[11].z = 0.0F;
normArray[11].x = 0.0F;
normArray[11].y = 0.0F;
normArray[11].z = 0.0F;
tu[11] = 0.2495592F;
tv[11] = 0.8728022F;
color[11] = 0;

vertArray[12].x = -10.0F;
vertArray[12].y = 30.0F;
vertArray[12].z = 0.0F;
normArray[12].x = 0.0F;
normArray[12].y = 0.0F;
normArray[12].z = 0.0F;
tu[12] = 0.37412032F;
tv[12] = 0.8732411F;
color[12] = 0;

vertArray[13].x = 0.0F;
vertArray[13].y = 30.0F;
vertArray[13].z = 0.0F;
normArray[13].x = 0.0F;
normArray[13].y = 0.0F;
normArray[13].z = 0.0F;
tu[13] = 0.4986802F;
tv[13] = 0.87368137F;
color[13] = 0;

vertArray[14].x = 10.0F;
vertArray[14].y = 30.0F;
vertArray[14].z = 0.0F;
normArray[14].x = 0.0F;
normArray[14].y = 0.0F;
normArray[14].z = 0.0F;
tu[14] = 0.62324166F;
tv[14] = 0.8741217F;
color[14] = 0;

vertArray[15].x = 20.0F;
vertArray[15].y = 30.0F;
vertArray[15].z = 0.0F;
normArray[15].x = 0.0F;
normArray[15].y = 0.0F;
normArray[15].z = 0.0F;
tu[15] = 0.7478001F;
tv[15] = 0.87456155F;
color[15] = 0;

vertArray[16].x = 30.0F;
vertArray[16].y = 30.0F;
vertArray[16].z = 0.0F;
normArray[16].x = 0.0F;
normArray[16].y = 0.0F;
normArray[16].z = 0.0F;
tu[16] = 0.8723611F;
tv[16] = 0.87500215F;
color[16] = 0;

vertArray[17].x = 40.0F;
vertArray[17].y = 30.0F;
vertArray[17].z = 0.0F;
normArray[17].x = 0.0F;
normArray[17].y = 0.0F;
normArray[17].z = 0.0F;
tu[17] = 0.9969217F;
tv[17] = 0.87544173F;
color[17] = 0;

vertArray[18].x = -40.0F;
vertArray[18].y = 20.0F;
vertArray[18].z = 0.0F;
normArray[18].x = 0.0F;
normArray[18].y = 0.0F;
normArray[18].z = 0.0F;
tu[18] = 0.0008791156F;
tv[18] = 0.7473623F;
color[18] = 0;

vertArray[19].x = -30.0F;
vertArray[19].y = 20.0F;
vertArray[19].z = 0.0F;
normArray[19].x = 0.0F;
normArray[19].y = 0.0F;
normArray[19].z = 0.0F;
tu[19] = 0.12543765F;
tv[19] = 0.7478014F;
color[19] = 0;

vertArray[20].x = -20.0F;
vertArray[20].y = 20.0F;
vertArray[20].z = 0.0F;
normArray[20].x = 0.0F;
normArray[20].y = 0.0F;
normArray[20].z = 0.0F;
tu[20] = 0.2499987F;
tv[20] = 0.74824125F;
color[20] = 0;

vertArray[21].x = -10.0F;
vertArray[21].y = 20.0F;
vertArray[21].z = 0.0F;
normArray[21].x = 0.0F;
normArray[21].y = 0.0F;
normArray[21].z = 0.0F;
tu[21] = 0.3745601F;
tv[21] = 0.7486816F;
color[21] = 0;

vertArray[22].x = 0.0F;
vertArray[22].y = 20.0F;
vertArray[22].z = 0.0F;
normArray[22].x = 0.0F;
normArray[22].y = 0.0F;
normArray[22].z = 0.0F;
tu[22] = 0.49912074F;
tv[22] = 0.74912065F;
color[22] = 0;

vertArray[23].x = 10.0F;
vertArray[23].y = 20.0F;
vertArray[23].z = 0.0F;
normArray[23].x = 0.0F;
normArray[23].y = 0.0F;
normArray[23].z = 0.0F;
tu[23] = 0.62368107F;
tv[23] = 0.7495613F;
color[23] = 0;

vertArray[24].x = 20.0F;
vertArray[24].y = 20.0F;
vertArray[24].z = 0.0F;
normArray[24].x = 0.0F;
normArray[24].y = 0.0F;
normArray[24].z = 0.0F;
tu[24] = 0.7482395F;
tv[24] = 0.7500004F;
color[24] = 0;

vertArray[25].x = 30.0F;
vertArray[25].y = 20.0F;
vertArray[25].z = 0.0F;
normArray[25].x = 0.0F;
normArray[25].y = 0.0F;
normArray[25].z = 0.0F;
tu[25] = 0.8728011F;
tv[25] = 0.75044006F;
color[25] = 0;

vertArray[26].x = 40.0F;
vertArray[26].y = 20.0F;
vertArray[26].z = 0.0F;
normArray[26].x = 0.0F;
normArray[26].y = 0.0F;
normArray[26].z = 0.0F;
tu[26] = 0.99736184F;
tv[26] = 0.75088143F;
color[26] = 0;

vertArray[27].x = -40.0F;
vertArray[27].y = 10.0F;
vertArray[27].z = 0.0F;
normArray[27].x = 0.0F;
normArray[27].y = 0.0F;
normArray[27].z = 0.0F;
tu[27] = 0.001320093F;
tv[27] = 0.62280124F;
color[27] = 0;

vertArray[28].x = -30.0F;
vertArray[28].y = 10.0F;
vertArray[28].z = 0.0F;
normArray[28].x = 0.0F;
normArray[28].y = 0.0F;
normArray[28].z = 0.0F;
tu[28] = 0.12587821F;
tv[28] = 0.6232407F;
color[28] = 0;

vertArray[29].x = -20.0F;
vertArray[29].y = 10.0F;
vertArray[29].z = 0.0F;
normArray[29].x = 0.0F;
normArray[29].y = 0.0F;
normArray[29].z = 0.0F;
tu[29] = 0.2504388F;
tv[29] = 0.6236811F;
color[29] = 0;

vertArray[30].x = -10.0F;
vertArray[30].y = 10.0F;
vertArray[30].z = 0.0F;
normArray[30].x = 0.0F;
normArray[30].y = 0.0F;
normArray[30].z = 0.0F;
tu[30] = 0.37499976F;
tv[30] = 0.62411964F;
color[30] = 0;

vertArray[31].x = 0.0F;
vertArray[31].y = 10.0F;
vertArray[31].z = 0.0F;
normArray[31].x = 0.0F;
normArray[31].y = 0.0F;
normArray[31].z = 0.0F;
tu[31] = 0.49956065F;
tv[31] = 0.6245603F;
color[31] = 0;

vertArray[32].x = 10.0F;
vertArray[32].y = 10.0F;
vertArray[32].z = 0.0F;
normArray[32].x = 0.0F;
normArray[32].y = 0.0F;
normArray[32].z = 0.0F;
tu[32] = 0.62412083F;
tv[32] = 0.62500054F;
color[32] = 0;

vertArray[33].x = 20.0F;
vertArray[33].y = 10.0F;
vertArray[33].z = 0.0F;
normArray[33].x = 0.0F;
normArray[33].y = 0.0F;
normArray[33].z = 0.0F;
tu[33] = 0.7486795F;
tv[33] = 0.62543935F;
color[33] = 0;

vertArray[34].x = 30.0F;
vertArray[34].y = 10.0F;
vertArray[34].z = 0.0F;
normArray[34].x = 0.0F;
normArray[34].y = 0.0F;
normArray[34].z = 0.0F;
tu[34] = 0.87324053F;
tv[34] = 0.62587845F;
color[34] = 0;

vertArray[35].x = 40.0F;
vertArray[35].y = 10.0F;
vertArray[35].z = 0.0F;
normArray[35].x = 0.0F;
normArray[35].y = 0.0F;
normArray[35].z = 0.0F;
tu[35] = 0.99780136F;
tv[35] = 0.6263187F;
color[35] = 0;

vertArray[36].x = -40.0F;
vertArray[36].y = 0.0F;
vertArray[36].z = 0.0F;
normArray[36].x = 0.0F;
normArray[36].y = 0.0F;
normArray[36].z = 0.0F;
tu[36] = 0.0017594481F;
tv[36] = 0.49824232F;
color[36] = 0;

vertArray[37].x = -30.0F;
vertArray[37].y = 0.0F;
vertArray[37].z = 0.0F;
normArray[37].x = 0.0F;
normArray[37].y = 0.0F;
normArray[37].z = 0.0F;
tu[37] = 0.12631792F;
tv[37] = 0.49868143F;
color[37] = 0;

vertArray[38].x = -20.0F;
vertArray[38].y = 0.0F;
vertArray[38].z = 0.0F;
normArray[38].x = 0.0F;
normArray[38].y = 0.0F;
normArray[38].z = 0.0F;
tu[38] = 0.25087854F;
tv[38] = 0.49912155F;
color[38] = 0;

vertArray[39].x = -10.0F;
vertArray[39].y = 0.0F;
vertArray[39].z = 0.0F;
normArray[39].x = 0.0F;
normArray[39].y = 0.0F;
normArray[39].z = 0.0F;
tu[39] = 0.37543917F;
tv[39] = 0.49956104F;
color[39] = 0;

vertArray[40].x = 0.0F;
vertArray[40].y = 0.0F;
vertArray[40].z = 0.0F;
normArray[40].x = 0.0F;
normArray[40].y = 0.0F;
normArray[40].z = 0.0F;
tu[40] = 0.50000066F;
tv[40] = 0.50000143F;
color[40] = 0;

vertArray[41].x = 10.0F;
vertArray[41].y = 0.0F;
vertArray[41].z = 0.0F;
normArray[41].x = 0.0F;
normArray[41].y = 0.0F;
normArray[41].z = 0.0F;
tu[41] = 0.6245608F;
tv[41] = 0.5004398F;
color[41] = 0;

vertArray[42].x = 20.0F;
vertArray[42].y = 0.0F;
vertArray[42].z = 0.0F;
normArray[42].x = 0.0F;
normArray[42].y = 0.0F;
normArray[42].z = 0.0F;
tu[42] = 0.7491198F;
tv[42] = 0.5008805F;
color[42] = 0;

vertArray[43].x = 30.0F;
vertArray[43].y = 0.0F;
vertArray[43].z = 0.0F;
normArray[43].x = 0.0F;
normArray[43].y = 0.0F;
normArray[43].z = 0.0F;
tu[43] = 0.87368023F;
tv[43] = 0.5013196F;
color[43] = 0;

vertArray[44].x = 40.0F;
vertArray[44].y = 0.0F;
vertArray[44].z = 0.0F;
normArray[44].x = 0.0F;
normArray[44].y = 0.0F;
normArray[44].z = 0.0F;
tu[44] = 0.9982415F;
tv[44] = 0.50175947F;
color[44] = 0;

vertArray[45].x = -40.0F;
vertArray[45].y = -10.0F;
vertArray[45].z = 0.0F;
normArray[45].x = 0.0F;
normArray[45].y = 0.0F;
normArray[45].z = 0.0F;
tu[45] = 0.00219931F;
tv[45] = 0.3736801F;
color[45] = 0;

vertArray[46].x = -30.0F;
vertArray[46].y = -10.0F;
vertArray[46].z = 0.0F;
normArray[46].x = 0.0F;
normArray[46].y = 0.0F;
normArray[46].z = 0.0F;
tu[46] = 0.12675713F;
tv[46] = 0.374119F;
color[46] = 0;

vertArray[47].x = -20.0F;
vertArray[47].y = -10.0F;
vertArray[47].z = 0.0F;
normArray[47].x = 0.0F;
normArray[47].y = 0.0F;
normArray[47].z = 0.0F;
tu[47] = 0.25131854F;
tv[47] = 0.37455875F;
color[47] = 0;

vertArray[48].x = -10.0F;
vertArray[48].y = -10.0F;
vertArray[48].z = 0.0F;
normArray[48].x = 0.0F;
normArray[48].y = 0.0F;
normArray[48].z = 0.0F;
tu[48] = 0.37587923F;
tv[48] = 0.3749999F;
color[48] = 0;

vertArray[49].x = -0.0F;
vertArray[49].y = -10.0F;
vertArray[49].z = 0.0F;
normArray[49].x = 0.0F;
normArray[49].y = 0.0F;
normArray[49].z = 0.0F;
tu[49] = 0.5004407F;
tv[49] = 0.3754402F;
color[49] = 0;

vertArray[50].x = 10.0F;
vertArray[50].y = -10.0F;
vertArray[50].z = 0.0F;
normArray[50].x = 0.0F;
normArray[50].y = 0.0F;
normArray[50].z = 0.0F;
tu[50] = 0.6250008F;
tv[50] = 0.3758795F;
color[50] = 0;

vertArray[51].x = 20.0F;
vertArray[51].y = -10.0F;
vertArray[51].z = 0.0F;
normArray[51].x = 0.0F;
normArray[51].y = 0.0F;
normArray[51].z = 0.0F;
tu[51] = 0.74955976F;
tv[51] = 0.37631902F;
color[51] = 0;

vertArray[52].x = 30.0F;
vertArray[52].y = -10.0F;
vertArray[52].z = 0.0F;
normArray[52].x = 0.0F;
normArray[52].y = 0.0F;
normArray[52].z = 0.0F;
tu[52] = 0.8741202F;
tv[52] = 0.37675965F;
color[52] = 0;

vertArray[53].x = 40.0F;
vertArray[53].y = -10.0F;
vertArray[53].z = 0.0F;
normArray[53].x = 0.0F;
normArray[53].y = 0.0F;
normArray[53].z = 0.0F;
tu[53] = 0.9986806F;
tv[53] = 0.3771997F;
color[53] = 0;

vertArray[54].x = -40.0F;
vertArray[54].y = -20.0F;
vertArray[54].z = 0.0F;
normArray[54].x = 0.0F;
normArray[54].y = 0.0F;
normArray[54].z = 0.0F;
tu[54] = 0.0026385637F;
tv[54] = 0.24912049F;
color[54] = 0;

vertArray[55].x = -30.0F;
vertArray[55].y = -20.0F;
vertArray[55].z = 0.0F;
normArray[55].x = 0.0F;
normArray[55].y = 0.0F;
normArray[55].z = 0.0F;
tu[55] = 0.1271974F;
tv[55] = 0.24956116F;
color[55] = 0;

vertArray[56].x = -20.0F;
vertArray[56].y = -20.0F;
vertArray[56].z = 0.0F;
normArray[56].x = 0.0F;
normArray[56].y = 0.0F;
normArray[56].z = 0.0F;
tu[56] = 0.2517589F;
tv[56] = 0.2500007F;
color[56] = 0;

vertArray[57].x = -10.0F;
vertArray[57].y = -20.0F;
vertArray[57].z = 0.0F;
normArray[57].x = 0.0F;
normArray[57].y = 0.0F;
normArray[57].z = 0.0F;
tu[57] = 0.376319F;
tv[57] = 0.25044015F;
color[57] = 0;

vertArray[58].x = 0.0F;
vertArray[58].y = -20.0F;
vertArray[58].z = 0.0F;
normArray[58].x = 0.0F;
normArray[58].y = 0.0F;
normArray[58].z = 0.0F;
tu[58] = 0.50088006F;
tv[58] = 0.25088006F;
color[58] = 0;

vertArray[59].x = 10.0F;
vertArray[59].y = -20.0F;
vertArray[59].z = 0.0F;
normArray[59].x = 0.0F;
normArray[59].y = 0.0F;
normArray[59].z = 0.0F;
tu[59] = 0.62544054F;
tv[59] = 0.25131956F;
color[59] = 0;

vertArray[60].x = 20.0F;
vertArray[60].y = -20.0F;
vertArray[60].z = 0.0F;
normArray[60].x = 0.0F;
normArray[60].y = 0.0F;
normArray[60].z = 0.0F;
tu[60] = 0.7499989F;
tv[60] = 0.25176018F;
color[60] = 0;

vertArray[61].x = 30.0F;
vertArray[61].y = -20.0F;
vertArray[61].z = 0.0F;
normArray[61].x = 0.0F;
normArray[61].y = 0.0F;
normArray[61].z = 0.0F;
tu[61] = 0.8745599F;
tv[61] = 0.25219968F;
color[61] = 0;

vertArray[62].x = 40.0F;
vertArray[62].y = -20.0F;
vertArray[62].z = 0.0F;
normArray[62].x = 0.0F;
normArray[62].y = 0.0F;
normArray[62].z = 0.0F;
tu[62] = 0.9991205F;
tv[62] = 0.2526391F;
color[62] = 0;

vertArray[63].x = -40.00F;
vertArray[63].y = -30.0F;
vertArray[63].z = 0.0F;
normArray[63].x = 0.0F;
normArray[63].y = 0.0F;
normArray[63].z = 0.0F;
tu[63] = 0.0030783243F;
tv[63] = 0.12456108F;
color[63] = 0;

vertArray[64].x = -30.0F;
vertArray[64].y = -30.0F;
vertArray[64].z = 0.0F;
normArray[64].x = 0.0F;
normArray[64].y = 0.0F;
normArray[64].z = 0.0F;
tu[64] = 0.127637F;
tv[64] = 0.12499851F;
color[64] = 0;

vertArray[65].x = -20.0F;
vertArray[65].y = -30.0F;
vertArray[65].z = 0.0F;
normArray[65].x = 0.0F;
normArray[65].y = 0.0F;
normArray[65].z = 0.0F;
tu[65] = 0.25219762F;
tv[65] = 0.12544012F;
color[65] = 0;

vertArray[66].x = -10.0F;
vertArray[66].y = -30.0F;
vertArray[66].z = 0.0F;
normArray[66].x = 0.0F;
normArray[66].y = 0.0F;
normArray[66].z = 0.0F;
tu[66] = 0.37675887F;
tv[66] = 0.12587813F;
color[66] = 0;

vertArray[67].x = 0.0F;
vertArray[67].y = -30.0F;
vertArray[67].z = 0.0F;
normArray[67].x = 0.0F;
normArray[67].y = 0.0F;
normArray[67].z = 0.0F;
tu[67] = 0.5013199F;
tv[67] = 0.12632118F;
color[67] = 0;

vertArray[68].x = 10.0F;
vertArray[68].y = -30.0F;
vertArray[68].z = 0.0F;
normArray[68].x = 0.0F;
normArray[68].y = 0.0F;
normArray[68].z = 0.0F;
tu[68] = 0.6258811F;
tv[68] = 0.1267601F;
color[68] = 0;

vertArray[69].x = 20.0F;
vertArray[69].y = -30.0F;
vertArray[69].z = 0.0F;
normArray[69].x = 0.0F;
normArray[69].y = 0.0F;
normArray[69].z = 0.0F;
tu[69] = 0.75043863F;
tv[69] = 0.1271987F;
color[69] = 0;

vertArray[70].x = 30.0F;
vertArray[70].y = -30.0F;
vertArray[70].z = 0.0F;
normArray[70].x = 0.0F;
normArray[70].y = 0.0F;
normArray[70].z = 0.0F;
tu[70] = 0.8750002F;
tv[70] = 0.12763894F;
color[70] = 0;

vertArray[71].x = 40.0F;
vertArray[71].y = -30.0F;
vertArray[71].z = 0.0F;
normArray[71].x = 0.0F;
normArray[71].y = 0.0F;
normArray[71].z = 0.0F;
tu[71] = 0.9995609F;
tv[71] = 0.12807834F;
color[71] = 0;

vertArray[72].x = -40.0F;
vertArray[72].y = -40.0F;
vertArray[72].z = 0.0F;
normArray[72].x = 0.0F;
normArray[72].y = 0.0F;
normArray[72].z = 0.0F;
tu[72] = 0.0035182876F;
tv[72] = 2.0F;
color[72] = 0;

vertArray[73].x = -30.0F;
vertArray[73].y = -40.0F;
vertArray[73].z = 0.0F;
normArray[73].x = 0.0F;
normArray[73].y = 0.0F;
normArray[73].z = 0.0F;
tu[73] = 0.12807707F;
tv[73] = 0.00043980315F;
color[73] = 0;

vertArray[74].x = -20.0F;
vertArray[74].y = -40.0F;
vertArray[74].z = 0.0F;
normArray[74].x = 0.0F;
normArray[74].y = 0.0F;
normArray[74].z = 0.0F;
tu[74] = 0.252637F;
tv[74] = 0.008742F;
color[74] = 0;

vertArray[75].x = -10.0F;
vertArray[75].y = -40.0F;
vertArray[75].z = 0.0F;
normArray[75].x = 0.0F;
normArray[75].y = 0.0F;
normArray[75].z = 0.0F;
tu[75] = 0.377199F;
tv[75] = 0.0013186454F;
color[75] = 0;

vertArray[76].x = 0.0F;
vertArray[76].y = -40.0F;
vertArray[76].z = 0.0F;
normArray[76].x = 0.0F;
normArray[76].y = 0.0F;
normArray[76].z = 0.0F;
tu[76] = 0.50175947F;
tv[76] = 0.0017590115F;
color[76] = 0;

vertArray[77].x = 10.0F;
vertArray[77].y = -40.0F;
vertArray[77].z = 0.0F;
normArray[77].x = 0.0F;
normArray[77].y = 0.0F;
normArray[77].z = 0.0F;
tu[77] = 0.6263202F;
tv[77] = 0.0021976887F;
color[77] = 0;

vertArray[78].x = 20.0F;
vertArray[78].y = -40.0F;
vertArray[78].z = 0.0F;
normArray[78].x = 0.0F;
normArray[78].y = 0.0F;
normArray[78].z = 0.0F;
tu[78] = 0.7508783F;
tv[78] = 0.0026379342F;
color[78] = 0;

vertArray[79].x = 30.0F;
vertArray[79].y = -40.0F;
vertArray[79].z = 0.0F;
normArray[79].x = 0.0F;
normArray[79].y = 0.0F;
normArray[79].z = 0.0F;
tu[79] = 0.8754396F;
tv[79] = 0.003078059F;
color[79] = 0;

vertArray[80].x = 40.0F;
vertArray[80].y = -40.0F;
vertArray[80].z = 0.0F;
normArray[80].x = 0.0F;
normArray[80].y = 0.0F;
normArray[80].z = 0.0F;
tu[80] = 1.0F;
tv[80] = 0.0035186263F;
color[80] = 0;

int retid[] = {0,};

meshc->AddFaces(81, vertArray, 81, normArray, fd, NULL);

meshc->SetMaterial(mat);
meshc->SetColor(RGBA_MAKE(0,0,0,255));
	rm1->Release();
	rm->Release();
	mat->Release();

	return meshc;
}
