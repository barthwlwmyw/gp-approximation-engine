#pragma once
#include "TreeNode.h"
#include "DoubleChildNode.h"

class MultiplicationNode :
	public DoubleChildNode
{
public:

	MultiplicationNode();

	~MultiplicationNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

