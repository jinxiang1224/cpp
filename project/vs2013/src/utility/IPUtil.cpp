/***************************************************************
* Copyright(C) 2018,Company All Rights Reserved
*
* @file    : NetWorkUtil.cpp
*
* @brief   :
*
* @version : 1.0
*
* @author  : Jimmy
*
* @date    : 2018/12/22 星期六
*
* Details  :
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "IPUtil.h"
#include <tchar.h>
#pragma comment(lib, "IPHLPAPI.lib")   
#pragma comment(lib, "ws2_32.lib") 

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

const int MAX_TRY_TIME = 3;

CIPUtil::CIPUtil()
{

}

CIPUtil::~CIPUtil()
{

}

bool CIPUtil::InitEnvoriment()
{
    WSADATA wsaData;

    int error = WSAStartup(0x0101, &wsaData);
    if (error != 0)
    {
        return false;
    }

    return true;
}

bool CIPUtil::UninitEnvoriment()
{
    WSACleanup();
    return true;
}

HOSTENT* CIPUtil::GetHostByName(const char* pszHostname)
{
    HOSTENT* pHost = NULL;
    int nTryCount = 0;

    if (NULL == pszHostname || strlen(pszHostname) == 0)
    {
        return pHost;
    }

    //gethostbyname可能返回null，增加重试，直至解析成功
    do
    {
        pHost = gethostbyname(pszHostname);
        if (pHost == NULL && nTryCount < MAX_TRY_TIME)
        {
            Sleep(500);
            nTryCount++;
        }
        else
        {
            break;
        }

    } while (1);

    return pHost;
}

bool CIPUtil::GetLocalHostName(char* pszHostname, unsigned uSize)
{
    if (NULL == pszHostname)
    {
        return false;
    }

    int ret = gethostname(pszHostname, uSize);

    return  ret == SOCKET_ERROR ? false : true;
}

bool  CIPUtil::GetIP(HOSTENT* host, std::vector<std::string>& vecIPlist)
{
    in_addr addr;
    char szIP[50] = {};
    int i = 0;
    vecIPlist.clear();

    //4.转化为char*并拷贝返回
    while (host->h_addr_list[i] != NULL)
    {
        addr.s_addr = *(u_long*)host->h_addr_list[i];
        if ((int)strlen(inet_ntoa(addr)) > sizeof(szIP))
        {
            break;
        }

        strcpy_s(szIP, 50, inet_ntoa(addr));
        vecIPlist.push_back(std::string(szIP));
        i++;
    }

    return vecIPlist.empty() ? false : true;
}


/**************************************************************
*  @brief : CIPUtil::GetLocalIPList
*
*  @param :
*
*    -std::vector<std::string>& vecIP
*
*    -int a
*
*    -int c
*
*  @return : bool
*
*  @author : Jimmy
*
*  @date : 2018/12/30 星期日
*
*  @note :
***************************************************************/
bool CIPUtil::GetLocalIPList(std::vector<std::string>& vecIP)
{
    bool bRet = false;
    char hostname[256] = {};
    vecIP.clear();

    if (!InitEnvoriment())
    {
        return false;
    }

    do
    {
        if (!GetLocalHostName(hostname, sizeof(hostname)))
        {
            break;
        }

        //3.获取主机ip
        HOSTENT* host = GetHostByName(hostname);
        if (host == NULL)
        {
            break;
        }

        //解析IP
        if (!GetIP(host, vecIP))
        {
            break;
        }

        bRet = true;
    } while (0);


    UninitEnvoriment();

    return bRet;
}

//变量或者结构体成员注释
/* */

