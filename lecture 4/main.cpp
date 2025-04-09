#include <iostream>

int divv(int a, int b)
{
	return a / b;
}

int main()
{
	int a = 5;
	int b = 0;
	try
	{
		divv(a, b);
	}
	catch (...)
	{
		std::cout << "LOX";
	}
}
