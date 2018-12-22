
#include "stdafx.h"
#include "CSqlManager.h"
#include <iostream>
#include <tchar.h>

CADOManager::CADOManager()
{

}

CADOManager::~CADOManager()
{

}


CADOManager& CADOManager::GetInstance()
{
    static CADOManager s_ADOManager;

    return s_ADOManager;
}


//********************************************
// 函数名:	InitADOConn
// 功  能:	用户编辑
// 返回值:  测试连接数据库是否成功
// 参  数: 	
// 备  注：每次连接数据库都需要以下步骤
// 日  期:  2018/12/20
//********************************************
BOOL CADOManager::InitADOConn(const STRU_CONN_SQL_INFO& stSqlInfo, unsigned int timeout)
{
    BOOL bRet = FALSE;

    m_strErrDesc.clear();

    try
   {
       //步骤一      
       CoInitialize(NULL); //初始化必不可少 
      
       std::wstring strConn;
       strConn = _T("Provider=SQLOLEDB;");

       strConn += _T("Password=");
       strConn += stSqlInfo.strPassword;

       strConn += _T(";User ID=");
       strConn += stSqlInfo.strUserName;

       strConn += _T(";Data Source=");
       strConn += stSqlInfo.strHost;
       strConn += _T(",");
       strConn += stSqlInfo.strPort;
       strConn += _T(";");

       strConn += _T("Initial Catalog=");
       strConn += stSqlInfo.strDBName;
       strConn += _T(";");

        //步骤二
       _ConnectionPtr pCon;  //ADO连接对象
       HRESULT hr = pCon.CreateInstance(__uuidof(Connection));
       if(FAILED(hr))
       {
           //std::cout<<"create _ConnectionPtr object failed ！！！"<< std::endl;
           m_strErrDesc = _T("create ptr object failed...");
           return FALSE;
       }
        
       //步骤三
       if (pCon != NULL)
       {
           pCon->ConnectionString = (_bstr_t)strConn.c_str();
           pCon->ConnectionTimeout = timeout;
           HRESULT hr =  pCon->Open("","","",NULL);

           if(!FAILED(hr))
           {
               bRet = TRUE;
               //若未能连接成功，关闭连接数据库存在异常 
               pCon->Close();
           }
       }

   }
   catch(_com_error &ex)
   {
       //提示登录异常情况
       std::wstring strError = ex.Description();
       int i = strError.find(_T("SQL Server"));
       if (strError.find(_T("SQL Server")) != std::string::npos)
       {
            m_strErrDesc = _T("SQL Server 不存在或者拒绝访问");
       }
       else
       {
            m_strErrDesc = strError;
       }
   }
   catch (...)
   {

   }
    
   //步骤四
   CoUninitialize();


   return bRet;
}


std::wstring CADOManager::GetErrorDesc()
{
    if (m_strErrDesc.empty())
    {
        m_strErrDesc = _T("数据库连接失败");
    }

    return m_strErrDesc;
}
