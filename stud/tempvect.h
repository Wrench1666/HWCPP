#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

void error(const int a);


template<typename T>
class tempvect
{
	T* v;
	int sz;
public:
	tempvect(int s = 3)
	{
		if (s <= 0)error(123);
		v = new T[s];
		if (v == 0)error(456);
		sz = s;
	}
	tempvect(const tempvect& a)
	{
		int s = size();
		for (int i = 0;i < s;i++)
		{
			elem(i) = a.elem(i);
		}
	}
	tempvect(tempvect&& a)
	{
		sz = a.size();
		v = a.v;
		a.v = nullptr;
	}

	~tempvect()
	{
		delete[] v;
		v = 0;
	}

	inline int size(void) const { return sz; }

	T& operator[](int i)
	{
		if (i < 0 || i >= sz) error(666);
		return v[i];
	}

	inline T& elem(int i) const { return v[i]; }

	void print(void)
	{
		int s = size();
		printf("[");
		for (int i = 0; i < s; i++)
		{
			if (i == s - 1) { cout << elem(i) << "]"; return; }
			cout << elem(i) << ", ";
		}
	}
	void operator=(const tempvect& a)
	{
		if (a.size() != size())
		{
			sz = a.size();
			delete[] v;
			v = new T[sz];
			if (v == 0)error(456);
		}
		int s = size();
		for (int i = 0; i < s; i++)
		{
			elem(i) = a.elem(i);
		}
	}

	void operator=(tempvect&& a)
	{
		delete[] v;
		sz = a.size();
		v = a.v;
		a.v = nullptr;
	}

	tempvect operator+(tempvect& a)
	{
		if (a.size() != size()) error(998);
		int s = size();
		tempvect b = s;
		for (int i = 0; i < s; i++)
		{
			b.elem(i) = elem(i) + a.elem(i);

		}
		return b;
	}

	tempvect operator-(tempvect& a)
	{
		if (a.size() != size()) error(998);
		int s = size();
		tempvect b = s;
		for (int i = 0; i < s; i++)
		{
			b.elem(i) = elem(i) - a.elem(i);

		}
		return b;
	}
};


template<>
void tempvect<fsat>::print()
{
	int s = size();
	printf("[");
	for (int i = 0; i < s; i++)
	{
		if (i == s - 1) { elem(i).print();cout << "]"; return; }
		elem(i).print();cout << ", ";
	}
}



template<>
void tempvect<tempvect<int>>::print()
{
	int s = size();
	printf("[");
	for (int i = 0; i < s; i++)
	{
		if (i == s - 1) { elem(i).print();cout << "]"; return; }
		elem(i).print();cout << ", ";
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
		printf("Неизвестная ошибка %d\n", a);
		break;
	}
	exit(EXIT_FAILURE);

}