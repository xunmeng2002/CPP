#include <vector>
#include <string>
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
	WorkThreadBase* DispatchWorkThread();

private:
	static WorkThreadManage m_Instance;

	std::vector<WorkThreadBase*> m_WorkThreads;
	int m_MinSessionNum;
};

