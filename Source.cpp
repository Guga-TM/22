#include <windows.h>
#include <time.h>
#include <random>
#include <iostream>
#include<process.h>
using namespace std;

DWORD WINAPI function(LPVOID arr)
{
	unsigned int tmp;
	unsigned int n = *((unsigned int*)arr);
	for (int i = 1; i < n + 1; i++) {
		tmp = *((unsigned int*)arr + i);
		if (tmp % 10 == 1)
			cout << tmp << endl;
		Sleep(10);
	}
	return 0;
}

int main()
{
	srand(time(0));
	HANDLE	worker;
	DWORD	ID;
	int n;
	cout << "enter array dimension\n";
	cin >> n;
	cout << "random array :\n";
	unsigned int* arr = new unsigned int[n + 1];
	arr[0] = n;
	for (int i = 1; i < n + 1; i++) {
		arr[i] = rand() % 100;
		cout << arr[i] << endl;
	}
	cout << "Numbers ending with 1 :\n";
	cout << "result1 :\n";
	worker = CreateThread(NULL, 0, function, (void*)arr, 0, &ID);
	if (worker == NULL)
		return GetLastError();
	SuspendThread(worker);
	Sleep(600);
	ResumeThread(worker);

	WaitForSingleObject(worker, INFINITE);
	CloseHandle(worker);
	cout << "result2 :\n";
	UINT	IDThread;
	worker = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)function, arr, 0, &IDThread);
	if (worker == NULL)
		return GetLastError();
	WaitForSingleObject(worker, INFINITE);
	return 0;
}