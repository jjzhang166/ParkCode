//环境监测项目接口的宏及结构体定义文件
#ifndef _VZ_CLIENT_SDK_HJT212_DEFINE_H_
#define _VZ_CLIENT_SDK_HJT212_DEFINE_H_

//判断IVSProtocolInput::strDetail为VZ_IVS_PROTOCOL_ALARM_HJT212_DETAIL，
//则可以将IVSProtocolInput::pParam类型转换为VZ_HJT212_DataInfo以便进一步分析
#define VZ_IVS_PROTOCOL_ALARM_HJT212_DETAIL		"t212data"		//:VZ_HJT212_DataInfo
#define VZ_IVS_PROTOCOL_CONFIG_HJT212_DETAIL	"HJT212Config"	//:VZ_HJT212_ConfigInfo

#define VZ_HJT212_PARAM_POLL_NUM	32	//设备同时检测的污染物种类上限

#define VZ_HJT212_ITEM_CODE_MAXLEN	4
#define VZ_HJT212_ITEM_NAME_MAXLEN	16
#define VZ_HJT212_ITEM_UNIT_MAXLEN	8
#define VZ_HJT212_ITEM_VALUE_MAXLEN	16

#define VZ_HJT212_TIME_MAXLEN	16
#define VZ_HJT212_SOURCE_STRING_MAXLEN	1036	//原始采集的字符串最大长度，按t212协议为1036

//个项的详细信息
typedef struct VZ_HJT212_ItemInfoDetail{
	char code[VZ_HJT212_ITEM_CODE_MAXLEN];	//标准代码
	char name[VZ_HJT212_ITEM_NAME_MAXLEN];	//名称：可通过API自定义名称，否则为标准名称
	float min;	//设定的报警范围下限
	float max;	//设定的报警范围上限
	char unit[VZ_HJT212_ITEM_UNIT_MAXLEN];	//单位：通过API设置是无效的，只能由API返回
	int isdisplay;
}VZ_HJT212_ItemInfoDetail;

//个项详细信息的数组
typedef struct VZ_HJT212_ItemInfo{
	VZ_HJT212_ItemInfoDetail itemInfo[VZ_HJT212_PARAM_POLL_NUM];
	int itemInfo_num;
}VZ_HJT212_ItemInfo;

typedef struct VZ_HJT212_Item{
	char code[VZ_HJT212_PARAM_POLL_NUM][VZ_HJT212_ITEM_CODE_MAXLEN];
}VZ_HJT212_Item;

typedef struct VZ_HJT212_OSD{
	unsigned int Firstitem_pos;
	unsigned int Gap_pos;
}VZ_HJT212_OSD;

//可用的OSD配置参数
//起始位置（startX、startY）是相对于图像尺寸为4CIF（704x576）的相对坐标
typedef struct VZ_HJT212_OSD_Readable{
	int startX;		//显示的起始位置X坐标（相对704的上限）
	int startY;		//显示的起始位置Y坐标（相对576的上限）
	int gapRow;		//行间距
	int gapCol;		//列间距
}VZ_HJT212_OSD_Readable;

//接收数采仪输入的串口配置参数
typedef struct VZ_HJT212_Serial{
	unsigned int    PtzComm;        //串口号（使用2）
	unsigned int    BaudRate;       //串口波特率 eg:9600 , 19200, 56000, etc
	unsigned int    Parity;         //串口校验位 其值为0-4=no,odd,even,mark,space
	unsigned int    DataBits;       //串口数据位 其值为4-8=4,5,6,7,8 位数据位
	unsigned int    StopBit;        //串口停止位 其值为0,1,2 = 1, 1.5, 2 位停止位
	unsigned int	Type;	    //协议类型，比如：HJ/T 212—2005
}VZ_HJT212_Serial;

//用于推送数据的服务器地址
typedef struct VZ_HJT212_Server{
	char hostname[32];
	int port;
}VZ_HJT212_Server;

typedef struct VZ_HJT212_Cfg{
	VZ_HJT212_OSD osd;	
	VZ_HJT212_Serial serial;
	unsigned char alarm_stream_enable;
	VZ_HJT212_Server server;
}VZ_HJT212_Cfg;

//个项的返回数据
typedef struct VZ_HJT212_ItemDataDetail{
	char code[VZ_HJT212_ITEM_CODE_MAXLEN];	//标准代码
	int bAlarm;		//报警标志：（0未报警，1报警，-1未采集到）
	char strRTD[VZ_HJT212_ITEM_VALUE_MAXLEN];	//污染物实时采样数据
}VZ_HJT212_ItemDataDetail;

//返回的数据信息
typedef struct VZ_HJT212_DataInfo{
	char strDataTime[VZ_HJT212_TIME_MAXLEN];		//数据时间
	int numPolls;		//有效的污染物个数
	VZ_HJT212_ItemDataDetail struData[VZ_HJT212_PARAM_POLL_NUM];	//污染物采样数据
	char strSrc[VZ_HJT212_SOURCE_STRING_MAXLEN + 8];			//原始采集的字符串，按t212协议maxlen=1036
}VZ_HJT212_DataInfo;


//返回的配置信息
typedef struct VZ_HJT212_ConfigInfo{
	VZ_HJT212_ItemInfo struItemInfo;
	VZ_HJT212_OSD_Readable struOSDConfig;
}VZ_HJT212_ConfigInfo;

#endif
