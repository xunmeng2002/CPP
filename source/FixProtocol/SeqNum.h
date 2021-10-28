#pragma once
#include <string>
#include <fstream>

using namespace std;


class SeqNum
{
	SeqNum();
	~SeqNum();
	SeqNum(const SeqNum&) = delete;
	SeqNum& operator=(const SeqNum&) = delete;
public:
	static SeqNum& GetInstance()
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
private:
	static SeqNum m_Instance;

	string m_SeqNumFileName;
	FILE* m_SeqNumFile;

	int m_LastSendSeqNum;
	int m_LastRecvSeqNum;
};

