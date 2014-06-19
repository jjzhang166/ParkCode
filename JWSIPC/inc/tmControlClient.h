/***************************************************************************
								tmControlClient.h
                             -------------------
    begin                :  2005.12.21
    copyright            : (C) 2005 by aip
 ***************************************************************************/

/***************************************************************************
 *  该文件为AIP视频服务器客户端配置服务器的接口定义文件					   *
 ***************************************************************************/

#ifndef __TMCONTROLCLIENT_H__
#define __TMCONTROLCLIENT_H__

#ifdef _LIB
	#define TMCC_API
	#define TMCC_CALL
#else
	#ifdef WIN32
		#define TMCC_API	extern "C" __declspec(dllexport) 
		#define TMCC_CALL	__cdecl
	#else
		#define TMCC_API	extern "C"	
		#define TMCC_CALL	
	#endif //WIN32
#endif //_LIB

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tmServerInfo_t	tmServerInfo_t;
typedef struct tmServerInfoEx_t	tmServerInfoEx_t;
typedef struct tmServerCfg_t	tmServerCfg_t;
typedef struct tmDecoderInfo_t	tmDecoderInfo_t;

#define USER_CONTEXT_SIZE		128
/* 连接用户信息结构定义 */
typedef struct tmConnectInfo_t
{
	unsigned int	dwSize;				//该结构的大小，必须填写
	char			pIp[32];			//连接服务器的IP地址
	int				iPort;				//服务器连接的端口
	char			szUser[32];			//登录用户名
	char			szPass[32];			//登录用户口令
	int				iUserLevel;			//登录用户级别，主要用户DVS的一些互斥访问资源
	unsigned char	pUserContext[USER_CONTEXT_SIZE];	//用户自定义数据
}tmConnectInfo_t;

/* 服务器命令包，输入命令以及命令具体内容 */
typedef struct tmCommandInfo_t
{
	unsigned int		dwSize;				//该结构的大小，必须填写为sizeof(tmCommandInfo_t)	
	unsigned int		dwMajorCommand;		//主消息数据命令即数据类型
	unsigned int		dwMinorCommand;		//次消息数据命令即数据类型	
	unsigned short		iChannel;			//通道号，该通道号要根据dwMajorCommand来判断是否有效
	unsigned short		iStream;			//子通道号，该通道号要根据dwMajorCommand来判断是否有效
	void*				pCommandBuffer;		//消息数据缓冲
	int					iCommandBufferLen;	//消息数据缓冲大小
	int					iCommandDataLen;	//消息数据实际大小
	unsigned int		dwResult;			//消息控制返回结果
}tmCommandInfo_t;

/*服务器系统升级进度信息*/
typedef struct tmProgressInfo_t
{
	HANDLE			hTmcc;					//接口控制句柄
	unsigned int	dwModalID;				//模块ID号
	unsigned int	dwModalSize;			//模块数据大小
	unsigned int	dwModalPos;				//数据传输当前位置
}tmProgressInfo_t;

//服务器自动升级配置结构
typedef struct tmUpgradeConfig_t
{
	unsigned int		dwSize;					//本结构大小
	
	int					iListenPort;			//服务器监听端口，设备将主动连接此端口

	int					iServerListCount;		//服务器列表数，当为0时请求网络所有机器升级	
	tmServerInfoEx_t*	pServerInfoList;		//需要升级的设备列表，由服务器信息组成列表
	
	int					iFileType;				//升级的包类型0-升级文件,1-IE升级包,2-内核升级包
	char				szFileName[MAX_PATH];	//升级的文件包，或IE升级目录

	BOOL				bAutoReboot;			//升级完成后自动重启
}tmUpgradeConfig_t;

//服务器自动升级信息结构
typedef struct tmUpgradeInfo_t
{
	unsigned int		dwSize;					//本结构大小
	tmServerInfoEx_t*	pServerInfo;			//设备信息
	unsigned int		dwResultCode;			//模块升级代码,请参考摄像机自动升级输出代码定义说明	
	int					iUpgradeProgress;		//升级进度0-100
}tmUpgradeInfo_t;

//捕获数据结构定义
typedef struct tmAvRenderConfig_t
{
	unsigned int	dwSize;

	//视频
	BOOL			bVideo;				//是否带视频
	int				iWidth;				//视频宽
	int				iHeight;			//视频高
	int				iFrameRate;			//帧率*1000

	//音频
	BOOL			bAudio;				//是否带音频
	unsigned char	byBitsPerSample;	//音频采样位数
	unsigned char	byChannels;			//音频的声道数
	int				iSamplesPerSec;		//音频采样率
}tmAvRenderConfig_t;

//解码数据结构定义
typedef struct tmAvDecoderConfig_t
{
	unsigned int	dwSize;
	
	BOOL			bSingleFrame;		//是否解码单关键帧，FALSE为解码数据流

	//视频
	BOOL			bVideo;				//是否带视频
	unsigned int	dwVideoTag;			//流类型Tag
	unsigned int	dwVideoId;			//流ID
	int				iWidth;				//视频宽
	int				iHeight;			//视频高

	//音频
	BOOL			bAudio;				//是否带音频
	unsigned int	dwAudioTag;			//音频流类型Tag
	unsigned int	dwAudioId;			//音频流ID	
	unsigned char	byBitsPerSample;	//音频采样位数
	unsigned char	byChannels;			//音频的声道数
	int				iSamplesPerSec;		//音频采样率
}tmAvDecoderConfig_t;

//语音对讲数据头
typedef struct tmVoiceHead_t
{
	unsigned int	dwSize;	
	unsigned char	byCompressFormat;	//音频编码格式0-MP2,1-AAC,2-S16LE,3-MULAW/G.711,4-ALAW/G.711,5-G.722,6-G.723,7-G.726,8-G.729
	unsigned char	byTemp;				//保留
	unsigned char	byBitsPerSample;	//音频采样位数
	unsigned char	byChannels;			//音频的声道数
	int				iSamplesPerSec;		//音频采样率
	int				iAudioBitRate;		//音频码流大小
}tmVoiceHead_t;

//捕获数据结构定义
typedef struct tmVoiceData_t
{
	unsigned int	dwSize;				//本结构大小
	unsigned char	byDataType;			//音频数据类型0是头，1是数据包
	unsigned char	byTemp[3];			//保留
	void*			pData;				//音频数据缓冲，没有包头，一包完整数据
	int				iDataSize;			//音频数据缓冲大小
	unsigned int	dwTimeStamp;		//音频包时间大小，毫秒
}tmVoiceData_t;

