// TestDllAPI.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../DLLCoding/DllAPI.h"
#pragma comment(lib,"../../lib/DLLCoding.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    const int MAX_MALLOC_NUM = 5;
    unsigned int usSize = sizeof(int)* MAX_MALLOC_NUM;
    int* pnArray = NULL;

    if (!XDll_Malloc_Memory(usSize, (void**)&pnArray))
    {
        printf("malloc memory error...\n");
        return 0;
    }

    for (int i = 0; i < MAX_MALLOC_NUM; i++)
    {
        pnArray[i] = i + 1;
    }

    for (int i = 0; i < MAX_MALLOC_NUM; i++)
    {
        printf("array[%d] = %d\n", i, pnArray[i]);
    }

    if (!XDll_Free_Memory((void**)&pnArray))
    {
        printf("free memory error...\n");
    }

    if (NULL != pnArray)
    {
        free(pnArray);
        pnArray = NULL;
    }



    return 0;
}

