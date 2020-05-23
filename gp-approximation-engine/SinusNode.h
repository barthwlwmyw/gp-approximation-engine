#pragma once
#include"SingleChildNode.h"
class SinusNode :
	public SingleChildNode
{
public:

	SinusNode();

	~SinusNode();

	TreeNode* clone();

	void print();

	double evaluate(double* varVals);
};

