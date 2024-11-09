#include "UntraceHook.h"

void UntraceHookOperation::onAddHook(LPVOID hookAddress) {
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(GetCurrentThread(), &ctx);
	for (int i = 0; i < 4; i++) {
		if (isIdle[i] == true) {
			switch (i) {
			case 0: ctx.Dr0 = (LONG_PTR)hookAddress; break;
			case 1:	ctx.Dr1 = (LONG_PTR)hookAddress; break;
			case 2:	ctx.Dr2 = (LONG_PTR)hookAddress; break;
			case 3:	ctx.Dr3 = (LONG_PTR)hookAddress; break;
			}
			break;
		}
	}
	ctx.Dr7 = 0x455;
	SetThreadContext(GetCurrentThread(), &ctx);
}

void UntraceHookOperation::onRemoveHook(LPVOID hookAddress) {
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(GetCurrentThread(), &ctx);
	if (ctx.Dr0 == (LONG_PTR)hookAddress) {
		ctx.Dr0 = 0; isIdle[0] = true;
	}
	else if (ctx.Dr1 == (LONG_PTR)hookAddress) {
		ctx.Dr1 = 0; isIdle[1] = true;
	}
	else if (ctx.Dr2 == (LONG_PTR)hookAddress) {
		ctx.Dr2 = 0; isIdle[2] = true;
	}
	else if (ctx.Dr3 == (LONG_PTR)hookAddress) {
		ctx.Dr3 = 0; isIdle[3] = true;
	}
	SetThreadContext(GetCurrentThread(), &ctx);
}
