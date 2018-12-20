
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

private:
    static bool IsValidElementIP(const std::string& strElement);

};