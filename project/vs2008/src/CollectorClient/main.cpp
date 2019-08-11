// CollectorClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MonitorUserCfg.h"

//0x10 监听初始化信息
//0x11 监听mac上报消息

int _tmain(int argc, _TCHAR* argv[])
{
	//监听广播消息
    //监听mac地址请求


    while (1)
    {
        CMonitorUserCfg Monitor;
        Monitor.Create();
        Monitor.Wait(INFINITE);
    }
    return 0;
}

