#include "pch.h"
#include "AlgorithmInputData.h"
#include <iostream>

AlgorithmInputData::AlgorithmInputData(int dimensions, int datasetSize) {

	this->dimensions = dimensions;
	this->datasetSize = datasetSize;

	resultsValues = new double[datasetSize];
	variablesValues = new double* [datasetSize];

	for (int i = 0; i < datasetSize; i++) {
		variablesValues[i] = new double[dimensions];
	}
}

AlgorithmInputData::~AlgorithmInputData() {

	for (int i = 0; i < this->datasetSize; i++) {
		delete[] variablesValues[i];
	}
	delete[] variablesValues;
	delete[] resultsValues;
}

void AlgorithmInputData::print() {
	std::cout << "dims: " << dimensions << " size: " << datasetSize;
	std::cout << "\n";

	for (int i = 0; i < datasetSize; i++) {
		for (int j = 0; j < dimensions; j++) {
			std::cout << "[" << variablesValues[i][j] << "]";
		}
		std::cout << "\n";
	}

	std::cout << "---\n";
	for (int i = 0; i < datasetSize; i++) {
		std::cout << "[" << resultsValues[i] << "]";
	}
}


std::string AlgorithmInputData::toString() {

	std::string res = "dims: " + std::to_string(dimensions);
	res += "\nsize: " + std::to_string(datasetSize);

	res += "\n";

	for (int i = 0; i < datasetSize; i++) {
		for (int j = 0; j < dimensions; j++) {
			res += "[";
			res += std::to_string(variablesValues[i][j]);
			res += "]";
		}
		res += "\n";
	}

	res += "---\n";
	for (int i = 0; i < datasetSize; i++) {
		res += "[";
		res += std::to_string(resultsValues[i]);
		res += "]";
	}

	return res;
}