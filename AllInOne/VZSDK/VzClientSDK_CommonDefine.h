//一些公有的符号定义
#ifndef _VZ_CLIENT_SDK_COMMON_DEFINE_H_
#define _VZ_CLIENT_SDK_COMMON_DEFINE_H_

/* common constants */
#ifndef  SUCCESS
	#define SUCCESS         0
#endif

#ifndef FAILURE
	#define FAILURE        -1
#endif

#define VZ_API_SUCCESS			0
#define VZ_API_FAILED			-1

#ifndef CIF4_WIDTH
#define CIF4_WIDTH	704
#define CIF4_HEIGHT   576
#define CIF_WIDTH	352
#define CIF_HEIGHT  288
#endif

#ifndef DWORD
#ifdef _WIN32
typedef unsigned long       DWORD;
#else
typedef unsigned int       DWORD;
#endif
//typedef int                 BOOL;
typedef unsigned short      WORD;
typedef unsigned char       BYTE;
typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned int uint32;
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

/************************************************************************

ERROR define

************************************************************************/
#define  E_SUCCESS   0		//Success
#define  E_INVAL     1		//Invalid parameters
#define  E_NOENT     2		//No such file or directory
#define  E_IO        3		//I/O Error
#define  E_NOMEM     4		//Out of memory
#define  E_NETERR    5      //Network error
#define  E_NEEDINIT  6      //Need call some initial function first
#define  E_OUTOFMAX  7      //Beyond the maxinum
#define  E_NOTLOGIN  8      //Not login  
#define  E_SREJECT   9      //Server reject the request
#define  E_MULTICASTNOTSUPPORT  10 //Multicast not support
#define  E_TALKNOTSUPPORT       11 //Talk not support
#define  E_AUDIOERR  12     //Audio can not operatioin
#define  E_BUFSMALL  13     //Buffer too small
#define  E_UNDEFINED   14

//实时流数据类型
typedef enum
{
	vHeadData = 1,	//视频编码头数据
	vStreamData,	//
	aStreamData		//	
}RealDataType;

//解码数据的作用模式
typedef enum VZC_DEC_DATA_MODE
{
	VZC_DEC_DATA_INSTANCE,	//实际解码数据，并将绘制到内部绘图（默认）。用户不能修改图像，否则影响图像质量
	VZC_DEC_DATA_REFERENCE,	//拷贝解码数据，如果用户修改了图像，将显示到内部绘图。
	VZC_DEC_DATA_COPY,		//拷贝解码数据，如果用户修改了图像，但不显示到内部绘图。
}
VZC_DEC_DATA_MODE;

typedef struct VzYUV420P
{
	unsigned char *pY;
	unsigned char *pU;
	unsigned char *pV;
	int widthStepY;
	int widthStepU;
	int widthStepV;
	int width;
	int height;
}
VzYUV420P;

typedef struct VzFrameBuffer
{
	VzYUV420P yuv;
	unsigned int uTimeStamp;	//当前帧的时间参数
	unsigned int uSerialNum;    //当前帧的编号
}
VzFrameBuffer;

#endif
