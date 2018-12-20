/*************************************************
// File name: CSqlManager.h
// Author: Jimmy
// Version: 1.0
// Date: 2018/12/20
// Description:
//  数据库连接测试
//
//
*************************************************/


#pragma  once
#include <string>

//根据操作系统修改路径
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","rsEOF")

#define  OPEN_SQL_DB_TIMEOUT (10)

typedef struct
{
    std::wstring strHost;
    std::wstring strPort;
    std::wstring strUserName;
    std::wstring strPassword;
    std::wstring strDBName;
}STRU_CONN_SQL_INFO;

class CADOManager
{
public:

    static CADOManager& GetInstance();

    BOOL  InitADOConn(const STRU_CONN_SQL_INFO& stSqlInfo, unsigned int timeout);

    std::wstring GetErrorDesc();
    
private:
    CADOManager();
    ~CADOManager();

    //拷贝构造函数
    CADOManager(const CADOManager&){};

    //赋值运算符
    CADOManager& operator=(const CADOManager&) {};


private:

    std::wstring m_strErrDesc;

};