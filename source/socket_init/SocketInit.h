#ifndef __h_socket_init_h__
#define __h_socket_init_h__

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <fcntl.h>
#pragma comment(lib,"ws2_32.lib")
#endif

#ifdef UNIX
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
typedef int cid_t;
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h>
#ifdef LINUX
#include <semaphore.h>
#include <signal.h>
#else
#include <sys/semaphore.h>
#endif
#endif


class SocketInit
{
public:
	SocketInit();
	virtual ~SocketInit();
};

#endif