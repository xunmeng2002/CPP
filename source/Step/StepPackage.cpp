#include <stdio.h>
#include "StepPackage.h"
#include "CacheList.h"


int ChangeEndian(int x)
{
	return
		((x & 0x000000ff) << 24) |
		((x & 0x0000ff00) << 8) |
		((x & 0x00ff0000) >> 8) |
		((x & 0xff000000) >> 24);
}
char* CheckSum(char* buff, int len)
{
	char tmpBuf[4] = { 0 };
	unsigned int sum;
	for (int i = 0; i < len; i++)
	{
		sum += (unsigned int)buff[i];
	}

	sprintf(tmpBuf, "%03d", (unsigned int)(sum % 256));
	return (tmpBuf);
}


void StepHeader::ToStream(char* buff)
{
	int tid = TID;
	int length = BodyLength;
	ChangeEndian(tid);
	ChangeEndian(length);

	::memcpy(buff, &Mark, 4);
	::memcpy(buff + 4, &tid, 4);
	::memcpy(buff + 8, &length, 4);
}
void StepHeader::FromStream(const char* buff)
{
	::memcpy(Mark, buff, 4);
	::memcpy(&TID, buff + 4, 4);
	::memcpy(&BodyLength, buff + 8, 4);
	ChangeEndian(TID);
	ChangeEndian(BodyLength);
}
bool StepHeader::CheckHeader()
{
	return strncmp(Mark, "STEP", 4) == 0 && TID > 0 && BodyLength >= 0;
}


StepPackage::StepPackage()
{
	m_Header = new StepHeader();
	m_FieldBuffer = new char[STEP_MAX_FIELD_LEN + 64];
	m_HeaderBuffer = new char[STEP_HEADER_LEN];
	m_CacheList = new CacheList();
}
StepPackage::~StepPackage()
{
	delete m_Header;
	delete[] m_FieldBuffer;
	delete[] m_HeaderBuffer;
	delete m_CacheList;
}
void StepPackage::SetTID(int tid)
{
	::memcpy(m_Header->Mark, "STEP", 4);
	m_Header->TID = tid;
}
void StepPackage::MakePackage()
{
	int len = 0;
	char recordOp = STRUCT_SEPARATOR;
	char fieldOp = FIELD_SEPARATOR;
	m_CacheList->Clear();

	for (auto& it : m_BaseRecord)
	{
		len = _snprintf(m_FieldBuffer, STEP_MAX_FIELD_LEN, "%d=%s", it.first, it.second.c_str());
		m_CacheList->PushBack(m_FieldBuffer, len);
		m_CacheList->PushBack(&fieldOp, 1);
	}
	m_CacheList->PushBack(&recordOp, 1);

	for (auto& record : m_Records)
	{
		for (auto& it : record)
		{
			len = _snprintf(m_FieldBuffer, STEP_MAX_FIELD_LEN, "%d=%s", it.first, it.second.c_str());
			m_CacheList->PushBack(m_FieldBuffer, len);
			m_CacheList->PushBack(&fieldOp, 1);
		}
		m_CacheList->PushBack(&recordOp, 1);
	}

	m_Header->BodyLength = m_CacheList->GetLength() + STEP_HEADER_LEN;
	m_Header->ToStream(m_HeaderBuffer);
	m_CacheList->PushFront(m_HeaderBuffer, STEP_HEADER_LEN);
}
bool StepPackage::ParsePackage()
{
	if (!ParseHeader())
	{
		return false;
	}
}
void StepPackage::AppendBaseRecord(std::map<int, std::string>& record)
{
	m_BaseRecord = record;
}
void StepPackage::AppendRecord(std::map<int, std::string>& record)
{
	m_Records.push_back(record);
}

const char* StepPackage::GetData(int& len)
{
	return (char*)m_CacheList->GetData(len);
}
void StepPackage::PushBack(const char* data, int len)
{
	m_CacheList->PushBack(data, len);
}
bool StepPackage::PopFront(int len)
{
	return m_CacheList->PopFront(nullptr, len);
}
bool StepPackage::IsEmpty()
{
	return m_CacheList->IsEmpty();
}

bool StepPackage::ParseHeader()
{
	int len = 0;
	auto data = m_CacheList->GetData(len);
	if (len >= STEP_HEADER_LEN)
	{
		::memcpy(m_HeaderBuffer, data, STEP_HEADER_LEN);
		m_CacheList->PopFront(nullptr, STEP_HEADER_LEN);
	}
	else
	{
		::memcpy(m_HeaderBuffer, data, len);
		m_CacheList->PopFront(nullptr, len);
		int len2 = 0;
		data = m_CacheList->GetData(len2);
		if (len2 < STEP_HEADER_LEN - len)
		{
			return false;
		}
		::memcpy(m_HeaderBuffer + len, data, STEP_HEADER_LEN - len);
		m_CacheList->PopFront(nullptr, STEP_HEADER_LEN - len);
	}
	m_Header->FromStream(m_HeaderBuffer);
	return m_Header->CheckHeader();
}
bool StepPackage::ParseBaseRecord()
{
	int len = 0;
	auto data = m_CacheList->GetData(len);
}
