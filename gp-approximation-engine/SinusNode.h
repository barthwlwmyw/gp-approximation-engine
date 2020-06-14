#pragma once
#include"SingleChildNode.h"
#include <string>

class SinusNode :
	public SingleChildNode
{
public:

	SinusNode();

	~SinusNode();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varVals);
};

