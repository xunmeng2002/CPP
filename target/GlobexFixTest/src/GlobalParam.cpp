#include "GlobalParam.h"
#include <fstream>
#include <Windows.h>
#include <process.h>
#include <assert.h>

GlobalParam GlobalParam::m_Instance;

#define DATA_FILE_PATH "Data"
#define SEQ_NUM_FILE "SeqNums.txt"

GlobalParam::GlobalParam()
:m_NextSendSeqNum(1), m_LastRecvSeqNum(1), m_ClOrdID(1)
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
	auto len = fscanf(m_SeqNumFile, "%d:%d", &m_LastRecvSeqNum, &m_NextSendSeqNum);
	assert(len == 2);
}
void GlobalParam::WriteSeqNum()
{
	rewind(m_SeqNumFile);
	fprintf(m_SeqNumFile, "%d:%d", m_LastRecvSeqNum, m_NextSendSeqNum);
	fflush(m_SeqNumFile);
}

int GlobalParam::GetNextSendSeqNum()
{
	return m_NextSendSeqNum;
}
void GlobalParam::SetNextSendSeqNum(int value)
{
	if (value < m_NextSendSeqNum)
		return;
	m_NextSendSeqNum = value;
	WriteSeqNum();
}
void GlobalParam::SetNextSendSeqNum(string value)
{
	SetNextSendSeqNum(atoi(value.c_str()));
}
void GlobalParam::ResetNextSendSeqNum(string value)
{
	m_NextSendSeqNum = atoi(value.c_str());
}
void GlobalParam::IncreaseNextSendSeqNum()
{
	m_NextSendSeqNum++;
	WriteSeqNum();
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



int GlobalParam::GetClOrdID()
{
	return m_ClOrdID++;
}