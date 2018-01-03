#include "stdafx.h"
#include "IPCFunc.h"

IPCFunc::IPCFunc(IntPtr funcPtr, int cArgs) {
	this->pFunc = funcPtr;
	this->cArgs = cArgs;
	this->arguments = new int*[cArgs];
}

extern "C" int IPCFunc::Invoke() {
	// Create function signature based on cArgs
	if (cArgs == 0)
		return ((int(*)())pFunc)();
	
	auto funcPtr = (int(*)(...))pFunc;
	int returnValue(0);

	int n_stack_int = cArgs * sizeof(int);      // space needed for int
	int n_stack = sizeof(int) + n_stack_int;    // overall stack space...needed for cleanup

	int p_stack = 0;

	__asm {
		sub esp, n_stack_int; // Reserve stack space
		mov p_stack, esp; // Get stack pointer
	}

	// copy to stack
	for (int i = 0; i < cArgs; i++) {
		new (&p_stack) int(*arguments[i]);
	}

	//mov ecx, returnValue; // Point ECX to returnValue
	
	__asm {
		push p_stack; // Push argument count... arguments right to left (__cdecl)
		call funcPtr; // call the function
	}

	__asm mov returnValue, eax; // write EAX into the pointer to "returnValue"
	// __asm add esp, n_stack; // Clear the stack
	__asm pop n_stack;
	
	// cleanup
	/*
	for (p = p_stack; p != p_stack + cArgs; ++p) {
		delete p;
	}
	*/
	return returnValue;
}

int IPCFunc::operator()(...) {
	va_list list;
	va_start(list, cArgs);
	for (int i = 0; i < cArgs; i++) {
		arguments[i] = &va_arg(list, int);
	}
	va_end(list);

	return Invoke();
}

int IPCFunc::GetArgCount() {
	return cArgs;
}

IPCFunc::~IPCFunc() {
}
