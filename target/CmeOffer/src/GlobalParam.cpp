#include "GlobalParam.h"
#include <fstream>
#include <Windows.h>
#include <process.h>
#include <assert.h>

GlobalParam GlobalParam::m_Instance;

#define DATA_FILE_PATH "Data"
#define SEQ_NUM_FILE "SeqNums.txt"

GlobalParam::GlobalParam()
:m_LastSendSeqNum(0), m_LastRecvSeqNum(0), m_OrderLocalID(1)
{
	m_SeqNumFileName = string(DATA_FILE_PATH) + "\\" + SEQ_NUM_FILE;
	CreateDataDir(DATA_FILE_PATH);
	Open();
	ReadSeqNum();
}
GlobalParam::~GlobalParam()
{
	WriteSeqNum();
}

bool GlobalParam::CreateDataDir(const char* path)
{
	return CreateDirectory(path, NULL) || ERROR_ALREADY_EXISTS == GetLastError();
}
void GlobalParam::Open()
{
	m_SeqNumFile = fopen(m_SeqNumFileName.c_str(), "r+");
	if (!m_SeqNumFile)
	{
		m_SeqNumFile = fopen(m_SeqNumFileName.c_str(), "w+");
	}
	if (!m_SeqNumFile)
	{
		throw exception(string("Can not Open SeqNumFile:" + m_SeqNumFileName).c_str());
	}
}
void GlobalParam::Close()
{
	if (m_SeqNumFile)
	{
		fclose(m_SeqNumFile);
	}
}

void GlobalParam::ReadSeqNum()
{
	rewind(m_SeqNumFile);
	auto len = fscanf(m_SeqNumFile, "%d:%d:%d", &m_LastRecvSeqNum, &m_LastSendSeqNum, &m_OrderLocalID);
	assert(len == 3);
}
void GlobalParam::WriteSeqNum()
{
	rewind(m_SeqNumFile);
	fprintf(m_SeqNumFile, "%d:%d:%d", m_LastRecvSeqNum, m_LastSendSeqNum, m_OrderLocalID);
	fflush(m_SeqNumFile);
}

void GlobalParam::ResetSeqNum()
{
	m_LastSendSeqNum = 0;
	m_LastRecvSeqNum = 0;
	m_OrderLocalID = 0;
	WriteSeqNum();
}

int GlobalParam::GetAndIncreaseNextSendSeqNum()
{
	++m_LastSendSeqNum;
	WriteSeqNum();
	return m_LastSendSeqNum;
}
int GlobalParam::GetNextSendSeqNum()
{
	return m_LastSendSeqNum + 1;
}
void GlobalParam::SetNextSendSeqNum(int value)
{
	if (value <= m_LastSendSeqNum)
		return;
	m_LastSendSeqNum = value - 1;
	WriteSeqNum();
}
void GlobalParam::SetNextSendSeqNum(string value)
{
	SetNextSendSeqNum(atoi(value.c_str()));
}


int GlobalParam::GetNextExpectSeqNum()
{
	return m_LastRecvSeqNum + 1;
}
int GlobalParam::GetLastRecvSeqNum()
{
	return m_LastRecvSeqNum;
}
void GlobalParam::SetLastRecvSeqNum(int value)
{
	if (value <= m_LastRecvSeqNum)
	{
		return;
	}
	m_LastRecvSeqNum = value;
	WriteSeqNum();
}
void GlobalParam::SetLastRecvSeqNum(string value)
{
	SetLastRecvSeqNum(atoi(value.c_str()));
}

int GlobalParam::GetNextOrderLocalID()
{
	++m_OrderLocalID;
	WriteSeqNum();
	return m_OrderLocalID;
}
