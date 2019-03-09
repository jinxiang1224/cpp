#pragma  once
#include "stdafx.h"
#include "Windows.h"

class CWorkProcess
{
public:
    CWorkProcess(char* szApp, char* arg);
    ~CWorkProcess();

    bool LaunchProcess();

    bool CheckIfProcessIsActive();

    bool StopProcess();

    bool Wait(int nTimeout);

private:

    PROCESS_INFORMATION m_pi;
    char*               m_pszCmd;
};