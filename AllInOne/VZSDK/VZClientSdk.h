//---------------------------------------------------------------------------
#ifndef VZCLIENTSDKH
#define VZCLIENTSDKH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#ifdef _USRDLL
#define VZC_DLL_EXP extern "C" __declspec(dllexport)
#else
#define VZC_DLL_EXP extern "C" __declspec(dllimport)
#endif

#include "VzClientSDK_CommonDefine.h"
#include "VzClientSDK_DeviceDefine.h"
#include "VzClientSDK_IVSDefine.h"

//登录函数可能的返回值，表示用户名或密码错误
#ifndef LOGIN_WRONG_USER_OR_PASS
	#define LOGIN_WRONG_USER_OR_PASS     -2
#endif

//登录函数可能的返回值，表示序列号已存在
#ifndef LOGIN_SERIALNO_EXIST
	#define LOGIN_SERIALNO_EXIST     -3
#endif

typedef void (CALLBACK * VZDEV_CallBackDecodeBuf)(int iRealHandle,VzYUV420P * pOutBuf, DWORD dwUser);
typedef void (CALLBACK * VZDEV_CallBackRealData) (int iRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, timeval timeStamp, int isIFrame, DWORD dwUser);
typedef void (CALLBACK * VZDEV_CallBackTalkData)(int iTalkHandle, const void *pDataBuffer, DWORD dwBufSize ,BYTE byAudioFlag, DWORD dwUser);

/**
*  @brief 使能远程设备报警，
*  @param  [IN] iUserID VZC_Login函数返回的用户ID
*  @enable [IN] enable 1是打开，0时关闭
*  @return 0表示成功，-1表示失败
*/
VZC_DLL_EXP int __stdcall VZC_SetMotionDetection(int iUserID,int enable);

/**
*  @brief 获取远程设备报警是否开启
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] enable 取得远程报警是否打开信息
*  @return 0表示成功，-1表示失败
*/
VZC_DLL_EXP int __stdcall VZC_GetMotionDetection(int iUserID,int *enable);

/**
*  @brief 打开本地报警通道，会使能远程设备报警
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return AlarmHandle-返回的报警通道Handle，需要保存起来，关闭报警的函数需要
*/
VZC_DLL_EXP int __stdcall VZC_SetupAlarmChan(int iUserID);

