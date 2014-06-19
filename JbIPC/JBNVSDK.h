#ifndef __JB_NV_SDK_H__
#define __JB_NV_SDK_H__

#include <MMSYSTEM.H>
/************************************************************************/
/*  Error Code Define                                                   */
/************************************************************************/
#define JB_SUCCESS                          0x00000000
#define JBERR_BASE							0x10000000
#define	JBERR_PASSWORD_UNMATCH				(JBERR_BASE|0x01)			//密码不匹配
#define	JBERR_TIME_OVER						(JBERR_BASE|0x02)			//操作超时
#define	JBERR_INVALID_PARAM					(JBERR_BASE|0x03)			//无效参数
#define	JBERR_MAX_LINK						(JBERR_BASE|0x04)			//超过最大连接数
#define	JBERR_INVALID_HANDLE				(JBERR_BASE|0x05)			//句柄非法或错误
#define	JBERR_INVALID_COMMAND				(JBERR_BASE|0x06)			//不被接受的命令
#define	JBERR_SENDCMD_FAILD					(JBERR_BASE|0x07)			//发送命令数据失败
#define	JBERR_GETCONFIG_FAILD				(JBERR_BASE|0x08)			//取得命令数据失败
#define	JBERR_NO_LOGON						(JBERR_BASE|0x09)			//没有登录
#define	JBERR_ALLOC_FAILD					(JBERR_BASE|0x0a)			//分配内存失败
#define	JBERR_INVALID_NETADDRESS			(JBERR_BASE|0x0b)			//无效的或无法解析的网络地址	
#define	JBERR_FILE_CRC32					(JBERR_BASE|0x0C)			//文件校验错
#define JBERR_SOFTVER_ERR					(JBERR_BASE|0x0D)			//程序版本过低，无法校验升级文件
#define	JBERR_CPUTYPE_ERR					(JBERR_BASE|0x0E)			//升级文件不适用于此CPU类型的主机
#define	JBERR_ERROR_10054					(JBERR_BASE|0x0F)			//连接被服务器强迫关闭!
#define	JBERR_ERROR_10061					(JBERR_BASE|0x10)			//服务器没有在指定端口打开服务!
#define	JBERR_ERROR_10060					(JBERR_BASE|0x11)			//没有发现指定IP的服务器!
#define	JBERR_ERROR_10065					(JBERR_BASE|0x12)			//网络未准备好!
#define	JBERR_INITSURFACE					(JBERR_BASE|0x13)			//初始化显示表面错误
#define	JBERR_UNSUPPORT						(JBERR_BASE|0x14)			//服务器不支持此功能
#define JBERR_TALK_REJECTED					(JBERR_BASE|0x15)			//对讲请求被服务器拒绝
#define JBERR_TALK_INITAUDIO				(JBERR_BASE|0x16)			//启动对讲时音频初始化失败
#define JBERR_OPEN_FILE						(JBERR_BASE|0x17)			//打开文件错
#define JBERR_BIND_PORT						(JBERR_BASE|0x18)			//绑定本地端口失败
#define JBERR_NO_FILE						(JBERR_BASE|0x19)			//没有找到文件
#define JBERR_NOMORE_FILE					(JBERR_BASE|0x1A)			//没有更多文件
#define	JBERR_FILE_FINDING					(JBERR_BASE|0x1B)			//正在查找
#define JBERR_DISK_NOTEXIST					(JBERR_BASE|0x1C)			//格式化/分区的硬盘不存在
#define JBERR_FILE_ERROR					(JBERR_BASE|0x1D)			//文件不正确或者不匹配此服务器
#define JBERR_UNINITOBJ						(JBERR_BASE|0x1E)			//对象没有初始化，稍候再试
#define JBERR_UNKNOW_SERVER					(JBERR_BASE|0x1F)			//服务器无法识别
#define JBERR_CHANNEL_NOT_OPEN				(JBERR_BASE|0x20)			//通道没有打开，操作失败
#define JBERR_INVALID_FILE					(JBERR_BASE|0x21)			//
#define JBERR_ENCRYPT_IC_NO_FIND			(JBERR_BASE|0x22)			//服务器没有找到加密IC
#define JBERR_ENCRYPT_IC_NO_MATCH			(JBERR_BASE|0x23)			//加密IC不匹配
#define JBERR_RTSP_GET_DESCRIBE				(JBERR_BASE|0x24)			//获取RTSP描述失败
#define	JBERR_RTSP_SETUPAUDIO				(JBERR_BASE|0x25)			//RTSP设置音频失败
#define	JBERR_RTSP_SETUPVIDIO				(JBERR_BASE|0x26)			//RTSP设置视频失败
#define	JBERR_RTSP_NOSTREAM					(JBERR_BASE|0x27)			//RTSP没有流数据
#define	JBERR_RTSP_PLAY						(JBERR_BASE|0x28)			//RTSP播放启动失败
#define JBERR_IP_ERROR						(JBERR_BASE|0x29)			//本地IP错误，不能连接指定服务器
#define JBERR_SERVER_UPDATAING				(JBERR_BASE|0x2A)			//服务器正在升级，不接受客户端的连接操作
/************************************************************************/
/* 消息定义		                                                        */
/************************************************************************/
#define  JB_MSG_VIDEOLOST					0x20000001  //视频丢失
#define  JB_MSG_MOVEDETECT                  0x20000002  //移动报警
#define  JB_MSG_SENSOR_ALARM                0x20000003  //探头报警
#define  JB_MSG_RESETSERVER                 0x20000004  //服务器因为某些参数被改变，将要重新启动
#define  JB_MSG_JPEGSNAP                    0x20000005  //JPEG抓图
#define  JB_MSG_UPGRADE                     0x20000006  //升级进度通知
#define  JB_MSG_CRCERROR                    0x20000007  //升级CRC错
#define  JB_MSG_SERVER_BUSY                 0x20000008  //服务器忙，设置失败
#define  JB_MSG_SERVER_BREAK                0x20000009  //服务器中断连接
#define  JB_MSG_CHANNEL_BREAK               0x2000000A  //通道中断连接
#define  JB_MSG_TALK_REQUEST				0x2000000B	//远程服务器请求对讲
#define  JB_MSG_UPGRADEOK            		0x2000000C  //升级完成
#define	 JB_MSG_VIDEORESUME					0x2000000D	//视频恢复
#define	 JB_MSG_COMDATA						0x2000000E	//串口数据
#define	 JB_MSG_USERDATA					0x2000000F	//用户数据
#define	 JB_MSG_DISK_REMOVE					0x20000010	//磁盘被探出或移出
#define  JB_MSG_ALARM_SNAP					0x20000011 
#define	 JB_MSG_FILE_DATA					0x20000012	//前端发回的文件，附加结构为：JBNV_DVR_FILE_DATA
#define	 JB_MSG_DISK_ERROR					0x20000013	//磁盘错，文件不可读写。
#define  JB_MSG_TEL_ALARM					0x20000014	//电话告警报警
#define  JB_MSG_CHANNEL_RECONN_SUCCESS		0x20000015	//通道连接成功
#define  JB_MSG_ITEV_ALART					0x20000016	//入侵报警
#define  JB_MSG_ITEV_ANOMALVIDEO_ALART		0x20000017	//视频异常
#define  JB_MSG_ITEV_TRIPWIRE_ALART			0x20000018	//絆线报警
#define  JB_MSG_ITEV_RESUME					0x20000019	//入侵报警清除





//Add 2009-02-24
#define  JB_MSG_TEMPHUM_LOST_ALARM			0x20000015	//TempHum Device is Off
#define  JB_MSG_TEMPHUM_TEMP_LOWER			0x20000016	//TempHum Temp is Lower
#define  JB_MSG_TEMPHUM_TEMP_UPPER			0x20000017	//TempHum Temp is Upper
#define  JB_MSG_TEMPHUM_HUM_LOWER			0x20000018	//TempHum Hum is Lower
#define  JB_MSG_TEMPHUM_HUM_UPPER			0x20000019	//TempHum Hum is Upper
#define	 JB_MSG_POWER_220V_OFF				0x2000001A	//220V Power is Off
#define	 JB_MSG_POWER_48V_OFF				0x2000001B	//220V Power is Off
#define	 JB_MSG_POWER_DEVICE_LOST			0x2000001C  //Power Device is Off

#define  JB_MSG_FILE_NAME_DATA				0x2000001D //前端发回的文件名  附加结构：JBNV_FILE_DATA_INFO
#define	 JB_MSG_ERROR_DEVICE				0x2000001E //不支持的前端设备

#define	 JB_MSG_IVS_DATA					0x2000001F //烟火报警
#define	 JB_MSG_SENSOR_RESUME				0x20000020 //探头报警恢复
#define	 JB_MSG_SERVER_LINK_OK              0x20000021 //服务器连接成功

//FTP上传时，可能出现的错误号。
#define JBERR_FTP_INVALID_PARAM					0x32000001
#define JBERR_FTP_CONNECT						0x32000002
#define JBERR_FTP_USERPASS						0x32000003
#define JBERR_FTP_NOSUPPORT						0x32000004
#define JBERR_FTP_CHANGEDIR						0x32000005
#define JBERR_FTP_PASVMODE						0x32000006
#define JBERR_FTP_DATACONNECT					0x32000007
#define JBERR_FTP_ALLOCSPACE					0x32000008
#define JBERR_FTP_STORFILE						0x32000009
#define JBERR_FTP_SENDDATA						0x3200000A
#define JBERR_FTP_MKDIR							0x3200000B

//发送EMAIL时，可能出现的错误
#define JBERR_EMAIL_INVALID_SERVER_ADDRESS		0x33000001
#define JBERR_EMAIL_CONNECT_FAILED				0x33000002
#define JBERR_EMAIL_SEND_LOGIN					0x33000003
#define JBERR_EMAIL_SEND_USERNAME				0x33000004
#define JBERR_EMAIL_SEND_PASSWORD				0x33000005
#define JBERR_EMAIL_GET_HOSTNAME				0x33000006
#define JBERR_EMAIL_SERVER_REJECT				0x33000007
//读写前端磁盘时，可能出现的错误
#define	JBERR_RECORD_DISK_READONLY				0x34000001	//磁盘错，文件不可读写。
/************************************************************************/
/* 云台指令                                                             */
/************************************************************************/

#define PTZ_CMD_UP				1
#define	PTZ_CMD_DOWN			2
#define	PTZ_CMD_LEFT			3
#define	PTZ_CMD_RIGHT			4
#define	PTZ_CMD_FOCUS_SUB		5		//Focus Far
#define	PTZ_CMD_FOCUS_ADD		6		//Focus Near
#define	PTZ_CMD_ZOOM_SUB		7		//Zoom Wide
#define	PTZ_CMD_ZOOM_ADD		8		//Zoom Tele
#define	PTZ_CMD_IRIS_SUB		9		//Iris Close
#define	PTZ_CMD_IRIS_ADD		10		//Iris Open
#define	PTZ_CMD_STOP			11
#define	PTZ_CMD_PRESET			12		//预置
#define	PTZ_CMD_CALL			13		//调用

#define	PTZ_CMD_AUTO_STRAT		14		//自动
#define	PTZ_CMD_AUTO_STOP		15
#define	PTZ_CMD_LIGHT_OPEN		16		//灯光
#define	PTZ_CMD_LIGHT_CLOSE		17		
#define	PTZ_CMD_BRUSH_START		18		//雨刷
#define	PTZ_CMD_BRUSH_STOP		19		
#define	PTZ_CMD_TRACK_START		20		//轨迹
#define	PTZ_CMD_TRACK_STOP		21
#define	PTZ_CMD_TRACK_RUN		22



#define PTZCMD_UP				1
#define	PTZCMD_DOWN			2
#define	PTZCMD_LEFT				3
#define	PTZCMD_RIGHT			4
#define	PTZCMD_FOCUS_SUB			5
#define	PTZCMD_FOCUS_ADD			6
#define	PTZCMD_ZOOM_SUB			7
#define	PTZCMD_ZOOM_ADD			8
#define	PTZCMD_IRIS_SUB			9
#define	PTZCMD_IRIS_ADD			10
#define	PTZCMD_LMAP			11
#define	PTZCMD_BRUSH			12
#define	PTZCMD_PRESET			13
#define	PTZCMD_CALL				14
#define	PTZCMD_AUTO			15
#define	PTZCMD_STOP				16
#define	PTZCMD_TRACK_CALL		17
#define	PTZCMD_KEYFN			18
#define	PTZCMD_AUTOSTOP			19
#define	PTZCMD_LIGHT			20
#define	PTZCMD_RAIN				21
#define	PTZCMD_TRACK_START		22
#define	PTZCMD_TRACK_STOP		23
#define	PTZCMD_TRACK_RUN			24
#define	PTZCMD_IO				25
#define	PTZCMD_IO_STOP			26



