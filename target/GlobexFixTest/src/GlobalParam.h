#pragma once
#include <string>

using namespace std;


class GlobalParam
{
	GlobalParam()
		:m_NextSendSeqNum(2), m_LastRecvSeqNum(1)
	{
	}
	GlobalParam(const GlobalParam&) = delete;
	GlobalParam& operator=(const GlobalParam&) = delete;
public:
	static GlobalParam& GetInstance()
	{
		return m_Instance;
	}
	void SetNextSendSeqNum(int value);
	int GetNextSendSeqNum();

	bool ResetLastRecvSeqNum(int value);
	bool SetLastRecvSeqNum(int value);
	int GetLastRecvSeqNum();
	int GetNextExpectSeqNum();

private:
	static GlobalParam m_Instance;

	int m_NextSendSeqNum;
	int m_LastRecvSeqNum;
};

