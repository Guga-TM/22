#include "MonitorStack.h"
MonitorStack st(15);
CRITICAL_SECTION cs1,cs2;
DWORD WINAPI consumer(LPVOID n)
{
	EnterCriticalSection(&cs2);
	for (int i = 0; i < (int)n; i++)
		st.pop();
	LeaveCriticalSection(&cs2);
	return 0;
}
DWORD WINAPI creator(LPVOID n)
{
	EnterCriticalSection(&cs1);
	for (int i = 0; i < (int)n; i++)
		st.push(5);
	LeaveCriticalSection(&cs1);
	return 0;
}

int main()
{
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);
	int numOfCreators;
	int numOfConsumers;
	std::cout << "Enter number of creators:\t";
	std::cin >> numOfCreators;
	std::cout << "Enter number of consumers:\t";
	std::cin >> numOfConsumers;
	HANDLE* hConsumer = new HANDLE[numOfConsumers];
	HANDLE* hCreator = new HANDLE[numOfCreators];
	DWORD IDThread;
	int n2;
	for (int i = 0; i < numOfCreators; i++) {
		std::cout << "enter number of elements to produce ";
		std::cin >> n2;
		hCreator[i] = CreateThread(NULL, 0, creator, (void*)n2, 0, &IDThread);
		if (hCreator[i] == NULL) {
			for (int j = 0; j < i; j++) {
				CloseHandle(hCreator[j]);
			}
			delete[] hConsumer;
			delete[] hCreator;
			DeleteCriticalSection(&cs1);
			DeleteCriticalSection(&cs2);
			return GetLastError();
		}
		Sleep(1);
	}
	int n1;
	for (int i = 0; i < numOfConsumers; i++) {
		std::cout << "enter number of elements to consume ";
		std::cin >> n1;
		hConsumer[i] = CreateThread(NULL, 0, consumer, (void*)n1, 0, &IDThread);
		if (hConsumer[i] == NULL) {
			for (int j = 0; j < i; j++) {
				CloseHandle(hConsumer[j]);
			}
			delete[] hConsumer;
			delete[] hCreator;
			DeleteCriticalSection(&cs1);
			DeleteCriticalSection(&cs2);
			return GetLastError();
		}
		Sleep(1);
	}

	HANDLE* hGeneral = new HANDLE[numOfCreators + numOfConsumers];
	for (int i = 0; i < numOfCreators; i++) {
		hGeneral[i] = hCreator[i];
	}
	for (int i = 0; i < numOfConsumers; i++) {
		hGeneral[numOfCreators + i] = hConsumer[i];
	}
	WaitForMultipleObjects(numOfConsumers + numOfCreators, hGeneral, TRUE, INFINITE);
	
	for (int i = 0; i < numOfConsumers + numOfCreators; i++) {
		CloseHandle(hGeneral[i]);
	}
	delete[] hConsumer;
	delete[] hCreator;
	delete[] hGeneral;
	DeleteCriticalSection(&cs1);
	DeleteCriticalSection(&cs2);
	return 0;
}

