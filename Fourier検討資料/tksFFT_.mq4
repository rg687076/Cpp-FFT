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
#property  indicator_color2  Red    /* ↑ */
#property  indicator_color3  Green	/* ↓ */
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

/* input parameters */
input double   smooth         = 4.0;         /* 滑らか具合(0～13ぐらいまで) */
input int      FFT_N          = 1024;        /* FFTのサイズ */
input int      AppliedPrice   = PRICE_OPEN;  /* 使用する価格データの種類(PRICE_OPEN,PRICE_HIGH,PRICE_LOW,PRICE_CLOSE) */

/* 計算用 */
double tempr[];      /* 実数部 */
double tempi[];      /* 虚数部 */
double filterary[];  /* フィルター */
/* 描画用 */
double   gFft[];
double   gUp[];
double   gDown[];

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
   SetIndexBuffer(1,gUp);
   SetIndexBuffer(2,gDown);

   SetIndexLabel(0,"FFT");
   SetIndexLabel(1,"Up");
   SetIndexLabel(2,"Down");

   SetIndexStyle(0,DRAW_LINE,STYLE_SOLID);
   SetIndexStyle(1,DRAW_LINE,STYLE_SOLID);
   SetIndexStyle(2,DRAW_LINE,STYLE_SOLID);

   SetIndexDrawBegin(0, FFT_N*15/16+1);
   SetIndexDrawBegin(1, FFT_N*15/16+1);
   SetIndexDrawBegin(2, FFT_N*15/16+1);

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

   for(int lpct = 0 ; lpct < limit; lpct+=FFT_N) {
      if(AppliedPrice == PRICE_OPEN)
         ArrayCopy(Prices, Open, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_HIGH)
         ArrayCopy(Prices, High, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_LOW)
         ArrayCopy(Prices, Low, 0, lpct, FFT_N);
      else if(AppliedPrice == PRICE_CLOSE)
         ArrayCopy(Prices, Close, 0, lpct, FFT_N);
//  printd(Prices, FFT_N);
      /* 窓関数適用 */
   	HigashiWindow(Prices[0], Prices, FFT_N);
//  printd(Prices, FFT_N);
      /* FFT実行 */
   	FFT1024(Prices, FFT_N, tempr, tempi);
      /* デジタルフィルタをかける */
   	execFilter(tempr, tempi, FFT_N, filterary);
//  printd(filterary, FFT_N);
      /* iFFT実行 */
   	iFFT1024(tempr, tempi, FFT_N, retr);
//  printd(retr, FFT_N);
      ArrayCopy(gFft, retr, lpct, 0, FFT_N);
   }
   
   return(rates_total);
}
//+------------------------------------------------------------------+
