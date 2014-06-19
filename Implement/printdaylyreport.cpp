#include "Header/printdaylyreport.h"
#include "ui_printdaylyreport.h"
#include "Common/commonfunction.h"
#include "Dialog/cdlgquerywhere.h"
#include "Dialog/cdlgmonthquery.h"

CPrintDaylyReport::CPrintDaylyReport(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CPrintDaylyReport)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );

    GetParameter( );

    ui->lblTitle->setText( windowTitle( ) );
    nReportType = 0;
    QString strName = "rdChx%1";
    QChar cFill = '0';
    for ( int nIndex = 1; nIndex <= ui->gbType->children().size( ); nIndex++ ) {
        QString strTmp = strName.arg( nIndex, 2, 10, cFill );
        QRadioButton* pRd = ui->gbType->findChild< QRadioButton* >( strTmp );
        if ( NULL != pRd ) {
            connect( pRd, SIGNAL( clicked( ) ), this, SLOT( OnRdChkClicked( ) ) );
        }
    }

    QDateTime date = QDateTime::currentDateTime( );
    SetDateTime( date, date );

#ifdef NewUI
    move( 123, 46 );
#else
    move( 123, 177 );
#endif
}

void CPrintDaylyReport::GetParameter( )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );

    bPersonTime = pSet->value( "Report/PersonTime", false ).toBool( );
    tPersonStartTime = pSet->value( "Report/PersonStartTime", "00:00:00" ).toTime( );
    tPersonEndTime = pSet->value( "Report/PersonEndTime", "23:59:59" ).toTime( );
    tTimeCardStartTime = pSet->value( "Report/TimeCardStartTime", "00:00:00" ).toTime( );
    tTimeCardEndTime = pSet->value( "Report/TimeCardEndTime", "23:59:59" ).toTime( );

    reporter.SetPersonTime( bPersonTime );
}

void CPrintDaylyReport::SaveParameter( CommonDataType::ReportType nType)
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    QString strFormat = "HH:mm:ss";

    if ( CommonDataType::ReportPerson == nType ) {
        if ( bPersonTime ) {
            tPersonStartTime = ui->dReportStartDate->time( );
            tPersonEndTime = ui->dReportEndDate->time( );

            pSet->setValue( "Report/PersonStartTime", tPersonStartTime.toString( strFormat ) );
            pSet->setValue( "Report/PersonEndTime", tPersonEndTime.toString( strFormat ) );
        }
    } else if( CommonDataType::ReportTimeCardDetail == nType ) {
        tTimeCardStartTime = ui->dReportStartDate->time( );
        tTimeCardEndTime = ui->dReportEndDate->time( );

        pSet->setValue( "Report/TimeCardStartTime", tTimeCardStartTime.toString( strFormat ) );
        pSet->setValue( "Report/TimeCardEndTime", tTimeCardEndTime.toString( strFormat ) );
    }
}

CPrintDaylyReport::~CPrintDaylyReport()
{
    delete ui;
}

void CPrintDaylyReport::SetDateTime( QDateTime& dtStart, QDateTime& dtEnd )
{
    ui->dReportStartDate->setDateTime( dtStart );
    ui->dReportEndDate->setDateTime( dtEnd );
}

void CPrintDaylyReport::SetDateTimeFormat( QString &strFormat )
{
    ui->dReportStartDate->setDisplayFormat( strFormat );
    ui->dReportEndDate->setDisplayFormat( strFormat );
}

void CPrintDaylyReport::OnRdChkClicked( )
{
    QRadioButton* pBtn = qobject_cast< QRadioButton* >( sender( ) );
    nReportType = pBtn->objectName( ).right( 2 ).toInt( ) - 1; // 1 - 9

    bool bMonth = CommonDataType::ReportMonth == nReportType;
    ui->dReportEndDate->setEnabled( !bMonth );
    ui->dReportStartDate->setEnabled( !bMonth );
    if ( bMonth ) {
        CDlgMonthQuery dlg;
        dlg.SetParams( lstMonthQuery );
        lstMonthQuery.clear( );

        if ( QDialog::Accepted == dlg.exec( ) ) {
            dlg.GetParams( lstMonthQuery );
        }

        reporter.SetWhere( lstMonthQuery );
        return;
    }

    QString strFormat = "yyyy-MM-dd";
    if ( CommonDataType::ReportTimeCardDetail == nReportType ) {
        strFormat = "yyyy-MM-dd HH:mm:ss";
        SetDateTimeFormat( strFormat );
        //QDateTime dtCurrent = QDateTime::currentDateTime( );
        QDateTime dtStart( ui->dReportStartDate->date( ), tTimeCardStartTime );
        QDateTime dtEnd( ui->dReportEndDate->date( ), tTimeCardEndTime );
        SetDateTime( dtStart, dtEnd );
    } if ( CommonDataType::ReportPerson == nReportType && bPersonTime ) {
        strFormat = "yyyy-MM-dd HH:mm:ss";
        SetDateTimeFormat( strFormat );
        //QDateTime dtCurrent = QDateTime::currentDateTime( );
        QDateTime dtStart( ui->dReportStartDate->date( ), tPersonStartTime );
        QDateTime dtEnd( ui->dReportEndDate->date( ), tPersonEndTime );
        SetDateTime( dtStart, dtEnd );
    } else {
        SetDateTimeFormat( strFormat );
    }

    if ( CommonDataType::ReportMonthInOut == nReportType ) {
        QStringList lstWhere;
        CDlgQueryWhere dlg;
        dlg.exec( );
        dlg.GetWhere( lstWhere );
        reporter.SetWhere( lstWhere );
    }
}

void CPrintDaylyReport::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CPrintDaylyReport::on_btnGenerate_clicked()
{
    SaveParameter( ( CommonDataType::ReportType ) nReportType );

    QDateTime dtStart = ui->dReportStartDate->dateTime( );
    QDateTime dtEnd = ui->dReportEndDate->dateTime( );
    //QTime time = ui->dReportEndDate->maximumTime( );
    //dtEnd.setTime( time );
    reporter.BuildHtmlDoc( dtStart, dtEnd, ( CommonDataType::ReportType ) nReportType, *ui->wvReport );
}

void CPrintDaylyReport::on_btnPrint_clicked()
{
    reporter.Print( ( CommonDataType::ReportType ) nReportType, *ui->wvReport );
}

void CPrintDaylyReport::on_btnClose_clicked()
{
    close( );
}

void CPrintDaylyReport::on_lblClose_linkActivated(QString)
{
    close( );
}
