#pragma once

#ifdef GP_ENG_EXPORTS
#define GP_ENG_API __declspec(dllexport)
#else
#define GP_ENG_API __declspec(dllimport)
#endif

struct GenerationMetadata;

extern "C" GP_ENG_API void runApproximation(
	void __stdcall onProgress(
		char* guid,
		int progress,
		double* evalValues,
		int evalValuesLength,
		GenerationMetadata genMetadata),
	void __stdcall onFinish(
		char* guid, 
		char* treeFormula),
	char* guid,
	char* datafilePath,
	int populationSize,
	int generationsNumber,
	double crossoverProbability, 
	double mutationProbability);