/**
*  @brief 关闭报警通道
*  @param [IN] iAlarmHandle VZC_SetupAlarmChan函数返回的报警通道Handle
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_CloseAlarmChan(int iAlarmHandle);

/**
*  @brief 获取智能视频显示模式
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [OUT] pDrawMode 显示模式，参考VZ_IVS_DRAWMODE
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETDrawMode(int iUserID, int iChannel, VZ_IVS_DRAWMODE * pDrawMode);

/**
*  @brief 设置智能视频显示模式
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [IN] pDrawMode 显示模式，参考VZ_IVS_DRAWMODE
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SETDrawMode(int iUserID, int iChannel, VZ_IVS_DRAWMODE * pDrawMode);

/**
*  @brief 获取相机健康状况检测配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetCamHealthAlarmEnable(int iUserID, bool *bEnable);

/**
*  @brief 保存相机健康状况检测配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetCamHealthAlarmEnable(int iUserID, bool bEnable);

/**
*  @brief 获取智能设备能力
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] pEvent_Ability 能力，参考VZ_IVS_EVENT_ABILITY
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETEventAbility(int iUserID,VZ_IVS_EVENT_ABILITY *pEvent_Ability);

/**
*  @brief 获取智能设备规则
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [OUT] pRuleCfg 规则参数，参考VZ_IVS_RULE_CFG
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETEventRule(int iUserID,int iChannel,VZ_IVS_RULE_CFG * pRuleCfg);

/**
*  @brief 设置智能设备规则，对于有时间表的设备调用，时间表将自动设为全时段
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [IN] pRuleCfg 规则参数，参考VZ_IVS_RULE_CFG
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SETEventRule(int iUserID,int iChannel,VZ_IVS_RULE_CFG * pRuleCfg);

/**
*  @brief 获取智能设备规则，带时间参数
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [OUT] pRuleCfg 规则参数，参考VZ_IVS_RULE_CFG_EX
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETEventRuleEx(int iUserID,int iChannel,VZ_IVS_RULE_CFG_EX * pRuleCfg);

/**
*  @brief 设置智能设备规则，带时间参数
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道编号
*  @param [IN] pRuleCfg 规则参数，参考VZ_IVS_RULE_CFG_EX
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SETEventRuleEx(int iUserID,int iChannel,VZ_IVS_RULE_CFG_EX * pRuleCfg);

/**
*  @brief 获取智能设备运行模式
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] RunMode 运行模式
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETRunMode(int iUserID,int iChannel,int *RunMode);

/**
*  @brief 设置智能设备运行模式
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] RunMode 运行模式
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SETRunMode(int iUserID,int iChannel,int RunMode);

/**
*  @brief 获取智能设备运行模式名称
*  @param [IN] DeviceType 参考IVS_TYPE
*  @param [IN] RunMode 运行模式
*  @param [OUT] RunmodeName 运行模式名称，长度大于20
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETRunModeName(int DeviceType,int RunMode,char *RunmodeName);

/**
*  @brief 获取当前使用的预置点
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] PresetNum 预置点，取值范围1-64
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GETPresetNum(int iUserID,int iChannel,int *PresetNum);

/**
*  @brief 设置预置点
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] PresetNum 预置点，取值范围1-64
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SETPresetNum(int iUserID,int iChannel,int PresetNum);

/**
*  @brief 获取 开启或关闭gio报警输入输出（总开关）状态
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetExtTriggerEnable(int iUserID, bool *bEnable);

/**
*  @brief 开启或关闭gio报警输入输出（总开关）
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetExtTriggerEnable(int iUserID, bool bEnable);

/**
*  @brief 获取 开启或关闭gio报警输出状态
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetExtTriggerOutputEnable(int iUserID, bool *bEnable);

/**
*  @brief 开启或关闭gio报警输出
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetExtTriggerOutputEnable(int iUserID, bool bEnable);

/**
*  @brief 异常回调函数定义，根据不同异常消息，异常消息参数不同
*  @param [IN] iCommand 异常消息
*  @param [IN] lUserID 设备UserID
*  @param [IN] lHandle 异常消息参数
*  @param [IN] pUser 用户定义参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
typedef void (CALLBACK* fExceptionCallBack)(int iCommand, int lUserID, int lHandle, void *pUser);

/**
*  @brief 报警回调函数定义，根据不同报警类型，报警信息缓存里数据不同
*  @param [IN] iCommand 报警类型
*  @param [IN] pBuffer 报警信息缓存
*  @param [IN] dwBufSize 报警信息缓存大小
*  @param [IN] pDevInfo 报警设备信息，参考VZ_IVS_DEV_INFO
*  @param [IN] pUser 用户定义参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
typedef int (CALLBACK *fMessCallBack) (int iCommand, BYTE *pBuffer, DWORD dwBufSize, VZ_IVS_DEV_INFO* pDevInfo , void *pUser);
//---------------------------------------------------------------------------


/**  
* @brief 初始化SDK
* @return 返回值为0表示初始化成功，其他值表示初始化失败。获取错误码调用VZC_GetLastError();
*/
VZC_DLL_EXP int __stdcall VZC_Init();

/**
*  @brief 注册处理异常的回调函数
*  @param [IN] nMessage 消息
*  @param [IN] hWnd 消息窗口
*  @param [IN] fExceptionCallBack 回调函数，函数体参考fExceptionCallBack
*  @param [IN] pUser 用户参数
*  @return 返回值0表示成功，其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetDVRExceptionCallBack(UINT nMessage, HWND hWnd, fExceptionCallBack, void *pUser);

/**
*  @brief 设置SDK报警回调函数
*  @param [IN] fMessCallBack 回调函数，函数体参考fMessCallBack说明
*  @param [IN] pUser 用户参数
*  @return 返回值0表示成功，其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetDVRMessageCallBack(fMessCallBack, void *pUser);


/**      
*  @brief 释放SDK资源
*  @return 返回值为0表示系统释放成功，其他值表示系统释放失败。获取错误码调用VZC_GetLastError();
*/
VZC_DLL_EXP int __stdcall VZC_Cleanup();


/**      
*  @brief 获取设备版本号，版本号由4个数值组成
*  @return 返回值为0表示成功;
*/
VZC_DLL_EXP int __stdcall VZC_GetRemoteSoftWareVersion(int iUserID, int &ver1, int &ver2, int &ver3, int &ver4);


