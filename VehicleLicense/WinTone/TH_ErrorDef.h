// ***************************************************************
//  TH_ErrorDef.h   version:  4.0     date: 2010.4.12
//  -------------------------------------------------------------
//  清华大学智能图文信息处理研究室。版权所有。
//  -------------------------------------------------------------
//  Center for Intelligent Image and Document Information Processing
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//   Author: Zhou Jian
// ***************************************************************
//		Revision history:
//			2010.4.12: v4.0, 定义SDK的出错信息
// ***************************************************************

#if !defined(__TH_ERRORDEF_INCLUDE_H__)
#define __TH_ERRORDEF_INCLUDE_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// The errors that may occur during the use of the SDK
#define		TH_ERR_NONE								0		//没有错误
#define		TH_ERR_GENERIC							1		//一般错误，没有专门的意思
#define		TH_ERR_NODOG			               -1		//没有找到加密狗
#define		TH_ERR_DOGERROR						   -2		//打开加密狗出错
#define		TH_ERR_READDOG						   -3		//读取加密狗出错
#define		TH_ERR_INVALIDDOG					   -4		//不是合法的加密狗
#define		TH_ERR_DOGUSERERROR					   -5		//读取加密狗用户出错  
#define		TH_ERR_INVALIDUSER	                   -6		//不是合法的加密狗用户
#define		TH_ERR_MOUDLEERROR	                   -7		//读取模块授权出错
#define     TH_ERR_INVALIDMOUDLE	               -8		//模块没有合法授权
#define     TH_ERR_DATABASEFULL					   -9		//特征库已满，无法再入库
#define		TH_ERR_DOGTIMEOUT					   -10		//授权已过期

#define     TH_ERR_INVALIDCALL					   -99		//非法调用
#define     TH_ERR_EXCEPTION					   -100		//异常
#define     TH_ERR_CANCELENROLL		                9		//取消本次捕获
#define     TH_ERR_THREADLIMIT						20		//调用线程数超过规定数量

#define		TH_ERR_MEMORYALLOC						2		//内存分配错误
#define		TH_ERR_DATACRC							3		//数据文件CRC校验错误
#define		TH_ERR_GETMODULEPATH					4		//无法得到dll所在路径
#define		TH_ERR_FILEIO							5		//文件I/O错误
#define		TH_ERR_MODENOTMATCH						6		//调用模式与初始化模式不匹配
#define		TH_ERR_INVALIDFORMAT					7		//不支持的图像格式
#define		TH_ERR_INVALIDWIDTH						8		//图像宽度必须是8的整数倍


#ifdef __cplusplus
}	// extern "C"
#endif

#endif // !defined(__TH_ERRORDEF_INCLUDE_H__)
