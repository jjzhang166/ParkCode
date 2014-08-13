#ifndef _VZ_CLIENT_SDK_LP_DEFINE_H_
#define _VZ_CLIENT_SDK_LP_DEFINE_H_

// 车牌识别相关参数
//---------------------------------------//
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
#define LT_HONGKONG 11  //香港进出中国大陆车牌
#define LT_TRACTOR  12  //农用车牌
#define LT_COACH	13  //教练车牌
#define LT_MACAO	14  //澳门进出中国大陆车牌
#define LT_ARMPOL2   15 //双层武警车牌

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
#define ImageFormatYUV420	4			//YYYY...U...V...	(YU12)
#define ImageFormatUYVY	    5			//UYVYUYVYUYVY...	(UYVY)
#define ImageFormatNV21		6			//YYYY...VU...		(NV21)
#define ImageFormatYV12		7			//YYYY...V...U		(YV12)
#define ImageFormatYUYV	    8			//YUYVYUYVYUYV..	(YUYV)

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

// 触发识别类型定义
typedef enum _TH_TRIGGER_TYPE
{
	TRIGGER_TYPE_AUTO		=	0,		//自动
	TRIGGER_TYPE_EXTERNAL	=	1,		//外部
	TRIGGER_TYPE_SOFTWARE	=	2,		//软件
}TH_TRIGGER_TYPE;

typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;

typedef struct TH_TimeVal
{
	long    tv_sec;         /* 秒 */
	long    tv_usec;        /* 微秒 */
	long	tv_frameStamp;	/* 帧编号 */
}TH_TimeVal;

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

typedef struct TH_PlateResultImage
{
	char license[16];				// 车牌号码
	char color[8];					// 车牌颜色
	int nColor;						// 车牌颜色序号
	int nType;						// 车牌类型
	int nConfidence;				// 车牌可信度
	int nBright;					// 亮度评价
	int nDirection;					// 运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down	
	int nTime;						// 识别所用时间
	unsigned char nCarBright;		// 车的亮度
	unsigned char nCarColor;		// 车的颜色

	unsigned char* pImageRGB24;     // 抓拍识别到车牌的图像,RGB24位格式
	int nImageWidth;				// 抓拍识别到车牌的图像的宽度
	int nImageHeight;				// 抓拍识别到车牌的图像的高度

	TH_RECT		rcLocation;			// 抓拍车牌所在的位置
	TH_TimeVal  tv_time;			// 抓拍车牌的时间
}TH_PlateResultImage;

////////////////////////////
////扩展定义
#define MAX_LP_RESULT 50

typedef struct TH_PlateResultInfo
{
	TH_PlateResult    result;
    unsigned int      dwReliableResults; // 可信结果 用来像上层反结果.
	unsigned int      dwBitsResults; //dwBitsResults = 1 在规则范围内需要返回结果
}TH_PlateResultInfo;

#endif