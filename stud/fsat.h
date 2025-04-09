#pragma once
#include "myfloat.h"

class fsat:public myfloat
{
protected:
	bool flag;
	void init(void);
public:
	fsat():myfloat(0.0) { flag = 0; }
	fsat(double);
	fsat(myfloat);
	void print(void) const;
	friend fsat operator+(fsat, fsat);
	friend fsat operator-(fsat, fsat);
	friend fsat operator*(fsat, fsat);
};