/************************************************************************/
/* 结构定义			                                                    */
/************************************************************************/
// 消息结构      
typedef struct tagJB_SERVER_MSG{
	DWORD		dwMsg;		//消息类型代码
	DWORD		dwChannel;	//通道
	SYSTEMTIME	st;			//服务器时间
	DWORD		cbSize;		//附加数据长度
}JB_SERVER_MSG,*PJB_SERVER_MSG;

/************************************************************************/
/* 设置视频服务器参数命令                                               */
/************************************************************************/
#define		CMD_REBOOT					0x00000001		//Param:
#define		CMD_RESTORE					0x00000002		//Param:
#define		CMD_UPDATEFLASH				0x00000003		//Param:
#define		CMD_SNAPSHOT				0x00000004		//Param:int
#define		CMD_SETSYSTIME				0x00000005		//Param:SYSTEMTIME
#define		CMD_SET_OSDINFO				0x00000006		//Param:JB_CHANNEL_OSDINFO
#define		CMD_SET_SHELTER				0x00000007		//Param:JB_CHANNEL_SHELTER
#define		CMD_SET_LOGO				0x00000008		//Param:JB_CHANNEL_LOGO
#define		CMD_SET_CHANNEL_CONFIG		0x00000009		//Param:JB_CHANNEL_CONFIG
#define		CMD_SET_COLOR				0x0000000A		//Param:JB_CHANNEL_COLOR
#define		CMD_SET_MOTION_DETECT		0x0000000B		//Param:JB_CHANNEL_MOTION_DETECT
#define		CMD_SET_SENSOR_ALARM		0x0000000C		//Param:JB_SENSOR_ALARM
#define		CMD_SET_VIDEO_LOST			0x0000000D		//Param:JB_CHANNEL_VIDEO_LOST
#define		CMD_SET_COMINFO				0x0000000E		//Param:JB_SERVER_COMINFO
#define		CMD_SET_USERINFO			0x0000000F		//Param:JB_SERVER_USER
#define		CMD_SET_NETWORK				0x00000010		//Param:JB_SERVER_NETWORK
#define		CMD_UPLOAD_PTZ_PROTOCOL		0x00000011		//Param:JB_UPLOAD_PTZ_PROTOCOL
#define		CMD_SEND_COMDATA			0x00000012		//Param:JB_COM_DATA
#define		CMD_SET_FTPUPDATA_PARAM		0x00000013		//Param:JB_FTPUPDATA_PARAM
#define		CMD_CLEAR_ALARM_OUT			0x00000014		//Param:
#define		CMD_SET_SERVER_COM2			0x00000015		//Param:JB_SERVER_COM2INFO
#define		CMD_SET_ALARM_OUT			0x00000016		//Param:JBNV_ALARM_OUT_INFO
#define		CMD_SET_NOTIFY_SERVER		0x00000017		//Param:JB_NOTIFY_SERVER
#define		CMD_SET_PPPOE_DDNS			0x00000018		//Param:JB_PPPOE_DDNS_CONFIG
#define		CMD_SET_SENSOR_STATE		0x00000019		//Param:JBNV_SENSOR_STATE
//Add 2007-08-30
#define		CMD_SET_SERVER_RECORD		0x00000020		//Param:JB_SERVER_RECORD_SET
#define		CMD_RECORD_BEGIN			0x00000021		//Param:
#define		CMD_RECORD_STOP				0x00000022		//Param:
//Add 2007-09-17
#define		CMD_SET_CENTER_INFO			0x00000023		//Param:JB_CENTER_INFO
#define		CMD_UPDATE_CENTER_LICENCE	0x00000024
//Add 2008-01-14
#define		CMD_SET_CHANNEL_ALARM_CONFIG 0x00000025		//Param:JB_CHANNEL_ALARM_CONFIG
//Add 2008-05-14
#define		CMD_SET_EMAIL_PARAM			0x00000026		//Param:JBNV_EMAIL_PARAM
//Add 2008-07-07
#define		CMD_SET_COMMODE				0x00000027		//Param:JBNV_SERVER_COMMODE
#define		CMD_SET_3322DDNS			0x00000028		//Param:JBNV_3322DDNS_CONFIG
#define		CMD_STOP_FILE_DOWNLOAD		0x00000029
//Add 2008-08-20	
#define		CMD_SET_NVD_SENSOR_ALARM	0x0000002A		//Param:JB_NVD_SENSOR_ALARM_SET

//Add 2008-11-25
#define     CMD_SET_WIFI				0x00000046		//Param:JB_WIFI_CONFIG
#define     CMD_SET_TDSCDMA				0x00000047		//Param:JB_TDSCDMA_CONFIG
#define		CMD_SET_PERIPH_CONFIG		0x00000048		//Param:JB_PERIPH_CONFIG
#define		CMD_SET_TEL_ALARM			0x00000049		//Param:JB_TEL_ALARM_SET
//Add 2009-02-24
#define		CMD_SET_TEMPHUM_SENSOR		0x0000004A		//Param:JB_TEMP_HUM_SENSOR_CONFIG
#define		CMD_SET_POWER_DEVICE		0x0000004B		//Param:JB_POWER_DEVICE_CONFIG

#define		CMD_SET_RECORD_CONFIG		0x0000004C		//Param:JB_SERVER_RECORD_CONFIG
#define  	CMD_SET_UPNP				0x0000004D  	//Param:JB_UPNP_CONFIG
#define		CMD_SET_PLAYBACK_NAME		0x0000004E		//Param: char *csPlayBackFileName
#define		CMD_SET_PLAYBACK_TIME		0x0000004F		//Param:JBNV_TIME
#define		CMD_PLAYBACK_VODACTION		0x00000050		//Param:JBNV
#define		CMD_SET_MOBILE_CENTER		0x00000051		//Param:JB_MOBILE_CENTER_INFO
#define		CMD_SET_CHANNEL_SUBSTREAM_CONFIG 0x00000052	//Param:JB_CHANNEL_CONFIG

#define		CMD_FDISK_DISK				0x00000061		//Param:JBNV_FDISK_DISK
#define		CMD_FORMAT_DISK				0x00000062		//Param:JBNV_FORMAT_DISK

//Added 2011-12-20
#define CMD_REQUEST_IFRAME				0x00000063 //Param:JB_CHANNEL_FRAMEREQ

#define CMD_SET_CENTER_INFO_EX			0x00000064 //Param:JBNV_NXSIGHT_SERVER_ADDR_EX
#define CMD_GET_CENTER_INFO_EX			0x00000065 //Param:JBNV_NXSIGHT_SERVER_ADDR_EX

#define CMD_SET_AUDIO_PARA				0x00000066 //Param:HI_CFG_AUDIO_ATTR_S
#define CMD_GET_AUDIO_PARA				0x00000067 //Param:HI_CFG_AUDIO_ATTR_S

#define CMD_FORMAT_DISK_NEW				0x00000068 //Param:HI_HDI_FORMAT

/************************************************************************/
/*获取服务器信息                                                        */
/************************************************************************/
#define		CMD_GET_SYSTIME				0x10000000		//Param:SYSTEMTIME
#define		CMD_GET_OSDINFO				0x10000001		//Param:JB_CHANNEL_OSDINFO
#define		CMD_GET_CHANNEL_CONFIG		0x10000002		//Param:JB_CHANNEL_CONFIG
#define		CMD_GET_COLOR				0x10000003		//Param:JB_CHANNEL_COLOR
#define		CMD_GET_MOTION_DETECT		0x10000004		//Param:JB_CHANNEL_MOTION_DETECT
#define		CMD_GET_SENSOR_ALARM		0x10000005		//Param:JB_SENSOR_ALARM
#define		CMD_GET_VIDEO_LOST			0x10000006		//Param:JB_CHANNEL_VIDEO_LOST
#define		CMD_GET_COMINFO				0x10000007		//Param:JB_SERVER_COMINFO
#define		CMD_GET_USERINFO			0x10000008		//Param:JB_SERVER_USER
#define		CMD_GET_NETWORK				0x10000009		//Param:JB_SERVER_NETWORK
#define		CMD_GET_FTPUPDATA_PARAM		0x1000000A		//Param:JB_FTPUPDATA_PARAM
#define		CMD_GET_PTZDATA				0x1000000B		//Param:JB_PTZ_PROTOCOL
#define		CMD_GET_SERVER_COM2			0x1000000C		//Param:JB_SERVER_COM2INFO
#define		CMD_GET_ALARM_OUT			0x1000000D		//Param:JBNV_ALARM_OUT_INFO
#define		CMD_GET_NOTIFY_SERVER		0x1000000E		//Param:JB_NOTIFY_SERVER
#define		CMD_GET_PPPOE_DDNS			0x1000000F		//Param:JB_PPPOE_DDNS_CONFIG
#define		CMD_GET_SENSOR_STATE		0x10000010		//Param:JBNV_SENSOR_STATE
//Add 2007-08-30
#define		CMD_GET_SERVER_RECORD_SET	0x10000011		//Param:JB_SERVER_RECORD_SET
#define		CMD_GET_SERVER_RECORD_STATE	0x10000012		//Param:JB_SERVER_RECORD_STATE
#define		CMD_UNLOAD_DISK				0x10000013		//Param:
//Add 2007-09-17
#define		CMD_GET_CENTER_INFO			0x10000014		//Param:JB_CENTER_INFO

//Add 2008-01-14
#define		CMD_GET_CHANNEL_ALARM_CONFIG	0x10000015	//Param:JB_CHANNEL_ALARM_CONFIG
#define		CMD_GET_CENTER_LICENCE		0x10000016		
//Add 2008-05-04
#define		CMD_GET_SERVER_STATUS		0x11000001		//Param:JB_SERVER_STATE	
//Add 2008-05-14
#define		CMD_GET_EMAIL_PARAM			0x10000017		//Param:JBNV_EMAIL_PARAM
//Add 2008-07-07
#define		CMD_GET_COMMODE				0x10000018		//Param:JBNV_SERVER_COMMODE
#define		CMD_GET_3322DDNS			0x10000019		//Param:JBNV_3322DDNS_CONFIG
//Add 2008-07-28
#define		CMD_GET_DIRECT_LIST			0x1000001A		//Param:JBNV_DIRECTORY_LIST
#define		CMD_GET_FILE_DATA			0x1000001B		//Param:char[64]
//Add 2008-08-20	
#define		CMD_GET_NVD_SENSOR_ALARM	0x1000001C		//Param:JB_NVD_SENSOR_ALARM_SET
//Add 2008-11-25
#define     CMD_GET_WIFI				0x10000046		//Param:JB_WIFI_CONFIG
#define     CMD_GET_TDSCDMA				0x10000047		//Param:JB_TDSCDMA_CONFIG
//Add 2008-12-22
#define		CMD_GET_PERIPH_CONFIG		0x10000048		//Param:JB_PERIPH_CONFIG
#define		CMD_GET_TEL_ALARM			0x10000049		//Param:JB_TEL_ALARM_SET
//Add 2009-02-24
#define		CMD_GET_TEMPHUM_SENSOR		0x1000004A		//Param:JB_TEMP_HUM_SENSOR_CONFIG
#define		CMD_GET_POWER_DEVICE		0x1000004B		//Param:JB_POWER_DEVICE_CONFIG

#define		CMD_GET_RECORD_CONFIG		0x1000004C		//Param:JB_SERVER_RECORD_CONFIG
#define		CMD_GET_UPNP				0x1000004D		//Param:JB_UPNP_CONFIG
#define		CMD_GET_FILELIST			0x1000004E		//Param:JBNV_FIND_FILE_RESP
#define		CMD_GET_MOBILE_CENTER		0x10000051		//Param:JB_MOBILE_CENTER_INFO
#define		CMD_GET_CHANNEL_SUBSTREAM_CONFIG 0x10000052	//Param:JB_CHANNEL_CONFIG

#define		CMD_GET_DISK_INFO			0x10000060			//Param:JBNV_DISK_INFO
#define		CMD_GET_FORMAT_STATE		0x10000061			//Param:JBNV_FORMAT_STATUS

/************************************************************************/
/* 可以通过SDK获取的服务器信息                                          */
/************************************************************************/
//用户权限定义
#define		USER_RIGHT_PTZ			0x0001		//控云台
#define		USER_RIGHT_SETUP		0x0002		//设置
#define		USER_RIGHT_UPDATE		0x0004		//升级

/************************************************************************/
/* 服务器功能定义                                                       */
/************************************************************************/
#define	JB_SYS_FLAG_ENCODE_D1			0x00000001	//支持D1
#define	JB_SYS_FLAG_HD_RECORD			0x00000002	//支持IDE录像
#define	JB_SYS_FLAG_CI_IDENTIFY			0x00000004	//支持智能识别
#define	JB_SYS_FLAG_MD_RECORD			0x00000008	//支持MD卡、U盘录像
#define JB_SYS_FLAG_DECODE_MPEG4		0x00000010	//支持解码MPEG4
#define JB_SYS_FLAG_DECODE_H264			0x00000020	//支持解码H264
#define JB_SYS_FLAG_ENCODE_SXGA			0x00000040	//支持高清1280*1024或1280*800

