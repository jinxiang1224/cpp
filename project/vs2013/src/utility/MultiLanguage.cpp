#include "MultiLanguage.h"

CMultiLang::CMultiLang()
{
}

CMultiLang::~CMultiLang()
{
}

CMultiLang& CMultiLang::GetMultiLang()
{
    static CMultiLang instance;
    return  instance;
}

std::wstring CMultiLang::GetStringByID(LPCTSTR strID)
{
    if (NULL == strID)
    {
        return TEXT("");
    }

    //CString cfgPath = util::getParentAppPath() + UTIL_MULTILIGNUAL;
    std::wstring strCfgPath;
    TCHAR szValue[MAX_PATH];
    ::GetPrivateProfileString(_T("DEFAULT"), strID, _T(""), szValue, MAX_PATH
        , strCfgPath.c_str());

    return szValue;
}

