#include "stdafx.h"
#include "stdio.h"
#include "utilityAPI.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SECURITY_ATTRIBUTES sa;
    sa.bInheritHandle = TRUE; //设置句柄可以继承
    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(sa);

    HANDLE hIN_Read = NULL;
    HANDLE hIN_Write = NULL;

    HANDLE hOUT_Read = NULL;
    HANDLE hOUT_Write = NULL;

    //获取匿名管道读写句柄
    if (!CreatePipe(&hIN_Read, &hIN_Write, &sa,0))
    {
        printf("create pipe error...\n");
        return 1;
    }
    
    if (!CreatePipe(&hOUT_Read, &hOUT_Write, &sa,0))
    {
        printf("create pipe error...\n");
        return 1;
    }
    
    //屏蔽不需要继承的句柄
    SetHandleInformation(hIN_Write, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(hOUT_Read, HANDLE_FLAG_INHERIT, 0);

    char szSendMsg[128] = {0};
    char szReadMsg[128] = {0};
    DWORD dwWrite = 0;
    DWORD dwRead = 0;

    //设置启动信息，将管道A读句柄和管道B的写句柄传递给子进程
    STARTUPINFOA startInfo;
    memset(&startInfo,0,sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    startInfo.dwFlags = STARTF_USESTDHANDLES;
    startInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    startInfo.hStdInput = hIN_Read;
    startInfo.hStdOutput= hOUT_Write;

    //创建子进程以及设置继承属性
    CWorkProcess cmdChild("PipeClient.exe",NULL);
    cmdChild.SetStartupInfo(startInfo);
    cmdChild.SetInheritanceOpt(); /*设置继承属性*/
    cmdChild.LaunchProcess(); /*启动进程*/

    //双向通信用户交互和显示
    printf("pls input msg...:\n");
    while (1)
    {
        //从控制台获取用户输入
        memset(szSendMsg,0, sizeof(szSendMsg));
        gets_s(szSendMsg, sizeof(szSendMsg));

        //屏幕显示
        printf("server: write data to pipe : %s\n",szSendMsg);

        //向管道中写入数据，
        if (!WriteFile(hIN_Write,szSendMsg, strlen(szSendMsg),&dwWrite,NULL))
        {
            printf("server: write file error...");
        }

        if (strcmp(szSendMsg,"quit") == 0)
        {
            break;
        }

        memset(szReadMsg,0, sizeof(szReadMsg));

        //从管道中读取数据
        if (!ReadFile(hOUT_Read,szReadMsg,sizeof(szReadMsg),&dwRead,NULL))
        {
            printf("server: read file error...");
        }
        else
        {
            printf("server: read data from client (%s)\n",szReadMsg);
        }
    }

    cmdChild.WaitForEnded(INFINITE);

    //不在操作句柄，确保资源正确被释放
    CloseHandle(hIN_Read);
    CloseHandle(hIN_Write);
    CloseHandle(hOUT_Read);
    CloseHandle(hOUT_Write);

    return 0;
}

