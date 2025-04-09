#include "myfloat.h"
#include "fsat.h"
#include "vector.h"
#include <stdio.h>
#include <iostream>



int main()
{
	setlocale(LC_ALL, "ru-RU");
	vector a = 5;
	vector b = 5;
	for (int i = 0; i < a.size(); i++)
	{
		a[i] = i + 0.1;
		b[i] = i + 1.2;
	}
	printf("a:"); a.print(); printf("\n");
	printf("b:"); b.print(); printf("\n");
	vector c = a + b;
	c = a + b;
	printf("a+b:"); c.print(); printf("\n");
	vector d = b - a;
	printf("b-a:"); d.print(); printf("\n");
	vector e = 6;
//	error(__LINE__);
	e = a;
	e.print();
//	error(__LINE__);
	printf("%d", e.size());


}




//int main()
//{
//	fsat a=10.1;
//	printf("a: ");
//	a.print();
//	printf("\nb: ");
//	fsat b = 991.0;
//	b.print(); 
//	printf("\na+b: ");
//	fsat c = a + b;
//	c.print();
//	printf("\na-b: ");
//	fsat d = a - b;
//	d.print();
//	printf("\na*b: ");
//	fsat e = a * b;
//	e.print();
//	printf("\n\na^3: ");
//	fsat f = a * a * a;
//	f.print();
//	printf("\na+b-b: ");
//	fsat g = a + b - b;
//	g.print();
//
//}



/*
int main()
{
	myfloat a = 12.3;
	myfloat b = 0.123;
	std::cout << "a: ";
	a.print();
	std::cout << std::endl << "b: ";
	b.print();
	std::cout << std::endl << "a+b: ";
	myfloat c = a + b;
	c.print();
	std::cout << std::endl << "a-b: ";
	myfloat d = a - b;
	d.print();
	std::cout << std::endl << "a*b: ";
	myfloat e = a * b;
	e.print();
	std::cout << std::endl;
}
*/
