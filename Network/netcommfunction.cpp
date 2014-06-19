#include "netcommfunction.h"

CNetCommFunction::CNetCommFunction(QObject *parent) :
    QObject(parent)
{
}

#if false
QNetworkReply::NoError 0 no error condition. Note: When the HTTP protocol returns a redirect no error will be reported. You can check if there is a redirect with the QNetworkRequest::RedirectionTargetAttribute attribute.
QNetworkReply::ConnectionRefusedError 1 the remote server refused the connection (the server is not accepting requests)
QNetworkReply::RemoteHostClosedError 2 the remote server closed the connection prematurely, before the entire reply was received and processed
QNetworkReply::HostNotFoundError 3 the remote host name was not found (invalid hostname)
QNetworkReply::TimeoutError 4 the connection to the remote server timed out
QNetworkReply::OperationCanceledError 5 the operation was canceled via calls to abort() or close() before it was finished.
QNetworkReply::SslHandshakeFailedError 6 the SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted.
QNetworkReply::TemporaryNetworkFailureError 7 the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established.
QNetworkReply::ProxyConnectionRefusedError 101 the connection to the proxy server was refused (the proxy server is not accepting requests)
QNetworkReply::ProxyConnectionClosedError 102 the proxy server closed the connection prematurely, before the entire reply was received and processed
QNetworkReply::ProxyNotFoundError 103 the proxy host name was not found (invalid proxy hostname)
QNetworkReply::ProxyTimeoutError 104 the connection to the proxy timed out or the proxy did not reply in time to the request sent
QNetworkReply::ProxyAuthenticationRequiredError 105 the proxy requires authentication in order to honour the request but did not accept any credentials offered (if any)
QNetworkReply::ContentAccessDenied 201 the access to the remote content was denied (similar to HTTP error 401)
QNetworkReply::ContentOperationNotPermittedError 202 the operation requested on the remote content is not permitted
QNetworkReply::ContentNotFoundError 203 the remote content was not found at the server (similar to HTTP error 404)
QNetworkReply::AuthenticationRequiredError 204 the remote server requires authentication to serve the content but the credentials provided were not accepted (if any)
QNetworkReply::ContentReSendError 205 the request needed to be sent again, but this failed for example because the upload data could not be read a second time.
QNetworkReply::ProtocolUnknownError 301 the Network Access API cannot honor the request because the protocol is not known
QNetworkReply::ProtocolInvalidOperationError 302 the requested operation is invalid for this protocol
QNetworkReply::UnknownNetworkError 99 an unknown network-related error was detected
QNetworkReply::UnknownProxyError 199 an unknown proxy-related error was detected
QNetworkReply::UnknownContentError 299 an unknown error related to the remote content was detected
QNetworkReply::ProtocolFailure 399 a breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)
#endif
void CNetCommFunction::GetErrorMsg( QString& strMsg, QNetworkReply::NetworkError code, QIODevice* pDevice )
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

    strMsg += "\r\n";

    if ( NULL != pDevice) {
        strMsg += pDevice->errorString( );
        strMsg += "\r\n";
    }
}

#if false
QAbstractSocket::ConnectionRefusedError 0 The connection was refused by the peer (or timed out).
QAbstractSocket::RemoteHostClosedError 1 The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.
QAbstractSocket::HostNotFoundError 2 The host address was not found.
QAbstractSocket::SocketAccessError 3 The socket operation failed because the application lacked the required privileges.
QAbstractSocket::SocketResourceError 4 The local system ran out of resources (e.g., too many sockets).
QAbstractSocket::SocketTimeoutError 5 The socket operation timed out.
//QAbstractSocket::DatagramTooLargeError 6 The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).
QAbstractSocket::NetworkError 7 An error occurred with the network (e.g., the network cable was accidentally plugged out).
QAbstractSocket::AddressInUseError 8 The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.
QAbstractSocket::SocketAddressNotAvailableError 9 The address specified to QUdpSocket::bind() does not belong to the host.
QAbstractSocket::UnsupportedSocketOperationError 10 The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).
QAbstractSocket::ProxyAuthenticationRequiredError 12 The socket is using a proxy, and the proxy requires authentication.
QAbstractSocket::SslHandshakeFailedError 13 The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)
QAbstractSocket::UnfinishedSocketOperationError 11 Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).
QAbstractSocket::ProxyConnectionRefusedError 14 Could not contact the proxy server because the connection to that server was denied
QAbstractSocket::ProxyConnectionClosedError 15 The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)
QAbstractSocket::ProxyConnectionTimeoutError 16 The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.
QAbstractSocket::ProxyNotFoundError 17 The proxy address set with setProxy() (or the application proxy) was not found.
QAbstractSocket::ProxyProtocolError 18 The connection negotiation with the proxy server because the response from the proxy server could not be understood.
QAbstractSocket::UnknownSocketError -1 An unidentified error occurred.
#endif
void CNetCommFunction::GetErrorMsg( QString& strMsg, QAbstractSocket::SocketError code, QIODevice* pDevice )
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

    strMsg += "\r\n";

    if ( NULL != pDevice) {
        strMsg += pDevice->errorString( );
        strMsg += "\r\n";
    }
}
