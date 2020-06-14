#pragma once
#include"Leaf.h"
#include<string>

class ConstantLeaf :
	public Leaf
{
public:

	ConstantLeaf(double val);

	~ConstantLeaf();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varValues);

private:

	double value;
};

