#pragma once
#include "DoubleChildNode.h"
class DivisionNode :
	public DoubleChildNode
{
public:

	DivisionNode();

	~DivisionNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

