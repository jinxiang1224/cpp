#ifndef __UTILITY_DLL_H__
#define __UTILITY_DLL_H__
#ifndef UTILITY_DLL
    #define UTILITY_API     __declspec(dllimport)
    #define UTILITY_CLASS   __declspec(dllimport)
#else
    #define UTILITY_API     __declspec(dllexport)
    #define UTILITY_CLASS   __declspec(dllexport)
#endif

#endif
