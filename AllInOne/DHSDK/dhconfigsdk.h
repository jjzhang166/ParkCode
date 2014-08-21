
#ifndef DHCONFIGSDK_H
#define DHCONFIGSDK_H

#include "avglobal.h"
#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#ifdef DHCONFIGSDK_EXPORTS

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllexport) 
#endif

#else

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllimport)
#endif

#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#ifndef LLONG
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN32
#define LLONG LONG
#else //WIN64 
#define LLONG __int64
#endif
#else	//linux
#define LLONG long 
#endif
#endif

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN32
#define LDWORD DWORD
#else //WIN64 
#define LDWORD __int64
#endif
#else	//linux
#define LDWORD long 
#endif
#endif

#else	//linux

//#define CFG_RELEASE_HEADER	//发布头文件
#ifndef CFG_RELEASE_HEADER
#include "../Platform/platform.h"
#endif

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#endif


#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 ** 常量定义
 ***********************************************************************/

#define MAX_CHANNEL_COUNT		8
#define MAX_VIDEO_CHANNEL_NUM	256					// 最大通道数256
#define MAX_CHANNELNAME_LEN		32					// 最大通道名称长度
#define MAX_VIDEOSTREAM_NUM		3					// 最大码流个数
#define MAX_VIDEO_COVER_NUM		16					// 最大遮挡区域个数
#define WEEK_DAY_NUM			7					// 一周的天数
#define MAX_REC_TSECT			6					// 录像时间段个数
#define MAX_REC_TSECT_EX		10					// 录像时间段扩展个数
#define MAX_WATERMARK_LEN		4096				// 数字水印数据最大长度
#define MAX_MOTION_ROW			32					// 动态检测区域的行数
#define MAX_MOTION_COL			32					// 动态检测区域的列数
#define MAX_IMAGESIZE_NUM		256					// 最大支持的分辨率个数
#define MAX_FPS_NUM				1024				// 最大支持的帧率个数
#define MAX_QUALITY_NUM			32					// 最大支持的画质个数
#define MAX_ADDRESS_LEN			256					// 最大的地址长度
#define MAX_USERNAME_LEN		64					// 最大用户名长度
#define MAX_PASSWORD_LEN		64					// 最大密码长度
#define MAX_DIRECTORY_LEN		256					// 文件夹名字字符串长度
#define MAX_NAS_TIME_SECTION	2					// 网络存储时间段个数
#define MAX_NAME_LEN			128					// 通用名字字符串长度
#define MAX_DECPRO_LIST_SIZE	100					// 解码器协议列表个数上限
#define MAX_SCENE_LIST_SIZE		32					// 视频分析设备支持的场景类型列表个数上限
#define MAX_OBJECT_LIST_SIZE	16					// 视频分析设备支持的检测物体类型列表个数上限
#define MAX_RULE_LIST_SIZE		128					// 视频分析设备支持的规则列表个数上限
#define MAX_ANALYSE_MODULE_NUM	16					// 视频分析设备最大检测模块个数
#define MAX_ANALYSE_RULE_NUM	32					// 视频分析设备最大规则个数
#define MAX_POLYGON_NUM			20					// 视频分析设备区域顶点个数上限
#define MAX_POLYLINE_NUM		20					// 视频分析设备折线顶点个数上限
#define MAX_VEHICLE_SIZE_LIST	4					// 视频分析设备车辆大小个数上限
#define MAX_VEHICLE_TYPE_LIST	4					// 视频分析设备车辆类型个数上限
#define MAX_PLATE_TYPE_LIST		32					// 视频分析设备车牌类型个数上限
#define MAX_LANE_NUM            8                   // 视频分析设备每个通道对应车道数上限
#define MAX_STAFF_NUM           20                  // 视频分析设备每个通道对应的标尺数上限
#define MAX_CALIBRATEAREA_NUM   20					// 视频分析设备标定区域的上限
#define MAX_EXCLUDEREGION_NUM   10                  // 智能分析检测区域中需要排除的区域个数上限 
#define MAX_CALIBRATEBOX_NUM    10                  // 智能分析校准框个数上限
#define MAX_SPECIALDETECT_NUM    10                  // 智能分析特殊检测区域上限
#define MAX_HUMANFACE_LIST_SIZE	8					// 视频分析设备支持的人脸检测类型列表个数上限
#define	MAX_SEVER_NUM           16                  // 服务类型上限
#define MAX_SERVER_NAME_LEN     16                  // 服务名称字符串大小
#define MAX_POWER_NUM           8                   // 电源个数上限
#define MAX_FUN_NUM             8                   // 风扇个数上限
#define MAX_CPU_NUM             8                   // cpu个数上限
#define MAX_HARDDISK_NUM        32                  // 硬盘上限
#define MAX_TANK_NUM            16                  // 最大存储柜上限
#define MAX_CHAN_NUM            256                 // 最大通道数上限
#define MAX_RAID_NUM            16                  // 最大磁盘阵列上限
#define MAX_DEV_NUM             16                  // 最大设备上限
#define MAX_STORAGEPOOL_NUM     16                  // 最大存储池上限
#define MAX_STRORAGEPOS_NUM     16                  // 最大存储位置上限
#define	MAX_VIDEODEV_NUM        256                 // 前端设备上限
#define MAX_REMOTEDEVICENAME_LEN 32					// 最大远程设备名字长度
#define	MAX_REMOTE_DEV_NUM       64                 // 最大远程设备数量
#define MAX_PLATEHINT_NUM       8                   // 车牌字符暗示个数上限
#define MAX_LIGHT_NUM           8                   // 交通灯个数上限
#define MAX_LIGHTGROUP_NUM      8                   // 交通灯组个数上限
#define MAX_LIGHT_TYPE          8                   // 交通灯类型上限
#define MAX_LIGHT_DIRECTION     8                   // 交通灯指示方向数上限
#define MAX_TRIGGERMODE_NUM     32                  // 交通路口规则触发模式上限 
#define MAX_VIOLATIONCODE       16                  // 智能交通违章代码长度上限
#define MAX_DETECTOR            6                   // 智能交通车检器配置上限
#define MAX_COILCONFIG          3                   // 智能交通车检器线圈配置上限
#define MAX_DEVICE_ADDRESS      256                 // TrafficSnapshot智能交通设备地址
#define MAX_DEPARTMENT          256                 // Department智能交通设备所属单位
#define MAX_ROADWAYNO           128                 // 道路编号	由32个数字和字母构成
#define MAX_VIOLATIONCODE_DESCRIPT    64            // 智能交通违章代码长度上限
#define MAX_DRIVINGDIRECTION          256           // 行驶方向字符串长度
#define MAX_ACTIVEUSER_NUM            64            // 最大活动用户信息数
#define MAX_POLYGON_NUM10			10				// 视频分析设备区域顶点个数上限
#define MAX_VIDEODIAGNOSIS_DETECT_TYPE 11           // 视频诊断类型个数上限
#define MAX_ACTION_LIST_SIZE	16					// 视频分析设备支持的规则的动作类型列表个数上限
#define MAX_STORAGEGROUPNAME_LEN 32                 // 存储组名称缓冲区上限
#define MAX_CALIBRATEAREA_TYPE_NUM 4                // 标定区域类型上限
#define MAX_PROTOCOL_NAME_LEN	32					// 协议名称长度
#define	MAX_COMM_NUM			16					// 最大串口数量
#define MAX_DNS_SERVER_NUM		2					// DNS最大数量
#define MAX_NETWORK_INTERFACE_NUM	32				// 最大网卡数量
#define	MAX_NAS_NUM				16					// 网络存储服务器最大数量
#define MAX_STORAGEPOINT_NUM        32              // 录像存储点映射最大数量
#define MAX_TRACKSCENE_NUM          10              // 智能跟踪场景最大数量
#define MAX_STATUS_NUM          16                  // 交通设备状态最大个数
#define MAX_SERVICE_NUM         128                 // 服务器支持的最大服务数
#define MAX_DBKEY_NUM           64                  // 数据库关键字最大值
#define MAX_SUMMARY_LEN         1024                // 叠加到JPEG图片的摘要信息最大长度
#define MAX_MOTION_WINDOW       10                  // 动检支持的视频窗口值
#define MAX_OSD_SUMMARY_LEN     256                 // osd叠加内容最大长度    
#define MAX_OSD_TITLE_LEN       128                 // osd叠加标题最大长度
#define MAX_CUSTOMCASE_NUM      16                  // 自定义司法案件最大个数
#define MAX_GLOBAL_MSTERSLAVE_NUM   64              //主从式跟踪器最大全局配置数
#define MAX_OBJECT_ATTRIBUTES_SIZE	16			    // 视频分析设备支持的检测物体属性类型列表个数上限
#define MAX_MODEL_LEN			32					// 设备型号长度
#define MAX_BURNING_DEV_NUM		32			        // 最大刻录设备个数
#define MAX_NET_TYPE_NUM        8                   // 最大网络类型个数
#define MAX_NET_TYPE_LEN        64                  // 网络类型字符串长度 
#define MAX_DEVICE_NAME_LEN		64			        // 机器名称
#define MAX_DEV_ID_LEN_EX		128		            // 设备ID最大长度
#define MONTH_OF_YEAR			12					// 一年中月份数
#define MAX_SERVER_NUM          10                  // 服务器最大个数
#define MAX_REGISTER_NUM        10                  // 主动注册配置最大个数 
#define AV_CFG_Channel_Name_Len				64			// 通道名称长度
#define AV_CFG_Weekday_Num					7			// 一周天数
#define AV_CFG_Max_TimeSection				6			// 时间段数量
#define AV_CFG_Device_ID_Len				64			// 设备ID长度
#define AV_CFG_IP_Address_Len				32			// ip长度
#define AV_CFG_User_Name_Len				64			// 用户名长度
#define AV_CFG_Password_Len					64			// 密码长度
#define AV_CFG_Protocol_Len					32			// 协议名长度
#define AV_CFG_Serial_Len					32			// 序列号长度
#define AV_CFG_Device_Class_Len				16			// 设备类型长度
#define AV_CFG_Device_Type_Len				32			// 设备具体型号长度
#define AV_CFG_Device_Name_Len				64			// 机器名称
#define AV_CFG_Address_Len					128			// 机器部署地点
#define AV_CFG_Group_Name_Len				64			// 分区名称	
#define AV_CFG_Max_Path						260			// 路径长度
#define AV_CFG_Max_Split_Window				128			// 最大分割窗口数量
#define	AV_CFG_Monitor_Favorite_In_Channel	64			// 每个输出通道的最大轮训画面收藏数量
#define AV_CFG_Monitor_Favorite_Name_Len	64			// 画面收藏名称长度
#define AV_CFG_Max_Monitor_Favorite_Window	64			// 画面收藏的最大窗口数量
#define AV_CFG_Max_Split_Group				64			// 分割最大分组数量
#define AV_CFG_Max_Split_Mode				32			// 分割模式最大数量
#define AV_CFG_Raid_Name_Len				64			// RAID名称长度
#define AV_CFG_Max_Rail_Member				32			// 单个RAID包含磁盘数
#define AV_CFG_Max_Encode_Main_Format		3			// 主码流编码类型数
#define AV_CFG_Max_Encode_Extra_Format		3			// 辅码流编码类型数
#define	AV_CFG_Max_Encode_Snap_Format		3			// 抓图编码类型数
#define AV_CFG_Max_VideoColor				24			// 每个通道最大视频输入颜色配置数量
#define AV_CFG_Custom_Title_Len				256			// 自定义标题名称长度
#define AV_CFG_Max_Video_Widget_Cover		16			// 编码区域覆盖最大数量
#define AV_CFG_Max_Video_Widget_Custom_Title 4			// 编码物件自定义标题最大数量
#define AV_CFG_Group_Name_Len				64			// 分组名称长度
#define AV_CFG_Group_Memo_Len				128			// 分组说明长度
#define AV_CFG_Max_Channel_Num				1024		// 最大通道数量
#define AV_CFG_Time_Format_Len				32			// 时间格式长度
#define AV_CFG_Max_White_List				1024		// 白名单数量
#define AV_CFG_Max_Black_List				1024		// 黑名单数量
#define AV_CFG_Filter_IP_Len				96			// 过滤IP最大长度
#define AV_CFG_Max_ChannelRule				32			// 通道存储规则最大长度, 仅通道部分
#define AV_CFG_Max_DBKey_Num				64			// 事件关键字数量
#define AV_CFG_DBKey_Len					32			// 事件关键字长度
#define AV_CFG_Max_Summary_Len				1024		// 摘要长度
#define AV_CFG_Max_Event_Title_Num			32			// 事件标题最大数量
#define AV_CFG_Max_Tour_Link_Num			128			// 联动轮巡最大数量
#define AV_CFG_PIP_BASE						1000		// 画中画分割模式基础值


#define AV_CFG_Local_Device_ID				"Local"		// 本地设备ID
#define AV_CFG_Remote_Devce_ID				"Remote"	// 远程设备ID   

/************************************************************************
 ** 配置命令 对应CLIENT_GetNewDevConfig和CLIENT_SetNewDevConfig接口
 ***********************************************************************/

#define CFG_CMD_ENCODE			"Encode"			// 图像通道属性配置(对应CFG_ENCODE_INFO)
#define CFG_CMD_RECORD			"Record"			// 定时录像配置(对应CFG_RECORD_INFO)
#define CFG_CMD_ALARMINPUT		"Alarm"				// 外部输入报警配置(对应CFG_ALARMIN_INFO)
#define CFG_CMD_NETALARMINPUT	"NetAlarm"			// 网络报警配置(对应CFG_NETALARMIN_INFO)
#define CFG_CMD_MOTIONDETECT	"MotionDetect"		// 动态检测报警配置(对应CFG_MOTION_INFO)
#define CFG_CMD_VIDEOLOST		"LossDetect"		// 视频丢失报警配置(对应CFG_VIDEOLOST_INFO)
#define CFG_CMD_VIDEOBLIND		"BlindDetect"		// 视频遮挡报警配置(对应CFG_SHELTER_INFO)
#define CFG_CMD_STORAGENOEXIST	"StorageNotExist"	// 无存储设备报警配置(对应CFG_STORAGENOEXIST_INFO)
#define CFG_CMD_STORAGEFAILURE	"StorageFailure"	// 存储设备访问出错报警配置(对应CFG_STORAGEFAILURE_INFO)
#define CFG_CMD_STORAGELOWSAPCE	"StorageLowSpace"	// 存储设备空间不足报警配置(对应CFG_STORAGELOWSAPCE_INFO)
#define CFG_CMD_NETABORT		"NetAbort"			// 网络断开报警配置(对应CFG_NETABORT_INFO)	
#define CFG_CMD_IPCONFLICT		"IPConflict"		// IP冲突报警配置(对应CFG_IPCONFLICT_INFO)
#define CFG_CMD_SNAPCAPINFO		"SnapInfo"			// 抓图能力查询(对应CFG_SNAPCAPINFO_INFO)
#define CFG_CMD_NAS				"NAS"				// 网络存储服务器配置(对应CFG_NAS_INFO)
#define CFG_CMD_PTZ				"Ptz"				// 云台配置(对应CFG_PTZ_INFO)
#define CFG_CMD_WATERMARK		"WaterMark"			// 视频水印配置(对应CFG_WATERMARK_INFO)
#define CFG_CMD_ANALYSEGLOBAL	"VideoAnalyseGlobal"// 视频分析全局配置(对应CFG_ANALYSEGLOBAL_INFO)
#define CFG_CMD_ANALYSEMODULE	"VideoAnalyseModule"// 物体的检测模块配置(对应CFG_ANALYSEMODULES_INFO)
#define CFG_CMD_ANALYSERULE		"VideoAnalyseRule"	// 视频分析规则配置(对应CFG_ANALYSERULES_INFO)
#define CFG_CMD_ANALYSESOURCE	"VideoAnalyseSource"// 视频分析资源配置(对应CFG_ANALYSESOURCE_INFO)
#define CFG_CMD_RAINBRUSH       "RainBrush"         // 雨刷配置(对应CFG_RAINBRUSH_INFO)
#define CFG_CMD_INTELLECTIVETRAFFIC "TrafficSnapshot" // 智能交通抓拍(CFG_TRAFFICSNAPSHOT_INFO只为兼容老协议；请使用CFG_CMD_TRAFFICSNAPSHOT_MULTI)
#define CFG_CMD_TRAFFICGLOBAL   "TrafficGlobal"     // 智能交通全局配置(CFG_TRAFFICGLOBAL_INFO)
#define CFG_CMD_DEV_GENERRAL    "General"           // 普通配置 (CFG_DEV_DISPOSITION_INFO)
#define CFG_CMD_ATMMOTION		"FetchMoneyOverTime"// ATM取款超时配置(对应CFG_ATMMOTION_INFO)
#define CFG_CMD_DEVICESTATUS    "DeviceStatus"      // 设备状态信息(对应CFG_DEVICESTATUS_INFO)
#define CFG_CMD_HARDDISKTANK    "HardDiskTank"      // 扩展柜信息(对应CFG_HARDISKTANKGROUP_INFO)
#define CFG_CMD_RAIDGROUP       "RaidGroup"         // Raid组信息(对应CFG_RAIDGROUP_INFO)
#define CFG_CMD_STORAGEPOOLGROUP "StoragePoolGroup" // 存储池组信息(对应CFG_STORAGEPOOLGROUP_INFO)
#define CFG_CMD_STORAGEPOSITIONGROUP  "StoragePositionGroup"  // 文件系统组信息(对应CFG_STORAGEPOSITIONGROUP_INFO)
#define CFG_CMD_VIDEOINDEVGROUP "VideoInDevGroup"   // 前端设备组信息(对应CFG_VIDEOINDEVGROUP_INFO)
#define CFG_CMD_DEVRECORDGROUP  "DevRecordGroup"    // 通道录像组状态(对应CFG_DEVRECORDGROUP_INFO)
#define CFG_CMD_IPSSERVER       "IpsServer"         // 服务状态(对应CFG_IPSERVER_STATUS)
#define CFG_CMD_SNAPSOURCE		"SnapSource"		// 抓图源配置(对应CFG_SNAPSOURCE_INFO)
#define CFG_CMD_DHRADER         "DahuaRadar"        // 大华雷达配置
#define CFG_CMD_TRANSRADER       "TransRadar"       // 川苏雷达配置
#define CFG_CMD_LANDUNRADER      "LanDunRadar"      // 蓝盾雷达配置
#define CFG_CMD_LANDUNCOILS      "LanDunCoils"      // 蓝盾线圈配置
#define CFG_CMD_MATRIX_SPOT      "SpotMatrix"       // Spot视屏矩阵(对应CFG_VIDEO_MATRIX)
#define CFG_CMD_HDVR_DSP         "DspEncodeCap"     // HDVR传每个数字通道的dsp信息 数字通道可以连IPC或DVR 也就是IPC或DVR的能力(对应CFG_DSPENCODECAP_INFO)
#define CFG_CMD_HDVR_ATTR_CFG    "SystemAttr"       // HDVR传每个数字通道的所连设备的信息
#define CFG_CMD_CHANNEL_HOLIDAY  "HolidaySchedule"  // 假期录像计划(对应结构体CFG_HOLIDAY_SCHEDULE数组)
#define CFG_CMD_HEALTH_MAIL      "HealthMail"       // 健康邮件
#define CFG_CMD_CAMERAMOVE       "IntelliMoveDetect"      // 摄像机移位侦测联动 
#define CFG_CMD_SPLITTOUR        "SplitTour"        // 视频分割轮巡配置(对应CFG_VIDEO_MATRIX)
#define CFG_CMD_VIDEOENCODEROI   "VideoEncodeROI"   // 视频编码ROI(Region of Intrest)配置
#define CFG_CMD_VIDEO_INMETERING "VideoInMetering"  // 测光配置(对应CFG_VIDEO_INMETERING_INFO)
#define CFG_CMD_TRAFFIC_FLOWSTAT "TrafficFlowStat"  // 交通流量统计配置(对应CFG_TRAFFIC_FLOWSTAT_INFO)
#define CFG_CMD_HDMIMATRIX        "HDMIMatrix"      // HDMI视频矩阵配置
#define CFG_CMD_VIDEOINOPTIONS	 "VideoInOptions"	// 视频输入前端选项(对应CFG_VIDEO_IN_OPTIONS)
#define CFG_CMD_RTSP             "RTSP"             // RTSP的配置( 对应CFG_RTSP_INFO_IN和CFG_RTSP_INFO_OUT )
#define CFG_CMD_TRAFFICSNAPSHOT  "TrafficSnapshotNew"// 智能交通抓拍(CFG_TRAFFICSNAPSHOT_INFO 废除，请使用CFG_CMD_TRAFFICSNAPSHOT_MULTI)
#define CFG_CMD_TRAFFICSNAPSHOT_MULTI  "TrafficSnapshotNew"// 智能交通抓拍(CFG_TRAFFICSNAPSHOT_NEW_INFO)
#define CFG_CMD_MULTICAST        "Multicast"         // 组播的相关配置(对应CFG_MULTICASTS_INFO_IN和CFG_MULTICASTS_INFO_OUT)
#define CFG_CMD_VIDEODIAGNOSIS_PROFILE   "VideoDiagnosisProfile"		// 视频诊断参数表(CFG_VIDEODIAGNOSIS_PROFILE)
#define CFG_CMD_VIDEODIAGNOSIS_TASK	      "VideoDiagnosisTask"			// 视频诊断任务表(CFG_VIDEODIAGNOSIS_TASK)
#define CFG_CMD_VIDEODIAGNOSIS_PROJECT    "VideoDiagnosisProject"		// 视频诊断计划表(CFG_VIDEODIAGNOSIS_PROJECT)
#define CFG_CMD_VIDEODIAGNOSIS_GLOBAL     "VideoDiagnosisGlobal"		// 视频诊断全局表(CFG_VIDEODIAGNOSIS_GLOBAL)
#define CFG_CMD_VIDEODIAGNOSIS_TASK_ONE   "VideoDiagnosisTask.x"	    // 视频诊断任务表(CFG_VIDEODIAGNOSIS_TASK)
#define CFG_CMD_TRAFFIC_WORKSTATE         "WorkState"                   // 设备工作状态相关配置(对应CFG_TRAFFIC_WORKSTATE_INFO)
#define CFG_CMD_STORAGEDEVGROUP           "StorageDevGroup"             // 磁盘存储组配置(对应CFG_STORAGEGROUP_INFO)
#define CFG_CMD_RECORDTOGROUP             "RecordToGroup"               // 录像存放的存储组配置(对应CFG_RECORDTOGROUP_INFO)
#define CFG_CMD_INTELLITRACKSCENE         "IntelliTrackScene"           // 智能跟踪场景配置(CFG_INTELLITRACKSCENE_INFO) 
#define CFG_CMD_IVSFRAM_RULE              "IVSFramRule"                 // 智能帧规则配置(对应CFG_ANALYSERULES_INFO)
#define CFG_CMD_RECORD_STORAGEPOINT       "RecordStoragePoint"          //录像存储点映射配置(对应CFG_RECORDTOSTORAGEPOINT_INFO)
#define CFG_CMD_MD_SERVER		          "MetaDataServer"	            //元数据服务器配置(对应CFG_METADATA_SERVER结构体)
#define CFG_CMD_CHANNELTITLE	"ChannelTitle"		// 通道名称(对应AV_CFG_ChannelName)
#define	CFG_CMD_RECORDMODE		"RecordMode"		// 录像模式(对应AV_CFG_RecordMode)
#define CFG_CMD_VIDEOOUT		"VideoOut"			// 视频输出属性(对应AV_CFG_VideoOutAttr)
#define CFG_CMD_REMOTEDEVICE    "RemoteDevice"		// 远程设备信息(对应AV_CFG_RemoteDevice数组, 通道无关)
#define CFG_CMD_REMOTECHANNEL	"RemoteChannel"		// 远程通道(对应AV_CFG_RemoteChannel)
#define CFG_CMD_MONITORTOUR		"MonitorTour"		// 画面轮训配置(对应AV_CFG_MonitorTour)
#define CFG_CMD_MONITORCOLLECTION	"MonitorCollection"	// 画面收藏配置(对应AV_CFG_MonitorCollection)
#define CFG_CMD_DISPLAYSOURCE	"DisplaySource"		// 画面分割显示源配置(对应AV_CFG_ChannelDisplaySource)(废除，不建议使用)
#define CFG_CMD_RAID			"Raid"				// 存储卷组配置(对应AV_CFG_Raid数组, 通道无关)
#define CFG_CMD_RECORDSOURCE	"RecordSource"		// 录像源配置(对应AV_CFG_RecordSource)
#define CFG_CMD_VIDEOCOLOR		"VideoColor"		// 视频输入颜色配置(对应AV_CFG_ChannelVideoColor)
#define CFG_CMD_VIDEOWIDGET		"VideoWidget"		// 视频编码物件配置(对应AV_CFG_VideoWidget)
#define CFG_CMD_STORAGEGROUP	"StorageGroup"		// 存储组信息(对应AV_CFG_StorageGroup数组, 通道无关)
#define CFG_CMD_LOCALS			"Locales"			// 区域配置(对应AV_CFG_Locales)
#define CFG_CMD_LANGUAGE		"Language"			// 语言选择(对应AV_CFG_Language)
#define CFG_CMD_ACCESSFILTER	"AccessFilter"		// 访问地址过滤(对应AV_CFG_AccessFilter)
#define CFG_CMD_AUTOMAINTAIN	"AutoMaintain"		// 自动维护(对应AV_CFG_AutoMaintain)
#define CFG_CMD_REMOTEEVENT		"RemoteEvent"		// 远程设备事件处理(对应AV_CFG_RemoteEvent数组)
#define CFG_CMD_MONITORWALL		"MonitorWall"		// 电视墙配置(对应AV_CFG_MonitorWall数组, 通道无关)
#define	CFG_CMD_SPLICESCREEN	"VideoOutputComposite"		// 融合屏配置(对应AV_CFG_SpliceScreen数组, 通道无关)
#define CFG_CMD_TEMPERATUREALARM	"TemperatureAlarm"		// 温度报警配置(对应AV_CFG_TemperatureAlarm, 通道无关)
#define	CFG_CMD_FANSPEEDALARM		"FanSpeedAlarm"			// 风扇转速报警配置(对应AV_CFG_FanSpeedAlarm, 通道无关)
#define CFG_CMD_RECORDBACKUP		"RecordBackupRestore"	// 录像回传配置(对应AV_CFG_RecordBackup, 通道无关)
#define CFG_CMD_COMM			    "Comm"				// 串口配置(对应CFG_COMMGROUP_INFO)
#define	CFG_CMD_NETWORK			    "Network"			// 网络配置(对应CFG_NETWORK_INFO)
#define CFG_CMD_NASEX			    "NAS"				// 网络存储服务器配置, 多服务器(对应CFG_NAS_INFO_EX)
#define CFG_CMD_LDAP                "LDAP"              // LDAP配置
#define CFG_CMD_ACTIVE_DIR          "ActiveDirectory"   // 活动目录配置
#define CFG_CMD_FLASH               "FlashLight"        // 补光灯配置(对应 CFG_FLASH_LIGHT)
#define CFG_CMD_AUDIO_ANALYSERULE   "AudioAnalyseRule"  // 音频分析规则配置(对应 CFG_ANALYSERULES_INFO)
#define CFG_CMD_JUDICATURE          "Judicature"        // 司法刻录配置(对应 CFG_JUDICATURE_INFO)
#define CFG_CMD_GOODS_WEIGHT		"CQDTSet"			// 车载货重配置(对应CFG_GOOD_WEIGHT_INFO)
#define CFG_CMD_VIDEOIN				"VideoIn"			// 输入通道配置(对应CFG_VIDEO_IN_INFO)
#define CFG_CMD_ENCODEPLAN          "EncodePlan"        // 刻录光盘编码计划(对应 CFG_ENCODE_PLAN_INFO)
#define CFG_CMD_PICINPIC            "PicInPic"          // 司法审讯画中画(对应 CFG_PICINPIC_INFO)
#define CFG_CMD_BURNFULL            "BurnFull"          // 刻录满事件配置(对应 CFG_BURNFULL_INFO)
#define CFG_CMD_MASTERSLAVE_GLOBAL  "MasterSlaveTrackerGlobal"   //主从式全局配置（对应）
#define CFG_CMD_ANALYSEWHOLE	"VideoAnalyseWhole"  // 视频分析整体配置(对应CFG_ANALYSEWHOLE_INFO)
#define CFG_CMD_VIDEO_IN_BOUNDARY	"VideoInBoundary"	// 视频输入边界配置(对应CFG_VIDEO_IN_BOUNDARY)
#define	CFG_CMD_MONITORWALL_COLLECTION	"MonitorWallCollection"	// 电视墙预案(对应CFG_MONITORWALL_COLLECTION数组)
#define CFG_CMD_ANALOGMATRIX		"AnalogMatrix"		// 模拟矩阵(对应CFG_ANALOG_MATRIX_INFO)
#define CFG_CMD_ANALOG_MATRIX_PROTOCOL	"AnalogMatrixProtocol"	// 模拟矩阵协议配置(对应CFG_ANALOG_MATRIX_PROTOCOL数组)
#define	CFG_CMD_VIDEO_OUT_TITLE		"VideoOutputTitle"		// 视频输出标题(对应CFG_VIDEO_OUT_TITLE)
#define CFG_CMD_DISK_FLUX_ALARM		"DiskFluxAlarm"		// 硬盘数据流量报警配置(对应CFG_DISK_FLUX_INFO)
#define CFG_CMD_NET_FLUX_ALARM		"NetFluxAlarm"		// 网络数据流量报警配置(对应CFG_NET_FLUX_INFO)
#define CFG_CMD_DVRIP               "DVRIP"             // 网络协议配置(对应CFG_DVRIP_INFO)
#define CFG_CMD_PARKINGSPACE_SCREEN "ParkingSpaceScreen"// 和相机对接的区域屏配置(对应 CFG_PARKINGSPACE_SCREEN_INFO ,是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen)
#define CFG_CMD_PARKINGSPACE_STATUS "ParkingSpaceCellStatus"// 车位设置(专有车位和普通车位设置)(对应 CFG_PARKINGSPACE_STATUS_INFO ，是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxRoadWays)
#define CFG_CMD_CLIENT_CUSTOM_DATA  "ClientCustomData"  // 平台自定义信息(对应 CFG_CLIENT_CUSTOM_INFO)
#define CFG_CMD_BURN_RECORD_FORMAT  "BurnRecordFormat"  // 刻录格式配置(对应 CFG_BURN_RECORD_FORMAT)
#define CFG_CMD_MULTIBURN           "MultiBurn"         // 多光盘同步刻录(对应 CFG_MULTIBURN_INFO)是一个数组，每一个元素表示一组多光盘同步刻录及校验

 /************************************************************************
 ** 能力集命令  对应CLIENT_QueryNewSystemInfo
 ***********************************************************************/

