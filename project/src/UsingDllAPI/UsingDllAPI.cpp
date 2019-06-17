// TestDllAPI.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../DLLCoding/DllAPI.h"
#pragma comment(lib,"../../lib/DLLCoding.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    //case1 vs2008 若crt有一个是MT，跨模块释放和分配会崩溃
    //但在vs 2013不存在这个问题，有可能vs解决了该问题
    const int MAX_MALLOC_NUM = 5;
    unsigned int usSize = sizeof(int)* MAX_MALLOC_NUM;
    int* pnArray = NULL;

    bool bCrossModule = false;
    bool bUsingSTLCrossModule = true;

    if (!XDll_Malloc_Memory(usSize, (void**)&pnArray))
    {
        printf("malloc memory error...\n");
        return 0;
    }

    for (int i = 0; i < MAX_MALLOC_NUM; i++)
    {
        pnArray[i] = i + 1;
        printf("array[%d] = %d\n", i, pnArray[i]);
    }

    if (!bCrossModule)
    {
        if (!XDll_Free_Memory((void**)&pnArray))
        {
            printf("free memory error...\n");
        }
    }
    else
    {
        if (NULL != pnArray)
        {
            free(pnArray);
            pnArray = NULL;
        }
    }

    //case2  vs2008和2013均会崩溃 不管crt是MT/MD
    if (bUsingSTLCrossModule)
    {
        //设计内存重新分配
        std::string strInfo;
        XDll_Assign_String(strInfo);
    }
    return 0;
}

