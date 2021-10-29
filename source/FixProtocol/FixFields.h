#pragma once
#include <string>
#include "FixMessage.h"

using namespace std;

#define HEAD_LEN 18
#define TRAILER_LEN 7

class FixReqHeader
{
public:
	FixReqHeader(const string& fieldName, const string& msgType, const string& MsgClass, FixMessage* fixMessage);
	FixReqHeader(const FixReqHeader&) = delete;
	FixReqHeader operator=(const FixReqHeader&) = delete;
	FixReqHeader(FixReqHeader&& other) noexcept;
	FixReqHeader& operator=(FixReqHeader&& other) noexcept;
	~FixReqHeader();
	
	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff);
	virtual FixMessage* GetFixMessage();
	static string CreateSql();
	virtual string InsertSql();
	int AddHeader(char* buff, int bodyLen);
	void SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID);
	
public:
	string BeginString;
	string BodyLength;
	string MsgType;
	string MsgSeqNum;
	string PossDupFlag;
	string SenderCompID;
	string SenderSubID;
	string SendingTime;
	string TargetCompID;
	string TargetSubID;
	string OrigSendingTime;
	string SenderLocationID;
	string LastMsgSeqNumProcessed;

	FixMessage* m_FixMessage;
	string FieldName;
	string MsgClass;
protected:
	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};
class FixRspHeader
{
public:
	FixRspHeader(const string& fieldName, const string& msgType, const string& MsgClass, FixMessage* fixMessage);
	FixRspHeader(const FixRspHeader&) = delete;
	FixRspHeader operator=(const FixRspHeader&) = delete;
	FixRspHeader(FixRspHeader&& other) noexcept;
	FixRspHeader& operator=(FixRspHeader&& other) noexcept;
	~FixRspHeader();
	
	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff);
	virtual FixMessage* GetFixMessage();
	static string CreateSql();
	virtual string InsertSql();
	int AddHeader(char* buff, int bodyLen);
	void SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID);
	
public:
	string BeginString;
	string BodyLength;
	string MsgType;
	string MsgSeqNum;
	string PossDupFlag;
	string SenderCompID;
	string SenderSubID;
	string SendingTime;
	string TargetCompID;
	string TargetSubID;
	string OrigSendingTime;
	string TargetLocationID;
	string LastMsgSeqNumProcessed;

	FixMessage* m_FixMessage;
	string FieldName;
	string MsgClass;
protected:
	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

class FixTrailer
{
public:
	FixTrailer(FixMessage* fixMessage);
	int ToString(char* buff, int size);
	void GetFixMessage(FixMessage* fixMessage);
	int AddTrailer(char* buff, int len);
	
public:
	string CheckSum;
};


class FixReqLogonField : public FixReqHeader, public FixTrailer
{
public:
	FixReqLogonField(FixMessage* fixMessage);
	FixReqLogonField(const FixReqLogonField&) = delete;
	FixReqLogonField& operator=(const FixReqLogonField&) = delete;
	FixReqLogonField(FixReqLogonField&& other) noexcept;
	FixReqLogonField& operator=(FixReqLogonField&& other) noexcept;
	~FixReqLogonField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string HeartBtInt;
	string ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	string EncodedTextLen;
	string EncodedText;
	string EncryptedPasswordMethod;
	string EncryptedPasswordLen;
	string EncryptedPassword;

	static constexpr char* TableName = "t_FixReqLogon";
};
class FixReqLogoutField : public FixReqHeader, public FixTrailer
{
public:
	FixReqLogoutField(FixMessage* fixMessage);
	FixReqLogoutField(const FixReqLogoutField&) = delete;
	FixReqLogoutField& operator=(const FixReqLogoutField&) = delete;
	FixReqLogoutField(FixReqLogoutField&& other) noexcept;
	FixReqLogoutField& operator=(FixReqLogoutField&& other) noexcept;
	~FixReqLogoutField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Text;
	string NextExpectedMsgSeqNum;
	string SplitMsg;