#define CFG_CAP_CMD_VIDEOANALYSE "devVideoAnalyse.getCaps"			// 视频分析能力集(对应CFG_CAP_ANALYSE_INFO)
#define CFG_NETAPP_REMOTEDEVICE	 "netApp.getRemoteDeviceStatus"		// 获取后端设备的的在线状态(对应CFG_REMOTE_DEVICE_STATUS)
#define CFG_CAP_CMD_PRODUCTDEFINITION "magicBox.getProductDefinition"	// 接入设备信息
#define CFG_DEVICE_CAP_CMD_VIDEOANALYSE "intelli.getVideoAnalyseDeviceChannels"   // 设备智能分析能力(对应CFG_CAP_DEVICE_ANALYSE_INFO)兼容老设备
#define CFG_DEVICE_CAP_NEW_CMD_VIDEOANALYSE "devVideoAnalyse.factory.getCollect"  // 设备智能分析能力(对应CFG_CAP_DEVICE_ANALYSE_INFO)
#define CFG_CAP_CMD_CPU_COUNT  "magicBox.getCPUCount"               // 获得CPU个数
#define CFG_CAP_CMD_CPU_USAGE  "magicBox.getCPUUsage"               // 获取CPU占用率
#define CFG_CAP_CMD_MEMORY_INFO  "magicBox.getMemoryInfo"           // 获得内存容量
#define CFG_CAP_CMD_DEVICE_STATE "trafficSnap.getDeviceStatus"      // 获取设备状态信息 (对应CFG_CAP_TRAFFIC_DEVICE_STATUS)
#define CFG_CAP_CMD_VIDEOINPUT "devVideoInput.getCaps"              // 视频输入能力集(对应CFG_CAP_VIDEOINPUT_INFO)
#define CFG_USERMANAGER_ACTIVEUSER    "userManager.getActiveUserInfoAll"      // 得到所有活动的用户信息(对应CFG_ACTIVEUSER_INFO)
#define CFG_CAP_VIDEOSTAT_SUMMARY     "videoStatServer.getSummary"            // 获取视频统计摘要信息(对应CFG_VIDEOSATA_SUMMARY_INFO)
#define CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER "videoDiagnosisServer.getCaps"			// 获取视频诊断服务能力(CFG_VIDEODIAGNOSIS_CAPS_INFO)
#define CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT          "videoDiagnosisServer.factory.getCollect"             // 获取视频诊断通道数目(CFG_VIDEODIAGNOSIS_GETCOLLECT_INFO)
#define CFG_CMD_VIDEODIAGNOSIS_GETSTATE            "videoDiagnosisServer.getState"                       // 获取视频诊断进行状态(CFG_VIDEODIAGNOSIS_STATE_INFO)
#define CFG_CAP_CMD_SERVICE_LIST                   "system.listService"        //获取服务器上支持的服务列表(CFG_DEV_SERVICE_LIST)
#define CFG_CAP_CMD_EVENTHANDLER    "capsManager.get&EventManagerEventHandler"       // 获取服务器报警联动能力集(CFG_CAP_EVENTHANDLER_INFO)
#define CFG_CAP_ALARM               "alarm.getAlarmCaps"                             // 获取报警能力集(CFG_CAP_ALARM_INFO)
#define CFG_CAP_CMD_AUDIO_ANALYSE   "devAudioAnalyse.getCaps"                        // 获取音频分析能力集(CFG_CAP_AUDIO_ANALYSE_INFO)
#define CFG_CMD_MASTERSLAVE_GETCOLLECT        "masterSlaveTracker.factory.getCollect"    // 获取主从式跟踪器通道数目(对应结构体CFG_MASTERSLAVETRACKER_INFO)
#define CFG_CAP_CMD_MASTERSLAVE               "capsManager.get&MasterSlaveTracker"       // 获取主从式设备能力集(CFG_CAP_MASTERSLAVE_INFO)
#define CFG_CAP_CMD_FOCUS_STATE		"devVideoInput.getFocusStatus"						// 获取镜头聚焦状态信息 (对应CFG_CAP_FOCUS_STATUS)
#define CFG_CAP_CMD_NETAPP          "netApp.getCaps"                                    // 获取网络应用能力集(对应CFG_CAP_NETAPP)
#define CFG_CAP_CMD_PTZ_ENABLE  	"ptz.factory.instance"					// 获取云台支持信息(CFG_CAP_PTZ_ENABLEINFO )
#define CFG_CAP_CMD_RECORD			"recordManager.getCaps"                 // 获取录像能力集(CFG_CAP_RECORD_INFO)
#define CFG_CAP_CMD_BURN_MANAGER    "BurnManager.getCaps"                   // 获取刻录管理能力集( CFG_CAP_BURN_MANAGER)
 /************************************************************************
 ** fAnalyzerData回调函数dwDataType类型定义
 ***********************************************************************/
#define    TYPE_CB_VIDEOSTAT      0x1000000      // 回调解析视频信息摘要类型，对应结构体为CFG_VIDEOSATA_SUMMARY_INFO 
#define    TYPE_CB_ANARULES       0x1000001      // 回调解析视频输入通道对应的所有事件规则类型，对应结构体为CFG_ANALYSERULES_INFO
#define    TYPE_CB_VIDEOSYNOPSIS  0x1000002	     // 回调解析浓缩视频的智能帧，对应结构体DH_MSG_OBJECT

/************************************************************************
 ** 配置信息(每个结构体都有能力信息，以区分不同设备程序版本和不同型号设备)
 ***********************************************************************/
// 协议版本信息
enum 
{
	CFG_PROTOCOL_VERSION_2 = 2,						// 二代协议
	CFG_PROTOCOL_VERSION_3 = 3						// 三代协议
};

// 视频输入通道
struct CFG_RemoteDeviceVideoInput 
{
	BOOL			bEnable;
	char			szName[MAX_DEVICE_NAME_LEN];
	char			szControlID[MAX_DEV_ID_LEN_EX];
	char			szMainUrl[MAX_PATH];			// 主码流url地址
	char			szExtraUrl[MAX_PATH];			// 辅码流url地址
	int				nServiceType;					// 服务类型, 0-TCP, 1-UDP, 2-MCAST, -1-AUTO
};

// 远程设备
struct AV_CFG_RemoteDevice 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szID[AV_CFG_Device_ID_Len];		// 设备ID
	char				szIP[AV_CFG_IP_Address_Len];	// 设备IP
	AV_int32			nPort;							// 端口
	char				szProtocol[AV_CFG_Protocol_Len];// 协议类型
	char				szUser[AV_CFG_User_Name_Len];	// 用户名
	char				szPassword[AV_CFG_Password_Len];// 密码
	char				szSerial[AV_CFG_Serial_Len];	// 设备序列号
	char				szDevClass[AV_CFG_Device_Class_Len];// 设备类型
	char				szDevType[AV_CFG_Device_Type_Len];	// 设备型号
	char				szName[AV_CFG_Device_Name_Len];	// 机器名称
	char				szAddress[AV_CFG_Address_Len];	// 机器部署地点
	char				szGroup[AV_CFG_Group_Name_Len];	// 机器分组
	AV_int32			nDefinition;					// 清晰度, 0-标清, 1-高清
	AV_int32			nVideoChannel;					// 视频输入通道数
	AV_int32			nAudioChannel;					// 音频输入通道数
	AV_int32            nRtspPort;                      // Rtsp端口号
	char                szVendor[MAX_PATH];             // 设备接入类型
	CFG_RemoteDeviceVideoInput *pVideoInput;            // 视频输入通道，用户申请nMaxVideoInputs个CFG_RemoteDeviceVideoInput空间
	int                 nMaxVideoInputs;
	int                 nRetVideoInputs;
};

//-----------------------------图像通道属性-------------------------------

// 画质
typedef enum tagCFG_IMAGE_QUALITY
{
	IMAGE_QUALITY_Q10 = 1,							// 图像质量10%
	IMAGE_QUALITY_Q30,								// 图像质量30%
	IMAGE_QUALITY_Q50,								// 图像质量50%
	IMAGE_QUALITY_Q60,								// 图像质量60%
	IMAGE_QUALITY_Q80,								// 图像质量80%
	IMAGE_QUALITY_Q100,								// 图像质量100%
} CFG_IMAGE_QUALITY;

// 视频压缩格式
typedef enum tagCFG_VIDEO_COMPRESSION
{
	VIDEO_FORMAT_MPEG4,								// MPEG4
	VIDEO_FORMAT_MS_MPEG4,							// MS-MPEG4
	VIDEO_FORMAT_MPEG2,								// MPEG2
	VIDEO_FORMAT_MPEG1,								// MPEG1
	VIDEO_FORMAT_H263,								// H.263
	VIDEO_FORMAT_MJPG,								// MJPG
	VIDEO_FORMAT_FCC_MPEG4,							// FCC-MPEG4
	VIDEO_FORMAT_H264,								// H.264
} CFG_VIDEO_COMPRESSION;
// 音频编码模式
typedef enum tatCFG_AUDIO_FORAMT
{
	AUDIO_FORMAT_G711A,                              // G711a
    AUDIO_FORMAT_PCM,                                // PCM
    AUDIO_FORMAT_G711U,                              // G711u
    AUDIO_FORMAT_AMR,                                // AMR
    AUDIO_FORMAT_AAC,                                // AAC
} CFG_AUDIO_FORMAT;

// 码流控制模式
typedef enum tagCFG_BITRATE_CONTROL
{
	BITRATE_CBR,									// 固定码流
	BITRATE_VBR,									// 可变码流
} CFG_BITRATE_CONTROL;

// 分辨率枚举
typedef enum tagCFG_CAPTURE_SIZE
{
	IMAGE_SIZE_D1,								// 704*576(PAL)  704*480(NTSC)
	IMAGE_SIZE_HD1,								// 352*576(PAL)  352*480(NTSC)
	IMAGE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	IMAGE_SIZE_CIF,								// 352*288(PAL)  352*240(NTSC)
	IMAGE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	IMAGE_SIZE_VGA,								// 640*480
	IMAGE_SIZE_QVGA,							// 320*240
	IMAGE_SIZE_SVCD,							// 480*480
	IMAGE_SIZE_QQVGA,							// 160*128
	IMAGE_SIZE_SVGA,							// 800*592
	IMAGE_SIZE_XVGA,							// 1024*768
	IMAGE_SIZE_WXGA,							// 1280*800
	IMAGE_SIZE_SXGA,							// 1280*1024  
	IMAGE_SIZE_WSXGA,							// 1600*1024  
	IMAGE_SIZE_UXGA,							// 1600*1200
	IMAGE_SIZE_WUXGA,							// 1920*1200
	IMAGE_SIZE_LTF,								// 240*192
	IMAGE_SIZE_720,								// 1280*720
	IMAGE_SIZE_1080,							// 1920*1080
	IMAGE_SIZE_1_3M,							// 1280*960
	IMAGE_SIZE_2M,							    // 1872*1408
	IMAGE_SIZE_5M,						   	    // 3744*1408
	IMAGE_SIZE_3M,							    // 2048*1536
	IMAGE_SIZE_5_0M,                            // 2432*2050
	IMAGE_SIZE_1_2M,							// 1216*1024
	IMAGE_SIZE_1408_1024,                       // 1408*1024
	IMAGE_SIZE_8M,                              // 3296*2472
	IMAGE_SIZE_2560_1920,                       // 2560*1920(5M)
	IMAGE_SIZE_960H,                            // 960*576(PAL) 960*480(NTSC)
	IMAGE_SIZE_960_720,                         // 960*720
	IMAGE_SIZE_NHD,							    // 640*360
	IMAGE_SIZE_QNHD,							// 320*180
	IMAGE_SIZE_QQNHD,							// 160*90
	IMAGE_SIZE_NR  
} CFG_CAPTURE_SIZE;

// 视频格式
typedef struct tagCFG_VIDEO_FORMAT
{
	// 能力
	bool				abCompression;
	bool				abWidth;
	bool				abHeight;
	bool				abBitRateControl;
	bool				abBitRate;
	bool				abFrameRate;
	bool				abIFrameInterval;
	bool				abImageQuality;
	bool				abFrameType;

	// 信息
	CFG_VIDEO_COMPRESSION emCompression;			// 视频压缩格式
	int					nWidth;						// 视频宽度
	int					nHeight;					// 视频高度
	CFG_BITRATE_CONTROL	emBitRateControl;			// 码流控制模式
	int					nBitRate;					// 视频码流(kbps)
	int					nFrameRate;					// 视频帧率
	int					nIFrameInterval;			// I帧间隔(1-100)，比如50表示每49个B帧或P帧，设置一个I帧。
	CFG_IMAGE_QUALITY	emImageQuality;				// 图像质量
	int					nFrameType;					// 打包模式，0－DHAV，1－"PS"
} CFG_VIDEO_FORMAT;

// 音频格式
typedef struct tagCFG_AUDIO_FORMAT 
{
	// 能力
	bool				abCompression;
	bool				abDepth;
	bool				abFrequency;
	bool				abMode;
	bool				abFrameType;
	bool				abPacketPeriod;

	// 信息
	CFG_AUDIO_FORMAT	emCompression;				// 音频压缩模式
	AV_int32			nDepth;						// 音频采样深度
	AV_int32			nFrequency;					// 音频采样频率
	AV_int32			nMode;						// 音频编码模式
	AV_int32			nFrameType;					// 音频打包模式, 0-DHAV, 1-PS
	AV_int32			nPacketPeriod;				// 音频打包周期, ms
} CFG_AUDIO_ENCODE_FORMAT;

// 视频编码参数
typedef struct tagCFG_VIDEOENC_OPT
{
	// 能力
	bool				abVideoEnable;
	bool				abAudioEnable;
	bool				abSnapEnable;
	bool                abAudioAdd;                 // 音频叠加能力
	bool				abAudioFormat;

	// 信息
	BOOL				bVideoEnable;				// 视频使能
	CFG_VIDEO_FORMAT	stuVideoFormat;				// 视频格式
	BOOL				bAudioEnable;				// 音频使能
	BOOL				bSnapEnable;				// 定时抓图使能
	BOOL                bAudioAddEnable;            // 音频叠加使能
	CFG_AUDIO_ENCODE_FORMAT	stuAudioFormat;			// 音频格式
} CFG_VIDEOENC_OPT;

// RGBA信息
typedef struct tagCFG_RGBA
{
	int					nRed;
	int					nGreen;
	int					nBlue;
	int					nAlpha;
} CFG_RGBA;

// 区域信息
typedef struct tagCFG_RECT
{
	int					nLeft;
	int					nTop;
    int					nRight;
    int					nBottom;				
} CFG_RECT;

// 区域顶点信息
typedef struct tagCFG_POLYGON
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYGON;

// 区域信息
typedef struct tagCFG_REGION
{
	int         nPointNum;
	CFG_POLYGON stuPolygon[MAX_POLYGON_NUM];
}CFG_REGION;

// 折线的端点信息
typedef struct tagCFG_POLYLINE
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYLINE;

// 车道信息
typedef struct tagCFG_LANE
{
	int                nLaneId;                           // 车道编号
	int                nDirection;                        // 车道方向(车开往的方向),0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	CFG_POLYLINE       stuLeftLine[MAX_POLYLINE_NUM];     // 左车道线，车道线的方向表示车道方向，沿车道方向左边的称为左车道线
	int                nLeftLineNum;                      // 左车道线顶点数
	CFG_POLYLINE       stuRightLine[MAX_POLYLINE_NUM];    // 右车道线，车道线的方向表示车道方向，沿车道方向右边的称为右车道线
	int                nRightLineNum;                     // 右车道线顶点数
	int                nLeftLineType;                     // 左车道线属性，1-表示白实线，2- 白虚线，3- 黄线
	int                nRightLineType;                    // 右车道线属性，1-表示白实线，2- 白虚线，3- 黄线
	BOOL               bDriveDirectionEnable;             // 车道行驶方向使能
	int                nDriveDirectionNum;                     // 车道行驶方向数 
	char               szDriveDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];  // 车道行驶方向，"Straight" 直行，"TurnLeft" 左转，"TurnRight" 右转,"U-Turn":掉头
	int                nStopLineNum;                      // 车道对应停止线顶点数
	CFG_POLYLINE       stuStopLine[MAX_POLYLINE_NUM];     // 车道对应停止线
	int                nTrafficLightNumber;               // 车道对应的红绿灯组编号

	bool               abDetectLine;                      // 对应能力集
	bool               abPreLine;
	bool               abPostLine;
	BYTE               byReserved[1];

	int                nDetectLine;
	CFG_POLYLINE       stuDetectLine[MAX_POLYLINE_NUM];   // 车道对应的检测线
	int                nPreLine;
	CFG_POLYLINE       stuPreLine[MAX_POLYLINE_NUM];      // 车道对应的前置线
	int                nPostLine;
	CFG_POLYLINE       stuPostLine[MAX_POLYLINE_NUM];     // 车道对应的后置线
}CFG_LANE;

// 交通灯属性
typedef struct tagCFG_LIGHTATTRIBUTE
{
	BOOL             bEnable;                           // 当前交通灯是否有效，与车辆通行无关的交通需要设置无效
	int              nTypeNum; 
	char		     szLightType[MAX_LIGHT_TYPE][MAX_NAME_LEN];      // 当前交通灯显现内容（包括:红-Red,黄-Yellow,绿-Green,倒计时-Countdown），如某交通灯可以显示红黄绿三种颜色，某交通灯只显示倒计时
	int              nDirectionNum;
	char             szDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];      // 交通灯指示的行车方向,"Straight": 直行，"TurnLeft":左转，"TurnRight":右转，"U-Turn": 掉头
	int              nYellowTime;                       // 黄灯亮时间
}CFG_LIGHTATTRIBUTE;

// 交通灯组配置信息 
typedef struct tagCFG_LIGHTGROUPS
{
	int                nLightGroupId;                     // 灯组编号
	CFG_RECT           stuLightLocation;                  // 灯组坐标
	int                nDirection;                        // 灯组的方向,1- 灯组水平向,2- 灯组垂直向
	BOOL               bExternalDetection;                // 是否为外接红绿灯信号,当外接红绿灯时，以外界信号为判断依据。外界信号每次跳变时通知
	BOOL               bSwingDetection;                   // 是否支持自适应灯组摇摆检测,在风吹或者容易震动的场景下，位置会进行一定的浮动偏差。如果由算法自行检测，会增加检测时间
	int                nLightNum;                         // 灯组中交通灯的数量
	CFG_LIGHTATTRIBUTE stuLightAtrributes[MAX_LIGHT_NUM]; // 灯组中各交通灯的属性

}CFG_LIGHTGROUPS;

enum EM_STAFF_TYPE
{
	EM_STAFF_TYPE_ERR,
		EM_STAFF_TYPE_HORIZONTAL,     // "Horizontal" 水平线段
		EM_STAFF_TYPE_VERTICAL,       // "Vertical" 垂直线段
		EM_STAFF_TYPE_ANY,            // "Any" 任意线段
		EM_STAFF_TYPE_CROSS,          // "Cross" 垂直面交线段
};

enum EM_CALIBRATEAREA_TYPE
{
	EM_CALIBRATEAREA_TYPE_ERR,
		EM_CALIBRATEAREA_TYPE_GROUD,                         // "Groud" : 地面，需要N条竖直线段+M条水平线段（（N=3，M=1）；（N=2，M=2）；今后扩展）。
		EM_CALIBRATEAREA_TYPE_HORIZONTAL,                    // "Horizontal"  : 水平面，需要水平面上一点到地面点的投影垂直线段。		
		EM_CALIBRATEAREA_TYPE_VERTICAL,                      // "Vertical" : 垂直面，需要垂直面与地面的交线。
		EM_CALIBRATEAREA_TYPE_ANY,                           // "Any" 任意平面，N条竖直线段，及每条长度（N=3，及今后扩展）。
};

// 特殊区域的属性类型
enum EM_SEPCIALREGION_PROPERTY_TYPE
{
	EM_SEPCIALREGION_PROPERTY_TYPE_HIGHLIGHT = 1,            // 高亮，屏幕检测区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_REGULARBLINK,             // 规律的闪烁，插卡区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_IREGULARBLINK,            // 不规律的闪烁，键盘区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_NUM,
};


// 人脸检测类型
enum EM_FACEDETECTION_TYPE
{
	EM_FACEDETECTION_TYPE_ERR,
	EM_FACEDETECTION_TYPE_SMALLFACE,						//小脸类型，人脸在视频中的比重大概17%
	EM_FACEDETECTION_TYPE_LARGEFACE,						//大脸类型，人脸在视频中的比重大概33%
	EM_FACEDETECTION_TYPE_BOTH,								//检测类型
};



typedef struct tagCFG_STAFF
{
	CFG_POLYLINE       stuStartLocation;      // 起始坐标点
	CFG_POLYLINE       stuEndLocation;        // 终止坐标点
	float                nLenth;              // 实际长度,单位米
	EM_STAFF_TYPE	   emType;                // 标尺类型
}CFG_STAFF;

// Size
typedef struct tagCFG_SIZE
{
	union
	{
		float				nWidth;			// 宽
		float				nArea;			// 面积
	};
	float					nHeight;		// 高
	
} CFG_SIZE;

// 遮挡信息
typedef struct tagCFG_COVER_INFO
{
	// 能力
	bool				abBlockType;
	bool				abEncodeBlend;
	bool				abPreviewBlend;

	// 信息
	CFG_RECT			stuRect;					// 覆盖的区域坐标
	CFG_RGBA			stuColor;					// 覆盖的颜色
	int					nBlockType;					// 覆盖方式；0－黑块，1－马赛克
	int					nEncodeBlend;				// 编码级遮挡；1－生效，0－不生效
	int					nPreviewBlend;				// 预览遮挡；1－生效，0－不生效
} CFG_COVER_INFO;

// 多区域遮挡配置
typedef struct tagCFG_VIDEO_COVER
{
	int                 nTotalBlocks;						// 支持的遮挡块数
	int					nCurBlocks;							// 已设置的块数
	CFG_COVER_INFO		stuCoverBlock[MAX_VIDEO_COVER_NUM];	// 覆盖的区域	
} CFG_VIDEO_COVER;

// OSD信息
typedef struct tagCFG_OSD_INFO
{
	// 能力
	bool				abShowEnable;

	// 信息
	CFG_RGBA			stuFrontColor;				// 前景颜色
	CFG_RGBA			stuBackColor;				// 背景颜色
	CFG_RECT			stuRect;					// 矩形区域
	BOOL				bShowEnable;				// 显示使能
} CFG_OSD_INFO;

// 画面颜色属性
typedef struct tagCFG_COLOR_INFO
{
	int					nBrightness;				// 亮度(0-100)
	int					nContrast;					// 对比度(0-100)
	int					nSaturation;				// 饱和度(0-100)
	int					nHue;						// 色度(0-100)
	int					nGain;						// 增益(0-100)
	BOOL				bGainEn;					// 增益使能
} CFG_COLOR_INFO;

// 图像通道属性信息
typedef struct tagCFG_ENCODE_INFO
{
	int                 nChannelID;							// 通道号(0开始)
	char				szChnName[MAX_CHANNELNAME_LEN];		// 通道名称
	CFG_VIDEOENC_OPT	stuMainStream[MAX_VIDEOSTREAM_NUM];	// 主码流，0－普通录像，1-动检录像，2－报警录像
	CFG_VIDEOENC_OPT	stuExtraStream[MAX_VIDEOSTREAM_NUM];// 辅码流，0－辅码流1，1－辅码流2，2－辅码流3
	CFG_VIDEOENC_OPT	stuSnapFormat[MAX_VIDEOSTREAM_NUM];	// 抓图，0－普通抓图，1－动检抓图，2－报警抓图
	DWORD				dwCoverAbilityMask;					// 区域遮盖能力掩码，按位分别是本地预览、录像及网络监视
	DWORD				dwCoverEnableMask;					// 区域遮盖使能掩码，按位分别是本地预览、录像及网络监视
	CFG_VIDEO_COVER		stuVideoCover;						// 区域覆盖
	CFG_OSD_INFO		stuChnTitle;						// 通道标题
	CFG_OSD_INFO		stuTimeTitle;						// 时间标题
	CFG_COLOR_INFO		stuVideoColor;						// 画面颜色
	CFG_AUDIO_FORMAT    emAudioFormat;                      // 音频格式: 0:G711A,1:PCM,2:G711U,3:AMR,4:AAC
	int					nProtocolVer;						// 协议版本号, 只读
} CFG_ENCODE_INFO;

// 水印配置
typedef struct tagCFG_WATERMARK_INFO 
{
	int                 nChannelID;					// 通道号(0开始)
	BOOL				bEnable;					// 使能开关
	int					nStreamType;				// 码流类型(1～n)，0－所有码流
	int					nDataType;					// 数据类型，1－文字，2－图片
	char				pData[MAX_WATERMARK_LEN];	// 字符串水印数据
} CFG_WATERMARK_INFO;

// dsp配置
typedef struct tagCFG_DSPENCODECAP_INFO{
	DWORD				dwVideoStandardMask;	// 视频制式掩码，按位表示设备能够支持的视频制式
	DWORD				dwImageSizeMask;		// 分辨率掩码，按位表示设备能够支持的分辨率
	DWORD				dwEncodeModeMask;		// 编码模式掩码，按位表示设备能够支持的编码模式
	DWORD				dwStreamCap;			// 按位表示设备支持的多媒体功能，
                                             	// 第一位表示支持主码流
	                                         	// 第二位表示支持辅码流1
	                                         	// 第三位表示支持辅码流2
	                                         	// 第五位表示支持jpg抓图
	DWORD				dwImageSizeMask_Assi[32];// 表示主码流为各分辨率时，支持的辅码流分辨率掩码。
	DWORD				dwMaxEncodePower;		// DSP支持的最高编码能力 
	WORD				wMaxSupportChannel;		// 每块DSP支持最多输入视频通道数 
	WORD				wChannelMaxSetSync;		// DSP每通道的最大编码设置是否同步；0：不同步，1：同步
	BYTE				bMaxFrameOfImageSize[256];// 不同分辨率下的最大采集帧率，与dwVideoStandardMask按位对应
	BYTE				bEncodeCap;				// 标志，配置时要求符合下面条件，否则配置不能生效；
	                                         	// 0：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
	                                         	// 1：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
	                                         	// 辅码流的编码能力 <= 主码流的编码能力，
	                                         	// 辅码流的分辨率 <= 主码流的分辨率，
	                                         	// 主码流和辅码流的帧率 <= 前端视频采集帧率
	                                         	// 2：N5的计算方法
	                                         	// 辅码流的分辨率 <= 主码流的分辨率
												// 查询支持的分辨率和相应最大帧率
	BYTE				byResolutionNum;			// bResolution的长度
	BYTE				byResolutionNum_1;		// bResolution_1的长度
	BYTE				byReserved;
	BYTE				byResolution[256];		//主码流,按照分辨率进行索引，如果支持该分辨率，则bResolution[n]等于支持的最大帧率.否则为0.							
	BYTE				byResolution_1[256];		//辅助码流1,同主码流说明.
	char				reserved[28];
	BYTE				byImageSize[256];		// 支持的分辨率数组,参见enum CAPTURE_SIZE
	BYTE				byImageSize_Assi[256][256]; //表示主码流为各分辨率时，支持的辅码流分辨率，数组下标表示主码流所支持的分辨率值。
}CFG_DSPENCODECAP_INFO;

//-------------------------------录象配置---------------------------------

// 时间段信息
typedef struct tagCFG_TIME_SECTION 
{
	DWORD				dwRecordMask;						// 录像掩码，按位分别为动态检测录像、报警录像、定时录像、Bit3~Bit15保留、Bit16动态检测抓图、Bit17报警抓图、Bit18定时抓图
	int					nBeginHour;
	int					nBeginMin;
	int					nBeginSec;
	int					nEndHour;
	int					nEndMin;
	int					nEndSec;
} CFG_TIME_SECTION;

// 定时录像配置信息
typedef struct tagCFG_RECORD_INFO
{
	int                 nChannelID;					// 通道号(0开始)
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT]; // 时间表
	int					nPreRecTime;				// 预录时间，为零时表示关闭(0~300)
	BOOL				bRedundancyEn;				// 录像冗余开关
	int					nStreamType;				// 0－主码流，1－辅码流1，2－辅码流2，3－辅码流3
	int					nProtocolVer;				// 协议版本号, 只读
} CFG_RECORD_INFO;

//-------------------------------报警配置---------------------------------

// 云台联动类型
typedef enum tagCFG_LINK_TYPE
{
	LINK_TYPE_NONE,						    		// 无联动
	LINK_TYPE_PRESET,								// 联动预置点
	LINK_TYPE_TOUR,									// 联动巡航
	LINK_TYPE_PATTERN,								// 联动轨迹
} CFG_LINK_TYPE;

// 联动云台信息
typedef struct tagCFG_PTZ_LINK
{
	CFG_LINK_TYPE		emType;						// 联动类型
	int					nValue;						// 联动取值分别对应预置点号，巡航号等等
} CFG_PTZ_LINK;

// 联动云台信息扩展
typedef struct tagCFG_PTZ_LINK_EX
{
	CFG_LINK_TYPE	emType;				// 联动类型 
	int			    nParam1;			// 联动参数1
	int			    nParam2;            // 联动参数2
	int			    nParam3;            // 联动参数3
	int			    nChannelID;         // 所联动云台通道
} CFG_PTZ_LINK_EX;

// 事件标题内容结构体
typedef struct tagCFG_EVENT_TITLE
{
	char				szText[MAX_CHANNELNAME_LEN];
	CFG_POLYGON			stuPoint;			// 标题左上角坐标, 采用0-8191相对坐标系
	CFG_SIZE     		stuSize;			// 标题的宽度和高度,采用0-8191相对坐标系，某项或者两项为0表示按照字体自适应宽高
    CFG_RGBA			stuFrontColor;		// 前景颜色
    CFG_RGBA			stuBackColor;		// 背景颜色
} CFG_EVENT_TITLE;

// 邮件附件类型
typedef enum tagCFG_ATTACHMENT_TYPE
{
		ATTACHMENT_TYPE_PIC,							// 图片附件
		ATTACHMENT_TYPE_VIDEO,							// 视频附件
		ATTACHMENT_TYPE_NUM,							// 附件类型总数
} CFG_ATTACHMENT_TYPE;
// 邮件详细内容
typedef struct tagCFG_MAIL_DETAIL
{
	   CFG_ATTACHMENT_TYPE emAttachType;                 // 附件类型
       int                 nMaxSize;                     // 文件大小上限，单位kB
       int                 nMaxTimeLength;               // 最大录像时间长度，单位秒，对video有效
}CFG_MAIL_DETAIL;

