#include "IDServer.h"
#include <stdlib.h> 
#include <time.h> 

CIDServer::CIDServer()
{

}

CIDServer::~CIDServer()
{

}

int CIDServer::GetID()
{
    int nNewID = 0;

    do 
    {
        nNewID = GenerateID();

    } while (!CheckUniqueID(nNewID));

    m_setID.insert(nNewID);

    return nNewID;
}

CIDServer& CIDServer::GetInstance()
{
    static CIDServer instance;

    return instance;
}


bool CIDServer::CheckUniqueID(int nID)
{
    INTSET::iterator it = m_setID.find(nID);

    return it != m_setID.end() ? false : true;
}

//[a ,b](rand() % (b-a+1))+ a
int CIDServer::GenerateID()
{
    const int MIN_ID = 1;
    const int MAX_ID = 255; 

    srand((unsigned)time(NULL)); 

    int nRandID = ( rand() % (MAX_ID - MIN_ID + 1)) + MIN_ID;
    return nRandID;
}

