#include "processcpuid.h"
#include <QDateEdit>
#include <QFileDialog>

CProcessCpuid::CProcessCpuid( QTableWidget* pWidget, QObject *parent ) :
    QObject(parent), pTableWidget( pWidget )
{
    connect( &CNetwork::Singleton( ), SIGNAL( OnReceiveDatagram( QStringList& ) ), this, SLOT( CpuidResponse( QStringList& ) ) );

    CreateDropSP( false );
    CreateDropSP( true );
}

CProcessCpuid::~CProcessCpuid( )
{

}

void CProcessCpuid::CreateDropSP( bool bCreate )
{
    QString strSql = bCreate ? "CREATE PROCEDURE MakeLicense( in ID varchar( 50 ) ) \n\
            BEGIN \n\
               if not exists ( select AdministrativeID from License where AdministrativeID = ID ) then \n\
                   Insert Into License ( AdministrativeID, KeyContent ) values ( ID, NULL );\n\
               end if;\n\
             END" : "drop procedure IF EXISTS MakeLicense";

    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
}

void CProcessCpuid::CpuidRequest( )
{
    if ( NULL == pTableWidget ) {
        return;
    }

    CCommonFunction::FreeAllRows( pTableWidget );
    QStringList lstData;
    lstData << "CPUID" << "IP"  << "ParkID"; // Get Data Item

    CNetwork::Singleton( ).BroadcastDatagram( CommonDataType::DGCpuidRequest, lstData );
}

void CProcessCpuid::CpuidResponse( QStringList &lstData )
{
    // PSN / IP
    if ( lstData.count( ) <= 3 ) {
        return;
    }

    int nField = 0;
    int nType = lstData[ nField++ ].toInt( );

    if ( CommonDataType::DGCpuidResponse != nType ) {
        return;
    }

    QString& strPSN = lstData[ nField++ ];
    QString& strIP = lstData[ nField++ ];
    QString& strAdminParkID = lstData[ nField++ ];

    bool bRet = CLicense::CreateSingleton( false ).GetDongle( )->IsAdminHID( strPSN );
    if ( bRet ) { // Generate License Machine
        return;
    }

    if ( NULL == pTableWidget ) {
        return;
    }

    QComboBox* pCBX = GetHidCbx( strPSN, NULL );
    if ( NULL != pCBX ) {
        return;
    }

    QStringList lstRow;
    GenerateRow( lstRow, strPSN, strIP, strAdminParkID );
    AddRow( lstRow );

    emit ParkIDChanged( strAdminParkID );
}

void CProcessCpuid::GenerateRow( QStringList &lstRow, QString &strHID, QString &strIP, QString& strAdminParkID )
{
    QDate curDate = QDate::currentDate( );
    QDate nxtDate = curDate.addMonths( 1 );
    QString strCurDate;
    QString strNxtDate;

    CCommonFunction::Date2String( curDate, strCurDate );
    CCommonFunction::Date2String( nxtDate, strNxtDate );

    lstRow << strHID << strIP << strCurDate << strNxtDate << strAdminParkID;
}

