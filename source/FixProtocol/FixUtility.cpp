#include "FixUtility.h"
#include "SeqNum.h"
#include "AccountInfo.h"
#include "Utility.h"
#include "TimeUtility.h"
#include "Logger.h"
#include "FixMessage.h"


FixMessage* PrepareReqHeader(const std::string& msgSeqNum)
{
	auto fixMessage = FixMessage::Allocate();
	auto& accountInfo = AccountInfo::GetInstance();

	fixMessage->SetItem(8, accountInfo.BeginString);
	if (msgSeqNum.empty())
	{
		fixMessage->SetItem(34, ItoA(SeqNum::GetInstance().GetAndIncreaseNextSendSeqNum()));
	}
	else
	{
		fixMessage->SetItem(34, msgSeqNum);
	}
	fixMessage->SetItem(43, "N");
	fixMessage->SetItem(49, accountInfo.SenderCompID);
	fixMessage->SetItem(50, accountInfo.SenderSubID);
	fixMessage->SetItem(52, GetUtcTime());
	fixMessage->SetItem(56, accountInfo.TargetCompID);
	fixMessage->SetItem(57, accountInfo.TargetSubID);

	fixMessage->SetItem(142, accountInfo.SenderLocationID);
	fixMessage->SetItem(369, ItoA(SeqNum::GetInstance().GetLastRecvSeqNum()));
	
	return fixMessage;
}

int WriteString(char* buff, int size, const string& name, const string& value)
{
	if (size < name.length() + value.length() + 10)
	{
		_ASSERT(false);
		return 0;
	}
	return sprintf(buff, "%s:[%s]", name.c_str(), value.c_str());
}
int WriteStream(char* ppos, int key, string value)
{
	if (value.length() > 0)
	{
		return sprintf(ppos, "%d=%s%c", key, value.c_str(), SOH);
	}
	return 0;
}


int CalculateSum(unsigned char* buff, int len)
{
	int sum = 0;
	for (auto p = buff; p - buff < len; p++)
	{
		sum += *p;
	}
	return sum % 256;
}
bool GetItemEnd(char* buff, int len, int& itemLen)
{
	char* p = buff;
	while (p - buff < len)
	{
		if (*p == SOH)
		{
			itemLen = (p - buff) + 1;
			return true;
		}
		++p;
	}
	itemLen = len;
	return false;
}
bool ParseOneItem(char* buff, int len, int& tag, string& value)
{
	char* p = buff;
	char* pEqual = buff, * pEnd = buff;
	bool equalFind = false;
	bool endFind = false;
	while (p - buff < len)
	{
		if (*p == '=')
		{
			pEqual = p;
			equalFind = true;
			break;
		}
		p++;
	}
	while (p - buff < len)
	{
		if (*p == SOH)
		{
			pEnd = p;
			endFind = true;
			break;
		}
		p++;
	}
	if (equalFind && endFind)
	{
		tag = atoi(buff);
		value = string(pEqual + 1, pEnd);
		return true;
	}
	WRITE_LOG(LogLevel::Error, "ParseOneItem Failed. Buff[%s], len[%d]", buff, len);
	return false;
}
