#include "MonitorStack.h"
MonitorStack::~MonitorStack() {
	delete[] stack;
	CloseHandle(hPopSemaphore);
	CloseHandle(hPushSemaphore);
}
void MonitorStack::push(short nElement) {
	printf("Trying to push ...\n");
	WaitForSingleObject(hPushSemaphore, INFINITE);
	printf("Push success!\n");
	ReleaseSemaphore(hPopSemaphore, 1, NULL);
	stack[realSize] = nElement;
	realSize++;
}
short MonitorStack::pop() {
	printf("Trying to pop ...\n");
	WaitForSingleObject(hPopSemaphore, INFINITE);
	printf("Pop success!\n");
	ReleaseSemaphore(hPushSemaphore, 1, NULL);
	realSize--;
	return stack[realSize];
}