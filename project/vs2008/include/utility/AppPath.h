#ifndef __APP_PATH_H__
#define __APP_PATH_H__

#include "utilityDll.h"


class UTILITY_CLASS CAppPathUtil
{
public:
    CAppPathUtil();
    ~CAppPathUtil();

    static bool     GetAppDir(char* pszPath, unsigned nBufferLen);

    static bool     IsValidPath(const char* szPath);
};

#endif