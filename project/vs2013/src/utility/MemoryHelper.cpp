#include"MemoryHelper.h"
#include<stdlib.h>

UTILITY_API bool AllocMemory(unsigned  usMemorySize, void **pOutMemory)
{

    if (0 == usMemorySize || NULL == pOutMemory)
    {
        return false;
    }

    void* pMemory = (void*)malloc(usMemorySize);

    *pOutMemory = pMemory;

    return NULL == pMemory ? false : true;
}


UTILITY_API bool FreeMemory(void** pMemory)
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