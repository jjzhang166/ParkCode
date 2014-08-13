//电表接口的宏及结构体定义文件
#ifndef _VZ_CLIENT_SDK_WATTHM_DEFINE_H_
#define _VZ_CLIENT_SDK_WATTHM_DEFINE_H_

//判断IVSProtocolInput::strDetail为VZ_IVS_PROTOCOL_ALARM_HJT212_DETAIL，
//则可以将IVSProtocolInput::pParam类型转换为VZ_WATTHM_DataInfo以便进一步分析
#define VZ_IVS_PROTOCOL_CONFIG_WATTHM_DETAIL	"Watt_hour_meterConfig"	//:VZ_WATTHM_ConfigInfo

#define VZ_WATTHM_PARAM_MAX_NUM	16	//设备同时检测的电表变量的上限

#define VZ_WATTHM_ITEM_CODE_MAXLEN	4
#define VZ_WATTHM_ITEM_NAME_MAXLEN	16
#define VZ_WATTHM_ITEM_UNIT_MAXLEN	8

//个项的详细信息
typedef struct VZ_WATTHM_ItemInfoDetail{
	char code[VZ_WATTHM_ITEM_CODE_MAXLEN];	//标准代码
	char name[VZ_WATTHM_ITEM_NAME_MAXLEN];	//名称：可通过API自定义名称，否则为标准名称
	float min;	//设定的报警范围下限
	float max;	//设定的报警范围上限
	char unit[VZ_WATTHM_ITEM_UNIT_MAXLEN];	//单位：通过API设置是无效的，只能由API返回
	int isdisplay;
}VZ_WATTHM_ItemInfoDetail;

//个项详细信息的数组
typedef struct VZ_WATTHM_ItemInfo{
	VZ_WATTHM_ItemInfoDetail itemInfo[VZ_WATTHM_PARAM_MAX_NUM];
	int itemInfo_num;
}VZ_WATTHM_ItemInfo;

typedef struct VZ_WATTHM_Item{
	char code[VZ_WATTHM_PARAM_MAX_NUM][VZ_WATTHM_ITEM_CODE_MAXLEN];
}VZ_WATTHM_Item;


//可用的OSD配置参数
//起始位置（startX、startY）是相对于图像尺寸为4CIF（704x576）的相对坐标
typedef struct VZ_WATT_OSD_Readable{
	int startX;		//显示的起始位置X坐标（相对704的上限）
	int startY;		//显示的起始位置Y坐标（相对576的上限）
	int gapRow;		//行间距
	int gapCol;		//列间距
}VZ_WATT_OSD_Readable;

typedef struct VZ_WATTHM_OSD{
	unsigned int Firstitem_pos;
	unsigned int Gap_pos;
}VZ_WATTHM_OSD;

//接收数采仪输入的串口配置参数
typedef struct VZ_WATTHM_Serial{
	unsigned int    PtzComm;        //串口号（使用2）
	unsigned int    BaudRate;       //串口波特率 eg:9600 , 19200, 56000, etc
	unsigned int    Parity;         //串口校验位 其值为0-4=no,odd,even,mark,space
	unsigned int    DataBits;       //串口数据位 其值为4-8=4,5,6,7,8 位数据位
	unsigned int    StopBit;        //串口停止位 其值为0,1,2 = 1, 1.5, 2 位停止位
	unsigned int	Type;	    //协议类型，比如：HJ/T 212—2005
}VZ_WATTHM_Serial;

typedef struct {
	VZ_WATTHM_OSD osd;	
	VZ_WATTHM_Serial serial;
}VZ_WattHM_UserCfg;


#endif
