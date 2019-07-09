// TestDllAPI.cpp : 定义控制台应用程序的入口点。

#include "utilityAPI.h"
#pragma comment(lib,"../../lib/utility.lib")
#include <iostream>
#include "stdafx.h"



int _tmain(int argc, _TCHAR* argv[])
{
    char szAppDir[128] = {};
    CAppPathUtil::GetAppDir(szAppDir, sizeof(szAppDir));

    std::string strCfgPath(szAppDir);
    strCfgPath.append(UTIL_MULTILIGNUAL);

    CMultiLang::GetMultiLang().Init(strCfgPath.c_str());

    char szUpateInfo[128] = {};

    CMultiLang::GetMultiLang().GetStringByID("STRID_GLOBAL_UPDATEREMIND", szUpateInfo, sizeof(szUpateInfo));

    std::cout << szUpateInfo << std::endl;

    char szMac[128] = {};
    CIPUtil::GetLocalMAC(szMac, sizeof(szMac));
    std::cout << szMac << std::endl;

    char szIP[128] = {};
    CIPUtil::GetLocalIP(szIP, sizeof(szIP));
    std::cout << szIP << std::endl;



    return 0;
}

