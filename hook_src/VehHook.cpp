#include "..\hook_Include\VehHook.h"
#include <iostream>
void VehHookOperation::onAddHook(LPVOID hookAddress) {
	if (hookAddress == nullptr)return;
	std::cout << "set veh Hook at 0x" << std::hex << reinterpret_cast<DWORD_PTR>(hookAddress) << std::endl;
	DWORD dwOld;
	VirtualProtect(hookAddress, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	oldCode = *static_cast<unsigned char*>(hookAddress);
	//std::cout << "old Code =" << std::hex << (int)oldCode << std::endl;
	*reinterpret_cast<unsigned char*>(hookAddress) = static_cast<unsigned char>(0xCC);
	VirtualProtect(hookAddress, 1, dwOld, &dwOld);
}

void VehHookOperation::onRemoveHook(LPVOID hookAddress) {
	std::cout << "remove veh Hook at 0x" << std::hex << reinterpret_cast<DWORD_PTR>(hookAddress) << std::endl;
	DWORD dwOld;
	VirtualProtect(hookAddress, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*reinterpret_cast<unsigned char*>(hookAddress) = oldCode;
	VirtualProtect(hookAddress, 1, dwOld, &dwOld);
}
