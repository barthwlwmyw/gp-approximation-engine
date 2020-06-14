#include "pch.h"
#include "MultiplicationNode.h"
#include <iostream>

MultiplicationNode::MultiplicationNode() : DoubleChildNode() {
}

MultiplicationNode::~MultiplicationNode() {
}

TreeNode* MultiplicationNode::clone() {

	MultiplicationNode* newNode = new MultiplicationNode();

	newNode->leftChild = leftChild->clone();
	newNode->rightChild = rightChild->clone();

	return newNode;
}

std::string MultiplicationNode::toString() {
	return "* " + leftChild->toString() + rightChild->toString();
}

double MultiplicationNode::evaluate(double* varVals) {
	return leftChild->evaluate(varVals) * rightChild->evaluate(varVals);
}
