#include<iostream>
#include<windows.h>
using namespace std;
int comp(const _int8* i, const _int8* j) {
	return *i - *j;
}
int main() {
	char 	c;		
	HANDLE 	hNamedPipe;
	char 	pipeName[80];
	DWORD 	dwBytesWritten;	
	DWORD 	dwBytesRead;		
	printf("Waiting for connection with Server ...\n");

	wsprintfA(pipeName, "\\\\%s\\pipe\\demo_pipe",
		"fpmi608st1");


	hNamedPipe = CreateFileA(
		pipeName,				// имя канала
		GENERIC_READ | GENERIC_WRITE,		// читаем и записываем в канал
		FILE_SHARE_READ | FILE_SHARE_WRITE,	// разрешаем чтение и запись в канал
		(LPSECURITY_ATTRIBUTES)NULL,		// защита по умолчанию
		OPEN_EXISTING,				// открываем существующий канал
		FILE_ATTRIBUTE_NORMAL,			// атрибуты по умолчанию
		(HANDLE)NULL				// дополнительных атрибутов нет
	);
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		cerr << "Connection with the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		cin >> c;
		return (0);
	}
	int n;
	if (!ReadFile(
		hNamedPipe,
		&n,
		sizeof(int),
		&dwBytesRead,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data reading from the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	_int8* a = new _int8[n];
	if (!ReadFile(
		hNamedPipe,
		a,
		n,
		&dwBytesRead,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data reading from the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}

	printf("Array from Server :\n");
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
	}
	qsort(a, n, sizeof(_int8), (int(*) (const void*, const void*)) comp);
	printf("Sorted array :\n");
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
	}
	if (!WriteFile(
		hNamedPipe,
		a,
		n,
		&dwBytesWritten,
		(LPOVERLAPPED)NULL
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return (0);
	}
	printf("press any key to continue.");
	cin.get();
	


	delete[] a;
}
