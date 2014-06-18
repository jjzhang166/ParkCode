#include "wintone.h"
#include <QFile>

#define ASSERT_VEHICLE( FunName ) qDebug( ) << FunName << " " << ( bRet ? "Success" : "Failed" ) << endl
#define OUTPUT_STRING( strInfo ) qDebug( ) << strInfo << endl;
extern void YUV420ToRGB24_1(unsigned char *yuv420, unsigned char *rgb24, int width, int height) ;
CWinTone::CWinTone( )
{
    SetKeyName( lstKeys );
    SetDefault( lstDefault );
    GetParameters( );

    OUTPUT_STRING( "CWinTone::CWinTone( )" );
}

CWinTone::~CWinTone( )
{
}

void CWinTone::RGB2BGR( LPBYTE pRgbBuf, unsigned long len )
{
    for ( int nIndex = 0; nIndex < len - 2; nIndex += 2 ) {
        BYTE R = pRgbBuf[ nIndex ];
        BYTE B = pRgbBuf[ nIndex + 2 ];

        pRgbBuf[ nIndex ] = B;
        pRgbBuf[ nIndex + 2 ] = R;
    }
}

bool CWinTone::YUV2RGB( LPBYTE yuvBuf, UINT nWidth,
                                                  UINT nHeight, LPBYTE pRgbBuf,
                                                  unsigned long *len )
{
    bool bRet = true;

    //  int i, j;
    //  unsigned char*bufY, *bufU, *bufV, *bufRGB;
    //
    //  bufY = yuvBuf;
    //  bufV = yuvBuf + nWidth * nHeight;
    //  bufU = yuvBuf + int(nWidth * nHeight* 5/4);
    //  *len = 0;
    //  unsigned char y, u, v, r, g, b,testu,testv;
    //  for( j = 0; j < nHeight; j++ )
    //  {
    //   int templen = 0;
    //   //从最低行的第一个RGB开始存放
    //   //存完一行又开始存倒数第二，
    //   bufRGB = pRgbBuf + nWidth * (nHeight - 1 - j) * 3 ;
    //   for( i = 0; i < nWidth; i++ )
    //   {
    //    y = *(bufY + i + j * nWidth);
    // //    if (i%2 ==0)
    // //    {
    // //     u = *(bufU++);
    // //     v = *(bufV++);
    // //    }
    // //    else
    // //    {
    // //     u = *(bufU);
    // //     v = *(bufV);
    // //    }
    //
    //    u = *(bufU + (i>>1) +( j>>1)*nWidth/2 );
    //    v = *(bufV + (i>>1) + (j>>1)*nWidth/2 );
    //    r = y + 1.402 * (v-128);
    //    g = y - 0.344 * (u-128) - 0.714 * (v-128);
    //    b = y + 1.717 * (u-128);
    //    *( bufRGB++ ) = unsigned char (b);//max( 0, min(r, 255 ) );
    //    *( bufRGB++ ) = unsigned char (g);//max( 0, min( g, 255 ) );
    //    *( bufRGB++ ) = unsigned char (r);//max( 0, min( b, 255 ) );
    //   }
    //  }
    //   *len = 3*nWidth*nHeight;
    //  return true;
    #define PIXELSIZE nWidth * nHeight

     //========================================================================
     const int Table_fv1[256]={ -180, -179, -177, -176, -174, -173, -172, -170, -169, -167, -166, -165, -163, -162, -160, -159, -158, -156, -155, -153, -152, -151, -149, -148, -146, -145, -144, -142, -141, -139, -138, -137, -135, -134, -132, -131, -130, -128, -127, -125, -124, -123, -121, -120, -118, -117, -115, -114, -113, -111, -110, -108, -107, -106, -104, -103, -101, -100, -99, -97, -96, -94, -93, -92, -90, -89, -87, -86, -85, -83, -82, -80, -79, -78, -76, -75, -73, -72, -71, -69, -68, -66, -65, -64, -62, -61, -59, -58, -57, -55, -54, -52, -51, -50, -48, -47, -45, -44, -43, -41, -40, -38, -37, -36, -34, -33, -31, -30, -29, -27, -26, -24, -23, -22, -20, -19, -17, -16, -15, -13, -12, -10, -9, -8, -6, -5, -3, -2, 0, 1, 2, 4, 5, 7, 8, 9, 11, 12, 14, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 29, 30, 32, 33, 35, 36, 37, 39, 40, 42, 43, 44, 46, 47, 49, 50, 51, 53, 54, 56, 57, 58, 60, 61, 63, 64, 65, 67, 68, 70, 71, 72, 74, 75, 77, 78, 79, 81, 82, 84, 85, 86, 88, 89, 91, 92, 93, 95, 96, 98, 99, 100, 102, 103, 105, 106, 107, 109, 110, 112, 113, 114, 116, 117, 119, 120, 122, 123, 124, 126, 127, 129, 130, 131, 133, 134, 136, 137, 138, 140, 141, 143, 144, 145, 147, 148, 150, 151, 152, 154, 155, 157, 158, 159, 161, 162, 164, 165, 166, 168, 169, 171, 172, 173, 175, 176, 178 };
     const int Table_fv2[256]={ -92, -91, -91, -90, -89, -88, -88, -87, -86, -86, -85, -84, -83, -83, -82, -81, -81, -80, -79, -78, -78, -77, -76, -76, -75, -74, -73, -73, -72, -71, -71, -70, -69, -68, -68, -67, -66, -66, -65, -64, -63, -63, -62, -61, -61, -60, -59, -58, -58, -57, -56, -56, -55, -54, -53, -53, -52, -51, -51, -50, -49, -48, -48, -47, -46, -46, -45, -44, -43, -43, -42, -41, -41, -40, -39, -38, -38, -37, -36, -36, -35, -34, -33, -33, -32, -31, -31, -30, -29, -28, -28, -27, -26, -26, -25, -24, -23, -23, -22, -21, -21, -20, -19, -18, -18, -17, -16, -16, -15, -14, -13, -13, -12, -11, -11, -10, -9, -8, -8, -7, -6, -6, -5, -4, -3, -3, -2, -1, 0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 27, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 39, 40, 40, 41, 42, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 62, 63, 64, 65, 65, 66, 67, 67, 68, 69, 70, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 79, 80, 80, 81, 82, 82, 83, 84, 85, 85, 86, 87, 87, 88, 89, 90, 90 };
     const int Table_fu1[256]={ -44, -44, -44, -43, -43, -43, -42, -42, -42, -41, -41, -41, -40, -40, -40, -39, -39, -39, -38, -38, -38, -37, -37, -37, -36, -36, -36, -35, -35, -35, -34, -34, -33, -33, -33, -32, -32, -32, -31, -31, -31, -30, -30, -30, -29, -29, -29, -28, -28, -28, -27, -27, -27, -26, -26, -26, -25, -25, -25, -24, -24, -24, -23, -23, -22, -22, -22, -21, -21, -21, -20, -20, -20, -19, -19, -19, -18, -18, -18, -17, -17, -17, -16, -16, -16, -15, -15, -15, -14, -14, -14, -13, -13, -13, -12, -12, -11, -11, -11, -10, -10, -10, -9, -9, -9, -8, -8, -8, -7, -7, -7, -6, -6, -6, -5, -5, -5, -4, -4, -4, -3, -3, -3, -2, -2, -2, -1, -1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43 };
     const int Table_fu2[256]={ -227, -226, -224, -222, -220, -219, -217, -215, -213, -212, -210, -208, -206, -204, -203, -201, -199, -197, -196, -194, -192, -190, -188, -187, -185, -183, -181, -180, -178, -176, -174, -173, -171, -169, -167, -165, -164, -162, -160, -158, -157, -155, -153, -151, -149, -148, -146, -144, -142, -141, -139, -137, -135, -134, -132, -130, -128, -126, -125, -123, -121, -119, -118, -116, -114, -112, -110, -109, -107, -105, -103, -102, -100, -98, -96, -94, -93, -91, -89, -87, -86, -84, -82, -80, -79, -77, -75, -73, -71, -70, -68, -66, -64, -63, -61, -59, -57, -55, -54, -52, -50, -48, -47, -45, -43, -41, -40, -38, -36, -34, -32, -31, -29, -27, -25, -24, -22, -20, -18, -16, -15, -13, -11, -9, -8, -6, -4, -2, 0, 1, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 37, 39, 40, 42, 44, 46, 47, 49, 51, 53, 54, 56, 58, 60, 62, 63, 65, 67, 69, 70, 72, 74, 76, 78, 79, 81, 83, 85, 86, 88, 90, 92, 93, 95, 97, 99, 101, 102, 104, 106, 108, 109, 111, 113, 115, 117, 118, 120, 122, 124, 125, 127, 129, 131, 133, 134, 136, 138, 140, 141, 143, 145, 147, 148, 150, 152, 154, 156, 157, 159, 161, 163, 164, 166, 168, 170, 172, 173, 175, 177, 179, 180, 182, 184, 186, 187, 189, 191, 193, 195, 196, 198, 200, 202, 203, 205, 207, 209, 211, 212, 214, 216, 218, 219, 221, 223, 225 };
     *len = 3* nWidth * nHeight;

      if(!yuvBuf || !pRgbBuf)
       return false;

      const long nYLen = long(PIXELSIZE);
      const int nHfWidth = (nWidth>>1);

      if(nYLen<1 || nHfWidth<1)
       return false;

      // Y data
      unsigned char* yData = yuvBuf;
      // v data
      unsigned char* vData = &yData[nYLen];
      // u data
      unsigned char* uData = &vData[nYLen>>2];

      if(!uData || !vData)
       return false;

      int rgb[3];
      int i, j, m, n, x, y, pu, pv, py, rdif, invgdif, bdif;
      m = -nWidth;
      n = -nHfWidth;

      bool addhalf = true;
      for(y=0; y<nHeight;y++) {
       m += nWidth;
       if( addhalf ){
        n+=nHfWidth;
        addhalf = false;
       } else {
        addhalf = true;
       }
       for(x=0; x<nWidth;x++)  {
        i = m + x;
        j = n + (x>>1);

        py = yData[i];

        // search tables to get rdif invgdif and bidif
        rdif = Table_fv1[vData[j]];    // fv1
        invgdif = Table_fu1[uData[j]] + Table_fv2[vData[j]]; // fu1+fv2
        bdif = Table_fu2[uData[j]]; // fu2
        rgb[0] = py+rdif;    // R
        rgb[1] = py-invgdif; // G
        rgb[2] = py+bdif;    // B
        j = nYLen - nWidth - m + x;
        i = (j<<1) + j;

        // copy this pixel to rgb data
        for(j=0; j<3; j++)
        {
         if(rgb[j]>=0 && rgb[j]<=255){
          pRgbBuf[i + j] = rgb[j];
         }
         else{
          pRgbBuf[i + j] = (rgb[j] < 0)? 0 : 255;
         }
        }
       }
      }

      RGB2BGR( pRgbBuf, *len );

    return bRet;
}

