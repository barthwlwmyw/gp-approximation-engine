#pragma once
#include "SingleChildNode.h"
#include <string>

class CosinusNode :
	public SingleChildNode
{
public:

	CosinusNode();

	~CosinusNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