#define JB_SYS_FLAG_VIDEO_ALARM_MODE2	0x00010000  //报警时,支持第二种模式
#define JB_SYS_FLAG_FTPUP				0x00020000	//支持FTP上传
#define JB_SYS_FLAG_EMAIL				0x00040000	//支持EMAIL上传
#define JB_SYS_FLAG_WIFI			0x00080000	//支持Wireless
#define JB_SYS_FLAG_PERIPH				0x00100000	//支持气体探测器
#define JB_SYS_FLAG_TELALARM			0x00200000	//支持电话报警
#define JB_SYS_FLAG_TEMPHUM				0x00400000	//支持温湿度，电源

#define JB_SYS_FLAG_UPNP				0x00800000
#define DMS_SYS_FLAG_PLATFORM           0x01000000 /* 支持平台功能*/
#define JB_SYS_FLAG_3G					0x02000000 /* 3G */

/************************************************************************/
/* 服务器类型定义                                                       */
/************************************************************************/
#define JB_NVS_FLAG			100001	//网络视频编码器
#define JB_NVD_FLAG			100002	//网络视频解码器
#define JB_DVR_FLAG			100003	//网络视频编码器（带硬盘）
#define DMS_IPCAM_FLAG		100004	//

#define DMS_DVR_D3_0001_FLAG	0x10D30001 // D3初版设备
#define DMS_DVR_D2_0001_FLAG	0x10D30002 // D3初版设备


//CPU类型
#define	CPUTYPE_8120		8120
#define	CPUTYPE_3510		3510
#define	CPUTYPE_3520		3520

//服务器基础信息
typedef struct tagJBNV_SERVER_INFO
{
	DWORD		dwSize;				//结构大小
	DWORD		dwServerFlag;		//服务器类型
	DWORD		dwServerIp;			//服务器IP(整数表示形式)
	char		szServerIp[16];		//服务器IP(字符串表示形式)
	WORD		wServerPort;		//服务器端口
	WORD		wChannelNum;		//通道数量
	DWORD		dwVersionNum;		//版本
	char		szServerName[32];	//服务器名称
	DWORD		dwServerCPUType;	//当前CPU类型
	BYTE		bServerSerial[48];	//服务器序列号，具有唯一标识功能
	BYTE		byMACAddr[6];		//服务器的物理地址
	DWORD		dwAlarmInCount;
	DWORD		dwAlarmOutCount;
	DWORD		dwSysFlags;			//系统支持的功能
	DWORD		dwUserRight;		//当前用户权限
	DWORD		dwNetPriviewRight;	//网络观看权限
	DWORD		dwCompany;
	char		csServerDes[60];
}JBNV_SERVER_INFO,*PJBNV_SERVER_INFO;

//音频编码类型
#define	 WAVE_FORMAT_ALAW						0x0006 
#define  WAVE_FORMAT_MPEGLAYER3                 0x0055
#define	 WAVE_FORMAT_G722_ADPCM					0x0065
#define	 WAVE_FORMAT_G711A						0x003E
#define	 WAVE_FORMAT_ADPCM						0x0002
#define	 WAVE_FORMAT_G726_ADPCM					0x0064		//海思编码的ADPCM
//服务器流信息
typedef struct tagJBNV_CHANNEL_INFO
{
    DWORD   dwSize;
    DWORD   dwStream1Height;	//视频高(1)
    DWORD   dwStream1Width;		//视频宽
	DWORD   dwStream1CodecID;	//视频编码类型号（MPEG4为0，JPEG2000为1,H264为2）
    DWORD   dwStream2Height;	//视频高(2)
    DWORD   dwStream2Width;		//视频宽
    DWORD   dwStream2CodecID;	//视频编码类型号（MPEG4为0，JPEG2000为1,H264为2）
    DWORD   dwAudioChannels;	//音频通道数
    DWORD   dwAudioBits;		//音频比特率
    DWORD   dwAudioSamples;		//音频采样率
    DWORD   dwWaveFormatTag;	//音频编码类型号
	char	csChannelName[32];	//通道名称
}JBNV_CHANNEL_INFO,*PJBNV_CHANNEL_INFO;

#define MAX_SENSOR_IN	16
#define MAX_SENSOR_OUT	16
#define MAX_SENSOR_INOUT	(MAX_SENSOR_IN +MAX_SENSOR_OUT)

//探头报警参数
//探头种类列表：
//0x0001 红外对射探头
//0x0002 户外探头
//0x0003 气体探头
//0x0004 门磁探头
//0x0005 玻璃破碎感应
//0x0006 有线红外探头
//0x0007 脚踏开关
//0x0008 烟感探头
//0x0009 手按开关
//0x000A 音频监听探头

//输出种类：
//0x0001 自动拨号器
//0x0002 蜂鸣器
//0x0003 灯具开关
//0x0004 机械开关
typedef struct tagJBNV_SENSOR_INFO
{
	DWORD	dwSize;
	DWORD	dwIndex;				//探头索引
	DWORD	dwSensorType;			//探头类型
	char	csSensorName[32];		//探头名称
}JBNV_SENSOR_INFO,*PJBNV_SENSOR_INFO;

//服务器状态
typedef struct tagJB_SERVER_STATE
{
	DWORD	dwSize;
	DWORD	dwAlarmInState;			//告警输入状态
	DWORD	dwAlarmOutState;		//告警输出状态
	DWORD	dwVideoState;			//视频状态
	DWORD	dwServerError;			//服务器错误信息
	DWORD	dwLinkNum;				//客户端连接的个数
	DWORD	dwClientIP[10];			//客户端的IP地址
}JB_SERVER_STATE,*LPJB_SERVER_STATE;
/************************************************************************/
/* 服务器配置信息结构                                                   */
/************************************************************************/

/*--------------------------通道设置结构--------------------------------*/
//通道OSD显示以及通道名称设置
typedef struct tagJB_CHANNEL_OSDINFO
{
	DWORD	dwSize;
	DWORD	dwChannel;
	BOOL	bShowTime;
	DWORD	dwTimeFormat;
			/*
			0 XXXX-XX-XX (年月日)
			1 XX-XX-XXXX (月日年)
			2 XXXX年XX月XX日
			3 XX月XX日XXXX年
			4 XX-XX-XXXX 日月年
			5 XX日XX月XXXX年
			*/
	BOOL	bShowString;		//是否显示用户输入字符串
	DWORD	dwStringx;			//x,字符显示位置，以D1大小为准，系统根据当前输出自动进行调整
	DWORD	dwStringy;			//y
	char	csString[48];		//用户输入字符串
	char	csOsdFontName[32];	//OSD叠加显示要使用的字体类型。
}JB_CHANNEL_OSDINFO,*LPJB_CHANNEL_OSDINFO;

//通道设置。
typedef struct tagJB_CHANNEL_CONFIG
{
	DWORD	dwSize;
	DWORD	dwChannel;			//通道号
	DWORD	nFrameRate;			//帧率 (1-25/30) PAL为25，NTSC为30
	DWORD	nStandard; 			//制式 (0为NTSC制,1为PAL制)
	DWORD	dwRateType;			//流模式(0为定码流，1为变码流)
	DWORD	dwStreamFormat;		//格式 (0为CIF,1为D1,2为HALF-D1,3为QCIF)
	DWORD	dwBitRate;			//码率 (16000-4096000)
	DWORD	dwImageQuality;		//编码质量(0-4),0为最好
	DWORD	nMaxKeyInterval;	//关键帧间隔(1-100)
	BOOL	bEncodeAudio;		//是否编码音频
	char	csChannelName[32];	//通道名称
}JB_CHANNEL_CONFIG,*LPJB_CHANNEL_CONFIG;

//通道颜色设置
typedef struct tagJB_CHANNEL_COLOR
{
	DWORD	dwSize;
	DWORD	dwChannel;
	DWORD	dwSetFlag;		//0,设置但不保存;1,保存参数;2,恢复上一次保存的
	DWORD	dwHue;			//色调
	DWORD	dwColor;		//色彩
	DWORD	dwContrast;		//对比度
	DWORD	dwBrightness;	//亮度
	DWORD	dwDefinition;	//清晰度
}JB_CHANNEL_COLOR,*PJB_CHANNEL_COLOR;

//以下两个结构只支持设置
//LOGO叠加设置
//LOGO设置暂不支持
#pragma warning( disable:4200 )
typedef struct tagJB_CHANNEL_LOGO
{
	DWORD	dwSize;
	DWORD	dwChannel;
	BOOL	bEnable;		//是否启用LOGO显示
	DWORD	dwLogox;		//LOGO显示起始位置，以D1为准
	DWORD	dwLogoy;
	BYTE	bLogoData[];	//此LOGO数据可以调用...获得。最大限制为40K
}JB_CHANNEL_LOGO;
#pragma warning( default:4200 )

//遮挡区域设置
typedef struct tagJB_CHANNEL_SHELTER
{
	DWORD	dwSize;
	DWORD	dwChannel;
	BOOL	bEnable;		//是否进行区域遮挡
	RECT	rcShelter[5];	//遮挡区域，最多支持5块的区域遮挡。RECT以D1为准
}JB_CHANNEL_SHELTER,*PJB_CHANNEL_SHELTER;

//请求关键帧
typedef struct tagJB_CHANNEL_FRAMEREQ
{
	DWORD	dwSize;
	DWORD	dwChannel;
	DWORD	dwStreamType;
	DWORD	dwFrameType;		// 0 - I，其余保留
}JB_CHANNEL_FRAMEREQ, *PJB_CHANNEL_FRAMEREQ;

//告警相关结构。
typedef struct tagJB_SET_TIME{
	WORD	wHour;				//(0-23)
	WORD	wMinute;			//(0-59)
}JB_SET_TIME;

//布防时间段
typedef struct tagJB_SCHED_TIME
{
	BOOL		bEnable;		//是否启用该时间段
	JB_SET_TIME	BeginTime1;		//时间段1
	JB_SET_TIME	EndTime1;
	JB_SET_TIME	BeginTime2;		//时间段2
	JB_SET_TIME	EndTime2;
}JB_SCHED_TIME;

//所有告警和图象抓拍均自动上传到客户端，不许要进行设置。
//视频移动告警
typedef struct tagJB_CHANNEL_MOTION_DETECT{
	DWORD			dwSize;
	DWORD			dwChannel;				//通道号
	BOOL			bEnable;				//是否进行布防
	DWORD			nDuration;				//报警IO端口输出持续时间(秒)
	BOOL			bShotSnap;				//是否自动抓图
	BOOL			bAlarmIOOut[4];			//探头输出
	DWORD			dwSensitive;			//灵敏度
	JB_SCHED_TIME	jbScheduleTime[8];		//布防时间段，星期一到星期天、每日。
	BYTE			pbMotionArea[44*36];	//布防区域块组.布防区域共有44*36个块,每一个块分别用一个
}JB_CHANNEL_MOTION_DETECT,*PJB_CHANNEL_MOTION_DETECT;

typedef struct tagJB_PRESET_CHANNEL{
	WORD	wPresetPoint1;
	WORD	wPresetPoint2;
}JB_PRESET_CHANNEL;

//探头输入告警
typedef struct tagJB_SENSOR_ALARM
{
	DWORD			dwSize;
	int				nSensorID;				//探头索引
	DWORD			dwSensorType;			//探头类型
	char			szSensorName[32];		//探头名称
	BOOL			bEnable;				//是否进行布防
	int				nDuration;				//报警IO端口输出持续时间(秒)
	BOOL			bAlarmIOOut[4];			//探头联动输出
	JB_PRESET_CHANNEL PresetChannel[4];	//当发生告警时，是否进行云台预置点1操作
	JB_SCHED_TIME	jbScheduleTime[8];		//布防时间
	BOOL			bSnapShot;				//发生告警时，是否抓图
	int				nCaptureChannel;		//报警时，进行抓图动作的通道
	BOOL			bReQuestTalkback;		//是否请求对讲
}JB_SENSOR_ALARM,*PJB_SENSER_ALARM;

typedef struct tagJBNV_ALARM_OUT
{
	DWORD	dwAlarmOutType;					//告警输出类型
	char	szAlarmOutName[32];				//告警输出名称
}JBNV_ALARM_OUT,*PJBNV_ALARM_OUT;

//告警输出
typedef struct tagJBNV_ALARM_OUT_INFO{
	DWORD	dwSize;
	JBNV_ALARM_OUT jbao[4];					//告警输出，根据探头输出个数决定设置多少
}JBNV_ALARM_OUT_INFO,*PJBNV_ALARM_OUT_INFO;

//视频丢失报警参数
typedef struct tagJB_CHANNEL_VIDEO_LOST
{
	DWORD			dwSize;
	DWORD			dwChannel;					//通道号
	BOOL			bEnable;					//是否进行布防
	int				nDuration;					//报警IO端口输出持续时间(秒)
	BOOL	        bAlarmIOOut[4];				//报警IO输出
	JB_SCHED_TIME   jbScheduleTime[8];			//布防时间段
}JB_CHANNEL_VIDEO_LOST,*PJB_CHANNEL_VIDEO_LOST;

