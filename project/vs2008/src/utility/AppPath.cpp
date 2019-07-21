
#include <string>
#include <shlwapi.h>
#include"AppPath.h"
#pragma comment(lib,"shlwapi.lib")

#define MAX_PATH_LEN 128

CAppPathUtil::CAppPathUtil()
{
}

CAppPathUtil::~CAppPathUtil()
{

}

bool CAppPathUtil::IsValidPath(const char* pszPath)
{
    if (NULL == pszPath)
    {
        return false;
    }

    return ::PathIsDirectoryA(pszPath) ? true : false;
}

bool CAppPathUtil::GetAppDir(char* pszPath, unsigned nBufferLen)
{
     char szPath[MAX_PATH_LEN] = {};
     std::string strPath;   
 
     if (GetModuleFileNameA(NULL, szPath, MAX_PATH_LEN))
     {
         strPath.assign(szPath);
         std::string::size_type nFindPos = strPath.find_last_of("\\");
         strPath = strPath.substr(0, nFindPos + 1);
         strcpy_s(pszPath, nBufferLen, strPath.c_str());
     }

    return  true;
}