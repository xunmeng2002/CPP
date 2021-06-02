#ifndef	__STEP_API_H__
#define __STEP_API_H__


	//�û����
	#define HANDLE_USER     void*
	
	//�����Ӧ����
	#define HANDLE_REQUEST  void*
	#define HANDLE_RESPONSE void*

	
	typedef int	(* __STEPRequestCallBack)(HANDLE_USER pInterface, HANDLE_RESPONSE pRes);
	typedef struct {
		__STEPRequestCallBack	pSTEPRequestCallBack;	//����Ӧ������͵Ļص�����
	} tagMainFuncPtr;

#ifdef STEP_API_EXPORTS
#ifdef	WINDOWSCODE
	#define STEP_API extern "C"  __declspec(dllexport)
#else
#define	STEP_API		extern "C"
#endif

	// ��̬���ʼ��������
	// ���ش���ţ�0�ɹ�������ʧ��
	STEP_API	int			StepApi_Init();
	STEP_API	int			StepApi_Release();			// ��̬���ͷź���

	//�汾��101֮��Ӧ����е����ı���ΪUTF8;
	//�汾��102֮���޸�StepApi_Request�ӿڣ�ReqNO��������м�����п��ƣ�
	//�ڽӿڷ���funcno���ܺš�ReqNO����ţ�������Լ��������ݡ�
	STEP_API	int			StepApi_GetApiVersion();	// ��ȡ�汾��

	// �����������󷵻�0ʱ��ʾ�ɹ���������ʾʧ��
	STEP_API	HANDLE_USER	StepApi_CreateUser();		// �����û�
	STEP_API	int			StepApi_CloseUser(HANDLE_USER pInterface);		// �ر��û�

	// ���÷�����,��ʽ��ip:port��ע�����ΪNULLʱ����ʾ��յ�ַ��Ϣ�������������Ϣ������-1��ʾ��ӵ�ַ����,����>=0��ʾ��Ӻ�ĵ�ַ����
	//Э��://ip:port/name:pwd@proxyIP:proxyPort;fens=true;gates=true;addrtype=0(0/��:���׵�ַ 1:���ڵ�ַ 2:��ѯ��ַ)
	STEP_API	int			StepApi_SetAddr(HANDLE_USER pInterface, const char* pAddr);	
	STEP_API	int			StepApi_SetHQAddr(HANDLE_USER pInterface, const char* pAddr);	

	STEP_API	int			StepApi_SetConfigPath(HANDLE_USER, const char*);

	//���ûص�����ָ��
	STEP_API	int			StepApi_SetCallBackFunc(tagMainFuncPtr*	MainFunc, int size);


	STEP_API	HANDLE_REQUEST	StepApi_CreateRequestHandle(HANDLE_USER pInterface);		// ���������Ӧ����
	STEP_API	HANDLE_RESPONSE	StepApi_CreateResponseHandle(HANDLE_USER pInterface);		// ���������Ӧ����
	STEP_API	int			StepApi_ReleaseMemory(HANDLE_USER pInterface, HANDLE_REQUEST pReq);		// �ͷŴ��������ݾ��

