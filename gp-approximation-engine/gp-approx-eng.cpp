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
	void __stdcall onProgress(char*, int),
	void __stdcall onFinish(char*),
	char* guid,
	char* datafilePath,
	int populationSize,
	int generationsNumber, 
	double crossoverProbability, 
	double mutationProbability)
{
	Sleep(2000);

	for (int i = 1; i <= 100; i++) {
		onProgress(guid, i);
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