void CWinTone::SetDefault( QStringList& lstData )
{
    lstData << "80"
            << "400"
            << "川"
            << "1"
            << "7"
            << "5"
            << "5"
            << "1"
            << "1"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "0"
            << "25"
            << "2"
            << "80"
            << "150"
            << "0"
            << "703"
            << "0"
            << "575"
            << "1"
            << "0"
            << "0"
            << "1"
            << "1"
            << "1"
            << "1";

    OUTPUT_STRING( "CWinTone::SetDefault( )" );
}

void CWinTone::SetKeyName(QStringList &lstKey)
{
    lstKey << "PlateMin"
           << "PlateMax"
           << "PlateProvince"
           << "PlateMaxOutput"
           << "PlateVideoPosThreshold"
           << "PlateVideoRegThreshold"
           << "PlateImagePosThreshold"
           << "PlateImageRegThreshold"
           << "PlateOnlyOnceOutput"
           << "PlateInterleaveSample"
           << "PlateInputEntranceImage"
           << "PlateRegDualYellowCard"
           << "PlateRegIndividuationCard"
           << "PlateRegMilitaryCard"
           << "PlateRegDualMilitaryCard"
           << "PlateRegFarmCard"
           << "PlateNightMode"
           << "PlateAreaLeft"
           << "PlateAreaRight"
           << "PlateAreaUp"
           << "PlateAreaDown"
           << "PlateDetectionDelay"
           << "PlateFrameRate"
           << "PlateGrade"
           << "PlateConfidence"
           << "PlateRecognizationTime"
           << "PlateDetectionLeft"
           << "PlateDetectionRight"
           << "PlateDetectionUp"
           << "PlateDetectionDown"
           << "PlateStart"
           << "PlateBlacklist"
           << "PlatePrecision"
           << "PlateLeft"
           << "PlateRight"
           << "PlateUp"
           << "PlateDown";

    OUTPUT_STRING( "CWinTone::SetKeyName( )" );
}

