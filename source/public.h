
#ifndef TOOL_H
#define TOOL_H

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#include <Iphlpapi.h>
#include <process.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <dlfcn.h>
#include <assert.h>
#include <poll.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>
struct hostent *gethostbyname(const char *name);

#define  DWORD unsigned int
#define  LONG  long
#define  Sleep(x) usleep((x)*1000)
#endif

#include <iostream>
using namespace std;

extern "C" typedef void (*TDFUNC)(void*);

#define MAX_CONNECT_SENCONDS			(3)

#define SDK_OK							0

#pragma warning (disable:4996)
#pragma warning (disable:4100)


char *hs_strncpy(char *dest,const char *src, size_t size);

/////////////////////////////////////////////////CThread///////////////////////////////////////////////
#ifdef WIN32
class CThread
{
	HANDLE hThread;
	TDFUNC tdfunc;
	void*  lpvoid;
	bool   isrunning;
	static unsigned int _stdcall Win32TdFunc(void *lpvoid);
public:
	CThread() { isrunning = false; }
	void Start(TDFUNC lpfunc, int stacksize, void* lpvoid);
	void Join();
	bool IsRunning(){ return isrunning; }
};
#else
class CThread
{
private:
	pthread_t threadid;
	TDFUNC tdfunc;
	void *lpvoid;
	bool isrunning;
	static void* LinuxTdFunc(void* lpvoid);
public:
	CThread() { isrunning = false; }
	void Start(TDFUNC tdfunc, int stacksize, void* lpvoid);
	void Join();
	bool IsRunning() { return isrunning; }

};
#endif
typedef unsigned char byte;

#endif
#define _CRT_SECURE_NO_WARNINGS