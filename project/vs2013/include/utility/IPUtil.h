#ifndef __IP_UTIL_H__
#define __IP_UTIL_H__

#include "utilityDll.h"
#include <string>
#include <vector>
#include <winsock2.h>
#include <iphlpapi.h>

#define MAX_BUFFER_SIZE 128

typedef struct
{
    char szIP[MAX_BUFFER_SIZE];
}STRU_IP_ADDR, *PSTRU_IP_ADDR;

typedef struct
{
    int nNum;
    STRU_IP_ADDR stIPList[]; //ÈáÐÔÊý×é
}STRU_IP_VECTOR, *PSTRU_IP_VECTOR;

typedef struct
{
    char szMacInfo[MAX_BUFFER_SIZE];
}STRU_MAC_INFO, *PSTRU_MAC_INFO;

typedef struct
{
    int nNum;
    STRU_MAC_INFO stMacList[];
}STRU_MAC_VECTOR, *PSTRU_MAC_VECTOR;



class UTILITY_CLASS CIPUtil
{
public:
    static bool GetLocalIPList(PSTRU_IP_VECTOR& pIPList);

    static bool GetLocalMAC(char* pszMac,unsigned uBufferLen);

    static bool GetDnsServerIP(char* pszPreferredDNS, char* pszOptionalDNS);

    static bool GetLocalIP(char* pszIP, unsigned uSize);

    static bool isValidSubmask(const char* pszSubmask);

    static bool isValidIP(const char* pszIP);

    static bool isValidGateway(const char* pszGateway);

    static bool isValidPort(const char* pszPort);

    static bool GetSubString(const char* pszURL,
        const char* pszPreffix,
        const char* pszSuffix,
        char* pszOutString);

private:
    static bool IsValidElementIP(const char* pszElement);
    static bool InitEnvoriment();
    static bool UninitEnvoriment();
    static bool GetLocalHostName(char* pszHostname, unsigned uSize);
    static bool GetIP(HOSTENT* host, PSTRU_IP_VECTOR & pIPList);
    static HOSTENT* GetHostByName(const char* pszHostname);

    CIPUtil();
    ~CIPUtil();
};


#endif