#ifndef _FEITIAN_ET199_32_H_
#define _FEITIAN_ET199_32_H_

#ifdef __cplusplus
	extern "C" {
#endif
	#define   ET_S_SUCCESS						0x00000000	/** 操作成功*/
	#define   ET_E_KEY_REMOVED					0xF0000001	/** 设备未连接，或者被移除*/
	#define   ET_E_INVALID_PARAMETER				0xF0000002	/** 参数错误*/
	#define   ET_E_COMM_ERROR					0xF0000003	/** 通讯错误，例如数据传输超时*/
	#define   ET_E_INSUFFICIENT_BUFFER				0xF0000004	/** 缓冲区空间不足*/
	#define   ET_E_NO_LIST						0xF0000005	/** 没有找到设备列表*/
	#define   ET_E_DEVPIN_NOT_CHECK					0xF0000006	/** 开发商口令没有验证*/
	#define   ET_E_USERPIN_NOT_CHECK				0xF0000007	/** 用户口令没有验证*/
	#define	  ET_E_RSA_FILE_FORMAT_ERROR				0xF0000008	/** RSA文件格式错误*/
	#define   ET_E_DIR_NOT_FOUND					0xF0000009	/** 目录没有找到*/
	#define   ET_E_ACCESS_DENIED					0xF000000A	/** 访问被拒绝*/
	#define   ET_E_ALREADY_INITIALIZED				0xF000000B	/** 产品已经初始化*/
	#define   ET_E_INCORRECT_PIN					0xF0000C00	/** 密码不正确*/
	#define   ET_E_DF_SIZE						0xF000000D	/** 指定的目录空间大小不够*/
	#define   ET_E_FILE_EXIST					0xF000000E	/** 文件已存在*/
	#define   ET_E_UNSUPPORTED					0xF000000F	/** 功能不支持或尚未建立文件系统*/
	#define   ET_E_FILE_NOT_FOUND					0xF0000010	/** 未找到指定的文件*/
	#define	  ET_E_ALREADY_OPENED					0xF0000011	/** 卡已经被打开*/
	#define   ET_E_DIRECTORY_EXIST					0xF0000012	/** 目录已存在*/
	#define   ET_E_CODE_RANGE					0xF0000013	/** 虚拟机内存地址溢出*/
	#define   ET_E_INVALID_POINTER					0xF0000014	/** 虚拟机错误的指针 */
	#define   ET_E_GENERAL_FILESYSTEM				0xF0000015	/** 常规文件系统错误 */
	#define   ET_E_OFFSET_BEYOND					0xF0000016	/** 文件偏移量超出文件大小*/
	#define   ET_E_FILE_TYPE_MISMATCH				0xF0000017	/** 文件类型不匹配*/
	#define   ET_E_PIN_BLOCKED					0xF0000018	/** PIN码锁死*/
	#define   ET_E_INVALID_CONTEXT					0xF0000019	/** ETContext 参数错误*/
	#define   ET_E_SHARING_VIOLATION				0XF000001A	/** 另一个程序正在使用此文件，进程无法访问*/
	#define   ET_E_ERROR_UNKNOWN					0xFFFFFFFF	/** 未知的错误*/
	#define   ET_E_LOAD_FILE_FAILED					0xF0001001
	
	#define	  MAX_ATR_LEN						16		/** 最大ATR长度 */
	#define   MAX_ID_LEN						8		/** 最大硬件ID长度*/
	
	#define   ET_USER_PIN						0x00000000	/** 用户PIN*/
	#define   ET_DEV_PIN						0x00000001	/** 开发商PIN*/
	
	#define   ET_CREATE_NEW						0x00000000	/** 创建新文件*/
	#define   ET_UPDATE_FILE					0x00000001	/** 更新数据文件*/
	
	#define   ET_CREATE_ROOT_DIR					0x00000000	/** 创建根目录*/
	#define   ET_CREATE_SUB_DIR					0x00000001	/** 创建当前目录的子目录*/
	
	
	#define   ET_LED_UP						0x00000001	/** LED灯亮*/
	#define   ET_LED_DOWN						0x00000002	/** LED灯灭*/
	#define   ET_LED_WINK						0x00000003	/** LED灯闪烁*/
	
	
	#define   ET_GET_DEVICE_TYPE					0x00000011	/** 获得设备类型*/
	#define   ET_GET_SERIAL_NUMBER					0x00000012	/** 获取硬件序列号*/
	#define   ET_GET_DEVICE_USABLE_SPACE				0x00000013	/** 获得设备空间大小*/
	#define   ET_GET_DEVICE_ATR					0x00000014	/** 获得设备ATR*/
	#define   ET_GET_CUSTOMER_NAME					0x00000015	/** 获得客户号*/
	#define   ET_GET_MANUFACTURE_DATE				0x00000016	/** 获得生产日期*/
	#define   ET_GET_DF_AVAILABLE_SPACE				0x00000017	/** 获得当前目录的剩余空间*/
	#define   ET_GET_EF_INFO					0x00000018	/** 获得指定文件信息*/
	#define   ET_GET_COS_VERSION					0x00000019	/** 获得COS版本信息*/
	#define   ET_GET_CURRENT_TIME					0x00000020	/** 获得时钟锁的当前时间*/
	
	#define   ET_SET_DEVICE_ATR					0x00000021	/** 设置设备ATR*/
	#define   ET_SET_DEVICE_TYPE					0x00000022	/** 设置设备类型*/
	#define   ET_SET_SHELL_KEY					0x00000023	/** 设置8字节外壳加密种子码*/
	#define	  ET_SET_CUSTOMER_NAME					0x00000024	/** 输入一个种子, 产生客户号*/
	
	#define   ET_RESET_DEVICE					0x00000031	/** 复位设备*/
	#define   ET_GET_PRODUCT_NAMEID					0x00000032	/** 获取产品名称*/
	
	
	#define   ET_DEVICE_TYPE_PKI					0x01		/** 身份验证锁类型*/
	#define   ET_DEVICE_TYPE_DONGLE					0x02		/** 加密锁类型*/
	#define   ET_DEVICE_TYPE_EMPTY					0x04		/** 空锁类型*/
	
	
	#define   ET_DEFAULT_TRY					0xff		/** 默认重试次数（无限次）*/
	
	#define	  ET_DEFAULT_DEV_PIN					(BYTE *)"123456781234567812345678"
	#define   ET_DEFAULT_USER_PIN					(BYTE *)"12345678"
	#define   ET_DEV_PIN_LEN					24
	#define   ET_USER_PIN_LEN					8
	
	
	#define	 ET_EXCLUSIVE_MODE					0		/** 独占模式*/
	#define  ET_SHARE_MODE						1		/** 共享模式*/
	
	#ifndef	 ET199_FILE_TYPE
		#define  ET199_FILE_TYPE
		#define  FILE_TYPE_EXE					0		/** 可执行文件*/
		#define  FILE_TYPE_DATA					1		/** 数据文件*/
		#define  FILE_TYPE_RSA_PUBLIC				2		/** RSA 公钥文件*/
		#define  FILE_TYPE_RSA_PRIVATE				3		/** RSA 私钥文件*/
		#define  FILE_TYPE_INTERNAL_EXE				4		/** 可执行文件（不可读写）*/
	#endif
	
	typedef struct
	{
		DWORD		dwIndex;				/** 以0开始的设备索引*/
		DWORD		dwVersion;				/** 设备COS版本*/
		HANDLE		hLock;					/** 设备句柄*/
		BYTE		reserve[12];				/** 保留*/
		DWORD		dwCustomer;				/** 客户号*/
		BYTE		bAtr[MAX_ATR_LEN];			/** ATR*/
		BYTE		bID[MAX_ID_LEN];			/** 硬件ID*/
		DWORD		dwAtrLen ;				/** ATR长度*/
	}
	ET_CONTEXT,*PET_CONTEXT;
	
	typedef struct
	{
		BYTE		byYear;					/** 年*/
		BYTE		byMonth;				/** 月*/
		BYTE		byDay;					/** 日*/
		BYTE		byHour;					/** 时*/
		BYTE		byMinute;				/** 分*/
		BYTE		bySecond;				/** 秒*/
	}
	ET_MANUFACTURE_DATE,*PET_MANUFACTURE_DATE;
	
	
	#ifndef ET199_FILEINFO
		#define ET199_FILEINFO
		
		#pragma pack(push,1)		
		typedef struct  {
			WORD	wFileID;																/** 文件ID*/
			BYTE	bFileType;																/** 文件类型*/
			WORD	wFileSize;																/** 文件大小*/
		}
		EFINFO,*PEFINFO;
		#pragma pack(pop)
	#endif
	
	
	typedef struct _ET_CREATEDIRINFO {
		DWORD	dwCreateDirInfoSize;													/** 结构体大小*/
		BYTE	szAtr[MAX_ATR_LEN];													/** ATR 字符串*/
	}ET_CREATEDIRINFO,*PET_CREATEDIRINFO;
	
	typedef struct _ET_OPENINFO {
		DWORD	dwOpenInfoSize;														/** 结构体大小*/
		DWORD	dwShareMode;															/** 共享模式*/
	} ET_OPENINFO,*PET_OPENINFO;
	
	/*====================ET199 COS RSA TLV==================================================*/
	#define STRUCT_COS_TLV_(Tlv_Length)										\
	struct																	\
	{																		\
		BYTE	bTagHigh;														\
		BYTE	bTagLow;														\
		BYTE	bLenHigh;														\
		BYTE	bLenLow;														\
		BYTE	bData[Tlv_Length];												\
	}
	/**===============ET199 COS RSA 公钥====================================================*/
	
	#define STRUCT_COS_RSA_PUBLIC_KEY_(Bits)								\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/8)		n;										\
		STRUCT_COS_TLV_(4)		e;										\
	}
	
	typedef STRUCT_COS_RSA_PUBLIC_KEY_(512 )	COS_RSA_PUBLIC_KEY_512;
	typedef STRUCT_COS_RSA_PUBLIC_KEY_(1024)	COS_RSA_PUBLIC_KEY_1024;
	typedef STRUCT_COS_RSA_PUBLIC_KEY_(2048)	COS_RSA_PUBLIC_KEY_2048;
	
	/*===============ET199 COS RSA 私钥=====================================================*/
	#define STRUCT_COS_RSA_CRT_PRIVATE_KEY_(Bits)								\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/16)	p;										\
		STRUCT_COS_TLV_(Bits/16)	q;										\
		STRUCT_COS_TLV_(Bits/16)	dp;										\
		STRUCT_COS_TLV_(Bits/16)	dq;										\
		STRUCT_COS_TLV_(Bits/16)	InvQ;									\
	}
	
	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(512 )	COS_RSA_CRT_PRIVATE_KEY_512;
	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(1024)	COS_RSA_CRT_PRIVATE_KEY_1024;
	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(2048)	COS_RSA_CRT_PRIVATE_KEY_2048;
	
	#define STRUCT_COS_RSA_PRIVATE_KEY_(Bits)								\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/8)	n;										\
		STRUCT_COS_TLV_(Bits/8)	d;										\
	}
	typedef STRUCT_COS_RSA_PRIVATE_KEY_(512 )	COS_RSA_PRIVATE_KEY_512;
	typedef STRUCT_COS_RSA_PRIVATE_KEY_(1024)	COS_RSA_PRIVATE_KEY_1024;
	typedef STRUCT_COS_RSA_PRIVATE_KEY_(2048)	COS_RSA_PRIVATE_KEY_2048;
	
	
	DWORD WINAPI ETEnum(
		OUT     ET_CONTEXT	*pETContextList,
		IN OUT  DWORD		*pdwDeviceCount
	);
	
	DWORD WINAPI ETOpen(
		IN OUT  ET_CONTEXT	*pETCtx
	);
	
	DWORD WINAPI ETOpenEx(
		IN OUT ET_CONTEXT	*pETCtx,
		IN	   ET_OPENINFO	*pETOpenInfo
	);
	
	DWORD WINAPI ETClose(
		IN OUT  ET_CONTEXT	*pETCtx
	);
	
	DWORD WINAPI ETControl(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      DWORD			dwCtlCode,
		IN      CONST VOID		*pInBuffer,
		IN      DWORD			dwInBufferLen,
		OUT     VOID			*pOutBuffer,
		IN      DWORD			dwOutBufferLen,
		OUT     DWORD			*pdwBytesReturned
	);
	
	
	DWORD WINAPI ETCreateDir(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszDirID,
		IN      DWORD			dwDirSize,
		IN      DWORD			dwFlags
	);
	
	DWORD WINAPI ETChangeDir(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszPath
	);
	
	
	DWORD WINAPI ETEraseDir(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszDirID
	);
	
	
	DWORD WINAPI ETVerifyPin(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      CONST BYTE		*pbPin,
		IN      DWORD			dwPinLen,
		IN      DWORD			dwPinType
	);
	
	
	DWORD WINAPI ETChangePin(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      CONST BYTE		*pbOldPin,
		IN      DWORD			dwOldPinLen,
		IN      CONST BYTE		*pbNewPin,
		IN      DWORD			dwNewPinLen,
		IN      DWORD			dwPinType,
		IN	BYTE			byPinTryCount
	);
	
	DWORD WINAPI ETWriteFile(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszFileID,
		IN      DWORD			dwOffset,
		IN      CONST VOID		*pBuffer,
		IN      DWORD			dwBufferSize
	);
	
	DWORD WINAPI ETWriteFileEx(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszFileID,
		IN      DWORD			dwOffset,
		IN      CONST VOID		*pBuffer,
		IN      DWORD			dwBufferSize,
		IN      DWORD			dwFileSize,
		OUT     DWORD			*pdwBytesWritten,
		IN      DWORD			dwFlags,
		IN      BYTE			bFileType
	);
	
	
	DWORD WINAPI ETExecute(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszFileID,
		IN      CONST VOID		*pInBuffer,
		IN      DWORD			dwInbufferSize,
		OUT     VOID			*pOutBuffer,
		IN      DWORD			dwOutBufferSize,
		OUT     DWORD			*pdwBytesReturned
	);
	
	
	DWORD WINAPI ETCreateDirEx(
		IN	CONST ET_CONTEXT	*pETCtx,
		IN	LPCSTR			lpszDirID,
		IN	DWORD			dwDirSize,
		IN	DWORD			dwFlags,
		IN	CONST ET_CREATEDIRINFO	*pCreateDirInfo
	);
	
	DWORD WINAPI ETCreateFile(
		IN      CONST ET_CONTEXT	*pETCtx,
		IN      LPCSTR			lpszFileID,
		IN      DWORD			dwFileSize,
		IN      BYTE			bFileType
	);
	
	
	DWORD WINAPI ETGenRsaKey(
		IN	CONST ET_CONTEXT	*pETCtx,
		IN	WORD			wKeySize,
		IN	DWORD			dwE,
		IN	LPCSTR			lpszPubFileID,
		IN	LPCSTR			lpszPriFileID,
		OUT	PVOID			pbPubKeyData,
		IN OUT	DWORD			*dwPubKeyDataSize,
		OUT	PVOID			pbPriKeyData,
		IN OUT	DWORD			*dwPriKeyDataSize
	);
	
	DWORD WINAPI ETFormatErrorMessage(
		IN	DWORD			dwRet,
		OUT	LPSTR			lpszMessage,
		IN	DWORD			dwMsgBufLen
	);

	DWORD WINAPI PETWriteFile (
		IN	ET_CONTEXT	*pETCtx,
		IN	LPCSTR		lpszFileID,
		IN	LPCSTR		lpszPCFilePath,
		IN	OUT DWORD	*pdwFileSize,
		IN	DWORD		dwFlags,
		IN	BYTE		bFileType,
		IN	OUT DWORD	*pdwBytesWritten
		);

#ifdef __cplusplus
	}
#endif

#endif
