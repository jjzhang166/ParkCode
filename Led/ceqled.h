#ifndef CEQLED_H
#define CEQLED_H

#include <QThread>
#include "cledevent.h"
#include <windows.h>
#include "EQ2008_Dll.h"

class CEqLed : public QThread
{
    Q_OBJECT
public:

    static CEqLed* CreateInstance( );
    void PostText( QString& strText );

protected:
    void run( );
    void customEvent( QEvent* e );

private:
    explicit CEqLed(QObject *parent = 0);

    inline void PostEvent( CLedEvent* pEvent );
    void GetFunctionPointer( );
    void ProcessPublishTextEvent( CLedEvent* pEvent );

private:
    static CEqLed* pThreadInstance;
    HMODULE hDllMod;

    typedef int ( WINAPI* User_AddProgram )( int CardNum, BOOL bWaitToEnd, int iPlayTime );

    //添加图文区
    typedef int  ( WINAPI* User_AddBmpZone )( int CardNum,User_Bmp *pBmp,int iProgramIndex);
    typedef BOOL ( WINAPI* User_AddBmp )( int CardNum,int iBmpPartNum,HBITMAP hBitmap,User_MoveSet* pMoveSet,int iProgramIndex);
    typedef BOOL ( WINAPI* User_AddBmpFile )( int CardNum,int iBmpPartNum,char *strFileName,User_MoveSet* pMoveSet,int iProgramIndex);

    //添加文本区
    typedef int ( WINAPI* User_AddText )( int CardNum,User_Text *pText,int iProgramIndex);

    //添加RTF区
    typedef int ( WINAPI* User_AddRTF )( int CardNum,User_RTF *pRTF,int iProgramIndex);

    //添加单行文本区
    typedef int ( WINAPI* User_AddSingleText )( int CardNum,User_SingleText *pSingleText,int iProgramIndex);

    //添加时间区
    typedef int ( WINAPI* User_AddTime )( int CardNum,User_DateTime *pDateTime,int iProgramIndex);

    //添加计时区
    typedef int ( WINAPI* User_AddTimeCount )( int CardNum,User_Timer *pTimeCount,int iProgramIndex);

    //添加温度区
    typedef int ( WINAPI* User_AddTemperature )( int CardNum,User_Temperature *pTemperature,int iProgramIndex);

    //删除节目
    typedef BOOL ( WINAPI* User_DelProgram )( int CardNum,int iProgramIndex);

    //删除所有节目
    typedef BOOL ( WINAPI* User_DelAllProgram )( int CardNum);

    //发送数据
    typedef BOOL ( WINAPI* User_SendToScreen )( int CardNum);

    //发送节目文件和索引文件
    typedef BOOL ( WINAPI* User_SendFileToScreen )( int CardNum,char pSendPath[MAX_PATH],char pIndexPath[MAX_PATH]);

    typedef BOOL ( WINAPI* User_CloseScreen )( int CardNum);

    //开机
    typedef BOOL ( WINAPI* User_OpenScreen )( int CardNum);

    //校正板卡的时间
    typedef BOOL ( WINAPI* User_AdjustTime )( int CardNum);

    //实时发送数据
    typedef BOOL ( WINAPI* User_RealtimeConnect )( int CardNum);	 //建立连接
    typedef BOOL ( WINAPI* User_RealtimeSendData )( int CardNum,int x,int y,int iWidth,int iHeight,HBITMAP hBitmap);	 //发送数据
    typedef BOOL ( WINAPI* User_RealtimeDisConnect )( int CardNum); //断开连接

    typedef BOOL ( WINAPI* User_RealtimeSendBmpData )( int CardNum,int x,int y,int iWidth,int iHeight,char *strFileName);	 //发送数据

    typedef BOOL ( WINAPI* User_ImportIniFile )( char*	pPath,int iLength); //导入ini配置文件

    //亮度调节
    typedef BOOL ( WINAPI* User_SetScreenLight )( int CardNum,int iLightDegreen);

    User_AddProgram MyUser_AddProgram;
    User_AddBmpZone MyUser_AddBmpZone;
    User_AddBmp MyUser_AddBmp;
    User_AddBmpFile MyUser_AddBmpFile;
    User_AddText MyUser_AddText;
    User_AddRTF MyUser_AddRTF;
    User_AddSingleText MyUser_AddSingleText;
    User_AddTime MyUser_AddTime;
    User_AddTimeCount MyUser_AddTimeCount;
    User_AddTemperature MyUser_AddTemperature;
    User_DelProgram MyUser_DelProgram;
    User_DelAllProgram MyUser_DelAllProgram;
    User_SendToScreen MyUser_SendToScreen;
    User_SendFileToScreen MyUser_SendFileToScreen;
    User_CloseScreen MyUser_CloseScreen;
    User_OpenScreen MyUser_OpenScreen;
    User_AdjustTime MyUser_AdjustTime;
    User_RealtimeConnect MyUser_RealtimeConnect;
    User_RealtimeSendData MyUser_RealtimeSendData;
    User_RealtimeDisConnect MyUser_RealtimeDisConnect;
    User_RealtimeSendBmpData MyUser_RealtimeSendBmpData;
    User_ImportIniFile MyUser_ImportIniFile;
    User_SetScreenLight MyUser_SetScreenLight;
    
signals:
    
public slots:
    
};

#endif // CEQLED_H
