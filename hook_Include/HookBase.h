#pragma once
#include <windows.h>
#include <memory>
class HookProc {
public:
	virtual void exec(PEXCEPTION_POINTERS cpuInfo) = 0;
};

class HookOperation {
public:
	virtual void onAddHook(LPVOID hookAddress) = 0;
	virtual void onRemoveHook(LPVOID hookAddress) = 0;
};

class HookInfo {
public:
	HookInfo(std::shared_ptr<HookOperation> hookOperation, std::shared_ptr<HookProc> hookFun)
		: hookOperation(hookOperation), hookFun(hookFun) {}

	std::shared_ptr<HookOperation> hookOperation;
	std::shared_ptr<HookProc> hookFun;
};