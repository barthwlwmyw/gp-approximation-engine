#include "pch.h"
#include "CosinusNode.h"
#include <iostream>

CosinusNode::CosinusNode() : SingleChildNode() {
}

CosinusNode::~CosinusNode() {
}

TreeNode* CosinusNode::clone() {

	CosinusNode* newNode = new CosinusNode();

	newNode->child = child->clone();

	return newNode;
}

double CosinusNode::evaluate(double* varVals) {
	return cos(child->evaluate(varVals));
}

std::string CosinusNode::toString() {
	return "COS " + child->toString();
}
