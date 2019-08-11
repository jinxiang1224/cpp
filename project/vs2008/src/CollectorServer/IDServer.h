#ifndef __ID_SERVER_H__
#define __ID_SERVER_H__

#include <set>

typedef std::set<int> INTSET;

class CIDServer
{
public:
    int GetID();
    static CIDServer& GetInstance();

private:
    CIDServer();
    ~CIDServer();

    bool CheckUniqueID(int nID);
    int  GenerateID();

private:
    INTSET m_setID ;
};

#endif
