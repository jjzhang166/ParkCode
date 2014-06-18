#include "mainwindow.h"
#include <QApplication>

// DVR,DVS,NVR,NVS,IVS
// ONVIF PSIA HDCCTV
// OpenAPI
// ONF SDN OpenFlow( APP--SDN Controller--Infrastructure Switch&Router ) Frenetic(Language) NOX Onix FlowVisor
// SDDC
// Open Platform--->Open API---> HTTP API--->(Like) Restful API -->XML JSON etc.

int main(int argc, char *argv[])
{
    qsrand( 1 );
    QTextCodec* pCodec = CMainConfigurator::GetConfigurator( )->GetTextCodec( );
    QTextCodec::setCodecForLocale( pCodec );

    DatabaseController::MySQLLibraryInit( 0, NULL );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DatabaseController::MySQLLibraryEnd( );
    
    return a.exec();
}