//	STEP_API	int 		StepApi_Request(HANDLE_USER pInterface, HANDLE_REQUEST pReq, int funcno, int ReqNO);	// ��������
	STEP_API	int 		StepApi_Request(HANDLE_USER pInterface, HANDLE_REQUEST pReq, HANDLE_RESPONSE pRes);	// ��������

	//��������HANDLE_REQUEST�Ŀ���
	STEP_API	void 		StepApi_PBSTEP_Init(HANDLE_REQUEST pData);	// ��ʼ�����
	STEP_API	void 		StepApi_PBSTEP_Free(HANDLE_REQUEST pData);	// �ͷž������ڴ�

	//��ʼ����ǰ��
	STEP_API	void		StepApi_PBSTEP_InitRecord(HANDLE_REQUEST pData);

	//���һ�У���ָ��ǰ��
	STEP_API	int			StepApi_PBSTEP_AppendRecord(HANDLE_REQUEST pData);
	

	//ɾ����ǰ�У������³�ʼ����ǰ�У��統ǰ�в����ڣ��򷵻�-1����ɾ������Խ�磬����-1
	STEP_API	int			StepApi_PBSTEP_DeleteCurrRecord(HANDLE_REQUEST pData);

	//����true��ʾ��¼���ڣ������ʾ��¼������
	STEP_API	bool		StepApi_PBSTEP_GotoFirst(HANDLE_REQUEST pData);
	STEP_API	bool		StepApi_PBSTEP_GotoNext(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetCurrRecNo(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetRecNum(HANDLE_REQUEST pData);

	STEP_API	int			StepApi_PBSTEP_GetTotalRecNum(HANDLE_REQUEST pData);

	//STEP_API	void		StepApi_PBSTEP_SetTotalRecNum(HANDLE_REQUEST pData, int num);

	//�ֶ�������Ϣ(Setϵ�л�����Ƿ�����ͬ�ֶΣ�Addϵ��ֱ������β�������)
	STEP_API	void		StepApi_PBSTEP_SetFieldValueINT(HANDLE_REQUEST pData, int id, int value);
	STEP_API	void		StepApi_PBSTEP_SetFieldValueString(HANDLE_REQUEST pData, int id, const char* value);	//ԭ������ֵ��������utf8��ʽ
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//��valueת��utf8��ʽ
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);//��value����
	//ֻ��������ݵ���ǰ��¼��������ظ��ֶΣ����ﲻ�жϣ��ɵ��������о���
	STEP_API	void		StepApi_PBSTEP_AddFieldValueINT(HANDLE_REQUEST pData, int id, int value);
	STEP_API	void		StepApi_PBSTEP_AddFieldValueString(HANDLE_REQUEST pData, int id, const char* value);		//ԭ�����ֵ��������utf8��ʽ
	//STEP_API	void		StepApi_PBSTEP_AddFieldValueString_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//��valueת��utf8
    //STEP_API	void		StepApi_PBSTEP_AddFieldValueString_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);	//��value����

	//����false��ʾ��ӦID���ؿ�ֵ
	STEP_API	int			StepApi_PBSTEP_GetFieldValueInt(HANDLE_REQUEST pData,  int id);
	STEP_API	bool		StepApi_PBSTEP_GetFieldValueString(HANDLE_REQUEST pData, int id, char* out, int size);		//ԭʼUTF8��ʽֵ
	//STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, int id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_Encrypted(HANDLE_REQUEST pData, int id, char* out, int size, const char* desKey);//��ȡ�����ֶ�����
	STEP_API	bool		StepApi_PBSTEP_IsEmptyRec(HANDLE_REQUEST pData);


	//������¼���ֶ���Ϣ
	STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValueString(HANDLE_REQUEST pData, int id, const char* value);	//ԭ������ֵ��������utf8��ʽ
	STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValueINT(HANDLE_REQUEST pData, int id, int value);			
	//STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, int id, const char* value);	//��valueת��utf8��ʽ
	//STEP_API	void		StepApi_PBSTEP_SetBaseRecFieldValue_Encrypt(HANDLE_REQUEST pData, int id, const char* value, const char* desKey);	//��value����

	STEP_API	int			StepApi_PBSTEP_GetBaseRecFieldValueINT(HANDLE_REQUEST pData, int id);
	STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString(HANDLE_REQUEST pData, int id, char* out, int size);	//ԭʼUTF8��ʽֵ
	//STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, int id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetBaseRecFieldValueString_Encrypted(HANDLE_REQUEST pData, int id, char* out, int size, const char* desKey);//��ȡ�����ֶ�����
    
    //��������͸��
    //͸�����ܺ�Ϊָ�����ܺ����䣬�ֶ�������Ϊ�ַ������������ṩ�ַ���ʽ���ֶ����ӿ�
	//STEP_API	void		StepApi_PBSTEP_SetFieldValueINT(HANDLE_REQUEST pData, const char* id, int value);
	STEP_API	void		StepApi_PBSTEP_SetFieldValueString_StringID(HANDLE_REQUEST pData, const char* id, const char* value);	//ԭ������ֵ��������utf8��ʽ
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_ChangeToUTF8(HANDLE_REQUEST pData, const char* id, const char* value);	//��valueת��utf8��ʽ
	//һ���������ֶζ���Ҫ���ܣ���Ҫ���ĵ���������
	//STEP_API	void		StepApi_PBSTEP_SetFieldValue_Encrypt(HANDLE_REQUEST pData, const char* id, const char* value, const char* desKey);//��value����

	//STEP_API	int			StepApi_PBSTEP_GetFieldValueInt(HANDLE_REQUEST pData,  const char* id);
	STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_StringID(HANDLE_REQUEST pData, const char* id, char* out, int size);	//ԭʼUTF8��ʽֵ
	//STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_ChangeUTF8ToAnsi(HANDLE_REQUEST pData, const char* id, char* out, int size);
    //STEP_API	bool		StepApi_PBSTEP_GetFieldValueString_Encrypted(HANDLE_REQUEST pData, const char* id, char* out, int size, const char* desKey);//��ȡ�����ֶ�����
	
	//���½ӿ����ڱ����ֶ�
	//����Ż�ȡ�ֶ���Ϣ�������ݺ�ID,pos��0��ʼ
	STEP_API	int			StepApi_PBSTEP_GetBaseRecFieldByPos(HANDLE_REQUEST pData, int pos, char* id, int id_len, char* out, int out_len);	//�������<=0����ʾû���ֶ���,Utf8
	STEP_API	int			StepApi_PBSTEP_GetFieldByPos(HANDLE_REQUEST pData, int pos, char* id, int id_len, char* out, int out_len);	//�������<=0����ʾû���ֶ���,Utf8

	//���ڼ���    
    STEP_API	int  		StepApi_PBSTEP_EncryptValueString(HANDLE_USER pInterface, const char* value, char* out, int& out_len, const char* desKey);
//    STEP_API	int  		StepApi_PBSTEP_DecryptValueString(HANDLE_USER pInterface, char* value, char* out, int& out_len, const char* desKey);
	
#else
	typedef int (* __StepApi_Init)();

	typedef int	(*	__StepApi_Release)();

	typedef int	(*	__StepApi_GetApiVersion)();			// ��ȡ�汾��
	
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
