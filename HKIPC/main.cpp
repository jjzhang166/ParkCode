#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec* pCodec = QTextCodec::codecForLocale( );
    QTextCodec::setCodecForLocale( pCodec );
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
