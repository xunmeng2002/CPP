#pragma once
#include <string>

using namespace std;


class GlobalParam
{
	GlobalParam()
		:m_NextSendSeqNum(1), m_NextExpectSeqNum(1)
	{
		ReadSeqNumFromFile();
	}
	~GlobalParam()
	{
		StoreSeqNumToFile();
	}
	GlobalParam(const GlobalParam&) = delete;
	GlobalParam& operator=(const GlobalParam&) = delete;
public:
	static GlobalParam& GetInstance()
	{
		return m_Instance;
	}
	void ReadSeqNumFromFile();
	void StoreSeqNumToFile();

	int GetNextSendSeqNum();
	void SetNextSendSeqNum(int value);
	void SetNextSendSeqNum(string value);
	int GetLastRecvSeqNum();
	void SetLastRecvSeqNum(int value);
	void SetLastRecvSeqNum(string value);
	int GetNextExpectSeqNum();
	void SetNextExpectSeqNum(int value);
	void SetNextExpectSeqNum(string value);
	void IncreaseNextExpectSeqNum();


private:
	static GlobalParam m_Instance;

	int m_NextSendSeqNum;
	int m_LastRecvSeqNum;
	int m_NextExpectSeqNum;
	int m_SequenceResetNum;
	int m_MaxRecvSeqNum;
};

