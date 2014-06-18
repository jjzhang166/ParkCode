
#ifndef __LPRINTERFACE__
#define __LPRINTERFACE__

//车牌颜色
#define LC_UNKNOWN  0  //未知
#define LC_BLUE     1  //蓝色
#define LC_YELLOW   2  //黄色 
#define LC_WHITE    3  //白色
#define LC_BLACK    4  //黑色
#define LC_GREEN    5  //绿色

//车牌类型
#define LT_UNKNOWN  0   //未知车牌
#define LT_BLUE     1   //蓝牌小汽车
#define LT_BLACK    2   //黑牌小汽车
#define LT_YELLOW   3   //单排黄牌
#define LT_YELLOW2  4   //双排黄牌（大车尾牌，农用车）
#define LT_POLICE   5   //警车车牌
#define LT_ARMPOL   6   //武警车牌
#define LT_INDIVI   7   //个性化车牌
#define LT_ARMY     8   //单排军车牌
#define LT_ARMY2    9   //双排军车牌
#define LT_EMBASSY  10  //使馆车牌
#define LT_HONGKONG 11  //香港车牌
#define LT_TRACTOR  12  //农用车牌
	
//运动方向
#define DIRECTION_LEFT	1  //左
#define DIRECTION_RIGHT	2  //右
#define DIRECTION_UP	3  //上
#define DIRECTION_DOWN	4  //下

//图像格式（TH_SetImageFormat函数的cImageFormat参数）
#define ImageFormatRGB		0			//RGBRGBRGB...
#define ImageFormatBGR		1			//BGRBGRBGR...
#define ImageFormatYUV422	2			//YYYY...UU...VV..	(YV16)
#define ImageFormatYUV420COMPASS 3		//YYYY...UV...		(NV12)
#define ImageFormatYUV420	 4			//YYYY...U...V...	(YU12)
#define ImageFormatUYVY	    5			//UYVYUYVYUYVY...	(UYVY)
#define ImageFormatNV21		6			//YYYY...VU...		(NV21)
#define ImageFormatYV12		7			//YYYY...V...U		(YV12)

//车辆颜色
#define LGRAY_DARK	0	//深
#define LGRAY_LIGHT	1	//浅

#define LCOLOUR_WHITE	0	//白	
#define LCOLOUR_SILVER	1	//灰(银)
#define LCOLOUR_YELLOW	2	//黄
#define LCOLOUR_PINK	3	//粉
#define LCOLOUR_RED		4	//红
#define LCOLOUR_GREEN	5	//绿
#define LCOLOUR_BLUE	6	//蓝
#define LCOLOUR_BROWN	7	//棕 
#define LCOLOUR_BLACK	8	//黑
	
typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;

typedef struct TH_PlateResult 
{
	char license[16];   // 车牌号码
	char color[8];      // 车牌颜色
	int nColor;			// 车牌颜色序号
	int nType;			// 车牌类型
	int nConfidence;	// 车牌可信度
	int nBright;		// 亮度评价
	int nDirection;		// 运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down	
	TH_RECT rcLocation; //车牌位置
	int nTime;          //识别所用时间
	unsigned char nCarBright;		//车的亮度
	unsigned char nCarColor;		//车的颜色
	char reserved[100];				// 保留
}TH_PlateResult;

