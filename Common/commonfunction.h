#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <QComboBox>
#include <QTableWidget>
#include <QDateTime>
#include <QTextCodec>

#if MULTIMEDIA_LIBRARY
    #include "../Common/CommonType.h"
#elif VEHICLELICENSE_LIBRARY
    #include "../Common/CommonType.h"
#elif PLATEDEMO_H
    #include "../Common/CommonType.h"
#elif PARAM_CFG_H
    #include "../Common/CommonType.h"
#elif PARKDATARECEIVER_APP
    #include "../Common/CommonType.h"
#elif PARKDATACLIENT_APP
    #include "../Common/CommonType.h"
#elif PLATFORM_SERVER
    #include "../Common/CommonType.h"
#elif PLATFORM_CLIENT
    #include "../Common/CommonType.h"
#else
    #include "Common/CommonType.h"
#endif

#include <QSettings>
#include <QMutex>
#include <QSplashScreen>
#include <phonon/phonon>

class CCommonFunction : public QObject
{
    Q_OBJECT
public:
    explicit CCommonFunction(QObject *parent = 0);

public:
    static void SetWindowIcon( QWidget* pWidget );
    static QString GetCarTypeString( QString& strIndex );
    static void OperationSuccess( QString strInfo = "" );
    static int MsgBox( QWidget* pParent, QString strTitle, QString strText, QMessageBox::Icon nType, QString strStyle = "" );
    static int FindComboBoxItem( QComboBox* pCBX, QString strText );
    static bool IsDigital( QString strText );
    static void FreeRow( QTableWidget* pTable, int nRow, int nCols );
    static void FreeAllRows( QTableWidget* pTable );
    static void FillTable( QTableWidget* pTable, int nRows, QStringList& lstRows );
    static void FillCardRightTable( QTableWidget* pTable, int nRows, QStringList& lstRows );
    static void DateTime2String( QDateTime &dtValue, QString& strText );
    static void Date2String( QDate &dtValue, QString& strText );
    static void Time2String( QTime &dtValue, QString& strText );
    static QDateTime String2DateTime( QString& strDateTime );
    static QTime String2Time( QString& strDateTime );
    static QDate String2Date( QString& strDateTime );
    static int GetDateTimeDiff( bool bDate, int nDiff, QDateTime& dtStart, QDateTime& dtEnd );
    static QTextCodec* GetTextCodec( );
    static void GetTableName( CommonDataType::CardType type, QString& strTable );
    static QSettings* GetSettings( CommonDataType::CfgType type );
    static void GetAllChannels( QStringList& lstChannel, QString& strPark, bool bEnter );
    static void GetAllParks( QStringList& lstPark );
    static int CalculateFee( QSettings& pSet, QString& strParkName, QString& strCarType,
                      QDateTime& dtStart, QDateTime& dtEnd, QStringList& lstText, bool bManual = false, bool bSect = false  );
    static void GetCarType( QComboBox* pCB );
    static int GetParkSection( QString& strName );
    static QMutex& GetSyncPass( );
    static void GetPath( QString& strFileName, CommonDataType::DataPath pathType );

    static void AddAddress( char cAddr, bool bEnter );
    static char GetAddress( int nIndex, bool bEnter );
    static int GetAddressCount( bool bEnter );
    static bool ContainAddress( char cAddr, bool bEnter );
    static void ControlSysMenu( QWidget& wg );
    static QString GetMsgTitle( QMessageBox::Icon nType );

    static CommonDataType::QEntityHash& GetCardEntity( );
    static CommonDataType::QPlateCardHash& GetPlateCardHash( );

    static void GetChannelInfo( QString& strCardNo, bool bEnter, QStringList& lstInfo );
    static QString GetHostIP( );
    static QString GetParkID( );
    static void WindowCenter( QWidget& widget );
    static void DisplayPlateChar( QLabel**pLicenseRow , int nChannel, QString& strContent );
    static QString GetFeeStd( QString &strFee );
    static void MySetWindowPos( QWidget* pWidget );
    static void ConnectCloseButton( QLabel* lblClose );
#ifdef COMMON_DB
    static void LoadFourImages( CommonDataType::BlobType blob, QString& strWhere, QLabel& lbl, bool bHistory = false );
#endif
    static void UpateCardRight( QStringList& lstRows, QTableWidget* pTable );

    static void StartupSplash( );
    static void CleanupSplash( QWidget* pWidget );
    static void ShowSplashMessage( QString strMsg );
    static QHash< char, QString >& GetCanParkIndexNum( int nIndex ); // 0 Index 1 Num 2 Name

    static void ClearAllFiles( QString& strDir );
    static void ConnectMySql( QStringList& lstParams, bool bHistory = false, int nIndex = 0 );
    static bool GetHistoryDb( );
    static void PlayMusic( QString strName, bool bStop = false );

private:
    static void CreateDiretory( QString& strPath, QString& strName );
    static QSettings* CreateSetting( QSettings** pSet, QString& strFile );

    // Fee
    static bool AddFee1( QString& strMin, QString& strFoot,
                 int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText );
    static void AddFee2( QString& strMin, QString& strFoot,
                 int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText );
    static void AddFee3( QString& strSection, QString& strMin, QString& strFootSufix,
                 int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText );
    static void AddFee4( QString& strSection, QString& strMin, QString& strFootSufix,
                 int &nFee, int& nMinDiff, QSettings &pSet, QStringList& lstText );
    static int GetTimeDiff( QTime time1, QTime time2 );
    static int GetDateTimeDiff( QDateTime& dt1, QDateTime& dt2, int  nT );
    static inline int GetQuotaValue( int nQuota, int nFee );
    static bool GetSectionAround( QTime& tSectionBegin, QTime& tSectionEnd, QDateTime& dtStart, QDateTime& dtEnd );
    static bool GetSectionAround( QTime& tSectionBegin, QTime& tSectionEnd, QDateTime& dtStart );
    //End Fee

private:
    static QSettings *pSysSettings;
    static QSettings *pFeeSettings;
    static QSettings *pDevSettings;
    static QSettings *pDbmSettings;
    static QSettings *pSysSetSettings;
    static QSettings *pPlateSettings;

    static QByteArray byteInAddr;
    static QByteArray byteOutAddr;
    static QSplashScreen* pSplash;

    static QMutex syncPass;
    static CommonDataType::QEntityHash cardEntity;
    static CommonDataType::QPlateCardHash plateCardHash; // < plate, card >
    static QHash< char, QString > hashCanParkIndex;
    static QHash< char, QString > hashCanParkNum;
    static QHash< char, QString > hashCanParkName;
signals:

public slots:

};

#endif // COMMONFUNCTION_H
