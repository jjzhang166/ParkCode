#ifndef VEHICLELICENSE_H
#define VEHICLELICENSE_H

#include <QObject>
#include <windows.h>
#include "VehicleLicense_global.h"
#include <QMessageBox>
#include <QDebug>
#include "../Common/commonfunction.h"
#include <QImage>

#ifdef RAW_API
#include "WinTone/TH_PlateID.h"
#else
#include "WinTone/LPKernelEx.h"
#endif

#define ONE_K       ( int ) ( 1024 )
#define ONE_M       ( int ) ( 1024 * 1024 )
#define PLATE_WAY ( int ) ( 4 )


class VEHICLELICENSESHARED_EXPORT CVehicleLicense : public QObject {

    Q_OBJECT
public:
    explicit CVehicleLicense(QObject *parent = 0);
    virtual ~CVehicleLicense( );

public:

    typedef enum __LicenseSdk {
        WinToneSdk,
    } LicenseSdk;

    void SetStop( bool bStop );

    virtual bool Initialize( uint nChannel = 0 )   = 0; // Sdk
    virtual bool Uninitialize( uint nChannel = 0 ) = 0;
    virtual bool RecognizedPlateType( QStringList& lstType ) = 0;
    virtual bool RecognizedImageFormat( QStringList& lstFormat ) = 0;
    virtual bool RecognizedSpecialParameters( QStringList& lstParam ) = 0;
    virtual bool RecognizeFile( QString& strFilePath,
#ifdef RAW_API
                                TH_PlateIDResult* pResult
#else
                                TH_PlateResult* pResult
#endif
                                , int& nPlateNumber, int nChannel = 0 ) = 0;
    virtual bool RecognizeVideo( quint8* pImgData, int nWidth, int nHeight,
#ifdef RAW_API
                                TH_PlateIDResult* pResult
#else
                                TH_PlateResult* pResult
#endif
                                , int& nPlateNumber, int nChannel = 0 ) = 0;
    virtual bool GetPlateImgData( quint8*& pImgData, int& nWidth, int& nHeight, int& nSize, int nChannel = 0 ) = 0;

    virtual void GetPlateType( QString& strType, int nType ) = 0;
    virtual void GetPlateMoveDirection( QString& strDirection, int nDirection ) = 0;
    virtual void GetVehicleColor( QString& strColor, int nColor ) = 0;
    virtual bool PlateFilter(
#ifdef RAW_API
                                TH_PlateIDResult* pResult
#else
                                TH_PlateResult* pResult
#endif
                                , int & nResult, int nChannel ) = 0;

    static CVehicleLicense* CreateInstance( LicenseSdk sdkType );
    static void DestroyInstance( CVehicleLicense* pInstance );

protected:

    virtual void GetParameters( ) = 0;
    void GetLibPath( QString& strLibPath );
    void SetMsgBox( QString& strText, QString& strTitle,
                    QMessageBox::StandardButton stdButton = QMessageBox::Ok,
                    QMessageBox::Icon ico = QMessageBox::Information );



protected:

    QMessageBox msgBox;
    QSettings* pSettings;
    bool bRegVideo;
    bool bStoping;

    QTextCodec* pCodec;
    QHash< QString, QString >  mapParameters[ PLATE_WAY ];
    QVector< int > vecDirection[ PLATE_WAY ];
    int nCameraDirection[ PLATE_WAY ];

};

#endif // VEHICLELICENSE_H
