#include <QtGui/QApplication>
#include <QTextCodec>
#include <QtPlugin>
#include "mainwindow.h"
#include "Common/commonfunction.h"

//Q_IMPORT_PLUGIN(qjpeg)
//Q_IMPORT_PLUGIN(qgif)
//Q_IMPORT_PLUGIN(qkrcodecs)

/*
  存储过程采用一个调用入口方式
  SpEntance( in xmlParam, out xmlInfo )
<Params>
<Host>127.0.0.1</Host>
<User></User>
<-- Call SP -->
<SubSP>Test</SubSP> switch call sub SP
<Operation>Insert Update Delete</Operation> switch
<Data>
<p0>...</p0>
</Data>
</Params>
*/


int main(int argc, char *argv[])
{
    CMySqlDatabase::MySQLLibraryInit( 0, NULL );

    QApplication a(argc, argv);

    // MBCS(DBCS) UCS
    // ASCI ANSI ISO14060 GB2313 GBK GB18030 GB13000 BIG5 CJK
    //GBK、GB2312 GB18030－－Unicode－－UTF8
    //UTF8－－Unicode－－GBK、GB2312 GB18030
    QTextCodec *pCodec = CCommonFunction::GetTextCodec( );// QTextCodec::codecForName( "GB18030" );    //System//获取系统编码

    QTextCodec::setCodecForLocale( pCodec );
    QTextCodec::setCodecForCStrings( pCodec );
    QTextCodec::setCodecForTr( pCodec );

    //CCommonFunction::GetSyncPass( ).lock( );

   CCommonFunction::StartupSplash( );
    MainWindow w;
    w.show();
    CCommonFunction::CleanupSplash( &w );

    //CMySqlDatabase::MySQLLibrayEnd( );

    return a.exec( );
}
