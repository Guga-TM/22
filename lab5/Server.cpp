
#include<windows.h>
#include <iostream>
#include<time.h>
#include<random>
int main()
{
	HANDLE hReadPipe, hWritePipe;
	HANDLE hEnableRead;
	HANDLE hEnableWrite;
	hEnableRead = CreateEvent(0, 0, 0, "EnableRead");
	hEnableWrite = CreateEvent(0, 0, 0, "EnableWrite");
	srand(time(0));
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	int n;
	printf("Enter array dimension :\t");
	std::cin >> n;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	char lpszComLine[80];
	wsprintf(lpszComLine, "Sort.exe %d %d %d", (int)hReadPipe, n, (int)hWritePipe);
	_int8 *a = new _int8[n];
	printf("Array :\n");
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 255;
		printf("%d\n", a[i]);
	}
	CreateProcess(NULL, lpszComLine, NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	DWORD dwBytesWritten;
	WriteFile(hWritePipe, a, n, &dwBytesWritten, 0);
	SetEvent(hEnableRead);
	WaitForSingleObject(hEnableWrite, INFINITE);
	DWORD dwBytesRead;
	ReadFile(hReadPipe, a, n, &dwBytesRead, 0);
	printf("Sorted array :\n");
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	delete[] a;
	return 0;
}