/*--------------------------服务器策略设置结构------------------------------*/
//服务器485线的COM配置
typedef struct tagJB_SERVER_COMINFO
{
	DWORD		dwSize;
	DWORD		dwChannel;		//通道号
	DWORD		dwBaudRate;		//波特率
				/*1200,2400,4800,9600,19200,38400,43000,56000,57600,115200*/
	int			nDataBits;		//数据位
	int			nStopBits;		//停止位
	int			nParity;		//校验位
	int			nStreamControl;	//流控制
	int			nPrePos;		//云台预置位
	int			nCruise;		//云台巡航
	int			nTrack;			//云台轨迹
	int			nPTZSpeed;		//云台速度
	int			nAddress;		//云台地址
	char		szPTZName[32];	//云台协议名称
}JB_SERVER_COMINFO,*PJB_SERVER_COMINFO;


typedef struct tagJB_SERVER_COM2INFO
{
	DWORD		dwSize;
	DWORD		dwChannel;		//通道号
	DWORD		dwBaudRate;		//波特率
	int			nDataBits;		//数据位
	int			nStopBits;		//停止位
	int			nParity;		//校验位
	int			nStreamControl;	//流控制
	BOOL		bTransferState;	//透明传输
}JB_SERVER_COM2INFO,*PJB_SERVER_COM2INFO;

//云台协议
typedef struct tagJB_PTZ_PROTOCOL{
	DWORD		dwSize;
	DWORD		dwChannel;
	char		szPTZName[32];			//协议名称
	char		szPTZData[4 * 1024];	//协议数据
}JB_PTZ_PROTOCOL,*PJB_PTZ_PROTOCOL;

#pragma warning( disable :4200 )
//直接通过COM口收发数据
typedef struct tagJB_COM_DATA
{
	DWORD		dwSize;
	DWORD		dwChannel;
	BOOL		bIs485;//485 or 232
	char		DataBuf[];				//最大128
}JB_COM_DATA;
#pragma warning( default:4200 )

//网络地址
typedef struct tagJB_SERVER_NETWORK
{
	DWORD		dwSize;
	DWORD		dwNetIpAddr;			//IP地址
	DWORD       dwNetMask;				//掩码
	DWORD       dwGateway;				//网关
	BYTE		bEnableDHCP;			//
	BYTE		bSetDNS;
	BYTE		bReserve;				//保留
	BYTE		bVideoStandard;			//0 - NTSC, 1 - PAL
	DWORD       dwHttpPort;				//Http端口
	DWORD       dwDataPort;				//数据端口
	DWORD		dwDNSServer;			//DNS服务器
	DWORD		dwTalkBackIp;			//服务器告警时，自动连接的对讲IP
	char        szMacAddr[6];			//网卡MAC地址
	char		szServerName[32];		//服务器名称
}JB_SERVER_NETWORK,*PJB_SERVER_NETWORK;



//用户设置
typedef struct tagJB_SERVER_USER{
	DWORD		dwSize;
	DWORD		dwIndex;			//最多5个用户，第一个默认名称为Admin.
	BOOL		bEnable;			//是否启用
	char		csUserName[32];
	char		csPassword[32];
	DWORD		dwUserRight;		/* 权限 */
									//0x01: 控制云台
									//0x02: 设置参数
									//0x04: 升级，格式化
	DWORD		dwNetPreviewRight;	//远程可以预览的通道 bit0 -- channel 1
	DWORD		dwUserIP;			//用户IP地址(为0时表示允许任何地址) 
	BYTE		byMACAddr[6];		//物理地址
}JB_SERVER_USER,*PJB_SERVER_USER;

/* ftp上传参数*/
typedef struct tagJB_FTPUPDATA_PARAM
{
	DWORD	dwSize;
	DWORD	dwEnableFTP;			/*是否启动ftp上传功能*/
	char	csFTPIpAddress[32];		/*ftp 服务器*/
	DWORD	dwFTPPort;				/*ftp端口*/
	BYTE	sUserName[32];			/*用户名*/
	BYTE	sPassword[32];			/*密码*/
	WORD 	wTopDirMode;			/*0x0 = 使用设备ip地址,0x1 = 使用设备名,0x2 = OFF*/
	WORD 	wSubDirMode;			/*0x0 = 使用通道号 ,0x1 = 使用通道名,0x2 = OFF*/
//	BYTE 	reservedData[28];		//保留
	BOOL	bAutoUpData;			//是否启用自动上传图片功能
	DWORD	dwAutoTime;				//自动定时上传时间
	DWORD	dwChannel;				//要上传的通道
	BYTE	reservedData[16];		//保留
}JB_FTPUPDATA_PARAM, *LPJB_FTPUPDATA_PARAM;

//在线通知设置
typedef struct tagJB_NOTIFY_SERVER
{
	DWORD		dwSize;
	BOOL		bEnable;			//服务器是否定时发送在线消息给目标主机
	DWORD		dwTimeDelay;		//服务器发送在线消息的间隔时间
	DWORD		dwPort;				//接收服务器在线消息的目标主机端口
	char        szDNS[128];			//接收服务器在线消息的目标主机域名
}JB_NOTIFY_SERVER,*PJB_NOTIFY_SERVER;

typedef struct tagJB_PPPOE_DDNS_CONFIG
{
	DWORD	dwSize;
	BOOL	bEnablePPPOE;				//0-不启用,1-启用
	char	csPPPoEUserName[32];		//PPPoE用户名
	char	csPPPoEPassword[32];		//PPPoE密码
	DWORD	dwPPPoEIP;					//PPPoE IP地址(只读)
	BOOL	bEnableDDNS;				//是否启用DDNS
	CHAR	csDDNSUsername[32];
	CHAR	csDDNSPassword[32];
	char	csDDNSDomain[32];			//在服务器注册的DDNS名称
	char	csDNSAddress[32];			//DNS服务器地址
	DWORD	dwDNSPort;					//DNS服务器端口，默认为6500
}JB_PPPOE_DDNS_CONFIG,*PJB_PPPOE_DDNS_CONFIG;


//告警输出设置
#define		SENSOR_OUT_1			0x0001		//探头1有输出
#define		SENSOR_OUT_2			0x0002		//探头2有输出
#define		SENSOR_OUT_3			0x0004		//探头3有输出
#define		SENSOR_OUT_4			0x0008		//探头4有输出
typedef struct tagJBNV_SENSOR_STATE{
	DWORD	dwSize;
	DWORD	dwSensorID;					//探头ID
	DWORD	dwSensorOut;				//探头输出状态
}JBNV_SENSOR_STATE;

typedef int	(CALLBACK *StreamCallBack)(
					HANDLE hServer,			//服务器句柄
					DWORD dwClientIndex,	//客户窗口索引，客户自定义
					DWORD dwChannelNo,		//服务器通道号，从0开始
					PBYTE pbDataBuffer,		//结构类型为 JB_DATAPACK
					DWORD dwUser);			//用户数据

typedef void (CALLBACK *DrawOSD)(
					HDC hDC,				//回调返回的绘图DC
					SIZE *pImageSize,		//画面大小
					DWORD dwUser);			//用户数据

//视频数据类型
#define		VIDEO_MODE_YUY2		1
#define		VIDEO_MODE_YV12		2
#define		VIDEO_MODE_UYVY		3

typedef void (CALLBACK *VideoCallBack)(
					HANDLE hHandle,
					DWORD dwVideoMode,		//视频数据类型
					DWORD dwWidth,			//当前视频的宽
					DWORD dwHeight,			//当前视频的高
					BYTE *lpData,			//视频数据
					DWORD dwLineLength,		//行长
					DWORD dwUser);			//用户数据


typedef void (CALLBACK *AudioCallBack)(
				    HANDLE hHandle,
				    DWORD dwAudioMode,		//音频数据类型
				    BYTE *lpData,			//音频数据
				    DWORD dwDataLength,		//音频数据长度
					DWORD dwUser);			//用户数据


typedef void(CALLBACK *VoiceDataCallBack)(
					DWORD dwAudioFormat,	//音频数据类型
					BYTE *lpEncode,			//编码后的数据
					int nELength,			//编码后的数据长度
					BYTE *lpPCMWave,		//PCM音频数据
					int nPCMLength,			//PCM音频数据长度
					DWORD dwUser);			//用户数据


typedef void(CALLBACK *SnapShotCallBack)(
					HANDLE hServer,
					DWORD dwChannel,
					BYTE *bPicBuffer,
					DWORD dwPicSize,
					DWORD dwUser);

typedef void(CALLBACK *fStreamCallBackEx)(
					HANDLE hHandle,
					DWORD dwDataType,		// 0(实时预览) :JB_DATAPACK结构类型 1(文件回放):JB_STREAM_BUFFER结构类型
					BYTE *pBuffer,
					DWORD dwBufSize,		//pBuffer 总长度
					DWORD dwUser);

typedef void(CALLBACK *TestResultCallBack)(
				  HANDLE hHandle,
				  BYTE *pBuffer,
				  DWORD dwBufSize,		//pBuffer 总长度
				  DWORD dwUser);


DWORD WINAPI JBNV_OpenServer(LPCSTR lpServerDNS,WORD wServerPort,
				LPCSTR lpszUserName,LPCSTR lpszPassword,LPVOID *lpHandle);
DWORD WINAPI JBNV_SetHDPreviewOptim(HANDLE hServer, BOOL enable);

DWORD WINAPI JBNV_CloseServer(HANDLE hServer);		//关闭服务器
DWORD WINAPI JBNV_GetServerInfo(HANDLE hServer,JBNV_SERVER_INFO *lpsi);	//获取服务器信息
DWORD WINAPI JBNV_SetMessage(HANDLE hServer,HWND hMsgWnd,UINT nMessage);//设置消息回调
DWORD WINAPI JBNV_SetStreamCallBack(HANDLE hServer,StreamCallBack lpscb,DWORD dwUser);//设置数据流回调
DWORD WINAPI JBNV_SetSecondSurface(HANDLE hServer,DWORD dwChannelNo,HWND hDisPlayWnd,DrawOSD pOSD,DWORD dwUser, DWORD dwStreamType);

DWORD WINAPI JBNV_PTZControl(HANDLE hServer,DWORD dwChannelNo,DWORD dwPTZCmd,DWORD dwValue);// 云台控制
DWORD WINAPI JBNV_PTZControlEx(HANDLE hServer,DWORD dwChannelNo,DWORD dwPTZCmd,DWORD dwSpeed,DWORD dwValue);// 云台控制 dwSpeed字段未使用
DWORD WINAPI JBNV_SetServerConfig(HANDLE hServer,DWORD dwCmd,LPVOID lpData,DWORD dwSize);// 配置服务器参数
DWORD WINAPI JBNV_GetServerConfig(HANDLE hServer,DWORD dwCmd,LPVOID lpData,DWORD dwSize);// 获取服务器参数
DWORD WINAPI JBNV_GetChannelInfo(HANDLE hServer,DWORD dwChannelNo,JBNV_CHANNEL_INFO *lpStreamInfo);//得到流信息
DWORD WINAPI JBNV_GetSensorInfo(HANDLE hServer,DWORD dwSensorID,	//输入为 0,1,...,15,输出为16,17,...31
								JBNV_SENSOR_INFO *lpSensor);
DWORD WINAPI JBNV_UpdateServer(HANDLE hServer,LPCSTR lpszFileName);
DWORD WINAPI JBNV_SetTestCommand(HANDLE hServer,DWORD dwCmd,LPVOID lpData,DWORD dwSize);// 发送自动测试命令
DWORD WINAPI JBNV_SetTestResultCallBack(HANDLE hServer,TestResultCallBack pTestResult,DWORD dwUser);// 设置测试结果接收回调

//预览操作函数
DWORD WINAPI JBNV_OpenChannel(HANDLE hServer,DWORD dwChannelNo,//服务器端通道
				DWORD dwClientIndex,	//客户窗口索引，客户自定义
				DWORD dwNetProtocol,	//网络协议
				DWORD dwStreamType,		//码流类型，大码流或者小码流
				HWND  hDispWnd,			//显示窗口
				BOOL  bUserDecode,		//客户自己解码
				DWORD dwShowMode,		//显示模式。0为OVERLAY显示模式。1为非OVERLAY显示模式。
				LPVOID *lpHandle);		//当打开通道成功后，lpHandle将被放入通道句柄
DWORD WINAPI JBNV_CloseChannel(HANDLE hChannel);
DWORD WINAPI JBNV_GetRecvCount(HANDLE hChannel,DWORD *pdwRecvCount);//得到网络数据接受量
DWORD WINAPI JBNV_GetSafePlayer(HANDLE hChannel,HANDLE *lphPlayer);

#define LANGID_EN_US		MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT)
#define	LANGID_CH			0x00000804
#define LANGID_CHTW			0x00000404
//现仅支持中文和英文，0或0x0804为中文，1或LANGID_EN_US为英文
DWORD WINAPI JBNV_GetErrorMessage(DWORD dwErrorID,
								  LPSTR lpBuffer,		// message buffer
								  DWORD nSize,			// maximum size of message buffer
								  DWORD dwLanguageId);	// language identifier 0x0 China,