// 分割模式
typedef enum tagCFG_SPLITMODE
{
	    SPLITMODE_1 = 1,						// 1画面
	    SPLITMODE_2 = 2,						// 2画面
	    SPLITMODE_4 = 4,						// 4画面
		SPLITMODE_6 = 6,						// 6画面
		SPLITMODE_8 = 8,						// 8画面
		SPLITMODE_9 = 9,						// 9画面
		SPLITMODE_12 = 12,				    	// 12画面
		SPLITMODE_16 = 16,				    	// 16画面
		SPLITMODE_20 = 20,				    	// 20画面
		SPLITMODE_25 = 25,					    // 25画面
		SPLITMODE_36 = 36,					    // 36画面
		SPLITMODE_64 = 64,					    // 64画面
		SPLITMODE_144 = 144,					// 144画面
		SPLITMODE_PIP = 1000,                   // 画中画分割模式基础值
		SPLITMODE_PIP1 = SPLITMODE_PIP + 1,		// 画中画模式, 1个全屏大画面+1个小画面窗口
		SPLITMODE_PIP3 = SPLITMODE_PIP + 3,		// 画中画模式, 1个全屏大画面+3个小画面窗口
		SPLITMODE_FREE = SPLITMODE_PIP * 2,	// 自由开窗模式，可以自由创建、关闭窗口，自由设置窗口位置和Z轴次序
		SPLITMODE_COMPOSITE_1 = SPLITMODE_PIP * 3 + 1,	// 融合屏成员1分割
		SPLITMODE_COMPOSITE_4 = SPLITMODE_PIP * 3 + 4,	// 融合屏成员4分割
		SPLITMODE_EOF,                          // 结束标识
} CFG_SPLITMODE;

// 轮巡联动配置
typedef struct tagCFG_TOURLINK
{
	BOOL				bEnable;			             // 轮巡使能
	CFG_SPLITMODE	    emSplitMode;		             // 轮巡时的分割模式
	int			        nChannels[MAX_VIDEO_CHANNEL_NUM];  // 轮巡通道号列表
	int			        nChannelCount;		             // 轮巡通道数量
} CFG_TOURLINK;
// 报警联动信息
typedef struct tagCFG_ALARM_MSG_HANDLE
{
	//能力
	bool				abRecordMask;
	bool				abRecordEnable;
	bool				abRecordLatch;
	bool				abAlarmOutMask;
	bool				abAlarmOutEn;
	bool				abAlarmOutLatch;	
	bool				abExAlarmOutMask;
	bool				abExAlarmOutEn;
	bool				abPtzLinkEn;
	bool				abTourMask;
	bool				abTourEnable;
	bool				abSnapshot;
	bool				abSnapshotEn;
	bool				abSnapshotPeriod;
	bool				abSnapshotTimes;
	bool				abTipEnable;
	bool				abMailEnable;
	bool				abMessageEnable;
	bool				abBeepEnable;
	bool				abVoiceEnable;
	bool				abMatrixMask;
	bool				abMatrixEnable;
	bool				abEventLatch;
	bool				abLogEnable;
	bool				abDelay;
	bool				abVideoMessageEn;
	bool				abMMSEnable;
	bool				abMessageToNetEn;
	bool				abTourSplit;
	bool				abSnapshotTitleEn;

    bool                abChannelCount;
	bool                abAlarmOutCount;
	bool                abPtzLinkEx;
	bool                abSnapshotTitle;
	bool                abMailDetail;
	bool                abVideoTitleEn;
	bool                abVideoTitle;
	bool                abTour;
	bool                abDBKeys;
	bool                abJpegSummary;
	bool                abFlashEn;
	bool                abFlashLatch;
	


	//信息
	int					nChannelCount;								 // 设备的视频通道数
	int					nAlarmOutCount;								 // 设备的报警输出个数
	DWORD				dwRecordMask[MAX_CHANNEL_COUNT];			 // 录像通道掩码(按位)
	BOOL				bRecordEnable;								 // 录像使能
	int					nRecordLatch;								 // 录像延时时间(秒)
	DWORD				dwAlarmOutMask[MAX_CHANNEL_COUNT];			 // 报警输出通道掩码
	BOOL				bAlarmOutEn;								 // 报警输出使能
	int					nAlarmOutLatch;								 // 报警输出延时时间(秒)
	DWORD				dwExAlarmOutMask[MAX_CHANNEL_COUNT];		 // 扩展报警输出通道掩码
	BOOL				bExAlarmOutEn;								 // 扩展报警输出使能
	CFG_PTZ_LINK		stuPtzLink[MAX_VIDEO_CHANNEL_NUM];			 // 云台联动项
	BOOL				bPtzLinkEn;									 // 云台联动使能
	DWORD				dwTourMask[MAX_CHANNEL_COUNT];				 // 轮询通道掩码
	BOOL				bTourEnable;								 // 轮询使能
	DWORD				dwSnapshot[MAX_CHANNEL_COUNT];				 // 快照通道号掩码
	BOOL				bSnapshotEn;								 // 快照使能
	int					nSnapshotPeriod;							 // 连拍周期(秒)
	int					nSnapshotTimes;								 // 连拍次数
	BOOL				bTipEnable;									 // 本地消息框提示
	BOOL				bMailEnable;								 // 发送邮件，如果有图片，作为附件
	BOOL				bMessageEnable;								  // 上传到报警服务器
	BOOL				bBeepEnable;							 	  // 蜂鸣
	BOOL				bVoiceEnable;								  // 语音提示
	DWORD				dwMatrixMask[MAX_CHANNEL_COUNT];			  // 联动视频矩阵通道掩码
	BOOL				bMatrixEnable;								  // 联动视频矩阵
	int					nEventLatch;								  // 联动开始延时时间(秒)，0－15
	BOOL				bLogEnable;									  // 是否记录日志
	int					nDelay;										  // 设置时先延时再生效，单位为秒
	BOOL				bVideoMessageEn;							  // 叠加提示字幕到视频。叠加的字幕包括事件类型，通道号，秒计时。
	BOOL				bMMSEnable;									  // 发送彩信使能
	BOOL				bMessageToNetEn;							  // 消息上传给网络使能
	int					nTourSplit;									  // 轮巡时的分割模式 0: 1画面; 1: 8画面
	BOOL				bSnapshotTitleEn;							  // 是否叠加图片标题
	int                 nPtzLinkExNum;                                // 云台配置数
	CFG_PTZ_LINK_EX     stuPtzLinkEx[MAX_VIDEO_CHANNEL_NUM];          // 扩展云台信息
	int                 nSnapTitleNum;                                // 图片标题内容数
	CFG_EVENT_TITLE     stuSnapshotTitle[MAX_VIDEO_CHANNEL_NUM];      // 图片标题内容
	CFG_MAIL_DETAIL     stuMailDetail;                                // 邮件详细内容
	BOOL                bVideoTitleEn;                                // 是否叠加视频标题，主要指主码流
    int                 nVideoTitleNum;                               // 视频标题内容数目
	CFG_EVENT_TITLE     stuVideoTitle[MAX_VIDEO_CHANNEL_NUM];         // 视频标题内容
	int                 nTourNum;                                     // 轮询联动数目
	CFG_TOURLINK        stuTour[MAX_VIDEO_CHANNEL_NUM];               // 轮询联动配置
	int                 nDBKeysNum;			                          // 指定数据库关键字的有效数
	char                szDBKeys[MAX_DBKEY_NUM][MAX_CHANNELNAME_LEN]; // 指定事件详细信息里需要写到数据库的关键字
	BYTE                byJpegSummary[MAX_SUMMARY_LEN];               // 叠加到JPEG图片的摘要信息
	BOOL                bFlashEnable;                                 // 是否使能补光灯
	int                 nFlashLatch;                                  // 补光灯延时时间(秒),延时时间范围：[10,300]
} CFG_ALARM_MSG_HANDLE;

// 传感器感应方式枚举类型
typedef enum
{
	EM_SENSE_DOOR=0,         //门磁
	EM_SENSE_PASSIVEINFRA,   //被动红外
	EM_SENSE_GAS,            //气感
	EM_SENSE_SMOKING,        //烟感
	EM_SENSE_WATER,          //水感
	EM_SENSE_ACTIVEFRA,      //主动红外
	EM_SENSE_NUM             //枚举类型总数
}EM_SENSE_METHOD;

// 报警使能控制方式枚举类型
typedef enum
{
	EM_CTRL_NORMAL=0,   //不控制使能
	EM_CTRL_ALWAYS_EN,  //总是使能
	EM_CTRL_ONCE_DIS,   //旁路
	EM_CTRL_ALWAYS_DIS, //移除
	EM_CTRL_NUM         //枚举类型总数
}EM_CTRL_ENABLE;

// 外部报警配置
typedef struct tagCFG_ALARMIN_INFO
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
	BOOL				abDevID;									// 
	char				szDevID[MAX_NAME_LEN];						// 设备ID
	int                 nPole;                                      //传感器触发模式, 0:高有效，1低有效；
	                                                                //具体表现为传感器接地or电源，与nAlarmType组合使用
	EM_SENSE_METHOD     emSense;                                    //传感器感应方式
	EM_CTRL_ENABLE      emCtrl;                                     //报警使能控制方式
	int                 nDisDelay;                                  //延时撤防时间,单位为秒,0~300，
	                                                                //emCtrl值为EM_CTRL_NORMAL或EM_CTRL_ALWAYS_EN 时有效。
} CFG_ALARMIN_INFO;

// 网络输入报警配置
typedef struct tagCFG_NETALARMIN_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_NETALARMIN_INFO;


// 动检支持的视频窗口配置
typedef struct tagCFG_MOTION_WINDOW
{
	int                  nThreshold;           // 面积阀值，取值[0, 100]
	int                  nSensitive;           // 灵敏度，取值[0, 100]
	CFG_RECT             stuWindow;            // 动检窗口区域, 坐标位置取值[0, 8192)
}CFG_MOTION_WINDOW;

// 动态检测报警配置
typedef struct tagCFG_MOTION_INFO 
{
	int					 nChannelID;									// 报警通道号(0开始), nVersion=1时，此字段无效
	BOOL				 bEnable;									    // 使能开关
	int					 nSenseLevel;								    // 灵敏度1～6
	int					 nMotionRow;									// 动态检测区域的行数
	int					 nMotionCol;									// 动态检测区域的列数
	BYTE				 byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	    // 检测区域，最多32*32块区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;							    // 报警联动
	CFG_TIME_SECTION	 stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];   // 事件响应时间段
	int			         nVersion;                                      // 0, 1, 由能力集确定, 只读, 等于1时以下字段有效
	BOOL                 bSenseLevelEn;                                 // 只读，决定nSenseLevel是否有效
	BOOL                 bVRatioEn;                                     // 只读，面积占用比使能， 决定nVolumeRatio是否有效
	int                  nVolumeRatio;                                  // 面积占用比,1-100
	BOOL                 bSRatioEn;                                     // 只读，灵敏度使能，决定nSubRatio值是否有效
	int                  nSubRatio;                                     // 动检的残差阈值, 1-100
	BOOL                 abWindow;                                      // 只读，0: nMotionRow, nMotionCol和byRegion字段有效, 1: 下面视频窗口字段 
	int                  nWindowCount;                                  // 视频窗口个数
	CFG_MOTION_WINDOW    stuWindows[MAX_MOTION_WINDOW];                 // 视频窗口数组
} CFG_MOTION_INFO;

// 视频丢失报警配置
typedef struct tagCFG_VIDEOLOST_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_VIDEOLOST_INFO;

// 视频遮挡报警配置
typedef struct tagCFG_SHELTER_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	int					nSenseLevel;								// 灵敏度
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_SHELTER_INFO;

// 无存储设备报警配置
typedef struct tagCFG_STORAGENOEXIST_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGENOEXIST_INFO;

// 存储设备访问出错报警配置
typedef struct tagCFG_STORAGEFAILURE_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGEFAILURE_INFO;

// 存储设备空间不足报警配置
typedef struct tagCFG_STORAGELOWSAPCE_INFO 
{
	BOOL				bEnable;						// 使能开关
	int					nLowerLimit;					// 硬盘剩余容量下限，百分数(0~99)
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGELOWSAPCE_INFO;

// 网络断开报警配置
typedef struct tagCFG_NETABORT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_NETABORT_INFO;

// IP冲突报警配置
typedef struct tagCFG_IPCONFLICT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_IPCONFLICT_INFO;

// CLIENT_QueryNewSystemInfo 接口的命令 CFG_CAP_ALARM (获取报警能力集)对应结构体
typedef struct tagCFG_CAP_ALARM_INFO
{
	BOOL                bAlarmPir;                      // 设备是否支持PIR(人体热式感应器)报警,外部报警的一种
	BOOL                bFlashLight;                    // 设备是否支持补光灯
}CFG_CAP_ALARM_INFO;

// 补光灯配置
typedef struct tagCFG_FLASH_LIGHT
{
	BOOL                bEnable;                        // 使能开关
	int                 nBrightness;                    // 亮度 0~100
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 补光灯工作时间段
}CFG_FLASH_LIGHT;

typedef struct tagCFG_CUSTOMCASE
{
	char                szCaseTitle[MAX_OSD_TITLE_LEN];    // 案件名称
	char                szCaseContent[MAX_OSD_SUMMARY_LEN];  // 案件名称
	BOOL                bCaseNoOsdEn;                        // 案件编号叠加使能
}CFG_CUSTOMCASE;

// 司法刻录配置
typedef struct tagCFG_JUDICATURE_INFO
{
	char                szDiskPassword[MAX_PASSWORD_LEN];// 光盘密码，播发时需输入正确密码才能播放

	char                szCaseNo[MAX_OSD_SUMMARY_LEN];     // 案件编号
	BOOL                bCaseNoOsdEn;                      // 案件编号叠加使能
	char                szCaseTitle[MAX_OSD_SUMMARY_LEN];  // 案件名称
	BOOL                bCaseTitleOsdEn;                   // 案件名称叠加使能
	char                szOfficer[MAX_OSD_SUMMARY_LEN];    // 办案人员
	BOOL                bOfficerOsdEn;                     // 办案人员叠加使能
	char                szLocation[MAX_OSD_SUMMARY_LEN];   // 办案地点
	BOOL                bLocationOsdEn;                    // 办案地点叠加使能
	char                szRelatedMan[MAX_OSD_SUMMARY_LEN]; // 涉案人员
	BOOL                bRelatedManOsdEn;                  // 涉案人员叠加使能
	char                szDiskNo[MAX_OSD_SUMMARY_LEN];     // 光盘编号
	BOOL                bDiskNoOsdEn;                      // 光盘编号叠加使能

	BOOL                bCustomCase;                       // TRUE:自定义司法案件信息,FALSE: 上边szCaseNo等字段有效
	int                 nCustomCase;                       // 实际CFG_CUSTOMCASE个数
	CFG_CUSTOMCASE      stuCustomCases[MAX_CUSTOMCASE_NUM];// 自定义司法案件信息

	BOOL                bDataCheckOsdEn;                   // 光盘刻录数据校验配置 叠加使能
	BOOL                bAttachFileEn;                     // 附件上传使能
}CFG_JUDICATURE_INFO;

// 刻录满事件配置
typedef struct tagCFG_BURNFULL_ONE
{
	char                szBurnDisk[MAX_NAME_LEN];          // 刻录设备
	BOOL                bEnable;                           // 使能开关
	unsigned int        nLowerLimit;                       // 光盘剩余容量下限	单位：M
	BOOL                bBurnStop;                         // 刻录停止使能
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
}CFG_BURNFULL_ONE;

typedef struct tagCFG_BURNFULL_INFO
{
	unsigned int        nBurnDev;                          // 实际刻录设备个数
	CFG_BURNFULL_ONE    stuBurns[MAX_BURNING_DEV_NUM];     // 每个元素对应一个刻录设备
}CFG_BURNFULL_INFO;

//-------------------------------抓图配置能力---------------------------------
// 抓图配置能力
typedef struct tagCFG_SNAPCAPINFO_INFO  
{
	int					nChannelID;						// 抓图通道号(0开始)
	DWORD				dwIMageSizeNum;					// 支持的分别率信息
	CFG_CAPTURE_SIZE	emIMageSizeList[MAX_IMAGESIZE_NUM];
	DWORD				dwFramesPerSecNum;				// 支持的帧率信息
	int					nFramesPerSecList[MAX_FPS_NUM];
	DWORD				dwQualityMun;					// 支持的画质信息
	CFG_IMAGE_QUALITY	emQualityList[MAX_QUALITY_NUM];

	DWORD               dwMode;							// 模式,按位：第一位：定时；第二位：手动。
	DWORD               dwFormat;						// 图片格式模式,按位：第一位：bmp；第二位：jpg。
} CFG_SNAPCAPINFO_INFO;


//-------------------------------网络存储服务器配置---------------------------------
// 网络存储服务器配置
typedef struct tagCFG_CHANNEL_TIME_SECTION 
{
	CFG_TIME_SECTION stuTimeSection[WEEK_DAY_NUM][MAX_NAS_TIME_SECTION];//存储时间段
} CFG_CHANNEL_TIME_SECTION;

typedef struct tagCFG_NAS_INFO
{
	BOOL						bEnable;									// 使能开关
	int							nVersion;									// 网络存储服务器版本0=老的FTP，1=NAS存储
	int							nProtocol;									// 协议类型0=FTP 1=SMB
	char						szAddress[MAX_ADDRESS_LEN];					// IP地址或网络名
	int							nPort;										// 端口号
	char						szUserName[MAX_USERNAME_LEN];				// 帐户名
	char						szPassword[MAX_PASSWORD_LEN];				// 密码
	char						szDirectory[MAX_DIRECTORY_LEN];				// 共享的目录名
	int							nFileLen;									// 文件长度
	int							nInterval;									// 相邻文件时间间隔
	CFG_CHANNEL_TIME_SECTION	stuChnTime[MAX_VIDEO_CHANNEL_NUM];			// 存储时间段
	int                         nChnTimeCount;                              // 有效的存储时间段数
} CFG_NAS_INFO;

//------------------------------云台配置--------------------------------------------
// 协议名
typedef struct tagCFG_PRONAME
{
	char				name[MAX_NAME_LEN];			// 协议名
} CFG_PRONAME;

// 串口基本属性
typedef struct tagCFG_COMM_PROP
{
	BYTE				byDataBit;					// 数据位；0：5，1：6，2：7，3：8
	BYTE				byStopBit;					// 停止位；0：1位，1：1.5位，2：2位
	BYTE				byParity;					// 校验位；0：无校验，1：奇校验；2：偶校验
	BYTE				byBaudRate;					// 波特率；0：300，1：600，2：1200，3：2400，4：4800，													
	                                                // 5：9600，6：19200，7：38400，8：57600，9：115200
} CFG_COMM_PROP;
// 归位预置点配置
typedef struct tagCFG_PRESET_HOMING
{
	int          nPtzPresetId;   //云台预置点编号	0~65535, -1表示无效
	int          nFreeSec;       //空闲的时间，单位为秒
}CFG_PRESET_HOMING;
// 云台配置
typedef struct tagCFG_PTZ_INFO
{
	// 能力
	bool				abMartixID;
	bool				abCamID;
	bool				abPTZType;

	// 信息
	int					nChannelID;								// 通道号(0开始)
	BOOL                bEnable;                                // 使能开关
	char                szProName[MAX_NAME_LEN];                // 协议名称
	int					nDecoderAddress;						// 解码器地址；0 - 255
	CFG_COMM_PROP		struComm;
	int					nMartixID;								// 矩阵号
	int					nPTZType;								// 云台类型0-兼容，本地云台 1-远程网络云台
	int					nCamID;									// 摄像头ID
	int                 nPort;                                  // 使用的串口端口号
	CFG_PRESET_HOMING   stuPresetHoming;                        // 一段时间不操作云台，自动归位到某个预置点
} CFG_PTZ_INFO;  

//----------------------------------视频分析设备配置------------------------------------------
// 场景支持的规则
typedef struct
{
	DWORD             dwSupportedRule;                                         // 规则类型
	int               nSupportedObjectTypeNum;                                 // 支持的检测物体类型个数
	char              szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	   // 支持的检测物体类型列表
	int               nSupportedActionsNum;                                    // 支持的检测物体动作个数
	char              szSupportedActions[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];  // 支持的检测物体动作列表
	int               nSupportedDetectTypeNum;                                 // 支持的检测类型个数
	char              szSupportedDetectTypes[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];// 支持的检测类型列表
	int               nSupportFaceTypeNum;                                       // 支持的人脸检测类型个数
	char              szSupportFaceTypes[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // 支持的人脸检测类型列表
	BOOL              bTriggerPosition;                                        // 是否支持触发报警位置
}SCENE_SUPPORT_RULE;

// 标定区域能力信息
typedef struct tagCFG_CAP_CELIBRATE_AREA
{
	EM_CALIBRATEAREA_TYPE  emType;												 // 标定区域类型
	BYTE                   byMaxHorizontalStaffNum;                              // 支持的水平标尺最大个数
	BYTE                   byMinHorizontalStaffNum;                              // 支持的水平标尺最小个数
	BYTE                   byMaxVerticalStaffNum;                                // 支持的垂直标尺最大个数
	BYTE                   byMinVerticalStaffNum;                                // 支持的垂直标尺最小个数
}CFG_CAP_CELIBRATE_AREA;

// 场景能力
typedef struct tagCFG_CAP_SCENE
{
	char               szSceneName[MAX_PATH];                                   // 场景名称
	int                nSupportedObjectTypeNum;                                 // 当前规则类型支持的检测物体类型个数
	char               szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 当前规则类型支持的检测物体类型列表
	int                nSupportRules;                                           // 支持的规则个数
	SCENE_SUPPORT_RULE stSpportRules[MAX_RULE_LIST_SIZE];                       // 支持的规则列表

	//支持的模块参数
	bool               bDisturbance;                                            // 是否支持扰动强度设置
	bool               bAntiDisturbance;                                        // 是否支持去扰动处理
	bool               bBacklight;                                              // 是否支持逆光处理
	bool               bShadow;                                                 // 是否支持阴影处理
	bool               bAccuracy;                                               // 是否支持检测精度
	bool               bMovingStep;												// 是否支持检测步长
	bool               bScalingFactor;                                          // 是否支持检测缩放
	bool               bThresholdY;                                             // 是否支持Y分量判定阈值
	bool               bThresholdUV;                                            // 是否支持UV分量判定阈值
	bool               bThresholdEdge;                                          // 是否支持边缘检测判定阈值
	bool               bDetectBalance;                                          // 是否支持检测平衡
	bool               bAlgorithmIndex;                                         // 是否支持算法序号
	bool               bHighlight;                                              // 是否支持高光处理，即Backgroud参数 
	bool               bSnapshot;                                               // 是否支持物体抓图
	bool               bDetectRegion;                                           // 是否支持检测区域配置
	bool               bExcludeRegion;                                          // 是否支持排除区域配置
	bool               bContourAssistantTrack;                                  // 是否支持轮廓辅助跟踪

	//支持的场景参数
	bool               bCameraAspect;                                            // 是否摄像头位置参数
	bool               bJitter;                                                  // 是否支持抖动参数
	bool               bDejitter;                                                // 是否支持去抖动处理参数

	// 支持的标定能力集
	int               nMaxCalibrateAreaNum;                                      // 最大标定区域个数
	int               nCalibrateAreaNum;                                         // 标定区域能力信息个数
	CFG_CAP_CELIBRATE_AREA stCalibrateAreaCap[MAX_CALIBRATEAREA_TYPE_NUM];       // 标定区域能力信息

	// 尺寸过滤器计量方式
	bool              bPixel;                                                    // 是否支持像素计量方式
	bool              bMetric;                                                   // 是否支持实际长度计量方式
	bool              bCalibratedPixel;                                          // 是否支持远端近端标定后的像素计量方式
}CFG_CAP_SCENE;

// 场景列表
typedef struct tagCFG_VACAP_SUPPORTEDSCENES
{
	int                nScenes;													   // 支持的场景个数
	CFG_CAP_SCENE      stScenes[MAX_SCENE_LIST_SIZE];                              // 支持的场景列表
}CFG_VACAP_SUPPORTEDSCENES;

#define CFG_DEVICE_ANALYSE_INFO CFG_CAP_DEVICE_ANALYSE_INFO
//视频分析设备能力信息
typedef struct tagCFG_CAP_DEVICE_ANALYSE_INFO
{
	int                nMaxChannels;											 // 支持智能分析的最大通道数
}CFG_CAP_DEVICE_ANALYSE_INFO;

// 某个规则支持的物体类型
typedef struct
{
	DWORD               dwRuleType;                                             // 当前规则类型
	int					nSupportedObjectTypeNum;								// 当前规则类型支持的检测物体类型个数
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 当前规则类型支持的检测物体类型列表
}RULE_SUPPORTED_OBJECT_TYPE;

// 视频分析能力集
typedef struct tagCFG_CAP_ANALYSE_INFO
{
	int					nSupportedSceneNum;										// 支持的场景个数
	char				szSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];			// 支持的场景列表
	int					nMaxMoudles;											// 每通道支持最大分析模块数
	int					nSupportedObjectTypeNum;								// 支持的检测物体类型个数
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 支持的检测物体类型列表
	int					nMaxRules;												// 每通道支持最大规则条数
	int					nSupportedRulesNum;										// 支持的事件类型规则个数
	DWORD				dwRulesType[MAX_RULE_LIST_SIZE];	             		// 支持的事件类型规则列表，事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int					nMaxStaffs;												// 支持的最大标尺个数
	int					nMaxPointOfLine;										// 折线最大顶点数
	int					nMaxPointOfRegion;										// 区域最大顶点数
	int                 nMaxInternalOptions;                                    // 最大内部选项个数
	bool                bComplexSizeFilter;                                     // 是否支持复杂尺寸过滤器	复杂尺寸过滤器使用独立的面积过滤和宽高比过滤参数。      
	bool                bSpecifiedObjectFilter;                                 // 是否支持特定的物体过滤器
	int                 nMaxExcludeRegionNum;                                   // 支持模块中的最大排除区域个数
	int                 nMaxCalibrateBoxNum;                                    // 支持的模块中的最大校准框个数
	int                 nMinCalibrateBoxNum;                                    // 模块中至少需要设置的校准框个数
	int                 nMaxSepcialDetectRegions;                               // 模块中支持的最大特殊区域检测个数
	int                 nSupportedTimeSectionNum;                               // 支持的每天的时间段个数 
	int                 nSpecialDetectPropertyNum;                              // 支持的特殊检测区属性个数
	int			        nSupportedSpecialDetectPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM]; // 支持的特殊检测区属性
	DWORD				nSupportedVideoChannelType;								// 支持的视频通道类型选择   第0位为1表示支持数字类型,第1位为1表示支持模拟类型,第2为1表示支持混合(数字和模拟)				
	CFG_VACAP_SUPPORTEDSCENES  stSupportScenes;                                 // 支持的场景能力集
} CFG_CAP_ANALYSE_INFO;

// 校准框信息
typedef struct tagCFG_CALIBRATEBOX_INFO
{
	CFG_POLYGON         stuCenterPoint;                       // 校准框中心点坐标(点的坐标归一化到[0,8191]区间)
	float               fRatio;                               // 相对基准校准框的比率(比如1表示基准框大小，0.5表示基准框大小的一半)
}CFG_CALIBRATEBOX_INFO;


// 标定区域,普通场景使用
typedef struct tagCFG_CALIBRATEAREA_INFO
{
	int               nLinePoint;                             // 水平方向标尺线顶点数
	CFG_POLYGON       stuLine[MAX_POLYLINE_NUM];              // 水平方向标尺线
	float             fLenth;                                 // 实际长度
	CFG_REGION        stuArea;                                // 区域
	int                 nStaffNum;                            // 垂直标尺数
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];             // 垂直标尺         
	EM_CALIBRATEAREA_TYPE emType;							  // 区域类型
}CFG_CALIBRATEAREA_INFO;

// 人脸识别场景
typedef struct tagCFG_FACERECOGNITION_SCENCE_INFO
{
	double				dbCameraHeight;							// 摄像头离地高度 单位：米
	double				dbCameraDistance;						// 摄像头离地面检测区域中心的水平距离 单位：米
	int                 nMainDirection;                         // 人流主要方向顶点数
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // 人流主要方向，第一个点是起始点，第二个点是终止点
	char                byFaceAngleDown;                        // 需要检测的人脸向下最大偏角, 单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleUp;                          // 需要检测的人脸向上最大偏角,单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
 	char                byFaceAngleLeft;                        // 需要检测的人脸向左最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	char                byFaceAngleRight;                       // 需要检测的人脸向右最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	EM_FACEDETECTION_TYPE	emDetectType;						// 人脸检测类型
}CFG_FACERECOGNITION_SCENCE_INFO;

// 人脸检测场景
typedef struct tagCFG_FACEDETECTION_SCENCE_INFO
{
	double				dbCameraHeight;							// 摄像头离地高度 单位：米
	double				dbCameraDistance;						// 摄像头离地面检测区域中心的水平距离 单位：米
	int                 nMainDirection;                         // 人流主要方向顶点数
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // 人流主要方向，第一个点是起始点，第二个点是终止点
	char                byFaceAngleDown;                        // 需要检测的人脸向下最大偏角, 单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleUp;                          // 需要检测的人脸向上最大偏角,单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleLeft;                        // 需要检测的人脸向左最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	char                byFaceAngleRight;                       // 需要检测的人脸向右最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	EM_FACEDETECTION_TYPE	emDetectType;						// 人脸检测类型
}CFG_FACEDETECTION_SCENCE_INFO;




// 视频分析全局配置
typedef struct tagCFG_ANALYSEGLOBAL_INFO
{
	// 信息
	char				szSceneType[MAX_NAME_LEN];				// 应用场景,详见"支持的场景列表"

	//交通场景信息
	double				CameraHeight;							// 摄像头离地高度	单位：米
	double				CameraDistance;							// 摄像头离地面检测区域中心的水平距离	单位：米
	CFG_POLYGON         stuNearDetectPoint;                     // 近景检测点
	CFG_POLYGON         stuFarDectectPoint;                     // 远景检测点
	int                 nNearDistance;                          // NearDetectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	int                 nFarDistance;                           // FarDectectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	char                szSubType[MAX_NAME_LEN];                // 交通场景的子类型,"Gate",卡口类型,"Junction" 路口类型                            
	int                 nLaneNum;                               // 车道数
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // 车道信息
	int                 nPlateHintNum;                          // 车牌字符暗示个数
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // 车牌字符暗示数组，在拍摄图片质量较差车牌识别不确定时，根据此数组中的字符进行匹配，数组下标越小，匹配优先级越高
	int                 nLightGroupNum;                         // 灯组数
	CFG_LIGHTGROUPS     stLightGroups[MAX_LIGHTGROUP_NUM];      // 灯组配置信息

	// 一般场景信息 
	int                 nStaffNum;                              // 标尺数
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];               // 标尺

	int                 nCalibrateAreaNum;                         // 标定区域数
	CFG_CALIBRATEAREA_INFO stuCalibrateArea[MAX_CALIBRATEBOX_NUM]; // 标定区域(若该字段不存在，则以整幅场景为标定区域)

	BOOL                bFaceRecognition;                          // 人脸识别场景是否有效
	CFG_FACERECOGNITION_SCENCE_INFO stuFaceRecognitionScene;       // 人脸识别场景
		
	bool                abJitter;
	bool                abDejitter;	
	BYTE                bReserved[2];                           // 保留字段

	int					nJitter;								// 摄像机抖动率 : 摄像机抖动率，取值0-100，反应静止摄像机抖动程度，抖动越厉害，值越大。
	BOOL                bDejitter;                              // 是否开启去抖动模块 目前不实现

	BOOL                abCompatibleMode;	
	int                 nCompatibleMode;                        // 0:"OldTrafficRule" : 交通老规则兼容模式;1:"NewTrafficRule" :  交通新规则兼容模式;-1:字符串错误

	int                 nCustomDataLen;                         // 实际数据长度，不能大于1024
	BYTE                byCustomData[1024];                     // 第三方自定义配置数据
	double				CameraAngle;							// 摄像头与垂方向的夹角
	CFG_POLYGON			stuLandLineStart;						// 地平线线段起始点(点的坐标坐标归一化到[0,8192)区间。)
	CFG_POLYGON			stuLandLineEnd;							// 地平线线段终止点(点的坐标坐标归一化到[0,8192)区间。)

	BOOL				bFaceDetection;							// 人脸检测场景是否有效
	CFG_FACEDETECTION_SCENCE_INFO	stuFaceDetectionScene;		// 人脸检测场景

	BYTE                bReserved2[2860];                       // 保留字段 用于扩展
} CFG_ANALYSEGLOBAL_INFO;

