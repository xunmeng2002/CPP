#include "GlobalParam.h"
#include <fstream>

GlobalParam GlobalParam::m_Instance;

#define SEQ_NUM_FILE "SeqNums.txt"

void GlobalParam::ReadSeqNumFromFile()
{
	ifstream file(SEQ_NUM_FILE, ios::in);
	char line[1024] = { 0 };
	file.getline(line, 1024);
	char* p = line;
	while (*p != ':' && *p != '\0')
	{
		++p;
	}
	m_NextSendSeqNum = atoi(line);
	m_NextExpectSeqNum = atoi(p + 1);
	file.close();
}
void GlobalParam::StoreSeqNumToFile()
{
	ofstream file(SEQ_NUM_FILE, ios::out);
	file << m_NextSendSeqNum << ":" << m_NextExpectSeqNum << endl;
	file.close();
}

int GlobalParam::GetNextSendSeqNum()
{
	return m_NextSendSeqNum;
}
void GlobalParam::SetNextSendSeqNum(int value)
{
	m_NextSendSeqNum = value;
}
void GlobalParam::SetNextSendSeqNum(string value)
{
	auto valueInt = atoi(value.c_str());
	if (valueInt > m_NextSendSeqNum)
	{
		m_NextSendSeqNum = valueInt;
	}
}
void GlobalParam::IncreaseNextSendSeqNum()
{
	m_NextSendSeqNum++;
}

int GlobalParam::GetLastRecvSeqNum()
{
	return m_LastRecvSeqNum;
}
void GlobalParam::SetLastRecvSeqNum(int value)
{
	if (value > m_NextExpectSeqNum)
	{
		m_LastRecvSeqNum = value;
	}
}
void GlobalParam::SetLastRecvSeqNum(string value)
{
	auto valueInt = atoi(value.c_str());
	if (valueInt > m_LastRecvSeqNum)
	{
		m_LastRecvSeqNum = valueInt;
	}
}
int GlobalParam::GetNextExpectSeqNum()
{
	return m_NextExpectSeqNum;
}
void GlobalParam::SetNextExpectSeqNum(int value)
{
	m_NextExpectSeqNum = value;
}
void GlobalParam::SetNextExpectSeqNum(string value)
{
	m_NextExpectSeqNum = atoi(value.c_str());
}
void GlobalParam::IncreaseNextExpectSeqNum()
{
	++m_NextExpectSeqNum;
}

int GlobalParam::GetClOrdID()
{
	return m_ClOrdID++;
}