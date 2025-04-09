#include <iostream>
#include <cmath>
#include "myfloat.h"

myfloat::myfloat(double val = 0.0)
{
	m = 0;
	e = 0;
	if (val == 0.0) return;
	while (abs(val) >= 1.0)
	{
		val /= 10.0; e++;
	}
	while (abs(val) < 0.1)
	{
		val *= 10.0; e--;
	}
	m = int(val * 1000);
}

myfloat::myfloat(int a, int b)
{

	while (abs(a) > 1000) 
	{
		a /= 10;
		b++;
	}
	while (abs(a) < 100)
	{
		a *= 10;
		b--;
	}
	m = a;
	e = b;
}

void myfloat::print(void) const
{
	printf("%.03f", (m / 1000.0) * std::pow(10.0, e));
	//printf("%.03f[%d, %d]", (m / 1000.0) * std::pow(10.0, e), m, e);
}

myfloat operator+(myfloat a, myfloat b)
{
	if (a.e > b.e)
	{
		while (a.e != b.e)
		{
			a.e--;
			a.m *= 10;
		}
	}
	else
	{
		while (a.e != b.e)
		{
			b.e--;
			b.m *= 10;
		}
	}
	return myfloat(a.m + b.m, a.e);
}

myfloat operator-(myfloat a, myfloat b)
{
	if (a.e > b.e)
	{
		while (a.e != b.e)
		{
			a.e--;
			a.m *= 10;
		}
	}
	else
	{
		while (a.e != b.e)
		{
			b.e--;
			b.m *= 10;
		}
	}
	return myfloat(a.m - b.m, a.e);
}

myfloat operator*(myfloat a, myfloat b)
{
	return myfloat((a.m * b.m), a.e + b.e - 3);
}