// 尺寸过滤器
typedef struct tagCFG_SIZEFILTER_INFO
{
	int                   nCalibrateBoxNum;                       // 校准框个数
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM]; // 校准框(远端近端标定模式下有效)
	bool                bMeasureModeEnable;                       // 计量方式参数是否有效
	BYTE                bMeasureMode;                             // 计量方式,0-像素，不需要远端、近端标定, 1-实际长度，单位：米, 2-远端近端标定后的像素
	bool                bFilterTypeEnable;                        // 过滤类型参数是否有效
	// ByArea,ByRatio仅作兼容，使用独立的ByArea和ByRatio选项代替 2012/03/06
	BYTE				bFilterType;			 				  // 过滤类型:0:"ByLength",1:"ByArea", 2"ByWidthHeight"
	BYTE                bReserved[2];                             // 保留字段
	bool                bFilterMinSizeEnable;                     // 物体最小尺寸参数是否有效
	bool                bFilterMaxSizeEnable;                     // 物体最大尺寸参数是否有效
	CFG_SIZE			stuFilterMinSize;						  // 物体最小尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效(远端近端标定模式下表示基准框的宽高尺寸)。
	CFG_SIZE			stuFilterMaxSize;				          // 物体最大尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效(远端近端标定模式下表示基准框的宽高尺寸)。
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByArea;                                  // 是否按面积过滤 通过能力ComplexSizeFilter判断是否可用
	bool                bReserved1[2];
	float               nMinArea;                                 // 最小面积
	float               nMaxArea;                                 // 最大面积
	CFG_SIZE            stuMinAreaSize;                           // 最小面积矩形框尺寸 "计量方式"为"像素"时，表示最小面积矩形框的宽高尺寸；"计量方式"为"远端近端标定模式"时，表示基准框的最小宽高尺寸；
	CFG_SIZE            stuMaxAreaSize;                           // 最大面积矩形框尺寸, 同上
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByRatio;                                 // 是否按宽高比过滤 通过能力ComplexSizeFilter判断是否可用
	bool                bReserved2[2];
	double              dMinRatio;                                // 最小宽高比
	double              dMaxRatio;                                // 最大宽高比
	CFG_SIZE            stuMinRatioSize;                          // 最小宽高比矩形框尺寸，最小宽高比对应矩形框的宽高尺寸。
	CFG_SIZE            stuMaxRatioSize;                          // 最大宽高比矩形框尺寸，同上
	
	int                 nAreaCalibrateBoxNum;                     // 面积校准框个数
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 面积校准框
	int                 nRatioCalibrateBoxs;                      // 宽高校准框个数
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 宽高校准框
	
	bool                abBySize;                                 // 长宽过滤使能参数是否有效
	bool                bBySize;                                  // 长宽过滤使能
}CFG_SIZEFILTER_INFO;

// 各种物体特定的过滤器
typedef struct tagCFG_OBJECT_SIZEFILTER_INFO
{
	char				szObjectType[MAX_NAME_LEN];              // 物体类型
	CFG_SIZEFILTER_INFO stSizeFilter;                            // 对应的尺寸过滤器
}CFG_OBJECT_SIZEFILTER_INFO;

// 特殊检测区，是指从检测区中区分出来，有特殊检测属性的区域
typedef struct tagCFG_SPECIALDETECTREGION_INFO
{
	int                nDetectNum;                              // 检测区域顶点数
	CFG_POLYGON        stDetectRegion[MAX_POLYGON_NUM];         // 检测区域
	int                nPropertyNum;                            // 特殊检测区属性个数
	int                nPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM];      // 特殊检测区属性
}CFG_SPECIALDETECT_INFO;

// 不同区域各种类型物体的检测模块配置
typedef struct tagCFG_MODULE_INFO
{
	// 信息
	char				szObjectType[MAX_NAME_LEN];				// 默认物体类型,详见"支持的检测物体类型列表"
	bool				bSnapShot;								// 是否对识别物体抓图
	BYTE                bSensitivity;                           // 灵敏度,取值1-10，值越小灵敏度越低
	bool                bMeasureModeEnable;                     // 计量方式参数是否有效
	BYTE                bMeasureMode;                           // 计量方式,0-像素，不需要远端、近端标定, 1-实际长度，单位：米, 2-远端近端标定后的像素
	int					nDetectRegionPoint;						// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 检测区域
	int					nTrackRegionPoint;						// 跟踪区域顶点数
	CFG_POLYGON			stuTrackRegion[MAX_POLYGON_NUM];		// 跟踪区域
	bool                bFilterTypeEnable;                      // 过滤类型参数是否有效
	// ByArea,ByRatio仅作兼容，使用独立的ByArea和ByRatio选项代替 2012/03/06
	BYTE				nFilterType;							// 过滤类型:0:"ByLength",1:"ByArea", 2:"ByWidthHeight", 3:"ByRatio": 按照宽高比，宽度除以高度的结果小于某个值或者大于某个值的问题将被过滤掉。
	bool                bBackgroudEnable;                       // 区域的背景类型参数是否有效
	BYTE                bBackgroud;                             // 区域的背景类型, 0-普通类型, 1-高光类型
	bool                abBySize;                               // 长宽过滤使能参数是否有效
	bool                bBySize;                                // 长宽过滤使能
	bool                bFilterMinSizeEnable;                   // 物体最小尺寸参数是否有效
	bool                bFilterMaxSizeEnable;                   // 物体最大尺寸参数是否有效
	CFG_SIZE			stuFilterMinSize;						// 物体最小尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。
	CFG_SIZE			stuFilterMaxSize;						// 物体最大尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。
	int                 nExcludeRegionNum;                      // 排除区域数
	CFG_REGION          stuExcludeRegion[MAX_EXCLUDEREGION_NUM];// 排除区域
	int                 nCalibrateBoxNum;                       // 校准框个数
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 校准框(远端近端标定模式下有效)
	bool                bAccuracy;                               // 检测精度是否有效
	BYTE                byAccuracy;                              // 检测精度
	bool                bMovingStep;                             // 算法移动步长是否有效                        
	BYTE                byMovingStep;                            // 算法移动步长
	bool                bScalingFactor;							 // 算法缩放因子是否有效
	BYTE                byScalingFactor;						 // 算法缩放因子

	BYTE                bReserved2[1];                           // 保留字段
	bool                abDetectBalance;						 // 漏检和误检平衡参数是否有效
	int					nDetectBalance;							 // 漏检和误检平衡	0-折中模式(默认)1-漏检更少2-误检更少
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByRatio;                                // 是否按宽高比过滤 通过能力ComplexSizeFilter判断是否可用 可以和nFilterType复用
	bool                bReserved1[2];
	double              dMinRatio;                               // 最小宽高比
	double              dMaxRatio;                               // 最大宽高比
	CFG_SIZE            stuMinAreaSize;                           // 最小面积矩形框尺寸 "计量方式"为"像素"时，表示最小面积矩形框的宽高尺寸；"计量方式"为"远端近端标定模式"时，表示基准框的最小宽高尺寸；
	CFG_SIZE            stuMaxAreaSize;                           // 最大面积矩形框尺寸, 同上
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByArea;                                 // 是否按面积过滤 通过能力ComplexSizeFilter判断是否可用  可以和nFilterType复用
	bool                bReserved3[2];
	float               nMinArea;                                // 最小面积
	float               nMaxArea;                                // 最大面积
	CFG_SIZE            stuMinRatioSize;                          // 最小宽高比矩形框尺寸，最小宽高比对应矩形框的宽高尺寸。
	CFG_SIZE            stuMaxRatioSize;                          // 最大宽高比矩形框尺寸，同上
	
	int                 nAreaCalibrateBoxNum;                    // 面积校准框个数
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 面积校准框
	int                 nRatioCalibrateBoxs;                      // 比例校准框个数
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 比例校准框个数

	bool                bAntiDisturbance;                        // 是否开启去扰动模块
	bool                bBacklight;                              // 是否有逆光
	bool                bShadow;                                 // 是否有阴影
	bool                bContourAssistantTrack;                  // 是否开启轮廓辅助跟踪，例：在人脸识别时可以通过跟踪人体来辅助识别人脸
	int                 nPtzPresetId;                            // 云台预置点，0~255，0表示固定场景，忽略预置点。大于0表示在此预置点时模块有效

	int                 nObjectFilterNum;                        // 物体特定的过滤器个数
	CFG_OBJECT_SIZEFILTER_INFO stObjectFilter[MAX_OBJECT_LIST_SIZE]; // 物体特定的过滤器信息

	BOOL                abObjectImageSize;                        
	CFG_SIZE            stObjectImageSize;                       // 保证物体图像尺寸相同,单位是像素,不支持小数，取值：>=0,  0 表示自动调整大小

	int                 nSpecailDetectNum;                                // 特殊检测区域个数
	CFG_SPECIALDETECT_INFO stSpecialDetectRegions[MAX_SPECIALDETECT_NUM];  // 特殊检测区信息

	unsigned int        nAttribute;                              // 需要识别物体的属性个数
	char                szAttributes[MAX_OBJECT_ATTRIBUTES_SIZE][MAX_NAME_LEN];   // 需要识别物体的属性列表，“Category” 物体子类；“Size” 物体大小；“Color” 物体颜色；“Speed” 物体速度；“Sign” 物体标志，对车辆而言，指车标；“Action” 物体动作
	
	BOOL                abPlateAnalyseMode;                      // nPlateAnalyseMode是否有效
	int                 nPlateAnalyseMode;                       // 车牌识别模式，0-只识别车头牌照 1-只识别车尾牌照 2-车头牌照优先（场景中大部分车均是车头牌照）3-车尾牌照优先（场景中大部分车均是车尾牌照）
} CFG_MODULE_INFO;

typedef struct tagCFG_ANALYSEMODULES_INFO
{
	int					nMoudlesNum;							// 检测模块数
	CFG_MODULE_INFO     stuModuleInfo[MAX_ANALYSE_MODULE_NUM];			// 每个视频输入通道对应的各种类型物体的检测模块配置

} CFG_ANALYSEMODULES_INFO;

// 视频分析事件规则配置相关结构体定义
enum CFG_EM_DETECTMODE_T{
	CFG_EM_DETECTMODE_NONE,            // 无此字段
	CFG_EM_DETECTMODE_BY_VIDEO,        // 视频检测模式
	CFG_EM_DETECTMODE_BY_BYAUDIO,      // 音频检测模式
	CFG_EM_DETECTMODE_BY_BOTH,         // 音视频联合检测模式
	CFG_EM_DETECTMODE_ERR=255          // 字段数据错误
};

// 视频分析事件规则配置
// 事件类型EVENT_IVS_CROSSLINEDETECTION(警戒线事件)对应的规则配置
typedef struct tagCFG_CROSSLINE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDirection;												// 检测方向:0:由左至右;1:由右至左;2:两者都可以
	int					nDetectLinePoint;										// 警戒线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 警戒线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
 	BOOL                bDisableTimeSection;                                    // stuTimeSection字段是否禁用，默认FALSE：不禁用，TRUE：禁用，用户控制

	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心

} CFG_CROSSLINE_INFO;

//事件类型EVENT_IVS_CROSSFENCEDETECTION(翻越围栏规则)对应的规则配置
typedef struct tagCFG_CROSSFENCEDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDirection;												// 翻越围栏方向:0:由左至右;1:由右至左;2:两者都可以
	int					nUpstairsLinePointNumber;								// 围栏上线顶点数
	CFG_POLYLINE		stuUpstairsLine[MAX_POLYLINE_NUM];						// 围栏上线
	int					nDownstairsLinePointNumber;								// 围栏下线顶点数
	CFG_POLYLINE		stuDownstairsLine[MAX_POLYLINE_NUM];					// 围栏下线
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_CROSSFENCEDETECTION_INFO;

// 事件类型EVENT_IVS_CROSSREGIONDETECTION(警戒区事件)对应的规则配置
typedef struct tagCFG_CROSSREGION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDirection;												// 检测方向:0:Enter;1:Leave;2:Both
	int					nDetectRegionPoint;										// 警戒区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 警戒区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动

	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
 	BOOL                bDisableTimeSection;                                    // stuTimeSection字段是否禁用，默认FALSE：不禁用，TRUE：禁用，用户控制

	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nActionType;                                            // 检测动作数
	BYTE                bActionType[4];                                         // 检测动作列表,0-出现 1-消失 2-在区域内 3-穿越区域
	int                 nMinTargets;                                            // 最小目标个数(当bActionType中包含"2-在区域内"时有效)
	int                 nMaxTargets;                                            // 最大目标个数(当bActionType中包含"2-在区域内"时有效)
	int                 nMinDuration;                                           // 最短持续时间， 单位秒(当bActionType中包含"2-在区域内"时有效)
	int                 nReportInterval;                                        // 报告时间间隔， 单位秒(当bActionType中包含"2-在区域内"时有效)
		
} CFG_CROSSREGION_INFO;

// 事件类型EVENT_IVS_PASTEDETECTION(ATM贴条事件)对应的规则配置
typedef struct tagCFG_PASTE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
		
} CFG_PASTE_INFO;

// 事件类型EVENT_IVS_LEFTDETECTION(物品遗留事件)对应的规则配置
typedef struct tagCFG_LEFT_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_LEFT_INFO;

// 事件类型EVENT_IVS_TAKENAWAYDETECTION(物品搬移规则配置)对应的规则配置
typedef struct tagCFG_TAKENAWAYDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_TAKENAWAYDETECTION_INFO;

// 事件类型EVENT_IVS_PARKINGDETECTION (非法停车)对应的规则配置
typedef struct tagCFG_PARKINGDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_PARKINGDETECTION_INFO;

// 事件类型EVENT_IVS_PRESERVATION(物品保全事件)对应的规则配置
typedef struct tagCFG_PRESERVATION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_PRESERVATION_INFO;

// 事件类型EVENT_IVS_STAYDETECTION(停留事件/滞留)对应的规则配置
typedef struct tagCFG_STAY_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nTriggerTargetsNumber;                                  // 触发报警的徘徊或滞留人数
	int                 nReportInterval;                                        // 报告时间间隔,单位秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	
} CFG_STAY_INFO;

// 事件类型EVENT_IVS_WANDERDETECTION(徘徊事件)对应的规则配置
typedef struct tagCFG_WANDER_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nTriggerTargetsNumber;                                  // 触发报警的徘徊或滞留人数
	int                 nReportInterval;                                        // 报告时间间隔,单位秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_WANDER_INFO;

// 事件类型EVENT_IVS_MOVEDETECTION(移动事件/运动检测)对应的规则配置
typedef struct tagCFG_MOVE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度，取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerSpeed;                                          // 触发速度，km/h
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器	
	int                 nTypeNumber;                                            // 检测类型数
	BYTE                bDetectType[4];                                         // 检测动作列表,0-快速运动 1-突然加速 2-突然减速

} CFG_MOVE_INFO;

// 事件类型EVENT_IVS_TAILDETECTION(尾随事件)对应的规则配置
typedef struct tagCFG_TAIL_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_TAIL_INFO;

// 事件类型EVENT_IVS_RIOTERDETECTION(聚众事件)对应的规则配置
typedef struct tagCFG_RIOTER_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bAreaPercent;                                           // 聚集所占区域面积百分比
	BYTE                bSensitivity;                                           // 灵敏度，取值1-10，值越小灵敏度越低，对应人群的密集程度越高(取代bAreaPercent)
	BYTE                bReserved;												// 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

	int                 nReportInterval;                                        // 报告时间间隔,单位秒 [1,600] 默认0表示不重复报警
	CFG_POLYGON         stuMinDetectRect[2];                                    // 最小聚集区域矩形框，分别对应矩形框的左上和右下点，矩形框的实际面积表示触发报警的最小人群聚集面积
} CFG_RIOTER_INFO;

// 事件类型EVENT_IVS_DENSITYDETECTION(人群密度检测事件)对应的规则配置
typedef struct tagCFG_DENSITYDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved1;                                             // 保留字段
	BYTE                bSensitivity;                                           // 灵敏度(取值1-10，值越小灵敏度越低，对应人群的密集程度越高)
	BYTE                bReserved2;                                             // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_DENSITYDETECTION_INFO;


// 事件类型EVENT_IVS_FIGHTDETECTION(斗殴事件)对应的规则配置
typedef struct tagCFG_FIGHT_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nSensitivity;											// 灵敏度, 1-10
    CFG_EM_DETECTMODE_T emDetectMode;                                           // 检测模式

} CFG_FIGHT_INFO;

// 事件类型EVENT_IVS_FIREDETECTION(火警事件/火焰检测)对应的规则配置
typedef struct tagCFG_FIRE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_FIRE_INFO;

// 事件类型EVENT_IVS_ELECTROSPARKDETECTION(电火花事件)对应的规则配置
typedef struct tagCFG_ELECTROSPARK_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_ELECTROSPARK_INFO;

// 事件类型EVENT_IVS_SMOKEDETECTION(烟雾报警事件)对应的规则配置
typedef struct tagCFG_SMOKE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_SMOKE_INFO;

// 事件类型EVENT_IVS_FLOWSTAT(流量统计事件)对应的规则配置
typedef struct tagCFG_FLOWSTAT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nUpperLimit;											// 流量上限	单位：个/秒，1~65535
	int					nPeriod;												// 上报周期	单位：秒，1~65535
	int					nDetectLinePoint;										// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 检测线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
		
} CFG_FLOWSTAT_INFO;

enum NET_NUMBERSTAT_TYPE
{
	NET_EM_NUMSTAT_TYPE_REGION,                  // "Region" 区域类型
		NET_EM_NUMSTAT_TYPE_ENTRANCE,            // "Entrance" 出入口类型
		NET_EM_NUMSTAT_TYPE_OTHER,               // other
};
// 事件类型EVENT_IVS_NUMBERSTAT(数量统计事件)对应的规则配置
typedef struct tagCFG_NUMBERSTAT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nUpperLimit;											// 数量上限 单位：个，1~65535
	int					nPeriod;												// 上报周期	单位：秒，1~65535
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	NET_NUMBERSTAT_TYPE emType;                                                 // 数量统计类型	支持："Region" 区域类型 "Entrance" 出入口类型
	CFG_POLYGON         stDirection[2];                                         // 正常运动方向, 按照此方向行驶是正向，反过来是逆行	只对出入口类型有效。第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间。
    int                 nRecordInterval;                                        // 记录周期，单位：分钟，1~10
} CFG_NUMBERSTAT_INFO;

//事件类型EVENT_IVS_RETROGRADEDETECTION(人员逆行事件)对应的规则配置
typedef struct tagCFG_RETROGRADEDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int                 nDirectionPoint;                                        // 正常行驶方向顶点数
	CFG_POLYGON			stuDirection[MAX_POLYLINE_NUM];					      	// 正常行驶方向, 按照此方向行驶是正向，反过来是逆行(第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间)
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_RETROGRADEDETECTION_INFO;

//事件类型EVENT_IVS_ABNORMALRUNDETECTION(异常奔跑事件)对应的规则配置
typedef struct tagCFG_ABNORMALRUNDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nDetectType;                                            // 检测类型数
	BYTE                bDetectType[4];                                         // 检测类型,0-快速奔跑, 1-突然加速, 2-突然减速
	int                 nTriggerSpeed;                                          // 触发速度，大于该速度报警	单位：km/h
	int                 nMinDuration;                                           // 最短持续时间	单位：秒，0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_ABNORMALRUNDETECTION_INFO;

//事件类型EVENT_IVS_VIDEOABNORMALDETECTION(视频异常)对应的规则配置
typedef struct tagCFG_VIDEOABNORMALDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低(只对检测类型视频遮挡，过亮，过暗，场景变化有效)
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nDetectType;                                            // 检测类型数
	BYTE                bDetectType[8];                                         // 检测类型,0-视频丢失, 1-视频遮挡, 2-画面冻结, 3-过亮, 4-过暗, 5-场景变化
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	
} CFG_VIDEOABNORMALDETECTION_INFO;

// 事件类型EVENT_IVS_FACERECOGNITION(人脸识别)对应的规则配置
typedef struct tagCFG_FACERECOGNITION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BYTE                 bySimilarity;                                          // 相似度，必须大于该相识度才报告(1~100)
	BYTE                 byAccuracy;                                            // 识别精度(取值1~10，随着值增大，检测精度提高，检测速度下降。最小值为1 表示检测速度优先，最大值为10表示检测精度优先)
	BYTE                 byMode;                                                // 对比模式, 0-正常, 1-指定人脸区域组合, 2-智能模式(算法根据人脸各个区域情况自动选取组合)
	BYTE                 byImportantRank;                                       // 查询重要等级大于等于此等级的人员(1~10,数值越高越重要)
	int                  nAreaNum;                                              // 区域数  
	BYTE                 byAreas[8];                                            // 人脸区域组合, 0-眉毛，1-眼睛，2-鼻子，3-嘴巴，4-脸颊(此参数在对比模式为1时有效)
	int                  nMaxCandidate;                                         // 报告的最大匹配图片个数
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_FACERECOGNITION_INFO;


// 事件类型EVENT_IVS_TRAFFICCONTROL(交通管制事件)对应的规则配置
typedef struct tagCFG_TRAFFICCONTROL_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];									// 规则名称,不同规则不能重名
	bool				bRuleEnable;												// 规则使能
	BYTE                bReserved[3];                                               // 保留字段
	int					nObjectTypeNum;												// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];			// 相应物体类型列表
	int					nDetectLinePoint;							            	// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];			            	// 检测线
	CFG_TIME_SECTION	stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];           	// 限行时间表
	int					nVehicleSizeNum;							            	// 车辆大小类型个数
	char				szVehicleSizeList[MAX_VEHICLE_SIZE_LIST][MAX_NAME_LEN];		// 车辆大小类型列表"Light-duty":小型车;	"Medium":中型车; "Oversize":大型车
	int					nPlateTypeNum;												// 车牌类型个数
	char				szPlateTypesList[MAX_PLATE_TYPE_LIST][MAX_NAME_LEN];		// 车牌类型列表"Unknown" 未知; "Normal" 蓝牌黑牌; "Yellow" 黄牌; "DoubleYellow" 双层黄尾牌
																					// "Police" 警牌; "Armed" 武警牌; "Military" 部队号牌; "DoubleMilitary" 部队双层
																					// "SAR" 港澳特区号牌; "Trainning" 教练车号牌; "Personal" 个性号牌; "Agri" 农用牌
																					// "Embassy" 使馆号牌; "Moto" 摩托车号牌; "Tractor" 拖拉机号牌; "Other" 其他号牌
	int					nPlateNumber;												// 车牌单双号 0:单号; 1:双号; 2:单双号;	
	CFG_ALARM_MSG_HANDLE stuEventHandler;											// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];				// 事件响应时间段
	int                 nPtzPresetId;												// 云台预置点编号	0~65535
} CFG_TRAFFICCONTROL_INFO;

// 事件类型EVENT_IVS_TRAFFICACCIDENT(交通事故事件)对应的规则配置
typedef struct tagCFG_TRAACCIDENT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_TRAACCIDENT_INFO;

// 事件类型EVENT_IVS_TRAFFICJUNCTION(交通路口老规则事件)对应的规则配置
typedef struct tagCFG_TRAJUNCTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];				// 规则名称,不同规则不能重名
	bool				bRuleEnable;							// 规则使能
	int					nObjectTypeNum;							// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nLane;									// 车道编号
	int                 nDirection;                             // 车道方向(车开往的方向),0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int					nPreLinePoint;							// 前置检测线顶点数
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			// 前置检测线
	int					nMiddleLinePoint;						// 中间检测线顶点数
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		// 中间检测线
	int					nPostLinePoint;							// 后置检测线顶点数
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			// 后置检测线
	int                 nFlowLimit;                             // 流量上限，单位辆/秒
	int                 nSpeedDownLimit;                        // 速度下限，若为0，则表示不设下限，km/h
	int                 nSpeedUpLimit;                          // 速度上限，若为0，则表示不设上限，km/h
	int                 nTriggerModeNum;                        // 触发模式个数
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];  // 触发模式，"Passing" : 穿过路口(以中间检测线为准，只能单独使用),"RunRedLight" : 闯红灯
																// "Overline":压白车道线,"OverYellowLine": 压黄线, "Retrograde":逆行
																// "TurnLeft":违章左转, "TurnRight":违章右转, "CrossLane":违章变道
																// "U-Turn" 违章掉头, "Parking":违章停车, "WaitingArea" 违章进入待行区
																// "OverSpeed": 超速,"UnderSpeed":欠速,"Overflow" : 流量过大
																// "Human":行人,"NoMotor":非机动车

	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bMaskRetrograde;         	             // 是否屏蔽逆行，即将逆行当作正常处理
			
} CFG_TRAJUNCTION_INFO;

// 事件类型EVENT_IVS_TRAFFICGATE(交通卡口老规则事件)对应的规则配置
typedef struct tagCFG_TRAFFICGATE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nLane;													// 车道编号
	int					nDetectLinePoint1;										// 检测线(虚拟线圈)1顶点数
	CFG_POLYLINE		stuDetectLine1[MAX_POLYLINE_NUM];						// 检测线1
	int					nDetectLinePoint2;										// 检测线(虚拟线圈)2顶点数
	CFG_POLYLINE		stuDetectLine2[MAX_POLYLINE_NUM];						// 检测线2
	int					nLeftLinePoint;											// 左车道线顶点数
	CFG_POLYLINE		stuLeftLine[MAX_POLYLINE_NUM];							// 左车道线
	int					nRightLinePoint;										// 右车道线顶点数
	CFG_POLYLINE		stuRightLine[MAX_POLYLINE_NUM];							// 右车道线
	int					nSpeedWeight;											// 速度权重系数(最终车速=测量车速*权重系数)
	double				MetricDistance;											// 两条检测线实际距离,单位：米
	int					nSpeedUpperLimit;										// 速度上限 0表示不限上限 单位：km/h
	int					nSpeedLowerLimit;										// 速度下限 0表示不限下限 单位：km/h
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nDirection;                                             // 车道方向(车开往的方向)，0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int                 nTriggerModeNum;                                        // 触发模式个数
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];       // 触发模式，"OverLine":压线,"Retrograde":逆行,"OverSpeed":超速,"UnderSpeed":欠速
	                                                                            // "Passing":穿过路口，属正常抓拍, "WrongRunningRoute":有车占道(单独使用),"YellowVehicleInRoute": 黄牌占道
	                                                                            // "OverYellowLine":压黄线
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bMaskRetrograde;         	             // 是否屏蔽逆行，即将逆行当作正常处理
} CFG_TRAFFICGATE_INFO;

// 事件类型EVENT_IVS_TRAFFIC_TOLLGATE(交通卡口新规则事件)对应的规则配置
typedef struct tagCFG_TRAFFICTOLLGATE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

	int					nLane;													// 车道编号
	int					nDetectLinePoint;										// 卡口报警线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 卡口报警线

	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
} CFG_TRAFFICTOLLGATE_INFO;

// 事件类型EVENT_IVS_FACEDETECT(人脸检测事件)对应的规则配置
typedef struct tagCFG_FACEDETECT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	int                 nHumanFaceTypeCount;                                    // 触发事件的人脸类型个数
	char                szHumanFaceType[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // 触发事件的人脸类型
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
}CFG_FACEDETECT_INFO;

//事件类型EVENT_IVS_TRAFFIC_NOPASSING(交通违章-禁止通行事件)对应的数据块描述信息
typedef struct tagCFG_NOPASSING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
}CFG_NOPASSING_INFO;

// 事件类型EVENT_IVS_TRAFFICJAM (交通拥堵事件)对应的规则配置
typedef struct tagCFG_TRAFFICJAM_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
    BYTE                bJamLineMargin;                                         // 占线限值，拥堵长度占车道比例限值，0-100
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nIntervalTime;                                          // 报警间隔时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int		            nDetectRegionPoint;                                     // 检测区顶点数
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区域
}CFG_TRAFFICJAM_INFO;

// 事件类型EVENT_IVS_TRAFFIC_IDLE (交通空闲事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_IDLE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
    BYTE                bJamLineMargin;                                         // 占线限值，拥堵长度占车道比例限值，0-100
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nIntervalTime;                                          // 报警间隔时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int		            nDetectRegionPoint;                                     // 检测区顶点数
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区域
}CFG_TRAFFIC_IDLE_INFO;


