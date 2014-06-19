#include "qdataprotocol.h"


QDataProtocol::QDataProtocol( QObject* parent ) : QObject( parent )
{
    pCodec = QCommonLibrary::GetTextCodec( );
    const QString& strToken = QCommonLibrary::GetDataToken( );
    byDataToken = pCodec->fromUnicode( strToken );
}

QDataProtocol::~QDataProtocol( )
{

}

QDataProtocol::ProtocolData& QDataProtocol::GetProtocolData( )
{
    return dataPackage;
}

bool QDataProtocol::ParseCommonHeader( QBuffer &buffer, QByteArray &byData )
{
    qint32 nUInt32Len = sizeof ( quint32 );
    bool bRet = true;

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.common.nDataLength = N2H< quint32 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.common.nReserved = N2H< quint32 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.common.eParcelType = ( PackageType ) N2H< quint32 >( byData );

    ERROR_PROCESS:
    return bRet;
}

bool QDataProtocol::ParseTableHeader( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;
    qint32 nUInt32Len = sizeof ( quint32 );
    qint32 nUInt16Len = sizeof ( quint16 );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerTable.eType = ( TableType ) N2H< quint32 >( byData );

    byData = buffer.read( nUInt16Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerTable.nRowCount = N2H< quint16 >( byData );

    byData = buffer.read( nUInt16Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerTable.nColumnCount = N2H< quint16 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerTable.nReserved = N2H< quint32 >( byData );

    ERROR_PROCESS:
    return bRet;
}

bool QDataProtocol::ParseFileHeader( QBuffer &buffer, QByteArray &byData )
{
    qint32 nUInt32Len = sizeof ( quint32 );
    bool bRet = true;

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerFile.eType = ( FileType ) N2H< quint32 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerFile.nNameLength = N2H< quint32 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerFile.nContentLength = N2H< quint32 >( byData );

    byData = buffer.read( nUInt32Len );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }
    dataPackage.header.aux.headerFile.nReserved = N2H< quint32 >( byData );

    ERROR_PROCESS:
    return bRet;
}

bool QDataProtocol::ParseCustomHeader( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;

    return bRet;
}

bool QDataProtocol::ParseAuxHeader( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;

    switch ( dataPackage.header.common.eParcelType ) {
    case PackageDatabase :
        bRet = ParseTableHeader( buffer, byData );
        break;

    case PackageFile :
        bRet = ParseFileHeader( buffer, byData );
        break;

    case PackageCustom :
        bRet = ParseCustomHeader( buffer, byData );
        break;
    }

    return bRet;
}

bool QDataProtocol::ParseTableBody( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;

    return bRet;
}

bool QDataProtocol::ParseFileBody( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;

    return bRet;
}

bool QDataProtocol::ParseBody( QBuffer &buffer, QByteArray &byData )
{
    bool bRet = true;

    switch ( dataPackage.header.common.eParcelType ) {
    case PackageDatabase :
        bRet = ParseTableBody( buffer, byData );
        break;

    case PackageFile :
        bRet = ParseFileBody( buffer, byData );
        break;

    case PackageCustom :
        break;
    }

    return bRet;
}

bool QDataProtocol::GenerateCommonHeader( QBuffer& buffer )
{
    qint32 nUInt32Len = sizeof ( quint32 );
    bool bRet = true;

    quint32 nIntValue = H2N< quint32 >( dataPackage.header.common.nDataLength );
    buffer.write( ( const char* ) & nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.common.nReserved );
    buffer.write( ( const char* ) & nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.common.eParcelType );
    buffer.write( ( const char* ) & nIntValue, nUInt32Len );

    return bRet;
}

bool QDataProtocol::GenerateAuxHeader( QBuffer& buffer )
{
    bool bRet = true;

    switch ( dataPackage.header.common.eParcelType ) {
    case PackageDatabase :
        bRet = GenerateTableHeader( buffer );
        break;

    case PackageFile :
        bRet = GenerateFileHeader( buffer );
        break;

    case PackageCustom :
        bRet = GenerateCustomHeader( buffer );
        break;
    }

    return bRet;
}

bool QDataProtocol::GenerateTableHeader( QBuffer& buffer )
{
    bool bRet = true;
    qint32 nUInt32Len = sizeof ( quint32 );
    qint32 nUInt16Len = sizeof ( quint16 );

    quint32 nIntValue = H2N< quint32 >( dataPackage.header.aux.headerTable.eType );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerTable.nColumnCount );
    buffer.write( ( const char* ) &nIntValue, nUInt16Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerTable.nReserved );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerTable.nRowCount );
    buffer.write( ( const char* ) &nIntValue, nUInt16Len );

    return bRet;
}

