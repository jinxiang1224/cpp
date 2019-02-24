#include "stdafx.h"
#include <string.h>
#include <new.h>

class Mystring
{
public:
    Mystring(char* pszStr)
    {
        m_nLenth = 0;
        m_pszBuff = NULL;

        if (NULL != pszStr && strlen(pszStr) != 0)
        {
            m_nLenth = strlen(pszStr);
            m_pszBuff = new (std::nothrow) char[m_nLenth + 1];
            if (m_pszBuff != NULL)
            {
                memcpy(m_pszBuff, pszStr, m_nLenth);
                m_pszBuff[m_nLenth]   = '\0';
            }
        }
    }

    virtual ~Mystring()
    {
        if (m_pszBuff != NULL)
        {
            delete[] m_pszBuff;
        }
    }

    //深拷贝
    Mystring(const Mystring& str)
    {
        m_nLenth = str.m_nLenth;
        m_pszBuff = new (std::nothrow) char[str.m_nLenth + 1];

        if (str.m_pszBuff != NULL)
        {
            memcpy(m_pszBuff, str.m_pszBuff, m_nLenth);
        }

        m_pszBuff[m_nLenth] = '\0';
    }

    //深拷贝
    Mystring& operator=(const Mystring& str)
    {
        //防止自我赋值
        if (this != &str)
        {
            if (m_pszBuff != NULL)
            {
                delete[] m_pszBuff;
            }

            m_nLenth = str.m_nLenth;
            m_pszBuff = new (std::nothrow) char[m_nLenth + 1];

            if (str.m_pszBuff != NULL)
            {
                memcpy(m_pszBuff, str.m_pszBuff, m_nLenth);
            }

            m_pszBuff[m_nLenth] = '\0';
        }

        return *this;
    }

    void Print() const
    {
        if (m_pszBuff != NULL)
        {
            printf("%s\n",m_pszBuff);
        }
    }

private:
    char* m_pszBuff;
    int   m_nLenth;
};


/*
    //定义对象
    Mystring str1("this my string");

    //调用拷贝构造函数
    Mystring str2(str1);
    str2.Print();

    Mystring str3("");
    str3.Print();

    str2 = str3;
    str2.Print();

    str3 = str1;
    str3.Print();

    str3 = str3;
*/