void CWinTone::GetParameters( )
{
    // [WintonePlate]
    // RecordFrame=true
    bRecordFrame = pSettings->value( "WintonePlate/RecordFrame", false ).toBool( );
    nFrameRate = pSettings->value( "WintonePlate/FrameRate", 25 ).toInt( );
    QString strSect = QString( "WintonePlate/WintonePlate%1/%2" );
    QString strWay[ ] = { "CameraDirection/OneWay", "CameraDirection/TwoWay",
                          "CameraDirection/ThreeWay", "CameraDirection/FourWay" };

    for ( int nIndex = 0; nIndex < PLATE_WAY; nIndex++ ) {
        QString strIndex = QString::number( nIndex );

        for ( int nItem = 0; nItem < lstKeys.count( ); nItem++ ) {
            QString& strKey = lstKeys[ nItem ];
            QString strVaule = pSettings->value( strSect.arg( strIndex, strKey ), lstDefault[nItem ] ).toString( );
            mapParameters[ nIndex ].insert( strKey, strVaule );

            if ( 32 < nItem && "0" != strVaule ) {
                vecDirection[ nIndex ].append( nItem - 32 );
            }
            qDebug( ) << strIndex << " : " << strSect.arg( strIndex, strKey ) << " = " << strVaule << endl;
        }

        //if ( 0 >= vecDirection[ nIndex ].count( ) ) {
        //   vecDirection[ nIndex ].append( 0 ); // Don't refer direction
        //}

        nCameraDirection[ nIndex ] = pSettings->value( strWay[ nIndex ], 0 ).toInt( );
    }

    OUTPUT_STRING( "CWinTone::GetParameters( )" );
}

