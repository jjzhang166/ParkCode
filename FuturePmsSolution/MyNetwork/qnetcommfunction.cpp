#include "qnetcommfunction.h"

QNetCommFunction::QNetCommFunction(QObject *parent) :
    QObject(parent)
{
    setObjectName( "QNetCommFunction" );
}

void QNetCommFunction::GetErrorMsg( QString& strMsg, QNetworkReply::NetworkError code, QIODevice* pDevice )
{
    switch ( code ) {
    case QNetworkReply::NoError :
        break;
        // network layer errors [relating to the destination server] (1-99):
    case QNetworkReply::ConnectionRefusedError :
        strMsg = "QNetworkReply::ConnectionRefusedError";
        break;
    case QNetworkReply::RemoteHostClosedError :
        strMsg = "QNetworkReply::RemoteHostClosedError";
        break;
    case QNetworkReply::HostNotFoundError :
        strMsg = "QNetworkReply::HostNotFoundError";
        break;
    case QNetworkReply::TimeoutError :
        strMsg = "QNetworkReply::TimeoutError";
        break;
    case QNetworkReply::OperationCanceledError :
        strMsg = "QNetworkReply::OperationCanceledError";
        break;
    case QNetworkReply::SslHandshakeFailedError :
        strMsg = "QNetworkReply::SslHandshakeFailedError";
        break;
    case QNetworkReply::TemporaryNetworkFailureError :
        strMsg = "QNetworkReply::TemporaryNetworkFailureError";
        break;
    case QNetworkReply::UnknownNetworkError :
        strMsg = "QNetworkReply::UnknownNetworkError";
        break;

        // proxy errors (101-199):
    case QNetworkReply::ProxyConnectionRefusedError :
        strMsg = "QNetworkReply::ProxyConnectionRefusedError";
        break;
    case QNetworkReply::ProxyConnectionClosedError :
        strMsg = "QNetworkReply::ProxyConnectionClosedError";
        break;
    case QNetworkReply::ProxyNotFoundError :
        strMsg = "QNetworkReply::ProxyNotFoundError";
        break;
    case QNetworkReply::ProxyTimeoutError :
        strMsg = "QNetworkReply::ProxyTimeoutError";
        break;
    case QNetworkReply::ProxyAuthenticationRequiredError :
        strMsg = "QNetworkReply::ProxyAuthenticationRequiredError";
        break;
    case QNetworkReply::UnknownProxyError :
        strMsg = "QNetworkReply::UnknownProxyError";
        break;

        // content errors (201-299):
    case QNetworkReply::ContentAccessDenied :
        strMsg = "QNetworkReply::ContentAccessDenied";
        break;
    case QNetworkReply::ContentOperationNotPermittedError :
        strMsg = "QNetworkReply::ContentOperationNotPermittedError";
        break;
    case QNetworkReply::ContentNotFoundError :
        strMsg = "QNetworkReply::ContentNotFoundError";
        break;
    case QNetworkReply::AuthenticationRequiredError :
        strMsg = "QNetworkReply::AuthenticationRequiredError";
        break;
    case QNetworkReply::ContentReSendError :
        strMsg = "QNetworkReply::ContentReSendError";
        break;
    case QNetworkReply::UnknownContentError :
        strMsg = "QNetworkReply::UnknownContentError";
        break;

        // protocol errors
    case QNetworkReply::ProtocolUnknownError :
        strMsg = "QNetworkReply::ProtocolUnknownError";
        break;
    case QNetworkReply::ProtocolInvalidOperationError :
        strMsg = "QNetworkReply::ProtocolInvalidOperationError";
        break;
    case QNetworkReply::ProtocolFailure :
        strMsg = "QNetworkReply::ProtocolFailure";
        break;
    }

    strMsg += "\n";

    if ( NULL != pDevice) {
        strMsg += pDevice->errorString( );
        strMsg += "\n";
    }
}

void QNetCommFunction::GetErrorMsg( QString& strMsg, QAbstractSocket::SocketError code, QIODevice* pDevice )
{
    switch ( code ) {
    case QAbstractSocket::ConnectionRefusedError :
        strMsg = "QAbstractSocket::ConnectionRefusedError";
        break;
    case QAbstractSocket::RemoteHostClosedError :
        strMsg = "QAbstractSocket::RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError :
        strMsg = "QAbstractSocket::HostNotFoundError";
        break;
    case QAbstractSocket::SocketAccessError :
        strMsg = "QAbstractSocket::SocketAccessError";
        break;
    case QAbstractSocket::SocketResourceError :
        strMsg = "QAbstractSocket::SocketResourceError";
        break;
    case QAbstractSocket::SocketTimeoutError :
        strMsg = "QAbstractSocket::SocketTimeoutError";
        break;
    case QAbstractSocket::DatagramTooLargeError :
        strMsg = "QAbstractSocket::DatagramTooLargeError";
        break;
    case QAbstractSocket::NetworkError :
        strMsg = "QAbstractSocket::NetworkError";
        break;
    case QAbstractSocket::AddressInUseError :
        strMsg = "QAbstractSocket::AddressInUseError";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError :
        strMsg = "QAbstractSocket::SocketAddressNotAvailableError";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError :
        strMsg = "QAbstractSocket::UnsupportedSocketOperationError";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError :
        strMsg = "QAbstractSocket::UnfinishedSocketOperationError";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError :
        strMsg = "QAbstractSocket::ProxyAuthenticationRequiredError";
        break;
    case QAbstractSocket::SslHandshakeFailedError :
        strMsg = "QAbstractSocket::SslHandshakeFailedError";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError :
        strMsg = "QAbstractSocket::ProxyConnectionRefusedError";
        break;
    case QAbstractSocket::ProxyConnectionClosedError :
        strMsg = "QAbstractSocket::ProxyConnectionClosedError";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError :
        strMsg = "QAbstractSocket::ProxyConnectionTimeoutError";
        break;
    case QAbstractSocket::ProxyNotFoundError :
        strMsg = "QAbstractSocket::ProxyNotFoundError";
        break;
    case QAbstractSocket::ProxyProtocolError :
        strMsg = "QAbstractSocket::ProxyProtocolError";
        break;
    case QAbstractSocket::UnknownSocketError :
        strMsg = "QAbstractSocket::UnknownSocketError";
        break;
    }

    strMsg += "\n";

    if ( NULL != pDevice) {
        strMsg += pDevice->errorString( );
        strMsg += "\n";
    }
}
