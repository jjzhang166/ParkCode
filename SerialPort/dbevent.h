#ifndef DBEVENT_H
#define DBEVENT_H

#include <QEvent>
#include "../Common/logicinterface.h"

class CDbEvent : public QEvent
{
public:
    explicit CDbEvent( Type event );

    typedef enum __UserEvent { // Write
        SQLInternal = User, // GarageInGarage
        SQLExternal, // StopRd
        ImgInternal,
        ImgExternal
    } UserEvent ;

    typedef struct __WriteParameter {
        QString strSql;
        CommonDataType::BlobType blob;
        QByteArray byData;
        bool bDbHistory;
        bool bTimeCard;
        bool bSelect;
    } WriteParameter;

    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard, bool bSelect );
    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard, bool bSelect, CommonDataType::BlobType blob, QByteArray& byData );
    WriteParameter& GetParameter( );

private:
    WriteParameter evtParamter;
};

#endif // DBEVENT_H
