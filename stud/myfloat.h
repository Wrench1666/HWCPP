#pragma once

#include <cmath>
class myfloat
{
protected:
	int m, e;
public:

	myfloat(double);

	myfloat(int, int);

	void print(void) const;

	friend myfloat operator+(myfloat, myfloat);
	friend myfloat operator-(myfloat, myfloat);
	friend myfloat operator*(myfloat, myfloat);
};