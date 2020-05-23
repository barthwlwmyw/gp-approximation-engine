#include "pch.h"
#include "Leaf.h"

Leaf::Leaf() :TreeNode() {
}

Leaf::~Leaf() {
}

TreeNode* Leaf::cloneSubtree(int nodeIdx) {
	return nodeIdx == 0 ?
		this->clone() :
		nullptr;
}

int Leaf::getSize() {
	return 1;
}
