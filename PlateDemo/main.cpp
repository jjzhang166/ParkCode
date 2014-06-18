#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include "../Common/commonfunction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec *pCodec = CCommonFunction::GetTextCodec( );// QTextCodec::codecForName( "GB18030" );    //System//获取系统编码

    //QTextCodec::setCodecForLocale( pCodec );
    //QTextCodec::setCodecForCStrings( pCodec );
    //QTextCodec::setCodecForTr( pCodec );

    MainWindow w;
    w.show();

    return a.exec();
}
