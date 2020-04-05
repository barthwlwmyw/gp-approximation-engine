#include "windows.h"
#include "pch.h" 
#include "gp-approx-eng.h"
#include <string>
#include <iostream>
#include <fstream>

int do_stuff(int a, int b)
{
	return a + b;
}

void callback_test(
	void __stdcall onProgress(int),
	void __stdcall onFinish(char*),
	char* guid)
{
	Sleep(2000);

	for (int i = 0; i < 40; i++) {
		onProgress(i);
		Sleep(250);
	}

	ofstream myfile;
	myfile.open("example.txt");
	myfile << guid;
	myfile.close();

	onFinish(guid);
}