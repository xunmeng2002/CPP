#include <vector>
#include <string>
#include <atomic>
#pragma once

class WorkThreadBase;
class WorkThreadManage
{
private:
	WorkThreadManage();
	~WorkThreadManage();
	WorkThreadManage(const WorkThreadManage&) = delete;
	WorkThreadManage& operator=(const WorkThreadManage&) = delete;

public:
	static WorkThreadManage& GetInstance();
	void Init(std::vector<WorkThreadBase*> workThreads);
	void Start();
	void Stop();
	void Join();
	void CloseConnects();
	void SendTestMessage(const std::string& message);
	void PrintSessions();
	WorkThreadBase* DispatchWorkThread();

	void AddConnect();
	void RemoveConnect();
	int GetConnectNum();

private:
	static WorkThreadManage m_Instance;

	std::vector<WorkThreadBase*> m_WorkThreads;
	int m_MinSessionNum;

	std::atomic<int> m_ConnectNum;
};

