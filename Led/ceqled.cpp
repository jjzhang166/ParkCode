#include "ceqled.h"
#include <QApplication>

#define EQ_LED "EQ2008_Dll.dll"

CEqLed* CEqLed::pThreadInstance = NULL;

CEqLed::CEqLed(QObject *parent) :
    QThread(parent)
{
    GetFunctionPointer( );
}

CEqLed* CEqLed::CreateInstance( )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new CEqLed( );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void CEqLed::GetFunctionPointer( )
{
    MyUser_AddProgram = NULL;
    MyUser_AddBmpZone = NULL;
    MyUser_AddBmp = NULL;
    MyUser_AddBmpFile = NULL;
    MyUser_AddText = NULL;
    MyUser_AddRTF = NULL;
    MyUser_AddSingleText = NULL;
    MyUser_AddTime = NULL;
    MyUser_AddTimeCount = NULL;
    MyUser_AddTemperature = NULL;
    MyUser_DelProgram = NULL;
    MyUser_DelAllProgram = NULL;
    MyUser_SendToScreen = NULL;
    MyUser_SendFileToScreen = NULL;
    MyUser_CloseScreen = NULL;
    MyUser_OpenScreen = NULL;
    MyUser_AdjustTime = NULL;
    MyUser_RealtimeConnect = NULL;
    MyUser_RealtimeSendData = NULL;
    MyUser_RealtimeDisConnect = NULL;
    MyUser_RealtimeSendBmpData = NULL;
    MyUser_ImportIniFile = NULL;
    MyUser_SetScreenLight = NULL;

    QString strPath = qApp->applicationDirPath( ) + "/" + EQ_LED;
    WCHAR* pPath = ( WCHAR* ) strPath.utf16( );

    hDllMod = ::LoadLibrary( pPath );
    if ( NULL == hDllMod ) {
        return;
    }

    MyUser_AddProgram = ( User_AddProgram ) ::GetProcAddress( hDllMod, "User_AddProgram" );
    MyUser_AddBmpZone = ( User_AddBmpZone ) ::GetProcAddress( hDllMod, "User_AddBmpZone" );

    MyUser_AddBmp = ( User_AddBmp ) ::GetProcAddress( hDllMod, "User_AddBmp" );
    MyUser_AddBmpFile = ( User_AddBmpFile ) ::GetProcAddress( hDllMod, "User_AddBmpFile" );
    MyUser_AddText = ( User_AddText ) ::GetProcAddress( hDllMod, "User_AddText" );
    MyUser_AddRTF = ( User_AddRTF ) ::GetProcAddress( hDllMod, "User_AddRTF" );
    MyUser_AddSingleText = ( User_AddSingleText ) ::GetProcAddress( hDllMod, "User_AddSingleText" );
    MyUser_AddTime = ( User_AddTime ) ::GetProcAddress( hDllMod, "User_AddTime" );
    MyUser_AddTimeCount = ( User_AddTimeCount ) ::GetProcAddress( hDllMod, "User_AddTimeCount" );
    MyUser_AddTemperature = ( User_AddTemperature ) ::GetProcAddress( hDllMod, "User_AddTemperature" );
    MyUser_DelProgram = ( User_DelProgram ) ::GetProcAddress( hDllMod, "User_DelProgram" );
    MyUser_DelAllProgram = ( User_DelAllProgram ) ::GetProcAddress( hDllMod, "User_DelAllProgram" );
    MyUser_SendToScreen = ( User_SendToScreen ) ::GetProcAddress( hDllMod, "User_SendToScreen" );
    MyUser_SendFileToScreen = ( User_SendFileToScreen ) ::GetProcAddress( hDllMod, "User_SendFileToScreen" );
    MyUser_CloseScreen = ( User_CloseScreen ) ::GetProcAddress( hDllMod, "User_CloseScreen" );
    MyUser_OpenScreen = ( User_OpenScreen ) ::GetProcAddress( hDllMod, "User_OpenScreen" );
    MyUser_AdjustTime = ( User_AdjustTime ) ::GetProcAddress( hDllMod, "User_AdjustTime" );
    MyUser_RealtimeConnect = ( User_RealtimeConnect ) ::GetProcAddress( hDllMod, "User_RealtimeConnect" );
    MyUser_RealtimeSendData = ( User_RealtimeSendData ) ::GetProcAddress( hDllMod, "User_RealtimeSendData" );
    MyUser_RealtimeDisConnect = ( User_RealtimeDisConnect ) ::GetProcAddress( hDllMod, "User_RealtimeDisConnect" );
    MyUser_RealtimeSendBmpData = ( User_RealtimeSendBmpData ) ::GetProcAddress( hDllMod, "User_RealtimeSendBmpData" );
    MyUser_ImportIniFile = ( User_ImportIniFile ) ::GetProcAddress( hDllMod, "User_ImportIniFile" );
    MyUser_SetScreenLight = ( User_SetScreenLight ) ::GetProcAddress( hDllMod, "User_SetScreenLight" );
}

void CEqLed::PostText( QString &strText )
{
    CLedEvent* pEvent = CLedEvent::CreateLedEvent( CLedEvent::PublishText );

    PostEvent( pEvent );
}

void CEqLed::run( )
{
    exec( );
}

void CEqLed::customEvent( QEvent *e )
{
    CLedEvent* pEvent = ( CLedEvent* ) e;
    CLedEvent::LedEvent eEvent = ( CLedEvent::LedEvent ) e->type( );

    switch( eEvent ) {
    case CLedEvent::PublishText :
        ProcessPublishTextEvent( pEvent );
        break;
    }
}

void CEqLed::PostEvent( CLedEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void CEqLed::ProcessPublishTextEvent( CLedEvent *pEvent )
{

}
