#include<iostream>
#include<windows.h>
int comp(const _int8* i, const _int8* j) {
	return *i - *j;
}
int main(int argc, char* argv[]) {
	HANDLE hReadPipe, hWritePipe;
	HANDLE hEnableRead;
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, 0, "EnableRead");
	HANDLE hEnableWrite;
	hEnableWrite = OpenEvent(EVENT_ALL_ACCESS, 0, "EnableWrite");
	DWORD dwBytesRead;
	hReadPipe = (HANDLE)atoi(argv[1]);
	hWritePipe = (HANDLE)atoi(argv[3]);
	int n = atoi(argv[2]);
	_int8* a = new _int8[n];
	WaitForSingleObject(hEnableRead, INFINITE);
	ReadFile(hReadPipe, a, n, &dwBytesRead, 0);
	std::qsort(a, n, sizeof(_int8), (int(*) (const void*, const void*)) comp);
	printf("Array is sorted, press any key to continue.\n");
	std::cin.get();
	hWritePipe = (HANDLE)atoi(argv[3]);
	DWORD dwBytesWritten;
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
		WriteFile(hWritePipe, &a[i], sizeof(a[i]), &dwBytesWritten, 0);
	}
	SetEvent(hEnableWrite);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableWrite);
	delete[] a;
}
