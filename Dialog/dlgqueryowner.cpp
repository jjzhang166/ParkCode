#include "dlgqueryowner.h"
#include "ui_dlgqueryowner.h"
#include "Common/logicinterface.h"
#include <QDebug>

CDlgQueryOwner::CDlgQueryOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgQueryOwner)
{
    ui->setupUi(this);
    ui->lblTitle->setText( windowTitle( ) );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    setStyleSheet( QString( "background-image:url(%1);" ).arg( statusTip( ) ) );
}

CDlgQueryOwner::~CDlgQueryOwner()
{
    delete ui;
}

void CDlgQueryOwner::on_btnQuery_clicked()
{
    QString strSql = "select cardselfno, cardno, carcp, username, Comments from userinfo a ";
            strSql += "inner join carinfo b on a.cardindex = b.cardindex inner join ";
            strSql += "( select cardno, cardselfno from monthcard union ";
            strSql += "select cardno, cardselfno from savecard ) c on c.cardno = a.cardindex ";

    QStringList lstData;
    QString strWhere = "";
    QString strName = QString( "edt%1q" );
    QString strTmp = "";
    QLineEdit* pEdit = NULL;

    for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
        strTmp = strName.arg( nIndex );
        pEdit = findChild< QLineEdit* >( strTmp );
        strTmp = pEdit->text( );

        if ( strTmp.isEmpty( ) ) {
            continue;
        }

        strWhere += pEdit->statusTip( ).arg( strTmp );
    }

    strSql += strWhere;

    qDebug( ) << strSql << endl;
    int nRows = CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );
    if ( 0>= nRows ) {
        return;
    }

    for ( int nIndex = 1; nIndex <= 4; nIndex++ ) {
        strTmp = strName.arg( nIndex );
        pEdit = findChild< QLineEdit* >( strTmp );
        pEdit->setText( lstData[ nIndex - 1 ] );
    }

    ui->edt5q->setPlainText( lstData[ 4 ] );
}

void CDlgQueryOwner::on_btnClose_clicked()
{
    close( );
}

void CDlgQueryOwner::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent( event );

    QString strFile = statusTip( );
    QPixmap bgimage( strFile );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);
}

void CDlgQueryOwner::on_lblClose_linkActivated(QString)
{
    close( );
}
