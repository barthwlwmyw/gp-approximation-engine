#include "pch.h"
#include<iostream>
#include "VariableLeaf.h"

VariableLeaf::VariableLeaf(int varIdx) :Leaf() {
	variableIdx = varIdx;
}

VariableLeaf::~VariableLeaf() {
}

TreeNode* VariableLeaf::clone() {

	TreeNode* newNode = new VariableLeaf(variableIdx);

	return newNode;
}

void VariableLeaf::print() {

	std::cout << "VAR[" << variableIdx << "] ";
}

double VariableLeaf::evaluate(double* varValues) {

	return varValues[variableIdx];
}
