#include "cyuv2bgr.h"

CYUV2BGR::CYUV2BGR(QObject *parent) :
    QObject(parent)
{
    InitColorSpace( );
}

void CYUV2BGR::RGB2BGR( LPBYTE pYUV420, LPBYTE pBGR, UINT nWidth, UINT nHeight )
{
#define PIXELSIZE nWidth * nHeight
 UINT nLen = 3* nWidth * nHeight;

  const long nYLen = long(PIXELSIZE);
  const int nHfWidth = (nWidth>>1);

  if(nYLen<1 || nHfWidth<1)
   return;

  // Y data
  unsigned char* yData = pYUV420;
  // v data
  unsigned char* vData = &yData[nYLen];
  // u data
  unsigned char* uData = &vData[nYLen>>2];


  YUV420_RGB24_3Pixel( pBGR, yData, uData, vData, nWidth );

  for ( int nIndex = 0; nIndex < nLen - 2; nIndex += 2 ) {
      BYTE R = pBGR[ nIndex ];
      BYTE B = pBGR[ nIndex + 2 ];

      pBGR[ nIndex ] = B;
      pBGR[ nIndex + 2 ] = R;
  }
}

void   CYUV2BGR::YUV420_RGB24_3Pixel(LPBYTE   pRGB,   LPBYTE   pY,   LPBYTE   pU,   LPBYTE   pV,   UINT   Width)
{
    int   nRGB4Y   =   0;
    int   nB4U       =   g_B4U_Tab[pU[0]];
    int   nG4UV     =   g_G4U_Tab[pU[0]]   +   g_G4V_Tab[pV[0]];
    int   nR4V       =   g_R4V_Tab[pV[0]];
    int WidthStep=Width*3;
    //R <- Y + 1.403*(Cr - delta)
    //G <- Y - 0.344*(Cr - delta) - 0.714*(Cb - delta)
    //B <- Y + 1.773*(Cb - delta),



    //   (0,   0)

    nRGB4Y   =   g_RGB4Y_Tab[pY[0]];

    pRGB[0]   =   ClipColorValue((nRGB4Y   +   nB4U   )   >>   SCALEBITS);
    pRGB[1]   =   ClipColorValue((nRGB4Y   -   nG4UV)   >>   SCALEBITS);
    pRGB[2]   =   ClipColorValue((nRGB4Y   +   nR4V   )   >>   SCALEBITS);


    //   (0,   1)

    nRGB4Y   =   g_RGB4Y_Tab[pY[1]];

    pRGB[3]   =   ClipColorValue((nRGB4Y   +   nB4U   )   >>   SCALEBITS);
    pRGB[4]   =   ClipColorValue((nRGB4Y   -   nG4UV)   >>   SCALEBITS);
    pRGB[5]   =   ClipColorValue((nRGB4Y   +   nR4V   )   >>   SCALEBITS);



    //   (1,   0)

    nRGB4Y   =   g_RGB4Y_Tab[pY[Width]];

    pRGB[WidthStep+0]   =   ClipColorValue((nRGB4Y   +   nB4U   )   >>   SCALEBITS);
    pRGB[WidthStep+1]   =   ClipColorValue((nRGB4Y   -   nG4UV)   >>   SCALEBITS);
    pRGB[WidthStep+2]   =   ClipColorValue((nRGB4Y   +   nR4V   )   >>   SCALEBITS);


    //   (1,   1)

    nRGB4Y   =   g_RGB4Y_Tab[pY[Width+1]];

    pRGB[WidthStep+3]   =   ClipColorValue((nRGB4Y   +   nB4U   )   >>   SCALEBITS);
    pRGB[(WidthStep)+4]   =   ClipColorValue((nRGB4Y   -   nG4UV)   >>   SCALEBITS);
    pRGB[(WidthStep)+5]   =   ClipColorValue((nRGB4Y   +   nR4V   )   >>   SCALEBITS);
}

void   CYUV2BGR::InitColorSpace()
{
    for   (UINT   i   =   0;   i   <   256;   i++)
    {
        g_RGB4Y_Tab[i] = FIX(RGB4Y)   *   (i   -   Y2ADD);
        g_B4U_Tab[i] =   FIX(B4U     )   *   (i   -   U2ADD);
        g_G4U_Tab[i] =   FIX(G4U     )   *   (i   -   U2ADD);
        g_G4V_Tab[i] =   FIX(G4V     )   *   (i   -   V2ADD);
        g_R4V_Tab[i] =   FIX(R4V     )   *   (i   -   V2ADD);
    }
}