/**
*  @brief 清除设备在线状态
*  @return 返回值0表示成功，其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_ClearOnline();

/**
*  @brief 登录设备，如果已有相同ip，端口登录，返回以前的userID,ip相同端口不同，返回失败,转发请输入指针的数组首地址，转发层数最多4层,wDVRRtspPort默认传0会自动获取服务器端口
*  @param [IN] sDVRIP 设备IP地址
*  @param [IN] wDVRPort 设备端口
*  @param [IN] sUserName 连接用户名
*  @param [IN] sPassword 连接密码
*  @param [OUT] pDeviceInfo 连接设备的信息，由VZDEV_DEVICEINFO定义
*  @param [IN] trans	连接的管理服务器阵列
*  @param [IN] nTrans_num 管理服务器级数
*  @param [IN] RTSPtrans 连接转发服务器地址阵列
*  @param [IN] nRTSPTrans_num 转发服务器的级数
*  @param [IN] wDVRRtspPort rtsp端口
*  @param [IN] httpTimeOut 的超时单位毫秒,0表示使用默认
*  @return UserID返回的用户ID，需要保存起来，操作设备的函数需要。
*/
VZC_DLL_EXP int __stdcall VZC_Login(char * _sDVRIP,WORD wDVRPort,
        char * _sUserName,char * sPassword,PVZDEV_DEVICEINFO pDeviceInfo,
		VZ_Transmit_Server **trans,int nTrans_num,VZ_Transmit_Server **RTSPtrans,int nRTSPTrans_num,
		WORD wDVRRtspPort=0,int httpTimeOut=0);

/**
*  @brief 注销设备
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_Logout(int iUserID);

/**
*  @brief 通过P2P的方式登录设备，如果已有相同P2PID，返回以前的userID，如果给定了P2P节点，则使用对应IP指定的节点，否则默认使用运行在本机上的P2P节点
*  @param [IN] pStrP2PID 设备唯一的P2P序列号
*  @param [IN] pStrUserName 设备登录用户名
*  @param [IN] pStrPassword 设备登录密码
*  @param [OUT] pDeviceInfo 连接设备的信息，由VZDEV_DEVICEINFO定义
*  @param [IN] pStruP2PNode	用于传输控制数据的P2P节点信息
*  @param [IN] pStruP2PNode	用于传输流媒体数据的P2P节点信息
*  @return UserID返回的用户ID，需要保存起来，操作设备的函数需要。
*/
VZC_DLL_EXP int __stdcall VZC_LoginVIAP2P(const char *pStrP2PID,
										  const char *pStrUserName,
										  const char *pStrPassword,
										  PVZDEV_DEVICEINFO pDeviceInfo,
										  const VZ_Transmit_Server *pStruP2PNode,
										  const VZ_Transmit_Server *pStruP2PNodeRTSP,
										  int httpTimeOut=0);
/**
*  @brief 设置设备时钟
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号由0开始定义
*  @param [IN] pDT 新的时钟变量，由PVZDEV_DateTimeParam定义
*  @return 返回值为0表示成功，返回其他值表示失败。 
*/
VZC_DLL_EXP int __stdcall VZC_SetTime(int iUserID, int iChannel, PVZDEV_DateTimeParam pDT);

/**
*  @brief 获取设备时钟
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号由0开始定义
*  @param [OUT] pDT 新的时钟变量，由PVZDEV_DateTimeParam定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetTime(int iUserID, int iChannel, PVZDEV_DateTimeParam pDT);

/**
*  @brief 改变本地客户端某个连接使用的ip和端口，本函数并没有修改设备IP及端口，而是由于设备IP及端口发生了改变后，便于保证正常连接用的。
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] ipaddr IP地址
*  @param [IN] http_port 端口
*  @param [IN] rtsp_port 端口
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetIP(int iUserID, char* ipaddr, WORD http_port,WORD rtsp_port);//改变本地客户端某个连接使用的ip和端口

/**
*  @brief 设备网络参数配置。
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] netcfg 参见VZDEV_NETCFG结构体定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetNetConfig(int iUserID, VZDEV_NETCFG* netcfg);

/**
*  @brief 获取设备网络参数配置。
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] netcfg 参见VZDEV_NETCFG结构体定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetNetConfig(int iUserID, VZDEV_NETCFG* netcfg);



/**
*  @brief 图像预览
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pClientInfo 客户端信息，由PVZDEV_CLIENTINFO定义
*  @param [IN] bNB 是否非阻塞
*  @return 返回值：预览通道Handle，需要保存起来，操作预览等相关的函数需要
*/
VZC_DLL_EXP int __stdcall VZC_RealPlay(int iUserID,PVZDEV_CLIENTINFO pClientInfo, BOOL bNB);

