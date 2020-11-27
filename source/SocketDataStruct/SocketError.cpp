#include "SocketError.h"
#include <Windows.h>
#include <map>
#include <string>

using namespace std;


std::map<int, string> g_SocketErrors = {
	{10093, "WSANOTINITIALISED：在使用此API之前应首先成功地调用WSAStartup()。"},
	{10050, "WSAENETDOWN：WINDOWS套接口实现检测到网络子系统失效。"},
	{10004, "WSAEINTR：通过一个WSACancelBlockingCall()来取消一个（阻塞的）调用。"},
	{10036, "WSAEINPROGRESS：一个阻塞的WINDOWS套接口调用正在运行中。"},
	{10014, "WSAEFAULT：buf参数不在用户地址空间中的有效位置。"},
	{10052, "WSAENETRESET：由于WINDOWS套接口实现放弃了连接，故该连接必需被复位。"},
	{10055, "WSAENOBUFS：WINDOWS套接口实现报告一个缓冲区死锁。"},
	{10057, "WSAENOTCONN：套接口未被连接。"},
	{10038, "WSAENOTSOCK：描述字不是一个套接口。"},
	{10045, "WSAEOPNOTSUPP：已设置了MSG_OOB，但套接口非SOCK_STREAM类型。"},
	{10058, "WSAESHUTDOWN：套接口已被关闭。一个套接口以1或2的how参数调用shutdown()关闭后，无法再用send()函数。"},
	{10035, "WSAEWOULDBLOCK："},
	{10040, "WSAEMSGSIZE：套接口为SOCK_DGRAM类型，且数据报大于WINDOWS套接口实现所支持的最大值。"},
	{10022, "WSAEINVAL：套接口未用bind()捆绑。"},
	{10053, "WSAECONNABORTED：由于超时或其他原因引起虚电路的中断。"},
	{10054, "WSAECONNRESET：虚电路被远端复位。 "}
};

