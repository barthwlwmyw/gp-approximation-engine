#pragma once
#include<string>

class AlgorithmInputData
{
public:
	AlgorithmInputData(int dimensions, int datasetSize);

	~AlgorithmInputData();

	double** variablesValues;

	double* resultsValues;

	int dimensions;

	int datasetSize;

	void print();

	std::string toString();
};

