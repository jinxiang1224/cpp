#pragma  once

#include "Windows.h"
#include <tchar.h>

class CWorkProcess
{
public:
    CWorkProcess(char* szApp, char* arg);
    ~CWorkProcess();

    bool LaunchProcess(bool bShowWind = false);

    bool CheckIfProcessIsActive();

    bool StopProcess();

    bool WaitForEnded(int nTimeout);

private:

    PROCESS_INFORMATION m_pi;
    char*               m_pszCmd;
};