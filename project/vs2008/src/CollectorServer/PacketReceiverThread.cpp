#include "PacketReceiverThread.h"
#include <stdio.h>


CPacketReceiver::CPacketReceiver()
{

}

CPacketReceiver::~CPacketReceiver()
{


}

unsigned CPacketReceiver::Process()
{
    char szReceiveMsg[128] = {};
    int  nBufferSize = sizeof(szReceiveMsg);
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =false;
    opt.reusesock = true;
    opt.multi_cast = false;

    DatagramSocket m_DatagramSocket(6002,"255.255.255.255",opt);

    while (1)
    {
        memset(szReceiveMsg,0, nBufferSize);
        m_DatagramSocket.receive(szReceiveMsg, nBufferSize);
        printf("receive data '(%s)' from client...\n",szReceiveMsg);
        printf("save mac data to file or db...\n");
    }
}