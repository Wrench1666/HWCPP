#pragma once
#include "fsat.h"

class vector
{
	fsat* v;
	int sz;
public:
	vector(int s=100);
	vector(const vector&);
	vector(vector&&); // тебе это не нужно 
	~vector(); 
	inline int size(void) const { return sz; }
	fsat& operator[](int);
	inline fsat& elem(int i) const { return v[i]; }
	void print(void);
	void operator=(const vector&);
	void operator=(vector&&); // тебе это не нужно
	vector operator+(vector& a);
	vector operator-(vector& a);
};
void error(const int a);