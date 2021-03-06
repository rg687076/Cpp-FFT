//+------------------------------------------------------------------+
//|                                                       tksFFT.mq4 |
//|                                   Copyright@ 2015, j-higashijima |
//|                                                 http://tks-w.com |
//+------------------------------------------------------------------+
#property copyright "Copyright@ 2015, j-higashijima"
#property link      "http://tks-w.com"
#property version   "1.00"
#property strict
#property indicator_chart_window

#property  indicator_buffers 8
#property  indicator_color1  Gold
#property  indicator_color2  Red
#property  indicator_color3  Green
#property  indicator_color4  Yellow /* ↑ */
#property  indicator_color5  Yellow	/* ↓ */
#property  indicator_width1  2
#property  indicator_width2  2
#property  indicator_width3  2

#import "Fourier.dll"
int HigashiWindow(double ConvergenceValue, double &ar[], int aN);
int setFilter(double smooth, int aN, double &filterary[]);
int execFilter(double &ar[], double &ai[], int aN, double &filterary[]);
int FFT1024(double &data[], int aN, double &retr[], double &reti[]);
int iFFT1024(double &ar[], double &ai[], int aN, double &retr[]);
void print(double &ar[], double &ai[], int n);
void printd(double &ar[], int n);
#import

#include <tks/tkslog.mqh>

#define DIR_THRESHOLD 3

/* input parameters */
input double   smooth         = 4.0;         /* 滑らか具合(0～13ぐらいまで) */
input int      FFT_N          = 1024;        /* FFTのサイズ */
input int      AppliedPrice   = PRICE_CLOSE;  /* 使用する価格データの種類(PRICE_OPEN,PRICE_HIGH,PRICE_LOW,PRICE_CLOSE) */

