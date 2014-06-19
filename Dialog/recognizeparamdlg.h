#ifndef RECOGNIZEPARAMDLG_H
#define RECOGNIZEPARAMDLG_H

#include <QDialog>
#include <QSettings>
#include <QComboBox>
#include <QResizeEvent>

namespace Ui {
    class CRecognizeParamDlg;
}

class CRecognizeParamDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CRecognizeParamDlg(QWidget *parent = 0);
    ~CRecognizeParamDlg();

protected:
    void resizeEvent(QResizeEvent * event );

private:
    void ControlValue( bool bRead, QStringList& lstData, int nTabIndex = 0 );
    void ReadFile( );
    void WriteFile( );
    void SetKeyName( QStringList& lstKey );
    void GetValue( bool bRead );
    void SetDefault( QStringList& lstData );
    void ReadCB( QString& strSection, QComboBox* pCB );
    void WriteCB( QString& strSection, QComboBox* pCB, QString& strDefault );
private:
    Ui::CRecognizeParamDlg *ui;
    QSettings* pSettings;
    QStringList lstKeys;
    QStringList defaultData;
    bool bRestart;
    QString strPath;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnDefault_clicked();
    void on_btnSave_clicked();
    void on_btnExit_clicked();
};

#endif // RECOGNIZEPARAMDLG_H
