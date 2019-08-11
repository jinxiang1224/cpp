
#include "utilityAPI.h"

class CTimedRequest : public TTThread
{
public:
    CTimedRequest();
    ~CTimedRequest();

private:
    virtual unsigned Process();

private:
    UINT m_uTimerID;
};