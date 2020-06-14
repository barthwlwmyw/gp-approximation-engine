#include "pch.h"
#include <iostream>
#include "SubtractionNode.h"
#include "ConstantLeaf.h"
#include "VariableLeaf.h"

SubtractionNode::SubtractionNode() : DoubleChildNode() {
}

SubtractionNode::~SubtractionNode() {
}

TreeNode* SubtractionNode::clone() {

	SubtractionNode* newNode = new SubtractionNode();

	newNode->leftChild = leftChild->clone();
	newNode->rightChild = rightChild->clone();

	return newNode;
}

std::string SubtractionNode::toString() {
	return "- " + leftChild->toString() + rightChild->toString();
}

double SubtractionNode::evaluate(double* varVals) {
	return leftChild->evaluate(varVals) - rightChild->evaluate(varVals);
}

