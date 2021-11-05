#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#pragma once

#define MESSAGE_SIZE 64 * 1024



enum class OperateType : int
{
    Invalid = 0,
    Accept = 1,
    Send = 2,
    Recv = 3,
    Connect = 4,
    Disconnect = 5,
};
enum class EventType : int
{
    Invalid = 0,
    NewConnect = 1,
    DisConnect = 2,
    Recv = 3,
};

struct SocketData : public OVERLAPPED
{
    SocketData()
    {
        Clear();
    }
    void Clear()
    {
        Event = EventType::Invalid;
        SessionID = 0;
        ConnectSocket = INVALID_SOCKET;
        Operate = OperateType::Invalid;
        Internal = InternalHigh = 0;
        Offset = OffsetHigh = 0;
        hEvent = NULL;
        WsaBuffer.len = 0;
        WsaBuffer.buf = Buffer;
        memset(Buffer, 0, sizeof(Buffer));
    }
    void FormatBuffer()
    {
        for (auto i = 0u; i < WsaBuffer.len; i++)
        {
            if (WsaBuffer.buf[i] == '\0')
            {
                WsaBuffer.buf[i] = ' ';
            }
        }
        WsaBuffer.buf[MESSAGE_SIZE - 1] = '\0';
    }
    EventType Event;
    int SessionID;
    SOCKET ConnectSocket;
    OperateType Operate;
    WSABUF WsaBuffer;
    char Buffer[MESSAGE_SIZE];
};

class WorkThreadBase;
struct ConnectInfo
{
    ConnectInfo()
        :ConnectSocket(INVALID_SOCKET), WorkThread(nullptr)
    {

    }
    ConnectInfo(SOCKET socket, WorkThreadBase* workThread)
        :ConnectSocket(socket), WorkThread(workThread)
    {

    }
    void SetConnectInfo(SOCKET socket, WorkThreadBase* workThread)
    {
        ConnectSocket = socket;
        WorkThread = workThread;
    }
    SOCKET ConnectSocket;
    WorkThreadBase* WorkThread;
};