// 事件类型EVENT_IVS_TRAFFIC_PARKING (交通违章停车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nParkingAllowedTime;                                    // 允许停车时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
		
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	
	
}CFG_TRAFFIC_PARKING_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_RUNREDLIGHT (交通违章-闯红灯事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_RUNREDLIGHT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDirection;                                             // 车道方向(车开往的方向)，0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int					nPreLinePoint;							                // 前置检测线顶点数
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			                // 前置检测线
	int					nMiddleLinePoint;						                // 中间检测线顶点数
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		                // 中间检测线
	int					nPostLinePoint;							                // 后置检测线顶点数
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			                // 后置检测线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_RUNREDLIGHT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_WRONGROUTE (交通违章-不按车道行驶事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_WRONGROUTE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_WRONGROUTE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_CROSSLANE (交通违章-违章变道)对应的规则配置
typedef struct tagCFG_TRAFFIC_CROSSLANE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_CROSSLANE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERLINE (交通违章-压车道线)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_OVERLINE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERYELLOWLINE (交通违章-压黄线)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERYELLOWLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域

}CFG_TRAFFIC_OVERYELLOWLINE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_RETROGRADE (交通违章-逆行事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_RETROGRADE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	BOOL                bLegal;                                                 // TRUE: 逆行合法;FALSE:逆行不合法
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
	CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
}CFG_TRAFFIC_RETROGRADE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_TURNLEFT (交通违章-违章左转事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_TURNLEFT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_TURNLEFT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_TURNRIGHT (交通违章-违章右转)对应的规则配置
typedef struct tagCFG_TRAFFIC_TURNRIGHT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_TURNRIGHT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_UTURN (交通违章-违章掉头)对应的规则配置
typedef struct tagCFG_TRAFFIC_UTURN_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段


	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int					nTriggerAngle;											// 掉头触发角度,取值范围(90,180)，目标调头前后的运动夹角
	BOOL                abSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	
}CFG_TRAFFIC_UTURN_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERSPEED (交通违章-超速)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nSpeedUpperLimit;                                       // 速度上限
	int                 nSpeedLowerLimit;                                       // 速度下限
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_OVERSPEED_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_UNDERSPEED (交通违章-欠速)对应的规则配置
typedef struct tagCFG_TRAFFIC_UNDERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nSpeedUpperLimit;                                       // 速度上限
	int                 nSpeedLowerLimit;                                       // 速度下限
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_UNDERSPEED_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE (交通违章-黄牌车占道事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_YELLOWPLATEINLANE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_YELLOWPLATEINLANE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_VEHICLEINROUTE (交通违章-有车占道事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_VEHICLEINROUTE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_VEHICLEINROUTE_INFO;

// 事件类型 EVENT_IVS_PRISONERRISEDETECTION (看守所起身检测事件)对应的规则配置
typedef struct tagCFG_PRISONRISEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 警戒区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM10];						// 警戒区
	CFG_POLYGON			stDirection[2];											// 人睡觉方向	第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间
	CFG_POLYGON			stBedMiddleLine[2];										// 床铺中线	点的坐标归一化到[0,8191]区间
	int					nBedSide;												// 床铺的方位	1左边铺位,2右边铺位
	int					nMinDuration;											// 最短触发时间	单位：秒
	int					nReportInterval;										// 重复报警间隔	单位：秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
}CFG_PRISONRISEDETECTION_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY (斑马线行人优先事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PEDESTRAINPRIORITY_INFO
{
	char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
	bool                bRuleEnable;                                            // 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int                 nObjectTypeNum;                                         // 相应物体类型个数
	char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
	int                 nPtzPresetId;                                           // 云台预置点编号	0~65535
	int                 nLane;                                                  // 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
	CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];            // 事件响应时间段
}CFG_TRAFFIC_PEDESTRAINPRIORITY_INFO;

// 事件类型 EVENT_IVS_QUEUEDETECTION (排队检测事件)对应的规则配置
typedef struct tagCFG_IVS_QUEUEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	CFG_POLYLINE		stuDetectLine[2];						                // 警戒线
	int                 nOccupyLineMargin;                                      // 占线限值，队伍长度占线比例限值
	int                 nTriggerTime;                                           // 单位秒，排队检测报警时间，排队超过阈值的状态维持了"排队检测报警时间"以后报警
}CFG_IVS_QUEUEDETECTION_INFO;

// 事件类型 EVENT_IVS_CLIMBDETECTION (攀高检测事件)对应的规则配置
typedef struct tagCFG_IVS_CLIMBDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int                 nDetectLine;                                            // 检测线顶点个数
	CFG_POLYLINE        stuDetectLine[MAX_POLYLINE_NUM];                        // 对应的检测折线,[0,8192)
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
}CFG_IVS_CLIMBDETECTION_INFO;

// 事件类型 EVENT_IVS_LEAVEDETECTION (离岗检测事件)对应的规则配置
enum CFG_EM_LEAVEDETECTION_MODE{
	CFG_EM_LEAVEDETECTION_MODE_NONE,
	CFG_EM_LEAVEDETECTION_MODE_PATROL,    // 巡逻模式
	CFG_EM_LEAVEDETECTION_MODE_SENTRY,    // 岗哨模式
	CFG_EM_LEAVEDETECTION_MODE_ERR=255
};
typedef struct tagCFG_IVS_LEAVEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	CFG_EM_LEAVEDETECTION_MODE emMode;                                          // 检测模式
	unsigned int        nMinDuration;                                           // 最短持续时间,单位：秒
	unsigned int        nReportInterval;                                        // 报告时间间隔,单位：秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
}CFG_IVS_LEAVEDETECTION_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX(黄网格线抓拍事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGONYELLOWBOX_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nLane;													// 车道号
	int					nInterval1;												// 第二张和第一张的延时时间，单位秒
	int					nInterval2;												// 第三张和第二张的延时时间，单位秒
	int					nFollowTime;											// 跟随时间，如果一辆车与前一辆车进入黄网格的时间差小于此值，就认为是跟车进入，跟车进入情况下如果停车则不算违章

}CFG_TRAFFIC_PARKINGONYELLOWBOX_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING(车位有车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGSPACEPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	int					nLane;													// 车道号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
}CFG_TRAFFIC_PARKINGSPACEPARKING_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING(车位无车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGSPACENOPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	int					nLane;													// 车道号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
}CFG_TRAFFIC_PARKINGSPACENOPARKING_INFO;

//事件类型 EVENT_IVS_TRAFFIC_PEDESTRAIN (交通行人事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PEDESTRAIN_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nMinDuration;                                           // 最短触发时间，单位：秒
}CFG_TRAFFIC_PEDESTRAIN_INFO;

//事件类型 EVENT_IVS_TRAFFIC_THROW (交通抛洒事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_THROW_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nMinDuration;                                           // 最短触发时间，单位：秒
}CFG_TRAFFIC_THROW_INFO;

typedef struct tagCFG_RULE_INFO
{
	DWORD				dwRuleType;							// 事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int					nRuleSize;							// 该事件类型规则配置结构体大小
	
} CFG_RULE_INFO;

// 每个视频输入通道对应的所有事件规则：缓冲区pRuleBuf填充多个事件规则信息，每个事件规则信息内容为CFG_RULE_INFO+"事件类型对应的规则配置结构体"。
typedef struct tagCFG_ANALYSERULES_INFO
{
	int					nRuleCount;							// 事件规则个数
	char*				pRuleBuf;							// 每个视频输入通道对应的视频分析事件规则配置缓冲
	int					nRuleLen;							// 缓冲大小

} CFG_ANALYSERULES_INFO;

// 每个视频输入通道对应的视频分析资源配置信息
typedef struct tagCFG_ANALYSESOURCE_INFO
{
	bool				bEnable;								// 视频分析使能
	BYTE				bReserved[3];							// 保留对齐
	int					nChannelID;								// 智能分析的前端视频通道号
	int					nStreamType;							// 智能分析的前端视频码流类型，0:抓图码流; 1:主码流; 2:子码流1; 3:子码流2; 4:子码流3; 5:物体流
	char				szRemoteDevice[MAX_NAME_LEN];			// 设备名
	BOOL				abDeviceInfo;				        	// 设备信息是否有效
	AV_CFG_RemoteDevice stuDeviceInfo;					        // 设备信息
} CFG_ANALYSESOURCE_INFO;

//视频分析整体配置，影响设备或服务器整体行为
typedef struct tagCFG_ANALYSEWHOLE_INFO
{	
	unsigned  int nVideoChannelType;		// 视频通道类型选择 0:数字，1;模拟，2:数字和模拟
	
}CFG_ANALYSEWHOLE_INFO;




typedef struct tagCFG_RAINBRUSH_INFO
{
	bool                bEnable;                                 // 雨刷使能
	BYTE                bSpeedRate;                              // 雨刷速度,1:快速;2:中速;3:慢速
	BYTE                bReserved[2];                            // 保留对齐
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段

}CFG_RAINBRUSH_INFO;

// BreakingSnapTimes
typedef struct tagBREAKINGSNAPTIMES_INFO
{
	int               nNormal;                          // 正常
	int               nRunRedLight;                     // 闯红灯
	int			      nOverLine;						// 压线
	int				  nOverYellowLine;			  	    // 压黄线
	int				  nRetrograde;			    	    // 逆向
	int				  nUnderSpeed;					    // 欠速
    int				  nOverSpeed;						// 超速
	int			      nWrongRunningRoute;				// 有车占道
	int			      nYellowInRoute;					// 黄牌占道
	int		    	  nSpecialRetrograde;				// 特殊逆行
	int			      nTurnLeft;						// 违章左转
	int			      nTurnRight;						// 违章右转
	int			      nCrossLane;						// 违章变道
	int			      nU_Turn;						    // 违章调头
	int			      nParking;						    // 违章停车
	int               nWaitingArea;						// 违章进入待行区
	int			      nWrongRoute;					    // 不按车道行驶		
	int               nParkingSpaceParking;             // 车位有车
	int               nParkingSpaceNoParking;           // 车位无车
}BREAKINGSNAPTIMES_INFO;

// Detector -- BEGIN
// CoilConfig
typedef struct tagCOILCONFIG_INFO
{
	int               nDelayFlashID;                 // 延时闪光灯序号	每个线圈对应的延时闪关灯序号，范围0~5，0表示不延时任何闪光灯
	int               nFlashSerialNum;               // 闪光灯序号	范围0~5，0表示不打开闪光灯（鄞州项目用）
	int               nRedDirection;                 // 红灯方向	每个线圈对应的红灯方向：0-不关联,1-左转红灯,2-直行红灯,3-右转红灯,4-待左,5-待直,6-待右, 只在电警中有效
	int               nTriggerMode ;                 // 线圈触发模式	触发模式：0-入线圈触发1-出线圈触发（鄞州项目用）
}COILCONFIG_INFO;

typedef struct tagDETECTOR_INFO
{
	int                nDetectBreaking;                  // 违章类型掩码	从低位到高位依次是：0-正常1-闯红灯2-压线3-逆行4-欠速5-超速6-有车占道7-黄牌占道
	COILCONFIG_INFO    arstCoilCfg[MAX_COILCONFIG];      // 线圈配置数组
	int				   nRoadwayNumber;				     // 车道号	1-16 ; 0表示不启用
	int                nRoadwayDirection;                // 车道方向（车开往的方向）	0-南向北 1-西南向东北 2-东 3-西北向东南 4-北向南 5-东北向西南 6-东向西 7-东南向西北 8-忽略
	int                nRedLightCardNum;                 // 卡口图片序号	表示将电警中的某一张图片作为卡口图片（共三张），0表示不采用，1~3,表示采用对应序号的图片
	int                nCoilsNumber;                     // 线圈个数	1-3
	int                nOperationType;                   // 业务模式	0-卡口电警1-电警2-卡口
	int                arnCoilsDistance[3];              // 两两线圈的间隔	范围0-1000，单位为厘米
	int                nCoilsWidth;                      // 每个线圈的宽度	0~200cm
	int                arnSmallCarSpeedLimit[2];         // 小型车辆速度下限和上限	0~255km/h，不启用大小车限速时作为普通车辆限速
	int				   arnBigCarSpeedLimit[2];           // 大型车辆速度下限和上限	0~255km/h，启用大小车限速时有效
	int				   nOverSpeedMargin;			     // 限高速宽限值	单位：km/h
	int                nBigCarOverSpeedMargin;           // 大车限高速宽限值	单位：km/h，启用大小车限速时有效
	int				   nUnderSpeedMargin;			     // 限低速宽限值	单位：km/h
	int                nBigCarUnderSpeedMargin;          // 大车限低速宽限值	单位：km/h，启用大小车限速时有效
	bool               bSpeedLimitForSize;               // 是否启用大小车限速
	bool			   bMaskRetrograde;				     // 逆行是否视为违章行为
	BYTE               byReserved[2];                    // 保留对齐
	char               szDrivingDirection[3][MAX_DRIVINGDIRECTION]; //
													     // "DrivingDirection" : ["Approach", "上海", "杭州"],行驶方向
													     // "Approach"-上行，即车辆离设备部署点越来越近；"Leave"-下行，
														 // 即车辆离设备部署点越来越远，第二和第三个参数分别代表上行和
														 // 下行的两个地点，UTF-8编码
	int                nOverPercentage;                  // 超速百分比，超过限速百分比后抓拍

	int                nCarScheme;                       // 具体的方案Index,具体方案含义参参考打包环境local.png;根据CFG_TRAFFICSNAPSHOT_INFO.abSchemeRange字段区分作用范围
	int                nSigScheme;                       // 同上，非卡口使用
	BOOL               bEnable;                          // 车道是否有效，只有有效时才抓拍
}DETECTOR_INFO;
// Detector -- END

// CFG_CMD_INTELLECTIVETRAFFIC
typedef struct tagCFG_TRAFFICSNAPSHOT_INFO
{
	char                     szDeviceAddress[MAX_DEVICE_ADDRESS];  // 设备地址	UTF-8编码，256字节
	int                      nVideoTitleMask;                      // OSD叠加类型掩码	从低位到高位分别表示：0-时间 1-地点 2-车牌3-车长 4-车速 5-限速6-大车限速 7-小车限速8-超速 9-违法代码10-车道号 11-车身颜色 12-车牌类型 13-车牌颜色14-红灯点亮时间 15-违章类型 16-雷达方向 17-设备编号 18-标定到期时间 19-车型 20-行驶方向
	int                      nRedLightMargin;                      // 红灯冗余间隔时间	红灯开始的一段时间内，车辆通行不算闯红灯，单位：秒
	float				     fLongVehicleLengthLevel;              // 超长车长度最小阈值	单位：米，包含
	float					 arfLargeVehicleLengthLevel[2];        // 大车长度阈值	单位：米，包含小值
	float					 arfMediumVehicleLengthLevel[2];       // 中型车长度阈值	单位：米，包含小值
	float					 arfSmallVehicleLengthLevel[2];        // 小车长度阈值	单位：米，包含小值
	float					 fMotoVehicleLengthLevel;              // 摩托车长度最大阈值	单位：米，不包含
	BREAKINGSNAPTIMES_INFO   stBreakingSnapTimes;                  // 违章抓拍张数
	DETECTOR_INFO            arstDetector[MAX_DETECTOR];           // 车检器配置，下标是车道号
	int 					 nCarType;			               	   // 抓拍车辆类型	0-大小车都抓拍1-抓拍小车2-抓拍大车3-大小车都不抓拍
	int						 nMaxSpeed;			               	   // 当测得的速度超过最大速度时，则以最大速度计	0~255km/h
	int						 nFrameMode;		               	   // 帧间隔模式	1-速度自适应（超过速度上限取0间隔，低于速度下限取2间隔，中间取1间隔）2-由联动参数决定
	int                      arnAdaptiveSpeed[2];                  // 速度自适应下限和上限
	CFG_ALARM_MSG_HANDLE     stuEventHandler;	                   // 交通抓拍联动参数
	BOOL                     abSchemeRange;                        // TRUE:方案针对相机,以车到0的值为准;FALSE:方案针对车道。不可以修改此字段数据, 只内部使用
	BYTE		             bReserved[756];                       // 保留字节
}CFG_TRAFFICSNAPSHOT_INFO;

typedef struct tagCFG_TRAFFICSNAPSHOT_NEW_INFO
{
	int							nCount;								// 有效成员个数
	CFG_TRAFFICSNAPSHOT_INFO	stInfo[8];							// 交通抓拍表数组

}CFG_TRAFFICSNAPSHOT_NEW_INFO;

// 普通配置 (CFG_CMD_DEV_GENERRAL) General 
typedef struct tagCFG_DEV_DISPOSITION_INFO
{
	int                      nLocalNo;              // 本机编号，主要用于遥控器区分不同设备	0~998
	char                     szMachineName[256];    // 机器名称或编号
	char                     szMachineAddress[256]; // 机器部署地点即道路编码
	char                     szMachineGroup[256];   // 机器分组或叫设备所属单位	默认为空，用户可以将不同的设备编为一组，便于管理，可重复。
	char					 szMachineID[64];		// 机器编号, 联网平台内唯一
	
	BYTE		             bReserved[960];        // 保留字节
}CFG_DEV_DISPOSITION_INFO;

typedef struct tagOVERSPEED_INFO
{
	int                      nSpeedingPercentage[2];                        // 超速百分比区间要求区间不能重叠。有效值为0,正数,-1，-1表示无穷大值
	                                                                        // 如果是欠速：要求区间不能重叠。有效值为0,正数,-1，-1表示无穷大值，欠速百分比的计算方式：限低速-实际车速/限低速
	char                     szCode[MAX_VIOLATIONCODE];                     // 违章代码
	char                     szDescription[MAX_VIOLATIONCODE_DESCRIPT];     // 违章描述

}CFG_OVERSPEED_INFO;

typedef CFG_OVERSPEED_INFO CFG_OVERSPEED_HIGHWAY_INFO;
typedef CFG_OVERSPEED_INFO CFG_UNDERSPEED_INFO;

//ViolationCode 违章代码配置表
typedef struct tagVIOLATIONCODE_INFO
{
    char                szRetrograde[MAX_VIOLATIONCODE];			// 逆行
	char                szRetrogradeDesc[MAX_VIOLATIONCODE_DESCRIPT];              // 违章描述信息

	char				szRetrogradeHighway[MAX_VIOLATIONCODE];		// 逆行-高速公路
	char				szRetrogradeHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];		// 违章描述信息

	char                szRunRedLight[MAX_VIOLATIONCODE];			// 闯红灯
	char                szRunRedLightDesc[MAX_VIOLATIONCODE_DESCRIPT];			   // 违章描述信息

	char                szCrossLane[MAX_VIOLATIONCODE];				// 违章变道
	char                szCrossLaneDesc[MAX_VIOLATIONCODE_DESCRIPT];			   // 违章描述信息

	char                szTurnLeft[MAX_VIOLATIONCODE];				// 违章左转
	char                szTurnLeftDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // 违章描述信息

	char                szTurnRight[MAX_VIOLATIONCODE];				// 违章右转
	char                szTurnRightDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息

	char                szU_Turn[MAX_VIOLATIONCODE];				// 违章掉头
	char                szU_TurnDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // 违章描述信息

	char                szJam[MAX_VIOLATIONCODE];					// 交通拥堵
	char                szJamDesc[MAX_VIOLATIONCODE_DESCRIPT];					   // 违章描述信息

	char                szParking[MAX_VIOLATIONCODE];				// 违章停车
	char                szParkingDesc[MAX_VIOLATIONCODE_DESCRIPT];			      	// 违章描述信息

	// 超速 和 超速比例 只需且必须有一个配置
	char                szOverSpeed[MAX_VIOLATIONCODE];				// 超速
	char                szOverSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息
	CFG_OVERSPEED_INFO  stOverSpeedConfig[5];                       // 超速比例代码

	// 超速(高速公路) 和 超速比例(高速公路) 只需且必须有一个配置
	char                szOverSpeedHighway[MAX_VIOLATIONCODE];		// 超速-高速公路
	char                szOverSpeedHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];	      	// 超速-违章描述信息
	CFG_OVERSPEED_HIGHWAY_INFO stOverSpeedHighwayConfig[5];         // 超速比例代码

	// 欠速 和 欠速比例 只需且必须有一个配置
	char                szUnderSpeed[MAX_VIOLATIONCODE];	        // 欠速
	char                szUnderSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];	            // 违章描述信息
	CFG_UNDERSPEED_INFO stUnderSpeedConfig[5];                            // 欠速配置信息	是一个数组，不同的欠速比违章代码不同，为空表示违章代码不区分超速比

	char                szOverLine[MAX_VIOLATIONCODE];				// 压线
	char                szOverLineDesc[MAX_VIOLATIONCODE_DESCRIPT];			    	// 违章描述信息

	char                szOverYellowLine[MAX_VIOLATIONCODE];	    // 压黄线
	char                szOverYellowLineDesc[MAX_VIOLATIONCODE_DESCRIPT];	    	// 违章描述信息

	char                szYellowInRoute[MAX_VIOLATIONCODE];			// 黄牌占道
	char                szYellowInRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];			// 违章描述信息

	char                szWrongRoute[MAX_VIOLATIONCODE];			// 不按车道行驶
	char                szWrongRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息

	char                szDrivingOnShoulder[MAX_VIOLATIONCODE];		// 路肩行驶
	char                szDrivingOnShoulderDesc[MAX_VIOLATIONCODE_DESCRIPT];		// 违章描述信息

	char                szPassing[MAX_VIOLATIONCODE];               // 正常行驶
	char                szPassingDesc[MAX_VIOLATIONCODE_DESCRIPT];               	// 违章描述信息

	char                szNoPassing[MAX_VIOLATIONCODE];             // 禁止行驶
	char                szNoPassingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

	char                szFakePlate[MAX_VIOLATIONCODE];              // 套牌
	char                szFakePlateDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息
	
	char                szParkingSpaceParking[MAX_VIOLATIONCODE];              // 车位有车
	char                szParkingSpaceParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

	char                szParkingSpaceNoParking[MAX_VIOLATIONCODE];              // 车位无车
	char                szParkingSpaceNoParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

	BYTE		        bReserved[864];
}VIOLATIONCODE_INFO;
// CFG_CMD_TRAFFICGLOBAL 交通全局配置配置表
typedef struct tagCFG_TRAFFICGLOBAL_INFO
{
	VIOLATIONCODE_INFO   stViolationCode;       // 违章代码配置表
	BYTE		        bReserved[1024];
}CFG_TRAFFICGLOBAL_INFO;

// CFG_CMD_VIDEOENCODEROI 视频编码ROI(Region of Intrest)配置
#define DH_MAX_QUALITY_REGION_NUM 8
typedef struct tagCFG_VIDEOENCODEROI_INFO
{
	int      nRegionNum;                               // 优化区域个数
	CFG_RECT stRegions[DH_MAX_QUALITY_REGION_NUM];     // 优化区域 支持多个优化区域，使用相对坐标体系，取值均为0~8191
	BYTE     byQuality;        // 图像质量 取值1~6，值越大，图像质量越好
	bool     bMain;            // 优化主码流视频编码
	bool     bExtra1;          // 优化辅码流1视频编码	
	bool     bExtra2;          // 优化辅码流2视频编码
	bool     bExtra3;          // 优化辅码流3视频编码
	bool     bSnapshot;        // 优化抓图编码
	BYTE     byReserved2[2];   // 对齐
}CFG_VIDEOENCODEROI_INFO;

// ATM取款超时配置
typedef struct tagCFG_ATMMOTION_INFO
{
	int nTimeLimit;            // 取款超时时间,单位:秒
}CFG_ATMMOTION_INFO;

typedef struct tagCFG_SNAPSOURCE_INFO_SINGLE_CHANNEL
{
	bool		bEnable;			// 使能
	BYTE		bReserved1[3];		// 保留字段，对齐
	BYTE		bDevice[64];		// 设备名
	DWORD		dwChannel;			// 视频通道号
	DWORD		dwLinkVideoChannel; // 抓图通道对应的视频通道号
	BYTE		bReserved[512];		// 保留字段
}SNAPSOURCE_INFO_SINGLE_CHANNEL;

typedef struct tagCFG_SNAPSOURCE_INFO
{
	DWORD dwCount;												//要配置的通道的个数
	SNAPSOURCE_INFO_SINGLE_CHANNEL singleChnSanpInfo[MAX_VIDEO_CHANNEL_NUM];	//SNAPSOURCE_INFO_SINGLE_CHANNEL数组的地址
}CFG_SNAPSOURCE_INFO;

typedef struct tagDEVICE_STATUS
{
	char	szDeviceName[MAX_REMOTEDEVICENAME_LEN];	//远程设备的名字
	BYTE	bDeviceStatus;							//远程设备的状态 0：断线 1：在线
	BYTE	bReserved[63];							//保留字节
}DEVICE_STATUS;

typedef struct tagCFG_REMOTE_DEVICE_STATUS
{
	DEVICE_STATUS devStatus[MAX_REMOTE_DEV_NUM]; //设备状态
	DWORD		  dwDevCount;					 //设备数量
	BYTE		  bReserved[1024];				 //保留字节
}CFG_REMOTE_DEVICE_STATUS;

//-----------------------------音频分析相关配置------------------------------
// 事件类型 EVENT_IVS_AUDIO_ABNORMALDETECTION (声音异常检测事件)对应规则配置
typedef struct tagCFG_IVS_AUDIO_ABNORMALDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int                 nDecibel;                                               // 声音强度，单位 db
	int                 nFrequency;                                             // 声音频率, 单位 Hz
	int                 nMinDuration;                                           // 最短持续时间, 单位 s
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
}CFG_IVS_AUDIO_ABNORMALDETECTION_INFO;

typedef struct tagCFG_CAP_AUDIO_ANALYSE_INFO
{
	int                 nSupportedRuleNum;                                      // 支持的规则类型数
	DWORD               dwSupportedRules[MAX_RULE_LIST_SIZE];                   // 具体支持的规则类型
}CFG_CAP_AUDIO_ANALYSE_INFO;

//-------------------------IPS && SVR------------------------------

// 设备状态信息
typedef struct tagCFG_DEVICESTATUS_INFO
{
	int                 nPowerNum;                               // 电源个数
	BYTE                byPowerStatus[MAX_POWER_NUM];            // 电源状态，1:正常 2:异常 3:未知
	int                 nCPUNum;                                 // CPU个数
	int                 nCPUTemperature[MAX_CPU_NUM];            // CPU温度
	int                 nFanNum;                                 // 风扇个数
	int                 nRotatoSpeed[MAX_FUN_NUM];               // 风扇转速
}CFG_DEVICESTATUS_INFO;

// 扩展柜信息
typedef struct tagCFG_HARDDISK_INFO 
{
	int                     nChannel;                        // 通道号
	int                     nCapacity;                       // 硬盘容量 
	BYTE                    byStatus;                        // 硬盘状态，0:unknown 1:running 2:fail 3.spare热备
															 // 4.sync同步 5.faulty失效 6.rebuilding重建 7.remove移除 8.sleep休眠
	BYTE                    byUsedStatus;                    // 使用状态，1.空闲 2.在用 3.未知
    BYTE                    byHotBack;                       // 是否是热备盘，0:热备盘 1:非热备盘
	BYTE                    byReserved;                      // 字节对齐
	char                    szRaidName[MAX_NAME_LEN];        // 所在Raid(磁盘组)的名称	"RaidName" : "Raid0",
															 // 所在Raid(磁盘组)的名称。如不属于任何Raid，则字段为null。
															 // 比如热备盘，属于全局热备盘的，则传null。
	char                    szType[32];                      // 硬盘型号
	int                     nTank;                           // 扩展柜, 0:主机;1:扩展柜1; 2:扩展柜2	……
	int						nRemainSpace;					 // 剩余容量，单位M
}CFG_HARDDISK_INFO;

typedef struct tagCFG_HARDDISKTANK_INFO
{
	char                    szTankName[MAX_NAME_LEN];           // 存储柜名称
	int                     nHardDiskNum;                       // 硬盘个数
	CFG_HARDDISK_INFO       stuHarddiskInfo[MAX_HARDDISK_NUM];  // 硬盘信息
}CFG_HARDDISKTANK_INFO;

typedef struct tagCFG_HARDISKTANKGROUP_INFO
{
	int                      nTankNum;                       // 硬盘存储柜个数
	CFG_HARDDISKTANK_INFO    stuHarddisktank[MAX_TANK_NUM];  // 硬盘存储柜数组
}CFG_HARDISKTANKGROUP_INFO;

// Raid组信息
typedef struct tagCFG_RAID_INFO
{
	char                    szRaidName[MAX_NAME_LEN];         // Raid名称
	BYTE                    byType;                           // 类型 1:Jbob, 2:Raid0, 3:Raid1, 4:Raid5
	BYTE                    byStatus;                         // 状态  0:unknown, 1:active, 2:degraded, 3:inactive, 4: Resyncing
															  // 5.Clean 6.Unknow 7.Recovering 8.Reshaping 9.Checking 10.NotStarted
	BYTE                    byStatusCount;                    // 状态数量, 状态数>=1时, 用byStatusGroup表示状态
	BYTE                    byReserved;						  // 字节对齐
	int                     nMember[MAX_CHAN_NUM];            // 组成磁盘通道
	int                     nDiskNUM;                         // 磁盘个数
	int                     nCapacity;                        // 容量
	int                     nTank;                            // 扩展柜
	int						nRemainSpace;					  // 剩余容量，单位M
	BYTE					byStatusGroup[MAX_STATUS_NUM];	  // 状态数组, 参数值同byStatus
}CFG_RAID_INFO;

typedef struct tagCFG_RAIDGROUP_INFO
{
	int                     nRaidNum;                         // Raid个数
	CFG_RAID_INFO           stuRaidInfo[MAX_RAID_NUM];        // Raid组信息
}CFG_RAIDGROUP_INFO;

// 存储池组信息
typedef struct tagCFG_STORAGEPOOL_INFO
{
	char                   szName[MAX_NAME_LEN];               // 存储池名称
	int                    nMemberNum;                         // 设备数量
	char                   szMember[MAX_DEV_NUM][MAX_NAME_LEN];// 组成设备
	int                    nUsed;                              // 已用容量
    int                    nCapacity;                          // 总容量
    int                    nStatus;                            // 状态	0:unknown 1:active 2:degraded 3:inactive
    int                    nTank;                              // 扩展柜	0:主机, 1:扩展柜1, 2:扩展柜2 ……
}CFG_STORAGEPOOL_INFO;

typedef struct tagCFG_STORAGEPOOLGROUP_INFO
{
	int                     nStroagePoolNum;                           // 存储池个数
	CFG_STORAGEPOOL_INFO    stuStoragePoolInfo[MAX_STORAGEPOOL_NUM];   // 存储池信息
}CFG_STORAGEPOOLGROUP_INFO;

// 文件系统组信息
typedef struct tagCFG_STORAGEPOSITION_INFO
{
	char                   szName[MAX_NAME_LEN];               // 存储位置名称	
    char                   szStoragePoolName[MAX_NAME_LEN];    // 存储池名称	
    int                    nUsedCapacity;                      // 已用容量,单位G	
    int                    nTotalCapacity;                     // 容量,单位G	
	BYTE                   byStatus;                           // 状态 0.未知 1.正常 2.配置异常 3.挂载异常
    BYTE                   byReserved[3];                      // 字节对齐
}CFG_STORAGEPOSITION_INFO;

typedef struct tafCFG_STORAGEPOSITIONGROUP_INFO
{
	int                      nStoragePositionNum;                         // 存储信息个数
	CFG_STORAGEPOSITION_INFO stuStoragePositionInfo[MAX_STRORAGEPOS_NUM]; // 文件系统组信息      
}CFG_STORAGEPOSITIONGROUP_INFO;

// 前端设备组信息
typedef struct tagCFG_VIDEOINDEV_INFO
{
	char                   szDevName[MAX_NAME_LEN];             // 前端设备名称	
    char                   szDevID[MAX_NAME_LEN];               // 设备ID	
    char                   szDevType[MAX_NAME_LEN];             // 设备类型
    int                    nTotalChan;                          // 总通道数
	int                    nTotalAlarmChan;                     // 报警通道总数
    char                   szIP[MAX_ADDRESS_LEN];               // 设备IP
	BYTE                   byStatus;                            // 状态 0:未知 1:在线 2:离线
	BYTE                   byReserved[3];                       // 字节对齐
}CFG_VIDEOINDEV_INFO;

typedef struct tafCFG_VIDEOINDEVGROUP_INFO
{
	int                    nVideoDevNum;                              // 前端设备个数
	CFG_VIDEOINDEV_INFO    stuVideoInDevInfo[MAX_VIDEODEV_NUM];       // 前端设备组信息      
}CFG_VIDEOINDEVGROUP_INFO;

