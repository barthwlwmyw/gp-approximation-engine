#pragma once

#ifdef GP_ENG_EXPORTS
#define GP_ENG_API __declspec(dllexport)
#else
#define GP_ENG_API __declspec(dllimport)
#endif

#include <string>

using namespace std;

struct GenerationMetadata;

extern "C" GP_ENG_API int do_stuff(int a, int b);

extern "C" GP_ENG_API void callback_test(
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
	double mutationProbability);