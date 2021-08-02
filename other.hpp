#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <filesystem>
#include "skCrypt.hpp"

#define _CRT_NONSTDC_NO_DEPRECATE

bool IsProcessRunningQQ(const wchar_t* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_wcsicmp((const wchar_t*)entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

void closeProcesses() {
	system(skCrypt("sc stop BEService >nul 2>&1"));
	system(skCrypt("sc stop BEDaisy >nul 2>&1"));
	system(skCrypt("sc stop EasyAntiCheat >nul 2>&1"));
	system(skCrypt("sc stop EasyAntiCheatSys >nul 2>&1"));
	system(skCrypt("TASKKILL /F /IM EpicGamesLauncher.exe >NUL 2>&1"));
	system(skCrypt("TASKKILL /F /IM UnrealCEFSubProcess.exe >NUL 2>&1"));
	system(skCrypt("TASKKILL /F /IM FortniteClient-Win64-Shipping.exe >NUL 2>&1"));
	system(skCrypt("TASKKILL /F /IM r5apex.exe >NUL 2>&1"));
	system(skCrypt("TASKKILL /F /IM r5apex.exe >NUL 2>&1"));
}