bool CWinTone::Initialize( uint nChannel )
{
    bool bRet  = false;
    bRet = LPR_InitEx( ++nChannel );
    ASSERT_VEHICLE( "LPR_InitEx" );
    QStringList lstParam;
    lstParam << QString::number( --nChannel );
    bRet = RecognizedPlateType( lstParam );

    OUTPUT_STRING( "CWinTone::Initialize( )" );
    return bRet;
}

bool CWinTone::Uninitialize( uint nChannel )
{
    bool bRet = true;
    LPR_UninitEx( ++nChannel );
    OUTPUT_STRING( "CWinTone::Uninitialize( )" );
    return bRet;
}

bool CWinTone::RecognizedPlateType( QStringList& lstType )
{
    bool bRet = false;
    if ( 1 != lstType.count( ) ) {
        return bRet;
    }

    int nChannel   = lstType[ 0 ].toInt( );
    BOOL bYellow   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 11 ] ).toInt( ) );
    BOOL bIndivi   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 12 ] ).toInt( ) );
    BOOL bArmPol   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 13 ] ).toInt( ) );
    BOOL bArmy2    = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 14 ] ).toInt( ) );
    BOOL bTractor  = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 15 ] ).toInt( ) );
    bRet = LPR_SetPlateType(TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,++nChannel);
    //bRet = LPR_SetPlateType(TRUE,FALSE,FALSE,FALSE,FALSE,++nChannel);

    typedef BOOL ( WINAPI* OldFun ) ( BOOL, BOOL, BOOL, BOOL, BOOL, int );
    //typedef BOOL ( WINAPI* OldFun ) ( BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, int );
    if ( !bRet ) {
        HMODULE hMod = LoadLibrary( L"LPKernelEx.dll" );

        if  ( NULL !=hMod  ) {
            OldFun fun = ( OldFun ) GetProcAddress( hMod, "LPR_SetPlateType" );
            if ( NULL != fun ) {
                bRet = fun( TRUE,FALSE,FALSE,FALSE,FALSE,++nChannel );
                //bRet = fun( TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,++nChannel );
                FreeLibrary( hMod );
            }
        }
    }
    //bRet = LPR_SetPlateType( bYellow, bIndivi, bArmPol, bArmy2, bTractor,
    //                         FALSE, FALSE, FALSE, FALSE, ++nChannel );
    ASSERT_VEHICLE( "LPR_SetPlateType" );
    OUTPUT_STRING( "CWinTone::RecognizedPlateType( )" );

    return bRet;
}