//数据流头信息
typedef struct tmStreamHeadInfo_t
{
	unsigned int	dwSize;

	//视频
	BOOL			bVideo;				//是否带视频
	unsigned int	dwVideoTag;			//流类型Tag
	unsigned int	dwVideoId;			//流ID
	int				iWidth;				//视频宽
	int				iHeight;			//视频高
	int				iDisplayScale;		//显示比例*1000
	int				iFrameRate;			//帧率*1000
	int				iVideoBitRate;		//此数据流的码流大小
	BOOL			bInterlacer;		//视频是Interlacer

	//音频
	BOOL			bAudio;				//是否采集音频
	unsigned int	dwAudioTag;			//音频流类型Tag
	unsigned int	dwAudioId;			//音频流ID	
	int				iBitsPerSample;		//音频采样位数
	int				iChannels;			//音频的声道数
	int				iSamplesPerSec;		//音频采样率
	int				iAudioBitRate;		//此音频流的码流大小
	unsigned int	dwSampleSize;		//一个音频包包含多少帧
	
}tmStreamHeadInfo_t;

//设备主动登录信息结构定义
typedef struct tmDeviceLoginInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceLoginInfo_t;
//设备主动数据上传信息结构定义
typedef struct tmDeviceStreamInfo_t
{
	unsigned int	dwSize;				//本结构大小
	unsigned int	dwDeviceIp;			//设备地址
	unsigned int	dwFactoryId;		//设备的厂商号
	char			sDeviceId[64];		//设备登录ID号
	char			sDeviceSn[48];		//设备唯一序列号
	unsigned char	byChannel;			//上传的通道
	unsigned char	byStream;			//上传的码流
}tmDeviceStreamInfo_t;
//设备主动语音对讲信息结构定义
typedef struct tmDeviceTalkInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceTalkInfo_t;


//摄像机自动升级输出代码说明定义
#define AUTO_UPGRADE_CODE_REQUEST			0x01//设备请求升级
#define AUTO_UPGRADE_CODE_START				0x02//设备开始升级
#define AUTO_UPGRADE_CODE_SUCCESS			0x03//设备成功升级
#define AUTO_UPGRADE_CODE_STATE				0x04//设备升级中
#define AUTO_UPGRADE_CODE_NETWORKERROR		0x05//设备和服务器网络不通
#define AUTO_UPGRADE_CODE_CANTCONNECT		0x06//设备请求连接时发生错误
#define AUTO_UPGRADE_CODE_WRITEERROR		0x07//设备升级Firmare时发生错误

//初始化类型
#define TMCC_INITTYPE_CONTROL				0x00//初始化成设备控制SDK句柄
#define TMCC_INITTYPE_ENUM					0x01//初始化成枚举SDK句柄
#define TMCC_INITTYPE_UPGRADE				0x02//初始化成升级SDK句柄
#define TMCC_INITTYPE_TALK					0x03//初始化成语音对讲SDK句柄
#define TMCC_INITTYPE_STREAM				0x04//初始化成播放数据流SDK句柄
#define TMCC_INITTYPE_REALSTREAM			0x05//初始化成播放实时数据流SDK句柄
#define TMCC_INITTYPE_LISTEN				0x06//初始化为状态接收和报警接收SDK句柄
#define TMCC_INITTYPE_VIDEORENDER			0x07//初始化为视频显示SDK句柄
#define TMCC_INITTYPE_VOICERENDER			0x08//初始化为语音对讲数据解码SDK句柄
#define TMCC_INITTYPE_LISTENDEVICE			0x09//初始化为主动监听设备上传SDK句柄
#define TMCC_INITTYPE_AVDECODER				0x0A//初始化为音视频解码SDK句柄
#define TMCC_INITTYPE_PLAYREMOTEFILE		0x0B//初始化为播放远程文件SDK句柄
#define TMCC_INITTYPE_RTPSTREAM				0x0C//初始化为播放RTP包的SDK句柄
#define TMCC_INITTYPE_REMOTEPLAY			0x0D//初始化为播放远程文件SDK句柄


/*
 * 接口函数TMCC_PutInStream的参数nData定义
 */
#define PUTIN_STREAMDATA_RESET				0x01
#define PUTIN_STREAMDATA_VIDEO				0x02
#define PUTIN_STREAMDATA_KEYFRAME			0x04

/* 操作回调函数定义 */
//调式回调函数，只有在开发模式下才有效
typedef void (CALLBACK* TMCC_LOG_CALLBACK)( HANDLE hTmCC, unsigned int code, const char* info, void* context );
//连接消息回调函数，通过它可以得到异步方式和断开连接状态
typedef BOOL (CALLBACK* TMCC_CONNECT_CALLBACK)( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult, void *context );
//消息读取回调函数，通过它可以得到服务器消息，同时异步方式的服务器数据获得也是通过该回调
typedef int  (CALLBACK* TMCC_DATAREAD_CALLBACK)( HANDLE hTmcc, tmCommandInfo_t* pCmd, void *context );
//服务器列举回调函数定义
typedef BOOL (CALLBACK* TMCC_ENUMSERVER_CALLBACK)( tmServerInfo_t* pEnum, void *context );
//服务器连接回调函数，通过它可以得到服务器登陆，或者服务器无连接的报警信息
typedef BOOL (CALLBACK* TMCC_SERVERINFO_CALLBACK)( tmCommandInfo_t* pCmd, void *context );
//服务器模块升级进度回调函数
typedef BOOL (CALLBACK* TMCC_PROGRESS_CALLBACK)( tmProgressInfo_t* pInfo, void *context );
//通明通道数据回调函数
typedef int  (CALLBACK* TMCC_SERIALDATA_CALLBACK)( HANDLE hTmCC, char *pRecvDataBuffer, int iBufSize, void* context );
//add by stone 20070930
//连接信息枚举回调定义
typedef int  (CALLBACK* TMCC_ENUMCONNECT_CALLBACK)( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pInfo, int iInfoSize,  void* context );
//服务器自动升级信息输出回调
typedef int  (CALLBACK* TMCC_UPGRADE_CALLBACK)( HANDLE hTmCC, tmUpgradeInfo_t* pInfo, void* context );
//数据流回调
typedef int  (CALLBACK* TMCC_STREAMREAD_CALLBACK)( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *context );
//视频显示回调
typedef void (CALLBACK* TMCC_DDRAW_CALLBACK)( HANDLE hTmCC, HDC hDC, RECT* lpRect, int iRegionNum, void* context );
//解码帧输出回调
typedef int	 (CALLBACK* TMCC_AVFRAME_CALLBACK)( HANDLE hTmCC, tmAvImageInfo_t* pImage, void* context );
//文件下载进度回调
typedef BOOL (CALLBACK* TMCC_DOWNLOADPROGRESS_CALLBACK)( HANDLE hTmCC, tmPlayStateCfg_t* pDownloadState, void *context );
//对讲音频数据输出回调
typedef int  (CALLBACK* TMCC_VOICEDATA_CALLBACK)( HANDLE hTmCC, tmVoiceData_t* pVoiceData, void *context );
//设备主动登录回调，注意hNewTmCC为新生成的句柄
typedef int  (CALLBACK* TMCC_DEVICELOGIN_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceLoginInfo_t* pDeviceLogin, void *context );
//设备主动数据连接回调，注意hNewTmCC为新生成的句柄
typedef int  (CALLBACK* TMCC_DEVICESTREAM_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceStreamInfo_t* pDeviceStream, void *context );
//设备主动语音连接回调，注意hNewTmCC为新生成的句柄
typedef int  (CALLBACK* TMCC_DEVICETALK_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceTalkInfo_t* pDeviceTalk, void *context );
//RTP包输出回调数据流回调
typedef int  (CALLBACK* TMCC_RTPSTREAMREAD_CALLBACK)( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *context );


