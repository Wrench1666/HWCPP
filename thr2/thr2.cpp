#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
long long counter;
int val;
#define NUMBER 100000001ll


void fun1(int a, long long start, long long stop,
	long long* pcounter)
{
	volatile long long count = 0;
	for (long long i = start;i < stop;i++)
	{
		if (i & 1)count -= a;
		else count += a;
	}
	*pcounter = count;
}

void test1T(int a)
{
	clock_t time0;
	long long cnt1 = 0;
	counter = 0;
	time0 = clock();
	fun1(a, 0, NUMBER, &cnt1);
	counter = cnt1;
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time = " << period;
	std::cout << " Counter = " << counter;
}

double test2(int n)
{
	clock_t time0;
	counter = 0;
	static long long start[1000];
	static long long stop[1000];
	static long long Res[1000];
	std::thread* pThreads[1000];
	long long stp = 0;
	for (int i = 0;i < n;i++)
	{
		start[i] = stp;
		stop[i] = stp = stp + NUMBER / n; //сначала stp станет равен правой части, а потом stp пойдет в массив
		Res[i] = 0;
	}
	stop[n - 1] = NUMBER;
	time0 = clock();
	for (int i = 0;i < n;i++)
	{
		pThreads[i] = new std::thread(fun1, val, start[i], stop[i], &Res[i]);
	}
	for (int i = 0;i < n;i++)
	{
		pThreads[i]->join();
	}
	for (int i = 0;i < n;i++)
	{
		counter += Res[i];
	}
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "\n\nThreads = " << n;
	std::cout << "\nTime = " << period;
	std::cout << " Counter = " << counter;
	return period;
} // меняем n и анализируем

double test3(int n)
{
	clock_t time0;
	counter = 0;
	time0 = clock();

#pragma omp parallel for reduction(+:counter) num_threads(n)
	for (long long i = 0;i < NUMBER;i++)
	{
		if (i & 1) counter -= val;
		else counter += val;
	}
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "\n\nOMP Threads = " << n;
	std::cout << "\nTime = " << period;
	std::cout << " Counter = " << counter;
	return period;
}

//(1),2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,30,40,50,100,200,300,500,(1000) - перебрать потоки
//x64/x86
//Debug/Realese
//Нужно логорифмически отображать время, вертикальная ось в виде логорифм

int main()
{
	cin >> val;
	std::ofstream file("R64E.csv");
	file << "N;2T;2T OMP\n";
	test1T(1);
	for (int i = 1; i < 20; i++)
	{
		file << i << ';' << test2(i) << ';' << test3(i) << '\n';
	}
	for (int i = 20; i < 51; i+=10)
	{
		file << i << ';' << test2(i) << ';' << test3(i) << '\n';
	}
	for (int i = 100; i < 801; i+=100)
	{
		file << i << ';' << test2(i) << ';' << test3(i) << '\n';
	}
	file.close();
}