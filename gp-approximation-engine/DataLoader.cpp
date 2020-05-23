#include "pch.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "DataLoader.h"

AlgorithmInputData* DataLoader::getData(std::string filePath) {

	AlgorithmInputData* result = new AlgorithmInputData(
		getDimensionsNumber(filePath),
		getDatasetSize(filePath));

	std::fstream dataFile(filePath, std::ios::in);
	if (dataFile.good()) {

		std::string line;

		int i = 0;
		while (std::getline(dataFile, line)) {

			std::stringstream ss(line);
			std::string token;

			int j = 0;
			while (std::getline(ss, token, ' ')) {

				if (j < result->dimensions) {
					result->variablesValues[i][j] = stod(token);
				}
				else {
					result->resultsValues[i] = stod(token);
				}
				j++;
			}
			i++;
		}
	}
	dataFile.close();

	return result;
}

int DataLoader::getDatasetSize(std::string filePath) {

	int result = 0;

	std::fstream dataFile(filePath, std::ios::in);
	if (dataFile.good()) {
		std::string line;
		while (std::getline(dataFile, line)) {
			result++;
		}
	}
	dataFile.close();

	return result;
}

int DataLoader::getDimensionsNumber(std::string filePath) {
	std::string line;
	int result = 0;

	std::fstream dataFile(filePath, std::ios::in);
	if (dataFile.good()) {
		std::getline(dataFile, line);

		std::stringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ' ')) {
			result++;
		}
	}
	dataFile.close();

	return result - 1;
}