	static constexpr char* TableName = "t_FixReqLogout";
};
class FixReqHeartBeatField : public FixReqHeader, public FixTrailer
{
public:
	FixReqHeartBeatField(FixMessage* fixMessage);
	FixReqHeartBeatField(const FixReqHeartBeatField&) = delete;
	FixReqHeartBeatField& operator=(const FixReqHeartBeatField&) = delete;
	FixReqHeartBeatField(FixReqHeartBeatField&& other) noexcept;
	FixReqHeartBeatField& operator=(FixReqHeartBeatField&& other) noexcept;
	~FixReqHeartBeatField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string TestReqID;
	string SplitMsg;

	static constexpr char* TableName = "t_FixReqHeartBeat";
};
class FixReqTestRequestField : public FixReqHeader, public FixTrailer
{
public:
	FixReqTestRequestField(FixMessage* fixMessage);
	FixReqTestRequestField(const FixReqTestRequestField&) = delete;
	FixReqTestRequestField& operator=(const FixReqTestRequestField&) = delete;
	FixReqTestRequestField(FixReqTestRequestField&& other) noexcept;
	FixReqTestRequestField& operator=(FixReqTestRequestField&& other) noexcept;
	~FixReqTestRequestField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string TestReqID;

	static constexpr char* TableName = "t_FixReqTestRequest";
};
class FixReqResendRequestField : public FixReqHeader, public FixTrailer
{
public:
	FixReqResendRequestField(FixMessage* fixMessage);
	FixReqResendRequestField(const FixReqResendRequestField&) = delete;
	FixReqResendRequestField& operator=(const FixReqResendRequestField&) = delete;
	FixReqResendRequestField(FixReqResendRequestField&& other) noexcept;
	FixReqResendRequestField& operator=(FixReqResendRequestField&& other) noexcept;
	~FixReqResendRequestField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string BeginSeqNo;
	string EndSeqNo;

	static constexpr char* TableName = "t_FixReqResendRequest";
};
class FixReqSequenceResetField : public FixReqHeader, public FixTrailer
{
public:
	FixReqSequenceResetField(FixMessage* fixMessage);
	FixReqSequenceResetField(const FixReqSequenceResetField&) = delete;
	FixReqSequenceResetField& operator=(const FixReqSequenceResetField&) = delete;
	FixReqSequenceResetField(FixReqSequenceResetField&& other) noexcept;
	FixReqSequenceResetField& operator=(FixReqSequenceResetField&& other) noexcept;
	~FixReqSequenceResetField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string NewSeqNo;
	string GapFillFlag;

	static constexpr char* TableName = "t_FixReqSequenceReset";
};
class FixReqNewOrderField : public FixReqHeader, public FixTrailer
{
public:
	FixReqNewOrderField(FixMessage* fixMessage);
	FixReqNewOrderField(const FixReqNewOrderField&) = delete;
	FixReqNewOrderField& operator=(const FixReqNewOrderField&) = delete;
	FixReqNewOrderField(FixReqNewOrderField&& other) noexcept;
	FixReqNewOrderField& operator=(FixReqNewOrderField&& other) noexcept;
	~FixReqNewOrderField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Account;
	string ClOrdID;
	string HandInst;
	string CustOrderHandlingInst;
	string OrderQty;
	string OrdType;
	string Price;
	string Side;
	string Symbol;
	string TimeInForce;
	string TransactTime;
	string ManualOrderIndicator;
	string NoAllocs;
	string AllocAccount;
	string StopPx;
	string SecurityDesc;
	string MinQty;
	string SecurityType;
	string CustomerOrFirm;
	string MaxShow;
	string ExpireDate;
	string SelfMatchPreventionID;
	string SelfMatchPreventionInstruction;
	string CtiCode;
	string AvgPxGroupID;
	string ClearingTradePriceType;
	string AvgPXIndicator;
	string Memo;
	string GiveUpFirm;
	string CmtaGiveupCD;
	string CorrelationClOrdID;
	string MarketSegmentID;

