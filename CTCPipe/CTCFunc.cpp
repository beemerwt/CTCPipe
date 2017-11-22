#include "stdafx.h"
#include "CTCFunc.h"

CTCFunc::CTCFunc(void* pFunc, int nArgs, ...) {
	this->pFunc = pFunc;
	this->arguments = new CTCType*[nArgs];
	va_list vargs;
	va_start(vargs, nArgs);
	for (int i = nArgs - 1; i > 0; i--) {
		CTCType val = va_arg(vargs, CTCType);
		this->arguments[i] = &val;
	}
	va_end(vargs);
}

CTCFunc::~CTCFunc() {
}
