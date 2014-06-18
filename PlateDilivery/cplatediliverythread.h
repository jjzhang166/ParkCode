#ifndef CPLATEDILIVERYTHREAD_H
#define CPLATEDILIVERYTHREAD_H

#include <QThread>
#include <QEvent>
#include <QStringList>
#include <QTcpSocket>
#include <QFile>
//#include "Common/commonfunction.h"
#include "cdataparser.h"
#include "qlistener.h"
#include "Common/logicinterface.h"

class CPlateDiliveryThread : public QThread
{
    Q_OBJECT
public:

    static CPlateDiliveryThread* GetSingleton( );
    ~CPlateDiliveryThread( );

protected:
    explicit CPlateDiliveryThread(QObject *parent = 0);

    void run( );
    void timerEvent(  QTimerEvent * event );

private:
    bool Connect2Host( );
    bool CreateSendData( quint8 nAddress, QByteArray& byteData, QStringList& lstData );
    void CheckSum( QByteArray& byteData, char& nCheckSum );

    void ParseRequestData( QByteArray& byRequest );
    bool ParseMultipleRequestData( QByteArray& byRequest );

    void SendPlate( quint8 nAddress, QStringList& lstData );
    void StartListener( );
    char GetConfidence( char nConfidence, const QString& strPlate );
    void ConnectDb( );
    void SavePlate( QString& strPlate );
    void SavePlate( QByteArray& byStream );

private:
    static CPlateDiliveryThread* pThreadInstance;
    QTcpSocket* pTcpSocket;
    QListener* pListener;
    QSettings* pSettings;
    QString strIP;
    quint16 nPort;
    QTextCodec* pTextCodec;
    QFile picFile;
    quint64 nBytesAvailable;
    QByteArray byData;
    quint32 nPakageSize;
    bool bActiveSend;
    bool bActivePlate;
    bool bPlateVideo;
    CDataParser dataParser;
    QHash< int, QStringList > hashPlate;
    QString strPlates[ 2 ];
    CLogicInterface logicInterf;
    QStringList lstConnParams;
    
signals:
    void WeighingRequest( QStringList lstData );
    void Capture( quint8 nChannel );
    void SendFileCount( quint32 nCount );
    
public slots:
    void HandlePlateDilivery( int nChannel, QStringList lstData, QString strPlate );
    void IncommingData( );
    void Reconnect( );
    void HandleResponse( QByteArray byResponse );
    void HandleAccept( int socketDescriptor );
    void HandleCapture( quint8 nChannel );
    
};

#endif // CPLATEDILIVERYTHREAD_H
