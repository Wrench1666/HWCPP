#include "fsat.h"
#include <stdio.h>

void fsat::init(void)
{
	flag = 0;
	if (e > 3)
	{
		flag = 1;
		if (m > 0)m = 999;else m = -999;
		e = 3;
	}
}
fsat::fsat(double a = 0.0):myfloat(a)
{
	init();
}

fsat::fsat(myfloat a):myfloat(a)
{
	init();
}

void fsat::print(void) const
{
	myfloat::print();
	if (flag)printf("*");
	// printf("         %d, %d", m, e);
}


fsat operator+(fsat a, fsat b)
{
	myfloat temp_fl = (myfloat)a + (myfloat)b;
	return fsat(temp_fl);
}

fsat operator-(fsat a, fsat b)
{
	myfloat temp_fl = (myfloat)a - (myfloat)b;
	return fsat(temp_fl);
}

fsat operator*(fsat a, fsat b)
{
	myfloat temp_fl = (myfloat)a * (myfloat)b;
	return fsat(temp_fl);
}