bool CWinTone::RecognizedImageFormat( QStringList& lstFormat /* ImageFormat, Channel */ )
{
    bool bRet = false;

    if ( 2 != lstFormat.count( ) ) {
        return bRet;
    }

    //QString strSect = "RecognizeMode/%1";
    //int nMode = pSettings->value( strSect.arg( "Current" ), 0 ).toInt( );
    BOOL bMoving = FALSE;//( 1 == nMode ) ? TRUE : FALSE;
    bRegVideo = bMoving;
    BOOL bFlip = FALSE;

    int nColor = lstFormat[ 0 ].toInt( );  //ImageFormatRGB
    BOOL bCompress = FALSE;

    int nChannel   = lstFormat[ 1 ].toInt( );
    int nMinWidth = mapParameters[ nChannel ].value( lstKeys[ 0 ] ).toInt( );
    int nMaxWidth = mapParameters[ nChannel ].value( lstKeys[ 1 ] ).toInt( );

    BOOL bAlign = TRUE;
//ImageFormatBGR ImageFormatYUV420 ImageFormatYUV420COMPASS
    BOOL bInput  = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 10 ] ).toInt( ) );
    BOOL bOutput = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 8 ] ).toInt( ) );
    bRet = LPR_SetImageFormat(FALSE,FALSE,nColor,FALSE,60,400,TRUE,FALSE,FALSE, ++nChannel );
    //bRet = LPR_SetImageFormat( bMoving, bFlip, nColor, bCompress, nMinWidth,
    //                           nMaxWidth, bAlign, bInput, bOutput, ++nChannel );
    //bRet = LPR_SetImageFormat(TRUE,TRUE,ImageFormatBGR,TRUE,80,400,TRUE,FALSE,TRUE,1);
    ASSERT_VEHICLE( "LPR_SetImageFormat" );
    OUTPUT_STRING( "CWinTone::RecognizedImageFormat( )" );

    return bRet;
}