DWORD WINAPI JBNV_Mute(HANDLE hChannel,BOOL bMute);		//静音操作
DWORD WINAPI JBNV_SetVolume(HANDLE hChannel,DWORD dwValume);
//本地捕捉图象，当服务器断线时，可以使用此函数捕捉最后一帧的图象数据。输出为BMP图片数据，可以直接保存
DWORD WINAPI JBNV_CaptureBitmap(HANDLE hChannel,BYTE *in_Buffer,DWORD *nSize);	
//获取和设置本地播放缓冲
DWORD WINAPI JBNV_GetStreamBufferSize(HANDLE hChannel,DWORD *lpMin,DWORD *lpMax,DWORD *lpCurrent);	
DWORD WINAPI JBNV_SetStreamBufferSize(HANDLE hChannel,DWORD dwMin,DWORD dwMax);
//设置显示区域
DWORD WINAPI JBNV_SetDisplayRect(HANDLE hChannel,RECT *lpRect);
//更新图片
DWORD WINAPI JBNV_UpdataImage(HANDLE hChannel,RECT *lpRect);
//设置OSD回调，可以通过此回调在画面上实现画线或文字输出等功能
DWORD WINAPI JBNV_SetOSDCallback(HANDLE hChannel,DrawOSD pOSD,DWORD dwUser);
//设置显示窗口
DWORD WINAPI JBNV_SetDisplayhWnd(HANDLE hChannel,HWND hDisplayWnd);
DWORD WINAPI JBNV_ShowToScale(HANDLE hChannel,BOOL bEnable);

//设置视频数据回调，回调的数据为YUV422
DWORD WINAPI JBNV_SetVideoCallback(HANDLE hChannel,VideoCallBack pvideocallback,DWORD dwUser);
DWORD WINAPI JBNV_SetVideoStatic(HANDLE hChannel,BOOL bShowVideo);
DWORD WINAPI JBNV_SetVideo2Static(HANDLE hChannel,BOOL bShowVideo);

DWORD WINAPI JBNV_SetStreamCallBackEx(HANDLE hChannel,fStreamCallBackEx cbStreamCallBackEx,DWORD dwUser);//设置通道码流回调

//录像操作函数
//设置预录像时间长度，最长60秒
DWORD WINAPI JBNV_SetPreRecord(HANDLE hChannel,DWORD dwSeconds);
DWORD WINAPI JBNV_StartRecord(HANDLE hChannel,LPCSTR lpszFile,
							DWORD dwFileType);	//0 为ASF，现仅支持1种格式
DWORD WINAPI JBNV_GetRecorded(HANDLE hChannel,DWORD *lpdwWrited);
DWORD WINAPI JBNV_StopRecord(HANDLE hChannel);

//对讲
DWORD WINAPI JBNV_TalkOpen(LPCSTR lpszServerIP,WORD wServerPort);
DWORD WINAPI JBNV_TalkOpenEx(HANDLE hServer, LPCSTR lpszServerIP,WORD wServerPort);
DWORD WINAPI JBNV_TalkWith(LPCSTR lpServerA,WORD wServerPortA,LPCSTR lpServerB,WORD wServerPortB,BOOL bBreak);
//斟听指定服务器的声音
DWORD WINAPI JBNV_TalkListen(LPCSTR lpServer,WORD nServerPort);
DWORD WINAPI JBNV_TalkClose();
DWORD WINAPI JBNV_TalkStartRecord(LPCSTR lpszFileName);
DWORD WINAPI JBNV_TalkStopRecord();


/*音频对讲透明传输*/
DWORD WINAPI JBNV_StartVoiceCom(LPCSTR lpszServerIP,WORD wServerPort, VoiceDataCallBack lpVideoData, DWORD dwUser, LONG *lpHandle);
DWORD WINAPI JBNV_StopVoiceCom();
DWORD WINAPI JBNV_VoiceComSendData (LONG  lVoiceComHandle, int nVoiceType, char  *pSendBuf, DWORD  dwBufSize);

/*远程抓拍*/
DWORD WINAPI JBNV_SnapShotCallBack(HANDLE hServer, SnapShotCallBack lpSnapShotData, DWORD dwUser);
DWORD WINAPI JBNV_CapturePicture(HANDLE hServer,DWORD dwChannel,LPCSTR lpPicFileName,BYTE *bPicBuffer,LPDWORD lpSizeReturned);
DWORD WINAPI JBNV_Capture(HANDLE hChannel,LPCSTR lpPicFileName);

DWORD WINAPI JBNV_SetConnectTime(DWORD dwWaitTime, DWORD dwTryTimes);		//dwWaitTime单位毫秒，取值范围[3000,75000]
DWORD WINAPI JBNV_SetReconnect(DWORD dwInterval,BOOL bEnableRecon = FALSE);	//dwInterval重连间隔，单位:毫秒 [30*1000,X]

//搜索主机
typedef struct tagJBNV_SERVER_PACK
{
	char	szIp[16];			//服务器Ip
	WORD	wMediaPort;			//流端口
	WORD	wWebPort;			//Http端口号
	WORD	wChannelCount;		//通道数量
	char	szServerName[32];	//服务器名
	DWORD	dwDeviceType;		//服务器类型
	DWORD	dwServerVersion;	//服务器版本
	WORD	wChannelStatic;		//通道状态(是否视频丢失)
	WORD	wSensorStatic;		//探头状态
	WORD	wAlarmOutStatic;	//报警输出状态
}JBNV_SERVER_PACK;

typedef struct tagJBNV_SERVER_MSG_DATA
{
	DWORD						dwSize;
	DWORD						dwPackFlag;
	JBNV_SERVER_PACK			jbServerPack;
	JB_SERVER_MSG				jbMsg;
}JBNV_SERVER_MSG_DATA;

///luo add,thees structs I just use it for send the answer back to servertools
typedef struct tagJBNV_SERVER_PACK_EX
{
	JBNV_SERVER_PACK jspack;
	BYTE	        bMac[6];
	BOOL	        bEnableDHCP;	
	BOOL			bEnableDNS;
	DWORD			dwNetMask;
	DWORD			dwGateway;
	DWORD			dwDNS;
	DWORD			dwComputerIP;	
	BOOL	        bEnableCenter;
	DWORD			dwCenterIpAddress;
	DWORD			dwCenterPort;
	char			csServerNo[64];
	int				bEncodeAudio;
}JBNV_SERVER_PACK_EX;

typedef struct tagJBNV_SERVER_MSG_DATA_EX
{
	DWORD					dwSize;
	DWORD					dwPackFlag; // == SERVER_PACK_FLAG
	JBNV_SERVER_PACK_EX		jbServerPack;
}JBNV_SERVER_MSG_DATA_EX;

typedef struct tagJBNV_MC_PACK{
	DWORD	dwFlag;
	DWORD	dwServerIpaddr;
	WORD	wServerPort;
	WORD	wBufSize;
	DWORD	dwCommand;
	DWORD	dwChannel;
}JBNV_MC_PACK;


DWORD WINAPI JBNV_SearchServer(HWND hWnd,DWORD dwMsg);
DWORD WINAPI JBNV_ModifyNewWork(JB_SERVER_NETWORK* pServerMsgData, BOOL bManualModify);
DWORD WINAPI JBNV_SetAlarmRecv(HWND hWnd,DWORD dwMsg,WORD wPort);

//辅助函数
//获得升级文件信息
DWORD WINAPI JBNV_GetUpgradeFileInfo(HANDLE hServer,LPCSTR lpFile,DWORD *lpFileVer,DWORD *lpFileLen,LPSTR lpDes);
DWORD WINAPI GetDataCRC (LPVOID lpData,DWORD dwSize);		//获得数据CRC32值，返回值为CRC值
DWORD WINAPI GetWindowsMacInfo(BYTE *lpMac,DWORD *lpdwSize);//获得当前计算机的MAC地址
DWORD WINAPI GetWindowsIpAddressInfo(DWORD *lpIpAddress,DWORD *lpdwSize);//获得当前计算机的IP地址列表
//帧头结构
typedef struct tagJB_FRAME_HEADER
{
	WORD	wMotionDetect;			//运动量
	WORD	wFrameIndex;			//帧索引
	DWORD	nVideoSize;				//视频大小
	DWORD	nTimeTick;				//时间戳
	WORD	nAudioSize;				//音频大小
	BYTE	bKeyFrame;				//是否关键帧
	BYTE	nPackIndex;				//包索引
}JB_FRAME_HEADER,*PJB_FRAME_HEADER;

#define MAX_STREAM_BUFF_SIZE (1024 * 1000) // 500 *1024

typedef struct tagJB_FRAME_DATA
{
	JB_FRAME_HEADER		jbFrameHeader;
	BYTE				*lpStreamData;
	DWORD				dwStreamSize;	//MAX_STREAM_BUFF_SIZE
}JB_FRAME_DATA,*PJB_FRAME_DATA;

#define JB_PACKDATA_SIZE	(8 *1024)
typedef struct tagJB_DATAPACK
{
	WORD				IsSampleHead;
	WORD				BufSize;			// Buf 中有多少可用
	JB_FRAME_HEADER		jbFrameHeader;
	BYTE				PackData[JB_PACKDATA_SIZE];
}JB_DATAPACK, *PJB_DATAPACK;

//播放命令
#define		JB_PLAY_CMD_PLAY			1
#define		JB_PLAY_CMD_PLAYPREV		2
#define		JB_PLAY_CMD_STEPIN			3
#define		JB_PLAY_CMD_STEPOUT			4
#define		JB_PLAY_CMD_PAUSE			5
#define		JB_PLAY_CMD_RESUME			6
#define		JB_PLAY_CMD_FASTPLAY		7
#define		JB_PLAY_CMD_FASTBACK		8
#define		JB_PLAY_CMD_STOP			9
#define		JB_PLAY_CMD_SLOWPLAY		10

#define		JB_PLAY_CMD_FIRST			11			/*定位到文件头*/
#define		JB_PLAY_CMD_LAST			12			/*定位到文件末尾*/
#define		JB_PLAY_CMD_SEEK			13			/*定位播放*/

#define		JB_PLAY_CMD_SOUND			14

#define		VIDEO_FORMAT_MPEG4		0
#define		VIDEO_FORMAT_H264		1
#define		VIDEO_FORMAT_MP4A		2

enum
{
	DOWNLOAD_WAITING,		// 等待下载
	DOWNLOAD_DOING,			// 正在下载
	DOWNLOAD_COMPLETE,		// 下载完成
};

typedef struct tagJB_STREAM_PLAY_INFO{
	DWORD	dwPlayState;		//播放状态
	DWORD	dwTimeLength;		//播放时间长（秒）
	DWORD	dwPlayedTime;		//已播放时间
	DWORD	dwImageWidth;
	DWORD	dwImageHeight;
	DWORD	dwFileLength;		// 2010-11-25，文件总长度，即字节数
	DWORD	dwVideoCode;
	DWORD	dwAudioCode;
	BOOL	m_bAudioPlay;		//是否播放音频
	BOOL	m_bLoopPlay;		//是否循环播放
	DWORD	dwDownloadTime;		//已下载的时间	// 2010-11-25，重新定义为以下载的字节数
	DWORD	dwDownloadStatus;	//下载状态		0 等待下载	1 正在下载	2 下载完成
}JB_STREAM_PLAY_INFO,*PJB_STREAM_PLAY_INFO;

DWORD WINAPI JBPlay_OpenFile(LPCSTR lpFile,DWORD dwFileNumber,HWND hVideoWnd,BOOL bUseOverlay,HANDLE *lpHandle);
DWORD WINAPI JBPlay_OpenStream(DWORD dwVideoFormat,HWND hVideoWnd,BOOL bUseOverlay,HANDLE *lpHandle);
DWORD WINAPI JBPlay_OpenStreamEx(DWORD dwVideoFormat,HWND hVideoWnd,BOOL bUseOverlay,int nVideoWidth,int nVideoHeight,HANDLE *lpHandle);
DWORD WINAPI JBPlay_PlayCommand(HANDLE hPlayer,DWORD dwPlayCmd);
DWORD WINAPI JBPlay_PlayCommandEx(HANDLE hPlayer,DWORD dwPlayCmd,DWORD dwValue);
DWORD WINAPI JBPlay_GetPlayInfo(HANDLE hPlayer,JB_STREAM_PLAY_INFO *lpInfo);
DWORD WINAPI JBPlay_SetAudio(HANDLE hPlayer,BOOL bEnabled);
DWORD WINAPI JBPlay_UpdateBound(HANDLE hPlayer);
DWORD WINAPI JBPlay_SetDisplayRect(HANDLE hPlayer,RECT *Rect);
DWORD WINAPI JBPlay_SetDisplayWnd(HANDLE hPlayer,HWND hDisplayWnd);
DWORD WINAPI JBPlay_SetOSDCallback(HANDLE hPlayer,DrawOSD pOSD,DWORD dwUser);
DWORD WINAPI JBPlay_SetVideoCallback(HANDLE hPlayer,VideoCallBack pvideocallback,DWORD dwUser);
DWORD WINAPI JBPlay_SetVolume(HANDLE hPlayer,DWORD dwValume);
DWORD WINAPI JBPlay_CapturePicture(HANDLE hPlayer,LPCSTR lpFile);
DWORD WINAPI JBPlay_SetImagePos(HANDLE hPlayer,RECT *lprc);

