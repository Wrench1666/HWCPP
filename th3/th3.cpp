#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int buffer[256];
unsigned char a;
unsigned char g;
bool err = 0;

int v = 100;
int v2 = 28000;
//maxx diff 28000-100=27900
void myadd(void)
{
	int i = 0;
	for (i; i < 1000;)
	{
		//cout << int(a) << ' ' << int(g) << '\n';
		if (unsigned char(a + 1) != g)
		{
			buffer[unsigned char(a + 1)]=i++;
			a += 1;
		}
		else
		{
			err = 1;
			return;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(v));
	}
}

void myget(void)
{
	int i = 0;
	while(i < 1000)
	{
		while (g != a)
		{
			cout << buffer[unsigned char(g + 1)] << ' ';
			g++;
			i++;
		}
		if (err == 1)
		{
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(v2));
	}
}

int main()
{

	thread addt(myadd);
	thread gett(myget);
	addt.join();
	gett.join();
	if (err == 1)
	{
		cout << "\n\nBUFFER OVERFLOWS";
	}
}