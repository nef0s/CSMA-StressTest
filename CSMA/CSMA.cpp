/*
 ________________________
|CSMA v0.3               |
|Developed by: nef0s     |
|Started: 8.10.2016      |
|Updated 1: 11.04.2017   |
|Updated 2: 05.06.2017   |
|Updated 3: 06.06.2017   |
|________________________|

*/

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

void task1(void *)
{
	while (1)
	{
		clock_t wakeup = clock() + 50;
		while (clock() < wakeup) {}
		Sleep(50);
	}
}

using namespace std;

int main(int, char**)
{
	SetConsoleTitle(TEXT("CSMA StressTest v0.3"));

	HANDLE hThread = GetCurrentThread();
	SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);

	system("color a");

	//Proverava komptabilnost sistema
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	std::cout << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	std::cout << "Total System Memory: " << (statex.ullTotalPhys / 1024) / 1024 << "MB" << endl;

	if (sysInfo.dwNumberOfProcessors > 1 //Broj jezgara
		&& (statex.ullTotalPhys / 1024) / 1024 > 512)//RAM u MB
		printf("The system meets the requirements.\n");
	else
	{
		printf("The system does not meet the requirements.\n");
		system("pause");
		return 0;
	}
	int ThreadNr;
	printf("\nDeveloped by nef0s\n");

	printf("Set difficulty: ");

	int x;
	cin >> x;
	printf("\nRunnin' %d threads\n", x / 100);
	for (int i = 0; i < x; i++) _beginthread(task1, 1, &ThreadNr);

	(void)getchar();

	system("pause");
	return 0;
}