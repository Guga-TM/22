
#include<windows.h>
#include<conio.h>
#include <iostream>
HANDLE hEventB;
HANDLE hMutex;
int main()
{
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, "Mutex");
	if (hMutex == 0) {
		std::cout << "OpenSemaphore failed.\n";
		std::cout << "Input any char to exit.\n";
		std::cin.get();
		return GetLastError();
	}
	hEventB = OpenEvent(EVENT_MODIFY_STATE, 0, "B");
	if (hEventB == 0) {
		std::cout << "OpenEvent failed.\n";
		std::cout << "Input any char to exit.\n";
		std::cin.get();
		return GetLastError();
	}
	std::cout << "Sending B message ... \n";
	WaitForSingleObject(hMutex, INFINITE);
	printf("This process is ready. Press any key to send B message.\n");
	system("@echo off");
	system("@pause >nul");
	SetEvent(hEventB);
}