DWORD WINAPI JBPlay_SetSecondSurface(HANDLE hPlayer,HWND hVideoWnd,DrawOSD pOSD,DWORD dwUser);

DWORD WINAPI JBPlay_Release(HANDLE hPlayer);

//下面四个函数仅针对文件播放
DWORD WINAPI JBPlay_SeekToSecond(HANDLE hPlayer,DWORD dwSecond);
DWORD WINAPI JBPlay_SetPlayLoop(HANDLE hPlayer,BOOL m_bLoopPlay);
DWORD WINAPI JBPlay_SaveStreamData(HANDLE hPlayer,DWORD dwSaveFormat,DWORD dwStartSecond,DWORD dwEndSecond,LPCSTR lpFileName);
DWORD WINAPI JBPlay_SetMessage(HANDLE hPlayer,HWND hMsgWnd,DWORD dwMessageID);

//下面三个函数仅针对流播放
DWORD WINAPI JBPlay_InputDataPack(HANDLE hPlayer,JB_DATAPACK *lpData);
DWORD WINAPI JBPlay_InputFrame(HANDLE hPlayer,JB_FRAME_DATA *lpFrame);
DWORD WINAPI JBPlay_SetAudioFormat(HANDLE hPlayer,WAVEFORMATEX *lpwfx);
DWORD WINAPI JBPlay_StartRecord(HANDLE hPlayer,LPCSTR lpszFile,DWORD dwFileType);
DWORD WINAPI JBPlay_GetRecorded(HANDLE hPlayer,DWORD *lpdwWrited);
DWORD WINAPI JBPlay_StopRecord(HANDLE hPlayer);

DWORD WINAPI JBPlay_SetStreamBufferSize(HANDLE hPlayer,DWORD dwMin,DWORD dwMax);

DWORD WINAPI JBPlay_SetAudioCallBack(HANDLE hPlayer,BOOL bDecode, AudioCallBack pAudioCallback,DWORD dwUser);

DWORD WINAPI JBPlay_SetStreamCallback(HANDLE hPlayer,fStreamCallBackEx pStreamCallBackEx,DWORD dwUser);

//Add 2007-08-30

//录像设置
typedef struct tagJB_SERVER_RECORD_SET{
	DWORD	dwSize;
	DWORD	dwLocalRecordMode;			//录像模式，0 不录像，1，全实时录像，2，非实时录像，3，告警录像
	BOOL	bAutoDeleteFile;			//是否自动删除文件
}JB_SERVER_RECORD_SET;


typedef struct tagJB_SERVER_RECORD_CONFIG{
	DWORD	dwSize;
	BOOL	bTimeControl;		
	BOOL	bSizeControl;		
	DWORD	dwRecordTime;		
	DWORD	dwRecordSize;	
}JB_SERVER_RECORD_CONFIG;

//录像状态
typedef struct tagJB_SERVER_RECORD_STATE{
	DWORD	dwSize;
	DWORD	dwChannelRecordState;		//当前通道录像状态
	DWORD	dwServerSpace;				//以M为单位
	DWORD	dwSpaceFree;				//自由空间
}JB_SERVER_RECORD_STATE;


//Add 2007-09-17
typedef struct tagJB_CENTER_INFO{
	DWORD	dwSize;
	BOOL	bEnable;
	DWORD	dwCenterIp;					//中心IP
	DWORD	dwCenterPort;				//中心端口
	char	csServerNo[64];				//服务器序列号
}JB_CENTER_INFO;

typedef struct tagJB_CENTER_INFO_EX{
	DWORD dwSize;
	char  csCenterid[32];
	char  csUsername[32];
	char  csUserpass[32];
	char csReserver[64];
}JBNV_NXSIGHT_SERVER_ADDR_EX;

typedef struct tagJB_CENTER_INFO_V2{
	DWORD	dwSize;
	BOOL	bEnable;
	DWORD	dwCenterIp; //不再用，为与之前版本兼容故保留。
	DWORD	dwCenterPort;
	char	csServerNo[64];
	char	csCenterIP[64];
}JBNV_NXSIGHT_SERVER_ADDR_V2;


//Add 2007-10-25 解码器设置
//解码器消息定义
/************************************************************************/
/*	设置视频解码器参数命令												*/
/************************************************************************/

#define		CMD_NVD_ALONE_SET_CHANNELINFO	0x01000001		//设置单路连接消息，	附加参数:DVS_DECODER_CHANNEL_INFO
#define		CMD_NVD_ALONE_STOP				0x01000002		//停止单路连接
#define		CMD_NVD_ALONE_START				0x01000003		//开始单路连接
#define		CMD_NVD_CYCLE_STOP				0x01000004		//停止循环
#define		CMD_NVD_CYCLE_START				0x01000005		//开始循环
#define		CMD_NVD_CYCLE_SET_INFO			0x01000006		//设置循环连接信息
#define		CMD_NVD_AUDIO_SET				0x01000007		//设置音频开关，		附加参数:int
#define		CMD_NVD_VIDEO_MODE_SET			0x01000008		//设置视频输出格式		附加参数:int
#define		CMD_NVD_TALK_BACK_SET			0x01000009		//设置对讲开关			附加参数:int
#define		CMD_NVD_LANGUAGE_SET			0x0100000A		//设置语言				附加参数:int
#define		CMD_NVD_SET_SYSTEM				0x0100000B		//系统设置
#define		CMD_NVD_SET_NETWORK				0x0100000C		//设置网络
#define		CMD_NVD_ALONE_AUTO_CON_SET		0x0100000D		//设置单路自动连接		附加参数:int
#define		CMD_NVD_CYCLE_AUTO_CON_SET		0x0100000E		//设置循环自动连接		附加参数:int
#define		CMD_NVD_MENU_SET				0x0100000F		//设置菜单				附加参数:int
#define		CMD_NVD_SET_SENSOR_ALARM_INFO	0x01000020		//设置告警输出			附加参数:DVS_DECODER_SENSOR_ALARM_INFO
#define		CMD_NVD_SET_SENSOR_STATE		0x01000021		//设置探头状态

#define		CMD_NVD_SET_COM485				0x01000022		//设置485参数			附加参数:JB_NVD_COM485_SET
#define		CMD_NVD_SET_BUFFER				0x01000023		//设置播放缓冲
#define		CMD_NVD_SET_AUDIO_CHANNEL		0x01000024		//设置解码音频通道

#define		CMD_NVD_CYCLE_GET_INFO			0x02000000		//获得循环连接信息
#define		CMD_NVD_ALONE_GET_CHANNELINFO	0x02000001		//获取当前连接参数		附加参数:DVS_DECODER_CHANNEL_INFO
#define		CMD_NVD_GET_NETWORK				0x02000002		//获取网络
#define		CMD_NVD_GET_SERVER_STATE		0x02000003		//解码器当前状态		附加参数:DVS_DECODER_SERVER_INFO
#define		CMD_NVD_GET_SYSTEM				0x02000004		//获取系统参数
#define		CMD_NVD_GET_SENSOR_ALARM_INFO	0x02000005		//获得告警输出设置		附加参数:DVS_DECODER_SENSOR_ALARM_INFO
#define		CMD_NVD_GET_SENSOR_STATE		0x02000006		//获得探头状态

#define		CMD_NVD_GET_COM485				0x02000007		//获得485参数			附加参数:JB_NVD_COM485_SET
#define		CMD_NVD_GET_BUFFER				0x02000008		//获得播放缓冲
#define		CMD_NVD_GET_AUDIO_CHANNEL		0x02000009		//设置解码音频通道
/************************************************************************/
/* 解码器用结构                                                         */
/************************************************************************/

typedef enum {
	nvd_nowork = 0,
	nvd_alone,
	nvd_cycle,
}NVD_CUR_STATE;

typedef enum {
	nvd_menu_Hide = 0,
	nvd_menu_Show,
	nvd_menu_Lock,
	nvd_menu_UnLock,
}NVD_MENU_STATE;

typedef struct tagNVD_DECODER_PARAM{
	BOOL			bAudioOpen;		//音频是否已经打开
	DWORD			dwVideoMode;	//0为PAL,1为NTSC
	DWORD			dwLanguage;		//语言
	DWORD			bAloneAutoCon;	//是否单路自动连接
	DWORD			bCycleAutoCon;	//循环连接自动连接
}NVD_DECODER_PARAM,*PNVD_DECODER_PARAM;

//解码器系统信息
typedef struct tagNVD_DECODER_SERVER_INFO
{
	NVD_CUR_STATE	ServerState;	//服务器状态
	BOOL			bAudioOpen;		//音频是否已经打开
	DWORD			bTalkback;		//是否在对讲
	DWORD			dwVideoMode;	//1为NTSC，0为PAL
	DWORD			dwLanguage;		//语言
	/*
	DWORD			bAloneAutoCon;	//是否单路自动连接
	DWORD			bCycleAutoCon;	//循环连接自动连接
	*/
	BOOL			bAloneAutoCon;	//是否单路自动连接
	BOOL			bCycleAutoCon;	//循环连接自动连接
}NVD_DECODER_SERVER_INFO;

typedef struct tagNVD_DECODER_NETWORK_INFO
{
	DWORD			dwServerIp;
	DWORD			dwServerMask;
	DWORD			dwGateway;
	DWORD			dwDNS;
	DWORD			dwServerPort;
}NVD_DECODER_NETWORK_INFO;

typedef struct tagNVD_DECODER_SYSTEM_SET
{
	DWORD			DeviceNo;		//设备号
	DWORD			dwMenuliveTime;	//菜单保持时间
}NVD_DECODER_SYSTEM_SET;

typedef struct tagNVD_DECODER_SENSOR_ALARM_INFO
{
	BYTE			bEnableAlarm;		//是否使用
	BYTE			dwSensitive;		//灵敏度
	WORD			dwKeepTime;			//保持时间
	DWORD			dwSensorOut[4];		//探头告警输出
	DWORD			dwMontionDec;		//视频移动告警输出
	DWORD			dwVideoLost;		//视频丢失告警输出
}NVD_DECODER_SENSOR_ALARM_INFO;

//解码器通道连接信息
typedef struct tagNVD_DECODER_CHANNEL_INFO
{ /*
	BYTE   bChannelIndex;			//通道ID，当解码器要解码多路视频时需要此参数
	BYTE   nChannel;				//要连接的服务器通道
	WORD   nProt;					//端口
	DWORD  dwNetPoc;				//网络协议
	DWORD  bConnectMode;			//连接方式，按IP或者域名 0 为 IP
	DWORD  dwIpaddress;				//Ip 地址	
	char   szChannelName[16];		//通道名称
	char   szUserName[24];			//用户名
	char   szPassword[24];			//密码
    char   DomainAddress[128];		//域名
	*/

	
	WORD	bEnable;	         	//是否可用
	WORD	nDelayTime;             //停留时间
	BYTE   	bIndexChannel;		    //通道下标
	BYTE   	nChannel;               //通道
	WORD   	nProt;                  //端口
	DWORD	ConnectProtocol;		// 0 TCP 1 UDP 2 MultiBrocast 
	DWORD   AddressType;            //address type 0x00 IP address  0x01 domemain
	DWORD   IPAddress; 		        //ip地址    
	char   	szChannelName[16];      //通道名称
	char   	szUserName[24];         //用户名
	char   	szPassword[24];		    //用户密码						
	char   	DomainAddress[128];     //域名
}NVD_DECODER_CHANNEL_INFO, *PNVD_DECODER_CHANNEL_INFO;

typedef struct tagJB_NVD_COM485_SET{
	DWORD		dwSize;
	DWORD		dwBaudRate;		//波特率
	int			nDataBits;		//数据位
	int			nStopBits;		//停止位
	int			nParity;		//校验位
	int			nStreamControl;	//流控制
	BOOL		bTransferState;	//透明传输
	DWORD		dwReserve[4];	//保留
}JB_NVD_COM485_SET;

typedef struct tagNVD_SNAP_IMAGE{
	BOOL	bEnable;
	DWORD	dwChannel;
	DWORD	dwSnapMode;
	DWORD	dwSnapNum;
	DWORD	dwIntervalTime;
}NVD_SNAP_IMAGE;

DWORD WINAPI JBNV_SendStreamToNVD(HANDLE hServer,int nChannel,JB_DATAPACK *lpData);
DWORD WINAPI JBNV_SendStreamToNVDx(HANDLE hServer,int nChannel,JB_FRAME_DATA *lpFrame);

