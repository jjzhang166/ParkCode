#ifndef _VZ_CLIENT_SDK_IVS_DEFINE_H_
#define _VZ_CLIENT_SDK_IVS_DEFINE_H_

#include "VzClientSDK_CommonDefine.h"

//智能视频相关参数
//---------------------------------------------------------------------------
///-------------------vz alarm------------------------

#define VZ_IVS_MAX_RELATIVE_SHORT 0x4000

//绝对坐标和相对的互转
typedef short VZ_FIXPOINT_SHORT;
//FIXPOINT_SHORT类型为 相对坐标的定点数表示，对于需要输入相对坐标的结构体，可以通过下面的IVS_I2S宏进行转换
/*例如：
窗口分辨率为640*480，坐标点（320，240）
用宏IVS_I2S，我们可以直接得到
VZ_FIXPOINT_SHORT x = IVS_I2S(320，640);
VZ_FIXPOINT_SHORT y = IVS_I2S(240，480);
*/
#define IVS_I2S(int_val,total) ((short)(((int)(int_val)<<14)/((int)(total))))
#define IVS_S2I(short_val,total) (((int)(short_val)*(total)+(1<<13))>>14)

//ivs状态
#define VZ_IVS_TRAINING  1
#define VZ_IVS_DETECTING 2
#define VZ_IVS_NO_SIGNAL 3
#define VZ_IVS_TAMPER	 4

//
typedef struct _VZ_IVS_POINT{
	VZ_FIXPOINT_SHORT  X;//相对坐标范围[0-VZ_IVS_MAX_RELATIVE_SHORT]
	VZ_FIXPOINT_SHORT  Y;
}VZ_IVS_POINT;//点坐标参数

typedef struct _VZ_IVS_LINE{
	VZ_IVS_POINT   struStart;
	VZ_IVS_POINT   struEnd;
}VZ_IVS_LINE;//线结构参数

#define IVS_MAX_BROKEN_LINE_POINT_NUM 10
typedef struct _VZ_IVS_BROKEN_LINE{
	DWORD           dwPointNum;
	VZ_IVS_POINT   struPos[IVS_MAX_BROKEN_LINE_POINT_NUM];
}VZ_IVS_BROKEN_LINE;//线结构参数

typedef struct _VZ_IVS_RECT{
	VZ_FIXPOINT_SHORT   X;//相对坐标范围[0-VZ_IVS_MAX_RELATIVE_SHORT]
	VZ_FIXPOINT_SHORT   Y;
	VZ_FIXPOINT_SHORT   Width;
	VZ_FIXPOINT_SHORT   Height;
}VZ_IVS_RECT;//区域

typedef struct _VZ_IVS_OBJSIZE_RANGE{
	WORD   Min;
	WORD   Max;
}VZ_IVS_OBJSIZE_RANGE;//区域

//sizeof POLYGON	2*sizeof(float)*IVS_MAX_POLYGON_POINT_NUM+4 = 84
#define IVS_MAX_POLYGON_POINT_NUM 15
typedef struct _VZ_IVS_POLYGON{
	DWORD           dwPointNum;
	VZ_IVS_POINT   struPos[IVS_MAX_POLYGON_POINT_NUM];
}VZ_IVS_POLYGON;//多边形

typedef enum _IVS_CROSS_DIRECTION{
	IVS_BOTH_DIRECTION  = 0,
	IVS_LEFT_GO_RIGHT   = 1,
	IVS_RIGHT_GO_LEFT   = 2
}IVS_CROSS_DIRECTION;//穿越方向