// 通道录像组状态
typedef struct tagCFG_DEVRECORD_INFO
{
	char                   szDevName[MAX_NAME_LEN];               // 设备名称
	char                   szIP[MAX_ADDRESS_LEN];                 // 设备IP	
	char                   szChannel[MAX_NAME_LEN];               // 通道号
    char                   szChannelName[MAX_NAME_LEN];           // 通道名称	
    char                   szStoragePosition[MAX_NAME_LEN];       // 存储位置信息
	BYTE                   byStatus;                              // 状态 0:未知 1:录像 2:停止
	BYTE                   byReserved[3];                         // 字节对齐
}CFG_DEVRECORD_INFO;

typedef struct tagCFG_DEVRECORDGROUP_INFO
{
	int                    nChannelNum;                          // 通道个数
	CFG_DEVRECORD_INFO     stuDevRecordInfo[MAX_CHAN_NUM];       // 通道录像状态信息
}CFG_DEVRECORDGROUP_INFO;

// 服务状态
typedef struct tagCFG_IPSERVER_STATUS
{
	int                    nSupportedServerNum;                  // 提供的服务个数
	char                   szSupportServer[MAX_SEVER_NUM][MAX_NAME_LEN];              // 提供的服务名称 Svr Svrd(SVR守护服务) DataBase DataBased(DataBase守护服务) NtpServer NtpServerd(NtpServer守护服务) DahuaII DahuaIId(DahuaII守护服务) Samba Nfs Ftp iScsi 
	int                    nSvrSuppSubServerNum;                                      // Svr提供的子服务信息个数
	char                   szSvrSuppSubServer[MAX_SEVER_NUM][MAX_NAME_LEN];           // Svr提供的子服务信息 CMS DMS	MTS	SS RMS DBR
	BYTE                   byCMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byDMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byMTS;                                // 0:未知 1:运行 2:未运行
	BYTE                   bySS;                                 // 0:未知 1:运行 2:未运行
	BYTE                   byRMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byDBR;                                // 0:未知 1:运行 2:未运行
	BYTE                   bySvrd;                               // 0:未知 1:运行 2:未运行
	BYTE                   byDataBase;                           // 0:未知 1:运行 2:未运行
	BYTE                   byDataBased;                          // 0:未知 1:运行 2:未运行
	BYTE                   byNtpServer;                          // 0:未知 1:运行 2:未运行
	BYTE                   byNtpServerd;                         // 0:未知 1:运行 2:未运行
	BYTE                   byDahuaII;                            // 0:未知 1:运行 2:未运行
	BYTE                   byDahuaIId;                           // 0:未知 1:运行 2:未运行
	BYTE                   bySAMBA;                              // 0:未知 1:运行 2:未运行
	BYTE                   byNFS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byFTP;                                // 0:未知 1:运行 2:未运行
	BYTE                   byISCSI;                              // 0:未知 1:运行 2:未运行
	BYTE                   byReserved[3];                        // 字节对齐
}CFG_IPSERVER_STATUS;

//---------------------------视频矩阵-----------------------------------
#define MAX_SUPPORT_SPLIT_MODE_NUM    16             // 支持的画面分割的能力最大数
#define MAX_MATRIX_PLAN               4              // 最大矩阵方案数
#define MAX_TOUR_MODE                 16             // 最大轮巡队列数

typedef enum MATRIX_VIEW_SPLITMODE
{
	MATRIX_VIEW_SPLIT1 = 0,
	MATRIX_VIEW_SPLIT2,	
	MATRIX_VIEW_SPLIT4,
	MATRIX_VIEW_SPLIT8,
	MATRIX_VIEW_SPLIT9,	
	MATRIX_VIEW_SPLIT16,
	MATRIX_VIEW_SPLITPIP,
	MATRIX_VIEW_SPLIT6,
	MATRIX_VIEW_SPLIT12,
	MATRIX_VIEW_SPLIT25,
	MATRIX_VIEW_SPLIT36,
	MATRIX_VIEW_SPLIT_NR,
};

// 轮巡模式
typedef struct tagCFG_TOUR_MODE
{
	int               nViewMode;                                    // 画面分割模式,参考枚举类型MATRIX_VIEW_SPLITMODE
	unsigned int      dwViewSplitMask;                     // 表示ViewMode指定模式下,使能的几个分隔方法,使用掩码表达方式
													       // 例如:0x00000007:表示模式3(SPLIT8)的分隔1,2,3使能开启,其他未使能,0x0000000F表示分隔1,2,3,4使能
}CFG_TOUR_MODE;

// SPOT视频矩阵方案
typedef struct tagCFG_VIDEO_MATRIX_PLAN
{
	BOOL            bEnable;                                          // 矩阵配置方案使能
	int             nTourPeriod;                                      // 矩阵轮巡间隔,单位秒,>=1
	int             nTourModeNum;                                     // 轮巡队列个数
	CFG_TOUR_MODE   stuTourMode[MAX_TOUR_MODE];                       // 轮巡队列
}CFG_VIDEO_MATRIX_PLAN;

// SPOT矩阵配置
typedef struct tagCFG_VIDEO_MATRIX
{
	int                         nSupportSplitModeNumber;         // 支持的画面分割的能力数
	BYTE                        bySupportSplitMode[MAX_SUPPORT_SPLIT_MODE_NUM];          // 支持的画面分割的能力
	int                         nMatrixPlanNumber;               // 矩阵方案数
	CFG_VIDEO_MATRIX_PLAN       stuMatrixPlan[MAX_MATRIX_PLAN];                // 矩阵方案
}CFG_VIDEO_MATRIX;

///////////////////////////////////视频诊断配置///////////////////////////////////////
// 视频抖动检测
typedef struct tagCFG_VIDEO_DITHER_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_DITHER_DETECTION;
// 条纹检测
typedef struct tagCFG_VIDEO_STRIATION_DETECTION 
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
	BYTE							byReserved1[2];								// 字节对齐
	BOOL							bUVDetection;								// UV分量是否检测					
}CFG_VIDEO_STRIATION_DETECTION;
// 视频丢失检测
typedef struct tagCFG_VIDEO_LOSS_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
}CFG_VIDEO_LOSS_DETECTION;
// 视频遮挡检测
typedef struct tagCFG_VIDEO_COVER_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_COVER_DETECTION;
// 画面冻结检测
typedef struct tagCFG_VIDEO_FROZEN_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
}CFG_VIDEO_FROZEN_DETECTION;
// 亮度异常检测
typedef struct tagCFG_VIDEO_BRIGHTNESS_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							bylowerThrehold1;							// 预警阀值 取值1-100
	BYTE							bylowerThrehold2;							// 报警阀值 取值1-100
	BYTE							byUpperThrehold1;							// 预警阀值 取值1-100
	BYTE							byUpperThrehold2;							// 报警阀值 取值1-100
}CFG_VIDEO_BRIGHTNESS_DETECTION;
// 对比度异常检测
typedef struct tagCFG_VIDEO_CONTRAST_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							bylowerThrehold1;							// 预警阀值 取值1-100
	BYTE							bylowerThrehold2;							// 报警阀值 取值1-100
	BYTE							byUpperThrehold1;							// 预警阀值 取值1-100
	BYTE							byUpperThrehold2;							// 报警阀值 取值1-100
}CFG_VIDEO_CONTRAST_DETECTION;
// 偏色检测
typedef struct tagCFG_VIDEO_UNBALANCE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_UNBALANCE_DETECTION;
// 噪声检测
typedef struct tagCFG_VIDEO_NOISE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_NOISE_DETECTION;
// 模糊检测
typedef struct tagCFG_VIDEO_BLUR_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_BLUR_DETECTION;
// 场景变化检测
typedef struct tagCFG_VIDEO_SCENECHANGE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_SCENECHANGE_DETECTION;
typedef struct tagCFG_VIDEO_DIAGNOSIS_PROFILE
{
	char							szName[MAX_PATH];							// 名称

	CFG_VIDEO_DITHER_DETECTION*		pstDither;									// 视频抖动检测
	CFG_VIDEO_STRIATION_DETECTION*	pstStriation;								// 视频条纹检测
	CFG_VIDEO_LOSS_DETECTION*		pstLoss;									// 视频丢失检测
	CFG_VIDEO_COVER_DETECTION*		pstCover;									// 视频遮挡检测
	CFG_VIDEO_FROZEN_DETECTION*		pstFrozen;									// 视频冻结检测
	CFG_VIDEO_BRIGHTNESS_DETECTION*	pstBrightness;								// 视频亮度异常检测
	CFG_VIDEO_CONTRAST_DETECTION*	pstContrast;								// 对比度异常检测
	CFG_VIDEO_UNBALANCE_DETECTION*	pstUnbalance;								// 偏色异常检测
	CFG_VIDEO_NOISE_DETECTION*		pstNoise;									// 噪声检测
	CFG_VIDEO_BLUR_DETECTION*		pstBlur;									// 模糊检测
	CFG_VIDEO_SCENECHANGE_DETECTION* pstSceneChange;							// 场景变化检测
}CFG_VIDEO_DIAGNOSIS_PROFILE;
// 视频诊断参数表(CFG_CMD_VIDEODIAGNOSIS_PROFILE)，支持多种参数表，用表名称来索引   调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_PROFILE
{
	int								nTotalProfileNum;							// 调用者分配参数表数 根据能力集获取
	int								nReturnProfileNum;							// 返回的实际参数表数
	CFG_VIDEO_DIAGNOSIS_PROFILE*	pstProfiles;								// 调用者分配nProfileCount个VIDEO_DIAGNOSIS_PROFILE
}CFG_VIDEODIAGNOSIS_PROFILE;

///// 视频诊断任务
enum CFG_EM_STREAM_TYPE
{
	CFG_EM_STREAM_ERR,                  // 其它
	CFG_EM_STREAM_MAIN,					// "Main"-主码流
	CFG_EM_STREAM_EXTRA_1,				// "Extra1"-辅码流1
	CFG_EM_STREAM_EXTRA_2,				// "Extra2"-辅码流2
	CFG_EM_STREAM_EXTRA_3,				// "Extra3"-辅码流3
	CFG_EM_STREAM_SNAPSHOT,				// "Snapshot"-抓图码流
	CFG_EM_STREAM_OBJECT,				// "Object"-物体流
};

// 设备详细信息
typedef struct tagCFG_TASK_REMOTEDEVICE
{
	char                            szAddress[MAX_PATH];                        // 设备地址或域名
	unsigned int                    dwPort;                                     // 端口号
	char                            szUserName[MAX_PATH];                       // 用户名
	char                            szPassword[MAX_PATH];                       // 密码明文
	char                            szProtocolType[MAX_PATH];                   // 连接设备的协议类型
	CFG_RemoteDeviceVideoInput      *pVideoInput;                               // 视频输入通道，用户申请nMaxVideoInputs个CFG_RemoteDeviceVideoInput空间
	int				                nMaxVideoInputs;					        // 视频输入通道最大数
	int				                nRetVideoInputs;					        // 返回的视频输入通道数
}CFG_TASK_REMOTEDEVICE;

typedef struct tagCFG_TAST_SOURCES
{
	// 能力
	bool							abDeviceID;                                 // abDeviceID(使用szDeviceID) 和 abRemoteDevice(使用stRemoteDevice) 必须有一个为true，否则Sources是null
	bool							abRemoteDevice;

	char							szDeviceID[MAX_PATH];						// 设备ID
	CFG_TASK_REMOTEDEVICE           stRemoteDevice;                             // 设备详细信息
	int								nVideoChannel;								// 视频通道号
	CFG_EM_STREAM_TYPE				emVideoStream;								// 视频码流类型
	int								nDuration;									// 持续诊断时间
}CFG_TAST_SOURCES;
typedef struct tagCFG_DIAGNOSIS_TASK
{
	char							szTaskName[MAX_PATH];						// 任务名称
	char							szProfileName[MAX_PATH]; 					// 本任务使用的诊断参数表名
	int								nTotalSourceNum;						    // 调用者分配任务数据源的个数  根据能力集获取
	int								nReturnSourceNum;							// 返回实际任务数据源的个数
	CFG_TAST_SOURCES*				pstSources;									// 任务数据源 调用者分配内存nTotalSourceNum个
}CFG_DIAGNOSIS_TASK;
// 视频诊断任务表(CFG_CMD_VIDEODIAGNOSIS_TASK),不同的任务通过名子索引  调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_TASK
{
	int								nTotalTaskNum; 								// 调用者分配任务个数  根据能力集获取
	int								nReturnTaskNum; 							// 返回实际任务个数
	CFG_DIAGNOSIS_TASK*				pstTasks;									// 任务配置 调用者分配内存nTotalTaskNum个
}CFG_VIDEODIAGNOSIS_TASK;

// 视频诊断计划
typedef struct tagPROJECT_TASK
{
	BOOL							bEnable;									// 任务是否使能
	char							szTaskName[MAX_PATH];						// 任务名称
	CFG_TIME_SECTION				stTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	// 任务时间段
}CFG_PROJECT_TASK;
typedef struct tagDIAGNOSIS_PROJECT
{
	char							szProjectName[MAX_PATH];					// 计划名称
	int								nTotalTaskNum;								// 调用者分配任务列表个数  根据能力集获取
	int								nReturnTaskNum;					    		// 返回实际任务列表个数
	CFG_PROJECT_TASK*				pstProjectTasks;								// 任务列表 调用者分配内存nTotalTaskNum个
}CFG_DIAGNOSIS_PROJECT;
// 频诊断计划表(CFG_CMD_VIDEODIAGNOSIS_PROJECT),不同的计划通过名字索引 调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_PROJECT
{
	int								nTotalProjectNum;							// 调用者分配计划个数  根据能力集获取
	int								nReturnProjectNum;							// 返回实际计划个数
	CFG_DIAGNOSIS_PROJECT*			pstProjects;									// 计划配置 调用者分配内存nTotalProjectNum个
}CFG_VIDEODIAGNOSIS_PROJECT;

// 视频诊断全局表(CFG_CMD_VIDEODIAGNOSIS_GLOBAL),每个通道支持一个诊断配置 
typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
{
	BOOL							bEnable;									// 计划是否使能
	BOOL							bApplyNow;									// 配置立即应用	立即应用表示参数表，任务，计划的修改立即生效，否则等到当前正在执行的任务完成后生效。
	char							szProjectName[MAX_PATH];					// 计划名称
}CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL;
typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL
{
	int								nTotalGlobalNum;							// 调用者分配全局配置个数  根据能力集获取
	int								nReturnGlobalNum;							// 返回实际全局配置个数
	CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL	*pstGlobals;									// 视频诊断全局配置 调用者分配内存nGlobalCount个CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
}CFG_VIDEODIAGNOSIS_GLOBAL;

// 视频诊断服务能力集(CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER)
typedef struct tagCFG_VIDEODIAGNOSIS_CAPS_INFO
{
	int								nTypeCount;									// 支持的视频诊断类型 个数
	char						    szSupportedType[MAX_VIDEODIAGNOSIS_DETECT_TYPE][MAX_PATH];// 支持的视频诊断类型
	int								nMaxProfiles;								// 最大参数表个数
	int								nMaxTasks;									// 最大任务个数
	int								nMaxSourcesOfTask;							// 最大单个任务的视频源个数
	int								nMaxProjects;								// 最大方案个数
}CFG_VIDEODIAGNOSIS_CAPS_INFO;

// 获取视频诊断通道数目( CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT )对应结构体
typedef struct tagCFG_VIDEODIAGNOSIS_COLLECT_INFO
{
	int                             nDiagnosisChannels;                                   // 视频诊断通道数目
}CFG_VIDEODIAGNOSIS_COLLECT_INFO;

// 获取视频诊断进行状态( CFG_CMD_VIDEODIAGNOSIS_GETSTATE )对应结构体
typedef struct tagCFG_VIDEODIAGNOSIS_STATE_INFO
{
	BOOL                            bEnable;                                     // 是否使能
	BOOL                            bRunning;                                    // 是否正在运行	使能开启，并且当前有工作任务正在进行，没有错误发生。
	char                            szCurrentProject[MAX_PATH];                  // 当前计划名称
	char                            szCurrentTask[MAX_PATH];                     // 当前任务名称
	char                            szCurrentProfile[MAX_PATH];                  // 当前任务配置参数表名称
	int                             nCurrentSourceCount;                         // 当前任务轮训视频源个数
	int                             nCurrentSourceIndex;                         // 当前任务当前视频源序号	从0开始
	CFG_TIME_SECTION                stCurrentTimeSection;                        // 当前计划时间段
	int                             nTaskCountOfProject;                         // 当前计划总任务数
	int                             nIndexOfCurrentTask;                         // 当前任务序号 从0开始
}CFG_VIDEODIAGNOSIS_STATE_INFO;

// 服务器支持的服务列表
typedef struct tagCFG_DEV_SERVICE_LIST
{
	int                             nServiceNum;                                 // 支持的服务数
	char                            szService[MAX_SERVICE_NUM][MAX_NAME_LEN];    // 服务器支持具体的服务项
}CFG_DEV_SERVICE_LIST;

//获取主从式跟踪器数目
typedef struct tagCFG_MASTERSLAVETRACKER_INFO
{
        int                nStructSize;
	    int                nChannels;	//主从式跟踪器通道数目
}CFG_MASTERSLAVETRACKER_INFO;

// 变倍类型
typedef enum tagCFG_ZOOM_TYPE
{
	ZOOM_TYPE_EXPECTMULTIPLE =0,     // 固定期望倍数变倍
	ZOOM_TYPE_IVSADAPTIVE,           // 根据智能设备输出自适应变倍
	ZOOM_TYPE_MULTIPLEADAPTIVE,      // 自适应变倍
	ZOOM_TYPE_NUM
}CFG_ZOOM_TYPE;

// 跟踪模式
typedef enum tagCFG_TRACKING_MODE
{
    TRACKING_MODE_ALARM=0,        // 报警跟踪
	TRACKING_MODE_MANUALOBJECT,   // 手动选定物体跟踪
	TRACKING_MODE_AUTOOBJECT,     // 自动选定物体跟踪
	TRACKING_MODE_SELECTPOINT,    // 定点跟踪
	TRACKING_MODE_MIX,            // 混合跟踪(以上四种跟踪模式同时支持)
	TRACKING_MODE_SLAVESELF,      // 球机自主控制（主要用于用户对球机控制）
	TRACKING_MODE_NUM
}CFG_TRACKING_MODE;

// 主从式跟踪器全局配置基本结构体
typedef struct tagCFG_MASTERSLAVE_GLOBAL_INFO
{
	int                nStructSize;
	float              fMaxZoom;                    // 最大变倍倍数
	float              fMinZoom;                    // 最小变倍倍数
	float              fExpectMultiple;             // 期望倍数（基准倍数），最小变倍倍数<期望倍数<最大变倍倍数
	float              fPollTrackTime;              // 轮询跟踪时长，单位：秒；>0.0
	float              fPointTrackTime;             // 定点跟踪时长,单位：秒；>0.0在报警跟踪、自动选定物体跟踪、混合跟踪模式下有效
    float              fObjectTrackTime;            // 手动选定物体跟踪时长, 单位：秒；>0.0在报警跟踪、自动选定物体跟踪、混合跟踪模式下有效
	float              fExpectAngleX;               // 期望倍数对应球机角度x(水平)
    float              fExpectAngleY;               // 期望倍数对应球机角度y(垂直)
	CFG_SIZE           stTargetFaceSize;            // 靶面尺寸(单位：毫米), 球机设备参数，与球机有关
	float              fMinFocus;                   // 最小焦距(单位：毫米)
	float              fMaxFocus;                   // 最大焦距(单位：毫米)
	CFG_ZOOM_TYPE      emZoomType;                  // 变倍类型
	CFG_TRACKING_MODE  emTrackingMode;              // 跟踪模式
}CFG_MASTERSLAVE_GLOBAL_INFO;


// 获取主从式设备能力集
typedef struct tagCFG_CAP_MASTERSLAVE_INFO
{
	int                     nStructSize;
	BYTE                    byTrackingMode[TRACKING_MODE_NUM]; // 数组下标表示CFG_TRACKING_MODE枚举相对应模式，1表示支持
}CFG_CAP_MASTERSLAVE_INFO;



// 获取服务器报警联动能力集
typedef struct tagCFG_CAP_EVENTHANDLER_INFO
{
	BOOL				bTimeSectionEnable;                                      // 
	BOOL				bRecordEnable;                                           // 是否支持录像
	BOOL				bAlarmOutEnable;                                         // 是否支持报警输出
	BOOL				bPtzLinkEnable;                                          // 是否支持报警输出
	BOOL				bSnapshotEnable;                                         // 是否支持快照
	BOOL				bMailEnable;                                             // 是否支持发送邮件
	BOOL				bBeepEnable;                                             // 是否支持蜂鸣
	BOOL				bDejitterEnable;                                         // 是否支持去抖动
	BOOL                bTipEnable;                                              // 是否支持本地消息框提示
	BOOL                bMonitorTourEnable;                                      // 是否支持轮询联动配置
}CFG_CAP_EVENTHANDLER_INFO;

//----------------------------------视频输入配置------------------------------------------
#define DH_MAX_INMETERING_REGION_NUM 8

typedef struct tagVIDEO_INMETERING_INFO_CHANNEL
{
	// 能力
	bool            bRegion;
	bool            bMode;
	BYTE			bReserved1[2];					         // 保留字段1
	
	int				nRegionNum;                                 // 测光区域个数
	CFG_RECT    	stuRegions[DH_MAX_INMETERING_REGION_NUM];   // 测光区域, 局部测光使用，支持多个测光区域，使用相对坐标体系，取值均为0~8191
	BYTE  			byMode;				                     // 测光模式,0:平均测光,1:局部测光
	BYTE  			bReserved2[3];				             // 保留字段2
	BYTE			bReserved3[32];					         // 保留字段3
}VIDEO_INMETERING_INFO_CHANNEL;

// 测光配置(CFG_CMD_VIDEO_INMETERING)是一个数组，每个视频输入通道一个配置
typedef struct tagCFG_VIDEO_INMETERING_INFO
{
	int				nChannelNum; // 通道数
	VIDEO_INMETERING_INFO_CHANNEL	stuMeteringMode[MAX_VIDEO_CHANNEL_NUM]; // 每个通道的测光信息，下标对应通道号
}CFG_VIDEO_INMETERING_INFO;

// 视频输入能力集(CFG_CAP_CMD_VIDEOINPUT)配置
typedef struct tagCFG_CAP_VIDEOINPUT_INFO
{
	int				nMeteringRegionCount;                   // 最大测光区域个数
	BOOL            bFishEye;                               // 是否支持鱼眼
	BOOL			bElectricFocus;							// 是否支持电动调焦
	DWORD			dwExposureMode;							// 支持的自动曝光模式掩码  从低位到高位依次表示，0-自动曝光，1-低噪声（增益）优先，2-弱拖影（快门）优先， 3-50HZ防闪烁，4-60HZ防闪烁
	int             nWideDynamicRange;						// 是否支持宽动态 0-不支持，1-支持数字宽动态
	int			    nGlareInhibition;						// 是否支持强光抑制 0-不支持，1-支持
}CFG_CAP_VIDEOINPUT_INFO;

// 流量统计报警信息配置
typedef struct tagCFG_TRAFFIC_FLOWSTAT_ALARM_INFO
{
	bool                            bEnable;                              // 是否使能
	int                             nPeriod;                              // 统计周期，单位：分钟
	int                             nLimit;                               // 统计周期内车辆数上下限，单位：辆
	int                             nRestore;                             // 统计周期内报警恢复车辆数，单位：辆 
    int                             nDelay;                               // 检测到报警发生到开始上报的时间, 单位:秒,范围1~65535
	int                             nInterval;                            // 报警间隔时间, 单位:秒, 范围1~65535
	int                             nReportTimes;                         // 上报次数,1~255
	CFG_TIME_SECTION                stCurrentTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX]; // 当前计划时间段
}CFG_TRAFFIC_FLOWSTAT_ALARM_INFO;

typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO_CHNL
{
	// 能力
	bool	                		 abEnable;

	bool			                 bEnable;								// 是否使能
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmUpperInfo;                     // 报警上线参数
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmLowInfo;                       // 报警下线参数
    int                              nDetectRegionPoint;                    // 检测区顶点数
    CFG_POLYGON                      stuDetectRegion[MAX_POLYGON_NUM];      // 检测区域
	char                             szName[MAX_NAME_LEN];                  // 当前车道规则名称，不同规则不能重名
}CFG_TRAFFIC_FLOWSTAT_INFO_LANE;

// 交通流量统计配置(CFG_CMD_TRAFFIC_FLOWSTAT)
typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO
{
	// 能力
	bool							abPeriod;
	BYTE							bReserved1[3];						        // 保留字段1

	int								nPeriod;									// 统计周期，单位分钟
	int								nLaneNum;									// 车道数
	CFG_TRAFFIC_FLOWSTAT_INFO_LANE	stuTrafficFlowstat[MAX_LANE_NUM];			// 每个车道的流量配置，下标对应车道号
}CFG_TRAFFIC_FLOWSTAT_INFO;

//-----------------------------------视频输入前端选项-------------------------------------------

// 视频输入夜晚特殊配置选项，在晚上光线较暗时自动切换到夜晚的配置参数
typedef struct tagCFG_VIDEO_IN_NIGHT_OPTIONS
{
	BYTE				bySwitchMode;			// 0-不切换，总是使用白天配置；1-根据亮度切换；2-根据时间切换；3-不切换，总是使用夜晚配置；4-使用普通配置； 
	BYTE				byBrightnessThreshold ;	// 亮度阈值 0~100	
	BYTE				bySunriseHour;			// 大致日出和日落时间，日落之后日出之前，将采用夜晚特殊的配置。
	BYTE				bySunriseMinute;		// 00:00:00 ~ 23:59:59
	BYTE				bySunriseSecond;
	BYTE				bySunsetHour;
	BYTE				bySunsetMinute;
	BYTE				bySunsetSecond;  
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance ;		// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					// 0~100, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	bool				bGainAuto;				// 自动增益
	bool				bIrisAuto;				// 自动光圈
	float               fExternalSyncPhase;     // 外同步的相位设置 0~360
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°
	bool				bMirror;				// 镜像
	BYTE                byWideDynamicRange;     // 宽动态值 0-关闭，1~100-为真实范围值
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域
	BYTE				reserved[76];			// 保留
} CFG_VIDEO_IN_NIGHT_OPTIONS;

typedef struct tagCFG_VIDEO_IN_NORMAL_OPTIONS
{
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance ;		// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					// 0~100, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	bool				bGainAuto;				// 自动增益
	bool				bIrisAuto;				// 自动光圈
	float               fExternalSyncPhase;     // 外同步的相位设置 0~360
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°
	bool				bMirror;				// 镜像
	BYTE                byWideDynamicRange;     // 宽动态值 0-关闭，1~100-为真实范围值
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域
	BYTE				reserved[76];			// 保留
}CFG_VIDEO_IN_NORMAL_OPTIONS;



// 闪光灯配置
typedef struct tagCFG_FLASH_CONTROL
{
	BYTE				byMode;					// 工作模式，0-禁止闪光，1-始终闪光，2-自动闪光
	BYTE				byValue;				// 工作值, 0-0us, 1-64us, 2-128us, 3-192...15-960us
	BYTE				byPole;					// 触发模式, 0-低电平 1-高电平 2-上升沿 3-下降沿
	BYTE                byPreValue;				// 亮度预设值  区间0~100
	BYTE				byDutyCycle;			// 占空比, 0~100
	BYTE				byFreqMultiple;			// 倍频, 0~10
	BYTE				reserved[122];			// 保留
}CFG_FLASH_CONTROL;

// 抓拍参数特殊配置
typedef struct tagCFG_VIDEO_IN_SNAPSHOT_OPTIONS
{
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance;			// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// 色温等级, 白平衡为"CustomColorTemperature"模式下有效
	bool				bGainAuto;				// 自动增益
	BYTE				byGain;					// 增益调节, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	BYTE				reversed[112];			// 保留
} CFG_VIDEO_IN_SNAPSHOT_OPTIONS;

// 鱼眼镜头配置
typedef struct tagCFG_FISH_EYE
{
    CFG_POLYGON         stuCenterPoint;         // 鱼眼圆心坐标,范围[0,8192]
	unsigned int        nRadius;                // 鱼眼半径大小,范围[0,8192]
	float               fDirection;             // 镜头旋转方向,旋转角度[0,360.0]
	BYTE                byPlaceHolder;          // 镜头安装方式	1顶装，2壁装；3地装,默认1
	BYTE				reversed[31];			// 保留
}CFG_FISH_EYE;
// 视频输入前端选项
typedef struct tagCFG_VIDEO_IN_OPTIONS
{
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byWhiteBalance;			// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// 色温等级, 白平衡为"CustomColorTemperature"模式下有效
	bool				bMirror;				// 镜像
	bool				bFlip;					// 翻转
	bool				bIrisAuto;				// 自动光圈
	bool				bInfraRed;				// 根据环境光自动开启红外补偿灯	
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	bool				bGainAuto;				// 自动增益
	BYTE				byGain;					// 增益调节, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	BYTE				bySignalFormat;			// 信号格式, 0-Inside(内部输入) 1-BT656 2-720p 3-1080p  4-1080i  5-1080sF
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°	
	float               fExternalSyncPhase;		// 外同步的相位设置 0~360	
	BYTE                byExternalSync;			// 外部同步信号输入,0-内部同步 1-外部同步
	BYTE				reserved0;				// 保留
	BYTE				byDoubleExposure;		// 双快门, 0-不启用，1-双快门全帧率，即图像和视频只有快门参数不同，2-双快门半帧率，即图像和视频快门及白平衡参数均不同
	BYTE                byWideDynamicRange;     // 宽动态值
	CFG_VIDEO_IN_NIGHT_OPTIONS stuNightOptions;	// 夜晚参数
	CFG_FLASH_CONTROL	stuFlash;				// 闪光灯配置
	CFG_VIDEO_IN_SNAPSHOT_OPTIONS stuSnapshot;	// 抓拍参数, 双快门时有效
	CFG_FISH_EYE        stuFishEye;             // 鱼眼镜头
	BYTE                reserved[29];           // 保留
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先,4-手动
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域            
	CFG_VIDEO_IN_NORMAL_OPTIONS stuNormalOptions;//普通参数
} CFG_VIDEO_IN_OPTIONS;

// RTSP输入参数和输出参数配置结构体
typedef struct tagCFG_MULTICAST_INFO
{
	int  nStructSize;
	bool abStreamType;
	BYTE byReserved[3];
	BOOL bEnable;      // 是否使能
	char szMulticastAddr[MAX_ADDRESS_LEN]; //组播地址
	int  nPort;        //组播端口
	char szLocalAddr[MAX_ADDRESS_LEN];   //单播地址，用于组播指定详细网卡
	int  nChannelID;   // 通道号
	int  nStreamType;  // 码流类型 0-主码流, 1-辅码流1,2-辅码流2,3-辅码流3
}CFG_MULTICAST_INFO;

