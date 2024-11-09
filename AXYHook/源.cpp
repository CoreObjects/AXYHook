// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <windows.h>
#include <iostream>
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
	MessageBoxA(NULL, NULL, NULL, NULL);
	while (true) {
		std::cout << "dll has been Injected..." << std::endl;
		Sleep(1000);  // 等待1秒，避免输出过快
	}
	return 0;
}



int __stdcall DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, ThreadFunc, hModule, 0, 0);
	}
	return 1;
}

