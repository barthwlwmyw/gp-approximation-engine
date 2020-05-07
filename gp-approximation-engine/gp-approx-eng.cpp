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

struct GenerationMetadata {
	double bestFitness, averageFitness, worstFitness;
	GenerationMetadata(double b, double a, double w) {
		bestFitness = b;
		averageFitness = a;
		worstFitness = w;
	}
};

void doStuffInGenerationMetadata(GenerationMetadata* foo) {

	foo->bestFitness = foo->bestFitness / 1.2;
	foo->averageFitness = foo->averageFitness / 1.1;
	foo->worstFitness = foo->worstFitness / 1.05;
}

void callback_test(
	void __stdcall onProgress(
		char* guid,
		int progress,
		double* evalValues,
		int evalValuesLength,
		GenerationMetadata foo3),
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

	struct GenerationMetadata *foo2 = new struct GenerationMetadata(-50,-100,-150);


	for (int i = 1; i <= 100; i++) {
		onProgress(guid, i, foo, fooLength, *foo2);
		doStuffInFoo(foo, fooLength);
		doStuffInGenerationMetadata(foo2);
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
