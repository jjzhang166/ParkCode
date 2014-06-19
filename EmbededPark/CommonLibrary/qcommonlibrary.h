#ifndef QCOMMONLIBRARY_H
#define QCOMMONLIBRARY_H
#include <QtCore>
#include <QtGui>
#include "CommonLibrary_global.h"
#include <QEvent>
#include <QtGlobal>
#include <QtNetwork>
#include <QtEndian>
#include <QDebug>
#include <QSettings>

class COMMONLIBRARYSHARED_EXPORT QCommonLibrary : public QObject
{
public:

    typedef enum __ThreadType {
        ThreadListener,
        ThreadSocketDispatcher,
        ThreadSocketClient,
        ThreadSocketServer,
        ThreadDataParser,
        ThreadDatabase,
        ThreadLog
    } ThreadType;

    typedef enum __ThreadEventType {
        // Thread Exit
        EventExit = QEvent::User,
        // Listener Thread
        EventStartListen,
        EventStopListen,
        // Socket Dispatcher Thread
        EventTimerRecycleSocketThread,
        EventSocketDescriptorDispatch,
        EventSocketDisconnection,
        // Socket Thread Server
        EventAttachSocketDescriptor,
        EventDetachSocketDescriptor,
        EventServerSendData,
        // Socket Thread Client
        EventClientConnection,
        EventClientDisconnection,
        EventClientSendData,

        // Data Parser Thread
        EventTCPData,
        EventUDPData,

        // Database Thread
        // Log Thread
        EventReadLog,
        EventWriteLog

    } ThreadEventType;

    typedef QMultiHash< qint32, QVariant > QIntVariantHash;

    typedef enum __ParamType {
        TypeLogContent
    } ParamType;

    typedef struct __EventParam {
        union __ParamValue {
            union __DistpatcherThread {
                union __Param {
                // EventSocketDescriptorDispatch Listener-->Dispatcher
                qintptr nSocketDescriptor;
                // EventSocketDisconnection SocketThreadServer-->Dispatcher
                QTcpSocket* pSocket;
                } Param;
            } DistpatcherThread;

            union __ServerSocketThread {
                // EventAttachSocketDescriptor Dispatcher-->SocketThreadServer
                union __Param {
                    struct __SocketDescriptor {
                        qintptr nSocketDescriptor;
                    } SocketDescriptor;

                    struct __Data {
                        QTcpSocket* pSocket;
                        QByteArray* pByteArray; // delete
                    } Data;
                } Param;
            } ServerSocketThread;

            union __ClientSocketThread {
                struct __Host { // EventClientConnection EventClientDisconnection
                    quint32 nIP;
                    quint16 nPort;
                    quint16 nSequence; // Connect Sequence
                    bool bAll;
                } Host;

                struct __Data { // EventClientSendData
                    __Host Host;
                    QByteArray* pByteArray; // delete
                } Data;
            } ClientSocketThread;

            union __ParserThread {
                struct __Param {
                    QTcpSocket* pSocket; // pSocket->thread( )
                    QByteArray* pByteArray; // delete
                } DataParam;
            } ParserThread;

            union __LogThread {
                struct __LogParam {
                    QString* pLogSQLStmt; // delete
                    bool bSingleRow;
                } LogParam;
            } LogThread;
        } ParamValue;

        ParamType type;
    } EventParam;

    typedef enum __LohType {
        LogInformation,
        LogWarning,
        LogError
    } LogType;

public:
    // DateTime
    static void GetCurrentDateTime( QString& strDateTime );
    static void GetCurrentDateTime( QDateTime& dtDateTime );
    static void DateTime2String( QDateTime &dtValue, QString& strText );
    static void Date2String( QDate &dValue, QString& strText );
    static void Time2String( QTime &tValue, QString& strText );
    static QDateTime String2DateTime( QString& strDateTime );
    static QTime String2Time( QString& strTime );
    static QDate String2Date( QString& strDate );
    static QString& GetDataToken( );
    static void PrintLog( QString& strText );
    static QString GetKeySeperator( );
    static bool GetDisplayLog( );
    static QString& GetConfigFileName( );

    // Application Initialization
    static void AppInitialize( );

    // Text codec
    static QTextCodec* GetTextCodec( );

private:
    static const QString strDateTimeFormat;
    static const QString strDateFormat;
    static const QString strTimeFormat;

private:
    QCommonLibrary( QObject* parent = 0 );
};

#endif // QCOMMONLIBRARY_H
