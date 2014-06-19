#ifndef HBEVENT_H
#define HBEVENT_H

#include <QEvent>
#include <QString>
#include <QByteArray>

class CHbEvent : public QEvent
{
public:
    typedef enum __UserEvent {
        HbPassRecord = User,
        HbInOutImg,
        HbForward,
        HbImgLog
    } UserEvent ;

    typedef struct __TableData {
        QString strPass;
        int nCols;
        int nRows;
        int tabType;
    } TableData;

    CHbEvent( UserEvent event );
    ~CHbEvent( );

    void SetPassRecord( TableData& tabPassRecord );
    TableData& GetPassRecord( );

    void SetByteArrayData( QByteArray&  byData, bool bTcp );
    QByteArray& GetByteArrayData( );
    bool GetProtocolType( );

    void SetImgLog( QString& strLog );
    QString& GetImgLog( );

private:
    TableData table;

    QByteArray byByteArray;
    QString strImgLog;
    bool bTransferProtocol;
};

#endif // HBEVENT_H