bool CWinTone::RecognizedSpecialParameters( QStringList& lstParam )
{
    bool bRet = false;

    if ( 1 != lstParam.count( ) ) {
        return bRet;
    }

    int nChannel   = lstParam[ 0 ].toInt( );
    BOOL bNight         = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 16 ] ).toInt( ) );
    int nPlateThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 4 : 6 ] ).toInt( ) );
    int nRecogThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 5 : 7 ] ).toInt( ) );
    int nPlatesNum      = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 3 ] ).toInt( ) );
    QString strProvince = mapParameters[ nChannel ].value( lstKeys[ 2 ] );
    LPSTR pProvince     = strProvince.toUtf8( ).data( );
    bRet = LPR_SetSpecialParameters(FALSE,7,5,6,pProvince,++nChannel); //video
    //bRet = LPR_SetSpecialParameters(FALSE,5,2,6,pProvince,++nChannel); //Picture
    //bRet = LPR_SetSpecialParameters( bNight, nPlateThr, nRecogThr, nPlatesNum,
    //                                 pProvince, ++nChannel );
    ASSERT_VEHICLE( "LPR_SetSpecialParameters" );
    OUTPUT_STRING( "CWinTone::RecognizedSpecialParameters( )" );

    return bRet;
}

bool CWinTone::RecognizeFile( QString& strFilePath, TH_PlateResult* pResult, int& nPlateNumber, int nChannel )
{
    // BMP JPG TIF Format
    bool bRet = false;
    TH_RECT rect = { 0 };
    //rect.left = mapParameters[ nChannel ].value( lstKeys[ 17 ] ).toInt( );
    //rect.top = mapParameters[ nChannel ].value( lstKeys[ 19 ] ).toInt( );
    //rect.right = mapParameters[ nChannel ].value( lstKeys[ 18 ] ).toInt( );
    //rect.bottom = mapParameters[ nChannel ].value( lstKeys[ 20 ] ).toInt( );

    nPlateNumber =  0;

    QByteArray byFile = pCodec->fromUnicode( strFilePath );
    char* pFile = byFile.data( );
    QString strPlatePath = "";
    CCommonFunction::GetPath( strPlatePath, CommonDataType::PathPlate );
    QByteArray byPath = pCodec->fromUnicode( strPlatePath );
    char* pPath = byPath.data( );

    bRet = LPR_FileEx( pFile, pPath, pResult, nPlateNumber, &rect, ++nChannel );
    ASSERT_VEHICLE( "LPR_FileEx" );
    OUTPUT_STRING( "CWinTone::RecognizeFile( )" );
    //WriteLog( bRet, pResult );

    return bRet;
}

void CWinTone::WriteLog( bool bSuccess, TH_PlateResult *pResult )
{
    static QFile file( "d:/test.txt");
    if ( !file.isOpen( ) ) {
        file.open( QFile::ReadWrite | QFile::Truncate );
    }

    static QTextStream stream( &file );

    stream << QDateTime::currentDateTime( ).toString( "yyyy-MM-dd HH:mm:ss" )
           <<" " << ( bSuccess ? QString( pResult->license ) : "Failed" ) << "\r\n";
}

bool CWinTone::RecognizeVideo( quint8* pImgData, int nWidth, int nHeight,
                               TH_PlateResult* pResult, int& nPlateNumber, int nChannel )
{
    bool bRet = false;

    if ( NULL == pImgData || bStoping ) {
        return bRet;
    }

    TH_RECT rect = { 0 };
    rect.left = mapParameters[ nChannel ].value( lstKeys[ 17 ] ).toInt( );
    rect.top = mapParameters[ nChannel ].value( lstKeys[ 19 ] ).toInt( );
    rect.right = mapParameters[ nChannel ].value( lstKeys[ 18 ] ).toInt( );
    rect.bottom = mapParameters[ nChannel ].value( lstKeys[ 20 ] ).toInt( );

    //unsigned long nLen = nWidth * nHeight * 3;
    //LPBYTE pBGR = new BYTE[ nLen ];
    //YUV420ToRGB24_1( pImgData, pBGR, nWidth, nHeight );
    //YUV2RGB( pImgData, nWidth, nHeight, pBGR, &nLen );
    //yuv2BGR.RGB2BGR( pImgData, pBGR, nWidth, nHeight );
    // 没有加密狗崩溃
    try {
        //bRet = false;
        bRet = LPR_RGB888Ex( pImgData, nWidth, nHeight, pResult, nPlateNumber, &rect, ++nChannel );
        if ( bRecordFrame ) {
            RecordFrame( bRet, pResult );
        }
    } catch ( ...  ) {
        qDebug( ) << "Test";
    }

    //delete pBGR;
    delete pImgData; // 2012-09-06 modify

    ASSERT_VEHICLE( "LPR_RGB888Ex" );
    if ( bRet ) {
        bRet = PlateFilter( pResult, nPlateNumber, --nChannel );
    }

    ASSERT_VEHICLE( "PlateFilter" );
    OUTPUT_STRING( "CWinTone::RecognizeVideo( )" );

    return bRet;
}

