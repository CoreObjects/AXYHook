#include <windows.h>

int __stdcall DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MessageBox(NULL, L"ע��ɹ�", L"ע��ɹ�", MB_OK);
	}

	return 0;
}