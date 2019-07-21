#include "MultiLanguage.h"
#include <windows.h>

CMultiLang::CMultiLang()
{
    memset(m_szCfgPath, 0, sizeof(m_szCfgPath));
    memset(m_szSection, 0, sizeof(m_szSection));
}

CMultiLang::~CMultiLang()
{

}

bool CMultiLang::Init(const char* pszCfgPath)
{
    memcpy(m_szCfgPath, pszCfgPath, sizeof(m_szCfgPath));

    DWORD nSize = ::GetPrivateProfileStringA("Configuration",
        "section",
        "",
        m_szSection,
        MAX_PATH,
        m_szCfgPath);
    
    return nSize ? true : false;
}


CMultiLang& CMultiLang::GetMultiLang()
{
    static CMultiLang instance;
    return  instance;
}


bool CMultiLang::GetStringByID(const char* szID,char* szBuffer, int nSize)
{
    if (NULL == szID)
    {
        return false;
    }
    
   ::GetPrivateProfileStringA(m_szSection, szID, "", 
       szBuffer,
       nSize,
       m_szCfgPath);

    return true;
}