typedef struct tagCFG_MULTICASTS_INFO
{
	int nStructSize;
	CFG_MULTICAST_INFO stuMultiInfo[MAX_CHAN_NUM]; //最大组播配置
	int nCount;                                    //有效数组个数
}CFG_MULTICASTS_INFO;

typedef struct tagCFG_RTSP_INFO_IN
{
	int         nStructSize;
	BOOL        bEnable;       // 整个功能是否使能
	int         nPort;         // RTSP服务端口
	int         nRtpStartPort; // RTP起始端口
	int         nRtpEndPort;   // RTP结束端口
	BOOL        bHttpEnable;   // RtspOverHttp使能
	int         nHttpPort;     // RtspOverHttp端口
}CFG_RTSP_INFO_IN;

typedef struct tagCFG_RTSP_INFO_OUT
{
	int         nStructSize;
	BOOL        bEnable;       // 整个功能是否使能
	int         nPort;         // RTSP服务端口
	int         nRtpStartPort; // RTP起始端口
	int         nRtpEndPort;   // RTP结束端口
	BOOL        bHttpEnable;   // RtspOverHttp使能
	int         nHttpPort;     // RtspOverHttp端口
}CFG_RTSP_INFO_OUT;

typedef struct tagCFG_MULTICASTS_INFO_IN
{
	int                  nStructSize;
	CFG_MULTICAST_INFO   *pTSMulticast;   //TS的组播配置
	int                  nTSCount;        //有效TS数组个数
	CFG_MULTICAST_INFO   *pRTPMulticast;  //RTP的组播配置
	int                  nRTPCount;       //有效RTP数组个数
	CFG_MULTICAST_INFO   *pDHIIMulticast; //DHII的组播配置
	int                  nDHIICount;      //有效DHII数组个数
}CFG_MULTICASTS_INFO_IN;

typedef struct tagCFG_MULTICASTS_INFO_OUT
{
	int                  nStructSize;
	CFG_MULTICASTS_INFO  stuTSMulticast;   //TS的组播配置
	CFG_MULTICASTS_INFO  stuRTPMulticast;  //RTP的组播配置
	CFG_MULTICASTS_INFO  stuDHIIMulticast; //DHII的组播配置
}CFG_MULTICASTS_INFO_OUT;

// 时间
typedef struct tagCFG_NET_TIME
{
	int                 nStructSize;
	DWORD				dwYear;					// 年
	DWORD				dwMonth;				// 月
	DWORD				dwDay;					// 日
	DWORD				dwHour;					// 时
	DWORD				dwMinute;				// 分
	DWORD				dwSecond;				// 秒
} CFG_NET_TIME;

typedef struct tagCFG_ACTIVEUSER_INFO
{
	int nStructSize;
	int nUserID;                         //活动用户ID，一般是会话ID
	char szUser[MAX_USERNAME_LEN];       // 用户名
	char szGroupName[MAX_USERNAME_LEN];  // 用户所在组名
	int  nGroupLevel;                    // 用户所在组等级
	char szClientType[MAX_USERNAME_LEN]; // 客户端类型
	char szClientAddr[MAX_ADDRESS_LEN];  // 客户端IP地址
	CFG_NET_TIME  stuLoginTime;              // 用户登入时间
}CFG_ACTIVEUSER_INFO;

typedef struct tagCFG_ACTIVEALLUSER_INFO
{
	int nStructSize;
	int nCount;                                                //有效数组个数
	CFG_ACTIVEUSER_INFO stuActiveUserInfo[MAX_ACTIVEUSER_NUM]; //  最大活动用户列表
}CFG_ACTIVEALLUSER_INFO;

typedef struct tagCFG_NET_TIME_EX
{
	DWORD				dwYear;					// 年
	DWORD				dwMonth;				// 月
	DWORD				dwDay;					// 日
	DWORD				dwHour;					// 时
	DWORD				dwMinute;				// 分
	DWORD				dwSecond;				// 秒
	DWORD               dwMillisecond;          // 毫秒
	DWORD               dwReserved[2];          // 保留字段
} CFG_NET_TIME_EX;

//获取视频统计摘要信息结构体
typedef struct tagCFG_CFG_VIDEOSATA_SUMMARY_INFO
{
	int         nStructSize;
	int         nChannelID;               //统计通道号
	char        szRuleName[MAX_NAME_LEN]; //规则名称
	CFG_NET_TIME_EX stuStatTime;          // 统计时间，转换到UTC
	int         nEnteredTotal;            //进入总计
	int         nEnteredToday;            //今天进入总计
	int         nEnteredMonth;            //本月进入总计
	int         nEnteredYear;             //今年进入总计
	int         nEnteredDaily;            //每日最大进入总计
	int         nExitedTotal;             //出去总计
	int         nExitedToday;             //今天出去总计
	int         nExitedMonth;             //本月出去总计
	int         nExitedYear;              //今年出去总计
	int         nExitedDaily;             //每日最大出去总计
	int         nAvgTotal;                //平均所有保有统计(除去零值)
	int         nAvgToday;                //平均今天保有统计
	int         nAvgMonth;                //平均本月保有统计
	int         nAvgYear;                 //平均今年保有统计         
	int         nMaxTotal;                //最大所有保有统计(除去零值)
	int         nMaxToday;                //最大今天保有统计
	int         nMaxMonth;                //最大本月保有统计
	int         nMaxYear;                 //最大今年保有统计
}CFG_VIDEOSATA_SUMMARY_INFO;

// 单场景跟踪结构体
typedef struct tagCFG_SINGLESCENE
{
	int                 nStructSize;
	int					nSingleAlarmDelay;					//报警延时:1~600秒
	int					nSinglePresetID;					//预置点编号：1~255(-1代表无定义)
}CFG_SINGLESCENE;
// 巡航路径结构体
typedef struct tagCFG_TOURPATH
{
	int                 nStructSize;
	int					nMultiPresetID;						//场景预置点编号
	int					nMultiDuration;						//停留时间30~900秒
}CFG_TOURPATH;
// 多场景跟踪结构体
typedef struct tagCFG_MULTISCENE
{
	int                 nStructSize;
	int					nMultiAlarmDelay;					    //报警延时：1~600秒
	int					nTourPathCount;						    //巡航路径个数
	CFG_TOURPATH	    stuMultiTourPath[MAX_TRACKSCENE_NUM];   //巡航路径
}CFG_MULTISCENE;
// 全场景跟踪结构体
typedef struct tagCFG_FULLSCENE
{
	int                 nStructSize;
	int					nFullAlarmDelay;					//报警延时：1~600秒
	int					nFullPresetID;						//预置点编号,全景跟踪预置点固定为0，用户不可设置
	int					nFullDuration;						//全景跟踪持续时间,0秒: 一直跟踪;1~300:跟踪持续时间
}CFG_FULLSCENE;
// 限位参数结构体
typedef struct tag_CFG_POSITION_LIMIT
{
	int                 nStructSize;
	BOOL				bEnable;							//启用限位参数
	int					nType;								//限位值表述方式：0: 由云台在限位设置操作时保存数据，限位值数据无意义
	                                                        //1：限位值用角度(单位0.1度)表示，用该值设置该场景的限位
	int					nTop;								//上限位值, 0~900:（单位0.1度）
	int					nBottom;							//下限位值：0~900:（单位0.1度）
	int					nLeft;								//左限位值：0~3600:（单位0.1度）
	int					nRight;								//右限位值：0~3600:（单位0.1度）
}CFG_POSITION_LIMIT;
// 场景信息结构体
typedef struct tagCFG_SCENE
{
	int                    nStructSize;
	int					   nScenePresetID;						//场景预置点，1~255，通过预置点编号关联到对应规则上
	char			       szSceneName[MAX_NAME_LEN];		    //场景名
	int					   nSceneDuration;						//跟踪持续时间:0秒: 一直跟踪;1~300:跟踪持续时间
	double		           dSceneMaxZoom;					    //归一化到0~1;为null表示使用全局MaxZoom值
	CFG_POSITION_LIMIT	   stuPositionLimit;                    //限位参数
}CFG_SCENE;
// 智能跟踪场景配置结构体
typedef struct tagCFG_INTELLITRACKSCENE_INFO
{
	int               nStructSize;
	BOOL		      bEnableTrack;				         //启用智能跟踪
	int				  nTrackType;						 //0,报警跟踪；1，手动跟踪
	double			  dMaxZoom;							 //最大跟踪倍率，归一化到0~1，为null表示无限制
	char			  szCategory[MAX_NAME_LEN];		     //当前跟踪类型，"SingleScene"：单场景跟踪；"MultiScene"：多场景跟踪；"FullScene"：全景跟踪
	CFG_SINGLESCENE   stuSingleTrack;					 //单场景跟踪
	CFG_MULTISCENE	  stuMultiTrack;	                 //多场景跟踪
	CFG_FULLSCENE	  stuFullTrack;						 //全景跟踪
	int				  nSceneCount;						 //支持的场景个数
	CFG_SCENE		  stuScene[MAX_TRACKSCENE_NUM];	     //场景列表
}CFG_INTELLITRACKSCENE_INFO;

/************************工作状态配置**********************************/

// 抓拍模式
typedef enum tagCFG_TRAFFIC_SNAP_MODE
{
	TRAFFIC_SNAP_MODE_AUTO = 0,				       // 自动抓拍
	TRAFFIC_SNAP_MODE_COIL,				           // 线圈抓拍
	TRAFFIC_SNAP_MODE_COIL_PICANALYSIS,		       // 线圈抓拍, 图片分析
	TRAFFIC_SNAP_MODE_STREAM,				       // 视频抓拍
	TRAFFIC_SNAP_MODE_STREAM_IDENTIFY,		       // 视频抓拍, 并且识别
	TRAFFIC_SNAP_MODE_MIX_IDENTIFY,		           // 混合抓拍, 并且识别
} CFG_TRAFFIC_SNAP_MODE;

// 设备工作状态信息
typedef struct tagCFG_TRAFFIC_WORKSTATE_INFO
{
	int                     nChannelID;  // 通道号
	CFG_TRAFFIC_SNAP_MODE   emSnapMode;  // 抓拍模式
	int                     nMatchMode;  // 抓拍匹配模式: 0-非实时匹配方式，先报警后抓拍，抓拍帧不是报警帧;  1-实时匹配模式，报警帧和抓拍帧是同一帧 
}CFG_TRAFFIC_WORKSTATE_INFO;

// 获取设备工作状态是否正常(CFG_CAP_CMD_DEVICE_STATE 对应的结构体)
typedef struct tagCFG_TRAFFIC_DEVICE_STATUS
{
	char                 szType[MAX_PATH];          // 设备类型	支持："Radar","Detector","SigDetector"
	char                 szSerialNo[MAX_PATH];      // 设备编号
	char                 szVendor[MAX_PATH];        // 生产厂商
	int                  nWokingState;              // 工作状态	0-故障,1-正常工作
}CFG_TRAFFIC_DEVICE_STATUS;

typedef struct tagCFG_CAP_TRAFFIC_DEVICE_STATUS
{
	int                        nStatus;             // stuStatus 实际个数
	CFG_TRAFFIC_DEVICE_STATUS  stuStatus[MAX_STATUS_NUM];
}CFG_CAP_TRAFFIC_DEVICE_STATUS;

/************************录像盘组配置**********************************/

// 存储组信息
typedef struct tagCFG_STORAGEGROUP_INFO
{
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];   // 存储组名称
	BYTE*                 byDisks;                                 // 物理磁盘序号缓冲区
	int                   nBufSize;                                // 缓冲区byDisks的长度
	int                   nDiskNum;                                // 存储组中的磁盘数
	int                   nGroupIndex;                             // 存储组序号(1~最大硬盘数)
}CFG_STORAGEGROUP_INFO;

// 录像-存储组 对应信息
typedef struct tagCFG_RECORDTOGROUP_INFO
{
	int                   nChannelID;                               // 通道号
	BOOL                  bEnable;                                  // 使能                       
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];    // 存储组名称, 只读
	int                   nGroupIndex;                              // 存储组序号(1~最大盘组, 0则表示无对应盘组)，通过此参数与CFG_STORAGE_GROUP_INFO关联
}CFG_RECORDTOGROUP_INFO;

enum EM_STORAGEPOINT_TYPE
{
       	EM_STORAGE_TIMINGRECORD,        //定时录像存储点类型
		EM_STORAGE_MANUALRECORD,        //手动录像存储点类型
		EM_STORAGE_VIDEODETECTRECORD,   //视频检测录像存储点类型
		EM_STORAGE_ALARMRECORD,         //报警录像存储点类型
		EM_STORAGE_CARDRECORD,          //卡号录像存储点类型
		EM_STORAGE_EVENTRECORD,         // 其他事件录像存储点类型                
		EM_STORAGE_TIMINGSNAPSHOT,      // 定时抓图存储点类型
		EM_STORAGE_MANUALSNAPSHOT,      // 手动抓图存储点类型
		EM_STORAGE_VIDEODETECTSNAPSHOT, // 视频检测抓图存储点类型
		EM_STORAGE_ALARMSNAPSHOT,       // 报警抓图存储点类型
		EM_STORAGE_CARDSNAPSHOT,        // 卡号抓图存储点类型
		EM_STORAGE_EVENTSNAPSHOT,       // 其他事件抓图存储点类型
};
// 存储点配置信息
typedef struct tagCFG_STORAGEPOINT_INFO
{
	DWORD dwSize;
	EM_STORAGEPOINT_TYPE emStoragePointType;// 存储点类型
	char szLocalDir[MAX_DIRECTORY_LEN];     //本地工作目录组名称, 空表示不录到本地
	char szCompressDir[MAX_DIRECTORY_LEN];  //实时压缩存储目录组，空表示不使用实时压缩存储。
	char szRedundantDir[MAX_DIRECTORY_LEN]; //冗余工作目录组名称,空表示没有冗余录像。
	char szRemoteDir[MAX_DIRECTORY_LEN];   //远程工作目录组名称,空表示不录到远程。
	BOOL bAutoSync;                         //远程存储网络故障恢复后，是否自动将本地存储的数据同步到远程存储。
	UINT nAutoSyncRange;                    //从网络恢复的时刻开始，需要往前同步的数据时间范围，小时为单位，0表示同步所有数据。
	BOOL bLocalEmergency;                   //远程目录无法访问时，是否保存到本地目录。
	UINT nCompressBefore;                   //设置将多少天之前的录像文件进行压缩。
}CFG_STORAGEPOINT_INFO;

// 录像存储点映射配置信息
typedef struct tagCFG_RECORDTOSTORAGEPOINT_INFO
{
	int	nStoragePointNum;                                        //存储点数目
	CFG_STORAGEPOINT_INFO stStoragePoints[MAX_STORAGEPOINT_NUM]; // 存储点配置信息
}CFG_RECORDTOSTORAGEPOINT_INFO;

//iscsi直存，元数据服务器配置接口
typedef struct __tagCFG_METADATA_SERVER
{
	DWORD       nStructSize;
	BOOL        bEnable;                              //使能开关
	char        szAddress[MAX_ADDRESS_LEN];           //IP地址或网络名
	DWORD       dwPort;                               //端口号
	char        szUserName[MAX_USERNAME_LEN];         //帐户名  
	char        szPassword[MAX_PASSWORD_LEN];         //密码
	char        szDeviceID[MAX_REMOTEDEVICENAME_LEN]; //为使用元数据服务器的设备统一分配的ID，设备以此ID标识自己
}CFG_METADATA_SERVER;

// 车载货重配置
typedef struct __tagCFG_GOOD_WEIGHT_INFO
{
	DWORD		dwMaxGoodsWeight;					// 最大货重(kg)
	DWORD		dwMinGoodsWeight;					// 最小货重(kg)
	DWORD		dwSelfWeight;						// 自重(kg)
	DWORD		dwStandardWeight;					// 核重(kg)
	DWORD		dwAlarmWeight;						// 报警阈值(kg)
	int			nCheckTime;							// 静止采集时间(s)
} CFG_GOOD_WEIGHT_INFO;

//镜头聚焦状态信息
typedef struct tagCFG_CAP_FOCUS_STATUS
{
	int					nAutofocusPeak;							// 当前AF峰值	辅助聚焦模式下有效
	double		        dFocus;									// 聚焦位置	归一化到0~1
	double		        dZoom;									// 放大倍数	归一化到0~1
	int					nStatus;								// 聚焦状态, 0 正常状态 1 正在自动聚焦
}CFG_CAP_FOCUS_STATUS;

//云台支持能力信息
typedef struct tagCFG_CAP_PTZ_ENABLEINFO 
{
	BOOL bEnable;												//该通道是否支持云台
	
}CFG_CAP_PTZ_ENABLEINFO;


// 网络应用能力集
typedef struct tagCFG_CAP_NETAPP
{
	int                nNetCardCount;                           // 网卡数量
	int                nNetTypeNumber;                          // 网络类型个数
	char               szNetType[MAX_NET_TYPE_NUM][MAX_NET_TYPE_LEN]; // 具体网络类型, "PPPoE"，"WIFI"，"3G"，"LAN"
}CFG_CAP_NETAPP;



///////////////////////////////////三代协议新增///////////////////////////////////////
// 录像模式
struct AV_CFG_RecordMode
{
	AV_int32			nStructSize;
	AV_int32			nMode;							// 录像模式, 0-自动录像，1-手动录像，2-关闭录像
};

// 通道名称
struct AV_CFG_ChannelName
{
	AV_int32			nStructSize;
	AV_int32			nSerial;						// 摄像头唯一编号
	char				szName[AV_CFG_Channel_Name_Len];// 通道名
};

// 视频输出属性
struct AV_CFG_VideoOutAttr
{
	AV_int32			nStructSize;
	AV_int32			nMarginLeft;					// 左边距, 比率, 0~100
	AV_int32			nMarginTop;						// 上边距, 比率, 0~100
	AV_int32			nMarginRight;					// 右边距, 比率, 0~100
	AV_int32			nMarginBottom;					// 下边距, 比率, 0~100
	AV_int32			nBrightness;					// 亮度, 0~100
	AV_int32			nContrast;						// 对比度, 0~100
	AV_int32			nSaturation;					// 饱和度, 0~100
	AV_int32			nHue;							// 色调, 0~100
	AV_int32			nWidth;							// 水平分辨率
	AV_int32			nHeight;						// 垂直分辨率
	AV_int32			nBPP;							// 颜色深度
	AV_int32			nFormat;						// 0-Auto, 1-TV, 2-VGA, 3-DVI
	AV_int32			nRefreshRate;					// 刷新频率
	AV_BOOL				bIQIMode;						// 输出图像增强
};

// 时间段
struct AV_CFG_TimeSection
{
	AV_int32			nStructSize;
	AV_int32			nMask;							// 掩码
	AV_int32			nBeginHour;						// 开始时间
	AV_int32			nBeginMinute;
	AV_int32			nBeginSecond;
	AV_int32			nEndHour;						// 结束时间
	AV_int32			nEndMinute;
	AV_int32			nEndSecond;
};

// 远程通道
struct AV_CFG_RemoteChannel 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];	// 设备ID
	AV_int32			nChannel;						// 通道号
};

// 显示源
struct AV_CFG_DisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowID;						// 窗口ID
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	AV_int32			nVideoChannel;					// 视频通道号
	AV_int32			nVideoStream;					// 视频码流
	AV_int32			nAudioChannle;					// 音频通道号
	AV_int32			nAudioStream;					// 音频码流
	AV_BOOL				bVideoEnable;			        // 表示该窗口是否有视频源
};

// 通道分割显示源
struct AV_CFG_ChannelDisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowNum;						// 分割窗口数量
	AV_CFG_DisplaySource stuSource[AV_CFG_Max_Split_Window];// 分割窗口显示源
};

// 画面轮训下分割模式的分组使能状态
struct AV_CFG_MonitorTourMask
{
	AV_int32			nStructSize;
	CFG_SPLITMODE		emSplitMode;					// 分割模式
	AV_int32			nGroupNum;						// 分组数量
	AV_int32			nGroup[AV_CFG_Max_Split_Group];	// 该分割模式下加入轮训的分组
};

// 画面轮训
struct AV_CFG_MonitorTour 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	AV_int32			nInterval;						// 时间间隔, 5~120s
	AV_int32			nSplitMaskNum;					// 分割分组使能数量
	AV_CFG_MonitorTourMask	stuSplitMask[AV_CFG_Max_Split_Mode];// 各分割模式对应的分组使能状态
	AV_int32			nCollectionNum;					// 收藏数量
	char				szCollection[AV_CFG_Monitor_Favorite_In_Channel][AV_CFG_Monitor_Favorite_Name_Len];// 画面收藏名称
};

// 监视画面收藏
struct AV_CFG_MonitorFavorite 
{
	AV_int32			nStructSize;
	AV_BOOL				bDir;										// 是否为目录	
	char				szName[AV_CFG_Monitor_Favorite_Name_Len];	// 名称
	char				szPath[AV_CFG_Max_Path];					// 目录路径, 格式如下: .name1.name2.name3
	CFG_SPLITMODE		emMode;										// 分割模式
	AV_int32			nWindowNum;									// 窗口数量
	AV_CFG_DisplaySource stuWindow[AV_CFG_Max_Monitor_Favorite_Window];	// 窗口显示源配置
};

// 监视画面收藏集合
struct AV_CFG_MonitorCollection 
{
	AV_int32			nStructSize;
	AV_CFG_MonitorFavorite*	pstuFavorite;				// 画面收藏数组
	AV_int32			nMaxCount;						// 画面收藏数组大小
	AV_int32			nRetCount;						// 返回的画面收藏数量
};

// Raid信息
struct AV_CFG_Raid 
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Raid_Name_Len];	// 名称
	AV_int32			nLevel;							// 等级
	AV_int32			nMemberNum;						// 磁盘成员数量
	char				szMembers[AV_CFG_Max_Rail_Member][AV_CFG_Max_Path];	// 磁盘成员
};

// 录像源
struct AV_CFG_RecordSource
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	AV_int32			nVideoChannel;					// 视频通道号
	AV_int32			nVideoStream;					// 视频码流
	AV_int32			nAudioChannle;					// 音频通道号
	AV_int32			nAudioStream;					// 音频码流
};

// 编码格式, 包括音频和视频
struct AV_CFG_EncodeFormat
{
	AV_int32			nStructSize;
	AV_BOOL				bAudioEnable;					// 音频使能
	AV_int32			nAudioBitRate;					// 音频比特率
	CFG_AUDIO_FORMAT	emAudioCompression;				// 音频压缩模式
	AV_int32			nAudioDepth;					// 音频采样深度
	AV_int32			nAudioFrequency;				// 音频采样频率
	AV_int32			nAudioMode;						// 音频编码模式
	AV_int32			nAudioPack;						// 音频打包模式, 0-DHAV, 1-PS

	AV_BOOL				bVideoEnable;					// 视频使能
	AV_int32			nVideoBitRate;					// 视频比特率
	CFG_BITRATE_CONTROL	emVideoBitRateControl;			// 码流控制模式
	CFG_VIDEO_COMPRESSION emVideoCompression;			// 视频压缩模式
	AV_int32			nVideoFPS;						// 视频帧率
	AV_int32			nVideoGOP;						// 视频I帧间隔
	AV_int32			nVideoWidth;					// 视频宽度
	AV_int32			nVideoHeight;					// 视频高度
	CFG_IMAGE_QUALITY	emVideoQuality;					// 视频图像质量
	AV_int32			nVideoPack;						// 视频打包模式, 0-DHAV, 1-PS	
};

// 编码配置
struct AV_CFG_Encode 
{
	AV_int32			nStructSize;
	AV_CFG_EncodeFormat stuMainFormat[AV_CFG_Max_Encode_Main_Format];	// 主码流, 包括普通编码, 动检编码, 报警编码
	AV_CFG_EncodeFormat	stuExtraFormat[AV_CFG_Max_Encode_Extra_Format];	// 辅码流, 包括辅码流1, 辅码流2, 辅码流3
	AV_CFG_EncodeFormat	stuSnapFormat[AV_CFG_Max_Encode_Snap_Format];	// 抓图, 包括普通抓图, 动检抓图, 报警抓图
};

// 视频输入颜色配置, 每个视频输入通道对应多个颜色配置
struct AV_CFG_VideoColor 
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection	stuTimeSection;					// 时间段
	AV_int32			nBrightness;					// 亮度, 0~100
	AV_int32			nContrast;						// 对比度, 0~100
	AV_int32			nSaturation;					// 饱和度, 0~100
	AV_int32			nHue;							// 色调, 0~100
	AV_int32			nGamma;							// 增益, 0~100
};


// 通道视频输入颜色配置
struct AV_CFG_ChannelVideoColor 
{
	AV_int32			nStructSize;
	AV_int32			nColorNum;						// 通道颜色配置数
	AV_CFG_VideoColor	stuColor[AV_CFG_Max_VideoColor];// 通道颜色配置, 每个通道对应多个颜色配置
};

// 颜色
struct AV_CFG_Color
{
	AV_int32			nStructSize;
	AV_int32			nRed;							// 红
	AV_int32			nGreen;							// 绿
	AV_int32			nBlue;							// 蓝
	AV_int32			nAlpha;							// 透明
};

// 区域
struct AV_CFG_Rect 
{
	AV_int32			nStructSize;
	AV_int32			nLeft;
	AV_int32			nTop;
	AV_int32			nRight;
	AV_int32			nBottom;	
};

// 编码物件-区域覆盖配置
struct AV_CFG_VideoWidgetCover 
{
	AV_int32			nStructSize;	
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};

// 编码物件-通道标题
struct AV_CFG_VideoWidgetChannelTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};

// 编码物件-时间标题
struct AV_CFG_VideoWidgetTimeTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	AV_BOOL				bShowWeek;						// 是否显示星期
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};
	
// 编码物件-自定义标题
struct AV_CFG_VideoWidgetCustomTitle 
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	char				szText[AV_CFG_Custom_Title_Len];// 标题内容
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};

// 视频编码物件配置
struct AV_CFG_VideoWidget 
{
	AV_int32						nStructSize;
	AV_CFG_VideoWidgetChannelTitle	stuChannelTitle;	// 通道标题
	AV_CFG_VideoWidgetTimeTitle		stuTimeTitle;		// 时间标题
	AV_int32						nConverNum;			// 区域覆盖数量
	AV_CFG_VideoWidgetCover			stuCovers[AV_CFG_Max_Video_Widget_Cover];				// 覆盖区域
	AV_int32						nCustomTitleNum;	// 自定义标题数量
	AV_CFG_VideoWidgetCustomTitle	stuCustomTitle[AV_CFG_Max_Video_Widget_Custom_Title];	// 自定义标题
};

// 存储组通道相关配置
struct AV_CFG_StorageGroupChannel 
{
	AV_int32			nStructSize;
	AV_int32			nMaxPictures;					// 每个通道文件夹图片存储上限, 超过就覆盖
	char				szPath[AV_CFG_Max_ChannelRule];	// 通道在命名规则里的字符串表示, %c对应的内容
};

// 存储组配置
struct AV_CFG_StorageGroup 
{
	AV_int32			nStructSize;	
	char				szName[AV_CFG_Group_Name_Len];	// 分组名称
	char				szMemo[AV_CFG_Group_Memo_Len];	// 分组说明
	AV_int32			nFileHoldTime;					// 文件保留时间
	AV_BOOL				bOverWrite;						// 存储空间满是否覆盖
	char				szRecordPathRule[AV_CFG_Max_Path];	// 录像文件路径命名规则
	char				szPicturePathRule[AV_CFG_Max_Path];	// 图片文件路径命名规则
															// %y年, %M月, %d日, %h时, %m分, %s秒, %c通道路径
															// 如果年月日时分秒出现两次, 第一次表示开始时间, 第二次表示结束时间
	AV_CFG_StorageGroupChannel	stuChannels[AV_CFG_Max_Channel_Num];// 通道相关配置 
	AV_int32				nChannelCount;				// 通道配置数
};

// DST时间
struct AV_CFG_DSTTime 
{
	AV_int32			nStructSize;
	AV_int32			nYear;							// 年, 2000~2038
	AV_int32			nMonth;							// 月, 1~12
	AV_int32			nWeek;							// 第几周, 1-第一周,2-第二周,...,-1-最后一周,0-按日期计算
	AV_int32			nDay;							// 星期几或日期
														// 按周计算时, 0-周日, 1-周一,..., 6-周六
														// 按日期算时, 表示几号, 1~31
	AV_int32			nHour;							// 小时
	AV_int32			nMinute;						// 分钟
};

// 区域配置
struct AV_CFG_Locales 
{
	AV_int32			nStructSize;
	char				szTimeFormat[AV_CFG_Time_Format_Len];	// 时间格式
	AV_BOOL				bDSTEnable;						// 夏令时时能
	AV_CFG_DSTTime		stuDstStart;					// 夏令时起始时间
	AV_CFG_DSTTime		stuDstEnd;						// 夏令时结束时间
};

// 语言类型
enum AV_CFG_LanguageType
{
	AV_CFG_Language_English,							// 英文
	AV_CFG_Language_SimpChinese,						// 简体中文
	AV_CFg_Language_TradChinese,						// 繁体中文
	AV_CFG_Language_Italian,							// 意大利文
	AV_CFG_Language_Spanish,							// 西班牙文
	AV_CFG_Language_Janpanese,							// 日文
	AV_CFG_Language_Russian,							// 俄文
	AV_CFG_Language_French,								// 法文
	AV_CFG_Language_German,								// 德文
};

// 语言配置
struct AV_CFG_Language 
{
	AV_int32			nStructSize;
	AV_CFG_LanguageType emLanguage;						// 当前语言
};

// 访问地址过滤
struct AV_CFG_AccessFilter
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	AV_int32			nType;							// 类型, 0-黑名单, 1-白名单
	AV_int32			nWhiteListNum;					// 白名单IP数量
	char				szWhiteList[AV_CFG_Max_White_List][AV_CFG_Filter_IP_Len];	// 白名单
	AV_int32			nBlackListNum;					// 黑名单IP或IP段数量
	char				szBlackList[AV_CFG_Max_Black_List][AV_CFG_Filter_IP_Len];	// 黑名单
};

// 自动维护
struct AV_CFG_AutoMaintain 
{
	AV_int32			nStructSize;
	AV_int32			nAutoRebootDay;					// 自动重启日期, -1永不, 0~6周日~周六, 7每天
	AV_int32			nAutoRebootHour;				// 自动重启小时, 0~23
	AV_int32			nAutoRebootMinute;				// 自动重启分钟, 0~59
	AV_int32			nAutoShutdownDay;				// 自动关机日期
	AV_int32			nAutoShutdownHour;				// 自动关机小时
	AV_int32			nAutoShutdownMinute;			// 自动关机分钟
	AV_int32			nAutoStartupDay;				// 自动启动日期
	AV_int32			nAutoStartupHour;				// 自动启动小时
	AV_int32			nAutoStartupMinute;				// 自动启动分钟
};

