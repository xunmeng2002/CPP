#include "TcpIOCPServer.h"
#include "Logger.h"

using namespace std;

#define EXIT_CODE 0
#define MAX_ACCPET_NUM 10

TcpIOCPServer TcpIOCPServer::m_Instance;

TcpIOCPServer::TcpIOCPServer()
    :TcpIOCP("TcpIOCPServer")
{

}
TcpIOCPServer::~TcpIOCPServer()
{
}

TcpIOCPServer& TcpIOCPServer::GetInstance()
{
    return m_Instance;
}

bool TcpIOCPServer::Init()
{
    return TcpIOCP::Init() && Bind() && Listen();
}

void TcpIOCPServer::ThreadInit()
{
    ThreadBase::ThreadInit();
    for (auto i = 0; i < MAX_ACCPET_NUM; i++)
    {
        if (!PostAccept())
        {
            WRITE_LOG(LogLevel::Debug, "ThreadInit PostAccept Failed.");
            m_ShouldRun.store(false);
            break;
        }
    }
}
void TcpIOCPServer::ThreadExit()
{
    TcpIOCP::ThreadExit();
    closesocket(m_InitSocket);
    for (auto& it : m_ConnectDatas)
    {
        closesocket(it.second->SocketID);
    }
    m_ConnectDatas.clear();
}

bool TcpIOCPServer::Bind()
{
    if (bind(m_InitSocket, (sockaddr*)&m_LocalAddress, sizeof(m_LocalAddress)) == SOCKET_ERROR)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Bind Failed.");
        closesocket(m_InitSocket);
        return false;
    }
    return true;
}
bool TcpIOCPServer::Listen(int backLog)
{
    if (listen(m_InitSocket, backLog) == SOCKET_ERROR)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Listen Failed.");
        closesocket(m_InitSocket);
        return false;
    }
    return true;
}

