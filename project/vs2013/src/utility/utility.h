//#ifndef __DLL_API_H__
//#define __DLL_API_H__
//
//#define  DLL_CALL __stdcall
//#include <string>
//#ifdef DLL_API
//
//#else
//
//#define DLL_API extern "C" __declspec(dllimport)
//
//#endif
//
//typedef struct
//{
//    int nDataNum; //数组大小
//    int arrData[0];//柔性数组具体内容，int代表数组类型，可以是任意类型
//}STRU_MSG_DATA,* PSTRU_MSG_DATA;
//
//
//DLL_API bool  
//DLL_CALL MallocMemory(unsigned usMemorySize,void **pOutMemory);
//
//DLL_API bool  
//DLL_CALL FreeMemory(void** p);
//
//DLL_API PSTRU_MSG_DATA  
//DLL_CALL GetMessage();
//
//DLL_API void 
//DLL_CALL ReleaseMessage(PSTRU_MSG_DATA *pData);
//
//
//#endif
