#pragma once
#include <Windows.h>


class IOCompletePort
{
private:
	IOCompletePort();
	~IOCompletePort();
	IOCompletePort(const IOCompletePort&) = delete;
	IOCompletePort& operator=(const IOCompletePort&) = delete;

public:
	static IOCompletePort& GetInstance();

	bool Create(int maxConcurrency = 0);
	bool Close();
	bool AssociateDevice(HANDLE device, ULONG_PTR completeKey);
	bool PostStatus(DWORD dwNumBytes, ULONG_PTR completeKey, OVERLAPPED* po = NULL);
	bool GetStatus(PDWORD pdwNumBytes, ULONG_PTR* pCompKey, OVERLAPPED** ppo, DWORD dwMilliseconds = INFINITE);


private:
	static IOCompletePort m_Instance;
	HANDLE m_Handle;
};