/*
 *函  数: TMCC_GetVersion 
 *说  明: 获得本客户端库版本信息
 *参  数: pBulid为存放编译序号
 *返回值: 返回版本号，格式如<返回值为10000，则版本V1.0.0.00>
 */
TMCC_API unsigned int TMCC_CALL TMCC_GetVersion( unsigned int* pBulid );

/*
 *函  数: TMCC_RegisterLogCallBack 
 *说  明: 注册调试信息回调函数，只有在开发模式下才有效
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterLogCallBack( TMCC_LOG_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_RegisterServerInfoCallBack 
 *说  明: 注册服务器消息信息回调函数，通过此回调可以得到服务器对管理中心的连接以及报警信息
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterServerInfoCallBack( TMCC_SERVERINFO_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_GetLastError 
 *说  明: 获得当前的错误码
 *参  数: 无
 *返回值: 返回错误码
 */
TMCC_API int TMCC_CALL TMCC_GetLastError();

/////////////////////////////////////////////////////////////////////
///////////////////////////设备基本配置控制接口//////////////////////
/////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_Init 
 *说  明: 初始化并获得一个服务器控制句柄，其它所有接口函数都依赖此句柄访问服务器
 *参  数: dwFlags保留，必须设为0
 *返回值: 成功返回控制句柄，失败返回NULL
 */
TMCC_API HANDLE	TMCC_CALL TMCC_Init( unsigned int dwFlags );

/*
 *函  数: TMCC_Done 
 *说  明: 释放服务器控制句柄相关资源
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_Done( HANDLE hTmCC );

/*
 *函  数: TMCC_RegisterConnectCallBack 
 *说  明: 注册连接信息返回回调函数，异步连接成功通过该回调函数返回，发生错误断开连接也通过该回调
 *参  数: hTmCC为服务器控制句柄，pCallBack为回调函数指针，context为自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterConnectCallBack( HANDLE hTmCC, TMCC_CONNECT_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_RegisterDataReadCallBack 
 *说  明: 注册服务器消息读取回调函数，异步方式通过它获得服务器消息，其它如报警消息也通过它得到
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，pCallBack为回调函数指针，context为自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterDataReadCallBack( HANDLE hTmCC, TMCC_DATAREAD_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_RegisterProgressCallBack 
 *说  明: 注册升级备份信息回调函数，只有在开发升级模式下才有效
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterProgressCallBack( HANDLE hTmCC, TMCC_PROGRESS_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_SetTimeOut 
 *说  明: 设置与服务器通讯操作的超时时间，必须要在TMCC_Connect调用前设置才有效
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，dwTime时间值单位为毫秒系统默认为2000毫秒
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetTimeOut( HANDLE hTmCC, int dwTime );

/*
 *函  数: TMCC_GetTimeOut 
 *说  明: 获得与服务器通讯操作的超时时间，任何时候都能调用
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回时间值，错误返回0
 */
TMCC_API int TMCC_CALL TMCC_GetTimeOut( HANDLE hTmCC );

/*
 *函  数: TMCC_SetAutoReConnect 
 *说  明: 设置发生错误后是否自动重新连接，注意必须要注册连接回调函数，且会根据回调函数返回值判断是否连接
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，bAutoConnect为自动连接标志，系统默认为FALSE
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetAutoReConnect( HANDLE hTmCC, BOOL bAutoConnect );

/*
 *函  数: TMCC_GetAutoReConnect 
 *说  明: 获得发生错误后是否自动重新连接标志，任何时候都能调用
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回自动连接标志，错误返回FALSE
 */
TMCC_API BOOL TMCC_CALL TMCC_GetAutoReConnect( HANDLE hTmCC );

/*
 *函  数: TMCC_IsConnect 
 *说  明: 获得当前是否正常连接服务器，任何时候都能调用
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回连接正常标志，错误返回FALSE
 */
TMCC_API BOOL TMCC_CALL TMCC_IsConnect( HANDLE hTmCC );

