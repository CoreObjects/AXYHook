#include <windows.h>

int __stdcall DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MessageBox(NULL, L"注入成功", L"注入成功", MB_OK);
	}

	return 0;
}