#include "QhkIPCThread.h"
#include <QApplication>

//DDOS / Distributed Denial of Service
// Flood SYN ACK UPD TCP Connection Script ICMP PING
// 僵尸主机(被控制的HOST)==》提供服务的HOST 造成网络阻塞 资源耗尽等

// ARM / Keil / uVision MDK-ARM / ( C51 C166 C251 ARM etc. )
// TI CCS Code Composer Studio 是用于 TI DSP、微处理器和应用处理器的集成开发环境 / 基于Eclipse
// VxWorks Tornado
// WinCE / Windows / Windows Phone
// BSP Board Surport Packet

// 医学影像信息系统简称PACS(Picture Archiving and Communication Systems)，
// 与临床信息系统（Clinical Information System, CIS）、
// 放射学信息系统(Radiology Information System, RIS)、
// 医院信息系统(Hospital Information System, HIS)、
// 实验室信息系统（Laboratory Information System, LIS）同属医院信息系统。
// DICOM 协议 Digital Imaging and Communications in Medicine ，医学数字成像和通信标准

// TMN Telecomunictions Management Networking
// BOSS Business Operation Surport System
// 计费及结算系统 营业、账务系统 客户服务系统 决策支持系统
// BSS OSS
// OSS包含用于运行和监控网络的所有系统，如报告或计费系统。
// BSS系统的设计目标包括客户关系管理（CRM）、业务供应链管理（SCM），经营决策支持系统（DSS）

// SCADA (Supervisory Control And Data Acquisition) 电力、冶金、石油、化工等领域

// Enterprise->ERP

// Bank->IOS (Integrated Operation System)

// Super computer 超级计算机是计算机中功能最强、运算速度最快、存储容量最大的一类计算机，多用于国家高科技领域和尖端技术研究
// Mainframe computer 大型机 金融 电信 / COBOL( COmmon Business Oriented Language )
// Minicomputer 小型机
// Microcomputer 微型机 PC

// SOA EDA MDA POA CEP EB ESB
// Pull/Push Publish/Subscription Store/Forward Request/Response Signal/Slot

QIPCThread* QHkIPCThread::pThreadInstance = NULL;

void CALLBACK ExceptionCallback( DWORD dwType,
                                 LONG lUserID,
                                 LONG lHandle,
                                 void* pUser )
{
    if ( NULL == pUser ) {
        return;
    }

    QHkIPCThread* pThread = ( QHkIPCThread* ) pUser;
    pThread->SendNotify( dwType, lUserID, lHandle );
}

QHkIPCThread::QHkIPCThread(QObject *parent) :
    QIPCThread(parent)
{
    bStarted = false;
    pCodec = CCommonFunction::GetTextCodec( );
}

void QHkIPCThread::SendNotify( DWORD dwType, LONG lUserID, LONG lHandle )
{
    Q_UNUSED( lUserID )
    Q_UNUSED( lHandle )

    QString strText;

    switch ( dwType ) {
    case EXCEPTION_EXCHANGE :
        strText = "用户交互时异常（注册心跳超时，心跳间隔为2分钟）";
        break;

    case EXCEPTION_AUDIOEXCHANGE :
        strText = "语音对讲异常";
        break;

    case EXCEPTION_ALARM :
        strText = "报警异常";
        break;

    case EXCEPTION_PREVIEW :
        strText = "网络预览异常";
        break;

    case EXCEPTION_SERIAL :
        strText = "透明通道异常";
        break;

    case EXCEPTION_RECONNECT :
        strText = "预览时重连";
        break;

    case EXCEPTION_ALARMRECONNECT :
        strText = "报警时重连";
        break;

    case EXCEPTION_SERIALRECONNECT :
        strText = "透明通道重连";
        break;

    case SERIAL_RECONNECTSUCCESS :
        strText = "透明通道重连成功";
        break;

    case EXCEPTION_PLAYBACK :
        strText = "回放异常";
        break;

    case EXCEPTION_DISKFMT :
        strText = "硬盘格式化";
        break;

    case EXCEPTION_PASSIVEDECODE :
        strText = "被动解码异常";
        break;

    case EXCEPTION_EMAILTEST :
        strText = "邮件测试异常";
        break;

    case EXCEPTION_BACKUP :
        strText = "备份异常";
        break;

    case PREVIEW_RECONNECTSUCCESS :
        strText = "预览时重连成功";
        break;

    case ALARM_RECONNECTSUCCESS :
        strText = "报警时重连成功";
        break;

    case RESUME_EXCHANGE :
        strText = "用户交互恢复";
        break;

    case NETWORK_FLOWTEST_EXCEPTION :
        strText = "网络流量检测异常";
        break;

    case EXCEPTION_PICPREVIEWRECONNECT :
        strText = "图片预览重连";
        break;

    case PICPREVIEW_RECONNECTSUCCESS :
        strText = "图片预览重连成功";
        break;

   case EXCEPTION_PICPREVIEW :
        strText = "图片预览异常";
        break;
    }

    EmitMsg( strText, Q_FUNC_INFO );
}