/*
 *函  数: TMCC_Connect 
 *说  明: 连接服务器，即登录到服务器，调用该函数成功后必须要调用TMCC_DisConnect才能再一次调用，
		  如果调用一异步方式则连接成功会通过连接回调函数反映，如没注册连接回调函数，异步连接会失败
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，pConnectInfo为用户连接信息，bSync为连接方式<异步或同步>
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_Connect( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo, BOOL bSync );

/*
 *函  数: TMCC_DisConnect 
 *说  明: 断开到服务器的连接
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_DisConnect( HANDLE hTmC );

/*
 *函  数: TMCC_SetConfig
 *说  明: 服务器参数配置，该函数所有配置的参数在服务器重新启后会丢失，除非调用TMCC_SaveConfig明确保存
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄；
 		  pCommandInfo命令消息结构指针，其中包含了所需要的命令，缓冲等
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );

/*
 *函  数: TMCC_GetConfig
 *说  明: 获取服务器参数
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄；
 		  pCommandInfo命令消息结构指针，其中包含了所需要的命令，缓冲等
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );

/*
 *函  数: TMCC_SaveConfig
 *说  明: 保存服务器配置参数，服务器中Flash的察写次数一般有限，建议不要经常调用
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SaveConfig( HANDLE hTmCC );

/*
 *函  数: TMCC_RestoreConfig
 *说  明: 恢复服务器配置参数为系统默认值
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_RestoreConfig( HANDLE hTmCC );

/*
 *函  数: TMCC_Reboot
 *说  明: 重新启动服务器，启动后客户端会自动连接它，重启期间所有设置均无效
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_Reboot( HANDLE hTmCC );

/*
 *函  数: TMCC_ShutDown
 *说  明: 关闭服务器，关闭后与服务器的连接自动断开
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ShutDown( HANDLE hTmCC );

/*
 *函  数: TMCC_UpgradeSystem
 *说  明: 升级服务器系统，升级系统也要操作Flash，所以建议不要经常升级系统，
 		  该函数为阻塞调用，操作期间其它所有操作无效
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，lpszFileName为系统镜像全路径名
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_UpgradeSystem( HANDLE hTmCC, const char *lpszFileName );

/*
 *函  数: TMCC_BackupSystem
 *说  明: 保存服务器系统为镜像文件，该函数为阻塞调用，操作期间其它所有操作无效
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄，lpszFileName为系统镜像全路径名；
 *		  iModal为要备份的模块标志，分别以位表示，从最低为开始 :
		  0位表示备份运行模块，1位表示备份升级的运行模块, 2位表示备份参数模块，3位表示备份PTZ模块，
		  4位表示备份WEB模块，5位表示备份扩展模块
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_BackupSystem( HANDLE hTmCC, const char *lpszFileName, int iModal = 0x3E );

/*
 *函  数: TMCC_EnumServer
 *说  明: 列举网络中的服务器，列举出来的设备仅能作为参考，可能有些不能列举到
 *参  数: pCallBack为回调函数指针；context为调用者设置的上下文指针
 *		  在函数pCallBack中返回TRUE表示继续列举，FALSE为停止列举
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_EnumServer( TMCC_ENUMSERVER_CALLBACK pCallBack, void* context, BOOL bRegisterCallBack = FALSE );

/*
 *函  数: TMCC_RefreshEnumServer
 *说  明: 刷新网络服务器列表
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_RefreshEnumServer();

/*
 *函  数: TMCC_ConfigServer
 *说  明: 配置服务器的地址信息
 *参  数: dwFlags为配置类型，即通过什么方式配置，目前仅支持网络
 *		  pConfig为新的服务器信息
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ConfigServer( tmServerCfg_t* pConfig, unsigned int dwFlags = 0 );

//云台控制
/*
 *函  数: TMCC_PtzGetDecoderList
 *说  明: 获得服务器内置解码器协议列表
 *参  数: pInfo为要填协议的列表，info_num为输入为列表最大个数，输出为当前协议个数
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzGetDecoderList( HANDLE hTmCC, tmDecoderInfo_t pInfo[], int* info_num );

/*
 *函  数: TMCC_PtzOpen
 *说  明: 打开云台控制，要控制服务器云台，必须先打开对应台号
 *参  数: iChannel为云台号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzOpen( HANDLE hTmCC, int iChannel, BOOL bLock = FALSE );

/*
 *函  数: TMCC_PtzClose
 *说  明: 关闭云台控制
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzClose( HANDLE hTmCC );

/*
 *函  数: TMCC_PtzLock
 *说  明: 锁定云台控制，必须先打开对应台号
 *参  数: hTmCC为控制句柄, iChannel为云台号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzLock( HANDLE hTmCC, int iChannel );

/*
 *函  数: TMCC_PtzUnLock
 *说  明: 解锁云台控制
 *参  数: hTmCC为控制句柄, iChannel为云台号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzUnLock( HANDLE hTmCC, int iChannel );

/*
 *函  数: TMCC_PtzControl
 *说  明: 云台控制命令，这些命令得经过选用协议转换后输出，调用此功能必须选用正确解码协议
 *参  数: hTmCC为控制句柄，dwPTZCommand为云台控制命令，dwPTZControl为控制方法0-关闭1-开始，dwSpeed为运动速度
 *		  如果NVS中无正确的对应协议，可以用	TMCC_PtzTrans来由上层软件处理	
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzControl( HANDLE hTmCC, unsigned int dwPTZCommand, unsigned int dwPTZControl, unsigned int dwSpeed );

/*
 *函  数: TMCC_PtzTrans
 *说  明: 为云台控制直接输出，不用内置解码协议转换
 *参  数: hTmCC为控制句柄，pPTZCodeBuf为输出的数据缓冲，iBufSize为数据大小，最大值必须小于128
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzTrans( HANDLE hTmCC, unsigned char *pPTZCodeBuf, int iBufSize );

/*
 *函  数: TMCC_PtzPreset
 *说  明: 云台预置点调用
 *参  数: hTmCC为控制句柄，dwPTZPresetCmd为云台控制命令号，dwPresetIndex为预置点号，dwSpeed为速度
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzPreset( HANDLE hTmCC, unsigned int dwPTZPresetCmd, unsigned int dwPresetIndex, unsigned int dwSpeed );

/*
 *函  数: TMCC_PtzIntegrate
 *说  明: 为云台综合控制，需要云台直接和一体机支持
 *参  数: hTmCC为控制句柄，pParam为控制的具体参数结构指针，iParamSize为结构大小大小，最大值必须小于128
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PtzIntegrate( HANDLE hTmCC, tmPtzParameter_t* pParam, int iParamSize );

//透明通道设置
/*
 *函  数: TMCC_RegisterSerialDataReadCallBack
 *说  明: 注册服务器串口数据获得回调函数
 *参  数: hTmCC为控制句柄, , pCallBack为获取通道的回传数据，context为用户自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterSerialDataReadCallBack( HANDLE hTmCC, TMCC_SERIALDATA_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_SerialOpen
 *说  明: 打开与服务器间的透明通道传输
 *参  数: hTmCC为控制句柄, iSerialPort==0时打开232,==1打开485
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SerialOpen( HANDLE hTmCC, int iSerialPort );

/*
 *函  数: TMCC_SerialSend
 *说  明: 向服务器发送通明数据，这些数据服务器将不作处理直接送出
 *参  数: hTmCC为控制句柄，iChannel为发送的通道号仅485有效
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SerialSend( HANDLE hTmCC, int iChannel, char *pSendBuf, int iBufSize );

/*
 *函  数: TMCC_SerialRecv
 *说  明: 从服务器读取通明数据，这些数据服务器将不作处理直接送出
 *参  数: hTmCC为控制句柄，iChannel为发送的通道号仅485有效
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SerialRecv( HANDLE hTmCC, int iChannel, char *pRecvBuf, int iBufSize );

/*
 *函  数: TMCC_SerialClose
 *说  明: 关闭与服务器的通明传输
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SerialClose( HANDLE hTmCC );

///////////////////////////////////////////////////////////////////////
///////////////////////////////语音对讲////////////////////////////////
///////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_StartVoiceCom
 *说  明: 启动语音对讲
 *参  数: hTmCC为控制句柄，pConnectInfo为语音对象可以为NULL
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartVoiceCom( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo );

/*
 *函  数: TMCC_SetVoiceComClientVolume
 *说  明: 设置客户端语音播放硬件声音大小
 *参  数: hTmCC为控制句柄，iVolume为声音值-10000~0,-10000最小,0最大
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolume( HANDLE hTmCC, int iVolume );

/*
 *函  数: TMCC_SetVoiceComClientVolumeZoom
 *说  明: 设置客户端语音播放软件放大值
 *参  数: hTmCC为控制句柄，fpmPerNum为声音放大值0 < fpmPerNum < 10.0
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolumeZoom( HANDLE hTmCC, float fpmPerNum );

/*
 *函  数: TMCC_SetVoiceComClientMicZoom
 *说  明: 设置客户端语音采集，即麦克风声音大小
 *参  数: hTmCC为控制句柄，fpmPerNum为声音放大值0 < fpmPerNum < 10.0
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientMicZoom( HANDLE hTmCC, float fpmPerNum );

/*
 *函  数: TMCC_StopVoiceCom
 *说  明: 关闭与服务器的语音队讲
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopVoiceCom( HANDLE hTmCC );

/*
 *函  数: TMCC_RegisterVoiceDataCallBack 
 *说  明: 注册语音对讲数据获得回调，通过此回调可以得到服务器的语音数据
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterVoiceDataCallBack( HANDLE hTmCC, TMCC_VOICEDATA_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_PutInVoiceData
 *说  明: 输入语音对讲数据
 *参  数: hTmCC为控制句柄，pVoiceData为音频数据结构
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PutInVoiceData( HANDLE hTmCC, tmVoiceData_t* pVoiceData );

/*
 *函  数: TMCC_OpenVoice
 *说  明: 打开语音对讲数据解码和语音捕获
 *参  数: hTmCC为控制句柄，pVoiceHead为音频数据头结构
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_OpenVoice( HANDLE hTmCC, tmVoiceHead_t* pVoiceInHead, tmVoiceHead_t* pVoiceOutHead );

/*
 *函  数: TMCC_CloseVoice
 *说  明: 关闭语音对讲数据解码和语音捕获
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CloseVoice( HANDLE hTmCC );


//服务器状态
/*
 *函  数: TMCC_GetServerWorkState
 *说  明: 得到服务器当前工作状态
 *参  数: hTmCC为控制句柄，lpWorkStatew为存放服务器状态信息的结构指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetServerWorkState( HANDLE hTmCC, tmWorkState_t* lpWorkState );

/*
 *函  数: TMCC_ConfigServerEx
 *说  明: 配置服务器的地址信息，1.0.0.09添加
 *参  数: dwFlags为配置类型，即通过什么方式配置，目前仅支持网络
 *		  pConfig为新的服务器信息
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ConfigServerEx( HANDLE hTmCC, tmServerExCfg_t* pConfig, unsigned int dwFlags );

//////////////////////////////////////////////////////////////////////////
//2007/07/16 franxkia 新加

//设置播放的wave文件
/*
 *函  数: TMCC_SetPlayWaveFile
 *说  明: PC播放WAVE文件,通过语音对讲通道传送到DVS,DVS输出
 *参  数: hTmCC为控制句柄，pFileName为文件名全路径,bPlayNum为要播放的次数
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetPlayWaveFile( HANDLE hTmCC, char *pFileName, unsigned char bCirclePlay );

/*
 *函  数: TMCC_SaveDefaultConfig
 *说  明: 保存服务器默认配置参数，服务器中Flash的察写次数一般有限，建议不要经常调用
 *参  数: hTmCC为TMCC_Init返回的服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SaveDefaultConfig( HANDLE hTmCC );

//////////////////////////////////////////////////////////////////////////////
///////////视频解码器直接操作函数接口定义 add by stone 20070930///////////////
//////////////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_SetConnectInfo
 *说  明: 配置服务器的连接信息，1.0.0.20添加，如果是循环连接则加入，如果是非循环那就处理
 *参  数: pConfig为连接信息, iChannel为通道号(或窗口号)，size为pConfig的缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );

/*
 *函  数: TMCC_GetConnectInfo
 *说  明: 得到当前的连接信息，1.0.0.20添加
 *参  数: pConfig为连接信息, iChannel为通道号(或窗口号)，size为pConfig的缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );

/*
 *函  数: TMCC_ClearConnectInfo
 *说  明: 清除当前的连接信息，如果是循环连接则清除指定循环序号，1.0.0.20添加
 *参  数: iChannel为通道号(或窗口号)，iIndex为为循环的序号为-1则为清除所有
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ClearConnectInfo( HANDLE hTmCC, int iChannel, int iIndex );

/*
 *函  数: TMCC_GetEnumConnectInfo
 *说  明: 枚举服务器的连接信息，通过回调输出，回调中可以反映通道号，是否是循环连接等信息，1.0.0.20添加
 *参  数: iChannel为通道号(或窗口号)，pCallBack为回调函数指针，context为用户定义的指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_EnumConnectInfo( HANDLE hTmCC, int iChannel, TMCC_ENUMCONNECT_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_SetWindowInfo
 *说  明: 设置显示的窗口信息，1.0.0.20添加
 *参  数: iChannel为通道号(或窗口号)，pConfig为窗口信息指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );

/*
 *函  数: TMCC_GetWindowInfo
 *说  明: 读取显示的窗口信息，1.0.0.20添加
 *参  数: iChannel为通道号(或窗口号)，pConfig为窗口信息指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );

/*
 *函  数: TMCC_SetDisplayInfo
 *说  明: 设置解码器的显示信息，如单屏放大等,1.0.0.20添加
 *参  数: pConfig为显示信息指针，size为数据缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );

/*
 *函  数: TMCC_GetDisplayInfo
 *说  明: 读取解码器的显示信息，如单屏放大等,1.0.0.20添加
 *参  数: pConfig为显示信息指针，size为数据缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );

/*
 *函  数: TMCC_SetLockInfo
 *说  明: 设置通道连接锁定信息，如单是否循环切换等, 注意循切的时间是在设置连接信息时配置,1.0.0.20添加
 *参  数: iChannel为通道号,pConfig为显示信息指针，size为数据缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );

/*
 *函  数: TMCC_GetLockInfo
 *说  明: 读取通道连接锁定信息，如单是否循环切换等, 注意循切的时间是在设置连接信息时配置,1.0.0.20添加
 *参  数: iChannel为通道号,pConfig为显示信息指针，size为数据缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );

/*
 *函  数: TMCC_StartConnect
 *说  明: 使解码器打开连接,1.0.0.20添加
 *参  数: iChannel为通道号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartConnect( HANDLE hTmCC, int iChannel );

/*
 *函  数: TMCC_StopConnect
 *说  明: 使解码器关闭连接,1.0.0.20添加
 *参  数: iChannel为通道号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopConnect( HANDLE hTmCC, int iChannel );

/*
 *函  数: TMCC_SetSerialNumber
 *说  明: 设置连接的唯一厂商信息
 *参  数: hTmCC控制句柄, szSerialNumber为序列号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetSerialNumber( HANDLE hTmCC, const char* szSerialNumber );

/*
 *函  数: TMCC_SetOtherParam
 *说  明: 设置一些扩展信息，已废弃
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetOtherParam( HANDLE hTmCC, unsigned int dwFlags, void* buf, int* iLen );

/*
 *函  数: TMCC_UpgradeWebPage
 *说  明: 升级服务器中的网页，网页可由用户自行设计，空间大小限制5M内
 *参  数: hTmCC为控制句柄, lpszPathName存放网页的目录
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_UpgradeWebPage( HANDLE hTmCC, const char *lpszPathName );

/*
 *函  数: TMCC_UpgradeKernel
 *说  明: 升级服务器的Firmware
 *参  数: hTmCC为控制句柄, lpszName为Firmware名称
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_UpgradeKernel( HANDLE hTmCC, const char *lpszName );

/*
 *函  数: TMCC_UpgradeTmccModule
 *说  明: 升级服务器的Tmcc扩展模块
 *参  数: hTmCC为控制句柄, lpszName为扩展模块目录名称
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_UpgradeTmccModule( HANDLE hTmCC, const char *lpszName );

//////////////////////////////////////////////////////////////
///////////////////设备自动升级模块///////////////////////////
//////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_ConfigUpgradeServer
 *说  明: 配置自动升级服务器
 *参  数: hTmCC为升级服务器控制句柄
 *返回值: 成功返回升级服务器控制句柄，失败返回NULL
 */
