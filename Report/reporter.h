#ifndef REPORTER_H
#define REPORTER_H

#include <QObject>
#include "Common/CommonType.h"
#include <QtWebKit/QWebView>
#include <QPrinter>
#include <QDateTime>
#include <QProcess>

class CReporter : public QObject
{
    Q_OBJECT
public:
    explicit CReporter(QObject *parent = 0);

public:
    void Print( CommonDataType::ReportType rType, QWebView& wvReport );
    void BuildHtmlDoc( QDateTime& dtStart, QDateTime& dtEnd, CommonDataType::ReportType rType, QWebView& wvReport );
    void SetWhere( QStringList& lstWhere );
    void SetPersonTime( bool bPerson );

private:
    void GetHtml( CommonDataType::ReportType rType, QString& strTitle, QString& strFooter, QString& strTableBody, QStringList& lstData );
    void RowData( int nSum[ ], QStringList& lstReslut, QStringList& lstData,
                  int nField, QString& strTotal1, QString& strTotal2, int nStartIndex, int nCols );
    inline void GetSumData( int nSum[ ], int nCounter, QString& strFooter );
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
signals:

public slots:

};

#endif // REPORTER_H
