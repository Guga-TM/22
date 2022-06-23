#pragma once
#include<windows.h>
#include<iostream>
class MonitorStack
{
	short* stack;
	int realSize;
	int maxSize;
	HANDLE hPushSemaphore;
	HANDLE hPopSemaphore;
public:
	MonitorStack(int nSize) : realSize(0), maxSize(nSize) {
		hPushSemaphore = CreateSemaphore(NULL, maxSize, maxSize, NULL);
		hPopSemaphore = CreateSemaphore(NULL, 0, maxSize, NULL);
		stack = new short[nSize];
	}
	~MonitorStack();
	void push(short nElement); 
	short pop(); 
};

