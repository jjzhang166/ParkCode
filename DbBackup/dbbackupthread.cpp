#include "DbBackup\dbbackupthread.h"
#include "Common/commonfunction.h"
#include <QDir>
#include <QFile>
#include <QtGui/QApplication>
#include <QDebug>

// www.openstack.org json xml
// MS SqlServer top / MySql Limit
// Select * From Tabel into outfile 'c:/text.txt'
#if false
SET @a=1;
PREPARE STMT FROM 'SELECT * FROM tbl LIMIT ?';
EXECUTE STMT USING @a;
////////////////////
SELECT
    [ALL | DISTINCT | DISTINCTROW ]
      [HIGH_PRIORITY]
      [STRAIGHT_JOIN]
      [SQL_SMALL_RESULT] [SQL_BIG_RESULT] [SQL_BUFFER_RESULT]
      [SQL_CACHE | SQL_NO_CACHE] [SQL_CALC_FOUND_ROWS]
    select_expr [, select_expr ...]
    [FROM table_references
    [WHERE where_condition]
    [GROUP BY {col_name | expr | position}
      [ASC | DESC], ... [WITH ROLLUP]]
    [HAVING where_condition]
    [ORDER BY {col_name | expr | position}
      [ASC | DESC], ...]
    [LIMIT {[offset,] row_count | row_count OFFSET offset}]
    [PROCEDURE procedure_name(argument_list)]
    [INTO OUTFILE 'file_name'
        [CHARACTER SET charset_name]
        export_options
      | INTO DUMPFILE 'file_name'
      | INTO var_name [, var_name]]
    [FOR UPDATE | LOCK IN SHARE MODE]]


LOAD DATA [LOW_PRIORITY | CONCURRENT] [LOCAL] INFILE 'file_name'
    [REPLACE | IGNORE] //重复是否替换
    INTO TABLE tbl_name
    [CHARACTER SET charset_name]
    [{FIELDS | COLUMNS}
        [TERMINATED BY 'string']
        [[OPTIONALLY] ENCLOSED BY 'char']
        [ESCAPED BY 'char'] // 列分隔符
    ]
    [LINES
        [STARTING BY 'string']
        [TERMINATED BY 'string'] // 行分隔符
    ]
    [IGNORE number LINES] // 放弃某些行
    [(col_name_or_user_var,...)] // 列名或变量
    [SET col_name = expr,...] // 赋值
#endif

CDbBackupThread& CDbBackupThread::GetInstance( bool bAuto, bool bRestore, QObject *parent )
{
    CDbBackupThread* pThread = new CDbBackupThread( bAuto, bRestore, parent );

    return *pThread;
}

CDbBackupThread::CDbBackupThread( bool bAuto, bool bRestore, QObject *parent ) :
    QThread(parent), bAutoBackup( bAuto ), bAutoRestore( bRestore )
{
    GetConfig( false );
    GetConfig( true );
    nDayDiff = DayDiff( );
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
}

void CDbBackupThread::GetConfig( bool bOption )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgDbMaintain );
    QString strSection = bOption ? "Options/" : "Database/";

    if ( bOption ) {
        tAutoBackupTime = pSet->value( strSection + "AutoBackupTime", QTime::currentTime( ) ).toTime( );
        bAutoBackupStartup = pSet->value( strSection + "AutoBackupStartup", false ).toBool( );
        bAutoBackupImg = pSet->value( strSection + "AutoBackupImg", false ).toBool( );
        dtNextAutoTime = pSet->value( strSection + "NextAutoTime", QDate::currentDate( ) ).toDate( );
        strManualBackupPath = pSet->value( strSection + "ManualBackupPath", QApplication::applicationDirPath( ) ).toString( );
        bManualBackupImg = pSet->value( strSection + "ManualBackupImg", false ).toBool( );
        strManualRestorePath = pSet->value( strSection + "ManualRestorePath", QApplication::applicationDirPath( ) ).toString( ) + "/";
        bManualOverwiteData = pSet->value( strSection + "ManualOverwiteData", false ).toBool( );
        nAutoInterval = pSet->value( strSection + "AutoInterval", 300 ).toUInt( );
    } else {
        QString strKey = "Tables";
        lstTables = pSet->value( strSection + strKey, "" ).toString( ).split( "@" );

        strKey = "CommonSelect";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );

        strKey = "CommonLoad";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );

        strKey = "SysinfoSelect";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );

        strKey = "SysinfoLoad";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );

        strKey = "StoprdSelect";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );

        strKey = "StoprdLoad";
        sqlHash.insert( strKey, pSet->value( strSection + strKey, "" ).toString( ).replace( "@", "," ) );
    }
}

