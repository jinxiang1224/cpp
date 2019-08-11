#include "TimedRequestThread.h"
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

CTimedRequest::CTimedRequest():
m_uTimerID(0)
{

}

CTimedRequest::~CTimedRequest()
{
    //步骤三：销毁定时器
    KillTimer(NULL, m_uTimerID);

}


//定时器使用方式二
//步骤二:定时器处理程序
void CALLBACK Timerproc (
                         HWND hwnd,        // handle to window for timer messages 
                         UINT message,     // WM_TIMER message 
                         UINT idTimer,     // timer identifier 
                         DWORD dwTime     // current system time 
                         )
{
    
    WSAData wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =true;
    opt.reusesock = true;
    opt.multi_cast = false;

    DatagramSocket RequestData(6000, "239.1.10.1",opt);

    char szServerIP[128] = {};
    CIPUtil::GetLocalIP(szServerIP,sizeof(szServerIP));

    //通知终端 执行类型
    char szSendMsg[128] = {};
    szSendMsg[0] = 0x11;
    strcat_s(szSendMsg,sizeof(szSendMsg) - 1,szServerIP);


    int ret = RequestData.send(szSendMsg,strlen(szSendMsg));
    printf("send ret %d.. errcode %d\n",ret,RequestData.getErrorcode());
}




//每5秒开始执行
unsigned CTimedRequest::Process()
{
    BOOL bRet = FALSE;
    MSG msg = { 0 };
    //步骤一:创建定时器

    //如果hWnd为NULL，返回值为新建立的timer的ID
    m_uTimerID = SetTimer(NULL, 0, 5000, (TIMERPROC)Timerproc);

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit 
        }
        else
        {
            //将定时器消息传递给so消息队列,这样才能触发Timerproc执行
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

