
#pragma once
#include <string>
#include <vector>

class CNetWorkUtil
{
public:
    CNetWorkUtil();
    ~CNetWorkUtil();

    static bool GetLocalIPList(std::vector<std::string>& vecIP);

    static bool GetLocalMACList(std::vector<std::string>& vecMac);

    static bool isValidSubmask(const std::string& strSubmask);

    static bool isValidIP(const std::string& strIP);

    static bool isValidGateway(const std::string& pszIP);

    static bool isValidPort(const std::string& strPort);
    static bool GetDnsServerIP(std::string& strPreferredDNS, std::string& strOptionalDNS);
    static bool GetLocalIP(std::string& strIP);

private:
    static bool IsValidElementIP(const std::string& strElement);

};