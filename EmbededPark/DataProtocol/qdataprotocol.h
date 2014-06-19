#ifndef QDATAPROTOCOL_H
#define QDATAPROTOCOL_H

#include "DataProtocol_global.h"
#include "../CommonLibrary/qcommonlibrary.h"

// class template< typename T0, typename T1 >
// T0 Func( T1 &param );

// class template< typename T0, typename T1 >

class DATAPROTOCOLSHARED_EXPORT QDataProtocol : public QObject
{
    Q_OBJECT
public:

    // Enum type
    typedef enum __PackageType {
        PackageDatabase = 0,
        PackageFile,
        PackageCustom
    } PackageType;

    typedef enum __TableType {
        TableUser = 0,
        TableMonthCard,
        TableTimeCard,
        TableSaveCard,
        TableCustom
    } TableType;

    typedef enum __FileType {
        FileImage = 0,
        FileData,
        FileCustom
    } FileType;

    // Common Header
    typedef struct __CommonHeader {
        QByteArray byDataToken;
        quint32 nDataLength;
        quint32 nReserved;
        PackageType eParcelType;
    } CommonHeader;

    // Aux Header
    typedef struct __DataTableHeader {
        TableType eType;
        quint16 nRowCount;
        quint16 nColumnCount;
        quint32 nReserved;
    } DataTableHeader;

    typedef struct __FileHeader {
        FileType eType;
        quint32 nNameLength;
        quint32 nContentLength;
        quint32 nReserved;
    } FileHeader;

    typedef union __AuxHeader {
        DataTableHeader headerTable;
        FileHeader headerFile;
    } AuxHeader;

    typedef struct __ProtocolHeader {
        CommonHeader common;
        AuxHeader aux;
    } ProtocolHeader;

    // union can't have members of class/struct with constructor

    typedef struct __ProtocolBody {
        QByteArray byData;
    } ProtocolBody;

    typedef struct __ProtocolData {
        ProtocolHeader header;
        ProtocolBody body;
    } ProtocolData, *PProtocolData;

    ////////////////////////////////////////
    void SetCommonHeader( CommonHeader& sHeader );
    void SetCommonHeaderDataToken( );
    void SetCommonHeaderDataLength( quint32 nDataLength );
    void SetCommonHeaderReserved( quint32 nReserved );
    void SetCommonHeaderPackageType( PackageType eType );

    void SetAuxHeader( AuxHeader& sHeader );

    void SetAuxDataTableHeader( DataTableHeader& sHeader );
    void SetAuxDataTableHeaderType( TableType eType );
    void SetAuxDataTableHeaderRow( quint16 nRow );
    void SetAuxDataTableHeaderColumn( quint16 nColumn );
    void SetAuxDataTableHeaderReserved( quint32 nReserved );

    void SetAuxFileHeader( FileHeader& sHeader );
    void SetAuxFileHeaderType( FileType eType );
    void SetAuxFileHeaderNameLength( quint32 nNameLen );
    void SetAuxFileHeaderContentLength( quint32 nContentLen );
    void SetAuxFileHeaderReserved( quint32 nReserved );

    void SetBody( ProtocolBody& sBody );

    void SetProtocolData( ProtocolData& sData );
    ////////////////////////////////////////

    CommonHeader& GetCommonHeader( );
    QByteArray& GetCommonHeaderDataToken( );
    quint32 GetCommonHeaderDataLength( );
    quint32& GetCommonHeaderReserved( );
    PackageType GetCommonHeaderPackageType( );

    AuxHeader& GetAuxHeader( );

    DataTableHeader& GetAuxDataTableHeader( );
    TableType GetAuxDataTableHeaderType( );
    quint16 GetAuxDataTableHeaderRow( );
    quint16 GetAuxDataTableHeaderColumn( );
    quint32 GetAuxDataTableHeaderReserved( );

    FileHeader& GetAuxFileHeader( );
    FileType GetAuxFileHeaderType( );
    quint32 GetAuxFileHeaderNameLength( );
    quint32 GetAuxFileHeaderContentLength( );
    quint32 GetAuxFileHeaderReserved( );

    ProtocolBody& GetBody( );

    ProtocolData& GetProtocolData( );
    bool ParsePackageData( QByteArray& byPackageData, QString& strInfo );
    bool GeneratePackageData( QByteArray& byPackageData, QString& strInfo );

    QDataProtocol( QObject* parent = 0 );
    ~QDataProtocol( );

private:
    // Nested depency must typename C::X a;
    template< class T > T H2N( T tValue );
    template< typename T > T N2H( QByteArray& byValue );
    bool HostByteSequence( ); // true LE else BE

    bool GenerateCommonHeader( QBuffer& buffer );
    bool GenerateAuxHeader( QBuffer& buffer );
    bool GenerateTableHeader( QBuffer& buffer );
    bool GenerateFileHeader( QBuffer& buffer );
    bool GenerateCustomHeader( QBuffer& buffer );

    bool ParseCommonHeader( QBuffer& buffer, QByteArray& byData );
    bool ParseAuxHeader( QBuffer& buffer, QByteArray& byData );
    bool ParseTableHeader( QBuffer& buffer, QByteArray& byData );
    bool ParseFileHeader( QBuffer& buffer, QByteArray& byData );
    bool ParseCustomHeader( QBuffer& buffer, QByteArray& byData );

    bool ParseBody( QBuffer& buffer, QByteArray& byData );
    bool ParseTableBody( QBuffer& buffer, QByteArray& byData );
    bool ParseFileBody( QBuffer& buffer, QByteArray& byData );

private:
    ProtocolData dataPackage;
    QByteArray byDataToken;
    QBuffer byBuffer;
    QTextCodec* pCodec;

signals:

public slots:

};

#endif // QDATAPROTOCOL_H
