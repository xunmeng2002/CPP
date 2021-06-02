#ifndef	__STEP_API_H__
#define __STEP_API_H__


	//用户句柄
	#define HANDLE_USER     void*
	
	//请求或应答句柄
	#define HANDLE_REQUEST  void*
	#define HANDLE_RESPONSE void*

	
	typedef int	(* __STEPRequestCallBack)(HANDLE_USER pInterface, HANDLE_RESPONSE pRes);
	typedef struct {
		__STEPRequestCallBack	pSTEPRequestCallBack;	//请求应答或推送的回调函数
	} tagMainFuncPtr;

#ifdef STEP_API_EXPORTS
#ifdef	WINDOWSCODE
	#define STEP_API extern "C"  __declspec(dllexport)
#else
#define	STEP_API		extern "C"
#endif

	// 动态库初始化函数，
	// 返回错误号，0成功，负数失败
	STEP_API	int			StepApi_Init();
	STEP_API	int			StepApi_Release();			// 动态库释放函数

	//版本号101之后：应答包中的中文编码为UTF8;
	//版本号102之后：修改StepApi_Request接口，ReqNO请求号由中间件进行控制，
	//在接口返回funcno功能号、ReqNO请求号，错误号以及错误内容。
	STEP_API	int			StepApi_GetApiVersion();	// 获取版本号

	// 以下所有请求返回0时表示成功，负数表示失败
	STEP_API	HANDLE_USER	StepApi_CreateUser();		// 创建用户
	STEP_API	int			StepApi_CloseUser(HANDLE_USER pInterface);		// 关闭用户

	// 设置服务器,格式：ip:port，注意参数为NULL时，表示清空地址信息，否则是添加信息，返回-1表示添加地址满了,返回>=0表示添加后的地址数量
	//协议://ip:port/name:pwd@proxyIP:proxyPort;fens=true;gates=true;addrtype=0(0/空:交易地址 1:银期地址 2:查询地址)
	STEP_API	int			StepApi_SetAddr(HANDLE_USER pInterface, const char* pAddr);	
	STEP_API	int			StepApi_SetHQAddr(HANDLE_USER pInterface, const char* pAddr);	

	STEP_API	int			StepApi_SetConfigPath(HANDLE_USER, const char*);

	//设置回调函数指针
	STEP_API	int			StepApi_SetCallBackFunc(tagMainFuncPtr*	MainFunc, int size);


	STEP_API	HANDLE_REQUEST	StepApi_CreateRequestHandle(HANDLE_USER pInterface);		// 创建请求或应答句柄
	STEP_API	HANDLE_RESPONSE	StepApi_CreateResponseHandle(HANDLE_USER pInterface);		// 创建请求或应答句柄
	STEP_API	int			StepApi_ReleaseMemory(HANDLE_USER pInterface, HANDLE_REQUEST pReq);		// 释放创建的数据句柄

