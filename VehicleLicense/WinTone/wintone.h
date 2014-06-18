#ifndef WINTONE_H
#define WINTONE_H
#include "../vehiclelicense.h"
//#include "LPKernelEx.h"
#include "cyuv2bgr.h"

#define MAX_WAY ( int ) ( 4 )

class CWinTone : public CVehicleLicense
{

public:
    CWinTone();
    virtual ~CWinTone( );

public:

    bool Initialize( uint nChannel = 0 ); // Sdk
    bool Uninitialize( uint nChannel = 0 );
    bool RecognizedPlateType( QStringList& lstType );
    bool RecognizedImageFormat( QStringList& lstFormat );
    bool RecognizedSpecialParameters( QStringList& lstParam );
    bool RecognizeFile( QString& strFilePath, TH_PlateResult* pResult, int& nPlateNumber, int nChannel = 0 );
    bool RecognizeVideo( quint8* pImgData, int nWidth, int nHeight,
                         TH_PlateResult* pResult, int& nPlateNumber, int nChannel = 0 );
    bool GetPlateImgData( quint8*& pImgData, int& nWidth, int& nHeight, int& nSize, int nChannel = 0 );

    void GetPlateType( QString& strType, int nType );
    void GetPlateMoveDirection( QString& strDirection, int nDirection );
    void GetVehicleColor( QString& strColor, int nColor );
    bool PlateFilter( TH_PlateResult* pResult, int & nResult, int nChannel );

private:
    void SetKeyName( QStringList& lstKey );
    void SetDefault( QStringList& lstData );
    int CalculateDirection( TH_RECT& recDirect, int& nChannel );
    void RecordFrame( bool bSuccess, TH_PlateResult* pResult );
    void WriteLog( bool bSuccess, TH_PlateResult* pResult );

protected:
    void GetParameters( );

private:
    bool YUV2RGB( LPBYTE yuvBuf, UINT nWidth,
                                 UINT nHeight, LPBYTE pRgbBuf,
                                 unsigned long *len );

    void RGB2BGR( LPBYTE pRgbBuf, unsigned long len );

private:
    QStringList lstKeys;
    QStringList lstDefault;
    CYUV2BGR yuv2BGR;
    bool bRecordFrame;
    int nFrameRate;

};

#endif // WINTONE_H
