#ifndef DATAGRAMSOCKET_H_INCLUDED
#define DATAGRAMSOCKET_H_INCLUDED
#include "utilityDll.h"


#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#endif


//Simple socket class for datagrams.  Platform independent between
//unix and Windows.
class UTILITY_CLASS DatagramSocket
{
private:
#ifdef WIN32
    WSAData wsaData;
    SOCKET sock;
#else                       
    int sock;
#endif
    long retval;
    sockaddr_in outaddr;
    char ip[30];
    char received[128];


public:
    DatagramSocket(int port, const char* address, bool Datagram, bool reusesock);
    ~DatagramSocket();

    long receive(char* msg, int msgsize);
    char* received_from();
    long send(const char* msg, int msgsize);
    long sendTo(const char* msg, int msgsize, const char* name);
    int getAddress(const char * name, char * addr);
    const char* getAddress(const char * name);
    int getErrorcode();

};



#endif // DATAGRAMSOCKET_H_INCLUDED
