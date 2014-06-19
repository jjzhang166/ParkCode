// sdk3000_7130.h : main header file for the SDK3000_7130 DLL
//

#if !defined(AFX_SDK3000_7130_H__37FDA63D_0A84_4797_9E52_320E37C41382__INCLUDED_)
#define AFX_SDK3000_7130_H__37FDA63D_0A84_4797_9E52_320E37C41382__INCLUDED_


static const ULONG BrightnessDefault = 0x80;
static const ULONG ContrastDefault   = 0x44;
static const ULONG SaturationDefault = 0x40;
static const ULONG HueDefault        = 0x00;
static const ULONG SharpnessDefault  = 0x00;

#define MIN_VAMP_BRIGHTNESS_UNITS    0
#define MAX_VAMP_BRIGHTNESS_UNITS  255

#define MIN_VAMP_CONTRAST_UNITS   -128 
#define MAX_VAMP_CONTRAST_UNITS    127 

#define MIN_VAMP_HUE_UNITS        -128
#define MAX_VAMP_HUE_UNITS         127

#define MIN_VAMP_SATURATION_UNITS -128 
#define MAX_VAMP_SATURATION_UNITS  127

#define MIN_VAMP_SHARPNESS_UNITS    -8
#define MAX_VAMP_SHARPNESS_UNITS     7

//图像格式
typedef enum
{
	IMAGE_BMP = 1,	//BMP文件格式			
	IMAGE_JPG = 2   //JPG文件格式
}enImageType;

//输入视频源端口
typedef enum
{               
    VIDEO_IN_1 = 0, //AV视频源1
    VIDEO_IN_2 = 1, //AV视频源2          
    VIDEO_IN_3 = 2, //AV视频源3
	VIDEO_IN_4 = 3, //AV视频源4
	SVIDEO_IN  = 4  //SVIDEO视频源
}VIDEOSOURCE;

//视频处理属性
typedef enum tagVideoProcAmpProperty
{	
	VideoProcAmp_Brightness				= 0,
	VideoProcAmp_Contrast				= VideoProcAmp_Brightness + 1,
	VideoProcAmp_Hue					= VideoProcAmp_Contrast + 1,
	VideoProcAmp_Saturation				= VideoProcAmp_Hue + 1,
	VideoProcAmp_Sharpness				= VideoProcAmp_Saturation + 1,
	VideoProcAmp_Gamma					= VideoProcAmp_Sharpness + 1,
	VideoProcAmp_ColorEnable			= VideoProcAmp_Gamma + 1,
	VideoProcAmp_WhiteBalance			= VideoProcAmp_ColorEnable + 1,
	VideoProcAmp_BacklightCompensation	= VideoProcAmp_WhiteBalance + 1,
	VideoProcAmp_Gain					= VideoProcAmp_BacklightCompensation + 1
}VideoProcAmpProperty;

//视频属性
typedef enum
{
	VideoProperty_Brightness				= VideoProcAmp_Brightness,		//亮度
	VideoProperty_Contrast					= VideoProcAmp_Contrast,		//对比度
	VideoProperty_Hue						= VideoProcAmp_Hue,				//色度
	VideoProperty_Saturation				= VideoProcAmp_Saturation,		//饱和度
	VideoProperty_Gamma						= VideoProcAmp_Gamma,			//Gamma校验
	VideoProperty_ColorEnable				= VideoProcAmp_ColorEnable,
	VideoProperty_WhiteBalance				= VideoProcAmp_WhiteBalance,	//白平衡
	VideoProperty_BacklightCompensation		= VideoProcAmp_BacklightCompensation,
	VideoProperty_Sharpness					= VideoProcAmp_Sharpness,
	VideoProperty_Gain						= VideoProcAmp_Gain,
} VideoProperty;

