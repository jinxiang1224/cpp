#include "utilityAPI.h"

class CReportMac : public TTThread
{
public:
    CReportMac();
    ~CReportMac();
    virtual unsigned Process();
    void CReportMac::ReportMac(const char* szConsoleIP);
};