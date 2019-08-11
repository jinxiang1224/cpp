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

    int nResult = 0;            // used to return function results

    //The WinSock DLL is acceptable.

    //创建用于监听的套接字
    SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM,0);
    if (INVALID_SOCKET == ListenSocket)
    {
        printf("create socket error (%d)\n",::WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //创建socket信息
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//地址族

    addrSrv.sin_port = htons(6100);//端口号

    //监听本机所有的主机地址，即不关心数据从哪个网卡过来
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    //将名字和套接字绑定在一起
    nResult = bind(ListenSocket,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR_IN));
    if (nResult == SOCKET_ERROR)
    {
        printf("bind socket error code = %d\n",::WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    

    //将套接字设为监听模式，准备接收客户请求
    nResult = listen(ListenSocket,SOMAXCONN);
    if (SOCKET_ERROR == nResult)
    {
        printf("listen socket error(%d)\n",::WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    fd_set allSocket;
    FD_ZERO(&allSocket);

    FD_SET(ListenSocket,&allSocket);

    printf("服务端启动监听...\n");

    while (TRUE)
    {
        fd_set read_set;
        FD_ZERO(&read_set);

        read_set = allSocket;

        nResult = select(0,&read_set,NULL,NULL,NULL);
        if (SOCKET_ERROR == nResult)
        {
            printf("select error(%d)...\n",::WSAGetLastError());
            break;
        }
        else
        {
            //printf("readable or writable socket number %d\n",nResult);
        }

        if (FD_ISSET(ListenSocket,&read_set))
        {
            SOCKADDR_IN ClientAddr;
            int nLen = sizeof(ClientAddr);
            SOCKET socketClient = accept(ListenSocket,(sockaddr*)&ClientAddr, &nLen);
            if (INVALID_SOCKET == socketClient)
            {
                printf("accept socket is invalid...\n");
                continue;
            }

            FD_SET(socketClient, &allSocket);

            char* pszClientIP = inet_ntoa(ClientAddr.sin_addr);
            if(NULL != pszClientIP)
            {
                printf("有新客户端[%s:%d]端请求连接\n",pszClientIP,ntohs(ClientAddr.sin_port));
                printf("目前客户端的数量为: %d\n",allSocket.fd_count - 1);
            }

            continue;
        }

        for (unsigned i = 0; i < allSocket.fd_count; i++)
        {
            SOCKET socket = allSocket.fd_array[i];

            SOCKADDR_IN addrClient;
            int nLen = sizeof(addrClient);
            getpeername(socket,(sockaddr*)&addrClient, &nLen);
            char* pszClientIp = inet_ntoa(addrClient.sin_addr);
            unsigned short usClientPort = ntohs(addrClient.sin_port);

            if (FD_ISSET(socket,&read_set))
            {
                char szMsg[128] = {};
                int nResult = recv(socket,szMsg,sizeof(szMsg),0);
                if (nResult > 0)
                {
                    printf("--------客户端[%s:%d]--------\n",pszClientIp,usClientPort);
                    printf("消息长度%d字节\n",nResult);
                    printf("消息内容: %s\n",szMsg);
                }
                else if (0 == nResult)
                {
                    //对方关闭连接
                    printf("客户端[%s:%d]主动关闭连接...\n",pszClientIp,usClientPort);
                    closesocket(socket);
                    FD_CLR(socket,&allSocket);
                    printf("目前客户端的数量为: %d\n",allSocket.fd_count - 1);
                    continue;
                }
                else
                {
                    DWORD err = WSAGetLastError();
                    // 客户端的socket没有被正常关闭,即没有调用closesocket
                    if (err == WSAECONNRESET)
                    {
                        printf("客户端[%s:%d]被强行关闭",pszClientIp,usClientPort);
                    }
                    else
                    {
                        printf("recv data error code(%d)...\n",::WSAGetLastError());
                    }

                    closesocket(socket);
                    FD_CLR(socket, &allSocket);

                    //监听socket不算客户端端
                    printf("目前客户端的数量为: %d\n",allSocket.fd_count - 1);

                    continue;

                }

            }//read end
        }


    }



    //关闭监听套接字
    closesocket(ListenSocket); 

    //清理套接字库的使用
    WSACleanup();
    system("pause");
    return 0;
}