/**
*  @brief 关闭图像预览
*  @param [IN] iRealHandle VZC_RealPlay函数返回的预览通道Handle
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_StopRealPlay(int iRealHandle);

/**
*  @brief 设置压缩数据的回调函数
*  @param [IN] iRealHandle VZC_RealPlay函数返回的预览通道Handle
*  @param [IN] fRealDataCallBack	回调函数
*  @param [IN] dwUser 上下文
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetRealDataCallBack(int iRealHandle,
								VZDEV_CallBackRealData fRealDataCallBack,DWORD dwUser);

/**
*  @brief 设置解压后的帧数据获取的回调函数
*  @param [IN] iRealHandle VZC_RealPlay函数返回的预览通道Handle
*  @param [IN] fDecodeBuf 回调函数
*  @param [IN] dwUser 上下文
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetCallBackDecodeBuf(int iRealHandle,
								VZDEV_CallBackDecodeBuf fDecodeBuf,DWORD dwUser);

/**
*  @brief 强制产生一个关键帧（I帧）
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_MakeKeyFrame(int iUserID, int iChannel);

/**
*  @brief 获取一幅图片
*  @param [IN] iRealHandle VZC_RealPlay函数返回的预览通道Handle
*  @param [IN] sPicFileName	将图片保存为BMP位图的文件目录和名称
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_CapturePicture(int iRealHandle,char *sPicFileName);


/**
*  @brief 获取视频分辨率，注意，如果以非阻塞方式调用了VZC_RealPlay后，立即调用该函数不一定能获得正确结果，因为视频数据可能未传输到本地；
*  所以需要阻塞方式调用VZC_RealPlay后，立即调用该函数，才能成功获取分辨率
*  @param [IN] iRealHandle VZC_RealPlay函数返回的预览通道Handle
*  @param [OUT] pWidth视频宽度 
*  @param [OUT] pHeight视频高度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoResolution(int iRealHandle, int *pWidth, int *pHeight);

/**
*  @brief 接收并播放音频
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值：音频播放句柄，需要保存起来，用于其他音频输出的操作
*/
VZC_DLL_EXP int __stdcall VZC_OpenSound(int iUserID);

/**
*  @brief 停止接收和播放音频
*  @param [IN] iAudioPlayHandle VZC_OpenSound函数返回的音频播放句柄
*  @return 返回值：返回值为0表示成功，返回其他值表示失败
*/
VZC_DLL_EXP int __stdcall VZC_CloseSound(int iAudioPlayHandle);

//接收及获取音频
/**
*  @brief 接收并获取音频数据
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] bNeedEncode 获取的数据是否压缩，0为ACM，1为G711
*  @param [IN] fAudioDataCallBack 音频数据回调函数
*  @param [IN] dwUser 回调函数的上下文
*  @return 返回值：音频播放句柄，需要保存起来，用于其他音频输出的操作
*/
VZC_DLL_EXP int __stdcall VZC_OpenSoundData(int iUserID, int bNeedEncode,
											VZDEV_CallBackTalkData fAudioDataCallBack, DWORD dwUser);
/**
*  @brief 停止接收和获取音频数据
*  @param [IN] iSoundDataHandle VZC_OpenSoundData函数返回的音频数据句柄
*  @return 返回值：返回值为0表示成功，返回其他值表示失败
*/
VZC_DLL_EXP int __stdcall VZC_CloseSoundData(int iSoundDataHandle);

/**
*  @brief 控制是否允许音频
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] bEnable 0为禁用音频播放和音频数据回调，1为允许
*  @return 返回值：返回值为0表示成功，返回其他值表示失败
*/
VZC_DLL_EXP int __stdcall VZC_AudioEnable(int iUserID, int bEnable);

/**
*  @brief 开始发送本地话筒的音频到远程
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] fTalkDataCallBack 本地音频数据回调，可以为空
*  @param [IN] dwUser 本地音频数据回调的上下文
*  @return 返回值：本地音频发送的句柄，需要保存起来，用于其他本地音频发送相关的操作
*/
VZC_DLL_EXP int __stdcall VZC_TalkStart(int iUserID, VZDEV_CallBackTalkData fTalkDataCallBack, DWORD dwUser);

