
#include "utilityAPI.h"

class CPacketReceiver : public TTThread
{
public:
    CPacketReceiver();
    ~CPacketReceiver();

private:
    virtual unsigned Process();


};