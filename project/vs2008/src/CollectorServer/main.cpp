// CollectorServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "IDServer.h"
#include "TimedRequestThread.h"
#include "PacketReceiverThread.h"



int _tmain(int argc, _TCHAR* argv[])
{
    
    int nUniqueID = CIDServer::GetInstance().GetID();

    //char szBroadcastAddr[128] = {};
    //sprintf_s(szBroadcastAddr,sizeof(128),"239.1.%d.1",nUniqueID);

    CTimedRequest myTimeThread;
    myTimeThread.Create();

    CPacketReceiver myPackeReciver;
    myPackeReciver.Create();

    HANDLE arrHandle[2] = 
    {
      myTimeThread.GetHandle(),
      myPackeReciver.GetHandle()
    };

    WaitForMultipleObjects(2,arrHandle,FALSE,INFINITE);

	return 0;
}

