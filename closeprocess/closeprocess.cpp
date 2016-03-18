// closeprocess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>
#include <string>
#include <iostream>

int killCount = 0;

void killProcessByName(const char *filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                ++killCount;
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int _tmain(int argc, _TCHAR* argv[])
{
  killCount = 0;
  if (argc < 2) {
    std::cout << "kill processes:apolloonline.exe" << std::endl;
    killProcessByName("apolloonline.exe");
  } else {
    std::cout << "kill processes:" << argv[1] << std::endl;
    killProcessByName(argv[1]);
  }
  std::cout << "total killed:" << killCount;
  return 0; 
}

