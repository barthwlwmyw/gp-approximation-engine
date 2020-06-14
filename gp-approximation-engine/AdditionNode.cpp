#include "pch.h"
#include <iostream>
#include "AdditionNode.h"
#include "ConstantLeaf.h"
#include "VariableLeaf.h"

AdditionNode::AdditionNode() : DoubleChildNode() {
}

AdditionNode::~AdditionNode() {
}

TreeNode* AdditionNode::clone() {

	AdditionNode* newNode = new AdditionNode();

	newNode->leftChild = leftChild->clone();
	newNode->rightChild = rightChild->clone();

	return newNode;
}

std::string AdditionNode::toString() {
	return "+ " + leftChild->toString() + rightChild->toString();
}

double AdditionNode::evaluate(double* varVals) {
	return leftChild->evaluate(varVals) + rightChild->evaluate(varVals);
}
