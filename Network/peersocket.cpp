#include "peersocket.h"

CPeerSocket::CPeerSocket(QObject *parent) :
    QTcpSocket(parent)
{
    pData = NULL;
    Clear( );

    pData = new QByteArray( );
}

CPeerSocket::~CPeerSocket( )
{
    if ( NULL != pData ) {
        delete pData;
        pData = NULL;
    }
}

void CPeerSocket::SetMaxDataSize( quint64 nSize )
{
    nDataLen = nSize;
}

quint64 CPeerSocket::GetMaxDataSize( )
{
    return nDataLen;
}

void CPeerSocket::Clear( )
{
    if ( NULL != pData ) {
        pData->resize( 0 );
    }

    nDataLen = 0;
    nCurrentLen = 0;
}

void CPeerSocket::SetCurrentDataSize( quint64 nSize )
{
    nCurrentLen += nSize;
}

quint64 CPeerSocket::GetCurrentDataSize( )
{
    return nCurrentLen;
}

QByteArray* CPeerSocket::GetData( )
{
    return pData;
}
