#ifdef _WIN32
#pragma once
#else
#ifndef HOGE_H
#define HOGE_H
#endif
#endif // HOGE_H

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>		/* _CrtDbgBreak */
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif	/* _DEBUG */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../Fourier/Fourier.h"
#pragma comment(lib, "../Debug/Fourier.lib")

void getAr(double ar[], int size);
void getAi(double ai[], int size);

int main(int argc, char* argv[]){
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif /* WIN32 */

	static double ar512[FFT_N_512];
	static double ai512[FFT_N_512];
	static double retr512[FFT_N_512] = {0};
	static double reti512[FFT_N_512] = {0};
	static double filterary512[FFT_N_512] = {0};
//	double smooth = 3.24;
	double smooth = 8;

	/* 初期設定 */
	getAr(ar512, FFT_N_512);
	setFilter(smooth, FFT_N_512, filterary512);
	HigashiWindow(ar512[0], ar512, FFT_N_512);
	FFT512(ar512, FFT_N_512, retr512, reti512);
	execFilter(retr512, reti512, FFT_N_512, filterary512);
	memcpy(ar512, retr512, sizeof(double)*FFT_N_512);
	memcpy(ai512, reti512, sizeof(double)*FFT_N_512);
	iFFT512(ar512, ai512, FFT_N_512, retr512);


	static double ar[FFT_N_1024];
	static double ai[FFT_N_1024];
	static double retr[FFT_N_1024] = {0};
	static double reti[FFT_N_1024] = {0};
	static double filterary[FFT_N_1024] = {0};

	/* 初期設定 */
	getAr(ar, FFT_N_1024);
//	printd(ar, FFT_N_1024);
	setFilter(smooth, FFT_N_1024, filterary);

	HigashiWindow(ar[0], ar, FFT_N_1024);
//	printd(ar, FFT_N_1024);

	/* forward FFT */
	int ret = FFT1024(ar, FFT_N_1024, retr, reti);
//	print(retr, reti, FFT_N_1024);

	/* フィルタの中身 */
//	printd(filterary, FFT_N_1024);

	/* フィルター適用 */
	execFilter(retr, reti, FFT_N_1024, filterary);
//	print(retr, reti, FFT_N_1024);

	/* reverse FFT */
	memcpy(ar, retr, sizeof(double)*FFT_N_1024);
	memcpy(ai, reti, sizeof(double)*FFT_N_1024);
	iFFT1024(ar, ai, FFT_N_1024, retr);
//	print(retr, reti, FFT_N_1024);

	clock_t t1 = clock();
	for(int lpct    = 0; lpct < 100000; lpct++) {
		HigashiWindow(ar[0], ar, FFT_N_1024);
		FFT1024(ar, FFT_N_1024, retr, reti);
		execFilter(retr, reti, FFT_N_1024, filterary);
		iFFT1024(ar, ai, FFT_N_1024, retr);
	}
	clock_t t2 = clock();	
	printf("fft time=%ld[msec]\n", t2 - t1);

	return 0;
}

void getAi(double ai[], int size) {
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif /* WIN32 */
	memset(ai, 0x00, FFT_N_1024);
}

