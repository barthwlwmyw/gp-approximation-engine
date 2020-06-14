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
	double bestFitness, bestFitnessInGeneration;
	GenerationMetadata(double bstFit, double bstFitnessInGen) {
		bestFitness = bstFit;
		bestFitnessInGeneration = bstFitnessInGen;
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
		fitness -= pow(ad->resultsValues[i] - tree->evaluate(ad->variablesValues[i]), 2);
	}
	return fitness;
}

void fixPopulation(
	Tree**& population,
	double*& fitnessVals,
	AlgorithmInputData* algData,
	int populationSize) {

	for (int i = 0; i < populationSize; i++) {
		while (std::isinf(fitnessVals[i])) {
			delete population[i];
			population[i] = new Tree(algData->dimensions);
			population[i]->generateRandom();
			fitnessVals[i] = calculateFitness(population[i], algData);
		}
	}
}

void evaluate(
	Tree** population,
	Tree*& bestSolution,
	double*& fitnessVals,
	double*& bestTreeEvalValues,
	AlgorithmInputData* algData,
	int populationSize,
	GenerationMetadata*& genMetadata) {

	double bestFitness = calculateFitness(population[0], algData);
	
	int bestTreeIdx = 0;


	for (int i = 0; i < populationSize; i++) {
		fitnessVals[i] = calculateFitness(population[i], algData);
	}

	fixPopulation(population, fitnessVals, algData, populationSize);

	for (int i = 0; i < populationSize; i++) {
		if (fitnessVals[i] > bestFitness) {
			bestFitness = fitnessVals[i];
			bestTreeIdx = i;
		}
	}

	for (int i = 0; i < algData->datasetSize; i++) {
		bestTreeEvalValues[i] = population[bestTreeIdx]->evaluate(algData->variablesValues[i]);
	}

	genMetadata->bestFitnessInGeneration = bestFitness;

	double bestFitnessSoFar = genMetadata->bestFitness;
	if (bestFitness > bestFitnessSoFar) {
		genMetadata->bestFitness = bestFitness;
		delete bestSolution;
		bestSolution = population[bestTreeIdx]->clone();
	}

}

Tree* selectTree(Tree**& population, int popSize, double* fitnessValues) {

	int TOURNAMENT_SIZE = 3;

	int winnerIdx = 0;
	double bestFitness = fitnessValues[winnerIdx];

	for (int i = 0; i < TOURNAMENT_SIZE; i++) {
		int randomIdx = std::rand() % popSize;

		if (fitnessValues[randomIdx] > fitnessValues[winnerIdx]) {
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
		GenerationMetadata genMeta),
	void __stdcall onFinish(
		char* guid,
		char* treeFormula),
	char* guid,
	char* datafilePath,
	int populationSize,
	int generationsNumber, 
	double crossoverProbability, 
	double mutationProbability)
{
	srand(time(NULL));

	struct GenerationMetadata* generationMetadata = new struct GenerationMetadata(-DBL_MAX, -DBL_MAX);

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
	Tree* bestSolution = population[0]->clone();

	evaluate(population, bestSolution, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);


	for (int i = 0; i < GEN_NUM; i++) {

		select(population, POP_SIZE, ad->dimensions, fitnessValues);
		mutate(population, POP_SIZE, MUT_PROB);
		crossover(population, POP_SIZE, CROSS_PROB);
		evaluate(population, bestSolution, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);
		

		onProgress(guid, ceil(i * 100 / GEN_NUM), bestTreeEvaluatedValues, ad->datasetSize, *generationMetadata);
	}
	evaluate(population, bestSolution, fitnessValues, bestTreeEvaluatedValues, ad, POP_SIZE, generationMetadata);



	std::string testFormula = population[0]->toString();
	char* treeFormulaCharArray = new char[testFormula.length() + 1];
	strcpy(treeFormulaCharArray, testFormula.c_str());

	onFinish(guid, treeFormulaCharArray);


	deletePopulation(population, POP_SIZE);

	delete dl;
	delete ad;

}
