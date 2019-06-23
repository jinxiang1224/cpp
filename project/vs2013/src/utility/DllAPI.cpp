//// DllCoding.cpp : 定义 DLL 应用程序的导出函数。
////
//
//#include "stdafx.h"
//#include <stdlib.h>
//
//#define DLL_API extern "C" __declspec(dllexport)
//
//#include "utility.h"
//
//const int MAX_BUFFER_SIZE = 128;
//
//char        g_szServerName[MAX_BUFFER_SIZE];
//unsigned    g_usCount = 0;
//
//
//DLL_API bool  DLL_CALL XDll_Malloc_Memory(unsigned  usMemorySize,void **pOutMemory)
//{
//    if (0 == usMemorySize || NULL ==pOutMemory )
//    {
//        return false;
//    }
//
//    void* pMemory = (void*)malloc(usMemorySize);
//
//    *pOutMemory =pMemory;
//
//    return NULL == pMemory ? false : true;
//}
//
//DLL_API bool  DLL_CALL XDll_Free_Memory(void** pMemory)
//{
//    bool bRet = false;
//
//    if (NULL != pMemory)
//    {
//        free(*pMemory);
//        *pMemory = NULL;
//        bRet = true;
//    }
//
//    return bRet;
//}
//
//DLL_API void  DLL_CALL XDll_Assign_String(std::string& strString)
//{
//   for (int i = 0; i < 30;i++)
//   {
//       strString[i] = i;
//   }
//}
//
//DLL_API PSTRU_MSG_DATA DLL_CALL XDll_GetMessage()
//{
//    int nDataCount = 5;
//    //Msg Info
//    int nDataSize = sizeof(int)*sizeof(nDataCount);
//    //整个内存块大小
//    PSTRU_MSG_DATA pData = (PSTRU_MSG_DATA)malloc(sizeof(STRU_MSG_DATA) + nDataSize);
//    if (pData)
//    {
//        pData->nDataNum = nDataCount;
//
//        for (size_t i = 0; i < nDataCount; i++)
//        {
//            pData->arrData[i] = i + 1;
//        }
//    }
//
//    return  pData;
//}
//
//DLL_API void DLL_CALL XDll_ReleaseMessage(PSTRU_MSG_DATA *pData)
//{
//    if (NULL != pData)
//    {
//        free(*pData);
//        *pData = NULL;
//    }
//}
//
//DLL_API PSTRU_STUDENT_INFO  DLL_CALL XDll_GetStudentInstance()
//{
//    static STRU_STUDENT_INFO stStudentIns;
//    stStudentIns.nAge = 10;
//    stStudentIns.nScore = 95;
//    strcpy_s(stStudentIns.szSex, sizeof(stStudentIns.szSex), "man");
//
//    return &stStudentIns;
//}
//
//
//
