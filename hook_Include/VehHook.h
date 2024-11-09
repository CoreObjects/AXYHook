#pragma once
#include "HookBase.h"
class VehHookOperation : public HookOperation {
public:
	void onAddHook(LPVOID hookAddress) override;
	void onRemoveHook(LPVOID hookAddress) override;
private:
	unsigned char oldCode = 0;
};