#include "hbevent.h"

CHbEvent::CHbEvent( UserEvent event ) :
    QEvent( ( Type ) event )
{
    bTransferProtocol = false;
}

CHbEvent::~CHbEvent( )
{

}

void CHbEvent::SetByteArrayData( QByteArray &byData, bool bTcp )
{
    byByteArray.clear( );
    byByteArray.append( byData.data( ), byData.count( ) );
    bTransferProtocol = bTcp;
}

QByteArray& CHbEvent::GetByteArrayData( )
{
    return byByteArray;
}

bool CHbEvent::GetProtocolType( )
{
    return bTransferProtocol;
}

void CHbEvent::SetPassRecord( TableData &tabPassRecord )
{
    table.strPass.clear( );
    table.strPass.append(  tabPassRecord.strPass );

    table.nCols = tabPassRecord.nCols;
    table.nRows = tabPassRecord.nRows;
    table.tabType = tabPassRecord.tabType;
}

CHbEvent::TableData& CHbEvent::GetPassRecord( )
{
    return table;
}

void CHbEvent::SetImgLog( QString &strLog )
{
    strImgLog.clear( );
    strImgLog.append( strLog );
}

QString& CHbEvent::GetImgLog( )
{
    return strImgLog;
}