//	STEP_API	int 		StepApi_Request(HANDLE_USER pInterface, HANDLE_REQUEST pReq, int funcno, int ReqNO);	// 处理请求
	STEP_API	int 		StepApi_Request(HANDLE_USER pInterface, HANDLE_REQUEST pReq, HANDLE_RESPONSE pRes);	// 处理请求

	//以下用于HANDLE_REQUEST的控制
	STEP_API	void 		StepApi_PBSTEP_Init(HANDLE_REQUEST pData);	// 初始化句柄
	STEP_API	void 		StepApi_PBSTEP_Free(HANDLE_REQUEST pData);	// 释放句柄里的内存

	//初始化当前行
	STEP_API	void		StepApi_PBSTEP_InitRecord(HANDLE_REQUEST pData);

	//添加一行，并指向当前行
	STEP_API	int			StepApi_PBSTEP_AppendRecord(HANDLE_REQUEST pData);
	

	//删除当前行，并重新初始化当前行，如当前行不存在，则返回-1，如删除后已越界，返回-1
	STEP_API	int			StepApi_PBSTEP_DeleteCurrRecord(HANDLE_REQUEST pData);

	//返回true表示记录存在，否则表示记录不存在
	STEP_API	bool		StepApi_PBSTEP_GotoFirst(HANDLE_REQUEST pData);
	STEP_API	bool		StepApi_PBSTEP_GotoNext(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetCurrRecNo(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetRecNum(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetTotalRecNum(HANDLE_REQUEST pData);

	//STEP_API	void		StepApi_PBSTEP_SetTotalRecNum(HANDLE_REQUEST pData, int num);

	//字段内容信息(Set系列会查找是否有相同字段，Add系列直接在行尾添加内容)
	STEP_API	void		StepApi_PBSTEP_SetFieldValueINT(HANDLE_REQUEST pData, int id, int value);
	STEP_API	void		StepApi_PBSTEP_SetFieldValueString(HANDLE_REQUEST pData, int id, const char* value);	//原样设置值，建议用utf8格式
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//将value转成utf8格式
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);//将value加密
	//只有添加数据到当前记录，如果有重复字段，这里不判断，由调用者自行决定
	STEP_API	void		StepApi_PBSTEP_AddFieldValueINT(HANDLE_REQUEST pData, int id, int value);
	STEP_API	void		StepApi_PBSTEP_AddFieldValueString(HANDLE_REQUEST pData, int id, const char* value);		//原样添加值，建议用utf8格式
	//STEP_API	void		StepApi_PBSTEP_AddFieldValueString_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//将value转成utf8
    //STEP_API	void		StepApi_PBSTEP_AddFieldValueString_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);	//将value加密

	//返回false表示对应ID返回空值
	STEP_API	int			StepApi_PBSTEP_GetFieldValueInt(HANDLE_REQUEST pData,  int id);
	STEP_API	bool		StepApi_PBSTEP_GetFieldValueString(HANDLE_REQUEST pData, int id, char* out, int size);		//原始UTF8格式值
	//STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, int id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_Encrypted(HANDLE_REQUEST pData, int id, char* out, int size, const char* desKey);//获取加密字段内容
	STEP_API	bool		StepApi_PBSTEP_IsEmptyRec(HANDLE_REQUEST pData);


	//基本记录的字段信息
	STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValueString(HANDLE_REQUEST pData, int id, const char* value);	//原样设置值，建议用utf8格式
	STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValueINT(HANDLE_REQUEST pData, int id, int value);			
	//STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//将value转成utf8格式
	//STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValue_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);	//将value加密

	STEP_API	int			StepApi_PBSTEP_GetBaseRecFieldValueINT(HANDLE_REQUEST pData, int id);
	STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString(HANDLE_REQUEST pData, int id, char* out, int size);	//原始UTF8格式值
	//STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, int id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString_Encrypted(HANDLE_REQUEST pData, int id, char* out, int size, const char* desKey);//获取加密字段内容
    
    //以下用于透传
    //透传功能号为指定功能号区间，字段名可能为字符串，这里特提供字符串式的字段名接口
	//STEP_API	void		StepApi_PBSTEP_SetFieldValueINT(HANDLE_REQUEST pData, const char* id, int value);
	STEP_API	void		StepApi_PBSTEP_SetFieldValueString_StringID(HANDLE_REQUEST pData, const char* id, const char* value);	//原样设置值，建议用utf8格式
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, const char* id, const char* value);	//将value转成utf8格式
	//一般是密码字段都需要加密，需要在文档里描述。
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_Encrypt(HANDLE_REQUEST pData, const char* id, const char* value, const char* desKey);//将value加密

	//STEP_API	int			StepApi_PBSTEP_GetFieldValueInt(HANDLE_REQUEST pData,  const char* id);
	STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_StringID(HANDLE_REQUEST pData, const char* id, char* out, int size);	//原始UTF8格式值
	//STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, const char* id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_Encrypted(HANDLE_REQUEST pData, const char* id, char* out, int size, const char* desKey);//获取加密字段内容
	
	//以下接口用于遍历字段
	//按序号获取字段信息返回内容和ID,pos从0开始
	STEP_API	int			StepApi_PBSTEP_GetBaseRecFieldByPos(HANDLE_REQUEST pData, int pos, char* id, int id_len, char* out, int out_len);	//如果返回<=0，表示没有字段了,Utf8
	STEP_API	int			StepApi_PBSTEP_GetFieldByPos(HANDLE_REQUEST pData, int pos, char* id, int id_len, char* out, int out_len);	//如果返回<=0，表示没有字段了,Utf8

	//用于加密    
    STEP_API	int  		StepApi_PBSTEP_EncryptValueString(HANDLE_USER pInterface, const char* value, char* out, int& out_len, const char* desKey);
//    STEP_API	int  		StepApi_PBSTEP_DecryptValueString(HANDLE_USER pInterface, char* value, char* out, int& out_len, const char* desKey);
	
#else
	typedef int (* __StepApi_Init)();

	typedef int	(*	__StepApi_Release)();

	typedef int	(*	__StepApi_GetApiVersion)();			// 获取版本号
	
	typedef HANDLE_USER	(* __StepApi_CreateUser)();

	typedef int	(* __StepApi_CloseUser)(HANDLE_USER );
	
	typedef int	(* __StepApi_SetAddr)(HANDLE_USER , const char* );

	typedef int	(* __StepApi_SetHQAddr)(HANDLE_USER , const char* );
	
	typedef int	(* __StepApi_SetCallBackFunc)(tagMainFuncPtr*	, int );
	
	typedef HANDLE_REQUEST	(* __StepApi_CreateRequestHandle)(HANDLE_USER );
	
	typedef HANDLE_RESPONSE	(* __StepApi_CreateResponseHandle)(HANDLE_USER );
	
	typedef int	(* __StepApi_ReleaseMemory)(HANDLE_USER , HANDLE_REQUEST );

	typedef int (* __StepApi_Request)(HANDLE_USER , HANDLE_REQUEST , HANDLE_RESPONSE ); 
	
	typedef void 		(* __StepApi_PBSTEP_Init)(HANDLE_REQUEST );
	
	typedef void 		(* __StepApi_PBSTEP_Free)(HANDLE_REQUEST );
	
	typedef void		(* __StepApi_PBSTEP_InitRecord)(HANDLE_REQUEST );
	
	typedef int			(* __StepApi_PBSTEP_AppendRecord)(HANDLE_REQUEST );
	
	typedef int			(* __StepApi_PBSTEP_DeleteCurrRecord)(HANDLE_REQUEST );
	
	typedef bool		(* __StepApi_PBSTEP_GotoFirst)(HANDLE_REQUEST );
	
	typedef bool		(* __StepApi_PBSTEP_GotoNext)(HANDLE_REQUEST );
	
	typedef int			(* __StepApi_PBSTEP_GetCurrRecNo)(HANDLE_REQUEST );
	
	typedef int			(* __StepApi_PBSTEP_GetRecNum)(HANDLE_REQUEST );
	
	typedef int			(* __StepApi_PBSTEP_GetTotalRecNum)(HANDLE_REQUEST );
	
	typedef void		(* __StepApi_PBSTEP_SetFieldValueINT)(HANDLE_REQUEST , int , int );
	
	typedef void		(* __StepApi_PBSTEP_SetFieldValueString)(HANDLE_REQUEST , int , const char* );

	typedef void		(* __StepApi_PBSTEP_AddFieldValueINT)(HANDLE_REQUEST , int , int );
	
	typedef void		(* __StepApi_PBSTEP_AddFieldValueString)(HANDLE_REQUEST , int , const char* );
	
	typedef int			(* __StepApi_PBSTEP_GetFieldValueInt)(HANDLE_REQUEST ,  int );
	
	typedef bool		(* __StepApi_PBSTEP_GetFieldValueString)(HANDLE_REQUEST , int , char* , int );
	
	typedef bool		(* __StepApi_PBSTEP_IsEmptyRec)(HANDLE_REQUEST );
	
	typedef void		(* __StepApi_PBSTEP_SetBaseRecFieldValueString)(HANDLE_REQUEST , int , const char* );
	
	typedef void		(* __StepApi_PBSTEP_SetBaseRecFieldValueINT)(HANDLE_REQUEST , int , int );
	
	typedef int			(* __StepApi_PBSTEP_GetBaseRecFieldValueINT)(HANDLE_REQUEST , int );
	
	typedef bool		(* __StepApi_PBSTEP_GetBaseRecFieldValueString)(HANDLE_REQUEST , int , char* , int );
    
	typedef void		(* __StepApi_PBSTEP_SetFieldValueString_StringID)(HANDLE_REQUEST , const char* , const char* );

	typedef bool		(* __StepApi_PBSTEP_GetFieldValueString_StringID)(HANDLE_REQUEST , const char* , char* , int );
	
	typedef int			(* __StepApi_PBSTEP_GetBaseRecFieldByPos)(HANDLE_REQUEST , int , char*, int, char* , int );

	typedef int			(* __StepApi_PBSTEP_GetFieldByPos)(HANDLE_REQUEST , int , char*, int, char* , int );

	typedef int  		(* __StepApi_PBSTEP_EncryptValueString)(HANDLE_USER , const char* , char* , int& , const char* );

	typedef int			(* __StepApi_PBSTEP_SetConfigPath)(HANDLE_USER, const char*  );

	
#endif

#endif
