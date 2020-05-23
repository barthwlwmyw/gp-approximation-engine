#pragma once
#include "DoubleChildNode.h"
class SubtractionNode :
	public DoubleChildNode
{
public:

	SubtractionNode();

	~SubtractionNode();

	TreeNode* clone();

	void print();

	double evaluate(double* varVals);
};