void getAr(double ar[], int size) {
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif /* WIN32 */
	ar[0]    = 1.09228;
	if(size <= 1) return;
	ar[1]    = 1.0922;
	if(size <= 2) return;
	ar[2]    = 1.09202;
	ar[3]    = 1.0919;
	if(size <= 4) return;
	ar[4]    = 1.09191;
	ar[5]    = 1.0919;
	ar[6]    = 1.09184;
	ar[7]    = 1.09184;
	if(size <= 7) return;
	ar[8]    = 1.09184;
	ar[9]    = 1.09179;
	ar[10]   = 1.0919;
	ar[11]   = 1.09202;
	ar[12]   = 1.0921;
	ar[13]   = 1.09193;
	ar[14]   = 1.09184;
	ar[15]   = 1.09181;
	if(size <= 16) return;
	ar[16]   = 1.092;
	ar[17]   = 1.09203;
	ar[18]   = 1.09188;
	ar[19]   = 1.09192;
	ar[20]   = 1.09197;
	ar[21]   = 1.09209;
	ar[22]   = 1.09209;
	ar[23]   = 1.09189;
	ar[24]   = 1.09213;
	ar[25]   = 1.09187;
	ar[26]   = 1.09201;
	ar[27]   = 1.09245;
	ar[28]   = 1.09203;
	ar[29]   = 1.09204;
	ar[30]   = 1.09238;
	ar[31]   = 1.0923;
	if(size <= 31) return;
	ar[32]   = 1.0922;
	ar[33]   = 1.09227;
	ar[34]   = 1.09251;
	ar[35]   = 1.09279;
	ar[36]   = 1.093;
	ar[37]   = 1.09305;
	ar[38]   = 1.09318;
	ar[39]   = 1.09319;
	ar[40]   = 1.09332;
	ar[41]   = 1.09349;
	ar[42]   = 1.0936;
	ar[43]   = 1.09375;
	ar[44]   = 1.09387;
	ar[45]   = 1.09365;
	ar[46]   = 1.09386;
	ar[47]   = 1.09411;
	ar[48]   = 1.09408;
	ar[49]   = 1.09407;
	ar[50]   = 1.0939;
	ar[51]   = 1.09384;
	ar[52]   = 1.09436;
	ar[53]   = 1.0943;
	ar[54]   = 1.09395;
	ar[55]   = 1.09414;
	ar[56]   = 1.09413;
	ar[57]   = 1.09384;
	ar[58]   = 1.09408;
	ar[59]   = 1.09411;
	ar[60]   = 1.09442;
	ar[61]   = 1.09426;
	ar[62]   = 1.09399;
	ar[63]   = 1.09416;
	if(size <= 64) return;
	ar[64]   = 1.09413;
	ar[65]   = 1.0941;
	ar[66]   = 1.09405;
	ar[67]   = 1.09442;
	ar[68]   = 1.09434;
	ar[69]   = 1.09399;
	ar[70]   = 1.0938;
	ar[71]   = 1.09365;
	ar[72]   = 1.09413;
	ar[73]   = 1.09383;
	ar[74]   = 1.09357;
	ar[75]   = 1.09403;
	ar[76]   = 1.09407;
	ar[77]   = 1.09394;
	ar[78]   = 1.09416;
	ar[79]   = 1.09415;
	ar[80]   = 1.09403;
	ar[81]   = 1.09381;
	ar[82]   = 1.09343;
	ar[83]   = 1.09312;
	ar[84]   = 1.09327;
	ar[85]   = 1.09331;
	ar[86]   = 1.09378;
	ar[87]   = 1.09283;
	ar[88]   = 1.09407;
	ar[89]   = 1.09407;
	ar[90]   = 1.09397;
	ar[91]   = 1.09373;
	ar[92]   = 1.09353;
	ar[93]   = 1.09353;
	ar[94]   = 1.09329;
	ar[95]   = 1.09322;
	ar[96]   = 1.09321;
	ar[97]   = 1.09313;
	ar[98]   = 1.09308;
	ar[99]   = 1.09332;
	ar[100]  = 1.09333;
	ar[101]  = 1.09363;
	ar[102]  = 1.09362;
	ar[103]  = 1.09386;
	ar[104]  = 1.09364;
	ar[105]  = 1.09359;
	ar[106]  = 1.09346;
	ar[107]  = 1.09346;
	ar[108]  = 1.09347;
	ar[109]  = 1.09359;
	ar[110]  = 1.09377;
	ar[111]  = 1.0938;
	ar[112]  = 1.0937;
	ar[113]  = 1.09363;
	ar[114]  = 1.09352;
	ar[115]  = 1.09364;
	ar[116]  = 1.09367;
	ar[117]  = 1.09353;
	ar[118]  = 1.09353;
	ar[119]  = 1.09352;
	ar[120]  = 1.09359;
	ar[121]  = 1.0936;
	ar[122]  = 1.09362;
	ar[123]  = 1.09363;
	ar[124]  = 1.0936;
	ar[125]  = 1.09355;
	ar[126]  = 1.09366;
	ar[127]  = 1.09364;
	if(size <= 128) return;
	ar[128]  = 1.0936;
	ar[129]  = 1.09352;
	ar[130]  = 1.09352;
	ar[131]  = 1.09339;
	ar[132]  = 1.09333;
	ar[133]  = 1.09335;
	ar[134]  = 1.09322;
	ar[135]  = 1.09311;
	ar[136]  = 1.09318;
	ar[137]  = 1.09306;
	ar[138]  = 1.09313;
	ar[139]  = 1.09306;
	ar[140]  = 1.09315;
	ar[141]  = 1.09318;
	ar[142]  = 1.09315;
	ar[143]  = 1.09305;
	ar[144]  = 1.09306;
	ar[145]  = 1.09313;
	ar[146]  = 1.09317;
	ar[147]  = 1.09319;
	ar[148]  = 1.09355;
	ar[149]  = 1.09391;
	ar[150]  = 1.09396;
	ar[151]  = 1.09388;
	ar[152]  = 1.09353;
	ar[153]  = 1.0935;
	ar[154]  = 1.09337;
	ar[155]  = 1.09321;
	ar[156]  = 1.09303;
	ar[157]  = 1.09259;
	ar[158]  = 1.09272;
	ar[159]  = 1.09269;
	ar[160]  = 1.093;
	ar[161]  = 1.09354;
	ar[162]  = 1.09373;
	ar[163]  = 1.09365;
	ar[164]  = 1.09375;
	ar[165]  = 1.09383;
	ar[166]  = 1.09403;
	ar[167]  = 1.09421;
	ar[168]  = 1.09417;
	ar[169]  = 1.09414;
	ar[170]  = 1.094;
	ar[171]  = 1.09383;
	ar[172]  = 1.0937;
	ar[173]  = 1.09389;
	ar[174]  = 1.09398;
	ar[175]  = 1.09366;
	ar[176]  = 1.09348;
	ar[177]  = 1.09338;
	ar[178]  = 1.09335;
	ar[179]  = 1.09386;
	ar[180]  = 1.09396;
	ar[181]  = 1.09383;
	ar[182]  = 1.09374;
	ar[183]  = 1.09383;
	ar[184]  = 1.09382;
	ar[185]  = 1.09402;
	ar[186]  = 1.09408;
	ar[187]  = 1.09406;
	ar[188]  = 1.09411;
	ar[189]  = 1.09412;
	ar[190]  = 1.09414;
	ar[191]  = 1.09421;
	ar[192]  = 1.0945;
	ar[193]  = 1.09456;
	ar[194]  = 1.09453;
	ar[195]  = 1.09469;
	ar[196]  = 1.09481;
	ar[197]  = 1.0949;
	ar[198]  = 1.09494;
	ar[199]  = 1.09525;
	ar[200]  = 1.09531;
	ar[201]  = 1.09551;
	ar[202]  = 1.09568;
	ar[203]  = 1.09585;
	ar[204]  = 1.09641;
	ar[205]  = 1.09639;
	ar[206]  = 1.09649;
	ar[207]  = 1.09635;
	ar[208]  = 1.09649;
	ar[209]  = 1.09677;
	ar[210]  = 1.0967;
	ar[211]  = 1.09654;
	ar[212]  = 1.09675;
	ar[213]  = 1.09653;
	ar[214]  = 1.09674;
	ar[215]  = 1.09667;
	ar[216]  = 1.09632;
	ar[217]  = 1.09624;
	ar[218]  = 1.09607;
	ar[219]  = 1.09463;
	ar[220]  = 1.09445;
	ar[221]  = 1.0942;
	ar[222]  = 1.09437;
	ar[223]  = 1.09444;
	ar[224]  = 1.09445;
	ar[225]  = 1.09432;
	ar[226]  = 1.09423;
	ar[227]  = 1.09415;
	ar[228]  = 1.09398;
	ar[229]  = 1.09409;
	ar[230]  = 1.09383;
	ar[231]  = 1.09415;
	ar[232]  = 1.09333;
	ar[233]  = 1.09337;
	ar[234]  = 1.09339;
	ar[235]  = 1.09352;
	ar[236]  = 1.09385;
	ar[237]  = 1.09376;
	ar[238]  = 1.09369;
	ar[239]  = 1.09373;
	ar[240]  = 1.09379;
	ar[241]  = 1.09371;
	ar[242]  = 1.09356;
	ar[243]  = 1.09388;
	ar[244]  = 1.0936;
	ar[245]  = 1.09327;
	ar[246]  = 1.09294;
	ar[247]  = 1.09281;
	ar[248]  = 1.09257;
	ar[249]  = 1.09255;
	ar[250]  = 1.09272;
	ar[251]  = 1.09318;
	ar[252]  = 1.09325;
	ar[253]  = 1.09356;
	ar[254]  = 1.09365;
	ar[255]  = 1.09365;
	if(size <= 256) return;
	ar[256]  = 1.09368;
	ar[257]  = 1.09376;
	ar[258]  = 1.09382;
	ar[259]  = 1.09378;
	ar[260]  = 1.09378;
	ar[261]  = 1.09352;
	ar[262]  = 1.09371;
	ar[263]  = 1.09378;
	ar[264]  = 1.09368;
	ar[265]  = 1.0936;
	ar[266]  = 1.09347;
	ar[267]  = 1.09268;
	ar[268]  = 1.09233;
	ar[269]  = 1.09205;
	ar[270]  = 1.09211;
	ar[271]  = 1.09202;
	ar[272]  = 1.09201;
	ar[273]  = 1.092;
	ar[274]  = 1.09178;
	ar[275]  = 1.09198;
	ar[276]  = 1.09191;
	ar[277]  = 1.09188;
	ar[278]  = 1.09188;
	ar[279]  = 1.09187;
	ar[280]  = 1.09175;
	ar[281]  = 1.09175;
	ar[282]  = 1.09219;
	ar[283]  = 1.09228;
	ar[284]  = 1.09242;
	ar[285]  = 1.09247;
	ar[286]  = 1.09247;
	ar[287]  = 1.09257;
	ar[288]  = 1.09251;
	ar[289]  = 1.09282;
	ar[290]  = 1.09282;
	ar[291]  = 1.09261;
	ar[292]  = 1.09284;
	ar[293]  = 1.09286;
	ar[294]  = 1.09283;
	ar[295]  = 1.09284;
	ar[296]  = 1.09256;
	ar[297]  = 1.09258;
	ar[298]  = 1.09255;
	ar[299]  = 1.09249;
	ar[300]  = 1.09261;
	ar[301]  = 1.09259;
	ar[302]  = 1.09251;
	ar[303]  = 1.09252;
	ar[304]  = 1.09238;
	ar[305]  = 1.09247;
	ar[306]  = 1.09236;
	ar[307]  = 1.09247;
	ar[308]  = 1.09235;
	ar[309]  = 1.09219;
	ar[310]  = 1.0921;
	ar[311]  = 1.09222;
	ar[312]  = 1.09225;
	ar[313]  = 1.0923;
	ar[314]  = 1.09214;
	ar[315]  = 1.09214;
	ar[316]  = 1.09212;
	ar[317]  = 1.09214;
	ar[318]  = 1.09209;
	ar[319]  = 1.09209;
	ar[320]  = 1.09213;
	ar[321]  = 1.09214;
	ar[322]  = 1.09208;
	ar[323]  = 1.09209;
	ar[324]  = 1.09197;
	ar[325]  = 1.09168;
	ar[326]  = 1.09178;
	ar[327]  = 1.09178;
	ar[328]  = 1.09182;
	ar[329]  = 1.09197;
	ar[330]  = 1.09196;
	ar[331]  = 1.09198;
	ar[332]  = 1.09198;
	ar[333]  = 1.09201;
	ar[334]  = 1.09206;
	ar[335]  = 1.09197;
	ar[336]  = 1.09198;
	ar[337]  = 1.09205;
	ar[338]  = 1.0919;
	ar[339]  = 1.09203;
	ar[340]  = 1.09194;
	ar[341]  = 1.09192;
	ar[342]  = 1.0916;
	ar[343]  = 1.09169;
	ar[344]  = 1.09164;
	ar[345]  = 1.09156;
	ar[346]  = 1.09181;
	ar[347]  = 1.09175;
	ar[348]  = 1.09186;
	ar[349]  = 1.09176;
	ar[350]  = 1.09188;
	ar[351]  = 1.09187;
	ar[352]  = 1.0919;
	ar[353]  = 1.09203;
	ar[354]  = 1.09194;
	ar[355]  = 1.09195;
	ar[356]  = 1.09191;
	ar[357]  = 1.09195;
	ar[358]  = 1.0919;
	ar[359]  = 1.09179;
	ar[360]  = 1.09182;
	ar[361]  = 1.09184;
	ar[362]  = 1.09174;
	ar[363]  = 1.09154;
	ar[364]  = 1.09154;
	ar[365]  = 1.09136;
	ar[366]  = 1.09134;
	ar[367]  = 1.09106;
	ar[368]  = 1.09108;
	ar[369]  = 1.09115;
	ar[370]  = 1.09099;
	ar[371]  = 1.09108;
	ar[372]  = 1.09108;
	ar[373]  = 1.091;
	ar[374]  = 1.09101;
	ar[375]  = 1.0911;
	ar[376]  = 1.09097;
	ar[377]  = 1.09106;
	ar[378]  = 1.09101;
	ar[379]  = 1.091;
	ar[380]  = 1.09085;
	ar[381]  = 1.09069;
	ar[382]  = 1.09096;
	ar[383]  = 1.09094;
	ar[384]  = 1.09089;
	ar[385]  = 1.09086;
	ar[386]  = 1.09057;
	ar[387]  = 1.09084;
	ar[388]  = 1.09095;
	ar[389]  = 1.09098;
	ar[390]  = 1.09067;
	ar[391]  = 1.09029;
	ar[392]  = 1.09033;
	ar[393]  = 1.09023;
	ar[394]  = 1.09014;
	ar[395]  = 1.09019;
	ar[396]  = 1.09026;
	ar[397]  = 1.09021;
	ar[398]  = 1.09028;
	ar[399]  = 1.09037;
	ar[400]  = 1.09042;
	ar[401]  = 1.09025;
	ar[402]  = 1.09032;
	ar[403]  = 1.09022;
	ar[404]  = 1.09017;
	ar[405]  = 1.09008;
	ar[406]  = 1.09003;
	ar[407]  = 1.08996;
	ar[408]  = 1.0901;
	ar[409]  = 1.09007;
	ar[410]  = 1.09003;
	ar[411]  = 1.09001;
	ar[412]  = 1.09;
	ar[413]  = 1.08997;
	ar[414]  = 1.09;
	ar[415]  = 1.09011;
	ar[416]  = 1.09022;
	ar[417]  = 1.09005;
	ar[418]  = 1.09007;
	ar[419]  = 1.09;
	ar[420]  = 1.09017;
	ar[421]  = 1.09018;
	ar[422]  = 1.08999;
	ar[423]  = 1.0899;
	ar[424]  = 1.08988;
	ar[425]  = 1.08991;
	ar[426]  = 1.08994;
	ar[427]  = 1.09002;
	ar[428]  = 1.0901;
	ar[429]  = 1.09001;
	ar[430]  = 1.09008;
	ar[431]  = 1.09004;
	ar[432]  = 1.09011;
	ar[433]  = 1.09009;
	ar[434]  = 1.08997;
	ar[435]  = 1.09007;
	ar[436]  = 1.08999;
	ar[437]  = 1.08998;
	ar[438]  = 1.08997;
	ar[439]  = 1.08991;
	ar[440]  = 1.0899;
	ar[441]  = 1.08989;
	ar[442]  = 1.08988;
	ar[443]  = 1.08966;
	ar[444]  = 1.08965;
	ar[445]  = 1.08947;
	ar[446]  = 1.08945;
	ar[447]  = 1.08948;
	ar[448]  = 1.08914;
	ar[449]  = 1.08926;
	ar[450]  = 1.08906;
	ar[451]  = 1.08896;
	ar[452]  = 1.08917;
	ar[453]  = 1.08947;
	ar[454]  = 1.08961;
	ar[455]  = 1.08925;
	ar[456]  = 1.08943;
	ar[457]  = 1.08964;
	ar[458]  = 1.08959;
	ar[459]  = 1.08968;
	ar[460]  = 1.08941;
	ar[461]  = 1.08937;
	ar[462]  = 1.08938;
	ar[463]  = 1.08957;
	ar[464]  = 1.08988;
	ar[465]  = 1.08978;
	ar[466]  = 1.0894;
	ar[467]  = 1.08949;
	ar[468]  = 1.08949;
	ar[469]  = 1.08972;
	ar[470]  = 1.0895;
	ar[471]  = 1.08949;
	ar[472]  = 1.089;
	ar[473]  = 1.08895;
	ar[474]  = 1.08897;
	ar[475]  = 1.08908;
	ar[476]  = 1.08892;
	ar[477]  = 1.08879;
	ar[478]  = 1.08887;
	ar[479]  = 1.08907;
	ar[480]  = 1.08924;
	ar[481]  = 1.08931;
	ar[482]  = 1.08928;
	ar[483]  = 1.08946;
	ar[484]  = 1.08972;
	ar[485]  = 1.08955;
	ar[486]  = 1.08968;
	ar[487]  = 1.08976;
	ar[488]  = 1.08994;
	ar[489]  = 1.08988;
	ar[490]  = 1.08996;
	ar[491]  = 1.09018;
	ar[492]  = 1.09015;
	ar[493]  = 1.09015;
	ar[494]  = 1.09031;
	ar[495]  = 1.09017;
	ar[496]  = 1.08998;
	ar[497]  = 1.08989;
	ar[498]  = 1.08966;
	ar[499]  = 1.08976;
	ar[500]  = 1.08979;
	ar[501]  = 1.08999;
	ar[502]  = 1.08993;
	ar[503]  = 1.08978;
	ar[504]  = 1.08966;
	ar[505]  = 1.08959;
	ar[506]  = 1.08937;
	ar[507]  = 1.08924;
	ar[508]  = 1.08935;
	ar[509]  = 1.0897;
	ar[510]  = 1.08968;
	ar[511]  = 1.0898;
	if(size <= FFT_N_512) return;
	ar[512]  = 1.08921;
	ar[513]  = 1.08903;
	ar[514]  = 1.08911;
	ar[515]  = 1.08928;
	ar[516]  = 1.0892;
	ar[517]  = 1.08879;
	ar[518]  = 1.08882;
	ar[519]  = 1.08898;
	ar[520]  = 1.08854;
	ar[521]  = 1.08858;
	ar[522]  = 1.08848;
	ar[523]  = 1.0886;
	ar[524]  = 1.08857;
	ar[525]  = 1.08878;
	ar[526]  = 1.08869;
	ar[527]  = 1.08858;
	ar[528]  = 1.08837;
	ar[529]  = 1.08831;
	ar[530]  = 1.08847;
	ar[531]  = 1.08874;
	ar[532]  = 1.08855;
	ar[533]  = 1.08866;
	ar[534]  = 1.08855;
	ar[535]  = 1.0887;
	ar[536]  = 1.08869;
	ar[537]  = 1.08857;
	ar[538]  = 1.08822;
	ar[539]  = 1.08807;
	ar[540]  = 1.08801;
	ar[541]  = 1.08837;
	ar[542]  = 1.08858;
	ar[543]  = 1.08847;
	ar[544]  = 1.08829;
	ar[545]  = 1.08817;
	ar[546]  = 1.08808;
	ar[547]  = 1.08757;
	ar[548]  = 1.08779;
	ar[549]  = 1.08779;
	ar[550]  = 1.0878;
	ar[551]  = 1.08746;
	ar[552]  = 1.08713;
	ar[553]  = 1.08725;
	ar[554]  = 1.08792;
	ar[555]  = 1.08809;
	ar[556]  = 1.08848;
	ar[557]  = 1.08844;
	ar[558]  = 1.08815;
	ar[559]  = 1.0884;
	ar[560]  = 1.08842;
	ar[561]  = 1.08857;
	ar[562]  = 1.08886;
	ar[563]  = 1.08912;
	ar[564]  = 1.0889;
	ar[565]  = 1.08868;
	ar[566]  = 1.08817;
	ar[567]  = 1.0881;
	ar[568]  = 1.08815;
	ar[569]  = 1.08841;
	ar[570]  = 1.08838;
	ar[571]  = 1.08822;
	ar[572]  = 1.08867;
	ar[573]  = 1.08895;
	ar[574]  = 1.08877;
	ar[575]  = 1.08846;
	ar[576]  = 1.08839;
	ar[577]  = 1.08841;
	ar[578]  = 1.08855;
	ar[579]  = 1.08875;
	ar[580]  = 1.08937;
	ar[581]  = 1.08919;
	ar[582]  = 1.08898;
	ar[583]  = 1.08946;
	ar[584]  = 1.08918;
	ar[585]  = 1.08891;
	ar[586]  = 1.08977;
	ar[587]  = 1.08946;
	ar[588]  = 1.0895;
	ar[589]  = 1.08962;
	ar[590]  = 1.08964;
	ar[591]  = 1.08928;
	ar[592]  = 1.08934;
	ar[593]  = 1.08965;
	ar[594]  = 1.08977;
	ar[595]  = 1.09004;
	ar[596]  = 1.08999;
	ar[597]  = 1.08962;
	ar[598]  = 1.08998;
	ar[599]  = 1.09008;
	ar[600]  = 1.09041;
	ar[601]  = 1.0912;
	ar[602]  = 1.0908;
	ar[603]  = 1.09146;
	ar[604]  = 1.09142;
	ar[605]  = 1.09091;
	ar[606]  = 1.09078;
	ar[607]  = 1.09068;
	ar[608]  = 1.09026;
	ar[609]  = 1.09042;
	ar[610]  = 1.09043;
	ar[611]  = 1.09034;
	ar[612]  = 1.09018;
	ar[613]  = 1.08989;
	ar[614]  = 1.09053;
	ar[615]  = 1.0906;
	ar[616]  = 1.09025;
	ar[617]  = 1.09008;
	ar[618]  = 1.08988;
	ar[619]  = 1.08978;
	ar[620]  = 1.08953;
	ar[621]  = 1.08918;
	ar[622]  = 1.08875;
	ar[623]  = 1.08898;
	ar[624]  = 1.08967;
	ar[625]  = 1.08919;
	ar[626]  = 1.0889;
	ar[627]  = 1.08893;
	ar[628]  = 1.08916;
	ar[629]  = 1.0893;
	ar[630]  = 1.08929;
	ar[631]  = 1.08897;
	ar[632]  = 1.0899;
	ar[633]  = 1.09045;
	ar[634]  = 1.09035;
	ar[635]  = 1.09058;
	ar[636]  = 1.09026;
	ar[637]  = 1.0908;
	ar[638]  = 1.0903;
	ar[639]  = 1.0904;
	ar[640]  = 1.08986;
	ar[641]  = 1.08979;
	ar[642]  = 1.09057;
	ar[643]  = 1.09042;
	ar[644]  = 1.09041;
	ar[645]  = 1.08979;
	ar[646]  = 1.08989;
	ar[647]  = 1.08966;
	ar[648]  = 1.08963;
	ar[649]  = 1.08939;
	ar[650]  = 1.0895;
	ar[651]  = 1.09004;
	ar[652]  = 1.09023;
	ar[653]  = 1.09004;
	ar[654]  = 1.08995;
	ar[655]  = 1.08983;
	ar[656]  = 1.08995;
	ar[657]  = 1.09008;
	ar[658]  = 1.08978;
	ar[659]  = 1.08969;
	ar[660]  = 1.0888;
	ar[661]  = 1.08877;
	ar[662]  = 1.08849;
	ar[663]  = 1.08874;
	ar[664]  = 1.08854;
	ar[665]  = 1.08881;
	ar[666]  = 1.08899;
	ar[667]  = 1.08902;
	ar[668]  = 1.089;
	ar[669]  = 1.08917;
	ar[670]  = 1.0889;
	ar[671]  = 1.08933;
	ar[672]  = 1.09019;
	ar[673]  = 1.09051;
	ar[674]  = 1.09047;
	ar[675]  = 1.09026;
	ar[676]  = 1.09029;
	ar[677]  = 1.09054;
	ar[678]  = 1.0896;
	ar[679]  = 1.08935;
	ar[680]  = 1.0886;
	ar[681]  = 1.08935;
	ar[682]  = 1.08947;
	ar[683]  = 1.08932;
	ar[684]  = 1.08922;
	ar[685]  = 1.08828;
	ar[686]  = 1.08871;
	ar[687]  = 1.08929;
	ar[688]  = 1.08866;
	ar[689]  = 1.08892;
	ar[690]  = 1.08864;
	ar[691]  = 1.0886;
	ar[692]  = 1.08913;
	ar[693]  = 1.08895;
	ar[694]  = 1.08814;
	ar[695]  = 1.08759;
	ar[696]  = 1.08736;
	ar[697]  = 1.08639;
	ar[698]  = 1.0866;
	ar[699]  = 1.08659;
	ar[700]  = 1.08708;
	ar[701]  = 1.08717;
	ar[702]  = 1.08729;
	ar[703]  = 1.08715;
	ar[704]  = 1.087;
	ar[705]  = 1.08697;
	ar[706]  = 1.08769;
	ar[707]  = 1.08748;
	ar[708]  = 1.08715;
	ar[709]  = 1.08719;
	ar[710]  = 1.08749;
	ar[711]  = 1.08843;
	ar[712]  = 1.08732;
	ar[713]  = 1.08696;
	ar[714]  = 1.08659;
	ar[715]  = 1.08564;
	ar[716]  = 1.0865;
	ar[717]  = 1.08582;
	ar[718]  = 1.08649;
	ar[719]  = 1.08625;
	ar[720]  = 1.08593;
	ar[721]  = 1.08609;
	ar[722]  = 1.0861;
	ar[723]  = 1.08634;
	ar[724]  = 1.08681;
	ar[725]  = 1.0871;
	ar[726]  = 1.0877;
	ar[727]  = 1.08739;
	ar[728]  = 1.08755;
	ar[729]  = 1.0873;
	ar[730]  = 1.08803;
	ar[731]  = 1.08753;
	ar[732]  = 1.08741;
	ar[733]  = 1.08732;
	ar[734]  = 1.08794;
	ar[735]  = 1.08859;
	ar[736]  = 1.08879;
	ar[737]  = 1.08834;
	ar[738]  = 1.08817;
	ar[739]  = 1.08728;
	ar[740]  = 1.08781;
	ar[741]  = 1.08703;
	ar[742]  = 1.08696;
	ar[743]  = 1.08589;
	ar[744]  = 1.0863;
	ar[745]  = 1.08661;
	ar[746]  = 1.08671;
	ar[747]  = 1.087;
	ar[748]  = 1.08685;
	ar[749]  = 1.08724;
	ar[750]  = 1.08628;
	ar[751]  = 1.08533;
	ar[752]  = 1.08445;
	ar[753]  = 1.08415;
	ar[754]  = 1.0836;
	ar[755]  = 1.08339;
	ar[756]  = 1.08392;
	ar[757]  = 1.08411;
	ar[758]  = 1.08498;
	ar[759]  = 1.08438;
	ar[760]  = 1.08491;
	ar[761]  = 1.08476;
	ar[762]  = 1.08479;
	ar[763]  = 1.08448;
	ar[764]  = 1.08451;
	ar[765]  = 1.08369;
	ar[766]  = 1.0841;
	ar[767]  = 1.08454;
	ar[768]  = 1.08283;
	ar[769]  = 1.08228;
	ar[770]  = 1.08221;
	ar[771]  = 1.08212;
	ar[772]  = 1.08277;
	ar[773]  = 1.08261;
	ar[774]  = 1.08266;
	ar[775]  = 1.08225;
	ar[776]  = 1.08188;
	ar[777]  = 1.08211;
	ar[778]  = 1.08251;
	ar[779]  = 1.08221;
	ar[780]  = 1.08331;
	ar[781]  = 1.08291;
	ar[782]  = 1.08157;
	ar[783]  = 1.08091;
	ar[784]  = 1.08046;
	ar[785]  = 1.08166;
	ar[786]  = 1.08225;
	ar[787]  = 1.08575;
	ar[788]  = 1.08601;
	ar[789]  = 1.08571;
	ar[790]  = 1.0857;
	ar[791]  = 1.08607;
	ar[792]  = 1.086;
	ar[793]  = 1.08601;
	ar[794]  = 1.08629;
	ar[795]  = 1.08645;
	ar[796]  = 1.08691;
	ar[797]  = 1.08677;
	ar[798]  = 1.08684;
	ar[799]  = 1.08684;
	ar[800]  = 1.08656;
	ar[801]  = 1.08639;
	ar[802]  = 1.08609;
	ar[803]  = 1.08605;
	ar[804]  = 1.086;
	ar[805]  = 1.08619;
	ar[806]  = 1.0864;
	ar[807]  = 1.08613;
	ar[808]  = 1.08613;
	ar[809]  = 1.08613;
	ar[810]  = 1.08638;
	ar[811]  = 1.08638;
	ar[812]  = 1.0865;
	ar[813]  = 1.08644;
	ar[814]  = 1.08618;
	ar[815]  = 1.08606;
	ar[816]  = 1.0863;
	ar[817]  = 1.08656;
	ar[818]  = 1.08644;
	ar[819]  = 1.08644;
	ar[820]  = 1.08637;
	ar[821]  = 1.08636;
	ar[822]  = 1.08658;
	ar[823]  = 1.08677;
	ar[824]  = 1.08666;
	ar[825]  = 1.08667;
	ar[826]  = 1.08712;
	ar[827]  = 1.08702;
	ar[828]  = 1.08702;
	ar[829]  = 1.08696;
	ar[830]  = 1.08715;
	ar[831]  = 1.08725;
	ar[832]  = 1.08715;
	ar[833]  = 1.08707;
	ar[834]  = 1.08699;
	ar[835]  = 1.08689;
	ar[836]  = 1.08708;
	ar[837]  = 1.08694;
	ar[838]  = 1.08681;
	ar[839]  = 1.08662;
	ar[840]  = 1.0867;
	ar[841]  = 1.08663;
	ar[842]  = 1.08669;
	ar[843]  = 1.0868;
	ar[844]  = 1.08685;
	ar[845]  = 1.08667;
	ar[846]  = 1.08658;
	ar[847]  = 1.08646;
	ar[848]  = 1.086;
	ar[849]  = 1.08597;
	ar[850]  = 1.08626;
	ar[851]  = 1.08634;
	ar[852]  = 1.08644;
	ar[853]  = 1.08661;
	ar[854]  = 1.08636;
	ar[855]  = 1.08645;
	ar[856]  = 1.08637;
	ar[857]  = 1.08647;
	ar[858]  = 1.08626;
	ar[859]  = 1.08639;
	ar[860]  = 1.0866;
	ar[861]  = 1.08632;
	ar[862]  = 1.08647;
	ar[863]  = 1.08654;
	ar[864]  = 1.08663;
	ar[865]  = 1.08661;
	ar[866]  = 1.0865;
	ar[867]  = 1.08667;
	ar[868]  = 1.08678;
	ar[869]  = 1.08678;
	ar[870]  = 1.08666;
	ar[871]  = 1.08672;
	ar[872]  = 1.08669;
	ar[873]  = 1.08698;
	ar[874]  = 1.08742;
	ar[875]  = 1.087;
	ar[876]  = 1.08698;
	ar[877]  = 1.0872;
	ar[878]  = 1.0872;
	ar[879]  = 1.08724;
	ar[880]  = 1.08715;
	ar[881]  = 1.08705;
	ar[882]  = 1.08709;
	ar[883]  = 1.08706;
	ar[884]  = 1.08702;
	ar[885]  = 1.08691;
	ar[886]  = 1.08694;
	ar[887]  = 1.08708;
	ar[888]  = 1.08702;
	ar[889]  = 1.087;
	ar[890]  = 1.08679;
	ar[891]  = 1.08683;
	ar[892]  = 1.0869;
	ar[893]  = 1.08686;
	ar[894]  = 1.08699;
	ar[895]  = 1.08701;
	ar[896]  = 1.08705;
	ar[897]  = 1.08719;
	ar[898]  = 1.08725;
	ar[899]  = 1.08722;
	ar[900]  = 1.08726;
	ar[901]  = 1.0873;
	ar[902]  = 1.08723;
	ar[903]  = 1.08738;
	ar[904]  = 1.08751;
	ar[905]  = 1.08759;
	ar[906]  = 1.0875;
	ar[907]  = 1.08748;
	ar[908]  = 1.08736;
	ar[909]  = 1.08725;
	ar[910]  = 1.08718;
	ar[911]  = 1.08717;
	ar[912]  = 1.08725;
	ar[913]  = 1.08708;
	ar[914]  = 1.08719;
	ar[915]  = 1.08715;
	ar[916]  = 1.08708;
	ar[917]  = 1.08696;
	ar[918]  = 1.08687;
	ar[919]  = 1.08696;
	ar[920]  = 1.08694;
	ar[921]  = 1.08671;
	ar[922]  = 1.0864;
	ar[923]  = 1.08639;
	ar[924]  = 1.08644;
	ar[925]  = 1.08638;
	ar[926]  = 1.08626;
	ar[927]  = 1.08658;
	ar[928]  = 1.08666;
	ar[929]  = 1.08657;
	ar[930]  = 1.08662;
	ar[931]  = 1.08695;
	ar[932]  = 1.08699;
	ar[933]  = 1.08668;
	ar[934]  = 1.08667;
	ar[935]  = 1.08676;
	ar[936]  = 1.08698;
	ar[937]  = 1.08688;
	ar[938]  = 1.08678;
	ar[939]  = 1.08721;
	ar[940]  = 1.08685;
	ar[941]  = 1.08721;
	ar[942]  = 1.08745;
	ar[943]  = 1.08744;
	ar[944]  = 1.08742;
	ar[945]  = 1.08729;
	ar[946]  = 1.08698;
	ar[947]  = 1.08694;
	ar[948]  = 1.08674;
	ar[949]  = 1.08671;
	ar[950]  = 1.08675;
	ar[951]  = 1.08673;
	ar[952]  = 1.08678;
	ar[953]  = 1.08677;
	ar[954]  = 1.08674;
	ar[955]  = 1.08677;
	ar[956]  = 1.08668;
	ar[957]  = 1.08665;
	ar[958]  = 1.08667;
	ar[959]  = 1.08662;
	ar[960]  = 1.08657;
	ar[961]  = 1.08677;
	ar[962]  = 1.08678;
	ar[963]  = 1.08686;
	ar[964]  = 1.08689;
	ar[965]  = 1.08688;
	ar[966]  = 1.08668;
	ar[967]  = 1.08647;
	ar[968]  = 1.08631;
	ar[969]  = 1.0866;
	ar[970]  = 1.08689;
	ar[971]  = 1.08662;
	ar[972]  = 1.08637;
	ar[973]  = 1.0863;
	ar[974]  = 1.08658;
	ar[975]  = 1.08633;
	ar[976]  = 1.08623;
	ar[977]  = 1.08602;
	ar[978]  = 1.08633;
	ar[979]  = 1.08622;
	ar[980]  = 1.08644;
	ar[981]  = 1.08654;
	ar[982]  = 1.08649;
	ar[983]  = 1.08664;
	ar[984]  = 1.0865;
	ar[985]  = 1.08647;
	ar[986]  = 1.08675;
	ar[987]  = 1.08689;
	ar[988]  = 1.08699;
	ar[989]  = 1.08695;
	ar[990]  = 1.08698;
	ar[991]  = 1.08703;
	ar[992]  = 1.08668;
	ar[993]  = 1.08675;
	ar[994]  = 1.08689;
	ar[995]  = 1.08686;
	ar[996]  = 1.08699;
	ar[997]  = 1.08727;
	ar[998]  = 1.08735;
	ar[999]  = 1.08723;
	ar[1000] = 1.08704;
	ar[1001] = 1.08719;
	ar[1002] = 1.08731;
	ar[1003] = 1.08739;
	ar[1004] = 1.08735;
	ar[1005] = 1.08706;
	ar[1006] = 1.08706;
	ar[1007] = 1.08723;
	ar[1008] = 1.08706;
	ar[1009] = 1.08723;
	ar[1010] = 1.08708;
	ar[1011] = 1.08739;
	ar[1012] = 1.08739;
	ar[1013] = 1.08729;
	ar[1014] = 1.0874;
	ar[1015] = 1.08755;
	ar[1016] = 1.08747;
	ar[1017] = 1.08713;
	ar[1018] = 1.08705;
	ar[1019] = 1.08707;
	ar[1020] = 1.08708;
	ar[1021] = 1.08669;
	ar[1022] = 1.08705;
	ar[1023] = 1.08727;
}

#ifndef _WIN32
//#endif
#endif
