#include "PBStepApi.h"
#include "StepApiFunc.h"
#include "PBStepCallback.h"
#include "Logger.h"
#include <mutex>
using namespace std;


PBStepApi::PBStepApi()
	:m_User(nullptr)
{
}
PBStepApi::~PBStepApi()
{
}
bool PBStepApi::Init(PBStepSpi* stepSpi, const char* address, const char* fileName)
{
	m_User = StepApi_CreateUser();
	if (m_User == nullptr)
		return false;
	SetSpi(m_User, stepSpi);
	StepApi_SetAddr(m_User, address);

	tagMainFuncPtr MainFuncPtr = { 0 };
	MainFuncPtr.pSTEPRequestCallBack = StepApiCallback;
	StepApi_SetCallBackFunc(&MainFuncPtr, sizeof(MainFuncPtr));
	return true;
}

int PBStepApi::ReqSetUserInfo(PBStepReqSetUserInfoField& ReqSetUserInfo, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqSetUserInfo");
	WRITE_LOG(LogLevel::Info, "PBStepReqSetUserInfoField: QQBZ[%s] RZLJ[%s] SQWJ[%s] PZWJ[%s] LOGID[%s] RSAKEY[%s] RZMWJ[%s] JYGT[%s]", ReqSetUserInfo.QQBZ, ReqSetUserInfo.RZLJ, ReqSetUserInfo.SQWJ, ReqSetUserInfo.PZWJ, ReqSetUserInfo.LOGID, ReqSetUserInfo.RSAKEY, ReqSetUserInfo.RZMWJ, ReqSetUserInfo.JYGT);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqSetUserInfo.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 10100);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QQBZ, ReqSetUserInfo.QQBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_RZLJ, ReqSetUserInfo.RZLJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SQWJ, ReqSetUserInfo.SQWJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_PZWJ, ReqSetUserInfo.PZWJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_LOGID, ReqSetUserInfo.LOGID);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_RSAKEY, ReqSetUserInfo.RSAKEY);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_RZMWJ, ReqSetUserInfo.RZMWJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_JYGT, ReqSetUserInfo.JYGT);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqSetUserInfo: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqSecurityVerity(PBStepReqSecurityVerityField& ReqSecurityVerity, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqSecurityVerity");
	WRITE_LOG(LogLevel::Info, "PBStepReqSecurityVerityField: MYKL[%s]", ReqSecurityVerity.MYKL);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqSecurityVerity.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 4);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_MYKL, ReqSecurityVerity.MYKL);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqSecurityVerity: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqLogin(PBStepReqLoginField& ReqLogin, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqLogin");
	WRITE_LOG(LogLevel::Info, "PBStepReqLoginField: YYBDM[%s] QSDM[%s] YPBH[%s] LOCAL_IP[%s] LOCAL_MAC[%s] VERSION[%s] DLLB[%s] DTMM[%s] DTMMLB[%s] ZHLB[%s] DLZH[%s] HQDXKL[%s] HXRZ[%s] HXMM[%s] CPU[%s] ZBRQ[%s] UNIQUE_ID[%s] YPFQ[%s] JSJM[%s] BROKER_ID[%s] CP[%s] PT[%s] SJHM[%s] HXZH[%s] ZWSJ[%s] IMSI[%s] LOCAL_INFO[%s] YCBS[%s] XXWZD[%s] CTSMYBB[%s] SQM[%s] CTSBB[%s] APPID[%s]", ReqLogin.YYBDM, ReqLogin.QSDM, ReqLogin.YPBH, ReqLogin.LOCAL_IP, ReqLogin.LOCAL_MAC, ReqLogin.VERSION, ReqLogin.DLLB, ReqLogin.DTMM, ReqLogin.DTMMLB, ReqLogin.ZHLB, ReqLogin.DLZH, ReqLogin.HQDXKL, ReqLogin.HXRZ, ReqLogin.HXMM, ReqLogin.CPU, ReqLogin.ZBRQ, ReqLogin.UNIQUE_ID, ReqLogin.YPFQ, ReqLogin.JSJM, ReqLogin.BROKER_ID, ReqLogin.CP, ReqLogin.PT, ReqLogin.SJHM, ReqLogin.HXZH, ReqLogin.ZWSJ, ReqLogin.IMSI, ReqLogin.LOCAL_INFO, ReqLogin.YCBS, ReqLogin.XXWZD, ReqLogin.CTSMYBB, ReqLogin.SQM, ReqLogin.CTSBB, ReqLogin.APPID);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqLogin.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6011);
	char JYMM[256] = { 0 };
	int JYMMLen = sizeof(JYMM);
	StepApi_PBSTEP_EncryptValueString(m_User, ReqLogin.HXMM, JYMM, JYMMLen, ReqLogin.DLZH);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_JYMM, JYMM);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YYBDM, ReqLogin.YYBDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QSDM, ReqLogin.QSDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YPBH, ReqLogin.YPBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_LOCAL_IP, ReqLogin.LOCAL_IP);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_LOCAL_MAC, ReqLogin.LOCAL_MAC);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_VERSION, ReqLogin.VERSION);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_DLLB, ReqLogin.DLLB);
	char DTMM[256] = { 0 };
	int DTMMLen = sizeof(DTMM);
	StepApi_PBSTEP_EncryptValueString(m_User, ReqLogin.DTMM, DTMM, DTMMLen, ReqLogin.DTMM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_DTMM, DTMM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_DTMMLB, ReqLogin.DTMMLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_ZHLB, ReqLogin.ZHLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_DLZH, ReqLogin.DLZH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HQDXKL, ReqLogin.HQDXKL);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HXRZ, ReqLogin.HXRZ);
	char HXMM[256] = { 0 };
	int HXMMLen = sizeof(HXMM);
	StepApi_PBSTEP_EncryptValueString(m_User, ReqLogin.HXMM, HXMM, HXMMLen, ReqLogin.HXMM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HXMM, HXMM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CPU, ReqLogin.CPU);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_ZBRQ, ReqLogin.ZBRQ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_UNIQUE_ID, ReqLogin.UNIQUE_ID);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YPFQ, ReqLogin.YPFQ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_JSJM, ReqLogin.JSJM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_BROKER_ID, ReqLogin.BROKER_ID);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CP, ReqLogin.CP);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_PT, ReqLogin.PT);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SJHM, ReqLogin.SJHM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HXZH, ReqLogin.HXZH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_ZWSJ, ReqLogin.ZWSJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_IMSI, ReqLogin.IMSI);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_LOCAL_INFO, ReqLogin.LOCAL_INFO);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YCBS, ReqLogin.YCBS);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XXWZD, ReqLogin.XXWZD);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CTSMYBB, ReqLogin.CTSMYBB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SQM, ReqLogin.SQM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CTSBB, ReqLogin.CTSBB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_APPID, ReqLogin.APPID);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqLogin: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqConfirmSettlement(PBStepReqConfirmSettlementField& ReqConfirmSettlement, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqConfirmSettlement");
	WRITE_LOG(LogLevel::Info, "PBStepReqConfirmSettlementField: JYRQ[%s]", ReqConfirmSettlement.JYRQ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqConfirmSettlement.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6071);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_JYRQ, ReqConfirmSettlement.JYRQ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqConfirmSettlement: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqInsertOrder(PBStepReqInsertOrderField& ReqInsertOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqInsertOrder");
	WRITE_LOG(LogLevel::Info, "PBStepReqInsertOrderField: SCDM[%s] HYDM[%s] MMLB[%s] KPBZ[%s] TBBZ[%s] WTSL[%s] WTJG[%s] GDH[%s] XWH[%s] SJWTLB[%s] BDBZ[%s] JGLB[%s] YXQLX[%s] CJLLX[%s] ZXCJL[%s] CFTJ[%s] WTZHLX[%s] YXRQ[%s] BDBDXH[%s] GTHHBZ[%s]", ReqInsertOrder.SCDM, ReqInsertOrder.HYDM, ReqInsertOrder.MMLB, ReqInsertOrder.KPBZ, ReqInsertOrder.TBBZ, ReqInsertOrder.WTSL, ReqInsertOrder.WTJG, ReqInsertOrder.GDH, ReqInsertOrder.XWH, ReqInsertOrder.SJWTLB, ReqInsertOrder.BDBZ, ReqInsertOrder.JGLB, ReqInsertOrder.YXQLX, ReqInsertOrder.CJLLX, ReqInsertOrder.ZXCJL, ReqInsertOrder.CFTJ, ReqInsertOrder.WTZHLX, ReqInsertOrder.YXRQ, ReqInsertOrder.BDBDXH, ReqInsertOrder.GTHHBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqInsertOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6021);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqInsertOrder.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, ReqInsertOrder.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_MMLB, ReqInsertOrder.MMLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_KPBZ, ReqInsertOrder.KPBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_TBBZ, ReqInsertOrder.TBBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTSL, ReqInsertOrder.WTSL);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTJG, ReqInsertOrder.WTJG);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqInsertOrder.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqInsertOrder.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SJWTLB, ReqInsertOrder.SJWTLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_BDBZ, ReqInsertOrder.BDBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_JGLB, ReqInsertOrder.JGLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YXQLX, ReqInsertOrder.YXQLX);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CJLLX, ReqInsertOrder.CJLLX);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_ZXCJL, ReqInsertOrder.ZXCJL);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CFTJ, ReqInsertOrder.CFTJ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTZHLX, ReqInsertOrder.WTZHLX);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_YXRQ, ReqInsertOrder.YXRQ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_BDBDXH, ReqInsertOrder.BDBDXH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GTHHBZ, ReqInsertOrder.GTHHBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqInsertOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqCancelOrder(PBStepReqCancelOrderField& ReqCancelOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqCancelOrder");
	WRITE_LOG(LogLevel::Info, "PBStepReqCancelOrderField: WTBH[%s] GDH[%s] XWH[%s] SCDM[%s] KZZD[%s] HYDM[%s] WTRQ[%s] XDXW[%s]", ReqCancelOrder.WTBH, ReqCancelOrder.GDH, ReqCancelOrder.XWH, ReqCancelOrder.SCDM, ReqCancelOrder.KZZD, ReqCancelOrder.HYDM, ReqCancelOrder.WTRQ, ReqCancelOrder.XDXW);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqCancelOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6022);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTBH, ReqCancelOrder.WTBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqCancelOrder.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqCancelOrder.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqCancelOrder.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_KZZD, ReqCancelOrder.KZZD);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, ReqCancelOrder.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTRQ, ReqCancelOrder.WTRQ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XDXW, ReqCancelOrder.XDXW);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqCancelOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryPosition(PBStepQryPositionField& QryPosition, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryPosition");
	WRITE_LOG(LogLevel::Info, "PBStepQryPositionField: SCDM[%s] HYDM[%s] CXBZ[%s]", QryPosition.SCDM, QryPosition.HYDM, QryPosition.CXBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryPosition.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6014);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QryPosition.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QryPosition.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CXBZ, QryPosition.CXBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryPosition: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryPositionDetail(PBStepQryPositionDetailField& QryPositionDetail, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryPositionDetail");
	WRITE_LOG(LogLevel::Info, "PBStepQryPositionDetailField: SCDM[%s] HYDM[%s]", QryPositionDetail.SCDM, QryPositionDetail.HYDM);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryPositionDetail.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6074);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QryPositionDetail.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QryPositionDetail.HYDM);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryPositionDetail: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryTodayOrder(PBStepQryTodayOrderField& QryTodayOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTodayOrder");
	WRITE_LOG(LogLevel::Info, "PBStepQryTodayOrderField: WTBH[%s] WTHLB[%s] CDBZ[%s]", QryTodayOrder.WTBH, QryTodayOrder.WTHLB, QryTodayOrder.CDBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryTodayOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6019);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTBH, QryTodayOrder.WTBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTHLB, QryTodayOrder.WTHLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CDBZ, QryTodayOrder.CDBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryTodayOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryOneOrder(PBStepQryTodayOrderField& QryTodayOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryOneOrder");
	WRITE_LOG(LogLevel::Info, "PBStepQryTodayOrderField: WTBH[%s] WTHLB[%s] CDBZ[%s]", QryTodayOrder.WTBH, QryTodayOrder.WTHLB, QryTodayOrder.CDBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryTodayOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 56019);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTBH, QryTodayOrder.WTBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTHLB, QryTodayOrder.WTHLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CDBZ, QryTodayOrder.CDBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryOneOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryTodayTrade(PBStepQryTodayTradeField& QryTodayTrade, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTodayTrade");
	WRITE_LOG(LogLevel::Info, "PBStepQryTodayTradeField: WTBH[%s] CJBH[%s] CDBZ[%s]", QryTodayTrade.WTBH, QryTodayTrade.CJBH, QryTodayTrade.CDBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryTodayTrade.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6013);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTBH, QryTodayTrade.WTBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CJBH, QryTodayTrade.CJBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CDBZ, QryTodayTrade.CDBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryTodayTrade: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryCapital(PBStepQryCapitalField& QryCapital, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryCapital");
	WRITE_LOG(LogLevel::Info, "PBStepQryCapitalField: HBDM[%s] KQBZ[%s]", QryCapital.HBDM, QryCapital.KQBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryCapital.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6012);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HBDM, QryCapital.HBDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_KQBZ, QryCapital.KQBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryCapital: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryHolderAccount(PBStepQryHolderAccountField& QryHolderAccount, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryHolderAccount");
	WRITE_LOG(LogLevel::Info, "PBStepQryHolderAccountField:");

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryHolderAccount.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6040);
	
	StepApi_PBSTEP_AppendRecord(request);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryHolderAccount: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryInstrument(PBStepQryInstrumentField& QryInstrument, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInstrument");
	WRITE_LOG(LogLevel::Info, "PBStepQryInstrumentField: SCLB[%s]", QryInstrument.SCLB);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryInstrument.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6018);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCLB, QryInstrument.SCLB);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryInstrument: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQrySystemStatus(PBStepQrySystemStatusField& QrySystemStatus, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySystemStatus");
	WRITE_LOG(LogLevel::Info, "PBStepQrySystemStatusField: SCDM[%s] HYDM[%s]", QrySystemStatus.SCDM, QrySystemStatus.HYDM);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QrySystemStatus.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6027);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QrySystemStatus.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QrySystemStatus.HYDM);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQrySystemStatus: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQrySettlement(PBStepQrySettlementField& QrySettlement, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySettlement");
	WRITE_LOG(LogLevel::Info, "PBStepQrySettlementField: JSDCXLB[%s] QSRQ[%s] ZZRQ[%s]", QrySettlement.JSDCXLB, QrySettlement.QSRQ, QrySettlement.ZZRQ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QrySettlement.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6072);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_JSDCXLB, QrySettlement.JSDCXLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QSRQ, QrySettlement.QSRQ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_ZZRQ, QrySettlement.ZZRQ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQrySettlement: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryTodayExecOrder(PBStepQryTodayExecOrderField& QryTodayExecOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTodayExecOrder");
	WRITE_LOG(LogLevel::Info, "PBStepQryTodayExecOrderField:");

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryTodayExecOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6103);
	
	StepApi_PBSTEP_AppendRecord(request);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryTodayExecOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqExecOrder(PBStepReqExecOrderField& ReqExecOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqExecOrder");
	WRITE_LOG(LogLevel::Info, "PBStepReqExecOrderField: SCDM[%s] HYDM[%s] XQSL[%s] GDH[%s] XWH[%s] FJYSQLB[%s] KPBZ[%s] TBBZ[%s] QHZDC[%s] BDBDXH[%s] GTHHBZ[%s]", ReqExecOrder.SCDM, ReqExecOrder.HYDM, ReqExecOrder.XQSL, ReqExecOrder.GDH, ReqExecOrder.XWH, ReqExecOrder.FJYSQLB, ReqExecOrder.KPBZ, ReqExecOrder.TBBZ, ReqExecOrder.QHZDC, ReqExecOrder.BDBDXH, ReqExecOrder.GTHHBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqExecOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6100);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqExecOrder.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, ReqExecOrder.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XQSL, ReqExecOrder.XQSL);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqExecOrder.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqExecOrder.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_FJYSQLB, ReqExecOrder.FJYSQLB);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_KPBZ, ReqExecOrder.KPBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_TBBZ, ReqExecOrder.TBBZ);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QHZDC, ReqExecOrder.QHZDC);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_BDBDXH, ReqExecOrder.BDBDXH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GTHHBZ, ReqExecOrder.GTHHBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqExecOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqCancelExecOrder(PBStepReqCancelExecOrderField& ReqCancelExecOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqCancelExecOrder");
	WRITE_LOG(LogLevel::Info, "PBStepReqCancelExecOrderField: WTBH[%s] SCDM[%s] XWH[%s] XDXW[%s] GDH[%s] KZZD[%s]", ReqCancelExecOrder.WTBH, ReqCancelExecOrder.SCDM, ReqCancelExecOrder.XWH, ReqCancelExecOrder.XDXW, ReqCancelExecOrder.GDH, ReqCancelExecOrder.KZZD);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqCancelExecOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6101);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTBH, ReqCancelExecOrder.WTBH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqCancelExecOrder.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqCancelExecOrder.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XDXW, ReqCancelExecOrder.XDXW);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqCancelExecOrder.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_KZZD, ReqCancelExecOrder.KZZD);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqCancelExecOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqInquiry(PBStepReqInquiryField& ReqInquiry, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqInquiry");
	WRITE_LOG(LogLevel::Info, "PBStepReqInquiryField: SCDM[%s] HYDM[%s] GDH[%s] XWH[%s]", ReqInquiry.SCDM, ReqInquiry.HYDM, ReqInquiry.GDH, ReqInquiry.XWH);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqInquiry.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6075);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqInquiry.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, ReqInquiry.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqInquiry.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqInquiry.XWH);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqInquiry: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryFutureCommissionRate(PBStepQryFutureCommissionRateField& QryFutureCommissionRate, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryFutureCommissionRate");
	WRITE_LOG(LogLevel::Info, "PBStepQryFutureCommissionRateField: SCDM[%s] HYDM[%s] SCLX[%s]", QryFutureCommissionRate.SCDM, QryFutureCommissionRate.HYDM, QryFutureCommissionRate.SCLX);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryFutureCommissionRate.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6078);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QryFutureCommissionRate.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QryFutureCommissionRate.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCLX, QryFutureCommissionRate.SCLX);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryFutureCommissionRate: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryFutureMarginRate(PBStepQryFutureMarginRateField& QryFutureMarginRate, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryFutureMarginRate");
	WRITE_LOG(LogLevel::Info, "PBStepQryFutureMarginRateField: SCDM[%s] HYDM[%s] TBBZ[%s]", QryFutureMarginRate.SCDM, QryFutureMarginRate.HYDM, QryFutureMarginRate.TBBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryFutureMarginRate.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6079);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QryFutureMarginRate.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QryFutureMarginRate.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_TBBZ, QryFutureMarginRate.TBBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryFutureMarginRate: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryTransferMoney(PBStepQryTransferMoneyField& QryTransferMoney, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTransferMoney");
	WRITE_LOG(LogLevel::Info, "PBStepQryTransferMoneyField: LSXH[%s]", QryTransferMoney.LSXH);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryTransferMoney.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6205);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_LSXH, QryTransferMoney.LSXH);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryTransferMoney: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryIncTrade(PBStepQryIncTradeField& QryIncTrade, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryIncTrade");
	WRITE_LOG(LogLevel::Info, "PBStepQryIncTradeField: GTDWC[%s] QQHS[%s] CDBZ[%s]", QryIncTrade.GTDWC, QryIncTrade.QQHS, QryIncTrade.CDBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryIncTrade.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6016);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GTDWC, QryIncTrade.GTDWC);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QQHS, QryIncTrade.QQHS);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CDBZ, QryIncTrade.CDBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryIncTrade: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryIncOrder(PBStepQryIncOrderField& QryIncOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryIncOrder");
	WRITE_LOG(LogLevel::Info, "PBStepQryIncOrderField: GTDWC[%s] QQHS[%s] CDBZ[%s]", QryIncOrder.GTDWC, QryIncOrder.QQHS, QryIncOrder.CDBZ);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryIncOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6020);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GTDWC, QryIncOrder.GTDWC);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_QQHS, QryIncOrder.QQHS);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_CDBZ, QryIncOrder.CDBZ);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryIncOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqQryLockAvailable(PBStepQryLockAvailableField& QryLockAvailable, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqQryLockAvailable");
	WRITE_LOG(LogLevel::Info, "PBStepQryLockAvailableField: XWH[%s] SCDM[%s] HYDM[%s] SDFX[%s] GDH[%s]", QryLockAvailable.XWH, QryLockAvailable.SCDM, QryLockAvailable.HYDM, QryLockAvailable.SDFX, QryLockAvailable.GDH);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, QryLockAvailable.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6104);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, QryLockAvailable.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, QryLockAvailable.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, QryLockAvailable.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SDFX, QryLockAvailable.SDFX);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, QryLockAvailable.GDH);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqQryLockAvailable: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}
