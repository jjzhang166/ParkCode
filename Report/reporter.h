#ifndef REPORTER_H
#define REPORTER_H

#include <QObject>
#include "Common/CommonType.h"
#include <QtWebKit/QWebView>
#include <QPrinter>
#include <QDateTime>
#include <QProcess>
#include "qreportthread.h"
#include <QRadioButton>

class CReporter : public QObject
{
    Q_OBJECT
public:
    explicit CReporter( QObject *parent = 0);

public:
    void Print( CommonDataType::ReportType rType, QWebView& wvReport );
    void BuildHtmlDoc( QDateTime& dtStart, QDateTime& dtEnd, CommonDataType::ReportType rType, QWebView& wvReport );

    void Print( CommonDataType::ReportType rType );
    void BuildHtmlDoc( QDateTime& dtStart, QDateTime& dtEnd, CommonDataType::ReportType rType );

    void SetWhere( QStringList& lstWhere );
    void SetPersonTime( bool bPerson );
    void SetWebView( QWebView* pView );
    void SetReportTitle( QRadioButton** ppTitle );

private:
    void PostReportEvent( const QString& strXml, QMyReportEvent::MyReportEvent eEvent );

    void GetHtml( CommonDataType::ReportType rType, QString& strTitle, QString& strFooter, QString& strTableBody, QStringList& lstData );
    void RowData( int nSum[ ], QStringList& lstReslut, QStringList& lstData,
                  int nField, QString& strTotal1, QString& strTotal2, int nStartIndex, int nCols );
    void RowData( QStringList& lstReslut, QStringList& lstData,
                  int nField, int nStartIndex, int nCols );
    inline void GetSumData( QString& strFooter, QStringList& lstData, int nSkip );
    inline void GetRowHtml( QString& strRow, QStringList& lstData );
    inline void GetSQL( QString& strSql, CommonDataType::ReportType rType, QDateTime& dtStart, QDateTime& dtEnd );
    void PrintPdf( QString& strFile );
    inline void GetTitle( CommonDataType::ReportType rType, QDateTime& dtStart, QDateTime& dtEnd, QString& strTitle );
    bool GetAdboeExePath( QString& strExe );
    void KillAdobeProcess( QString& strExe );
private:
    QPrinter printer;
    //QProcess prococess;
    QString strAdobeExe;
    QStringList lstWheres;
    bool bPersonTime;
    QReportThread* pReportThread;
    QWebView* pReportView;
    QString strPronvice;
    QDateTime dtStartTime;
    QDateTime dtEndTime;
    QRadioButton** ppReportTitle;
signals:

public slots:
    void HandleReportData( int nType, QStringList lstData );
};

#endif // REPORTER_H
