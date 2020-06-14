#include "pch.h"
#include "SinusNode.h"
#include <iostream>

SinusNode::SinusNode() : SingleChildNode() {
}

SinusNode::~SinusNode() {
}

TreeNode* SinusNode::clone() {

	SinusNode* newNode = new SinusNode();

	newNode->child = child->clone();

	return newNode;
}

double SinusNode::evaluate(double* varVals) {
	return sin(child->evaluate(varVals));
}

std::string SinusNode::toString() {
	return "SIN ";
}
