#include "../CommonLibrary/qmyapplication.h"
#include "mainwindow.h"

QPlatformGlobal* g_pPlatformGlobal = NULL;

int main(int argc, char *argv[])
{
    QMyApplication a(argc, argv);

    g_pPlatformGlobal = QPlatformGlobal::GetSingleton( );
    g_pPlatformGlobal->ParseMainArgs( MyEnums::PlatformCentralDataReceiver, argc, argv );
    g_pPlatformGlobal->InitializeApplication( MyEnums::PlatformCentralDataReceiver );

    MainWindow w;
    w.DisplayMainArgs( g_pPlatformGlobal->GetTcpListenerPortMaxConnectionList( ) );
    w.DisplayMainArgs( g_pPlatformGlobal->GetUdpListenerPortList( ) );
    w.DisplayMainArgs( g_pPlatformGlobal->GetUdpBroadcastListenerPortList( ) );
    w.DisplayMainArgs( g_pPlatformGlobal->GetUdpMulticastListenerIpPortList( ) );
    w.show();
    
    return a.exec();
}
