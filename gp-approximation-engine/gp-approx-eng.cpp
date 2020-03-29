#include "windows.h"
#include "pch.h" 
#include "gp-approx-eng.h"

int do_stuff(int a, int b)
{
	return a + b;
}

void callback_test(void __stdcall cb(int))
{
	for (int i = 0; i < 10; i++) {
		cb(i);
		Sleep(1000);
	}
}