void QHkIPCThread::PostIPCEvent( QIPCEvent::IPCEventType evtType )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    qApp->postEvent( this, pEvent );
}

void QHkIPCThread::PostIPCEvent( QIPCEvent::IPCEventType evtType,
                               QIPCEvent::EventParam &uParam )
{
    QIPCEvent* pEvent = QIPCEvent::GetInstance( evtType );

    pEvent->SetEventParam( uParam );
    qApp->postEvent( this, pEvent );
}

void QHkIPCThread::PostIPCStartupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCStartup );
}

void QHkIPCThread::PostIPCSetConnectTimeoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetConnectTimeout, uParam );
}

void QHkIPCThread::PostIPCSetReconnectTimeEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCSetReconnectTime, uParam );
}

void QHkIPCThread::PostIPCLoginEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogin, uParam );
}

void QHkIPCThread::PostIPCCaptureJPGEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCCaptureJPG, uParam );
}

void QHkIPCThread::PostIPCStartRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStartRealPlay, uParam );
}

void QHkIPCThread::PostIPCStopRealPlayEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCStopRealPlay, uParam );
}

void QHkIPCThread::PostIPCLogoutEvent( QIPCEvent::EventParam& uParam )
{
    PostIPCEvent( QIPCEvent::IPCLogout, uParam );
}

void QHkIPCThread::PostIPCCleanupEvent( )
{
    PostIPCEvent( QIPCEvent::IPCCleanup );
}

QIPCThread* QHkIPCThread::GetInstance( )
{
    if ( NULL == pThreadInstance ) {
        QIPCThread* pThread = new QHkIPCThread( );

        pThread->InitializeThread( );
        pThread->start( );
        pThread->moveToThread( pThread );

        pThreadInstance = pThread;
    }

    return pThreadInstance;
}

void QHkIPCThread::InitializeThread( )
{
    bool bRet = connect( this, SIGNAL( started( ) ),
                         this, SLOT( HandleStarted( ) ) );
    bRet = connect( this, SIGNAL( finished( ) ),
                             this, SLOT( HandleFinished( ) ) );
}

void QHkIPCThread::HandleStarted( )
{
}

void QHkIPCThread::HandleFinished( )
{
}

void QHkIPCThread::run( )
{
    exec( );
}

void QHkIPCThread::CapturePreviewImage( HWND hPlayWnd, QString& strFileName )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    QByteArray byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );

    LONG lPlayHandle = GetPlayHandle( hPlayWnd );
    if ( -1 == lPlayHandle ) {
        return;
    }

    BOOL bRet = NET_DVR_CapturePicture( lPlayHandle, pFile );
    bRet = TRUE;
}

void QHkIPCThread::CaptureDeviceImage( QString& strIP, QString& strFileName, HWND hPlayWnd )
{
    Q_UNUSED( hPlayWnd )
    //CProcessData::CaptureSenseImage
    QByteArray byData = pCodec->fromUnicode( strIP );
    byData.append( char( 0 ) );
    char* pIP = byData.data( );
    LONG lUserID = GetUserID( pIP );

    byData = pCodec->fromUnicode( strFileName );
    byData.append( char( 0 ) );
    char* pFile = byData.data( );

    if ( -1 == lUserID ) {
        return;
    }

    BOOL bRet = FALSE;
    NET_DVR_JPEGPARA sJpgData = { 0 };

    sJpgData.wPicSize = 0xff;
    sJpgData.wPicQuality = 0;

    bRet = NET_DVR_CaptureJPEGPicture( lUserID, 1, &sJpgData, pFile );
}

void QHkIPCThread::GetErrorMessage( )
{
    char* pMsg = NET_DVR_GetErrorMsg( );
    QString strText = pMsg;
    EmitMsg( strText, Q_FUNC_INFO );
}

