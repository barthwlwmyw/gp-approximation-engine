#pragma once
#include "DoubleChildNode.h"
class DivisionNode :
	public DoubleChildNode
{
public:

	DivisionNode();

	~DivisionNode();

	TreeNode* clone();

	void print();

	double evaluate(double* varVals);
};

