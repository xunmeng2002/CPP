#include "SeqNum.h"
#include <fstream>
#include <Windows.h>
#include <process.h>
#include <assert.h>

SeqNum SeqNum::m_Instance;

#define DATA_FILE_PATH "Data"
#define SEQ_NUM_FILE "SeqNums.txt"

SeqNum::SeqNum()
:m_LastSendSeqNum(0), m_LastRecvSeqNum(0)
{
	m_SeqNumFileName = string(DATA_FILE_PATH) + "\\" + SEQ_NUM_FILE;
	CreateDataDir(DATA_FILE_PATH);
	Open();
	ReadSeqNum();
}
SeqNum::~SeqNum()
{
	WriteSeqNum();
}

bool SeqNum::CreateDataDir(const char* path)
{
	return CreateDirectory(path, NULL) || ERROR_ALREADY_EXISTS == GetLastError();
}
void SeqNum::Open()
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
void SeqNum::Close()
{
	if (m_SeqNumFile)
	{
		fclose(m_SeqNumFile);
	}
}

void SeqNum::ReadSeqNum()
{
	rewind(m_SeqNumFile);
	auto len = fscanf(m_SeqNumFile, "%d:%d", &m_LastRecvSeqNum, &m_LastSendSeqNum);
	assert(len == 2);
}
void SeqNum::WriteSeqNum()
{
	rewind(m_SeqNumFile);
	fprintf(m_SeqNumFile, "%d:%d", m_LastRecvSeqNum, m_LastSendSeqNum);
	fflush(m_SeqNumFile);
}

void SeqNum::ResetSeqNum()
{
	m_LastSendSeqNum = 0;
	m_LastRecvSeqNum = 0;
	WriteSeqNum();
}

int SeqNum::GetAndIncreaseNextSendSeqNum()
{
	++m_LastSendSeqNum;
	WriteSeqNum();
	return m_LastSendSeqNum;
}
int SeqNum::GetNextSendSeqNum()
{
	return m_LastSendSeqNum + 1;
}
void SeqNum::SetNextSendSeqNum(int value)
{
	if (value <= m_LastSendSeqNum)
		return;
	m_LastSendSeqNum = value - 1;
	WriteSeqNum();
}
void SeqNum::SetNextSendSeqNum(string value)
{
	SetNextSendSeqNum(atoi(value.c_str()));
}


int SeqNum::GetNextExpectSeqNum()
{
	return m_LastRecvSeqNum + 1;
}
int SeqNum::GetLastRecvSeqNum()
{
	return m_LastRecvSeqNum;
}
void SeqNum::SetLastRecvSeqNum(int value)
{
	if (value <= m_LastRecvSeqNum)
	{
		return;
	}
	m_LastRecvSeqNum = value;
	WriteSeqNum();
}
void SeqNum::SetLastRecvSeqNum(string value)
{
	SetLastRecvSeqNum(atoi(value.c_str()));
}