bool CProcessCpuid::GetPlainData( QByteArray &byData )
{
    bool bRet = false;

    if ( NULL == pTableWidget ) {
        return bRet;
    }

    CCommonFunction::FreeAllRows( pTableWidget );

    if ( !CLicense::CreateSingleton( false ).GenerateIniFile( byData ) ) {
        return bRet;
    }

#if false
    [Counter]
    Count = 1;
    [0]
    PSN=1234
    IP=192.168.1.1
    StartDate=2011-12-12
    EndDate=2012-12-12
#endif

    QTemporaryFile file;
    if ( !file.open( ) ) {
        return bRet;
    }

    QTextStream stream( &file );
    stream << QString( byData );

    file.close( );

    QString strFile = file.fileName( );
    QSettings setings( strFile, QSettings::IniFormat );
    setings.setIniCodec( CCommonFunction::GetTextCodec( ) );

    QString strAdminParkID = setings.value( "ParkID/AdminID", "" ).toString( );

    int nCounter = setings.value( "Counter/Count", 0 ).toInt( );
    QString strSection = "%1/%2";

    QStringList lstRow;
    QDate date;
    QString strDate = "";

    for ( int nItem = 0; nItem < nCounter; nItem++ ) {
        lstRow.clear( );
        QString strRow = QString::number( nItem );
        lstRow << setings.value( strSection.arg( strRow, "PSN" ) ).toString( )
                     << setings.value( strSection.arg( strRow, "IP" ) ).toString( );

        date = QDateTime::fromMSecsSinceEpoch( setings.value( strSection.arg( strRow, "StartDate" ) ).toLongLong( ) ).date( );
        CCommonFunction::Date2String( date, strDate );
        lstRow << strDate;

       date = QDateTime::fromMSecsSinceEpoch( setings.value( strSection.arg( strRow, "EndDate" ) ).toLongLong( ) ).date( );
       CCommonFunction::Date2String( date, strDate );
       lstRow << strDate;

       lstRow << strAdminParkID;

       AddRow( lstRow );
    }

    emit ParkIDChanged( strAdminParkID );

    bRet = true;

    return bRet;
}

bool CProcessCpuid::Import2Database( )
{
    bool bRet = false;

    QString strFile = QFileDialog::getOpenFileName( );

    if ( strFile.isEmpty( ) ) {
        return bRet;
    }

    QByteArray byData;
    QString strParkID = CCommonFunction::GetParkID( );
    if ( !OperateFileData( byData, strFile, false ) ) {
        return bRet;
    }

    CallSP( strParkID );

    if ( !OperateBlob( byData, strParkID, false ) ) {
        return bRet;
    }

    bRet = true;

    return bRet;
}

bool CProcessCpuid::OperateFileData( QByteArray &byData, QString &strFile, bool bWrite )
{
    bool bRet = false;
    QFile file( strFile );

    if ( !bWrite && !file.exists( ) ) {
        return bRet;
    }

    if ( !file.open( QIODevice::ReadWrite ) ) {
        return bRet;
    }

    if ( bWrite ) {
        bRet = ( -1 != file.write( byData ) );
    } else {
        byData = file.readAll( );
        bRet = true;
    }

    file.close( );

    return bRet;
}

bool CProcessCpuid::ImportData( QString &strFile )
{
    bool bRet = false;
    QByteArray byData;

    if ( !OperateFileData( byData, strFile, false ) ) {
        return bRet;
    }

    bRet = GetPlainData( byData );

    return bRet;
}

bool CProcessCpuid::ExportData( QString &strFile, QString& strParkID )
{
    bool bRet = false;
    QByteArray byData;

    if ( !GetCipherData( byData, strParkID ) ) {
        return bRet;
    }

    bRet = OperateFileData( byData, strFile, true ) ;

    return bRet;
}

void CProcessCpuid::GetData( QString& strParkID )
{
    QByteArray byData;
    if ( !OperateBlob( byData, strParkID, true ) ) {
        return;
    }

    GetPlainData( byData );
}

bool CProcessCpuid::OperateBlob( QByteArray &byData, QString& strParkID, bool bRead )
{
    QString strSql = bRead ? QString( "Select KeyContent From License Where AdministrativeID = '%1'" ).arg( strParkID ) :
                             QString( "update License set KeyContent = ? where AdministrativeID = '%1'" ).arg( strParkID );
    QString strError;
    bool bRet = bRead ? CLogicInterface::GetInterface( )->GetMysqlDb( ).BlobReadDb( byData, strSql, strError ) :
            CLogicInterface::GetInterface( )->GetMysqlDb( ).BlobWriteDb( byData, strSql, strError );

    return bRet;
}

