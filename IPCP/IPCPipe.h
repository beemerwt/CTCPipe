#pragma once
#include "IPCFunc.h"

using namespace std;

class IPCPipe {
private:
	string location;
	char* FunctionToByte(void*);

	map<string, IPCFunc*> vFuncs;
public:
	IPCPipe(string);
	~IPCPipe();
	unsigned int Read();
	void Write(void*);

	// string, void*, int nArg = 0, ...
	void RegisterFunction(string, IPCFunc*);

	IPCFunc* FetchFunction(string);

	int Invoke(IPCFunc*, ...);
};

IPCPipe* OpenCTCPipe(string location) {
	return new IPCPipe(location);
}