/**
*  @brief 停止发送本地音频
*  @param [IN] iTalkHandle VZC_TalkStart函数和VZC_TalkStartByWaveFile函数返回的本地音频发送的句柄
*  @return 返回值：返回值为0表示成功，返回其他值表示失败
*/
VZC_DLL_EXP int __stdcall VZC_TalkStop(int iTalkHandle);
//VZC_DLL_EXP int __stdcall VZC_TalkGetStat(int iTalkHandle);       //返回VZDEV_TALK_STAT_xxx

/**
*  @brief 开始发送本地音频文件的音频到远程，音频文件支持PCM编码的wav格式
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] strFileName 音频文件的绝对路径
*  @return 返回值：本地音频发送的句柄，需要保存起来，用于其他本地音频发送相关的操作
*/
VZC_DLL_EXP int __stdcall VZC_TalkStartByWaveFile(int UserID, const char *strFileName);

/**
*  @brief 完全恢复默认参数；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_RestoreConfig(int iUserID);


/**
*  @brief 部分恢复默认参数，ip端口配置，用户配置，设备名保留；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_RestoreConfigPartly(int iUserID);


/**
*  @brief 重启设备；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_RebootDVR(int iUserID);


/**
*  @brief 透明通道开启；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iSerialPort 透明通道端口号
*  @param [IN] fSerialDataCallBack 透明通道回调函数
*  @param [IN] dwUser 用户定义参数
*  @return 返回值透明通道handle，-1为失败。
*/
VZC_DLL_EXP int __stdcall VZC_SerialStart(int iUserID,int iSerialPort,
										  void(CALLBACK *fSerialDataCallBack)(int iSerialHandle,char *pRecvDataBuffer,
										  DWORD dwBufSize,DWORD dwUser),DWORD dwUser);
/**
*  @brief 透明通道发送数据；
*  @param [IN] iSerialHandle VZC_SerialStart函数返回的句柄
*  @param [IN] param 串口数据，参见VZDEV_CommDataGetParam结构体
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SerialSend(int iSerialHandle, VZDEV_CommDataGetParam *param);

/**
*  @brief 透明通道停止发送数据；
*  @param iSerialHandle VZC_SerialStart函数返回的句柄
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SerialStop(int iSerialHandle);




//参数设置
/**
*  @brief 获取设备名称；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] name 设备名
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetDeviceName(int iUserID, char *name);
/**
*  @brief 设置设备名称；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] name  设备名
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetDeviceName(int iUserID, char *name);

/**
*  @brief 获取视频参数；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] brt 亮度
*  @param [OUT] cst 对比度
*  @param [OUT] sat 饱和度
*  @param [OUT] hue 色度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoPara(int iUserID, int iChannel, int *brt, int *cst, int *sat, int *hue);

/**
*  @brief 设置视频参数；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] brt 亮度
*  @param [IN] cst 对比度
*  @param [IN] sat 饱和度
*  @param [IN] hue 色度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetVideoPara(int iUserID, int iChannel, int brt, int cst, int sat, int hue);

/**
*  @brief 设置视频OSD参数；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] pParam 详见VZDEV_OSD_Param结构体
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetChannelOsdParam(int iUserID, int iChannel, VZDEV_OSD_Param *pParam);

/**
*  @brief 获取视频OSD参数；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] pParam 详见VZDEV_OSD_Param结构体
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetChannelOsdParam(int iUserID, int iChannel, VZDEV_OSD_Param *pParam);

/**
*  @brief 获取主码流分辨率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] sizeval 详见VZDEV_FRAMESIZE_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoFrameSize(int iUserID, int iChannel, int *sizeval);//VZDEV_FRAMESIZE_XXX

/**
*  @brief 设置主码流分辨率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] sizeval 详见VZDEV_FRAMESIZE_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetVideoFrameSize(int iUserID, int iChannel, int sizeval);//VZDEV_FRAMESIZE_XXX

/**
*  @brief 获取主码流帧率
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] Rateval 帧率，范围1-25
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoFrameRate(int iUserID, int iChannel, int *Rateval);//1-25

/**
*  @brief 设置主码流帧率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] Rateval 帧率，范围1-25
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetVideoFrameRate(int iUserID, int iChannel, int Rateval);//1-25

/**
*  @brief 获取主码流压缩模式；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] modeval 详见VZDEV_VIDEO_COMPRESS_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoCompressMode(int iUserID, int iChannel, int *modeval);//VZDEV_VIDEO_COMPRESS_XXX

/**
*  @brief 设置主码流压缩模式；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] modeval 详见VZDEV_VIDEO_COMPRESS_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetVideoCompressMode(int iUserID, int iChannel, int modeval);//VZDEV_VIDEO_COMPRESS_XXX

//VZC_DLL_EXP int __stdcall VZC_GetVideoVBR(int iUserID, int iChannel, int *levelval);//0~7，7最好
//VZC_DLL_EXP int __stdcall VZC_SetVideoVBR(int iUserID, int iChannel, int levelval);//0~7，7最好

/**
*  @brief 获取主码流比特率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] rateval 当前视频比特率
*  @param [OUT] ratelist 暂时不用
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetVideoCBR(int iUserID, int iChannel, int *rateval/*Kbps*/, int *ratelist);

