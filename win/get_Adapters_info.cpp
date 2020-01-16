#include <string>
#include <winsock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#pragma  comment(lib,"iphlpapi.lib")
std::string GetIP(sockaddr_in *sa_in)
{
    char buff[128] = {0};
    DWORD bufflen=128;

    if (sa_in != NULL)
    {
        inet_ntop(AF_INET,&(sa_in->sin_addr),buff,bufflen);
    }

    return std::string(buff);
}

void GetDnsServerByIP(const std::string& strSrcIP, std::string& strDnsServer)
{
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicast  = NULL;
    BOOL bFind = FALSE;

    ULONG outBufLen = 0;
    DWORD dwRetVal = 0;


    GetAdaptersAddresses(AF_UNSPEC,0, NULL, pAddresses,&outBufLen);

    pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(outBufLen);

    if ((dwRetVal = GetAdaptersAddresses(AF_INET,GAA_FLAG_SKIP_ANYCAST,NULL,pAddresses,&outBufLen)) == NO_ERROR) 
    {

        while (pAddresses) 
        {
            pUnicast = pAddresses->FirstUnicastAddress;
            for (int i = 0; pUnicast != NULL; i++)
            {
                if (pUnicast->Address.lpSockaddr->sa_family == AF_INET)
                {
                    sockaddr_in *sa_in = (sockaddr_in *)pUnicast->Address.lpSockaddr;
                    if (strSrcIP == GetIP(sa_in))
                    {
                        bFind = TRUE;
                        break;
                    }
                }

                pUnicast = pUnicast->Next;
            }

            pDnServer = pAddresses->FirstDnsServerAddress;
            if(pDnServer && bFind)
            {
                sockaddr_in *sa_in = (sockaddr_in *)pDnServer->Address.lpSockaddr;
                strDnsServer = GetIP(sa_in);
                break;
            }


            pAddresses = pAddresses->Next;
        }
    }
    else 
    {
        //printf("Call to GetAdaptersAddresses failed.\n");

    }

    if (pAddresses)
    {
        free(pAddresses);
    }
}


void Test()
{
    std::string strIP="192.168.0.107";
    std::string strDns;
    GetDnsServerByIP(strIP,strDns);
    printf("dns:%s\n",strDns.c_str());
}