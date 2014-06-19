#include "qmytcpsocket.h"

QMyTcpSocket::QMyTcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
    pByteArray = NULL;
    Clear( );
    setObjectName( "QMyTcpSocket" );
}

void QMyTcpSocket::SetMaxDataSize( quint64 nSize )
{
    nDataLen = nSize;
}

quint64 QMyTcpSocket::GetMaxDataSize( )
{
    return nDataLen;
}

void QMyTcpSocket::Clear( )
{
    nDataLen = 0;
    nCurrentLen = 0;
}

void QMyTcpSocket::GetKeyMsg( QString &strKey, QString &strMsg, bool bConnected )
{
    strKey = QString( "Local %1:%2 Peer %3:%4" ).arg( localAddress( ).toString( ), QString::number( localPort( ) ), peerAddress( ).toString( ), QString::number( peerPort( ) ) );

    QDateTime dt = QDateTime::currentDateTime( );
    QString strDateTime = commonFunction.GetDateTimeString( dt );

    strMsg = QString ( "%1 %2 %3" ).arg( strDateTime, strKey,
            bConnected ? "Connected" : " Disconnected" );
}

void QMyTcpSocket::GenerateLogText( bool bConnected )
{
    QString strKey;
    QString* pstrMsg = new QString( );

    GetKeyMsg( strKey, *pstrMsg, bConnected );

    *pstrMsg = LogText( *pstrMsg );
    OutputMsg( QString( "emit NotifyMessage( %1, QManipulateIniFile::LogNetwork )" ).arg( *pstrMsg ) );

    emit NotifyMessage( pstrMsg, QManipulateIniFile::LogNetwork );
}

bool QMyTcpSocket::GetTcpStreamData( )
{
    bool bRet = false;

    quint64 nRealTimeDataLen = bytesAvailable( );

    if ( NULL == pByteArray ) {
        pByteArray = new QByteArray( );
    }

    quint64 nPreSize = GetCurrentDataSize( );
    quint64 nCurDataSize = nPreSize + nRealTimeDataLen;
    if ( 0 == GetMaxDataSize( ) || processMsg.GetCommonHeaderSize( ) > nCurDataSize ) {
        pByteArray->resize( nCurDataSize );
    }

    char* pSegData = ( char* ) ( ( quint64 ) pByteArray->data( ) + nPreSize );
    quint64 nDataRetLen = read( pSegData, nRealTimeDataLen );
    SetCurrentDataSize( nDataRetLen );

    if ( 0 == GetMaxDataSize( ) && processMsg.GetCommonHeaderSize( ) <= nCurDataSize ) {
        MyDataStructs::CommonHeader& commHeader = processMsg.GetCommonHeader( pSegData );
        SetMaxDataSize( commHeader.nDataLen );
        pByteArray->resize( commHeader.nDataLen );
    }

#ifndef QT_NO_DEBUG
    if ( nDataRetLen != nRealTimeDataLen ) {
        OutputMsg( QString( "Read Client data: %1 error" ).arg( peerAddress( ).toString( ) ) );
    }
#endif

    if ( GetCurrentDataSize( ) == GetMaxDataSize( ) ) { // Read to finish
        Clear( );
        write( HANDSHAKE );
        bRet = true;
    }

    return bRet;
}

void QMyTcpSocket::SetCurrentDataSize( quint64 nSize )
{
    nCurrentLen += nSize;
}

quint64 QMyTcpSocket::GetCurrentDataSize( )
{
    return nCurrentLen;
}

quint64 QMyTcpSocket::SendData( const char * data, qint64 maxSize )
{
    return write( data, maxSize );
}

quint64 QMyTcpSocket::SendData( const QByteArray & byteArray )
{
    quint64 nRet = 0;

    int nPackageSize = 10 * 1024 * 1024;
    int nTotalSize = byteArray.count( );
    int nMode = nTotalSize / nPackageSize;
    int nSurplus = nTotalSize % nPackageSize;
    const char* pData = byteArray.data( );
    const char* pPkgData = NULL;

    if ( 0 == nMode ) { // < 10M
        nRet += write( byteArray );
    } else { // >= 10M
        int nIndex = 0;
        for ( nIndex = 0; nIndex < nMode; nIndex++ ) {
            pPkgData = ( pData + nIndex * nPackageSize );
            nRet += write( pPkgData, nPackageSize );
        }

        if ( 0 != nSurplus ) {
            pPkgData = ( pData + nIndex * nPackageSize );
            nRet += write( pPkgData, nSurplus );
        }
    }

    if ( !flush( ) ) {
        waitForBytesWritten( );
    }

    return nRet;
}

quint64 QMyTcpSocket::ReceiveData( char* data, qint64 maxSize )
{
    return read( data, maxSize );
}

QByteArray QMyTcpSocket::ReceiveData( qint64 maxSize )
{
    return read( maxSize );
}

QByteArray QMyTcpSocket::ReceiveData(  )
{
    return readAll( );
}
