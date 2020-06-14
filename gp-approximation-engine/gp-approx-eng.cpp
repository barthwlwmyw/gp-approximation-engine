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
#include <math.h> 




struct GenerationMetadata {
	double bestFitness, averageFitness, worstFitness;
	GenerationMetadata(double b, double a, double w) {
		bestFitness = b;
		averageFitness = a;
		worstFitness = w;
	}
};

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
	return std::isinf(fitness) ?
		DBL_MAX :
		fitness;
}

void evaluate(
	Tree** population,
	double*& fitnessVals,
	double*& bestTreeEvalValues,
	AlgorithmInputData* algData,
	int populationSize,
	GenerationMetadata* genMetadata) {

	double bestFitness = calculateFitness(population[0], algData);
	double sumFitness = bestFitness;
	double worstFitness = bestFitness;

	int bestTreeIdx = 0;


	for (int i = 0; i < populationSize; i++) {
		fitnessVals[i] = calculateFitness(population[i], algData);

		if (fitnessVals[i] < bestFitness) {
			bestFitness = fitnessVals[i];
			bestTreeIdx = i;
		}
		if (fitnessVals[i] > worstFitness) {
			worstFitness = fitnessVals[i];
		}
		sumFitness += fitnessVals[i];
	}

	for (int i = 0; i < algData->datasetSize; i++) {
		bestTreeEvalValues[i] = population[i]->evaluate(algData->variablesValues[i]);
	}
	if (isinf(sumFitness)) sumFitness = DBL_MAX;
	// genMetadata->averageFitness = sumFitness / (double)populationSize;
	genMetadata->averageFitness = 0;
	genMetadata->bestFitness = bestFitness;
	genMetadata->worstFitness = 0;

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

void runApproximation(
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

	struct GenerationMetadata* generationMetadata = new struct GenerationMetadata(0,0,0);

	//------------------------------------------------------

	int GEN_NUM = generationsNumber;
	int POP_SIZE = populationSize;
	int CROSS_PROB = (int)(crossoverProbability * 100);
	int MUT_PROB = (int)(mutationProbability * 100);

	DataLoader* dl = new DataLoader();
	AlgorithmInputData* ad = dl->getData(std::string(datafilePath));

	double* fitnessValues = new double[POP_SIZE];
	double* bestTreeEvaluatedValues = new double[ad->datasetSize];

	Tree** population = initiatePopulation(POP_SIZE, ad);
	evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);

	for (int i = 0; i < GEN_NUM; i++) {

		select(population, POP_SIZE, ad->dimensions, fitnessValues);
		mutate(population, POP_SIZE, MUT_PROB);
		crossover(population, POP_SIZE, CROSS_PROB);
		evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);

		onProgress(guid, ceil(i * 100 / GEN_NUM), bestTreeEvaluatedValues, ad->datasetSize, *generationMetadata);
	}
	evaluate(population, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);

	deletePopulation(population, POP_SIZE);

	delete dl;
	delete ad;

	onFinish(guid);
}
