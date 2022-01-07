#include "PBStepCallback.h"
#include "PBApiDataStruct.h"
#include "Logger.h"
#include <iostream>

using namespace std;

#define PBSTEP_ERROR_DISCONNECT -3
#define PBSTEP_ERROR_NOT_LOGIN -8

std::map<HANDLE_USER, PBStepSpi*> g_UserSpis;

void SetSpi(HANDLE_USER user, PBStepSpi* stepSpi)
{
	g_UserSpis[user] = stepSpi;
}

PBStepSpi* GetSpi(HANDLE_USER user)
{
	if (g_UserSpis.find(user) == g_UserSpis.end())
	{
		return nullptr;
	}
	return g_UserSpis[user];
}

int StepApiCallback(HANDLE_USER user, HANDLE_RESPONSE response)
{
	if (user == NULL || response == NULL)
	{
		return -1;
	}
	auto spi = GetSpi(user);
	if (spi == nullptr)
	{
		WRITE_LOG(LogLevel::Error, "StepApiCallback Cannot find SPI for User[%p]", user);
		return -1;
	}
	int reqno = 0;
	PBStepRspErrorField RspError;
	::memset(&RspError, 0, sizeof(RspError));
	int errorID = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	sprintf(RspError.CODE, "%d", errorID);
	if (errorID < 0)
	{
		StepApi_PBSTEP_GetBaseRecFieldValueString(response, STEP_MSG, RspError.MSG, sizeof(RspError.MSG));
		reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	}
	if (errorID == PBSTEP_ERROR_DISCONNECT)
	{
		WRITE_LOG(LogLevel::Error, "StepApiCallback PBSTEP_ERROR_DISCONNECT");
		spi->OnDisConnected();
		return 0;
	}
	
	int funcNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_FUNC);
	printf("funcNo=%d\n", funcNo);
	switch(funcNo)
	{
	case 10100:
	{
		if (errorID < 0)
		{
			spi->OnRspSetUserInfo(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspSetUserInfoField RspSetUserInfo;
		::memset(&RspSetUserInfo, 0, sizeof(RspSetUserInfo));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspSetUserInfo(&RspSetUserInfo, &RspError, reqno, true);
				break;
			}
			spi->OnRspSetUserInfo(&RspSetUserInfo, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspSetUserInfo(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 4:
	{
		if (errorID < 0)
		{
			spi->OnRspSecurityVerity(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspSecurityVerityField RspSecurityVerity;
		::memset(&RspSecurityVerity, 0, sizeof(RspSecurityVerity));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_AQMY, RspSecurityVerity.AQMY, sizeof(RspSecurityVerity.AQMY));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SJJGS, RspSecurityVerity.SJJGS, sizeof(RspSecurityVerity.SJJGS));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspSecurityVerity(&RspSecurityVerity, &RspError, reqno, true);
				break;
			}
			spi->OnRspSecurityVerity(&RspSecurityVerity, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspSecurityVerity(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6011:
	{
		if (errorID < 0)
		{
			spi->OnRspLogin(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspLoginField RspLogin;
		::memset(&RspLogin, 0, sizeof(RspLogin));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZJZH, RspLogin.ZJZH, sizeof(RspLogin.ZJZH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TRADE_DATE, RspLogin.TRADE_DATE, sizeof(RspLogin.TRADE_DATE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_LAST_TRADE_DATE, RspLogin.LAST_TRADE_DATE, sizeof(RspLogin.LAST_TRADE_DATE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_LOGIN_FLAG, RspLogin.LOGIN_FLAG, sizeof(RspLogin.LOGIN_FLAG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XGMMTS, RspLogin.XGMMTS, sizeof(RspLogin.XGMMTS));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, RspLogin.GTHHBZ, sizeof(RspLogin.GTHHBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_AQMY, RspLogin.AQMY, sizeof(RspLogin.AQMY));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspLogin(&RspLogin, &RspError, reqno, true);
				break;
			}
			spi->OnRspLogin(&RspLogin, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspLogin(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6071:
	{
		if (errorID < 0)
		{
			spi->OnRspConfirmSettlement(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspConfirmSettlementField RspConfirmSettlement;
		::memset(&RspConfirmSettlement, 0, sizeof(RspConfirmSettlement));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspConfirmSettlement(&RspConfirmSettlement, &RspError, reqno, true);
				break;
			}
			spi->OnRspConfirmSettlement(&RspConfirmSettlement, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspConfirmSettlement(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6021:
	{
		if (errorID < 0)
		{
			spi->OnRspInsertOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspInsertOrderField RspInsertOrder;
		::memset(&RspInsertOrder, 0, sizeof(RspInsertOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, RspInsertOrder.WTBH, sizeof(RspInsertOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, RspInsertOrder.BDBDXH, sizeof(RspInsertOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, RspInsertOrder.GTHHBZ, sizeof(RspInsertOrder.GTHHBZ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspInsertOrder(&RspInsertOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspInsertOrder(&RspInsertOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspInsertOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6022:
	{
		if (errorID < 0)
		{
			spi->OnRspCancelOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspCancelOrderField RspCancelOrder;
		::memset(&RspCancelOrder, 0, sizeof(RspCancelOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspCancelOrder(&RspCancelOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspCancelOrder(&RspCancelOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspCancelOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6014:
	{
		if (errorID < 0)
		{
			spi->OnRspQryPosition(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepPositionField Position;
		::memset(&Position, 0, sizeof(Position));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, Position.SCDM, sizeof(Position.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, Position.HYDM, sizeof(Position.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_DQSL, Position.DQSL, sizeof(Position.DQSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MRJJ, Position.MRJJ, sizeof(Position.MRJJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CBJ, Position.CBJ, sizeof(Position.CBJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, Position.GDH, sizeof(Position.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HBDM, Position.HBDM, sizeof(Position.HBDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, Position.BDBZ, sizeof(Position.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, Position.MMLB, sizeof(Position.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, Position.TBBZ, sizeof(Position.TBBZ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryPosition(&Position, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryPosition(&Position, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryPosition(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6074:
	{
		if (errorID < 0)
		{
			spi->OnRspQryPositionDetail(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepPositionDetailField PositionDetail;
		::memset(&PositionDetail, 0, sizeof(PositionDetail));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, PositionDetail.SCDM, sizeof(PositionDetail.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, PositionDetail.HYDM, sizeof(PositionDetail.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_DQSL, PositionDetail.DQSL, sizeof(PositionDetail.DQSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CBJ, PositionDetail.CBJ, sizeof(PositionDetail.CBJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, PositionDetail.MMLB, sizeof(PositionDetail.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, PositionDetail.TBBZ, sizeof(PositionDetail.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZJ, PositionDetail.BZJ, sizeof(PositionDetail.BZJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KCRQ, PositionDetail.KCRQ, sizeof(PositionDetail.KCRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HBDM, PositionDetail.HBDM, sizeof(PositionDetail.HBDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJBH, PositionDetail.CJBH, sizeof(PositionDetail.CJBH));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryPositionDetail(&PositionDetail, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryPositionDetail(&PositionDetail, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryPositionDetail(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6019:
	{
		if (errorID < 0)
		{
			spi->OnRspQryTodayOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayOrderField TodayOrder;
		::memset(&TodayOrder, 0, sizeof(TodayOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayOrder.SCDM, sizeof(TodayOrder.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayOrder.WTBH, sizeof(TodayOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayOrder.HYDM, sizeof(TodayOrder.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, TodayOrder.WTZT, sizeof(TodayOrder.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, TodayOrder.MMLB, sizeof(TodayOrder.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, TodayOrder.WTSL, sizeof(TodayOrder.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTJG, TodayOrder.WTJG, sizeof(TodayOrder.WTJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, TodayOrder.CJSL, sizeof(TodayOrder.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSL, TodayOrder.CDSL, sizeof(TodayOrder.CDSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, TodayOrder.WTSJ, sizeof(TodayOrder.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SJWTLB, TodayOrder.SJWTLB, sizeof(TodayOrder.SJWTLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, TodayOrder.GDH, sizeof(TodayOrder.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTRQ, TodayOrder.WTRQ, sizeof(TodayOrder.WTRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, TodayOrder.KPBZ, sizeof(TodayOrder.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayOrder.TBBZ, sizeof(TodayOrder.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, TodayOrder.BDBZ, sizeof(TodayOrder.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZXX, TodayOrder.BZXX, sizeof(TodayOrder.BZXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JGLB, TodayOrder.JGLB, sizeof(TodayOrder.JGLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXQLX, TodayOrder.YXQLX, sizeof(TodayOrder.YXQLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLLX, TodayOrder.CJLLX, sizeof(TodayOrder.CJLLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZXCJL, TodayOrder.ZXCJL, sizeof(TodayOrder.ZXCJL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, TodayOrder.KZZD, sizeof(TodayOrder.KZZD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CFTJ, TodayOrder.CFTJ, sizeof(TodayOrder.CFTJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSJ, TodayOrder.CDSJ, sizeof(TodayOrder.CDSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXRQ, TodayOrder.YXRQ, sizeof(TodayOrder.YXRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, TodayOrder.BDBDXH, sizeof(TodayOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, TodayOrder.GTHHBZ, sizeof(TodayOrder.GTHHBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTDWC, TodayOrder.GTDWC, sizeof(TodayOrder.GTDWC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTLX, TodayOrder.WTLX, sizeof(TodayOrder.WTLX));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryTodayOrder(&TodayOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryTodayOrder(&TodayOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryTodayOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 56019:
	{
		if (errorID < 0)
		{
			spi->OnRspQryOneOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayOrderField TodayOrder;
		::memset(&TodayOrder, 0, sizeof(TodayOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayOrder.SCDM, sizeof(TodayOrder.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayOrder.WTBH, sizeof(TodayOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayOrder.HYDM, sizeof(TodayOrder.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, TodayOrder.WTZT, sizeof(TodayOrder.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, TodayOrder.MMLB, sizeof(TodayOrder.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, TodayOrder.WTSL, sizeof(TodayOrder.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTJG, TodayOrder.WTJG, sizeof(TodayOrder.WTJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, TodayOrder.CJSL, sizeof(TodayOrder.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSL, TodayOrder.CDSL, sizeof(TodayOrder.CDSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, TodayOrder.WTSJ, sizeof(TodayOrder.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SJWTLB, TodayOrder.SJWTLB, sizeof(TodayOrder.SJWTLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, TodayOrder.GDH, sizeof(TodayOrder.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTRQ, TodayOrder.WTRQ, sizeof(TodayOrder.WTRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, TodayOrder.KPBZ, sizeof(TodayOrder.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayOrder.TBBZ, sizeof(TodayOrder.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, TodayOrder.BDBZ, sizeof(TodayOrder.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZXX, TodayOrder.BZXX, sizeof(TodayOrder.BZXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JGLB, TodayOrder.JGLB, sizeof(TodayOrder.JGLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXQLX, TodayOrder.YXQLX, sizeof(TodayOrder.YXQLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLLX, TodayOrder.CJLLX, sizeof(TodayOrder.CJLLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZXCJL, TodayOrder.ZXCJL, sizeof(TodayOrder.ZXCJL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, TodayOrder.KZZD, sizeof(TodayOrder.KZZD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CFTJ, TodayOrder.CFTJ, sizeof(TodayOrder.CFTJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSJ, TodayOrder.CDSJ, sizeof(TodayOrder.CDSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXRQ, TodayOrder.YXRQ, sizeof(TodayOrder.YXRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, TodayOrder.BDBDXH, sizeof(TodayOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, TodayOrder.GTHHBZ, sizeof(TodayOrder.GTHHBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTDWC, TodayOrder.GTDWC, sizeof(TodayOrder.GTDWC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTLX, TodayOrder.WTLX, sizeof(TodayOrder.WTLX));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryOneOrder(&TodayOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryOneOrder(&TodayOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryOneOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6013:
	{
		if (errorID < 0)
		{
			spi->OnRspQryTodayTrade(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayTradeField TodayTrade;
		::memset(&TodayTrade, 0, sizeof(TodayTrade));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayTrade.SCDM, sizeof(TodayTrade.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayTrade.HYDM, sizeof(TodayTrade.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDMMC, TodayTrade.HYDMMC, sizeof(TodayTrade.HYDMMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, TodayTrade.MMLB, sizeof(TodayTrade.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, TodayTrade.KPBZ, sizeof(TodayTrade.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayTrade.TBBZ, sizeof(TodayTrade.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSJ, TodayTrade.CJSJ, sizeof(TodayTrade.CJSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayTrade.WTBH, sizeof(TodayTrade.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, TodayTrade.CJSL, sizeof(TodayTrade.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJJG, TodayTrade.CJJG, sizeof(TodayTrade.CJJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJBH, TodayTrade.CJBH, sizeof(TodayTrade.CJBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, TodayTrade.BDBZ, sizeof(TodayTrade.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJRQ, TodayTrade.CJRQ, sizeof(TodayTrade.CJRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYLB, TodayTrade.HYLB, sizeof(TodayTrade.HYLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTDWC, TodayTrade.GTDWC, sizeof(TodayTrade.GTDWC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLX, TodayTrade.CJLX, sizeof(TodayTrade.CJLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YWTH, TodayTrade.YWTH, sizeof(TodayTrade.YWTH));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryTodayTrade(&TodayTrade, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryTodayTrade(&TodayTrade, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryTodayTrade(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6012:
	{
		if (errorID < 0)
		{
			spi->OnRspQryCapital(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepCapitalField Capital;
		::memset(&Capital, 0, sizeof(Capital));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZJZH, Capital.ZJZH, sizeof(Capital.ZJZH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HBDM, Capital.HBDM, sizeof(Capital.HBDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_QCYE, Capital.QCYE, sizeof(Capital.QCYE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KYZJ, Capital.KYZJ, sizeof(Capital.KYZJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZZC, Capital.ZZC, sizeof(Capital.ZZC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PCDSYK, Capital.PCDSYK, sizeof(Capital.PCDSYK));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SXF, Capital.SXF, sizeof(Capital.SXF));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XJZC, Capital.XJZC, sizeof(Capital.XJZC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CRJ, Capital.CRJ, sizeof(Capital.CRJ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryCapital(&Capital, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryCapital(&Capital, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryCapital(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6040:
	{
		if (errorID < 0)
		{
			spi->OnRspQryHolderAccount(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepHolderAccountField HolderAccount;
		::memset(&HolderAccount, 0, sizeof(HolderAccount));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, HolderAccount.SCDM, sizeof(HolderAccount.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCMC, HolderAccount.SCMC, sizeof(HolderAccount.SCMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, HolderAccount.GDH, sizeof(HolderAccount.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZZHBZ, HolderAccount.ZZHBZ, sizeof(HolderAccount.ZZHBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, HolderAccount.TBBZ, sizeof(HolderAccount.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XWH, HolderAccount.XWH, sizeof(HolderAccount.XWH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCXX, HolderAccount.SCXX, sizeof(HolderAccount.SCXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WPBZ, HolderAccount.WPBZ, sizeof(HolderAccount.WPBZ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryHolderAccount(&HolderAccount, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryHolderAccount(&HolderAccount, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryHolderAccount(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6018:
	{
		if (errorID < 0)
		{
			spi->OnRspQryInstrument(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepInstrumentField Instrument;
		::memset(&Instrument, 0, sizeof(Instrument));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, Instrument.SCDM, sizeof(Instrument.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, Instrument.HYDM, sizeof(Instrument.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYCS, Instrument.HYCS, sizeof(Instrument.HYCS));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZXBDJW, Instrument.ZXBDJW, sizeof(Instrument.ZXBDJW));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDMMC, Instrument.HYDMMC, sizeof(Instrument.HYDMMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSX, Instrument.WTSX, sizeof(Instrument.WTSX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZCSX, Instrument.ZCSX, sizeof(Instrument.ZCSX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_DWBZJ, Instrument.DWBZJ, sizeof(Instrument.DWBZJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCLX, Instrument.SCLX, sizeof(Instrument.SCLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_DQR, Instrument.DQR, sizeof(Instrument.DQR));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_DBYH, Instrument.DBYH, sizeof(Instrument.DBYH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PZDM, Instrument.PZDM, sizeof(Instrument.PZDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZDJC, Instrument.ZDJC, sizeof(Instrument.ZDJC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYLB, Instrument.HYLB, sizeof(Instrument.HYLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDDM, Instrument.BDDM, sizeof(Instrument.BDDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDMC, Instrument.BDMC, sizeof(Instrument.BDMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XQJG, Instrument.XQJG, sizeof(Instrument.XQJG));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryInstrument(&Instrument, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryInstrument(&Instrument, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryInstrument(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6027:
	{
		if (errorID < 0)
		{
			spi->OnRspQrySystemStatus(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepSystemStatusField SystemStatus;
		::memset(&SystemStatus, 0, sizeof(SystemStatus));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, SystemStatus.SCDM, sizeof(SystemStatus.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, SystemStatus.HYDM, sizeof(SystemStatus.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XTZT, SystemStatus.XTZT, sizeof(SystemStatus.XTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JYZZT, SystemStatus.JYZZT, sizeof(SystemStatus.JYZZT));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQrySystemStatus(&SystemStatus, &RspError, reqno, true);
				break;
			}
			spi->OnRspQrySystemStatus(&SystemStatus, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQrySystemStatus(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6072:
	{
		if (errorID < 0)
		{
			spi->OnRspQrySettlement(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepSettlementField Settlement;
		::memset(&Settlement, 0, sizeof(Settlement));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JSD, Settlement.JSD, sizeof(Settlement.JSD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_QRBZ, Settlement.QRBZ, sizeof(Settlement.QRBZ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQrySettlement(&Settlement, &RspError, reqno, true);
				break;
			}
			spi->OnRspQrySettlement(&Settlement, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQrySettlement(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6103:
	{
		if (errorID < 0)
		{
			spi->OnRspQryTodayExecOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayExecOrderField TodayExecOrder;
		::memset(&TodayExecOrder, 0, sizeof(TodayExecOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayExecOrder.SCDM, sizeof(TodayExecOrder.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayExecOrder.WTBH, sizeof(TodayExecOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayExecOrder.HYDM, sizeof(TodayExecOrder.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, TodayExecOrder.WTZT, sizeof(TodayExecOrder.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTJG, TodayExecOrder.WTJG, sizeof(TodayExecOrder.WTJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, TodayExecOrder.WTSL, sizeof(TodayExecOrder.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, TodayExecOrder.WTSJ, sizeof(TodayExecOrder.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SBSJ, TodayExecOrder.SBSJ, sizeof(TodayExecOrder.SBSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XWH, TodayExecOrder.XWH, sizeof(TodayExecOrder.XWH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XDXW, TodayExecOrder.XDXW, sizeof(TodayExecOrder.XDXW));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_FJYSQLB, TodayExecOrder.FJYSQLB, sizeof(TodayExecOrder.FJYSQLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayExecOrder.TBBZ, sizeof(TodayExecOrder.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, TodayExecOrder.KZZD, sizeof(TodayExecOrder.KZZD));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryTodayExecOrder(&TodayExecOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryTodayExecOrder(&TodayExecOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryTodayExecOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6100:
	{
		if (errorID < 0)
		{
			spi->OnRspExecOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspExecOrderField RspExecOrder;
		::memset(&RspExecOrder, 0, sizeof(RspExecOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, RspExecOrder.WTBH, sizeof(RspExecOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, RspExecOrder.BDBDXH, sizeof(RspExecOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, RspExecOrder.GTHHBZ, sizeof(RspExecOrder.GTHHBZ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspExecOrder(&RspExecOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspExecOrder(&RspExecOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspExecOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6101:
	{
		if (errorID < 0)
		{
			spi->OnRspCancelExecOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspCancelExecOrderField RspCancelExecOrder;
		::memset(&RspCancelExecOrder, 0, sizeof(RspCancelExecOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspCancelExecOrder(&RspCancelExecOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspCancelExecOrder(&RspCancelExecOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspCancelExecOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6075:
	{
		if (errorID < 0)
		{
			spi->OnRspInquiry(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspInquiryField RspInquiry;
		::memset(&RspInquiry, 0, sizeof(RspInquiry));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XJBH, RspInquiry.XJBH, sizeof(RspInquiry.XJBH));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspInquiry(&RspInquiry, &RspError, reqno, true);
				break;
			}
			spi->OnRspInquiry(&RspInquiry, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspInquiry(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6078:
	{
		if (errorID < 0)
		{
			spi->OnRspQryFutureCommissionRate(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepFutureCommissionRateField FutureCommissionRate;
		::memset(&FutureCommissionRate, 0, sizeof(FutureCommissionRate));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, FutureCommissionRate.SCDM, sizeof(FutureCommissionRate.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, FutureCommissionRate.HYDM, sizeof(FutureCommissionRate.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, FutureCommissionRate.TBBZ, sizeof(FutureCommissionRate.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KCJEBL, FutureCommissionRate.KCJEBL, sizeof(FutureCommissionRate.KCJEBL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PCJEBL, FutureCommissionRate.PCJEBL, sizeof(FutureCommissionRate.PCJEBL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PJJEBL, FutureCommissionRate.PJJEBL, sizeof(FutureCommissionRate.PJJEBL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KCDWJE, FutureCommissionRate.KCDWJE, sizeof(FutureCommissionRate.KCDWJE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PCDWJE, FutureCommissionRate.PCDWJE, sizeof(FutureCommissionRate.PCDWJE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_PJDWJE, FutureCommissionRate.PJDWJE, sizeof(FutureCommissionRate.PJDWJE));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryFutureCommissionRate(&FutureCommissionRate, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryFutureCommissionRate(&FutureCommissionRate, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryFutureCommissionRate(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6079:
	{
		if (errorID < 0)
		{
			spi->OnRspQryFutureMarginRate(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepFutureMarginRateField FutureMarginRate;
		::memset(&FutureMarginRate, 0, sizeof(FutureMarginRate));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, FutureMarginRate.SCDM, sizeof(FutureMarginRate.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, FutureMarginRate.HYDM, sizeof(FutureMarginRate.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, FutureMarginRate.TBBZ, sizeof(FutureMarginRate.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, FutureMarginRate.MMLB, sizeof(FutureMarginRate.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KCJEBL, FutureMarginRate.KCJEBL, sizeof(FutureMarginRate.KCJEBL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KCDWJE, FutureMarginRate.KCDWJE, sizeof(FutureMarginRate.KCDWJE));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryFutureMarginRate(&FutureMarginRate, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryFutureMarginRate(&FutureMarginRate, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryFutureMarginRate(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6205:
	{
		if (errorID < 0)
		{
			spi->OnRspQryTransferMoney(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTransferMoneyField TransferMoney;
		::memset(&TransferMoney, 0, sizeof(TransferMoney));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_LSXH, TransferMoney.LSXH, sizeof(TransferMoney.LSXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZZJE, TransferMoney.ZZJE, sizeof(TransferMoney.ZZJE));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HBDM, TransferMoney.HBDM, sizeof(TransferMoney.HBDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YZYWBZ, TransferMoney.YZYWBZ, sizeof(TransferMoney.YZYWBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YZYWZT, TransferMoney.YZYWZT, sizeof(TransferMoney.YZYWZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SQRQ, TransferMoney.SQRQ, sizeof(TransferMoney.SQRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SQSJ, TransferMoney.SQSJ, sizeof(TransferMoney.SQSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JGSM, TransferMoney.JGSM, sizeof(TransferMoney.JGSM));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryTransferMoney(&TransferMoney, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryTransferMoney(&TransferMoney, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryTransferMoney(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6016:
	{
		if (errorID < 0)
		{
			spi->OnRspQryIncTrade(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayTradeField TodayTrade;
		::memset(&TodayTrade, 0, sizeof(TodayTrade));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayTrade.SCDM, sizeof(TodayTrade.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayTrade.HYDM, sizeof(TodayTrade.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDMMC, TodayTrade.HYDMMC, sizeof(TodayTrade.HYDMMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, TodayTrade.MMLB, sizeof(TodayTrade.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, TodayTrade.KPBZ, sizeof(TodayTrade.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayTrade.TBBZ, sizeof(TodayTrade.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSJ, TodayTrade.CJSJ, sizeof(TodayTrade.CJSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayTrade.WTBH, sizeof(TodayTrade.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, TodayTrade.CJSL, sizeof(TodayTrade.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJJG, TodayTrade.CJJG, sizeof(TodayTrade.CJJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJBH, TodayTrade.CJBH, sizeof(TodayTrade.CJBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, TodayTrade.BDBZ, sizeof(TodayTrade.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJRQ, TodayTrade.CJRQ, sizeof(TodayTrade.CJRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYLB, TodayTrade.HYLB, sizeof(TodayTrade.HYLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTDWC, TodayTrade.GTDWC, sizeof(TodayTrade.GTDWC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLX, TodayTrade.CJLX, sizeof(TodayTrade.CJLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YWTH, TodayTrade.YWTH, sizeof(TodayTrade.YWTH));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryIncTrade(&TodayTrade, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryIncTrade(&TodayTrade, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryIncTrade(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6020:
	{
		if (errorID < 0)
		{
			spi->OnRspQryIncOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepTodayOrderField TodayOrder;
		::memset(&TodayOrder, 0, sizeof(TodayOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, TodayOrder.SCDM, sizeof(TodayOrder.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, TodayOrder.WTBH, sizeof(TodayOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, TodayOrder.HYDM, sizeof(TodayOrder.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, TodayOrder.WTZT, sizeof(TodayOrder.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, TodayOrder.MMLB, sizeof(TodayOrder.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, TodayOrder.WTSL, sizeof(TodayOrder.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTJG, TodayOrder.WTJG, sizeof(TodayOrder.WTJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, TodayOrder.CJSL, sizeof(TodayOrder.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSL, TodayOrder.CDSL, sizeof(TodayOrder.CDSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, TodayOrder.WTSJ, sizeof(TodayOrder.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SJWTLB, TodayOrder.SJWTLB, sizeof(TodayOrder.SJWTLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, TodayOrder.GDH, sizeof(TodayOrder.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTRQ, TodayOrder.WTRQ, sizeof(TodayOrder.WTRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, TodayOrder.KPBZ, sizeof(TodayOrder.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, TodayOrder.TBBZ, sizeof(TodayOrder.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, TodayOrder.BDBZ, sizeof(TodayOrder.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZXX, TodayOrder.BZXX, sizeof(TodayOrder.BZXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JGLB, TodayOrder.JGLB, sizeof(TodayOrder.JGLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXQLX, TodayOrder.YXQLX, sizeof(TodayOrder.YXQLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLLX, TodayOrder.CJLLX, sizeof(TodayOrder.CJLLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZXCJL, TodayOrder.ZXCJL, sizeof(TodayOrder.ZXCJL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, TodayOrder.KZZD, sizeof(TodayOrder.KZZD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CFTJ, TodayOrder.CFTJ, sizeof(TodayOrder.CFTJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSJ, TodayOrder.CDSJ, sizeof(TodayOrder.CDSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXRQ, TodayOrder.YXRQ, sizeof(TodayOrder.YXRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, TodayOrder.BDBDXH, sizeof(TodayOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, TodayOrder.GTHHBZ, sizeof(TodayOrder.GTHHBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTDWC, TodayOrder.GTDWC, sizeof(TodayOrder.GTDWC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTLX, TodayOrder.WTLX, sizeof(TodayOrder.WTLX));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryIncOrder(&TodayOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryIncOrder(&TodayOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryIncOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6104:
	{
		if (errorID < 0)
		{
			spi->OnRspQryLockAvailable(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepLockAvailableField LockAvailable;
		::memset(&LockAvailable, 0, sizeof(LockAvailable));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KMSL, LockAvailable.KMSL, sizeof(LockAvailable.KMSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, LockAvailable.SCDM, sizeof(LockAvailable.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, LockAvailable.HYDM, sizeof(LockAvailable.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SDFX, LockAvailable.SDFX, sizeof(LockAvailable.SDFX));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspQryLockAvailable(&LockAvailable, &RspError, reqno, true);
				break;
			}
			spi->OnRspQryLockAvailable(&LockAvailable, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspQryLockAvailable(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 6105:
	{
		if (errorID < 0)
		{
			spi->OnRspLockSecurityOrder(nullptr, &RspError, reqno, true);
			break;
		}
		PBStepRspLockSecurityOrderField RspLockSecurityOrder;
		::memset(&RspLockSecurityOrder, 0, sizeof(RspLockSecurityOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, RspLockSecurityOrder.WTBH, sizeof(RspLockSecurityOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, RspLockSecurityOrder.WTSJ, sizeof(RspLockSecurityOrder.WTSJ));

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->OnRspLockSecurityOrder(&RspLockSecurityOrder, &RspError, reqno, true);
				break;
			}
			spi->OnRspLockSecurityOrder(&RspLockSecurityOrder, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->OnRspLockSecurityOrder(nullptr, &RspError, reqno, true);
		}
		break;
	}
	case 56001:
	{
		PBStepSystemStatusField SystemStatus;
		::memset(&SystemStatus, 0, sizeof(SystemStatus));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, SystemStatus.SCDM, sizeof(SystemStatus.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, SystemStatus.HYDM, sizeof(SystemStatus.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XTZT, SystemStatus.XTZT, sizeof(SystemStatus.XTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JYZZT, SystemStatus.JYZZT, sizeof(SystemStatus.JYZZT));

			spi->OnRtnSystemStatus(&SystemStatus);
		}
		if (recnum == 0)
		{
			spi->OnRtnSystemStatus(nullptr);
		}
		break;
	}
	case 56005:
	{
		PBStepOrderField Order;
		::memset(&Order, 0, sizeof(Order));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, Order.SCDM, sizeof(Order.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, Order.HYDM, sizeof(Order.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GDH, Order.GDH, sizeof(Order.GDH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, Order.MMLB, sizeof(Order.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, Order.KPBZ, sizeof(Order.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, Order.TBBZ, sizeof(Order.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, Order.WTZT, sizeof(Order.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_QPBZ, Order.QPBZ, sizeof(Order.QPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, Order.WTSJ, sizeof(Order.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSJ, Order.CDSJ, sizeof(Order.CDSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, Order.WTBH, sizeof(Order.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTXTH, Order.WTXTH, sizeof(Order.WTXTH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, Order.WTSL, sizeof(Order.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, Order.CJSL, sizeof(Order.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WCJSL, Order.WCJSL, sizeof(Order.WCJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTRQ, Order.WTRQ, sizeof(Order.WTRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JYRQ, Order.JYRQ, sizeof(Order.JYRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTJG, Order.WTJG, sizeof(Order.WTJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZHLX, Order.WTZHLX, sizeof(Order.WTZHLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_JGLB, Order.JGLB, sizeof(Order.JGLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_YXQLX, Order.YXQLX, sizeof(Order.YXQLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJLLX, Order.CJLLX, sizeof(Order.CJLLX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_ZXCJL, Order.ZXCJL, sizeof(Order.ZXCJL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CFTJ, Order.CFTJ, sizeof(Order.CFTJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, Order.KZZD, sizeof(Order.KZZD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYLB, Order.HYLB, sizeof(Order.HYLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, Order.BDBZ, sizeof(Order.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CDSL, Order.CDSL, sizeof(Order.CDSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZXX, Order.BZXX, sizeof(Order.BZXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SJWTLB, Order.SJWTLB, sizeof(Order.SJWTLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, Order.BDBDXH, sizeof(Order.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, Order.GTHHBZ, sizeof(Order.GTHHBZ));

			spi->OnRtnOrder(&Order);
		}
		if (recnum == 0)
		{
			spi->OnRtnOrder(nullptr);
		}
		break;
	}
	case 56006:
	{
		PBStepTradeField Trade;
		::memset(&Trade, 0, sizeof(Trade));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, Trade.SCDM, sizeof(Trade.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, Trade.HYDM, sizeof(Trade.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDMMC, Trade.HYDMMC, sizeof(Trade.HYDMMC));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_MMLB, Trade.MMLB, sizeof(Trade.MMLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KPBZ, Trade.KPBZ, sizeof(Trade.KPBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, Trade.TBBZ, sizeof(Trade.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSJ, Trade.CJSJ, sizeof(Trade.CJSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, Trade.WTBH, sizeof(Trade.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJSL, Trade.CJSL, sizeof(Trade.CJSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJJG, Trade.CJJG, sizeof(Trade.CJJG));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJBH, Trade.CJBH, sizeof(Trade.CJBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBZ, Trade.BDBZ, sizeof(Trade.BDBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_CJRQ, Trade.CJRQ, sizeof(Trade.CJRQ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYLB, Trade.HYLB, sizeof(Trade.HYLB));

			spi->OnRtnTrade(&Trade);
		}
		if (recnum == 0)
		{
			spi->OnRtnTrade(nullptr);
		}
		break;
	}
	case 56103:
	{
		PBStepExecOrderField ExecOrder;
		::memset(&ExecOrder, 0, sizeof(ExecOrder));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
			StepApi_PBSTEP_GetFieldValueString(response, STEP_SCDM, ExecOrder.SCDM, sizeof(ExecOrder.SCDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTBH, ExecOrder.WTBH, sizeof(ExecOrder.WTBH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_HYDM, ExecOrder.HYDM, sizeof(ExecOrder.HYDM));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTZT, ExecOrder.WTZT, sizeof(ExecOrder.WTZT));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSL, ExecOrder.WTSL, sizeof(ExecOrder.WTSL));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_WTSJ, ExecOrder.WTSJ, sizeof(ExecOrder.WTSJ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_XWH, ExecOrder.XWH, sizeof(ExecOrder.XWH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BZXX, ExecOrder.BZXX, sizeof(ExecOrder.BZXX));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_FJYSQLB, ExecOrder.FJYSQLB, sizeof(ExecOrder.FJYSQLB));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_TBBZ, ExecOrder.TBBZ, sizeof(ExecOrder.TBBZ));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_KZZD, ExecOrder.KZZD, sizeof(ExecOrder.KZZD));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_BDBDXH, ExecOrder.BDBDXH, sizeof(ExecOrder.BDBDXH));
			StepApi_PBSTEP_GetFieldValueString(response, STEP_GTHHBZ, ExecOrder.GTHHBZ, sizeof(ExecOrder.GTHHBZ));

			spi->OnRtnExecOrder(&ExecOrder);
		}
		if (recnum == 0)
		{
			spi->OnRtnExecOrder(nullptr);
		}
		break;
	}
	}
	return 0;
}