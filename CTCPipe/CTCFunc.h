#pragma once
#include "CTCType.h"

class CTCFunc {
private:
	void* pFunc;
	CTCType** arguments;
public:
	CTCFunc(void*, int, ...);
	~CTCFunc();
};

