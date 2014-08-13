//VZ车牌识别设备SDK的结构体等定义

#include "VzClientSDK_CommonDefine.h"
//#include "VzClientSDK_LPDefine.h"

/**设备句柄，由VzLPRClient_Open获得，设备操作相关的函数都需要*/
typedef int VzLPRClientHandle;

/**设置回调函数时需要指定的类型*/
typedef enum
{
	VZ_LPRC_CALLBACK_COMMON_NOTIFY,	/**<SDK通用信息反馈（预留）*/
	VZ_LPRC_CALLBACK_PLATE_STR,		/**<车牌号码字符（预留）*/
	VZ_LRPC_CALLBACK_FULL_IMAGE,	/**<完整图像*/
	VZ_LPRC_CALLBACK_CLIP_IMAGE,	/**<截取图像*/
	VZ_LPRC_CALLBACK_PLATE_RESULT,	/**<实时识别结果*/
	VZ_LPRC_CALLBACK_PLATE_RESULT_STABLE,	/**<稳定识别结果*/
	VZ_LPRC_CALLBACK_PLATE_RESULT_TRIGGER,	/**<触发的识别结果，包括API（软件）和IO（硬件）方式的*/
	VZ_LPRC_CALLBACK_VIDEO,			/**<视频帧回调*/
}
VZ_LPRC_CALLBACK_TYPE;

/**通用信息反馈类型*/
typedef enum
{
	VZ_LPRC_NO_ERR = 0,		/**<无错误*/
	VZ_LPRC_ACCESS_DENIED,	/**<用户名密码错误*/
	VZ_LPRC_NETWORK_ERR,	/**<网络连接故障*/
}
VZ_LPRC_COMMON_NOTIFY;

/**识别结果的类型*/
typedef enum
{
	VZ_LPRC_RESULT_REALTIME,		/**<实时识别结果*/
	VZ_LPRC_RESULT_STABLE,			/**<稳定识别结果*/
	VZ_LPRC_RESULT_FORCE_TRIGGER,	/**<调用“VzLPRClient_ForceTrigger”触发的识别结果*/
	VZ_LPRC_RESULT_IO_TRIGGER,		/**<外部IO信号触发的识别结果*/
	VZ_LPRC_RESULT_VLOOP_TRIGGER,	/**<虚拟线圈触发的识别结果*/
}
VZ_LPRC_RESULT_TYPE;

/**顶点定义
  *X_1000和Y_1000的取值范围为[0, 1000]；
  *即位置信息为实际图像位置在整体图像位置的相对尺寸；
  *例如X_1000 = x*1000/win_width，其中x为点在图像中的水平像素位置，win_width为图像宽度
*/
typedef struct
{
	unsigned X_1000;	/**<水平方向相对坐标*/
	unsigned Y_1000;	/**<竖直方向相对坐标*/
}
VZ_LPRC_VERTEX;

/**虚拟线圈名称*/
#define VZ_LPRC_VIRTUAL_LOOP_NAME_LEN	32

/**虚拟线圈顶点个数*/
#define VZ_LPRC_VIRTUAL_LOOP_VERTEX_NUM	4

/**虚拟线圈信息定义*/
typedef struct
{
	BYTE			byID;		/**<序号*/
	BYTE			byEnable;	/**<是否有效*/
	BYTE			byDraw;		/**<是否绘制*/
	BYTE			byRes[1];	/**<预留*/
	char			strName[VZ_LPRC_VIRTUAL_LOOP_NAME_LEN];			/**<自定义名称*/
	VZ_LPRC_VERTEX	struVertex[VZ_LPRC_VIRTUAL_LOOP_VERTEX_NUM];	/**<顶点数组*/
}
VZ_LPRC_VIRTUAL_LOOP;

/**最大虚拟线圈个数*/
#define VZ_LPRC_VIRTUAL_LOOP_MAX_NUM	8

/**虚拟线圈序列*/
typedef struct
{
	unsigned				uNumVirtualLoop;	/**<实际个数*/
	VZ_LPRC_VIRTUAL_LOOP	struLoop[VZ_LPRC_VIRTUAL_LOOP_MAX_NUM];	/**<虚拟线圈数组*/
}
VZ_LPRC_VIRTUAL_LOOPS;

/**省份字符串的最大尺寸*/
#define VZ_LPRC_PROVINCE_STR_LEN	128

/**预设省份信息*/
typedef struct
{
	char strProvinces[VZ_LPRC_PROVINCE_STR_LEN];	/**<所有支持的省份简称构成的字符串*/
	int nCurrIndex;	/**<当前的预设省份的序号，在strProvinces中的，-1为未设置*/
}
VZ_LPRC_PROVINCE_INFO;

/**图像信息*/
typedef struct
{
	unsigned		uWidth;			/**<宽度*/
	unsigned		uHeight;		/**<高度*/
	unsigned		uPitch;			/**<图像宽度的一行像素所占内存字节数*/
	unsigned		uPixFmt;		/**<图像像素格式，参考枚举定义图像格式（ImageFormatXXX）*/
	const unsigned char	*pBuffer;	/**<图像内存的首地址*/
}
VZ_LPRC_IMAGE_INFO;
