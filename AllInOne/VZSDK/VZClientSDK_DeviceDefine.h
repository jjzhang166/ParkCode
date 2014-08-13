//设备相关的符号定义
#ifndef _VZ_CLIENT_SDK_DEVICE_DEFINE_H_
#define _VZ_CLIENT_SDK_DEVICE_DEFINE_H_

//回调函数、消息等定义信息
#define VZC_MSG_STAT 					0x0100
#define VZC_MSG_ONLINE 					(VZC_MSG_STAT+0x01)
#define VZC_MSG_NOTONLINE 		        (VZC_MSG_STAT+0x02)
#define VZC_MSG_VALID 					(VZC_MSG_STAT+0x03)
#define VZC_MSG_NOTVALID 		        (VZC_MSG_STAT+0x04)
#define VZC_MSG_ACTIVE 					(VZC_MSG_STAT+0x05)
#define VZC_MSG_DEACTIVE 		        (VZC_MSG_STAT+0x06)
#define VZC_MSG_TALK_ERROR 		        (VZC_MSG_STAT+0x07)
#define VZC_MSG_STREAM_ERROR			(VZC_MSG_STAT+0x08)

#define VZC_MSG_ALARM 		        0x0200
#define VZC_MSG_ALARM_VIDEO_LOST 		(VZC_MSG_ALARM+0x01)
#define VZC_MSG_ALARM_IO 		        (VZC_MSG_ALARM+0x02)
#define VZC_MSG_ALARM_MD 		        (VZC_MSG_ALARM+0x03)
#define VZC_MSG_ALARM_IV_TRACK 	        (VZC_MSG_ALARM+0x04)
#define VZC_MSG_ALARM_IV_CROSS 	        (VZC_MSG_ALARM+0x05)

#define VZC_MSG_TALK 		        0x0300
#define VZC_MSG_TALK_SNEDFILE_END 		(VZC_MSG_TALK+0x01)

//升级错误代码
typedef enum{
	UPDATE_ERROR_SUCCESS,//升级成功
	UPDATE_ERROR_ABORT,//用户取消
	UPDATE_ERROR_FILE_FORMAT,//文件名不符
	UPDATE_ERROR_WRITE,//写nand错误
	UPDATE_ERROR_READ,//读文件错误
	UPDATE_ERROR_INTERNAL,//程序内部错误
	UPDATE_ERROR_TIMEOUT,//连接时间过长
	UPDATE_ERROR_UNDEFINED,//其他错误
}UPDATE_ERROR;
//常用参数定义
#define VZDEV_SERIALNO_LEN 					7
#define VZDEV_MAX_MDNUM						8

#define VZDEV_DATATYPE_AV					0x01    //音视频同步数据
#define VZDEV_DATATYPE_USVIDEO		        0x02    //自定义视频数据
#define VZDEV_DATATYPE_SOUND		        0x04    //语音对讲数据

#define VZDEV_STREAM_TYPE_AV		        0	/* 复合流*/
#define VZDEV_STREAM_TYPE_VIDEO				1	/* 视频流*/

#define VZDEV_FRAMESIZE_CIF4				0	/* CIF4 704*576*/
#define VZDEV_FRAMESIZE_CIF					1	/* CIF 352*288*/

#define VZDEV_VIDEO_COMPRESS_FIX_RATE		0	/* 固定码流 */
#define VZDEV_VIDEO_COMPRESS_VAR_RATE		1	/* 可变码流 */

#define VZDEV_TALK_STAT_OPENED		        0x01	//语音对讲打开
#define VZDEV_TALK_WAVEIN_INSIDE			0x01	//采用内部语音设备
#define VZDEV_TALK_WAVEIN_OUTSIDE			0x02	//采用外部语音数据

//中心服务器
#define CENTERSERVER_MAX_GROUP 128 //用户组编号的最大值1-128
#define CENTERSERVER_MAX_GROUPS 8//一次可以取得的最多用户组数

typedef struct  {
	BYTE sSerialNumber[VZDEV_SERIALNO_LEN];  //序列号
	BYTE byAlarmInPortNum;		//device报警输入个数
	BYTE byAlarmOutPortNum;		//device报警输出个数
	BYTE byDiskNum;				//device 硬盘个数
	BYTE byDVRType;				//device类型,
	BYTE byChanNum;				//device 通道个数
	BYTE byRev;
}VZDEV_DEVICEINFO, *PVZDEV_DEVICEINFO;

typedef struct{
	char			 sIpV4[16];	//局域网IP地址
	WORD             wPort;		//端口号
	int				 iUserID;	//登录用户标识
	BYTE             byChannel;	//通道号
	char			 sP2PID[32];//云标识
	BYTE             byRes;
}VZ_IVS_DEV_INFO;//前端设备信息

typedef struct VZ_Transmit_Server
{
	char m_hostname[32];
	int  m_port;
	int  m_isEnable;
}VZ_Transmit_Server;

typedef struct
{
	char Name[32];                  //设备名
	unsigned int SerialHi;      //设备唯一序列号
	unsigned int SerialLo;     //设备唯一序列号
	unsigned int mcaip;            //局域网内组播的ip地址（通常保存在数据库内）
	unsigned int udpip;            //udp连接的ip地址（从网络连接获得）
	unsigned int udpport;         //udp连接端口（从网络连接获得）
	unsigned int checkrd;         //用于服务器验证的随机数
	unsigned int avnum;           //设备通道数
	unsigned int diginnum;         //设备开关量输入数
	unsigned int digoutnum;        //设备开关量输出数
	unsigned int Valid;             //设备是否注册、合法
}VZDEV_DEVICE_REG, *PVZDEV_DEVICE_REG;

