

class CCollector
{
public:
    CCollector();
    ~CCollector();

private:
    bool SendBroadcastAdrr(int nID);
    bool CreateReceiverPacketThread();
    bool CreateTimedRequestThread();
};