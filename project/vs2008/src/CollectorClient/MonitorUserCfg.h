#include "utilityAPI.h"

class CMonitorUserCfg : public TTThread
{
public:
    CMonitorUserCfg();
    ~CMonitorUserCfg();
    virtual unsigned Process();
    void SaveListenAddr(const char* szMsg);
};