TMCC_API int TMCC_CALL TMCC_ConfigUpgradeServer( HANDLE hTmCC, tmUpgradeConfig_t* pConfig );

/*
 *函  数: TMCC_RegisterUpgradeCallBack
 *说  明: 注册升级服务器信息输出回调函数
 *参  数: hTmCC为升级服务器控制句柄
 *返回值: 成功返回升级服务器控制句柄，失败返回NULL
 */
TMCC_API void TMCC_CALL TMCC_RegisterUpgradeCallBack( HANDLE hTmCC, TMCC_UPGRADE_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_StartUpgrade
 *说  明: 启动升级服务器，开始升级
 *参  数: hTmCC为升级服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartUpgrade( HANDLE hTmCC );

/*
 *函  数: TMCC_StopUpgrade
 *说  明: 停止升级服务器
 *参  数: hTmCC为升级服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopUpgrade( HANDLE hTmCC );

/*
 *函  数: TMCC_SendUpgradeMessage
 *说  明: 向网络上发送升级消息
 *参  数: hTmCC为升级服务器控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SendUpgradeMessage( HANDLE hTmCC );

//////////////////////////////////////////////////////////////
///////////////////设备自动服务器搜索/////////////////////////
//////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_RegisterEnumServerCallBack 
 *说  明: 注册枚举服务器信息回调函数
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterEnumServerCallBack( HANDLE hEnum, TMCC_ENUMSERVER_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_StartEnum
 *说  明: 启动搜索
 *参  数: hEnum为回枚举控制句柄，由TMCC_CreateEnumServer初始化返回句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartEnum( HANDLE hEnum );

/*
 *函  数: TMCC_StopListen
 *说  明: 关闭枚举监听 
 *参  数: hEnum为回枚举控制句柄，由TMCC_CreateEnumServer初始化返回句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopEnum( HANDLE hEnum );

/*
 *函  数: TMCC_EnumServer
 *说  明: 列举网络中的服务器
 *参  数: hEnum为回枚举控制句柄，由TMCC_CreateEnumServer初始化返回句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_RefreshEnum( HANDLE hEnum );

/*
 *函  数: TMCC_ConfigServerBuEnum
 *说  明: UDP方式配置服务器
 *参  数: hEnum为回枚举控制句柄，由TMCC_CreateEnumServer初始化返回句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ConfigServerByMulti( HANDLE hEnum, tmMultiServerCfg_t* pConfig );


////////////////////////////////////////////////////////
///////////////////实时数据播放/////////////////////////
////////////////////////////////////////////////////////
/*
 *函  数: TMCC_RegisterStreamCallBack
 *说  明: 注册实时数据输出回调
 *参  数: hClient为文件服务器句柄,pCallBack为回调函数指针,context为用户指针式
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API void TMCC_CALL TMCC_RegisterStreamCallBack( HANDLE hClient, TMCC_STREAMREAD_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_RegisterRtpStreamCallBack
 *说  明: 注册实时RTP数据输出回调
 *参  数: hClient为文件服务器句柄,pCallBack为回调函数指针,context为用户指针式
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API void TMCC_CALL TMCC_RegisterRtpStreamCallBack( HANDLE hClient, TMCC_RTPSTREAMREAD_CALLBACK pCallBack, void* context, BOOL bTcpPacket = FALSE );

/*
 *函  数: TMCC_RegisterConnectMessage
 *说  明: 注册连接状态输出消息
 *参  数: hClient为服务器句柄,hWnd用户接收消息窗口,msgID消息ID
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterConnectMessage( HANDLE hClient, HWND hWnd, unsigned int msgID );

/*
 *函  数: TMCC_ConnectStream
 *说  明: 以指定条件打开服务器实时流
 *参  数: hClient为播放句柄,pPlayInfo为打开文件的条件
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ConnectStream( HANDLE hClient, tmPlayRealStreamCfg_t* pPlayInfo, HWND hPlayWnd );

/*
 *函  数: TMCC_MakeKeyFrame
 *说  明: 强制下一帧为关键帧，当句柄是连接视频的那么通道信息用连接中的信息
 *参  数: hClient为播放句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_MakeKeyFrame( HANDLE hClient );

/*
 *函  数: TMCC_SetRealStreamBufferTime
 *说  明: 设置缓冲时间大小
 *参  数: hClient为播放句柄,dwTime为缓冲时间(单位毫秒)
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetStreamBufferTime( HANDLE hClient, unsigned int dwTime );

/*
 *函  数: TMCC_RefreshRealStreamBuffer
 *说  明: 刷新当前数据缓冲
 *参  数: hClient为播放句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_RefreshStreamBuffer( HANDLE hClient );

/*
 *函  数: TMCC_SwicthRealStream
 *说  明: 切换数据流连接的码流
 *参  数: hClient为播放句柄,iStreamId为码流号
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SwicthRealStream( HANDLE hClient, int iStreamId );


////////////////////////////////////////////////////////
/////////////////////数据流播放/////////////////////////
////////////////////////////////////////////////////////
/*
 *函  数: TMCC_OpenStream
 *说  明: 以指定条件打开服务器文件
 *参  数: hTmFile为文件服务器句柄,pHeadBuf为打开文件头或者tmStreamHeadInfo_t头,hPlayWnd为显示视频的窗口
 *		  iPushBufferSize为缓冲大小，根据编码格式决定，一般1024*1024
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_OpenStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize, HWND hPlayWnd, int iPushBufferSize );

/*
 *函  数: TMCC_ResetStream
 *说  明: 以指定条件复位数据流
 *参  数: hStream数据流控制句柄,pHeadBuf为数据流头缓冲，iHeadSize头缓冲大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ResetStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize );

/*
 *函  数: TMCC_CloseStream
 *说  明: 关闭数据流播放
 *参  数: hStream为文件服务器句柄,pPlayInfo为打开文件的条件,hPlayWnd为显示视频的窗口
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CloseStream( HANDLE hStream );

/*
 * 函  数: TMCC_GetFileHead
 * 说  明: 读取文件的头，可以直接输入OpenStream
 * 参  数: pHeadBuf为数据流头存放缓冲,iBufSize缓冲长度
 * 返回值: 成功返回文件头长度，失败返回<=0
 */
TMCC_API int TMCC_CALL TMCC_GetFileHead( const char* lpszFileName, unsigned char* pHeadBuf, int iBufSize );

/*
 * 函  数: TMCC_GetFileIndex
 * 说  明: 读取文件的索引，可以直接输入文件播放，此函数可能很费时
 * 参  数: pHeadBuf为索引存放缓冲,iBufSize缓冲长度
 * 返回值: 成功返回文件索引长度，失败返回<=0
 */
TMCC_API int TMCC_CALL TMCC_GetFileIndex( const char* lpszFileName, unsigned char* pHeadBuf, int iBufSize );

/*
 *函  数: TMCC_PutInStream
 *说  明: 输入数据流播放
 *参  数: hStream为数据流播放句柄句柄,pStreamBuf为数据流缓冲,iStreamSize为数据流大小
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PutInStream( HANDLE hStream, unsigned char* pStreamBuf, int iStreamSize, unsigned int nData );


////////////////////////////////////////////////////////
///////////////////远程文件搜索/////////////////////////
////////////////////////////////////////////////////////
/*
 *函  数: TMCC_FindFirst
 *说  明: 开始主动方式搜索服务器文件
 *参  数: hTmFile为文件服务器句柄，pFindCondition为搜索条件，lpFindFileData为输出文件信息
 *返回值: 成功返回文件搜索句柄，失败返回NULL
 */
TMCC_API HANDLE TMCC_CALL TMCC_FindFirstFile( HANDLE hTmCC, tmFindConditionCfg_t* pFindCondition, tmFindFileCfg_t* lpFindFileData );

/*
 *函  数: TMCC_FindNextFile
 *说  明: 搜索下一个文件
 *参  数: hTmFile为文件服务器句柄，lpFindFileData为输出文件信息
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_FindNextFile( HANDLE hTmFile, tmFindFileCfg_t* lpFindFileData );

/*
 *函  数: TMCC_FindCloseFile
 *说  明: 关闭搜索
 *参  数: hTmFile为文件服务器句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_FindCloseFile( HANDLE hTmFile );

/*
 *函  数: TMCC_DownloadFile
 *说  明: 下载服务器文件
 *参  数: hTmFile为文件服务器句柄, pPlayInfo为下载条件,lpSaveFileName为保存的本地文件,bCancel下载中停止指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_DownloadFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, const char* lpSaveFileName, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_DownloadFileA( HANDLE hTmCC, tmDownloadFileCfg_t* pDownloadInfo, int iDownloadNum, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );


////////////////////////////////////////////////////////
//////////////////////文件播放//////////////////////////
////////////////////////////////////////////////////////
/*
 *函  数: TMCC_OpenFile
 *说  明: 以指定条件打开服务器文件
 *参  数: hTmCC为文件服务器句柄,pPlayInfo为打开文件的条件,hPlayWnd为显示视频的窗口;
 *		  当hTmCC==NULL是为播放本地文件
 *返回值: 成功返回播放控制句柄,失败返回NULL
 */
TMCC_API HANDLE TMCC_CALL TMCC_OpenFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, HWND hPlayWnd );

