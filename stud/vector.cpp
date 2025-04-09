#include "vector.h"
#include "fsat.h"
#include <stdio.h>

vector::vector(int s)
{
	if (s <= 0)error(123);
	v = new fsat[s];
	if (v == 0)error(456);
	sz = s;
}
vector::vector(const vector& a):vector(a.size())
{
	int s = size();
	for (int i = 0;i < s;i++)
	{
		elem(i) = a.elem(i);
	}
}

vector::vector(vector&& a) //тебе это не нужно
{
	sz = a.size();
	v = a.v;
	a.v = nullptr;
}

vector::~vector()
{
//	if (v == 0)error(891);
	delete[] v;
	v = 0;
}

fsat& vector::operator[](int i)
{
	if (i < 0 || i >= sz) error(666);
		return v[i];
}

void vector::operator=(const vector& a)
{
	if (a.size() != size())
	{
		sz = a.size();
		delete[] v;
		v = new fsat[sz];
		if (v == 0)error(456);
	}
	int s = size();
	for (int i = 0; i < s; i++)
	{
		elem(i) = a.elem(i);
	}
}

void vector::operator=(vector&& a) //тебе это не нужно
{
	delete[] v;
	sz = a.size();
	v = a.v;
	a.v = nullptr;
}

vector vector::operator+(vector& a)
{
	if (a.size() != size()) error(998);
	int s = size();
	vector b=s;
	for (int i = 0; i < s; i++)
	{
		b.elem(i) = elem(i) + a.elem(i);
		
	}
	return b;
}

vector vector::operator-(vector& a)
{
	if (a.size() != size()) error(998);
	int s = size();
	vector b = s;
	for (int i = 0; i < s; i++)
	{
		b.elem(i) = elem(i) - a.elem(i);

	}
	return b;
}

void vector::print(void)
{
	int s = size();
	printf("[");
	for (int i = 0; i < s; i++)
	{
		if (i == s - 1) { elem(i).print();printf("]"); return; }
		elem(i).print();printf(", ");
	}
}

void error(const int a)
{
	switch (a)
	{
	case 123:
		printf("Размер вектора может быть меньше или равен нулю\n");
		break;
	case 456:
		printf("Не удалось выделить память\n");
		break;
	case 891:
		printf("Повторное удаление элемента\n");
		break;
	case 666:
		printf("Индекс вектора выходит за пределы диапазона\n");
		break;
	case 889:
		printf("Приравневание невозможно: разный размер векторов\n");
		break;
	case 998:
		printf("Сложение/вычитание невозможно: разный размер векторов\n");
		break;
	default:
		printf("Неизвестная ошибка %d\n",a);
		break;
	}
	exit(EXIT_FAILURE);
}