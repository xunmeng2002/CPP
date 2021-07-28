#include "GlobalParam.h"


GlobalParam GlobalParam::m_Instance;

void GlobalParam::SetNextSendSeqNum(int value)
{
	m_NextSendSeqNum = value;
}
int GlobalParam::GetNextSendSeqNum()
{
	return m_NextSendSeqNum++;
}


int GlobalParam::GetLastRecvSeqNum()
{
	return m_LastRecvSeqNum;
}
int GlobalParam::GetNextExpectSeqNum()
{
	return m_LastRecvSeqNum + 1;
}
bool GlobalParam::SetLastRecvSeqNum(int value)
{
	if (value > m_LastRecvSeqNum)
	{
		m_LastRecvSeqNum = value;
		return true;
	}
	else
	{
		return false;
	}
}
bool GlobalParam::ResetLastRecvSeqNum(int value)
{
	if (value > m_LastRecvSeqNum)
	{
		m_LastRecvSeqNum = value;
		return true;
	}
	else
	{
		return false;
	}
}