#ifdef __cplusplus
extern "C" {
#endif

/**************************************
LPR_SetParameters设置识别参数
参数：bMovingImage[in]            识别运动或静止图像
      nPlatesNum[in]              最多识别的车牌个数
	  bFlipVertical[in]           是否上下颠倒图像后识别
	  nColorOrder[in]             是否图像格式
	  bVertCompress[in]           是否垂直方向压缩一倍识别
	  nImageplateThr[in]          车牌定位阈值
	  nImageRecogThr[in]          车牌识别阈值
	  nMinPlateWidth[in]          最小车牌宽度
	  nMaxPlateWidth[in]          最大车牌宽度
	  LocalProvince[in]           默认省份
	  bDwordAligned[in]           是否四字节对齐
	  bInputHalfHeightImage[in]   是否输入场图像
	  bOutputSingleFrame[in]      是否只输出一个识别结果
	  bYellow2[in]                是否识别双层黄牌
	  bIndivi[in]                 是否识别个性化车牌
	  bArmPol[in]                 是否识别军牌
	  bArmy2[in]                  是否识别双层军牌
	  bTractor[in]                是否识别农用车牌 
	  bNight[in]                  是否是夜间模式	
	  nChannel[in]                通道号
***************************************/
BOOL WINAPI LPR_SetParameters(BOOL bMovingImage,
		int nPlatesNum,
		BOOL bFlipVertical, 
		int nColorOrder,
		BOOL bVertCompress,
		int nImageplateThr, int nImageRecogThr, 
		int nMinPlateWidth, int nMaxPlateWidth, 
		char *LocalProvince,
		BOOL bDwordAligned,
		BOOL bInputHalfHeightImage,    												   
		BOOL bOutputSingleFrame,
		BOOL bYellow2, BOOL bIndivi, BOOL bArmPol, BOOL bArmy2, BOOL bTractor, 
		BOOL bNight, 	
		int nChannel=1);

/**************************************
LPR_SetImageFormat设置图像格式。必须在调用LPR_InitEx之前设置
参数：bMovingImage[in]            识别运动或静止图像
	  bFlipVertical[in]           是否上下颠倒图像后识别
	  nColorOrder[in]             图像格式
	  bVertCompress[in]           是否垂直方向压缩一倍识别
	  nMinPlateWidth[in]          最小车牌宽度
	  nMaxPlateWidth[in]          最大车牌宽度
	  bDwordAligned[in]           是否四字节对齐
	  bInputHalfHeightImage[in]   是否输入场图像
	  bOutputSingleFrame[in]      是否只输出一个识别结果 	
	  nChannel[in]                通道号
***************************************/
BOOL WINAPI LPR_SetImageFormat(BOOL bMovingImage,		
		BOOL bFlipVertical, 
		int nColorOrder,
		BOOL bVertCompress, 
		int nMinPlateWidth, 
		int nMaxPlateWidth, 
		BOOL bDwordAligned,
		BOOL bInputHalfHeightImage,    												   
		BOOL bOutputSingleFrame,	
		int nChannel=1);

/**************************************
LPR_SetPlateType设置识别车牌类型。必须在调用LPR_InitEx之后设置
参数：bYellow2[in]                是否识别双层黄牌
      bIndivi[in]                 是否识别个性化车牌
      bArmPol[in]                 是否识别军警车牌
      bArmy2[in]                  是否识别双层军牌
      bTractor[in]                是否识别农用车牌 
	  bOnlyDyellow[in]			  只是别双层黄牌
	  bEmbassy[in]				  是否识别使馆车牌
	  bDarmpolice[in]			  是否识别双层武警车牌
	  bOnlyLocation[in]			  只定位车牌
	  nChannel[in]                通道号
***************************************/
BOOL WINAPI LPR_SetPlateType(BOOL bYellow2, 
							 BOOL bIndivi,
							 BOOL bArmPol, 
							 BOOL bArmy2,
							 BOOL bTractor,
                             BOOL bOnlyDyellow,
                             BOOL bEmbassy,
                             BOOL bDarmpolice,
                             BOOL bOnlyLocation,
							 int  nChannel=1);

/**************************************
LPR_SetSpecialParameters设置夜间模式、识别阈值、省份默认值、识别车牌个数。必须在调用LPR_InitEx之后设置
参数：bNight[in]                  是否是夜间模式
	  nImageplateThr[in]          车牌定位阈值
	  nImageRecogThr[in]          车牌识别阈值
	  nPlatesNum[in]              最多识别的车牌个数
	  LocalProvince[in]           默认省份	  	
	  nChannel[in]                通道号
***************************************/
BOOL WINAPI LPR_SetSpecialParameters(BOOL bNight,		
		int nImageplateThr, 
		int nImageRecogThr,
		int nPlatesNum,
		char *LocalProvince,
		int nChannel=1);

/**************************************
LPR_InitEx初始化核心库
参数：nChannel[in] 通道号
***************************************/
BOOL WINAPI LPR_InitEx(int  nChannel=1);

/**************************************
LPR_UninitEx卸载核心库
参数：nChannel[in] 通道号
***************************************/
void WINAPI LPR_UninitEx(int  nChannel=1);

/**************************************
LPR_RGB888Ex识别连续视频流和内存图片
参数：pImg[in]       指向内存中图像的指针，格式为RGB888,YUV420,YUV422，格式在LPR_SetImageFormat函数中指定
      nWidth[in]     图像的宽度，以像素为单位
	  nHeight[in]    图像的高度，以像素为单位 
	  pResult[in]    识别结果结构体
	  nRecogNum[out] 实际识别到的车牌个数
	  prcRange[in]   车牌识别的范围；设为(0,0,0,0)整张图片都识别，以像素为单位
      nChannel[in]   通道号
***************************************/
BOOL WINAPI LPR_RGB888Ex(unsigned char *pImg, int nWidth, int  nHeight, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange, int  nChannel=1);

/************************* *************
LPR_GetImageBuf识别连续视频流时获取识别到车牌的帧内存
参数：pImageBuf[in,out]   输入一个BYTE类型指针，不需要分配内存；输出图像的指针
      nWidth[out]         图像的宽度，以像素为单位
	  nHeight[out]        图像的高度，以像素为单位
	  nSize[out]          图像的大小，以字节为单位
	  nChannel[in]       通道号
说明：在LPR_SetImageFormat的参数bOutputSingleFrame设为TRUE，且调用函数LPR_RGB888Ex识别连续视频流时，
      用此函数获取识别到车牌的帧内存。
***************************************/
BOOL WINAPI LPR_GetImageBuf(unsigned char *&pImageBuf, int &nWidth, int &nHeight, int &nSize, int  nChannel=1);

/**************************************
LPR_FileEx识别图片文件
参数：lpszFileName[in]     图像的路径
      lpszPlateFile[in]    车牌的保存路径，如果不保存车牌图片此参数传NULL
	  pResult[in]          识别结果结构体
	  RecogNum[out]        实际识别到的车牌个数
	  prcRange[in]         车牌识别的范围；设为(0,0,0,0)整张图片都识别，以像素为单位
      nChannel[in]         通道号
***************************************/
BOOL WINAPI LPR_FileEx(char* lpszFileName, char *lpszPlateFile, TH_PlateResult* pResult, int &nRecogNum, TH_RECT *prcRange,int nChannel=1);

#ifdef __cplusplus
}	// extern "C"
#endif

#endif


