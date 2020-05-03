#include "windows.h"
#include "pch.h" 
#include "gp-approx-eng.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

int do_stuff(int a, int b)
{
	return a + b;
}


void doStuffInFoo(double* foo, int size) {
	

	for (int i = 0; i < size; i++) {
		foo[i] = foo[i] + (std::rand() % 5) - 2;
	}
}

void callback_test(
	void __stdcall onProgress(char*, int, double*, int),
	void __stdcall onFinish(char*),
	char* guid,
	char* datafilePath,
	int populationSize,
	int generationsNumber, 
	double crossoverProbability, 
	double mutationProbability)
{
	srand(time(NULL));
	Sleep(80);

	double foo[] = { 0.1, 0.3, 0.5, 0.6, 0.64, 0.4, -0.1, -2 };
	int fooLength = 8;

	for (int i = 1; i <= 100; i++) {
		onProgress(guid, i, foo, fooLength);
		doStuffInFoo(foo, fooLength);
		Sleep(80);
	}

	ofstream myfile;
	myfile.open("example.txt");
	myfile << guid << endl;
	myfile << datafilePath << endl;
	myfile << populationSize <<endl;
	myfile << generationsNumber << endl;
	myfile << crossoverProbability << endl;
	myfile << mutationProbability << endl;
	myfile.close();

	onFinish(guid);
}