void QHkIPCThread::EmitMsg(QString strMsg, QString strFunName)
{
    emit NotifyMessage( strMsg );
    qDebug( ) << strMsg << ":" << strFunName << endl;
}

void QHkIPCThread::ProcessIPCStartupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    if( bStarted ) {
        EmitMsg( "已经初始化了。", Q_FUNC_INFO );
        return;
    }

    bStarted = true;

    BOOL bRet = NET_DVR_Init( );
    if ( !bRet ) {
        GetErrorMessage( );
    }

    // Lookup SDK info log
    //bRet = NET_DVR_SetLogToFile( 3 );

    bRet = NET_DVR_SetExceptionCallBack_V30( 0, NULL, ExceptionCallback, this );
    if ( !bRet ) {
        GetErrorMessage( );
    }
}

void QHkIPCThread::ProcessIPCSetConnectTimeoutEvent( QIPCEvent* pEvent )
{
    // 300,75000 // Reserved
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );

    BOOL bRet = NET_DVR_SetConnectTime(
                uParam.EventConnectTimeout.dwWaitTime,
                uParam.EventConnectTimeout.dwTryTimes );
    if ( !bRet ) {
        GetErrorMessage( );
    }
}

void QHkIPCThread::ProcessIPCSetReconnectTimeEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );

    BOOL bRet = NET_DVR_SetReconnect(
                uParam.EventReconnectTimeout.dwInterval,
                uParam.EventReconnectTimeout.bEnableRecon );
    if ( !bRet ) {
        GetErrorMessage( );
    }
}

void QHkIPCThread::SetUserID( char *pIP, LONG lUserID )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.insert( pIP, lUserID );
}

void QHkIPCThread::SetPlayHandle( HWND hPlayWnd, LONG lPlayHandle )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.insert( hPlayWnd, lPlayHandle );
}

LONG QHkIPCThread::GetUserID( char *pIP )
{
    LONG lUserID = -1;

    if ( NULL != pIP ) {
        lUserID = hashIP_UserHandle.value( pIP, -1 );
    }

    return lUserID;
}

void QHkIPCThread::RemoveUserID( char *pIP )
{
    if ( NULL == pIP ) {
        return;
    }

    hashIP_UserHandle.remove( pIP );
}

LONG QHkIPCThread::GetPlayHandle( HWND hPlayWnd )
{
    LONG lPlayHandle = -1;

    if ( INVALID_HANDLE_VALUE != hPlayWnd ) {
        lPlayHandle = hashWnd_PlayHandle.value( hPlayWnd, -1 );
    }

    return lPlayHandle;
}

void QHkIPCThread::RemovePlayHandle( HWND hPlayWnd )
{
    if ( INVALID_HANDLE_VALUE == hPlayWnd ) {
        return;
    }

    hashWnd_PlayHandle.remove( hPlayWnd );
}

void QHkIPCThread::ProcessIPCLoginEvent( QIPCEvent* pEvent )
{
    NET_DVR_DEVICEINFO_V30 sDevInfo;
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventLogin.cIP );
    char* pIP = uParam.EventLogin.cIP;

    if ( -1 != lUserID ) {
        EmitMsg( QString( "已经登录【%1】." ).arg( pIP ), Q_FUNC_INFO );
        return;
    }

    // Login once, play multiple
    lUserID = NET_DVR_Login_V30( pIP,
                                 uParam.EventLogin.wPort,
                                 uParam.EventLogin.cUser,
                                 uParam.EventLogin.cPwd,
                                 &sDevInfo );

   if ( -1 == lUserID ) {
        GetErrorMessage( );
    } else {
        SetUserID( pIP, lUserID );
    }
}

void QHkIPCThread::ProcessIPCCaptureJPGEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventCaptureJPG.cIP );
    char* pFile = uParam.EventCaptureJPG.cFile;

    if ( -1 == lUserID ) {
        EmitMsg( "未登录.", Q_FUNC_INFO );
        return;
    }

    if ( NULL == pFile ) {
        EmitMsg( "文件未指定.", Q_FUNC_INFO );
        return;
    }

    BOOL bRet = FALSE;
    NET_DVR_JPEGPARA sJpgData = { 0 };

    sJpgData.wPicSize = 0xff;
    sJpgData.wPicQuality = 0;

    bRet = NET_DVR_CaptureJPEGPicture( lUserID, 1, &sJpgData, pFile );
    if ( !bRet ) {
        GetErrorMessage( );
        return;
    }

    QString strFile = pFile;

    emit CapturedJPGImage( uParam.EventCaptureJPG.nChannel, strFile ); // Send to UI
}

