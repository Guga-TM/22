
#include<windows.h>
#include <iostream>
HANDLE hSemaphore;
HANDLE hEventA;
int main()
{
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, 0, "Semaphore");
	if (hSemaphore == 0) {
		std::cout << "OpenSemaphore failed.\n";
		std::cout << "Input any char to exit.\n";
		std::cin.get();
		return GetLastError();
	}
	hEventA = OpenEvent(EVENT_MODIFY_STATE, 0, "A");
	if (hEventA == 0) {
		std::cout << "OpenEvent failed.\n";
		std::cout << "Input any char to exit.\n";
		std::cin.get();
		return GetLastError();
	}
	std::cout << "Sending A message...\n";
	WaitForSingleObject(hSemaphore, INFINITE);
	printf("This process is ready. Press any key to send A message.\n");
	system("@echo off");
	system("@pause >nul");
	SetEvent(hEventA);
}


