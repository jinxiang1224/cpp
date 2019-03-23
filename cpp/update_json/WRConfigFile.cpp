#include "stdafx.h"
#include "WRConfigFile.h"
#include "json/json.h"


CWRConfigFile::CWRConfigFile(const char * szFileName) :
m_strFile(szFileName)
{

}

CWRConfigFile::~CWRConfigFile()
{

}

CWRConfigFile&CWRConfigFile::GetInstance()
{
    static  CWRConfigFile  wrConfFile("deployment.conf");

    return   wrConfFile;
}

bool CWRConfigFile::ReadFile()
{
    bool bRet = false;

    //ate 打开后立即寻位到流结尾
    // in 为读打开
    m_strContent.clear();
    m_FileStream.open(m_strFile, std::ios::in | std::ios::ate | std::ios::binary);
    if (!m_FileStream.is_open())
    {
        printf("open file error...\n");
    }



    std::streamoff  position = m_FileStream.tellg();
    if (position != -1)
    {
        // 构造 string 为流大小
        std::string strJSON(position, '\0');
        //定位到流开始位置
        m_FileStream.seekg(0);
        //读取指定大小到strJSON
        if (m_FileStream.read(&strJSON[0], position))
        {
            m_strContent = strJSON;
            bRet = true;
        }
        else
        {
            printf("read error..\n");
        }
    }
    m_FileStream.close();
    m_FileStream.clear();
    return bRet;
}


bool CWRConfigFile::WriteFile()
{
    // out 为写打开
    m_FileStream.open(m_strFile, std::ios::out);
    m_FileStream << m_strContent;
    m_FileStream.close();
    m_FileStream.clear();

    return true;
}


void CWRConfigFile::UpdateFile(const char* szRoot, const char* szKey, const char* szValue)
{

    ReadFile();

    Json::Reader reader;
    Json::StyledWriter writer;
    Json::Value  root;

    if (reader.parse(m_strContent, root))
    {
        root[szRoot][szKey] = szValue;
    }

    m_strContent = writer.write(root);

    WriteFile();
}