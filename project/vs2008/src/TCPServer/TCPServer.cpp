// TCPServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include "ConnectThread.h"
#pragma  comment(lib, "ws2_32.lib")




int _tmain(int argc, _TCHAR* argv[])
{
    //加载套接字库
    WORD wVersionRequested;
    WSADATA wsaData = {0};
    wVersionRequested = MAKEWORD(1,1);

    if (WSAStartup(wVersionRequested, &wsaData) != 0 ) 
    {
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) 
    {
        WSACleanup( );
        return 1; 
    }

    //The WinSock DLL is acceptable.

    //创建用于监听的套接字，拥有地址族 但是没有名字：地址族+地址+端口号
    SOCKET socketSrv = socket(AF_INET, SOCK_STREAM,0);

    //创建socket信息
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//地址族

    addrSrv.sin_port = htons(6100);//端口号

    //监听本机所有的主机地址，即不关心数据从哪个网卡过来
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


    //将名字和套接字绑定在一起
    bind(socketSrv,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR_IN));

    //将套接字设为监听模式，准备接收客户请求
    listen(socketSrv,SOMAXCONN);

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    const int MAX_THREAD = 5;

    //模拟线程池，最大5个
    CConnectThread vecThread[MAX_THREAD];

    while (1)
    {
        //accpet会阻塞，直到client端调用connect
        SOCKET sockConn = accept(socketSrv,(SOCKADDR*)&addrClient,&len);
        int index = 0;
        vecThread[index].InitSocket(sockConn);
        vecThread[index].Create();
        index++;

        if (index >= MAX_THREAD)
        {
            break;
        }
    }

    //关闭监听套接字
    closesocket(socketSrv); 

    //清理套接字库的使用
    WSACleanup();

    system("pause");
    return 0;
}

