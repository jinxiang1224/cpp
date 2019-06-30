/******************************************************************************* 
*  @file      TTThread.cpp
*  @author    jimmy
*  @brief   windows线程处理的包装
******************************************************************************/

#include "stdafx.h"
#include "TTThread.h"


TTThread::TTThread()
:m_hThread(0)
{

}


TTThread::~TTThread()
{
    if (m_hThread)
    {
        ::CloseHandle(m_hThread);
    }

    m_hThread = 0;
}

/**************************************************************
*  @brief : TTThread::create
*     
*  @param : -none
*     
*  @return : BOOL
*     
*  @author : Jimmy
*     
*  @date : 2019/2/13 星期三
*     
*  @note : 创建线程函数
***************************************************************/
BOOL TTThread::Create()
{

    m_hThread = (HANDLE)_beginthreadex(0,0, _threadProc, this, 0, (unsigned*)&m_dwThreadID);
    if (0 == m_hThread)
    {
        m_dwThreadID = 0;
    }

    return m_hThread >(HANDLE)1;
}

void TTThread::Destory()
{
    if (m_hThread)
    {
        //TerminateThread以异步方式执行,函数返回不代表线程结束,
        //线程函数停止执行，位置随机，类对象不会被析构导致内存泄漏
        ::TerminateThread(m_hThread, 0);

        //等待线程结束
        ::WaitForSingleObject(m_hThread, 500);

        ::CloseHandle(m_hThread);
        m_hThread = 0;
        m_dwThreadID = 0;
    }
}

BOOL TTThread::Wait(DWORD dwWaitTime)
{
    if (m_hThread == 0)
        return TRUE;
    return (::WaitForSingleObject(m_hThread, dwWaitTime) != WAIT_TIMEOUT);
}

/**************************************************************
*  @brief : TTThread::Process
*     
*  @param : -none
*     
*  @return : unsigned
*     
*  @author : Jimmy
*     
*  @date : 2019/2/16 星期六
*     
*  @note :  子类继承，用于实现每个线程独特业务逻辑
***************************************************************/
unsigned TTThread::Process()
{
    return 0;
}

unsigned __stdcall TTThread::_threadProc(void *lpParam)
{
    TTThread* pThread = (TTThread*)lpParam;
    assert(pThread);
    if (pThread != 0)
    {
        pThread->Process();
    }
    return 0;
}


/******************************************************************************/