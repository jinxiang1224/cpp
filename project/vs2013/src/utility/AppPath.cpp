#include"AppPath.h"

CAppPathUtil::CAppPathUtil()
{
}

CAppPathUtil::~CAppPathUtil()
{

}

BOOL CAppPathUtil::IsValidPath(const char* pszPath)
{
    if (NULL == pszPath)
    {
        return FALSE;
    }
	
    return ::PathIsDirectoryA(pszPath);
}

BOOL CAppPathUtil::GetAppDir(char* pszPath, unsigned nBufferLen)
{
    char szPath[MAX_PATH] = {};
    std::string strPath;   

    if (GetModuleFileNameA(NULL, szPath, MAX_PATH))
    {
        strPath.assign(szPath);
        strPath = strPath.substr(0, strPath.find_last_of(("\\") + 1));
        strcpy_s(pszPath, nBufferLen, strPath.c_str());
    }

    return  TRUE;
}