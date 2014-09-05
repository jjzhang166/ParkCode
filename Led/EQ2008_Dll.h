#ifndef __EQ2008_DLL__
#define __EQ2008_DLL__

#ifdef DLL_API
#else
#define DLL_API _declspec(dllimport) 
#endif

#include "DataStruct.h" 

/****************参数说明******************/
 //通讯方式常量
#define DEVICE_TYPE_COM		0    //串口通讯
#define DEVICE_TYPE_NET		1    //网络通讯

//串行通讯速度常量
#define SBR_9600			9600
#define SBR_19200			19200
#define SBR_57600			57600
#define SBR_115200			115200

//EQ3002/2008控制卡类型
#define EQ3002_I			0
#define EQ3002_II			1
#define EQ3002_III			2
#define EQ2008_I			3
#define EQ2008_II			3
#define EQ2010_I			4
#define EQ2010_II			4
#define EQ2010_64			4
#define EQ2008_IE			5
#define EQ2008_IIE			5
#define EQ3002_IE			6
#define EQ3002_IIE			6

//颜色常量
#define RED					0x0000FF
#define GREEN				0x00FF00
#define YELLOW				0x00FFFF

//返回值常量
#define EQ_FALSE			0
#define EQ_TRUE			    1

//添加节目
DLL_API int __stdcall User_AddProgram(int CardNum,BOOL bWaitToEnd,int iPlayTime);

//添加图文区
DLL_API int  __stdcall User_AddBmpZone(int CardNum,User_Bmp *pBmp,int iProgramIndex);
DLL_API BOOL __stdcall User_AddBmp(int CardNum,int iBmpPartNum,HBITMAP hBitmap,User_MoveSet* pMoveSet,int iProgramIndex);
DLL_API BOOL __stdcall User_AddBmpFile(int CardNum,int iBmpPartNum,char *strFileName,User_MoveSet* pMoveSet,int iProgramIndex);

//添加文本区
DLL_API int __stdcall User_AddText(int CardNum,User_Text *pText,int iProgramIndex);

//添加RTF区
DLL_API int __stdcall User_AddRTF(int CardNum,User_RTF *pRTF,int iProgramIndex);

//添加单行文本区
DLL_API int __stdcall User_AddSingleText(int CardNum,User_SingleText *pSingleText,int iProgramIndex);

//添加时间区
DLL_API int __stdcall User_AddTime(int CardNum,User_DateTime *pDateTime,int iProgramIndex);

//添加计时区
DLL_API int __stdcall User_AddTimeCount(int CardNum,User_Timer *pTimeCount,int iProgramIndex);

//添加温度区
DLL_API int __stdcall User_AddTemperature(int CardNum,User_Temperature *pTemperature,int iProgramIndex);

//删除节目
DLL_API BOOL __stdcall User_DelProgram(int CardNum,int iProgramIndex);

//删除所有节目
DLL_API BOOL __stdcall User_DelAllProgram(int CardNum);

//发送数据
DLL_API BOOL __stdcall User_SendToScreen(int CardNum);

//发送节目文件和索引文件
DLL_API BOOL __stdcall User_SendFileToScreen(int CardNum,char pSendPath[MAX_PATH],char pIndexPath[MAX_PATH]);

DLL_API BOOL __stdcall User_CloseScreen(int CardNum);

//开机
DLL_API BOOL __stdcall User_OpenScreen(int CardNum);

//校正板卡的时间
DLL_API BOOL __stdcall User_AdjustTime(int CardNum);

//实时发送数据
DLL_API BOOL __stdcall User_RealtimeConnect(int CardNum);	 //建立连接
DLL_API BOOL __stdcall User_RealtimeSendData(int CardNum,int x,int y,int iWidth,int iHeight,HBITMAP hBitmap);	 //发送数据
DLL_API BOOL __stdcall User_RealtimeDisConnect(int CardNum); //断开连接

DLL_API BOOL __stdcall User_RealtimeSendBmpData(int CardNum,int x,int y,int iWidth,int iHeight,char *strFileName);	 //发送数据

DLL_API BOOL __stdcall User_ImportIniFile(char*	pPath,int iLength); //导入ini配置文件

//亮度调节
DLL_API BOOL __stdcall User_SetScreenLight(int CardNum,int iLightDegreen);

/********************************************************************************/

#endif __EQ2008_DLL__
