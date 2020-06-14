#include "pch.h"
#include <iostream>
#include <iomanip>
#include <sstream>
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

std::string  ConstantLeaf::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	return stream.str() + " ";
}

double ConstantLeaf::evaluate(double* varValues) {
	
	return value;
}
