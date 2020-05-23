#include "windows.h"
#include "pch.h" 
#include "gp-approx-eng.h"
#include "AlgorithmInputData.h"
#include "DataLoader.h"
#include "TreeNode.h"
#include "Tree.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>





//------------------------------------------------------------

Tree** initiatePopulation(int populationSize, AlgorithmInputData* algorithmData) {
	Tree** population = new Tree * [populationSize];

	for (int i = 0; i < populationSize; i++) {
		population[i] = new Tree(algorithmData->dimensions);
		population[i]->generateRandom();
	}

	return population;
}

double calculateFitness(Tree* tree, AlgorithmInputData* ad) {
	double fitness = 0;
	for (int i = 0; i < ad->datasetSize; i++) {
		fitness += pow(ad->resultsValues[i] - tree->evaluate(ad->variablesValues[i]), 2);
	}
	return fitness;
}

void evaluate(Tree** population, double*& fitnessVals, double*& bestTreeEvalValues, AlgorithmInputData* algData, int populationSize) {

	double best = calculateFitness(population[0], algData);
	int bestTreeIdx = 0;


	for (int i = 0; i < populationSize; i++) {
		fitnessVals[i] = calculateFitness(population[i], algData);

		if (fitnessVals[i] < best) {
			best = fitnessVals[i];
			bestTreeIdx = i;
		}
	}

	for (int i = 0; i < algData->datasetSize; i++) {
		bestTreeEvalValues[i] = population[i]->evaluate(algData->variablesValues[i]);
	}

}

Tree* selectTree(Tree**& population, int popSize, double* fitnessValues) {

	int TOURNAMENT_SIZE = 3;

	int winnerIdx = 0;
	double bestFitness = fitnessValues[winnerIdx];

	for (int i = 0; i < TOURNAMENT_SIZE; i++) {
		int randomIdx = std::rand() % popSize;

		if (fitnessValues[randomIdx] < fitnessValues[winnerIdx]) {
			winnerIdx = randomIdx;
		}
	}
	return population[winnerIdx]->clone();
}

void select(Tree**& population, int popSize, int dims, double* fitnessValues) {
	Tree** newGeneration = new Tree * [popSize];

	for (int i = 0; i < popSize; i++) {
		newGeneration[i] = selectTree(population, popSize, fitnessValues);
	}

	for (int i = 0; i < popSize; i++) {
		delete population[i];
	}
	delete population;

	population = newGeneration;
}

void mutate(Tree**& population, int popSize, int mutProb) {

	for (int i = 0; i < popSize; i++) {
		if (std::rand() % 100 <= mutProb) {
			population[i]->mutateSelf();
		}
	}
}

void crossover(Tree**& population, int popSize, int crossProb) {

	for (int i = 0; i < popSize - 1; i += 2) {
		if (std::rand() % 100 <= crossProb) {
			population[i]->crossoverWith(population[i + 1]);
		}
	}
}

void deletePopulation(Tree**& population, int popSize) {

	for (int i = 0; i < popSize; i++) {
		delete population[i];
	}
	delete population;
}

//------------------------------------------------------------











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
	void __stdcall onFinish(char* guid),
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






	//------------------------------------------------------

	int GEN_NUM = 250;
	int POP_SIZE = 250;
	int CROSS_PROB = 40;
	int MUT_PROB = 30;

	DataLoader* dl = new DataLoader();
	AlgorithmInputData* ad = dl->getData(std::string(datafilePath));

	double* fitnessValues = new double[POP_SIZE];
	double* bestTreeEvaluatedValues = new double[ad->datasetSize];

	Tree** population = initiatePopulation(POP_SIZE, ad);
	evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE);

	for (int i = 0; i < GEN_NUM; i++) {

		select(population, POP_SIZE, ad->dimensions, fitnessValues);
		mutate(population, POP_SIZE, MUT_PROB);
		crossover(population, POP_SIZE, CROSS_PROB);
		evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE);

		std::cout << "GEN: " << i << "/" << GEN_NUM << "\n";

		// printPopulation(population, POP_SIZE);

		//to do: replace foo2
		onProgress(guid, i * 100 / GEN_NUM, bestTreeEvaluatedValues, ad->datasetSize, *foo2);
	}
	evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE);

	deletePopulation(population, POP_SIZE);

	//------------------------------------------------------







	/*for (int i = 1; i <= 100; i++) {
		onProgress(guid, i, foo, fooLength, *foo2);
		doStuffInFoo(foo, fooLength);
		doStuffInGenerationMetadata(foo2);
		Sleep(80);
	}*/

	ofstream myfile;
	myfile.open("example.txt");
	myfile << guid << endl;
	myfile << datafilePath << endl;
	myfile << populationSize <<endl;
	myfile << generationsNumber << endl;
	myfile << crossoverProbability << endl;
	myfile << mutationProbability << endl;
	myfile << "----------------" << endl;
	myfile << ad->toString() << endl;
	myfile.close();

	onFinish(guid);
}
