#ifndef DLGBULKREGISTER_H
#define DLGBULKREGISTER_H

#include <QDialog>
#include "Common/logicinterface.h"
#include <QResizeEvent>
#include <QCheckBox>

namespace Ui {
    class CDlgBulkRegister;
}

class CDlgBulkRegister : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgBulkRegister( CommonDataType::CardType card, QTableWidget* table, QString strUser, QWidget *parent = 0);
    ~CDlgBulkRegister();

    QLineEdit* GetEditCntrl( );

protected:
    void resizeEvent(QResizeEvent * event );

private:
    void ChangeCheckBoxStatus( QCheckBox* pChk );
    void AddRecord( const QString& strCardID );
    void AddColumn( );
    void AddMonthRow( const QString& strCardID );
    void AddValueRow( const QString& strCardID );
    void AddTimeRow( const QString& strCardID );

    void SaveData( );
    void SaveMonthData( QStringList& lstDuplication, QStringList& lstTotalSql );
    void SaveValueData( QStringList& lstDuplication, QStringList& lstTotalSql );
    void SaveTimeData( QStringList& lstDuplication, QStringList& lstTotalSql );

    void ExecuteSql( QStringList& lstTotalSql );

    inline void AddItem( const QString& strText, int nRow, int nCol, QTableWidget* pTable );
    inline void AddCheckBoxItem( int nRow, int nCol, QTableWidget* pTable, bool bChecked = false );
    inline void AddDateTimeItem( int nRow, int nCol, const QDateTime& dtDefault, QTableWidget* pTable );
    inline void AddComboBoxItem( int nRow, int nCol, int nDefault, int nItem, QTableWidget* pTable );

    void GetSelfNumber( QString& strNumber );
    void AddCbxValue( QComboBox* pCbx );

private slots:
    void on_edtCardID_textChanged(const QString &arg1);

    void on_lblClose_linkActivated(const QString &);

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void on_chkID_clicked(bool checked);

    void OnBulkCarType( int nIndex );

    void OnBulkMonth( int nMonth );

    void on_chkEnterCard_clicked();

    void on_chkLeaveCard_clicked();

    void on_chkMIO_clicked();

private:
    CommonDataType::CardType cardType;
    QString strCreator;
    QTableWidget* tabWidget;
    int nBulkEndMonth;

private:
    Ui::CDlgBulkRegister *ui;
};

#endif // DLGBULKREGISTER_H
