//VzClientSDK中与环境监测相关的定义
#ifndef _VZ_CLIENT_SDK_HJ_T212_H_
#define _VZ_CLIENT_SDK_HJ_T212_H_

#include "VzClientSDK_HJT212Define.h"
#include "VzClientSDK.h"

//环境监测api
/**
*  @brief 环境报警流配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] enable 1表示开启，0表示关闭
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetHJ212AlarmStreamEnable(int iUserID, int* enable);

/**
*  @brief 环境报警流配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] enable 1表示开启，0表示关闭
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SetHJ212AlarmStreamEnable(int iUserID, int enable);
/**
*  @brief 环境串口参数配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT]  pSerial 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetHJ212Serial(int iUserID, VZ_HJT212_Serial* pSerial);

/**
*  @brief 环境串口参数配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pSerial 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SetHJ212Serial(int iUserID, VZ_HJT212_Serial* pSerial);
/**
*  @brief 环境OSD配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT] pOSD 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetHJ212OSD(int iUserID, VZ_HJT212_OSD_Readable *pOSD);

/**
*  @brief 环境OSD配置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pOSD 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SetHJ212OSD(int iUserID, VZ_HJT212_OSD_Readable *pOSD);
/**
*  @brief 环境服务器设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [OUT]  pServer 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetHJ212Server(int iUserID, VZ_HJT212_Server* pServer);

/**
*  @brief 环境服务器设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pServer 参数
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SetHJ212Server(int iUserID, VZ_HJT212_Server* pServer);
/**
*  @brief 获取设备上已配置的污染物信息，或者返回指定污染物编码对应的其他信息
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN][OUT] pItemInfo 参数，若code全部为空，获得设备已配置的污染物信息，否则，获得与code对应的其他信息
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_GetHJ212ItemInfo(int iUserID, VZ_HJT212_ItemInfo* pItemInfo);

/**
*  @brief 环境参数设置
*  @param [IN] iUserID VZC_Login函数返回的用户ID
*  @param [IN] pItemInfo 参数，设置其中对单位的设置是无效的
*  @return 返回值为0表示成功，返回其他值表示失败。
*/
VZC_DLL_EXP int __stdcall VZC_IVS_SetHJ212ItemInfo(int iUserID, VZ_HJT212_ItemInfo* pItemInfo);

#endif
