#include "pch.h"
#include <iostream>
#include "DivisionNode.h"
#include "ConstantLeaf.h"
#include "VariableLeaf.h"

DivisionNode::DivisionNode() : DoubleChildNode() {
}

DivisionNode::~DivisionNode() {
}

TreeNode* DivisionNode::clone() {

	DivisionNode* newNode = new DivisionNode();

	newNode->leftChild = leftChild->clone();
	newNode->rightChild = rightChild->clone();

	return newNode;
}

void DivisionNode::print() {
	std::cout << "/ ";
	leftChild->print();
	rightChild->print();
}

double DivisionNode::evaluate(double* varVals) {
	
	double leftSubtreeResult = leftChild->evaluate(varVals);
	double rightSubtreeResult = rightChild->evaluate(varVals);

	if (abs(rightSubtreeResult) > 0.0001) {
		return leftSubtreeResult / rightSubtreeResult;
	}
	else {
		return DBL_MAX/1000;
	}
}
