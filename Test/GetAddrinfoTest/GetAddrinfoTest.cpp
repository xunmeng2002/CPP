﻿#include <iostream>
#include <set>
#include <string.h>

#ifdef WINDOWS
#include <Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#endif // WINDOWS
#ifdef LINUX
#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>  
#endif // LINUX

#include <thread>

using namespace std;

void Init()
{
#ifdef WINDOWS
    cout << "ON WINDOWS" << endl;
    WSADATA initData;
    initData.wVersion = 0;
    initData.wHighVersion = 2;
    memset(initData.szDescription, 0, sizeof(initData.szDescription));
    memset(initData.szSystemStatus, 0, sizeof(initData.szSystemStatus));
    initData.iMaxSockets = 100;
    initData.lpVendorInfo = nullptr;
    if (WSAStartup(2, &initData) != 0)
    {
        std::cout << "SocketInit Failed!" << std::endl;
    }
#endif
#ifdef LINUX
    cout << "ON LINUX" << endl;
#endif
}

int ParseSockAddr(const struct sockaddr* addr, string& ip, int& port)
{
    void* numeric_addr = nullptr;
    if (AF_INET == addr->sa_family)
    {
        numeric_addr = &((struct sockaddr_in*)addr)->sin_addr;
        port = ntohs(((struct sockaddr_in*)addr)->sin_port);
    }
    else if (AF_INET6 == addr->sa_family)
    {
        numeric_addr = &((struct sockaddr_in6*)addr)->sin6_addr;
        port = ntohs(((struct sockaddr_in6*)addr)->sin6_port);
    }
    else
    {
        return -1;
    }
    char addr_buff[INET6_ADDRSTRLEN];
    if (inet_ntop(addr->sa_family, numeric_addr, addr_buff, sizeof(addr_buff)) == nullptr)
        return -1;
    ip = addr_buff;
    return 0;
}
void PrintAddr(const struct addrinfo* addr)
{
    printf("ai_flags:[%d], ai_family[%d], ai_socktype[%d], ai_protocol[%d], ai_addrlen[%d], ai_canonname[%s]\n",
        addr->ai_flags, addr->ai_family, addr->ai_socktype, addr->ai_protocol, addr->ai_addrlen, addr->ai_canonname);
    string ip;
    int port = 0;
    auto ret = ParseSockAddr(addr->ai_addr, ip, port);
    printf("ParseSockAddr: ret[%d], Address<%s|%d>\n", ret, ip.c_str(), port);
}
void Test()
{
    set<string> ips = { "::", "::0","::1", "fe80::20c:29ff:fed5:82f","fe80::20c:29ff:fed5:82f%ens33", "fe80::59d8:5d6d:25cc:42cf%14", "0.0.0.0", "127.0.0.1","192.168.137.129" };
    addrinfo hints, * res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_IP;

    auto port = "10000";
    cout << endl;
    for (auto& ip : ips)
    {
        auto ret = getaddrinfo(ip.c_str(), port, &hints, &res);
        printf("getaddrinfo: ret[%d], SrcAddress:<%s|%s>\n", ret, ip.c_str(), port);
        while (res != nullptr)
        {
            PrintAddr(res);
            res = res->ai_next;
        }
        cout << endl;
    }
    cout << endl;
}

void ParseProcessName(const char* fullProcessName, char* processName, int len)
{
#if WINDOWS
    const char* temp = strrchr(fullProcessName, '\\');
    temp = temp == nullptr ? fullProcessName : ++temp;
    temp = strtok((char*)temp, ".");
#endif
#if LINUX
    const char* temp = strrchr(fullProcessName, '/');
    temp = temp == nullptr ? fullProcessName : ++temp;
#endif
    strncpy(processName, temp, len);
}

void ThreadFunc()
{
#if WINDOWS
    auto id = GetCurrentThreadId();
    cout << "GetCurrentThreadId()" << id << endl;
#endif
#if LINUX
    cout <<"gettid()" << gettid() << endl;
#endif    
}


int main(int argc, const char* argv[])
{  
    auto m_Thread = thread(ThreadFunc);
    cout << "get_id()" << m_Thread.get_id() << endl;
    
    m_Thread.join();

	return 0;
}