/**
*  @brief 设置主码流比特率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] rateval 当前视频比特率
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetVideoCBR(int iUserID, int iChannel, int rateval/*Kbps*/);

//子码流
/**
*  @brief 开启子码流；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] bEnable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetSubStreamEnable(int iUserID, int iChannel, int bEnable);
/**
*  @brief 获取子码流分辨率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] sizeval 详见VZDEV_FRAMESIZE_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSubVideoFrameSize(int iUserID, int iChannel, int * sizeval);

/**
*  @brief 设置子码流分辨率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] sizeval 详见VZDEV_FRAMESIZE_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetSubVideoFrameSize(int iUserID, int iChannel, int sizeval);

/**
*  @brief 获取子码流帧率
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] Rateval 帧率，范围1-25
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSubVideoFrameRate(int iUserID, int iChannel, int *Rateval);

/**
*  @brief 设置子码流帧率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] Rateval 帧率，范围1-25
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetSubVideoFrameRate(int iUserID, int iChannel, int Rateval);

/**
*  @brief 获取子码流压缩模式；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] modeval 详见VZDEV_VIDEO_COMPRESS_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSubVideoCompressMode(int iUserID, int iChannel, int *modeval);

/**
*  @brief 设置子码流压缩模式；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [IN] modeval 详见VZDEV_VIDEO_COMPRESS_宏定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetSubVideoCompressMode(int iUserID, int iChannel, int modeval);


/**
*  @brief 获取子码流比特率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] rateval 当前视频比特率
*  @param [OUT] ratelist 暂时不用
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSubVideoCBR(int iUserID, int iChannel, int *rateval/*Kbps*/, int *ratelist);

/**
*  @brief 设置子码流比特率；
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] rateval 当前视频比特率
*  @param [OUT] ratelist 暂时不用
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetSubVideoCBR(int iUserID, int iChannel, int rateval/*Kbps*/);

/**
*  @brief 设置播放缓存；
*  @param [IN] iRealHandle  VZC_RealPlay函数返回的预览通道Handle
*  @param [IN] len 范围[1~60],设置播放缓冲，设为1，延迟最小，60最流畅
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetPlayCacheLen(int iRealHandle, int len);	

/**
*  @brief 获取设备序列号；
*  @param [IN] ip ip统一使用字符串的形式传入
*  @param [IN] port 使用和登录时相同的端口
*  @param [OUT] SerHi 序列号高位
*  @param [OUT] SerLo 序列号低位
*  @param [IN] trans 转发服务器，用于跨网段获取设备信息
*  @param [IN] nTrans_num 转发服务器层数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSerailNo(char *ip, WORD port, unsigned int *SerHi, unsigned int *SerLo,VZ_Transmit_Server **trans,int nTrans_num,int httpTimeOut=0);

/**
*  @brief 获取设备序列号，已经登录的设备，用该接口可以快速获得序列号
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] SerHi 序列号高位
*  @param [OUT] SerLo 序列号低位
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSerailNoByUserID(int iUserID, unsigned int *SerHi, unsigned int *SerLo);

//云台解码器
/**
*  @brief 获取设备云台协议相关
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] pParam 详见PVZDEV_PtzTypeParam
*  @param [IN] timeout 如果timeout == 0，采用默认的超时时间
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetPtzType(int iUserID, int iChannel, PVZDEV_PtzTypeParam pParam, DWORD timeout);

/**
*  @brief 设置设备云台协议相关
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] pParam 详见PVZDEV_PtzTypeParam
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetPtzType(int iUserID, int iChannel, PVZDEV_PtzTypeParam pParam);

/**
*  @brief 获取设备云台预制位相关
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] pParam 详见PVZDEV_PtzPresetParam
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetPtzPreset(int iUserID, int iChannel, PVZDEV_PtzPresetParam pParam);

/**
*  @brief 设置设备云台预制位相关
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] iChannel 通道号
*  @param [OUT] pParam 详见PVZDEV_PtzPresetParam
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetPtzPreset(int iUserID, int iChannel, PVZDEV_PtzPresetParam pParam);

/**
*  @brief 获取远程视频列表
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] path 视频文件的相对路径
*  @param [OUT] buf xml格式的文件列表，缓冲区长度不小于65536
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSdVideoFileList(int iUserID, char* path, char* buf);

//升级
/**
*  @brief 获得升级文件版本号
*  @param [IN] file_path_name 升级文件路径
*  @param [OUT] ver1 版本号1
*  @param [OUT] ver2 版本号2
*  @param [OUT] ver3 版本号3
*  @param [OUT] ver4 版本号4
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetUpdateFileVersion(char *file_path_name, int &ver1, int &ver2, int &ver3, int &ver4);

/**
*  @brief 开始升级
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] file_path_name 升级文件路径
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_Update(int iUserID, char *file_path_name);



/**
*  @brief 获取升级的状态
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 升级的状态
*			0: 还未升过级
*			1: 升级成功
*			2: 正在升级，上传中，可以取消升级
*			3: 正在升级，写flash中，取消升级不可用
*		    4: 网络问题，状态未知
*		   -1: 升级失败
*			失败或者网络问题时可以通过getlasterror获得升级错误信息，定义在UPDATE_ERROR里
*/
VZC_DLL_EXP int __stdcall VZC_GetUpdateState(int iUserID);