typedef struct{
	int lChannel;//通道号
	int lLinkMode;//最高位(31)为0表示主码流，为1表示子码流，0－30位表示码流连接方式: 0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
	HWND hPlayWnd;//播放窗口的句柄,为NULL表示不播放图象
	char* sMultiCastIP;//多播组地址
}VZDEV_CLIENTINFO,*PVZDEV_CLIENTINFO;

typedef struct
{
	unsigned int       year;
	unsigned int       month;
	unsigned int       date;
	unsigned int       hour;
	unsigned int       min;
	unsigned int       sec;
	unsigned int       day;   //1-7. Sunday is 1 , Saturday is 7
}VZDEV_DateTimeParam, *PVZDEV_DateTimeParam;

typedef struct
{
	unsigned int    PtzComm;                //串口号（1为232、2为485）
	unsigned int    PtzAddress;             //地址
	unsigned int    PtzBaudRate;            //串口波特率 eg:9600 , 19200, 56000, etc
	unsigned int    PtzParity;              //串口校验位 其值为0-4=no,odd,even,mark,space
	unsigned int    PtzDataBits;            //串口数据位 其值为4-8=4,5,6,7,8 位数据位
	unsigned int    PtzStopBit;             //串口停止位 其值为0,1,2 = 1, 1.5, 2 位停止位
	char	        Type[32];	        //协议类型，比如：PELCO D
}VZDEV_PtzTypeParam, *PVZDEV_PtzTypeParam;

#define VZDEV_MAX_PTZ_PRESET_NUM                       64
#define VZDEV_MAX_PTZ_PRESET_NAMELEN                   8
typedef struct
{
	char    Enabled;                                //预置位是否使用
	char	Name[VZDEV_MAX_PTZ_PRESET_NAMELEN];    //预置位名称
}VZDEV_PtzPresetUnit, *PVZDEV_PtzPresetUnit;

typedef struct
{
	VZDEV_PtzPresetUnit            PresetUnit[VZDEV_MAX_PTZ_PRESET_NUM];
}VZDEV_PtzPresetParam, *PVZDEV_PtzPresetParam;

typedef struct
{
	unsigned int    PtzComm;        //串口号（1为232、2为485）
	unsigned int    BaudRate;       //串口波特率 eg:9600 , 19200, 56000, etc
	unsigned int    Parity;         //串口校验位 其值为0-4=no,odd,even,mark,space
	unsigned int    DataBits;       //串口数据位 其值为4-8=4,5,6,7,8 位数据位
	unsigned int    StopBit;        //串口停止位 其值为1,2 = 1,2 位停止位
	unsigned int    ReplyLen;       //返回数据长度
	unsigned int    len;            //数据长度
	char            data[128];      //数据内容
}VZDEV_CommDataGetParam, *PVZDEV_CommDataGetParam;

//VZC_SetDVRMessageCallBack的消息回调报警信息
typedef struct
{
	unsigned int SerialHi;
	unsigned int SerialLo;
	unsigned int avport;
	unsigned int ip;
	unsigned int res1;
	unsigned int res2;
	unsigned int res3;
	unsigned int res4;
}VZDEV_CallbackAlarmParam, *PVZDEV_CallbackAlarmParam;

#define OSDTEXTLEN				16
//-----------OSD----------------
typedef struct
{
	unsigned char	dstampenable;					//0 off 1 on
	int				dateFormat;// 0:YYYY/MM/DD;1:MM/DD/YYYY;2:DD/MM/YYYY
	int				datePosX;
	int				datePosY;
	unsigned char	tstampenable;   				//0 off 1 on
	int				timeFormat;//0:12Hrs;1:24Hrs
	int				timePosX;
	int				timePosY;
	unsigned char	nLogoEnable;					//0 off 1 on
	int				nLogoPositionX;   				///<  logo position
	int				nLogoPositionY;   				///<  logo position
	unsigned char	nTextEnable;					///0 off 1 on
	int				nTextPositionX;   				///<  text position
	int				nTextPositionY;   				///<  text position
	char			overlaytext[OSDTEXTLEN];			///user define text
}VZDEV_OSD_Param;

typedef struct VZDEV_NETCFG
{
	char ipaddr[16];
	char netmask[16];
	char gateway[16];
	char dns[16];
	WORD  http_port;
}VZDEV_NETCFG;

typedef struct VZDEV_FTPCFG
{
	char hostname[32];
	int  port;
	char username[32];
	char password[32];
	char path[256];
}VZDEV_FTPCFG;

typedef enum HwFlags {
	HW_FLAG_BASE =0x00000001,
	HW_FLAG_3G   =0x00000002,
	HW_FLAG_SD   =0x00000004,
	HW_FLAG_USB  =0x00000008,
	HW_FLAG_WIFI =0x00000010,
	HW_FLAG_ONVIF=0x00000020,
}HwFlags;

#define OEM_INFO_SIZE 7
#define HW_VERSION_SIZE 4
typedef struct fs_info_ex {
	char reserved;
	unsigned char oem_info[OEM_INFO_SIZE];		///< 前3位厂商的编号，后4位厂商简称
	unsigned char hw_version[HW_VERSION_SIZE];	///< 硬件版本号,1001是老版，,新版第三位表示通道路数，最后一位表示hwflag（HwFlags的按位与）
	unsigned int hw_flag;						///< 硬件标识,新版改为保存HwType
}fs_info_ex_t;

#endif