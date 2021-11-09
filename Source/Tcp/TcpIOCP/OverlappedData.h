#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#pragma once

#define MESSAGE_SIZE 64 * 1024


struct OverlappedData : public OVERLAPPED
{
    OverlappedData()
    {
        Clear();
    }
    void Clear()
    {
        EventID = -1;
        SessionID = 0;
        ConnectSocket = INVALID_SOCKET;
        Internal = InternalHigh = 0;
        Offset = OffsetHigh = 0;
        hEvent = NULL;
        WsaBuffer.len = 0;
        WsaBuffer.buf = Buffer;
        memset(Buffer, 0, sizeof(Buffer));
        RemoteAddress = { 0 };
    }
    static OverlappedData* Allocate();
    void Free();

    int EventID;
    int SessionID;
    SOCKET ConnectSocket;
    WSABUF WsaBuffer;
    char Buffer[MESSAGE_SIZE];
    SOCKADDR_IN RemoteAddress;
};
