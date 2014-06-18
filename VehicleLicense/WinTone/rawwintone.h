#ifndef RAWWINTONE_H
#define RAWWINTONE_H

#include "../vehiclelicense.h"
//#include "TH_PlateID.h"

#define MAX_WAY ( int ) ( 4 )
#define REAL_WAY ( int ) ( 2 )
#define MEM_ONE_SIZE ( int ) ( 0x4000 )
#define MEM_TWO_SIZE ( int ) ( 40000000 )

class CRawWintone : public CVehicleLicense
{
public:
    CRawWintone();
    virtual ~CRawWintone( );

    // Define Function Pointer Prototype
    typedef int __stdcall ( *InitPlateIDSDK ) ( TH_PlateIDCfg* pPlateConfig );
    typedef int __stdcall ( *UninitPlateIDSDK ) ( TH_PlateIDCfg* pPlateCfg );
    typedef int __stdcall ( *RecogImage ) ( const unsigned char *pbyBits, int nWidth, int nHeight,
                                            TH_PlateIDResult *pResult, int *nResultNum,
                                            const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig );
    typedef int __stdcall ( *EvaluateCarColor ) ( const unsigned char *pbyBits, int nWidth, int nHeight,
                                                  TH_PlateIDResult *pResult, int *nResultNum,
                                                  const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig );
    typedef int __stdcall ( *SetImageFormat ) ( unsigned char cImageFormat, unsigned char bVertFlip,
                                                unsigned char bDwordAligned, TH_PlateIDCfg *pPlateConfig );
    typedef int __stdcall ( *SetDayNightMode ) ( unsigned char bIsNight, TH_PlateIDCfg *pPlateConfig );
    typedef int __stdcall ( *SetEnlargeMode ) ( unsigned char bEnlarge , TH_PlateIDCfg *pPlateCfg );

    typedef int __stdcall ( *SetEnabledPlateFormat ) ( unsigned int dFormat, TH_PlateIDCfg *pPlateConfig );

    typedef int __stdcall ( *SetProvinceOrder ) ( char* szProvince, TH_PlateIDCfg *pPlateConfig );
    typedef int __stdcall ( *SetRecogThreshold ) ( unsigned char nPlateLocate_Th, unsigned char nOCR_Th, TH_PlateIDCfg *pPlateCfg );

    typedef int __stdcall ( *CheckMinFreeMemory ) ( int *pnMinFreeSRAM, int *pnMinFreeSDRAM, TH_PlateIDCfg *pPlateCfg );
    typedef const char * __stdcall ( *GetVersion )( );

    typedef int __stdcall ( *SetContrast ) ( unsigned char nContrast, TH_PlateIDCfg *pPlateCfg );
    typedef int __stdcall ( *SetAutoSlopeRectifyMode ) ( unsigned char bIsAutoSlope, unsigned char nSlopeDetectRange, TH_PlateIDCfg *pPlateConfig );

public:

    bool Initialize( uint nChannel = 0 ); // Sdk
    bool Uninitialize( uint nChannel = 0 );
    bool RecognizedPlateType( QStringList& lstType );
    bool RecognizedImageFormat( QStringList& lstFormat );
    bool RecognizedSpecialParameters( QStringList& lstParam );
    bool RecognizeFile( QString& strFilePath, TH_PlateIDResult* pResult, int& nPlateNumber, int nChannel = 0 );
    bool RecognizeVideo( quint8* pImgData, int nWidth, int nHeight,
                         TH_PlateIDResult* pResult, int& nPlateNumber, int nChannel = 0 );
    bool GetPlateImgData( quint8*& pImgData, int& nWidth, int& nHeight, int& nSize, int nChannel = 0 );

    void GetPlateType( QString& strType, int nType );
    void GetPlateMoveDirection( QString& strDirection, int nDirection );
    void GetVehicleColor( QString& strColor, int nColor );
    bool PlateFilter( TH_PlateIDResult* pResult, int & nResult, int nChannel );

private:
    void SetKeyName( QStringList& lstKey );
    void SetDefault( QStringList& lstData );
    void GetFunctionPointer( );
    inline TH_PlateIDCfg& GetCfg( uint nChannel = 0 );

protected:
    void GetParameters( );

private:
    QStringList lstKeys;
    QStringList lstDefault;
    TH_PlateIDCfg cfgPlateID[ MAX_WAY ];
    quint8 MemOne[ REAL_WAY ][ MEM_ONE_SIZE ];
    quint8 MemTwo[ REAL_WAY ][ MEM_TWO_SIZE ];

    // Function Pointer
    InitPlateIDSDK MyInitPlateIDSDK;
    UninitPlateIDSDK MyUninitPlateIDSDK;
    RecogImage MyRecogImage;
    EvaluateCarColor MyEvaluateCarColor;
    SetImageFormat MySetImageFormat;
    SetDayNightMode MySetDayNightMode;
    SetEnlargeMode MySetEnlargeMode;
    SetEnabledPlateFormat MySetEnabledPlateFormat;
    SetProvinceOrder MySetProvinceOrder;
    SetRecogThreshold MySetRecogThreshold;
    CheckMinFreeMemory MyCheckMinFreeMemory;
    GetVersion MyGetVersion;
    SetContrast MySetContrast;
    SetAutoSlopeRectifyMode MySetAutoSlopeRectifyMode;

    HMODULE hDllMod;
};

#endif // RAWWINTONE_H
