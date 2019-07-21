#ifndef __MEMORY_HELPER_H__
#define __MEMORY_HELPER_H__

#include "utilityDll.h"

UTILITY_API bool AllocMemory(unsigned  usMemorySize, void **pOutMemory);

UTILITY_API bool FreeMemory(void** pMemory);
#endif