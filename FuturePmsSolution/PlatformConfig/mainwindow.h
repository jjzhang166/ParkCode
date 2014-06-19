#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>

#include "../ManipulateIniFile/qmanipulateinifile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void ReadData( );
    void SaveData( );
    inline void GetItemValue(const QManipulateIniFile::IniFileNames iniFile,
                             const QManipulateIniFile::IniFileSections iniSection,
                             const QManipulateIniFile::IniFileSectionItems iniItem,
                             QLineEdit* pEdit );

    inline void GetItemValue(const QManipulateIniFile::IniFileNames iniFile,
                             const QManipulateIniFile::IniFileSections iniSection,
                             const QManipulateIniFile::IniFileSectionItems iniItem,
                             QComboBox* pComboBox );

    inline void SetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                              const QManipulateIniFile::IniFileSections iniSection,
                              const QManipulateIniFile::IniFileSectionItems iniItem,
                              QLineEdit* pEdit );

    inline void SetItemValue( const QManipulateIniFile::IniFileNames iniFile,
                              const QManipulateIniFile::IniFileSections iniSection,
                              const QManipulateIniFile::IniFileSectionItems iniItem,
                              QComboBox* pComboBox );

    void ReadPClientConfig( );
    void ReadPServerConfig( );
    void ReadPDataServerConfig( );

    void SavePClientConfig( );
    void SavePServerConfig( );
    void SavePDataServerConfig( );

    void SetDbType( );
    
private slots:
    void on_btnSave_clicked();

    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
    QManipulateIniFile manipulateIniFile;
};

#endif // MAINWINDOW_H