void CWinTone::RecordFrame( bool bSuccess, TH_PlateResult *pResult )
{
    static int nConter = nFrameRate;
    static QFile file;

    QTime time;
    QString strText = "";

    if ( !file.isOpen( ) ) {
        file.setFileName( "c:/FrameRate.txt" );
        file.open( QIODevice::WriteOnly | QIODevice::Append );
    }

    if ( nConter == nFrameRate ) {
        time = QTime::currentTime( );
        strText = time.toString( "Begin hh:mm:ss.zzz" ) + "\r\n";
    }

    strText += QString( "FrameCount %1\r\n" ).arg( nConter );

    if ( bSuccess ) {
        strText += QString( "Plate %1\r\n" ).arg( QString( pResult->license ) );
    }

    if ( 0 == ( --nConter ) ) {
        time = QTime::currentTime( );
        strText += time.toString( "End hh:mm:ss.zzz" ) + "\r\n";
        nConter = nFrameRate;
    }

    QByteArray byData = strText.toAscii( );
    file.write( byData );
    file.flush( );
}

int CWinTone::CalculateDirection( TH_RECT& recDirect, int& nChannel )
{
    static int nFirst[ PLATE_WAY ] = { 0 };
    int nDelta = 0;

    qDebug( ) << "nFirst[ nChannel ]1 : " << QString::number( nFirst[ nChannel ] ) << endl;
    switch ( nCameraDirection[ nChannel ] ) {
    case DIRECTION_LEFT :
    case DIRECTION_RIGHT :
        nDelta = recDirect.left - nFirst[ nChannel ];
        nFirst[ nChannel ] = recDirect.left;

        nDelta = ( nDelta < 0 ) ? DIRECTION_LEFT : DIRECTION_RIGHT;
        break;

    case DIRECTION_UP :
    case DIRECTION_DOWN :
        nDelta = recDirect.top - nFirst[ nChannel ];
        nFirst[ nChannel ] = recDirect.top;

        nDelta = ( nDelta < 0 ) ? DIRECTION_UP : DIRECTION_DOWN;
        break;
    }

    qDebug( ) << "nFirst[ nChannel ]2 : " << QString::number( nFirst[ nChannel ] ) << endl;

    return nDelta;
}

