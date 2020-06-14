#pragma once
#include "DoubleChildNode.h"
#include <string>

class SubtractionNode :
	public DoubleChildNode
{
public:

	SubtractionNode();

	~SubtractionNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