	static constexpr char* TableName = "t_FixReqNewOrder";
};
class FixReqOrderCancelRequestField : public FixReqHeader, public FixTrailer
{
public:
	FixReqOrderCancelRequestField(FixMessage* fixMessage);
	FixReqOrderCancelRequestField(const FixReqOrderCancelRequestField&) = delete;
	FixReqOrderCancelRequestField& operator=(const FixReqOrderCancelRequestField&) = delete;
	FixReqOrderCancelRequestField(FixReqOrderCancelRequestField&& other) noexcept;
	FixReqOrderCancelRequestField& operator=(FixReqOrderCancelRequestField&& other) noexcept;
	~FixReqOrderCancelRequestField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Account;
	string ClOrdID;
	string OrderID;
	string OrigClOrdID;
	string Side;
	string Symbol;
	string TransactTime;
	string ManualOrderIndicator;
	string Memo;
	string SecurityDesc;
	string SecurityType;
	string CorrelationClOrdID;

	static constexpr char* TableName = "t_FixReqOrderCancelRequest";
};
class FixReqOrderCancelReplaceRequestField : public FixReqHeader, public FixTrailer
{
public:
	FixReqOrderCancelReplaceRequestField(FixMessage* fixMessage);
	FixReqOrderCancelReplaceRequestField(const FixReqOrderCancelReplaceRequestField&) = delete;
	FixReqOrderCancelReplaceRequestField& operator=(const FixReqOrderCancelReplaceRequestField&) = delete;
	FixReqOrderCancelReplaceRequestField(FixReqOrderCancelReplaceRequestField&& other) noexcept;
	FixReqOrderCancelReplaceRequestField& operator=(FixReqOrderCancelReplaceRequestField&& other) noexcept;
	~FixReqOrderCancelReplaceRequestField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Account;
	string ClOrdID;
	string OrderID;
	string HandInst;
	string OrderQty;
	string CustOrderHandlingInst;
	string OrdType;
	string OrigClOrdID;
	string Price;
	string Side;
	string Symbol;
	string Text;
	string TimeInForce;
	string ManualOrderIndicator;
	string TransactTime;
	string NoAllocs;
	string AllocAccount;
	string StopPx;
	string SecurityDesc;
	string MinQty;
	string SecurityType;
	string CustomerOrFirm;
	string MaxShow;
	string ExpireDate;
	string SelfMatchPreventionID;
	string SelfMatchPreventionInstruction;
	string CtiCode;
	string AvgPxGroupID;
	string ClearingTradePriceType;
	string AvgPXIndicator;
	string Memo;
	string CorrelationClOrdID;
	string OFMOverride;

	static constexpr char* TableName = "t_FixReqOrderCancelReplaceRequest";
};
class FixReqOrderStatusRequestField : public FixReqHeader, public FixTrailer
{
public:
	FixReqOrderStatusRequestField(FixMessage* fixMessage);
	FixReqOrderStatusRequestField(const FixReqOrderStatusRequestField&) = delete;
	FixReqOrderStatusRequestField& operator=(const FixReqOrderStatusRequestField&) = delete;
	FixReqOrderStatusRequestField(FixReqOrderStatusRequestField&& other) noexcept;
	FixReqOrderStatusRequestField& operator=(FixReqOrderStatusRequestField&& other) noexcept;
	~FixReqOrderStatusRequestField();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string ClOrdID;
	string OrderID;
	string Side;
	string Symbol;
	string TransactTime;
	string ManualOrderIndicator;
	string SecurityDesc;
	string SecurityType;
	string CorrelationClOrdID;

	static constexpr char* TableName = "t_FixReqOrderStatusRequest";
};

class FixRspLogonField : public FixRspHeader, public FixTrailer
{
public:
	FixRspLogonField(FixMessage* fixMessage);
	FixRspLogonField(const FixRspLogonField&) = delete;
	FixRspLogonField& operator=(const FixRspLogonField&) = delete;
	FixRspLogonField(FixRspLogonField&& other) noexcept;
	FixRspLogonField& operator=(FixRspLogonField&& other) noexcept;
	~FixRspLogonField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string HeartBtInt;
	string ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	string SplitMsg;

