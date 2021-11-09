#include "TcpIOCPClient.h"

using namespace std;

TcpIOCPClient TcpIOCPClient::m_Instance;

TcpIOCPClient::TcpIOCPClient()
    :TcpIOCP("TcpIOCPClient")
{

}
TcpIOCPClient::~TcpIOCPClient()
{

}

TcpIOCPClient& TcpIOCPClient::GetInstance()
{
    return m_Instance;
}
void TcpIOCPClient::Connect(const char* ip, int port)
{
    TcpEvent* tcpEvent = TcpEvent::Allocate();
    tcpEvent->EventID = EventConnect;
    tcpEvent->IP = string(ip);
    tcpEvent->Port = port;
    OnEvent(tcpEvent);
}

