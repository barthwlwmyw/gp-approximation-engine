#pragma once
#include "SingleChildNode.h"
class CosinusNode :
	public SingleChildNode
{
public:

	CosinusNode();

	~CosinusNode();

	TreeNode* clone();

	void print();

	double evaluate(double* varVals);
};