	static constexpr char* TableName = "t_FixRspLogon";
};
class FixRspLogoutField : public FixRspHeader, public FixTrailer
{
public:
	FixRspLogoutField(FixMessage* fixMessage);
	FixRspLogoutField(const FixRspLogoutField&) = delete;
	FixRspLogoutField& operator=(const FixRspLogoutField&) = delete;
	FixRspLogoutField(FixRspLogoutField&& other) noexcept;
	FixRspLogoutField& operator=(FixRspLogoutField&& other) noexcept;
	~FixRspLogoutField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Text;
	string NextExpectedMsgSeqNum;
	string SplitMsg;

	static constexpr char* TableName = "t_FixRspLogout";
};
class FixRspHeartBeatField : public FixRspHeader, public FixTrailer
{
public:
	FixRspHeartBeatField(FixMessage* fixMessage);
	FixRspHeartBeatField(const FixRspHeartBeatField&) = delete;
	FixRspHeartBeatField& operator=(const FixRspHeartBeatField&) = delete;
	FixRspHeartBeatField(FixRspHeartBeatField&& other) noexcept;
	FixRspHeartBeatField& operator=(FixRspHeartBeatField&& other) noexcept;
	~FixRspHeartBeatField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string TestReqID;
	string SplitMsg;

	static constexpr char* TableName = "t_FixRspHeartBeat";
};
class FixRspTestRequestField : public FixRspHeader, public FixTrailer
{
public:
	FixRspTestRequestField(FixMessage* fixMessage);
	FixRspTestRequestField(const FixRspTestRequestField&) = delete;
	FixRspTestRequestField& operator=(const FixRspTestRequestField&) = delete;
	FixRspTestRequestField(FixRspTestRequestField&& other) noexcept;
	FixRspTestRequestField& operator=(FixRspTestRequestField&& other) noexcept;
	~FixRspTestRequestField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string TestReqID;

	static constexpr char* TableName = "t_FixRspTestRequest";
};
class FixRspResendRequestField : public FixRspHeader, public FixTrailer
{
public:
	FixRspResendRequestField(FixMessage* fixMessage);
	FixRspResendRequestField(const FixRspResendRequestField&) = delete;
	FixRspResendRequestField& operator=(const FixRspResendRequestField&) = delete;
	FixRspResendRequestField(FixRspResendRequestField&& other) noexcept;
	FixRspResendRequestField& operator=(FixRspResendRequestField&& other) noexcept;
	~FixRspResendRequestField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string BeginSeqNo;
	string EndSeqNo;

	static constexpr char* TableName = "t_FixRspResendRequest";
};
class FixRspSessionLevelRejectField : public FixRspHeader, public FixTrailer
{
public:
	FixRspSessionLevelRejectField(FixMessage* fixMessage);
	FixRspSessionLevelRejectField(const FixRspSessionLevelRejectField&) = delete;
	FixRspSessionLevelRejectField& operator=(const FixRspSessionLevelRejectField&) = delete;
	FixRspSessionLevelRejectField(FixRspSessionLevelRejectField&& other) noexcept;
	FixRspSessionLevelRejectField& operator=(FixRspSessionLevelRejectField&& other) noexcept;
	~FixRspSessionLevelRejectField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string RefSeqNum;
	string Text;
	string RefTagID;
	string SessionRejectReason;
	string ManualOrderIndicator;
	string SplitMsg;

	static constexpr char* TableName = "t_FixRspSessionLevelReject";
};
class FixRspSequenceResetField : public FixRspHeader, public FixTrailer
{
public:
	FixRspSequenceResetField(FixMessage* fixMessage);
	FixRspSequenceResetField(const FixRspSequenceResetField&) = delete;
	FixRspSequenceResetField& operator=(const FixRspSequenceResetField&) = delete;
	FixRspSequenceResetField(FixRspSequenceResetField&& other) noexcept;
	FixRspSequenceResetField& operator=(FixRspSequenceResetField&& other) noexcept;
	~FixRspSequenceResetField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string NewSeqNo;
	string GapFillFlag;