/*
 *函  数: TMCC_OpenRemoteFile
 *说  明: 以指定条件打开服务器文件
 *参  数: hTmCC为文件服务器句柄,pPlayInfo为打开文件的条件,hPlayWnd为显示视频的窗口;
 *返回值: 成功返回播放控制句柄,失败返回NULL
 */
TMCC_API int TMCC_CALL TMCC_OpenRemoteFile( HANDLE hTmCC, tmRemoteFileInfo_t* pPlayInfo, HWND hPlayWnd );

/*
 *函  数: TMCC_CloseFile
 *说  明: 关闭打开的服务器文件
 *参  数: hTmFile为文件服务器句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CloseFile( HANDLE hTmFile );

/*
 *函  数: TMCC_ReadFile
 *说  明: 读取文件数据，可以任意读取，或读取完整一帧
 *参  数: hTmFile为文件服务器句柄,buf数据缓冲，iReadSize为读取大小
 *返回值: 成功返回读取的大小，失败返回小于0
 */
TMCC_API int TMCC_CALL TMCC_ReadFile( HANDLE hTmFile, BYTE* buf, int iReadSize );

/*
 *函  数: TMCC_ControlFile
 *说  明: 控制文件播放
 *参  数: hTmFile为文件服务器句柄,pPlayControl为文件控制参数信息
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ControlFile( HANDLE hTmFile, tmPlayControlCfg_t* pPlayControl );

/*
 *函  数: TMCC_GetFilePlayState
 *说  明: 读取打开的文件位置
 *参  数: hTmFile为文件服务器句柄,tmTimeInfo_t为存放文件位置指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetFilePlayState( HANDLE hTmFile, tmPlayStateCfg_t* pState );

/*
 *函  数: TMCC_RegisterFileCallBack 
 *说  明: 注册文件访问回调函数
 *参  数: pCallBack为回调函数指针，context为调用者自定义数据
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterFileCallBack( HANDLE hTmFile, tmFileAccessInterface_t* pCallBack, void* context );

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////视频控制接口定义//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_RegisterAVFrameCallBack
 *说  明: 注册解码视频输出回调
 *参  数: hTmCC为服务器句柄,pCallBack用户回调函数指针,context为用户自定义指针
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterAVFrameCallBack( HANDLE hTmCC, TMCC_AVFRAME_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_RegisterDrawCallBack
 *说  明: 注册解码视频自会输出回调
 *参  数: hTmCC为服务器句柄,pCallBack用户回调函数指针,context为用户自定义指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API void TMCC_CALL TMCC_RegisterDrawCallBack( HANDLE hTmCC, TMCC_DDRAW_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_SetVolume
 *说  明: 设置音频播放音量
 *参  数: hTmCC为控制句柄，iVolume为音量(-10000~0,-10000最小,0最大)
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetVolume( HANDLE hTmCC, int iVolume );

/*
 *函  数: TMCC_SetMute
 *说  明: 设置播放声音开关，只是本地解码后的声音
 *参  数: hTmCC为控制句柄，bMute为开关(FALSE打开声音，TRUE静音)
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetMute( HANDLE hTmCC, BOOL bMute );

/*
 *函  数: TMCC_SetDisplayShow
 *说  明: 设置解码视频是否显示，默认打开
 *参  数: hTmCC为控制句柄，bShow为开关(FALSE不显示，TRUE显示)
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayShow( HANDLE hTmCC, BOOL bShow );

/*
 *函  数: TMCC_SetImageOutFmt
 *说  明: 设置解码视频输出格式(默认是YUV420)
 *参  数: hTmCC为控制句柄，iOutFmt为输出格式
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetImageOutFmt( HANDLE hTmCC, unsigned int iOutFmt );

/*
 *函  数: TMCC_GetDisplayRegion
 *说  明: 读取显示视频的显示位置
 *参  数: hTmCC为控制句柄，iRegionNum为显示号,pSrcRect为显示位置相对于原始图像,hDestWnd显示窗口,bEnable为是否显示
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND* hDestWnd, BOOL* bEnable );

/*
 *函  数: TMCC_SetDisplayRegion
 *说  明: 读取显示视频的显示位置
 *参  数: hTmCC为控制句柄，iRegionNum为显示号,pSrcRect为显示位置相对于原始图像,hDestWnd显示窗口,bEnable为是否显示
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND hDestWnd, BOOL bEnable );

/*
 *函  数: TMCC_RefreshDisplay
 *说  明: 刷新当前显示
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_RefreshDisplay( HANDLE hTmCC );

/*
 *函  数: TMCC_ClearDisplay
 *说  明: 清空当前显示
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_ClearDisplay( HANDLE hTmCC );

/*
 *函  数: TMCC_GetImageSize
 *说  明: 读取视频大小
 *参  数: hTmCC为控制句柄，iWidth/iHeight为存放大小的指针
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetImageSize( HANDLE hTmCC, int* iWidth, int* iHeight );

/*
 *函  数: TMCC_GetDisplayScale
 *说  明: 读取视频原始显示比例
 *参  数: hTmCC为控制句柄，iScale为存放显示比例的指针，注意此比例为宽/高*1000
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayScale( HANDLE hTmCC, int* iScale );

/*
 *函  数: TMCC_CapturePictureToFile
 *说  明: 当前显示视频抓图到指定文件
 *参  数: hTmCC为控制句柄,pFileName为存放的文件,pFmt为格式
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CapturePictureToFile( HANDLE hTmCC, const char* pFileName, const char* pFmt );

/*
 *函  数: TMCC_CapturePictureToBuffer
 *说  明: 当前显示视频抓图到指定缓冲
 *参  数: hTmCC为控制句柄,lpBuffer为存放图片缓冲,iBufferSize为缓冲大小(输入为缓冲大小，输出实际数据大小),pFmt为格式
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CapturePictureToBuffer( HANDLE hTmCC, const char* pFmt, void* lpBuffer, int* iBufferSize );

/*
 *函  数: TMCC_OpenAvRender
 *说  明: 以指定条件打开音视频Render
 *参  数: pCfg为打开条件
 *返回值: 成功返回RENDER控制句柄,失败返回NULL
 */
