#pragma once
#include "..\hook_Include\HookBase.h"

class UntraceHookOperation : public HookOperation {
public:
	void onAddHook(LPVOID hookAddress) override;
	void onRemoveHook(LPVOID hookAddress) override;
private:
	bool isIdle[4]{ true };
};