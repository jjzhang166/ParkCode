/*////////////////////////////////////////////////////////////////////////////////
// JVSDK.h
// JVSDK 动态连接库的导出头文件，应用程序应包含此头文件
// 济南中维世纪科技有限公司
// 2010年02月26日最后更新
// JVSDK包含采集卡的初始化、预览、压缩、参数设置等功能，为上层应用程序提供二次开发
// 该SDK采用C编译，在C++下使用时需要extern "C"{}
//////////////////////////////////////////////////////////////////////////////////*/

#ifndef		_JVSDK_H
#define		_JVSDK_H

#define JVSDK_API extern "C" __declspec(dllexport)

typedef void  (*CALLBACK_ENC_DATA)(int nChannel, PUCHAR pData, UINT nBuffLen, int nFrameType, BOOL bMov);
typedef void  (*CALLBACK_RAW_DATA)(int nChannel, PUCHAR pRawBuffer, DWORD dwVideo, DWORD dwHD1);

//SDK通知消息：
#define	JVS_WM_BITMAP_OK	0x01		//抓图完成
#define JVS_WM_COPYRIGHT	0x02		//通过版权验证

//帧类型
#define JVS_TYPE_P			0x00		
#define JVS_TYPE_IDR		0x01
#define JVS_TYPE_AUD		0x02
#define JVS_TYPE_SKIP		0x03
#define JVS_TYPE_D			0x04


typedef struct _JVS_FILE_HEADER
{
	DWORD	dwFLAGS;			//中维录像文件头标志字段
	DWORD	dwFrameWidth;		//帧宽
	DWORD	dwFrameHeight;		//帧高
	DWORD	dwTotalFrames;		//总帧数
	DWORD	dwVideoFormat;		//源视频格式：0表示PAL，1表示NTSC
	DWORD	bThrowFrame;		//是否抽帧：0表示不抽帧，1表示抽帧（互联网模式）
	DWORD	dwReserved1;		//保留字段
	DWORD	dwReserved2;		//保留字段
} JVS_FILE_HEADER, *PJVS_FILE_HEADER;

typedef struct _JVS_CARD_INFO
{
	DWORD	dwCardType;		//卡类型
	DWORD	dwGroup;		//编组号
	DWORD	dwSerialNum;	//序列号
	DWORD	dwDateTime;		//出厂日期
	DWORD	dwGUID[4];		//GUID，共16字节
} JVS_CARD_INFO, *PJVS_CARD_INFO;


/////////////////////////////初始化和释放SDK资源////////////////////////////////////
JVSDK_API	int		__stdcall	JVS_InitSDK();
JVSDK_API	void	__stdcall	JVS_ReleaseSDK();

////////////////////////////////打开通道前的综合设置////////////////////////////////
//注册压缩数据处理的回调函数
JVSDK_API	void	__stdcall	JVS_SetCallBack(CALLBACK_ENC_DATA cbEncData, CALLBACK_RAW_DATA cbRawData);
//设置无视频信号时SDK输出的图片
JVSDK_API	void	__stdcall	JVS_SetNoSignalFile(char * szBmpCIF);
//注册SDK通知事件
JVSDK_API	void	__stdcall	JVS_RegisterNotify(HWND hWnd, DWORD dwNotifyMsg);


//////////////////////////////////打开与关闭通道/////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_OpenChannel(int nChannel);		//打开通道，从0通道开始
JVSDK_API	void	__stdcall	JVS_CloseChannel(int nChannel);		//关闭通道，从0通道开始


//////////////////////////////////针对通道的综合设置////////////////////////////////
//设置视频捕获分辨率模式
JVSDK_API	void	__stdcall	JVS_SetVideoPixelMode(int nChannel, DWORD dwPixelMode, DWORD dwVideoFormat);
//开启捕获
JVSDK_API	void	__stdcall	JVS_StartCapture(int nChannel);


//////////////////////////////////////////预览////////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_InitPreview();
JVSDK_API	void	__stdcall	JVS_ReleasePreview();
JVSDK_API	BOOL	__stdcall	JVS_SetVideoPreview(int nChannel, HWND hWnd, RECT * rt, BOOL bPreview);
JVSDK_API	BOOL	__stdcall	JVS_SetAudioPreview(int nChannel, HWND hWnd, BOOL bPreview);


////////////////////////////////////////压缩//////////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_InitCompress();
JVSDK_API	void	__stdcall	JVS_ReleaseCompress();
JVSDK_API	BOOL	__stdcall	JVS_StartCompress ( int nChannel );	//开始压缩
JVSDK_API	void	__stdcall	JVS_StopCompress( int nChannel, BOOL bWaitForStop );
//设置压缩模式
JVSDK_API	void	__stdcall	JVS_SetQualityMode(int nChannel, DWORD dwQualityMode, DWORD dwMBPH);
JVSDK_API	void	__stdcall	JVS_SetKeyFramePeriod(int nChannel, DWORD dwKeyFramePeriod);
JVSDK_API	void	__stdcall	JVS_InsertKeyFrame(int nChannel);
JVSDK_API	BOOL	__stdcall	JVS_SetAudioCompress(int nChannel, BOOL bCompress);
//获取压缩文件头数据
JVSDK_API	BOOL	__stdcall	JVS_GetHeaderData(int nChannel, PJVS_FILE_HEADER pheaderData);


////////////////////////////////////////抓图//////////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_GetBitmapSize(int nChannel, DWORD * dwWidth, DWORD * dwHeight);
JVSDK_API	BOOL	__stdcall	JVS_GetBitmap(int nChannel, PUCHAR pBuffer);
JVSDK_API	BOOL	__stdcall	JVS_GetBitmapToFile(int nChannel, PUCHAR pCapBmpFile);


///////////////////////////////////////移动检测//////////////////////////////////////
JVSDK_API	void	__stdcall	JVS_SetMovDetect(int nChannel, int nScenecutGrade, int nScenecutThreshold, int nScenecutCoeff, int nRectNumber, RECT * pScenecutRect);


//////////////////////////////////////视频设置////////////////////////////////////////
JVSDK_API	void	__stdcall	JVS_SetOSD(int nChannel, DWORD dwOsdMode, PUCHAR pText, BOOL bEnable);
JVSDK_API	void	__stdcall	JVS_SetVideoPara(int nChannel, int nBrightness, int nContrast, int nSatuation, int nHue);
JVSDK_API	void	__stdcall	JVS_EnablePreviewHD1(int nChannel, BOOL bEnableD1);
JVSDK_API	void	__stdcall	JVS_EnableLowConfig(int nChannel, BOOL bLowCfg);
JVSDK_API	void	__stdcall	JVS_EnableVideoClean(int nChannel, BOOL bVideoClean);

//设置视频遮挡区域
JVSDK_API	void	__stdcall	JVS_SetVideoMask(int nChannel, BOOL bEnableMask, int nMaskX, int nMaskY, int nWidth, int nHeight);
JVSDK_API	void	__stdcall	JVS_SetVideoCrop(int nChannel, DWORD dwPixelCroped);


///////////////////////////////////////音频设置///////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_SetVolume(int nChannel, DWORD dwVolume);


///////////////////////////////////////板卡信息///////////////////////////////////////
JVSDK_API	BOOL	__stdcall	JVS_GetCardInfo(int nChannel, PJVS_CARD_INFO pCardInfo);




#endif