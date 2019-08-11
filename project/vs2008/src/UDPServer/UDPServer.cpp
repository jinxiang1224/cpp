// UDPServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdlib.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    int iResult = 0;
    const int BufLen = 1024;
    char RecvBuf[BufLen];

    WSADATA wsaData;
    SOCKET RecvSocket;

    sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof (SenderAddr);

    //-----------------------------------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) 
    {
        printf("WSAStartup failed with error %d\n", iResult);
        return 1;
    }
    // Create a receiver socket to receive datagrams
    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (RecvSocket == INVALID_SOCKET) 
    {
        printf("socket failed with error %d\n", WSAGetLastError());
        return 1;
    }

    int so_broadcast = 1;
    //默认的套接字描述符sock是不支持广播，必须设置套接字描述符以支持广播
    setsockopt(RecvSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast,sizeof(so_broadcast));

    //-----------------------------------------------
    // Bind the socket to any address and the specified port.
    sockaddr_in RecvAddr;
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(6000);
    RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    iResult = bind(RecvSocket, (sockaddr *) & RecvAddr, sizeof (RecvAddr));
    if (iResult != 0) 
    {
        printf("bind failed with error %d\n", WSAGetLastError());
        return 1;
    }

//     //加入多播组
//     struct ip_mreq stMreq;
//     //IP multicast address of group
//     stMreq.imr_multiaddr.s_addr = inet_addr("239.1.100.1");
//     //Local IP address of interface
//     stMreq.imr_interface.s_addr=htonl(INADDR_ANY);
// 
//     setsockopt(RecvSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&stMreq,sizeof(stMreq)); 


    // Call the recvfrom function to receive datagrams
    // on the bound socket.
    char szMsgData[128] = {};

    while (1)
    {
        printf("waiting get msg ....\n");
        memset(RecvBuf,0, sizeof(RecvBuf));

        iResult = recvfrom(RecvSocket,RecvBuf, BufLen, 0, (sockaddr*)&SenderAddr, &SenderAddrSize);
        if (iResult == SOCKET_ERROR) 
        {
            printf("recvfrom failed with error %d\n", WSAGetLastError());
        }
        else
        {
            printf("client->server:%s\n",RecvBuf);

            int nSendSize = sendto(RecvSocket,"i received",strlen("i received"),0,(sockaddr*)&SenderAddr,SenderAddrSize);
            if (nSendSize <= 0)
            {
                printf("send data error...\n");
            }
        }

         if (strlen(RecvBuf) == 1 && 'q' == RecvBuf[0])
         {
             break;
         }

//         printf("pls input msg...:\n");
// 
//         gets_s(szMsgData, sizeof(szMsgData));
// 
//         if (strlen(szMsgData) == 1 && 'q' == szMsgData[0])
//         {
//             break;
//         }
// 
//          int nSendSize = sendto(RecvSocket,RecvBuf,strlen(RecvBuf),0,(sockaddr*)&SenderAddr,SenderAddrSize);
//          if (nSendSize > 0)
//          {
//              printf("server->client:%s\n",RecvBuf);
//          }
//          else
//          {
//              printf("send data error...\n");
//         }
    }


    // Close the socket when finished receiving datagrams

    printf("Finished receiving. Closing socket.\n");

    //结束后退出组播地址
    //setsockopt(RecvSocket,IPPROTO_IP,IP_DROP_MEMBERSHIP,(char *)&stMreq,sizeof(stMreq)); 

    if (closesocket(RecvSocket) == SOCKET_ERROR) 
    {
        printf("closesocket failed with error %d\n", WSAGetLastError());
        return 1;
    }

    // Clean up and exit.
    WSACleanup();
    return 0;
}

