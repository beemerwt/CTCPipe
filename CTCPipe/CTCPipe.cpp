#include "stdafx.h"
#include "CTCPipe.h"
#define DBG_LOC "C:\\test.txt"

CTCPipe::CTCPipe(string location) {
	this->location = location;
}

char* CTCPipe::FunctionToByte(void* pFunc) {
	char buf[16+1];
	sprintf_s(buf, "%p", pFunc);
	return buf;
}

unsigned int CTCPipe::Read() {
	FILE* testRead;
	fopen_s(&testRead, DBG_LOC, "r");
	char buf[16 + 1];
	fread(buf, 16, 1, testRead);
	fclose(testRead);
	return *buf;
}

void CTCPipe::Write(void* pFunc) {
	FILE* write;
	fopen_s(&write, DBG_LOC, "w");
	char* buf = FunctionToByte(pFunc);
	fwrite(buf, 16, 1, write);
	fclose(write);
}

void CTCPipe::RegisterFunction(void* pFunc, int nArgs=0, ...) {
	vFuncs.push_back(new CTCFunc(pFunc, nArgs));
}

void CTCPipe::Invoke(void* pFunc, ...) {

}

CTCPipe::~CTCPipe() {
}

int GetHealth() {
	return 0; // ReadMemory(ptr) example;
}

void testFunction(const char* f) {
	cout << f;
}

int main() {
	CTCPipe test("Test");
	test.RegisterFunction(GetHealth);
	test.RegisterFunction(testFunction);


	auto pFunc = testFunction;
	test.Write(pFunc);

	pFunc("test");
	
	// How we will import it to C#
	// Cannot directly import it, so we'll have to create it through managed functions.
	CTCPipe* pipe = OpenCTCPipe(DBG_LOC);

	auto testFunc = (PIPE_CHAR)test.Read();
	testFunc("test");

	Sleep(1000);
	return 0;
}
