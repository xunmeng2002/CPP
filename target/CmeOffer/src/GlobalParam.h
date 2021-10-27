#pragma once
#include <string>
#include <fstream>

using namespace std;


class GlobalParam
{
	GlobalParam();
	~GlobalParam();
	GlobalParam(const GlobalParam&) = delete;
	GlobalParam& operator=(const GlobalParam&) = delete;
public:
	static GlobalParam& GetInstance()
	{
		return m_Instance;
	}
	bool CreateDataDir(const char* path);
	void Open();
	void Close();

	void ReadSeqNum();
	void WriteSeqNum();

	void ResetSeqNum();

	int GetNextSendSeqNum();
	int GetAndIncreaseNextSendSeqNum();
	void SetNextSendSeqNum(int value);
	void SetNextSendSeqNum(string value);
	
	int GetNextExpectSeqNum();
	int GetLastRecvSeqNum();
	void SetLastRecvSeqNum(int value);
	void SetLastRecvSeqNum(string value);
	

	int GetNextOrderLocalID();
private:
	static GlobalParam m_Instance;

	string m_SeqNumFileName;
	FILE* m_SeqNumFile;

	int m_LastSendSeqNum;
	int m_LastRecvSeqNum;

	int m_OrderLocalID;
};

