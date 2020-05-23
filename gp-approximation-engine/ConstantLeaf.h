#pragma once
#include"Leaf.h"
class ConstantLeaf :
	public Leaf
{
public:

	ConstantLeaf(double val);

	~ConstantLeaf();

	TreeNode* clone();

	void print();

	double evaluate(double* varValues);

private:

	double value;
};

