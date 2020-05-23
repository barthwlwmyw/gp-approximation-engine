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

	void print();

	double evaluate(double* varVals);
};

