#pragma once
#include <windows.h>
#include <iostream>
class HookHandle {
public:
	static LONG NTAPI VehHookHandle(PEXCEPTION_POINTERS exceptionInfo);

	static LONG NTAPI UnTraceHookHandle(PEXCEPTION_POINTERS exceptionInfo);
};