/**************************************************************
*  @brief : CIPUtil::GetLocalMACList
*
*  @param :
*
*    -std::vector<std::string>& vecMac
*
*  @return : bool
*
*  @author : Jimmy
*
*  @date : 2018/12/22 星期六
*
*  @note : 通过GetAdaptersAddresses函数（适用于Windows XP及以上版本）
***************************************************************/
bool CIPUtil::GetLocalMACList(std::vector<std::string>& vecMac)
{
    bool ret = false;
    vecMac.clear();
    ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
    PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
    if (pAddresses == NULL)
    {
        return false;
    }

    // Make an initial call to GetAdaptersAddresses to get the necessary size into the ulOutBufLen variable
    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
        if (pAddresses == NULL)
        {
            return false;
        }
    }

    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
    {
        // If successful, output some information from the data we received
        for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
        {
            // 确保MAC地址的长度为 00-00-00-00-00-00
            if (pCurrAddresses->PhysicalAddressLength != 6)
            {
                continue;
            }

            char acMAC[128] = { 0 };

            sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pCurrAddresses->PhysicalAddress[0]),
                int(pCurrAddresses->PhysicalAddress[1]),
                int(pCurrAddresses->PhysicalAddress[2]),
                int(pCurrAddresses->PhysicalAddress[3]),
                int(pCurrAddresses->PhysicalAddress[4]),
                int(pCurrAddresses->PhysicalAddress[5]));

            vecMac.push_back(std::string(acMAC));
            ret = true;
        }
    }

    free(pAddresses);
    return ret;
}

//********************************************
// 函数名:	
// 功  能:	检查是否合法的子网掩码
// 返回值:  
// 参  数: 	
// 备  注：
//********************************************
bool CIPUtil::isValidSubmask(const std::string& strSubmask)
{
    //验证是否合法IP
    if (!isValidIP(strSubmask))
    {
        return false;
    }

    //转换unsing long 整型 并且转化大端模式才符合算法要求
    unsigned long  ulSubmask = htonl(inet_addr(strSubmask.c_str()));

    //取反 & (取反+1)
    //合法：11111111 11111111 11111100 00000000 11..1连续
    //非法：111111111111111111111111111001111

    return ((~ulSubmask + 1) & ~ulSubmask) == 0;
}


bool CIPUtil::isValidIP(const std::string& strIP)
{
    std::string::size_type     nBeginIndex = 0;
    std::string::size_type     nTargetIndex = 0;
    std::string                strSubstr = strIP;
    std::string                strElement;
    std::vector<std::string>   vecIPElement;

    //192.168.245 
    do
    {
        nTargetIndex = strSubstr.find_first_of(_T('.'));
        if (nTargetIndex != std::string::npos)
        {
            strElement = strSubstr.substr(0, nTargetIndex);
            strSubstr = strSubstr.substr(++nTargetIndex);
        }
        else
        {
            strElement = strSubstr;
        }

        if (!IsValidElementIP(strElement))
        {
            return false;
        }

        //防止异常，导致死循环
        if (vecIPElement.size() > 4)
        {
            return false;
        }


        vecIPElement.push_back(strElement);

    } while (nTargetIndex != std::string::npos);


    if (vecIPElement.size() != 4)
    {
        return false;
    }

    return true;
}

bool CIPUtil::isValidPort(const std::string& strPort)
{
    if (strPort.empty())
    {
        return false;
    }

    size_t nLen = strPort.length();
    for (size_t i = 0; i < nLen; i++)
    {
        if (!(strPort[i] >= _T('0') && strPort[i] <= _T('9')))
        {
            return false;
        }
    }

    return true;
}


bool CIPUtil::IsValidElementIP(const std::string& strElement)
{
    if (strElement.empty())
    {
        return false;
    }

    size_t nsize = strElement.length();
    for (size_t i = 0; i < nsize; i++)
    {
        if (!(strElement[i] >= _T('0') && strElement[i] <= _T('9')))
        {
            return false;
        }
    }

    if (atoi(strElement.c_str()) > 255)
    {
        return false;
    }

    return true;
}

bool CIPUtil::GetLocalIP(std::string& strIP)
{
    char hostname[256] = {};

    bool bRet = false;


    if (!InitEnvoriment())
    {
        return false;
    }

    if (!GetLocalHostName(hostname, sizeof(hostname)))
    {
        return false;
    }

    //3.获取主机ip
    HOSTENT* host = GetHostByName(hostname);
    if (NULL == host)
    {
        return false;
    }
    std::vector<std::string> vecIPlist;
    if (!GetIP(host, vecIPlist))
    {
        return false;
    }

    strIP = vecIPlist[0];

    UninitEnvoriment();
    return true;
}


