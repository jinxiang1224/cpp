 #include <string>
#include "utilityAPI.h"
#include <tchar.h>

#include <stdio.h>
#include <iostream>

#define BUFSIZE 4096 



int _tmain(int argc, _TCHAR* argv[])
{
   CWorkProcess cmd("cmd","/c net user");
   cmd.LaunchProcess();
   cmd.WaitForEnded(10);

   std::cout << cmd.GetExitCode();
    return 0;
}