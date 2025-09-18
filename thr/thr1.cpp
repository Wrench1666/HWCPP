#include <thread>
#include <mutex>
#include <atomic>
#include <Windows.h>
#include <iostream>

volatile long long counter;
std::atomic<long long> counter2 = 0;
CRITICAL_SECTION win_cs;
std::mutex counter_mutex;
int val;
#define REPEATER 100

void add1or2T(int a)
{
	for (int i = 0;i < REPEATER;i++)
	{
		for (int j = 0;j < 1000001;j++)
		{
			counter+=a;
		}
	}
}

void sub1or2T(int a)
	{
		for (int i = 0;i < REPEATER;i++)
		{
			for (int j = 0;j < 1000001;j++)
			{
				counter-=a;
			}
		}
	}

void test1T(int a)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	add1or2T(a);
	sub1or2T(a);
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

void test2T(int a)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(add1or2T, a);
	std::thread th2(sub1or2T, a);
	th1.join();
	th2.join();
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

void addmutex(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			counter_mutex.lock();
			counter += a;
			counter_mutex.unlock();
		}
	}
}

void submutex(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			counter_mutex.lock();
			counter -= a;
			counter_mutex.unlock();
		}
	}
}

void testmutex(int a)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(addmutex, a);
	std::thread th2(submutex, a);
	th1.join();
	th2.join();
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

void addatomic(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			counter2.fetch_add(a);
		}
	}
}

void subatomic(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			counter2.fetch_sub(a);
		}
	}
}

void testatomic(int a)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(addatomic, a);
	std::thread th2(subatomic, a);
	th1.join();
	th2.join();
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

void addcs(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			EnterCriticalSection(&win_cs);
			counter += a;
			LeaveCriticalSection(&win_cs);
		}
	}
}

void subcs(int a)
{
	for (int i = 0; i < REPEATER; i++)
	{
		for (int j = 0; j < 1000001; j++)
		{
			EnterCriticalSection(&win_cs);
			counter -= a;
			LeaveCriticalSection(&win_cs);
		}
	}
}

void testcs(int a)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	std::thread th1(addcs, a);
	std::thread th2(subcs, a);
	th1.join();
	th2.join();
	double period = ((clock() - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

int main()
{
	std::cout << "\nEnter a value: ";
	std::cin >> val;

	test1T(val);
	std::cout << "\nCounter = " << counter;
	counter = 0;
	std::cout << "\n\n2T\n";

	test2T(val);
	std::cout << "\nCounter = " << counter;
	counter = 0;
	std::cout << "\n\nMutex\n";

	testmutex(val);
	std::cout << "\nCounter = " << counter;
	counter = 0;
	std::cout << "\n\nAtomic\n";

	testatomic(val);
	std::cout << "\nCounter = " << counter2;
	std::cout << "\n\nCritical Section\n";

	InitializeCriticalSection(&win_cs);
	testcs(val);
	std::cout << "\nCounter = " << counter;
}