/* 計算用 */
double tempr[];      /* 実数部 */
double tempi[];      /* 虚数部 */
double filterary[];  /* フィルター */
/* 描画用 */
double   gFft[];
double   gUpDt[];
double   gDnDt[];
double   gUpArw[];
double   gDnArw[];

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
{
   int ret0 = ArrayResize(filterary, FFT_N);
   int ret1 = ArrayResize(tempr, FFT_N);
   int ret2 = ArrayResize(tempi, FFT_N);
   if(ret0 != FFT_N || ret1 != FFT_N || ret2 != FFT_N) {
      printf("OnInit() ArrayResize() failured.");
      return(INIT_FAILED);
   }

   setFilter(smooth, FFT_N, filterary);

   IndicatorBuffers(8);
   SetIndexBuffer(0,gFft);
   SetIndexBuffer(1,gUpDt);
   SetIndexBuffer(2,gDnDt);
   SetIndexBuffer(3,gUpArw);
   SetIndexBuffer(4,gDnArw);

   SetIndexLabel(0,"FFT");
   SetIndexLabel(1,"Up");
   SetIndexLabel(2,"Down");

   SetIndexStyle(0,DRAW_LINE,STYLE_SOLID);
   SetIndexStyle(1,DRAW_LINE,STYLE_SOLID);
   SetIndexStyle(2,DRAW_LINE,STYLE_SOLID);
   SetIndexStyle(3,DRAW_ARROW);
   SetIndexStyle(4,DRAW_ARROW);

   SetIndexArrow(3,228);         /* ↑ */
   SetIndexArrow(4,230);         /* ↓ */

   SetIndexDrawBegin(0, FFT_N*15/16+1);
   SetIndexDrawBegin(1, FFT_N*15/16+1);
   SetIndexDrawBegin(2, FFT_N*15/16+1);
   SetIndexDrawBegin(3, FFT_N*15/16+1);
   SetIndexDrawBegin(4, FFT_N*15/16+1);

   return(INIT_SUCCEEDED);
}
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
{
   /* BarsがFFT_N以下なら、処理しない */
   if(Bars<FFT_N) {
      IndicatorShortName("Error!! Bars < " + (string)FFT_N);
      return(0);
   }

   /* 初期化 */
   int limit=rates_total-prev_calculated;
   if(limit == 0) limit = 1;
   
   /* FFT計算 */
   double Prices[];
   double retr[];

   int ret0 = ArrayResize(retr, FFT_N);
   if(ret0 != FFT_N) return 0;

   int lpmax = (limit/FFT_N-1) * FFT_N;
   if(lpmax < 0) lpmax = 0;
   for(int lpct = lpmax; lpct >= 0; lpct-=FFT_N) {
      if(AppliedPrice == PRICE_OPEN)
         ArrayCopy(Prices, Open, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_HIGH)
         ArrayCopy(Prices, High, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_LOW)
         ArrayCopy(Prices, Low, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_CLOSE)
         ArrayCopy(Prices, Close, 0, lpct, FFT_N);
      /* 窓関数適用 */
      HigashiWindow(Prices[0], Prices, FFT_N);
      /* FFT実行 */
      FFT1024(Prices, FFT_N, tempr, tempi);
      /* デジタルフィルタをかける */
      execFilter(tempr, tempi, FFT_N, filterary);
      /* iFFT実行 */
      iFFT1024(tempr, tempi, FFT_N, retr);
      ArrayCopy(gFft, retr, lpct, 0, FFT_N);

      if(lpct == lpmax) continue;
      
      /* 後ろを丸める(継ぎ目でガクンてなるから) */
      int idx = 0;
      for(int rct = lpct+(FFT_N*15/16); rct < (lpct+FFT_N); rct++,idx++)
         gFft[rct] = (gFft[rct] * smoothconnect1024[idx]) + (gFft[lpct+FFT_N] * (1-smoothconnect1024[idx]));
   }

   /* 副次的な線を計算 */
   int loopmax = (limit-1);
   if(loopmax < (FFT_N / 16)) loopmax = FFT_N / 16;
   if(loopmax == (rates_total-1)) loopmax-=2;
   for(int lpct = loopmax; lpct >= 0; lpct--) {
      double diff = gFft[lpct] - gFft[lpct+1];
      if(gUpDt[lpct] == EMPTY_VALUE && gDnDt[lpct] == EMPTY_VALUE) {
         gUpDt[lpct] = gUpDt[lpct+1];
         gDnDt[lpct] = gDnDt[lpct+1];
      }
      
      /* 上向き */
      if(diff-(DIR_THRESHOLD*Point) > 0) {
         /* 上向きに変化した */
         if(gUpDt[lpct] == EMPTY_VALUE) {
            gUpArw[lpct] = gFft[lpct];
            gDnArw[lpct] = EMPTY_VALUE;
         }
         gUpDt[lpct] = gFft[lpct];
         gDnDt[lpct] = EMPTY_VALUE;
      }
      /* 下向き */
      else if(diff+(DIR_THRESHOLD*Point) < 0) {
         /* 下向きに変化した */
         if(gDnDt[lpct] == EMPTY_VALUE) {
            gUpArw[lpct] = EMPTY_VALUE;
            gDnArw[lpct] = gFft[lpct];
         }
         gUpDt[lpct] = EMPTY_VALUE;
         gDnDt[lpct] = gFft[lpct];
      }
      /* 横ばい */
      else {
         if(gUpDt[lpct] != EMPTY_VALUE)
            gUpDt[lpct] = gFft[lpct];
         else
            gDnDt[lpct] = gFft[lpct];
      }
   }

   return(rates_total);
}
//+------------------------------------------------------------------+
/***************************/
/* cos関数(16πn/1024)の値 */
/***************************/
const double smoothconnect1024[] = {
0.999469611,0.997735961,0.994800877,0.990671442,0.985357626,0.978872254,0.971230981,0.96245225 ,
0.952557254,0.941569875,0.929516635,0.916426628,0.902331452,0.887265128,0.871264024,0.854366763,
0.836614133,0.818048983,0.798716128,0.778662232,0.757935701,0.736586565,0.714666357,0.692227987,
0.669325618,0.646014531,0.622350994,0.598392127,0.57419576 ,0.549820301,0.525324584,0.50076774 ,
0.476209042,0.451707771,0.427323067,0.403113792,0.379138379,0.355454703,0.33211993 ,0.309190385,
0.286721417,0.26476726 ,0.243380907,0.222613982,0.20251661 ,0.183137304,0.16452284 ,0.146718151,
0.129766213,0.113707945,0.098582108,0.084425213,0.071271432,0.059152516,0.048097716,0.038133718,
0.029284572,0.021571639,0.015013535,0.009626091,0.005422311,0.002412342,0.00060345 ,0          ,
};
