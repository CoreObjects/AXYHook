#pragma once

#include "VehHook.h"
#include "HookHandle.h"
#include <unordered_map>


class Hook {
public:
	// ��ȡ����ʵ��
	static Hook& getInstance() {
		static Hook instance;
		return instance;
	}

	// ���ÿ�������͸�ֵ�����
	Hook(const Hook&) = delete;
	Hook& operator=(const Hook&) = delete;

	// ��� Hook ����
	void addHook(LPVOID hookAddress,
		std::shared_ptr<HookProc> hookFun,
		std::shared_ptr<HookOperation> hookOperation);
	

	// �Ƴ� Hook ����
	void removeHook(LPVOID hookAddress);


	std::shared_ptr<HookProc> getHookFun(LPVOID hookAddress);
	std::shared_ptr<HookOperation> getHookOperation(LPVOID hookAddress);

private:
	// ˽�й��캯������ֹ�ⲿ����ʵ��
	Hook();

	// ��Ա����
	std::unordered_map<LPVOID, std::shared_ptr<HookInfo>> hookMap;
};

