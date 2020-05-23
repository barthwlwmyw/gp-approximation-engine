#pragma once
#include "DoubleChildNode.h"
class AdditionNode :
	public DoubleChildNode
{
public:

	AdditionNode();

	~AdditionNode();

	TreeNode* clone();

	void print();

	double evaluate(double* varVals);
};