//Add 2008-01-14
//通道告警编码设置
typedef struct tagJB_CHANNEL_ALARM_CONFIG
{
	DWORD	dwSize;
	DWORD	dwChannel;			//通道号
	BOOL	bEnable;
	DWORD	nFrameRate;			//帧率 (1-25/30) PAL为25，NTSC为30
	DWORD	dwRateType;			//流模式(0为定码流，1为变码流)
	DWORD	dwStreamFormat;		//格式 (0为CIF,1为D1,2为HALF-D1,3为QCIF)
	DWORD	dwBitRate;			//码率 (16000-4096000)
	DWORD	dwImageQuality;		//编码质量(0-4),0为最好
	DWORD	nMaxKeyInterval;	//关键帧间隔(1-100)
	BOOL	bEncodeAudio;		//是否编码音频
}JB_CHANNEL_ALARM_CONFIG,*LPJB_CHANNEL_ALARM_CONFIG;

//Add 2008-05-14
typedef struct tagJBNV_EMAIL_PARAM
{
	DWORD	dwSize;
	BOOL	bEnableEmail;
	BOOL	bAttachPicture;
	char	csEmailServer[64];
	char	csEMailUser[32];
	char	csEmailPass[32];
	char	csEmailFrom[64];
	char	csEmailTo[128];
	char	csEmailCopy[128];
	char	csEmailBCopy[128];
	char	csReserved[32];
}JBNV_EMAIL_PARAM, *PJBNV_EMAIL_PARAM;

//Add 2008-07-07
typedef struct tagJBNV_SERVER_COMMODE{
	DWORD dwSize;
	DWORD dwChannel;
	DWORD dwComMode;		//0 WriteOnly; 1 ReadOnly ; 2 Read after Write.
	DWORD dwInterval;
	DWORD dwReserved[4];	//保留
}JBNV_SERVER_COMMODE;

typedef struct tagJBNV_3322DDNS_CONFIG
{
	DWORD	dwSize;
	BOOL	bEnableDDNS;			//0-不启用,1-启用
	char	csDDNSUserName[32];		//用户名
	char	csDDNSPassword[32];		//密码
	char	csDNSDomain[64];		//DDNS域名
	int		updateTime;             //刷新域名的时间
	char	reserved[32];           //保留
}JBNV_3322DDNS_CONFIG,*PJBNV_3322DDNS_CONFIG;
/*
typedef enum
{
    DDNS_ZK = 0,
    DDNS_3322,
    DDNS_SELF,
    DDNS_DYDNS
}e_ddns_t;
*/

typedef struct
{
	DWORD	dwSize;
	BYTE byEnableDDNS;
	BYTE byDdnsType;
	char resv[2];
	char	csDDNSUserName[32];		
	char	csDDNSPassword[32];		
	char	csDNSDomain[64];		
	int	updateTime;
    DWORD dwIsMaped;
	char	reserved[28];
}JB_DDNS_CONFIG,*PJB_DDNS_CONFIG;

DWORD JBNV_TalkStartRecordEx(LPCSTR lpServer, WORD wServerPort,LPCSTR lpFile);
DWORD JBNV_TalkStopRecordEx(LPCSTR lpServer, WORD wServerPort);


typedef struct tagJBNV_TRANSMIT_ITEM{
	char	csServerDNS[64];	//服务器地址
	DWORD	dwServerPort;		//服务器端口
	BOOL	bEnableSetup;		//服务器是否允许转发设置数据
	DWORD	dwTransMitChannel;	//服务器要转发的通道，-1为所有通道
				//0x0001 为通道1，0x0002为通道2，0x0004为通道3，0x0008为通道4
}JBNV_TRANSMIT_ITEM;

typedef struct tagJBNV_TRANSMIT_VERIFY{
	char	csUserName[32];
	char	csPassword[32];
	DWORD	dwPreviewCount;		//此用户名和密码的用户能够看的服务器数量，-1为所有服务器
	JBNV_TRANSMIT_ITEM *lpItem; //此用户能够看的服务器的列表
}JBNV_TRANSMIT_VERIFY;

typedef struct tagJBNV_CONNECT_LIST{
	char	csUserName[32];			//连接使用的用户名
	DWORD	dwPriviewChannel;		//正在看的图像
	DWORD	dwRemoteIPAddress;		//连接使用的IP地址
	DWORD	dwRemotePort;			//连接使用的端口
	DWORD	dwDataTransMit;			//转发的数据量,单位K Bit
	tagJBNV_CONNECT_LIST *lpNext;
}JBNV_CONNECT_LIST;

//开始启用转发服务,当客户连接上请求数据和断开等操作，服务器都
//会发送消息给应用程序，应用程序可以进行保存日志等工作
DWORD WINAPI JBNV_TM_StartServer(HWND hMessageWnd,DWORD dwMessage,WORD wServerPort,HANDLE *lpHandle);
//设置用户名密码校验信息,如果不调用此接口，默认使用admin进行
//用户和密码检查，并赋予此用户所有观看和设置权限
DWORD WINAPI JBNV_TM_SetVerifyInfo(HANDLE hServer,JBNV_TRANSMIT_VERIFY *lpVerify);
//插入想转发的视频服务器列表
DWORD WINAPI JBNV_TM_InsertItem(HANDLE hServer,JBNV_TRANSMIT_ITEM *lpItem);
//获得连接上的用户列表
DWORD WINAPI JBNV_TM_GetConnectList(HANDLE hServer,JBNV_CONNECT_LIST *lpConnectList);
//停止转发服务
DWORD WINAPI JBNV_TM_CloseServer(HANDLE hServer);

typedef struct tagJBNV_SERVER_ITEM{
	char	csServerDNS[64];
	DWORD	dwServerPort;
	char	csUserName[32];
	char	csPassword[32];
}JBNV_SERVER_ITEM;

DWORD WINAPI JBNV_OpenServerByTransMit(JBNV_SERVER_ITEM *lpTMServer,//转发服务器
	JBNV_SERVER_ITEM *lpServer,	/*需要连接的服务器*/LPVOID *lpHandle);
DWORD WINAPI JBNV_TM_OpenServer(JBNV_SERVER_ITEM *lpTMServer,LPVOID *lpHandle);
DWORD WINAPI JBNV_TM_GetServerList(HANDLE hTMServer,JBNV_SERVER_ITEM *lpServer,DWORD *lpdwServerCount);
DWORD WINAPI JBNV_TM_CloseHandle(HANDLE hTMServer);

//Add 2008-07-28
typedef struct tagJBNV_DIRECTORY_LIST{
	DWORD	dwSize;
	char	csDirectory[64];
	char	csBuffer[0x8000];	//JBNV_FILE_INFO[];
}JBNV_DIRECTORY_LIST;

typedef struct tagJBNV_FILE_INFO{
	char	csFileName[16];
	DWORD	bIsDir;
	DWORD	dwFileSize;
}JBNV_FILE_INFO;

typedef struct tagJBNV_DVR_FILE_DATA{
	DWORD	dwFileLength;			//文件长度
	DWORD	dwDataIndex;			//包索引
	DWORD	dwDataLength;			//数据长度
	DWORD	dwReserved;				//保留
	char	csFileName[64];
	BYTE	bFileData[64 * 1024];
}JBNV_DVR_FILE_DATA;

//Add 2008-08-08 反向连接
typedef struct tagJBNV_BROADCAST_DATA
{
	DWORD				CommandType;
	DWORD				dwServerType;
	DWORD				dwServerIp;
	WORD				wServerDataPort;
	WORD				wServerWebPort;	
	char				csServerName[32];
	BYTE				bServerMac[8];
	BYTE				bChannelCount;
	BYTE				bAlarmInCount;
	BYTE				bAlarmOutCount;
	BYTE				bChanneNo;
	DWORD				dwReserve[6];
	DWORD				dwRemoteIp;
	WORD				wRemotePort;
}JBNV_BROADCAST_DATA;

//开启反向连接侦听后，如果有服务器连接，SDK会向客户发送Message,
//其中wParam 为 JBNV_BROADCAST_DATA 结构的指针
//		JBNV_BROADCAST_DATA *lpData = (JBNV_BROADCAST_DATA *)wParam;

//调用连接服务器时，需要使用接口JBNV_OpenServerByBackConnect
//参数dwServerIpAddress 为 lpData->dwRemoteIp;
//参数wServerPort		为 lpData->wRemotePort;
DWORD WINAPI JBNV_StartBackConnectListen(HWND  hMsgWnd,DWORD dwMsgID,WORD wLocalPort);
DWORD WINAPI JBNV_StopBackConnectListen();

DWORD WINAPI JBNV_OpenServerByBackConnect(DWORD dwServerIpAddress,WORD wServerPort,
		LPCSTR lpszUserName,LPCSTR lpszPassword,LPVOID *lpHandle);
DWORD WINAPI JBNV_OpenRTSPChannel(LPCSTR lpUrl,HWND hShowWnd,LPCSTR lpUserName,LPCSTR lpPassword,HANDLE *lpHandle);
//Add 2008-08-20
typedef struct tagJB_NVD_SENSOR_ALARM_SET
{
	DWORD			dwSize;
	BOOL			bEnableAlarm;		//是否使用
	DWORD			dwKeepTime;			//保持时间
	DWORD			dwSensorOut[4];		//探头告警输出
	DWORD			dwMontionDec;		//视频移动告警输出
	DWORD			dwVideoLost;		//视频丢失告警输出
	DWORD			dwReserved[2];
}JB_NVD_SENSOR_ALARM_SET;

#define WIRELESS_WIFI           0x01
#define WIRELESS_TDSCDMA_ZX     0x02
#define WIRELESS_EVDO_HUAWEI    0x03
#define WIRELESS_WCDMA			0x04
//Add 2008-11-25
typedef struct tagJB_TDSCDMA_CONFIG
{
	DWORD			dwSize;
	BYTE			bCdmaEnable;
	BYTE			byDevType;
	BYTE			byStatus;
	BYTE			byReserve;
	DWORD		    dwNetIpAddr;			//IP  (wifi enable)
}JB_TDSCDMA_CONFIG;


typedef struct tagJB_WIFI_CONFIG
{
	DWORD		dwSize;
	int         bWifiEnable; // 0: disable, 1:static ip address, 2:dhcp
	DWORD		dwNetIpAddr;
	DWORD       dwNetMask;
	DWORD       dwGateway;
	DWORD		dwDNSServer;
	char		szEssid[32];
	unsigned char         nSecurity;  //0: none,1:web 64  assii,
                                      //2:web 64  hex,
                                      //3:web 128 assii
						 	          // 4:web 128 hex
                                      //5 WPAPSK-TKIP 
                                      //6 WPAPSK-AES
                                      //7 WPA2PSK-TKIP
                                      //8 WPA2PSK-AES   
    unsigned char byMode;  // 1. managed 2. ad-hoc
	BYTE          byStatus; //	0:	成功,其他值是错误码
	BYTE          byRes;  // 1:wps开启
    char		  szWebKey[32];
}JB_WIFI_CONFIG;


typedef struct tagJBPeriphSensorConfig{
	BOOL		bEnable;
	DWORD		nAddress;
	BOOL		bOSDVideo;
	BOOL		bAlarmRecord;
	DWORD		nLinkVideoChn; //bit 
	DWORD		nStatus; //the current status identify
} JB_PERIPH_SENSOR_CONFIG;

typedef struct tagJBPeriphConfig{
	DWORD		dwSize;
	BOOL 		bEnable;
	char      	csDevName[32];
	DWORD		nComID; // 0:485, 1:232
	DWORD 		nEnableDevNO;	
	JB_PERIPH_SENSOR_CONFIG SensorCfg[16]; //MAX 16 device 
} JB_PERIPH_CONFIG;

//Add 2009-01-06
typedef struct tagJB_TEL_ALARM_SET{
	DWORD		dwSize;
	char		csTelNo[9][20];
	DWORD		dwBeepTime;
	BOOL		bArming;
	BOOL		bEnableVideoLost;
	BOOL		bEnableMotionDetect;
	BYTE		bPrepos[8];
	DWORD		dwReserved[2];
}JB_TEL_ALARM_SET;


typedef struct tagJB_TEMP_HUM_SENSOR_CONFIG{
	DWORD		dwSize;
	BOOL		bEnableDevice;
	BOOL		bEnableDeviceLostAlarm;
	BOOL		bEnableDeviceLimitAlarm;
	BOOL		bEnableShowDataOnVideo;
	DWORD		dwDeviceNo;
	char		csDeviceName[32];
	BOOL		bDeviceIsOnline;
	float       fTempUpperLimit;
	float       fTempLowerLimit;
	float       fTempValue;
	float       fHumUpperLimit;
	float       fHumLowerLimit;
	float       fHumValue;
	DWORD		dwRecved[4];
}JB_TEMP_HUM_SENSOR_CONFIG;

typedef struct tagJB_POWER_DEVICE_CONFIG{
	DWORD		dwSize;
	BOOL		bEnableDevice;
	BOOL		bDeviceIsOnline;
	BOOL		bEnableDeviceLostAlarm;
	BOOL		bEnableShowDataOnVideo;
	DWORD		dwDeviceNo;
	char		csDeviceName[32];
	DWORD		dwPower220VState;		//0 off,1 on
	DWORD		dwPower48VState;		//0 oof,1 on
	DWORD		dwRecved[4];
}JB_POWER_DEVICE_CONFIG;

