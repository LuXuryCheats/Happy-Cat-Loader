#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

#include "skCrypt.hpp"
#include "lazy_importer.hpp"


bool find(const char* name)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    auto snapshot = LI_FN(CreateToolhelp32Snapshot).safe()(TH32CS_SNAPPROCESS, NULL);

    if (LI_FN(Process32First).safe()(snapshot, &entry) == TRUE)
    {
        while (LI_FN(Process32Next).safe()(snapshot, &entry) == TRUE)
        {
            if (!strcmp(entry.szExeFile, name))
            {

                return true;
            }
        }
    }

    LI_FN(CloseHandle).safe()(snapshot);
    return false;
}
/**
* Checks for bad processes
* @return Checks a bunch of processes and returns boolean containing status.
*/
int check()
{
    std::vector<const char*> processes = {
        skCrypt("ollydbg.exe"),
        skCrypt("ProcessHacker.exe"),
        skCrypt("tcpview.exe"),
        skCrypt("autoruns.exe"),
        skCrypt("autorunsc.exe"),
        skCrypt("filemon.exe"),
        skCrypt("procmon.exe"),
        skCrypt("regmon.exe"),
        skCrypt("procexp.exe"),
        skCrypt("idaq.exe"),
        skCrypt("idaq64.exe"),
        skCrypt("ida.exe"),
        skCrypt("ida64.exe"),
        skCrypt("ImmunityDebugger.exe"),
        skCrypt("Wireshark.exe"),
        skCrypt("dumpcap.exe"),
        skCrypt("HookExplorer.exe"),
        skCrypt("ImportREC.exe"),
        skCrypt("PETools.exe"),
        skCrypt("LordPE.exe"),
        skCrypt("SysInspector.exe"),
        skCrypt("proc_analyzer.exe"),
        skCrypt("sysAnalyzer.exe"),
        skCrypt("sniff_hit.exe"),
        skCrypt("windbg.exe"),
        skCrypt("joeboxcontrol.exe"),
        skCrypt("joeboxserver.exe"),
        skCrypt("ResourceHacker.exe"),
        skCrypt("x32dbg.exe"),
        skCrypt("x64dbg.exe"),
        skCrypt("Fiddler.exe"),
        skCrypt("httpdebugger.exe"),
        //you can add more if you want
    };

    for (auto process : processes)
    {
        if (find(process)) exit(-1);
    }

    return false;
}

void titledetect()
{
    HWND window;
    window = FindWindow(0, skCrypt(("Attach")));
    if (window)
    {
        exit(-1);
    }

    window = FindWindow(0, skCrypt(("Memory Viewer")));
    if (window)
    {
        exit(-1);
    }

    window = FindWindow(0, skCrypt(("Process List")));
    if (window)
    {
        exit(-1);
    }
    //you can add more if you want

}

