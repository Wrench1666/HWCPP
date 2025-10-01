#include <thread>
#include <iostream>

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
	std::cout << "Counter = " << counter;
}

void test2(int n)
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
	for (int i;i < n;i++)
	{
		counter += Res[i];
	}
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time = " << period;
	std::cout << "Counter = " << counter;
} // меняем n и анализируем

void test3(int n)
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
	std::cout << "Time = " << period;
	std::cout << "Counter = " << counter;
}

//(1),2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,30,40,50,100,200,300,500,(1000) - перебрать потоки
//x64/x86
//Debug/Realese
//Нужно логорифмически отображать время, вертикальная ось в виде логорифма