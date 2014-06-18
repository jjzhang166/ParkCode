#ifndef SMSEVENT_H
#define SMSEVENT_H

#include <QEvent>
#include <QByteArray>
#include <QStringList>

class CSmsEvent : public QEvent
{
public:
    void SetParameters( QStringList& lstTel, QString& strCnt );
    CSmsEvent( Type evtType );
    QStringList& GetTelList( );
    QString& GetSmsCnt( );

private:
    QStringList lstTelNumber;
    QString strContent;
};

#endif // SMSEVENT_H
