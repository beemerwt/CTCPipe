#pragma once
#include "stdafx.h"

typedef int IntPtr;

using namespace std;

class IPCFunc {
private:
	IntPtr pFunc;
	int cArgs;
public:
	// IntPtr - The integer value of the pointer to a function.
	// int - The integer value of the count of arguments for that function.
	IPCFunc(IntPtr, int);
	int** arguments;

	int GetArgCount();
	int Invoke();
	int operator()(...);
	~IPCFunc();
};

