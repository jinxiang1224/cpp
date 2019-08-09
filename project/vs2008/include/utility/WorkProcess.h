#pragma  once
#include "utilityDll.h"
#include <Windows.h>

class UTILITY_CLASS CWorkProcess
{
public:
    CWorkProcess(const char* szApp, char* arg);
    ~CWorkProcess();

    bool LaunchProcess(bool showWnd = false);

    bool CheckIfProcessIsActive();

    bool StopProcess();

    bool WaitForEnded(int nTimeout);

    void SetStartupInfo(const STARTUPINFOA& si);
    
    void SetInheritanceOpt(bool bInherit = true);

    DWORD GetExitCode();

private:

    PROCESS_INFORMATION m_pi;
    STARTUPINFOA        m_sa;
    char*               m_pszCmd;
    BOOL                m_bInherit;
};