//SDK3000属性页
typedef enum
{
	PropertyDlg_VideoCaptureFilter = 0,//SDK3000视频设备属性页 
	PropertyDlg_VideoCapturePin,	   //SDK3000视频设备输出引脚属性页
	PropertyDlg_VideoCrossbar,		   //Video Crossbar属性页
	PropertyDlg_DeinterlaceFilter,		//Deinterlace设备属性页
	PropertyDlg_DeinterlaceCapturePin,	//Deinterlace设备捕获引脚属性页
	PropertyDlg_DeinterlacePreviewPin	//Deinterlace设备预览引脚属性页
} PropertyDialog;

//视频运行状态
typedef enum{
	STATE_STOP	= 0,
	STATE_RUN,
	STATE_PAUSE
}GRAPH_STATE;

//视频格式
//VideoSubType_YUY2格式支持SDK3000所有功能。
//视频制式除VideoSubType_YUY2外，只能支持视频原始回调方式。
typedef enum
{
	VideoSubType_None	= -1,
	VideoSubType_RGB555 = 0,
	VideoSubType_RGB24,
	VideoSubType_YUY2,
	VideoSubType_RGB8,
	VideoSubType_RGB32
} VideoSubType;

//视频制式
typedef enum
{
	VideoStandard_None		= 0x00000000,
	VideoStandard_NTSC_M	= 0x00000001, 
	VideoStandard_NTSC_M_J	= 0x00000002,  
	VideoStandard_NTSC_433	= 0x00000004,
	VideoStandard_PAL_B		= 0x00000010,
	VideoStandard_PAL_D		= 0x00000020,
	VideoStandard_PAL_H		= 0x00000080,
	VideoStandard_PAL_I		= 0x00000100,
	VideoStandard_PAL_M		= 0x00000200,
	VideoStandard_PAL_N		= 0x00000400,
	VideoStandard_PAL_60	= 0x00000800,
	VideoStandard_SECAM_B	= 0x00001000,
	VideoStandard_SECAM_D	= 0x00002000,
	VideoStandard_SECAM_G	= 0x00004000,
	VideoStandard_SECAM_H	= 0x00008000,
	VideoStandard_SECAM_K	= 0x00010000,
	VideoStandard_SECAM_K1	= 0x00020000,
	VideoStandard_SECAM_L	= 0x00040000,
	VideoStandard_SECAM_L1	= 0x00080000,
} VideoStandard;

//场类型
typedef enum
{
	Even_Field = 0, //偶场
	Odd_Field,		//奇场
	Odd_Even_Field, //奇场、偶场
	Interlaced_Field//复合场
}VideoFieldType;

//视频叠加参数
typedef struct
{
	LONG		cfHeight;		//字符高度
	LONG		cfWidth;		//字符宽度
	LONG		cfWeight;		//字符粗细
	LONG		cfSpacing;		//字符间距
	BOOL		cfItalic;		//斜体
	BOOL		cfUnderline;	//下划线
	BOOL		cfStrikeOut;	//删除线
	COLORREF	cfBkColor;		//背景色 
	COLORREF	cfTextColor;	//前景色
	TCHAR		cfFaceName[32];	//字体名
}OSDPARAM;

//视频属性范围
typedef struct 
{
	long nValue;		//当前值
	long nMin;			//最小值
	long nMax;			//最大值
	long nStepDelta;	//最小步进值
	long nDefault;		//默认值
	long nCapsFlags;	//风格
} VIDEOPROPERTYRANGE;

//视频流信息
typedef struct
{
	VideoSubType		subtype;        //视频格式
	RECT				rcSource;       //视频源范围
	RECT				rcTarget;		//目标视频范围
	DWORD				dwBitRate;      //比特率
	DWORD				dwBitErrorRate; //比特错误率
	LONGLONG			AvgTimePerFrame;//帧率
	BITMAPINFOHEADER	bmiHeader;		//宽、高、颜色位率等
} VIDEOSTREAMINFO;

