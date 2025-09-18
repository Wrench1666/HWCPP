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

void f1(int a)
	{
		for (int i = 0;i < REPEATER;i++)
		{
			for (int j = 0;j < 1000001;j++)
			{
				//действие +
			}
		}
	}

void f2(int a)
	{
		for (int i = 0;i < REPEATER;i++)
		{
			for (int j = 0;j < 1000001;j++)
			{
				//действие -
			}
		}
	}

void test1(void)
{
	clock_t time0, time1;
	counter = 0;
	time0 = clock();
	//тест
	time1 = clock();
	double period = ((time1 - time0) * 10000) / CLOCKS_PER_SEC;
	std::cout << "Time= " << period;
}

int main()
{
	std::cout << "\nEnter a value: ";
	//std::cin >> b;
}