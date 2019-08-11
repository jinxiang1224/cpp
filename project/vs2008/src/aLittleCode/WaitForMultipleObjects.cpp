//#include <windows.h>
//#include <stdio.h>
//#include <process.h>    
//
//
//unsigned  __stdcall SetMyEvent(void *lpParam)
//{
//    if (NULL != lpParam)
//    {
//        HANDLE* hEvent = (HANDLE*)lpParam;
//        Sleep(2000);
//        ::SetEvent(*hEvent);
//    }
//
//    return 0;
//}
//
//unsigned  __stdcall SleepThread(void *pSleeptime)
//{
//    if (NULL != pSleeptime)
//    {
//        int Sleeptime  = (*(int*)pSleeptime) ;
//        Sleep(Sleeptime * 1000);
//    }
//
//    return 0;
//}
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//    const int EVENT_NUM = 2;
//
//    HANDLE hObject[EVENT_NUM] = {NULL,NULL};
//
//    //创建线程，2秒后hObject[0]事件对象变成有信号
//    hObject[0] = ::CreateEvent(NULL,FALSE,FALSE,NULL);
//    HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,SetMyEvent,(void*)&hObject[0],0,NULL);
//    CloseHandle(hThread); //后续不会对该线程进行操作，直接关掉句柄
//
//
//    //创建线程，并等待线程结束
//    int nSleepTime = 1;
//    hObject[1] = (HANDLE) _beginthreadex(NULL,0,SleepThread,(void*)&nSleepTime,0,NULL);
//
//
//    //等待事件对象有信号、线程返回
//    DWORD dwEvent = WaitForMultipleObjects(EVENT_NUM, hObject, FALSE/*TRUE*/, 1500);
//
//    switch(dwEvent)
//    {
//    case WAIT_OBJECT_0 + 0: /*hObject[0]有信号*/
//        {
//            printf("event arrived ...\n");
//            break;
//        }
//
//    case WAIT_OBJECT_0 + 1: /*hObject[1]线程返回*/
//        {
//            printf("thread return ...\n");
//            break;
//        }
//
//    case WAIT_TIMEOUT: /*规定时间内，定义的事件和线程均未返回或者有信号*/
//        {
//            printf("wait multi object timeout ...\n");
//            break;
//        }
//
//    default:
//        {
//            printf("wait for multi object error...\n");
//        }
//    }
//
//    for (int i = 0; i < EVENT_NUM; i++)
//    {
//        CloseHandle(hObject[i]);
//    }
//
//    return 0;
//}
