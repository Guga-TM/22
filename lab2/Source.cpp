#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include<string.h>
#include<string>
#include <conio.h>
using namespace std;
int main()
{
	char lpszAppName[] = "D:\\temp\\Projectt\\Parent\\Debug\\Child.exe";
	_cputs("Enter name of program, -Child.exe- , \n then number of elements, then\n elements, then $ as the end of the string: \n ");
	char* lpszCommandLine = new char[55];
	cin.getline(lpszCommandLine, 55, '$');
	cout << "\n\n";
	printf("%s\n", lpszCommandLine);
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USECOUNTCHARS;
	si.dwXCountChars = 1000;
	if (!CreateProcess(lpszAppName, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	_cputs("The new process is created.\n");
	// ждем завершения созданного прцесса
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	return 0;
}