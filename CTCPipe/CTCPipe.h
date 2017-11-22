#pragma once
#include <string>
#include <vector>
#include "CTCFunc.h"
#define PIPE_VOID void (*)(void)
#define PIPE_BOOL void (*)(bool)
#define  PIPE_INT void (*)(int)
#define PIPE_CHAR void (*)(const char*)

using namespace std;

class CTCPipe {
private:
	std::string location;
	vector<CTCFunc*> vFuncs;
	char* FunctionToByte(void*);
public:
	CTCPipe(std::string);
	~CTCPipe();
	unsigned int Read();
	void Write(void*);
	void RegisterFunction(void*, int nArg = 0, ...);
	void Invoke(void*, ...);
};

CTCPipe* OpenCTCPipe(std::string location) {
	return new CTCPipe(location);
}