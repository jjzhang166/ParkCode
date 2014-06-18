#include "rawwintone.h"

#define ASSERT_VEHICLE( FunName ) qDebug( ) << FunName << " " << ( bRet ? "Success" : "Failed" ) << endl
#define OUTPUT_STRING( strInfo ) qDebug( ) << strInfo << endl;
#define PLATE_RECOGNIZE_ALG "TH_PLATEID.dll"

CRawWintone::CRawWintone( )
{
    hDllMod = NULL;
    SetKeyName( lstKeys );
    SetDefault( lstDefault );
    GetParameters( );
    GetFunctionPointer( );

    for ( int nIndex = 0; nIndex < MAX_WAY; nIndex++ ) {
        cfgPlateID[ nIndex ] = c_defConfig;
    }

    OUTPUT_STRING( "CRawWintone::CRawWintone( )" );
}

CRawWintone::~CRawWintone( )
{
    if ( NULL != hDllMod ) {
        BOOL bRet = ::FreeLibrary( hDllMod );
        ASSERT_VEHICLE( "FreeLibrary" );
    }
}

void CRawWintone::GetFunctionPointer( )
{
    QString strPath;
    CCommonFunction::GetPath( strPath, CommonDataType::PathExe );
    strPath += PLATE_RECOGNIZE_ALG;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyInitPlateIDSDK = ( InitPlateIDSDK ) ::GetProcAddress( hDllMod, "TH_InitPlateIDSDK" );
    MyInitPlateIDSDK = ( InitPlateIDSDK ) ::GetProcAddress( hDllMod, "TH_InitPlateIDSDK" );

    MyInitPlateIDSDK = ( InitPlateIDSDK ) ::GetProcAddress( hDllMod, "TH_InitPlateIDSDK" );
    MyUninitPlateIDSDK = ( UninitPlateIDSDK ) ::GetProcAddress( hDllMod, "TH_UninitPlateIDSDK" );
    MyRecogImage = ( RecogImage ) ::GetProcAddress( hDllMod, "TH_RecogImage" );
    MyEvaluateCarColor = ( EvaluateCarColor ) ::GetProcAddress( hDllMod, "TH_EvaluateCarColor" );
    MySetImageFormat = ( SetImageFormat ) ::GetProcAddress( hDllMod, "TH_SetImageFormat" );
    MySetDayNightMode = ( SetDayNightMode ) ::GetProcAddress( hDllMod, "TH_SetDayNightMode" );
    MySetEnlargeMode = ( SetEnlargeMode ) ::GetProcAddress( hDllMod, "TH_SetEnlargeMode" );
    MySetEnabledPlateFormat = ( SetEnabledPlateFormat ) ::GetProcAddress( hDllMod, "TH_SetEnabledPlateFormat" );
    MySetProvinceOrder = ( SetProvinceOrder ) ::GetProcAddress( hDllMod, "TH_SetProvinceOrder" );
    MySetRecogThreshold = ( SetRecogThreshold ) ::GetProcAddress( hDllMod, "TH_SetRecogThreshold" );
    MyCheckMinFreeMemory = ( CheckMinFreeMemory ) ::GetProcAddress( hDllMod, "TH_CheckMinFreeMemory" );
    MyGetVersion = ( GetVersion ) ::GetProcAddress( hDllMod, "TH_GetVersion" );
    MySetContrast = ( SetContrast ) ::GetProcAddress( hDllMod, "TH_SetContrast" );
    MySetAutoSlopeRectifyMode = ( SetAutoSlopeRectifyMode ) ::GetProcAddress( hDllMod, "TH_SetAutoSlopeRectifyMode" );
}

void CRawWintone::SetDefault( QStringList& lstData )
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
            << "704"
            << "0"
            << "576"
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

    OUTPUT_STRING( "CRawWintone::SetDefault( )" );
}

void CRawWintone::SetKeyName(QStringList &lstKey)
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

    OUTPUT_STRING( "CRawWintone::SetKeyName( )" );
}

void CRawWintone::GetParameters( )
{
    QString strSect = QString( "WintonePlate/WintonePlate%1/%2" );

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
    }

    OUTPUT_STRING( "CRawWintone::GetParameters( )" );
}

TH_PlateIDCfg& CRawWintone::GetCfg( uint nChannel )
{
    return cfgPlateID[ nChannel ];
}