typedef struct _VZ_IVS_TRAVERSE_PLANE{
	VZ_IVS_BROKEN_LINE	  struPlaneBottom;
	IVS_CROSS_DIRECTION   dwCrossDirection;
	BYTE                  byRes1;
	BYTE                  byPlaneHeight;
	BYTE                  byRes2[38];
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_TRAVERSE_PLANE;//穿越警戒面参数


typedef struct _VZ_IVS_TRAVERSE_PLANE_EXT{
	VZ_IVS_BROKEN_LINE	  struPlaneBottom;
	IVS_CROSS_DIRECTION   dwCrossDirection;
	BYTE				  byIsCalibed[IVS_MAX_BROKEN_LINE_POINT_NUM-1];
	VZ_IVS_LINE			  CalibLine[IVS_MAX_BROKEN_LINE_POINT_NUM-1];
}VZ_IVS_TRAVERSE_PLANE_EXT;//穿越警戒面扩展
/////////////////////////////////////////

typedef struct _VZ_IVS_ENTER_OUT{
	BYTE			  byEnable;
	BYTE			  byEnter;	// 0离开 1进入 2（进入、离开）同时检测
	BYTE              byRes[2];
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_ENTER_OUT;//进入/离开区域参数

typedef struct _VZ_IVS_INTRUSION{
	BYTE			  byEnable;
	BYTE              byRes[1];
	WORD              wDuration;
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_INTRUSION;//入侵参数

typedef struct _VZ_IVS_LOITER{
	BYTE			    byEnable;
	BYTE				byRes[1];
	WORD				wDuration;
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_LOITER;//徘徊参数

typedef struct _VZ_IVS_TAKE_LEFT{
	BYTE			  byEnable;
	BYTE			  byTake; // 0丢包 1捡包 2（捡包、丢包）同时检测
	WORD              wDuration;
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_TAKE_LEFT;//丢包/捡包参数

typedef struct _VZ_IVS_PARKING{
	BYTE			  byEnable;
	BYTE              byRes[1];
	WORD              wDuration;
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_PARKING;//停车参数

typedef struct _VZ_IVS_RUN{
	BYTE			  byEnable;
	BYTE              byRes[1];
	VZ_FIXPOINT_SHORT              RunDistance;//相对坐标范围[0-VZ_IVS_MAX_RELATIVE_SHORT]
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_RUN;//奔跑参数

typedef struct _VZ_IVS_HIGH_DENSITY{
	BYTE			  byEnable;
	BYTE              byRes[3];
	float             fDensity;
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_HIGH_DENSITY;	// 人员聚集参数

typedef struct _VZ_IVS_OIL_INTRUSION{
	BYTE			  byEnable;
	BYTE              byRes[7];
	VZ_IVS_OBJSIZE_RANGE  ObjectSize;
}VZ_IVS_OIL_INTRUSION; // 油井入侵参数

//车牌识别参数
typedef struct _VZ_IVS_LPR{
	BYTE					byEnable;
	BYTE					byRes[7];
	VZ_IVS_OBJSIZE_RANGE	struObjSize;
}VZ_IVS_LPR;

//环境监测类型
typedef enum _HJ_DETECT_TYPE
{
	PIPE_WATER = 1,	//废水排放
	BUBBLE,			//气泡
	EXHAUST_GAS,	//废气
	HJ_DETECT_NUM
}
HJ_DETECT_TYPE;

typedef struct _VZ_IVS_HJ
{
	BYTE			byEnable;
	BYTE			byRes[1];
	HJ_DETECT_TYPE	dwDetectType;
}
VZ_IVS_HJ;	//环境检测参数

// 区域规则
typedef struct _VZ_IVS_AREA{
	VZ_IVS_POLYGON			struRegion;
	BYTE					byRes[8];
	VZ_IVS_ENTER_OUT		struEnterOut;
	VZ_IVS_INTRUSION		struIntrusion;
	VZ_IVS_LOITER			struLoiter;
	VZ_IVS_TAKE_LEFT		struTakeLeft;
	VZ_IVS_PARKING			struParking;
	VZ_IVS_RUN				struRun;
	VZ_IVS_HIGH_DENSITY		struDensity;
	VZ_IVS_OIL_INTRUSION    struOilIntrusion;
}VZ_IVS_AREA;

typedef struct _VZ_IVS_AREA_EXT{
	VZ_IVS_POLYGON			struRegion;
	BYTE					byRes[8];
	VZ_IVS_HJ				struHJ;
	VZ_IVS_LPR				struLPR;
}VZ_IVS_AREA_EXT;

typedef union _VZ_IVS_EVENT_UNION{
	DWORD                   uLen[36];
	VZ_IVS_TRAVERSE_PLANE   struTraversePlane;
	VZ_IVS_TRAVERSE_PLANE_EXT struTraversePlaneExt;
	VZ_IVS_AREA             struArea;
	VZ_IVS_AREA_EXT			struAreaExt;
}VZ_IVS_EVENT_UNION;

typedef enum _IVS_RULE_TYPE{
	IVS_RULE_LINE = 0x1,	// 绊线规则
	IVS_RULE_AREA = 0x2,	// 区域规则
	IVS_RULE_LINE_EX,		//扩展的绊线规则
	IVS_RULE_AREA_EX,		//扩展的区域规则
}IVS_RULE_TYPE;

#define MAX_EVENT_NUM 32

enum
{
	OFFSET_TRAVERSE_PLANE = 0,	//穿越警戒面
	OFFSET_ENTER_AREA,			//目标进入区域，支持区域规则 
	OFFSET_EXIT_AREA,			//目标离开区域，支持区域规则
	OFFSET_INTRUSION,			//周界入侵，支持区域规则 
	OFFSET_LOITER,				//徘徊，支持区域规则 
	OFFSET_LEFT_TAKE,			//丢包捡包，支持区域规则
	OFFSET_PARKING,				//停车，支持区域规则 
	OFFSET_RUN,					//奔跑，支持区域规则 
	OFFSET_HIGH_DENSITY,		//区域内人员密度，支持区域规则 
	OFFSET_OIL_INTRUSION,		//油井入侵
	OFFSET_FIRE_SMOKE,			//烟火事件
	OFFSET_PEOPLE_COUNT,		//人数统计
	OFFSET_PLATE_R,				//车牌识别
	OFFSET_CAM_HEALTH,			//摄像机健康状况检测
	OFFSET_CAR_COUNT,			//车流统计
	OFFSET_PLATE_R_SERVER,		//车牌识别服务器版
	OFFSET_AUTO_PTZ,			//PTZ自动跟踪事件
	OFFSET_HJ_PIPE_WATER,		//环境废水
	OFFSET_HJ_BUBBLE,			//环境气泡
	OFFSET_HJ_EXHAUST_GAS		//环境废气
};

typedef enum _IVS_EVENT_TYPE{
	IVS_TRAVERSE_PLANE	= 1<<OFFSET_TRAVERSE_PLANE,	//穿越警戒面 
	IVS_ENTER_AREA		= 1<<OFFSET_ENTER_AREA,		//目标进入区域，支持区域规则 
	IVS_EXIT_AREA		= 1<<OFFSET_EXIT_AREA,		//目标离开区域，支持区域规则 
	IVS_INTRUSION		= 1<<OFFSET_INTRUSION,		//周界入侵，支持区域规则 
	IVS_LOITER			= 1<<OFFSET_LOITER,			//徘徊，支持区域规则 
	IVS_LEFT_TAKE		= 1<<OFFSET_LEFT_TAKE,		//丢包捡包，支持区域规则 
	IVS_PARKING			= 1<<OFFSET_PARKING,		//停车，支持区域规则 
	IVS_RUN				= 1<<OFFSET_RUN,			//奔跑，支持区域规则 
	IVS_HIGH_DENSITY	= 1<<OFFSET_HIGH_DENSITY,	//区域内人员密度，支持区域规则 
	IVS_OIL_INTRUSION	= 1<<OFFSET_OIL_INTRUSION,	//油井入侵
	IVS_FIRE_SMOKE		= 1<<OFFSET_FIRE_SMOKE,		//烟火事件
	IVS_PEOPLE_COUNT	= 1<<OFFSET_PEOPLE_COUNT,	//人数统计
	IVS_PLATE_R			= 1<<OFFSET_PLATE_R,		//车牌识别
	IVS_CAM_HEALTH		= 1<<OFFSET_CAM_HEALTH,		//摄像机健康状况检测
	IVS_CAR_COUNT 		= 1<<OFFSET_CAR_COUNT,		//车流统计
	IVS_PLATE_R_SERVER	= 1<<OFFSET_PLATE_R_SERVER,	//车牌识别服务器
	IVS_AUTO_PTZ		= 1<<OFFSET_AUTO_PTZ,		//PTZ自动跟踪事件
	IVS_HJ_PIPE_WATER	= 1<<OFFSET_HJ_PIPE_WATER,	//环境废水
	IVS_HJ_BUBBLE	    = 1<<OFFSET_HJ_BUBBLE,		//环境气泡
	IVS_HJ_EXHAUST_GAS	= 1<<OFFSET_HJ_EXHAUST_GAS	//环境废气
}IVS_EVENT_TYPE;

#define NAME_LEN 32
typedef struct _VZ_IVS_RULE_INFO{
	BYTE                  byRuleID;
	BYTE				  byEnable;
	BYTE				  byDrawbyDSP;
	BYTE                  byRes[1];
	char                  byRuleName[NAME_LEN];
	IVS_RULE_TYPE         dwRuleType;
	VZ_IVS_EVENT_UNION    uEventParam;
}VZ_IVS_RULE_INFO;//事件规则信息

/////////////////////////////////////////

#define MAX_RULE_NUM	8
typedef struct _VZ_IVS_RULE_CFG{
	DWORD			 dwRuleNum;
	VZ_IVS_RULE_INFO struRules[MAX_RULE_NUM];
}VZ_IVS_RULE_CFG;


#define	VZ_IVS_DAY_MON  0x01
#define	VZ_IVS_DAY_TUE  0x02
#define	VZ_IVS_DAY_WED  0x04
#define	VZ_IVS_DAY_THU  0x08
#define	VZ_IVS_DAY_FRI  0x10
#define	VZ_IVS_DAY_SAT  0x20
#define	VZ_IVS_DAY_SUN  0x40
#define VZ_IVS_DAY_NULL	0x80	//表示使用每帧输入的时间戳来评估规则时间有效

typedef struct _VZ_IVS_TIME_PERIOD{
	BYTE uStartHour;
	BYTE uStartMinute;
	BYTE uEndHour;
	BYTE uEndMinute;
}VZ_IVS_TIME_PERIOD;

#define MAX_TIME_PERIOD_NUM	4
#define MAX_WEEK_DAY 7
typedef struct _VZ_IVS_RULE_TIME_INFO{
	VZ_IVS_TIME_PERIOD struPeriod[MAX_WEEK_DAY][MAX_TIME_PERIOD_NUM];
}VZ_IVS_RULE_TIME_INFO;

typedef struct _VZ_IVS_RULE_TIME_CFG{
	VZ_IVS_RULE_TIME_INFO struRuleTimes[MAX_RULE_NUM];
}VZ_IVS_RULE_TIME_CFG;

typedef struct _VZ_IVS_RULE_CFG_EX{
	DWORD			 dwRuleNum;
	VZ_IVS_RULE_INFO struRules[MAX_RULE_NUM];
	VZ_IVS_RULE_TIME_INFO struRuleTimes[MAX_RULE_NUM];
}VZ_IVS_RULE_CFG_EX;

typedef struct{
	DWORD          dwID;
	VZ_IVS_RECT   struRect;
	BYTE           byRes[4];
}VZ_IVS_TARGET_INFO;//报警目标信息


#define VZ_MAX_TARGET_NUM	32
//blob类型
#define VZ_BLOB_HUMAN	0
#define VZ_BLOB_CAR		1
#define VZ_BLOB_TRUCK	2
#define VZ_BLOB_ANIMAL	3
#define VZ_BLOB_WATER	4
#define VZ_BLOB_BUBBLE	5
#define VZ_BLOB_GAS		6


typedef struct VZ_IVS_TARGET
{
	int id;		//目标ID
	int kind;	//目标种类
	unsigned short x;	//矩形起点X值
	unsigned short y;	//矩形起点Y值
	unsigned short w;	//矩形宽度
	unsigned short h;	//矩形高度
	unsigned int dwBitsRules;		//按位对应ruleID，违规该为置1
	unsigned int dwBitsEvent;		//由IVS_EVENT_TYPE求或
	//判断该目标是否违规，就用dwBitsEvente而不用rulesFlag
}
VZ_IVS_TARGET;	//单个报警目标 size= 8+8+8 = 24

//报警信息
typedef struct VzTargetsInfo
{
	unsigned int num;
	VZ_IVS_TARGET tags[VZ_MAX_TARGET_NUM];
}
VzTargetsInfo;	//size = 24*32 + 4 = 772

#ifndef MAX_HIS_NUM
#define MAX_HIS_NUM		24
#endif

typedef struct VZ_IVS_TARGET_EXT
{
	VZ_IVS_TARGET ivsTarget;
	int motionKind;							//0为闯入，1为滞留
	int contrailLen;						//轨迹实际长度	//*/
	unsigned short contrailX[MAX_HIS_NUM];	//轨迹X
	unsigned short contrailY[MAX_HIS_NUM];	//轨迹Y
}
VZ_IVS_TARGET_EXT;	//size = 24 + 8 + 4*24*2 = 224

typedef struct VzTargetExtsInfo
{
	unsigned int num;
	VZ_IVS_TARGET_EXT tags[VZ_MAX_TARGET_NUM];
}
VzTargetExtsInfo;	//size = 4 + 224*32 = 

typedef enum VZ_ALARM_TYPE{
	VZ_ALARM_TYPE_NO_INFO,
	VZ_ALARM_TYPE_RULE,		//由报警规则触发的
	VZ_ALARM_TYPE_INPUT,	//由输入报警返回的
	VZ_ALARM_TYPE_PROTOCOL,	//由输入的协议数据触发的
	VZ_ALARM_TYPE_MAX
} VZ_ALARM_TYPE;

//智能视频
typedef struct _VZ_IVS_DRAWMODE{
	BYTE byDspAddTarget;		//dsp叠加报警目标
	BYTE byDspAddRule;			//dsp叠加设置规则
	BYTE byDspAddTrajectory;	//dsp叠加轨迹	
	BYTE dwRes[2];
}VZ_IVS_DRAWMODE;

#define IVS_MAX_MODE 4	//设备运行的最大模式数	
typedef struct _IVS_Ability_INFO_{
	int ModeNum;//模式数量
	int AbilityMask[IVS_MAX_MODE];//模式能力
}IVS_Ability_INFO;

typedef struct _VZ_IVS_EVENT_ABILITY{
	IVS_Ability_INFO ability_info;
	BYTE  byMaxRuleNum;		//最大规则数	
	BYTE  byMaxTargetNum;	//最大目标数
}VZ_IVS_EVENT_ABILITY;

//智能设备类型 
typedef enum _IVS_TYPE_{		
	IVS_NO				= 0,	//无智能视频版本
	IVS_OIL_BASE		= 1,	//油田基本版
	IVS_OIL_FULL		= 2,	//油田全功能版
	IVS_BEHAVIOR_BASE   = 3,	//行为分析基本版
	IVS_BEHAVIOR_FULL   = 4,    //行为分析全功能版
	IVS_ITS				= 5,	//智能交通设备
	IVS_FIRE			= 6,    //烟火识别
	IVS_ENHANCE			= 7,    //视频增强器
	IVS_ATM				= 8,	//ATM 智能设备
	IVS_CARCOUNT		= 9,	//车流统计设备
	IVS_CAMHEALTH_SERVER= 10,	//摄像机健康状况检测
	IVS_PLATER_CLIENT   = 11,	//车牌识别客户端
	IVS_PLATER_SERVER   = 12,	//车牌识别服务器
	IVS_PTZ				= 13,	//ptz跟踪器
	IVS_HJ_T212			= 14,	//环境监测智能设备
	IVS_PTZ_TA			= 15,	//PTZ跟踪器（十所（天奥））
	IVS_PCOUNT_SERVER	= 16,	//人数统计器
	IVS_BEHAVIOR_BASE_HELMET = 17,	//安全帽检测
	IVS_TYPE_NUM
}IVS_TYPE;

//--------------------end of vz alarm config-----------------------

//=======================通用智能规则命令======================
//由命令名称（必须）+智能类型（用于区分不同智能能力，如果需要）+编号（用于区分多次发出的相同命令，如果需要）
#define MAKE_IVS_CMD(CMD_NAME, IVS_TYPE, CMD_SN) ((((CMD_SN)&0xFF)<<16)|(((IVS_TYPE)&0xFF)<<8)|((CMD_NAME)&0xFF))

#define GET_IVS_CMD_NAME(CMD) ((CMD)&0xFF)

#define GET_IVS_CMD_IVS_TYPE(CMD) (((CMD)>>8)&0xFF)

#define GET_IVS_CMD_SN(CMD) (((CMD)>>16)&0xFF)

#define MAX_VZIVS_CTRL_CMD_BUF_LEN	1016
typedef struct
{
	unsigned int uCMD;		//IVS通用命令
	unsigned int uLenCMD;	//命令buf的长度
	unsigned char buf[MAX_VZIVS_CTRL_CMD_BUF_LEN];	//IVS通用命令的内容
}
VZ_IVS_CTRL;	//用于控制智能设备的通用命令结构体

//==================VS信息额外====================s
#define MAXNUM_CLIENT_INFO	256
//已连接的客户端信息
typedef struct VzClientInfo
{
	unsigned char ip[4];	//IP地址
}
VzClientInfo;

//信息表
typedef struct VzConnectedClients
{
	VzClientInfo clientInfo[MAXNUM_CLIENT_INFO];
	int count;
}
VzConnectedClients;

typedef struct IVSAlarmBuffer
{
	long tv_sec;
	long tv_usec;
	VzTargetsInfo targetsInfo;
}
IVSAlarmBuffer;		//size = 8+900 = 908

typedef struct IVSAlarmBufferExt
{
	long tv_sec;
	long tv_usec;
	int bTSTimeout;	//时间戳导致的规则无效
	VzTargetExtsInfo targetsInfo;
}
IVSAlarmBufferExt;

typedef struct RuleCountStatisInfo
{
	int ruleID;
	int L2RCount;
	int R2LCount;
}RuleCountStatisInfo;

typedef struct IVSCountStatisInfo
{
	long tv_sec_begin;
	long tv_usec_begin;
	int infoNum;
	RuleCountStatisInfo RuleStatisInfo[MAX_RULE_NUM];
}
IVSCountStatisInfo;


#define MAX_STRLEN_PROTOCOL_DETAIL	32
//基于协议数据的报警(VZ_ALARM_TYPE_PROTOCOL)返回的结构体
typedef struct _IVSProtocolInput
{
	char strDetail[MAX_STRLEN_PROTOCOL_DETAIL];		//详细的数据结构描述
	int sizeParam;	//数据结构尺寸（可作为校验）
	void *pParam;	//数据结构指针，参考与strDetail对应的头文件中定义的
}
IVSProtocolInput;

#endif