bool CWinTone::PlateFilter( TH_PlateResult *pResult, int &nResult, int nChannel )
{
    bool bRet = false;

    if ( NULL == pResult ) {
        return bRet;
    }

    const int nConfidence = mapParameters[ nChannel ].value( lstKeys[ 24 ] ).toInt( );
    const int nTime = mapParameters[ nChannel ].value( lstKeys[ 25 ] ).toInt( );
    //bool bDirection =  ( 0 !=  vecDirection[ nChannel ].count( ) );

    for ( int nIndex = 0; nIndex < nResult; nIndex++ ) {
        //pResult[ nIndex ].nDirection = CalculateDirection( pResult[ nIndex ].rcLocation, nChannel );
        if ( nConfidence <= pResult[ nIndex ].nConfidence &&
             ( 0 == nTime || nTime >= pResult[ nIndex ].nTime ) ) {
            //if ( bDirection && !vecDirection[ nChannel ].contains( pResult[ nIndex ].nDirection ) ) {
             //   continue;
            //}

            strcpy( pResult[ 0 ].license, pResult[ nIndex ].license );
            pResult[ 0 ].nConfidence = pResult[ nIndex ].nConfidence;
            //CCommonFunction::MsgBox( NULL, "Test", QString::number( pResult[ nIndex ].nConfidence ), QMessageBox::Information );
            //CCommonFunction::MsgBox( NULL, "Test", QString::number( pResult[ 0 ].nConfidence ), QMessageBox::Information );
            pResult[ 0 ].nTime = pResult[ nIndex ].nTime;
            //qDebug( ) << "Plate Direction : " << pResult[ 0 ].nDirection;
            bRet = true;
            nResult = 1;
            break;
        }
    }

    OUTPUT_STRING( "CWinTone::PlateFilter( )" );

    return bRet;
}

bool CWinTone::GetPlateImgData( quint8*& pImgData, int& nWidth, int& nHeight,
                                int& nSize, int nChannel )
{
    bool bRet = TRUE;//LPR_GetImageBuf( pImgData, nWidth, nHeight, nSize, ++nChannel );
    OUTPUT_STRING( "CWinTone::GetPlateImgData( )" );

    return bRet;
}

void CWinTone::GetPlateType( QString& strType, int nType )
{
    strType= "";

    switch ( nType ) {
    case LT_UNKNOWN :
        strType = "未知车牌";
        break;

    case LT_BLUE :
        strType = "蓝牌小汽车";
        break;

    case LT_BLACK :
        strType = "黑牌小汽车";
        break;

    case LT_YELLOW :
        strType = "单排黄牌";
        break;

    case LT_YELLOW2 :
        strType = "双排黄牌（大车尾牌，农用车）";
        break;

    case LT_POLICE :
        strType = "警车车牌";
        break;

    case LT_ARMPOL :
        strType = "武警车牌";
        break;

    case LT_INDIVI :
        strType = "个性化车牌";
        break;

    case LT_ARMY :
        strType = "单排军车牌";
        break;

    case LT_ARMY2 :
        strType = "双排军车牌";
        break;

    case LT_EMBASSY :
        strType = "使馆车牌";
        break;

    case LT_HONGKONG :
        strType = "香港车牌";
        break;

    case LT_TRACTOR :
        strType = "农用车牌";
        break;
    }
}

void CWinTone::GetPlateMoveDirection( QString& strDirection, int nDirection )
{
    strDirection = "";

    switch ( nDirection ) {
    case DIRECTION_LEFT :
        strDirection = "左";
        break;

    case DIRECTION_RIGHT :
        strDirection = "右";
        break;

    case DIRECTION_UP :
        strDirection = "上";
        break;

    case DIRECTION_DOWN :
        strDirection = "下";
        break;
    default :
        strDirection = "无";
        break;
    }
}

void CWinTone::GetVehicleColor( QString& strColor, int nColor )
{
    strColor = "";

    switch ( nColor ) {
    case LCOLOUR_WHITE :
        strColor = "白";
        break;

    case LCOLOUR_SILVER :
        strColor = "灰(银)";
        break;

    case LCOLOUR_YELLOW :
        strColor = "黄";
        break;

    case LCOLOUR_PINK :
        strColor = "粉";
        break;

    case LCOLOUR_RED :
        strColor = "红";
        break;

    case LCOLOUR_GREEN :
        strColor = "绿";
        break;

    case LCOLOUR_BLUE :
        strColor = "蓝";
        break;

    case LCOLOUR_BROWN :
        strColor = "棕";
        break;

    case LCOLOUR_BLACK :
        strColor = "黑";
        break;
    }
}