TMCC_API int TMCC_CALL TMCC_OpenAvRender( HANDLE hTmCC, tmAvRenderConfig_t* pCfg, HWND hPlayWnd );

/*
 *函  数: TMCC_CloseAvRender
 *说  明: 关闭打开的Render
 *参  数: hTmFile为文件服务器句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CloseAvRender( HANDLE hTmCC );

/*
 *函  数: TMCC_PutinAvFrame
 *说  明: 输入音视频播放显示
 *参  数: hTmCC为控制句柄,pImage音视频帧
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PutinAvFrame( HANDLE hTmCC, tmAvImageInfo_t* pImage );

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////设备状态和报警监听/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_StartListen
 *说  明: 开启状态和报警监听，以及报警图片上传
 *参  数: hTmCC为控制句柄,iPort为监听端口
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartListen( HANDLE hTmCC, int iPort );

/*
 *函  数: TMCC_StopListen
 *说  明: 关闭状态和报警监听，以及报警图片上传
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopListen( HANDLE hTmCC );


//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////监听设备主动上传///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *函  数: TMCC_RegisterDeviceLoginCallBack
 *说  明: 注册设备主动登录输出回调
 *参  数: hTmCC为服务器句柄,pCallBack用户回调函数指针,context为用户自定义指针
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceLoginCallBack( HANDLE hTmCC, TMCC_DEVICELOGIN_CALLBACK pCallBack, void* context );
/*
 *函  数: TMCC_RegisterDeviceStreamCallBack
 *说  明: 注册设备数据上传输出回调
 *参  数: hTmCC为服务器句柄,pCallBack用户回调函数指针,context为用户自定义指针
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceStreamCallBack( HANDLE hTmCC, TMCC_DEVICESTREAM_CALLBACK pCallBack, void* context );
/*
 *函  数: TMCC_RegisterDeviceTalkCallBack
 *说  明: 注册设备主动语音对讲输出回调
 *参  数: hTmCC为服务器句柄,pCallBack用户回调函数指针,context为用户自定义指针
 *返回值: 无
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceTalkCallBack( HANDLE hTmCC, TMCC_DEVICETALK_CALLBACK pCallBack, void* context );

/*
 *函  数: TMCC_StartListenDevice
 *说  明: 开启设备上传监听
 *参  数: hTmCC为控制句柄,iPort为监听端口
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StartListenDevice( HANDLE hTmCC, int iPort );

/*
 *函  数: TMCC_StopListenDevice
 *说  明: 关闭设备上传监听
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_StopListenDevice( HANDLE hTmCC );

//音视频解码
/*
 *函  数: TMCC_OpenAvDecoder
 *说  明: 打开音视频解码
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_OpenAvDecoder( HANDLE hTmCC, tmAvDecoderConfig_t* pCfg );

/*
 *函  数: TMCC_CloseAvDecoder
 *说  明: 关闭音视频解码
 *参  数: hTmCC为控制句柄
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_CloseAvDecoder( HANDLE hTmCC );

/*
 *函  数: TMCC_PutInAvDecoderData
 *说  明: 输入原始数据解码成图片YUV
 *参  数: hTmCC为控制句柄,pImageIn为原始数据, pImageOut为解码输出的数据, iGetFrame放回是否解码完成
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_PutInAvDecoderData( HANDLE hTmCC, tmAvImageInfo_t* pImageIn, tmAvImageInfo_t* pImageOut, int* iGetFrame );

/*
 *函  数: TMCC_SetMD5EncryptParameter
 *说  明: 设置MD5的加密矩阵信息
 *参  数: hTmCC控制句柄, byData为矩阵数据
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_SetMD5EncryptParameter( HANDLE hTmCC, const unsigned char* byData, int iDataSize );

/*
 *函  数: TMCC_GetMD5EncryptData
 *说  明: 根据设置的MD5矩阵信息，加密数据
 *参  数: hTmCC控制句柄, byUserData为需要加密的数据,iUserDataSize为数据长度,byMD5Data为机密后的数据缓冲必须大于16
 *返回值: 成功返回TMCC_ERR_SUCCESS，失败返回其它值
 */
TMCC_API int TMCC_CALL TMCC_GetMD5EncryptData( HANDLE hTmCC, const unsigned char* byUserData, int iUserDataSize, unsigned char* byMD5Data );


#ifdef __cplusplus
}
#endif

#endif //__TMCONTROLCLIENT_H__
