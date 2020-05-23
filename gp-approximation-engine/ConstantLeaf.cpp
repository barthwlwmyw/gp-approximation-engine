#include "pch.h"
#include<iostream>
#include "ConstantLeaf.h"

ConstantLeaf::ConstantLeaf(double val) :Leaf() {
	value = val;
}

ConstantLeaf::~ConstantLeaf() {
}

TreeNode* ConstantLeaf::clone() {

	ConstantLeaf* newNode = new ConstantLeaf(value);

	return newNode;
}

void ConstantLeaf::print() {
	std::cout << "CONST(" << value << ") ";
}

double ConstantLeaf::evaluate(double* varValues) {
	return value;
}
