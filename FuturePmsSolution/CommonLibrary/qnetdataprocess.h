#ifndef QNETDATAPROCESS_H
#define QNETDATAPROCESS_H

#include "QCommonFunction_global.h"
#include <QObject>
#include "CommonEnum.h"
#include "CommonDataStruct.h"

class QCOMMONFUNCTIONSHARED_EXPORT QNetDataProcess : public QObject
{
    Q_OBJECT
public:
    explicit QNetDataProcess(QObject *parent = 0);

private:
    void ProcessData( const char* pData, quint64 nLen );
    void ProcessTableData( const char* pData );
    void ProcessImageData( const char* pData );
    void ProcessHeartbeatData( const char* pData );
    void ProcessSvrMsgData( const char* pData );
    void ProcessCltMsgData( const char* pData );
    void ProcessMgmtData( const char* pData );
    
signals:
    
public slots:
    
};

#endif // QNETDATAPROCESS_H
