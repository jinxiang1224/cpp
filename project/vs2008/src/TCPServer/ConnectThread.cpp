#include "ConnectThread.h"
#include <stdio.h>


CConnectThread::CConnectThread():m_socket(SOCKET_ERROR)
{

}

CConnectThread::~CConnectThread()
{
    if (SOCKET_ERROR != m_socket)
    {
      //关闭套接字
      closesocket(m_socket); 
    }
}



unsigned CConnectThread::Process()
{
    char recvBuf[100] = {0};
    char sendBuf[100] = {0};


    while (1)
    {
        //接收数据
        memset(recvBuf,0,sizeof(recvBuf));

        recv(m_socket,recvBuf,sizeof(char)*100,0/*一般设置为0*/);

        //打印接收数据
        printf("recv data:%s\n",recvBuf);

        if ('q' == recvBuf[0] && 1 == strlen(recvBuf))
        {
            printf("quit one chat thread:%d\n",GetThreadID());
            send(m_socket,"q", strlen("q"),0);
            break;
        }

        sprintf_s(sendBuf, sizeof(sendBuf),"%s","recv data ok.");

        //发送数据
        send(m_socket,sendBuf, strlen(sendBuf),0);
    }

   return 0;
}


void CConnectThread::InitSocket(SOCKET fd)
{
    m_socket = fd;
}