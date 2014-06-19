#ifndef QCONTROLLER_H
#define QCONTROLLER_H

#include <QObject>
#include "Controller_global.h"
#include "../ControllerSP/qcontrollersp.h"
#include "../ControllerCommon/qcontrollercommon.h"

class CONTROLLERSHARED_EXPORT QController : public QObject {
    Q_OBJECT

public:
    explicit QController( QObject* parent = 0 );
    ~QController( );

    bool ConrollSP( const bool bOpen );
    qint64 WriteData( QByteArray& data, int nWaitTime = 0, const bool bThread = false );

private:
    QControllerSP* pController;

signals:
    void Cmd( QByteArray data, bool bSend );
    void Data( QByteArray data );
    void Query( QString strInfo, qint8 nIndex, QByteArray byData );

private slots:
    void HandleCmd( QByteArray data, bool bSend );
    void HandleData( QByteArray data );
    void HandleQuery( QString strInfo, qint8 nIndex, QByteArray byData );
};

#endif // QCONTROLLER_H
