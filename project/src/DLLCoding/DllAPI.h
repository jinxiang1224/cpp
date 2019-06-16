#ifndef __DLL_API_H__
#define __DLL_API_H__

#define  DLL_CALL __stdcall
#include <string>
#ifdef DLL_API

#else

#define DLL_API extern "C" __declspec(dllimport)

#endif

DLL_API bool  DLL_CALL XDll_Malloc_Memory(unsigned  usMemorySize,void **pOutMemory);
DLL_API bool  DLL_CALL XDll_Free_Memory(void** p);
DLL_API void  DLL_CALL XDll_Assign_String(std::string& strString);


#endif
