#include "stdafx.h"
#include "CTCType.h"

CTCType::CTCType(size_t varSize) {
	value = (void*)malloc(varSize);
}

CTCType::~CTCType() {
}
