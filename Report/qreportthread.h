#ifndef QREPORTTHREAD_H
#define QREPORTTHREAD_H

#include <QApplication>
#include <QThread>
#include "qreportevent.h"
#include "Common/logicinterface.h"
//作为所有查询使用, 比如进出记录

class QReportThread : public QThread
{
    Q_OBJECT
public:
    static QReportThread* CreateReportThread( );
    void PostReportEvent( const QString& strXmlParams, QMyReportEvent::MyReportEvent eEvent );

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    explicit QReportThread(QObject *parent = 0);
    bool ConnectDb( );
    inline void PostEvent( QMyReportEvent* pEvent );
    void ProcessEvent( int nType, QString& strSQL );

private:
    CLogicInterface interfaceNormal;
    static QReportThread* pThreadInstance;
    QString strSpSql;
    
signals:
    void ReportData( int nType, QStringList lstData );
    void ExecuteSQLData( int nType, QStringList lstData );
    
public slots:
    
};

#endif // QREPORTTHREAD_H
