#include "stdafx.h"
#include "public.h"

char *hs_strncpy(char *dest,const char *src, size_t size)
{
    if( dest == NULL)
        return 0;
    if( src == NULL)
    {
        dest[0] = '\0';
        return 0;
    }
	if (size == 0)
	{
		return 0;
	}
    char *ret = strncpy(dest, src, size - 1);
    dest[size-1] = '\0';
    return ret;
}

/////////////////////////////////////////////////CThread///////////////////////////////////////////////
#ifdef WIN32
unsigned int _stdcall CThread::Win32TdFunc(void *lpvoid)
{
	CThread *lpThread = (CThread*)lpvoid;
	lpThread->isrunning = true;
	lpThread->tdfunc(lpThread->lpvoid);
	lpThread->isrunning = false;
	return 0;
}

void CThread::Start(TDFUNC lpfunc, int stacksize, void* lpvoid)
{
	this->tdfunc = lpfunc;
	this->lpvoid = lpvoid;
	hThread = (HANDLE)_beginthreadex(NULL,stacksize,Win32TdFunc,(void*)this,0,NULL);
}

void CThread::Join()
{
	if( isrunning == true)
	{
		WaitForSingleObject(hThread, -1);
	}
	CloseHandle(hThread);
}

#else

void* CThread::LinuxTdFunc(void* lpvoid)
{
	CThread *lpThread = (CThread*)lpvoid;
	lpThread->isrunning = true;
	lpThread->tdfunc(lpThread->lpvoid);
	lpThread->isrunning = false;
	return NULL;
}

void CThread::Start(TDFUNC tdfunc,int stacksize, void* lpvoid)
{	
	this->tdfunc = tdfunc;
	this->lpvoid = lpvoid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if( stacksize < 1024 * 1024 )
		pthread_attr_setstacksize(&attr, 1024 * 1024);
	else 
		pthread_attr_setstacksize(&attr, stacksize);
	pthread_create(&threadid, &attr, LinuxTdFunc, (void *)this);
	pthread_attr_destroy(&attr);
}

void CThread::Join()
{
	void *res;
	pthread_join(threadid, &res);
	free(res);
}
#endif
