#pragma  once
#include <fstream>
#include <string>
#include "json/json.h"

class CWRConfigFile
{
public:
    CWRConfigFile(const char * szFileName);
    ~CWRConfigFile();
    static CWRConfigFile&   GetInstance();
    void        UpdateFile(const char* szRoot, const char* szKey, const char* szValue);
    void       AddMember(const char* szKey, const Json::Value &  newObj);

private:
    bool        ReadFile();
    bool        WriteFile();

private:
    std::fstream    m_FileStream;
    std::string       m_strFile;
    std::string       m_strContent;
};