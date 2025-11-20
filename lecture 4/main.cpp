#pragma comment (linker, "/DEFAULTLIB:PowrProf.lib")
#include <iostream>
#include <windows.h>
#include <powerbase.h>
#define DELAY 5000
using namespace std;
SYSTEM_BATTERY_STATE BatState;

int main()
{
	NTSTATUS st; DWORD LastET = 0; int LastETrepeater = 0;
	st = CallNtPowerInformation(SystemBatteryState, NULL, 0, &BatState, sizeof(BatState));
	if (st) return -1;
	cout << "\nExternal Power is: ";
	if (BatState.AcOnLine) { cout << "ON"; } else { cout << "OFF"; }
	cout << "\nWe have battery: ";
	if (BatState.BatteryPresent) { cout << "YES"; } else { cout << "NO"; }
	cout << "\nLeft time to work: ";
	do
	{
		st = CallNtPowerInformation(SystemBatteryState, NULL, 0, &BatState, sizeof(BatState));
		if (st) return -1;
		if (BatState.EstimatedTime != LastET) { LastETrepeater = 0; cout << '\n'; }
		LastET = BatState.EstimatedTime; LastETrepeater++;
		if (LastET == (DWORD)-1) { cout << "\nUNLIMITED "; } else {cout << "\n" << LastET << "sec"; }
		Sleep(DELAY);
	} while (!(GetKeyState(VK_RSHIFT) & 0x8000));
	return 0;
}