	static constexpr char* TableName = "t_FixRspSequenceReset";
};
class FixExecutionReportField : public FixRspHeader, public FixTrailer
{
public:
	FixExecutionReportField(FixMessage* fixMessage);
	FixExecutionReportField(const FixExecutionReportField&) = delete;
	FixExecutionReportField& operator=(const FixExecutionReportField&) = delete;
	FixExecutionReportField(FixExecutionReportField&& other) noexcept;
	FixExecutionReportField& operator=(FixExecutionReportField&& other) noexcept;
	~FixExecutionReportField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Account;
	string AvgPx;
	string ClOrdID;
	string CumQty;
	string ExecID;
	string ExecRefID;
	string ExecTransType;
	string LastPx;
	string LastQty;
	string OrderID;
	string OrderQty;
	string OrderStatus;
	string OrdType;
	string OrigClOrdID;
	string Price;
	string SecurityID;
	string Side;
	string Symbol;
	string Text;
	string TimeInForce;
	string TransactTime;
	string SettlDate;
	string TradeDate;
	string NoAllocs;
	string AllocAccount;
	string StopPx;
	string OrdRejReason;
	string SecurityDesc;
	string MinQty;
	string ExecType;
	string LeavesQty;
	string SecurityType;
	string MaxShow;
	string ContraTrader;
	string RefMsgType;
	string ContraBroker;
	string ExecRestatementReason;
	string BusinessRejectReason;
	string TotalNumSecurities;
	string ExpireDate;
	string MultiLegReportingType;
	string SecondaryExecID;
	string CrossID;
	string CrossType;
	string MassStatusReqID;
	string UnderlyingPx;
	string OptionDelta;
	string AvgPXIndicator;
	string LastRptRequest;
	string HostCrossID;
	string ManualOrderIndicator;
	string CustOrderHandlingInst;
	string Volatility;
	string ExpirationTimeValue;
	string RiskFreeRate;
	string NoFills;
	string FillExecID;
	string FillPx;
	string FillQty;
	string ClearingTradePriceType;
	string FillYieldType;
	string AvgPxGroupID;
	string Memo;
	string DelayDuration;
	string RequestTime;
	string SelfMatchPreventionID;
	string SelfMatchPreventionInstruction;
	string SplitMsg;
	string OriginalSecondaryExecID;
	string CorrelationClOrdID;
	string MDTradeEntryID;
	string MarketSegmentID;

	static constexpr char* TableName = "t_FixExecutionReport";
};
class FixRspOrderCancelRejectField : public FixRspHeader, public FixTrailer
{
public:
	FixRspOrderCancelRejectField(FixMessage* fixMessage);
	FixRspOrderCancelRejectField(const FixRspOrderCancelRejectField&) = delete;
	FixRspOrderCancelRejectField& operator=(const FixRspOrderCancelRejectField&) = delete;
	FixRspOrderCancelRejectField(FixRspOrderCancelRejectField&& other) noexcept;
	FixRspOrderCancelRejectField& operator=(FixRspOrderCancelRejectField&& other) noexcept;
	~FixRspOrderCancelRejectField();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string Account;
	string ClOrdID;
	string ExecID;
	string OrderID;
	string OrderStatus;
	string OrigClOrdID;
	string SecurityID;
	string Text;
	string TransactTime;
	string CxlRejReason;
	string SecurityDesc;
	string CancelRejResponseTo;
	string ManualOrderIndicator;
	string CustOrderHandlingInst;
	string Memo;
	string SelfMatchPreventionID;
	string CorrelationClOrdID;
	string RequestTime;
	string DelayDuration;
	string SplitMsg;

	static constexpr char* TableName = "t_FixRspOrderCancelReject";
};

class FixProduct
{
public:
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string ExchangeID;
	string ProductID;
	string MarketSegmentID;

	static constexpr char* TableName = "t_FixProduct";
	
private:
	char m_Buff[4096];
};
class FixInstrument
{
public:
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
	string ExchangeID;
	string ProductID;
	string InstrumentID;
	string ITCAlias;
	string GenCode;
	string MarketSegmentID;

	static constexpr char* TableName = "t_FixInstrument";
	
private:
	char m_Buff[4096];
};

