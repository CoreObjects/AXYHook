#pragma once
#include "..\hook_Include\HookHandle.h"
#include "..\hook_Include\Hook.h"

LPVOID g_hookAddress = nullptr;

LONG NTAPI HookHandle::VehHookHandle(PEXCEPTION_POINTERS exceptionInfo) {
	if (exceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {

		std::cout << "VehHookHandle" << std::endl;

		LPVOID hookAddress = (LPVOID)exceptionInfo->ExceptionRecord->ExceptionAddress;
		auto hookFun = Hook::getInstance().getHookFun(hookAddress);
		if (hookFun == nullptr)return EXCEPTION_CONTINUE_SEARCH;

		hookFun->exec(exceptionInfo);
		Hook::getInstance().getHookOperation(hookAddress)->onRemoveHook(hookAddress);
		g_hookAddress = hookAddress;
		exceptionInfo->ContextRecord->EFlags |= 0x100;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if (exceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
		std::cout << "VehHookHandle EXCEPTION_SINGLE_STEP" << std::endl;
		if (g_hookAddress) {
			Hook::getInstance().getHookOperation(g_hookAddress)->onAddHook(g_hookAddress);
			g_hookAddress = nullptr;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

LONG NTAPI HookHandle::UnTraceHookHandle(PEXCEPTION_POINTERS exceptionInfo) {

	if (exceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP) {
		std::cout << "UnTraceHookHandle EXCEPTION_SINGLE_STEP" << std::endl;
		LPVOID hookAddress = (LPVOID)exceptionInfo->ExceptionRecord->ExceptionAddress;
		auto hookFun = Hook::getInstance().getHookFun(hookAddress);
		if (hookFun == nullptr) {
			
			exceptionInfo->ContextRecord->Dr7 = 0x455;
		}
		else {
			hookFun->exec(exceptionInfo);
			exceptionInfo->ContextRecord->Dr7 = 0;
			exceptionInfo->ContextRecord->EFlags |= 0x100;
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;

}
