#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDate>
#include <QString>
#include <QPixmap>
#include <QFile>


int main(int argc, char *argv[])
{
    QString str;
    bool bRet = str.isNull( );
    bRet = str.isEmpty( );

    QString str1( "" );
    bRet = str1.isNull( );
    bRet = str1.isEmpty( );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString strFile = "D:/WinParkUI/debug/Image/NewIcon/wer.jpg";
    QFile::remove( strFile );

    return a.exec();
}
