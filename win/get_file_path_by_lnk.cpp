#include <Shlobj.h>
#include <shlwapi.h>
#include <vector>
#pragma  comment(lib, "shlwapi.lib")

BOOL GetSpecialFolderPath(std::string & strChromeLnkPath,int csidl)
{
    char szChromeLnkPath[MAX_PATH] = {0};
    strChromeLnkPath.clear();
    if (SHGetSpecialFolderPath(0,szChromeLnkPath,csidl,0))
    {
        strChromeLnkPath = szChromeLnkPath;
        strChromeLnkPath += "\\Google Chrome.lnk";
        return TRUE;
    }

    return FALSE;
}


BOOL GetValidChromeLnkPath(std::string & strValidChromeLnkPath)
{
    std::vector<std::string> vecLnkPath;
    std::string strChromeLnkPath;
    strValidChromeLnkPath.clear();

    if (GetSpecialFolderPath(strChromeLnkPath,CSIDL_COMMON_PROGRAMS))
    {
        vecLnkPath.push_back(strChromeLnkPath);
    }

    if (GetSpecialFolderPath(strChromeLnkPath,CSIDL_DESKTOP))
    {
        vecLnkPath.push_back(strChromeLnkPath);
    }

    if (GetSpecialFolderPath(strChromeLnkPath,CSIDL_PROGRAMS))
    {
        vecLnkPath.push_back(strChromeLnkPath);
    }

    for (unsigned i = 0; i < vecLnkPath.size(); i++)
    {
        if (::PathFileExists(vecLnkPath[i].c_str()))
        {
            strValidChromeLnkPath = vecLnkPath[i];
            break;
        }
    }

    return strValidChromeLnkPath.empty() ? FALSE : TRUE;
}

BOOL GetChromePath(std::string& strChromeLnkPath, std::string& strExePath)
{
    BOOL bRet = FALSE;
    HRESULT hr = 0;
    IShellLink     *pLink = NULL; 
    IPersistFile   *ppf = NULL; 
    CoInitialize(NULL);

    char  szExePath[MAX_PATH] = {0};
    WCHAR wszLnkPath[MAX_PATH] = {0};
    swprintf_s(wszLnkPath,sizeof(wszLnkPath),L"%S",strChromeLnkPath.c_str());

    do 
    {
        hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
        if (FAILED(hr))
        {
            break;      
        }

        hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
        if (FAILED(hr))
        {
            break;
        }
        //多字节工程，竟然是WCHAR类型，load接口比较奇怪
        hr = ppf->Load(wszLnkPath, STGM_READWRITE);
        if (SUCCEEDED(hr))
        {
            hr = pLink->Resolve(NULL, SLR_NO_UI);
            if (SUCCEEDED(hr))
            {
                hr = pLink->GetPath(szExePath, MAX_PATH, NULL, SLGP_RAWPATH);
                if (SUCCEEDED(hr))
                {
                    bRet = TRUE;
                }
            }
        }

    } while (0);

    if (bRet)
    {
        strExePath.assign(szExePath);  
    }

    if (ppf != NULL)
    {
        ppf->Release();
    }

    if (pLink != NULL)
    {
        pLink->Release();
    }

    CoUninitialize();

    return bRet;

}


void Test()
{
    std::string strLnkPath;
    std::string strExePath;
    if (GetValidChromeLnkPath(strLnkPath))
    {
        if (GetChromePath(strLnkPath,strExePath))
        {
            printf("path=%s\n",strExePath.c_str());
        }
    }
}