/**
*  @brief 取消升级，当升级状态在2时，可以取消升级，其余时候无用途
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_StopUpdate(int iUserID);

/**
*  @brief 获取升级进度，上传完毕为50，升级完成为100，当前会从50直接跳到100，中间进度不会更新，以后解决
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetUpdateProgress(int iUserID);

/**
*  @brief 清除升级状态，升级完成获得错误代码后调用，在再次升级前必须调用一次
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_ClearUpdateState(int iUserID);
#ifdef UPDATECALLBACK
//升级回调函数，可以获得当前的升级状态，当升级进度变化时，SDK会调用该函数，userp为用户自定义参数
//当升级状态在 UPDATE_STATE_UPLOAD时，如果该函数返回true,可以取消升级，其余时候函数返回值无用途
typedef	bool (*VZF_UpdateCallBack) (int upload_percent, int download_percent, 
										 UPDATE_STATE state,UPDATE_ERROR error,void* userp);
VZC_DLL_EXP int __stdcall VZC_SetUpdateProgressCallback(int iUserID,VZF_UpdateCallBack Function,void* userp);
#endif

/**
*  @brief 检测转发服务路径状态
*  @param [IN] trans 转发服务器地址列表
*  @param [IN] nTrans_num 转发层数
*  @param [OUT] timeMS 连接延迟
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP	int _stdcall VZC_PingTransimitServer(VZ_Transmit_Server **trans,int nTrans_num,int & timeMS);


/**
*  @brief 获取SDK错误代码
*  @return 返回值详见ERROR define
*/
VZC_DLL_EXP int __stdcall VZC_GetLastError();

/**
*  @brief 获取设备硬件信息
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] status 状态 0 没有取得硬件信息，1有基本信息，2有基本和扩展信息
*  @param [OUT] mac 输出mac地址，输入字符串缓冲长度至少为20
*  @param [OUT] serialno 输出序列号，输入字符串缓冲长度至少为20
*  @param [OUT] device_type 设备类型，参考IVS_TYPE定义
*  @param [OUT] pdata_ex 扩展硬件信息，参考fs_info_ex定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetHwInfo(int iUserID, int* status, char* mac, char* serialno,IVS_TYPE *device_type,fs_info_ex *pdata_ex);

/**
*  @brief 在线设备搜索回调函数定义
*  @param [IN] devName 设备名
*  @param [IN] ipaddr 设备ip
*  @param [IN] port1 http端口
*  @param [IN] port2 rtsp端口
*  @param [IN] type 设备类型
*  @param [IN] pUser 用户自定义指针
*/
typedef void (CALLBACK * VZDEV_CallBackAddDevice)(char * devName,char * ipaddr, int port1,int port2,int type,void * pUser);

