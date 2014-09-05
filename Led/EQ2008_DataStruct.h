#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

typedef struct						//字体设置
{
	char*		strFontName;		//字体的名称
	int			iFontSize;			//字体的大小
	BOOL		bFontBold;			//字体是否加粗
	BOOL		bFontItaic;			//字体是否是斜体
	BOOL		bFontUnderline;		//字体是否带下划线
	COLORREF	colorFont;			//字体的颜色
	int			iAlignStyle;		//对齐方式
									//0－ 左对齐 
									//1－居中 
									//2－右对齐
	int         iVAlignerStyle;		//上下对齐方式
									//0-顶对齐
									//1-上下居中
									//2-底对齐
	int         iRowSpace;			//行间距
}User_FontSet;

typedef struct						//窗体设置
{
	int			iX;					//窗口的起点X
	int			iY;					//窗口的起点Y
	int			iWidth;				//窗体的宽度
	int			iHeight;			//窗体的高度
	int			iFrameMode;			//边框的样式
	COLORREF	FrameColor;			//边框颜色
}User_PartInfo;

typedef struct _User_MoveSet
{
	int			iActionType;		//节目变换方式
	int			iActionSpeed;		//节目的播放速度	
	BOOL		bClear;				//是否需要清除背景
	int			iHoldTime;			//在屏幕上停留的时间
	int         iClearSpeed;		//清除显示屏的速度
	int			iClearActionType;	//节目清除的变换方式
	int         iFrameTime;
}User_MoveSet;

//“计时窗口” 
typedef struct _User_Timer
{
	User_PartInfo	PartInfo;			//分区信息
	COLORREF		BkColor;			//背景颜色
	User_FontSet	FontInfo;			//字体设置
	DWORD			ReachTimeYear;		//到达年
	DWORD			ReachTimeMonth;		//到达月
	DWORD			ReachTimeDay;		//到达日
	DWORD			ReachTimeHour;		//到达时
	DWORD			ReachTimeMinute;	//到达分
	DWORD			ReachTimeSecond;	//到达秒
	BOOL			bDay;				//是否显示天 0－不显示 1－显示
	BOOL			bHour;				//是否显示小时
	BOOL			bMin;				//是否显示分钟
	BOOL			bSec;				//是否显示秒
	BOOL			bMulOrSingleLine;	//单行还是多行
	char			*chTitle;			//添加显示文字
}User_Timer;


//“温度窗口”
typedef struct _User_Temperature
{
	User_PartInfo	PartInfo;			//分区信息
	COLORREF		BkColor;			//背景颜色
	User_FontSet	FontInfo;			//字体设置
	char			*chTitle;			//标题
	int				DisplayType;		//显示格式：0－度 1－C
}User_Temperature;

//“日期时间窗口” 
typedef struct _User_DateTime
{
	User_PartInfo	PartInfo;			//分区信息
	COLORREF		BkColor;			//背景颜色
	User_FontSet	FontInfo;			//字体设置
	int				iDisplayType;		//显示风格
	char			*chTitle;			//添加显示文字
	BOOL			bYearDisType;		//年份位数0 －4；1－2位
	BOOL			bMulOrSingleLine;	//单行还是多行
	BOOL			bYear;
	BOOL			bMouth;
	BOOL			bDay;
	BOOL			bWeek;
	BOOL			bHour;
	BOOL			bMin;
	BOOL			bSec;
}User_DateTime;

//“图文框” 
typedef struct _User_Bmp
{
	User_PartInfo	PartInfo;			 //分区信息
}User_Bmp;

//“单行文本框”
typedef struct _User_SingleText
{
	char			*chContent;         //显示内容
	User_PartInfo	PartInfo;			//分区信息
	COLORREF		BkColor;			//背景颜色
	User_FontSet	FontInfo;			//字体设置
	User_MoveSet	MoveSet;			//动作方式设置
}User_SingleText;

//“文本框” 
typedef struct _User_Text
{
	char			*chContent;         //显示内容
	User_PartInfo	PartInfo;			//分区信息
	COLORREF		BkColor;			//背景颜色
	User_FontSet	FontInfo;			//字体设置
	User_MoveSet	MoveSet;			//动作方式设置
}User_Text;

//“RTF文件” 
typedef struct _User_RTF
{
	char            *strFileName;       //RTF文件名
	User_PartInfo	PartInfo;			//分区信息
	User_MoveSet    MoveSet;			//动作方式设置
}User_RTF;

#endif _DATASTRUCTURE_H_
