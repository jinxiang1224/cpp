#pragma  once
#include "utilityAPI.h"
#include <WinSock2.h>

class CConnectThread : public TTThread
{
public:
    CConnectThread();
    ~CConnectThread();
    void             InitSocket(SOCKET fd);
    virtual unsigned Process();

private:
    SOCKET m_socket;
};