#pragma once
#include "DoubleChildNode.h"
class AdditionNode :
	public DoubleChildNode
{
public:

	AdditionNode();

	~AdditionNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

