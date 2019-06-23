#include "MultiLanguage.h"

CMultiLang::CMultiLang()
{
    memset(m_szCfgPath, 0, sizeof(m_szCfgPath));
    memset(m_szSection, 0, sizeof(m_szSection));
}

CMultiLang::~CMultiLang()
{

}

void CMultiLang::Init(const std::wstring & wstrCfgPath)
{
    swprintf_s(m_szCfgPath, sizeof(m_szCfgPath), _T("%s"), wstrCfgPath.c_str());

    std::wstring strSection = GetSectionName();

    swprintf_s(m_szSection, sizeof(m_szSection), _T("%s"), strSection.c_str());

}


CMultiLang& CMultiLang::GetMultiLang()
{
    static CMultiLang instance;
    return  instance;
}

std::wstring CMultiLang::GetSectionName()
{
    TCHAR szValue[MAX_PATH];
    ::GetPrivateProfileString(_T("Configuration"), _T("section"), _T(""), szValue, MAX_PATH
        , m_szCfgPath);

    return szValue;
}

std::wstring CMultiLang::GetStringByID(LPCTSTR strID)
{
    if (NULL == strID)
    {
        return TEXT("");
    }
    
    TCHAR szValue[MAX_PATH];
    ::GetPrivateProfileString(m_szSection, strID, _T(""), szValue, MAX_PATH
        , m_szCfgPath);

    return szValue;
}