bool CProcessCpuid::GetCipherData( QByteArray &byData, QString& strParkID )
{
    bool bRet = false;

    if ( NULL == pTableWidget ) {
        return bRet;
    }

    int nRows = pTableWidget->rowCount( );
    QDateEdit* pDateEdit = NULL;
    QLineEdit* pLineEdit = NULL;
    QComboBox* pCBX = NULL;

    QTemporaryFile file;
    if ( !file.open( ) ) {
        return bRet;
    }

    file.close( );

    QSettings* pSetings = new QSettings( file.fileName( ), QSettings::IniFormat );
    pSetings->setIniCodec( CCommonFunction::GetTextCodec( ) );

    pSetings->setValue( "ParkID/AdminID", strParkID );
    pSetings->setValue( "Counter/Count", nRows );

    QString strSection = "%1/%2";

    for ( int nRow = 0; nRow < nRows; nRow++ ) {
        QString strRow = QString::number( nRow );

        pCBX = ( QComboBox* ) pTableWidget->cellWidget( nRow, 0 );
        pSetings->setValue( strSection.arg( strRow, "PSN" ), pCBX->currentText( ) );

        pLineEdit = ( QLineEdit* ) pTableWidget->cellWidget( nRow, 1 );
        pSetings->setValue( strSection.arg( strRow, "IP" ), pLineEdit->text( ) );

        pDateEdit =( QDateEdit* ) pTableWidget->cellWidget( nRow, 2 );
        pSetings->setValue( strSection.arg( strRow, "StartDate" ), pDateEdit->dateTime( ).toMSecsSinceEpoch( ) );

        pDateEdit =( QDateEdit* ) pTableWidget->cellWidget( nRow, 3 );
        pSetings->setValue( strSection.arg( strRow, "EndDate" ), pDateEdit->dateTime( ).toMSecsSinceEpoch( ) );
    }

    pSetings->sync( );
    delete pSetings;
    pSetings = NULL;

    if ( !file.exists( ) || !file.open(  ) ) {
        return bRet;
    }

    byData = file.readAll( );
    file.close( );

    int nPad = byData.count( ) % 8;

    if ( 0 < nPad ) {
        QByteArray byPad( 8 - nPad, '\0' );
        byData.append( byPad );
    }

    bRet = CLicense::CreateSingleton( false ).OpenCrypt( true, byData );

    DWORD dwSignature = CLicense::CreateSingleton( false ).SignatureValue( );
    CLicense::CreateSingleton( false ).OperateSignature( byData, dwSignature, TRUE );
    byData = byData.toBase64( );

    return bRet;
}

void CProcessCpuid::CallSP( QString &strParkID )
{
    QString strSql = QString( "call MakeLicense( '%1' )" ).arg( strParkID );
    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
}

void CProcessCpuid::SaveData( QString& strParkID )
{
    QByteArray byData;
    bool bRet = false;

    if ( !GetCipherData( byData, strParkID ) ) {
        return;
    }

    //QString strSql = QString( "call MakeLicense( '%1' )" ).arg( strParkID );
    //CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    CallSP( strParkID );

    bRet = OperateBlob( byData, strParkID, false );
    CCommonFunction::MsgBox( NULL, "提示",  bRet ? " 操作成功！" : "操作失败！" , QMessageBox::Information );
}

bool CProcessCpuid::RowExist( QStringList &lstRow )
{
    bool bRet = false;
    QComboBox* pCBX = NULL;

    for ( int nIndex = 0; nIndex < pTableWidget->rowCount( ); nIndex++ ) {
        pCBX = ( QComboBox* ) pTableWidget->cellWidget( nIndex, 0 );

        bRet = ( pCBX->currentText( ).toUpper( ) == lstRow[ 0 ].toUpper( ) );
        if ( bRet ) {
            break;
        }
    }

    return bRet;
}

void CProcessCpuid::GetAllHIDs( QStringList &lstHids )
{
    CDongle* pDonge = new CETDongle( false );
    pDonge->GetAllHids( lstHids );
    delete pDonge;
}

