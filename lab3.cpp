// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<windows.h>
#include <iostream>
using namespace std;
CRITICAL_SECTION cs;
HANDLE endSort, sumBegin;
int n, k;
double result = 0;
DWORD WINAPI work(LPVOID str)
{
	int time;
	cout << "Enter sleep time: \t";
	cin >> time;
	int j = 0;
	char tmp;
	for (int i = 0; i < n; i++) {
		if (i == k) {
			SetEvent(endSort);
		}
		j = i;
		for (int l = i; l < n; l++) {
			if (*((char*)str + j) > * ((char*)str + l)) {
				j = l;
			}
		}
		tmp = *((char*)str + i);
		*((char*)str + i) = *((char*)str + j);
		*((char*)str + j) = tmp;
		Sleep(time);
	}
	return 0;
}
DWORD WINAPI SumElement(LPVOID str)
{
	EnterCriticalSection(&cs); 
	WaitForSingleObject(sumBegin, INFINITE);
	
	for (int i = 0; i < k; i++) {
		result += (double)(int)*((char*)str + i);
	}
	result /= k;
	LeaveCriticalSection(&cs);
	return 0;
}
int main()
{
	HANDLE hWork, hSumElement;
	DWORD IDWork, IDSumElement;
	endSort = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (endSort == NULL)
		return GetLastError();
	sumBegin = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (sumBegin == NULL)
		return GetLastError();
	char* str;
	cout << "Enter array dimension :\t";
	cin >> n;
	str = new char[n];
	cout << "Enter array :\n";
	cin >> str;
	cout << "Enter k :\t";
	cin >> k;
	InitializeCriticalSection(&cs);
	hWork = CreateThread(NULL, 0, work, (void*)str, 0, &IDWork);
	if (hWork == NULL)
		return GetLastError();
	hSumElement = CreateThread(NULL, 0, SumElement, (void*)str, 0, &IDSumElement);
	if (hSumElement == NULL)
		return GetLastError();
	WaitForSingleObject(endSort, INFINITE);
	for (int i = 0; i < k; i++) {
		cout << str[i];
	}
	SetEvent(sumBegin);
	cout << endl;
	EnterCriticalSection(&cs);
	cout << result << endl;
	LeaveCriticalSection(&cs);

	cout << endl;
	DeleteCriticalSection(&cs);
	WaitForSingleObject(hWork, INFINITE);
	for (int i = k - 1; i < n; i++) {
		cout << str[i];
	}
	WaitForSingleObject(hSumElement, INFINITE);
	CloseHandle(hWork);
	CloseHandle(hSumElement);
	return 0;
}

