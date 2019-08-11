// TCPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#pragma  comment(lib, "ws2_32.lib")
#include <string>

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

    //创建用于监听的套接字
    SOCKET socketClient = socket(AF_INET, SOCK_STREAM,0);
    if (INVALID_SOCKET == socketClient)
    {
        printf("create socket error(%d)",::WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //创建socket信息
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//地址族

    addrSrv.sin_port = htons(6100);//端口号

    //请求连接的服务器地址,特殊地址使用 inet_addr("192.168.xxx.xxx"),本地地址使用  htonl(INADDR_LOOPBACK)
    addrSrv.sin_addr.S_un.S_addr =  inet_addr("192.168.0.107");

    int nLength = sizeof(SOCKADDR_IN);

    if (SOCKET_ERROR == connect(socketClient,(SOCKADDR*)&addrSrv,nLength))
    {
        printf("connect server error(%d)",::WSAGetLastError());
        closesocket(socketClient);
        WSACleanup();
        return 1;
    }

    //发送数据
    char szSendMsg[100] = {};
    //接收数据
    char szRecvBuf[100] = {0};
    while (1)
    {
        //发送数据
        printf("pls input msg...:\n");

        memset(szSendMsg,0, sizeof(szSendMsg));

        gets_s(szSendMsg, sizeof(szSendMsg));

        if (strlen(szSendMsg) == 1 && szSendMsg[0]=='q')
        {
            printf("quit chat...\n");
            break;
        }

        int nSendSize = send(socketClient,szSendMsg,strlen(szSendMsg),0);
        if (nSendSize > 0)
        {
            printf("client->server:%s\n",szSendMsg);
        }
        else
        {
            printf("send data error...\n");
        }

    }

    //关闭监听套接字
    closesocket(socketClient); 

    //清理套接字库的使用
    WSACleanup();
          
    system("pause");
    return 0;
}

