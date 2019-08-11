#include "ReportMac.h"
#include <string>

CReportMac::~CReportMac()
{

}

CReportMac::CReportMac()
{

}

unsigned CReportMac::Process()
{
//     //监听控制台请求类型
//     DatagramSocket ListenActionType(6001,"255.255.255.255",false,true);
//     char szCtrlMsg[128] = {};
//     while (1)
//     {
//         memset(szCtrlMsg, 0, sizeof(szCtrlMsg))
//         ListenActionType.receive(szCtrlMsg, sizeof(szCtrlMsg));
//         
//         if (strlen(szCtrlMsg) > 0)
//         {
//             if (szCtrlMsg[1] == 0x11)
//             {
//                 ReportMac(szCtrlMsg + 1);
//             }
//         }
// 
//     }

    return 0;
}


//指定方向上报
void CReportMac::ReportMac(const char* szConsoleIP)
{
    //获取mac地址
    char szMacInfo[128] = {};
    CIPUtil::GetLocalMAC(szMacInfo,sizeof(szMacInfo));

    //向控制台发送信息
    //
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =false;
    opt.reusesock = true;
    opt.multi_cast = false;

    DatagramSocket reportMac(6002,szConsoleIP,opt);
    reportMac.send(szMacInfo,sizeof(szMacInfo));
}