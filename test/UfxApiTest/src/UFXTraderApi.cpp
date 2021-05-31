#include "UFXTraderApi.h"


CUFXTraderApi::CUFXTraderApi()
	:m_FrontAddress{ 0 }
{
	m_pConfig = NewConfig();
	m_pConfig->AddRef();

	m_pConnection = nullptr;
}
CUFXTraderApi::~CUFXTraderApi()
{
	if (m_pConfig)
	{
		m_pConfig->Release();
	}
	m_pConfig = nullptr;
	if (m_pConnection)
	{
		m_pConnection->Release();
	}
	m_pConnection = nullptr;
}

void CUFXTraderApi::RegisterFront(const char* pszFrontAddress)
{
	strncpy(m_FrontAddress, pszFrontAddress, sizeof(m_FrontAddress) - 1);
}
int CUFXTraderApi::InitConfig(const char* pszLicFile, const char* pszSafeLevel, const char* pszPwd, const char* pszSslFile, const char* pszSslPwd)
{
	//配置连接对象
	m_pConfig->SetString("t2sdk", "servers", m_FrontAddress);
	m_pConfig->SetString("t2sdk", "license_file", pszLicFile);
	m_pConfig->SetString("t2sdk", "login_name", "CUFXTraderApi");

	m_pConfig->SetInt("t2sdk", "init_recv_buf_size", 512);
	m_pConfig->SetInt("t2sdk", "init_send_buf_size", 512);
	m_pConfig->SetInt("t2sdk", "send_queue_size", 10000);
	m_pConfig->SetInt("t2sdk", "heartbeat_time", 30);

	//通讯加密设置，必须在NewConnection之前
	//如果接入前置t2通道设置了safe_level = pwd
	if (pszSafeLevel == "pwd")
	{
		m_pConfig->SetString("safe", "safe_level", "pwd");
		//通信密码
		m_pConfig->SetString("safe", "comm_pwd", pszPwd);
	}

	//如果接入前置t2通道设置了safe_level = ssl
	if (strcmp(pszSslFile, "") != 0)
	{
		m_pConfig->SetString("safe", "safe_level", "ssl");
		m_pConfig->SetString("safe", "cert_file", pszSslFile); //Cert文件
		m_pConfig->SetString("safe", "cert_pwd", pszSslPwd); //Cert密码
	}
}
int CUFXTraderApi::ReqGetClientConnectionSessionID(const char* pszFundAccount, const char* pszPassword)
{

}
int CUFXTraderApi::ReqClientAuth(const char* pszFundAccount, const char* pszAppId, const char* pszAuthCode)
{

}
int CUFXTraderApi::ReqClientSysInfoSubmit(const char* pszFundAccount, const char* pszAppId)
{

}
int CUFXTraderApi::ReqClientLogin(const char* pszFundAccount, const char* pszPassword, char cEntrustWay)
{

}
int CUFXTraderApi::ReqOrderInsert(const char* pszExchangeType, const char* pszFutuCode, char cEntrustBs, char cFuturesDirection, int nEntrustAmount, double dFutuEntrustPrice)
{

}
int CUFXTraderApi::ReqOrderAction(int nEntrustNo)
{

}
int CUFXTraderApi::ReqOrderQry(const char* pszPositionStr, int nRequestNum)
{

}
int CUFXTraderApi::ReqTradeQry()
{

}
int CUFXTraderApi::ReqInvestorPositionQry()
{

}
int CUFXTraderApi::SubscribeEntrustDeal(int nIssueType)
{

}

