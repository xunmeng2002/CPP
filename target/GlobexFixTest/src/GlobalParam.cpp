#include "GlobalParam.h"


GlobalParam GlobalParam::m_Instance;

void GlobalParam::SetNextExpectedMsgSeqNum(int value)
{
	m_NextExpectedMsgSeqNum = value;
}
int GlobalParam::GetNextExpectedMsgSeqNum()
{
	return m_NextExpectedMsgSeqNum++;
}

void GlobalParam::SetSenderCompID(string value)
{
	m_SenderCompID = value;
}
string GlobalParam::GetSenderCompID()
{
	return m_SenderCompID;
}