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
        bool bEnter;
        QString strCardNo;
        int nType;
        int nInsert;
        bool bGarage;
        QStringList lstBroadcastData;
    } WriteParameter;

    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard, bool bSelect, int nInsert, QStringList& lstBroadcastData, QString& strCardNumber );
    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard, bool bSelect, bool bGarage );
    void SetParameter( QString& strSql, bool bHistory, bool bTimerCard, bool bSelect, CommonDataType::BlobType blob, QByteArray& byData );
    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard,
                       bool bEnter, QString& strCardNo, bool bGarage, int nType,
                       bool bSelect, int nInsert, QStringList& lstBroadcastData,
                       CommonDataType::BlobType blob, QByteArray& byData );
    void SetParameter( QString&  strSql, bool bHistory, bool bTimeCard,
                       bool bEnter, QString& strCardNo, bool bGarage, int nType,
                       bool bSelect,
                       CommonDataType::BlobType blob, QByteArray& byData );
    void SetParameter( bool bEnter, int nType, bool bGarage, QString& strCardNo, QByteArray& byData );
    WriteParameter& GetParameter( );

    void SetRefreshUI( bool bRefresh );
    bool GetRefreshUI( );

    void SetStoprdid( QString& strRdid );
    QString& GetStoprdid( );

private:
    WriteParameter evtParamter;
    bool bRefreshUI;
    QString strStoprdid;
};

#endif // DBEVENT_H
