//用于接入VZ的车牌识别设备（包括智能识别一体机和智能识别终端等）的应用程序接口
#ifndef _VZ_LPRC_SDK_H_
#define _VZ_LPRC_SDK_H_

#include "VzLPRClientSDKDefine.h"

#ifdef _DEV_API_
#define VZ_LPRC_API extern "C" __declspec(dllexport)
#else
#define VZ_LPRC_API extern "C" __declspec(dllimport)
#endif

/**
* @defgroup group_global 全局操作函数
* @defgroup group_device 单个设备操作函数
*/

/**
*  @brief 全局初始化
*  @return 0表示成功，-1表示失败
*  @note 在所有接口调用之前调用
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VzLPRClient_Setup();

/**
*  @brief 全局释放
*  @note 在程序结束时调用，释放SDK的资源
*  @ingroup group_global
*/
VZ_LPRC_API void __stdcall VzLPRClient_Cleanup();

/**
*  @brief 通过该回调函数获得找到的设备基本信息
*  @param  [IN] pStrDevName 设备名称
*  @param  [IN] pStrIPAddr	设备IP地址
*  @param  [IN] usPort1		设备端口号
*  @param  [IN] usPort2		预留
*  @param  [IN] pUserData	回调函数上下文
*  @ingroup group_global
*/
typedef void (__stdcall *VZLPRC_FIND_DEVICE_CALLBACK)(const char *pStrDevName, const char *pStrIPAddr, WORD usPort1, WORD usPort2, void *pUserData);

/**
*  @brief 开始查找设备
*  @param  [IN] func 找到的设备通过该回调函数返回
*  @param  [IN] pUserData 回调函数中的上下文
*  @return 0表示成功，-1表示失败
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VZLPRClient_StartFindDevice(VZLPRC_FIND_DEVICE_CALLBACK func, void *pUserData);

/**
*  @brief 停止查找设备
*  @ingroup group_global
*/
VZ_LPRC_API void __stdcall VZLPRClient_StopFindDevice();

/**
*  @brief 通过该回调函数获得设备的一般状态信息
*  @param  [IN] handle		由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pUserData	回调函数上下文
*  @param  [IN] eNotify		通用信息反馈类型
*  @param  [IN] pStrDetail	详细描述字符串
*  @ingroup group_global
*/
typedef void (__stdcall *VZLPRC_COMMON_NOTIFY_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													   VZ_LPRC_COMMON_NOTIFY eNotify, const char *pStrDetail);

/**
*  @brief 设置设备连接反馈结果相关的回调函数
*  @param  [IN] func 设备连接结果和状态，通过该回调函数返回
*  @param  [IN] pUserData 回调函数中的上下文
*  @return 0表示成功，-1表示失败
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VZLPRClient_SetCommonNotifyCallBack(VZLPRC_COMMON_NOTIFY_CALLBACK func, void *pUserData);

/**
*  @brief 打开一个设备
*  @param  [IN] pStrIP 设备的IP地址
*  @param  [IN] wPort 设备的端口号
*  @param  [IN] pStrUserName 访问设备所需用户名
*  @param  [IN] pStrPassword 访问设备所需密码
*  @return 返回设备的操作句柄，当打开失败时，返回0
*  @ingroup group_device
*/
VZ_LPRC_API VzLPRClientHandle __stdcall VzLPRClient_Open(const char *pStrIP, WORD wPort, const char *pStrUserName, const char *pStrPassword);

/**
*  @brief 关闭一个设备
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_Close(VzLPRClientHandle handle);

/**
*  @brief 通过IP地址关闭一个设备
*  @param  [IN] pStrIP 设备的IP地址
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_CloseByIP(const char *pStrIP);

/**
*  @brief 获取连接状态
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN/OUT] pStatus 输入获取状态的变量地址，输出内容为 1已连上，0未连上
*  @return 0表示成功，-1表示失败
*  @note   用户可以周期调用该函数来主动查询设备是否断线，以及断线后是否恢复连接
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_IsConnected(VzLPRClientHandle handle, BYTE *pStatus);

/**
*  @brief 播放实时视频
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] hWnd 窗口的句柄
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StartRealPlay(VzLPRClientHandle handle, void *hWnd);

/**
*  @brief 停止正在播放的窗口上的实时视频
*  @param  [IN] hWnd 窗口的句柄
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_StopRealPlay(void *hWnd);

/**
*  @brief  通过该回调函数获得实时图像数据
*  @param  [IN] handle		由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pUserData	回调函数的上下文
*  @param  [IN] pFrame		图像帧信息，详见结构体定义VzYUV420P
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
typedef void (__stdcall *VZLPRC_VIDEO_FRAME_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													  const VzYUV420P *pFrame);
/**
*  @brief 设置实时图像数据的回调函数
*  @param  [IN] handle		由VzLPRClient_Open函数获得的句柄
*  @param  [IN] func		实时图像数据函数
*  @param  [IN] pUserData	回调函数中的上下文
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetVideoFrameCallBack(VzLPRClientHandle handle, VZLPRC_VIDEO_FRAME_CALLBACK func, void *pUserData);

/**
*  @brief 通过该回调函数获得车牌识别信息
*  @param  [IN] handle			由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pUserData		回调函数的上下文
*  @param  [IN] pResult			车牌信息数组首地址，详见结构体定义 TH_PlateResult
*  @param  [IN] uNumPlates		车牌数组中的车牌个数
*  @param  [IN] eResultType		车牌识别结果类型，详见枚举类型定义VZ_LPRC_RESULT_TYPE
*  @param  [IN] pImgFull		当前帧的图像内容，详见结构体定义VZ_LPRC_IMAGE_INFO
*  @param  [IN] pImgPlateClip	当前帧中车牌区域的图像内容数组，其中的元素与车牌信息数组中的对应
*  @return 0表示成功，-1表示失败
*  @note   如果需要该回调函数返回截图内容 pImgFull 和pImgPlateClip，需要在设置回调函数（VzLPRClient_SetPlateInfoCallBack）时允许截图内容，否则该回调函数返回的这两个指针为空；
*  @note   实时结果（VZ_LPRC_RESULT_REALTIME）的回调是不带截图内容的
*  @ingroup group_device
*/
typedef int (__stdcall *VZLPRC_PLATE_INFO_CALLBACK)(VzLPRClientHandle handle, void *pUserData,
													const TH_PlateResult *pResult, unsigned uNumPlates,
													VZ_LPRC_RESULT_TYPE eResultType,
													const VZ_LPRC_IMAGE_INFO *pImgFull,
													const VZ_LPRC_IMAGE_INFO *pImgPlateClip);

