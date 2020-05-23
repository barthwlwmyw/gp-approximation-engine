#include "pch.h"
#include "TreeNodeFactory.h"
#include "AdditionNode.h"
#include "SubtractionNode.h"
#include "DivisionNode.h"
#include "ConstantLeaf.h"
#include "VariableLeaf.h"
#include "SinusNode.h"
#include "MultiplicationNode.h"
#include <cstdlib>

TreeNode* TreeNodeFactory::generateRandomNode(int dimensions) {
	TreeNode* root;

	int rnd = (std::rand() % 100) + 1;


	if (rnd < 40) {
		int rndConst = (std::rand() % 10) + 1;
		return new ConstantLeaf(rndConst);
	}

	if (rnd < 70) {
		int rndDim = (std::rand() % dimensions);
		return new VariableLeaf(rndDim);
	}

	if (rnd < 76) {
		return new DivisionNode();
	}

	if (rnd < 82) {
		return new SubtractionNode();
	}

	if (rnd < 88) {
		return new AdditionNode();
	}

	if (rnd < 94) {
		return new MultiplicationNode();
	}

	return new SinusNode();
}
