// HookTestExe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <memory>
#include <iostream>
#include <windows.h>
#include "..\hook_Include\Hook.h"
#include "UntraceHook.h"
void fun_1() {
    std::cout << "fun_1\n";
}

void fun_2() {
	std::cout << "fun_2\n";
}

class MyFun :public HookProc {
public:
    void exec(PEXCEPTION_POINTERS cpuInfo) override {
        std::cout << "hook Fun" << std::endl;
    }
};


int main() {
    Hook& hookManager = Hook::getInstance();
    LPVOID testAddress = reinterpret_cast<LPVOID>(fun_1);
    LPVOID testAddress_2 = reinterpret_cast<LPVOID>(fun_2);
    // 测试使用 unique_ptr 传递 hookFun 和 hookOperation
    auto hookFun = std::make_shared<MyFun>();
    auto hookOperation = std::make_shared<VehHookOperation>();
    auto Untracehook = std::make_shared<UntraceHookOperation>();
    std::cout << "执行函数" << std::endl;
    fun_1();
    std::cout << "添加VehHook" << std::endl;
    
    hookManager.addHook(testAddress, hookFun, hookOperation);
    
    std::cout << "执行函数" << std::endl;
    fun_1();

    // 移除 hook
    std::cout << "移除VehHook" << std::endl;
    
    hookManager.removeHook(testAddress);
    
	std::cout << "执行函数" << std::endl;
    fun_1();

    
	// 移除 hook
	std::cout << "添加无痕Hook" << std::endl;

    hookManager.addHook(testAddress, std::move(hookFun), std::move(Untracehook));
    std::cout << "执行函数" << std::endl;

    fun_1();
	// 移除 hook
    std::cout << "移除无痕hook" << std::endl;

	hookManager.removeHook(testAddress);

    std::cout << "执行函数" << std::endl;
    fun_1();

    system("pause");
    return 0;
}


