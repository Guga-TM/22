
#include<windows.h>
#include <iostream>
int main()
{

	int numofParents, numofChildren;
	std::cout << "Enter number of Parents\n";
	std::cin >> numofParents;
	STARTUPINFO* Psi;
	Psi = new STARTUPINFO[numofParents];
	PROCESS_INFORMATION* Ppi;
	Ppi = new PROCESS_INFORMATION[numofParents];
	for (int i = 0; i < numofParents; i++) {
		ZeroMemory(&Psi[i], sizeof(STARTUPINFO));
		Psi[i].cb = sizeof(STARTUPINFO);
	}
	HANDLE* pHandles;
	pHandles = new HANDLE[numofParents];
	for (int i = 0; i < numofParents; i++) {
		pHandles[i] = Ppi[i].hProcess;
	}



	std::cout << "Enter number of Children\n";
	std::cin >> numofChildren;
	STARTUPINFO* Csi;
	Csi = new STARTUPINFO[numofChildren];
	PROCESS_INFORMATION* Cpi;
	Cpi = new PROCESS_INFORMATION[numofChildren];
	for (int i = 0; i < numofChildren; i++) {
		ZeroMemory(&Csi[i], sizeof(STARTUPINFO));
		Csi[i].cb = sizeof(STARTUPINFO);
	}
	HANDLE* cHandles;
	cHandles = new HANDLE[numofChildren];
	for (int i = 0; i < numofChildren; i++) {
		cHandles[i] = Cpi[i].hProcess;
	}
	char lpszComLine[80];
	char lpszComLine2[80];
	HANDLE hEventA, hEventB;
	hEventA = CreateEvent(0, 0, 0, "A");
	hEventB = CreateEvent(0, 0, 0, "B");
	HANDLE hSemaphore;
	hSemaphore = CreateSemaphore(NULL, 1, 1, "Semaphore");
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, 0, "Mutex");
	//wsprintf(lpszComLine, "Parent.exe %d",(int)hEventA);
	//wsprintf(lpszComLine2, "Child.exe %d",(int)hEventB);
	for (int i = 0; i < numofParents; i++) {
		CreateProcess(NULL, (LPSTR)"Parent.exe", NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &Psi[i], &Ppi[i]);
	}
	for (int i = 0; i < numofChildren; i++) {
		CreateProcess(NULL, (LPSTR)"Child.exe", NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &Csi[i], &Cpi[i]);
	}	HANDLE events[2];	events[0] = hEventA;	events[1] = hEventB;	int whichEvent;	for (int i = 0; i < numofChildren + numofParents; i++) {		std::cout << "\nWaiting for A or B message...\n\n";		whichEvent = WaitForMultipleObjects(2, events, FALSE, INFINITE) - WAIT_OBJECT_0;		if (whichEvent == 0) {			std::cout << "A message from Parent.\n";			ReleaseSemaphore(hSemaphore, 1, 0);		}		else {			std::cout << "B message from Child.\n";			ReleaseMutex(hMutex);		}	}	//WaitForMultipleObjects(numofParents, pHandles, TRUE, INFINITE);	//WaitForMultipleObjects(numofChildren, cHandles, TRUE, INFINITE);	CloseHandle(hEventA);	CloseHandle(hEventB);
	for (int i = 0; i < numofParents; i++) {
		CloseHandle(Ppi[i].hProcess);
		CloseHandle(Ppi[i].hThread);
	}
	for (int i = 0; i < numofChildren; i++) {
		CloseHandle(Cpi[i].hProcess);
		CloseHandle(Cpi[i].hThread);
	}
	return 0;
}