int PBStepApi::ReqLockSecurityOrder(PBStepReqLockSecurityOrderField& ReqLockSecurityOrder, int& reqNo)
{
	WRITE_LOG(LogLevel::Info, "ReqLockSecurityOrder");
	WRITE_LOG(LogLevel::Info, "PBStepReqLockSecurityOrderField: SCDM[%s] HYDM[%s] WTSL[%s] GDH[%s] XWH[%s] SDFX[%s]", ReqLockSecurityOrder.SCDM, ReqLockSecurityOrder.HYDM, ReqLockSecurityOrder.WTSL, ReqLockSecurityOrder.GDH, ReqLockSecurityOrder.XWH, ReqLockSecurityOrder.SDFX);

	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, ReqLockSecurityOrder.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, 6105);
	
	StepApi_PBSTEP_AppendRecord(request);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SCDM, ReqLockSecurityOrder.SCDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_HYDM, ReqLockSecurityOrder.HYDM);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_WTSL, ReqLockSecurityOrder.WTSL);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_GDH, ReqLockSecurityOrder.GDH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_XWH, ReqLockSecurityOrder.XWH);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_SDFX, ReqLockSecurityOrder.SDFX);
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	WRITE_LOG(LogLevel::Info, "ReqLockSecurityOrder: ReqNo:[%d], ErrorCode:[%d]", reqNo, errorCode);
	return errorCode;
}


void PBStepApi::SetBaseInfo(HANDLE_REQUEST request, PBStepBaseInfoField& baseInfo)
{
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_LOCAL_IP, baseInfo.LOCAL_IP);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_IP, baseInfo.IP);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_LOCAL_MAC, baseInfo.LOCAL_MAC);
}