//视频源输入频率
typedef enum  
{          //@enum Field frequency
    FIELD_FREQ_50HZ = 0,        //@emem source is 50 Hz (PAL)
    FIELD_FREQ_60HZ = 1,        //@emem source is 60 Hz (NTSC)
    FIELD_FREQ_0HZ  = 2         //@emem source is 0 Hz   (NO SIGNL)
}eFieldFrequency;


//动态检测回调
typedef void (CALLBACK *PrcCbMotionDetect)( long lnCardID, BOOL bMove, LPVOID lpContext );
//捕获原始流回调
typedef void (CALLBACK *PrcCapSourceStream)( long lnCardID, long pBuf, long lnWidth, long lnHeight, long lnBiCount );
//IO报警回调
typedef void (CALLBACK *PrcIoAlertCallBack)( long lnCardID );
typedef void (CALLBACK *PrcPicMessage)( long lnCardID, long pBuf, long lnWidth, long lnHeight);
//初始化SDK
HRESULT WINAPI VCAInitSdk();
//释放SDK资源
void WINAPI VCAUnInitSdk();
//得到SDK3000设备总数
HRESULT WINAPI VCAGetDevNum(int *pDevNum);
//连接设备
HRESULT	WINAPI VCAConnectDevice(int nCards, BOOL bOverlay, HWND hParentWnd, SIZE& szVidSize, VIDEOSOURCE enVideoSource, int nFrameRate = 25, VideoSubType enVideoSubType = VideoSubType_YUY2);
//断开设备
HRESULT WINAPI VCADisConnectDevice(int nCards);
//设置捕获文件名
HRESULT	WINAPI VCASetCaptureFile(int nCards, LPCTSTR szFileName);
//开始捕获
HRESULT	WINAPI VCAStartCapture(int nCards);
//停止捕获
HRESULT	WINAPI VCAStopCapture(int nCards);
//是否正在捕获
HRESULT	WINAPI VCAIsCapturing(int nCards, BOOL* bIsCapturing);
//设置视频在显示窗口中的区域
HRESULT WINAPI VCASetWindowPos(int nCards, RECT rc);
//设置动态检测
HRESULT WINAPI VCAEnableMotionDetect(int nCards, BOOL bEnaDetect, BYTE *pAreaMap, LONG nSizeOfMap, LONG nPersistTime, LPVOID lpContext, PrcCbMotionDetect OnObjectMove);
//抓图
HRESULT WINAPI VCACapturePicture(int nCards, LPCTSTR szFileName, enImageType enImgType, RECT* rcImg, long nQuality, long nCapCount, BOOL bCapFast );
//切换视频源
HRESULT WINAPI VCASwitchVideoSource(int nCards, VIDEOSOURCE enVideoSource, BOOL bFast = TRUE );
//设置视频属性
HRESULT WINAPI VCASetVideoPropertyValue(int nCards, VideoProperty eVideoProperty, long value);
//得到视频属性
HRESULT WINAPI VCAGetVideoPropertyValue(int nCards, VideoProperty eVideoProperty, VIDEOPROPERTYRANGE* pVPR);
//IO输出
HRESULT WINAPI VCAIOAlertOut(int nCards, BOOL bHighLevel);
//初始化IO输入
HRESULT WINAPI VCAInitIOAlertIn(int nCards, PrcIoAlertCallBack ppCall);
//开始等待IO输入
HRESULT WINAPI VCAStartIOAlertIn(int nCards, BOOL bHigh);
//停止等待IO输入
HRESULT WINAPI VCAStopIOAlertIn(int nCards);
//设置文本叠加
HRESULT WINAPI VCASetTextOSD(int nCards, BOOL bEnableOSD, TCHAR* pText, POINT ptTopLeft, BOOL bTransparent, OSDPARAM* pOSD,  HWND nWndMain);
//设置时间叠加
HRESULT WINAPI VCASetDateTimeOSD(int nCards, BOOL bEnableOSD, POINT ptTopLeft, BOOL bTransparent, OSDPARAM* pOSD,  HWND nWndMain);
//显示属性页对话框
HRESULT WINAPI VCADisplayPropertyDialogs(int nCards, PropertyDialog id, HWND hParentWnd, LPCTSTR szCaption);
//运行视频流
HRESULT WINAPI VCARun(int nCards);
//暂停视频流
HRESULT WINAPI VCAPause(int nCards);
//停止视频流
HRESULT WINAPI VCAStop(int nCards);
//得到视频流状况
HRESULT WINAPI VCAGetStreamStatus(int nCards, GRAPH_STATE* pStatus);
//设置视频帧率
HRESULT WINAPI VCASetFrameRate(int nCards, int nFrameRate);
//得到视频信息
HRESULT WINAPI VCAGetVideoInfo(int nCards, VIDEOSTREAMINFO * pVSI);
//设置视频信息
HRESULT WINAPI VCASetVideoInfo(int nCards, VIDEOSTREAMINFO * pVSI);
//设置视频大小为全屏
HRESULT WINAPI VCASetFullScreen(int nCards, BOOL bFullSrc);
//是否视频为全屏模式
HRESULT WINAPI VCAIsFullSrcMode(int nCards, BOOL* pFullSrc);
//得到视频制式
HRESULT WINAPI VCAGetVideoStandard(int nCards, VideoStandard* pVideoStandard, long* pAvailable);
//设置视频制式
HRESULT WINAPI VCASetVideoStandard(int nCards, VideoStandard vs);
//枚举视频压缩格式
HRESULT WINAPI VCAEnumVideoCompressor(int nCards, char* arrCompDevName,int * pCompDevCount);
//得到视频当前压缩格式
HRESULT WINAPI VCAGetCurrentVideoCompressor(int nCards, LPSTR pCompDevName);
//枚举视频当前压缩格式
HRESULT WINAPI VCASetCurrentVideoCompressor(int nCards, LPCTSTR pCompDevName);
//设置视频原始回调格式
HRESULT WINAPI VCAEnableCapSourceStream(int nCards, BOOL bCapStream, VideoFieldType enVideoFieldType, PrcCapSourceStream pCapStream);
//
HRESULT WINAPI VCAEnablePicMessage(int nCards, BOOL bPicMessage, PrcPicMessage pPicMessage);
//读E2C
HRESULT WINAPI VCAReadE2C(int nCards, int iSubAddr, BYTE* pucData);
//写E2C
HRESULT WINAPI VCAWriteE2C(int nCards, int iSubAddr, BYTE ucData);
//得到视频源输入频率( 0HZ / 50HZ / 60HZ )对应( 无信号 / PAL制 / NTSC制 ), 参考枚举变量eFieldFrequency
HRESULT WINAPI VCAGetVideoFieldFrq(int nCards, eFieldFrequency* pFieldFrequency);
//枚举音频设备
HRESULT WINAPI VCAEnumAudioCaptureDev(int nCards, char* arrAudDevName,int * pAudDevCount);
//通过音频设备名设置音频采集,一个音频设备(声卡)仅供一路卡, strAudDevName 为"",表示取消音频采集
HRESULT WINAPI VCASetCurrentAudioCompressorName(int nCards, LPCTSTR strAudDevName);
//通过音频设备序号设置音频采集,一个音频设备(声卡)仅供一路卡, nCurrentAudDevice 为-1,表示取消音频采集
HRESULT WINAPI VCASetCurrentAudioCompressorNum(int nCards, int nCurrentAudDevice);
/////////////////////////////////////////////////////////////////////////////

//	拷贝图像数据到剪贴板
HRESULT WINAPI VCACopyToClipBoard(int nCards);
//	检测是否按Overlay方式显示
HRESULT	WINAPI VCAIsOverlay(int nCards, BOOL* bIsOverlay);


#endif // !defined(AFX_SDK3000_7130_H__37FDA63D_0A84_4797_9E52_320E37C41382__INCLUDED_)