bool CRawWintone::Initialize( uint nChannel )
{
    bool bRet  = false;
    if ( NULL == MyInitPlateIDSDK ) {
        return bRet;
    }

    TH_PlateIDCfg& cfg = GetCfg( nChannel );
    BOOL bMoving = 1;
    bRegVideo = bMoving;

    int nColor = ImageFormatRGB;//ImageFormatYUV422;  //ImageFormatRGB
    BOOL bCompress = FALSE;

    int nMinWidth = mapParameters[ nChannel ].value( lstKeys[ 0 ] ).toInt( );
    int nMaxWidth = mapParameters[ nChannel ].value( lstKeys[ 1 ] ).toInt( );

    BOOL bInput  = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 10 ] ).toInt( ) );
    BOOL bOutput = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 8 ] ).toInt( ) );

    cfg.bMovingImage = bMoving;
    cfg.nImageFormat = nColor;
    cfg.bVertCompress = bCompress;
    cfg.nMinPlateWidth = nMinWidth;
    cfg.nMaxPlateWidth = nMaxWidth;
    cfg.nMaxImageWidth = 704;
    cfg.nMaxImageHeight = 576;
    cfg.bIsFieldImage = bInput;
    cfg.bOutputSingleFrame = bOutput;

    cfg.pFastMemory = MemOne[ nChannel ];
    cfg.nFastMemorySize = MEM_ONE_SIZE;
    cfg.pMemory = MemTwo[ nChannel ];
    cfg.nMemorySize = MEM_TWO_SIZE;
    ///////////////////////////////////////////////
    int nRet = MyInitPlateIDSDK( &cfg );
    bRet = ( 0 == nRet );
    ASSERT_VEHICLE( "InitPlateIDSDK" );
    //////////////////////////////////////////////
    BOOL bYellow   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 11 ] ).toInt( ) );
    BOOL bIndivi   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 12 ] ).toInt( ) );
    BOOL bArmPol   = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 13 ] ).toInt( ) );
    BOOL bArmy2    = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 14 ] ).toInt( ) );
    BOOL bTractor  = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 15 ] ).toInt( ) );

    if ( MySetEnabledPlateFormat ) {
        nRet = MySetEnabledPlateFormat( bYellow ? PARAM_TWOROWYELLOW_ON : PARAM_TWOROWYELLOW_OFF, &cfg );//
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bIndivi ? PARAM_INDIVIDUAL_ON : PARAM_INDIVIDUAL_OFF, &cfg );//
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bArmPol ? PARAM_ARMPOLICE_ON : PARAM_ARMPOLICE_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bArmy2 ? PARAM_TWOROWARMY_ON : PARAM_TWOROWARMY_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bTractor ? PARAM_TRACTOR_ON : PARAM_TRACTOR_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );
    }
    ////////////////////////////////////////////////
    if ( MySetImageFormat ) {
        nRet = MySetImageFormat( ImageFormatYUV422, FALSE, FALSE, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetImageFormat" );
    }
    /////////////////////////////
    BOOL bNight         = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 16 ] ).toInt( ) );
    int nPlateThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 4 : 6 ] ).toInt( ) );
    int nRecogThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 5 : 7 ] ).toInt( ) );
    //int nPlatesNum      = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 3 ] ).toInt( ) );
    QString strProvince = mapParameters[ nChannel ].value( lstKeys[ 2 ] );
    LPSTR pProvince     = strProvince.toUtf8( ).data( );

    if ( MySetDayNightMode ) {
        nRet = MySetDayNightMode( bNight, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetDayNightMode" );
    }

    if ( MySetRecogThreshold ) {
        nRet = MySetRecogThreshold( nPlateThr, nRecogThr, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetRecogThreshold" );
    }

    if ( MySetProvinceOrder ) {
        nRet = MySetProvinceOrder( pProvince, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetProvinceOrder" );
    }
    ////////////////////////////////////////////
    OUTPUT_STRING( "CRawWintone::Initialize( )" );
    return bRet;
}

#if 0
bool CRawWintone::Initialize( uint nChannel )
{
    bool bRet  = false;
    if ( NULL == MyInitPlateIDSDK ) {
        return bRet;
    }

    TH_PlateIDCfg& cfg = GetCfg( nChannel );
    int nRet = MyInitPlateIDSDK( &cfg );
    bRet = ( 0 == nRet );
    ASSERT_VEHICLE( "InitPlateIDSDK" );

    if ( MySetImageFormat ) {
        nRet = MySetImageFormat( ImageFormatYUV422, FALSE, FALSE, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetImageFormat" );
    }

    QStringList lstParam;
    lstParam << QString::number( nChannel );
    bRet = RecognizedPlateType( lstParam );

    OUTPUT_STRING( "CRawWintone::Initialize( )" );
    return bRet;
}
#endif

bool CRawWintone::Uninitialize( uint nChannel )
{
    bool bRet = false;
    if ( NULL == MyUninitPlateIDSDK ) {
        return bRet;
    }

    TH_PlateIDCfg& cfg = GetCfg( nChannel );
    int nRet = MyUninitPlateIDSDK( &cfg );
    bRet = ( 0 == nRet );
    OUTPUT_STRING( "CRawWintone::Uninitialize( )" );
    return bRet;
}

bool CRawWintone::RecognizedPlateType( QStringList& lstType )
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

    TH_PlateIDCfg& cfg = GetCfg( nChannel );
    int nRet = 0;

    if ( MySetEnabledPlateFormat ) {
        nRet = MySetEnabledPlateFormat( bYellow ? PARAM_TWOROWYELLOW_ON : PARAM_TWOROWYELLOW_OFF, &cfg );//
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bIndivi ? PARAM_INDIVIDUAL_ON : PARAM_INDIVIDUAL_OFF, &cfg );//
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bArmPol ? PARAM_ARMPOLICE_ON : PARAM_ARMPOLICE_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bArmy2 ? PARAM_TWOROWARMY_ON : PARAM_TWOROWARMY_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );

        nRet = MySetEnabledPlateFormat( bTractor ? PARAM_TRACTOR_ON : PARAM_TRACTOR_OFF, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "MySetEnabledPlateFormat" );
    }

    OUTPUT_STRING( "CRawWintone::RecognizedPlateType( )" );

    return bRet;
}

