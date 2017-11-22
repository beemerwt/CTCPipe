#pragma once
#define CTCBool CTCType(sizeof bool);
#define CTCInt CTCType(sizeof int);
#define CTCChar CTCType(sizeof char);
#define CTCSingle CTCType(sizeof float);
#define CTCDouble CTCType(sizeof double);

class CTCType {
public:
	CTCType(size_t);
	~CTCType();
	void* value;
};

