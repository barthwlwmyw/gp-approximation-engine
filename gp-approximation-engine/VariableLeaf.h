#pragma once
#include"Leaf.h"
class VariableLeaf :
	public Leaf
{
public:

	VariableLeaf(int varIdx);

	~VariableLeaf();

	TreeNode* clone();

	void print();

	double evaluate(double* varValues);

private:

	int variableIdx;
};

