#include"AppPath.h"

CAppUtil::CAppUtil()
{
}

CAppUtil::~CAppUtil()
{

}

BOOL CAppUtil::IsValidPath(const std::wstring & wstrPath)
{
    return ::PathIsDirectory(wstrPath.c_str());
}

std::wstring CAppUtil::GetPath()
{
    TCHAR szPath[MAX_PATH];
    std::wstring wstrPath;

    ZeroMemory(szPath, sizeof(szPath));
    if (GetModuleFileName(NULL, szPath, MAX_PATH))
    {
        wstrPath.assign(szPath);
        wstrPath = wstrPath.substr(0, wstrPath.find_last_of(_T("\\")));
        wstrPath += _T("\\");
    }

    return  wstrPath;
}