void CDbBackupThread::BackupData( bool bImg, bool bAuto )
{
    QDate date = QDate::currentDate( );
    QString strDate;
    CCommonFunction::Date2String( date, strDate );

    QString strPath = strManualBackupPath + "/" + strDate + "/";
    QDir dir( strPath );
    if ( !dir.exists( ) ) {
        dir.mkpath( strPath );
    } else {
        QFileInfoList lstFile = dir.entryInfoList( );
        int nCount = lstFile.count( );

        for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
            QFileInfo info = lstFile.at( nIndex );
            if ( info.isFile( ) ) {
                QFile::remove( info.filePath( ) );
            }
        }
    }

    QString strSuffix = "Select";
    QString strSql;
    QString strFile;
    QList< QString > lstKeys = sqlHash.keys( );

    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams );
    bool bRet = dbInterf.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
    if ( false == bRet ) {
        return;
    }

    foreach ( const QString& strTable, lstTables ) {
        if ( strTable.isEmpty( ) ) {
            continue;
        }

        strFile = strPath + strTable;
        strSql = "Common" + strSuffix; // Backup Img
        if ( !bImg && lstKeys.contains( strTable + strSuffix ) ) {
            strSql = strTable + strSuffix;
            strFile += "_NoImg";
        }

        if ( QFile::exists( strFile ) ) {
            QFile::remove( strFile );
        }

        strSql = sqlHash.value( strSql );
        strSql = strSql.arg( strTable, strFile );

        if ( !strSql.isEmpty( ) ) {
            dbInterf.ExecuteSql( strSql );
        }
    }

    dbInterf.GetMysqlDb( ).DbDisconnect( );

    // Delete
    //if ( bAuto ) {
    //    CRdAutoDeleteThread::GetInstance( this ).start( );
        //delThread.start( );
    //}
}

void CDbBackupThread::RestoreData( )
{
    QDir dir( strManualRestorePath );
    if ( !dir.exists( ) ) {
        return;
    }

    QString strSuffix = "Load";
    QString strSql;
    QString strFile;
    QList< QString > lstKeys = sqlHash.keys( );

    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams );
    bool bRet = dbInterf.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );
    if ( false == bRet ) {
        return;
    }

    foreach ( const QString& strTable, lstTables ) {
        if ( strTable.isEmpty( ) ) {
            continue;
        }

        strFile = strManualRestorePath + strTable;
        strSql = "Common" + strSuffix; // Backup Img
        if ( lstKeys.contains( strTable + strSuffix ) && !QFile::exists( strFile ) ) {
            strSql = strTable + strSuffix;
            strFile += "_NoImg";
        }

        if ( !QFile::exists( strFile ) ) {
            continue;
        }

        strSql = sqlHash.value( strSql );
        strSql = strSql.arg( strFile, bManualOverwiteData ?  "Replace" : "", strTable );

        if ( !strSql.isEmpty( ) ) {
            dbInterf.ExecuteSql( strSql );
        }
    }

    dbInterf.GetMysqlDb( ).DbDisconnect( );
}

int CDbBackupThread::DayDiff( )
{
    return QDate::currentDate( ).daysTo( dtNextAutoTime );
}

bool CDbBackupThread::CheckTimePoint( )
{
    bool bRet = false;
    QTime time = QTime::currentTime( );
    int nSecs = 2 * 60;

    if ( 0 == DayDiff( ) /*Current Day*/ && tAutoBackupTime.addSecs( -1 * nSecs ) <= time && time <= tAutoBackupTime.addSecs( nSecs ) ) {
        return true;
    }

    sleep( nAutoInterval );

    return bRet;
}

void CDbBackupThread::LetSleep( bool bCurrentDay  )
{
    int nDaySeconds = 24 * 3600;

    if ( bCurrentDay ) {
        QTime time = QTime::currentTime( );
        int nInterval = 1 * 60;
        int nTime = time.hour( ) * 60 * 60 + time.minute( ) * 60 + time.second( );
        int nStart = tAutoBackupTime.hour( ) * 60 * 60 + tAutoBackupTime.minute( ) * 60 + tAutoBackupTime.second( );
        nTime = nStart - nTime;

        if ( nInterval > qAbs< int >( nTime ) ) { // [ -1, +1 ]
            return;
        }

        nTime = ( 0 < nTime ) ? ( nTime - nInterval ) : ( nDaySeconds + nTime - nInterval );
        sleep( nTime );
        qDebug( ) << "First" << endl;
    } else {
        quint64 nCurDay = QDateTime::currentMSecsSinceEpoch( );
        quint64 nNxtDay = QDateTime( dtNextAutoTime, tAutoBackupTime ).toMSecsSinceEpoch( );

        int nDay = ( nNxtDay - nCurDay ) / ( nDaySeconds * 1000 );
        sleep( nDay * nDaySeconds );
        qDebug( ) << "Next" << endl;
    }
}

void CDbBackupThread::run( )
{
    if ( bAutoBackup ) {
        if ( !bAutoBackupStartup ) {
            return;
        }

        bool bFirst = true;

        while( true ) {
            if ( bFirst ) {
                LetSleep( true );
                bFirst = false;
            }

            BackupData( bAutoBackupImg, bAutoBackup );
            dtNextAutoTime.addDays( nDayDiff );
            LetSleep( false );
            qDebug( ) << "BackupData( ) success" << endl;
        }
    } else {
        bAutoRestore ? RestoreData( ) : BackupData( bManualBackupImg, bAutoBackup );
    }
}

void CDbBackupThread::ExitThread( )
{
    delete this;
}