/**************************************************************
*  @brief : GetDnsServerIP
*
*  @param :
*
*    -std::string& strPreferredDNS 首选
*
*    -std::string& strOptionalDNS  备选
*
*  @return : BOOL
*
*  @author : jin
*
*  @date : 2019/3/25
*
*  @note : 获取首选DNS以及备选DNS信息
***************************************************************/
bool CIPUtil::GetDnsServerIP(std::string& strPreferredDNS, std::string& strOptionalDNS)
{
    FIXED_INFO *pFixedInfo = NULL;
    ULONG ulOutBufLen;
    DWORD dwRetVal;
    IP_ADDR_STRING *pIPAddr;

    pFixedInfo = (FIXED_INFO *)MALLOC(sizeof(FIXED_INFO));
    if (pFixedInfo == NULL)
    {
        printf("Error allocating memory needed to call GetNetworkParams\n");
        return false;
    }

    ulOutBufLen = sizeof(FIXED_INFO);

    // Make an initial call to GetAdaptersInfo to get
    // the necessary size into the ulOutBufLen variable
    if (GetNetworkParams(pFixedInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        FREE(pFixedInfo);
        pFixedInfo = (FIXED_INFO *)MALLOC(ulOutBufLen);
        if (pFixedInfo == NULL)
        {
            printf("Error allocating memory needed to call GetNetworkParams\n");
            return false;
        }
    }

    if (dwRetVal = GetNetworkParams(pFixedInfo, &ulOutBufLen) == NO_ERROR)
    {

        printf("Host Name: %s\n", pFixedInfo->HostName);
        printf("Domain Name: %s\n", pFixedInfo->DomainName);
        printf("DNS Servers:\n\t first ip %s\n", pFixedInfo->DnsServerList.IpAddress.String);

        strPreferredDNS = std::string(pFixedInfo->DnsServerList.IpAddress.String);

        pIPAddr = pFixedInfo->DnsServerList.Next;
        while (pIPAddr)
        {
            printf("\t second ip%s\n", pIPAddr->IpAddress.String);
            strOptionalDNS = std::string(pIPAddr->IpAddress.String);
            pIPAddr = pIPAddr->Next;
        }
    }
    else
    {
        printf("GetNetworkParams failed with error: %d\n", dwRetVal);
        return false;
    }

    if (pFixedInfo)
    {
        FREE(pFixedInfo);
    }

    return true;
}


std::string CIPUtil::GetSubString(const char* pszURL,
    const char* pszFistrPreffix,
    const char* pszLastSuffix)
{
    if (NULL == pszURL || strlen(pszURL) == 0)
    {
        return std::string("");
    }

    std::string strSrc(pszURL);
    std::string strTarget;

    std::string::size_type nBegin = 0;
    std::string::size_type nEnd = std::string::npos;
    const std::string::size_type nStingTail = std::string::npos;
    const std::string::size_type nStringSize = strSrc.size();

    //前缀为空，最后一后缀之后的字符串
    if (NULL == pszFistrPreffix)
    {
        if (NULL != pszLastSuffix)
        {
            nBegin = strSrc.rfind(pszLastSuffix);
            if (nBegin != std::string::npos)
            {
                strTarget = strSrc.substr(nBegin + strlen(pszLastSuffix), nStingTail);
            }
        }
    }

    //后缀为空，前缀之后的字符串
    if (NULL == pszLastSuffix)
    {
        if (NULL != pszFistrPreffix)
        {
            nEnd = strSrc.find(pszFistrPreffix);
            strTarget = strSrc.substr(0, nEnd);
        }
    }

    //取中间部分
    if (NULL != pszLastSuffix && NULL != pszFistrPreffix)
    {
        nBegin = strSrc.find(pszFistrPreffix);
        nEnd = strSrc.rfind(pszLastSuffix);
        int nPreffixOffset = strlen(pszFistrPreffix);
        int nSubCount = nEnd - nPreffixOffset - nBegin;
        if (nBegin != nStingTail && nEnd != nStingTail)
        {
            strTarget = strSrc.substr(nBegin + nPreffixOffset, nSubCount);
        }
    }
    
    return strTarget;
}