void CProcessCpuid::Batch( QString& strAdminParkID, QString& shrHid )
{
    QString strIP = CCommonFunction::GetHostIP( );
    QStringList lstRow;
    GenerateRow( lstRow, shrHid, strIP, strAdminParkID );
    AddRow( lstRow );
}

void CProcessCpuid::GetAllHIDs( QString &strParkID, QComboBox *pCbx )
{
    if ( strParkID.isEmpty( ) || NULL == pCbx ) {
        return;
    }

    QStringList lstRow;
    QString strSql = QString( "Select AES_DECRYPT( DongleHID, '%1' ) From ParkDongleInfo Where AdministrativeID = '%2'" ).arg( KEY_GUID, strParkID );

    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRow );
    QString strHIDs = lstRow.join( "," );

    if ( strHIDs.isEmpty( ) ) {
        return;
    }

    strHIDs = "," + strHIDs;
    lstRow = strHIDs.split( "," );
    pCbx->addItems( lstRow );
}

QComboBox* CProcessCpuid::GetHidCbx( QString& strHid, QComboBox* pSender )
{
    int nRows = pTableWidget->rowCount( );
    QComboBox* pCBX = NULL;

    for ( int nIndex = 0; nIndex < nRows; nIndex++ ) {
        pCBX = ( QComboBox* ) pTableWidget->cellWidget( nIndex, 0 );
        if ( pCBX->currentText( ) == strHid && pSender != pCBX ) {
            break;
        }

        pCBX = NULL;
    }

    return pCBX;
}

void CProcessCpuid::HIDChanged( QString strHID  )
{
    if ( strHID.isEmpty( ) ) {
        return;
    }

    QComboBox* pSender = ( QComboBox* ) sender( );
    QComboBox* pCBX = GetHidCbx( strHID, pSender );

    if ( NULL != pCBX ) {
        CCommonFunction::MsgBox( NULL, QString( "提示" ),
                                 QString( "加密狗【%1】已被使用！" ).arg(  strHID ), QMessageBox::Information );
        pSender->setCurrentIndex( 0 );
    }
}

void CProcessCpuid::AddRow( QStringList &lstRow )
{
    if ( RowExist( lstRow ) ) {
        return;
    }

    QDateEdit* pDateEdit = NULL;
    QLineEdit* pLineEdit = NULL;
    QComboBox* pCbx = NULL;
    QTableWidgetItem* pItem = NULL;

    pTableWidget->insertRow( 0 );
    int nField = 0;
    int nRowIndex = 0;
    QString strParkID = "";
    int nCurIndex = -1;

    if ( 5 <= lstRow.count( ) ) {
        strParkID = lstRow.at( 4 );
        lstRow.removeAt( 4 );
    }

    foreach ( const QString& str, lstRow ) {
        switch ( nField ) {
        case 0 :
            pCbx = new QComboBox( );
            GetAllHIDs( strParkID, pCbx );
            nCurIndex = pCbx->findText( str );
            if ( -1 == nCurIndex ) {
                pCbx->insertItem( 0, str );
                pCbx->setCurrentIndex( 0 );
            } else {
                pCbx->setCurrentIndex( nCurIndex );
            }

            pItem = new QTableWidgetItem( str );
            pTableWidget->setItem(  nRowIndex, nField, pItem );

            connect( pCbx, SIGNAL(currentIndexChanged( QString ) ), this, SLOT( HIDChanged( QString ) ) );
            pTableWidget->setCellWidget( nRowIndex, nField, pCbx );
            break;

        case 1 :
            pLineEdit = new QLineEdit( str );
            pTableWidget->setCellWidget( nRowIndex, nField, pLineEdit );
            break;

        case 2 :
        case 3 :
            pDateEdit = new QDateEdit( CCommonFunction::String2Date( ( QString& ) str ) );
            pTableWidget->setCellWidget( nRowIndex, nField, pDateEdit );
            break;
        }

        nField++;
    }
}