void QHkIPCThread::ProcessIPCStartRealPlayEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    LONG lUserID = GetUserID( uParam.EventStartRealPlay.cIP );
    bool bMainStream = uParam.EventStartRealPlay.bMainStream;

    if ( - 1 == lUserID ) {
        EmitMsg( "未登录.", Q_FUNC_INFO );
        return;
    }

    HWND hPlayWnd = uParam.EventStartRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );

    if ( -1 != lPlayHandle ) {
        EmitMsg( "窗口正在播放.", Q_FUNC_INFO );
        return;
    }

    NET_DVR_CLIENTINFO sClientInfo = { 0 };
    sClientInfo.lChannel = 1;
    sClientInfo.lLinkMode  = bMainStream ? 0x00000000 : 0x80000000;
    sClientInfo.hPlayWnd = hPlayWnd;

    lPlayHandle = NET_DVR_RealPlay_V30( lUserID, &sClientInfo, NULL );

    if ( -1 == lPlayHandle ) {
        GetErrorMessage( );
    } else {
        SetPlayHandle( hPlayWnd, lPlayHandle );
    }
}

void QHkIPCThread::ProcessIPCStopRealPlayEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    HWND hPlayWnd = uParam.EventStopRealPlay.hPlayWnd;
    LONG lPlayHandle = GetPlayHandle( hPlayWnd );

    if ( - 1 == lPlayHandle ) {
        EmitMsg( "未播放.", Q_FUNC_INFO );
        return;
    }

    BOOL bRet = NET_DVR_StopRealPlay( lPlayHandle );
    if ( !bRet ) {
        GetErrorMessage( );
        return;
    }

    RemovePlayHandle( hPlayWnd );
}

void QHkIPCThread::ProcessIPCLogoutEvent( QIPCEvent* pEvent )
{
    QIPCEvent::EventParam& uParam = pEvent->GetEventParam( );
    char* pIP = uParam.EventLogout.cIP;
    LONG lUserID = GetUserID( pIP );

    if ( - 1 == lUserID ) {
        EmitMsg( "未登录.", Q_FUNC_INFO );
        return;
    }

    BOOL bRet = NET_DVR_Logout( lUserID );
    if ( !bRet ) {
        GetErrorMessage( );
        return;
    }

    RemoveUserID( pIP );
}

void QHkIPCThread::ClearHash( )
{
    hashIP_UserHandle.clear( );
    hashWnd_PlayHandle.clear( );
}

void QHkIPCThread::ProcessIPCCleanupEvent( QIPCEvent* pEvent )
{
    Q_UNUSED( pEvent )

    BOOL bRet = NET_DVR_Cleanup( );
    if ( !bRet ) {
        GetErrorMessage( );
    }

    ClearHash( );
    bStarted = false;
}

void QHkIPCThread::customEvent( QEvent* event )
{
    QIPCEvent* pEvent = ( QIPCEvent* ) event;
    QIPCEvent::IPCEventType evtType = ( QIPCEvent::IPCEventType ) pEvent->type( );

    switch ( evtType ) {
    case QIPCEvent::IPCStartup :
        ProcessIPCStartupEvent( pEvent );
        break;

    case QIPCEvent::IPCSetConnectTimeout :
        ProcessIPCSetConnectTimeoutEvent( pEvent );
        break;

    case QIPCEvent::IPCSetReconnectTime :
        ProcessIPCSetReconnectTimeEvent( pEvent );
        break;

    case QIPCEvent::IPCLogin :
        ProcessIPCLoginEvent( pEvent );
        break;

    case QIPCEvent::IPCCaptureJPG :
        ProcessIPCCaptureJPGEvent( pEvent );
        break;

    case QIPCEvent::IPCStartRealPlay :
        ProcessIPCStartRealPlayEvent( pEvent );
        break;

    case QIPCEvent::IPCStopRealPlay :
        ProcessIPCStopRealPlayEvent( pEvent );
        break;

    case QIPCEvent::IPCLogout :
        ProcessIPCLogoutEvent( pEvent );
        break;

    case QIPCEvent::IPCCleanup :
        ProcessIPCCleanupEvent( pEvent );
        break;

    default :
        break;
    }
}
