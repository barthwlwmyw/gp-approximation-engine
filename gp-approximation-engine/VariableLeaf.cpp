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

std::string VariableLeaf::toString() {

	return "X" + std::to_string(variableIdx) + " ";
}

double VariableLeaf::evaluate(double* varValues) {

	return varValues[variableIdx];
}
