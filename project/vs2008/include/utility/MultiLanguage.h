#ifndef __MULTI_LANGUAGE_H__
#define __MULTI_LANGUAGE_H__

#include "utilityDll.h"
#include "GlobalConfig.h"


class UTILITY_CLASS CMultiLang
{
public:
    bool    GetStringByID(const char* szID, char* szBuffer, int nSize);
    bool    Init(const char* pszCfgPath);

    static CMultiLang& GetMultiLang();

private:
    CMultiLang();
    ~CMultiLang();
private:
    char               m_szCfgPath[128];
    char               m_szSection[128];
};

#endif