bool CRawWintone::RecognizedImageFormat( QStringList& lstFormat /* ImageFormat, Channel */ )
{
    bool bRet = false;

    if ( 2 != lstFormat.count( ) ) {
        return bRet;
    }

    //QString strSect = "RecognizeMode/%1";
    //int nMode = pSettings->value( strSect.arg( "Current" ), 0 ).toInt( );
    BOOL bMoving = 1;//( 1 == nMode ) ? TRUE : FALSE;
    bRegVideo = bMoving;

    int nColor = lstFormat[ 0 ].toInt( );  //ImageFormatRGB
    BOOL bCompress = FALSE;

    int nChannel   = lstFormat[ 1 ].toInt( );
    int nMinWidth = mapParameters[ nChannel ].value( lstKeys[ 0 ] ).toInt( );
    int nMaxWidth = mapParameters[ nChannel ].value( lstKeys[ 1 ] ).toInt( );

    BOOL bInput  = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 10 ] ).toInt( ) );
    BOOL bOutput = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 8 ] ).toInt( ) );


    TH_PlateIDCfg& cfg = GetCfg( nChannel );
    cfg.bMovingImage = bMoving;
    cfg.nImageFormat = nColor;
    cfg.bVertCompress = bCompress;
    cfg.nMinPlateWidth = nMinWidth;
    cfg.nMaxPlateWidth = nMaxWidth;
    cfg.nMaxImageWidth = 704;
    cfg.nMaxImageHeight = 576;
    cfg.bIsFieldImage = bInput;
    cfg.bOutputSingleFrame = bOutput;

    cfg.pFastMemory = MemOne[ nChannel ];
    cfg.nFastMemorySize = MEM_ONE_SIZE;
    cfg.pMemory = MemTwo[ nChannel ];
    cfg.nMemorySize = MEM_TWO_SIZE;

    OUTPUT_STRING( "CRawWintone::RecognizedImageFormat( )" );

    bRet = true;
    return bRet;
}

bool CRawWintone::RecognizedSpecialParameters( QStringList& lstParam )
{
    bool bRet = false;

    if ( 1 != lstParam.count( ) ) {
        return bRet;
    }

    int nChannel   = lstParam[ 0 ].toInt( );
    BOOL bNight         = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 16 ] ).toInt( ) );
    int nPlateThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 4 : 6 ] ).toInt( ) );
    int nRecogThr       = ( 1 == mapParameters[ nChannel ].value( lstKeys[ bRegVideo ? 5 : 7 ] ).toInt( ) );
    //int nPlatesNum      = ( 1 == mapParameters[ nChannel ].value( lstKeys[ 3 ] ).toInt( ) );
    QString strProvince = mapParameters[ nChannel ].value( lstKeys[ 2 ] );
    LPSTR pProvince     = strProvince.toUtf8( ).data( );

    int nRet = 0;
    TH_PlateIDCfg& cfg = GetCfg( nChannel );

    if ( MySetDayNightMode ) {
        nRet = MySetDayNightMode( bNight, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetDayNightMode" );
    }

    if ( MySetRecogThreshold ) {
        nRet = MySetRecogThreshold( nPlateThr, nRecogThr, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetRecogThreshold" );
    }

    if ( MySetProvinceOrder ) {
        nRet = MySetProvinceOrder( pProvince, &cfg );
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "SetProvinceOrder" );
    }

    OUTPUT_STRING( "CRawWintone::RecognizedSpecialParameters( )" );

    return bRet;
}