/**
*  @brief 设置识别结果的回调函数
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] func 识别结果回调函数，如果为NULL，则表示关闭该回调函数的功能
*  @param  [IN] pUserData 回调函数中的上下文
*  @param  [IN] bEnableImage 指定识别结果的回调是否需要包含截图信息：1为需要，0为不需要
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetPlateInfoCallBack(VzLPRClientHandle handle, VZLPRC_PLATE_INFO_CALLBACK func, void *pUserData, int bEnableImage);

/**
*  @brief 发送软件触发信号，强制处理当前时刻的数据并输出结果
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @return 0表示成功，-1表示失败
*  @note   车牌识别结果通过回调函数的方式返回，如果当前视频画面中无车牌，则回调函数不会被调用
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_ForceTrigger(VzLPRClientHandle handle);

/**
*  @brief 设置虚拟线圈
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pVirtualLoops 虚拟线圈的结构体指针
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_SetVirtualLoop(VzLPRClientHandle handle, const VZ_LPRC_VIRTUAL_LOOPS *pVirtualLoops);

/**
*  @brief 获取已设置的虚拟线圈
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pVirtualLoops 虚拟线圈的结构体指针
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetVirtualLoop(VzLPRClientHandle handle,  VZ_LPRC_VIRTUAL_LOOPS *pVirtualLoops);

/**
*  @brief 获取已设置的预设省份
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] pProvInfo 预设省份信息指针
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSupportedProvinces(VzLPRClientHandle handle, VZ_LPRC_PROVINCE_INFO *pProvInfo);

/**
*  @brief 设置预设省份
*  @param  [IN] handle 由VzLPRClient_Open函数获得的句柄
*  @param  [IN] nIndex 设置预设省份的序号，序号需要参考VZ_LPRC_PROVINCE_INFO::strProvinces中的顺序，从0开始，如果小于0，则表示不设置预设省份
*  @return 0表示成功，-1表示失败
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_PresetProvinceIndex(VzLPRClientHandle handle, int nIndex);

/**
*  @brief 将图像保存为JPEG到指定路径
*  @param  [IN] pImgInfo 图像结构体，目前只支持默认的格式，即ImageFormatRGB
*  @param  [IN] pFullPathName 设带绝对路径和JPG后缀名的文件名字符串
*  @param  [IN] nQuality JPEG压缩的质量，取值范围1~100；
*  @return 0表示成功，-1表示失败
*  @note   给定的文件名中的路径需要存在
*  @ingroup group_global
*/
VZ_LPRC_API int __stdcall VzLPRClient_ImageSaveToJpeg(const VZ_LPRC_IMAGE_INFO *pImgInfo, const char *pFullPathName, int nQuality);

/**
*  @brief 保存正在播放的视频的当前帧的截图到指定路径
*  @param  [IN] hWnd 正在播放视频的窗口的句柄
*  @param  [IN] pFullPathName 设带绝对路径和JPG后缀名的文件名字符串
*  @param  [IN] nQuality JPEG压缩的质量，取值范围1~100；
*  @return 0表示成功，-1表示失败
*  @note   前提条件是指定的hWnd的窗口已经调用了VzLPRClient_StartRealPlay播放实时视频
*  @note   使用的文件名中的路径需要存在
*  @ingroup group_device
*/
VZ_LPRC_API int __stdcall VzLPRClient_GetSnapShootToJpeg(void *hWnd, const char *pFullPathName, int nQuality);

#endif