//Add 2009-04-07
//添加此函数给客户使用，此回调作用同JBNV_SetMessage函数。
typedef int (CALLBACK *MyMessageCallBack)
( HANDLE hServer,				//服务器句柄
 JB_SERVER_MSG *lpmsg,			//消息
 DWORD dwUser);					//用户数据
DWORD WINAPI JBNV_SetMessageEx(HANDLE hServer,MyMessageCallBack lpMessagecb,DWORD dwUser);

#include <WINSOCK2.H>

//关于搜索服务器
typedef int (CALLBACK *SearchServerCallBack)(JBNV_SERVER_MSG_DATA *lpServerMsgData,	//服务器返回的消息
											 sockaddr_in *lpRemote,DWORD dwUser);				//服务器地址
DWORD WINAPI JBNV_SearchServerEx(SearchServerCallBack lpSearchServer,DWORD dwUser);
//关于反向连接
typedef int (CALLBACK *BackConnectCallBack)(JBNV_BROADCAST_DATA *lpData,DWORD dwUser);		//反向连接消息
DWORD WINAPI JBNV_StartBackConnectListenEx(BackConnectCallBack lpBackConnect,DWORD dwUser,WORD wLocalPort);



#define CMD_NVD_SET_TVSIZE 0x01000010 //设置解码器视频输出大小
#define CMD_NVD_GET_TVSIZE 0x02000010 //获得解码器视频输出大小

typedef struct tagNVD_DECODER_CHANNEL_TV
{
	DWORD dwSize;
	DWORD dwChannel;	//通道号
	DWORD dwTop;        //上边距
	DWORD dwLeft;		//左边距
	DWORD dwRight;		//右边距
	DWORD dwBottom;		//下边距
}NVD_DECODER_CHANNEL_TV; 


DWORD WINAPI JBNV_TalkOpenByBackConnect(DWORD dwServerIpAddress,WORD wServerPort);
DWORD WINAPI JBNV_TalkOpenByBackConnectEx(HANDLE hServer, DWORD dwServerIpAddress,WORD wServerPort);



typedef struct tagJBNV_TIME{
	DWORD dwYear;	
	DWORD dwMonth;
	DWORD dwDay;
	DWORD dwHour;
	DWORD dwMinute;
	DWORD dwSecond;	
}JBNV_TIME;

typedef struct tagJBNV_FindFileReq{		//查询条件
	DWORD		dwSize;
	DWORD		nChannel;				//0xff：全部通道，0，1，2 ......
	DWORD		nFileType;				//文件类型 ：0xff － 全部，0 － 定时录像，1 - 移动侦测，2 － 报警触发，3  － 手动录像
	JBNV_TIME	BeginTime;				//
	JBNV_TIME	EndTime;				//StartTime StopTime 的值都为0000-00-00 00:00:00表示查找所有时间
}JBNV_FIND_FILE_REQ;


typedef struct tagJBNV_FILE_DATA_INFO{
	char		sFileName[256];			//文件名
	JBNV_TIME	BeginTime;				//
	JBNV_TIME	EndTime;
	DWORD		nChannel;
	DWORD		nFileSize;				//文件的大小
	DWORD		nState;					//文件转储状态
}JBNV_FILE_DATA_INFO;

typedef struct tagJBNV_FindFileResp{
	DWORD		dwSize;
	DWORD		nResult;		//0:success ;1:find file error ; 2:the number of file more than the memory size, and the result contains part of the data
	DWORD		nCount;
	DWORD		dwReserved[3];
}JBNV_FIND_FILE_RESP;

typedef enum 
{
	WL_OK = 0,
	WL_NOT_CONNECT,		//没有在连接
	WL_DEVICE_NOT_EXIST,	//ipc的wifi硬件不存在
	WL_ESSID_NOT_EXIST,	//essid不存在
	WL_DHCP_ERROR,			//dhcp获取不到ip
	WL_ENCRYPT_FAIL,		//密码认证错误
	WL_IP_CONFLICT,		//IP地址冲突
	WL_UNSUPPORT_WPS,      //不支持WPS功能
}WIRELESS_STATUS_E;

DWORD WINAPI JBPlay_PlayBackByName(HANDLE	hServer ,					//JBNV_OPENSERVER 的返回值
								  LPCSTR	lpszFileName,				//要回放的文件名
								  DWORD		dwImageIndex,				//回放窗口序号
								  HWND  	hWnd,						//回放文件的窗口句柄
								  JB_STREAM_PLAY_INFO *lpInfo,
								  LPVOID	*lpHandle
								  );


DWORD WINAPI JBPlay_PlayBackByTime(HANDLE	hServer ,			//JBNV_OPENSERVER 的返回值
								  DWORD		lChannel,			//通道号
								  JBNV_TIME	lpBeginTime, 		//开始时间
								  JBNV_TIME	lpEndTime , 		//结束时间
								  DWORD dwImageIndex,
								  HWND hWnd,				//要播放的窗口句柄
								  JB_STREAM_PLAY_INFO *lpInfo,
								  LPVOID *lpHandle);

DWORD WINAPI JBPlay_StopPlay(HANDLE hPlayHandle);		//播放句柄由JBNV_PlayBackByName//或者JBNV_PlayBackByTime的返回


DWORD WINAPI JBPlay_RemotePlayCommand(HANDLE hPlayHandle ,
									 DWORD  dwControlCode,		//控制录像回放状态命令
									 DWORD  dwInValue			//设置文件回放的进度(JBNV_PLAYSETPOS)时,此参数表示进度值；
									 );

DWORD WINAPI JBPlay_RemoteDownloadStart(HANDLE hServer, LPCSTR	lpszRemoteFileName,  LPCSTR	lpszSaveFileName, LPVOID *lpHandle);//下载列表内的文件
DWORD WINAPI JBPlay_RemoteDownloadStop(HANDLE hHandle);//停止下载列表内的文件


DWORD WINAPI JBPlay_GetRemotePlayInfo(HANDLE hPlayHandle,JB_STREAM_PLAY_INFO *lpInfo); //获取播放信息
DWORD WINAPI JBPlay_RemoteSetMessage(HANDLE hServer,HWND hMsgWnd,UINT nMessage);//设置消息回调
DWORD WINAPI JBPlay_RemoteCapturePicture(HANDLE hPlayHandle,LPCSTR lpFileName); //远程抓拍图片

typedef struct tagJBUPnPConfig
{
	DWORD dwSize;
	BOOL bEnable; /*是否启用upnp*/
	DWORD dwMode; /*upnp工作方式.0为自动端口映射，1为指定端口映射*/
	DWORD dwLineMode; /*upnp网卡工作方式.0为有线网卡,1为无线网卡*/
	char csServerIp[32]; /*upnp映射主机.即对外路由器IP*/
	DWORD dwDataPort; /*upnp映射数据端口*/
	DWORD dwWebPort; /*upnp映射网络端口*/
	DWORD dwMobilePort;         /*upnp映射手机端口*/  
	DWORD dwDataPort1; /*upnp已映射成功的数据端口*/
	DWORD dwWebPort1; /*upnp已映射成功的网络端口*/
	DWORD dwMobilePort1;      /*upnp映射成功的手机端口*/  
}JB_UPNP_CONFIG; 


#define MAX_DISK_NUM	64

typedef struct tagJBNV_DISK_ITEM{
	DWORD	dwDiskID;			//此Item指的是第几个硬盘上的
	DWORD	dwDiskType;			//磁盘类型
	DWORD	dwPartitionIndex; 
	DWORD	dwPartitionType;
	DWORD	dwPartitionState;	//磁盘状态
	DWORD	dwPartitionSize;	//磁盘容量,以M为单位
	DWORD	dwPartitionFree;	//磁盘剩余空间
}JBNV_DISK_ITEM;

typedef struct tagJBNV_DISK_INFO{
	DWORD	dwSize;
	DWORD	dwItemCount;
	JBNV_DISK_ITEM DiskItem[MAX_DISK_NUM];
}JBNV_DISK_INFO;

typedef struct tagJBNV_FDISK_DISK{
	DWORD	dwSize;
	DWORD	dwDiskID;			//要分区的磁盘ID
	DWORD	dwPartitionSize;	//格式分区大小(G)
	DWORD	dwRecvParam[8];
}JBNV_FDISK_DISK;

typedef struct tagJBNV_FORMAT_DISK{
	DWORD	dwSize;
	DWORD	dwDiskID;			//磁盘ID
	DWORD	dwPartitionIndex;	//要格式化的磁盘
	BOOL	bFastFormat;		//是否进行快速格式化
	DWORD	dwClusterSize;		//格式化簇大小
	DWORD	dwRecvParam[8];
}JBNV_FORMAT_DISK;

#define JBNV_STOP_RECORDING			0x1000
#define JBNV_STOP_RECORDSUCCESS		0x1001
#define JBNV_FDISK_RUNING			0x1002
#define	JBNV_FDISK_SUCCESS			0x1003
#define JBNV_FDISK_ERROR_NODISK		0x1004
#define JBNV_FDISK_ERROR_NOFIND		0x1005
#define JBNV_FORMAT_RUNING			0x1006
#define JBNV_FORMAT_SUCCESS			0x1007
#define JBNV_FORMAT_ERROR_NODISK	0x1008
#define JBNV_FORMAT_ERROR_FAILED	0x1009

typedef struct tagJBNV_FORMAT_STATUS{
	DWORD dwSize;
	DWORD dwDiskID;
	DWORD dwPartitionIndex;
	DWORD dwFormatState;
	DWORD dwParam1;
	DWORD dwParam2;
}JBNV_FORMAT_STATUS;


typedef struct tagJB_MOBILE_CONFIG
{
	unsigned long		dwSize; 
	unsigned short      wPort;
	char				reserved[128];
}JB_MOBILE_CONFIG,*PJB_MOBILE_CONFIG; 


#define CMD_SET_MOBILE                0x00000051
#define CMD_GET_MOBILE                0x10000051

typedef struct tagJB_MOBILE_CENTER_INFO{
	DWORD	dwSize;
	BOOL	bEnable;
	char	szIp[64];					//服务器Ip
	DWORD	dwCenterPort;				//中心端口
	char	csServerNo[64];				//服务器序列号
	DWORD	dwStatus;					//服务器连接状态 0为未连接 1为连接中 2连接成功
	char	csUserName[32];				//用户名
	char	csPassWord[32];				//密码
	BYTE	byAlarmPush;
	BYTE	breservedData[3];
	DWORD	reservedData;				//保留
}JB_MOBILE_CENTER_INFO;

typedef struct tagJB_SERVER_SET_INFO{
	DWORD	dwSize;
	DWORD	dwIp;			//Server Ip
	DWORD	wMediaPort;		//Media Port:8200
	DWORD	wWebPort;		//Http Port:80
	DWORD	dwNetMask;
	DWORD	dwGateway;
	DWORD	dwDNS;
	DWORD	dwComputerIP;
	
	BOOL	bEnableDHCP;	
	BOOL	bEnableAutoDNS;
	BOOL	bEncodeAudio;
	
	char	szMac[6];
	char	szoldMac[6];
	char	szServerName[32];	
}JBNV_SET_SIGHT_SERVER_INFO_EX;

///数据头,用来解析数据
typedef struct
{
	DWORD	dwSize;
	DWORD	nCmd;
	DWORD	dwPackFlag; // == SERVER_PACK_FLAG
	DWORD	nErrorCode;
	
}JBNV_BROADCAST_HEADER_EX;


//this is the broadcast package over the network
typedef struct tagJBNV_SERVER_INFO_BROADCAST{
	DWORD	nBufSize;       /*sieze of JBNV_SET_SERVER_INFO_BROADCAST*/
	JBNV_BROADCAST_HEADER_EX			hdr;
	JBNV_SET_SIGHT_SERVER_INFO_EX      	setInfo;
	JB_CENTER_INFO					    nxServer;
}JBNV_SET_SERVER_INFO_BROADCAST_EX;

typedef struct tagJBNV_SERVER_INFO_BROADCAST_V2{
	DWORD	                                                nBufSize;       /*sieze of JBNV_SET_SERVER_INFO_BROADCAST*/
	JBNV_BROADCAST_HEADER_EX				hdr;
	JBNV_SET_SIGHT_SERVER_INFO_EX      	        setInfo;
	JBNV_NXSIGHT_SERVER_ADDR_V2           nxServer;
}JBNV_SET_SERVER_INFO_BROADCAST_EX_V2;


typedef struct tagJBNV_PTZ_CONTROL
{
	DWORD		dwSize;
	DWORD		dwChannel;
	DWORD		dwPTZCommand;		//PTZCMD_UP .....
	int			nPTZParam;		// 根据具体命令字而定
	BYTE		byReserve[32];
}JBNV_PTZ_CONTROL;

#endif