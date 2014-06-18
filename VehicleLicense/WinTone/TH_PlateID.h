// ***************************************************************
//  TH_PlateID.h   version:  4.0     date: 2010.4.12
//  -------------------------------------------------------------
//  清华大学智能图文信息处理研究室。版权所有。
//  -------------------------------------------------------------
//  Center for Intelligent Image and Document Information Processing
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//   Author: Liu CS, Zhou J
// ***************************************************************
//		Revision history:
//			2010.4.12: v4.0, TH_PlateID车牌识别SDK的接口
// ***************************************************************

#ifndef __TH_PLATEID_H_INCLUDE__
#define __TH_PLATEID_H_INCLUDE__

#if !defined(WIN32) && !defined(__stdcall)
#define __stdcall
#endif

#include "TH_ErrorDef.h"

#ifdef __cplusplus
extern "C" {
#endif


//车牌颜色
#define LC_UNKNOWN  0
#define LC_BLUE   1
#define LC_YELLOW 2
#define LC_WHITE  3
#define LC_BLACK  4
#define LC_GREEN  5
	
//车牌类型
#define LT_UNKNOWN  0   //未知车牌
#define LT_BLUE     1   //蓝牌小汽车
#define LT_BLACK    2   //黑牌小汽车
#define LT_YELLOW   3   //单排黄牌
#define LT_YELLOW2  4   //双排黄牌（大车尾牌，农用车）
#define LT_POLICE   5   //警车车牌
#define LT_ARMPOL   6   //武警车牌
#define LT_INDIVI   7   //个性化车牌
#define LT_ARMY     8   //单排军车
#define LT_ARMY2    9   //双排军车
#define LT_EMBASSY  10  //使馆牌
#define LT_HONGKONG 11  //香港牌
#define LT_TRACTOR  12  //拖拉机

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

//运动方向
#define DIRECTION_LEFT	1
#define DIRECTION_RIGHT	2
#define DIRECTION_UP	3
#define DIRECTION_DOWN	4
	
//图像格式
#define ImageFormatRGB		0
#define ImageFormatBGR		1
#define ImageFormatYUV422	 2
#define ImageFormatYUV420COMPASS 3

#define PARAM_INDIVIDUAL_ON          0
#define PARAM_INDIVIDUAL_OFF         1
#define PARAM_TWOROWYELLOW_ON	     2
#define PARAM_TWOROWYELLOW_OFF	     3
#define PARAM_ARMPOLICE_ON           4
#define PARAM_ARMPOLICE_OFF          5
#define PARAM_TWOROWARMY_ON          6
#define PARAM_TWOROWARMY_OFF         7
#define PARAM_TRACTOR_ON			 8
#define PARAM_TRACTOR_OFF			 9


#define RECOG_STAGE_ALL			0		// 无错误
#define RECOG_STAGE_FINDPLATE	1		// 没有找到车牌
#define RECOG_STAGE_PLATESCORE_ZERO	2	// 车牌评价值(0分)
#define RECOG_STAGE_PLATESCORE_LOW	3	// 车牌评价值(不及格)
#define RECOG_STAGE_RECOGSCORE_ZERO	4	// 车牌识别分数(0分)
#define RECOG_STAGE_RECOGSCORE_LOW	5	// 车牌识别分数(不及格)

	
typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;

typedef struct TH_PlateIDCfg
{
	int nMinPlateWidth;			// 检测的最小车牌宽度，以像素为单位
	int nMaxPlateWidth;			// 检测的最大车牌宽度，以像素为单位
	
	int nMaxImageWidth;		// 最大图像宽度
	int nMaxImageHeight;	// 最大图像高度

	unsigned char bVertCompress;			// 是否垂直方向压缩1倍后识别
	unsigned char bIsFieldImage;			// 是否是场图像
	unsigned char bOutputSingleFrame;	// 是否视频图像中同一个车的多幅图像只输出一次结果		
	unsigned char bMovingImage;			// 识别运动or静止图像

	unsigned char bIsNight;
	unsigned char nImageFormat;

	unsigned char * pFastMemory;	// DSP等的片内内存，耗时多的运算优先使用这些内存
	int nFastMemorySize;			// 快速内存的大小

	unsigned char *pMemory;			// 普通内存的地址，内建的内存管理，避免内存泄漏等问题
	int nMemorySize;				// 普通内存的大小

	int (*DMA_DataCopy)(void *dst, void *src,int nSize);
	int (*Check_DMA_Finished)();

	int nLastError;			// 用于传递错误信息
							// 0: 无错误
							// 1: FindPlate(没有找到车牌)
							// 2: 车牌评价值(0分)
							// 3: 车牌评价值(不及格)
							// 4: 车牌识别分数(0分)
	                        // 5: 车牌识别分数(不及格)
	int nErrorModelSN;		// 出错的模块编号

	char reserved[120];
}TH_PlateIDCfg;

// 缺省车牌识别SDK配置
const TH_PlateIDCfg c_defConfig = {80, 200, /* Min and Max Plate Width */ 
	720, 576, /* Max Image Width and Height*/ 
	0, /*vert compress*/ 1, /* Field Image? */1, /* output single*/  0/*Moving */,
	0 /* Night? */ , ImageFormatBGR, 
	NULL, 0, 
	NULL,0, 
	NULL, NULL,
	0,0};

typedef struct TH_PlateIDResult 
{
	char license[16];
	char color[8];
	int nColor;			// 车牌颜色
	int nType;			// 车牌类型
	int nConfidence;	// 整牌可信度
	int nBright;		// 亮度评价
	int nDirection;		//车牌运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down
	
	TH_RECT rcLocation;
	const unsigned char *pbyBits;	/* 该识别结果对应的图片的缓冲区, 只有当 bOutputSingleFrame = true 时，该指针才有效。
									下次识别后，该缓冲区内容被覆盖。调用程序无需释放该缓冲区。
									缓冲区大小等于传递进来的图片数据的长度*/
	int nTime;
	unsigned char nCarBright;		//车的亮度
	unsigned char nCarColor;		//车的颜色
	char reserved[100];				// 保留
}TH_PlateIDResult;


/************************************************************************/
/* TH_InitPlateIDSDK: 初始化车牌识别SDK，在使用该SDK的功能前			*/
/*			必需且仅需调用一次该函数									*/
/*		Parameters:														*/
/*			pPlateConfig[in]: 车牌识别SDK的配置							*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_InitPlateIDSDK(TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_UninitPlateIDSDK: 释放车牌识别SDK，在使用该SDK的功能后			*/
/*			必需且仅需调用一次该函数，以释放内存。						*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_UninitPlateIDSDK(TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* TH_RecogStillImage2: 识别内存中车牌图像(输出识别到的多个结果)	*/
/*		Parameters:														*/
/*			pbyBits[in]: 指向内存图像数据的指针，3个字节表示1个像素		*/
/*			nWidth[in]: 图像的宽度										*/
/*			nHeight[in]: 图像的高度										*/
/*			pResult[out]: 车牌识别结果数组, 调用方开辟pResult[nResultNum]内存*/
/*			nResultNum[in,out]: in 最大候选车牌个数，out 识别出的车牌个数*/
/*			prcRange[in]: 指定识别范围									*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_RecogImage(const unsigned char *pbyBits, int nWidth, int nHeight, TH_PlateIDResult *pResult,
	int *nResultNum, const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig);

int __stdcall TH_EvaluateCarColor(const unsigned char *pbyBits, int nWidth, int nHeight, TH_PlateIDResult *pResult,
	int *nResultNum, const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig);

int __stdcall TH_SetImageFormat( unsigned char cImageFormat, unsigned char bVertFlip, unsigned char bDwordAligned, TH_PlateIDCfg *pPlateConfig );

/************************************************************************/
/* TH_SetDayNightMode: 设置夜晚模式										*/
/*		Parameters:														*/
/*			bIsNight[in]: true:晚上; false:白天							*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetDayNightMode( unsigned char bIsNight, TH_PlateIDCfg *pPlateConfig);


int __stdcall TH_SetEnlargeMode( unsigned char bEnlarge , TH_PlateIDCfg *pPlateCfg);

int __stdcall TH_SetEnabledPlateFormat(unsigned int dFormat, TH_PlateIDCfg *pPlateConfig);

int __stdcall TH_SetProvinceOrder( char* szProvince, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_SetRecogThreshold: 设置识别阈值									*/
/*		Parameters:														*/
/*			nPlateLocate_Th[in]: 0 - 9		--   7: 默认阈值			*/
/*					nOCR_Th[in]: 0 - 9		--   5: 默认阈值			*/
/*				0: 最宽松的阈值											*/
/*				9:最严格的阈值											*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetRecogThreshold( unsigned char nPlateLocate_Th, unsigned char nOCR_Th, TH_PlateIDCfg *pPlateCfg);

//检查工作过程中最小的剩余内存，如果出现负数，则需要增加给定的初始内存
int __stdcall TH_CheckMinFreeMemory( int *pnMinFreeSRAM, int *pnMinFreeSDRAM, TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* 功能: 获取版本号														*/
/*		Parameters：无													*/
/*		返回值: 字符串 格式：主版本号.副版本号.修订号.编译号			*/
/*				不用释放该指针。										*/
/************************************************************************/
const char * __stdcall TH_GetVersion();

int __stdcall TH_SetContrast( unsigned char nContrast, TH_PlateIDCfg *pPlateCfg ); // 清晰度指数 nContrast[in]: 0 - 9
																				 // 最模糊时设为1;最清晰时9设为;
                                                                                 // 自动探测设为0;默认值9
/************************************************************************/
/* TH_SetAutoSlopeRectifyMode: 设置是否自动倾斜校正(仅支持RGB888,图片方式)*/
/*		Parameters:														*/
/*			bIsAutoSlope[in]: true:自动倾斜校正; false:不自动倾斜校正	*/
/*          nSlopeDetectRange:  0 - 16 度								*/
/*		Return Value: int(ERR_Code)										*/
/*		支持格式: ImageFormatBGR, ImageFormatRGB						*/
/************************************************************************/
int __stdcall TH_SetAutoSlopeRectifyMode( unsigned char bIsAutoSlope, unsigned char nSlopeDetectRange, TH_PlateIDCfg *pPlateConfig);


#ifdef __cplusplus
}
#endif

#endif	//	__TH_PLATEID_H_INCLUDE__
