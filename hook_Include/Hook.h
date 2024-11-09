#pragma once

#include "VehHook.h"
#include "HookHandle.h"
#include <unordered_map>


class Hook {
public:
	// 获取单例实例
	static Hook& getInstance() {
		static Hook instance;
		return instance;
	}

	// 禁用拷贝构造和赋值运算符
	Hook(const Hook&) = delete;
	Hook& operator=(const Hook&) = delete;

	// 添加 Hook 方法
	void addHook(LPVOID hookAddress,
		std::shared_ptr<HookProc> hookFun,
		std::shared_ptr<HookOperation> hookOperation);
	

	// 移除 Hook 方法
	void removeHook(LPVOID hookAddress);


	std::shared_ptr<HookProc> getHookFun(LPVOID hookAddress);
	std::shared_ptr<HookOperation> getHookOperation(LPVOID hookAddress);

private:
	// 私有构造函数，防止外部创建实例
	Hook();

	// 成员变量
	std::unordered_map<LPVOID, std::shared_ptr<HookInfo>> hookMap;
};

