#include "PBStepSpi.h"
#include "Logger.h"

using namespace std;

void PBStepSpi::OnDisConnected()
{
	WRITE_LOG(LogLevel::Info, "OnDisConnected");
}

void PBStepSpi::OnRspSetUserInfo(PBStepRspSetUserInfoField* RspSetUserInfo, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspSetUserInfo, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspSetUserInfo)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspSetUserInfoField:");
	}
}
void PBStepSpi::OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspSecurityVerity, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspSecurityVerity)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspSecurityVerityField: AQMY[%s] SJJGS[%s]", RspSecurityVerity->AQMY, RspSecurityVerity->SJJGS);
	}
}
void PBStepSpi::OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspLogin, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspLogin)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspLoginField: ZJZH[%s] TRADE_DATE[%s] LAST_TRADE_DATE[%s] LOGIN_FLAG[%s] XGMMTS[%s] GTHHBZ[%s] AQMY[%s]", RspLogin->ZJZH, RspLogin->TRADE_DATE, RspLogin->LAST_TRADE_DATE, RspLogin->LOGIN_FLAG, RspLogin->XGMMTS, RspLogin->GTHHBZ, RspLogin->AQMY);
	}
}
void PBStepSpi::OnRspConfirmSettlement(PBStepRspConfirmSettlementField* RspConfirmSettlement, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspConfirmSettlement, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspConfirmSettlement)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspConfirmSettlementField:");
	}
}
void PBStepSpi::OnRspInsertOrder(PBStepRspInsertOrderField* RspInsertOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspInsertOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspInsertOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspInsertOrderField: WTBH[%s] BDBDXH[%s] GTHHBZ[%s]", RspInsertOrder->WTBH, RspInsertOrder->BDBDXH, RspInsertOrder->GTHHBZ);
	}
}
void PBStepSpi::OnRspCancelOrder(PBStepRspCancelOrderField* RspCancelOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspCancelOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspCancelOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspCancelOrderField:");
	}
}
void PBStepSpi::OnRspQryPosition(PBStepPositionField* Position, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryPosition, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (Position)
	{
		WRITE_LOG(LogLevel::Info, "PBStepPositionField: SCDM[%s] HYDM[%s] DQSL[%s] MRJJ[%s] CBJ[%s] GDH[%s] HBDM[%s] BDBZ[%s] MMLB[%s] TBBZ[%s]", Position->SCDM, Position->HYDM, Position->DQSL, Position->MRJJ, Position->CBJ, Position->GDH, Position->HBDM, Position->BDBZ, Position->MMLB, Position->TBBZ);
	}
}
void PBStepSpi::OnRspQryPositionDetail(PBStepPositionDetailField* PositionDetail, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryPositionDetail, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (PositionDetail)
	{
		WRITE_LOG(LogLevel::Info, "PBStepPositionDetailField: SCDM[%s] HYDM[%s] DQSL[%s] CBJ[%s] MMLB[%s] TBBZ[%s] BZJ[%s] KCRQ[%s] HBDM[%s] CJBH[%s]", PositionDetail->SCDM, PositionDetail->HYDM, PositionDetail->DQSL, PositionDetail->CBJ, PositionDetail->MMLB, PositionDetail->TBBZ, PositionDetail->BZJ, PositionDetail->KCRQ, PositionDetail->HBDM, PositionDetail->CJBH);
	}
}
void PBStepSpi::OnRspQryTodayOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTodayOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayOrderField: SCDM[%s] WTBH[%s] HYDM[%s] WTZT[%s] MMLB[%s] WTSL[%s] WTJG[%s] CJSL[%s] CDSL[%s] WTSJ[%s] SJWTLB[%s] GDH[%s] WTRQ[%s] KPBZ[%s] TBBZ[%s] BDBZ[%s] BZXX[%s] JGLB[%s] YXQLX[%s] CJLLX[%s] ZXCJL[%s] KZZD[%s] CFTJ[%s] CDSJ[%s] YXRQ[%s] BDBDXH[%s] GTHHBZ[%s] GTDWC[%s] WTLX[%s]", TodayOrder->SCDM, TodayOrder->WTBH, TodayOrder->HYDM, TodayOrder->WTZT, TodayOrder->MMLB, TodayOrder->WTSL, TodayOrder->WTJG, TodayOrder->CJSL, TodayOrder->CDSL, TodayOrder->WTSJ, TodayOrder->SJWTLB, TodayOrder->GDH, TodayOrder->WTRQ, TodayOrder->KPBZ, TodayOrder->TBBZ, TodayOrder->BDBZ, TodayOrder->BZXX, TodayOrder->JGLB, TodayOrder->YXQLX, TodayOrder->CJLLX, TodayOrder->ZXCJL, TodayOrder->KZZD, TodayOrder->CFTJ, TodayOrder->CDSJ, TodayOrder->YXRQ, TodayOrder->BDBDXH, TodayOrder->GTHHBZ, TodayOrder->GTDWC, TodayOrder->WTLX);
	}
}
void PBStepSpi::OnRspQryOneOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOneOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayOrderField: SCDM[%s] WTBH[%s] HYDM[%s] WTZT[%s] MMLB[%s] WTSL[%s] WTJG[%s] CJSL[%s] CDSL[%s] WTSJ[%s] SJWTLB[%s] GDH[%s] WTRQ[%s] KPBZ[%s] TBBZ[%s] BDBZ[%s] BZXX[%s] JGLB[%s] YXQLX[%s] CJLLX[%s] ZXCJL[%s] KZZD[%s] CFTJ[%s] CDSJ[%s] YXRQ[%s] BDBDXH[%s] GTHHBZ[%s] GTDWC[%s] WTLX[%s]", TodayOrder->SCDM, TodayOrder->WTBH, TodayOrder->HYDM, TodayOrder->WTZT, TodayOrder->MMLB, TodayOrder->WTSL, TodayOrder->WTJG, TodayOrder->CJSL, TodayOrder->CDSL, TodayOrder->WTSJ, TodayOrder->SJWTLB, TodayOrder->GDH, TodayOrder->WTRQ, TodayOrder->KPBZ, TodayOrder->TBBZ, TodayOrder->BDBZ, TodayOrder->BZXX, TodayOrder->JGLB, TodayOrder->YXQLX, TodayOrder->CJLLX, TodayOrder->ZXCJL, TodayOrder->KZZD, TodayOrder->CFTJ, TodayOrder->CDSJ, TodayOrder->YXRQ, TodayOrder->BDBDXH, TodayOrder->GTHHBZ, TodayOrder->GTDWC, TodayOrder->WTLX);
	}
}
void PBStepSpi::OnRspQryTodayTrade(PBStepTodayTradeField* TodayTrade, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTodayTrade, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayTrade)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayTradeField: SCDM[%s] HYDM[%s] HYDMMC[%s] MMLB[%s] KPBZ[%s] TBBZ[%s] CJSJ[%s] WTBH[%s] CJSL[%s] CJJG[%s] CJBH[%s] BDBZ[%s] CJRQ[%s] HYLB[%s] GTDWC[%s] CJLX[%s] YWTH[%s]", TodayTrade->SCDM, TodayTrade->HYDM, TodayTrade->HYDMMC, TodayTrade->MMLB, TodayTrade->KPBZ, TodayTrade->TBBZ, TodayTrade->CJSJ, TodayTrade->WTBH, TodayTrade->CJSL, TodayTrade->CJJG, TodayTrade->CJBH, TodayTrade->BDBZ, TodayTrade->CJRQ, TodayTrade->HYLB, TodayTrade->GTDWC, TodayTrade->CJLX, TodayTrade->YWTH);
	}
}
void PBStepSpi::OnRspQryCapital(PBStepCapitalField* Capital, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCapital, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (Capital)
	{
		WRITE_LOG(LogLevel::Info, "PBStepCapitalField: ZJZH[%s] HBDM[%s] QCYE[%s] KYZJ[%s] ZZC[%s] PCDSYK[%s] SXF[%s] XJZC[%s] CRJ[%s]", Capital->ZJZH, Capital->HBDM, Capital->QCYE, Capital->KYZJ, Capital->ZZC, Capital->PCDSYK, Capital->SXF, Capital->XJZC, Capital->CRJ);
	}
}
void PBStepSpi::OnRspQryHolderAccount(PBStepHolderAccountField* HolderAccount, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryHolderAccount, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (HolderAccount)
	{
		WRITE_LOG(LogLevel::Info, "PBStepHolderAccountField: SCDM[%s] SCMC[%s] GDH[%s] ZZHBZ[%s] TBBZ[%s] XWH[%s] SCXX[%s] WPBZ[%s]", HolderAccount->SCDM, HolderAccount->SCMC, HolderAccount->GDH, HolderAccount->ZZHBZ, HolderAccount->TBBZ, HolderAccount->XWH, HolderAccount->SCXX, HolderAccount->WPBZ);
	}
}
void PBStepSpi::OnRspQryInstrument(PBStepInstrumentField* Instrument, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrument, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (Instrument)
	{
		WRITE_LOG(LogLevel::Info, "PBStepInstrumentField: SCDM[%s] HYDM[%s] HYCS[%s] ZXBDJW[%s] HYDMMC[%s] WTSX[%s] ZCSX[%s] DWBZJ[%s] SCLX[%s] DQR[%s] DBYH[%s] PZDM[%s] ZDJC[%s] HYLB[%s] BDDM[%s] BDMC[%s] XQJG[%s]", Instrument->SCDM, Instrument->HYDM, Instrument->HYCS, Instrument->ZXBDJW, Instrument->HYDMMC, Instrument->WTSX, Instrument->ZCSX, Instrument->DWBZJ, Instrument->SCLX, Instrument->DQR, Instrument->DBYH, Instrument->PZDM, Instrument->ZDJC, Instrument->HYLB, Instrument->BDDM, Instrument->BDMC, Instrument->XQJG);
	}
}
void PBStepSpi::OnRspQrySystemStatus(PBStepSystemStatusField* SystemStatus, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySystemStatus, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (SystemStatus)
	{
		WRITE_LOG(LogLevel::Info, "PBStepSystemStatusField: SCDM[%s] HYDM[%s] XTZT[%s] JYZZT[%s]", SystemStatus->SCDM, SystemStatus->HYDM, SystemStatus->XTZT, SystemStatus->JYZZT);
	}
}
void PBStepSpi::OnRspQrySettlement(PBStepSettlementField* Settlement, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySettlement, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (Settlement)
	{
		WRITE_LOG(LogLevel::Info, "PBStepSettlementField: JSD[%s] QRBZ[%s]", Settlement->JSD, Settlement->QRBZ);
	}
}
void PBStepSpi::OnRspQryTodayExecOrder(PBStepTodayExecOrderField* TodayExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTodayExecOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayExecOrderField: SCDM[%s] WTBH[%s] HYDM[%s] WTZT[%s] WTJG[%s] WTSL[%s] WTSJ[%s] SBSJ[%s] XWH[%s] XDXW[%s] FJYSQLB[%s] TBBZ[%s] KZZD[%s]", TodayExecOrder->SCDM, TodayExecOrder->WTBH, TodayExecOrder->HYDM, TodayExecOrder->WTZT, TodayExecOrder->WTJG, TodayExecOrder->WTSL, TodayExecOrder->WTSJ, TodayExecOrder->SBSJ, TodayExecOrder->XWH, TodayExecOrder->XDXW, TodayExecOrder->FJYSQLB, TodayExecOrder->TBBZ, TodayExecOrder->KZZD);
	}
}
void PBStepSpi::OnRspExecOrder(PBStepRspExecOrderField* RspExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspExecOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspExecOrderField: WTBH[%s] BDBDXH[%s] GTHHBZ[%s]", RspExecOrder->WTBH, RspExecOrder->BDBDXH, RspExecOrder->GTHHBZ);
	}
}
void PBStepSpi::OnRspCancelExecOrder(PBStepRspCancelExecOrderField* RspCancelExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspCancelExecOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspCancelExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspCancelExecOrderField:");
	}
}
void PBStepSpi::OnRspInquiry(PBStepRspInquiryField* RspInquiry, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspInquiry, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspInquiry)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspInquiryField: XJBH[%s]", RspInquiry->XJBH);
	}
}
void PBStepSpi::OnRspQryFutureCommissionRate(PBStepFutureCommissionRateField* FutureCommissionRate, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryFutureCommissionRate, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (FutureCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "PBStepFutureCommissionRateField: SCDM[%s] HYDM[%s] TBBZ[%s] KCJEBL[%s] PCJEBL[%s] PJJEBL[%s] KCDWJE[%s] PCDWJE[%s] PJDWJE[%s]", FutureCommissionRate->SCDM, FutureCommissionRate->HYDM, FutureCommissionRate->TBBZ, FutureCommissionRate->KCJEBL, FutureCommissionRate->PCJEBL, FutureCommissionRate->PJJEBL, FutureCommissionRate->KCDWJE, FutureCommissionRate->PCDWJE, FutureCommissionRate->PJDWJE);
	}
}
void PBStepSpi::OnRspQryFutureMarginRate(PBStepFutureMarginRateField* FutureMarginRate, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryFutureMarginRate, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (FutureMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "PBStepFutureMarginRateField: SCDM[%s] HYDM[%s] TBBZ[%s] MMLB[%s] KCJEBL[%s] KCDWJE[%s]", FutureMarginRate->SCDM, FutureMarginRate->HYDM, FutureMarginRate->TBBZ, FutureMarginRate->MMLB, FutureMarginRate->KCJEBL, FutureMarginRate->KCDWJE);
	}
}
void PBStepSpi::OnRspQryTransferMoney(PBStepTransferMoneyField* TransferMoney, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTransferMoney, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TransferMoney)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTransferMoneyField: LSXH[%s] ZZJE[%s] HBDM[%s] YZYWBZ[%s] YZYWZT[%s] SQRQ[%s] SQSJ[%s] JGSM[%s]", TransferMoney->LSXH, TransferMoney->ZZJE, TransferMoney->HBDM, TransferMoney->YZYWBZ, TransferMoney->YZYWZT, TransferMoney->SQRQ, TransferMoney->SQSJ, TransferMoney->JGSM);
	}
}
void PBStepSpi::OnRspQryIncTrade(PBStepTodayTradeField* TodayTrade, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryIncTrade, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayTrade)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayTradeField: SCDM[%s] HYDM[%s] HYDMMC[%s] MMLB[%s] KPBZ[%s] TBBZ[%s] CJSJ[%s] WTBH[%s] CJSL[%s] CJJG[%s] CJBH[%s] BDBZ[%s] CJRQ[%s] HYLB[%s] GTDWC[%s] CJLX[%s] YWTH[%s]", TodayTrade->SCDM, TodayTrade->HYDM, TodayTrade->HYDMMC, TodayTrade->MMLB, TodayTrade->KPBZ, TodayTrade->TBBZ, TodayTrade->CJSJ, TodayTrade->WTBH, TodayTrade->CJSL, TodayTrade->CJJG, TodayTrade->CJBH, TodayTrade->BDBZ, TodayTrade->CJRQ, TodayTrade->HYLB, TodayTrade->GTDWC, TodayTrade->CJLX, TodayTrade->YWTH);
	}
}
void PBStepSpi::OnRspQryIncOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryIncOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (TodayOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepTodayOrderField: SCDM[%s] WTBH[%s] HYDM[%s] WTZT[%s] MMLB[%s] WTSL[%s] WTJG[%s] CJSL[%s] CDSL[%s] WTSJ[%s] SJWTLB[%s] GDH[%s] WTRQ[%s] KPBZ[%s] TBBZ[%s] BDBZ[%s] BZXX[%s] JGLB[%s] YXQLX[%s] CJLLX[%s] ZXCJL[%s] KZZD[%s] CFTJ[%s] CDSJ[%s] YXRQ[%s] BDBDXH[%s] GTHHBZ[%s] GTDWC[%s] WTLX[%s]", TodayOrder->SCDM, TodayOrder->WTBH, TodayOrder->HYDM, TodayOrder->WTZT, TodayOrder->MMLB, TodayOrder->WTSL, TodayOrder->WTJG, TodayOrder->CJSL, TodayOrder->CDSL, TodayOrder->WTSJ, TodayOrder->SJWTLB, TodayOrder->GDH, TodayOrder->WTRQ, TodayOrder->KPBZ, TodayOrder->TBBZ, TodayOrder->BDBZ, TodayOrder->BZXX, TodayOrder->JGLB, TodayOrder->YXQLX, TodayOrder->CJLLX, TodayOrder->ZXCJL, TodayOrder->KZZD, TodayOrder->CFTJ, TodayOrder->CDSJ, TodayOrder->YXRQ, TodayOrder->BDBDXH, TodayOrder->GTHHBZ, TodayOrder->GTDWC, TodayOrder->WTLX);
	}
}
void PBStepSpi::OnRspQryLockAvailable(PBStepLockAvailableField* LockAvailable, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryLockAvailable, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (LockAvailable)
	{
		WRITE_LOG(LogLevel::Info, "PBStepLockAvailableField: KMSL[%s] SCDM[%s] HYDM[%s] SDFX[%s]", LockAvailable->KMSL, LockAvailable->SCDM, LockAvailable->HYDM, LockAvailable->SDFX);
	}
}
void PBStepSpi::OnRspLockSecurityOrder(PBStepRspLockSecurityOrderField* RspLockSecurityOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspLockSecurityOrder, reqNo:[%d], isLast:[%d]", reqNo, isLast);
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (RspLockSecurityOrder)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspLockSecurityOrderField: WTBH[%s] WTSJ[%s]", RspLockSecurityOrder->WTBH, RspLockSecurityOrder->WTSJ);
	}
}
void PBStepSpi::OnRtnSystemStatus(PBStepSystemStatusField* SystemStatus)
{
	WRITE_LOG(LogLevel::Info, "OnRtnSystemStatus");
	WRITE_LOG(LogLevel::Info, "PBStepSystemStatusField: SCDM[%s] HYDM[%s] XTZT[%s] JYZZT[%s]", SystemStatus->SCDM, SystemStatus->HYDM, SystemStatus->XTZT, SystemStatus->JYZZT);
}
void PBStepSpi::OnRtnOrder(PBStepOrderField* Order)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOrder");
	WRITE_LOG(LogLevel::Info, "PBStepOrderField: SCDM[%s] HYDM[%s] GDH[%s] MMLB[%s] KPBZ[%s] TBBZ[%s] WTZT[%s] QPBZ[%s] WTSJ[%s] CDSJ[%s] WTBH[%s] WTXTH[%s] WTSL[%s] CJSL[%s] WCJSL[%s] WTRQ[%s] JYRQ[%s] WTJG[%s] WTZHLX[%s] JGLB[%s] YXQLX[%s] CJLLX[%s] ZXCJL[%s] CFTJ[%s] KZZD[%s] HYLB[%s] BDBZ[%s] CDSL[%s] BZXX[%s] SJWTLB[%s] BDBDXH[%s] GTHHBZ[%s]", Order->SCDM, Order->HYDM, Order->GDH, Order->MMLB, Order->KPBZ, Order->TBBZ, Order->WTZT, Order->QPBZ, Order->WTSJ, Order->CDSJ, Order->WTBH, Order->WTXTH, Order->WTSL, Order->CJSL, Order->WCJSL, Order->WTRQ, Order->JYRQ, Order->WTJG, Order->WTZHLX, Order->JGLB, Order->YXQLX, Order->CJLLX, Order->ZXCJL, Order->CFTJ, Order->KZZD, Order->HYLB, Order->BDBZ, Order->CDSL, Order->BZXX, Order->SJWTLB, Order->BDBDXH, Order->GTHHBZ);
}
void PBStepSpi::OnRtnTrade(PBStepTradeField* Trade)
{
	WRITE_LOG(LogLevel::Info, "OnRtnTrade");
	WRITE_LOG(LogLevel::Info, "PBStepTradeField: SCDM[%s] HYDM[%s] HYDMMC[%s] MMLB[%s] KPBZ[%s] TBBZ[%s] CJSJ[%s] WTBH[%s] CJSL[%s] CJJG[%s] CJBH[%s] BDBZ[%s] CJRQ[%s] HYLB[%s]", Trade->SCDM, Trade->HYDM, Trade->HYDMMC, Trade->MMLB, Trade->KPBZ, Trade->TBBZ, Trade->CJSJ, Trade->WTBH, Trade->CJSL, Trade->CJJG, Trade->CJBH, Trade->BDBZ, Trade->CJRQ, Trade->HYLB);
}
void PBStepSpi::OnRtnExecOrder(PBStepExecOrderField* ExecOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnExecOrder");
	WRITE_LOG(LogLevel::Info, "PBStepExecOrderField: SCDM[%s] WTBH[%s] HYDM[%s] WTZT[%s] WTSL[%s] WTSJ[%s] XWH[%s] BZXX[%s] FJYSQLB[%s] TBBZ[%s] KZZD[%s] BDBDXH[%s] GTHHBZ[%s]", ExecOrder->SCDM, ExecOrder->WTBH, ExecOrder->HYDM, ExecOrder->WTZT, ExecOrder->WTSL, ExecOrder->WTSJ, ExecOrder->XWH, ExecOrder->BZXX, ExecOrder->FJYSQLB, ExecOrder->TBBZ, ExecOrder->KZZD, ExecOrder->BDBDXH, ExecOrder->GTHHBZ);
}