#define AV_CFG_Monitor_Name_Len		64			// 电视墙名称长度
#define AV_CFG_Max_TV_In_Block		64			// 区块中TV的最大数量
#define AV_CFG_Max_Block_In_Wall	64			// 电视墙中区块的最大数量

// 电视墙输出通道信息
struct AV_CFG_MonitorWallTVOut
{
	AV_int32		nStructSize;
	char			szDeviceID[AV_CFG_Device_ID_Len];	// 设备ID, 为空或"Local"表示本地设备
	AV_int32		nChannelID;							// 通道ID
	char			szName[AV_CFG_Channel_Name_Len];	// 屏幕名称
};

// 电视墙区块
struct AV_CFG_MonitorWallBlock 
{
	AV_int32				nStructSize;
	AV_int32				nLine;				// 单个TV占的网格行数
	AV_int32				nColumn;			// 单个TV占的网格列数
	AV_CFG_Rect				stuRect;			// 区块的区域坐标
	AV_int32				nTVCount;			// TV数量
	AV_CFG_MonitorWallTVOut	stuTVs[AV_CFG_Max_TV_In_Block];					// TV数组
	CFG_TIME_SECTION		stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	// 开关机时间
	char					szName[AV_CFG_Channel_Name_Len];				// 区块名称
	char					szCompositeID[AV_CFG_Device_ID_Len];			// 融合屏ID
};

// 电视墙
struct AV_CFG_MonitorWall
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Monitor_Name_Len];	// 名称
	AV_int32			nLine;								// 网络行数
	AV_int32			nColumn;							// 网格列数
	AV_int32			nBlockCount;						// 区块数量
	AV_CFG_MonitorWallBlock stuBlocks[AV_CFG_Max_Block_In_Wall];// 区块数组

};

// 拼接屏
struct AV_CFG_SpliceScreen
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Channel_Name_Len];	// 拼接屏名称	
	char				szWallName[AV_CFG_Monitor_Name_Len];// 所属电视墙名称
	AV_int32			nBlockID;							// 所属区块序号
	AV_CFG_Rect			stuRect;							// 区域坐标(0~8191)
};

// 云台联动类型
typedef enum tagAV_CFG_PtzLinkType
{
	AV_CFG_PtzLink_None,				// 无联动
	AV_CFG_PtzLink_Preset,				// 联动预置点
	AV_CFG_PtzLink_Tour,				// 联动巡航
	AV_CFG_PtzLink_Pattern,				// 联动轨迹
} AV_CFG_PtzLinkType;

// 联动云台信息
typedef struct tagAV_CFG_PtzLink
{
	AV_int32            nStructSize;
	AV_CFG_PtzLinkType	emType;				// 联动类型 
	AV_int32			nParam1;			// 联动参数1
	AV_int32			nParam2;            // 联动参数2
	AV_int32			nParam3;            // 联动参数3
	AV_int32			nChannelID;         // 所联动云台通道
} AV_CFG_PtzLink;

// 坐标点
typedef struct tagAV_CFG_Point
{
	AV_int32			nStructSize;
	AV_int32			nX;
	AV_int32			nY;
} AV_CFG_Point;

// 宽高
typedef struct tagAV_CFG_Size
{
	AV_int32			nStructSize;
	AV_uint32			nWidth;
	AV_uint32			nHeight;
} AV_CFG_Size;	

// 事件标题内容
typedef struct tagAV_CFG_EventTitle
{
	AV_int32			nStructSize;
	char				szText[AV_CFG_Channel_Name_Len];	// 标题文本
	AV_CFG_Point		stuPoint;			// 标题左上角坐标, 采用0-8191相对坐标系
	AV_CFG_Size			stuSize;			// 标题的宽度和高度,采用0-8191相对坐标系，某项或者两项为0表示按照字体自适应宽高
    AV_CFG_Color		stuFrontColor;		// 前景颜色
    AV_CFG_Color		stuBackColor;		// 背景颜色
} AV_CFG_EventTitle;


// 轮巡联动配置
typedef struct tagAV_CFG_TourLink
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;			// 轮巡使能
	CFG_SPLITMODE		emSplitMode;		// 轮巡时的分割模式
	AV_int32			nChannels[AV_CFG_Max_Channel_Num];  // 轮巡通道号列表
	AV_int32			nChannelCount;		// 轮巡通道数量
} AV_CFG_TourLink;

// 报警联动
typedef struct tagAV_CFG_EventHandler
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection  stuTimeSect[AV_CFG_Weekday_Num][AV_CFG_Max_TimeSection]; // 事件响应时间表
	AV_BOOL             bRecordEnable;		// 录像使能
	AV_uint32           nRecordMask[AV_CFG_Max_Channel_Num];	// 录像通道号列表
	AV_BOOL             abRecordLatch;		// 能力集, 标识nRecordLatch是否有效
	AV_int32            nRecordLatch;		// 录像延时时间（10~300秒）
	AV_BOOL				bAlarmOutEn;		// 报警输出使能
	AV_uint32			nAlarmOutMask[AV_CFG_Max_Channel_Num];	// 报警输出通道号列表
	AV_BOOL             abAlarmOutLatch;	// 能力集, 标识nAlarmOutLatch是否有效
	AV_int32			nAlarmOutLatch;		// 报警输出延时时间（10~300秒）
	AV_BOOL				bExAlarmOutEn;		// 扩展报警输出使能
	AV_uint32			nExAlarmOutMask[AV_CFG_Max_Channel_Num]; // 扩展报警输出通道列表
	AV_BOOL				bPtzLinkEn;			// 云台联动使能
	AV_int32            nPtzLinkNum;		// 有效联动项数目
	AV_CFG_PtzLink		stuPtzLink[AV_CFG_Max_Channel_Num];		// 云台联动项
	AV_BOOL				bSnapshotEn;		// 快照使能
	AV_uint32			nSnapshotMask[AV_CFG_Max_Channel_Num];  // 快照通道号列表	
	AV_BOOL             abSnapshotPeriod;	// 能力集, 标识nSnapshotPeriod是否有效
	AV_int32			nSnapshotPeriod;	// 帧间隔，每隔多少帧抓一张图片，一定时间内抓拍的张数还与抓图帧率有关。0表示不隔帧，连续抓拍。
	AV_BOOL             abSnapshotTimes;	// 能力集, nSnapshotTimes有效性
	AV_int32			nSnapshotTimes;		// 连拍次数, 在SnapshotEnable为true的情况下，SnapshotTimes为0则表示持续抓拍，直到事件结束。
	AV_BOOL             bSnapshotTitleEn;	// 是否叠加图片标题
	AV_int32            nSnapTitleNum;      // 有效图片标题数目
	AV_CFG_EventTitle   stuSnapTitles[AV_CFG_Max_Event_Title_Num]; // 图片标题内容
	AV_BOOL				bTipEnable;			// 本地消息框提示
	AV_BOOL				bMailEnable;		// 发送邮件，如果有图片，作为附件
	AV_BOOL				bMessageEnable;		// 上传到报警服务器
	AV_BOOL				bBeepEnable;		// 蜂鸣
	AV_BOOL				bVoiceEnable;		// 语音提示
	AV_BOOL             abDejitter;			// 能力集, nDejitter有效性
	AV_int32            nDejitter;			// 信号去抖动时间，单位为秒,0~100
	AV_BOOL             bLogEnable;			// 是否记录日志
	AV_BOOL             abDelay;			// nDelay有效性
	AV_int32            nDelay;				// 设置时先延时再生效, 单位为秒
	AV_BOOL             bVideoTitleEn;		// 是否叠加视频标题，主要指主码流
	AV_int32            nVideoTitleNum;		// 有效视频标题数目
	AV_CFG_EventTitle	stuVideoTitles[AV_CFG_Max_Event_Title_Num]; // 视频标题内容
	AV_BOOL				bMMSEnable;			// 发送彩信使能
	AV_int32            nTourNum;			// 轮巡联动数目，和视频输出一致
	AV_CFG_TourLink	    stuTour[AV_CFG_Max_Tour_Link_Num];		// 轮巡联动配置, 每个视频输出对应一个配置
	AV_int32            nDBKeysNum;			// 关键字数量
	char	            szDBKeys[AV_CFG_Max_DBKey_Num][AV_CFG_DBKey_Len]; // 关键字
	AV_BOOL             abJpegSummary;		// 能力集, 标识byJpegSummary是否有效
	AV_BYTE             byJpegSummary[AV_CFG_Max_Summary_Len]; // 叠加到JPEG图片的摘要信息
} AV_CFG_EventHandler;

#define AV_CFG_Event_Code_Len	64		// 事件码长度

// 远程设备事件处理
struct AV_CFG_RemoteEvent 
{
	AV_int32            nStructSize;
	AV_BOOL             bEnable;						 // 使能
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	char                szCode[AV_CFG_Event_Code_Len];	 // 事件码
	AV_int32            nIndex;							 // 序号
	AV_BOOL             abSensorType;                    // nSensorType是否有效
	AV_uint32           nSensorType;                     // 传感器类型 常开:1 or 常闭:0
	AV_CFG_EventHandler stuEventHandler;				 // 报警联动
};

// 温度报警配置
typedef struct tagAV_CFG_TemperatureAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// 报警使能
	char				szName[AV_CFG_Device_Name_Len];		// 传感器名称
	AV_float			fNormalTempMin;						// 正常温度最小值
	AV_float			fNormalTempMax;						// 正常温度最大值
	AV_CFG_EventHandler stuEventHandler;					// 报警联动
} AV_CFG_TemperatureAlarm;

// 风扇转速报警配置
typedef struct tagAV_CFG_FanSpeedAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// 报警使能
	char				szName[AV_CFG_Device_Name_Len];		// 传感器名称
	AV_uint32			nNormalSpeedMin;					// 正常转速最小值
	AV_uint32			nNormalSpeedMax;					// 正常转速最大值
	AV_CFG_EventHandler stuEventHandler;					// 报警联动
} AV_CFG_FanSpeedAlarm;

// 硬盘流量报警配置
typedef struct tagCFG_DISK_FLUX_INFO 
{
	BOOL				bEnable;							// 报警使能
	unsigned int		nNormalFluxMin;						// 正常流量最小值, 单位KB
	unsigned int		nNormalFluxMax;						// 正常流量最大值, 单位KB
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// 事件响应时间段
} CFG_DISK_FLUX_INFO;

// 网络流量报警配置
typedef struct tagCFG_NET_FLUX_INFO
{
	BOOL				bEnable;							// 报警使能
	unsigned int		nNormalFluxMin;						// 正常流量最小值, 单位KB
	unsigned int		nNormalFluxMax;						// 正常流量最大值, 单位KB
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// 事件响应时间段
} CFG_NET_FLUX_INFO;

// 服务器
typedef struct tagCFG_SERVER_INFO
{
	int                 nPort;                             // 服务器端口号
	char                szAddress[MAX_ADDRESS_LEN];        // IP地址或网络名
}CFG_SERVER_INFO;

// 主动注册配置
typedef struct tagCFG_REGISTER_SERVER_INFO
{
	BOOL                bEnable;                            // 主动注册使能
	char                szDeviceID[MAX_ADDRESS_LEN];        // 设备ID
	int                 nServersNum;                        // 服务器个数
	CFG_SERVER_INFO     stuServers[MAX_SERVER_NUM];         // 服务器数组
}CFG_REGISTER_SERVER_INFO;

// 网络协议配置
typedef struct tagCFG_DVRIP_INFO
{
	int                 nTcpPort;                           // TCP服务端口,1025~65535
	int                 nSSLPort;                           // SSL服务端口,1025~65535
	int                 nUDPPort;                           // UDP服务端口,1025~65535
	int                 nMaxConnections;                    // 最大连接数 
	BOOL                bMCASTEnable;                       // 组播使能
	int                 nMCASTPort;                         // 组播端口号
	char                szMCASTAddress[MAX_ADDRESS_LEN];    // 组播地址
	int                 nRegistersNum;                      // 主动注册配置个数
	CFG_REGISTER_SERVER_INFO stuRegisters[MAX_REGISTER_NUM];// 主动注册配置 
}CFG_DVRIP_INFO;

// 假期录像计划
typedef struct tagCFG_HOLIDAY_SCHEDULE
{
	BOOL				bEnable;
	int					nChannel;
	DWORD				dwMonthSchedule[MONTH_OF_YEAR];		// 每个月的假期安排, 每个元素表示一个月, 
															// 掩码从低到高依次表示每月1-28/29/30/31号是否为假期
															// 0:不是假期, 1:是假期
	CFG_TIME_SECTION	stuTimeSection[MAX_REC_TSECT];		// 录像时间表
} CFG_HOLIDAY_SCHEDULE;

// 录像回传配置
typedef struct tagAV_CFG_RecordBackup
{
	AV_int32			nStructSize;
	AV_uint32			nBitrateLimit;						// 最大流量配置, 单位Kbps
	AV_CFG_RemoteDevice	*pstuDevices;						// 备份设备数组, 用户分配内存
	int					nMaxDeviceCount;					// 备份设置数组大小, 用户填写
	int					nRetDeviceCount;					// 返回的设备数量
} AV_CFG_RecordBackup;

typedef struct tagALARM_EVENT_INFO
{
	DWORD	        	dwEventType;					    // 事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int		         	nEventSize;							// 该事件类型规则配置结构体大小
} ALARM_EVENT__INFO;

// 每个视频输入通道对应的所有事件：缓冲区pEventBuf填充多个事件信息，每个事件规则信息内容为ALARM_EVENT_INFO+"事件类型对应的规则配置结构体"。
typedef struct tagALARM_ANALYSEEVENTS_INFO
{
	int	         		nEventCount;						// 事件个数
	char*				pEventBuf;							// 每个视频输入通道对应的视频分析事件缓冲
	int		        	nEventBufLen;						// 缓冲大小
	
} ALARM_ANALYSEEVENTS_INFO;

// 串口信息
typedef struct tagCFG_COMM_INFO
{
	char				szProtocolName[MAX_PROTOCOL_NAME_LEN];	// 串口协议
	CFG_COMM_PROP		stuAttribute;							// 串口属性
	int					nAddress;								// 设备地址
} CFG_COMM_INFO;

// 串口配置
typedef struct tagCFG_COMMGROUP_INFO
{
	int					nCommNum;						// 串口数量
	CFG_COMM_INFO		stuComms[MAX_COMM_NUM];			// 串口数组
} CFG_COMMGROUP_INFO;

// 网络接口
typedef struct tagCFG_NETWORK_INTERFACE 
{
	char				szName[MAX_NAME_LEN];			// 网络接口名称
	char				szIP[MAX_ADDRESS_LEN];			// ip地址
	char				szSubnetMask[MAX_ADDRESS_LEN];	// 子网掩码
	char				szDefGateway[MAX_ADDRESS_LEN];	// 默认网关
	BOOL				bDhcpEnable;					// 是否开启DHCP
	BOOL				bDnsAutoGet;					// DNS获取方式，dhcp使能时可以设置为true，支持通过dhcp获取
	char				szDnsServers[MAX_DNS_SERVER_NUM][MAX_ADDRESS_LEN];	// DNS服务器地址
	int					nMTU;							// 网络最大传输单元
} CFG_NETWORK_INTERFACE;

// 网络接口配置
typedef struct tagCFG_NETWORK_INFO 
{
	char				szHostName[MAX_NAME_LEN];		// 主机名称
	char				szDomain[MAX_NAME_LEN];			// 所属域
	char				szDefInterface[MAX_NAME_LEN];	// 默认使用的网卡
	int					nInterfaceNum;					// 网卡数量
	CFG_NETWORK_INTERFACE	stuInterfaces[MAX_NETWORK_INTERFACE_NUM];	// 网卡列表
} CFG_NETWORK_INFO;

// 网络存储配置
typedef struct tagCFG_NAS_INFO_NEW
{
	BOOL				bEnable;						// 使能
	char				szName[MAX_NAME_LEN];			// 名称
	int					nPortocol;						// 协议类型, 0-FTP, 1-SMB, 2-ISCSI
	char				szAddress[MAX_ADDRESS_LEN];		// IP地址或网址
	int					nPort;							// 端口
	char				szUser[MAX_USERNAME_LEN];		// 用户名
	char				szPassword[MAX_PASSWORD_LEN];	// 密码
	char				szDirectory[MAX_NAME_LEN];		// 共享的目录名
	int					nCharEncoding;					// 字符编码格式, 0-UTF8, 1-GB2312
} CFG_NAS_INFO_NEW;

// 网络存储服务器配置, 包含多个服务器
typedef struct tagCFG_NAS_GROUP_INFO
{
	int					nNasNum;						// 存储服务器数量
	CFG_NAS_INFO_NEW	stuNasInfo[MAX_NAS_NUM];		// 存储服务器数组	
} CFG_NAS_GROUP_INFO;

// 网络存储服务器配置
typedef struct tagCFG_NAS_INFO_EX 
{
	int					nVersion;						// 0, 1, 由能力集确定, 只读
	CFG_NAS_INFO		stuNasOld;						// nVersion == 0时有效, 仅支持单服务器
	CFG_NAS_GROUP_INFO	stuNasGroup;					// nVersion == 1时有效, 支持多个服务器
} CFG_NAS_INFO_EX;

// 输入通道基本配置
typedef struct tagCFG_VIDEO_IN_INFO 
{
	char				szDevType[MAX_NAME_LEN];		// 通道类型（指通道连接的设备类型）
	char				szDevID[MAX_NAME_LEN];			// 摄像头唯一编号
	char				szChnName[MAX_NAME_LEN];		// 通道名词
	char				szManufacturer[MAX_NAME_LEN];	// 厂商
	char				szModel[MAX_NAME_LEN];			// 设备型号
	char				szAddress[MAX_ADDRESS_LEN];		// 安装地址
	char				szCivilCode[MAX_NAME_LEN];		// 行政区域
	char				szOwner[MAX_NAME_LEN];			// 设备归属
	BOOL				bParental;						// 是否有子设备
	BOOL				bEnable;						// 通道使能
	int					nRegisterWay;					// 注册方式
														// 0-符合sip3261标准的认证注册模式
														// 1-基于口令的双向认证注册模式
														// 2-基于数字证书的双向认证注册模式
	BOOL				bSecrecy;						// 保密属性, FALSE不涉密, TRUE涉密
	char				szUpperDevID[MAX_NAME_LEN];		// 上级连接设备设备ID
	int					nUpperDevOutChn;				// 上级连接设备输出通道号
} CFG_VIDEO_IN_INFO;

// 刻录光盘编码计划(对应命令 CFG_CMD_ENCODEPLAN)，每个通道(包括画中画通道)一个配置结构体
typedef struct tagCFG_ENCODE_PLAN_INFO
{
	BOOL                bEnable;                        // 通道是否需要配置,FALSE:没有此通道,TRUE:此通道可用
	unsigned int        nExpectTime;                    // 业务预期时长	 整型,单位：分钟
	CFG_CAPTURE_SIZE    emResolution;                   // 视频分辨率
	unsigned int        nBitRate;                       // 视频固定码流值(kbps)
}CFG_ENCODE_PLAN_INFO;

//////////////////////////////////////////////////////////////////////////
// 司法审讯画中画需求
// 小画面窗口信息
typedef struct tagCFG_SMALLPIC_INFO
{
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	int                 nChannelID;						 // 通道号(0开始)
	BOOL                bAudio;                          // 大画面是否混合小画面音频
    CFG_RECT            stuPosition;                     // 使用相对坐标体系，取值均为0-8192,在整个屏幕上的位置
}CFG_SMALLPIC_INFO;

// 分割通道
typedef struct tagCFG_SPLIT_CHANNEL_INFO
{
	BOOL                bEnable;                         // 使能
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	int                 nChannelID;						 // 通道号(0开始)
	unsigned int        nMaxSmallChannels;               // 小画面通道个数，每个通道一个CFG_SMALLPIC_INFO,这里最大应该是设备通道数减一
	unsigned int        nReturnSmallChannels;            // 解析返回的或封装发送的小画面通道个数
	CFG_SMALLPIC_INFO  *pPicInfo;                        // 小画面信息
}CFG_SPLIT_CHANNEL_INFO;

// 分割方案
typedef struct tagCFG_SPLIT_INFO
{
	CFG_SPLITMODE       emSplitMode;        // 分割模式，通过CLIENT_GetSplitCaps接口获取，见emSplitMode
	unsigned int        nMaxChannels;       // 申请内存CFG_SPLIT_CHANNEL_INFO个数,比如有16个通道，nMaxChannels就是16，SPLITMODE_4模式，则按顺序依次分为4组
	unsigned int        nReturnChannels;    // 解析返回通道个数,要封装发送的通道个数
	CFG_SPLIT_CHANNEL_INFO* pSplitChannels; // 分割通道信息
}CFG_SPLIT_INFO;

// 画中画方案
typedef struct tagCFG_PICINPIC_INFO
{
	unsigned int        nMaxSplit;          // 内存申请的CFG_SPLIT_INFO个数,最大值通过CLIENT_GetSplitCaps接口获取，见nModeCount
	unsigned int        nReturnSplit;       // 解析得到实际使用的或封装发送的CFG_SPLIT_INFO个数
	CFG_SPLIT_INFO     *pSplits;            // 分割方案
}CFG_PICINPIC_INFO;

// 模拟矩阵外部输入源
typedef struct tagCFG_ANALOG_MATRIX_INPUT_CHN_SRC 
{
	char				szName[MAX_NAME_LEN];			// 输入通道名称
	char				szControlID[MAX_NAME_LEN];		// 控制编号
	BOOL				bActive;						// 是否激活启动
	int					nFormat;						// 类型, 0-VGA
} CFG_ANALOG_MATRIX_INPUT_CHN_SRC;

// 串口
typedef struct tagCFG_COM_PORT 
{
	int					nPortIndex;						// 串口索引号
	int					nAddress;						// 设备地址
	CFG_COMM_PROP		stComProp;						// 串口属性
} CFG_COM_PORT;

// 模拟矩阵
typedef struct tagCFG_ANALOG_MATRIX_INFO
{
	char				szDevID[MAX_NAME_LEN];			// 设备ID
	char				szName[MAX_NAME_LEN];			// 设备名称
	char				szModel[MAX_MODEL_LEN];			// 型号
	char				szUserName[MAX_USERNAME_LEN];	// 用户名
	char				szPassword[MAX_PASSWORD_LEN];	// 密码
	int					nChnInCount;					// 输入通道数量
	int					nChnOutCount;					// 输出通道数量
	CFG_ANALOG_MATRIX_INPUT_CHN_SRC* pstuChnInSrc;		// 外部输入源数组, 用户分配内存
	int					nChnInSrcCount;					// 外部输入源数组大小
	int					nRetChnInSrcCount;				// 实际返回的外部输入源数量, 一般同nChnInCount
	CFG_COM_PORT		stComPort;						// 关联串口
	char				szProtocol[MAX_NAME_LEN];		// 协议名称
} CFG_ANALOG_MATRIX_INFO;

// 模拟矩阵协议配置
typedef struct tagCFG_ANALOG_MATRIX_PROTOCOL 
{
	char				szName[MAX_NAME_LEN];			// 协议名称
	char				szProtocolRule[MAX_NAME_LEN];	// 协议内容, 规则：%A-地址码，%I-输入端口号，%O-输出端口号
} CFG_ANALOG_MATRIX_PROTOCOL;

// 视频输出标题
typedef struct tagCFG_VIDEO_OUT_TITLE 
{
	char				szName[MAX_NAME_LEN];			// 通道名称
} CFG_VIDEO_OUT_TITLE;

// 显示源
typedef struct tagCFG_DISPLAY_SOURCE
{
	BOOL				bEnable;						// 是否使能
	char				szDeviceID[MAX_NAME_LEN];		// 设备ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	int					nVideoChannel;					// 视频通道号
	int					nVideoStream;					// 视频码流, -1-自动, 0-主码流, 1-辅码流1, 2-辅码流2, 3-辅码流3 
	int					nAudioChannel;					// 音频通道号
	int					nAudioStream;					// 音频码流, -1-自动, 0-主码流, 1-辅码流1, 2-辅码流2, 3-辅码流3 
	BOOL				abDeviceInfo;					// 设备信息是否有效
	AV_CFG_RemoteDevice stuDeviceInfo;					// 设备信息
} CFG_DISPLAY_SOURCE;

// 窗口位置
typedef struct tagCFG_SPLIT_WINDOW_POSITION 
{
	CFG_RECT			stuRect;						// 窗口区域
	BOOL				bDirectable;					// 是否满足直通条件, 直通是指拼接屏方式下，此窗口区域正好为物理屏区域
	int					nZorder;						// Z次序
} CFG_SPLIT_WINDOW_POSITION;

// 拼接屏窗口信息
typedef struct tagCFG_SPLIT_WINDOW 
{
	BOOL				bEnable;						// 窗口是否有视频源, 为FALSE时表示没有视频，也不用处理Source内容
	int					nWindowID;						// 窗口ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	CFG_SPLIT_WINDOW_POSITION stuPosition;				// 窗口位置
	CFG_DISPLAY_SOURCE	stuSource;						// 视频源
} CFG_SPLIT_WINDOW;

// 拼接屏场景
typedef struct tagCFG_BLOCK_COLLECTION 
{
	char				szBlockID[MAX_NAME_LEN];		// 拼接屏ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	CFG_SPLITMODE		emSplitMode;					// 分割模式
	CFG_SPLIT_WINDOW*	pstuWnds;						// 窗口信息数组, 用户分配内存
	int					nMaxWndCount;					// 窗口信息数组大小, 用户填写
	int					nRetWndCount;					// 返回的窗口数量
} CFG_BLOCK_COLLECTION;

// 电视墙中的某个预案配置
typedef struct tagCFG_MONITORWALL_COLLECTION_SINGLE
{
	char				szName[MAX_NAME_LEN];			// 名称
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	AV_CFG_MonitorWall	stuMonitorWall;					// 电视墙配置
	CFG_BLOCK_COLLECTION* pstuBlockCollections;			// 拼接屏场景信息数组, 用户分配内存
	int					nMaxBlockCollectionCount;		// 拼接屏场景数组大小, 用户填写
	int					nRetBlockCollectionCount;		// 返回的拼接屏场景数量
} CFG_MONITORWALL_COLLECTION_SINGLE;

// 电视墙预案列表, 表示某个电视墙对应的多个预案
typedef struct tagCFG_MONITORWALL_COLLECTION_LIST
{
	CFG_MONITORWALL_COLLECTION_SINGLE* pstuCollections;	// 预案数组, 用户分配内存
	int					nMaxCollectionCount;			// 预案数组大小, 用户填写
	int					nRetCollectionCount;			// 返回的预案数量
} CFG_MONITORWALL_COLLECTION;

// 视频输入边界配置
typedef struct tagCFG_VIDEO_IN_BOUNDARY 
{
	CFG_RECT			stuBoundary;					// 边界
} CFG_VIDEO_IN_BOUNDARY;

// 和相机对接的区域屏配置,是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen)
typedef struct tagCFG_PARKINGSPACE_SCREEN_INFO
{
	char                szAddress[MAX_PATH];            // 区域屏地址或域名
	int                 nPort;                          // 区域屏端口
	char                szAuthorization[MAX_PATH];      // 权限字
    char                szDeviceNo[MAX_PATH];           // 设备序号
	BOOL                bEnable;                        // 屏配置是否启用
} CFG_PARKINGSPACE_SCREEN_INFO;

// 车位设置(专有车位和普通车位设置)，是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxRoadWays)
typedef struct tagCFG_PARKINGSPACE_STATUS_INFO
{
	int                  nLaneID;                        // 车位号
	int                  nLaneType;                      // 0：普通车位 1：专有车位
} CFG_PARKINGSPACE_STATUS_INFO;

// 平台自定义信息
typedef struct tagCFG_CLIENT_CUSTOM_INFO
{
	char                 szDescription[MAX_PATH];        // 描述信息,不同平台自定义描述信息,目前支持"LiFang"
	char*                pData;                          // 自定义数据缓冲，数据中间不能存在二进制的0也就是字符'\0'
	int                  nDataLen;                       // 用户申请的长度，不同平台自己确定
} CFG_CLIENT_CUSTOM_INFO;

// 刻录格式配置,兼容性考虑：无此配置时默认DHAV格式
typedef struct tagCFG_BURN_RECORD_FORMAT
{
	char                 szRecordPack[MAX_PATH];         // 码流打包模式:目前支持"DHAV","PS"
}CFG_BURN_RECORD_FORMAT;

// 多光盘同步刻录(对应 CFG_MULTIBURN_INFO) 是一个数组，每一个元素表示一组多光盘同步刻录及校验
typedef struct tagCFG_MULTIBURN_INFO
{
	BOOL                 bEnable;                        // 此配置使能开关
    BOOL                 bDataCheck;                     // 多光盘一致性校验使能
    char                 szDataCheckSpeed[MAX_PATH];     // 校验速度 "High":高速（头尾数据校验）,"Normal":正常（随机数据校验）,"Low":低速 （全盘数据校验）
}CFG_MULTIBURN_INFO;

// 获取刻录管理能力集
typedef struct tagCFG_CAP_BURN_MANAGER	
{
    BOOL                 bSupportMultiBurn;              // 是否支持多光盘同步刻录
    int                  nMultiBurnGroups;               // 支持几组同步刻录
}CFG_CAP_BURN_MANAGER;

// 录像能力信息
typedef struct tagCFG_CAP_RECORD_INFO	
{
	BOOL  bSupportHoliday;				                 //录像计划是否支持假日功能
	BOOL  bSupportExtraRecordMode;						 //是否支持设置辅码流录像模式	
	DWORD dwMaxPreRecordTime;							 //最大预录时间
	DWORD dwMaxRemoteBitrate;							 //最大接入总码流,单位kbps
	DWORD dwMaxRemoteRawBitrate;						 //最大接入祼码流（包括路数、分辨率、帧率，色深按16bpp计算）
} CFG_CAP_RECORD_INFO;

/************************************************************************
** 接口定义
***********************************************************************/
// 报警事件类型根据dhnetsdk.h解析出来的报警类型
typedef int  (CALLBACK *fALARMEvent)(DWORD dwAlarmType, void* pAlarmInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// 回调方式进行数据解析，dwDataType表示数据解析得到类型
typedef int  (CALLBACK *fAnalyzerData)(DWORD dwDataType, void* pDataInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// 解析查询到的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_ParseData(char* szCommand, char* szInBuffer, LPVOID lpOutBuffer, DWORD dwOutBufferSize, void* pReserved);

// 组成要设置的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_PacketData(char* szCommand, LPVOID lpInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize);

// 录像报警事件解析
CLIENT_API BOOL  CALL_METHOD CLIENT_ParseAnalyzerEventData(LPVOID lpInBuffer, DWORD dwInBufferSize, fALARMEvent cbEvent, LDWORD dwUser);

// 回调方式数据解析
CLIENT_API BOOL CALL_METHOD CLIENT_ParseDataByCallback(LPVOID lpInBuffer, DWORD dwInBufferSize, fAnalyzerData cbAnalyzer, LDWORD dwUser);
#ifdef __cplusplus
}
#endif

#endif // DHCONFIGSDK_H

