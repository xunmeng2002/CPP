#pragma once
#include <string>

using namespace std;


class GlobalParam
{
	GlobalParam()
		:m_NextExpectedMsgSeqNum(0)
	{
	}
	GlobalParam(const GlobalParam&) = delete;
	GlobalParam& operator=(const GlobalParam&) = delete;
public:
	static GlobalParam& GetInstance()
	{
		return m_Instance;
	}
	void SetNextExpectedMsgSeqNum(int value);
	int GetNextExpectedMsgSeqNum();

	void SetSenderCompID(string value);
	string GetSenderCompID();


private:
	static GlobalParam m_Instance;

	int m_NextExpectedMsgSeqNum;
	string m_SenderCompID;
};

