// learn_code.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <windows.h>
using namespace std;
#include "extern_c.h"
#include <exception>

     


class CStudent
{
    //友元声明
    friend void print_age(const CStudent& stu);
public:
    CStudent():
      m_nAge(10)
    {

    }

    ~CStudent()
    {

    }

    int GetAge() const
    {
        //error 修改了成员函数
        //m_nAge += 10;
        return m_nAge;
    }

private:
    int m_nAge;
};



void print_age(const CStudent& stu)
{
    printf("age is: %d\n", stu.m_nAge);
}


 //线程基类
 class CWorkBaseThread
 {
 public:
     CWorkBaseThread();

     virtual ~CWorkBaseThread();

     static DWORD WINAPI    ThreadFunWrapper(LPVOID lpThreadParameter);

     DWORD                  GetThreadID();  

     BOOL                   WaitThreadEnd(DWORD dwTimeout = INFINITE);

     BOOL                   BeginThread();

     BOOL                   EndThread();
     
     //纯虚函数， 子类必须实现该函数
     //实现不同的业务逻辑
     virtual BOOL           ThreadFun() = 0;

 private:
     DWORD      m_dwThreadID;
     HANDLE     m_hThread;
 };

 CWorkBaseThread::CWorkBaseThread():
 m_dwThreadID(0),
 m_hThread(NULL)
 {

 }

 CWorkBaseThread::~CWorkBaseThread()
 {
      if (m_hThread != NULL)
      {
          CloseHandle(m_hThread);
      }
 }


 DWORD CWorkBaseThread::GetThreadID()
 {
     return m_dwThreadID;
 }

 BOOL CWorkBaseThread::WaitThreadEnd(DWORD dwTimeout)
 {
     DWORD  dwRet = WaitForSingleObject(m_hThread, 10 *1000);
     switch (dwRet)
     {
     case WAIT_OBJECT_0:
         {
             return TRUE;
         }
     case WAIT_TIMEOUT:
         {
             break;
         }
     case WAIT_ABANDONED :
         {
             break;
         }

     case WAIT_FAILED  :
         {
             break;
         }

     default:
         {

         }
     }

      return FALSE;
 }

BOOL CWorkBaseThread::BeginThread()
{
    m_hThread = CreateThread( 
        NULL,                   // default security attributes
        0,                      // use default stack size  
        ThreadFunWrapper,       // thread function name
        (LPVOID)this,           // argument to thread function 
        0,                      // use default creation flags 
        &m_dwThreadID);         // returns the thread identifier 

    return m_hThread != NULL ? TRUE : FALSE;
}

DWORD CWorkBaseThread::ThreadFunWrapper(LPVOID lpThreadParameter)
{
     if (lpThreadParameter != NULL)
     {
         CWorkBaseThread* pInstance = static_cast<CWorkBaseThread*>(lpThreadParameter);

         pInstance->ThreadFun();
     }

    return 0;
}


class CCollectMacThread:public CWorkBaseThread
{
public:
    CCollectMacThread();

    ~CCollectMacThread();

    virtual BOOL ThreadFun()
    {
        std::cout << "run collect mac thread\n";
        return TRUE;
    }
};

CCollectMacThread::CCollectMacThread():CWorkBaseThread()
{

}
CCollectMacThread::~CCollectMacThread()
{

}




int _tmain(int argc, _TCHAR* argv[])
{

   //异常捕获
   try
   {
       char sz[5] = {"123"};
       //抛出异常
       throw runtime_error("runtime error");
       throw exception("1111");
   }
   //异常处理
   catch (exception e)
   {
      printf("%s", e.what()) ;
   }
   catch(...)
   {
      printf("error");
   }
 
    return 0;
}



// 
// int _tmain(int argc, _TCHAR* argv[])
// {
// 	//c++调用c语音函数
//     //fun();
// 
//     //友元函数
//     //CStudent stu;
//     //print_age(stu); 
//     CC C1;
//     int a = 0;
// 
// 
// 
// //     CCollectMacThread macThread;
// //     if (macThread.BeginThread() != FALSE)
// //     {
// //         macThread.WaitThreadEnd(1000);
// //     }
// 
// 
// 
// 
//    
//     return 0;
// }
// 