/**
*  @brief 注册设备搜索回调函数
*  @param [IN] VZDEV_CallBackAddDevice 函数指针
*  @param [IN] pUsr用户参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_RegSearchOnlineCallback(VZDEV_CallBackAddDevice,void * pUsr);


/**
*  @brief 开始搜索在线设备
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_StartSearchDevice();

/**
*  @brief 停止搜索在线设备
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_StopSearchDevice();
//-----------------------------------------------------------------------------

/**
*  @brief 获取远程连接客户端信息
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] pConnectedClients 详见VzConnectedClients结构定义
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int VZC_GetConnectedClientInfo(int iUserID, VzConnectedClients *pConnectedClients);

//中心服务器

/**
*  @brief 初始化中心服务器
*  @param [IN] servername 中心服务器地址
*  @param [IN] port 中心服务器端口
*  @param [IN] name 用户名
*  @param [IN] pass 密码
*  @param [IN] groups 用户组
*  @param [IN] group_num 用户组数组长度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_InitCenterServer(char* servername,WORD port, char *name, char *pass, int *groups, int group_num);

/**
*  @brief 获取中心服务器设备信息
*  @param [OUT] device_info 设备信息
*  @param [OUT] device_group 设备分组信息
*  @param [OUT] trans_server 设备转发信息
*  @param [IN] buf_len 输入的buffer长度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_CenterServerGetXml(char* device_info,char* device_group, char *trans_server,int buf_len);

/**
*  @brief 获取中心服务器设备信息
*  @param [OUT] user_right 用户权限信息
*  @param [IN] buf_len 输入的buffer长度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_CenterGetRightXml(char *user_right, int buf_len);

/**
*  @brief 设备中心服务器设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] hostname 中心服务器地址
*  @param [IN] port  中心服务器端口
*  @param [IN] enable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetDeviceCenterServerParam(int iUserID, char* hostname,WORD port, int enable);

/**
*  @brief 获取设备中心服务器设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] hostname 中心服务器地址
*  @param [OUT] port  中心服务器端口
*  @param [OUT] enable 是否开启
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetDeviceCenterServerParam(int iUserID, char* hostname,WORD &port, int &enable);

//ftp
/**
*  @brief 获取设备ftp设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] ftp_cfg ftp配置信息，参考VZDEV_FTPCFG
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetFtpConfig(int iUserID, VZDEV_FTPCFG *ftp_cfg);

/**
*  @brief 设备ftp设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] ftp_cfg ftp配置信息，参考VZDEV_FTPCFG
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetFtpConfig(int iUserID, VZDEV_FTPCFG *ftp_cfg);

//sd卡

/**
*  @brief 是否支持sd卡
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] bSupport 0不支持，1支持
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IsSdSupported(int iUserID, int *bSupport);

#define VZ_SD_STATUS_INSERTED 0x01		///< sd卡已插入
#define VZ_SD_STATUS_MOUNTED 0x10		///< sd卡已加载

/**
*  @brief sd卡状态获取
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] status 为VZ_SD_STATUS_INSERTED 和 VZ_SD_STATUS_MOUNTED 的按位组合
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetSdStatus(int iUserID,int *status);

//gio directout0

/**
*  @brief GIO直通输出的状态获取
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] gio_output gio状态
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_GetGioDirectOut0(int iUserID, bool *gio_output);

/**
*  @brief GIO直通输出的状态设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] gio_output gio状态
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_SetGioDirectOut0(int iUserID, bool gio_output);

/**
*  @brief 给算法程序发送数据
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pIvsCtrl 参考VZ_IVS_CTRL结构体
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SendCtrlData(int iUserID, VZ_IVS_CTRL *pIvsCtrl);

/**
*  @brief 获取ivsctrl数据
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [INOUT] pIvsCtrl 参考VZ_IVS_CTRL结构体
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetCtrlData(int iUserID, VZ_IVS_CTRL *pIvsCtrl);

//GetSDKVersion
//VZC_DLL_EXP int __stdcall VZC_GetSDKVersion();
//VZC_DLL_EXP int __stdcall VZC_GetSDKBuildVersion();
//VZC_DLL_EXP int __stdcall VZC_SetUserPassword(int iUserID, char *oldpass, char *newpass);


/**
*  @brief 获取设备类型名称
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] device_type_name 设备类型名称
*  @param [IN] max_len device_type_name的最大可用长度
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetDeviceTypeName(int iUserID,char* device_type_name,int max_len);

#endif
