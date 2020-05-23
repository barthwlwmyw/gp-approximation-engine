#pragma once
#include <string>

#include "AlgorithmInputData.h"

class DataLoader
{
public:
	AlgorithmInputData* getData(std::string filePath);

private:
	int getDatasetSize(std::string filePath);
	int getDimensionsNumber(std::string filePath);
};

