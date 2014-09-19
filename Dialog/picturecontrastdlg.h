#ifndef PICTURECONTRASTDLG_H
#define PICTURECONTRASTDLG_H

#include <QDialog>
#include <QCloseEvent>
#include <QDateTime>
#include <QRadioButton>
#include <QShowEvent>
#include <QResizeEvent>
#include "Common/CommonType.h"
#include "Common/logicinterface.h"
#include "../Header/printMonthlyReport.h"

namespace Ui {
    class CPictureContrastDlg;
}

class CPictureContrastDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CPictureContrastDlg( QWidget *parent = 0);
    ~CPictureContrastDlg();

    void SetParams( QByteArray &byData, QByteArray &vData, int nMin, int nHour, int nAmount, bool bEnter );
    QString GetFeeRateType( );
    QString GetDiscountType( );
    void SetNoEnterTime( bool bUnknown, int nMiNFee = 0 );
    QString GetCardNo( );
    QString GetPlate( );

public:
    void InitDlg( QStringList& lstRows, QPixmap& bmpEnter, QPixmap& bmpLeave, QByteArray& byData, bool bBuffer);
    void InitDlg( QStringList& lstData, QString& strWhere, QString& strCardNo, int nType, bool bEnter  );
    int GetAmount( );
    int GetDisAmount( );
    void LoadMyImage( CommonDataType::BlobType blob, QString& strCardNo, bool bHistory, bool bAuto = true, bool bBuffer = false );
    void LoadRemoteImg( CommonDataType::BlobType blob, QString& strWhere, bool bHistory, QLabel *pLbl );
    void SetParkID( QString& strID );

    void DefaultClicked(  );
    void SetDbInterf( CLogicInterface* pInterf );

protected:
    void closeEvent( QCloseEvent *e );
    void showEvent(QShowEvent *  );
    void resizeEvent( QResizeEvent *event );
    void keyPressEvent ( QKeyEvent * event );

signals:
    void SendTimeCardInfo( QByteArray &byData, QByteArray &vData, int nMin, int nHour, int nAmount, bool bEnter );

private:
    void DisableButton( bool bEnable );
    void ShowVerifyPlate( int nChannel );
    void ConnectRadioBtn( );
    void Calculate( QRadioButton& rbtn );
    void SwitchImage( QPushButton *pBtn, bool bDown );
    void Write2UI( QStringList& lstRows, bool bEnter , bool bAuto = true, bool bBuffer = false );
    void FillDiscount(  );
    void CaculateAndPlay( QRadioButton& rbtn, bool bCalculate = true );
    int GetDiscount( int nPrevValue );
    QRadioButton& SetCarType( QString& strType );
    void SetCurrentRadioBox( QRadioButton* pRbx );
    void AnalogClicked( QRadioButton* pBtn, bool bCalculate = true );
    void ClearPlate( );
    QLabel* lblLicense[ 4 ][ 8 ];

private slots:
    void on_btnPass_clicked();
    void RbtnClicked( );
    void BtnPressed( );
    void BtnReleased( );
    void OnClickedDlgPopup( );
    void CbxIndexChanged( int nIndex );
    void onLinkActivated( QString link );
    void PlateCheck( QString strChar, int nChannel, int nIndex );
    void HandleManualRecogonization( int nChannel, QString strPlate );
    void HandleEnterPlate( QStringList lstParams );

private:
    Ui::CPictureContrastDlg *ui;
    int nAmount;
    int nStandardFee;
    int nFeeNum;
    QString strTabName;
    QString strParkName;
    QDateTime dtStart;
    QDateTime dtEnd;
    int nHour;
    int nMin;
    QByteArray byData;
    QString strButtonStyle;
    QString strImagePath;
    QString strVideoWhere;
    int nCardType;
    QString strParkID;
    CPictureContrastDlg* pFeeDlg;
    CPrintMonthlyReport *pPrintMonthlyReport;

    QByteArray byData1;
    QByteArray vData1;
    int nMin1;
    int nHour1;
    int nAmount1;
    bool bEnter1;

    QString strFeeRateType;
    CLogicInterface* pDbInterface;
    bool bNoEnterTime;
    bool bRawNoEnterTime;
    int nMinFee4NoEnterTime;
};

#endif // PICTURECONTRASTDLG_H
