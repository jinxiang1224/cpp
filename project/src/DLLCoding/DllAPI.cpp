// DllCoding.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdlib.h>

#define DLL_API extern "C" __declspec(dllexport)

#include "DllAPI.h"


DLL_API bool  DLL_CALL XDll_Malloc_Memory(unsigned  usMemorySize,void **pOutMemory)
{
    if (0 == usMemorySize || NULL ==pOutMemory )
    {
        return false;
    }

    void* pMemory = (void*)malloc(usMemorySize);

    *pOutMemory =pMemory;

    return NULL == pMemory ? false : true;
}

DLL_API bool  DLL_CALL XDll_Free_Memory(void** pMemory)
{
    bool bRet = false;

    if (NULL != pMemory)
    {
        free(*pMemory);
        *pMemory = NULL;
        bRet = true;
    }

    return bRet;
}

DLL_API void  DLL_CALL XDll_Assign_String(std::string& strString)
{
   for (int i = 0; i < 30;i++)
   {
       strString[i] = i;
   }
}