bool CRawWintone::RecognizeFile( QString& strFilePath, TH_PlateIDResult* pResult, int& nPlateNumber, int nChannel )
{
    // BMP JPG TIF Format
    bool bRet = false;
    TH_RECT rect = { 0 };
    rect.left = mapParameters[ nChannel ].value( lstKeys[ 17 ] ).toInt( );
    rect.top = mapParameters[ nChannel ].value( lstKeys[ 19 ] ).toInt( );
    rect.right = mapParameters[ nChannel ].value( lstKeys[ 18 ] ).toInt( );
    rect.bottom = mapParameters[ nChannel ].value( lstKeys[ 20 ] ).toInt( );

    nPlateNumber =  0;

    QByteArray byFile = pCodec->fromUnicode( strFilePath );
    char* pFile = byFile.data( );
    QString strPlatePath = "";
    CCommonFunction::GetPath( strPlatePath, CommonDataType::PathPlate );
    QByteArray byPath = pCodec->fromUnicode( strPlatePath );
    char* pPath = byPath.data( );

    //bRet = LPR_FileEx( pFile, pPath, pResult, nPlateNumber, &rect, ++nChannel );
    ASSERT_VEHICLE( "LPR_FileEx" );
    OUTPUT_STRING( "CRawWintone::RecognizeFile( )" );

    return bRet;
}

bool CRawWintone::RecognizeVideo( quint8* pImgData, int nWidth, int nHeight,
                               TH_PlateIDResult* pResult, int& nPlateNumber, int nChannel )
{
    bool bRet = false;

    if ( NULL == pImgData || NULL == pResult ) {
        return bRet;
    }

    TH_RECT rect = { 0 };
    rect.left = mapParameters[ nChannel ].value( lstKeys[ 17 ] ).toInt( );
    rect.top = mapParameters[ nChannel ].value( lstKeys[ 19 ] ).toInt( );
    rect.right = mapParameters[ nChannel ].value( lstKeys[ 18 ] ).toInt( );
    rect.bottom = mapParameters[ nChannel ].value( lstKeys[ 20 ] ).toInt( );

    if ( MyRecogImage ) {
        TH_PlateIDCfg& cfg = GetCfg( nChannel );
        int nRet = MyRecogImage( pImgData, nWidth, nHeight, pResult, &nPlateNumber, &rect, &cfg );
        qDebug( ) <<  "Eror : "  << cfg.nLastError << endl;
        bRet = ( 0 == nRet );
        ASSERT_VEHICLE( "RecogImage" );
    }

    bRet = PlateFilter( pResult, nPlateNumber, nChannel );
    ASSERT_VEHICLE( "PlateFilter" );
    OUTPUT_STRING( "CRawWintone::RecognizeVideo( )" );

    return bRet;
}

bool CRawWintone::PlateFilter( TH_PlateIDResult *pResult, int &nResult, int nChannel )
{
    bool bRet = false;

    if ( NULL == pResult ) {
        return bRet;
    }

    const int nConfidence = mapParameters[ nChannel ].value( lstKeys[ 24 ] ).toInt( );
    const int nTime = mapParameters[ nChannel ].value( lstKeys[ 25 ] ).toInt( );
    bool bDirection =  ( 0 !=  vecDirection[ nChannel ].count( ) );
    //qDebug( ) << "Plate Direction : " << pResult[ 0 ].license;

    for ( int nIndex = 0; nIndex < nResult; nIndex++ ) {
        if ( nConfidence <= pResult[ nIndex ].nConfidence &&
             ( 0 == nTime || nTime >= pResult[ nIndex ].nTime ) ) {
            if ( bDirection && !vecDirection[ nChannel ].contains( pResult[ nIndex ].nDirection ) ) {
                continue;
            }

            strcpy( pResult[ 0 ].license, pResult[ nIndex ].license );
            pResult[ 0 ].nConfidence = pResult[ nIndex ].nConfidence;
            pResult[ 0 ].nTime = pResult[ nIndex ].nTime;
            qDebug( ) << "Plate Direction : " << pResult[ 0 ].nDirection;
            bRet = true;
            nResult = 1;
            break;
        }
    }

    OUTPUT_STRING( "CRawWintone::PlateFilter( )" );

    return bRet;
}

bool CRawWintone::GetPlateImgData( quint8*& pImgData, int& nWidth, int& nHeight,
                                int& nSize, int nChannel )
{
    bool bRet = true;//LPR_GetImageBuf( pImgData, nWidth, nHeight, nSize, ++nChannel );
    OUTPUT_STRING( "CRawWintone::GetPlateImgData( )" );

    return bRet;
}

void CRawWintone::GetPlateType( QString& strType, int nType )
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

void CRawWintone::GetPlateMoveDirection( QString& strDirection, int nDirection )
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

void CRawWintone::GetVehicleColor( QString& strColor, int nColor )
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
