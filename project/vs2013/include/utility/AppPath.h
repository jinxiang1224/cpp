#ifndef __APP_PATH_H__
#define __APP_PATH_H__

#include "utilityDll.h"
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

class UTILITY_CLASS CAppPathUtil
{
public:
    CAppPathUtil();
    ~CAppPathUtil();

    static BOOL     GetAppDir(char* pszPath, unsigned nBufferLen);

    static BOOL     IsValidPath(const char* szPath);
private:

};

#endif