bool QDataProtocol::GenerateFileHeader( QBuffer& buffer )
{
    bool bRet = true;
    qint32 nUInt32Len = sizeof ( quint32 );

    quint32 nIntValue = H2N< quint32 >( dataPackage.header.aux.headerFile.eType );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerFile.nContentLength );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerFile.nNameLength );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );

    nIntValue = H2N< quint32 >( dataPackage.header.aux.headerFile.nReserved );
    buffer.write( ( const char* ) &nIntValue, nUInt32Len );


    return bRet;
}

bool QDataProtocol::GenerateCustomHeader( QBuffer& buffer )
{
    bool bRet = true;
    return bRet;
}

bool QDataProtocol::GeneratePackageData( QByteArray &byPackageData, QString &strInfo )
{
    byPackageData.clear( );
    qint64 nRetLen;

    byBuffer.setBuffer( &byPackageData );
    bool bRet = byBuffer.open( QIODevice::WriteOnly );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = byBuffer.reset( );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    nRetLen = byBuffer.write( byDataToken );
    bRet = ( byDataToken.length( ) != nRetLen );
    if ( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = GenerateCommonHeader( byBuffer );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = GenerateAuxHeader( byBuffer );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    ERROR_PROCESS:
    if( !bRet ) {
        strInfo = byBuffer.errorString( );
    }

    byBuffer.close( );

    return bRet;
}

bool QDataProtocol::ParsePackageData( QByteArray& byPackageData, QString& strInfo )
{
    byBuffer.setBuffer( &byPackageData );
    QByteArray byData;

    bool bRet = byBuffer.open( QIODevice::ReadOnly );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = byBuffer.reset( );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    byData = byBuffer.read( byDataToken.length( ) );
    if ( byData.isEmpty( ) ) {
        bRet = false;
        goto ERROR_PROCESS;
    }

    bRet = ParseCommonHeader( byBuffer, byData );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = ParseAuxHeader( byBuffer, byData );
    if( !bRet ) {
        goto ERROR_PROCESS;
    }

    bRet = ParseBody( byBuffer, byData );

    ERROR_PROCESS:
    if( !bRet ) {
        strInfo = byBuffer.errorString( );
    }

    byBuffer.close( );

    return bRet;
}

void QDataProtocol::SetCommonHeader( CommonHeader& sHeader )
{
    dataPackage.header.common = sHeader;
}

void QDataProtocol::SetCommonHeaderDataToken( )
{
    dataPackage.header.common.byDataToken = byDataToken;
}

void QDataProtocol::SetCommonHeaderDataLength( quint32 nDataLength )
{
    dataPackage.header.common.nDataLength = nDataLength;
}

void QDataProtocol::SetCommonHeaderReserved( quint32 nReserved )
{
    dataPackage.header.common.nReserved = nReserved;
}

void QDataProtocol::SetCommonHeaderPackageType( PackageType eType )
{
    dataPackage.header.common.eParcelType = eType;
}

void QDataProtocol::SetAuxHeader( AuxHeader& sHeader )
{
    dataPackage.header.aux = sHeader;
}

void QDataProtocol::SetAuxDataTableHeader( DataTableHeader& sHeader )
{
    dataPackage.header.aux.headerTable = sHeader;
}

void QDataProtocol::SetAuxDataTableHeaderType( TableType eType )
{
    dataPackage.header.aux.headerTable.eType = eType;
}

void QDataProtocol::SetAuxDataTableHeaderRow( quint16 nRow )
{
    dataPackage.header.aux.headerTable.nRowCount = nRow;
}

void QDataProtocol::SetAuxDataTableHeaderColumn( quint16 nColumn )
{
    dataPackage.header.aux.headerTable.nColumnCount = nColumn;
}

void QDataProtocol::SetAuxDataTableHeaderReserved( quint32 nReserved )
{
    dataPackage.header.aux.headerTable.nReserved = nReserved;
}

void QDataProtocol::SetAuxFileHeader( FileHeader& sHeader )
{
    dataPackage.header.aux.headerFile = sHeader;
}

void QDataProtocol::SetAuxFileHeaderType( FileType eType )
{
    dataPackage.header.aux.headerFile.eType = eType;
}

void QDataProtocol::SetAuxFileHeaderNameLength( quint32 nNameLen )
{
    dataPackage.header.aux.headerFile.nNameLength = nNameLen;
}

void QDataProtocol::SetAuxFileHeaderContentLength( quint32 nContentLen )
{
    dataPackage.header.aux.headerFile.nContentLength = nContentLen;
}

void QDataProtocol::SetAuxFileHeaderReserved( quint32 nReserved )
{
    dataPackage.header.aux.headerFile.nReserved = nReserved;
}

void QDataProtocol::SetBody( ProtocolBody& sBody )
{
    dataPackage.body = sBody;
}

void QDataProtocol::SetProtocolData( ProtocolData& sData )
{
    dataPackage = sData;
}

QDataProtocol::CommonHeader& QDataProtocol::GetCommonHeader( )
{
    return dataPackage.header.common;
}

QByteArray& QDataProtocol::GetCommonHeaderDataToken( )
{
    return dataPackage.header.common.byDataToken;
}

quint32 QDataProtocol::GetCommonHeaderDataLength( )
{
    return dataPackage.header.common.nDataLength;
}

quint32& QDataProtocol::GetCommonHeaderReserved( )
{
    return dataPackage.header.common.nReserved;
}

QDataProtocol::PackageType QDataProtocol::GetCommonHeaderPackageType( )
{
    return dataPackage.header.common.eParcelType;
}

QDataProtocol::AuxHeader& QDataProtocol::GetAuxHeader( )
{
    return dataPackage.header.aux;
}

QDataProtocol::DataTableHeader& QDataProtocol::GetAuxDataTableHeader( )
{
    return dataPackage.header.aux.headerTable;
}

QDataProtocol::TableType QDataProtocol::GetAuxDataTableHeaderType( )
{
    return dataPackage.header.aux.headerTable.eType;
}

quint16 QDataProtocol::GetAuxDataTableHeaderRow( )
{
    return dataPackage.header.aux.headerTable.nRowCount;
}

quint16 QDataProtocol::GetAuxDataTableHeaderColumn( )
{
    return dataPackage.header.aux.headerTable.nColumnCount;
}

quint32 QDataProtocol::GetAuxDataTableHeaderReserved( )
{
    return dataPackage.header.aux.headerTable.nReserved;
}

QDataProtocol::FileHeader& QDataProtocol::GetAuxFileHeader( )
{
    return dataPackage.header.aux.headerFile;
}

QDataProtocol::FileType QDataProtocol::GetAuxFileHeaderType( )
{
    return dataPackage.header.aux.headerFile.eType;
}

quint32 QDataProtocol::GetAuxFileHeaderNameLength( )
{
    return dataPackage.header.aux.headerFile.nNameLength;
}

quint32 QDataProtocol::GetAuxFileHeaderContentLength( )
{
    return dataPackage.header.aux.headerFile.nContentLength;
}

quint32 QDataProtocol::GetAuxFileHeaderReserved( )
{
    return dataPackage.header.aux.headerFile.nReserved;
}

QDataProtocol::ProtocolBody& QDataProtocol::GetBody( )
{
    return dataPackage.body;
}

template< class T >
T QDataProtocol::H2N( T tValue )
{
    bool bLE = HostByteSequence( );

    if ( bLE ) {
        tValue = qToBigEndian< T >( tValue );
    }

    return tValue;
}

template< typename T >
T QDataProtocol::N2H( QByteArray& byValue )
{
    const char* pData = byValue.data( );
    T tData = *( ( T* ) pData );

    bool bLE = HostByteSequence( );

    if ( bLE ) {
        tData = qFromBigEndian< T >( tData );
    }

    return tData;
}

bool QDataProtocol::HostByteSequence( )
{
    // true LE else BE
    quint8 cData[ ] = { 0x11, 0x22 };
    quint16 nData = 0x1122;
    quint8* pData = ( quint8* ) &nData;

    bool bRet = ( cData[ 0 ] == pData[ 0 ] ) && ( cData[ 1 ] == pData[ 1 ] );

    return bRet;
}
