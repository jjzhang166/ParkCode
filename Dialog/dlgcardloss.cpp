#include "dlgcardloss.h"
#include "ui_dlgcardloss.h"

CDlgCardLoss::CDlgCardLoss(QString& strCardID, CommonDataType::CardType card,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgCardLoss)
{
    ui->setupUi(this);
    CCommonFunction::SetWindowIcon( this );
    cardType = card;
    strCardNo = strCardID;

    if ( CommonDataType::MonthlyCard == card ) {
        ui->cbFeeType->setEnabled( false );
        ui->sbAmount->setEnabled( false );
        ui->sbRealAmount->setEnabled( false );
    }

    AddCbxValue( ui->cbFeeType );
    const QDateTime dt = QDateTime::currentDateTime( );
    ui->dtLeave->setDateTime( dt );
}

void CDlgCardLoss::AddCbxValue( QComboBox *pCbx )
{
    QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgTariff );
    QString strKey = "CarType/Count%1";
    int nCount = pSet->value( strKey.arg( "" ), 0 ).toInt( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        pCbx->addItem( pSet->value( strKey.arg( nIndex ), "" ).toString( ) );
    }
}

CDlgCardLoss::~CDlgCardLoss()
{
    delete ui;
}

void CDlgCardLoss::SaveData( )
{
    QString strTables[ ] = { "monthcard", "savecard", "tmpcard" };
    QString strFees[ ] = { "", "储值卡", "计时卡" };
    QString strSql = QString( "update %1 set Inside = 0, CardState = '挂失' where cardno ='%2'" ).arg(  strTables[ cardType ], strCardNo );

    CLogicInterface::GetInterface( )->ExecuteSql( strSql );

    strSql = "update stoprd set outshebeiname = '%1', outtime = '%2', feenum = %3,  \
                  feetime = '%4', feeoperator = '%5', feefactnum = '%6', feekind = '%7', carcpout = '%8', MayDelete = 3 \
                  where cardno = '%9' and outtime is null and feetime is null";

    QString strFormat = ui->dtLeave->displayFormat( );
    QString strFeeTime = QDateTime::currentDateTime( ).toString( strFormat );

    switch ( cardType ) {
    case CommonDataType::MonthlyCard :
        strSql = strSql.arg( ui->edtChannel->text( ), ui->dtLeave->dateTime( ).toString( strFormat ), "0",
                                        strFeeTime, ui->edtOperator->text( ),
                                        "0", "", ui->edtPlate->text( ), strCardNo );
        break;

    case CommonDataType::ValueCard :
    case CommonDataType::TimeCard :
        strSql = strSql.arg( ui->edtChannel->text( ), ui->dtLeave->dateTime( ).toString( strFormat ), ui->sbAmount->text( ),
                                        strFeeTime, ui->edtOperator->text( ),
                                        ui->sbRealAmount->text( ), ui->cbFeeType->currentText( ), ui->edtPlate->text( ), strCardNo );
        strFormat = QString( "insert feerd( feenumb, feetime, feekind, feeoperator, cardno ) \
                                            Values( %1, '%2', '%3收费', '%4', '%5')" ).arg( ui->sbRealAmount->text( ), strFeeTime,
                                            strFees[ cardType ], ui->edtOperator->text( ), strCardNo );
        CLogicInterface::GetInterface( )->ExecuteSql( strFormat );
        break;
    }

    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
}

void CDlgCardLoss::on_btnCancel_clicked()
{
    close( );
}

void CDlgCardLoss::on_btnOK_clicked()
{
    SaveData( );
    close( );
}
