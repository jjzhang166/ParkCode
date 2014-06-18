#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qRegisterMetaType<ItemType>("ItemType");

    QTextCodec *tmpCodec = CMySqlDatabase::GetTextCodec( );
    QTextCodec::setCodecForLocale( tmpCodec );

    MainWindow w;
    w.show();
    
    return a.exec();
}
