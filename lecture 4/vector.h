#pragma once
#include "fsat.h"

class vector
{
	fsat* v;
	int sz;
public:
	vector(int s);
	vector();
	~vector(); // деструктор, вызывается при удалении объекта
	inline int size(void) { return sz; }
	fsat& operator[](int);
	inline fsat& elem(int i) { return v[i] }
	void print(void);
};
void error(char* p);