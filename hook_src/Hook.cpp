#include "..\hook_Include\Hook.h"

void Hook::addHook(LPVOID hookAddress, 
	std::shared_ptr<HookProc> hookFun,
	std::shared_ptr<HookOperation> hookOperation) 
{
	hookMap.emplace(hookAddress, std::make_shared<HookInfo>(hookOperation, hookFun));
	//std::cout << hookMap.at(hookAddress)->hookOperation << std::endl;
	hookMap.at(hookAddress)->hookOperation->onAddHook(hookAddress);
}

void Hook::removeHook(LPVOID hookAddress) {
	auto it = hookMap.find(hookAddress);
	if (it != hookMap.end()) {
		it->second->hookOperation->onRemoveHook(hookAddress);
		hookMap.erase(it);
	}
}

std::shared_ptr<HookProc> Hook::getHookFun(LPVOID hookAddress) {
	auto it = hookMap.find(hookAddress);
	if (it != hookMap.end()) {
		return it->second->hookFun;
	}
	else {
		return nullptr; // key 不存在，返回 nullptr
	}
}

std::shared_ptr<HookOperation> Hook::getHookOperation(LPVOID hookAddress) {
	auto it = hookMap.find(hookAddress);
	if (it != hookMap.end()) {
		return it->second->hookOperation;
	}
	else {
		return nullptr; // key 不存在，返回 nullptr
	}
}

Hook::Hook() { 
	
	AddVectoredExceptionHandler(1, HookHandle::VehHookHandle); 
	AddVectoredExceptionHandler(1, HookHandle::UnTraceHookHandle);
}
