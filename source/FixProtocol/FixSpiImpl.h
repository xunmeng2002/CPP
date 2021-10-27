#pragma once
#include "FixApi.h"
#include "MdbInterface.h"


class FixSpiImpl : public FixSpi
{
public:
	virtual void OnFixRspSessionLevelReject(FixRspSessionLevelRejectField* rspField) override;
	virtual void OnFixExecutionReport(FixExecutionReportField* rspField) override;
	virtual void OnFixRspOrderCancelReject(FixRspOrderCancelRejectField* rspField) override;

private:
	void OnRtnOrder(FixExecutionReportField* rspField);
	void OnRtnTrade(FixExecutionReportField* rspField);
	void OnErrRtnOrderCancel(FixRspOrderCancelRejectField* rspField);
};

