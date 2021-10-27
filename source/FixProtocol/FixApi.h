#pragma once
#include "FixFields.h"
#include "FixMessage.h"
#include "MdbInterface.h"
#include <string>

using namespace std;

class FixSpi
{
public:
	FixSpi();
	virtual ~FixSpi();
	
	void RegisterSubscriber(MdbPublisher* mdbPublisher) { m_MdbPublisher = mdbPublisher; }
	virtual void OnFixConnected();
	virtual void OnFixDisConnected();
	
	virtual void OnFixRspLogon(FixRspLogonField* rspField);
	virtual void OnFixRspLogout(FixRspLogoutField* rspField);
	virtual void OnFixRspHeartBeat(FixRspHeartBeatField* rspField);
	virtual void OnFixRspTestRequest(FixRspTestRequestField* rspField);
	virtual void OnFixRspResendRequest(FixRspResendRequestField* rspField);
	virtual void OnFixRspSessionLevelReject(FixRspSessionLevelRejectField* rspField);
	virtual void OnFixRspSequenceReset(FixRspSequenceResetField* rspField);
	virtual void OnFixExecutionReport(FixExecutionReportField* rspField);
	virtual void OnFixRspOrderCancelReject(FixRspOrderCancelRejectField* rspField);
protected:
	MdbPublisher* m_MdbPublisher;
	char* m_FixLogBuff;
};


class FixApi
{
public:
	virtual void ReqLogon(FixReqLogonField* reqField);
	virtual void ReqLogout(FixReqLogoutField* reqField);
	virtual void ReqHeartBeat(FixReqHeartBeatField* reqField);
	virtual void ReqTestRequest(FixReqTestRequestField* reqField);
	virtual void ReqResendRequest(FixReqResendRequestField* reqField);
	virtual void ReqSequenceReset(FixReqSequenceResetField* reqField);
	virtual void ReqNewOrder(FixReqNewOrderField* reqField);
	virtual void ReqOrderCancelRequest(FixReqOrderCancelRequestField* reqField);
	virtual void ReqOrderCancelReplaceRequest(FixReqOrderCancelReplaceRequestField* reqField);
	virtual void ReqOrderStatusRequest(FixReqOrderStatusRequestField* reqField);
};

