#include "stdafx.h"
#include "IPCPipe.h"
#define DBG_LOC "C:\\test.txt"

IPCPipe::IPCPipe(string location) {
	this->location = location;
}

char* IPCPipe::FunctionToByte(void* pFunc) {
	char buf[16+1];
	sprintf_s(buf, "%p", pFunc);
	return buf;
}

unsigned int IPCPipe::Read() {
	FILE* testRead;
	fopen_s(&testRead, DBG_LOC, "r");
	char buf[16 + 1];
	fread(buf, 16, 1, testRead);
	fclose(testRead);
	return *buf;
}

void IPCPipe::Write(void* pFunc) {
	FILE* write;
	fopen_s(&write, DBG_LOC, "w");
	char* buf = FunctionToByte(pFunc);
	fwrite(buf, 16, 1, write);
	fclose(write);
}

// ... - The size of each variable type required by the function.
// string fName, void* pFunc, int nArgs=0, ...
void IPCPipe::RegisterFunction(string name, IPCFunc* pFunc) {
	vFuncs[name] = pFunc;
}

IPCFunc* IPCPipe::FetchFunction(string fName) {
	return vFuncs[fName];
}

// Returns a pointer to the value that the function returned.
int IPCPipe::Invoke(IPCFunc* pFunc, ...) {
	int size = pFunc->GetArgCount();
	
	va_list valist;
	va_start(valist, size);
	for (int i = 0; i < size; i++) {
		pFunc->arguments[i] = &va_arg(valist, int);
	}
	va_end(valist);

	return pFunc->Invoke();
}

IPCPipe::~IPCPipe() {
}

// Example of a function that would be implemented.
int TestReadMemory(int base, int address) {
	return base + address;
}

bool TestPrintMessage(LPCWSTR message) {
	return MessageBox(NULL, message, L"Test", MB_OK);
}

int isthisokay(int f) {
	std::cout << "Yes, it is okay, Mr." << f << std::endl;
	return f + 1;
}

int main() {
	IPCPipe test("Test");
	IPCFunc* func = new IPCFunc((IntPtr)isthisokay, 1);
	test.RegisterFunction("isthisokay", func);

	IPCFunc* testFunc = test.FetchFunction("isthisokay");

	//int x = (*testFunc)(1);
	int x = 1;
	printf("Test Func: %d\n", isthisokay);
	printf("X: %d %d\n", x, &x);
	int t = test.Invoke(testFunc, x);

	printf("X: %d\nT: %d\n", x, t);

	// How we will import it to C#
	// Cannot directly import it, so we'll have to create it through managed functions.
	IPCPipe* pipe = OpenCTCPipe(DBG_LOC);

	Sleep(1000);
	
	return 0;
}
