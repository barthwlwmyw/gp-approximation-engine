#pragma once
#include"Leaf.h"
#include<string>

class VariableLeaf :
	public Leaf
{
public:

	VariableLeaf(int varIdx);

	~VariableLeaf();

	TreeNode* clone();

	std::string toString();

	double evaluate(double* varValues);

private:

	int variableIdx;
};

